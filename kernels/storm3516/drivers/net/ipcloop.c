
#include <linux/kernel.h>
#include <linux/jiffies.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/string.h>
#include <linux/socket.h>
#include <linux/errno.h>
#include <linux/fcntl.h>
#include <linux/in.h>
#include <linux/init.h>

#include <asm/system.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <asm/hardware.h>
#include <linux/delay.h>

#include <linux/inet.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/skbuff.h>
#include <linux/ethtool.h>
#include <net/sock.h>
#include <net/checksum.h>
#include <linux/if_ether.h>	/* For the statistics structure. */
#include <linux/if_arp.h>	/* For ARPHRD_ETHER */
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/percpu.h>
#include <asm/arch/ipi.h>
#include <linux/dma-mapping.h>
#include <linux/pci.h>

#define DESC_IN_DRAM

#define MEMORY_POOL		(128*0x100000)	// 128MB
#define CPU0_MEM_SIZE		(64*0x100000)	// 64MB
#define CPU1_MEM_SIZE		(MEMORY_POOL-CPU0_MEM_SIZE)
#define CPU0_MEM_OFFSET		0
#define CPU1_MEM_OFFSET		(CPU0_MEM_SIZE)	// cpu0 don't use this space
#define CONFIG_IPC_NAPI

#ifdef CONFIG_IPC_NAPI
#define IPC_NAPI_WEIGHT	64
#endif


#define REG32(addr)     			(*(volatile unsigned long  * const)(addr))
#define SKB_RESERVE_BYTES	4
#define IPC_DESC_NO	192
//#define IPC_MTU		(4*1024)
#define IPC_MTU		2000
#define DMA	1
#define CPU	0
#define IPC_UP	1
#define IPC_DOWN 0
#define BUDGET		4
#define FLAG_IPC_INTERRUPT	0x00001
#define FLAG_IPC_PROCESSING	0x10000

typedef struct ipc_rx_desc_t
{
	union func_ctrl_t
	{
		unsigned int bit32;
		struct bits_0000
		{
			#ifdef BIG_ENDIAN
			unsigned int own		: 1; /* owner bit */
			unsigned int reserve		: 15; /* reserve */
			unsigned int buffer_size	: 16;	/* transfer buffer size associated with current description*/
			#else
			unsigned int buffer_size	: 16;	/* transfer buffer size associated with current description*/
			unsigned int reserve		: 15; /* reserve */
			unsigned int own		: 1; /* owner bit */
			#endif
		} bits;
	} func_ctrl;
	unsigned int skb_ptr;
	unsigned int buf_addr;
	unsigned int next_desc_addr;
	
} IPC_RX_DESC_T;

typedef struct ipc_priv_data_t
{
	unsigned int status;
	unsigned int int_stat;		// bit0 : penging interrupt is for me
					// bit16: processing flag
	unsigned int desc_no;
	IPC_RX_DESC_T *write_point;
	IPC_RX_DESC_T *read_point;
} IPC_PRIV_DATA_T;

typedef struct ipc_head_desc_s
{
	spinlock_dt sp_lock0;
	spinlock_dt sp_lock1;
	IPC_PRIV_DATA_T cpu0_priv;
	IPC_PRIV_DATA_T cpu1_priv;
	IPC_RX_DESC_T	cpu0_rx_desc[IPC_DESC_NO];
	IPC_RX_DESC_T	cpu1_rx_desc[IPC_DESC_NO];
	
} IPC_HEAD_DESC_S;

volatile IPC_HEAD_DESC_S	*ipc_head_data;

volatile IPC_PRIV_DATA_T	*local_priv_data;
volatile IPC_PRIV_DATA_T	*peer_priv_data;
volatile IPC_RX_DESC_T 	*local_rx_desc;
volatile IPC_RX_DESC_T 	*peer_rx_desc;
unsigned int cpu_id;
unsigned int peer_vm;

unsigned char mac_addr[6]={0x00,0x50,0xC2,0x2B,0x0DF,0xFD};

