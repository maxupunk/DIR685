/*
 * (C) Copyright Linus Torvalds 1999
 * (C) Copyright Johannes Erdfelt 1999-2001
 * (C) Copyright Andreas Gal 1999
 * (C) Copyright Gregory P. Smith 1999
 * (C) Copyright Deti Fliegl 1999
 * (C) Copyright Randy Dunlap 2000
 * (C) Copyright David Brownell 2000-2002
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
#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/completion.h>
#include <linux/utsname.h>
#include <linux/mm.h>
#include <asm/io.h>
#include <asm/scatterlist.h>
#include <linux/device.h>
#include <linux/dma-mapping.h>
#include <asm/irq.h>
#include <asm/byteorder.h>

#include <linux/usb.h>

#include "usb.h"
#include "hcd.h"
#include "hub.h"

#include <asm/arch/sl2312.h>
#include <asm/arch/irqs.h>

#include <linux/signal.h>
#include <linux/platform_device.h>

#include <asm/mach-types.h>
#include <asm/hardware.h>
// #define USB_BANDWIDTH_MESSAGES

/*-------------------------------------------------------------------------*/

/*
 * USB Host Controller Driver framework
 *
 * Plugs into usbcore (usb_bus) and lets HCDs share code, minimizing
 * HCD-specific behaviors/bugs.
 *
 * This does error checks, tracks devices and urbs, and delegates to a
 * "hc_driver" only for code (and data) that really needs to know about
 * hardware differences.  That includes root hub registers, i/o queues,
 * and so on ... but as little else as possible.
 *
 * Shared code includes most of the "root hub" code (these are emulated,
 * though each HC's hardware works differently) and PCI glue, plus request
 * tracking overhead.  The HCD code should only block on spinlocks or on
 * hardware handshaking; blocking on software events (such as other kernel
 * threads releasing resources, or completing actions) is all generic.
 *
 * Happens the USB 2.0 spec says this would be invisible inside the "USBD",
 * and includes mostly a "HCDI" (HCD Interface) along with some APIs used
 * only by the hub driver ... and that neither should be seen or used by
 * usb client device drivers.
 *
 * Contributors of ideas or unattributed patches include: David Brownell,
 * Roman Weissgaerber, Rory Bolt, Greg Kroah-Hartman, ...
 *
 * HISTORY:
 * 2002-02-21	Pull in most of the usb_bus support from usb.c; some
 *		associated cleanup.  "usb_hcd" still != "usb_bus".
 * 2001-12-12	Initial patch version for Linux 2.5.1 kernel.
 */

/*-------------------------------------------------------------------------*/

/* host controllers we manage */
LIST_HEAD (usb_bus_list);
EXPORT_SYMBOL_GPL (usb_bus_list);

/* used when allocating bus numbers */
#define USB_MAXBUS		64
struct usb_busmap {
	unsigned long busmap [USB_MAXBUS / (8*sizeof (unsigned long))];
};
static struct usb_busmap busmap;

/* used when updating list of hcds */
DECLARE_MUTEX (usb_bus_list_lock);	/* exported only for usbfs */
EXPORT_SYMBOL_GPL (usb_bus_list_lock);

/* used for controlling access to virtual root hubs */
static DEFINE_SPINLOCK(hcd_root_hub_lock);

/* used when updating hcd data */
static DEFINE_SPINLOCK(hcd_data_lock);

/* wait queue for synchronous unlinks */
DECLARE_WAIT_QUEUE_HEAD(usb_kill_urb_queue);

//#ifdef CONFIG_USB_SL2312
struct usb_hcd		*ghcd_FOTG2XX;//Faraday-EHCI(FOTG2XX/FUSBH200)
struct usb_hcd		*ghcd_FUSBH200;//Faraday-EHCI(FOTG2XX/FUSBH200)
//#else
//#ifdef CONFIG_USB_SL2312_1
struct usb_hcd		*ghcd_FOTG2XX_1;//Faraday-EHCI(FOTG2XX/FUSBH200)
struct usb_hcd		*ghcd_FUSBH200_1;//Faraday-EHCI(FOTG2XX/FUSBH200)
//#endif
//#endif

//Start;;Faraday-EHCI(FOTG2XX/FUSBH200)
static const char FOTG200_BusName[]={'A','H','B','-','B','U','S',0x00};
static const char FOTG200_product_desc[]={'F','-','E','H','C','I',0x00};
static const char FUSBH200_BusName[]={'A','H','B','-','B','U','S',0x00};
static const char FUSBH200_product_desc[]={'F','-','E','H','C','I',0x00};
//End;;Faraday-EHCI(FOTG2XX/FUSBH200)

/*-------------------------------------------------------------------------*/

/*
 * Sharable chunks of root hub code.
 */

/*-------------------------------------------------------------------------*/

#define KERNEL_REL	((LINUX_VERSION_CODE >> 16) & 0x0ff)
#define KERNEL_VER	((LINUX_VERSION_CODE >> 8) & 0x0ff)
//#ifdef CONFIG_USB_SL2312
#define IRQ_USB_HOST20   IRQ_USB0//IRQ_USB0
#define CPE_HOST20_BASE  SL2312_USB0_BASE//SL2312_USB0_BASE
//#else
//#ifdef CONFIG_USB_SL2312_1
#define IRQ_USB_HOST20_1   IRQ_USB1
#define CPE_HOST20_BASE_1  SL2312_USB1_BASE
//#endif
//#endif

/* usb 2.0 root hub device descriptor */
static const u8 usb2_rh_dev_descriptor [18] = {
	0x12,       /*  __u8  bLength; */
	0x01,       /*  __u8  bDescriptorType; Device */
	0x00, 0x02, /*  __le16 bcdUSB; v2.0 */

	0x09,	    /*  __u8  bDeviceClass; HUB_CLASSCODE */
	0x00,	    /*  __u8  bDeviceSubClass; */
	0x01,       /*  __u8  bDeviceProtocol; [ usb 2.0 single TT ]*/
//	0x40,       /*  __u8  bMaxPacketSize0; 64 Bytes */
        0x08,       /*  __u8  bMaxPacketSize0; 8 Bytes */

	0x00, 0x00, /*  __le16 idVendor; */
 	0x00, 0x00, /*  __le16 idProduct; */
	KERNEL_VER, KERNEL_REL, /*  __le16 bcdDevice */

	0x03,       /*  __u8  iManufacturer; */
	0x02,       /*  __u8  iProduct; */
	0x01,       /*  __u8  iSerialNumber; */
	0x01        /*  __u8  bNumConfigurations; */
};

/* no usb 2.0 root hub "device qualifier" descriptor: one speed only */

/* usb 1.1 root hub device descriptor */
static const u8 usb11_rh_dev_descriptor [18] = {
	0x12,       /*  __u8  bLength; */
	0x01,       /*  __u8  bDescriptorType; Device */
	0x10, 0x01, /*  __le16 bcdUSB; v1.1 */

	0x09,	    /*  __u8  bDeviceClass; HUB_CLASSCODE */
	0x00,	    /*  __u8  bDeviceSubClass; */
	0x00,       /*  __u8  bDeviceProtocol; [ low/full speeds only ] */
//	0x40,       /*  __u8  bMaxPacketSize0; 64 Bytes */
        0x08,       /*  __u8  bMaxPacketSize0; 8 Bytes */

	0x00, 0x00, /*  __le16 idVendor; */
 	0x00, 0x00, /*  __le16 idProduct; */
	KERNEL_VER, KERNEL_REL, /*  __le16 bcdDevice */

	0x03,       /*  __u8  iManufacturer; */
	0x02,       /*  __u8  iProduct; */
	0x01,       /*  __u8  iSerialNumber; */
	0x01        /*  __u8  bNumConfigurations; */
};


/*-------------------------------------------------------------------------*/

/* Configuration descriptors for our root hubs */

static const u8 fs_rh_config_descriptor [] = {

	/* one configuration */
	0x09,       /*  __u8  bLength; */
	0x02,       /*  __u8  bDescriptorType; Configuration */
	0x19, 0x00, /*  __le16 wTotalLength; */
	0x01,       /*  __u8  bNumInterfaces; (1) */
	0x01,       /*  __u8  bConfigurationValue; */
	0x00,       /*  __u8  iConfiguration; */
	0xc0,       /*  __u8  bmAttributes; 
				 Bit 7: must be set,
				     6: Self-powered,
				     5: Remote wakeup,
				     4..0: resvd */
	0x00,       /*  __u8  MaxPower; */
      
	/* USB 1.1:
	 * USB 2.0, single TT organization (mandatory):
	 *	one interface, protocol 0
	 *
	 * USB 2.0, multiple TT organization (optional):
	 *	two interfaces, protocols 1 (like single TT)
	 *	and 2 (multiple TT mode) ... config is
	 *	sometimes settable
	 *	NOT IMPLEMENTED
	 */

	/* one interface */
	0x09,       /*  __u8  if_bLength; */
	0x04,       /*  __u8  if_bDescriptorType; Interface */
	0x00,       /*  __u8  if_bInterfaceNumber; */
	0x00,       /*  __u8  if_bAlternateSetting; */
	0x01,       /*  __u8  if_bNumEndpoints; */
	0x09,       /*  __u8  if_bInterfaceClass; HUB_CLASSCODE */
	0x00,       /*  __u8  if_bInterfaceSubClass; */
	0x00,       /*  __u8  if_bInterfaceProtocol; [usb1.1 or single tt] */
	0x00,       /*  __u8  if_iInterface; */
     
	/* one endpoint (status change endpoint) */
	0x07,       /*  __u8  ep_bLength; */
	0x05,       /*  __u8  ep_bDescriptorType; Endpoint */
	0x81,       /*  __u8  ep_bEndpointAddress; IN Endpoint 1 */
 	0x03,       /*  __u8  ep_bmAttributes; Interrupt */
 	0x02, 0x00, /*  __le16 ep_wMaxPacketSize; 1 + (MAX_ROOT_PORTS / 8) */
	0xff        /*  __u8  ep_bInterval; (255ms -- usb 2.0 spec) */
};

static const u8 hs_rh_config_descriptor [] = {

	/* one configuration */
	0x09,       /*  __u8  bLength; */
	0x02,       /*  __u8  bDescriptorType; Configuration */
	0x19, 0x00, /*  __le16 wTotalLength; */
	0x01,       /*  __u8  bNumInterfaces; (1) */
	0x01,       /*  __u8  bConfigurationValue; */
	0x00,       /*  __u8  iConfiguration; */
	0xc0,       /*  __u8  bmAttributes; 
				 Bit 7: must be set,
				     6: Self-powered,
				     5: Remote wakeup,
				     4..0: resvd */
	0x00,       /*  __u8  MaxPower; */
      
	/* USB 1.1:
	 * USB 2.0, single TT organization (mandatory):
	 *	one interface, protocol 0
	 *
	 * USB 2.0, multiple TT organization (optional):
	 *	two interfaces, protocols 1 (like single TT)
	 *	and 2 (multiple TT mode) ... config is
	 *	sometimes settable
	 *	NOT IMPLEMENTED
	 */

	/* one interface */
	0x09,       /*  __u8  if_bLength; */
	0x04,       /*  __u8  if_bDescriptorType; Interface */
	0x00,       /*  __u8  if_bInterfaceNumber; */
	0x00,       /*  __u8  if_bAlternateSetting; */
	0x01,       /*  __u8  if_bNumEndpoints; */
	0x09,       /*  __u8  if_bInterfaceClass; HUB_CLASSCODE */
	0x00,       /*  __u8  if_bInterfaceSubClass; */
	0x00,       /*  __u8  if_bInterfaceProtocol; [usb1.1 or single tt] */
	0x00,       /*  __u8  if_iInterface; */
     
	/* one endpoint (status change endpoint) */
	0x07,       /*  __u8  ep_bLength; */
	0x05,       /*  __u8  ep_bDescriptorType; Endpoint */
	0x81,       /*  __u8  ep_bEndpointAddress; IN Endpoint 1 */
 	0x03,       /*  __u8  ep_bmAttributes; Interrupt */
 	0x02, 0x00, /*  __le16 ep_wMaxPacketSize; 1 + (MAX_ROOT_PORTS / 8) */
	0x0c        /*  __u8  ep_bInterval; (256ms -- usb 2.0 spec) */
};

