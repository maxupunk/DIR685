/*
 *
 * BRIEF MODULE DESCRIPTION
 *      SL2312 IDE controller support
 *
 * Copyright 2003 StorLink Inc.
 * Author: StorLine, Inc.
 *         jason@storlink.com.tw
 *
 *  This program is free software; you can redistribute  it and/or modify it
 *  under  the terms of  the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the  License, or (at your
 *  option) any later version.
 *
 *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS'' AND   ANY  EXPRESS OR IMPLIED
 *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF
 *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  You should have received a copy of the  GNU General Public License along
 *  with this program; if not, write  to the Free Software Foundation, Inc.,
 *  675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <linux/config.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/ioport.h>
#include <linux/pci.h>
#include <linux/hdreg.h>
#include <linux/ide.h>
#include <linux/delay.h>
#include <linux/init.h>
#include <linux/ide.h>

#include <asm/io.h>
//#include <asm/arch/ide.h>
#include <asm/arch/sl2312.h>
#include <asm/arch/int_ctrl.h>

#define SL2312_IDE_DMA_OFFSET			0x00
#define SL2312_IDE_PIO_TIMING_OFFSET	0x10
#define SL2312_IDE_MDMA_TIMING_OFFSET	0x11		// only support 1 multi-word DMA device
#define SL2312_IDE_UDMA_TIMING0_OFFSET	0x12		// for master
#define SL2312_IDE_UDMA_TIMING1_OFFSET	0x13		// for slave
#define SL2312_IDE_CLK_MOD_OFFSET		0x14		
#define SL2312_IDE_CMD_OFFSET			0x20
#define SL2312_IDE_CTRL_OFFSET			0x36

/*
 * Prototypes
 */
static void sl2312_tune_drive (ide_drive_t *drive, byte pio);
#if defined(CONFIG_BLK_DEV_IDEDMA)
static byte sl2312_dma_2_pio (byte xfer_rate);
static int sl2312_tune_chipset (ide_drive_t *drive, byte speed);
static int sl2312_config_chipset_for_dma (ide_drive_t *drive);
static int sl2312_config_drive_xfer_rate(ide_drive_t *drive);
#endif

void __init ide_init_sl2312(void);

#ifndef CONFIG_SL3516_ASIC
#define SL2312_FPGA_IDE		1
#define SL2312_IDE_BEST_MODE	XFER_UDMA_2
#else
#define SL2312_IDE_BEST_MODE	XFER_UDMA_6
#endif

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

// convinient macro for chip timing setting
#define PIO_TIMING_REG	(*(volatile unsigned char *)(hwif->dma_base + SL2312_IDE_PIO_TIMING_OFFSET))
#define MDMA_TIMING_REG	(*(volatile unsigned char *)(hwif->dma_base + SL2312_IDE_MDMA_TIMING_OFFSET))
#define UDMA_TIMING0_REG	(*(volatile unsigned char *)(hwif->dma_base + SL2312_IDE_UDMA_TIMING0_OFFSET))
#define UDMA_TIMING1_REG	(*(volatile unsigned char *)(hwif->dma_base + SL2312_IDE_UDMA_TIMING1_OFFSET))
#define CLK_MOD_REG		(*(volatile unsigned char *)(hwif->dma_base + SL2312_IDE_CLK_MOD_OFFSET))

unsigned int iomux;
unsigned int sata_phy0=0;
unsigned int sata_phy1=0;
EXPORT_SYMBOL(iomux);
extern unsigned int ide0_base;

static ide_pci_device_t sl2312_chipsets[] __devinitdata = {
	{	/* 0 */
		.name		= "SL2312",
		.init_chipset	= NULL,
		.init_iops	= NULL,
		.init_hwif	= NULL,
		.channels	= 2,
		.autodma	= AUTODMA,
		.enablebits	= {{0x00,0x00,0x00}, {0x00,0x00,0x00}},
		.bootable	= ON_BOARD,
		.extra		= 0,
	},
	{
		.channels	= 0,
		.bootable	= NEVER_BOARD,
	}
};


static void sl2312_tune_drive (ide_drive_t *drive, byte pio)
{
    ide_hwif_t *hwif	= HWIF(drive);
    
    pio = ide_get_best_pio_mode(drive, pio, 5, NULL);
    PIO_TIMING_REG = PIO_TIMING[pio];
}