#define DRAMCTL_DMA_CTL		0X20
#define DRAMCTL_DMA_SA		0X24
#define DRAMCTL_DMA_DA		0X28
#define DRAMCTL_DMA_CNT		0X2C
#define MEMCPY_UNIT		0x1000
inline hw_memcpy(unsigned int to, unsigned int from, unsigned int bytes)
{
	unsigned int reg_a,reg_d;
	int count = bytes;

	// wait if dma not complete
	//do{
	//	reg_d = readl(IO_ADDRESS(SL2312_DRAM_CTRL_BASE)+DRAMCTL_DMA_CTL+(cpu_id?0x10:0));
	//}while(reg_d&0x1);
		
	//printk("copy 0x%x to 0x%x (%d bytes)\n",from,to,bytes);
	// SA
	reg_a = IO_ADDRESS(SL2312_DRAM_CTRL_BASE)+DRAMCTL_DMA_SA+(cpu_id?0x10:0);
	reg_d = (unsigned int )(from);
	//DEB(printk("hwmemcpy:from 0x%08x\n",reg_d));
	writel(reg_d,reg_a);
	// DA
	reg_a = IO_ADDRESS(SL2312_DRAM_CTRL_BASE)+DRAMCTL_DMA_DA+(cpu_id?0x10:0);
	reg_d = (unsigned int )(to);
	writel(reg_d,reg_a);
	//DEB(printk("hwmemcpy:to 0x%08x\n",reg_d));
	// byte count
	reg_a = IO_ADDRESS(SL2312_DRAM_CTRL_BASE)+DRAMCTL_DMA_CNT+(cpu_id?0x10:0);
	reg_d = count;
	writel(reg_d,reg_a);
	// start DMA
	reg_a = IO_ADDRESS(SL2312_DRAM_CTRL_BASE)+DRAMCTL_DMA_CTL+(cpu_id?0x10:0);
	writel(0x80000001,reg_a);	
	
	if((peer_priv_data->int_stat&FLAG_IPC_PROCESSING)==0){	// first packet, wait complete
	
		do{
			reg_d = readl(IO_ADDRESS(SL2312_DRAM_CTRL_BASE)+DRAMCTL_DMA_CTL+(cpu_id?0x10:0));
		}while(reg_d&0x1);
	}
	
	return bytes;
}

int sw_memcpy(unsigned int to, unsigned int *from, unsigned int bytes)
{
	if(to<0x4000000)
		to += 0x4000000;
		
	const char *ptr=(unsigned int)__phys_to_virt(to);
	memcpy(ptr,from,bytes);
	consistent_sync(ptr,bytes, DMA_TO_DEVICE);
	wmb();
	return bytes;
}

/*
 * The higher levels take care of making this non-reentrant (it's
 * called with bh's disabled).
 */
static int ipc_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct net_device_stats *lb_stats;
	volatile IPC_RX_DESC_T *desc,*rdesc;
	unsigned char *ptr,*ptr2,pattern;
	int i;
	unsigned int reg_d;
	
	skb_orphan(skb);


	if(peer_priv_data->status==IPC_DOWN){
		printk("please Up CPU%d's interface\n",cpu_id?0:1);
		//clear_bit(__LINK_STATE_START, &dev->state);
		dev_kfree_skb(skb);	// free skb
		return 0;
	}
	
	// parse peer rx descript and copy to
#ifndef DESC_IN_DRAM
	desc = peer_priv_data->write_point;
#else
	desc = (IPC_RX_DESC_T *)((unsigned char *)peer_priv_data->write_point + 0x400000);