/*-------------------------------------------------------------------------*/

/*
 * helper routine for returning string descriptors in UTF-16LE
 * input can actually be ISO-8859-1; ASCII is its 7-bit subset
 */
static int ascii2utf (char *s, u8 *utf, int utfmax)
{
	int retval;

	for (retval = 0; *s && utfmax > 1; utfmax -= 2, retval += 2) {
		*utf++ = *s++;
		*utf++ = 0;
	}
	if (utfmax > 0) {
		*utf = *s;
		++retval;
	}
	return retval;
}

/*
 * rh_string - provides manufacturer, product and serial strings for root hub
 * @id: the string ID number (1: serial number, 2: product, 3: vendor)
 * @hcd: the host controller for this root hub
 * @type: string describing our driver 
 * @data: return packet in UTF-16 LE
 * @len: length of the return packet
 *
 * Produces either a manufacturer, product or serial number string for the
 * virtual root hub device.
 */
static int rh_string (
	int		id,
	struct usb_hcd	*hcd,
	u8		*data,
	int		len
) {
	char buf [100];

	// language ids
	if (id == 0) {
		buf[0] = 4;    buf[1] = 3;	/* 4 bytes string data */
		buf[2] = 0x09; buf[3] = 0x04;	/* MSFT-speak for "en-us" */
		len = min (len, 4);
		memcpy (data, buf, len);
		return len;

	// serial number
	} else if (id == 1) {
		strlcpy (buf, hcd->self.bus_name, sizeof buf);

	// product description
	} else if (id == 2) {
		strlcpy (buf, hcd->product_desc, sizeof buf);

 	// id 3 == vendor description
	} else if (id == 3) {
		snprintf (buf, sizeof buf, "%s %s %s", system_utsname.sysname,
			system_utsname.release, hcd->driver->description);

	// unsupported IDs --> "protocol stall"
	} else
		return -EPIPE;

	switch (len) {		/* All cases fall through */
	default:
		len = 2 + ascii2utf (buf, data + 2, len - 2);
	case 2:
		data [1] = 3;	/* type == string */
	case 1:
		data [0] = 2 * (strlen (buf) + 1);
	case 0:
		;		/* Compiler wants a statement here */
	}
	return len;
}


/* Root hub control transfers execute synchronously */
static int rh_call_control (struct usb_hcd *hcd, struct urb *urb)
{
	struct usb_ctrlrequest *cmd;
 	u16		typeReq, wValue, wIndex, wLength;
	u8		*ubuf = urb->transfer_buffer;
	u8		tbuf [sizeof (struct usb_hub_descriptor)];
	const u8	*bufp = tbuf;
	int		len = 0;
	int		patch_wakeup = 0;
	unsigned long	flags;
	int		status = 0;
	int		n;

	cmd = (struct usb_ctrlrequest *) urb->setup_packet;
	typeReq  = (cmd->bRequestType << 8) | cmd->bRequest;
	wValue   = le16_to_cpu (cmd->wValue);
	wIndex   = le16_to_cpu (cmd->wIndex);
	wLength  = le16_to_cpu (cmd->wLength);

	if (wLength > urb->transfer_buffer_length)
		goto error;

	urb->actual_length = 0;
	switch (typeReq) {

	/* DEVICE REQUESTS */

	case DeviceRequest | USB_REQ_GET_STATUS:
		tbuf [0] = (hcd->remote_wakeup << USB_DEVICE_REMOTE_WAKEUP)
				| (1 << USB_DEVICE_SELF_POWERED);
		tbuf [1] = 0;
		len = 2;
		break;
	case DeviceOutRequest | USB_REQ_CLEAR_FEATURE:
		if (wValue == USB_DEVICE_REMOTE_WAKEUP)
			hcd->remote_wakeup = 0;
		else
			goto error;
		break;
	case DeviceOutRequest | USB_REQ_SET_FEATURE:
		if (hcd->can_wakeup && wValue == USB_DEVICE_REMOTE_WAKEUP)
			hcd->remote_wakeup = 1;
		else
			goto error;
		break;
	case DeviceRequest | USB_REQ_GET_CONFIGURATION:
		tbuf [0] = 1;
		len = 1;
			/* FALLTHROUGH */
	case DeviceOutRequest | USB_REQ_SET_CONFIGURATION:
		break;
	case DeviceRequest | USB_REQ_GET_DESCRIPTOR:
		switch (wValue & 0xff00) {
		case USB_DT_DEVICE << 8:
			if (hcd->driver->flags & HCD_USB2)
				bufp = usb2_rh_dev_descriptor;
			else if (hcd->driver->flags & HCD_USB11)
				bufp = usb11_rh_dev_descriptor;
			else
				goto error;
			len = 18;
			break;
		case USB_DT_CONFIG << 8:
			if (hcd->driver->flags & HCD_USB2) {
				bufp = hs_rh_config_descriptor;
				len = sizeof hs_rh_config_descriptor;
			} else {
				bufp = fs_rh_config_descriptor;
				len = sizeof fs_rh_config_descriptor;
			}
			if (hcd->can_wakeup)
				patch_wakeup = 1;
			break;
		case USB_DT_STRING << 8:
			n = rh_string (wValue & 0xff, hcd, ubuf, wLength);
			if (n < 0)
				goto error;
			urb->actual_length = n;
			break;
		default:
			goto error;
		}
		break;
	case DeviceRequest | USB_REQ_GET_INTERFACE:
		tbuf [0] = 0;
		len = 1;
			/* FALLTHROUGH */
	case DeviceOutRequest | USB_REQ_SET_INTERFACE:
		break;
	case DeviceOutRequest | USB_REQ_SET_ADDRESS:
		// wValue == urb->dev->devaddr
		dev_dbg (hcd->self.controller, "root hub device address %d\n",
			wValue);
		break;

	/* INTERFACE REQUESTS (no defined feature/status flags) */

	/* ENDPOINT REQUESTS */

	case EndpointRequest | USB_REQ_GET_STATUS:
		// ENDPOINT_HALT flag
		tbuf [0] = 0;
		tbuf [1] = 0;
		len = 2;
			/* FALLTHROUGH */
	case EndpointOutRequest | USB_REQ_CLEAR_FEATURE:
	case EndpointOutRequest | USB_REQ_SET_FEATURE:
		dev_dbg (hcd->self.controller, "no endpoint features yet\n");
		break;

	/* CLASS REQUESTS (and errors) */

	default:
		/* non-generic request */
		switch (typeReq) {
		case GetHubStatus:
		case GetPortStatus:
			len = 4;
			break;
		case GetHubDescriptor:
			len = sizeof (struct usb_hub_descriptor);
			break;
		}
		status = hcd->driver->hub_control (hcd,
			typeReq, wValue, wIndex,
			tbuf, wLength);
		break;
error:
		/* "protocol stall" on error */
		status = -EPIPE;
	}

	if (status) {
		len = 0;
		if (status != -EPIPE) {
			dev_dbg (hcd->self.controller,
				"CTRL: TypeReq=0x%x val=0x%x "
				"idx=0x%x len=%d ==> %d\n",
				typeReq, wValue, wIndex,
				wLength, status);
		}
	}
	if (len) {
		if (urb->transfer_buffer_length < len)
			len = urb->transfer_buffer_length;
		urb->actual_length = len;
		// always USB_DIR_IN, toward host
		memcpy (ubuf, bufp, len);

		/* report whether RH hardware supports remote wakeup */
		if (patch_wakeup &&
				len > offsetof (struct usb_config_descriptor,
						bmAttributes))
			((struct usb_config_descriptor *)ubuf)->bmAttributes
				|= USB_CONFIG_ATT_WAKEUP;
	}

	/* any errors get returned through the urb completion */
	local_irq_save (flags);
	spin_lock (&urb->lock);
	if (urb->status == -EINPROGRESS)
		urb->status = status;
	spin_unlock (&urb->lock);
	usb_hcd_giveback_urb (hcd, urb, NULL);
	local_irq_restore (flags);
	return 0;
}

/*-------------------------------------------------------------------------*/
static int rh_queue_status (struct usb_hcd *hcd, struct urb *urb)
{
	int		retval;
	unsigned long	flags;
	int		len = 1 + (urb->dev->maxchild / 8);
        
	spin_lock_irqsave (&hcd_root_hub_lock, flags);
//	printk("rh_queue_status hcd %x\n",hcd);
	if (urb->status != -EINPROGRESS)	/* already unlinked */
		retval = urb->status;
//#ifdef CONFIG_USB_SL2312
//#ifdef CONFIG_USB_SL2312_1
//	else if (hcd!=ghcd_FOTG2XX || hcd!=ghcd_FOTG2XX_1){
//#else
//        else if (hcd!=ghcd_FOTG2XX){
//#endif
//#else
//#ifdef CONFIG_USB_SL2312_1
//        else if (hcd!=ghcd_FOTG2XX_1){
//#endif
//#endif
        /* Two port Host Only support !!!!*/
        else if (0){
	if (hcd->status_urb || urb->transfer_buffer_length < len) {
		dev_dbg (hcd->self.controller, "not queuing rh status urb\n");
		retval = -EINVAL;
	      }
	} else {
		hcd->status_urb = urb;
		urb->hcpriv = hcd;	/* indicate it's queued */

		if (!hcd->uses_new_polling)
			mod_timer (&hcd->rh_timer, jiffies +
					msecs_to_jiffies(250));

		/* If a status change has already occurred, report it ASAP */
		else if (hcd->poll_pending)
			mod_timer (&hcd->rh_timer, jiffies);
		retval = 0;
	}
	spin_unlock_irqrestore (&hcd_root_hub_lock, flags);
	return retval;
}
/*
 * Root Hub interrupt transfers are polled using a timer if the
 * driver requests it; otherwise the driver is responsible for
 * calling usb_hcd_poll_rh_status() when an event occurs.
 *
 * Completions are called in_interrupt(), but they may or may not
 * be in_irq().
 */
