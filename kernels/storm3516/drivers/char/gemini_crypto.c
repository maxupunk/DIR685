/*
 * FILE NAME gemini_i2s.c
 *
 * BRIEF MODULE DESCRIPTION
 *  Driver for CIR device.
 *
 *  Author: StorLink, Corp.
 *          Middle Huang
 *
 * Copyright 2005 StorLink, Corp.
 *
 *  This program is free software; you can redistribute  it and/or modify it
 *  under  the terms of  the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the  License, or (at your
 *  option) any later version.
 *
 *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS'' AND   ANY  EXPRESS OR IMPLIED
 *  WARRANTIES,   INCLUDING, BUT NOT  LIMit8712D  TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 *  NO  EVENT  SHALL   THE AUTHOR  BE	LIABLE FOR ANY   DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMit8712D   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF
 *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  You should have received a copy of the  GNU General Public License along
 *  with this program; if not, writ8712  to the Free Software Foundation, Inc.,
 *  675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <linux/module.h>
#include <linux/config.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/miscdevice.h>
#include <linux/interrupt.h>
#include <linux/init.h>
#include <asm/uaccess.h>
#include <linux/ioport.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/pci.h> 
#include <asm/hardware.h>
#include <asm/io.h>
#include <asm/delay.h>
#include <linux/signal.h>
#include <asm/scatterlist.h>

#include <asm/arch-sl2312/gemini_crypto.h>
#define     IPSEC_TEXT_LEN    32768 //2048

static unsigned char outpacket[IPSEC_TEXT_LEN];
static unsigned char inpacket[IPSEC_TEXT_LEN];
static struct PACKET_SSL  *arg_op;//, *cto_op;
static struct IPSEC_PACKET_S  *ipsec_op;
static struct dev_rand  *rand_op;

//IRQ_DMA_OFFSET  -> int_ctrl.h
// mknod /dev/smcrypto c 10 244
#define     IPSEC_PHYSICAL_BASE_ADDR	(SL2312_SECURITY_BASE)  //0x51000000
#define     IPSEC_BASE_ADDR			    (IO_ADDRESS(IPSEC_PHYSICAL_BASE_ADDR))
#define ipsec_read_reg(offset)              (readl(IPSEC_BASE_ADDR + offset))
#define IPSEC_RAND_NUM_REG  0x00ac

#ifndef SMCRYPTO_MINOR
#define SMCRYPTO_MINOR	249		// Documents/devices.txt suggest to use 240~255 for local driver!!
#endif

static int test_flag = 0;
/* ====== CryptoAPI ====== */

#define FILL_SG(sg,ptr,len)					\
	do {							\
		(sg)->page = virt_to_page(ptr);			\
		(sg)->offset = offset_in_page(ptr);		\
		(sg)->length = len;				\
		(sg)->dma_address = 0;				\
	} while (0)
	

static int smcrypto_open(struct inode *inode, struct file *file)
{
//		struct PACKET_SSL *cry_op;
//#ifdef CONFIG_SL2312_IPSEC
//	printk(KERN_INFO PFX "HW:stormdev_open.\n");
//#else	
//	printk(KERN_INFO PFX "SW:stormdev_open_open.\n");
//#endif
//	cry_op = kmalloc(sizeof(*cry_op), GFP_KERNEL);
//	if(!cry_op)
//		return -ENOMEM;
//
//	memset(cry_op, 0, sizeof(*cry_op));
//	init_MUTEX(&cry_op->sem);
//	INIT_LIST_HEAD(&cry_op->list);
//	filp->private_data = cry_op;
	rand_op = kmalloc(sizeof(struct dev_rand), GFP_KERNEL);
	if(!rand_op)
		return -ENOMEM;


	return 0;
}


static int smcrypto_release(struct inode *inode, struct file *file)
{
static struct dev_rand  *rand_op;
				
				if(rand_op)
					kfree(rand_op);
	return 0;
}



//static ssize_t smcrypto_write(struct file *file_p, const char __user *buf, size_t count, loff_t * ppos)
//{
//	
//}
//
//static ssize_t smcrypto_read(struct file * file_p, char __user *buf, size_t length, loff_t * ppos)
//{
//
//
//}


