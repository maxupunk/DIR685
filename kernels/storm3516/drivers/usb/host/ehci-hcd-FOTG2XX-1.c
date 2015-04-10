/*
 * Copyright (c) 2000-2004 by David Brownell
 * 
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <linux/config.h>

#ifdef CONFIG_USB_DEBUG
	#define DEBUG
#else
	#undef DEBUG
#endif
#include <linux/platform_device.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/pci.h>
#include <linux/dmapool.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/ioport.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/smp_lock.h>
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/timer.h>
#include <linux/list.h>
#include <linux/interrupt.h>
#include <linux/reboot.h>
#include <linux/usb.h>
#include <linux/usb_otg.h>
#include <linux/moduleparam.h>
#include <linux/dma-mapping.h>

#include "../core/hcd.h"


#include <asm/byteorder.h>
#include <asm/io.h>
#include <asm/irq.h>
#include <asm/system.h>
#include <asm/unaligned.h>


/*-------------------------------------------------------------------------*/

/*
 * EHCI hc_driver implementation ... experimental, incomplete.
 * Based on the final 1.0 register interface specification.
 *
 * USB 2.0 shows up in upcoming www.pcmcia.org technology.
 * First was PCMCIA, like ISA; then CardBus, which is PCI.
 * Next comes "CardBay", using USB 2.0 signals.
 *
 * Contains additional contributions by Brad Hards, Rory Bolt, and others.
 * Special thanks to Intel and VIA for providing host controllers to
 * test this driver on, and Cypress (including In-System Design) for
 * providing early devices for those host controllers to talk to!
 *
 * HISTORY:
 *
 * 2004-05-10 Root hub and PCI suspend/resume support; remote wakeup. (db)
 * 2004-02-24 Replace pci_* with generic dma_* API calls (dsaxena@plexity.net)
 * 2003-12-29 Rewritten high speed iso transfer support (by Michal Sojka,
 *	<sojkam@centrum.cz>, updates by DB).
 *
 * 2002-11-29	Correct handling for hw async_next register.
 * 2002-08-06	Handling for bulk and interrupt transfers is mostly shared;
 *	only scheduling is different, no arbitrary limitations.
 * 2002-07-25	Sanity check PCI reads, mostly for better cardbus support,
 * 	clean up HC run state handshaking.
 * 2002-05-24	Preliminary FS/LS interrupts, using scheduling shortcuts
 * 2002-05-11	Clear TT errors for FS/LS ctrl/bulk.  Fill in some other
 *	missing pieces:  enabling 64bit dma, handoff from BIOS/SMM.
 * 2002-05-07	Some error path cleanups to report better errors; wmb();
 *	use non-CVS version id; better iso bandwidth claim.
 * 2002-04-19	Control/bulk/interrupt submit no longer uses giveback() on
 *	errors in submit path.  Bugfixes to interrupt scheduling/processing.
 * 2002-03-05	Initial high-speed ISO support; reduce ITD memory; shift
 *	more checking to generic hcd framework (db).  Make it work with
 *	Philips EHCI; reduce PCI traffic; shorten IRQ path (Rory Bolt).
 * 2002-01-14	Minor cleanup; version synch.
 * 2002-01-08	Fix roothub handoff of FS/LS to companion controllers.
 * 2002-01-04	Control/Bulk queuing behaves.
 *
 * 2001-12-12	Initial patch version for Linux 2.5.1 kernel.
 * 2001-June	Works with usb-storage and NEC EHCI on 2.4
 */
#if !defined  (CONFIG_USB_SL2312_1) && !defined (CONFIG_USB_SL2312_1_MODULE)
#define DRIVER_VERSION "10 Dec 2004"
#define DRIVER_AUTHOR "David Brownell"
#define DRIVER_DESC "USB 2.0 'Enhanced' Host Controller (EHCI) Driver"
#endif
static const char	hcd_name [] = "ehci_hcd";
extern int hcd_register_root (struct usb_device *usb_dev,struct usb_hcd *hcd);
extern struct otg_transceiver *FOTG2XX_get_otg_transceiver_1(void);
#if defined  (CONFIG_USB_SL2312_1) || defined (CONFIG_USB_SL2312_1_MODULE)
#define DRIVER_VERSION "2005-May-02"//Faraday-EHCI(FOTG2XX)
#define DRIVER_AUTHOR "Faraday-SW"//Faraday-EHCI(FOTG2XX)
#define DRIVER_DESC "USB 2.0 'Enhanced' Host Controller (EHCI) Driver for Faraday OTG"//Faraday-EHCI(FOTG2XX)
#endif
#define CPE_HOST20_BASE  SL2312_USB1_BASE
#define IRQ_USB_HOST20   IRQ_USB1

#undef EHCI_VERBOSE_DEBUG
#undef EHCI_URB_TRACE

#ifdef DEBUG
#define EHCI_STATS
#endif

/* magic numbers that can affect system performance */
#define	EHCI_TUNE_CERR		3	/* 0-3 qtd retries; 0 == don't stop */
#define	EHCI_TUNE_RL_HS		4	/* nak throttle; see 4.9 */
#define	EHCI_TUNE_RL_TT		0
#define	EHCI_TUNE_MULT_HS	1	/* 1-3 transactions/uframe; 4.10.3 */
#define	EHCI_TUNE_MULT_TT	1
#define	EHCI_TUNE_FLS		2	/* (small) 256 frame schedule */

#define EHCI_IAA_JIFFIES	(HZ/100)	/* arbitrary; ~10 msec */
#define EHCI_IO_JIFFIES		(HZ/10)		/* io watchdog > irq_thresh */
#define EHCI_ASYNC_JIFFIES	(HZ/20)		/* async idle timeout */
#define EHCI_SHRINK_JIFFIES	(HZ/200)	/* async qh unlink delay */

/* Initial IRQ latency:  faster than hw default */
static int log2_irq_thresh = 0;		// 0 to 6
module_param (log2_irq_thresh, int, S_IRUGO);
MODULE_PARM_DESC (log2_irq_thresh, "log2 IRQ latency, 1-64 microframes");

/* initial park setting:  slower than hw default */
static unsigned park = 0;
module_param (park, uint, S_IRUGO);
MODULE_PARM_DESC (park, "park setting; 1-3 back-to-back async packets");

#define	INTR_MASK (STS_IAA | STS_FATAL | STS_PCD | STS_ERR | STS_INT)

/*-------------------------------------------------------------------------*/

#include "ehci_FEHCI.h"
#include "ehci-dbg.c"
#include <asm/arch/sl2312.h>


//static const char FOTG200_BusName[]={'A','H','B','-','B','U','S',0x00};
//static const char FOTG200_product_desc[]={'F','-','E','H','C','I',0x00};
//static const char FUSBH200_BusName[]={'A','H','B','-','B','U','S',0x00};
//static const char FUSBH200_product_desc[]={'F','-','E','H','C','I',0x00};
//struct usb_hcd		*ghcd_FOTG2XX_1;//Faraday-EHCI(FOTG2XX/FUSBH200)
//struct usb_hcd		*ghcd_FUSBH200_1;//Faraday-EHCI(FOTG2XX/FUSBH200)

//Start;;Faraday-EHCI(FOTG2XX)       
//================= Faraday EHCI Function Call ============================//


//=============================================================================
// Name:FEHCI_ReadSpeed()
// Description:
// Input:NA
// Output:  
//=============================================================================
int FEHCI_ReadSpeed_1 (void)//0=>None 1=>Full Speed 2=>High Speed
{
 int     base;//Bruce;;
 int     val1;//Bruce;;         
     base=IO_ADDRESS((CPE_HOST20_BASE+0x80)); 
     val1=readl(base);

       
     if (((val1>>22)&0x03) == 2 )
        { 
         return 2;
        }
     else if (((val1>>22)&0x03) == 1 )
        {
         return 1;               
        }
     else 
       {
         return 0; 		       
       }
 }

