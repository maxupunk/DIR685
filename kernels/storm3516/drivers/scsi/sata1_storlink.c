/*
 *  sata_storlink.c - Storlinksemi SATA
 *
 *  Copyright 2006 STORLINK Corp.  All rights reserved.
 *  Copyright 2004 Jason Lee
 *
 *
 *  Alternatively, the contents of this file may be used under the terms
 *  of the GNU General Public License version 2 (the "GPL") as distributed
 *  in the kernel source COPYING file, in which case the provisions of
 *  the GPL are applicable instead of the above.  If you wish to allow
 *  the use of your version of this file only under the terms of the
 *  GPL and not to allow others to use your version of this file under
 *  the OSL, indicate your decision by deleting the provisions above and
 *  replace them with the notice and other provisions required by the GPL.
 *  If you do not delete the provisions above, a recipient may use your
 *  version of this file under either the OSL or the GPL.
 *
 *
 *  0.01
 *     - Initial revision.
 */

#include <linux/config.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/pci.h>
#include <linux/init.h>
#include <linux/blkdev.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include "scsi.h"
#include <scsi/scsi_host.h>
#include <linux/libata.h>
#include <asm/arch/sl2312.h>

#define DRV_NAME			"sata_lepus1"
#define DRV_VERSION			"0.1"

#define lepus_sata_PORTS			2
#define LEPUS_SATA_PIO_MASK			0x1f
#define LEPUS_SATA_MWDMA_MASK			0x07
#define LEPUS_SATA_UDMA_MASK			0x7f
#define lepus_sata_PORT0_SCR_REG_OFFSET		0x00
#define lepus_sata_PORT1_SCR_REG_OFFSET		0x40

#define lepus_sata_INT_STATUS			0x10
#define lepus_sata_INT_STATUS_CK804		0x440
#define lepus_sata_INT_STATUS_PDEV_INT		0x01
#define lepus_sata_INT_STATUS_PDEV_PM		0x02
#define lepus_sata_INT_STATUS_PDEV_ADDED	0x04
#define lepus_sata_INT_STATUS_PDEV_REMOVED	0x08
#define lepus_sata_INT_STATUS_SDEV_INT		0x10
#define lepus_sata_INT_STATUS_SDEV_PM		0x20
#define lepus_sata_INT_STATUS_SDEV_ADDED	0x40
#define lepus_sata_INT_STATUS_SDEV_REMOVED	0x80
#define lepus_sata_INT_STATUS_PDEV_HOTPLUG	(lepus_sata_INT_STATUS_PDEV_ADDED | \
					lepus_sata_INT_STATUS_PDEV_REMOVED)
#define lepus_sata_INT_STATUS_SDEV_HOTPLUG	(lepus_sata_INT_STATUS_SDEV_ADDED | \
					lepus_sata_INT_STATUS_SDEV_REMOVED)
#define lepus_sata_INT_STATUS_HOTPLUG		(lepus_sata_INT_STATUS_PDEV_HOTPLUG | \
					lepus_sata_INT_STATUS_SDEV_HOTPLUG)

#define lepus_sata_INT_ENABLE			0x11
#define lepus_sata_INT_ENABLE_CK804		0x441
#define lepus_sata_INT_ENABLE_PDEV_MASK		0x01
#define lepus_sata_INT_ENABLE_PDEV_PM		0x02
#define lepus_sata_INT_ENABLE_PDEV_ADDED	0x04
#define lepus_sata_INT_ENABLE_PDEV_REMOVED	0x08
#define lepus_sata_INT_ENABLE_SDEV_MASK		0x10
#define lepus_sata_INT_ENABLE_SDEV_PM		0x20
#define lepus_sata_INT_ENABLE_SDEV_ADDED	0x40
#define lepus_sata_INT_ENABLE_SDEV_REMOVED	0x80
#define lepus_sata_INT_ENABLE_PDEV_HOTPLUG	(lepus_sata_INT_ENABLE_PDEV_ADDED | \
					lepus_sata_INT_ENABLE_PDEV_REMOVED)
#define lepus_sata_INT_ENABLE_SDEV_HOTPLUG	(lepus_sata_INT_ENABLE_SDEV_ADDED | \
					lepus_sata_INT_ENABLE_SDEV_REMOVED)