#endif

	rmb();
	if((desc->func_ctrl.bit32 & 0x80000000)==0){
		//printk("CPU%d RX Descripts full\n",cpu_id?0:1);
		dev_kfree_skb(skb);	// free skb
		return 0;
/*		
		i=0
		do{
			mdelay(1);
			if(i++ > 20){
				dev_kfree_skb(skb);	// free skb
				return 0;			// drop
			}
		}while((desc->func_ctrl.bit32 & 0x80000000)==0);
*/			
	}
	else{
		
		consistent_sync(skb->data,skb->len,PCI_DMA_TODEVICE);
		wmb();
		reg_d = readl(IO_ADDRESS(SL2312_DRAM_CTRL_BASE)+DRAMCTL_DMA_CTL+(cpu_id?0x10:0));
		if((reg_d&0x01)||(skb->len < 256)){
			sw_memcpy(desc->buf_addr,skb->data,skb->len);
			//lb_stats->collisions++;
		}
		else{
			hw_memcpy(desc->buf_addr,__pa(skb->data)+(cpu_id?0x4000000:0),skb->len);
			//lb_stats->collisions--;
		}
		//sw_memcpy(desc->buf_addr,skb->data,skb->len);
		
/*		ptr = (unsigned int)__phys_to_virt((desc->buf_addr>0x4000000) ? desc->buf_addr:desc->buf_addr+0x4000000);
		consistent_sync(ptr,IPC_MTU, PCI_DMA_FROMDEVICE);
		if(skb->len>70){
			pattern = 0x06;
			ptr2 = skb->data;
			for(i=0;i<skb->len;i++){
				if(*ptr ^ *ptr2){
				//if(skb->data[i]^ptr[i]){	// God .. mismatch
					// Trig hw here ...
					readl(0xF6600000);
					printk("IPC:TX error!!\n");
					printk("Address 0x%x should 0x%x but 0x%x\n",ptr,*ptr2,*ptr);
					//printk("Address 0x%x should 0x%x but 0x%x\n",ptr,skb->data[i],ptr[i]);
				}
				ptr++;
				ptr2++;
				//pattern++;
			}
		}
*/		
		spin_lock_dt(cpu_id? &ipc_head_data->sp_lock0:&ipc_head_data->sp_lock1);
		desc->func_ctrl.bit32 		= skb->len;
		wmb();
		if( (peer_priv_data->int_stat&FLAG_IPC_PROCESSING)==0 ) {	// set INT. flag for peer
			peer_priv_data->int_stat |= FLAG_IPC_INTERRUPT;
			writel(0x80000000,cpu_id?CPU1_STATUS:CPU0_STATUS);	// Req. INT
		}
		spin_unlock_dt(cpu_id? &ipc_head_data->sp_lock0:&ipc_head_data->sp_lock1);
		
		peer_priv_data->write_point = (IPC_RX_DESC_T *)desc->next_desc_addr;
		wmb();
		lb_stats = dev->priv;
		lb_stats->tx_bytes += skb->len;
		lb_stats->tx_packets++;
		dev_kfree_skb(skb);	// free skb
		
	}

	return(0);
}

#ifdef CONFIG_IPC_NAPI
static int ipc_poll(struct net_device *dev, int *budget)
{
	unsigned int work_done=0, work_to_do = min(*budget, dev->quota);
	struct net_device_stats *lb_stats;
	struct sk_buff	*skb;
	struct sk_buff	*new_skb;
	unsigned int pkt_size;
	volatile IPC_RX_DESC_T *desc;
		
	desc = local_priv_data->read_point;	
	rmb();
	while(((desc->func_ctrl.bit32&0x80000000)==0)&&(work_done<work_to_do)){
		rmb();
		pkt_size = desc->func_ctrl.bit32&0x0000FFFF;
		skb = desc->skb_ptr ;
		consistent_sync(skb->data,pkt_size+16,PCI_DMA_FROMDEVICE);
		wmb();
		skb->dev = dev;
		skb->ip_summed = CHECKSUM_UNNECESSARY;
		skb_put(skb, pkt_size);
		skb->protocol = eth_type_trans(skb,dev);
		
		// IPI debug
		//if(skb->len>64){
		//	if(((skb->data[skb->len-1]-1)==skb->data[skb->len-2])&&((skb->data[skb->len-2]-1)==skb->data[skb->len-3]))
		//		printk("IPI[RX]:Addr[0x%x] 0x%x,0x%x,0x%x,0x%x\n",&skb->data[skb->len-4],skb->data[skb->len-4],skb->data[skb->len-3],skb->data[skb->len-2],skb->data[skb->len-1]);
		//}
		
		netif_receive_skb(skb);  /* socket rx */
		dev->last_rx = jiffies;
		work_done++;
		
		lb_stats = dev->priv;
		lb_stats->rx_bytes += pkt_size;
		lb_stats->rx_packets++;
		
		if ((new_skb = dev_alloc_skb(IPC_MTU)) == NULL) {
			printk("%s::skb allocation fail!\n", __func__);
			while(1);
		}
		//consistent_sync(new_skb->data,IPC_MTU,PCI_DMA_BIDIRECTIONAL);
		//spin_lock_dt(cpu_id? &ipc_head_data->sp_lock1:&ipc_head_data->sp_lock0);
		desc->skb_ptr	= (unsigned int)new_skb ;
		desc->buf_addr = (unsigned int)(__pa(new_skb->data)+(cpu_id?0x4000000:0));
		desc->func_ctrl.bit32 = 0x80000000;
		wmb();
		local_priv_data->read_point = (IPC_RX_DESC_T *)desc->next_desc_addr;
		desc = local_priv_data->read_point;
		//spin_unlock_dt(cpu_id? &ipc_head_data->sp_lock1:&ipc_head_data->sp_lock0);
		
	}
	
	spin_lock_dt(cpu_id? &ipc_head_data->sp_lock1:&ipc_head_data->sp_lock0);
	
	*budget -= work_done;
	dev->quota -= work_done;

	if (work_done < work_to_do) {
		netif_rx_complete(dev);
		local_priv_data->int_stat &= ~FLAG_IPC_PROCESSING;
		smp_wmb();
		//if((desc->func_ctrl.bit32&0x80000000)!=0)	// no extra pending packet
		//	writel(0,cpu_id?CPU0_STATUS:CPU1_STATUS);	// clear interrupt
		//enable_irq(dev->irq);
	}
	
	spin_unlock_dt(cpu_id? &ipc_head_data->sp_lock1:&ipc_head_data->sp_lock0);
	
	return (work_done >= work_to_do);
}
#endif