void usb_hcd_poll_rh_status(struct usb_hcd *hcd)
{
	struct urb	*urb;
	int		length;
	unsigned long	flags;
	char		buffer[4];	/* Any root hubs with > 31 ports? */
//	printk("usb_hcd_poll_rh_status hcd %x\n",hcd);
if (!hcd->uses_new_polling && !hcd->status_urb)
		return;

	length = hcd->driver->hub_status_data(hcd, buffer);
	if (length > 0) {

		/* try to complete the status urb */
		spin_lock_irqsave (&urb->lock, flags);
		spin_lock(&hcd_root_hub_lock);
		urb = hcd->status_urb;
		if (urb) {
			spin_lock(&urb->lock);
			if (urb->status == -EINPROGRESS) {
				hcd->poll_pending = 0;
				hcd->status_urb = NULL;
				urb->status = 0;
				urb->hcpriv = NULL;
				urb->actual_length = length;
				memcpy(urb->transfer_buffer, buffer, length);
			} else		/* urb has been unlinked */
//				length = 0;
                              {
 /* Two port Host Only support !!!!*/             
#if defined  (CONFIG_USB_SL2312) || defined (CONFIG_USB_SL2312_MODULE)
#if defined  (CONFIG_USB_SL2312_1) || defined (CONFIG_USB_SL2312_1_MODULE)
                                  if (ghcd_FOTG2XX==hcd || ghcd_FOTG2XX_1==hcd)  //Faraday-EHCI(FOTG2XX)
#else
	                          if (ghcd_FOTG2XX==hcd)  //Faraday-EHCI(FOTG2XX)
#endif	                          
#else
#if defined  (CONFIG_USB_SL2312_1) || defined (CONFIG_USB_SL2312_1_MODULE)
                                  if (ghcd_FOTG2XX_1==hcd)  //Faraday-EHCI(FOTG2XX)
#endif
#endif	                     
	                                               {
                                			 rh_queue_status (hcd, urb);//Faraday-EHCI(FOTG2XX)
                                			 length = 0;
			                                 }
			         }
			spin_unlock(&urb->lock);
		} else
			length = 0;
		spin_unlock(&hcd_root_hub_lock);

		/* local irqs are always blocked in completions */
		if (length > 0)
			usb_hcd_giveback_urb (hcd, urb, NULL);
		else
			hcd->poll_pending = 1;
		spin_unlock_irqrestore (&urb->lock, flags);
	}

	/* The USB 2.0 spec says 256 ms.  This is close enough and won't
	 * exceed that limit if HZ is 100. */
	if (hcd->uses_new_polling ? hcd->poll_rh :
			(length == 0 && hcd->status_urb != NULL))
		mod_timer (&hcd->rh_timer, jiffies + msecs_to_jiffies(250));
}
EXPORT_SYMBOL_GPL(usb_hcd_poll_rh_status);

/* timer callback */
void rh_timer_func (unsigned long _hcd)
{
	usb_hcd_poll_rh_status((struct usb_hcd *) _hcd);
}
EXPORT_SYMBOL(rh_timer_func);
/*-------------------------------------------------------------------------*/

static int rh_urb_enqueue (struct usb_hcd *hcd, struct urb *urb)
{
	if (usb_pipeint (urb->pipe))
		return rh_queue_status (hcd, urb);
	if (usb_pipecontrol (urb->pipe))
		return rh_call_control (hcd, urb);
	return -EINVAL;
}

/*-------------------------------------------------------------------------*/

/* Asynchronous unlinks of root-hub control URBs are legal, but they
 * don't do anything.  Status URB unlinks must be made in process context
 * with interrupts enabled.
 */
static int usb_rh_urb_dequeue (struct usb_hcd *hcd, struct urb *urb)
{
	if (usb_pipeendpoint(urb->pipe) == 0) {	/* Control URB */
		if (in_interrupt())
			return 0;		/* nothing to do */

		spin_lock_irq(&urb->lock);	/* from usb_kill_urb */
		++urb->reject;
		spin_unlock_irq(&urb->lock);

		wait_event(usb_kill_urb_queue,
				atomic_read(&urb->use_count) == 0);

		spin_lock_irq(&urb->lock);
		--urb->reject;
		spin_unlock_irq(&urb->lock);

	} else {				/* Status URB */
		if (!hcd->uses_new_polling)
			del_timer_sync (&hcd->rh_timer);
		local_irq_disable ();
		spin_lock (&hcd_root_hub_lock);
		if (urb == hcd->status_urb) {
			hcd->status_urb = NULL;
			urb->hcpriv = NULL;
		} else
			urb = NULL;		/* wasn't fully queued */
		spin_unlock (&hcd_root_hub_lock);
		if (urb)
			usb_hcd_giveback_urb (hcd, urb, NULL);
		local_irq_enable ();
	}

	return 0;
}

/*-------------------------------------------------------------------------*/

/* exported only within usbcore */
struct usb_bus *usb_bus_get(struct usb_bus *bus)
{
	if (bus)
		kref_get(&bus->kref);
	return bus;
}

static void usb_host_release(struct kref *kref)
{
	struct usb_bus *bus = container_of(kref, struct usb_bus, kref);

	if (bus->release)
		bus->release(bus);
}

/* exported only within usbcore */
void usb_bus_put(struct usb_bus *bus)
{
	if (bus)
		kref_put(&bus->kref, usb_host_release);
}

/*-------------------------------------------------------------------------*/

static struct class *usb_host_class;
/*static struct class usb_host_class = {
	.name              = "usb_host",
	.release        = &usb_host_release,
	}
*/
int usb_host_init(void)
{
	int retval = 0;

	usb_host_class = class_create(THIS_MODULE, "usb_host");
	if (IS_ERR(usb_host_class))
		retval = PTR_ERR(usb_host_class);
//	printk("********usb_host_init usb_host_class %x\n",usb_host_class);
	return retval;
}

void usb_host_cleanup(void)
{
	class_destroy(usb_host_class);
}

/**
 * usb_bus_init - shared initialization code
 * @bus: the bus structure being initialized
 *
 * This code is used to initialize a usb_bus structure, memory for which is
 * separately managed.
 */
void usb_bus_init (struct usb_bus *bus)
{
	memset (&bus->devmap, 0, sizeof(struct usb_devmap));

	bus->devnum_next = 1;

	bus->root_hub = NULL;
	bus->hcpriv = NULL;
	bus->busnum = -1;
	bus->bandwidth_allocated = 0;
	bus->bandwidth_int_reqs  = 0;
	bus->bandwidth_isoc_reqs = 0;

	INIT_LIST_HEAD (&bus->bus_list);

	kref_init(&bus->kref);
}
EXPORT_SYMBOL (usb_bus_init);
/**
 * usb_alloc_bus - creates a new USB host controller structure
 * @op: pointer to a struct usb_operations that this bus structure should use
 * Context: !in_interrupt()
 *
 * Creates a USB host controller bus structure with the specified 
 * usb_operations and initializes all the necessary internal objects.
 *
 * If no memory is available, NULL is returned.
 *
 * The caller should call usb_put_bus() when it is finished with the structure.
 */
struct usb_bus *usb_alloc_bus (struct usb_operations *op)
{
	struct usb_bus *bus;

	bus = kzalloc (sizeof *bus, GFP_KERNEL);
	if (!bus)
		return NULL;
	usb_bus_init (bus);
	bus->op = op;
	return bus;
}

/*-------------------------------------------------------------------------*/

/**
 * usb_register_bus - registers the USB host controller with the usb core
 * @bus: pointer to the bus to register
 * Context: !in_interrupt()
 *
 * Assigns a bus number, and links the controller into usbcore data
 * structures so that it can be seen by scanning the bus list.
 */
int usb_register_bus(struct usb_bus *bus)
{
	int busnum;

	down (&usb_bus_list_lock);
	busnum = find_next_zero_bit (busmap.busmap, USB_MAXBUS, 1);
	if (busnum < USB_MAXBUS) {
		set_bit (busnum, busmap.busmap);
		bus->busnum = busnum;
	} else {
		printk ("too many buses %s\n", usbcore_name);
		up(&usb_bus_list_lock);
		return -E2BIG;
	}
	bus->class_dev = class_device_create(usb_host_class, NULL, MKDEV(0,0),
					     bus->controller, "usb_host%d", busnum);
	if (IS_ERR(bus->class_dev)) {
		clear_bit(busnum, busmap.busmap);
		up(&usb_bus_list_lock);
		return PTR_ERR(bus->class_dev);
	}
	class_set_devdata(bus->class_dev, bus);
	/* Add it to the local list of buses */
	list_add (&bus->bus_list, &usb_bus_list);
	up (&usb_bus_list_lock);
	usb_notify_add_bus(bus);
	dev_info (bus->controller, "new USB bus registered, assigned bus number %d\n", bus->busnum);
	return 0;
}
EXPORT_SYMBOL (usb_register_bus);
/**
 * usb_deregister_bus - deregisters the USB host controller
 * @bus: pointer to the bus to deregister
 * Context: !in_interrupt()
 *
 * Recycles the bus number, and unlinks the controller from usbcore data
 * structures so that it won't be seen by scanning the bus list.
 */
static void usb_deregister_bus (struct usb_bus *bus)
{
	dev_info (bus->controller, "USB bus %d deregistered\n", bus->busnum);

	/*
	 * NOTE: make sure that all the devices are removed by the
	 * controller code, as well as having it call this when cleaning
	 * itself up
	 */
	down (&usb_bus_list_lock);
	list_del (&bus->bus_list);
	up (&usb_bus_list_lock);

	usb_notify_remove_bus(bus);

	clear_bit (bus->busnum, busmap.busmap);

	class_device_unregister(bus->class_dev);
}


/**
 * usb_hc_died - report abnormal shutdown of a host controller (bus glue)
 * @hcd: pointer to the HCD representing the controller
 *
 * This is called by bus glue to report a USB host controller that died
 * while operations may still have been pending.  It's called automatically
 * by the PCI glue, so only glue for non-PCI busses should need to call it. 
 */
#if !defined  (CONFIG_USB_SL2312) && !defined (CONFIG_USB_SL2312_MODULE)
#if !defined  (CONFIG_USB_SL2312_1) && !defined (CONFIG_USB_SL2312_1_MODULE)
void usb_hc_died (struct usb_hcd *hcd)
#else
void hc_died (struct usb_hcd *hcd)
#endif
#else 
void hc_died (struct usb_hcd *hcd)
#endif
{
	unsigned long flags;

	dev_err (hcd->self.controller, "HC died; cleaning up\n");

	spin_lock_irqsave (&hcd_root_hub_lock, flags);
	if (hcd->rh_registered) {
		hcd->poll_rh = 0;

		/* make khubd clean up old urbs and devices */
		usb_set_device_state (hcd->self.root_hub,
				USB_STATE_NOTATTACHED);
		usb_kick_khubd (hcd->self.root_hub);
	}
	spin_unlock_irqrestore (&hcd_root_hub_lock, flags);
}
#if !defined  (CONFIG_USB_SL2312) && !defined (CONFIG_USB_SL2312_MODULE)
#if !defined  (CONFIG_USB_SL2312_1) && !defined (CONFIG_USB_SL2312_1_MODULE)
EXPORT_SYMBOL_GPL (usb_hc_died);
#endif
#else
#endif


/**
 * register_root_hub - called by usb_add_hcd() to register a root hub
 * @usb_dev: the usb root hub device to be registered.
 * @hcd: host controller for this root hub
 *
 * This function registers the root hub with the USB subsystem.  It sets up
 * the device properly in the device tree and stores the root_hub pointer
 * in the bus structure, then calls usb_new_device() to register the usb
 * device.  It also assigns the root hub's USB address (always 1).
 */
static int register_root_hub (struct usb_device *usb_dev,
		struct usb_hcd *hcd)
{
	struct device *parent_dev = hcd->self.controller;
	const int devnum = 1;
	int retval;