/*
 *
 */
static byte sl2312_dma_2_pio (byte xfer_rate)
{
    switch(xfer_rate) {
        case XFER_UDMA_5:
        case XFER_UDMA_4:
        case XFER_UDMA_3:
        case XFER_UDMA_2:
        case XFER_UDMA_1:
        case XFER_UDMA_0:
        case XFER_MW_DMA_2:
        case XFER_PIO_4:
    	    return 4;
        case XFER_MW_DMA_1:
        case XFER_PIO_3:
    	    return 3;
        case XFER_SW_DMA_2:
        case XFER_PIO_2:
    	    return 2;
        case XFER_MW_DMA_0:
        case XFER_SW_DMA_1:
        case XFER_SW_DMA_0:
        case XFER_PIO_1:
        case XFER_PIO_0:
        case XFER_PIO_SLOW:
        default:
    	    return 0;
    }
}

static int sl2312_tune_chipset (ide_drive_t *drive, byte speed)
{
    ide_hwif_t *hwif	= HWIF(drive);
    int err		= 0;
    int use66m = 0;
    
    //printk("sl2312_tune_chipset: hwif->dma_base = %08x\n", hwif->dma_base);
     
	if (speed & XFER_UDMA_0)	// ultra dma
		CLK_MOD_REG |= (1 << (4 + (drive->dn & 0x01)));
	else if (speed & XFER_MW_DMA_0)
		CLK_MOD_REG &= ~(1 << (4 + (drive->dn & 0x01)));
		
	// for better performance
	if ((speed == XFER_UDMA_6) || (speed == XFER_UDMA_3) || (speed == XFER_UDMA_4) || (speed & XFER_MW_DMA_0)) {
		use66m = 1;
#ifdef SL2312_FPGA_IDE
		CLK_MOD_REG &= ~(1 << (drive->dn & 0x01));
#else
		CLK_MOD_REG |= (1 << (drive->dn & 0x01));
#endif

		if (speed & XFER_MW_DMA_0) {
#ifdef SL2312_FPGA_IDE
			MDMA_TIMING_REG = TIMING_MDMA_50M[speed & ~XFER_MW_DMA_0];
#else
			MDMA_TIMING_REG = TIMING_MDMA_66M[speed & ~XFER_MW_DMA_0];
#endif
		}
		else {
			if (drive->dn & 0x01)
#ifdef SL2312_FPGA_IDE
				UDMA_TIMING1_REG = TIMING_UDMA_50M[speed & ~XFER_UDMA_0];
#else
				UDMA_TIMING1_REG = TIMING_UDMA_66M[speed & ~XFER_UDMA_0];
#endif
			else
#ifdef SL2312_FPGA_IDE
				UDMA_TIMING0_REG = TIMING_UDMA_50M[speed & ~XFER_UDMA_0];
#else
				UDMA_TIMING0_REG = TIMING_UDMA_66M[speed & ~XFER_UDMA_0];
#endif
		}
	}
	else {

		CLK_MOD_REG &= ~(1 << (drive->dn & 0x01));				// FPGA use 50MHz
		
		if (speed & XFER_MW_DMA_0) {
			MDMA_TIMING_REG = TIMING_MDMA_50M[speed & ~XFER_MW_DMA_0];
		}
		else {
			if (drive->dn & 0x01)
				UDMA_TIMING1_REG = TIMING_UDMA_50M[speed & ~XFER_UDMA_0];
			else
				UDMA_TIMING0_REG = TIMING_UDMA_50M[speed & ~XFER_UDMA_0];
		}
	}
    
    sl2312_tune_drive(drive, sl2312_dma_2_pio(speed));

    if (!drive->init_speed)
		drive->init_speed = speed;
    err = ide_config_drive_speed(drive, speed);
    drive->current_speed = speed;
    
    // show IDE mode
    printk("%s speed:",drive->name);
    if((speed&0x40) == 0x40)
    	printk("U%x (%sMHz)",speed&0x0F,use66m?"66":"50");
    else if((speed&0x20) == 0x20)
    	printk("MW%x ((%sMHz))",speed&0x0F,use66m?"66":"50");
    else 
    	printk("P%x ",(speed&0x0F)-8);
    printk("(0x%x)\n",speed);	
    
    return err;
}