static int 	smcrypto_ioctl(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg)

{
	int ret = 0, i,j, value;
	struct scatterlist sg;
	

	unsigned char dname[2][8]={"md5","sha1"};
	unsigned int  dalgorithm[2][2]={{MD5,HMAC_MD5},{SHA1,HMAC_SHA1}};
	unsigned char cname[3][8]={"des","des3_ede","aes"};
  unsigned int  calgorithm[2][3]={{ECB_DES,ECB_3DES,ECB_AES},{CBC_DES,CBC_3DES,CBC_AES}};
		
		
		
	switch(cmd) {
		case DO_CRYPTO:
						
						//if(test_flag==0)
						//		test_flag=1;
						//else
						//	printk("%s :######################## re entry <--\n",__func__);
								
						//memset(arg_op, 0, sizeof(struct PACKET_SSL));
						//memset(ipsec_op, 0, sizeof(struct IPSEC_PACKET_S));
						//memset(&outpacket, 0, IPSEC_TEXT_LEN);
						//memset(&inpacket, 0, IPSEC_TEXT_LEN);
						
						if(arg) 
						{
									copy_from_user(arg_op, (void*)arg,  sizeof(struct PACKET_SSL));

									ipsec_op->op_mode = arg_op->op_mode;
									ipsec_op->pkt_len = arg_op->pkt_len;
									ipsec_op->cipher_algorithm = arg_op->cipher_algorithm;
									ipsec_op->auth_algorithm = arg_op->auth_algorithm;
									ipsec_op->auth_result_mode = arg_op->auth_result_mode;
									ipsec_op->process_id = arg_op->process_id;
									ipsec_op->auth_header_len = arg_op->auth_header_len;
									ipsec_op->auth_algorithm_len = arg_op->auth_algorithm_len;
									ipsec_op->cipher_header_len = arg_op->cipher_header_len;
									ipsec_op->cipher_algorithm_len = arg_op->cipher_algorithm_len;
									ipsec_op->iv_size = arg_op->iv_size;
									ipsec_op->auth_key_size = arg_op->auth_key_size;
									ipsec_op->cipher_key_size = arg_op->cipher_key_size;
									ipsec_op->callback = NULL;
									
									if(ipsec_op->iv_size > 0)
												memcpy(ipsec_op->iv, (unsigned char *)arg_op->iv, ipsec_op->iv_size);
											//copy_from_user(ipsec_op->iv, (unsigned char *)arg_op->iv, ipsec_op->iv_size);
									
									if(ipsec_op->auth_key_size > 0)
											memcpy(ipsec_op->auth_key, (unsigned char *)arg_op->auth_key, ipsec_op->auth_key_size);
											//copy_from_user(ipsec_op->auth_key, (unsigned char *)arg_op->auth_key, ipsec_op->auth_key_size);
											
									if(ipsec_op->cipher_key_size > 0)
											memcpy(ipsec_op->cipher_key, (unsigned char *)arg_op->cipher_key, ipsec_op->cipher_key_size);
											//copy_from_user(ipsec_op->cipher_key, (unsigned char *)arg_op->cipher_key, ipsec_op->cipher_key_size);
						
									
									ipsec_op->out_packet   = &outpacket;
									if(ipsec_op->pkt_len > 0)
									{
										copy_from_user(&inpacket, arg_op->in_packet, arg_op->pkt_len);

									}
									FILL_SG(&sg, &inpacket, ipsec_op->pkt_len);
									ipsec_op->in_packet   = &sg;
						}
				
							
								//printk("====DO_CRYPTO -->(len:%d opmod:%d cy_alg:%d authalg:%d)\n",ipsec_op->pkt_len,ipsec_op->op_mode,ipsec_op->cipher_algorithm,ipsec_op->auth_algorithm);

  						ipsec_crypto_hw_process(ipsec_op);
  						value = 0;
  						if(ipsec_op->out_pkt_len > 0)
  						{
  							if(ipsec_op->op_mode==AUTH)
  							{

										copy_to_user(arg_op->out_packet, (ipsec_op->out_packet+ipsec_op->pkt_len), (ipsec_op->out_pkt_len-ipsec_op->pkt_len));
										value = (ipsec_op->out_pkt_len-ipsec_op->pkt_len);

										//copy_to_user(&(arg_op->out_pkt_len), &value, sizeof(value));

								}
								else //if(ipsec_op->op_mode==AUTH)
								{
									
									copy_to_user(arg_op->out_packet, ipsec_op->out_packet, ipsec_op->out_pkt_len);
									value = ipsec_op->out_pkt_len;
									//copy_to_user(&(arg_op->out_pkt_len), &value, sizeof(value));

								}
								copy_to_user((void*)arg, arg_op, sizeof(struct PACKET_SSL));
							}
							else
								printk("%s :########################DO_CRYPTO no length <--\n",__func__);
								
							//if(test_flag==1)
							//	test_flag=0;

			break;
		

		case DO_GET_RAND32:
		
						if(arg) 
						{
									copy_from_user(rand_op, (void*)arg,  sizeof(struct dev_rand));
						}
						
						//printk("========= :DO_GET_RAND32 -->\n");
						//memset(&outpacket, 0, IPSEC_TEXT_LEN);
						if((rand_op->len/4)>0)
						{	
							for(i=0;i<rand_op->len;i+=4)
							{
									value = 0;
  								value = ipsec_read_reg(IPSEC_RAND_NUM_REG);
  								//memcpy(&outpacket[i],(unsigned char *)value,sizeof(int));
  								sprintf(&outpacket[i], "%c%c%c%c", value&0xff, (value>>8)&0xff, (value>>16)&0xff, (value>>24)&0xff);
  						}
  					}
  					if(rand_op->len%4)
  					{
  							value = 0;
  							value = ipsec_read_reg(IPSEC_RAND_NUM_REG);
  							//memcpy(&outpacket[i], (unsigned char *)value, (rand_op->len%4));
  							for(j=0;j<(rand_op->len%4);j++)
  									sprintf(&outpacket[i+j], "%c",(value>>(8*j)&0xff));
  					}
					
					copy_to_user(rand_op->buf, &outpacket[0], rand_op->len);
						//ret = -EFAULT;
			break;
		default:
			printk("%s :default <--\n",__func__);
			return -1;
	}
	return ret; 

}