	usb_dev->devnum = devnum;
	usb_dev->bus->devnum_next = devnum + 1;
	memset (&usb_dev->bus->devmap.devicemap, 0,
			sizeof usb_dev->bus->devmap.devicemap);
	set_bit (devnum, usb_dev->bus->devmap.devicemap);
	usb_set_device_state(usb_dev, USB_STATE_ADDRESS);

	down (&usb_bus_list_lock);
	usb_dev->bus->root_hub = usb_dev;

	usb_dev->ep0.desc.wMaxPacketSize = __constant_cpu_to_le16(64);
	retval = usb_get_device_descriptor(usb_dev, USB_DT_DEVICE_SIZE);
	if (retval != sizeof usb_dev->descriptor) {
		usb_dev->bus->root_hub = NULL;
		up (&usb_bus_list_lock);
		dev_dbg (parent_dev, "can't read %s device descriptor %d\n",
				usb_dev->dev.bus_id, retval);
		return (retval < 0) ? retval : -EMSGSIZE;
	}

	usb_lock_device (usb_dev);
	retval = usb_new_device (usb_dev);
	usb_unlock_device (usb_dev);
	if (retval) {
		usb_dev->bus->root_hub = NULL;
		dev_err (parent_dev, "can't register root hub for %s, %d\n",
				usb_dev->dev.bus_id, retval);
	}
	up (&usb_bus_list_lock);

	if (retval == 0) {
		spin_lock_irq (&hcd_root_hub_lock);
		hcd->rh_registered = 1;
		spin_unlock_irq (&hcd_root_hub_lock);

		/* Did the HC die before the root hub was registered? */
		if (hcd->state == HC_STATE_HALT)
#if defined  (CONFIG_USB_SL2312) || defined (CONFIG_USB_SL2312_MODULE)
                        hc_died(hcd);
#else
#if defined  (CONFIG_USB_SL2312_1) || defined (CONFIG_USB_SL2312_1_MODULE)
                        hc_died(hcd);
#else
			usb_hc_died (hcd);	/* This time clean up */
#endif
#endif
	}

	return retval;
}

int hcd_register_root (struct usb_device *usb_dev,
		struct usb_hcd *hcd)
{
	/* hcd->driver->start() reported can_wakeup, probably with
	 * assistance from board's boot firmware.
	 * NOTE:  normal devices won't enable wakeup by default.
	 */
	if (hcd->can_wakeup)
		printk("supports USB remote wakeup\n");
	hcd->remote_wakeup = hcd->can_wakeup;

	return register_root_hub (usb_dev, hcd);
}
EXPORT_SYMBOL (hcd_register_root);

void usb_enable_root_hub_irq (struct usb_bus *bus)
{
	struct usb_hcd *hcd;

	hcd = container_of (bus, struct usb_hcd, self);
	if (hcd->driver->hub_irq_enable && !hcd->poll_rh &&
			hcd->state != HC_STATE_HALT)
		hcd->driver->hub_irq_enable (hcd);
}


/*-------------------------------------------------------------------------*/

/**
 * usb_calc_bus_time - approximate periodic transaction time in nanoseconds
 * @speed: from dev->speed; USB_SPEED_{LOW,FULL,HIGH}
 * @is_input: true iff the transaction sends data to the host
 * @isoc: true for isochronous transactions, false for interrupt ones
 * @bytecount: how many bytes in the transaction.
 *
 * Returns approximate bus time in nanoseconds for a periodic transaction.
 * See USB 2.0 spec section 5.11.3; only periodic transfers need to be
 * scheduled in software, this function is only used for such scheduling.
 */
long usb_calc_bus_time (int speed, int is_input, int isoc, int bytecount)
{
	unsigned long	tmp;

	switch (speed) {
	case USB_SPEED_LOW: 	/* INTR only */
		if (is_input) {
			tmp = (67667L * (31L + 10L * BitTime (bytecount))) / 1000L;
			return (64060L + (2 * BW_HUB_LS_SETUP) + BW_HOST_DELAY + tmp);
		} else {
			tmp = (66700L * (31L + 10L * BitTime (bytecount))) / 1000L;
			return (64107L + (2 * BW_HUB_LS_SETUP) + BW_HOST_DELAY + tmp);
		}
	case USB_SPEED_FULL:	/* ISOC or INTR */
		if (isoc) {
			tmp = (8354L * (31L + 10L * BitTime (bytecount))) / 1000L;
			return (((is_input) ? 7268L : 6265L) + BW_HOST_DELAY + tmp);
		} else {
			tmp = (8354L * (31L + 10L * BitTime (bytecount))) / 1000L;
			return (9107L + BW_HOST_DELAY + tmp);
		}
	case USB_SPEED_HIGH:	/* ISOC or INTR */
		// FIXME adjust for input vs output
		if (isoc)
			tmp = HS_NSECS_ISO (bytecount);
		else
			tmp = HS_NSECS (bytecount);
		return tmp;
	default:
		pr_debug ("%s: bogus device speed!\n", usbcore_name);
		return -1;
	}
}
EXPORT_SYMBOL (usb_calc_bus_time);

/*
 * usb_check_bandwidth():
 *
 * old_alloc is from host_controller->bandwidth_allocated in microseconds;
 * bustime is from calc_bus_time(), but converted to microseconds.
 *
 * returns <bustime in us> if successful,
 * or -ENOSPC if bandwidth request fails.
 *
 * FIXME:
 * This initial implementation does not use Endpoint.bInterval
 * in managing bandwidth allocation.
 * It probably needs to be expanded to use Endpoint.bInterval.
 * This can be done as a later enhancement (correction).
 *
 * This will also probably require some kind of
 * frame allocation tracking...meaning, for example,
 * that if multiple drivers request interrupts every 10 USB frames,
 * they don't all have to be allocated at
 * frame numbers N, N+10, N+20, etc.  Some of them could be at
 * N+11, N+21, N+31, etc., and others at
 * N+12, N+22, N+32, etc.
 *
 * Similarly for isochronous transfers...
 *
 * Individual HCDs can schedule more directly ... this logic
 * is not correct for high speed transfers.
 */
int usb_check_bandwidth (struct usb_device *dev, struct urb *urb)
{
	unsigned int	pipe = urb->pipe;
	long		bustime;
	int		is_in = usb_pipein (pipe);
	int		is_iso = usb_pipeisoc (pipe);
	int		old_alloc = dev->bus->bandwidth_allocated;
	int		new_alloc;


	bustime = NS_TO_US (usb_calc_bus_time (dev->speed, is_in, is_iso,
			usb_maxpacket (dev, pipe, !is_in)));
	if (is_iso)
		bustime /= urb->number_of_packets;

	new_alloc = old_alloc + (int) bustime;
	if (new_alloc > FRAME_TIME_MAX_USECS_ALLOC) {
#ifdef	DEBUG
		char	*mode = 
#ifdef CONFIG_USB_BANDWIDTH
			"";
#else
			"would have ";
#endif
		dev_dbg (&dev->dev, "usb_check_bandwidth %sFAILED: %d + %ld = %d usec\n",
			mode, old_alloc, bustime, new_alloc);
#endif
#ifdef CONFIG_USB_BANDWIDTH
		bustime = -ENOSPC;	/* report error */
#endif
	}

	return bustime;
}
EXPORT_SYMBOL (usb_check_bandwidth);


/**
 * usb_claim_bandwidth - records bandwidth for a periodic transfer
 * @dev: source/target of request
 * @urb: request (urb->dev == dev)
 * @bustime: bandwidth consumed, in (average) microseconds per frame
 * @isoc: true iff the request is isochronous
 *
 * Bus bandwidth reservations are recorded purely for diagnostic purposes.
 * HCDs are expected not to overcommit periodic bandwidth, and to record such
 * reservations whenever endpoints are added to the periodic schedule.
 *
 * FIXME averaging per-frame is suboptimal.  Better to sum over the HCD's
 * entire periodic schedule ... 32 frames for OHCI, 1024 for UHCI, settable
 * for EHCI (256/512/1024 frames, default 1024) and have the bus expose how
 * large its periodic schedule is.
 */
void usb_claim_bandwidth (struct usb_device *dev, struct urb *urb, int bustime, int isoc)
{
	dev->bus->bandwidth_allocated += bustime;
	if (isoc)
		dev->bus->bandwidth_isoc_reqs++;
	else
		dev->bus->bandwidth_int_reqs++;
	urb->bandwidth = bustime;

#ifdef USB_BANDWIDTH_MESSAGES
	dev_dbg (&dev->dev, "bandwidth alloc increased by %d (%s) to %d for %d requesters\n",
		bustime,
		isoc ? "ISOC" : "INTR",
		dev->bus->bandwidth_allocated,
		dev->bus->bandwidth_int_reqs + dev->bus->bandwidth_isoc_reqs);
#endif
}
EXPORT_SYMBOL (usb_claim_bandwidth);


/**
 * usb_release_bandwidth - reverses effect of usb_claim_bandwidth()
 * @dev: source/target of request
 * @urb: request (urb->dev == dev)
 * @isoc: true iff the request is isochronous
 *
 * This records that previously allocated bandwidth has been released.
 * Bandwidth is released when endpoints are removed from the host controller's
 * periodic schedule.
 */
void usb_release_bandwidth (struct usb_device *dev, struct urb *urb, int isoc)
{
	dev->bus->bandwidth_allocated -= urb->bandwidth;
	if (isoc)
		dev->bus->bandwidth_isoc_reqs--;
	else
		dev->bus->bandwidth_int_reqs--;

#ifdef USB_BANDWIDTH_MESSAGES
	dev_dbg (&dev->dev, "bandwidth alloc reduced by %d (%s) to %d for %d requesters\n",
		urb->bandwidth,
		isoc ? "ISOC" : "INTR",
		dev->bus->bandwidth_allocated,
		dev->bus->bandwidth_int_reqs + dev->bus->bandwidth_isoc_reqs);
#endif
	urb->bandwidth = 0;
}
EXPORT_SYMBOL (usb_release_bandwidth);


/*-------------------------------------------------------------------------*/

/*
 * Generic HC operations.
 */

/*-------------------------------------------------------------------------*/

static void urb_unlink (struct urb *urb)
{
	unsigned long		flags;

	/* Release any periodic transfer bandwidth */
	if (urb->bandwidth)
		usb_release_bandwidth (urb->dev, urb,
			usb_pipeisoc (urb->pipe));

	/* clear all state linking urb to this dev (and hcd) */

	spin_lock_irqsave (&hcd_data_lock, flags);
	list_del_init (&urb->urb_list);
	spin_unlock_irqrestore (&hcd_data_lock, flags);
	usb_put_dev (urb->dev);
}


/* may be called in any context with a valid urb->dev usecount
 * caller surrenders "ownership" of urb
 * expects usb_submit_urb() to have sanity checked and conditioned all
 * inputs in the urb
 */