#define lepus_sata_INT_ENABLE_HOTPLUG		(lepus_sata_INT_ENABLE_PDEV_HOTPLUG | \
					lepus_sata_INT_ENABLE_SDEV_HOTPLUG)


#define SATA_HOT_PLUG_ENABLE		0x10

#define SATA_ENABLE_CMD0			0x38
#define SATA_ENABLE_CMD1			0x48
#define SATA_DISABLE_CMD0			SATA_ENABLE_CMD0
#define SATA_DISABLE_CMD1			0xA0

#define SATA_CONTROL_REG0			0x18
#define SATA_CONTROL_REG1			0x1C

#ifndef SL2312_FPGA_IDE
static unsigned char PIO_TIMING[5] = { 0xaa, 0xa3, 0xa1, 0x33, 0x31 };
static unsigned char TIMING_MDMA_50M[3] = { 0x66, 0x22, 0x21 };
static unsigned char TIMING_MDMA_66M[3] = { 0x88, 0x32, 0x31 };
static unsigned char TIMING_UDMA_50M[6] = { 0x33, 0x31, 0x21, 0x21, 0x11, 0x91 };
static unsigned char TIMING_UDMA_66M[7] = { 0x44, 0x42, 0x31, 0x21, 0x11, 0x91,  0x91};
#else
static unsigned char PIO_TIMING[5] = { 0x88, 0x82, 0x81, 0x32, 0x21 };
static unsigned char TIMING_MDMA_50M[3] = { 0x33, 0x11, 0x11 };
static unsigned char TIMING_MDMA_66M[3] = { 0x33, 0x11, 0x11 };
static unsigned char TIMING_UDMA_50M[6] = { 0x22, 0x11, 0x11, 0x11 };
static unsigned char TIMING_UDMA_66M[7] = { 0x22, 0x11, 0x11, 0x11 };
#endif

#define SL2312_IDE_DMA_OFFSET			0x00
#define SL2312_IDE_PIO_TIMING_OFFSET	0x10
#define SL2312_IDE_MDMA_TIMING_OFFSET	0x11		// only support 1 multi-word DMA device
#define SL2312_IDE_UDMA_TIMING0_OFFSET	0x12		// for master
#define SL2312_IDE_UDMA_TIMING1_OFFSET	0x13		// for slave
#define SL2312_IDE_CLK_MOD_OFFSET		0x14		
#define SL2312_IDE_CMD_OFFSET			0x20
#define SL2312_IDE_CTRL_OFFSET			0x36

#define SATA_REG_PHY_STATUS0				0x08
#define SATA_REG_PHY_STATUS1				0x0C


#define PIO_TIMING_REG	(*(volatile unsigned char *)(ap->ioaddr.bmdma_addr + SL2312_IDE_PIO_TIMING_OFFSET))
#define MDMA_TIMING_REG	(*(volatile unsigned char *)(ap->ioaddr.bmdma_addr + SL2312_IDE_MDMA_TIMING_OFFSET))
#define UDMA_TIMING0_REG	(*(volatile unsigned char *)(ap->ioaddr.bmdma_addr + SL2312_IDE_UDMA_TIMING0_OFFSET))
#define UDMA_TIMING1_REG	(*(volatile unsigned char *)(ap->ioaddr.bmdma_addr + SL2312_IDE_UDMA_TIMING1_OFFSET))
#define CLK_MOD_REG		(*(volatile unsigned char *)(ap->ioaddr.bmdma_addr + SL2312_IDE_CLK_MOD_OFFSET))



static int lepus_sata_init_one (struct device *pdev);
irqreturn_t lepus_sata_interrupt (int irq, void *dev_instance, struct pt_regs *regs);
static u32 lepus_sata_scr_read (struct ata_port *ap, unsigned int sc_reg);
static void lepus_sata_scr_write (struct ata_port *ap, unsigned int sc_reg, u32 val);
static void lepus_sata_host_stop (struct ata_host_set *host_set);
static void lepus_phy_reset (struct ata_port *ap);
static void lepus_set_piomode(struct ata_port *, struct ata_device *);
static void lepus_set_dmamode(struct ata_port *, struct ata_device *);

enum lepus_sata_host_type
{
	ATA_HOST,
	SATA_HOST,
};


#define lepus_sata_HOST_FLAGS_SCR_MMIO	0x00000001