static int FOTG2XX_Force_Speed_1( //0=>None 1=>Full Speed 2=>High Speed
	int		iSpeed
) 
{
   int base;
   int val2;

   base=IO_ADDRESS((CPE_HOST20_BASE+0x80)); 
   val2 = inl(base);  
   switch (iSpeed)
   {
      case 0://Clear All
         val2&=~(1<<12);//Clear Bit12(Clear ForceFullSpeed Bit)
         val2&=~(1<<14);//Clear Bit14(Clear ForceHighSpeed Bit)
         break;
      case 1://Force Full Speed
         val2|=(1<<12);//Clear Bit12(Set ForceFullSpeed Bit)
         val2&=~(1<<14);//Clear Bit14(Clear ForceHighSpeed Bit)
         break;
      case 2://Force High Speed
         val2&=~(1<<12);//Clear Bit12(Clear ForceFullSpeed Bit)
         val2|=(1<<14);//Clear Bit14(Set ForceHighSpeed Bit)
         break;
      default:
         break;
   }
        
   outl(val2,base);  	        
//   DO_PRINT("### Force Speed Finish Add=0x%x Data=0x%x\n",base,val);
   return 0;
}

//=============================================================================
// FEHCI_ForceSpeed()
// Description:
// Input:NA
// Output: int 0 => ok
//=============================================================================
static int FEHCI_ForceSpeed_1(int iSpeed)  
{
  FOTG2XX_Force_Speed_1(iSpeed); 
   return 0;
}

//End;;Faraday-EHCI(FOTG2XX)

/*-------------------------------------------------------------------------*/

/*
 * handshake - spin reading hc until handshake completes or fails
 * @ptr: address of hc register to be read
 * @mask: bits to look at in result of read
 * @done: value of those bits when handshake succeeds
 * @usec: timeout in microseconds
 *
 * Returns negative errno, or zero on success
 *
 * Success happens when the "mask" bits have the specified value (hardware
 * handshake done).  There are two failure modes:  "usec" have passed (major
 * hardware flakeout), or the register reads as all-ones (hardware removed).
 *
 * That last failure should_only happen in cases like physical cardbus eject
 * before driver shutdown. But it also seems to be caused by bugs in cardbus
 * bridge shutdown:  shutting down the bridge before the devices using it.
 */
static int handshake (void __iomem *ptr, u32 mask, u32 done, int usec)
{
	u32	result;

	do {
		result = readl (ptr);
		if (result == ~(u32)0)		/* card removed */
			return -ENODEV;
		result &= mask;
		if (result == done)
			return 0;
		udelay (1);
		usec--;
	} while (usec > 0);
	return -ETIMEDOUT;
}

/* force HC to halt state from unknown (EHCI spec section 2.3) */
static int ehci_halt (struct ehci_hcd *ehci)
{
	u32	temp = readl (&ehci->regs->status);

	/* disable any irqs left enabled by previous code */
	writel (0, &ehci->regs->intr_enable);

	if ((temp & STS_HALT) != 0)
		return 0;

	temp = readl (&ehci->regs->command);
	temp &= ~CMD_RUN;
	writel (temp, &ehci->regs->command);
	return handshake (&ehci->regs->status, STS_HALT, STS_HALT, 16 * 125);
}

/* put TDI/ARC silicon into EHCI mode */
static void tdi_reset (struct ehci_hcd *ehci)
{
	u32 __iomem	*reg_ptr;
	u32		tmp;

	reg_ptr = (u32 __iomem *)(((u8 __iomem *)ehci->regs) + 0x68);
	tmp = readl (reg_ptr);
	tmp |= 0x3;
	writel (tmp, reg_ptr);
}

/* reset a non-running (STS_HALT == 1) controller */
static int ehci_reset (struct ehci_hcd *ehci)
{
	int	retval;
	u32	command = readl (&ehci->regs->command);

	command |= CMD_RESET;
//	printk("reset", command);
	writel (command, &ehci->regs->command);
	ehci->hcd.state = HC_STATE_HALT;
	ehci->next_statechange = jiffies;
	retval = handshake (&ehci->regs->command, CMD_RESET, 0, 250 * 1000);

	if (retval)
		return retval;

	if (ehci_is_TDI(ehci))
		tdi_reset (ehci);

	return retval;
}

/* idle the controller (from running) */
static void ehci_quiesce (struct ehci_hcd *ehci)
{
	u32	temp;

#ifdef DEBUG
	if (!HC_IS_RUNNING (ehci->hcd.state))
		BUG ();
#endif

	/* wait for any schedule enables/disables to take effect */
	temp = readl (&ehci->regs->command) << 10;
	temp &= STS_ASS | STS_PSS;
	if (handshake (&ehci->regs->status, STS_ASS | STS_PSS,
				temp, 16 * 125) != 0) {
		ehci->hcd.state = HC_STATE_HALT;
		return;
	}

	/* then disable anything that's still active */
	temp = readl (&ehci->regs->command);
	temp &= ~(CMD_ASE | CMD_IAAD | CMD_PSE);
	writel (temp, &ehci->regs->command);

	/* hardware can take 16 microframes to turn off ... */
	if (handshake (&ehci->regs->status, STS_ASS | STS_PSS,
				0, 16 * 125) != 0) {
		ehci->hcd.state = HC_STATE_HALT;
		return;
	}
}

/*-------------------------------------------------------------------------*/

static void ehci_work(struct ehci_hcd *ehci, struct pt_regs *regs);

#include "ehci-hub-FOTG2XX-1.c"
#include "ehci-mem.c"
#include "ehci-q-FEHCI.c"
#include "ehci-sched-FEHCI.c"

//#include "ehci-hub.c"
//#include "ehci-mem.c"
//#include "ehci-q.c"
//#include "ehci-sched.c"

/*-------------------------------------------------------------------------*/

static void ehci_watchdog_1 (unsigned long param)
{
	struct ehci_hcd		*ehci = (struct ehci_hcd *) param;
	unsigned long		flags;

	spin_lock_irqsave (&ehci->lock, flags);

	/* lost IAA irqs wedge things badly; seen with a vt8235 */
	if (ehci->reclaim) {
		u32		status = readl (&ehci->regs->status);

		if (status & STS_IAA) {
			ehci_vdbg (ehci, "lost IAA\n");
			COUNT (ehci->stats.lost_iaa);
			writel (STS_IAA, &ehci->regs->status);
			ehci->reclaim_ready = 1;
		}
	}

 	/* stop async processing after it's idled a bit */
	if (test_bit (TIMER_ASYNC_OFF, &ehci->actions))
 		start_unlink_async (ehci, ehci->async);

	/* ehci could run by timer, without IRQs ... */
	ehci_work (ehci, NULL);

	spin_unlock_irqrestore (&ehci->lock, flags);
}

/* Reboot notifiers kick in for silicon on any bus (not just pci, etc).
 * This forcibly disables dma and IRQs, helping kexec and other cases
 * where the next system software may expect clean state.
 */
static int
ehci_reboot (struct notifier_block *self, unsigned long code, void *null)
{
	struct ehci_hcd		*ehci;

	ehci = container_of (self, struct ehci_hcd, reboot_notifier);
	(void) ehci_halt (ehci);
#if !defined  (CONFIG_USB_SL2312_1) && !defined (CONFIG_USB_SL2312_1_MODULE)	
	/* make BIOS/etc use companion controller during reboot */
	writel (0, &ehci->regs->configured_flag);
#endif
	return 0;
}