static irqreturn_t ipc_isr(int irq, void *dev_instance, struct pt_regs *regs)
{
	struct net_device   *dev = (struct net_device *)dev_instance;
	struct net_device_stats *lb_stats;
	struct sk_buff	*skb;
	struct sk_buff	*new_skb;
	unsigned int pkt_size,i;
	IPC_RX_DESC_T *desc;
	unsigned int tmp;

	
#ifdef CONFIG_IPC_NAPI
	//disable_irq(dev->irq);
	tmp = local_priv_data->int_stat;
	if( !(tmp&FLAG_IPC_INTERRUPT) ) {			// SHARE INT, not for me
		writel(0,cpu_id?CPU0_STATUS:CPU1_STATUS);	// clear interrupt
		return IRQ_HANDLED;
	}
	barrier();
	tmp |= FLAG_IPC_PROCESSING;			// processing flag 	
	tmp &= ~FLAG_IPC_INTERRUPT;			// clear INT flag
	local_priv_data->int_stat = tmp;
	tmp = local_priv_data->int_stat;
	
	spin_lock_dt(cpu_id? &ipc_head_data->sp_lock1:&ipc_head_data->sp_lock0);
	writel(0,cpu_id?CPU0_STATUS:CPU1_STATUS);	// clear interrupt
	spin_unlock_dt(cpu_id? &ipc_head_data->sp_lock1:&ipc_head_data->sp_lock0);
	
	if (likely(netif_rx_schedule_prep(dev)))
		__netif_rx_schedule(dev);
		
	return IRQ_HANDLED;
#endif	

	desc = local_priv_data->read_point;
	
	do{	
		pkt_size = desc->func_ctrl.bit32&0x0000FFFF;
		//writel(0,cpu_id?CPU0_STATUS:CPU1_STATUS);	// clear interrupt
		//skb = (struct sk_buff *)__va(desc->buf_addr-(cpu_id?0x4000000:0));
		skb = desc->skb_ptr ;
		consistent_sync(skb->data,pkt_size,PCI_DMA_FROMDEVICE);
		wmb();
		skb->dev = dev;
		skb->ip_summed = CHECKSUM_UNNECESSARY;

/*		// compare data
		if(pkt_size>150){
			pattern = 0x06;
			for(i=0x36+6;i<pkt_size-6;i++){
				if(skb->data[i]^pattern){	// God .. mismatch
					// Trig hw here ...
					readl(0xF6600000);
					printk("IPC:RX error!!\n");
					printk("Address 0x%x should 0x%x but 0x%x\n",&skb->data[i],pattern,skb->data[i]);
				}
				pattern++;
			}
		}
		//
*/		//dev_kfree_skb(skb);
		
		skb_put(skb, pkt_size);
		skb->protocol = eth_type_trans(skb,dev);
		netif_rx(skb);  /* socket rx */
		dev->last_rx = jiffies;

		lb_stats = dev->priv;
		lb_stats->rx_bytes += pkt_size;
		lb_stats->rx_packets++;
		
		if ((new_skb = dev_alloc_skb(IPC_MTU)) == NULL) {
			printk("%s::skb allocation fail!\n", __func__);
			while(1);
		}
		consistent_sync(new_skb->data,IPC_MTU,PCI_DMA_FROMDEVICE);
		wmb();
		//REG32(new_skb->data) = (unsigned long)new_skb;
		//skb_reserve(new_skb, SKB_RESERVE_BYTES);
		desc->func_ctrl.bit32 = 0x80000000;
		desc->skb_ptr	= (unsigned int)new_skb ;
		desc->buf_addr = (unsigned int)(__pa(new_skb->data)+(cpu_id?0x4000000:0));
		local_priv_data->read_point = (IPC_RX_DESC_T *)desc->next_desc_addr;
		desc = local_priv_data->read_point;

	}while((desc->func_ctrl.bit32&0x80000000)==0);
	spin_lock_dt(cpu_id? &ipc_head_data->sp_lock1:&ipc_head_data->sp_lock0);
	writel(0,cpu_id?CPU0_STATUS:CPU1_STATUS);	// clear interrupt
	spin_unlock_dt(cpu_id? &ipc_head_data->sp_lock1:&ipc_head_data->sp_lock0);
	
	return IRQ_HANDLED;
}