static int hcd_submit_urb (struct urb *urb, gfp_t mem_flags)
{
	int			status;
	struct usb_hcd		*hcd = urb->dev->bus->hcpriv;
	struct usb_host_endpoint *ep;
	unsigned long		flags;

	if (!hcd)
		return -ENODEV;

//	usbmon_urb_submit(&hcd->self, urb);

	/*
	 * Atomically queue the urb,  first to our records, then to the HCD.
	 * Access to urb->status is controlled by urb->lock ... changes on
	 * i/o completion (normal or fault) or unlinking.
	 */

	// FIXME:  verify that quiescing hc works right (RH cleans up)

	spin_lock_irqsave (&hcd_data_lock, flags);
	ep = (usb_pipein(urb->pipe) ? urb->dev->ep_in : urb->dev->ep_out)
			[usb_pipeendpoint(urb->pipe)];
	if (unlikely (!ep))
		status = -ENOENT;
	else if (unlikely (urb->reject))
		status = -EPERM;
	else switch (hcd->state) {
	case HC_STATE_RUNNING:
	case HC_STATE_RESUMING:
//doit:
		usb_get_dev (urb->dev);
		list_add_tail (&urb->urb_list, &ep->urb_list);
		status = 0;
		break;
//	case HC_STATE_SUSPENDED:
		/* HC upstream links (register access, wakeup signaling) can work
		 * even when the downstream links (and DMA etc) are quiesced; let
		 * usbcore talk to the root hub.
		 */
//		if (hcd->self.controller->power.power_state.event == PM_EVENT_ON
//				&& urb->dev->parent == NULL)
//			goto doit;
		/* FALL THROUGH */
	default:
		status = -ESHUTDOWN;
		break;
	}
	spin_unlock_irqrestore (&hcd_data_lock, flags);
	if (status) {
		INIT_LIST_HEAD (&urb->urb_list);
//		usbmon_urb_submit_error(&hcd->self, urb, status);
//                printk("****** hcd_submit_urb status 3 %x\n",status);
		return status;
	}

	/* increment urb's reference count as part of giving it to the HCD
	 * (which now controls it).  HCD guarantees that it either returns
	 * an error or calls giveback(), but not both.
	 */
	urb = usb_get_urb (urb);
	atomic_inc (&urb->use_count);

	if (urb->dev == hcd->self.root_hub) {
		/* NOTE:  requirement on hub callers (usbfs and the hub
		 * driver, for now) that URBs' urb->transfer_buffer be
		 * valid and usb_buffer_{sync,unmap}() not be needed, since
		 * they could clobber root hub response data.
		 */
		urb->transfer_flags |= (URB_NO_TRANSFER_DMA_MAP
					| URB_NO_SETUP_DMA_MAP); 
		status = rh_urb_enqueue (hcd, urb);
//		printk("****** hcd_submit_urb status 2 %x\n",status);
		goto done;
	}

	/* lower level hcd code should use *_dma exclusively,
	 * unless it uses pio or talks to another transport.
	 */
	if (hcd->self.controller->dma_mask) {
		if (usb_pipecontrol (urb->pipe)
			&& !(urb->transfer_flags & URB_NO_SETUP_DMA_MAP))
			urb->setup_dma = dma_map_single (
					hcd->self.controller,
					urb->setup_packet,
					sizeof (struct usb_ctrlrequest),
					DMA_TO_DEVICE);
		if (urb->transfer_buffer_length != 0
			&& !(urb->transfer_flags & URB_NO_TRANSFER_DMA_MAP))
			urb->transfer_dma = dma_map_single (
					hcd->self.controller,
					urb->transfer_buffer,
					urb->transfer_buffer_length,
					usb_pipein (urb->pipe)
					    ? DMA_FROM_DEVICE
					    : DMA_TO_DEVICE);
	}

	status = hcd->driver->urb_enqueue (hcd, ep, urb, mem_flags);
//	printk("****** hcd_submit_urb status %x\n",status);
done:
	if (unlikely (status)) {
		urb_unlink (urb);
		atomic_dec (&urb->use_count);
		if (urb->reject)
			wake_up (&usb_kill_urb_queue);
		usb_put_urb (urb);
//		usbmon_urb_submit_error(&hcd->self, urb, status);
	}
//	printk("****** hcd_submit_urb status 1 %x\n",status);
	return status;
}

/*-------------------------------------------------------------------------*/

/* called in any context */
static int hcd_get_frame_number (struct usb_device *udev)
{
	struct usb_hcd	*hcd = (struct usb_hcd *)udev->bus->hcpriv;
	if (!HC_IS_RUNNING (hcd->state))
		return -ESHUTDOWN;
	return hcd->driver->get_frame_number (hcd);
}

/*-------------------------------------------------------------------------*/

/* this makes the hcd giveback() the urb more quickly, by kicking it
 * off hardware queues (which may take a while) and returning it as
 * soon as practical.  we've already set up the urb's return status,
 * but we can't know if the callback completed already.
 */
static int
unlink1 (struct usb_hcd *hcd, struct urb *urb)
{
	int		value;

	if (urb->dev == hcd->self.root_hub)
		value = usb_rh_urb_dequeue (hcd, urb);
	else {

		/* The only reason an HCD might fail this call is if
		 * it has not yet fully queued the urb to begin with.
		 * Such failures should be harmless. */
		value = hcd->driver->urb_dequeue (hcd, urb);
	}

	if (value != 0)
		dev_dbg (hcd->self.controller, "dequeue %p --> %d\n",
				urb, value);
	return value;
}

/*
 * called in any context
 *
 * caller guarantees urb won't be recycled till both unlink()
 * and the urb's completion function return
 */
static int hcd_unlink_urb (struct urb *urb, int status)
{
	struct usb_host_endpoint	*ep;
	struct usb_hcd			*hcd = NULL;
	struct device			*sys = NULL;
	unsigned long			flags;
	struct list_head		*tmp;
	int				retval;

	if (!urb)
		return -EINVAL;
	if (!urb->dev || !urb->dev->bus)
		return -ENODEV;
	ep = (usb_pipein(urb->pipe) ? urb->dev->ep_in : urb->dev->ep_out)
			[usb_pipeendpoint(urb->pipe)];
	if (!ep)
		return -ENODEV;

	/*
	 * we contend for urb->status with the hcd core,
	 * which changes it while returning the urb.
	 *
	 * Caller guaranteed that the urb pointer hasn't been freed, and
	 * that it was submitted.  But as a rule it can't know whether or
	 * not it's already been unlinked ... so we respect the reversed
	 * lock sequence needed for the usb_hcd_giveback_urb() code paths
	 * (urb lock, then hcd_data_lock) in case some other CPU is now
	 * unlinking it.
	 */
	spin_lock_irqsave (&urb->lock, flags);
	spin_lock (&hcd_data_lock);

	sys = &urb->dev->dev;
	hcd = urb->dev->bus->hcpriv;
	if (hcd == NULL) {
		retval = -ENODEV;
		goto done;
	}

	/* insist the urb is still queued */
	list_for_each(tmp, &ep->urb_list) {
		if (tmp == &urb->urb_list)
			break;
	}
	if (tmp != &urb->urb_list) {
		retval = -EIDRM;
		goto done;
	}

	/* Any status except -EINPROGRESS means something already started to
	 * unlink this URB from the hardware.  So there's no more work to do.
	 */
	if (urb->status != -EINPROGRESS) {
		retval = -EBUSY;
		goto done;
	}

	/* IRQ setup can easily be broken so that USB controllers
	 * never get completion IRQs ... maybe even the ones we need to
	 * finish unlinking the initial failed usb_set_address()
	 * or device descriptor fetch.
	 */
//	printk("HCD_FLAG_SAW_IRQ %x\n",HCD_FLAG_SAW_IRQ); 
//	printk("hcd_unlink_urb hcd  %x hcd->flags %x self.root_hub %x urb->dev %x\n",hcd,hcd->flags,hcd->self.root_hub,urb->dev);
	if (!test_bit(HCD_FLAG_SAW_IRQ, &hcd->flags)
//        if (!(HCD_FLAG_SAW_IRQ && hcd->flags)  
	    && hcd->self.root_hub != urb->dev) {
		dev_warn (hcd->self.controller, "Unlink after no-IRQ?  "
			"Controller is probably using the wrong IRQ."
			"\n");
		set_bit(HCD_FLAG_SAW_IRQ, &hcd->flags);
	}

	urb->status = status;

	spin_unlock (&hcd_data_lock);
	spin_unlock_irqrestore (&urb->lock, flags);
//        printk("unlink1 \n");
	retval = unlink1 (hcd, urb);
//	printk("unlink1 end retval %x\n",retval);
	if (retval == 0)
		retval = -EINPROGRESS;
	return retval;

done:
	spin_unlock (&hcd_data_lock);
	spin_unlock_irqrestore (&urb->lock, flags);
	if (retval != -EIDRM && sys && sys->driver)
		dev_dbg (sys, "hcd_unlink_urb %p fail %d\n", urb, retval);
	return retval;
}

/*-------------------------------------------------------------------------*/

/* disables the endpoint: cancels any pending urbs, then synchronizes with
 * the hcd to make sure all endpoint state is gone from hardware. use for
 * set_configuration, set_interface, driver removal, physical disconnect.
 *
 * example:  a qh stored in ep->hcpriv, holding state related to endpoint
 * type, maxpacket size, toggle, halt status, and scheduling.
 */
static void
hcd_endpoint_disable (struct usb_device *udev, struct usb_host_endpoint *ep)
{
	struct usb_hcd		*hcd;
	struct urb		*urb;

	hcd = udev->bus->hcpriv;

	WARN_ON (!HC_IS_RUNNING (hcd->state) && hcd->state != HC_STATE_HALT &&
			udev->state != USB_STATE_NOTATTACHED);

	local_irq_disable ();

	/* FIXME move most of this into message.c as part of its
	 * endpoint disable logic
	 */

	/* ep is already gone from udev->ep_{in,out}[]; no more submits */
rescan:
	spin_lock (&hcd_data_lock);
	list_for_each_entry (urb, &ep->urb_list, urb_list) {
		int	tmp;

		/* another cpu may be in hcd, spinning on hcd_data_lock
		 * to giveback() this urb.  the races here should be
		 * small, but a full fix needs a new "can't submit"
		 * urb state.
		 * FIXME urb->reject should allow that...
		 */
		if (urb->status != -EINPROGRESS)
			continue;
		usb_get_urb (urb);
		spin_unlock (&hcd_data_lock);

		spin_lock (&urb->lock);
		tmp = urb->status;
		if (tmp == -EINPROGRESS)
			urb->status = -ESHUTDOWN;
		spin_unlock (&urb->lock);

		/* kick hcd unless it's already returning this */
		if (tmp == -EINPROGRESS) {
			tmp = urb->pipe;
			unlink1 (hcd, urb);
			dev_dbg (hcd->self.controller,
				"shutdown urb %p pipe %08x ep%d%s%s\n",
				urb, tmp, usb_pipeendpoint (tmp),
				(tmp & USB_DIR_IN) ? "in" : "out",
				({ char *s; \
				 switch (usb_pipetype (tmp)) { \
				 case PIPE_CONTROL:	s = ""; break; \
				 case PIPE_BULK:	s = "-bulk"; break; \
				 case PIPE_INTERRUPT:	s = "-intr"; break; \
				 default: 		s = "-iso"; break; \
				}; s;}));
		}
		usb_put_urb (urb);

		/* list contents may have changed */
		goto rescan;
	}
	spin_unlock (&hcd_data_lock);
	local_irq_enable ();

	/* synchronize with the hardware, so old configuration state
	 * clears out immediately (and will be freed).
	 */
	might_sleep ();
	if (hcd->driver->endpoint_disable)
		hcd->driver->endpoint_disable (hcd, ep);
}

/*-------------------------------------------------------------------------*/

#ifdef	CONFIG_PM

int hcd_bus_suspend (struct usb_bus *bus)
{
	struct usb_hcd		*hcd;
	int			status;

	hcd = container_of (bus, struct usb_hcd, self);
	if (!hcd->driver->bus_suspend)
		return -ENOENT;
	hcd->state = HC_STATE_QUIESCING;
	status = hcd->driver->bus_suspend (hcd);
	if (status == 0)
		hcd->state = HC_STATE_SUSPENDED;
	else
		dev_dbg(&bus->root_hub->dev, "%s fail, err %d\n",
				"suspend", status);
	return status;
}