static void ehci_port_power (struct ehci_hcd *ehci, int is_on)
{
	unsigned port;

	if (!HCS_PPC (ehci->hcs_params))
		return;

	printk("...power%s ports...\n", is_on ? "up" : "down");
	for (port = HCS_N_PORTS (ehci->hcs_params); port > 0; )
		(void) ehci_hub_control_1(&ehci->hcd,
				is_on ? SetPortFeature : ClearPortFeature,
				USB_PORT_FEAT_POWER,
				port--, NULL, 0);
	msleep(20);
}

/*-------------------------------------------------------------------------*/

/*
 * ehci_work is called from some interrupts, timers, and so on.
 * it calls driver completion functions, after dropping ehci->lock.
 */
static void ehci_work (struct ehci_hcd *ehci, struct pt_regs *regs)
{
	timer_action_done (ehci, TIMER_IO_WATCHDOG);
	if (ehci->reclaim_ready)
		end_unlink_async (ehci, regs);

	/* another CPU may drop ehci->lock during a schedule scan while
	 * it reports urb completions.  this flag guards against bogus
	 * attempts at re-entrant schedule scanning.
	 */
	if (ehci->scanning)
		return;
	ehci->scanning = 1;
	scan_async (ehci, regs);
	if (ehci->next_uframe != -1)
		scan_periodic (ehci, regs);
	ehci->scanning = 0;

	/* the IO watchdog guards against hardware or driver bugs that
	 * misplace IRQs, and should let us run completely without IRQs.
	 * such lossage has been observed on both VT6202 and VT8235.
	 */
	if (HC_IS_RUNNING (ehci->hcd.state) &&
			(ehci->async->qh_next.ptr != NULL ||
			 ehci->periodic_sched != 0))
		timer_action (ehci, TIMER_IO_WATCHDOG);
}

static void ehci_stop_1 (struct usb_hcd *hcd)
{
	struct ehci_hcd		*ehci = hcd_to_ehci (hcd);

	printk("stop\n");

	/* Turn off port power on all root hub ports. */
	ehci_port_power (ehci, 0);

	/* no more interrupts ... */
	del_timer_sync (&ehci->watchdog);

	spin_lock_irq(&ehci->lock);
	if (HC_IS_RUNNING (hcd->state))
		ehci_quiesce (ehci);

	ehci_reset (ehci);
	writel (0, &ehci->regs->intr_enable);
	spin_unlock_irq(&ehci->lock);

	/* let companion controllers work when we aren't */
#if !defined  (CONFIG_USB_SL2312_1) && !defined (CONFIG_USB_SL2312_1_MODULE)
	writel (0, &ehci->regs->configured_flag);
#endif
	unregister_reboot_notifier (&ehci->reboot_notifier);

	remove_debug_files (ehci);

	/* root hub is shut down separately (first, when possible) */
	spin_lock_irq (&ehci->lock);
	if (ehci->async)
		ehci_work (ehci, NULL);
	spin_unlock_irq (&ehci->lock);
	ehci_mem_cleanup (ehci);

#ifdef	EHCI_STATS
	printk("irq normal %ld err %ld reclaim %ld (lost %ld)\n",
		ehci->stats.normal, ehci->stats.error, ehci->stats.reclaim,
		ehci->stats.lost_iaa);
	printk("complete %ld unlink %ld\n",
		ehci->stats.complete, ehci->stats.unlink);
#endif

	printk("ehci_stop_1 completed %x \n", readl (&ehci->regs->status));
}

/* one-time init, only for memory state */
static int ehci_init(struct usb_hcd *hcd)
{
	struct ehci_hcd		*ehci = hcd_to_ehci(hcd);
	u32			temp;
	int			retval;
	u32			hcc_params;
        ehci->caps = (struct ehci_caps *) hcd->regs;  //stone 2.6.15
	ehci->regs = (struct ehci_regs *) (hcd->regs + ehci->caps->length);
	printk("ehci->caps->length %x, ehci->regs %d \n",ehci->caps->length,ehci->regs);

	spin_lock_init(&ehci->lock);

	init_timer(&ehci->watchdog);
	ehci->watchdog.function = ehci_watchdog_1;
	ehci->watchdog.data = (unsigned long) ehci;

	/*
	 * hw default: 1K periodic list heads, one per frame.
	 * periodic_size can shrink by USBCMD update if hcc_params allows.
	 */
	ehci->periodic_size = DEFAULT_I_TDPS;
	if ((retval = ehci_mem_init(ehci, GFP_KERNEL)) < 0)
		return retval;

	/* controllers may cache some of the periodic schedule ... */
	hcc_params = readl(&ehci->caps->hcc_params);
	if (HCC_ISOC_CACHE(hcc_params)) 	// full frame cache
		ehci->i_thresh = 8;
	else					// N microframes cached
		ehci->i_thresh = 2 + HCC_ISOC_THRES(hcc_params);

	ehci->reclaim = NULL;
	ehci->reclaim_ready = 0;
	ehci->next_uframe = -1;

	/*
	 * dedicate a qh for the async ring head, since we couldn't unlink
	 * a 'real' qh without stopping the async schedule [4.8].  use it
	 * as the 'reclamation list head' too.
	 * its dummy is used in hw_alt_next of many tds, to prevent the qh
	 * from automatically advancing to the next td after short reads.
	 */
	ehci->async->qh_next.qh = NULL;
	ehci->async->hw_next = QH_NEXT(ehci->async->qh_dma);
	ehci->async->hw_info1 = cpu_to_le32(QH_HEAD);
	ehci->async->hw_token = cpu_to_le32(QTD_STS_HALT);
	ehci->async->hw_qtd_next = EHCI_LIST_END;
	ehci->async->qh_state = QH_STATE_LINKED;
	ehci->async->hw_alt_next = QTD_NEXT(ehci->async->dummy->qtd_dma);

	/* clear interrupt enables, set irq latency */
	if (log2_irq_thresh < 0 || log2_irq_thresh > 6)
		log2_irq_thresh = 0;
	temp = 1 << (16 + log2_irq_thresh);
	if (HCC_CANPARK(hcc_params)) {
		/* HW default park == 3, on hardware that supports it (like
		 * NVidia and ALI silicon), maximizes throughput on the async
		 * schedule by avoiding QH fetches between transfers.
		 *
		 * With fast usb storage devices and NForce2, "park" seems to
		 * make problems:  throughput reduction (!), data errors...
		 */
		if (park) {
			park = min(park, (unsigned) 3);
			temp |= CMD_PARK;
			temp |= park << 8;
		}
		printk("park %d\n", park);
	}
	if (HCC_PGM_FRAMELISTLEN(hcc_params)) {
		/* periodic schedule size can be smaller than default */
		temp &= ~(3 << 2);
		temp |= (EHCI_TUNE_FLS << 2);
		switch (EHCI_TUNE_FLS) {
		case 0: ehci->periodic_size = 1024; break;
		case 1: ehci->periodic_size = 512; break;
		case 2: ehci->periodic_size = 256; break;
		default:	BUG();
		}
	}
	ehci->command = temp;

	ehci->reboot_notifier.notifier_call = ehci_reboot;
	register_reboot_notifier(&ehci->reboot_notifier);

	return 0;
}