static int sl2312_config_chipset_for_dma (ide_drive_t *drive)
{
    struct hd_driveid *id = drive->id;
    byte speed;


	if (id->dma_ultra & 0x0040) {
	    speed = XFER_UDMA_6;
	} 
	else if (id->dma_ultra & 0x0020) {
	    speed = XFER_UDMA_5;
	} 
	else if (id->dma_ultra & 0x0010) {
	    speed = XFER_UDMA_4;
    } 
    else if (id->dma_ultra & 0x0008) {
	    speed = XFER_UDMA_3;
    } 
    else if (id->dma_ultra & 0x0004) {
	    speed = XFER_UDMA_2;
    } 
    else if (id->dma_ultra & 0x0002) {
	    speed = XFER_UDMA_1;
    } 
    else if (id->dma_ultra & 0x0001) {
	    speed = XFER_UDMA_0;
    } 
    else if (id->dma_mword & 0x0004) {
	    speed = XFER_MW_DMA_2;
    } 
    else if (id->dma_mword & 0x0002) {
	    speed = XFER_MW_DMA_1;
    } 
    else if (id->dma_1word & 0x0004) {
	    speed = XFER_SW_DMA_2;
    } 
    else {
	    speed = XFER_PIO_0 + ide_get_best_pio_mode(drive, 255, 5, NULL);
    }
    
	if (speed > SL2312_IDE_BEST_MODE)
		speed = SL2312_IDE_BEST_MODE;

    sl2312_tune_chipset(drive, speed);
    return(ide_dma_enable(drive));

}

static int sl2312_config_drive_xfer_rate(ide_drive_t *drive)
{
        ide_hwif_t *hwif        = HWIF(drive);
        struct hd_driveid *id   = drive->id;
                                                                                                       
        drive->init_speed = 0;
                                                                                                       
        if (id && (id->capability & 1) && drive->autodma) {
                /* Consult the list of known "bad" drives */
//                if (__ide_dma_bad_drive(drive))
//                        goto fast_ata_pio;
                if (id->field_valid & 4) {
                        if (id->dma_ultra & hwif->ultra_mask) {
                                /* Force if Capable UltraDMA */
                                int dma = sl2312_config_chipset_for_dma(drive);
                                if ((id->field_valid & 2) && !dma)
                                        goto try_dma_modes;
                        }
                } else if (id->field_valid & 2) {
try_dma_modes:
                        if ((id->dma_mword & hwif->mwdma_mask) ||
                            (id->dma_1word & hwif->swdma_mask)) {
                                /* Force if Capable regular DMA modes */
                                if (!sl2312_config_chipset_for_dma(drive))
                                        goto no_dma_set;
                        }
//                } else if (__ide_dma_good_drive(drive) &&
//                           (id->eide_dma_time < 150)) {
//                        /* Consult the list of known "good" drives */
//                        if (!sl2312_config_chipset_for_dma(drive))
//                                goto no_dma_set;
                } 
                else {
                        goto fast_ata_pio;
                }
                return hwif->ide_dma_on(drive);
        } else if ((id->capability & 8) || (id->field_valid & 2)) {
fast_ata_pio:
no_dma_set:
                sl2312_tune_drive(drive, 5);
                return hwif->ide_dma_off_quietly(drive);
        }
         /* IORDY not supported */
        return 0;
}


static int sl2312_ide_dma_off(ide_drive_t *drive)
{
	drive->using_dma = 0;
	return 0;
}

static int sl2312_ide_dma_on(ide_drive_t *drive)
{
	ide_hwif_t *hwif	= HWIF(drive);
	u8 unit			= (drive->select.b.unit & 0x01);
	u8 dma_stat		= hwif->INB(hwif->dma_status);

	hwif->OUTB((dma_stat|(1<<(5+unit))), hwif->dma_status);
	drive->using_dma = 1;

	return 0;
}
/*
 *	This can be called for a dynamically installed interface. Don't __init it
 */