int hcd_bus_resume (struct usb_bus *bus)
{
	struct usb_hcd		*hcd;
	int			status;

	hcd = container_of (bus, struct usb_hcd, self);
	if (!hcd->driver->bus_resume)
		return -ENOENT;
	if (hcd->state == HC_STATE_RUNNING)
		return 0;
	hcd->state = HC_STATE_RESUMING;
	status = hcd->driver->bus_resume (hcd);
	if (status == 0)
		hcd->state = HC_STATE_RUNNING;
	else {
		dev_dbg(&bus->root_hub->dev, "%s fail, err %d\n",
				"resume", status);
		usb_hc_died(hcd);
	}
	return status;
}

/*
 * usb_hcd_suspend_root_hub - HCD autosuspends downstream ports
 * @hcd: host controller for this root hub
 *
 * This call arranges that usb_hcd_resume_root_hub() is safe to call later;
 * that the HCD's root hub polling is deactivated; and that the root's hub
 * driver is suspended.  HCDs may call this to autosuspend when their root
 * hub's downstream ports are all inactive:  unpowered, disconnected,
 * disabled, or suspended.
 *
 * The HCD will autoresume on device connect change detection (using SRP
 * or a D+/D- pullup).  The HCD also autoresumes on remote wakeup signaling
 * from any ports that are suspended (if that is enabled).  In most cases,
 * overcurrent signaling (on powered ports) will also start autoresume.
 *
 * Always called with IRQs blocked.
 */
void usb_hcd_suspend_root_hub (struct usb_hcd *hcd)
{
	struct urb	*urb;

	spin_lock (&hcd_root_hub_lock);
	usb_suspend_root_hub (hcd->self.root_hub);

	/* force status urb to complete/unlink while suspended */
	if (hcd->status_urb) {
		urb = hcd->status_urb;
		urb->status = -ECONNRESET;
		urb->hcpriv = NULL;
		urb->actual_length = 0;

		del_timer (&hcd->rh_timer);
		hcd->poll_pending = 0;
		hcd->status_urb = NULL;
	} else
		urb = NULL;
	spin_unlock (&hcd_root_hub_lock);
	hcd->state = HC_STATE_SUSPENDED;

	if (urb)
		usb_hcd_giveback_urb (hcd, urb, NULL);
}
EXPORT_SYMBOL_GPL(usb_hcd_suspend_root_hub);

/**
 * usb_hcd_resume_root_hub - called by HCD to resume its root hub 
 * @hcd: host controller for this root hub
 *
 * The USB host controller calls this function when its root hub is
 * suspended (with the remote wakeup feature enabled) and a remote
 * wakeup request is received.  It queues a request for khubd to
 * resume the root hub (that is, manage its downstream ports again).
 */
void usb_hcd_resume_root_hub (struct usb_hcd *hcd)
{
	unsigned long flags;

	spin_lock_irqsave (&hcd_root_hub_lock, flags);
	if (hcd->rh_registered)
		usb_resume_root_hub (hcd->self.root_hub);
	spin_unlock_irqrestore (&hcd_root_hub_lock, flags);
}
EXPORT_SYMBOL_GPL(usb_hcd_resume_root_hub);

#endif

/*-------------------------------------------------------------------------*/

#ifdef	CONFIG_USB_OTG

/**
 * usb_bus_start_enum - start immediate enumeration (for OTG)
 * @bus: the bus (must use hcd framework)
 * @port_num: 1-based number of port; usually bus->otg_port
 * Context: in_interrupt()
 *
 * Starts enumeration, with an immediate reset followed later by
 * khubd identifying and possibly configuring the device.
 * This is needed by OTG controller drivers, where it helps meet
 * HNP protocol timing requirements for starting a port reset.
 */
int usb_bus_start_enum(struct usb_bus *bus, unsigned port_num)
{
	struct usb_hcd		*hcd;
	int			status = -EOPNOTSUPP;

	/* NOTE: since HNP can't start by grabbing the bus's address0_sem,
	 * boards with root hubs hooked up to internal devices (instead of
	 * just the OTG port) may need more attention to resetting...
	 */
	hcd = container_of (bus, struct usb_hcd, self);
	if (port_num && hcd->driver->start_port_reset)
		status = hcd->driver->start_port_reset(hcd, port_num);

	/* run khubd shortly after (first) root port reset finishes;
	 * it may issue others, until at least 50 msecs have passed.
	 */
	if (status == 0)
		mod_timer(&hcd->rh_timer, jiffies + msecs_to_jiffies(10));
	return status;
}
EXPORT_SYMBOL (usb_bus_start_enum);

#endif

/*-------------------------------------------------------------------------*/

/*
 * usb_hcd_operations - adapts usb_bus framework to HCD framework (bus glue)
 */
struct usb_operations usb_hcd_operations = {
	.get_frame_number =	hcd_get_frame_number,
	.submit_urb =		hcd_submit_urb,
	.unlink_urb =		hcd_unlink_urb,
	.buffer_alloc =		hcd_buffer_alloc,
	.buffer_free =		hcd_buffer_free,
	.disable =		hcd_endpoint_disable,
};
EXPORT_SYMBOL (usb_hcd_operations);
/*-------------------------------------------------------------------------*/

/**
 * usb_hcd_giveback_urb - return URB from HCD to device driver
 * @hcd: host controller returning the URB
 * @urb: urb being returned to the USB device driver.
 * @regs: pt_regs, passed down to the URB completion handler
 * Context: in_interrupt()
 *
 * This hands the URB from HCD to its USB device driver, using its
 * completion function.  The HCD has freed all per-urb resources
 * (and is done using urb->hcpriv).  It also released all HCD locks;
 * the device driver won't cause problems if it frees, modifies,
 * or resubmits this URB.
 */
void usb_hcd_giveback_urb (struct usb_hcd *hcd, struct urb *urb, struct pt_regs *regs)
{
	int at_root_hub;

	at_root_hub = (urb->dev == hcd->self.root_hub);
	urb_unlink (urb);

	/* lower level hcd code should use *_dma exclusively */
	if (hcd->self.controller->dma_mask && !at_root_hub) {
		if (usb_pipecontrol (urb->pipe)
			&& !(urb->transfer_flags & URB_NO_SETUP_DMA_MAP))
			dma_unmap_single (hcd->self.controller, urb->setup_dma,
					sizeof (struct usb_ctrlrequest),
					DMA_TO_DEVICE);
		if (urb->transfer_buffer_length != 0
			&& !(urb->transfer_flags & URB_NO_TRANSFER_DMA_MAP))
			dma_unmap_single (hcd->self.controller, 
					urb->transfer_dma,
					urb->transfer_buffer_length,
					usb_pipein (urb->pipe)
					    ? DMA_FROM_DEVICE
					    : DMA_TO_DEVICE);
	}

	usbmon_urb_complete (&hcd->self, urb);
	/* pass ownership to the completion handler */
	urb->complete (urb, regs);
	atomic_dec (&urb->use_count);
	if (unlikely (urb->reject))
		wake_up (&usb_kill_urb_queue);
	usb_put_urb (urb);
}
EXPORT_SYMBOL (usb_hcd_giveback_urb);

/*-------------------------------------------------------------------------*/
#if !defined  (CONFIG_USB_SL2312) && !defined (CONFIG_USB_SL2312_MODULE)
#if !defined  (CONFIG_USB_SL2312_1) && !defined (CONFIG_USB_SL2312_1_MODULE)
/**
 * usb_hcd_irq - hook IRQs to HCD framework (bus glue)
 * @irq: the IRQ being raised
 * @__hcd: pointer to the HCD whose IRQ is being signaled
 * @r: saved hardware registers
 *
 * If the controller isn't HALTed, calls the driver's irq handler.
 * Checks whether the controller is now dead.
 */
irqreturn_t usb_hcd_irq (int irq, void *__hcd, struct pt_regs * r)
{
	struct usb_hcd		*hcd = __hcd;
	int			start = hcd->state;

	if (unlikely(start == HC_STATE_HALT ||
	    !test_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags)))
		return IRQ_NONE;
	if (hcd->driver->irq (hcd, r) == IRQ_NONE)
		return IRQ_NONE;

	set_bit(HCD_FLAG_SAW_IRQ, &hcd->flags);

	if (unlikely(hcd->state == HC_STATE_HALT))
		usb_hc_died (hcd);
	return IRQ_HANDLED;
}
#endif
#endif
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/

void hcd_release (struct usb_bus *bus)
{
	struct usb_hcd *hcd;

	hcd = container_of(bus, struct usb_hcd, self);
	kfree(hcd);
}
EXPORT_SYMBOL(hcd_release);
//---------------------------------------------------------------------------
//Faraday code---------------------------------------------------------------
void hcd_irq (int irq, void *__hcd, struct pt_regs * r)
{
	struct usb_hcd		*hcd = __hcd;
	int			start = hcd->state;

//  DBG_HOST_HCD("### >>> Enter hcd.c file --> hcd_irq function \n");
    
    set_bit(HCD_FLAG_SAW_IRQ, &hcd->flags);
    if (unlikely (hcd->state == HC_STATE_HALT))	/* irq sharing? */
		return;

	hcd->driver->irq (hcd);
	if (hcd->state != start && hcd->state == HC_STATE_HALT)
		hc_died (hcd);
}
EXPORT_SYMBOL (hcd_irq);


int Host_Disconnect_for_OTG(struct usb_bus *bus, unsigned port_num)
{
 struct usb_hcd  *phcd;

        phcd=(struct usb_hcd  *)bus->hcpriv;
	phcd->driver->disconnect_for_OTG (phcd, 0);
        phcd->state =USB_STATE_READY;//This mode is not really suspend for OTG
        return (0);

}
EXPORT_SYMBOL (Host_Disconnect_for_OTG);

//#ifdef CONFIG_USB_SL2312
static int hcd_irq_For_OTG (struct usb_bus	*bus)
{
	struct usb_hcd		*hcd;
	int		start;

//printk("### >>> Enter hcd.c file --> hcd_irq_For_OTG function \n");

//    printk("hcd_irq_For_OTG bus %x\n",bus);
    hcd=(struct usb_hcd		*)(bus->hcpriv);
//    printk("hcd_irq_For_OTG hcd %x\n",hcd);
    start = hcd->state;
	if (unlikely (ghcd_FOTG2XX->state == HC_STATE_HALT))	/* irq sharing? */
		return 0;

//        printk("Go to ehci_irq ghcd_FOTG2xx %x\n",ghcd_FOTG2XX); 
        set_bit(HCD_FLAG_SAW_IRQ, &hcd->flags);
	ghcd_FOTG2XX->driver->irq (ghcd_FOTG2XX);
	if (ghcd_FOTG2XX->state != start && ghcd_FOTG2XX->state == HC_STATE_HALT)
		hc_died (ghcd_FOTG2XX);

  return 0;
}

//static void hcd_irq (int irq, void *__hcd, struct pt_regs *r);
//extern void cpe_int_set_irq(unsigned int irq,int mode,int level);
//extern static int hcd_irq_For_OTG (struct usb_bus	*bus);
int usb_ehcd_FEHCI_probe (const struct hc_driver *driver,
			  struct usb_hcd **hcd_out,
			  struct platform_device *dev)//Input the EHCI Driver pointer
{
//	struct platform_device *pdev = to_platform_device(dev);
//	struct usb_bus		*bus;
//        struct usb_bus          bus;
	struct usb_hcd		*hcd;
    unsigned int	ioaddr ;