/* start HC running; it's halted, ehci_init() has been run (once) */
static int ehci_run (struct usb_hcd *hcd)
{
	struct ehci_hcd		*ehci = hcd_to_ehci (hcd);
	int			retval;
	u32			temp;
	u32			hcc_params;

	/* EHCI spec section 4.1 */
	if ((retval = ehci_reset(ehci)) != 0) {
		unregister_reboot_notifier(&ehci->reboot_notifier);
		ehci_mem_cleanup(ehci);
		return retval;
	}
	writel(ehci->periodic_dma, &ehci->regs->frame_list);
	writel((u32)ehci->async->qh_dma, &ehci->regs->async_next);

	/*
	 * hcc_params controls whether ehci->regs->segment must (!!!)
	 * be used; it constrains QH/ITD/SITD and QTD locations.
	 * pci_pool consistent memory always uses segment zero.
	 * streaming mappings for I/O buffers, like pci_map_single(),
	 * can return segments above 4GB, if the device allows.
	 *
	 * NOTE:  the dma mask is visible through dma_supported(), so
	 * drivers can pass this info along ... like NETIF_F_HIGHDMA,
	 * Scsi_Host.highmem_io, and so forth.  It's readonly to all
	 * host side drivers though.
	 */
	hcc_params = readl(&ehci->caps->hcc_params);
	if (HCC_64BIT_ADDR(hcc_params)) {
#if !defined  (CONFIG_USB_SL2312_1) && !defined (CONFIG_USB_SL2312_1_MODULE)
		writel(0, &ehci->regs->segment);
#endif
#if 0
// this is deeply broken on almost all architectures
		if (!dma_set_mask(hcd->self.controller, DMA_64BIT_MASK))
			ehci_info(ehci, "enabled 64bit DMA\n");
#endif
	}


	// Philips, Intel, and maybe others need CMD_RUN before the
	// root hub will detect new devices (why?); NEC doesn't
	ehci->command &= ~(CMD_LRESET|CMD_IAAD|CMD_PSE|CMD_ASE|CMD_RESET);
	ehci->command |= CMD_RUN;
	writel (ehci->command, &ehci->regs->command);
	printk("init %x \n", ehci->command);

	/*
	 * Start, enabling full USB 2.0 functionality ... usb 1.1 devices
	 * are explicitly handed to companion controller(s), so no TT is
	 * involved with the root hub.  (Except where one is integrated,
	 * and there's no companion controller unless maybe for USB OTG.)
	 */
	hcd->state = HC_STATE_RUNNING;
#if !defined  (CONFIG_USB_SL2312_1) && !defined (CONFIG_USB_SL2312_1_MODULE)
	writel (FLAG_CF, &ehci->regs->configured_flag);
#endif
	readl (&ehci->regs->command);	/* unblock posted writes */
#if !defined  (CONFIG_USB_SL2312_1) && !defined (CONFIG_USB_SL2312_1_MODULE)
	temp = HC_VERSION(readl (&ehci->caps->hc_capbase));
	ehci_info (ehci,
		"USB %x.%x started, EHCI %x.%02x, driver %s\n",
		((ehci->sbrn & 0xf0)>>4), (ehci->sbrn & 0x0f),
		temp >> 8, temp & 0xff, DRIVER_VERSION);
#else 
        temp = readl(&ehci->caps->hci_version);
        info ("USB support enabled, EHCI rev %x.%2x",temp >> 8,temp & 0xff);
#endif
	writel (INTR_MASK, &ehci->regs->intr_enable); /* Turn On Interrupts */

	/* GRR this is run-once init(), being done every time the HC starts.
	 * So long as they're part of class devices, we can't do it init()
	 * since the class device isn't created that early.
	 */
	create_debug_files(ehci);

	//*** Connect Host to OTG //For OTG
//Start;;Faraday-EHCI(FOTG2XX)
       //Init otg port 
//       	ehci->hcd.bus->otg_port = 1;//Faraday OTG dafault port=1
       	ehci->hcd.self.otg_port = 1;//Faraday OTG dafault port=1
 
		ehci->transceiver = FOTG2XX_get_otg_transceiver_1();
		if (ehci->transceiver) {
//			int	status = otg_set_host(ehci->transceiver,
//						ehci->hcd.bus);
			int	status = otg_set_host(ehci->transceiver,
						&ehci->hcd.self);
//			DBG_HOST_EHCI("init %s transceiver, status %d\n",
//					ehci->transceiver->label, status);
                        printk("ehci otg_set_host status %x \n",status);
			if (status) {
				if (ehci->transceiver)
					printk("??? HCD=>otg_set_host fail ...\n");
				return status;
			}
		} else {
			printk("can't find transceiver\n");
			return -ENODEV;
		}


//End;;Faraday-EHCI(FOTG2XX)

	return 0;
}

/*-------------------------------------------------------------------------*/

static irqreturn_t ehci_irq_1 (struct usb_hcd *hcd, struct pt_regs *regs)
{
	struct ehci_hcd		*ehci = hcd_to_ehci (hcd);
	u32			status;
	int			bh;

	spin_lock (&ehci->lock);
       
	status = readl (&ehci->regs->status);
//         printk("ehci_irq_1 ehci->regs %x status %x\n",ehci->regs,status);
	/* e.g. cardbus physical eject */
	if (status == ~(u32) 0) {
		printk("device removed\n");
		goto dead;
	}

	status &= INTR_MASK;
	if (!status) {			/* irq sharing? */
		spin_unlock(&ehci->lock);
		return IRQ_NONE;
	}

	/* clear (just) interrupts */
	writel (status, &ehci->regs->status);
	readl (&ehci->regs->command);	/* unblock posted write */
	bh = 0;

#ifdef	EHCI_VERBOSE_DEBUG
	/* unrequested/ignored: Frame List Rollover */
	printk("irq", status);
#endif

	/* INT, ERR, and IAA interrupt rates can be throttled */

	/* normal [4.15.1.2] or error [4.15.1.1] completion */
	if (likely ((status & (STS_INT|STS_ERR)) != 0)) {
		if (likely ((status & STS_ERR) == 0))
			COUNT (ehci->stats.normal);
		else
			COUNT (ehci->stats.error);
		bh = 1;
	}

	/* complete the unlinking of some qh [4.15.2.3] */
	if (status & STS_IAA) {
		COUNT (ehci->stats.reclaim);
		ehci->reclaim_ready = 1;
		bh = 1;
	}

	/* remote wakeup [4.3.1] */
	if ((status & STS_PCD) && hcd->remote_wakeup) {
		unsigned	i = HCS_N_PORTS (ehci->hcs_params);

		/* resume root hub? */
		status = readl (&ehci->regs->command);
		if (!(status & CMD_RUN))
			writel (status | CMD_RUN, &ehci->regs->command);

		while (i--) {
			status = readl (&ehci->regs->port_status [i]);
#if !defined  (CONFIG_USB_SL2312_1) && !defined (CONFIG_USB_SL2312_1_MODULE)
			if (status & PORT_OWNER)
				continue;
#endif
			if (!(status & PORT_RESUME)
					|| ehci->reset_done [i] != 0)
				continue;

			/* start 20 msec resume signaling from this port,
			 * and make khubd collect PORT_STAT_C_SUSPEND to
			 * stop that signaling.
			 */
			ehci->reset_done [i] = jiffies + msecs_to_jiffies (20);
			mod_timer (&ehci->hcd.rh_timer,
					ehci->reset_done [i] + 1);
			printk("port %d remote wakeup\n", i + 1);
			usb_hcd_resume_root_hub(hcd);
		}
	}

	/* PCI errors [4.15.2.4] */
	if (unlikely ((status & STS_FATAL) != 0)) {
		/* bogus "fatal" IRQs appear on some chips... why?  */
		status = readl (&ehci->regs->status);
		printk("fatal %x \n", readl (&ehci->regs->command));
		printk("fatal %x \n", status);
		if (status & STS_HALT) {
			printk("fatal error\n");
dead:
			ehci_reset (ehci);
#if !defined  (CONFIG_USB_SL2312_1) && !defined (CONFIG_USB_SL2312_1_MODULE)
			writel (0, &ehci->regs->configured_flag);
#endif
			/* generic layer kills/unlinks all urbs, then
			 * uses ehci_stop_1 to clean up the rest
			 */
			bh = 1;
		}
	}

	if (bh)
		ehci_work (ehci, regs);
	spin_unlock (&ehci->lock);
	return IRQ_HANDLED;
}

/*-------------------------------------------------------------------------*/