static struct net_device_stats *ipc_if_get_stats(struct net_device *dev)
{
	struct net_device_stats *stats = dev->priv;

	if (!stats) {
		return NULL;
	}
				
	return stats;
}

static int ipc_dev_open(struct net_device *dev)
{
	int retval;
	
	retval = request_irq (dev->irq, ipc_isr, SA_SHIRQ, dev->name, dev);
	if (retval){
		printk("Request IPC interrupt fail");
		return retval;
	}
	local_priv_data->status	= IPC_UP;
	local_priv_data->int_stat = 0;
	if(cpu_id==0)
		ipc_head_data->sp_lock0.lock=0;
	else
		ipc_head_data->sp_lock1.lock=0;
	return 0;
}

static int ipc_dev_stop (struct net_device *dev)
{
	free_irq(dev->irq,dev);
	local_priv_data->status	= IPC_DOWN;
	return 0;
}

static int ipc_dev_set_mac_address(struct net_device *dev, void *addr)
{
	return 0;
}

static int ipc_dev_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
	return 0;
}

static void ipc_dev_setup(struct net_device *new_dev)
{
	struct net_device_stats *stats;
	
	SET_MODULE_OWNER(new_dev);
	stats = kmalloc(sizeof(struct net_device_stats), GFP_KERNEL);
	if (stats) {
		memset(stats, 0, sizeof(struct net_device_stats));
		new_dev->priv = stats;
	}
	    
	new_dev->get_stats 	= ipc_if_get_stats;		
	new_dev->tx_queue_len 	= IPC_DESC_NO;
	new_dev->irq		= IRQ_CPU0_IP_IRQ;
	new_dev->open 		= ipc_dev_open;
	new_dev->stop 		= ipc_dev_stop;
	new_dev->set_mac_address= ipc_dev_set_mac_address;
	new_dev->destructor 	= free_netdev;
	new_dev->do_ioctl 	= ipc_dev_ioctl;
	new_dev->hard_start_xmit= ipc_start_xmit;
	new_dev->mtu		= IPC_MTU-64;
	new_dev->hard_header_len= ETH_HLEN;
	new_dev->addr_len 	= ETH_ALEN;

#ifdef CONFIG_IPC_NAPI
	new_dev->poll = ipc_poll;
	new_dev->weight = IPC_NAPI_WEIGHT;
#endif	
	
	new_dev->features 	= NETIF_F_HIGHDMA |NETIF_F_LLTX
				 |NETIF_F_FRAGLIST;
	//new_dev->flags	  	= IFF_NOARP;
	new_dev->hard_start_xmit= ipc_start_xmit;
	new_dev->hard_header	= eth_header;
	new_dev->rebuild_header = eth_rebuild_header;
	memset(new_dev->broadcast, 0xFF, ETH_ALEN);
	new_dev->dev_addr[0]=0x00;
	new_dev->dev_addr[1]=0x50;
	new_dev->dev_addr[2]=0xC2;
	new_dev->dev_addr[3]=0x2B;
	new_dev->dev_addr[4]=0xDF;
	new_dev->dev_addr[5]=cpu_id ? 0xFE:0xFD;
}