    u32 base,val;
    int retval,iType;
    
    iType =1;

//  printk("### >>> Enter hcd.c file --> usb_ehcd_FUSB200_probe function (iType=%d)\n",iType);

  if (iType>1)
      {
      printk("??? usb_ehcd_FEHCI_probe error => iType input error...Halt system...");	
      while(1);	
      }
      
      
      if (dev->resource[1].flags != IORESOURCE_IRQ) {
		pr_debug ("resource[1] is not IORESOURCE_IRQ");
		return -ENOMEM;
	}
	//Step1:Init Interrupt

        //<2.1>Allocate ehci_HCD
//               DBG_HOST_HCD("### >>> driver = 0x%x \n",*driver);               
//	           hcd = driver->hcd_alloc (); //2.4.20
//                   hcd = usb_create_hcd (driver, &dev->dev, "sl2312");  //2.6.15 update to line 1903
                hcd = kzalloc(sizeof(*hcd) + driver->hcd_priv_size, GFP_KERNEL);
	           if (hcd == NULL)
		          {dbg ("hcd alloc fail");
		          }
		 dev_set_drvdata(&dev->dev, hcd);
        //<2.2>.Set Data to HCD
                   usb_bus_init (&hcd->self);
	           hcd->self.op = &usb_hcd_operations;
	           hcd->self.hcpriv = hcd;
	           hcd->self.release = &hcd_release;
	           hcd->self.controller = &dev->dev;
	           printk("hcd->self.controller %x\n",&hcd->self.controller);
//	           printk("hcd->self.hcpriv %x \n",hcd->self.hcpriv);
	           hcd->self.bus_name = "sl2312-otg";
	           init_timer (&hcd->rh_timer);
	           hcd->rh_timer.function = rh_timer_func;
	           hcd->rh_timer.data = (unsigned long) hcd;
       	           hcd->driver = driver;
       	           hcd->product_desc = "sl2312 OTG";
	           hcd->description = driver->description;
	           hcd->irq = IRQ_USB_HOST20;//Use PCI's IRQ
	           hcd->regs =  (void *)IO_ADDRESS(CPE_HOST20_BASE);
                   ioaddr = (unsigned int)hcd->regs;
                   
                  if (!hcd)
		   return -ENOMEM;
		  set_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags); //2.6.15 hcd->flags != SAW_IRQ
		  if (hcd->driver->reset && (retval = hcd->driver->reset(hcd)) < 0) {
	        	dev_err(hcd->self.controller, "can't reset\n");
		        return retval;
         	       } 
		  printk("hcd end\n"); 
                  retval = hcd_buffer_create (hcd);
                  printk("hcd_buffer_create\n");
                  if (!request_mem_region(dev->resource[0].start,
				dev->resource[0].end
				- dev->resource[0].start + 1, "ehci-hcd-FOTG2XX")) {
		pr_debug("request_mem_region failed");
		return -EBUSY;
	        }
                                    
        //<2.3>.Allocate Bus "usb_create_hcd" for 2.6.15

	           usb_register_bus (&hcd->self);
                   printk("usb_register_bus\n");
	           if (iType==0)//Type =1 => FUSBH200
	              {hcd->bus_name = FUSBH200_BusName;
	               hcd->product_desc = FUSBH200_product_desc;
	               ghcd_FUSBH200= hcd;
	              
	          }else if (iType==1)//Type=1 =>OTG
	                  {hcd->bus_name = FOTG200_BusName;
	                   hcd->product_desc = FOTG200_product_desc;
	                   ghcd_FOTG2XX= hcd;
	                   printk("ghcd_FOTG2XX hcd %x\n",ghcd_FOTG2XX);
//                           hcd->bus->hcd_isr=hcd_irq_For_OTG;
                           hcd->self.hcd_isr=hcd_irq_For_OTG;
                           printk("hcd_irq_For_OTG\n");
	                  }
 

         //<2.4>.Assign IRQ
//               DBG_HOST_HCD("###  //<3.2>.Assign IRQ\n");    

              if (iType==0)//
                 {
	          // if (request_irq (IRQ_USB_HOST20, hcd_irq, SA_SHIRQ, hcd->description, hcd)!= 0) 
		  //        {dbg ("request_irq fail");
		  //        }		    	
                 
                 
                }else if (iType==1)//Type=1 =>OTG
                         {
//                          DBG_HOST_HCD("###  //<3.2>.Assign IRQ\n");  
	                      base = IO_ADDRESS((CPE_HOST20_BASE+0x0c4)); 
  	                      val = inl(base);             
//                          DBG_HOST_HCD("### @@@ Initial CPE_HOST20_BASE+0x0c4 = 0x%x\n",val);
  	                      outl((val | 0x08),base);   
  	                      val = inl(base);             
//                          DBG_HOST_HCD("### @@@ Initial CPE_HOST20_BASE+0x0c4 = 0x%x\n",val);                 	
                         
                         }
			
         //<2.5>.Init Others
//               DBG_HOST_HCD("###  //<2.5>.Init Others\n");    
//	           INIT_LIST_HEAD (&hcd->dev_list);
	           INIT_LIST_HEAD (&hcd->hcd_list);

//            	down (&hcd_list_lock);
//            	list_add (&hcd->hcd_list, &hcd_list);
//            	up (&hcd_list_lock);
            
//	            usb_register_bus (&bus);
   
      //Step3:driver->start
//               DBG_HOST_HCD("###  //<3.4>.driver->start (hcd)\n");    
	           if ((driver->start (hcd)) < 0)
	           	{dbg ("Enter ehci-hcd file --> init function");	
	           	 }


              if (iType==0)
                 {
	           if (request_irq (IRQ_USB_HOST20, hcd_irq, SA_SHIRQ, hcd->description, hcd)!= 0) 
		          {dbg ("request_irq fail");
		          }		    	
                 
                 
                }
                *hcd_out = hcd;
      return retval;
                
// err2:
	hcd_buffer_destroy (hcd);
 //err1:
	kfree(hcd);
//	sl2312_stop_hc(dev);
	release_mem_region(dev->resource[0].start,
				dev->resource[0].end
			   - dev->resource[0].start + 1);
	return retval;



}
EXPORT_SYMBOL (usb_ehcd_FEHCI_probe);
//#else
//#ifdef CONFIG_USB_SL2312_1
static int hcd_irq_For_OTG_1 (struct usb_bus	*bus)
{
	struct usb_hcd		*hcd;
	int		start;

//printk("### >>> Enter hcd.c file --> hcd_irq_For_OTG_1 function \n");

//    printk("hcd_irq_For_OTG_1 bus %x\n",bus);
    hcd=(struct usb_hcd		*)(bus->hcpriv);
//    printk("hcd_irq_For_OTG_1 hcd %x\n",hcd);
    start = hcd->state;
	if (unlikely (ghcd_FOTG2XX_1->state == HC_STATE_HALT))	/* irq sharing? */
		return 0;

//        printk("Go to ehci_irq ghcd_FOTG2XX_1 %x\n",ghcd_FOTG2XX_1); 
        set_bit(HCD_FLAG_SAW_IRQ, &hcd->flags);
	ghcd_FOTG2XX_1->driver->irq (ghcd_FOTG2XX_1);
	if (ghcd_FOTG2XX_1->state != start && ghcd_FOTG2XX_1->state == HC_STATE_HALT)
		hc_died (ghcd_FOTG2XX_1);

  return 0;
}

int usb_ehcd_FEHCI_probe_1 (const struct hc_driver *driver,
			  struct usb_hcd **hcd_out,
			  struct platform_device *dev)//Input the EHCI Driver pointer
{
//	struct platform_device *pdev = to_platform_device(dev);
//	struct usb_bus		*bus;
//        struct usb_bus          bus;
	struct usb_hcd		*hcd;
    unsigned int	ioaddr ;

    u32 base,val;
    int retval,iType;
    
    iType =1;

//  printk("### >>> Enter hcd.c file --> usb_ehcd_FUSB200_probe function (iType=%d)\n",iType);

  if (iType>1)
      {
      printk("??? usb_ehcd_FEHCI_probe_1 error => iType input error...Halt system...");	
      while(1);	
      }
      
      
      if (dev->resource[1].flags != IORESOURCE_IRQ) {
		pr_debug ("resource[1] is not IORESOURCE_IRQ");
		return -ENOMEM;
	}
	//Step1:Init Interrupt

        //<2.1>Allocate ehci_HCD
//               DBG_HOST_HCD("### >>> driver = 0x%x \n",*driver);               
//	           hcd = driver->hcd_alloc (); //2.4.20
//                   hcd = usb_create_hcd (driver, &dev->dev, "sl2312");  //2.6.15 update to line 1903
                hcd = kzalloc(sizeof(*hcd) + driver->hcd_priv_size, GFP_KERNEL);
	           if (hcd == NULL)
		          {dbg ("hcd alloc fail");
		          }
		 dev_set_drvdata(&dev->dev, hcd);
        //<2.2>.Set Data to HCD
                   usb_bus_init (&hcd->self);
	           hcd->self.op = &usb_hcd_operations;
	           hcd->self.hcpriv = hcd;
	           hcd->self.release = &hcd_release;
	           hcd->self.controller = &dev->dev;
	           printk("hcd->self.controller %x\n",&hcd->self.controller);
//	           printk("hcd->self.hcpriv %x \n",hcd->self.hcpriv);
	           hcd->self.bus_name = "sl2312-otg";
	           init_timer (&hcd->rh_timer);
	           hcd->rh_timer.function = rh_timer_func;
	           hcd->rh_timer.data = (unsigned long) hcd;
       	           hcd->driver = driver;
       	           hcd->product_desc = "sl2312 OTG";
	           hcd->description = driver->description;
	           hcd->irq = IRQ_USB_HOST20_1;//Use PCI's IRQ
	           hcd->regs =  (void *)IO_ADDRESS(CPE_HOST20_BASE_1);
                   ioaddr = (unsigned int)hcd->regs;
                   
                  if (!hcd)
		   return -ENOMEM;
		  set_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags); //2.6.15 hcd->flags != SAW_IRQ
		  if (hcd->driver->reset && (retval = hcd->driver->reset(hcd)) < 0) {
	        	dev_err(hcd->self.controller, "can't reset\n");
		        return retval;
         	       } 
		  printk("hcd end\n"); 
                  retval = hcd_buffer_create (hcd);
                  printk("hcd_buffer_create\n");
                  if (!request_mem_region(dev->resource[0].start,
				dev->resource[0].end
				- dev->resource[0].start + 1, "ehci-hcd-FOTG2XX-1")) {
		pr_debug("request_mem_region failed");
		return -EBUSY;
	        }
                                    
        //<2.3>.Allocate Bus "usb_create_hcd" for 2.6.15

	           usb_register_bus (&hcd->self);
                   printk("usb_register_bus\n");
	           if (iType==0)//Type =1 => FUSBH200
	              {hcd->bus_name = FUSBH200_BusName;
	               hcd->product_desc = FUSBH200_product_desc;
	               ghcd_FUSBH200_1= hcd;
	              
	          }else if (iType==1)//Type=1 =>OTG
	                  {hcd->bus_name = FOTG200_BusName;
	                   hcd->product_desc = FOTG200_product_desc;
	                   ghcd_FOTG2XX_1= hcd;
	                   printk("ghcd_FOTG2XX_1 hcd %x\n",ghcd_FOTG2XX_1);
//                           hcd->bus->hcd_isr=hcd_irq_For_OTG;
                           hcd->self.hcd_isr=hcd_irq_For_OTG_1;
                           printk("hcd_irq_For_OTG_1\n");
	                  }
 

         //<2.4>.Assign IRQ