/*
 * non-error returns are a promise to giveback() the urb later
 * we drop ownership so next owner (or urb unlink) can get it
 *
 * urb + dev is in hcd.self.controller.urb_list
 * we're queueing TDs onto software and hardware lists
 *
 * hcd-specific init for hcpriv hasn't been done yet
 *
 * NOTE:  control, bulk, and interrupt share the same code to append TDs
 * to a (possibly active) QH, and the same QH scanning code.
 */
static int ehci_urb_enqueue_1 (
	struct usb_hcd	*hcd,
	struct usb_host_endpoint *ep,
	struct urb	*urb,
	gfp_t		mem_flags
) {
	struct ehci_hcd		*ehci = hcd_to_ehci (hcd);
	struct list_head	qtd_list;

	INIT_LIST_HEAD (&qtd_list);

	switch (usb_pipetype (urb->pipe)) {
	// case PIPE_CONTROL:
	// case PIPE_BULK:
	default:
		if (!qh_urb_transaction (ehci, urb, &qtd_list, mem_flags))
		   {
		   	printk("***ehci_urb_enqueue_1 %x \n",qh_urb_transaction (ehci, urb, &qtd_list, mem_flags));
			return -ENOMEM;
		    }
//		printk("***ehci_urb_enqueue_1 1 %x \n",submit_async (ehci, ep, urb, &qtd_list, mem_flags));    //2.6.15 cant not open !!!!
		return submit_async (ehci, ep, urb, &qtd_list, mem_flags);

	case PIPE_INTERRUPT:
		if (!qh_urb_transaction (ehci, urb, &qtd_list, mem_flags))
			return -ENOMEM;
		return intr_submit (ehci, ep, urb, &qtd_list, mem_flags);

	case PIPE_ISOCHRONOUS:
		if (urb->dev->speed == USB_SPEED_HIGH)
			return itd_submit (ehci, urb, mem_flags);
		else
			return sitd_submit (ehci, urb, mem_flags);
	}
}

static void unlink_async (struct ehci_hcd *ehci, struct ehci_qh *qh)
{
	/* if we need to use IAA and it's busy, defer */
	if (qh->qh_state == QH_STATE_LINKED
			&& ehci->reclaim
			&& HC_IS_RUNNING (ehci->hcd.state)) {
		struct ehci_qh		*last;

		for (last = ehci->reclaim;
				last->reclaim;
				last = last->reclaim)
			continue;
		qh->qh_state = QH_STATE_UNLINK_WAIT;
		last->reclaim = qh;

	/* bypass IAA if the hc can't care */
	} else if (!HC_IS_RUNNING (ehci->hcd.state) && ehci->reclaim)
		end_unlink_async (ehci, NULL);

	/* something else might have unlinked the qh by now */
	if (qh->qh_state == QH_STATE_LINKED)
		start_unlink_async (ehci, qh);
	if ( (readl (&ehci->regs->port_status[1])&PORT_CONNECT) == 0 ){
	   printk("unlink_async ... reclaim: %p\n",ehci->reclaim);
	   end_unlink_async (ehci, NULL);
	}
	else{
	   printk("Host ==> Device No Response ....\n");
	   end_unlink_async (ehci, NULL);
	   //printk("No Cover running:%x reclaim:%p %p st:%x\n",HC_IS_RUNNING (ehci_to_hcd(ehci)->state),ehci->reclaim,qh,qh->qh_state);
	}	
}

/* remove from hardware lists
 * completions normally happen asynchronously
 */

static int ehci_urb_dequeue_1 (struct usb_hcd *hcd, struct urb *urb)
{
	struct ehci_hcd		*ehci = hcd_to_ehci (hcd);
	struct ehci_qh		*qh;
	unsigned long		flags;

	spin_lock_irqsave (&ehci->lock, flags);
	switch (usb_pipetype (urb->pipe)) {
	// case PIPE_CONTROL:
	// case PIPE_BULK:
	default:
		qh = (struct ehci_qh *) urb->hcpriv;
		if (!qh)
			break;
		unlink_async (ehci, qh);
		break;

	case PIPE_INTERRUPT:
		qh = (struct ehci_qh *) urb->hcpriv;
		if (!qh)
			break;
		switch (qh->qh_state) {
		case QH_STATE_LINKED:
			intr_deschedule (ehci, qh);
			/* FALL THROUGH */
		case QH_STATE_IDLE:
			qh_completions (ehci, qh, NULL);
			break;
		default:
			printk("bogus qh %p state %d\n",
					qh, qh->qh_state);
			goto done;
		}

		/* reschedule QH iff another request is queued */
		if (!list_empty (&qh->qtd_list)
				&& HC_IS_RUNNING (hcd->state)) {
			int status;

			status = qh_schedule (ehci, qh);
			spin_unlock_irqrestore (&ehci->lock, flags);

			if (status != 0) {
				// shouldn't happen often, but ...
				// FIXME kill those tds' urbs
				err ("can't reschedule qh %p, err %d",
					qh, status);
			}
			return status;
		}
		break;

	case PIPE_ISOCHRONOUS:
		// itd or sitd ...

		// wait till next completion, do it then.
		// completion irqs can wait up to 1024 msec,
		break;
	}
done:
	spin_unlock_irqrestore (&ehci->lock, flags);
	return 0;
}

/*-------------------------------------------------------------------------*/

// bulk qh holds the data toggle

static void
ehci_endpoint_disable_1 (struct usb_hcd *hcd, struct usb_host_endpoint *ep)
{
	struct ehci_hcd		*ehci = hcd_to_ehci (hcd);
	unsigned long		flags;
	struct ehci_qh		*qh, *tmp;
	int i=0;

	/* ASSERT:  any requests/urbs are being unlinked */
	/* ASSERT:  nobody can be submitting urbs for this any more */

rescan:
	spin_lock_irqsave (&ehci->lock, flags);
	qh = ep->hcpriv;
	if (!qh)
		goto done;

	/* endpoints can be iso streams.  for now, we don't
	 * accelerate iso completions ... so spin a while.
	 */
	if (qh->hw_info1 == 0) {
		ehci_vdbg (ehci, "iso delay\n");
		goto idle_timeout;
	}

	if (!HC_IS_RUNNING (hcd->state))
		qh->qh_state = QH_STATE_IDLE;
	switch (qh->qh_state) {
	case QH_STATE_LINKED:
		for (tmp = ehci->async->qh_next.qh;
				tmp && tmp != qh;
				tmp = tmp->qh_next.qh)
			continue;
		/* periodic qh self-unlinks on empty */
		if (!tmp)
			goto nogood;
		unlink_async (ehci, qh);
		/* FALL THROUGH */
	case QH_STATE_UNLINK:		/* wait for hw to finish? */
idle_timeout:
		spin_unlock_irqrestore (&ehci->lock, flags);
		schedule_timeout_uninterruptible(10);
#if defined  (CONFIG_USB_SL2312_1) || defined (CONFIG_USB_SL2312_1_MODULE)
//                if (hcd->rsrc_start == 0x68000000) {
                   unlink_async (ehci, qh);
                   printk("i_1 %x\n",i);  	
                   i++;
		   //printk("ehci_endpoint_disable ==> Warning wait for hardware may cause deadlock\n");
//		   }
#endif		
		goto rescan;
	case QH_STATE_IDLE:		/* fully unlinked */
		if (list_empty (&qh->qtd_list)) {
			qh_put (qh);
			break;
		}
		/* else FALL THROUGH */
	default:
nogood:
		/* caller was supposed to have unlinked any requests;
		 * that's not our job.  just leak this memory.
		 */
		printk("qh %p (#%02x) state %d%s\n",
			qh, ep->desc.bEndpointAddress, qh->qh_state,
			list_empty (&qh->qtd_list) ? "" : "(has tds)");
		break;
	}
	ep->hcpriv = NULL;
done:
	spin_unlock_irqrestore (&ehci->lock, flags);
	return;
}