void __init ide_init_sl2312()
{
    ide_hwif_t *hwif;
    unsigned long cmdBase, ctrlBase;
    unsigned long baseptr;
    int h, channel, irq;

    unsigned int gdata;
    gdata = readl(0xf4000030);
    gdata &= ~0x07000000 ;

    gdata |= 0x02000012 ;
    iomux = 2;
#ifdef SATA_FIRST
    gdata |= 0x03000000 ;
    iomux = 3;
#endif

    writel(gdata,0xf4000030);
    gdata = 0x03;
#ifndef SATA_FIRST
    writel(gdata,0xf4600018);
    writel(0x00000011,0xF460001C);
#else
    writel(gdata,0xf460001C);
    writel(0x00000011,0xF4600018);
#endif
    mdelay(100);
 
    for (channel = 0; channel < 2; channel++) {
#ifndef CONFIG_BLK_DEV_SL2312_IDE_CHANNEL_0
		if (channel == 0)
			continue;
#endif		    	
#ifndef CONFIG_BLK_DEV_SL2312_IDE_CHANNEL_1
		if (channel == 1)
			continue;
#endif		    	    	
    	if (channel == 0) {
    		baseptr = (unsigned long)ioremap_nocache((unsigned long)SL2312_IDE0_BASE, 0x40);
    		irq = IRQ_IDE0_OFFSET;
#ifndef SATA_FIRST
    		ide0_base = baseptr + SL2312_IDE_CMD_OFFSET;
#endif    		
    		printk("ide %d: physical = %08x, virtual = %08x, irq = %d\n", channel, SL2312_IDE0_BASE, (unsigned int)baseptr, irq);
    	}
    	else {
    		baseptr = (unsigned long)ioremap_nocache((unsigned long)SL2312_IDE1_BASE, 0x40);
    		irq = IRQ_IDE1_OFFSET;
#ifdef SATA_FIRST
    		ide0_base = baseptr + SL2312_IDE_CMD_OFFSET;
#endif    		
    		printk("ide %d: physical = %08x, virtual = %08x, irq = %d\n", channel, SL2312_IDE1_BASE, (unsigned int)baseptr, irq);
    	}
    
    	for (h = 0; h < MAX_HWIFS; ++h) {
        	hwif = &ide_hwifs[h];
        	if (hwif->chipset == ide_unknown)
            	break;	/* pick an unused entry */
    	}         
    	
    	hwif->chipset = ide_sl2312;
    	hwif->autodma = 1;
    	hwif->tuneproc = &sl2312_tune_drive;
    	hwif->drives[0].autotune = 1;
    	hwif->drives[1].autotune = 1;
    	hwif->dma_base = baseptr + SL2312_IDE_DMA_OFFSET;
    	hwif->irq = irq;
        hwif->mmio = 2;
        
        hwif->atapi_dma = 1;
        hwif->ultra_mask = 0x7f;
        hwif->mwdma_mask = 0x06;
        hwif->swdma_mask = 0x04;
        hwif->udma_four = 1;
        hwif->autodma = 1;
    	hwif->ide_dma_check = &sl2312_config_drive_xfer_rate;
    	hwif->speedproc = &sl2312_tune_chipset;
		
		hwif->ide_dma_off_quietly = &sl2312_ide_dma_off;
		hwif->ide_dma_on = &sl2312_ide_dma_on;
		hwif->ide_dma_host_on	= &sl2312_ide_dma_on;
		hwif->drives[0].using_dma = 1;
		hwif->drives[1].using_dma = 1;
		hwif->drives[0].autodma = 1;
		hwif->drives[1].autodma = 1;
    	hwif->noprobe = 0;
        
       	hwif->cds = (struct ide_pci_device_s *) &sl2312_chipsets[0];
    	cmdBase = baseptr + SL2312_IDE_CMD_OFFSET;
    	ctrlBase = baseptr + SL2312_IDE_CTRL_OFFSET;
    
    	ide_init_hwif_ports(&hwif->hw, cmdBase, ctrlBase, NULL);
    	memcpy(hwif->io_ports, hwif->hw.io_ports, sizeof(hwif->io_ports));
    	ide_setup_dma(hwif, baseptr, 8);
    
#ifdef SATA_FIRST
	if(channel==0){
#else
	if(channel==1){
#endif
		hwif->hwif_data = (void *)"GEM_SATA";
		gdata = readl(IO_ADDRESS(SL2312_SATA_BASE)+0x08);
		if((gdata & 0x5)==0x5)
			sata_phy0 = 1;
		gdata = readl(IO_ADDRESS(SL2312_SATA_BASE)+0x0C);
		if((gdata&0x5)==0x5)
			sata_phy1 = 1;
	}
	else
		hwif->hwif_data = (void *)"GEM_ATA";
    }
}