struct lupus_host_desc
{
	enum lepus_sata_host_type	host_type;
	unsigned long		host_flags;
	void			(*enable_hotplug)(struct ata_probe_ent *probe_ent);
	void			(*disable_hotplug)(struct ata_host_set *host_set);
	void			(*check_hotplug)(struct ata_host_set *host_set);

};

struct lepus_sata_host
{
	struct lupus_host_desc	*host_desc;
};

static struct  scsi_host_template lepus_sata_sht = {
	.module			= THIS_MODULE,
	.name			= DRV_NAME,
	.ioctl			= ata_scsi_ioctl,
	.queuecommand		= ata_scsi_queuecmd,
	.eh_strategy_handler	= ata_scsi_error,
	.can_queue		= ATA_DEF_QUEUE,
	.this_id		= ATA_SHT_THIS_ID,
	.sg_tablesize		= LIBATA_MAX_PRD,
	.max_sectors		= ATA_MAX_SECTORS,
	.cmd_per_lun		= ATA_SHT_CMD_PER_LUN,
	.emulated		= ATA_SHT_EMULATED,
	.use_clustering		= ATA_SHT_USE_CLUSTERING,
	.proc_name		= DRV_NAME,
	.dma_boundary		= ATA_DMA_BOUNDARY,
	.slave_configure	= ata_scsi_slave_config,
	.bios_param		= ata_std_bios_param,
	.ordered_flush		= 1,
};

static struct ata_port_operations lepus_sata_ops = {
	.port_disable		= ata_port_disable,
	.check_status	= ata_check_status,
	.set_piomode	= lepus_set_piomode,
	.set_dmamode	= lepus_set_dmamode,
	.tf_load		= ata_tf_load,
	.tf_read		= ata_tf_read,
	.exec_command		= ata_exec_command,
	.check_status		= ata_check_status,
	.dev_select		= ata_std_dev_select,
	.phy_reset		= lepus_phy_reset,
	.bmdma_setup		= ata_bmdma_setup,
	.bmdma_start		= ata_bmdma_start,
	.bmdma_stop		= ata_bmdma_stop,
	.bmdma_status	= ata_bmdma_status,
	.qc_prep		= ata_qc_prep,
	.qc_issue		= ata_qc_issue_prot,
	.eng_timeout		= ata_eng_timeout,
	.irq_handler		= ata_interrupt,/*lepus_sata_interrupt,*/
	.irq_clear		= ata_bmdma_irq_clear,
	.scr_read		= lepus_sata_scr_read,
	.scr_write		= lepus_sata_scr_write,
	.port_start		= ata_port_start,
	.port_stop		= ata_port_stop,
	.host_stop		= lepus_sata_host_stop,
};

/* FIXME: The hardware provides the necessary SATA PHY controls
 * to support ATA_FLAG_SATA_RESET.  However, it is currently
 * necessary to disable that flag, to solve misdetection problems.
 * See http://bugme.osdl.org/show_bug.cgi?id=3352 for more info.
 *
 * This problem really needs to be investigated further.  But in the
 * meantime, we avoid ATA_FLAG_SATA_RESET to get people working.
 */
static struct ata_port_info lepus_sata_port_info = {
	.sht		= &lepus_sata_sht,
	.host_flags	= ATA_FLAG_SATA | 
			  /* ATA_FLAG_SATA_RESET | */
			  ATA_FLAG_SRST |
#ifdef CONFIG_GEMINI_4BAY_SATA
			  ATA_FLAG_SLAVE_POSS |
#endif
			  ATA_FLAG_MMIO,
	.pio_mask	= LEPUS_SATA_PIO_MASK,
	.mwdma_mask	= LEPUS_SATA_MWDMA_MASK,
	.udma_mask	= LEPUS_SATA_UDMA_MASK,
	.port_ops	= &lepus_sata_ops,
};