static int ehci_get_frame_1 (struct usb_hcd *hcd)
{
	struct ehci_hcd		*ehci = hcd_to_ehci (hcd);
	return (readl (&ehci->regs->frame_index) >> 3) % ehci->periodic_size;
}


/*-------------------------------------------------------------------------*/

#define DRIVER_INFO DRIVER_VERSION " " DRIVER_DESC

MODULE_DESCRIPTION (DRIVER_INFO);
MODULE_AUTHOR (DRIVER_AUTHOR);
MODULE_LICENSE ("GPL");

#if !defined  (CONFIG_USB_SL2312_1) && !defined (CONFIG_USB_SL2312_1_MODULE)
#ifdef CONFIG_PCI
#include "ehci-pci.c"
#endif

#if !defined(CONFIG_PCI)
#error "missing bus glue for ehci-hcd"
#endif
#endif

//stone 2.6.15 
//Start;;Faraday-EHCI(FOTG2XX)
static int ehci_hc_reset_1 (struct usb_hcd *hcd)
{
	struct ehci_hcd		*ehci = hcd_to_ehci (hcd);
	u32			temp;
	unsigned		count = 256/4;

	spin_lock_init (&ehci->lock);
#if !defined  (CONFIG_USB_SL2312_1) && !defined (CONFIG_USB_SL2312_1_MODULE)
	ehci->caps = hcd->regs;
	ehci->regs = hcd->regs + HC_LENGTH (readl (&ehci->caps->hc_capbase));
#else
	ehci->caps = (struct ehci_caps *) hcd->regs;
	ehci->regs = (struct ehci_regs *) (hcd->regs + ehci->caps->length);
//	printk("ehci_hc_reset_1 \n");
#endif
	dbg_hcs_params (ehci, "reset");
	dbg_hcc_params (ehci, "reset");

#if !defined  (CONFIG_USB_SL2312_1) && !defined (CONFIG_USB_SL2312_1_MODULE)
#ifdef	CONFIG_PCI
	/* EHCI 0.96 and later may have "extended capabilities" */
	if (hcd->self.controller->bus == &pci_bus_type) {
		struct pci_dev	*pdev = to_pci_dev(ehci->hcd.self.controller);

		/* AMD8111 EHCI doesn't work, according to AMD errata */
		if ((pdev->vendor == PCI_VENDOR_ID_AMD)
				&& (pdev->device == 0x7463)) {
			ehci_info (ehci, "ignoring AMD8111 (errata)\n");
			return -EIO;
		}

		temp = HCC_EXT_CAPS (readl (&ehci->caps->hcc_params));
	} else
		temp = 0;
	while (temp && count--) {
		u32		cap;

		pci_read_config_dword (to_pci_dev(ehci->hcd.self.controller),
				temp, &cap);
		ehci_dbg (ehci, "capability %04x at %02x\n", cap, temp);
		switch (cap & 0xff) {
		case 1:			/* BIOS/SMM/... handoff */
			if (bios_handoff (ehci, temp, cap) != 0)
				return -EOPNOTSUPP;
			break;
		case 0:			/* illegal reserved capability */
			ehci_warn (ehci, "illegal capability!\n");
			cap = 0;
			/* FALLTHROUGH */
		default:		/* unknown */
			break;
		}
		temp = (cap >> 8) & 0xff;
	}
	if (!count) {
		ehci_err (ehci, "bogus capabilities ... PCI problems!\n");
		return -EIO;
	}
#endif
#endif
	/* cache this readonly data; minimize PCI reads */
	ehci->hcs_params = readl (&ehci->caps->hcs_params);

	/* at least the Genesys GL880S needs fixup here */
	temp = HCS_N_CC(ehci->hcs_params) * HCS_N_PCC(ehci->hcs_params);
	temp &= 0x0f;
	if (temp && HCS_N_PORTS(ehci->hcs_params) > temp) {
		temp |= (ehci->hcs_params & ~0xf);
		ehci->hcs_params = temp;
	}

	/* force HC to halt state */
	return ehci_halt (ehci);
}