/* Setup and register the loopback device. */
int __init ipc_if_init(void)
{

	struct net_device *pseudo_dev;
	int i;
	struct sk_buff	*skb;

	cpu_id = getcpuid();
	printk("CPU%d interface Initialize\n",cpu_id);
	
#ifdef DESC_IN_DRAM
	ipc_head_data = (IPC_HEAD_DESC_S *)IO_ADDRESS(0x7f00000);
#else
	// Initial Descript
	ipc_head_data = (IPC_HEAD_DESC_S *)IO_ADDRESS(SL2312_SRAM_BASE);
#endif
	local_priv_data = cpu_id ? &ipc_head_data->cpu1_priv : &ipc_head_data->cpu0_priv;
	peer_priv_data = cpu_id ? &ipc_head_data->cpu0_priv : &ipc_head_data->cpu1_priv;
	local_rx_desc = (IPC_RX_DESC_T *)(cpu_id ? &ipc_head_data->cpu1_rx_desc:&ipc_head_data->cpu0_rx_desc);
	peer_rx_desc = (IPC_RX_DESC_T *)(cpu_id ? &ipc_head_data->cpu0_rx_desc:&ipc_head_data->cpu1_rx_desc);
	
	for(i=0;i<IPC_DESC_NO-1;i++){
		local_rx_desc->func_ctrl.bits.own = DMA;
		if ((skb = dev_alloc_skb(IPC_MTU)) == NULL) {
			printk("%s::skb allocation fail!\n", __func__);
			while(1);
		}
		consistent_sync(skb->data,IPC_MTU,PCI_DMA_BIDIRECTIONAL);
		wmb();
		//REG32(skb->data) = (unsigned long)skb;
		//skb_reserve(skb, SKB_RESERVE_BYTES);
		local_rx_desc->skb_ptr	= (unsigned int)skb ;
		local_rx_desc->buf_addr = (unsigned int)(__pa(skb->data)+(cpu_id?0x4000000:0));
		local_rx_desc->next_desc_addr = (unsigned int)&local_rx_desc[1];
		local_rx_desc = &local_rx_desc[1];
	}
	local_rx_desc->func_ctrl.bits.own = DMA;
	if ((skb = dev_alloc_skb(IPC_MTU)) == NULL) {
		printk("%s::skb allocation fail!\n", __func__);
		while(1);
	}
	consistent_sync(skb->data,IPC_MTU,PCI_DMA_BIDIRECTIONAL);
	wmb();
	//REG32(skb->data) = (unsigned long)skb;
	//skb_reserve(skb, SKB_RESERVE_BYTES);
	local_rx_desc->skb_ptr	= (unsigned int)skb ;
	local_rx_desc->buf_addr = __pa(skb->data)+(cpu_id?0x4000000:0);
	local_rx_desc->next_desc_addr = \
	(unsigned int)(cpu_id ? &ipc_head_data->cpu1_rx_desc:&ipc_head_data->cpu0_rx_desc);
	local_rx_desc = (IPC_RX_DESC_T *)(cpu_id ? &ipc_head_data->cpu1_rx_desc:&ipc_head_data->cpu0_rx_desc);
	
	local_priv_data->read_point = local_rx_desc;
	local_priv_data->write_point = local_rx_desc;
	local_priv_data->status	= IPC_DOWN;
	
	rtnl_lock();
	pseudo_dev = alloc_etherdev(0);
	
	if(pseudo_dev ==NULL){
		printk("IPC dev alloc fial\n");
		return 0;
	}
	strcpy(pseudo_dev->name,"ipi");
	ipc_dev_setup(pseudo_dev);
	register_netdevice(pseudo_dev);
	rtnl_unlock();
	
	return 0;
};

module_init(ipc_if_init);