//               DBG_HOST_HCD("###  //<3.2>.Assign IRQ\n");    

              if (iType==0)//
                 {
	          // if (request_irq (IRQ_USB_HOST20, hcd_irq, SA_SHIRQ, hcd->description, hcd)!= 0) 
		  //        {dbg ("request_irq fail");
		  //        }		    	
                 
                 
                }else if (iType==1)//Type=1 =>OTG
                         {
//                          DBG_HOST_HCD("###  //<3.2>.Assign IRQ\n");  
	                      base = IO_ADDRESS((CPE_HOST20_BASE_1+0x0c4)); 
  	                      val = inl(base);             
//                          DBG_HOST_HCD("### @@@ Initial CPE_HOST20_BASE+0x0c4 = 0x%x\n",val);
  	                      outl((val | 0x08),base);   
  	                      val = inl(base);             
//                          DBG_HOST_HCD("### @@@ Initial CPE_HOST20_BASE+0x0c4 = 0x%x\n",val);                 	
                         
                         }
			
         //<2.5>.Init Others
//               DBG_HOST_HCD("###  //<2.5>.Init Others\n");    
//	           INIT_LIST_HEAD (&hcd->dev_list);
	           INIT_LIST_HEAD (&hcd->hcd_list);

//            	down (&hcd_list_lock);
//            	list_add (&hcd->hcd_list, &hcd_list);
//            	up (&hcd_list_lock);
            
//	            usb_register_bus (&bus);
   
      //Step3:driver->start
//               DBG_HOST_HCD("###  //<3.4>.driver->start (hcd)\n");    
	           if ((driver->start (hcd)) < 0)
	           	{dbg ("Enter ehci-hcd file --> init function");	
	           	 }


              if (iType==0)
                 {
	           if (request_irq (IRQ_USB_HOST20_1, hcd_irq, SA_SHIRQ, hcd->description, hcd)!= 0) 
		          {dbg ("request_irq fail");
		          }		    	
                 
                 
                }
                 *hcd_out = hcd;
      return retval;
                
// err2:
	hcd_buffer_destroy (hcd);
 //err1:
	kfree(hcd);
//	sl2312_stop_hc(dev);
	release_mem_region(dev->resource[0].start,
				dev->resource[0].end
			   - dev->resource[0].start + 1);
	return retval;



}
EXPORT_SYMBOL (usb_ehcd_FEHCI_probe_1);
//#endif  /#ifdef CONFIG_USB_SL2312_1
//#endif //#ifdef CONFIG_USB_SL2312

//Faraday code end---------------------------------------------------------------
/**
 * usb_create_hcd - create and initialize an HCD structure
 * @driver: HC driver that will use this hcd
 * @dev: device for this HC, stored in hcd->self.controller
 * @bus_name: value to store in hcd->self.bus_name
 * Context: !in_interrupt()
 *
 * Allocate a struct usb_hcd, with extra space at the end for the
 * HC driver's private data.  Initialize the generic members of the
 * hcd structure.
 *
 * If memory is unavailable, returns NULL.
 */
struct usb_hcd *usb_create_hcd (const struct hc_driver *driver,
		struct device *dev, char *bus_name)
{
	struct usb_hcd *hcd;

	hcd = kzalloc(sizeof(*hcd) + driver->hcd_priv_size, GFP_KERNEL);
	if (!hcd) {
		dev_dbg (dev, "hcd alloc failed\n");
		return NULL;
	}
	dev_set_drvdata(dev, hcd);

	usb_bus_init(&hcd->self);
	hcd->self.op = &usb_hcd_operations;
	hcd->self.hcpriv = hcd;
	hcd->self.release = &hcd_release;
	hcd->self.controller = dev;
	hcd->self.bus_name = bus_name;

	init_timer(&hcd->rh_timer);
	hcd->rh_timer.function = rh_timer_func;
	hcd->rh_timer.data = (unsigned long) hcd;

	hcd->driver = driver;
	hcd->product_desc = (driver->product_desc) ? driver->product_desc :
			"USB Host Controller";

	return hcd;
}
EXPORT_SYMBOL (usb_create_hcd);

void usb_put_hcd (struct usb_hcd *hcd)
{
	dev_set_drvdata(hcd->self.controller, NULL);
	usb_bus_put(&hcd->self);
}
EXPORT_SYMBOL (usb_put_hcd);


#if !defined  (CONFIG_USB_SL2312) && !defined (CONFIG_USB_SL2312_MODULE)
#if !defined  (CONFIG_USB_SL2312_1) && !defined (CONFIG_USB_SL2312_1_MODULE)
/**
 * usb_add_hcd - finish generic HCD structure initialization and register
 * @hcd: the usb_hcd structure to initialize
 * @irqnum: Interrupt line to allocate
 * @irqflags: Interrupt type flags
 *
 * Finish the remaining parts of generic HCD initialization: allocate the
 * buffers of consistent memory, register the bus, request the IRQ line,
 * and call the driver's reset() and start() routines.
 */
int usb_add_hcd(struct usb_hcd *hcd,
		unsigned int irqnum, unsigned long irqflags)
{
	int retval;
	struct usb_device *rhdev;

	dev_info(hcd->self.controller, "%s\n", hcd->product_desc);

	set_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags);

	/* till now HC has been in an indeterminate state ... */
	if (hcd->driver->reset && (retval = hcd->driver->reset(hcd)) < 0) {
		dev_err(hcd->self.controller, "can't reset\n");
		return retval;
	}

	if ((retval = hcd_buffer_create(hcd)) != 0) {
		dev_dbg(hcd->self.controller, "pool alloc failed\n");
		return retval;
	}

	if ((retval = usb_register_bus(&hcd->self)) < 0)
		goto err_register_bus;

	if (hcd->driver->irq) {
		char	buf[8], *bufp = buf;

#ifdef __sparc__
		bufp = __irq_itoa(irqnum);
#else
		sprintf(buf, "%d", irqnum);
#endif

		snprintf(hcd->irq_descr, sizeof(hcd->irq_descr), "%s:usb%d",
				hcd->driver->description, hcd->self.busnum);
		if ((retval = request_irq(irqnum, &usb_hcd_irq, irqflags,
				hcd->irq_descr, hcd)) != 0) {
			dev_err(hcd->self.controller,
					"request interrupt %s failed\n", bufp);
			goto err_request_irq;
		}
		hcd->irq = irqnum;
		dev_info(hcd->self.controller, "irq %s, %s 0x%08llx\n", bufp,
				(hcd->driver->flags & HCD_MEMORY) ?
					"io mem" : "io base",
					(unsigned long long)hcd->rsrc_start);
	} else {
		hcd->irq = -1;
		if (hcd->rsrc_start)
			dev_info(hcd->self.controller, "%s 0x%08llx\n",
					(hcd->driver->flags & HCD_MEMORY) ?
					"io mem" : "io base",
					(unsigned long long)hcd->rsrc_start);
	}

	/* Allocate the root hub before calling hcd->driver->start(),
	 * but don't register it until afterward so that the hardware
	 * is running.
	 */
	if ((rhdev = usb_alloc_dev(NULL, &hcd->self, 0)) == NULL) {
		dev_err(hcd->self.controller, "unable to allocate root hub\n");
		retval = -ENOMEM;
		goto err_allocate_root_hub;
	}
	rhdev->speed = (hcd->driver->flags & HCD_USB2) ? USB_SPEED_HIGH :
			USB_SPEED_FULL;

	/* Although in principle hcd->driver->start() might need to use rhdev,
	 * none of the current drivers do.
	 */
	if ((retval = hcd->driver->start(hcd)) < 0) {
		dev_err(hcd->self.controller, "startup error %d\n", retval);
		goto err_hcd_driver_start;
	}

	/* hcd->driver->start() reported can_wakeup, probably with
	 * assistance from board's boot firmware.
	 * NOTE:  normal devices won't enable wakeup by default.
	 */
	if (hcd->can_wakeup)
		dev_dbg(hcd->self.controller, "supports USB remote wakeup\n");
	hcd->remote_wakeup = hcd->can_wakeup;

	if ((retval = register_root_hub(rhdev, hcd)) != 0)
		goto err_register_root_hub;

	if (hcd->uses_new_polling && hcd->poll_rh)
		usb_hcd_poll_rh_status(hcd);
	return retval;

 err_register_root_hub:
	hcd->driver->stop(hcd);

 err_hcd_driver_start:
	usb_put_dev(rhdev);

 err_allocate_root_hub:
	if (hcd->irq >= 0)
		free_irq(irqnum, hcd);

 err_request_irq:
	usb_deregister_bus(&hcd->self);

 err_register_bus:
	hcd_buffer_destroy(hcd);
	return retval;
} 
EXPORT_SYMBOL (usb_add_hcd);
#endif
#endif
/**
 * usb_remove_hcd - shutdown processing for generic HCDs
 * @hcd: the usb_hcd structure to remove
 * Context: !in_interrupt()
 *
 * Disconnects the root hub, then reverses the effects of usb_add_hcd(),
 * invoking the HCD's stop() method.
 */
void usb_remove_hcd(struct usb_hcd *hcd)
{
	dev_info(hcd->self.controller, "remove, state %x\n", hcd->state);

	if (HC_IS_RUNNING (hcd->state))
		hcd->state = HC_STATE_QUIESCING;

	dev_dbg(hcd->self.controller, "roothub graceful disconnect\n");
	spin_lock_irq (&hcd_root_hub_lock);
	hcd->rh_registered = 0;
	spin_unlock_irq (&hcd_root_hub_lock);
	usb_disconnect(&hcd->self.root_hub);

	hcd->poll_rh = 0;
	del_timer_sync(&hcd->rh_timer);

	hcd->driver->stop(hcd);
	hcd->state = HC_STATE_HALT;

	if (hcd->irq >= 0)
		free_irq(hcd->irq, hcd);
	usb_deregister_bus(&hcd->self);
	hcd_buffer_destroy(hcd);
}
EXPORT_SYMBOL (usb_remove_hcd);

/*-------------------------------------------------------------------------*/

#if defined(CONFIG_USB_MON)

struct usb_mon_operations *mon_ops;

/*
 * The registration is unlocked.
 * We do it this way because we do not want to lock in hot paths.
 *
 * Notice that the code is minimally error-proof. Because usbmon needs
 * symbols from usbcore, usbcore gets referenced and cannot be unloaded first.
 */
 
int usb_mon_register (struct usb_mon_operations *ops)
{

	if (mon_ops)
		return -EBUSY;

	mon_ops = ops;
	mb();
	return 0;
}
EXPORT_SYMBOL_GPL (usb_mon_register);

void usb_mon_deregister (void)
{

	if (mon_ops == NULL) {
		printk(KERN_ERR "USB: monitor was not registered\n");
		return;
	}
	mon_ops = NULL;
	mb();
}
EXPORT_SYMBOL_GPL (usb_mon_deregister);

#endif /* CONFIG_USB_MON */