static int ehci_start_1 (struct usb_hcd *hcd)
{
	struct ehci_hcd		*ehci = hcd_to_ehci (hcd);
	u32			temp;
	struct usb_device	*udev;
	struct usb_bus		*bus;
	int			retval;
	u32			hcc_params;
	u8                      sbrn = 0;
	int			first;

        ehci->caps = (struct ehci_caps *) hcd->regs;
	ehci->regs = (struct ehci_regs *) (hcd->regs + ehci->caps->length);
	printk("ehci->caps->length %x, hcd->regs %x , ehci->regs %x \n",ehci->caps->length,hcd->regs,ehci->regs);
	
	/* skip some things on restart paths */
	first = (ehci->watchdog.data == 0);
	if (first) {
		init_timer (&ehci->watchdog);
		ehci->watchdog.function = ehci_watchdog_1;
		ehci->watchdog.data = (unsigned long) ehci;
	}

	/*
	 * hw default: 1K periodic list heads, one per frame.
	 * periodic_size can shrink by USBCMD update if hcc_params allows.
	 */
	ehci->periodic_size = DEFAULT_I_TDPS;
	if (first && (retval = ehci_mem_init (ehci, GFP_KERNEL)) < 0)
		return retval;

	/* controllers may cache some of the periodic schedule ... */
	hcc_params = readl (&ehci->caps->hcc_params);
	ehci->hcs_params = readl (&ehci->caps->hcs_params);
	if (HCC_ISOC_CACHE (hcc_params)) 	// full frame cache
		ehci->i_thresh = 8;
	else					// N microframes cached
		ehci->i_thresh = 2 + HCC_ISOC_THRES (hcc_params);

	ehci->reclaim = NULL;
	ehci->reclaim_ready = 0;
	ehci->next_uframe = -1;

	/* controller state:  unknown --> reset */

	/* EHCI spec section 4.1 */
	if ((retval = ehci_reset (ehci)) != 0) {
		ehci_mem_cleanup (ehci);
		return retval;
	}
	writel (ehci->periodic_dma, &ehci->regs->frame_list);
#if !defined  (CONFIG_USB_SL2312_1) && !defined (CONFIG_USB_SL2312_1_MODULE)
#ifdef	CONFIG_PCI
	if (hcd->self.controller->bus == &pci_bus_type) {
		struct pci_dev		*pdev;
		u16			port_wake;

		pdev = to_pci_dev(hcd->self.controller);

		/* Serial Bus Release Number is at PCI 0x60 offset */
		pci_read_config_byte(pdev, 0x60, &sbrn);

		/* port wake capability, reported by boot firmware */
		pci_read_config_word(pdev, 0x62, &port_wake);
		hcd->can_wakeup = (port_wake & 1) != 0;

		/* help hc dma work well with cachelines */
		pci_set_mwi (pdev);

		/* chip-specific init */
		switch (pdev->vendor) {
		case PCI_VENDOR_ID_ARC:
			if (pdev->device == PCI_DEVICE_ID_ARC_EHCI)
				ehci->is_arc_rh_tt = 1;
			break;
		}

	}
#endif
#endif

	/*
	 * dedicate a qh for the async ring head, since we couldn't unlink
	 * a 'real' qh without stopping the async schedule [4.8].  use it
	 * as the 'reclamation list head' too.
	 * its dummy is used in hw_alt_next of many tds, to prevent the qh
	 * from automatically advancing to the next td after short reads.
	 */
	if (first) {
		ehci->async->qh_next.qh = NULL;
		ehci->async->hw_next = QH_NEXT (ehci->async->qh_dma);
		ehci->async->hw_info1 = cpu_to_le32 (QH_HEAD);
		ehci->async->hw_token = cpu_to_le32 (QTD_STS_HALT);
		ehci->async->hw_qtd_next = EHCI_LIST_END;
		ehci->async->qh_state = QH_STATE_LINKED;
		ehci->async->hw_alt_next = QTD_NEXT (ehci->async->dummy->qtd_dma);
	}
	writel ((u32)ehci->async->qh_dma, &ehci->regs->async_next);

	/*
	 * hcc_params controls whether ehci->regs->segment must (!!!)
	 * be used; it constrains QH/ITD/SITD and QTD locations.
	 * pci_pool consistent memory always uses segment zero.
	 * streaming mappings for I/O buffers, like pci_map_single(),
	 * can return segments above 4GB, if the device allows.
	 *
	 * NOTE:  the dma mask is visible through dma_supported(), so
	 * drivers can pass this info along ... like NETIF_F_HIGHDMA,
	 * Scsi_Host.highmem_io, and so forth.  It's readonly to all
	 * host side drivers though.
	 */
#if !defined  (CONFIG_USB_SL2312_1) && !defined (CONFIG_USB_SL2312_1_MODULE)
	if (HCC_64BIT_ADDR (hcc_params)) {
		writel (0, &ehci->regs->segment);
#if 0
// this is deeply broken on almost all architectures
		if (!pci_set_dma_mask (to_pci_dev(ehci->hcd.self.controller), 0xffffffffffffffffULL))
			ehci_info (ehci, "enabled 64bit PCI DMA\n");
#endif
	}
#endif
	/* clear interrupt enables, set irq latency */
	temp = readl (&ehci->regs->command) & 0x0fff;
	if (log2_irq_thresh < 0 || log2_irq_thresh > 6)
		log2_irq_thresh = 0;
	temp |= 1 << (16 + log2_irq_thresh);
	// if hc can park (ehci >= 0.96), default is 3 packets per async QH 
	if (HCC_PGM_FRAMELISTLEN (hcc_params)) {
		/* periodic schedule size can be smaller than default */
		temp &= ~(3 << 2);
		temp |= (EHCI_TUNE_FLS << 2);
		switch (EHCI_TUNE_FLS) {
		case 0: ehci->periodic_size = 1024; break;
		case 1: ehci->periodic_size = 512; break;
		case 2: ehci->periodic_size = 256; break;
		default:	BUG ();
		}
	}
	temp &= ~(CMD_IAAD | CMD_ASE | CMD_PSE),
	// Philips, Intel, and maybe others need CMD_RUN before the
	// root hub will detect new devices (why?); NEC doesn't
//	temp |= CMD_RUN; //Faraday OTG can not set in begin else port connect can not detect.
	writel (temp, &ehci->regs->command);
//	dbg_cmd (ehci, "init", temp);

	/* set async sleep time = 10 us ... ? */

	/* wire up the root hub */
	bus = hcd_to_bus (hcd);
	udev = first ? usb_alloc_dev (NULL, bus, 0) : bus->root_hub;
	if (!udev) {
done2:
		ehci_mem_cleanup (ehci);
		return -ENOMEM;
	}
	udev->speed = USB_SPEED_HIGH;
	udev->state = first ? USB_STATE_ATTACHED : USB_STATE_CONFIGURED;
        printk("udev->state %x \n",udev->state);
	/*
	 * Start, enabling full USB 2.0 functionality ... usb 1.1 devices
	 * are explicitly handed to companion controller(s), so no TT is
	 * involved with the root hub.  (Except where one is integrated,
	 * and there's no companion controller unless maybe for USB OTG.)
	 */
	if (first) {
		ehci->reboot_notifier.notifier_call = ehci_reboot;
		register_reboot_notifier (&ehci->reboot_notifier);
	}

	ehci->hcd.state = HC_STATE_RUNNING;
#if !defined  (CONFIG_USB_SL2312_1) && !defined (CONFIG_USB_SL2312_1_MODULE)
	writel (FLAG_CF, &ehci->regs->configured_flag);
#endif
	readl (&ehci->regs->command);	/* unblock posted write */
#if !defined  (CONFIG_USB_SL2312_1) && !defined (CONFIG_USB_SL2312_1_MODULE)
	temp = HC_VERSION(readl (&ehci->caps->hc_capbase));
#else
        temp = readl(&ehci->caps->hci_version);
#endif
#if !defined  (CONFIG_USB_SL2312_1) && !defined (CONFIG_USB_SL2312_1_MODULE)
	ehci_info (ehci,
		"USB %x.%x %s, EHCI %x.%02x, driver %s\n",
		((sbrn & 0xf0)>>4), (sbrn & 0x0f),
		first ? "initialized" : "restarted",
		temp >> 8, temp & 0xff, DRIVER_VERSION);
#else
      info ("USB support enabled, EHCI rev %x.%2x",temp >> 8,temp & 0xff);
#endif

	/*
	 * From here on, khubd concurrently accesses the root
	 * hub; drivers will be talking to enumerated devices.
	 * (On restart paths, khubd already knows about the root
	 * hub and could find work as soon as we wrote FLAG_CF.)
	 *
	 * Before this point the HC was idle/ready.  After, khubd
	 * and device drivers may start it running.
	 */
	if (first && hcd_register_root (udev, hcd) != 0) {
		if (hcd->state == HC_STATE_RUNNING)
			ehci_quiesce (ehci);
		ehci_reset (ehci);
		usb_put_dev (udev); 
		retval = -ENODEV;
		goto done2;
	}

//	writel (INTR_MASK, &ehci->regs->intr_enable); /* Turn On Interrupts */

	if (first)
		create_debug_files (ehci);
		
	//*** Connect Host to OTG //For OTG
//Start;;Faraday-EHCI(FOTG2XX)
       //Init otg port 
//       	ehci->hcd.bus->otg_port = 1;//Faraday OTG dafault port=1
       	ehci->hcd.self.otg_port = 1;//Faraday OTG dafault port=1
 
		ehci->transceiver = FOTG2XX_get_otg_transceiver_1();
		if (ehci->transceiver) {
//			int	status = otg_set_host(ehci->transceiver,
//						ehci->hcd.bus);
			int	status = otg_set_host(ehci->transceiver,
						&ehci->hcd.self);
//			DBG_HOST_EHCI("init %s transceiver, status %d\n",
//					ehci->transceiver->label, status);
                        printk("ehci otg_set_host status %x \n",status);
			if (status) {
				if (ehci->transceiver)
					printk("??? HCD=>otg_set_host fail ...\n");
				return status;
			}
		} else {
			printk("can't find transceiver\n");
			return -ENODEV;
		}


//End;;Faraday-EHCI(FOTG2XX)
//Stone add for module 
writel (INTR_MASK, &ehci->regs->intr_enable); /* Turn On Interrupts */


	return 0;
}

static void ehci_ready (struct ehci_hcd *ehci)
{ 
	u32	command;
//    DBG_HOST_EHCI("### >>> Enter ehci-hcd.c file --> ehci_ready function \n");


#ifdef DEBUG
	if (!HCD_IS_RUNNING (ehci->hcd.state))
		BUG ();
#endif



//Faraday-EHCI(FOTG2XX);;	while (!(readl (&ehci->regs->status) & (STS_ASS | STS_PSS)))
//Faraday-EHCI(FOTG2XX);;            udelay (100);



	command = readl (&ehci->regs->command);
	command &= ~(CMD_ASE | CMD_IAAD | CMD_PSE);
	writel (command, &ehci->regs->command);

	// hardware can take 16 microframes to turn off ...
	ehci->hcd.state = USB_STATE_READY;


	
}