static struct file_operations smcrypto_fops =
{
	.owner		=	THIS_MODULE,
	.ioctl		=	smcrypto_ioctl,
	.open		=	smcrypto_open,
	.release	=	smcrypto_release,
	//.write	= smcrypto_write,
	//.read	= smcrypto_read,
};

/* include/linux/miscdevice.h */
static struct miscdevice smcrypto_miscdev =
{
	SMCRYPTO_MINOR,
	"smcrypto",
	&smcrypto_fops
};
  

int __init smcrypto_init(void)
{

						arg_op = (struct PACKET_SSL *)kmalloc(sizeof(struct PACKET_SSL),GFP_ATOMIC);
						//cto_op = (struct PACKET_SSL *)kmalloc(sizeof(struct PACKET_SSL),GFP_ATOMIC);
						ipsec_op = (struct IPSEC_PACKET_S *)kmalloc(sizeof(struct IPSEC_PACKET_S),GFP_ATOMIC);
						//if(!arg_op||!cto_op||!ipsec_op)
						if(!arg_op||!ipsec_op)
						{
							if(!arg_op)
								kfree(arg_op);
							//if(!cto_op)
							//	kfree(cto_op);	
							if(!ipsec_op)
								kfree(ipsec_op);		
						  printk("%s : memory alloc error\n",__func__);
						  
							return -EFAULT;   
						}
						//memset(cto_op, 0, sizeof(struct PACKET_SSL));
						memset(arg_op, 0, sizeof(struct PACKET_SSL));
						memset(ipsec_op, 0, sizeof(struct IPSEC_PACKET_S));
						
	misc_register(&smcrypto_miscdev);
	
	printk("Storm crypto Initialization\n");
	return 0;
}	

void __exit smcrypto_exit(void)
{

}

module_init(smcrypto_init);
module_exit(smcrypto_exit);

MODULE_AUTHOR("Middle Huang <middle@stormsemi.com>");
MODULE_DESCRIPTION("Gemini crypto driver");
MODULE_LICENSE("GPL");