MODULE_AUTHOR("STORLINK <Jason Lee>");
MODULE_DESCRIPTION("low-level driver for Gemini SATA Bridge driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);

irqreturn_t lepus_sata_interrupt (int irq, void *dev_instance, struct pt_regs *regs)
{
	struct ata_host_set *host_set = dev_instance;
	unsigned int i;
	unsigned int handled = 0;
	unsigned long flags;

	spin_lock_irqsave(&host_set->lock, flags);

	for (i = 0; i < host_set->n_ports; i++) {
		struct ata_port *ap;

		ap = host_set->ports[i];
		if (ap && (!(ap->flags & ATA_FLAG_PORT_DISABLED))) {
			struct ata_queued_cmd *qc;

			qc = ata_qc_from_tag(ap, ap->active_tag);
			if (qc && (!(qc->tf.ctl & ATA_NIEN)))
				handled += ata_host_intr(ap, qc);
		}

	}

//	if (host->host_desc->check_hotplug)
//		host->host_desc->check_hotplug(host_set);

	spin_unlock_irqrestore(&host_set->lock, flags);

	return IRQ_RETVAL(handled);
}

u32 lepus_sata_scr_read (struct ata_port *ap, unsigned int sc_reg)
{
	struct ata_host_set *host_set = ap->host_set;
	struct lepus_sata_host *host = host_set->private_data;

	if (sc_reg > SCR_CONTROL)
		return 0xffffffffU;

	switch (sc_reg) {
		case SCR_STATUS:	
			return 0x3; 
			break;
		case SCR_CONTROL:	
			break;
		case SCR_ERROR:		
			break;
		case SCR_ACTIVE:	
			break;
		default:
			return 0xffffffffU;
	}
	return 0xffffffffU;

	if (host->host_desc->host_flags & lepus_sata_HOST_FLAGS_SCR_MMIO)
		return readl(ap->ioaddr.scr_addr + (sc_reg * 4));
	else
		return inl(ap->ioaddr.scr_addr + (sc_reg * 4));
}

void lepus_sata_scr_write (struct ata_port *ap, unsigned int sc_reg, u32 val)
{
	struct ata_host_set *host_set = ap->host_set;
	struct lepus_sata_host *host = host_set->private_data;

	if (sc_reg > SCR_CONTROL)
		return;
	
	return ;

	if (host->host_desc->host_flags & lepus_sata_HOST_FLAGS_SCR_MMIO)
		writel(val, ap->ioaddr.scr_addr + (sc_reg * 4));
	else
		outl(val, ap->ioaddr.scr_addr + (sc_reg * 4));
}
extern unsigned int gemini_sata_probe_flag;
void lepus_phy_reset (struct ata_port *ap)
{
	u32 status_p1,reg;
	unsigned long timeout = jiffies + (HZ * 1);
#ifndef CONFIG_GEMINI_4BAY_SATA
	reg = readl(IO_ADDRESS(SL2312_GLOBAL_BASE)+GLOBAL_RESET_REG);
	reg |=RESET_SATA1;
	writel(reg,IO_ADDRESS(SL2312_GLOBAL_BASE)+GLOBAL_RESET_REG);	// Reset SATA module
		
	msleep(10);
	
	do{
		msleep(100);
		status_p1 = inl(ap->ioaddr.scr_addr + SATA_REG_PHY_STATUS1);
		if(status_p1&0x01)
			break;
	}while (time_before(jiffies, timeout));
	if((gemini_sata_probe_flag&0x80000000) && !(status_p1&0x01)){
		ap->device[gemini_sata_probe_flag&0x00000001].class = ATA_DEV_NONE;
		printk("PHY not ready!!\n");
		return ;
	}

#else
//	status_p1 = 1;
	if(gemini_sata_probe_flag&0x80000000){
		status_p1 = inl(ap->ioaddr.scr_addr +  \
				((gemini_sata_probe_flag&0x0001)?SATA_REG_PHY_STATUS0:SATA_REG_PHY_STATUS1));
		status_p1 &= 0x01;
		if(!status_p1){
			ap->device[gemini_sata_probe_flag&0x0001].class = ATA_DEV_NONE;
			printk("PHY not ready!!\n");
			return ;
		}
	}
	else{
		status_p1 = inl(ap->ioaddr.scr_addr + SATA_REG_PHY_STATUS1)|
				inl(ap->ioaddr.scr_addr + SATA_REG_PHY_STATUS0);
		//status_p1 = 1;
	}
#endif

	if((status_p1&0x01))		// device attach and link estabilished
		ata_port_probe(ap);
	else
		ata_port_disable(ap);
	
	ap->cbl = ATA_CBL_SATA;
	
	if (ap->flags & ATA_FLAG_PORT_DISABLED)
		return;
	ata_bus_reset(ap);
}

void lepus_sata_host_stop (struct ata_host_set *host_set)
{
//	struct lepus_sata_host *host = host_set->private_data;

	// Disable hotplug event interrupts.
//	if (host->host_desc->disable_hotplug)
//		host->host_desc->disable_hotplug(host_set);

//	kfree(host);
}

void lepus_set_piomode(struct ata_port *ap, struct ata_device *adev)
{
	unsigned int pio	= adev->pio_mode - XFER_PIO_0;
	PIO_TIMING_REG = PIO_TIMING[pio];
}

void lepus_set_dmamode(struct ata_port *ap, struct ata_device *adev)
{
	unsigned int udma	= adev->dma_mode; /* FIXME: MWDMA too */
	u8 speed		= udma;
	unsigned int drive_dn	= (ap->hard_port_no ? 2 : 0) + adev->devno;
	         
	if (speed & XFER_UDMA_0)	// ultra dma
		CLK_MOD_REG |= (1 << (4 + (drive_dn & 0x01)));
	else if (speed & XFER_MW_DMA_0)
		CLK_MOD_REG &= ~(1 << (4 + (drive_dn & 0x01)));
		
	// for better performance
	if ((speed == XFER_UDMA_6) || (speed == XFER_UDMA_3) || (speed == XFER_UDMA_4) || (speed & XFER_MW_DMA_0)) {
#ifdef SL2312_FPGA_IDE
		CLK_MOD_REG |= (1 << (drive_dn & 0x01));
#else
		CLK_MOD_REG |= (1 << (drive_dn & 0x01));
#endif
		if (speed & XFER_MW_DMA_0) {
			MDMA_TIMING_REG = TIMING_MDMA_66M[speed & ~XFER_MW_DMA_0];
		}
		else {
			if (drive_dn & 0x01)
				UDMA_TIMING1_REG = TIMING_UDMA_66M[speed & ~XFER_UDMA_0];
			else
				UDMA_TIMING0_REG = TIMING_UDMA_66M[speed & ~XFER_UDMA_0];
		}
	}
	else {
#ifdef SL2312_FPGA_IDE
		CLK_MOD_REG |= (1 << (drive_dn & 0x01));
#else
		CLK_MOD_REG &= ~(1 << (drive_dn & 0x01));
#endif
		
		if (speed & XFER_MW_DMA_0) {
			MDMA_TIMING_REG = TIMING_MDMA_50M[speed & ~XFER_MW_DMA_0];
		}
		else {
			if (drive_dn & 0x01)
				UDMA_TIMING1_REG = TIMING_UDMA_50M[speed & ~XFER_UDMA_0];
			else
				UDMA_TIMING0_REG = TIMING_UDMA_50M[speed & ~XFER_UDMA_0];
		}
	}
    
//    sl2312_tune_drive(drive, sl2312_dma_2_pio(speed));
  
    // show IDE mode
    printk("HD speed:");
    if((speed&0x40) == 0x40)
    	printk("U%x ",speed&0x0F);
    else if((speed&0x20) == 0x20)
    	printk("MW%x ",speed&0x0F);
    else 
    	printk("P%x ",(speed&0x0F)-8);
    printk("(0x%x)\n",speed);	
    
    return ;
    
}

void lepus_sata_setup_port(struct ata_ioports *port, unsigned long base)
{
	port->bmdma_addr	= base;
	port->cmd_addr		= 
	port->data_addr		= base + 0x20;
	port->feature_addr	= 
	port->error_addr	= base + 0x21;
	port->nsect_addr	= base + 0x22;
	port->lbal_addr		= base + 0x23;
	port->lbam_addr		= base + 0x24;
	port->lbah_addr		= base + 0x25;
	port->device_addr	= base + 0x26;
	port->command_addr	=
	port->status_addr	= base + 0x27;
	port->altstatus_addr	=
	port->ctl_addr		= base + 0x36;

}

int lepus_sata_init_one (struct device *pdev)
{
	static int printed_version = 0;
	struct lepus_sata_host *host;
	struct ata_probe_ent *probe_ent;
	int rc=0;
	
	unsigned int reg;
    reg = readl(IO_ADDRESS(SL2312_GLOBAL_BASE)+GLOBAL_MISC_REG);
    reg &= ~0x07000000 ;
//    reg |= 0x02000017 ;
//    writel(reg,IO_ADDRESS(SL2312_GLOBAL_BASE)+GLOBAL_MISC_REG);											// IO-mux
//	writel(0x03,IO_ADDRESS(SL2312_SATA_BASE)+0x18);					// Enable SATA salve mode	

	if (!printed_version++)
		printk(DRV_NAME " version " DRV_VERSION "\n");

	probe_ent = kmalloc(sizeof(*probe_ent), GFP_KERNEL);
	
	host = kmalloc(sizeof(struct lepus_sata_host), GFP_KERNEL);
	if (!host)
		goto err_out_free_ent;

	probe_ent->sht		= lepus_sata_port_info.sht;
	probe_ent->host_flags	= lepus_sata_port_info.host_flags;
	probe_ent->pio_mask	= lepus_sata_port_info.pio_mask;
	probe_ent->mwdma_mask	= lepus_sata_port_info.mwdma_mask;
	probe_ent->udma_mask	= lepus_sata_port_info.udma_mask;
	probe_ent->port_ops	= lepus_sata_port_info.port_ops;
	probe_ent->irq = 4+1;
	
	probe_ent->private_data = host;
	probe_ent->dev = pdev;

	probe_ent->mmio_base = ioremap_nocache((unsigned long)SL2312_IDE1_BASE, 0x40);
	if (probe_ent->mmio_base == NULL) {
		rc = -EIO;
		goto err_out_free_host;
	}
	lepus_sata_setup_port(&probe_ent->port[0], probe_ent->mmio_base );

	probe_ent->port[0].scr_addr = ioremap_nocache((unsigned long)SL2312_SATA_BASE, 0x40);
	
	probe_ent->n_ports = 1;
	
	rc = ata_device_add(probe_ent);

	// Enable hotplug event interrupts.
//	if (host->host_desc->enable_hotplug)
//		host->host_desc->enable_hotplug(probe_ent);

	kfree(probe_ent);

	return 0;

err_out_free_host:
	kfree(host);
err_out_free_ent:
	kfree(probe_ent);
	return rc;
}


int lepus_sata_remove_one(struct device *pdev)
{
	struct device *dev = pdev;
	struct ata_host_set *host_set = dev_get_drvdata(dev);
	struct ata_port *ap;
	unsigned int i;

	for (i = 0; i < host_set->n_ports; i++) {
		ap = host_set->ports[i];

		scsi_remove_host(ap->host);
	}

	free_irq(host_set->irq, host_set);
	if (host_set->ops->host_stop)
		host_set->ops->host_stop(host_set);
	if (host_set->mmio_base)
		iounmap(host_set->mmio_base);


	for (i = 0; i < host_set->n_ports; i++) {
		ap = host_set->ports[i];
		ata_scsi_release(ap->host);

		scsi_host_put(ap->host);
	}

	for (i = 0; i < host_set->n_ports; i++) {
		struct ata_ioports *ioaddr;

		ap = host_set->ports[i];
		ioaddr = &ap->ioaddr;

		if ((ap->flags & ATA_FLAG_NO_LEGACY) == 0) {
			if (ioaddr->cmd_addr == 0x1f0)
				release_region(0x1f0, 8);
			else if (ioaddr->cmd_addr == 0x170)
				release_region(0x170, 8);
		}
	}

	kfree(host_set);
	dev_set_drvdata(dev, NULL);
	return 0;
}

#ifdef CONFIG_PM
static int lepus_sata_suspend(struct device *dev, pm_message_t state)
{
	printk("%s: not implemented yet\n", __FUNCTION__);

	return 0;
}

static int lepus_sata_resume(struct device *dev)
{
	printk("%s: not implemented yet\n", __FUNCTION__);

	return 0;
}
#endif

static struct device_driver lepus_sata_driver = {
	.name		= "lepus-sata",
	.bus		= &platform_bus_type,
	.probe		= lepus_sata_init_one,
	.remove		= lepus_sata_remove_one,
#ifdef CONFIG_PM
	.suspend	= lepus_sata_suspend,
	.resume		= lepus_sata_resume,
#endif
};

static int __init lepus_sata_init(void)
{
	return driver_register(&lepus_sata_driver);
}

static void __exit lepus_sata_exit(void)
{
	driver_unregister(&lepus_sata_driver);
}


module_init(lepus_sata_init);
module_exit(lepus_sata_exit);