static int ehci_disconnect_for_OTG_1 (struct usb_hcd *hcd, u32 state)
{
	struct ehci_hcd		*ehci = hcd_to_ehci (hcd);
	int			ports;
	int			i,iTemp;
      
//    DBG_HOST_EHCI("### >>> Enter ehci-hcd.c file --> ehci_disconnect_for_OTG_1 function \n");


	ports = HCS_N_PORTS (ehci->hcs_params);

	// FIXME:  This assumes what's probably a D3 level suspend...

	// FIXME:  usb wakeup events on this bus should resume the machine.
	// pci config register PORTWAKECAP controls which ports can do it;
	// bios may have initted the register...

	/* suspend each port, then stop the hc */
	for (i = 0; i < ports; i++) {
		int	temp = readl (&ehci->regs->port_status [i]);


    if (((temp & PORT_PE) == 0))
      continue;



dbg ("%s: suspend port %d", hcd->bus_name, i);
//Bruce;;04212005;;		temp |= PORT_SUSPEND;
//Bruce;;04212005;;		writel (temp, &ehci->regs->port_status [i]);
	}

	if (hcd->state == HC_STATE_RUNNING)
		ehci_ready (ehci);
	while (readl (&ehci->regs->status) & (STS_ASS | STS_PSS))
		udelay (100);
	writel (readl (&ehci->regs->command) & ~CMD_RUN, &ehci->regs->command);


#if !defined  (CONFIG_USB_SL2312_1) && !defined (CONFIG_USB_SL2312_1_MODULE)
//#if 0
	 iTemp = readl (&ehci->regs->port_status [0]);
	 if (iTemp&PORT_RESUME)
	    {
	    printk("TEMP===========> Detected the PORT_RESUME signal...\n");	
	    iTemp &= ~PORT_RESUME;	    	
 	    writel (iTemp, &ehci->regs->port_status [0]);	    
	    }

	
#endif	

#if defined  (CONFIG_USB_SL2312_1) || defined (CONFIG_USB_SL2312_1_MODULE)
//#if 1 
//Suspend the host;;
                iTemp = readl (&ehci->regs->port_status [0]);
		iTemp |= PORT_SUSPEND;
		writel (iTemp, &ehci->regs->port_status [0]);
#endif

	return 0;
}



static const struct hc_driver ehci_sl2312_hc_driver_1 = {
	.description =		"ehci-hcd-FOTG2XX-1",
        .product_desc = "FOTG200 Host 1 Controller", //2.6.15
        .hcd_priv_size =	sizeof(struct ehci_hcd), //2.6.115
	/*
	 * generic hardware linkage
	 */
	.irq =			ehci_irq_1,
	.flags =		HCD_MEMORY | HCD_USB2,

	/*
	 * basic lifecycle operations
	 */
	.reset =		ehci_hc_reset_1,
	.start =		ehci_start_1,
#ifdef	CONFIG_PM
	.suspend =		ehci_suspend,
	.resume =		ehci_resume,
#endif
	.stop =			ehci_stop_1,

	/*
	 * memory lifecycle (except per-request)
	 */
//	.hcd_alloc =		ehci_hcd_alloc,   2.6.15

	/*
	 * managing i/o requests and associated device resources
	 */
	.urb_enqueue =		ehci_urb_enqueue_1,
	.urb_dequeue =		ehci_urb_dequeue_1,
	.endpoint_disable =	ehci_endpoint_disable_1,

	/*
	 * scheduling support
	 */
	.get_frame_number =	ehci_get_frame_1,

	/*
	 * root hub support
	 */
	.hub_status_data =	ehci_hub_status_data_1,
	.hub_control =		ehci_hub_control_1,
	.bus_suspend =		ehci_bus_suspend_1,  //2.6.15
	.bus_resume =		ehci_bus_resume_1,   //2.6.15
#if defined  (CONFIG_USB_SL2312_1) || defined (CONFIG_USB_SL2312_1_MODULE)
        .disconnect_for_OTG =   ehci_disconnect_for_OTG_1,
#endif
};

//End;;Faraday-EHCI(FOTG2XX)
extern int usb_ehcd_FEHCI_probe_1 (const struct hc_driver *driver,
			  struct usb_hcd **hcd_out,
			  struct platform_device *dev);//Input the EHCI Driver pointer

static int ehci_hcd_sl2312_drv_probe_1(struct platform_device *pdev)
{
//	struct platform_device *pdev = to_platform_device(dev);
	struct usb_hcd *hcd = NULL;
	int ret;
#ifdef USB_BUILD_MODULE		
  USB_driver_Flag_1 =0;
#endif  
	pr_debug ("In ohci_hcd_sl2312_drv_probe");

//        sl2312_ohci_configure();
        
	if (usb_disabled())
		return -ENODEV;

	ret = usb_ehcd_FEHCI_probe_1(&ehci_sl2312_hc_driver_1, &hcd, pdev);

	if (ret == 0)
		dev_set_drvdata(&pdev->dev, hcd);

	return ret;
}

static int ehci_hcd_sl2312_drv_remove_1(struct platform_device *pdev)
{
//	struct platform_device *pdev = to_platform_device(dev);
#ifdef USB_BUILD_MODULE
struct usb_hcd *hcd = platform_get_drvdata(pdev);
printk("ehci_hcd_sl2312_drv_remove hcd %x \n",hcd);
if (!hcd)
		return 0;
usb_remove_hcd(hcd);
	release_mem_region(pdev->resource[0].start, pdev->resource[0].end - pdev->resource[0].start + 1);
usb_put_hcd(hcd);
#else
	struct usb_hcd *hcd = dev_get_drvdata(&pdev->dev);

//	usb_hcd_sl2312_remove(hcd, pdev);
	dev_set_drvdata(&pdev->dev, NULL);
#endif
	return 0;
}

static int ehci_hcd_sl2312_drv_suspend_1(struct platform_device *pdev, u32 state, u32 level)
{
//	struct platform_device *pdev = to_platform_device(dev);
//	struct usb_hcd *hcd = dev_get_drvdata(dev);
	printk("%s: not implemented yet\n", __FUNCTION__);

	return 0;
}

static int ehci_hcd_sl2312_drv_resume_1(struct platform_device *pdev, u32 state)
{
//	struct platform_device *pdev = to_platform_device(dev);
//	struct usb_hcd *hcd = dev_get_drvdata(dev);
	printk("%s: not implemented yet\n", __FUNCTION__);

	return 0;
}


static struct platform_driver ehci_hcd_sl2312_driver_1 = {
//	.name		= "ehci-hcd-FOTG2XX",
//	.bus		= &platform_bus_type,
	.probe		= ehci_hcd_sl2312_drv_probe_1,
	.remove		= ehci_hcd_sl2312_drv_remove_1,
	.suspend	= ehci_hcd_sl2312_drv_suspend_1, 
	.resume		= ehci_hcd_sl2312_drv_resume_1, 
	.driver	= {
		.name = "ehci-hcd-FOTG2XX-1",
	},
};



static int __init sl2312_usb_init_1 (void) 
{

//	dbg (DRIVER_INFO);
        pr_debug (DRIVER_INFO " (sl2312)");
	pr_debug ("block sizes: ed %d td %d\n",
		sizeof (struct ed), sizeof (struct td));
	dbg ("block sizes: qh %Zd qtd %Zd itd %Zd sitd %Zd",
		sizeof (struct ehci_qh), sizeof (struct ehci_qtd),
		sizeof (struct ehci_itd), sizeof (struct ehci_sitd));
//    DBG_HOST_EHCI("### >>> &ehci_driver = 0x%x \n",&ehci_driver);
return platform_driver_register(&ehci_hcd_sl2312_driver_1);
	
//Faraday-EHCI(FOTG2XX);;return pci_module_init (&ehci_pci_driver);

}
module_init (sl2312_usb_init_1);

static void __exit sl2312_usb_cleanup_1 (void) 
{	


//    DBG_HOST_EHCI("### >>> Enter ehci-hcd.c file --> cleanup function \n");
platform_driver_unregister(&ehci_hcd_sl2312_driver_1);
  //Faraday-EHCI(FOTG2XX);;pci_unregister_driver (&ehci_pci_driver);
}
module_exit (sl2312_usb_cleanup_1);
