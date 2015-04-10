/*-------------------------------------------------------------
 * new sl2312_ipsec.c
 * Description: the new sl2312_ipsec.c with macro that sets to use
 *				either interrupt or tasklet, or polling. 
 *				Default mode is polling, which is tested working, 
 *				but performs worse than NAPI mode.
 *				Interrupt mode is not maintained.
 *				NAPI mode is well tuned and it performs the best for
 *				hardware-accelerated VPN. Recommend using this one.
 *
 *				CONFIG_CRYPTO_BATCH will enable batch implementation
 *				which will send a batch of packet to the crypto engine
 *				at once and read a batch from crypto engine at once.
 *				This is also recommended to turn it on.
 * Modified: Wen Hsu, Feb 08.
 *-----------------------------------------------------------*/
//#define CONFIG_SL2312_IPSEC_INTERRUPT
#define CONFIG_SL2312_IPSEC_TASKLET
//#define CONFIG_SL2312_IPSEC_NAPI
#define CONFIG_CRYPTO_BATCH		// to enable the batch implementation

#include <linux/config.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/compiler.h>
#include <linux/pci.h>
#include <linux/init.h>
#include <linux/ioport.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/rtnetlink.h>
#include <linux/delay.h>
#include <linux/ethtool.h>
#include <linux/mii.h>
#include <linux/completion.h>
#include <asm/hardware.h>
#include <asm/io.h>
#include <asm/system.h>
#include <asm/arch/irqs.h>
#include <asm/arch/sl2312.h>
#include <asm/arch/sl2312_ipsec.h>
#include <linux/dma-mapping.h>
#include <linux/sysctl_storlink.h>
#ifdef CONFIG_SL2312_IPSEC_TASKLET
#include <asm/irq.h>
#endif
#ifdef CONFIG_SL2312_IPSEC_NAPI
#include <asm/irq.h>
#include <linux/netdevice.h>
#endif


#ifdef CONFIG_SL351X_IPSEC
#include <asm/arch/sl351x_ipsec.h>
#endif


/*****************************
 *      const definition     *
 *****************************/
 
#define CONFIG_IPSEC_GEMINI

/* define TX/RX descriptor parameter */
#define     TX_BUF_TOT_LEN		(TX_BUF_SIZE * IPSEC_TX_DESC_NUM)
#define     RX_BUF_TOT_LEN		(RX_BUF_SIZE * IPSEC_RX_DESC_NUM)

/* define EMAC base address */
#define     IPSEC_PHYSICAL_BASE_ADDR	(SL2312_SECURITY_BASE)  //0x51000000
#define     IPSEC_BASE_ADDR			    (IO_ADDRESS(IPSEC_PHYSICAL_BASE_ADDR))
#define     IPSEC_GLOBAL_BASE_ADDR      (IO_ADDRESS(SL2312_GLOBAL_BASE)) 

//#define     IPSEC_IRQ		        0x04

#define     IPSEC_MAX_PACKET_LEN    32768//2048 + 256

#define     APPEND_MODE             0 
#define     CHECK_MODE              1

#define     MIN_HW_CHECKSUM_LEN     60

/* memory management utility */
#define DMA_MALLOC(size,handle)		pci_alloc_consistent(NULL,size,handle)	
#define DMA_MFREE(mem,size,handle)	pci_free_consistent(NULL,size,mem,handle)

#define ipsec_read_reg(offset)              (readl(IPSEC_BASE_ADDR + offset))
//#define ipsec_write_reg(offset,data,mask)    writel( (ipsec_read_reg(offset)&(~mask)) |(data&mask),(IPSEC_BASE_ADDR+offset))
#define ipsec_write_reg2(offset,data)       writel(data,(unsigned int *)(IPSEC_BASE_ADDR + offset))

/* define owner bit */
enum OWN_BIT {
    CPU = 0,
    DMA	= 1
};   

typedef struct IPSEC_PACKET_S qhead;

/*****************************
 * Global Variable Declare   *
 *****************************/
struct IPSEC_TEST_RESULT_S
{
    unsigned int    auth_cmp_result;
    unsigned int    sw_pkt_len;
    unsigned char   sw_cipher[IPSEC_MAX_PACKET_LEN];
    unsigned int    hw_pkt_len;
    unsigned char   hw_cipher[IPSEC_MAX_PACKET_LEN];
} ipsec_result; 

static IPSEC_CIPHER_CBC_T       cbc;
static IPSEC_CIPHER_ECB_T       ecb;
static IPSEC_AUTH_T             auth;
static IPSEC_AUTH_T             fcs_auth;
static IPSEC_HMAC_AUTH_T        auth_hmac;
static IPSEC_CBC_AUTH_T         cbc_auth;
static IPSEC_ECB_AUTH_T         ecb_auth;
static IPSEC_CBC_AUTH_HMAC_T    cbc_auth_hmac;
static IPSEC_ECB_AUTH_HMAC_T    ecb_auth_hmac;

static IPSEC_DESCRIPTOR_T       *rx_desc_index[IPSEC_RX_DESC_NUM];
static unsigned int             rx_index = 0;
static unsigned int pid = 0;
static unsigned int last_rx_pid = 255;

static struct IPSEC_PACKET_S    fcs_op; /* for tcp/ip checksum */
//static unsigned char out_packet[2048];  /* for tcp/ip checksum */

volatile static IPSEC_T			*tp;
static unsigned int     tx_desc_virtual_base = 0;
static unsigned int     rx_desc_virtual_base = 0;
static qhead            *ipsec_queue,dummy[3];
static spinlock_t		ipsec_irq_lock;
static spinlock_t	    ipsec_q_lock;
static spinlock_t		ipsec_polling_lock;
static spinlock_t		ipsec_tx_lock;
static spinlock_t		ipsec_pid_lock;

//static unsigned int     fcs_data_len = 0;
static unsigned int wep_crc_ok = 0;
static unsigned int tkip_mic_ok = 0;
static unsigned int ccmp_mic_ok = 0;

#ifdef CONFIG_SL2312_IPSEC_TASKLET
static IPSEC_TASKLET_INFO_T ipsec_tasklet_data;
static unsigned int flag_tasklet_scheduled = 0;
static unsigned int rx_poll_num = 10;
#endif

#ifdef CONFIG_SL2312_IPSEC_NAPI
static struct net_device *crypto_rx_dev;
static unsigned int flag_tasklet_scheduled = 0;
static unsigned int rx_poll_num = 10;
#endif

#if defined(CONFIG_SL2312_IPSEC_TASKLET) || defined(CONFIG_SL2312_IPSEC_INTERRUPT) || defined(CONFIG_SL2312_IPSEC_NAPI)
static unsigned int polling_flag = 0;
static int polling_process_id = -1;
#endif

#ifdef CONFIG_CRYPTO_BATCH
#ifndef CONFIG_SL351X_IPSEC
#define CRYPTO_QUEUE_SIZE	64
#endif
static IPSEC_DESCRIPTOR_T *first_batch_tx_desc;
extern struct IPSEC_PACKET_S CRYPTO_QUEUE[CRYPTO_QUEUE_SIZE];
static unsigned int tx_desc_count = 0;
static IPSEC_CBC_AUTH_T CBC_AUTH_T_list[CRYPTO_QUEUE_SIZE];
static IPSEC_CBC_AUTH_HMAC_T CBC_AUTH_HMAC_T_list[CRYPTO_QUEUE_SIZE];
static IPSEC_ECB_AUTH_T ECB_AUTH_T_list[CRYPTO_QUEUE_SIZE];
static IPSEC_ECB_AUTH_HMAC_T ECB_AUTH_HMAC_T_list[CRYPTO_QUEUE_SIZE];
static IPSEC_AUTH_T AUTH_T_list[CRYPTO_QUEUE_SIZE];
static IPSEC_HMAC_AUTH_T HMAC_AUTH_T_list[CRYPTO_QUEUE_SIZE];
#endif

/*************************************
 *     Function Prototype            *
 *************************************/
static void ipsec_fcs_init(void);
static void ipsec_hw_auth(unsigned char *ctrl_pkt,int ctrl_len,struct scatterlist *data_pkt, int data_len, unsigned int tqflag,
                            unsigned char *out_pkt,int *out_len);
static void ipsec_hw_cipher(volatile unsigned char *ctrl_pkt,int ctrl_len,volatile struct scatterlist *data_pkt,
							int data_len, unsigned int tqflag,unsigned char *out_pkt,int *out_len);
static void ipsec_hw_fcs(unsigned char *ctrl_pkt,int ctrl_len,struct scatterlist *data_pkt, int data_len, unsigned int tqflag,
                            unsigned char *out_pkt,int *out_len);
static void ipsec_byte_change(unsigned char *in_key,unsigned int in_len,unsigned char *out_key,unsigned int *out_len);
static int ipsec_rx_packet(unsigned int mode);
static int ipsec_tx_packet(struct scatterlist *packet, int len, unsigned int tqflag);
static void ipsec_complete_tx_packet(void);
static int ipsec_auth_and_cipher(struct IPSEC_PACKET_S  *op);
static int ipsec_auth_or_cipher(struct IPSEC_PACKET_S  *op);
static void ipsec_byte_change(unsigned char *in_key,unsigned int in_len,unsigned char *out_key,unsigned int *out_len);
static void ipsec_put_queue(qhead *q,struct IPSEC_PACKET_S *item);
static struct IPSEC_PACKET_S *ipsec_get_queue(qhead *q);
static void start_dma(void);
static int ipsec_interrupt_polling(void);

#ifdef CONFIG_SL2312_IPSEC_INTERRUPT
static irqreturn_t ipsec_interrupt(int irq, void *dev_id, struct pt_regs *regs);
#endif

#ifdef CONFIG_SL2312_IPSEC_TASKLET
static irqreturn_t ipsec_interrupt(int irq, void *dev_id, struct pt_regs *regs);
static int ipsec_napi_func(unsigned long data);
#endif

#ifdef CONFIG_SL2312_IPSEC_NAPI
static irqreturn_t ipsec_interrupt(int irq, void *dev_id, struct pt_regs *regs);
static inline int ipsec_rx_poll(struct net_device *dev, int *budget);
#endif

#ifdef CONFIG_CRYPTO_BATCH
static void process_ipsec_recursive(struct IPSEC_PACKET_S *crypto_queue,int count, int current_count, int loc, int queue_size);
static int ipsec_auth_and_cipher_vpn(struct IPSEC_PACKET_S *op,int count, int cur_loc);
static int ipsec_auth_vpn(struct IPSEC_PACKET_S *op,int count,int cur_loc);
static void ipsec_hw_cipher_vpn(volatile unsigned char *ctrl_pkt,int ctrl_len, volatile unsigned char *data_pkt, 
					 int data_len, unsigned int tqflag, int count);
static int ipsec_fill_desc(IPSEC_DESCRIPTOR_T *desc, unsigned char * data, int len, unsigned int flag, int ownership);
static int desc_free_space(void);
#endif

/************************************************/
/*                 function body                */
/************************************************/
__inline__ unsigned int ipsec_get_time(void)
{
    return (readl(0xf2300000));
}

#if 0    
static unsigned int ipsec_read_reg(unsigned int offset)
{
    volatile unsigned int    reg_val;
    
    reg_val = readl(IPSEC_BASE_ADDR + offset);
	return (reg_val);
}
#endif

static void ipsec_write_reg(unsigned int offset,unsigned int data,unsigned int bit_mask)
{
	volatile unsigned int reg_val;
    unsigned int *addr;
    	
	reg_val = ( ipsec_read_reg(offset) & (~bit_mask) ) | (data & bit_mask);
	addr = (unsigned int *)(IPSEC_BASE_ADDR + offset);
    writel(reg_val,addr);
	return;
}	

void ipsec_sw_reset(void)
{
    unsigned int reg_val;
    
    reg_val = readl(IPSEC_GLOBAL_BASE_ADDR + 0x10) | 0x00000010;
    writel(reg_val,IPSEC_GLOBAL_BASE_ADDR + 0x10);
    return;
}

static void ipsec_put_queue(qhead *q,struct IPSEC_PACKET_S *i)
{
	unsigned long flags;

	spin_lock_irqsave(&ipsec_q_lock, flags);

	i->next = q->next;
	i->prev = q;
	q->next->prev = i;
	q->next = i;

	spin_unlock_irqrestore(&ipsec_q_lock, flags);
	return;
}

static struct IPSEC_PACKET_S * ipsec_get_queue(qhead *q)
{
	struct IPSEC_PACKET_S *i;
	unsigned long flags;

	if(q->prev == q)
	{
		return NULL;
	}

	spin_lock_irqsave(&ipsec_q_lock, flags);
	i = q->prev;
	q->prev = i->prev;
	i->prev->next = i->next;

	spin_unlock_irqrestore(&ipsec_q_lock, flags);

	i->next = i->prev = NULL;
	return i;
}

/*****************************************************************************
 * Function    : ipsec_crypto_hw_process
 * Description : This function processes H/W authentication and cipher.
 *       Input : op_info - the authentication and cipher information for IPSec module.
 *      Output : none.
 *      Return : 0 - success, others - failure.
 *****************************************************************************/
int ipsec_crypto_hw_process(struct IPSEC_PACKET_S  *op_info)
{
    volatile IPSEC_DESCRIPTOR_T  *rx_desc;
	unsigned long flags, flags2, flags3;
	volatile IPSEC_RXDMA_CTRL_T	rxdma_ctrl;
	int available_space = desc_free_space();
    
	if (op_info == NULL) {
		printk("%s::hm. op_info is null o_O?\n",__func__);
		return -1;
	}

	// check if there is an available space for this crypto packet
	if (available_space < 1) {
		printk("%s::tx queue is full a\n",__func__);
		return -1;
	}

	spin_lock_irqsave(&ipsec_pid_lock,flags3);
	op_info->process_id = (pid++) % 256;
	spin_unlock_irqrestore(&ipsec_pid_lock,flags3);

#if defined(CONFIG_SL2312_IPSEC_TASKLET) || defined(CONFIG_SL2312_IPSEC_INTERRUPT) || defined(CONFIG_SL2312_IPSEC_NAPI)
	// first turn off the interrupt, such that there won't be conflict
	spin_lock_irqsave(&ipsec_irq_lock,flags2);
	rxdma_ctrl.bits32 = ipsec_read_reg(IPSEC_RXDMA_CTRL);
	rxdma_ctrl.bits.rd_eof_en = 0;
	ipsec_write_reg2(IPSEC_RXDMA_CTRL,rxdma_ctrl.bits32);
	spin_unlock_irqrestore(&ipsec_irq_lock,flags2);

	// 2nd, turn on the polling flag.
	spin_lock_irqsave(&ipsec_polling_lock,flags);
	polling_flag = 1;
//	if (polling_process_id != -1)
//		printk("current polling_process_id %d will be updated to %d, last_rx_pid = %d\n",
//			polling_process_id, op_info->process_id, last_rx_pid);
	polling_process_id = (int)(op_info->process_id);
	spin_unlock_irqrestore(&ipsec_polling_lock,flags);
#endif

#if (ZERO_COPY==1)
	/* get rx descriptor for this operation */
	rx_desc = rx_desc_index[rx_index%IPSEC_RX_DESC_NUM];
	/* set receive buffer address for this operation */
//	consistent_sync(op_info->out_packet,op_info->pkt_len,PCI_DMA_TODEVICE);
	rx_desc->buf_adr = __pa(op_info->out_packet); //virt_to_phys(op_info->out_packet);
//	ipsec_write_reg(IPSEC_RXDMA_BUF_ADDR,rx_desc->buf_adr,0xffffffff);
	unsigned int rxdma_desc = (ipsec_read_reg(IPSEC_RXDMA_CURR_DESC) & 0xfffffff0)+rx_desc_virtual_base;
	if ((unsigned int)rx_desc == (unsigned int)rxdma_desc) {
		ipsec_write_reg2(IPSEC_RXDMA_BUF_ADDR,rx_desc->buf_adr);
		consistent_sync(rx_desc,sizeof(IPSEC_DESCRIPTOR_T),PCI_DMA_TODEVICE);
	}

	if (op_info->out_buffer_len)
		rx_desc->frame_ctrl.bits.buffer_size = op_info->out_buffer_len;
	else
		rx_desc->frame_ctrl.bits.buffer_size = RX_BUF_SIZE;

	rx_index++;
#endif
	ipsec_put_queue(ipsec_queue,op_info);

	if ((op_info->op_mode==ENC_AUTH) || (op_info->op_mode==AUTH_DEC))
	{
		ipsec_auth_and_cipher(op_info);
	}
	else
	{
		ipsec_auth_or_cipher(op_info);
	}
	return 0;
}    

static unsigned char       iv[16];
static unsigned char       cipher_key[32];
static unsigned char       auth_key[64];
static unsigned char       auth_result[20];
    
