#
# Makefile for USB Core files and filesystem
#

ifeq ($(CONFIG_USB_SL2312),y)
usbcore-objs	:= usb_FEHCI.o hub_FEHCI.o hcd_FEHCI.o urb.o message.o \
			config.o file.o buffer.o sysfs.o devio.o notify.o
else
ifeq ($(CONFIG_USB_SL2312_1),y)
usbcore-objs	:= usb_FEHCI.o hub_FEHCI.o hcd_FEHCI.o urb.o message.o \
			config.o file.o buffer.o sysfs.o devio.o notify.o
else
ifeq ($(CONFIG_USB_SL2312),m)
usbcore-objs	:= usb_FEHCI.o hub_FEHCI.o hcd_FEHCI.o urb.o message.o \
			config.o file.o buffer.o sysfs.o devio.o notify.o
else
ifeq ($(CONFIG_USB_SL2312_1),m)
usbcore-objs	:= usb_FEHCI.o hub_FEHCI.o hcd_FEHCI.o urb.o message.o \
			config.o file.o buffer.o sysfs.o devio.o notify.o
else
usbcore-objs	:= usb.o hub.o hcd.o urb.o message.o \
			config.o file.o buffer.o sysfs.o devio.o notify.o


ifeq ($(CONFIG_PCI),y)
	usbcore-objs	+= hcd-pci.o
endif
endif
endif
endif
endif

ifeq ($(CONFIG_USB_DEVICEFS),y)
	usbcore-objs	+= inode.o devices.o
endif

obj-$(CONFIG_USB)	+= usbcore.o

ifeq ($(CONFIG_USB_DEBUG),y)
EXTRA_CFLAGS += -DDEBUG
endif