/*======================================================================================================*/
/*    Generate random packet and do software/hardware authentication/encryption/decryption   */ 
/*======================================================================================================*/
static int ipsec_auth_or_cipher(struct IPSEC_PACKET_S  *op)
{
    unsigned int        iv_size;
	unsigned int		tdflag=0;
	unsigned int        ctrl_pkt_len;
	unsigned int        cipher_key_size;
	unsigned int        auth_key_size;
	unsigned int        auth_result_len;

    if ( (op->op_mode == CIPHER_ENC) || (op->op_mode == CIPHER_DEC) )   /* Encryption & Decryption */
    {
        if ((op->cipher_algorithm == CBC_DES) || (op->cipher_algorithm == CBC_3DES) || (op->cipher_algorithm == CBC_AES))
        {
            memset(&cbc,0x00,sizeof(IPSEC_CIPHER_CBC_T));
            cbc.control.bits.op_mode = op->op_mode;    /* cipher encryption */
            cbc.control.bits.cipher_algorithm = op->cipher_algorithm; /* DES-CBC mode */ 
            cbc.control.bits.process_id = op->process_id;   /* set frame process id */
            cbc.cipher.bits.cipher_header_len = op->cipher_header_len;  /* the header length to be skipped by the cipher */
            cbc.cipher.bits.cipher_algorithm_len = op->cipher_algorithm_len;   /* the length of message body to be encrypted */
            ipsec_byte_change(op->cipher_key,op->cipher_key_size,cipher_key,&cipher_key_size);
            memcpy(cbc.cipher_key,cipher_key,cipher_key_size);
        }
        else
        {    
            memset(&ecb,0x00,sizeof(IPSEC_CIPHER_ECB_T));
            ecb.control.bits.op_mode = op->op_mode;    /* cipher encryption */
            ecb.control.bits.cipher_algorithm = op->cipher_algorithm; /* DES-CBC mode */ 
            ecb.control.bits.process_id = op->process_id;   /* set frame process id */
            ecb.cipher.bits.cipher_header_len = op->cipher_header_len;  /* the header length to be skipped by the cipher */
            ecb.cipher.bits.cipher_algorithm_len = op->cipher_algorithm_len;   /* the length of message body to be encrypted */
            ipsec_byte_change(op->cipher_key,op->cipher_key_size,cipher_key,&cipher_key_size);
            memcpy(ecb.cipher_key,cipher_key,cipher_key_size);
        } 
    }

	if (op->op_mode == AUTH)    /* Authentication */
    {
        if ((op->auth_algorithm == MD5) || (op->auth_algorithm == SHA1) )
        {   
            memset(&auth,0x00,sizeof(IPSEC_AUTH_T));
            auth.var.control.bits.op_mode = op->op_mode;    /* authentication */
            auth.var.control.bits.auth_mode = op->auth_result_mode;  /* append/check authentication result  */
            auth.var.control.bits.auth_algorithm = op->auth_algorithm; /* MD5 */
            auth.var.control.bits.process_id = op->process_id;   /* set frame process id */
            auth.var.auth.bits.auth_header_len = op->auth_header_len;
            auth.var.auth.bits.auth_algorithm_len = op->auth_algorithm_len;
        }
#if 1
        else if (op->auth_algorithm == FCS)
        {
            fcs_auth.var.control.bits.process_id = op->process_id;   /* set frame process id */
            fcs_auth.var.auth.bits.auth_header_len = op->auth_header_len;
            fcs_auth.var.auth.bits.auth_algorithm_len = op->auth_algorithm_len;
//            fcs_auth.var.control.bits.auth_check_len = 4; /* 4-word to be checked or appended */
            ipsec_hw_fcs((unsigned char *)&fcs_auth,28,
                        op->in_packet,op->pkt_len,0x45,
                        ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len); 
            return 0;
        }
#endif        
        else
        {
            memset(&auth_hmac,0x00,sizeof(IPSEC_HMAC_AUTH_T));
            auth_hmac.control.bits.op_mode = op->op_mode;    /* authentication */
            auth_hmac.control.bits.auth_mode = op->auth_result_mode;  /* append/check authentication result  */
            auth_hmac.control.bits.auth_algorithm = op->auth_algorithm; /* MD5 */
            auth_hmac.control.bits.process_id = op->process_id;   /* set frame process id */
            auth_hmac.auth.bits.auth_header_len = op->auth_header_len;
            auth_hmac.auth.bits.auth_algorithm_len = op->auth_algorithm_len;
            ipsec_byte_change(op->auth_key,op->auth_key_size,auth_key,&auth_key_size);
            memcpy(auth_hmac.auth_key,auth_key,auth_key_size);
        }
    }

	switch (op->op_mode)
    {
        case CIPHER_ENC:
        	switch(op->cipher_algorithm)
        	{
            	case CBC_DES:
            	    op->iv_size = 8;
                    ipsec_byte_change(op->iv,op->iv_size,iv,&iv_size);
                    memcpy(cbc.cipher_iv,iv,iv_size);
#ifdef CONFIG_IPSEC_GEMINI                    
                    tdflag = 0x7b;  /* 1+2+8+10+20+40 */
#else                    
                    tdflag = 0x1b;
#endif                    
                    /* hardware encryption */
                    ipsec_hw_cipher((unsigned char *)&cbc,sizeof(IPSEC_CIPHER_CBC_T),
                                    op->in_packet,op->pkt_len,tdflag,
                                    ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
        			break;
        			
                case ECB_DES:
#ifdef CONFIG_IPSEC_GEMINI                    
                    tdflag = 0x73;  /* 1+2+10+20+40 */
#else
                    tdflag = 0x13;
#endif                    
                    /* hardware encryption */
                    ipsec_hw_cipher((unsigned char *)&ecb,sizeof(IPSEC_CIPHER_ECB_T),
                                    op->in_packet,op->pkt_len,tdflag,
                                    ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
                    break;
        			
                case CBC_3DES:
            	    op->iv_size = 8;
                    ipsec_byte_change(op->iv,op->iv_size,iv,&iv_size);
                    memcpy(cbc.cipher_iv,iv,iv_size); /* set IV */
#ifdef CONFIG_IPSEC_GEMINI                    
                    tdflag = 0x7b;
#else
                    tdflag = 0x1b;
#endif                    
                    /* hardware encryption */
                    ipsec_hw_cipher((unsigned char *)&cbc,sizeof(IPSEC_CIPHER_CBC_T),
                                    op->in_packet,op->pkt_len,tdflag,
                                    ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
                    break;
        			
                case ECB_3DES:
#ifdef CONFIG_IPSEC_GEMINI                    
                    tdflag = 0x73;
#else
                    tdflag = 0x13;
#endif                    
                    /* hardware encryption */
                    ipsec_hw_cipher((unsigned char *)&ecb,sizeof(IPSEC_CIPHER_ECB_T),
                                    op->in_packet,op->pkt_len,tdflag,
                                    ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
           			break;
        			
                case CBC_AES:
                    cbc.control.bits.aesnk = op->cipher_key_size/4; /* AES key size */ 
            	    op->iv_size = 16;
                    ipsec_byte_change(op->iv,op->iv_size,iv,&iv_size);
                    memcpy(cbc.cipher_iv,iv,iv_size); /* set IV */
#ifdef CONFIG_IPSEC_GEMINI                    
                    tdflag = 0x7b;
#else
                    tdflag = 0x1b;
#endif                    
                    /* hardware encryption */
                    ipsec_hw_cipher((unsigned char *)&cbc,sizeof(IPSEC_CIPHER_CBC_T),
                                    op->in_packet,op->pkt_len,tdflag,
                                    ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
        			break;
        			
                case ECB_AES:
                    ecb.control.bits.aesnk = op->cipher_key_size/4; /* AES key size */ 
#ifdef CONFIG_IPSEC_GEMINI                    
                    tdflag = 0x73;
#else
                    tdflag = 0x13;
#endif                    
                    /* hardware encryption */
                    ipsec_hw_cipher((unsigned char *)&ecb,sizeof(IPSEC_CIPHER_ECB_T),
                                    op->in_packet,op->pkt_len,tdflag,
                                    ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
        			break;        			
        	}
            break;
            
        case CIPHER_DEC:
        	switch(op->cipher_algorithm)
        	{
            	case CBC_DES:
            	    op->iv_size = 8;
                    ipsec_byte_change(op->iv,op->iv_size,iv,&iv_size);
                    memcpy(cbc.cipher_iv,iv,iv_size); /* set IV */
#ifdef CONFIG_IPSEC_GEMINI                    
                    tdflag = 0x7b;
#else
                    tdflag = 0x1b;
#endif                    
                    /* hardware decryption */
                    ipsec_hw_cipher((unsigned char *)&cbc,sizeof(IPSEC_CIPHER_CBC_T),
                                    op->in_packet,op->pkt_len,tdflag,
                                    ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
        			break;
        			
                case ECB_DES:
#ifdef CONFIG_IPSEC_GEMINI                    
                    tdflag = 0x73;
#else
                    tdflag = 0x13;
#endif                    
                    /* hardware decryption */
                    ipsec_hw_cipher((unsigned char *)&ecb,sizeof(IPSEC_CIPHER_ECB_T),
                                    op->in_packet,op->pkt_len,tdflag,
                                    ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
                    break;
        			
                case CBC_3DES:
            	    op->iv_size = 8;
                    ipsec_byte_change(op->iv,op->iv_size,iv,&iv_size);
                    memcpy(cbc.cipher_iv,iv,iv_size); /* set IV */
#ifdef CONFIG_IPSEC_GEMINI                    
                    tdflag = 0x7b;
#else
                    tdflag = 0x1b;
#endif                    
                    /* hardware decryption */
                    ipsec_hw_cipher((unsigned char *)&cbc,sizeof(IPSEC_CIPHER_CBC_T),
                                    op->in_packet,op->pkt_len,tdflag,
                                    ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
                    break;
        			
                case ECB_3DES:
#ifdef CONFIG_IPSEC_GEMINI                    
                    tdflag = 0x73;
#else
                    tdflag = 0x13;
#endif                    
                    /* hardware decryption */
                    ipsec_hw_cipher((unsigned char *)&ecb,sizeof(IPSEC_CIPHER_ECB_T),
                                    op->in_packet,op->pkt_len,tdflag,
                                    ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
           			break;
        			
                case CBC_AES:
                    cbc.control.bits.aesnk = op->cipher_key_size/4; /* AES key size */ 
            	    op->iv_size = 16;
                    ipsec_byte_change(op->iv,op->iv_size,iv,&iv_size);
                    memcpy(cbc.cipher_iv,iv,iv_size); /* set IV */
#ifdef CONFIG_IPSEC_GEMINI                    
                    tdflag = 0x7b;
#else
                    tdflag = 0x1b;
#endif                    
                    /* hardware decryption */
                    ipsec_hw_cipher((unsigned char *)&cbc,sizeof(IPSEC_CIPHER_CBC_T),
                                    op->in_packet,op->pkt_len,tdflag,
                                    ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
        			break;
        			
                case ECB_AES:
                    ecb.control.bits.aesnk = op->cipher_key_size/4; /* AES key size */ 
#ifdef CONFIG_IPSEC_GEMINI                    
                    tdflag = 0x73;
#else
                    tdflag = 0x13;
#endif                    
                    /* hardware encryption */
                    ipsec_hw_cipher((unsigned char *)&ecb,sizeof(IPSEC_CIPHER_ECB_T),
                                    op->in_packet,op->pkt_len,tdflag,
                                    ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
        			break;        			
        	}
            break;
                        
        case AUTH:
            switch (op->auth_algorithm)
            {
                 case MD5:
                    if (op->auth_result_mode == APPEND_MODE)
                    {
                        ctrl_pkt_len = 8;
#ifdef CONFIG_IPSEC_GEMINI                    
                        tdflag = 0x05; 
#else
                        tdflag = 0x05;
#endif                        
                    }    
                    else
                    {
                        ipsec_result.sw_pkt_len = 16;
                        ipsec_byte_change(ipsec_result.sw_cipher,ipsec_result.sw_pkt_len,auth_result,&auth_result_len);
                        memcpy(auth.var.auth_check_val,auth_result,auth_result_len);
                        ctrl_pkt_len = 28;
#ifdef CONFIG_IPSEC_GEMINI                    
                        tdflag = 0x205;
#else
                        tdflag = 0x45;
#endif                        
                    }    
                        
                    auth.var.control.bits.auth_check_len = 4; /* 4-word to be checked or appended */
                    ipsec_hw_auth((unsigned char *)&auth,ctrl_pkt_len,
                                op->in_packet,op->pkt_len,tdflag,
                                ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);       
                    break;
                    
                case SHA1:    
                    if (op->auth_result_mode == APPEND_MODE)
                    {
                        ctrl_pkt_len = sizeof(IPSEC_AUTH_T) - 20;
#ifdef CONFIG_IPSEC_GEMINI                    
                        tdflag = 0x05;
#else
                        tdflag = 0x05;
#endif                   
                    }    
                    else
                    {
                        ipsec_result.sw_pkt_len = 20;
                        ipsec_byte_change(ipsec_result.sw_cipher,ipsec_result.sw_pkt_len,auth_result,&auth_result_len);
                        memcpy(auth.var.auth_check_val,auth_result,auth_result_len);
                        ctrl_pkt_len = sizeof(IPSEC_AUTH_T);
#ifdef CONFIG_IPSEC_GEMINI                    
                        tdflag = 0x205;
#else
                        tdflag = 0x45;
#endif                        
                    }    
                    auth.var.control.bits.auth_check_len = 5; /* 6-word to be checked or appended */
                    ipsec_hw_auth((unsigned char *)&auth,ctrl_pkt_len,
                                op->in_packet,op->pkt_len,tdflag,
                                ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);       
                    break;
                    
                case HMAC_MD5:
                    if (op->auth_result_mode == APPEND_MODE)
                    {
                        ctrl_pkt_len = sizeof(IPSEC_HMAC_AUTH_T) - 20;
#ifdef CONFIG_IPSEC_GEMINI                    
                        tdflag = 0x185;  /* 1+4+80+100 */
#else
                        tdflag = 0x25;
#endif                        
                    }    
                    else
                    {
                        ipsec_result.sw_pkt_len = 16;
                        ipsec_byte_change(ipsec_result.sw_cipher,ipsec_result.sw_pkt_len,auth_result,&auth_result_len);
                        memcpy(auth_hmac.auth_check_val,auth_result,auth_result_len);
                        ctrl_pkt_len = sizeof(IPSEC_HMAC_AUTH_T);
#ifdef CONFIG_IPSEC_GEMINI                    
                        tdflag = 0x385; /* 1+4+80+100+200 */
#else
                        tdflag = 0x65;
#endif                        
                    }    
                    auth_hmac.control.bits.auth_check_len = 4; /* 4-word to be checked or appended */
                    ipsec_hw_auth((unsigned char *)&auth_hmac,ctrl_pkt_len,
                                op->in_packet,op->pkt_len,tdflag,
                                ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);       
                    break;
                    
                case HMAC_SHA1:
                    if (op->auth_result_mode == APPEND_MODE)
                    {
                        ctrl_pkt_len = sizeof(IPSEC_HMAC_AUTH_T) - 20;
#ifdef CONFIG_IPSEC_GEMINI                    
                        tdflag = 0x185;  /* 1+4+80+100 */
#else
                        tdflag = 0x25;
#endif                        
                    }    
                    else
                    {
                        ipsec_result.sw_pkt_len = 20;
                        ipsec_byte_change(ipsec_result.sw_cipher,ipsec_result.sw_pkt_len,auth_result,&auth_result_len);
                        memcpy(auth_hmac.auth_check_val,auth_result,auth_result_len);
                        ctrl_pkt_len = sizeof(IPSEC_HMAC_AUTH_T);
#ifdef CONFIG_IPSEC_GEMINI                    
                        tdflag = 0x385; /* 1+4+80+100+200 */
#else
                        tdflag = 0x65;
#endif                        
                    }    
                    auth_hmac.control.bits.auth_check_len = 5; /* 6-word to be checked or appended */
                    ipsec_hw_auth((unsigned char *)&auth_hmac,ctrl_pkt_len,
                                op->in_packet,op->pkt_len,tdflag,
                                ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);       
                    break;
                     
                 case FCS:
#if 0                 
                   if (op->auth_result_mode == APPEND_MODE)
                    {
                        ctrl_pkt_len = 8;
                        tdflag = 0x05;
                    }    
                    else

                    {
                        ctrl_pkt_len = 28;
                        tdflag = 0x45;
                    }    
                        
                    ipsec_hw_fcs((unsigned char *)&auth,ctrl_pkt_len,
                                op->in_packet,op->pkt_len,tdflag,
                                ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len); 
#endif
                    ipsec_hw_fcs((unsigned char *)&fcs_auth,28,
                                op->in_packet,op->pkt_len,0x45,
                                ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len); 
                    break;    
                }    
            break;
        
        default:
            break;            
    } 
	return (0);
}


/*======================================================================================================*/
/*    Generate random packet and do software/hardware authentication/encryption/decryption   */ 
/*======================================================================================================*/
static int ipsec_auth_and_cipher(struct IPSEC_PACKET_S  *op)
{
    unsigned char           iv[16];
    unsigned int            iv_size;
	unsigned int		    tdflag=0;
	unsigned char           cipher_key[32];
	unsigned int            cipher_key_size;
	unsigned char           auth_key[64];
	unsigned int            auth_key_size;
	unsigned int            control_packet_len;
	unsigned char           auth_result[20];
	unsigned int            auth_result_len;
    
    /* CBC mode */
	if ((op->cipher_algorithm == CBC_DES) || (op->cipher_algorithm == CBC_3DES) || (op->cipher_algorithm == CBC_AES))
    {
        if ((op->auth_algorithm == MD5) || (op->auth_algorithm == SHA1))
        {
			/* Authentication and Cipher CBC mode */
            memset(&cbc_auth,0x00,sizeof(IPSEC_CBC_AUTH_T));
            cbc_auth.control.bits.op_mode = op->op_mode;    /* cipher encryption */
            cbc_auth.control.bits.cipher_algorithm = op->cipher_algorithm; /* cipher algorithm */ 
            cbc_auth.control.bits.process_id = op->process_id;   /* set frame process id */
            cbc_auth.cipher.bits.cipher_header_len = op->cipher_header_len;  /* the header length to be skipped by the cipher */
            cbc_auth.cipher.bits.cipher_algorithm_len = op->cipher_algorithm_len;   /* the length of message body to be encrypted */
            ipsec_byte_change(op->cipher_key,op->cipher_key_size,cipher_key,&cipher_key_size);
            memcpy(cbc_auth.cipher_key,cipher_key,cipher_key_size);
            cbc_auth.control.bits.auth_algorithm = op->auth_algorithm; /* authentication algorithm */ 
            cbc_auth.control.bits.auth_mode = op->auth_result_mode; /* append/check mode */ 
            cbc_auth.auth.bits.auth_header_len = op->auth_header_len;  /* the header length to be skipped by the cipher */
            cbc_auth.auth.bits.auth_algorithm_len = op->auth_algorithm_len;   /* the length of message body to be encrypted */
			
		}
        else    /* HMAC */
        {
            /* Authentication HMAC mode and Cipher CBC mode */
            memset(&cbc_auth_hmac,0x00,sizeof(IPSEC_CBC_AUTH_HMAC_T));
            cbc_auth_hmac.control.bits.op_mode = op->op_mode;    /* cipher encryption */
            cbc_auth_hmac.control.bits.cipher_algorithm = op->cipher_algorithm; /* cipher algorithm */ 
            cbc_auth_hmac.control.bits.process_id = op->process_id;   /* set frame process id */
            cbc_auth_hmac.cipher.bits.cipher_header_len = op->cipher_header_len;  /* the header length to be skipped by the cipher */
            cbc_auth_hmac.cipher.bits.cipher_algorithm_len = op->cipher_algorithm_len;   /* the length of message body to be encrypted */
            ipsec_byte_change(op->cipher_key,op->cipher_key_size,cipher_key,&cipher_key_size);
            memcpy(cbc_auth_hmac.cipher_key,cipher_key,cipher_key_size);
            cbc_auth_hmac.control.bits.auth_algorithm = op->auth_algorithm; /* authentication algorithm */ 
            cbc_auth_hmac.control.bits.auth_mode = op->auth_result_mode; /* append/check mode */ 
            cbc_auth_hmac.auth.bits.auth_header_len = op->auth_header_len;  /* the header length to be skipped by the cipher */
            cbc_auth_hmac.auth.bits.auth_algorithm_len = op->auth_algorithm_len;   /* the length of message body to be encrypted */
            ipsec_byte_change(op->auth_key,op->auth_key_size,auth_key,&auth_key_size);
            memcpy(cbc_auth_hmac.auth_key,auth_key,auth_key_size);
        }
    }
    else    /* ECB mode */
    {
        if ((op->auth_algorithm == MD5) || (op->auth_algorithm == SHA1))
        {
            /* Authentication and Cipher ECB mode */
            memset(&ecb_auth,0x00,sizeof(IPSEC_ECB_AUTH_T));
            ecb_auth.control.bits.op_mode = op->op_mode;    /* cipher encryption */
            ecb_auth.control.bits.cipher_algorithm = op->cipher_algorithm; /* cipher algorithm */ 
            ecb_auth.control.bits.process_id = op->process_id;   /* set frame process id */
            ecb_auth.cipher.bits.cipher_header_len = op->cipher_header_len;  /* the header length to be skipped by the cipher */
            ecb_auth.cipher.bits.cipher_algorithm_len = op->cipher_algorithm_len;   /* the length of message body to be encrypted */
            ipsec_byte_change(op->cipher_key,op->cipher_key_size,cipher_key,&cipher_key_size);
            memcpy(ecb_auth.cipher_key,cipher_key,cipher_key_size);
            ecb_auth.control.bits.auth_algorithm = op->auth_algorithm; /* authentication algorithm */ 
            ecb_auth.control.bits.auth_mode = op->auth_result_mode; /* append/check mode */ 
            ecb_auth.auth.bits.auth_header_len = op->auth_header_len;  /* the header length to be skipped by the cipher */
            ecb_auth.auth.bits.auth_algorithm_len = op->auth_algorithm_len;   /* the length of message body to be encrypted */
        }
        else    /* HMAC */
        {
            /* Authentication HMAC mode and Cipher ECB mode */
            memset(&ecb_auth_hmac,0x00,sizeof(IPSEC_ECB_AUTH_HMAC_T));
            ecb_auth_hmac.control.bits.op_mode = op->op_mode;    /* cipher encryption */
            ecb_auth_hmac.control.bits.cipher_algorithm = op->cipher_algorithm; /* cipher algorithm */ 
            ecb_auth_hmac.control.bits.process_id = op->process_id;   /* set frame process id */
            ecb_auth_hmac.cipher.bits.cipher_header_len = op->cipher_header_len;  /* the header length to be skipped by the cipher */
            ecb_auth_hmac.cipher.bits.cipher_algorithm_len = op->cipher_algorithm_len;   /* the length of message body to be encrypted */
            ipsec_byte_change(op->cipher_key,op->cipher_key_size,cipher_key,&cipher_key_size);
            memcpy(ecb_auth_hmac.cipher_key,cipher_key,cipher_key_size);
            ecb_auth_hmac.control.bits.auth_algorithm = op->auth_algorithm; /* authentication algorithm */ 
            ecb_auth_hmac.control.bits.auth_mode = op->auth_result_mode; /* append/check mode */ 
            ecb_auth_hmac.auth.bits.auth_header_len = op->auth_header_len;  /* the header length to be skipped by the cipher */
            ecb_auth_hmac.auth.bits.auth_algorithm_len = op->auth_algorithm_len;   /* the length of message body to be encrypted */
            ipsec_byte_change(op->auth_key,op->auth_key_size,auth_key,&auth_key_size);
            memcpy(ecb_auth_hmac.auth_key,auth_key,auth_key_size);
        }
    }    
    
	switch (op->op_mode)
	{
		case ENC_AUTH:
			switch(op->cipher_algorithm)
			{
				case CBC_DES:
					switch (op->auth_algorithm)
					{
						case MD5:
							//control_packet_len = 4 + 4 + 4 + 16 + 32;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10;
							control_packet_len = 60;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x7f;  /* 1+2+4+8+10+20+40 */
#else
							tdflag = 0x1f;
#endif
							/* IPSec Control Register */
							cbc_auth.control.bits.aesnk = 0;
							cbc_auth.control.bits.auth_check_len = 4;
							/* Cipher IV */
							ipsec_byte_change(op->iv,8,iv,&iv_size);
							memcpy(cbc_auth.cipher_iv,iv,iv_size);
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,16,cbc_auth.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(cbc_auth.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}
							ipsec_hw_cipher((unsigned char *)&cbc_auth,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;

						case SHA1:
							//control_packet_len = 4 + 4 + 4 + 16 + 32;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10;
							control_packet_len = 60;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x7f;  /* 1+2+4+8+10+20+40 */
#else
							tdflag = 0x1f;
#endif
							/* IPSec Control Register */
							cbc_auth.control.bits.aesnk = 0;
							cbc_auth.control.bits.auth_check_len = 5;
							/* Cipher IV */
							ipsec_byte_change(op->iv,8,iv,&iv_size);
							memcpy(cbc_auth.cipher_iv,iv,iv_size);
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,20,cbc_auth.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(cbc_auth.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}
							ipsec_hw_cipher((unsigned char *)&cbc_auth,control_packet_len,
									op->in_packet,op->pkt_len,tdflag,
									ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);                                    
							break;
                            
                        case HMAC_MD5:
                            //control_packet_len = 4 + 4 + 4 + 16 + 32 + 64;
                            //tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10 + 0x20;
                            control_packet_len = 124;
#ifdef CONFIG_IPSEC_GEMINI                    
                            tdflag = 0x1ff;  /* 1+2+4+8+10+20+40+80+100 */
#else
                            tdflag = 0x3f;
#endif                            
                            /* IPSec Control Register */
                            cbc_auth_hmac.control.bits.aesnk = 0;
                            cbc_auth_hmac.control.bits.auth_check_len = 4;
                            /* Cipher IV */
                            ipsec_byte_change(op->iv,8,iv,&iv_size);
                            memcpy(cbc_auth_hmac.cipher_iv,iv,iv_size);
                            if (op->auth_result_mode == CHECK_MODE)
                            {
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,16,cbc_auth_hmac.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(cbc_auth_hmac.auth_check_val,auth_result,auth_result_len);
								}
                                control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI                    
                                tdflag = tdflag + 0x200;
#else
                                tdflag = tdflag + 0x40;
#endif                                
                            }
                            
                            ipsec_hw_cipher((unsigned char *)&cbc_auth_hmac,control_packet_len,
                                        op->in_packet,op->pkt_len,tdflag,
                                        ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);                                    
                            break;
                            
                        case HMAC_SHA1:
                            //control_packet_len = 4 + 4 + 4 + 16 + 32 + 64;
                            //tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10 + 0x20;
                            control_packet_len = 124;
#ifdef CONFIG_IPSEC_GEMINI                    
                            tdflag = 0x1ff;  /* 1+2+4+8+10+20+40+80+100 */
#else
                            tdflag = 0x3f;
#endif
							/* IPSec Control Register */
							cbc_auth_hmac.control.bits.aesnk = 0;
							cbc_auth_hmac.control.bits.auth_check_len = 5;
							/* Cipher IV */
							ipsec_byte_change(op->iv,8,iv,&iv_size);
							memcpy(cbc_auth_hmac.cipher_iv,iv,iv_size);
                            if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,20,cbc_auth_hmac.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(cbc_auth_hmac.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&cbc_auth_hmac,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;
					}
					break;

				case ECB_DES:
					switch (op->auth_algorithm)
					{
						case MD5:
							//control_packet_len = 4 + 4 + 4 + 32;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x10;
							control_packet_len = 44;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x77;  /* 1+2+4+10+20+40 */
#else
							tdflag = 0x17;
#endif
							/* IPSec Control Register */
							ecb_auth.control.bits.aesnk = 0;
							ecb_auth.control.bits.auth_check_len = 4;
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,16,ecb_auth.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(ecb_auth.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&ecb_auth,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;

						case SHA1:
							//control_packet_len = 4 + 4 + 4 + 32;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x10;
							control_packet_len = 44;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x77;  /* 1+2+4+10+20+40 */
#else
							tdflag = 0x17;
#endif
							/* IPSec Control Register */
							ecb_auth.control.bits.aesnk = 0;
							ecb_auth.control.bits.auth_check_len = 5;
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,20,ecb_auth.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(ecb_auth.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&ecb_auth,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;

						case HMAC_MD5:
							//control_packet_len = 4 + 4 + 4 + 32 + 64;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x10 + 0x20;
							control_packet_len = 108;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x1f7;  /* 1+2+4+10+20+40+80+100 */
#else
							tdflag = 0x37;
#endif
							/* IPSec Control Register */
							ecb_auth_hmac.control.bits.aesnk = 0;
							ecb_auth_hmac.control.bits.auth_check_len = 4;
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,16,ecb_auth_hmac.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(ecb_auth_hmac.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&ecb_auth_hmac,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;

						case HMAC_SHA1:
							//control_packet_len = 4 + 4 + 4 + 32 + 64;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x10 + 0x20;
							control_packet_len = 108;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x1f7;  /* 1+2+4+10+20+40+80+100 */
#else
							tdflag = 0x37;
#endif
							/* IPSec Control Register */
							ecb_auth_hmac.control.bits.aesnk = 0;
							ecb_auth_hmac.control.bits.auth_check_len = 5;
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,20,ecb_auth_hmac.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(ecb_auth_hmac.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&ecb_auth_hmac,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;
					}
					break;

				case CBC_3DES:
					switch (op->auth_algorithm)
					{
						case MD5:
							//control_packet_len = 4 + 4 + 4 + 16 + 32 ;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10;
							control_packet_len = 60 ;						
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x7f;  /* 1+2+4+8+10+20+40*/
#else
							tdflag = 0x1f;
#endif
							/* IPSec Control Register */
							cbc_auth.control.bits.aesnk = 0;
							cbc_auth.control.bits.auth_check_len = 4;
							/* Cipher IV */
							ipsec_byte_change(op->iv,8,iv,&iv_size);
							memcpy(cbc_auth.cipher_iv,iv,iv_size);
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,16,cbc_auth.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(cbc_auth.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&cbc_auth,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);                                    

							break;

						case SHA1:
							//control_packet_len = 4 + 4 + 4 + 16 + 32;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10;
							control_packet_len = 60 ;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x7f;
#else
							tdflag = 0x1f;
#endif
							/* IPSec Control Register */
							cbc_auth.control.bits.aesnk = 0;
							cbc_auth.control.bits.auth_check_len = 5;
							/* Cipher IV */
							ipsec_byte_change(op->iv,8,iv,&iv_size);
							memcpy(cbc_auth.cipher_iv,iv,iv_size);
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,20,cbc_auth.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(cbc_auth.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&cbc_auth,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;

						case HMAC_MD5:
							//control_packet_len = 4 + 4 + 4 + 16 + 32 + 64;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10 + 0x20;
							control_packet_len = 124;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x1ff;  /* 1+2+4+8+10+20+40+80+100 */
#else
							tdflag = 0x3f;
#endif
							/* IPSec Control Register */
							cbc_auth_hmac.control.bits.aesnk = 0;
							cbc_auth_hmac.control.bits.auth_check_len = 4;
							/* Cipher IV */
							ipsec_byte_change(op->iv,8,iv,&iv_size);
							memcpy(cbc_auth_hmac.cipher_iv,iv,iv_size);
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,16,cbc_auth_hmac.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(cbc_auth_hmac.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&cbc_auth_hmac,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;

						case HMAC_SHA1:
							//control_packet_len = 4 + 4 + 4 + 16 + 32 + 64;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10 + 0x20;
							control_packet_len = 124;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x1ff;
#else
							tdflag = 0x3f;
#endif
							/* IPSec Control Register */
							cbc_auth_hmac.control.bits.aesnk = 0;
							cbc_auth_hmac.control.bits.auth_check_len = 5;
							/* Cipher IV */
							ipsec_byte_change(op->iv,8,iv,&iv_size);
							memcpy(cbc_auth_hmac.cipher_iv,iv,iv_size);
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,20,cbc_auth_hmac.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(cbc_auth_hmac.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&cbc_auth_hmac,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;
					}
					break;

				case ECB_3DES:
					switch (op->auth_algorithm)
					{
						case MD5:
							//control_packet_len = 4 + 4 + 4 + 32;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x10;
							control_packet_len = 44;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x77;  /* 1+2+4+10+20+40*/
#else
							tdflag = 0x17;
#endif
							/* IPSec Control Register */
							ecb_auth.control.bits.aesnk = 0;
							ecb_auth.control.bits.auth_check_len = 4;
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,16,ecb_auth.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(ecb_auth.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&ecb_auth,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;

						case SHA1:
							//control_packet_len = 4 + 4 + 4 + 32 ;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x10;
							control_packet_len = 44;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x77;
#else
							tdflag = 0x17;
#endif
							/* IPSec Control Register */
							ecb_auth.control.bits.aesnk = 0;
							ecb_auth.control.bits.auth_check_len = 5;
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,20,ecb_auth.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(ecb_auth.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&ecb_auth,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;

						case HMAC_MD5:
							//control_packet_len = 4 + 4 + 4 + 32 + 64;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x10 + 0x20;
							control_packet_len = 108;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x1f7;  /* 1+2+4+10+20+40+80+100*/
#else
							tdflag = 0x37;
#endif
							/* IPSec Control Register */
							ecb_auth_hmac.control.bits.aesnk = 0;
							ecb_auth_hmac.control.bits.auth_check_len = 4;
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,16,ecb_auth_hmac.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(ecb_auth_hmac.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&ecb_auth_hmac,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;

						case HMAC_SHA1:
							//control_packet_len = 4 + 4 + 4 + 32 + 64;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x10 + 0x20;
							control_packet_len = 108;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x1f7;
#else
							tdflag = 0x37;
#endif
							/* IPSec Control Register */
							ecb_auth_hmac.control.bits.aesnk = 0;
							ecb_auth_hmac.control.bits.auth_check_len = 5;
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,20,ecb_auth_hmac.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(ecb_auth_hmac.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&ecb_auth_hmac,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;
					}
					break;
        		
				case CBC_AES:
					switch (op->auth_algorithm)
					{
						case MD5:
							//control_packet_len = 4 + 4 + 4 + 16 + 32 ;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10;
							control_packet_len = 60 ;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x7f;  /* 1+2+4+8+10+20+40 */
#else
							tdflag = 0x1f;
#endif
							/* IPSec Control Register */
							cbc_auth.control.bits.aesnk = op->cipher_key_size/4;
							cbc_auth.control.bits.auth_check_len = 4;
							/* Cipher IV */
							ipsec_byte_change(op->iv,16,iv,&iv_size);
							memcpy(cbc_auth.cipher_iv,iv,iv_size);
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,16,cbc_auth.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(cbc_auth.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&cbc_auth,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;

						case SHA1:
							//control_packet_len = 4 + 4 + 4 + 16 + 32;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10;
							control_packet_len = 60 ;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x7f;  /* 1+2+4+8+10+20+40 */
#else
							tdflag = 0x1f;
#endif
							/* IPSec Control Register */
							cbc_auth.control.bits.aesnk = op->cipher_key_size/4;
							cbc_auth.control.bits.auth_check_len = 5;
							/* Cipher IV */
							ipsec_byte_change(op->iv,16,iv,&iv_size);
							memcpy(cbc_auth.cipher_iv,iv,iv_size);
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,20,cbc_auth.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(cbc_auth.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&cbc_auth,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;

						case HMAC_MD5:
							//control_packet_len = 4 + 4 + 4 + 16 + 32 + 64;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10 + 0x20;
							control_packet_len = 124;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x1ff;  /* 1+2+4+8+10+20+40+80+100 */
#else
							tdflag = 0x3f;
#endif
							/* IPSec Control Register */
							cbc_auth_hmac.control.bits.aesnk = op->cipher_key_size/4;
							cbc_auth_hmac.control.bits.auth_check_len = 4;
							/* Cipher IV */
							ipsec_byte_change(op->iv,16,iv,&iv_size);
							memcpy(cbc_auth_hmac.cipher_iv,iv,iv_size);
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,16,cbc_auth_hmac.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(cbc_auth_hmac.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&cbc_auth_hmac,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;

						case HMAC_SHA1:
							//control_packet_len = 4 + 4 + 4 + 16 + 32 + 64;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10 + 0x20;
							control_packet_len = 124;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x1ff;  /* 1+2+4+8+10+20+40+80+100 */
#else
							tdflag = 0x3f;
#endif
							/* IPSec Control Register */
							cbc_auth_hmac.control.bits.aesnk = op->cipher_key_size/4;
							cbc_auth_hmac.control.bits.auth_check_len = 5;
							/* Cipher IV */
							ipsec_byte_change(op->iv,16,iv,&iv_size);
							memcpy(cbc_auth_hmac.cipher_iv,iv,iv_size);
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,20,cbc_auth_hmac.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(cbc_auth_hmac.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&cbc_auth_hmac,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;
					}
					break;

				case ECB_AES:
					switch (op->auth_algorithm)
					{
						case MD5:
							//control_packet_len = 4 + 4 + 4 + 32;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x10;
							control_packet_len = 44;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x77;  /* 1+2+4+10+20+40 */
#else
							tdflag = 0x17;
#endif
							/* IPSec Control Register */
							ecb_auth.control.bits.aesnk = op->cipher_key_size/4;
							ecb_auth.control.bits.auth_check_len = 4;
							if (op->auth_result_mode == CHECK_MODE)
                            {
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,16,ecb_auth.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(ecb_auth.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&ecb_auth,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;

						case SHA1:
							//control_packet_len = 4 + 4 + 4 + 32 ;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x10;
							control_packet_len = 44;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x77;  /* 1+2+4+10+20+40 */
#else
							tdflag = 0x17;
#endif
							/* IPSec Control Register */
							ecb_auth.control.bits.aesnk = op->cipher_key_size/4;
							ecb_auth.control.bits.auth_check_len = 5;
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,20,ecb_auth.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(ecb_auth.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&ecb_auth,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;

						case HMAC_MD5:
							//control_packet_len = 4 + 4 + 4 + 32 + 64;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x10 + 0x20;
							control_packet_len = 108;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x1f7;  /* 1+2+4+10+20+40+80+100 */
#else
							tdflag = 0x37;
#endif
							/* IPSec Control Register */
							ecb_auth_hmac.control.bits.aesnk = op->cipher_key_size/4;
							ecb_auth_hmac.control.bits.auth_check_len = 4;
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,16,ecb_auth_hmac.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(ecb_auth_hmac.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&ecb_auth_hmac,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;

						case HMAC_SHA1:
							//control_packet_len = 4 + 4 + 4 + 32 + 64;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x10 + 0x20;
							control_packet_len = 108;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x1f7;  /* 1+2+4+10+20+40+80+100 */
#else
							tdflag = 0x37;
#endif
							/* IPSec Control Register */
							ecb_auth_hmac.control.bits.aesnk = op->cipher_key_size/4;
							ecb_auth_hmac.control.bits.auth_check_len = 5;
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,20,ecb_auth_hmac.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(ecb_auth_hmac.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&ecb_auth_hmac,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;
					}
					break;
			}
			break;

		case AUTH_DEC:
			switch (op->auth_algorithm)
			{
				case MD5:
					switch(op->cipher_algorithm)
					{
						case CBC_DES:
							//control_packet_len = 4 + 4 + 4 + 16 + 32 ;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10;
							control_packet_len = 60 ;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x7f;  /* 1+2+4+8+10+20+40 */
#else
							tdflag = 0x1f;
#endif
							/* IPSec Control Register */
							cbc_auth.control.bits.aesnk = 0;
							cbc_auth.control.bits.auth_check_len = 4;
							/* Cipher IV */
							ipsec_byte_change(op->iv,8,iv,&iv_size);
							memcpy(cbc_auth.cipher_iv,iv,iv_size);
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,16,cbc_auth.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(cbc_auth.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&cbc_auth,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;

						case ECB_DES:
							//control_packet_len = 4 + 4 + 4 + 32;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x10;
							control_packet_len = 44 ;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x77;  /* 1+2+4+10+20+40 */
#else
							tdflag = 0x17;
#endif
							/* IPSec Control Register */
							ecb_auth.control.bits.aesnk = 0;
							ecb_auth.control.bits.auth_check_len = 4;
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,16,ecb_auth.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(ecb_auth.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&ecb_auth,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;

						case CBC_3DES:
							//control_packet_len = 4 + 4 + 4 + 16 + 32 ;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10;
							control_packet_len = 60 ;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x7f;  /* 1+2+4+8+10+20+40 */
#else
							tdflag = 0x1f;
#endif
							/* IPSec Control Register */
							cbc_auth.control.bits.aesnk = 0;
							cbc_auth.control.bits.auth_check_len = 4;
							/* Cipher IV */
							ipsec_byte_change(op->iv,8,iv,&iv_size);
							memcpy(cbc_auth.cipher_iv,iv,iv_size);
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,16,cbc_auth.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(cbc_auth.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&cbc_auth,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;

						case ECB_3DES:
							//control_packet_len = 4 + 4 + 4 + 32;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x10;
							control_packet_len = 44 ;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x77;  /* 1+2+4+10+20+40 */
#else
							tdflag = 0x17;
#endif
							/* IPSec Control Register */
							ecb_auth.control.bits.aesnk = 0;
							ecb_auth.control.bits.auth_check_len = 4;
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,16,ecb_auth.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(ecb_auth.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&ecb_auth,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;

						case CBC_AES:
							//control_packet_len = 4 + 4 + 4 + 16 + 32 ;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10;
							control_packet_len = 60 ;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x7f;  /* 1+2+4+8+10+20+40 */
#else
							tdflag = 0x1f;
#endif
							/* IPSec Control Register */
							cbc_auth.control.bits.aesnk = op->cipher_key_size/4;
							cbc_auth.control.bits.auth_check_len = 4;
							/* Cipher IV */
							ipsec_byte_change(op->iv,16,iv,&iv_size);
							memcpy(cbc_auth.cipher_iv,iv,iv_size);
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,16,cbc_auth.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(cbc_auth.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&cbc_auth,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;

						case ECB_AES:
							//control_packet_len = 4 + 4 + 4 + 32 ;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x10;
							control_packet_len = 44 ;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x77;  /* 1+2+4+10+20+40 */
#else
							tdflag = 0x17;
#endif
							/* IPSec Control Register */
							ecb_auth.control.bits.aesnk = op->cipher_key_size/4;
							ecb_auth.control.bits.auth_check_len = 4;
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,16,ecb_auth.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(ecb_auth.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&ecb_auth,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;
					}
					break;

				case SHA1:
					switch(op->cipher_algorithm)
					{
						case CBC_DES:
							//control_packet_len = 4 + 4 + 4 + 16 + 32;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10;
							control_packet_len = 60 ;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x7f;  /* 1+2+4+8+10+20+40 */
#else
							tdflag = 0x1f;
#endif
							/* IPSec Control Register */
							cbc_auth.control.bits.aesnk = 0;
							cbc_auth.control.bits.auth_check_len = 5;
							/* Cipher IV */
							ipsec_byte_change(op->iv,8,iv,&iv_size);
							memcpy(cbc_auth.cipher_iv,iv,iv_size);
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,20,cbc_auth.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(cbc_auth.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&cbc_auth,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;

						case ECB_DES:
							//control_packet_len = 4 + 4 + 4 + 32;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x10;
							control_packet_len = 44 ;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x77;  /* 1+2+4+10+20+40 */
#else
							tdflag = 0x17;
#endif
							/* IPSec Control Register */
							ecb_auth.control.bits.aesnk = 0;
							ecb_auth.control.bits.auth_check_len = 5;
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,20,ecb_auth.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(ecb_auth.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&ecb_auth,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;

						case CBC_3DES:
							//control_packet_len = 4 + 4 + 4 + 16 + 32;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10;
							control_packet_len = 60 ;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x7f;  /* 1+2+4+8+10+20+40 */
#else
							tdflag = 0x1f;
#endif
							/* IPSec Control Register */
							cbc_auth.control.bits.aesnk = 0;
							cbc_auth.control.bits.auth_check_len = 5;
							/* Cipher IV */
							ipsec_byte_change(op->iv,8,iv,&iv_size);
							memcpy(cbc_auth.cipher_iv,iv,iv_size);
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,20,cbc_auth.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(cbc_auth.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&cbc_auth,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;

						case ECB_3DES:
							//control_packet_len = 4 + 4 + 4 + 32;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x10;
							control_packet_len = 44 ;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x77;  /* 1+2+4+10+20+40 */
#else
							tdflag = 0x17;
#endif
							/* IPSec Control Register */
							ecb_auth.control.bits.aesnk = 0;
							ecb_auth.control.bits.auth_check_len = 5;
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,20,ecb_auth.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(ecb_auth.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&ecb_auth,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;

						case CBC_AES:
							//control_packet_len = 4 + 4 + 4 + 16 + 32 ;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10;
							control_packet_len = 60 ;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x7f;  /* 1+2+4+8+10+20+40 */
#else
							tdflag = 0x1f;
#endif
							/* IPSec Control Register */
							cbc_auth.control.bits.aesnk = op->cipher_key_size/4;
							cbc_auth.control.bits.auth_check_len = 5;
							/* Cipher IV */
							ipsec_byte_change(op->iv,16,iv,&iv_size);
							memcpy(cbc_auth.cipher_iv,iv,iv_size);
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,20,cbc_auth.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(cbc_auth.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&cbc_auth,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;

						case ECB_AES:
							//control_packet_len = 4 + 4 + 4 + 32;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x10;
							control_packet_len = 44 ;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x77;  /* 1+2+4+10+20+40 */
#else
							tdflag = 0x17;
#endif
							/* IPSec Control Register */
							ecb_auth.control.bits.aesnk = op->cipher_key_size/4;
							ecb_auth.control.bits.auth_check_len = 5;
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,20,ecb_auth.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(ecb_auth.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&ecb_auth,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;
					}
					break;

				case HMAC_MD5:
					switch(op->cipher_algorithm)
					{
						case CBC_DES:
							//control_packet_len = 4 + 4 + 4 + 16 + 32 + 64;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10 + 0x20;
							control_packet_len = 124 ;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x1ff;  /* 1+2+4+8+10+20+40+80+100 */
#else
							tdflag = 0x3f;
#endif
							/* IPSec Control Register */
							cbc_auth_hmac.control.bits.aesnk = 0;
							cbc_auth_hmac.control.bits.auth_check_len = 4;
							/* Cipher IV */
							ipsec_byte_change(op->iv,8,iv,&iv_size);
							memcpy(cbc_auth_hmac.cipher_iv,iv,iv_size);
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,16,cbc_auth_hmac.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(cbc_auth_hmac.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&cbc_auth_hmac,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;

						case ECB_DES:
							//control_packet_len = 4 + 4 + 4 + 32 + 64;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x10 + 0x20;
							control_packet_len = 108 ;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x1f7;  /* 1+2+4+10+20+40+80+100 */
#else
							tdflag = 0x37;
#endif
							/* IPSec Control Register */
							ecb_auth_hmac.control.bits.aesnk = 0;
							ecb_auth_hmac.control.bits.auth_check_len = 4;
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,16,ecb_auth_hmac.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(ecb_auth_hmac.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&ecb_auth_hmac,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;

						case CBC_3DES:
							//control_packet_len = 4 + 4 + 4 + 16 + 32 + 64;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10 + 0x20;
							control_packet_len = 124 ;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x1ff;  /* 1+2+4+8+10+20+40+80+100 */
#else
							tdflag = 0x3f;
#endif
							/* IPSec Control Register */
							cbc_auth_hmac.control.bits.aesnk = 0;
							cbc_auth_hmac.control.bits.auth_check_len = 4;
							/* Cipher IV */
							ipsec_byte_change(op->iv,8,iv,&iv_size);
							memcpy(cbc_auth_hmac.cipher_iv,iv,iv_size);
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,16,cbc_auth_hmac.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(cbc_auth_hmac.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&cbc_auth_hmac,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;

						case ECB_3DES:
							//control_packet_len = 4 + 4 + 4 + 32 + 64;
                            //tdflag = 0x01 + 0x02 + 0x04 + 0x10 + 0x20;
							control_packet_len = 108 ;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x1f7;  /* 1+2+4+10+20+40+80+100 */
#else
							tdflag = 0x37;
#endif
							/* IPSec Control Register */
							ecb_auth_hmac.control.bits.aesnk = 0;
							ecb_auth_hmac.control.bits.auth_check_len = 4;
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,16,ecb_auth_hmac.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(ecb_auth_hmac.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&ecb_auth_hmac,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;

						case CBC_AES:
							//control_packet_len = 4 + 4 + 4 + 16 + 32 + 64;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10 + 0x20;
							control_packet_len = 124 ;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x1ff;
#else
							tdflag = 0x3f;
#endif
							/* IPSec Control Register */
							cbc_auth_hmac.control.bits.aesnk = op->cipher_key_size/4;
							cbc_auth_hmac.control.bits.auth_check_len = 4;
							/* Cipher IV */
							ipsec_byte_change(op->iv,16,iv,&iv_size);
							memcpy(cbc_auth_hmac.cipher_iv,iv,iv_size);
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,16,cbc_auth_hmac.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(cbc_auth_hmac.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&cbc_auth_hmac,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;

						case ECB_AES:
							//control_packet_len = 4 + 4 + 4 + 32 + 64;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x10 + 0x20;
							control_packet_len = 108 ;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x1f7;
#else
							tdflag = 0x37;
#endif
							/* IPSec Control Register */
							ecb_auth_hmac.control.bits.aesnk = op->cipher_key_size/4;
							ecb_auth_hmac.control.bits.auth_check_len = 4;
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,16,ecb_auth_hmac.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(ecb_auth_hmac.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&ecb_auth_hmac,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;
					}
					break;

				case HMAC_SHA1:
					switch(op->cipher_algorithm)
					{
						case CBC_DES:
							//control_packet_len = 4 + 4 + 4 + 16 + 32 + 64;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10 + 0x20;
							control_packet_len = 124 ;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x1ff;
#else
							tdflag = 0x3f;
#endif
							/* IPSec Control Register */
							cbc_auth_hmac.control.bits.aesnk = 0;
							cbc_auth_hmac.control.bits.auth_check_len = 5;
							/* Cipher IV */
							ipsec_byte_change(op->iv,8,iv,&iv_size);
							memcpy(cbc_auth_hmac.cipher_iv,iv,iv_size);
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,20,cbc_auth_hmac.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(cbc_auth_hmac.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&cbc_auth_hmac,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;

						case ECB_DES:
							//control_packet_len = 4 + 4 + 4 + 32 + 64;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x10 + 0x20;
							control_packet_len = 108 ;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x1f7;
#else
							tdflag = 0x37;
#endif
							/* IPSec Control Register */
							ecb_auth_hmac.control.bits.aesnk = 0;
							ecb_auth_hmac.control.bits.auth_check_len = 5;
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,20,ecb_auth_hmac.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(ecb_auth_hmac.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&ecb_auth_hmac,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;

						case CBC_3DES:
							//control_packet_len = 4 + 4 + 4 + 16 + 32 + 64;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10 + 0x20;
							control_packet_len = 124 ;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x1ff;
#else
							tdflag = 0x3f;
#endif
							/* IPSec Control Register */
							cbc_auth_hmac.control.bits.aesnk = 0;
							cbc_auth_hmac.control.bits.auth_check_len = 5;
							/* Cipher IV */
							ipsec_byte_change(op->iv,8,iv,&iv_size);
							memcpy(cbc_auth_hmac.cipher_iv,iv,iv_size);
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,20,cbc_auth_hmac.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(cbc_auth_hmac.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&cbc_auth_hmac,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;

						case ECB_3DES:
							//control_packet_len = 4 + 4 + 4 + 32 + 64;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x10 + 0x20;
							control_packet_len = 108 ;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x1f7;
#else
							tdflag = 0x37;
#endif
							/* IPSec Control Register */
							ecb_auth_hmac.control.bits.aesnk = 0;
							ecb_auth_hmac.control.bits.auth_check_len = 5;
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,20,ecb_auth_hmac.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(ecb_auth_hmac.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&ecb_auth_hmac,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;

						case CBC_AES:
							//control_packet_len = 4 + 4 + 4 + 16 + 32 + 64;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10 + 0x20;
							control_packet_len = 124 ;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x1ff;
#else
							tdflag = 0x3f;
#endif
							/* IPSec Control Register */
							cbc_auth_hmac.control.bits.aesnk = op->cipher_key_size/4;
							cbc_auth_hmac.control.bits.auth_check_len = 5;
							/* Cipher IV */
							ipsec_byte_change(op->iv,16,iv,&iv_size);
							memcpy(cbc_auth_hmac.cipher_iv,iv,iv_size);
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,20,cbc_auth_hmac.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(cbc_auth_hmac.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&cbc_auth_hmac,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;

						case ECB_AES:
							//control_packet_len = 4 + 4 + 4 + 32 + 64;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x10 + 0x20;
							control_packet_len = 108 ;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x1f7;
#else
							tdflag = 0x37;
#endif
							/* IPSec Control Register */
							ecb_auth_hmac.control.bits.aesnk = op->cipher_key_size/4;
							ecb_auth_hmac.control.bits.auth_check_len = 5;
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_checkval) {
									ipsec_byte_change(op->auth_checkval,20,ecb_auth_hmac.auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(ecb_auth_hmac.auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}

							ipsec_hw_cipher((unsigned char *)&ecb_auth_hmac,control_packet_len,
										op->in_packet,op->pkt_len,tdflag,
										ipsec_result.hw_cipher,&ipsec_result.hw_pkt_len);
							break;
					}
					break;
			}
			break;
	}
	return (0);
}


/*======================================================================================================*/
/*    Hardware authentication & encrypt & decrypt function    */ 
/*======================================================================================================*/
//void ipsec_hw_cipher(unsigned char *ctrl_pkt,int ctrl_len,unsigned char *data_pkt, int data_len, unsigned int tqflag,
//                           unsigned char *out_pkt,int *out_len)
void ipsec_hw_cipher(volatile unsigned char *ctrl_pkt,int ctrl_len, volatile struct scatterlist *data_pkt, 
					 int data_len, unsigned int tqflag, unsigned char *out_pkt,int *out_len)
{
	volatile struct				scatterlist sg[1];
	unsigned long		flags;

//	disable_irq(IRQ_IPSEC);
	sg[0].page = virt_to_page(ctrl_pkt);
	sg[0].offset = offset_in_page(ctrl_pkt);
	sg[0].length = ctrl_len;
//	ipsec_tx_packet(ctrl_pkt,ctrl_len,tqflag);
	spin_lock_irqsave(&ipsec_tx_lock,flags);
	ipsec_tx_packet(sg,ctrl_len,tqflag);
	ipsec_tx_packet(data_pkt,data_len,0);
	start_dma();
	spin_unlock_irqrestore(&ipsec_tx_lock,flags);
#if 1
	unsigned int        ipsec_status; 
	unsigned int        i;  

	for (i=0;i<5000;i++)
	{
		ipsec_status = ipsec_read_reg(IPSEC_STATUS_REG);
		if ((ipsec_status & 0x00000fff)==0) /* check IPSec status register */
		{
			break;
		}
	}
	if ((ipsec_status & 0x00000fff) != 0)
	{
		printk("\nipsec_hw_cipher : IPSEC Control Packet Error !!!(%08x)\n",ipsec_status);
		ipsec_write_reg2(IPSEC_STATUS_REG,ipsec_status);
	}
#endif
//	enable_irq(IRQ_IPSEC);

#if !defined(CONFIG_SL2312_IPSEC_INTERRUPT) && !defined(CONFIG_SL2312_IPSEC_TASKLET) && !defined(CONFIG_SL2312_IPSEC_NAPI)
	if(ipsec_interrupt_polling()==0)
   	{
		//printk("ipsec_interrupt_polling: ok\n");
   	}
   	else
   		printk("%s : polling\n",__func__);
#else
	if (polling_flag) {
		if(ipsec_interrupt_polling()==0)
		{
			//printk("ipsec_interrupt_polling: ok\n");
		}
		else
			printk("%s::polling\n",__func__);
	}
#endif
}

void ipsec_hw_auth(unsigned char *ctrl_pkt,int ctrl_len,struct scatterlist *data_pkt, int data_len, unsigned int tqflag,
                            unsigned char *out_pkt,int *out_len)
{
	struct scatterlist sg[1];
	unsigned long		flags;

//	disable_irq(IRQ_IPSEC);
    sg[0].page = virt_to_page(ctrl_pkt);
	sg[0].offset = offset_in_page(ctrl_pkt);
	sg[0].length = ctrl_len;

	spin_lock_irqsave(&ipsec_tx_lock,flags);
	ipsec_tx_packet(sg,ctrl_len,tqflag);
	ipsec_tx_packet(data_pkt,data_len,0);
	start_dma();
	spin_unlock_irqrestore(&ipsec_tx_lock,flags);

#if 1
	unsigned int        ipsec_status;
	unsigned int        i;   

	for (i=0;i<5000;i++)
	{
		ipsec_status = ipsec_read_reg(IPSEC_STATUS_REG);
		if ((ipsec_status & 0x00000fff)==0) /* check IPSec status register */
		{
			break;
		}
    }
    if ((ipsec_status & 0x00000fff) != 0)
    {
        printk("\nipsec_hw_auth : IPSEC Control Packet Error !!!(%08x)\n",ipsec_status); 
		ipsec_write_reg2(IPSEC_STATUS_REG,ipsec_status);
    }
#endif
//	enable_irq(IRQ_IPSEC);

#if !defined(CONFIG_SL2312_IPSEC_INTERRUPT) && !defined(CONFIG_SL2312_IPSEC_TASKLET) && !defined(CONFIG_SL2312_IPSEC_NAPI)
	if(ipsec_interrupt_polling()==0)
	{
		//printk("ok\n");
	}
    else
    	printk("%s : polling\n",__func__);
#else
	if (polling_flag) {
		if(ipsec_interrupt_polling()==0)
		{
			//printk("ipsec_interrupt_polling: ok\n");
		}
		else
			printk("%s::polling\n",__func__);
	}
#endif
}    

void ipsec_hw_fcs(unsigned char *ctrl_pkt,int ctrl_len,struct scatterlist *data_pkt, int data_len, unsigned int tqflag,
                            unsigned char *out_pkt,int *out_len)
{
	//IPSEC_DMA_STATUS_T	status;
    unsigned int        ipsec_status;
    //unsigned int        reg_val;
    unsigned int        i;   
	struct scatterlist sg[1];
	unsigned long	flags;

	//	disable_irq(IRQ_IPSEC);

    sg[0].page = virt_to_page(ctrl_pkt);
	sg[0].offset = offset_in_page(ctrl_pkt);
	sg[0].length = ctrl_len;

	//ipsec_tx_packet(ctrl_pkt,ctrl_len,tqflag);
	spin_lock_irqsave(&ipsec_tx_lock,flags);
	ipsec_tx_packet(sg,ctrl_len,tqflag);
	ipsec_tx_packet(data_pkt,data_len,0);
	start_dma();
	spin_unlock_irqrestore(&ipsec_tx_lock,flags);

	for (i=0;i<=100;i++)
	{
		ipsec_status = ipsec_read_reg(IPSEC_STATUS_REG);
		if ((ipsec_status & 0x00000fff)==0) /* check IPSec status register */
		{
			break;
		}
		if ( i == 100)
		{
			printk("\nipsec_hw_fcs : IPSEC Control Packet Error !!!(%08x)\n",ipsec_status);
		}
	}
    

#if !defined(CONFIG_SL2312_IPSEC_INTERRUPT) && !defined(CONFIG_SL2312_IPSEC_TASKLET) && !defined(CONFIG_SL2312_IPSEC_NAPI)
	if (ipsec_interrupt_polling() == 0)
	{
	
	}
#else
	if (polling_flag) {
		if(ipsec_interrupt_polling()==0)
		{
			//printk("ipsec_interrupt_polling: ok\n");
		}
		else
			printk("%s::polling\n",__func__);
	}
#endif
}    

static int ipsec_buf_init(void)
{
	dma_addr_t   tx_first_desc_dma=0;
	dma_addr_t   rx_first_desc_dma=0;
//	dma_addr_t   tx_first_buf_dma=0;
//	dma_addr_t   rx_first_buf_dma=0;
	int    i;

	tp = kmalloc(sizeof(IPSEC_T),GFP_ATOMIC);
	if (tp == NULL)
	{
		printk("memory allocation fail !\n");
	}
	
#if (ZERO_COPY == 0)
	/* allocates TX/RX DMA packet buffer */
	/* tx_buf_virtual:virtual address  tp.tx_bufs_dma:physical address */
	tp->tx_bufs = DMA_MALLOC(TX_BUF_TOT_LEN,(dma_addr_t *)&tp->tx_bufs_dma);
    tx_buf_virtual_base = (unsigned int)tp->tx_bufs - (unsigned int)tp->tx_bufs_dma;
	memset(tp->tx_bufs,0x00,TX_BUF_TOT_LEN);
	tx_first_buf_dma = tp->tx_bufs_dma;		/* physical address of tx buffer */
	tp->rx_bufs = DMA_MALLOC(RX_BUF_TOT_LEN,(dma_addr_t *)&tp->rx_bufs_dma);
    rx_buf_virtual_base = (unsigned int)tp->rx_bufs - (unsigned int)tp->rx_bufs_dma;
	memset(tp->rx_bufs,0x00,RX_BUF_TOT_LEN);
	rx_first_buf_dma = tp->rx_bufs_dma;		/* physical address of rx buffer */
    printk("ipsec tx_buf = %08x\n",(unsigned int)tp->tx_bufs);
    printk("ipsec rx_buf = %08x\n",(unsigned int)tp->rx_bufs);
    printk("ipsec tx_buf_dma = %08x\n",tp->tx_bufs_dma);
    printk("ipsec rx_buf_dma = %08x\n",tp->rx_bufs_dma);
#endif
	
	spin_lock_init(&ipsec_irq_lock);
	spin_lock_init(&ipsec_q_lock);
	spin_lock_init(&ipsec_polling_lock);
	spin_lock_init(&ipsec_tx_lock);
	spin_lock_init(&ipsec_pid_lock);
//	spin_lock_init(&ipsec_rx_lock);
	/* allocates TX/RX descriptors */
	tp->tx_desc = DMA_MALLOC(IPSEC_TX_DESC_NUM*sizeof(IPSEC_DESCRIPTOR_T),(dma_addr_t *)&tp->tx_desc_dma);
    tx_desc_virtual_base = (unsigned int)tp->tx_desc - (unsigned int)tp->tx_desc_dma;
    memset(tp->tx_desc,0x00,IPSEC_TX_DESC_NUM*sizeof(IPSEC_DESCRIPTOR_T));
	tp->rx_desc = DMA_MALLOC(IPSEC_RX_DESC_NUM*sizeof(IPSEC_DESCRIPTOR_T),(dma_addr_t *)&tp->rx_desc_dma);
    rx_desc_virtual_base = (unsigned int)tp->rx_desc - (unsigned int)tp->rx_desc_dma;
    memset(tp->rx_desc,0x00,IPSEC_RX_DESC_NUM*sizeof(IPSEC_DESCRIPTOR_T));

#if (ZERO_COPY == 0)
	if (tp->tx_bufs==0x00 || tp->rx_bufs==0x00 || tp->tx_desc==0x00 || tp->rx_desc==0x00) 
#else
	if (tp->tx_desc==0x00 || tp->rx_desc==0x00) 
#endif
	{
#if (ZERO_COPY == 0)
		if (tp->tx_bufs)
			DMA_MFREE(tp->tx_bufs, TX_BUF_TOT_LEN, (unsigned int)tp->tx_bufs_dma);
		if (tp->rx_bufs)
			DMA_MFREE(tp->rx_bufs, RX_BUF_TOT_LEN, (unsigned int)tp->rx_bufs_dma);
#endif
		if (tp->tx_desc)
			DMA_MFREE(tp->tx_desc, IPSEC_TX_DESC_NUM*sizeof(IPSEC_DESCRIPTOR_T),(unsigned int)tp->tx_desc_dma);
		if (tp->rx_desc)
			DMA_MFREE(tp->rx_desc, IPSEC_RX_DESC_NUM*sizeof(IPSEC_DESCRIPTOR_T),(unsigned int)tp->rx_desc_dma);
		return -ENOMEM;
	}
	
	/* TX descriptors initial */
	tp->tx_cur_desc = tp->tx_desc;          /* virtual address */
	tp->tx_finished_desc = tp->tx_desc;     /* virtual address */
	tx_first_desc_dma = tp->tx_desc_dma;    /* physical address */
	for (i = 1; i < IPSEC_TX_DESC_NUM; i++)
	{
		tp->tx_desc->frame_ctrl.bits.own = CPU; /* set owner to CPU */
		tp->tx_desc->frame_ctrl.bits.buffer_size = TX_BUF_SIZE;  /* set tx buffer size for descriptor */
#if (ZERO_COPY == 0)
		tp->tx_desc->buf_adr = tp->tx_bufs_dma; /* set data buffer address */
		tp->tx_bufs_dma = tp->tx_bufs_dma + TX_BUF_SIZE; /* point to next buffer address */
#endif
		tp->tx_desc_dma = tp->tx_desc_dma + sizeof(IPSEC_DESCRIPTOR_T); /* next tx descriptor DMA address */
		tp->tx_desc->next_desc.next_descriptor = tp->tx_desc_dma | 0x0000000b;
		tp->tx_desc = &tp->tx_desc[1] ; /* next tx descriptor virtual address */
	}
	/* the last descriptor will point back to first descriptor */
	tp->tx_desc->frame_ctrl.bits.own = CPU;
	tp->tx_desc->frame_ctrl.bits.buffer_size = TX_BUF_SIZE;
#if (ZERO_COPY == 0)
	tp->tx_desc->buf_adr = (unsigned int)tp->tx_bufs_dma;
#endif
	tp->tx_desc->next_desc.next_descriptor = tx_first_desc_dma | 0x0000000b;
	tp->tx_desc = tp->tx_cur_desc;
	tp->tx_desc_dma = tx_first_desc_dma;
#if (ZERO_COPY == 0)
	tp->tx_bufs_dma = tx_first_buf_dma;
#endif
	
	/* RX descriptors initial */
	tp->rx_cur_desc = tp->rx_desc;
	rx_first_desc_dma = tp->rx_desc_dma;
	rx_desc_index[0] = tp->rx_desc;
	for (i = 1; i < IPSEC_RX_DESC_NUM; i++)
	{
		tp->rx_desc->frame_ctrl.bits.own = DMA;  /* set owner bit to DMA */
		tp->rx_desc->frame_ctrl.bits.buffer_size = RX_BUF_SIZE; /* set rx buffer size for descriptor */
#if (ZERO_COPY == 0)
		tp->rx_desc->buf_adr = tp->rx_bufs_dma;   /* set data buffer address */
		tp->rx_bufs_dma = tp->rx_bufs_dma + RX_BUF_SIZE;    /* point to next buffer address */
#endif
		tp->rx_desc_dma = tp->rx_desc_dma + sizeof(IPSEC_DESCRIPTOR_T); /* next rx descriptor DMA address */
		tp->rx_desc->next_desc.next_descriptor = tp->rx_desc_dma | 0x0000000b;
		tp->rx_desc = &tp->rx_desc[1]; /* next rx descriptor virtual address */
	    rx_desc_index[i] = tp->rx_desc;
	}
	/* the last descriptor will point back to first descriptor */
	tp->rx_desc->frame_ctrl.bits.own = DMA;
	tp->rx_desc->frame_ctrl.bits.buffer_size = RX_BUF_SIZE;
#if (ZERO_COPY == 0)
	tp->rx_desc->buf_adr = tp->rx_bufs_dma;
#endif
	tp->rx_desc->next_desc.next_descriptor = rx_first_desc_dma | 0x0000000b;
	tp->rx_desc = tp->rx_cur_desc;
	tp->rx_desc_dma = rx_first_desc_dma;
#if (ZERO_COPY == 0)
	tp->rx_bufs_dma = rx_first_buf_dma;
#endif
#ifdef CONFIG_CRYPTO_BATCH
//	memset(sg_list,0,IPSEC_TX_DESC_NUM*sizeof(struct scatterlist));
//	CBC_AUTH_T_list = (IPSEC_CBC_AUTH_T*)kmalloc(CRYPTO_QUEUE_SIZE*sizeof(IPSEC_CBC_AUTH_T),GFP_ATOMIC);
//	CBC_AUTH_HMAC_T_list = (IPSEC_CBC_AUTH_HMAC_T*)kmalloc(CRYPTO_QUEUE_SIZE*sizeof(IPSEC_CBC_AUTH_HMAC_T),GFP_ATOMIC);
//	ECB_AUTH_T_list = (IPSEC_ECB_AUTH_T*)kmalloc(CRYPTO_QUEUE_SIZE*sizeof(IPSEC_ECB_AUTH_T),GFP_ATOMIC);
//	ECB_AUTH_HMAC_T_list = (IPSEC_ECB_AUTH_HMAC_T*)kmalloc(CRYPTO_QUEUE_SIZE*sizeof(IPSEC_ECB_AUTH_HMAC_T),GFP_ATOMIC);
	memset(CBC_AUTH_T_list,0,CRYPTO_QUEUE_SIZE*sizeof(IPSEC_CBC_AUTH_T));
	memset(CBC_AUTH_HMAC_T_list,0,CRYPTO_QUEUE_SIZE*sizeof(IPSEC_CBC_AUTH_HMAC_T));
	memset(ECB_AUTH_T_list,0,CRYPTO_QUEUE_SIZE*sizeof(IPSEC_ECB_AUTH_T));
	memset(ECB_AUTH_HMAC_T_list,0,CRYPTO_QUEUE_SIZE*sizeof(IPSEC_ECB_AUTH_HMAC_T));
#endif
	printk("ipsec tx_desc = %08x\n",(unsigned int)tp->tx_desc);
	printk("ipsec rx_desc = %08x\n",(unsigned int)tp->rx_desc);
	printk("ipsec tx_desc_dma = %08x\n",tp->tx_desc_dma);
	printk("ipsec rx_desc_dma = %08x\n",tp->rx_desc_dma);
	return (0);	
}

static void ipsec_hw_start(void)
{
	volatile IPSEC_TXDMA_CURR_DESC_T	tx_desc;
	volatile IPSEC_RXDMA_CURR_DESC_T	rx_desc;
    volatile IPSEC_TXDMA_CTRL_T			txdma_ctrl,txdma_ctrl_mask;
    volatile IPSEC_RXDMA_CTRL_T			rxdma_ctrl,rxdma_ctrl_mask;
	volatile IPSEC_DMA_STATUS_T			dma_status,dma_status_mask;

    ipsec_sw_reset();
	
	ipsec_write_reg(0xff40,0x00000044,0xffffffff);

	/* program TxDMA Current Descriptor Address register for first descriptor */
	tx_desc.bits32 = (unsigned int)(tp->tx_desc_dma);
	tx_desc.bits.eofie = 0;			// turn off by wen
	tx_desc.bits.dec = 0;
	tx_desc.bits.sof_eof = 0x03;
	ipsec_write_reg(IPSEC_TXDMA_CURR_DESC,tx_desc.bits32,0xffffffff);
	
	/* program RxDMA Current Descriptor Address register for first descriptor */
	rx_desc.bits32 = (unsigned int)(tp->rx_desc_dma);
	rx_desc.bits.eofie = 1;			// turn off by Wen
	rx_desc.bits.dec = 0;
	rx_desc.bits.sof_eof = 0x03;
	ipsec_write_reg(IPSEC_RXDMA_CURR_DESC,rx_desc.bits32,0xffffffff);
		
	/* enable IPSEC interrupt & disable loopback */
//	dma_status.bits32 = (unsigned int)(tp->tx_desc_dma) - 6;
	dma_status.bits32 = 0;
	dma_status.bits.loop_back = 0;
	dma_status_mask.bits32 = 0xffffffff;
	dma_status_mask.bits.loop_back = 1;
	ipsec_write_reg(IPSEC_DMA_STATUS,dma_status.bits32,dma_status_mask.bits32);
	
	txdma_ctrl.bits32 = 0;
	txdma_ctrl.bits.td_start = 0;    /* start DMA transfer */
	txdma_ctrl.bits.td_continue = 0; /* continue DMA operation */
	txdma_ctrl.bits.td_chain_mode = 1; /* chain mode */
	txdma_ctrl.bits.td_prot = 0;
	txdma_ctrl.bits.td_burst_size = 1;
	txdma_ctrl.bits.td_bus = 0;
	txdma_ctrl.bits.td_endian = 0;				// turn off by wen
	txdma_ctrl.bits.td_finish_en = 0;			// turn off by wen
	txdma_ctrl.bits.td_fail_en = 0;				// turn off by wen
	txdma_ctrl.bits.td_perr_en = 0;				// turn off by wen
	txdma_ctrl.bits.td_eod_en = 0;				// turn off by wen
	txdma_ctrl.bits.td_eof_en = 0;				// turn off by wen
	txdma_ctrl_mask.bits32 = 0;
	txdma_ctrl_mask.bits.td_start = 1;    
	txdma_ctrl_mask.bits.td_continue = 1; 
	txdma_ctrl_mask.bits.td_chain_mode = 1;
	txdma_ctrl_mask.bits.td_prot = 0xf;
	txdma_ctrl_mask.bits.td_burst_size = 3;
	txdma_ctrl_mask.bits.td_bus = 3;
	txdma_ctrl_mask.bits.td_endian = 1;
	txdma_ctrl_mask.bits.td_finish_en = 0;		// turn off by wen
	txdma_ctrl_mask.bits.td_fail_en = 0;		// turn off by wen
	txdma_ctrl_mask.bits.td_perr_en = 0;		// turn off by wen
	txdma_ctrl_mask.bits.td_eod_en = 0;			// turn off by wen
	txdma_ctrl_mask.bits.td_eof_en = 0;			// turn off by wen
	ipsec_write_reg(IPSEC_TXDMA_CTRL,txdma_ctrl.bits32,txdma_ctrl_mask.bits32);

	rxdma_ctrl.bits32 = 0;
	rxdma_ctrl.bits.rd_start = 0;    /* start DMA transfer */
	rxdma_ctrl.bits.rd_continue = 0; /* continue DMA operation */
	rxdma_ctrl.bits.rd_chain_mode = 1;   /* chain mode */
	rxdma_ctrl.bits.rd_prot = 0;
	rxdma_ctrl.bits.rd_burst_size = 1;
	rxdma_ctrl.bits.rd_bus = 0;
	rxdma_ctrl.bits.rd_endian = 0;
	rxdma_ctrl.bits.rd_finish_en = 0;			// turn off by wen
	rxdma_ctrl.bits.rd_fail_en = 0;				// turn off by wen
	rxdma_ctrl.bits.rd_perr_en = 0;				// turn off by wen
	rxdma_ctrl.bits.rd_eod_en = 0;				// turn off by wen
	rxdma_ctrl.bits.rd_eof_en = 1;				// turn off by wen
	rxdma_ctrl_mask.bits32 = 0;
	rxdma_ctrl_mask.bits.rd_start = 1;    
	rxdma_ctrl_mask.bits.rd_continue = 1; 
	rxdma_ctrl_mask.bits.rd_chain_mode = 1;
	rxdma_ctrl_mask.bits.rd_prot = 15;
	rxdma_ctrl_mask.bits.rd_burst_size = 3;
	rxdma_ctrl_mask.bits.rd_bus = 3;
	rxdma_ctrl_mask.bits.rd_endian = 1;
	rxdma_ctrl_mask.bits.rd_finish_en = 0;		// turn off by wen
	rxdma_ctrl_mask.bits.rd_fail_en = 0;		// turn off by wen
	rxdma_ctrl_mask.bits.rd_perr_en = 0;		// turn off by wen
	rxdma_ctrl_mask.bits.rd_eod_en = 0;			// turn off by wen
	rxdma_ctrl_mask.bits.rd_eof_en = 1;			// turn off by wen
	ipsec_write_reg(IPSEC_RXDMA_CTRL,rxdma_ctrl.bits32,rxdma_ctrl_mask.bits32);
	
    return;	
}	

static void ipsec_complete_tx_packet(void)
{
    IPSEC_DESCRIPTOR_T	    *tx_complete_desc;
    IPSEC_DESCRIPTOR_T	    *tx_finished_desc = tp->tx_finished_desc;
    unsigned int desc_cnt;
    unsigned int i;
    
	tx_complete_desc = (IPSEC_DESCRIPTOR_T *)((ipsec_read_reg(IPSEC_TXDMA_CURR_DESC) & 0xfffffff0)+tx_desc_virtual_base);
	
//	printk("%s::complete TX\n",__func__);
	/* check tx status and accumulate tx statistics */
    for (;;)
    {
		if (tx_finished_desc->frame_ctrl.bits.own == CPU)
    	{
			if ( (tx_finished_desc->frame_ctrl.bits.derr) ||
    	         (tx_finished_desc->frame_ctrl.bits.perr) )
    	    {
    	        printk("Descriptor Processing Error !!!\n");
    	    }
    	              
            desc_cnt = tx_finished_desc->frame_ctrl.bits.desc_count;

//			if (desc_cnt > 1)
//				printk("%s::%d descriptor counts\n",__func__,desc_cnt);
        	for (i=1; i<desc_cnt; i++)  /* multi_descriptor */
        	{
				tx_finished_desc = (IPSEC_DESCRIPTOR_T *)((tx_finished_desc->next_desc.next_descriptor & 0xfffffff0)+tx_desc_virtual_base);
				tx_finished_desc->frame_ctrl.bits.own = CPU;
         	}
            tx_finished_desc = (IPSEC_DESCRIPTOR_T *)((tx_finished_desc->next_desc.next_descriptor & 0xfffffff0)+tx_desc_virtual_base);
            if (tx_finished_desc == tx_complete_desc)
            {
                break;
            }
        }
     	else
     	{
     	    break;
     	}
    }
    tp->tx_finished_desc = tx_finished_desc;
}	

//static int ipsec_tx_packet(unsigned char *packet, int len, unsigned int tqflag)
static int ipsec_tx_packet(struct scatterlist *packet, int len, unsigned int tqflag)
{
	IPSEC_DESCRIPTOR_T	        *tx_desc = tp->tx_cur_desc;
//	IPSEC_DESCRIPTOR_T			*return_desc = tx_desc;
//	IPSEC_TXDMA_CTRL_T		    tx_ctrl,tx_ctrl_mask;
//	IPSEC_RXDMA_CTRL_T		    rx_ctrl,rx_ctrl_mask;
	unsigned int                desc_cnt;
	unsigned int                i,tmp_len;
	unsigned int                sof;
	unsigned int                last_desc_byte_cnt;
	unsigned char               *pkt_ptr;

	if (tx_desc->frame_ctrl.bits.own != CPU)
	{
		printk("\nipsec_tx_packet : Current Tx Descriptor is in use!\n");
		ipsec_read_reg(0x0000);
	}
//#if (ZERO_COPY == 0)
//    pkt_ptr = packet;
//#else
//    pkt_ptr = kmap(packet[0].page) + packet[0].offset;
//		//consistent_sync(pkt_ptr,packet[0].length,PCI_DMA_TODEVICE);
//    pkt_ptr = (unsigned char *)virt_to_phys(pkt_ptr);  //__pa(packet);   
//	ipsec_write_reg2(IPSEC_TXDMA_BUF_ADDR,(unsigned int)pkt_ptr);
////	
////    consistent_sync(packet,len,PCI_DMA_TODEVICE);
////    pkt_ptr = (unsigned char *)virt_to_phys(packet);  //__pa(packet);
//////	ipsec_write_reg(IPSEC_TXDMA_BUF_ADDR,(unsigned int)pkt_ptr,0xffffffff);
////	ipsec_write_reg2(IPSEC_TXDMA_BUF_ADDR,(unsigned int)pkt_ptr);
//#endif
	sof = 0x02;		/* the first descriptor */
	desc_cnt = (len/TX_BUF_SIZE);
	last_desc_byte_cnt = len % TX_BUF_SIZE;
	//for (i=0; i<desc_cnt ;i++)
	tmp_len=0;i=0;
	while(tmp_len < len)
	{
//		printk("%s::filling in desc@%x\n",__func__,tx_desc);
		tx_desc->frame_ctrl.bits32 = 0;
		tx_desc->flag_status.bits32 = 0;
		
		tx_desc->frame_ctrl.bits.buffer_size = packet[i].length;	/* descriptor byte count */
		tx_desc->flag_status.bits_tx_flag.tqflag = tqflag;			/* set tqflag */

		pkt_ptr = kmap(packet[i].page) + packet[i].offset;
		consistent_sync(pkt_ptr,packet[i].length,PCI_DMA_TODEVICE);
		pkt_ptr = (unsigned char *)virt_to_phys(pkt_ptr);			// __pa(packet);
    
#if (ZERO_COPY == 0)
		memcpy((char *)(tx_desc->buf_adr+tx_buf_virtual_base),pkt_ptr,packet[i].length); /* copy packet to descriptor buffer address */
		//pkt_ptr = &pkt_ptr[packet[i].length];
#else
		tx_desc->buf_adr = (unsigned int)pkt_ptr;
		//pkt_ptr = (unsigned char *)((unsigned int)pkt_ptr + packet[i].length);
#endif
        
		if ( (packet[i].length == len) && i==0 )
        {
			sof = 0x03; /*only one descriptor*/
        }
		else if ( ((packet[i].length + tmp_len)== len) && (i != 0) )
		{
			sof = 0x01;		/*the last descriptor*/
		}
		tx_desc->next_desc.bits.eofie = 1;
		tx_desc->next_desc.bits.dec = 0;
		tx_desc->next_desc.bits.sof_eof = sof;
		if (sof==0x02)
		{
			sof = 0x00;		/* the linking descriptor */
		}

		wmb();

		///middle	
        tmp_len+=packet[i].length;
        i++;

//		printk("%s::tmp_len %d,len %d\n",__func__,tmp_len,len);
    	/* set owner bit */
		tx_desc->frame_ctrl.bits.own = DMA;

		// move to the next tx_desc
        tx_desc = (IPSEC_DESCRIPTOR_T *)((tx_desc->next_desc.next_descriptor & 0xfffffff0)+tx_desc_virtual_base);
	    if (tx_desc->frame_ctrl.bits.own != CPU)
		{
			printk("\nipsec_tx_packet : Next Tx Descriptor is in use!\n");
        }    
	};
	tp->tx_cur_desc = tx_desc;

//	consistent_sync(tx_desc,sizeof(IPSEC_DESCRIPTOR_T),DMA_BIDIRECTIONAL);

	/* if TX DMA process is stop->ed , restart it */
//	if(tqflag>0)
//	return (0);

#if 0
	txdma_busy.bits32 = ipsec_read_reg(IPSEC_TXDMA_FIRST_DESC);
	if (txdma_busy.bits.td_busy == 0)
	{
//		printk("%s::restart Tx/Rx DMA process\n",__func__);
		/* restart Rx DMA process */
		reg_val = ipsec_read_reg(IPSEC_RXDMA_CTRL);
		reg_val |= (0x03<<30);
		ipsec_write_reg2(IPSEC_RXDMA_CTRL, reg_val);

		/* restart Tx DMA process */
		reg_val = ipsec_read_reg(IPSEC_TXDMA_CTRL);
		reg_val |= (0x03<<30);
		ipsec_write_reg2(IPSEC_TXDMA_CTRL, reg_val);
	}
#endif
	return (0);
}

static int ipsec_rx_packet(unsigned int mode)
{
	IPSEC_DESCRIPTOR_T      *rx_desc = tp->rx_cur_desc ;
    struct IPSEC_PACKET_S   *op_info ;
//    unsigned char           *pkt_ptr,*rx_buf_adr;
	unsigned int			pkt_len;
//	unsigned int			remain_pkt_len;
	unsigned int			desc_count;
	unsigned int			process_id=256;
	unsigned int			auth_cmp_result;
	unsigned int			checksum = 0;
//	unsigned int			own; 
	unsigned int			i;
	unsigned long			flags;
	unsigned int			count = 0;

	while ((count < rx_poll_num) || (polling_flag == 1))
    {
		consistent_sync((void *)rx_desc,sizeof(IPSEC_DESCRIPTOR_T),PCI_DMA_FROMDEVICE);

		// debug message
		if ((rx_desc < 0xf0000000) || (rx_desc > 0xffffffff))
			printk("%s::descriptor address is out of range? 0x%x\n",__func__,rx_desc);
		if (rx_desc == NULL)
		{
			printk("%s::WHAT IS GOING ON?!?! rx_desc == NULL?\n",__func__);
			return -1;
		}

//		spin_lock_irqsave(&ipsec_rx_lock,flags_a);
		if (rx_desc->frame_ctrl.bits.own == CPU)
		{
			if ( (rx_desc->frame_ctrl.bits.derr==1)||(rx_desc->frame_ctrl.bits.perr==1) )
			{
				printk("%s:: Descriptor Processing Error !!!\n",__func__);
			}
			pkt_len = rx_desc->flag_status.bits_rx_status.frame_count;  /* total byte count in a frame*/
			process_id = rx_desc->flag_status.bits_rx_status.process_id; /* get process ID from descriptor */
			auth_cmp_result = rx_desc->flag_status.bits_rx_status.auth_result;
			wep_crc_ok = rx_desc->flag_status.bits_rx_status.wep_crc_ok;
			tkip_mic_ok = rx_desc->flag_status.bits_rx_status.tkip_mic_ok;
			ccmp_mic_ok = rx_desc->flag_status.bits_rx_status.ccmp_mic_ok;
			desc_count = rx_desc->frame_ctrl.bits.desc_count; /* get descriptor count per frame */ 
//			checksum = rx_desc->flag_status.bits_rx_status.checksum ;
//			checksum = checksum + rx_desc->frame_ctrl.bits.checksum * 256;
		}
		else
		{
			return count;
		}

		if (last_rx_pid == process_id)
		{
			printk("error!! last_rx_pid = %d, process_id = %d\n",last_rx_pid,process_id);
//			spin_unlock_irqrestore(&ipsec_rx_lock,flags_a);
			rx_desc->frame_ctrl.bits.own = DMA;
			tp->rx_finished_desc = rx_desc;
			/* get next RX descriptor pointer */
			rx_desc = (IPSEC_DESCRIPTOR_T *)((rx_desc->next_desc.next_descriptor & 0xfffffff0)+rx_desc_virtual_base);
			tp->rx_cur_desc = rx_desc;
			return -1;
		}

		if (process_id != 256)
			last_rx_pid = process_id;

		/* get request information from queue */
		if ((op_info = ipsec_get_queue(ipsec_queue))!=NULL)
		{
			/* fill request result */
			op_info->out_pkt_len = pkt_len;
			op_info->auth_cmp_result = auth_cmp_result;
			op_info->checksum = checksum;
			op_info->status = 0;

			// problme might be caused by prefetch and cache.
			mb();
			if ((op_info->out_packet < 0xc0000000) || (op_info->out_packet >= 0xd0000000))
				printk("%s::op_info->out_packet address is out of range? 0x%x\n",__func__,op_info->out_packet);
			consistent_sync((void *)op_info->out_packet,pkt_len,PCI_DMA_FROMDEVICE);
			mb();

			if ((op_info->process_id != process_id))
			{
				op_info->status = 2;
				printk("ipsec_rx_packet:op_info->out_pkt_len =%d , op_info->pkt_len= %d\n",op_info->out_pkt_len,op_info->pkt_len);
				printk("ipsec_rx_packet:Process ID or Packet Length Error %d %d !\n",op_info->process_id,process_id);
            }

#if defined(CONFIG_SL2312_IPSEC_TASKLET) || defined(CONFIG_SL2312_IPSEC_INTERRUPT) || defined(CONFIG_SL2312_IPSEC_NAPI)
			if ((polling_flag == 1 ) && ((int)process_id == polling_process_id)) {
				spin_lock_irqsave(&ipsec_polling_lock,flags);
				polling_flag = 0;
				polling_process_id = -1;
				spin_unlock_irqrestore(&ipsec_polling_lock,flags);
			}
#endif
		}
		else
		{
//			op_info->status = 1;
//			spin_unlock_irqrestore(&ipsec_rx_lock,flags_a);
			printk("ipsec_rx_packet:IPSec Queue Empty!\n");
		}
		count++;

#if (ZERO_COPY == 0)
		if (op_info > 0)
		{
			//pkt_ptr = &op_info->out_packet[0];
			pkt_ptr = op_info->out_packet;
		}

		remain_pkt_len = pkt_len;
#endif

		for (i=0; i<desc_count; i++)
		{
#if (ZERO_COPY == 0)	    
			if (op_info > 0)
			{
				rx_buf_adr = (char *)(rx_desc->buf_adr+rx_buf_virtual_base);
				if ( remain_pkt_len < RX_BUF_SIZE )
				{
					memcpy(pkt_ptr,rx_buf_adr,remain_pkt_len);  
					//hw_memcpy(pkt_ptr,rx_buf_adr,remain_pkt_len);  
				}
				else
				{
					memcpy(pkt_ptr,rx_buf_adr,RX_BUF_SIZE);
					//hw_memcpy(pkt_ptr,rx_buf_adr,RX_BUF_SIZE);
//					pkt_ptr = &pkt_ptr[RX_BUF_SIZE];
					ptr_ptr = pkt_ptr + RX_BUF_SIZE;
					remain_pkt_len = remain_pkt_len - RX_BUF_SIZE;
				}
			}
#endif
			/* return RX descriptor to DMA */
			rx_desc->frame_ctrl.bits.own = DMA;
			consistent_sync((void*)rx_desc,sizeof(IPSEC_DESCRIPTOR_T),PCI_DMA_TODEVICE);
			tp->rx_finished_desc = rx_desc;
			/* get next RX descriptor pointer */
			rx_desc = (IPSEC_DESCRIPTOR_T *)((rx_desc->next_desc.next_descriptor & 0xfffffff0)+rx_desc_virtual_base);
		}
		tp->rx_cur_desc = rx_desc;
//		spin_unlock_irqrestore(&ipsec_rx_lock,flags_a);

		/* to call callback function */
		if (op_info > 0)
		{
			if (op_info->out_packet == NULL)
			{
				printk("%s::shouldn't happen!!!\n",__func__);
				return -1;
			}

			// if callback exists, use callback function, if not. just skip it.
			if (op_info->callback != NULL) {
				op_info->flag_polling = polling_flag;
				op_info->callback(op_info);
			}
		}
	}
	return count;
}

#ifdef CONFIG_SL2312_IPSEC_TASKLET
static int ipsec_napi_func(unsigned long data)
{
	IPSEC_TASKLET_INFO_T *ipsec_info = (IPSEC_TASKLET_INFO_T *)data;
	unsigned long flags, flags1;
	volatile IPSEC_RXDMA_CTRL_T	rxdma_ctrl;
	int rx_count;

//	if (down_trylock(&ipsec_info->sem)!=0) {
//		tasklet_hi_schedule(&ipsec_info->tasklet);
//		cond_resched();
//		return;
//	}

	rx_count = ipsec_rx_packet(0);
	ipsec_complete_tx_packet();

	if (rx_count < 10) {
		flag_tasklet_scheduled = 0;
		spin_lock_irqsave(&ipsec_irq_lock,flags);
		rxdma_ctrl.bits32 = ipsec_read_reg(IPSEC_RXDMA_CTRL);
		rxdma_ctrl.bits.rd_eof_en = 1;
		ipsec_write_reg2(IPSEC_RXDMA_CTRL,rxdma_ctrl.bits32);
		spin_unlock_irqrestore(&ipsec_irq_lock,flags);
//		up(&ipsec_info->sem);
		clear_bit(0,&ipsec_info->sched);
		return 0;
	}
	else {
		tasklet_hi_schedule(&ipsec_info->tasklet);
//		tasklet_schedule(&ipsec_info->tasklet);
//		cond_resched();
		return 1;
	}
}
#endif

#ifdef CONFIG_SL2312_IPSEC_NAPI
static inline int ipsec_rx_poll(struct net_device *dev, int *budget) 
{
	unsigned long flags;
	volatile IPSEC_RXDMA_CTRL_T	rxdma_ctrl;
	int rx_count = 0;

	rx_count = ipsec_rx_packet(0);
	ipsec_complete_tx_packet();

	if (rx_count == 0) {
		flag_tasklet_scheduled = 0;
		netif_rx_complete(dev);
		spin_lock_irqsave(&ipsec_irq_lock,flags);
		rxdma_ctrl.bits32 = ipsec_read_reg(IPSEC_RXDMA_CTRL);
		rxdma_ctrl.bits.rd_eof_en = 1;
		ipsec_write_reg2(IPSEC_RXDMA_CTRL,rxdma_ctrl.bits32);
		spin_unlock_irqrestore(&ipsec_irq_lock,flags);
		return 0;
	}
	else
		return 1;
}
#endif

static irqreturn_t ipsec_interrupt(int irq, void *dev_id, struct pt_regs *regs)
{
	IPSEC_DMA_STATUS_T	status;
	int                 handled = 0;
	unsigned long		flags;
    		
	handled = 1;

	disable_irq(IRQ_IPSEC);

	/* read DMA status */
	status.bits32 = ipsec_read_reg(IPSEC_DMA_STATUS);

	/* clear DMA status */
	ipsec_write_reg(IPSEC_DMA_STATUS,status.bits32,status.bits32);

	//if ((status.bits32 & 0xffffc000)==0)
	//{
	//    break;
	//}  
  
	if ((status.bits32 & 0x63000000) > 0)
	{
		printk("Error :");
		if (status.bits.ts_derr==1)
		{
			printk("AHB bus Error While Tx !!!\n");
		}
		if (status.bits.ts_perr==1)
		{
			printk("Tx Descriptor Protocol Error !!!\n");
		}    
		if (status.bits.rs_derr==1)
		{
			printk("AHB bus Error While Rx !!!\n");
		}
		if (status.bits.rs_perr==1)
		{
			printk("Rx Descriptor Protocol Error !!!\n");         
		} 
	}

#ifdef CONFIG_SL2312_IPSEC_INTERRUPT

	if (status.bits.ts_eofi==1)
	{
		ipsec_complete_tx_packet();
	}
	if (status.bits.rs_eofi==1)
	{
		ipsec_rx_packet(0);
//		mark_bh(RISCOM8_BH);
		if (status.bits.ts_eofi==0) /* Tx interrupt losed */
		{
			ipsec_complete_tx_packet();
		}
	}
#endif
#ifdef CONFIG_SL2312_IPSEC_TASKLET
		
	IPSEC_TASKLET_INFO_T *ipsec_info = &ipsec_tasklet_data;
	volatile IPSEC_RXDMA_CTRL_T	rxdma_ctrl;
	
	// schedule the tasklet
	if (status.bits.rs_eofi == 1)
	{
		spin_lock_irqsave(&ipsec_irq_lock,flags);
		if (!test_and_set_bit(0, &ipsec_info->sched)) {
			rxdma_ctrl.bits32 = ipsec_read_reg(IPSEC_RXDMA_CTRL);
			rxdma_ctrl.bits.rd_eof_en = 0;
			ipsec_write_reg2(IPSEC_RXDMA_CTRL,rxdma_ctrl.bits32);
			flag_tasklet_scheduled = 1;
			tasklet_hi_schedule(&ipsec_info->tasklet);
//			tasklet_schedule(&ipsec_info->tasklet);
			//cond_resched();
		}
		spin_unlock_irqrestore(&ipsec_irq_lock,flags);
	}
#endif
#ifdef CONFIG_SL2312_IPSEC_NAPI
	volatile IPSEC_RXDMA_CTRL_T	rxdma_ctrl;
	
	// schedule the NAPI
	if (status.bits.rs_eofi == 1)
	{
		spin_lock_irqsave(&ipsec_irq_lock,flags);
		if (likely(netif_rx_schedule_prep(crypto_rx_dev))) {
			rxdma_ctrl.bits32 = ipsec_read_reg(IPSEC_RXDMA_CTRL);
			rxdma_ctrl.bits.rd_eof_en = 0;
			ipsec_write_reg2(IPSEC_RXDMA_CTRL,rxdma_ctrl.bits32);
			flag_tasklet_scheduled = 1;
			__netif_rx_schedule(crypto_rx_dev);
		}
		spin_unlock_irqrestore(&ipsec_irq_lock,flags);
	}
#endif
	enable_irq(IRQ_IPSEC);
	return IRQ_RETVAL(handled);
}

static int ipsec_interrupt_polling(void)
{
	IPSEC_DMA_STATUS_T	status;
	unsigned int        i;
	unsigned long		flags;
	int	do_tx_complete = 0;
	volatile IPSEC_RXDMA_CTRL_T	rxdma_ctrl;

	if (polling_flag == 0)
	{
		printk("%s::polling flag has been turned off\n",__func__);
		return 0;
	}

//	disable_irq(IRQ_IPSEC);
	for (i=0;i<40001;i++)
    {
		/* read DMA status */
		status.bits32 = ipsec_read_reg(IPSEC_DMA_STATUS);
//		ipsec_write_reg(IPSEC_DMA_STATUS,status.bits32,status.bits32);

		if (status.bits.rs_eofi==1)
		{
			/* clear DMA status */
			ipsec_write_reg(IPSEC_DMA_STATUS,status.bits32,status.bits32);
			break;
		}
        if (i>40000)
        {
//			ipsec_read_reg(0x0000);
			printk("FCS fail.......\n");
			return -1;
        }
    }

	if (polling_flag == 0)
	{
		printk("%s::polling flag has been turned off 2\n",__func__);
		return 0;
	}

	if (status.bits.rs_eofi==1) {
		ipsec_rx_packet(1);
		do_tx_complete = 1;
	}
//	enable_irq(IRQ_IPSEC);

#if defined(CONFIG_SL2312_IPSEC_TASKLET) || defined(CONFIG_SL2312_IPSEC_INTERRUPT) || defined(CONFIG_SL2312_IPSEC_NAPI)
	if (polling_flag == 1)
	{
		do_tx_complete = 0;
//		printk("%s::gotta run polling more to get to the number we want !!\n",__func__);
//		printk("polling_process_id = %d, last_rx_pid = %d\n",polling_process_id,last_rx_pid);
//		start_dma();
		if(ipsec_interrupt_polling()==0)
		{
			//printk("%s::more polling done!\n",__func__);
		}
		else
			printk("%s::polling\n",__func__);
	}
	else {
		if (flag_tasklet_scheduled != 1) {
			spin_lock_irqsave(&ipsec_irq_lock,flags);
			rxdma_ctrl.bits32 = ipsec_read_reg(IPSEC_RXDMA_CTRL);
			rxdma_ctrl.bits.rd_eof_en = 1;
			ipsec_write_reg2(IPSEC_RXDMA_CTRL,rxdma_ctrl.bits32);
			spin_unlock_irqrestore(&ipsec_irq_lock,flags);
		}
	}

	if (do_tx_complete == 1)
		ipsec_complete_tx_packet();

#endif

#if 0		// original	
	if ((status.bits32 & 0x63000000) > 0)
	{ 
		printk("Error :");       
		if (status.bits.ts_derr==1)
		{
			printk("AHB bus Error While Tx !!!\n");
			return -2;
		}
		if (status.bits.ts_perr==1)
		{
			printk("Tx Descriptor Protocol Error !!!\n");
			return -3;
		}
		if (status.bits.rs_derr==1)
		{
			printk("AHB bus Error While Rx !!!\n");
			return -4;
		}
		if (status.bits.rs_perr==1)
		{
			printk("Rx Descriptor Protocol Error !!!\n");
			return -5;
		}
	}
		
	if (status.bits.ts_eofi==1)
	{
		//printk("ipsec_interrupt_polling: going ipsec_complete_tx_packet\n");
		ipsec_complete_tx_packet();
	}

	//if ((status.bits.rs_eodi==1) || (status.bits.rs_eofi==1))
	if (status.bits.rs_eofi==1)
	{
		//printk("do i get here to check ipsec queue #2?\n");
		ipsec_rx_packet(1);
		if (status.bits.ts_eofi==0) /* Tx interrupt losed */
		{
			ipsec_complete_tx_packet();
		}
	}
#endif
	return 0;    
}

static void ipsec_byte_change(unsigned char *in_key,unsigned int in_len,unsigned char *out_key,unsigned int *out_len)
{
    unsigned int    i,j;
    
    memset(out_key,0x00,sizeof(out_key));
    *out_len = ((in_len + 3)/4) * 4;
    for (i=0;i<(*out_len/4);i++)
    {
        for (j=0;j<4;j++)
        {
            out_key[i*4+(3-j)] =  in_key[i*4+j];
        }
    }        
}

static void ipsec_fcs_init(void)
{
    memset(&fcs_op,0x00,sizeof(fcs_op));
    fcs_op.op_mode = AUTH;
    fcs_op.auth_algorithm = FCS;
    fcs_op.auth_result_mode = CHECK_MODE; 
    fcs_op.callback = NULL;
    fcs_op.auth_header_len = 0;
#if 1    
    memset(&fcs_auth,0x00,sizeof(IPSEC_AUTH_T));
    fcs_auth.var.control.bits.op_mode = fcs_op.op_mode;    /* authentication */
    fcs_auth.var.control.bits.auth_mode = fcs_op.auth_result_mode;  /* append/check authentication result  */
    fcs_auth.var.control.bits.auth_algorithm = fcs_op.auth_algorithm; /* FCS */
    fcs_auth.var.control.bits.auth_check_len = 4; /* 4-word to be checked or appended */
#endif
}

#ifdef CONFIG_SL2312_HW_CHECKSUM
unsigned int csum_partial(const unsigned char * buff, int len, unsigned int sum)
{
    static unsigned int     pid = 0;
    unsigned int            checksum=0;
    
    if (len < MIN_HW_CHECKSUM_LEN)
    {
        checksum = csum_partial_sw(buff,len,sum);
    }
    else
    {
//        fcs_op.process_id = (pid++) % 256;
        fcs_op.in_packet = (unsigned char *)buff;
        fcs_op.pkt_len = len;
        fcs_op.out_packet = (unsigned char *)&out_packet[0];
        fcs_op.auth_algorithm_len = len;
        ipsec_crypto_hw_process(&fcs_op);
//interruptible_sleep_on(&ipsec_wait_q);
        checksum = fcs_op.checksum + sum;
    } 
    return (checksum);
}
unsigned int csum_partial_copy_nocheck(const char *src, char *dst, int len, int sum)
{
    unsigned int            checksum;

    if (len < MIN_HW_CHECKSUM_LEN)
    {
        checksum = csum_partial_copy_nocheck_sw(src,dst,len,sum);    
    }
    else    
    {
        fcs_op.in_packet = (unsigned char *)src;
        fcs_op.pkt_len = len;
        fcs_op.out_packet = (unsigned char *)dst;
        fcs_op.auth_algorithm_len = len;
        ipsec_crypto_hw_process(&fcs_op);
        checksum = fcs_op.checksum + sum;
#if (ZERO_COPY==1)    
        memcpy(dst,src,len);		
#endif        
    }
    return (checksum);
}    


int ipsec_checksum_test(void)
{
    unsigned int    i,j;
    unsigned int    t1,t2;
    unsigned int    sum1,sum2;
    unsigned char   *src;
    unsigned char   *dst;
        
    src = kmalloc(IPSEC_MAX_PACKET_LEN,GFP_ATOMIC);
    dst = kmalloc(IPSEC_MAX_PACKET_LEN,GFP_ATOMIC);

    for(i=0;i<IPSEC_MAX_PACKET_LEN;i++)
    {
        src[i]=i%256;
    }
        
    for (i=64;i<=2048;i=i+64)
    {
        t1 = jiffies;
        for (j=0;j<100000;j++)
        {
            sum1=csum_partial_copy_nocheck_sw(src, dst, i, 0);
        }
        t2 = jiffies;
        sum1 = (sum1 >> 16) + (sum1 & 0x0000ffff);
        if (sum1 > 0xffff)  sum1 = (sum1 & 0x0000ffff) + 1;
        printk("S/W len=%04d sum=%04x time=%04d<===>",i,sum1,t2-t1);

        t1 = jiffies;
        for (j=0;j<100000;j++)
        {
            sum2=csum_partial_copy_nocheck(src, dst, i, 0);
        }
        t2 = jiffies;
        printk("H/W(A) len=%04d sum=%04x time=%04d",i,sum2,t2-t1);
        if (sum1 == sum2)
        {
            printk ("---OK!\n");
        }
        else
        {
            printk("---FAIL!\n");    
        }    
    }

    return (0);        
}
#endif

int ipsec_get_cipher_algorithm(unsigned char *alg_name,unsigned int alg_mode)
{
    static unsigned char name[3][8]={"des","des3_ede","aes"};
    static unsigned int  algorithm[2][3]={{ECB_DES,ECB_3DES,ECB_AES},{CBC_DES,CBC_3DES,CBC_AES}};
    unsigned int         i;

    if ((alg_mode != ECB) && (alg_mode != CBC))
        return -1;
        
    for (i=0;i<3;i++)
    {
        if (strncmp(alg_name,&name[i][0],8) == 0)
        {
            return (algorithm[alg_mode][i]);
        }    
    }
    return -1;
}

int ipsec_get_auth_algorithm(unsigned char *alg_name,unsigned int alg_mode)
{
    static unsigned char name[2][8]={"md5","sha1"};
    static unsigned int  algorithm[2][2]={{MD5,HMAC_MD5},{SHA1,HMAC_SHA1}};
    unsigned int         i;

    //if ((alg_mode != 0) && (alg_mode != 1))
    //    return -1;

//	printk("%s::alg_name=%s,alg_mode=%d\n",__func__,alg_name,alg_mode);
    for (i=0;i<2;i++)
    {
        if (strncmp(alg_name,&name[i][0],8) == 0)
        {
            	return (algorithm[i][alg_mode]);
        }    
    }
    return -1;
}

#ifdef CONFIG_CRYPTO_BATCH
#if 0	// nonrecursive version.. incomplete
int process_ipsec_batch(struct IPSEC_PACKET_S *crypto_queue, int count, int start_loc, int queue_size)
{
	int available_space = desc_free_space();
	int result = 0;
	unsigned long flags;
	int i;

	if (count <= 0)
		return count;

	if (available_space <= 0) {
		printk("%s::available space (%d) is less or equal to 0\n",__func__,available_space);
		return count;
	}

	if (count > available_space) {
		printk("%s::count(%d) vs space(%d)\n",__func__,count,available_space);
		result = count - available_space;
		count = available_space;
	}

	for (i=0;i<count;i++)
		ipsec_put_queue(ipsec_queue,&(crypto_queue[i]));
	for (i=count-1;i>=0;i--)
		ipsec_auth_and_cipher_vpn(&(crypto_queue[i]),i);
}
#endif

//#if 0	// recursive version
int process_ipsec_batch(struct IPSEC_PACKET_S *crypto_queue, int count, int start_loc, int queue_size)
{
	int available_space = desc_free_space();
	int result = 0;
	unsigned long flags;
	
	if (count <= 0)
		return count;

	if (available_space <= 0) {
		return count;
	}

	if (count >= available_space) {
		result = count - available_space + 1;
		count = available_space - 1;
	}
//	printk("%s::count = %d, available space = %d\n",__func__, count, available_space);
	tx_desc_count = 0;

	spin_lock_irqsave(&ipsec_tx_lock,flags);
	process_ipsec_recursive(crypto_queue, count, 0, start_loc, queue_size);
	spin_unlock_irqrestore(&ipsec_tx_lock,flags);

#if defined(CONFIG_SL2312_IPSEC_INTERRUPT) || defined(CONFIG_SL2312_IPSEC_TASKLET) || defined(CONFIG_SL2312_IPSEC_NAPI)
	// restart dma here
	start_dma();
#else
	start_dma();
	if(ipsec_interrupt_polling()==0)
   	{
		//printk("ipsec_interrupt_polling: ok\n");
   	}
   	else
   		printk("%s : polling\n",__func__);
#endif

	return result;
}
//#endif 

static void process_ipsec_recursive(struct IPSEC_PACKET_S *crypto_queue, int count, int current_count, int loc, int queue_size)
{
	IPSEC_DESCRIPTOR_T *rx_desc;
	int cur_loc;
	unsigned int rxdma_desc;
	unsigned long flags;

	if (count > current_count) {
		cur_loc = current_count + loc;
		if (cur_loc >= queue_size)
			cur_loc -= queue_size;
		struct IPSEC_PACKET_S * packet_ptr = (struct IPSEC_PACKET_S*)&(crypto_queue[cur_loc]);
		spin_lock_irqsave(&ipsec_pid_lock,flags);
		packet_ptr->process_id = (pid++) % 256;
		spin_unlock_irqrestore(&ipsec_pid_lock,flags);
		ipsec_put_queue(ipsec_queue,packet_ptr);
		process_ipsec_recursive(crypto_queue,count,current_count+1,loc, queue_size);
		rx_desc = rx_desc_index[(rx_index+(unsigned int)current_count)%IPSEC_RX_DESC_NUM];
//		consistent_sync(packet_ptr->output_skb,SW_RX_BUF_SIZE,DMA_BIDIRECTIONAL);
		rx_desc->buf_adr = __pa(packet_ptr->out_packet);
		if (packet_ptr->out_buffer_len)
			rx_desc->frame_ctrl.bits.buffer_size = packet_ptr->out_buffer_len;
		else
			rx_desc->frame_ctrl.bits.buffer_size = RX_BUF_SIZE;
//		consistent_sync(rx_desc,sizeof(IPSEC_DESCRIPTOR_T),DMA_BIDIRECTIONAL);

		if (current_count == 0) {
			rx_index = rx_index + (unsigned int)count;
			rxdma_desc = (ipsec_read_reg(IPSEC_RXDMA_CURR_DESC) & 0xfffffff0)+rx_desc_virtual_base;
			if ((unsigned int)rx_desc == (unsigned int)rxdma_desc) {
				ipsec_write_reg2(IPSEC_RXDMA_BUF_ADDR,rx_desc->buf_adr);
				if ((rx_desc < 0xf0000000) || (rx_desc > 0xffffffff))
					printk("%s::descriptor address is out of range? 0x%x\n",__func__, rx_desc);
				consistent_sync((void *)rx_desc,sizeof(IPSEC_DESCRIPTOR_T),PCI_DMA_TODEVICE);
			}
		}
		if ((packet_ptr->op_mode == ENC_AUTH) || (packet_ptr->op_mode == AUTH_DEC))
			ipsec_auth_and_cipher_vpn(packet_ptr,current_count,cur_loc);
		else if (packet_ptr->op_mode = AUTH)
			ipsec_auth_vpn(packet_ptr,current_count,cur_loc);
	}
	return;
}

/***
 * Name: ipsec_auth_and_cipher_vpn
 * Description: for each given IPSEC_PACKET_S, it completes the control packet,
 *				and fill control + data packet backwards from (count * 2 + current
 *				tx_desc location)
 **/
static int ipsec_auth_and_cipher_vpn(struct IPSEC_PACKET_S  *op, int count, int cur_loc)
{
    unsigned char           iv[16];
    unsigned int            iv_size;
	unsigned int		    tdflag=0;
	unsigned char           cipher_key[32];
	unsigned int            cipher_key_size;
	unsigned char           auth_key[64];
	unsigned int            auth_key_size;
	unsigned int            control_packet_len;
	unsigned char           auth_result[20];
	unsigned int            auth_result_len;
	IPSEC_CBC_AUTH_T		*cbc_auth_ptr;
	IPSEC_ECB_AUTH_T		*ecb_auth_ptr;
	IPSEC_CBC_AUTH_HMAC_T	*cbc_auth_hmac_ptr;
	IPSEC_ECB_AUTH_HMAC_T	*ecb_auth_hmac_ptr;
    
    /* CBC mode */
	if ((op->cipher_algorithm == CBC_DES) || (op->cipher_algorithm == CBC_3DES) || (op->cipher_algorithm == CBC_AES))
    {
        if ((op->auth_algorithm == MD5) || (op->auth_algorithm == SHA1))
        {
			/* Authentication and Cipher CBC mode */
//			cbc_auth_ptr = (IPSEC_CBC_AUTH_T*)kmalloc(sizeof(IPSEC_CBC_AUTH_T),GFP_ATOMIC);
//			op->ctrl_ptr = (unsigned char*)cbc_auth_ptr;
//			printk("%s::got here in setting ctrl pkt for cipher cbc mode\n",__func__);
			cbc_auth_ptr = &(CBC_AUTH_T_list[cur_loc]);
			memset(cbc_auth_ptr,0,sizeof(IPSEC_CBC_AUTH_T));
			cbc_auth_ptr->control.bits.op_mode = op->op_mode;    /* cipher encryption */
            cbc_auth_ptr->control.bits.cipher_algorithm = op->cipher_algorithm; /* cipher algorithm */ 
            cbc_auth_ptr->control.bits.process_id = op->process_id;   /* set frame process id */
            cbc_auth_ptr->cipher.bits.cipher_header_len = op->cipher_header_len;  /* the header length to be skipped by the cipher */
            cbc_auth_ptr->cipher.bits.cipher_algorithm_len = op->cipher_algorithm_len;   /* the length of message body to be encrypted */
            ipsec_byte_change(op->cipher_key,op->cipher_key_size,cipher_key,&cipher_key_size);
            memcpy(cbc_auth_ptr->cipher_key,cipher_key,cipher_key_size);
            cbc_auth_ptr->control.bits.auth_algorithm = op->auth_algorithm; /* authentication algorithm */ 
            cbc_auth_ptr->control.bits.auth_mode = op->auth_result_mode; /* append/check mode */ 
            cbc_auth_ptr->auth.bits.auth_header_len = op->auth_header_len;  /* the header length to be skipped by the cipher */
            cbc_auth_ptr->auth.bits.auth_algorithm_len = op->auth_algorithm_len;   /* the length of message body to be encrypted */
		}
        else    /* HMAC */
        {
            /* Authentication HMAC mode and Cipher CBC mode */
//			cbc_auth_hmac_ptr = (IPSEC_CBC_AUTH_HMAC_T*)kmalloc(sizeof(IPSEC_CBC_AUTH_HMAC_T),GFP_ATOMIC);
//			op->ctrl_ptr = (unsigned char*)cbc_auth_hmac_ptr;
//			printk("%s::got here in setting ctrl pkt for cipher cbc hmac mode\n",__func__);
			cbc_auth_hmac_ptr = &(CBC_AUTH_HMAC_T_list[cur_loc]);
			memset(cbc_auth_hmac_ptr,0,sizeof(IPSEC_CBC_AUTH_HMAC_T));
            cbc_auth_hmac_ptr->control.bits.op_mode = op->op_mode;    /* cipher encryption */
            cbc_auth_hmac_ptr->control.bits.cipher_algorithm = op->cipher_algorithm; /* cipher algorithm */ 
            cbc_auth_hmac_ptr->control.bits.process_id = op->process_id;   /* set frame process id */
            cbc_auth_hmac_ptr->cipher.bits.cipher_header_len = op->cipher_header_len;  /* the header length to be skipped by the cipher */
            cbc_auth_hmac_ptr->cipher.bits.cipher_algorithm_len = op->cipher_algorithm_len;   /* the length of message body to be encrypted */
            ipsec_byte_change(op->cipher_key,op->cipher_key_size,cipher_key,&cipher_key_size);
            memcpy(cbc_auth_hmac_ptr->cipher_key,cipher_key,cipher_key_size);
            cbc_auth_hmac_ptr->control.bits.auth_algorithm = op->auth_algorithm; /* authentication algorithm */ 
            cbc_auth_hmac_ptr->control.bits.auth_mode = op->auth_result_mode; /* append/check mode */ 
            cbc_auth_hmac_ptr->auth.bits.auth_header_len = op->auth_header_len;  /* the header length to be skipped by the cipher */
            cbc_auth_hmac_ptr->auth.bits.auth_algorithm_len = op->auth_algorithm_len;   /* the length of message body to be encrypted */
            ipsec_byte_change(op->auth_key,op->auth_key_size,auth_key,&auth_key_size);
            memcpy(cbc_auth_hmac_ptr->auth_key,auth_key,auth_key_size);
        }
    }
    else    /* ECB mode */
    {
        if ((op->auth_algorithm == MD5) || (op->auth_algorithm == SHA1))
        {
			/* Authentication and Cipher ECB mode */
//			ecb_auth_ptr = (IPSEC_ECB_AUTH_T*)kmalloc(sizeof(IPSEC_ECB_AUTH_T),GFP_ATOMIC);
//			op->ctrl_ptr = (unsigned char*)ecb_auth_ptr;
//			printk("%s::got here in setting ctrl pkt for cipher ecb mode\n",__func__);
			ecb_auth_ptr = &(ECB_AUTH_T_list[cur_loc]);
			memset(ecb_auth_ptr,0,sizeof(IPSEC_ECB_AUTH_T));
			ecb_auth_ptr->control.bits.op_mode = op->op_mode;    /* cipher encryption */
            ecb_auth_ptr->control.bits.cipher_algorithm = op->cipher_algorithm; /* cipher algorithm */ 
            ecb_auth_ptr->control.bits.process_id = op->process_id;   /* set frame process id */
            ecb_auth_ptr->cipher.bits.cipher_header_len = op->cipher_header_len;  /* the header length to be skipped by the cipher */
            ecb_auth_ptr->cipher.bits.cipher_algorithm_len = op->cipher_algorithm_len;   /* the length of message body to be encrypted */
            ipsec_byte_change(op->cipher_key,op->cipher_key_size,cipher_key,&cipher_key_size);
            memcpy(ecb_auth_ptr->cipher_key,cipher_key,cipher_key_size);
            ecb_auth_ptr->control.bits.auth_algorithm = op->auth_algorithm; /* authentication algorithm */ 
            ecb_auth_ptr->control.bits.auth_mode = op->auth_result_mode; /* append/check mode */ 
            ecb_auth_ptr->auth.bits.auth_header_len = op->auth_header_len;  /* the header length to be skipped by the cipher */
            ecb_auth_ptr->auth.bits.auth_algorithm_len = op->auth_algorithm_len;   /* the length of message body to be encrypted */
        }
        else    /* HMAC */
        {
            /* Authentication HMAC mode and Cipher ECB mode */
//			ecb_auth_hmac_ptr = (IPSEC_ECB_AUTH_HMAC_T*)kmalloc(sizeof(IPSEC_ECB_AUTH_HMAC_T),GFP_ATOMIC);
//			op->ctrl_ptr = (unsigned char*)ecb_auth_hmac_ptr;
//			printk("%s::got here in setting ctrl pkt for cipher ecb hmac mode\n",__func__);
			ecb_auth_hmac_ptr = &(ECB_AUTH_HMAC_T_list[cur_loc]);
			memset(ecb_auth_hmac_ptr,0,sizeof(IPSEC_ECB_AUTH_HMAC_T));
            ecb_auth_hmac_ptr->control.bits.op_mode = op->op_mode;    /* cipher encryption */
            ecb_auth_hmac_ptr->control.bits.cipher_algorithm = op->cipher_algorithm; /* cipher algorithm */ 
            ecb_auth_hmac_ptr->control.bits.process_id = op->process_id;   /* set frame process id */
            ecb_auth_hmac_ptr->cipher.bits.cipher_header_len = op->cipher_header_len;  /* the header length to be skipped by the cipher */
            ecb_auth_hmac_ptr->cipher.bits.cipher_algorithm_len = op->cipher_algorithm_len;   /* the length of message body to be encrypted */
            ipsec_byte_change(op->cipher_key,op->cipher_key_size,cipher_key,&cipher_key_size);
            memcpy(ecb_auth_hmac_ptr->cipher_key,cipher_key,cipher_key_size);
            ecb_auth_hmac_ptr->control.bits.auth_algorithm = op->auth_algorithm; /* authentication algorithm */ 
            ecb_auth_hmac_ptr->control.bits.auth_mode = op->auth_result_mode; /* append/check mode */ 
            ecb_auth_hmac_ptr->auth.bits.auth_header_len = op->auth_header_len;  /* the header length to be skipped by the cipher */
            ecb_auth_hmac_ptr->auth.bits.auth_algorithm_len = op->auth_algorithm_len;   /* the length of message body to be encrypted */
            ipsec_byte_change(op->auth_key,op->auth_key_size,auth_key,&auth_key_size);
            memcpy(ecb_auth_hmac_ptr->auth_key,auth_key,auth_key_size);
        }
    }    
    
	switch (op->op_mode)
	{
		case ENC_AUTH:
			switch(op->cipher_algorithm)
			{
				case CBC_DES:
					switch (op->auth_algorithm)
					{
						case MD5:
							//control_packet_len = 4 + 4 + 4 + 16 + 32;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10;
							control_packet_len = 60;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x7f;  /* 1+2+4+8+10+20+40 */
#else
							tdflag = 0x1f;
#endif
							/* IPSec Control Register */
							cbc_auth_ptr->control.bits.aesnk = 0;
							if (op->auth_check_len)
								cbc_auth_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								cbc_auth_ptr->control.bits.auth_check_len = 4;
							/* Cipher IV */
							ipsec_byte_change(op->iv,8,iv,&iv_size);
							memcpy(cbc_auth_ptr->cipher_iv,iv,iv_size);
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,cbc_auth_ptr->auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(cbc_auth_ptr->auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}
							ipsec_hw_cipher_vpn((unsigned char *)cbc_auth_ptr,control_packet_len,
									op->in_packet2,op->pkt_len,tdflag,count);
							break;

						case SHA1:
							//control_packet_len = 4 + 4 + 4 + 16 + 32;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10;
							control_packet_len = 60;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x7f;  /* 1+2+4+8+10+20+40 */
#else
							tdflag = 0x1f;
#endif
							/* IPSec Control Register */
							cbc_auth_ptr->control.bits.aesnk = 0;
							if (op->auth_check_len)
								cbc_auth_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								cbc_auth_ptr->control.bits.auth_check_len = 5;
							/* Cipher IV */
							ipsec_byte_change(op->iv,8,iv,&iv_size);
							memcpy(cbc_auth_ptr->cipher_iv,iv,iv_size);
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,cbc_auth_ptr->auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(cbc_auth_ptr->auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}
							ipsec_hw_cipher_vpn((unsigned char *)cbc_auth_ptr,control_packet_len,
									op->in_packet2,op->pkt_len,tdflag,count);
							break;

						case HMAC_MD5:
							//control_packet_len = 4 + 4 + 4 + 16 + 32 + 64;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10 + 0x20;
							control_packet_len = 124;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x1ff;  /* 1+2+4+8+10+20+40+80+100 */
#else
							tdflag = 0x3f;
#endif
							/* IPSec Control Register */
							cbc_auth_hmac_ptr->control.bits.aesnk = 0;
							if (op->auth_check_len)
								cbc_auth_hmac_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								cbc_auth_hmac_ptr->control.bits.auth_check_len = 4;
							/* Cipher IV */
							ipsec_byte_change(op->iv,8,iv,&iv_size);
							memcpy(cbc_auth_hmac_ptr->cipher_iv,iv,iv_size);
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,cbc_auth_hmac_ptr->auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(cbc_auth_hmac_ptr->auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}
							ipsec_hw_cipher_vpn((unsigned char *)cbc_auth_hmac_ptr,control_packet_len,
									op->in_packet2,op->pkt_len,tdflag,count);
							break;

						case HMAC_SHA1:
							//control_packet_len = 4 + 4 + 4 + 16 + 32 + 64;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10 + 0x20;
							control_packet_len = 124;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x1ff;  /* 1+2+4+8+10+20+40+80+100 */
#else
							tdflag = 0x3f;
#endif
							/* IPSec Control Register */
							cbc_auth_hmac_ptr->control.bits.aesnk = 0;
							if (op->auth_check_len)
								cbc_auth_hmac_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								cbc_auth_hmac_ptr->control.bits.auth_check_len = 5;
							/* Cipher IV */
							ipsec_byte_change(op->iv,8,iv,&iv_size);
							memcpy(cbc_auth_hmac_ptr->cipher_iv,iv,iv_size);
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,cbc_auth_hmac_ptr->auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(cbc_auth_hmac_ptr->auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}
							ipsec_hw_cipher_vpn((unsigned char *)cbc_auth_hmac_ptr,control_packet_len,
									op->in_packet2,op->pkt_len,tdflag,count);
							break;
					}
					break;

				case ECB_DES:
					switch (op->auth_algorithm)
					{
						case MD5:
							//control_packet_len = 4 + 4 + 4 + 32;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x10;
							control_packet_len = 44;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x77;  /* 1+2+4+10+20+40 */
#else
							tdflag = 0x17;
#endif
							/* IPSec Control Register */
							ecb_auth_ptr->control.bits.aesnk = 0;
							if (op->auth_check_len)
								ecb_auth_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								ecb_auth_ptr->control.bits.auth_check_len = 4;
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,ecb_auth_ptr->auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(ecb_auth_ptr->auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}
							ipsec_hw_cipher_vpn((unsigned char *)ecb_auth_ptr,control_packet_len,
										op->in_packet2,op->pkt_len,tdflag,count);
							break;

						case SHA1:
							//control_packet_len = 4 + 4 + 4 + 32;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x10;
							control_packet_len = 44;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x77;  /* 1+2+4+10+20+40 */
#else
							tdflag = 0x17;
#endif
							/* IPSec Control Register */
							ecb_auth_ptr->control.bits.aesnk = 0;
							if (op->auth_check_len)
								ecb_auth_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								ecb_auth_ptr->control.bits.auth_check_len = 5;
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,ecb_auth_ptr->auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(ecb_auth_ptr->auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}
							ipsec_hw_cipher_vpn((unsigned char *)ecb_auth_ptr,control_packet_len,
										op->in_packet2,op->pkt_len,tdflag,count);
							break;

						case HMAC_MD5:
							//control_packet_len = 4 + 4 + 4 + 32 + 64;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x10 + 0x20;
							control_packet_len = 108;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x1f7;  /* 1+2+4+10+20+40+80+100 */
#else
							tdflag = 0x37;
#endif
							/* IPSec Control Register */
							ecb_auth_hmac_ptr->control.bits.aesnk = 0;
							if (op->auth_check_len)
								ecb_auth_hmac_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								ecb_auth_hmac_ptr->control.bits.auth_check_len = 4;
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,ecb_auth_hmac_ptr->auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(ecb_auth_hmac_ptr->auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}
							ipsec_hw_cipher_vpn((unsigned char *)ecb_auth_hmac_ptr,control_packet_len,
										op->in_packet2,op->pkt_len,tdflag,count);
							break;

						case HMAC_SHA1:
							//control_packet_len = 4 + 4 + 4 + 32 + 64;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x10 + 0x20;
							control_packet_len = 108;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x1f7;  /* 1+2+4+10+20+40+80+100 */
#else
							tdflag = 0x37;
#endif
							/* IPSec Control Register */
							ecb_auth_hmac_ptr->control.bits.aesnk = 0;
							if (op->auth_check_len)
								ecb_auth_hmac_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								ecb_auth_hmac_ptr->control.bits.auth_check_len = 5;
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,ecb_auth_hmac_ptr->auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(ecb_auth_hmac_ptr->auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}
							ipsec_hw_cipher_vpn((unsigned char *)ecb_auth_hmac_ptr,control_packet_len,
										op->in_packet2,op->pkt_len,tdflag,count);
							break;
					}
					break;
        		
				case CBC_3DES:
					switch (op->auth_algorithm)
					{
						case MD5:
							//control_packet_len = 4 + 4 + 4 + 16 + 32 ;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10;
							control_packet_len = 60 ;
							// debug message
							// printk("Got here into processing CBC 3DES, MD5\n");
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x7f;  /* 1+2+4+8+10+20+40*/
#else
							tdflag = 0x1f;
#endif
							/* IPSec Control Register */
							cbc_auth_ptr->control.bits.aesnk = 0;
							if (op->auth_check_len)
								cbc_auth_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								cbc_auth_ptr->control.bits.auth_check_len = 4;
							/* Cipher IV */
							ipsec_byte_change(op->iv,8,iv,&iv_size);
							memcpy(cbc_auth_ptr->cipher_iv,iv,iv_size);
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,cbc_auth_ptr->auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(cbc_auth_ptr->auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}
							ipsec_hw_cipher_vpn((unsigned char *)cbc_auth_ptr,control_packet_len,
										op->in_packet2,op->pkt_len,tdflag,count);
							break;

						case SHA1:
							//control_packet_len = 4 + 4 + 4 + 16 + 32;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10;
							control_packet_len = 60 ;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x7f;
#else
							tdflag = 0x1f;
#endif
							/* IPSec Control Register */
							cbc_auth_ptr->control.bits.aesnk = 0;
							if (op->auth_check_len)
								cbc_auth_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								cbc_auth_ptr->control.bits.auth_check_len = 5;
							/* Cipher IV */
							ipsec_byte_change(op->iv,8,iv,&iv_size);
							memcpy(cbc_auth_ptr->cipher_iv,iv,iv_size);
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,cbc_auth_ptr->auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(cbc_auth_ptr->auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}
							ipsec_hw_cipher_vpn((unsigned char *)cbc_auth_ptr,control_packet_len,
										op->in_packet2,op->pkt_len,tdflag,count);
							break;

						case HMAC_MD5:
							//control_packet_len = 4 + 4 + 4 + 16 + 32 + 64;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10 + 0x20;
							control_packet_len = 124;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x1ff;  /* 1+2+4+8+10+20+40+80+100 */
#else
							tdflag = 0x3f;
#endif
							/* IPSec Control Register */
							cbc_auth_hmac_ptr->control.bits.aesnk = 0;
							if (op->auth_check_len)
								cbc_auth_hmac_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								cbc_auth_hmac_ptr->control.bits.auth_check_len = 4;
							/* Cipher IV */
							ipsec_byte_change(op->iv,8,iv,&iv_size);
							memcpy(cbc_auth_hmac_ptr->cipher_iv,iv,iv_size);
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,cbc_auth_hmac_ptr->auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(cbc_auth_hmac_ptr->auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}
							ipsec_hw_cipher_vpn((unsigned char *)cbc_auth_hmac_ptr,control_packet_len,
										op->in_packet2,op->pkt_len,tdflag,count);
							break;

						case HMAC_SHA1:
							//control_packet_len = 4 + 4 + 4 + 16 + 32 + 64;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10 + 0x20;
							control_packet_len = 124;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x1ff;
#else
							tdflag = 0x3f;
#endif
							/* IPSec Control Register */
							cbc_auth_hmac_ptr->control.bits.aesnk = 0;
							if (op->auth_check_len)
								cbc_auth_hmac_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								cbc_auth_hmac_ptr->control.bits.auth_check_len = 5;
							/* Cipher IV */
							ipsec_byte_change(op->iv,8,iv,&iv_size);
							memcpy(cbc_auth_hmac_ptr->cipher_iv,iv,iv_size);
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,cbc_auth_hmac_ptr->auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(cbc_auth_hmac_ptr->auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}
							ipsec_hw_cipher_vpn((unsigned char *)cbc_auth_hmac_ptr,control_packet_len,
										op->in_packet2,op->pkt_len,tdflag,count);
							break;
					}
					break;

				case ECB_3DES:
					switch (op->auth_algorithm)
					{
						case MD5:
							//control_packet_len = 4 + 4 + 4 + 32;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x10;
							control_packet_len = 44;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x77;  /* 1+2+4+10+20+40*/
#else
							tdflag = 0x17;
#endif
							/* IPSec Control Register */
							ecb_auth_ptr->control.bits.aesnk = 0;
							if (op->auth_check_len)
								ecb_auth_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								ecb_auth_ptr->control.bits.auth_check_len = 4;
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,ecb_auth_ptr->auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(ecb_auth_ptr->auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}
							ipsec_hw_cipher_vpn((unsigned char *)ecb_auth_ptr,control_packet_len,
										op->in_packet2,op->pkt_len,tdflag,count);
							break;

						case SHA1:
							//control_packet_len = 4 + 4 + 4 + 32 ;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x10;
							control_packet_len = 44;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x77;
#else
							tdflag = 0x17;
#endif
							/* IPSec Control Register */
							ecb_auth_ptr->control.bits.aesnk = 0;
							if (op->auth_check_len)
								ecb_auth_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								ecb_auth_ptr->control.bits.auth_check_len = 5;
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,ecb_auth_ptr->auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(ecb_auth_ptr->auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}
							ipsec_hw_cipher_vpn((unsigned char *)ecb_auth_ptr,control_packet_len,
										op->in_packet2,op->pkt_len,tdflag,count);
							break;

						case HMAC_MD5:
							//control_packet_len = 4 + 4 + 4 + 32 + 64;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x10 + 0x20;
							control_packet_len = 108;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x1f7;  /* 1+2+4+10+20+40+80+100*/
#else
							tdflag = 0x37;
#endif
							/* IPSec Control Register */
							ecb_auth_hmac_ptr->control.bits.aesnk = 0;
							if (op->auth_check_len)
								ecb_auth_hmac_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								ecb_auth_hmac_ptr->control.bits.auth_check_len = 4;
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,ecb_auth_hmac_ptr->auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(ecb_auth_hmac_ptr->auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}
							ipsec_hw_cipher_vpn((unsigned char *)ecb_auth_hmac_ptr,control_packet_len,
										op->in_packet2,op->pkt_len,tdflag,count);
							break;

						case HMAC_SHA1:
							//control_packet_len = 4 + 4 + 4 + 32 + 64;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x10 + 0x20;
							control_packet_len = 108;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x1f7;
#else
							tdflag = 0x37;
#endif
							/* IPSec Control Register */
							ecb_auth_hmac_ptr->control.bits.aesnk = 0;
							if (op->auth_check_len)
								ecb_auth_hmac_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								ecb_auth_hmac_ptr->control.bits.auth_check_len = 5;
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,ecb_auth_hmac_ptr->auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(ecb_auth_hmac_ptr->auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}
							ipsec_hw_cipher_vpn((unsigned char *)ecb_auth_hmac_ptr,control_packet_len,
										op->in_packet2,op->pkt_len,tdflag,count);
							break;
					}
					break;

				case CBC_AES:
					switch (op->auth_algorithm)
					{
						case MD5:
							//control_packet_len = 4 + 4 + 4 + 16 + 32 ;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10;
							control_packet_len = 60 ;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x7f;  /* 1+2+4+8+10+20+40 */
#else
							tdflag = 0x1f;
#endif
							/* IPSec Control Register */
							cbc_auth_ptr->control.bits.aesnk = op->cipher_key_size/4;
							if (op->auth_check_len)
								cbc_auth_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								cbc_auth_ptr->control.bits.auth_check_len = 4;
							/* Cipher IV */
							ipsec_byte_change(op->iv,16,iv,&iv_size);
							memcpy(cbc_auth_ptr->cipher_iv,iv,iv_size);
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,cbc_auth_ptr->auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(cbc_auth_ptr->auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}
							ipsec_hw_cipher_vpn((unsigned char *)cbc_auth_ptr,control_packet_len,
										op->in_packet2,op->pkt_len,tdflag,count);
							break;

						case SHA1:
							//control_packet_len = 4 + 4 + 4 + 16 + 32;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10;
							control_packet_len = 60 ;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x7f;  /* 1+2+4+8+10+20+40 */
#else
							tdflag = 0x1f;
#endif
							/* IPSec Control Register */
							/* Cipher IV */
							ipsec_byte_change(op->iv,16,iv,&iv_size);
							memcpy(cbc_auth_ptr->cipher_iv,iv,iv_size);
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,cbc_auth_ptr->auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(cbc_auth_ptr->auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}
							ipsec_hw_cipher_vpn((unsigned char *)cbc_auth_ptr,control_packet_len,
										op->in_packet2,op->pkt_len,tdflag,count);
							break;

						case HMAC_MD5:
							//control_packet_len = 4 + 4 + 4 + 16 + 32 + 64;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10 + 0x20;
							control_packet_len = 124;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x1ff;  /* 1+2+4+8+10+20+40+80+100 */
#else
							tdflag = 0x3f;
#endif
							/* IPSec Control Register */
							cbc_auth_hmac_ptr->control.bits.aesnk = op->cipher_key_size/4;
							if (op->auth_check_len)
								cbc_auth_hmac_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								cbc_auth_hmac_ptr->control.bits.auth_check_len = 4;
							/* Cipher IV */
							ipsec_byte_change(op->iv,16,iv,&iv_size);
							memcpy(cbc_auth_hmac_ptr->cipher_iv,iv,iv_size);
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,cbc_auth_hmac_ptr->auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(cbc_auth_hmac_ptr->auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}
							ipsec_hw_cipher_vpn((unsigned char *)cbc_auth_hmac_ptr,control_packet_len,
										op->in_packet2,op->pkt_len,tdflag,count);
							break;

						case HMAC_SHA1:
							//control_packet_len = 4 + 4 + 4 + 16 + 32 + 64;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10 + 0x20;
							control_packet_len = 124;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x1ff;  /* 1+2+4+8+10+20+40+80+100 */
#else
							tdflag = 0x3f;
#endif
							/* IPSec Control Register */
							cbc_auth_hmac_ptr->control.bits.aesnk = op->cipher_key_size/4;
							if (op->auth_check_len)
								cbc_auth_hmac_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								cbc_auth_hmac_ptr->control.bits.auth_check_len = 5;
							/* Cipher IV */
							ipsec_byte_change(op->iv,16,iv,&iv_size);
							memcpy(cbc_auth_hmac_ptr->cipher_iv,iv,iv_size);
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,cbc_auth_hmac_ptr->auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(cbc_auth_hmac_ptr->auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}
							ipsec_hw_cipher_vpn((unsigned char *)cbc_auth_hmac_ptr,control_packet_len,
										op->in_packet2,op->pkt_len,tdflag,count);
							break;
					}
					break;

				case ECB_AES:
					switch (op->auth_algorithm)
					{
						case MD5:
							//control_packet_len = 4 + 4 + 4 + 32;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x10;
							control_packet_len = 44;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x77;  /* 1+2+4+10+20+40 */
#else
							tdflag = 0x17;
#endif
							/* IPSec Control Register */
							ecb_auth_ptr->control.bits.aesnk = op->cipher_key_size/4;
							if (op->auth_check_len)
								ecb_auth_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								ecb_auth_ptr->control.bits.auth_check_len = 4;
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,ecb_auth_ptr->auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(ecb_auth_ptr->auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}
							ipsec_hw_cipher_vpn((unsigned char *)ecb_auth_ptr,control_packet_len,
										op->in_packet2,op->pkt_len,tdflag,count);
							break;

						case SHA1:
							//control_packet_len = 4 + 4 + 4 + 32 ;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x10;
							control_packet_len = 44;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x77;  /* 1+2+4+10+20+40 */
#else
							tdflag = 0x17;
#endif
							/* IPSec Control Register */
							ecb_auth_ptr->control.bits.aesnk = op->cipher_key_size/4;
							if (op->auth_check_len)
								ecb_auth_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								ecb_auth_ptr->control.bits.auth_check_len = 5;
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,ecb_auth_ptr->auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(ecb_auth_ptr->auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}
							ipsec_hw_cipher_vpn((unsigned char *)ecb_auth_ptr,control_packet_len,
										op->in_packet2,op->pkt_len,tdflag,count);
							break;

						case HMAC_MD5:
							//control_packet_len = 4 + 4 + 4 + 32 + 64;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x10 + 0x20;
							control_packet_len = 108;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x1f7;  /* 1+2+4+10+20+40+80+100 */
#else
							tdflag = 0x37;
#endif
							/* IPSec Control Register */
							ecb_auth_hmac_ptr->control.bits.aesnk = op->cipher_key_size/4;
							if (op->auth_check_len)
								ecb_auth_hmac_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								ecb_auth_hmac_ptr->control.bits.auth_check_len = 4;
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,ecb_auth_hmac_ptr->auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(ecb_auth_hmac_ptr->auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}
							ipsec_hw_cipher_vpn((unsigned char *)ecb_auth_hmac_ptr,control_packet_len,
										op->in_packet2,op->pkt_len,tdflag,count);
							break;

						case HMAC_SHA1:
							//control_packet_len = 4 + 4 + 4 + 32 + 64;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x10 + 0x20;
							control_packet_len = 108;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x1f7;  /* 1+2+4+10+20+40+80+100 */
#else
							tdflag = 0x37;
#endif
							/* IPSec Control Register */
							ecb_auth_hmac_ptr->control.bits.aesnk = op->cipher_key_size/4;
							if (op->auth_check_len)
								ecb_auth_hmac_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								ecb_auth_hmac_ptr->control.bits.auth_check_len = 5;
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,ecb_auth_hmac_ptr->auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(ecb_auth_hmac_ptr->auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}
							ipsec_hw_cipher_vpn((unsigned char *)ecb_auth_hmac_ptr,control_packet_len,
										op->in_packet2,op->pkt_len,tdflag,count);
							break;
					}
					break;
			}
			break;

		case AUTH_DEC:
			switch (op->auth_algorithm)
			{
				case MD5:
					switch(op->cipher_algorithm)
					{
						case CBC_DES:
							//control_packet_len = 4 + 4 + 4 + 16 + 32 ;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10;
							control_packet_len = 60 ;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x7f;  /* 1+2+4+8+10+20+40 */
#else
							tdflag = 0x1f;
#endif
							/* IPSec Control Register */
							cbc_auth_ptr->control.bits.aesnk = 0;
							if (op->auth_check_len)
								cbc_auth_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								cbc_auth_ptr->control.bits.auth_check_len = 4;
							/* Cipher IV */
							ipsec_byte_change(op->iv,8,iv,&iv_size);
							memcpy(cbc_auth_ptr->cipher_iv,iv,iv_size);
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,cbc_auth_ptr->auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(cbc_auth_ptr->auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}
							ipsec_hw_cipher_vpn((unsigned char *)cbc_auth_ptr,control_packet_len,
										op->in_packet2,op->pkt_len,tdflag,count);
							break;

						case ECB_DES:
                            //control_packet_len = 4 + 4 + 4 + 32;
                            //tdflag = 0x01 + 0x02 + 0x04 + 0x10;
                            control_packet_len = 44 ;
#ifdef CONFIG_IPSEC_GEMINI
                            tdflag = 0x77;  /* 1+2+4+10+20+40 */
#else
                            tdflag = 0x17;
#endif
                            /* IPSec Control Register */
                            ecb_auth_ptr->control.bits.aesnk = 0;
                            if (op->auth_check_len)
								ecb_auth_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								ecb_auth_ptr->control.bits.auth_check_len = 4;
                            if (op->auth_result_mode == CHECK_MODE)
                            {
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,ecb_auth_ptr->auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(ecb_auth_ptr->auth_check_val,auth_result,auth_result_len);
								}
                                control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
                                tdflag = tdflag + 0x200;
#else
                                tdflag = tdflag + 0x40;
#endif
							}
							ipsec_hw_cipher_vpn((unsigned char *)ecb_auth_ptr,control_packet_len,
                                        op->in_packet2,op->pkt_len,tdflag,count);
                            break;
                			
                        case CBC_3DES:
                            //control_packet_len = 4 + 4 + 4 + 16 + 32 ;
                            //tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10;
                            control_packet_len = 60 ;
#ifdef CONFIG_IPSEC_GEMINI
                            tdflag = 0x7f;  /* 1+2+4+8+10+20+40 */
#else
                            tdflag = 0x1f;
#endif
                            /* IPSec Control Register */
                            cbc_auth_ptr->control.bits.aesnk = 0;
                            if (op->auth_check_len)
								cbc_auth_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								cbc_auth_ptr->control.bits.auth_check_len = 4;
                            /* Cipher IV */
                            ipsec_byte_change(op->iv,8,iv,&iv_size);
                            memcpy(cbc_auth_ptr->cipher_iv,iv,iv_size);
                            if (op->auth_result_mode == CHECK_MODE)
                            {
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,cbc_auth_ptr->auth_check_val,&auth_result_len);
								}
								else {
	                                ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
		                            memcpy(cbc_auth_ptr->auth_check_val,auth_result,auth_result_len);
								}
                                control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
                                tdflag = tdflag + 0x200;
#else
                                tdflag = tdflag + 0x40;
#endif
                            }
							ipsec_hw_cipher_vpn((unsigned char *)cbc_auth_ptr,control_packet_len,
                                        op->in_packet2,op->pkt_len,tdflag,count);
                            break;
                			
                        case ECB_3DES:
                            //control_packet_len = 4 + 4 + 4 + 32;
                            //tdflag = 0x01 + 0x02 + 0x04 + 0x10;
                            control_packet_len = 44 ;
#ifdef CONFIG_IPSEC_GEMINI
                            tdflag = 0x77;  /* 1+2+4+10+20+40 */
#else
                            tdflag = 0x17;
#endif
                            /* IPSec Control Register */
                            ecb_auth_ptr->control.bits.aesnk = 0;
                            if (op->auth_check_len)
								ecb_auth_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								ecb_auth_ptr->control.bits.auth_check_len = 4;
                            if (op->auth_result_mode == CHECK_MODE)
                            {
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,ecb_auth_ptr->auth_check_val,&auth_result_len);
								}
								else {
	                                ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
		                            memcpy(ecb_auth_ptr->auth_check_val,auth_result,auth_result_len);
								}
                                control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
                                tdflag = tdflag + 0x200;
#else
                                tdflag = tdflag + 0x40;
#endif
                            }
							ipsec_hw_cipher_vpn((unsigned char *)ecb_auth_ptr,control_packet_len,
                                        op->in_packet2,op->pkt_len,tdflag,count);
                   			break;
                			
                        case CBC_AES:
                            //control_packet_len = 4 + 4 + 4 + 16 + 32 ;
                            //tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10;
                            control_packet_len = 60 ;
#ifdef CONFIG_IPSEC_GEMINI
                            tdflag = 0x7f;  /* 1+2+4+8+10+20+40 */
#else
                            tdflag = 0x1f;
#endif
                            /* IPSec Control Register */
                            cbc_auth_ptr->control.bits.aesnk = op->cipher_key_size/4;
                            if (op->auth_check_len)
								cbc_auth_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								cbc_auth_ptr->control.bits.auth_check_len = 4;
                            /* Cipher IV */
                            ipsec_byte_change(op->iv,16,iv,&iv_size);
                            memcpy(cbc_auth_ptr->cipher_iv,iv,iv_size);
                            if (op->auth_result_mode == CHECK_MODE)
                            {
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,cbc_auth_ptr->auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(cbc_auth_ptr->auth_check_val,auth_result,auth_result_len);
								}
                                control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
                                tdflag = tdflag + 0x200;
#else
                                tdflag = tdflag + 0x40;
#endif
                            }
							ipsec_hw_cipher_vpn((unsigned char *)cbc_auth_ptr,control_packet_len,
                                        op->in_packet2,op->pkt_len,tdflag,count);
               			    break;
                			
                        case ECB_AES:
                            //control_packet_len = 4 + 4 + 4 + 32 ;
                            //tdflag = 0x01 + 0x02 + 0x04 + 0x10;
                            control_packet_len = 44 ;
#ifdef CONFIG_IPSEC_GEMINI
                            tdflag = 0x77;  /* 1+2+4+10+20+40 */
#else
                            tdflag = 0x17;
#endif
                            /* IPSec Control Register */
                            ecb_auth_ptr->control.bits.aesnk = op->cipher_key_size/4;
                            if (op->auth_check_len)
								ecb_auth_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								ecb_auth_ptr->control.bits.auth_check_len = 4;
                             if (op->auth_result_mode == CHECK_MODE)
                            {
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,ecb_auth_ptr->auth_check_val,&auth_result_len);
								}
								else {
	                                ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
		                            memcpy(ecb_auth_ptr->auth_check_val,auth_result,auth_result_len);
								}
                                control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
                                tdflag = tdflag + 0x200;
#else
                                tdflag = tdflag + 0x40;
#endif
                            }
							ipsec_hw_cipher_vpn((unsigned char *)ecb_auth_ptr,control_packet_len,
                                        op->in_packet2,op->pkt_len,tdflag,count);
                			break;
                	}
                    break;
                    
                case SHA1:
                	switch(op->cipher_algorithm)
                	{
                    	case CBC_DES:
                            //control_packet_len = 4 + 4 + 4 + 16 + 32;
                            //tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10;
                            control_packet_len = 60 ;
#ifdef CONFIG_IPSEC_GEMINI
                            tdflag = 0x7f;  /* 1+2+4+8+10+20+40 */
#else
                            tdflag = 0x1f;
#endif
                            /* IPSec Control Register */
                            cbc_auth_ptr->control.bits.aesnk = 0;
                            if (op->auth_check_len)
								cbc_auth_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								cbc_auth_ptr->control.bits.auth_check_len = 5;
                            /* Cipher IV */
                            ipsec_byte_change(op->iv,8,iv,&iv_size);
                            memcpy(cbc_auth_ptr->cipher_iv,iv,iv_size);
                            if (op->auth_result_mode == CHECK_MODE)
                            {
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,cbc_auth_ptr->auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(cbc_auth_ptr->auth_check_val,auth_result,auth_result_len);
								}
                                control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
                                tdflag = tdflag + 0x200;
#else
                                tdflag = tdflag + 0x40;
#endif
                            }
							ipsec_hw_cipher_vpn((unsigned char *)cbc_auth_ptr,control_packet_len,
                                        op->in_packet2,op->pkt_len,tdflag,count);
                			break;
                			
                        case ECB_DES:
                            //control_packet_len = 4 + 4 + 4 + 32;
                            //tdflag = 0x01 + 0x02 + 0x04 + 0x10;
                            control_packet_len = 44 ;
#ifdef CONFIG_IPSEC_GEMINI
                            tdflag = 0x77;  /* 1+2+4+10+20+40 */
#else
                            tdflag = 0x17;
#endif
                            /* IPSec Control Register */
                            ecb_auth_ptr->control.bits.aesnk = 0;
                            if (op->auth_check_len)
								ecb_auth_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								ecb_auth_ptr->control.bits.auth_check_len = 5;
                            if (op->auth_result_mode == CHECK_MODE)
                            {
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,ecb_auth_ptr->auth_check_val,&auth_result_len);
								}
								else {
	                                ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
		                            memcpy(ecb_auth_ptr->auth_check_val,auth_result,auth_result_len);
								}
                                control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
                                tdflag = tdflag + 0x200;
#else
                                tdflag = tdflag + 0x40;
#endif
                            }
							ipsec_hw_cipher_vpn((unsigned char *)ecb_auth_ptr,control_packet_len,
                                        op->in_packet2,op->pkt_len,tdflag,count);
                            break;
                			
                        case CBC_3DES:
                            //control_packet_len = 4 + 4 + 4 + 16 + 32;
                            //tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10;
                            control_packet_len = 60 ;
#ifdef CONFIG_IPSEC_GEMINI
                            tdflag = 0x7f;  /* 1+2+4+8+10+20+40 */
#else
                            tdflag = 0x1f;
#endif
                            /* IPSec Control Register */
                            cbc_auth_ptr->control.bits.aesnk = 0;
                            if (op->auth_check_len)
								cbc_auth_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								cbc_auth_ptr->control.bits.auth_check_len = 5;
                            /* Cipher IV */
                            ipsec_byte_change(op->iv,8,iv,&iv_size);
                            memcpy(cbc_auth_ptr->cipher_iv,iv,iv_size);
                            if (op->auth_result_mode == CHECK_MODE)
                            {
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,cbc_auth_ptr->auth_check_val,&auth_result_len);
								}
								else {
	                                ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
		                            memcpy(cbc_auth_ptr->auth_check_val,auth_result,auth_result_len);
								}
                                control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
                                tdflag = tdflag + 0x200;
#else
                                tdflag = tdflag + 0x40;
#endif
                            }
							ipsec_hw_cipher_vpn((unsigned char *)cbc_auth_ptr,control_packet_len,
                                        op->in_packet2,op->pkt_len,tdflag,count);
                            break;
                			
                        case ECB_3DES:
                            //control_packet_len = 4 + 4 + 4 + 32;
                            //tdflag = 0x01 + 0x02 + 0x04 + 0x10;
                            control_packet_len = 44 ;
#ifdef CONFIG_IPSEC_GEMINI
                            tdflag = 0x77;  /* 1+2+4+10+20+40 */
#else
                            tdflag = 0x17;
#endif
                            /* IPSec Control Register */
                            ecb_auth_ptr->control.bits.aesnk = 0;
                            if (op->auth_check_len)
								ecb_auth_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								ecb_auth_ptr->control.bits.auth_check_len = 5;
                            if (op->auth_result_mode == CHECK_MODE)
                            {
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,ecb_auth_ptr->auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(ecb_auth_ptr->auth_check_val,auth_result,auth_result_len);
								}
                                control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
                                tdflag = tdflag + 0x200;
#else
                                tdflag = tdflag + 0x40;
#endif
                            }
							ipsec_hw_cipher_vpn((unsigned char *)ecb_auth_ptr,control_packet_len,
                                        op->in_packet2,op->pkt_len,tdflag,count);
                   			break;
                			
                        case CBC_AES:
                            //control_packet_len = 4 + 4 + 4 + 16 + 32 ;
                            //tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10;
                            control_packet_len = 60 ;
#ifdef CONFIG_IPSEC_GEMINI
                            tdflag = 0x7f;  /* 1+2+4+8+10+20+40 */
#else
                            tdflag = 0x1f;
#endif
                            /* IPSec Control Register */
                            cbc_auth_ptr->control.bits.aesnk = op->cipher_key_size/4;
                            if (op->auth_check_len)
								cbc_auth_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								cbc_auth_ptr->control.bits.auth_check_len = 5;
                            /* Cipher IV */
                            ipsec_byte_change(op->iv,16,iv,&iv_size);
                            memcpy(cbc_auth_ptr->cipher_iv,iv,iv_size);
                            if (op->auth_result_mode == CHECK_MODE)
                            {
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,cbc_auth_ptr->auth_check_val,&auth_result_len);
								}
								else {
	                                ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
		                            memcpy(cbc_auth_ptr->auth_check_val,auth_result,auth_result_len);
								}
                                control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
                                tdflag = tdflag + 0x200;
#else
                                tdflag = tdflag + 0x40;
#endif
                            }
							ipsec_hw_cipher_vpn((unsigned char *)cbc_auth_ptr,control_packet_len,
                                        op->in_packet2,op->pkt_len,tdflag,count);
               				break;
                			
                        case ECB_AES:
                            //control_packet_len = 4 + 4 + 4 + 32;
                            //tdflag = 0x01 + 0x02 + 0x04 + 0x10;
                            control_packet_len = 44 ;
#ifdef CONFIG_IPSEC_GEMINI
                            tdflag = 0x77;  /* 1+2+4+10+20+40 */
#else
                            tdflag = 0x17;
#endif
                            /* IPSec Control Register */
                            ecb_auth_ptr->control.bits.aesnk = op->cipher_key_size/4;
                            if (op->auth_check_len)
								ecb_auth_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								ecb_auth_ptr->control.bits.auth_check_len = 5;
                            if (op->auth_result_mode == CHECK_MODE)
                            {
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,ecb_auth_ptr->auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(ecb_auth_ptr->auth_check_val,auth_result,auth_result_len);
								}
                                control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
                                tdflag = tdflag + 0x200;
#else
                                tdflag = tdflag + 0x40;
#endif
                            }
							ipsec_hw_cipher_vpn((unsigned char *)ecb_auth_ptr,control_packet_len,
                                        op->in_packet2,op->pkt_len,tdflag,count);
                			break;        			
                	}
                    break;
                    
                case HMAC_MD5:
                	switch(op->cipher_algorithm)
                	{
                    	case CBC_DES:
                            //control_packet_len = 4 + 4 + 4 + 16 + 32 + 64;
                            //tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10 + 0x20;
                            control_packet_len = 124 ;
#ifdef CONFIG_IPSEC_GEMINI
                            tdflag = 0x1ff;  /* 1+2+4+8+10+20+40+80+100 */
#else
                            tdflag = 0x3f;
#endif
                            /* IPSec Control Register */
                            cbc_auth_hmac_ptr->control.bits.aesnk = 0;
                            if (op->auth_check_len)
								cbc_auth_hmac_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								cbc_auth_hmac_ptr->control.bits.auth_check_len = 4;
                            /* Cipher IV */
                            ipsec_byte_change(op->iv,8,iv,&iv_size);
                            memcpy(cbc_auth_hmac_ptr->cipher_iv,iv,iv_size);
                            if (op->auth_result_mode == CHECK_MODE)
                            {
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,cbc_auth_hmac_ptr->auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(cbc_auth_hmac_ptr->auth_check_val,auth_result,auth_result_len);
								}
                                control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
                                tdflag = tdflag + 0x200;
#else
                                tdflag = tdflag + 0x40;
#endif
                            }
							ipsec_hw_cipher_vpn((unsigned char *)cbc_auth_hmac_ptr,control_packet_len,
                                        op->in_packet2,op->pkt_len,tdflag,count);
                			break;
                			
                        case ECB_DES:
                            //control_packet_len = 4 + 4 + 4 + 32 + 64;
                            //tdflag = 0x01 + 0x02 + 0x04 + 0x10 + 0x20;
                            control_packet_len = 108 ;
#ifdef CONFIG_IPSEC_GEMINI
                            tdflag = 0x1f7;  /* 1+2+4+10+20+40+80+100 */
#else
                            tdflag = 0x37;
#endif
                            /* IPSec Control Register */
                            ecb_auth_hmac_ptr->control.bits.aesnk = 0;
                            if (op->auth_check_len)
								ecb_auth_hmac_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								ecb_auth_hmac_ptr->control.bits.auth_check_len = 4;
                            if (op->auth_result_mode == CHECK_MODE)
                            {
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,ecb_auth_hmac_ptr->auth_check_val,&auth_result_len);
								}
								else {
	                                ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
		                            memcpy(ecb_auth_hmac_ptr->auth_check_val,auth_result,auth_result_len);
								}
                                control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
                                tdflag = tdflag + 0x200;
#else
                                tdflag = tdflag + 0x40;
#endif
                            }
							ipsec_hw_cipher_vpn((unsigned char *)ecb_auth_hmac_ptr,control_packet_len,
                                        op->in_packet2,op->pkt_len,tdflag,count);
                            break;
                			
                        case CBC_3DES:
                            //control_packet_len = 4 + 4 + 4 + 16 + 32 + 64;
                            //tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10 + 0x20;
                            control_packet_len = 124 ;
#ifdef CONFIG_IPSEC_GEMINI
                            tdflag = 0x1ff;  /* 1+2+4+8+10+20+40+80+100 */
#else
                            tdflag = 0x3f;
#endif
                            /* IPSec Control Register */
                            cbc_auth_hmac_ptr->control.bits.aesnk = 0;
                            if (op->auth_check_len)
								cbc_auth_hmac_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								cbc_auth_hmac_ptr->control.bits.auth_check_len = 4;
                            /* Cipher IV */
                            ipsec_byte_change(op->iv,8,iv,&iv_size);
                            memcpy(cbc_auth_hmac_ptr->cipher_iv,iv,iv_size);
                            if (op->auth_result_mode == CHECK_MODE)
                            {
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,cbc_auth_hmac_ptr->auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(cbc_auth_hmac_ptr->auth_check_val,auth_result,auth_result_len);
								}
                                control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
                                tdflag = tdflag + 0x200;
#else
                                tdflag = tdflag + 0x40;
#endif
                            }
							ipsec_hw_cipher_vpn((unsigned char *)cbc_auth_hmac_ptr,control_packet_len,
                                        op->in_packet2,op->pkt_len,tdflag,count);
                            break;
                			
                        case ECB_3DES:
                            //control_packet_len = 4 + 4 + 4 + 32 + 64;
                            //tdflag = 0x01 + 0x02 + 0x04 + 0x10 + 0x20;
                            control_packet_len = 108 ;
#ifdef CONFIG_IPSEC_GEMINI
                            tdflag = 0x1f7;  /* 1+2+4+10+20+40+80+100 */
#else
                            tdflag = 0x37;
#endif
                            /* IPSec Control Register */
                            ecb_auth_hmac_ptr->control.bits.aesnk = 0;
                            if (op->auth_check_len)
								ecb_auth_hmac_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								ecb_auth_hmac_ptr->control.bits.auth_check_len = 4;
                            if (op->auth_result_mode == CHECK_MODE)
                            {
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,ecb_auth_hmac_ptr->auth_check_val,&auth_result_len);
								}
								else {
	                                ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
		                            memcpy(ecb_auth_hmac_ptr->auth_check_val,auth_result,auth_result_len);
								}
                                control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
                                tdflag = tdflag + 0x200;
#else
                                tdflag = tdflag + 0x40;
#endif
                            }
							ipsec_hw_cipher_vpn((unsigned char *)ecb_auth_hmac_ptr,control_packet_len,
                                        op->in_packet2,op->pkt_len,tdflag,count);
                   			break;
                			
                        case CBC_AES:
                            //control_packet_len = 4 + 4 + 4 + 16 + 32 + 64;
                            //tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10 + 0x20;
                            control_packet_len = 124 ;
#ifdef CONFIG_IPSEC_GEMINI
                            tdflag = 0x1ff;
#else
                            tdflag = 0x3f;
#endif
                            /* IPSec Control Register */
                            cbc_auth_hmac_ptr->control.bits.aesnk = op->cipher_key_size/4;
                            if (op->auth_check_len)
								cbc_auth_hmac_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								cbc_auth_hmac_ptr->control.bits.auth_check_len = 4;
                            /* Cipher IV */
                            ipsec_byte_change(op->iv,16,iv,&iv_size);
                            memcpy(cbc_auth_hmac_ptr->cipher_iv,iv,iv_size);
                            if (op->auth_result_mode == CHECK_MODE)
                            {
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,cbc_auth_hmac_ptr->auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(cbc_auth_hmac_ptr->auth_check_val,auth_result,auth_result_len);
								}
                                control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
                                tdflag = tdflag + 0x200;
#else
                                tdflag = tdflag + 0x40;
#endif
                            }
							ipsec_hw_cipher_vpn((unsigned char *)cbc_auth_hmac_ptr,control_packet_len,
                                        op->in_packet2,op->pkt_len,tdflag,count);
               			    break;
                			
                        case ECB_AES:
                            //control_packet_len = 4 + 4 + 4 + 32 + 64;
                            //tdflag = 0x01 + 0x02 + 0x04 + 0x10 + 0x20;
                            control_packet_len = 108 ;
#ifdef CONFIG_IPSEC_GEMINI
                            tdflag = 0x1f7;
#else
                            tdflag = 0x37;
#endif
                            /* IPSec Control Register */
                            ecb_auth_hmac_ptr->control.bits.aesnk = op->cipher_key_size/4;
                            if (op->auth_check_len)
								ecb_auth_hmac_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								ecb_auth_hmac_ptr->control.bits.auth_check_len = 4;
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,ecb_auth_hmac_ptr->auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],16,auth_result,&auth_result_len);
									memcpy(ecb_auth_hmac_ptr->auth_check_val,auth_result,auth_result_len);
								}
                                control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
                                tdflag = tdflag + 0x200;
#else
                                tdflag = tdflag + 0x40;
#endif
                            }
							ipsec_hw_cipher_vpn((unsigned char *)ecb_auth_hmac_ptr,control_packet_len,
										op->in_packet2,op->pkt_len,tdflag,count);
							break;
                	}
					break;
                    
				case HMAC_SHA1:
					switch(op->cipher_algorithm)
					{
                    	case CBC_DES:
							//control_packet_len = 4 + 4 + 4 + 16 + 32 + 64;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10 + 0x20;
							control_packet_len = 124 ;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x1ff;
#else
							tdflag = 0x3f;
#endif
							/* IPSec Control Register */
							cbc_auth_hmac_ptr->control.bits.aesnk = 0;
							if (op->auth_check_len)
								cbc_auth_hmac_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								cbc_auth_hmac_ptr->control.bits.auth_check_len = 5;
							/* Cipher IV */
							ipsec_byte_change(op->iv,8,iv,&iv_size);
							memcpy(cbc_auth_hmac_ptr->cipher_iv,iv,iv_size);
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,cbc_auth_hmac_ptr->auth_check_val,&auth_result_len);
								}
								else {
	                                ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
		                            memcpy(cbc_auth_hmac_ptr->auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}
							ipsec_hw_cipher_vpn((unsigned char *)cbc_auth_hmac_ptr,control_packet_len,
										op->in_packet2,op->pkt_len,tdflag,count);
							break;

						case ECB_DES:
							//control_packet_len = 4 + 4 + 4 + 32 + 64;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x10 + 0x20;
							control_packet_len = 108 ;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x1f7;
#else
							tdflag = 0x37;
#endif
							/* IPSec Control Register */
							ecb_auth_hmac_ptr->control.bits.aesnk = 0;
							if (op->auth_check_len)
								ecb_auth_hmac_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								ecb_auth_hmac_ptr->control.bits.auth_check_len = 5;
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,ecb_auth_hmac_ptr->auth_check_val,&auth_result_len);
								}
								else {
	                                ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
		                            memcpy(ecb_auth_hmac_ptr->auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}
							ipsec_hw_cipher_vpn((unsigned char *)ecb_auth_hmac_ptr,control_packet_len,
										op->in_packet2,op->pkt_len,tdflag,count);
							break;

						case CBC_3DES:
							//control_packet_len = 4 + 4 + 4 + 16 + 32 + 64;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10 + 0x20;
							control_packet_len = 124 ;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x1ff;
#else
							tdflag = 0x3f;
#endif
							/* IPSec Control Register */
							cbc_auth_hmac_ptr->control.bits.aesnk = 0;
							if (op->auth_check_len)
								cbc_auth_hmac_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								cbc_auth_hmac_ptr->control.bits.auth_check_len = 5;
							/* Cipher IV */
							ipsec_byte_change(op->iv,8,iv,&iv_size);
							memcpy(cbc_auth_hmac_ptr->cipher_iv,iv,iv_size);
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,cbc_auth_hmac_ptr->auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(cbc_auth_hmac_ptr->auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}
							ipsec_hw_cipher_vpn((unsigned char *)cbc_auth_hmac_ptr,control_packet_len,
										op->in_packet2,op->pkt_len,tdflag,count);
							break;

						case ECB_3DES:
							//control_packet_len = 4 + 4 + 4 + 32 + 64;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x10 + 0x20;
							control_packet_len = 108 ;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x1f7;
#else
							tdflag = 0x37;
#endif
							/* IPSec Control Register */
							ecb_auth_hmac_ptr->control.bits.aesnk = 0;
							if (op->auth_check_len)
								ecb_auth_hmac_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								ecb_auth_hmac_ptr->control.bits.auth_check_len = 5;
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,ecb_auth_hmac_ptr->auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(ecb_auth_hmac_ptr->auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}
							ipsec_hw_cipher_vpn((unsigned char *)ecb_auth_hmac_ptr,control_packet_len,
										op->in_packet2,op->pkt_len,tdflag,count);
							break;

						case CBC_AES:
							//control_packet_len = 4 + 4 + 4 + 16 + 32 + 64;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x08 + 0x10 + 0x20;
							control_packet_len = 124 ;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x1ff;
#else
							tdflag = 0x3f;
#endif
							/* IPSec Control Register */
							cbc_auth_hmac_ptr->control.bits.aesnk = op->cipher_key_size/4;
							if (op->auth_check_len)
								cbc_auth_hmac_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								cbc_auth_hmac_ptr->control.bits.auth_check_len = 5;
							/* Cipher IV */
							ipsec_byte_change(op->iv,16,iv,&iv_size);
							memcpy(cbc_auth_hmac_ptr->cipher_iv,iv,iv_size);
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,cbc_auth_hmac_ptr->auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(cbc_auth_hmac_ptr->auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}
							ipsec_hw_cipher_vpn((unsigned char *)cbc_auth_hmac_ptr,control_packet_len,
										op->in_packet2,op->pkt_len,tdflag,count);
							break;

						case ECB_AES:
							//control_packet_len = 4 + 4 + 4 + 32 + 64;
							//tdflag = 0x01 + 0x02 + 0x04 + 0x10 + 0x20;
							control_packet_len = 108 ;
#ifdef CONFIG_IPSEC_GEMINI
							tdflag = 0x1f7;
#else
							tdflag = 0x37;
#endif
							/* IPSec Control Register */
							ecb_auth_hmac_ptr->control.bits.aesnk = op->cipher_key_size/4;
							if (op->auth_check_len)
								ecb_auth_hmac_ptr->control.bits.auth_check_len = op->auth_check_len;
							else
								ecb_auth_hmac_ptr->control.bits.auth_check_len = 5;
							if (op->auth_result_mode == CHECK_MODE)
							{
								if (op->auth_check_len) {
									ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,ecb_auth_hmac_ptr->auth_check_val,&auth_result_len);
								}
								else {
									ipsec_byte_change(&ipsec_result.sw_cipher[op->pkt_len],20,auth_result,&auth_result_len);
									memcpy(ecb_auth_hmac_ptr->auth_check_val,auth_result,auth_result_len);
								}
								control_packet_len = control_packet_len + 20;
#ifdef CONFIG_IPSEC_GEMINI
								tdflag = tdflag + 0x200;
#else
								tdflag = tdflag + 0x40;
#endif
							}
							ipsec_hw_cipher_vpn((unsigned char *)ecb_auth_hmac_ptr,control_packet_len,
										op->in_packet2,op->pkt_len,tdflag,count);
							break;
					}
					break;
			}
			break;
    }
    return (0);
}

/***
 * Name: ipsec_auth_or_cipher_vpn
 * Description: for each given IPSEC_PACKET_S, it completes the control packet,
 *				and fill control + data packet backwards from (count * 2) + current
 *				tx_desc_location
 **/
static int ipsec_auth_vpn(struct IPSEC_PACKET_S *op, int count, int cur_loc)
{
	unsigned int		tdflag=0;
	unsigned int		ctrl_pkt_len;
	unsigned int		auth_key_size;
	unsigned int		auth_result_len;
	IPSEC_AUTH_T		*auth;
	IPSEC_HMAC_AUTH_T	*auth_hmac;

	if (op->op_mode == AUTH)    /* Authentication */
	{
		if ((op->auth_algorithm == MD5) || (op->auth_algorithm == SHA1) )
		{
			auth = &(AUTH_T_list[cur_loc]);
			memset(auth,0,sizeof(IPSEC_AUTH_T));
			auth->var.control.bits.op_mode = op->op_mode;    /* authentication */
			auth->var.control.bits.auth_mode = op->auth_result_mode;  /* append/check authentication result  */
			auth->var.control.bits.auth_algorithm = op->auth_algorithm;
			auth->var.control.bits.process_id = op->process_id;   /* set frame process id */
			auth->var.auth.bits.auth_header_len = op->auth_header_len;
			auth->var.auth.bits.auth_algorithm_len = op->auth_algorithm_len;
		}
		else if ((op->auth_algorithm == HMAC_SHA1) || (op->auth_algorithm == HMAC_MD5))
		{
			auth_hmac = &(HMAC_AUTH_T_list[cur_loc]);
			memset(auth_hmac,0,sizeof(IPSEC_HMAC_AUTH_T));
			auth_hmac->control.bits.op_mode = op->op_mode;    /* authentication */
			auth_hmac->control.bits.auth_mode = op->auth_result_mode;  /* append/check authentication result  */
			auth_hmac->control.bits.auth_algorithm = op->auth_algorithm;
			auth_hmac->control.bits.process_id = op->process_id;   /* set frame process id */
			auth_hmac->auth.bits.auth_header_len = op->auth_header_len;
			auth_hmac->auth.bits.auth_algorithm_len = op->auth_algorithm_len;
			ipsec_byte_change(op->auth_key,op->auth_key_size,auth_key,&auth_key_size);
			memcpy(auth_hmac->auth_key,auth_key,auth_key_size);
		}
		else
			printk("%s::This function does not take care of FCS Auth\n",__func__);
	}

	switch (op->op_mode)
	{
		case AUTH:
			switch (op->auth_algorithm)
			{
				case MD5:
					if (op->auth_result_mode == APPEND_MODE)
					{
						ctrl_pkt_len = 8;
#ifdef CONFIG_IPSEC_GEMINI
						tdflag = 0x05; 
#else
						tdflag = 0x05;
#endif
					}
					else
					{
						if ((op->auth_check_len) && (op->auth_checkval))
						{
							ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,auth->var.auth_check_val,&auth_result_len);
						}
						else
						{
							ipsec_result.sw_pkt_len = 16;
							ipsec_byte_change(ipsec_result.sw_cipher,ipsec_result.sw_pkt_len,auth_result,&auth_result_len);
							memcpy(auth->var.auth_check_val,auth_result,auth_result_len);
						}
						ctrl_pkt_len = 28;
#ifdef CONFIG_IPSEC_GEMINI
						tdflag = 0x205;
#else
						tdflag = 0x45;
#endif
					}    

					if (op->auth_check_len)
						auth->var.control.bits.auth_check_len = op->auth_check_len;
					else
						auth->var.control.bits.auth_check_len = 4;

					ipsec_hw_cipher_vpn((unsigned char *)auth,ctrl_pkt_len,
								op->in_packet2,op->pkt_len,tdflag,count);
					break;

				case SHA1:
					if (op->auth_result_mode == APPEND_MODE)
					{
						ctrl_pkt_len = sizeof(IPSEC_AUTH_T) - 20;
#ifdef CONFIG_IPSEC_GEMINI
						tdflag = 0x05;
#else
						tdflag = 0x05;
#endif
					}
					else
					{
						if ((op->auth_check_len) && (op->auth_checkval))
							ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,auth->var.auth_check_val,&auth_result_len);
						else
						{
							ipsec_result.sw_pkt_len = 20;
							ipsec_byte_change(ipsec_result.sw_cipher,ipsec_result.sw_pkt_len,auth_result,&auth_result_len);
							memcpy(auth->var.auth_check_val,auth_result,auth_result_len);
						}
						ctrl_pkt_len = sizeof(IPSEC_AUTH_T);
#ifdef CONFIG_IPSEC_GEMINI
						tdflag = 0x205;
#else
						tdflag = 0x45;
#endif
					}
					if (op->auth_check_len)
						auth->var.control.bits.auth_check_len = op->auth_check_len;
					else
						auth->var.control.bits.auth_check_len = 5;

					ipsec_hw_cipher_vpn((unsigned char *)auth,ctrl_pkt_len,
								op->in_packet2,op->pkt_len,tdflag,count);
					break;

				case HMAC_MD5:
					if (op->auth_result_mode == APPEND_MODE)
					{
						ctrl_pkt_len = sizeof(IPSEC_HMAC_AUTH_T) - 20;
#ifdef CONFIG_IPSEC_GEMINI
						tdflag = 0x185;  /* 1+4+80+100 */
#else
						tdflag = 0x25;
#endif
					}
					else
					{
						if ((op->auth_check_len) && (op->auth_checkval))
							ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,auth_hmac->auth_check_val,&auth_result_len);
						else
						{
							ipsec_result.sw_pkt_len = 16;
							ipsec_byte_change(ipsec_result.sw_cipher,ipsec_result.sw_pkt_len,auth_result,&auth_result_len);
							memcpy(auth_hmac->auth_check_val,auth_result,auth_result_len);
						}
						ctrl_pkt_len = sizeof(IPSEC_HMAC_AUTH_T);
#ifdef CONFIG_IPSEC_GEMINI
						tdflag = 0x385; /* 1+4+80+100+200 */
#else
						tdflag = 0x65;
#endif
					}
					if (op->auth_check_len)
						auth_hmac->control.bits.auth_check_len = op->auth_check_len;
					else
						auth_hmac->control.bits.auth_check_len = 4;

					ipsec_hw_cipher_vpn((unsigned char *)auth_hmac,ctrl_pkt_len,
								op->in_packet2,op->pkt_len,tdflag,count);
					break;

				case HMAC_SHA1:
					if (op->auth_result_mode == APPEND_MODE)
					{
						ctrl_pkt_len = sizeof(IPSEC_HMAC_AUTH_T) - 20;
#ifdef CONFIG_IPSEC_GEMINI
						tdflag = 0x185;  /* 1+4+80+100 */
#else
						tdflag = 0x25;
#endif
					}
					else
					{
						if ((op->auth_check_len) && (op->auth_checkval))
							ipsec_byte_change(op->auth_checkval,op->auth_check_len*4,auth_hmac->auth_check_val,&auth_result_len);
						else
						{
							ipsec_result.sw_pkt_len = 20;
							ipsec_byte_change(ipsec_result.sw_cipher,ipsec_result.sw_pkt_len,auth_result,&auth_result_len);
							memcpy(auth_hmac->auth_check_val,auth_result,auth_result_len);
						}
						ctrl_pkt_len = sizeof(IPSEC_HMAC_AUTH_T);
#ifdef CONFIG_IPSEC_GEMINI
						tdflag = 0x385; /* 1+4+80+100+200 */
#else
						tdflag = 0x65;
#endif
					}
					if (op->auth_check_len)
						auth_hmac->control.bits.auth_check_len = op->auth_check_len;
					else
						auth_hmac->control.bits.auth_check_len = 5; /* 6-word to be checked or appended */
					
					ipsec_hw_cipher_vpn((unsigned char *)auth_hmac,ctrl_pkt_len,
								op->in_packet2,op->pkt_len,tdflag,count);
					break;
			}
			break;
		default:
			break;
	}
	return (0);
}

static void ipsec_hw_cipher_vpn(volatile unsigned char *ctrl_pkt,int ctrl_len, volatile unsigned char *data_pkt, 
					 int data_len, unsigned int tqflag, int count)

{
//    unsigned int        ipsec_status; 
	IPSEC_STATUS_T		ipsec_status;
//	IPSEC_DMA_STATUS_T	ipsec_dma_status;
	int					i;  
	IPSEC_DESCRIPTOR_T	*tx_desc;
	int					first_flag = 0;

	if (tx_desc_count == 0) {
		first_flag = 1;
		first_batch_tx_desc = tp->tx_cur_desc;
	}
	tx_desc = first_batch_tx_desc;

	// move tx_desc to the tx_desc that's going to be filled with the information
	for (i=0; i<(count+count); i++) {
		tx_desc = (IPSEC_DESCRIPTOR_T *)((tx_desc->next_desc.next_descriptor & 0xfffffff0)+tx_desc_virtual_base);
		if (tx_desc->frame_ctrl.bits.own != CPU) {
			printk("%s::Not enough TX Descriptors@%x a\n",__func__,tx_desc);
			ipsec_read_reg(0x0000);
		}
	}

	// fill desc for control packet
	ipsec_fill_desc(tx_desc,ctrl_pkt,ctrl_len,tqflag,DMA);
	tx_desc_count++;

	// fill desc for data packet
	tx_desc = (IPSEC_DESCRIPTOR_T *)((tx_desc->next_desc.next_descriptor & 0xfffffff0)+tx_desc_virtual_base);
	if (tx_desc->frame_ctrl.bits.own != CPU) {
		printk("%s::Not enough TX Descriptors@%x b\n",__func__,tx_desc);
		ipsec_read_reg(0x0000);
	}

	ipsec_fill_desc(tx_desc,data_pkt,data_len,0,DMA);
	tx_desc_count++;

	if (first_flag == 1)
		tp->tx_cur_desc = (IPSEC_DESCRIPTOR_T *)((tx_desc->next_desc.next_descriptor & 0xfffffff0)+tx_desc_virtual_base);

//	for (i=0;i<60000;i++)
	for (i=0;i<5000;i++)	// original
	{
		ipsec_status.status = ipsec_read_reg(IPSEC_STATUS_REG);
		if ((ipsec_status.status & 0x00000fff)==0) /* check IPSec status register */
		{
//			ipsec_dma_status.bits32 = ipsec_read_reg(IPSEC_DMA_STATUS);
//			ipsec_write_reg(IPSEC_DMA_STATUS,ipsec_dma_status.bits32,ipsec_dma_status.bits32);
				break;
		}
	}
	if ((ipsec_status.status & 0x00000fff) != 0)
	{
		printk("\nipsec_hw_cipher : IPSEC Control Packet Error !!!(%08x)\n",ipsec_status);
		printk("data_len=%d vs ah_len(%d)+auth_len(%d) vs ch_len(%d)+ciph_len(%d)\n",
				data_len, 
				((IPSEC_CBC_AUTH_HMAC_T*)ctrl_pkt)->auth.bits.auth_header_len,
				((IPSEC_CBC_AUTH_HMAC_T*)ctrl_pkt)->auth.bits.auth_algorithm_len,
				((IPSEC_CBC_AUTH_HMAC_T*)ctrl_pkt)->cipher.bits.cipher_header_len,
				((IPSEC_CBC_AUTH_HMAC_T*)ctrl_pkt)->cipher.bits.cipher_algorithm_len);
		ipsec_write_reg2(IPSEC_STATUS_REG,ipsec_status.status);
		// anyway to reset the crypto engine?
		// write 1 to IPSEC_DMA_STATUS_T->dma_reset and peri_reset ?

//		temp_desc = (IPSEC_DESCRIPTOR_T *)((first_desc->next_desc.next_descriptor & 0xfffffff0)+tx_desc_virtual_base);
//		while (temp_desc != tp->tx_cur_desc)
//		{
//			temp_desc->frame_ctrl.bits.own = CPU;
//			temp_desc = (IPSEC_DESCRIPTOR_T *)((temp_desc->next_desc.next_descriptor & 0xfffffff0)+tx_desc_virtual_base);
//		}
//		tp->tx_cur_desc = prev_tx_desc;
//		if (prev_tx_desc->frame_ctrl.bits.own == CPU)
//		prev_tx_desc->frame_ctrl.bits.own = CPU;
	}
	// restart dma to process ready descriptors
}

static void start_dma(void)
{
	IPSEC_TXDMA_FIRST_DESC_T	txdma_busy;
	unsigned int				reg_val;

	/* if TX DMA process is stop->ed , restart it */
	txdma_busy.bits32 = ipsec_read_reg(IPSEC_TXDMA_FIRST_DESC);
	if (txdma_busy.bits.td_busy == 0)
	{
		/* restart Rx DMA process */
		reg_val = ipsec_read_reg(IPSEC_RXDMA_CTRL);
		reg_val |= (0x03<<30);
		ipsec_write_reg2(IPSEC_RXDMA_CTRL, reg_val);

		/* restart Tx DMA process */
		reg_val = ipsec_read_reg(IPSEC_TXDMA_CTRL);
		reg_val |= (0x03<<30);
		ipsec_write_reg2(IPSEC_TXDMA_CTRL, reg_val);
	}
}

static int ipsec_fill_desc(IPSEC_DESCRIPTOR_T *desc, unsigned char * data, int len, unsigned int flag, int ownership)
{
	if (desc->frame_ctrl.bits.own == CPU)
	{
		int desc_cnt = (len/TX_BUF_SIZE);
		if (desc_cnt > 1)
			printk("%s::don't allow more than 1 descriptor for 1 packet\n",__func__);
		desc->frame_ctrl.bits32 = 0;
		desc->frame_ctrl.bits.buffer_size = len;
		desc->flag_status.bits32 = 0;
		desc->flag_status.bits_tx_flag.tqflag = flag;
		desc->next_desc.bits.eofie = 1;
		desc->next_desc.bits.dec = 0;
		desc->next_desc.bits.sof_eof = 0x03;
//		wmb();
		consistent_sync(data,len,PCI_DMA_TODEVICE);
		desc->buf_adr = (unsigned int)__pa(data);
		//desc->buf_adr = (unsigned int)virt_to_phys(data);
		wmb();
		desc->frame_ctrl.bits.own = ownership;
		consistent_sync(desc, sizeof(IPSEC_DESCRIPTOR_T), PCI_DMA_TODEVICE);
	}
	return 0;
}

/*************************************************************************************
 * Name: rx_desc_free_space
 * Description: An API for crypto batch implementation
 *				It will return the number of free desc space, so caller function
 *				can control the number of crypto packet sending to the crypto engine w/o
 *				overflooding the crypto engine's descriptor.
 * Return: rxq_available_space > txq_available_space ? txq_available_space : rxq_available_space
 * Note: to avoid some weird RX bugs, it's better that #_TX_desc >= 2 (#_RX_desc + 2)
 ************************************************************************************/
static int desc_free_space(void)
{
	IPSEC_DESCRIPTOR_T	*tx_desc_wptr = tp->tx_cur_desc;
	IPSEC_DESCRIPTOR_T	*tx_desc_rptr = (IPSEC_DESCRIPTOR_T *)((ipsec_read_reg(IPSEC_TXDMA_CURR_DESC) & 0xfffffff0)+tx_desc_virtual_base);
	IPSEC_DESCRIPTOR_T	*rx_desc_rptr = tp->rx_cur_desc;
	IPSEC_DESCRIPTOR_T	*rx_desc_wptr = (IPSEC_DESCRIPTOR_T *)((ipsec_read_reg(IPSEC_RXDMA_CURR_DESC) & 0xfffffff0)+rx_desc_virtual_base);
	unsigned int rx_space, tx_space;
	int result;

	// calculate available space in rxq
//	if ((rx_desc_wptr->frame_ctrl.bits.own == CPU) && ((unsigned int)rx_desc_wptr == (unsigned int)rx_desc_rptr))
//	{
//		rx_space = 0;
//		if (flag_tasklet_scheduled == 0)
//			printk("%s::all the rx desc are in used, and tasklet is not scheduled?\n",__func__);
//	}
//	else {
		if ((unsigned int)rx_desc_wptr >= (unsigned int)rx_desc_rptr)
			rx_space = IPSEC_RX_DESC_NUM - (((unsigned int)rx_desc_wptr - (unsigned int)rx_desc_rptr) / sizeof(IPSEC_DESCRIPTOR_T));
		else
			rx_space = ((unsigned int)rx_desc_rptr - (unsigned int)rx_desc_wptr) / sizeof(IPSEC_DESCRIPTOR_T);
//	}

	// calculate current used space in txq
	if (tx_desc_wptr->frame_ctrl.bits.own != CPU)
		tx_space = 0;
	else {
		if ((unsigned int)tx_desc_wptr >= (unsigned int)tx_desc_rptr)
			tx_space = IPSEC_TX_DESC_NUM - (((unsigned int)tx_desc_wptr - (unsigned int)tx_desc_rptr) / sizeof(IPSEC_DESCRIPTOR_T));
		else
			tx_space = ((unsigned int)tx_desc_rptr - (unsigned int)tx_desc_wptr) / sizeof(IPSEC_DESCRIPTOR_T);
	}
	
	tx_space = tx_space >> 1;

	result = (int)((rx_space < tx_space) ? rx_space : tx_space);

	if (result == 0)
	{
		printk("%s::rx_space = %d, tx_space = %d\n",__func__,rx_space,tx_space);
		if (rx_desc_wptr->frame_ctrl.bits.own == CPU)
			printk("%s::rx_desc_wptr is owned by CPU\n",__func__);
		if (tx_desc_wptr->frame_ctrl.bits.own != CPU)
			printk("%s::tx_desc_wptr is owned by DMA\n",__func__);
	}

	return result;
}
#endif

static int __init ipsec_initial(void)
{

	printk ("ipsec_init : cryptographic accelerator \n");
        
    ipsec_queue = &dummy[2];
	ipsec_queue->next = ipsec_queue->prev = ipsec_queue;

    ipsec_fcs_init();    
    ipsec_buf_init();
    ipsec_hw_start();
    
#ifdef CONFIG_SL2312_IPSEC_INTERRUPT
	/* Install interrupt request */
	request_irq(IRQ_IPSEC,ipsec_interrupt,SA_INTERRUPT,"SL2312-IPSEC",NULL);
#endif
#ifdef CONFIG_SL2312_IPSEC_TASKLET
	request_irq(IRQ_IPSEC,ipsec_interrupt,SA_INTERRUPT,"SL2312-IPSEC",NULL);
	IPSEC_TASKLET_INFO_T *ipsec_tasklet_info = (IPSEC_TASKLET_INFO_T*)&ipsec_tasklet_data;
//	sema_init(&ipsec_tasklet_info->sem, 1);
	tasklet_init(&ipsec_tasklet_info->tasklet, ipsec_napi_func, (unsigned long)ipsec_tasklet_info);
	clear_bit(0, &ipsec_tasklet_info->sched);
#endif
#ifdef CONFIG_SL2312_IPSEC_NAPI
	crypto_rx_dev = alloc_etherdev(0);
	SET_MODULE_OWNER(crypto_rx_dev);
	if (crypto_rx_dev == NULL)
	{
		printk("%s::cannot allocate etherdev for crypto engine\n",__func__);
	}
	request_irq(IRQ_IPSEC,ipsec_interrupt,SA_INTERRUPT,"SL2312-IPSEC",NULL);
	netif_start_queue(crypto_rx_dev);
	crypto_rx_dev->open = NULL;
	crypto_rx_dev->stop = NULL;
	crypto_rx_dev->irq = IRQ_IPSEC;
	crypto_rx_dev->hard_start_xmit = NULL;
	crypto_rx_dev->poll = ipsec_rx_poll;
	crypto_rx_dev->weight = 16;
	if (register_netdev(crypto_rx_dev))
	{
		printk("%s::fail to register a dummy crypto rx device\n",__func__);
	}
#endif
	// on default, make sure hw crypto support for kernel is on.
	storlink_ctl.hw_crypto = 1;
#if 0
for (;;)
{
    unsigned int t1,t2;
    
    t1 = ipsec_get_time();
//    ipsec_checksum_test();
/*    ipsec_adv_auth_fix_algorithm_test();
    ipsec_adv_auth_vary_algorithm_test();
    ipsec_adv_cipher_fix_algorithm_test();
    ipsec_adv_cipher_vary_algorithm_test();
    ipsec_adv_auth_then_decrypt_test();
*/    ipsec_adv_encrypt_then_auth_test();
    
    t2 = ipsec_get_time();
    printk("Time = %d \n",t1-t2);
}
#endif
	
	return 0;
}

static void __exit ipsec_cleanup (void)
{
	free_irq(IRQ_IPSEC,NULL);
	if (tp->tx_desc)
	{
		DMA_MFREE(tp->tx_desc, IPSEC_TX_DESC_NUM*sizeof(IPSEC_DESCRIPTOR_T),(unsigned int)tp->tx_desc_dma);
	}
	if (tp->rx_desc)
	{
		DMA_MFREE(tp->rx_desc, IPSEC_RX_DESC_NUM*sizeof(IPSEC_DESCRIPTOR_T),(unsigned int)tp->rx_desc_dma);
    }
#ifdef CONFIG_SL2312_IPSEC_TASKLET
	IPSEC_TASKLET_INFO_T *ipsec_info = &ipsec_tasklet_data;
	tasklet_kill(&ipsec_info->tasklet);
#endif
}

EXPORT_SYMBOL(ipsec_crypto_hw_process);
module_init(ipsec_initial);
module_exit(ipsec_cleanup); 

