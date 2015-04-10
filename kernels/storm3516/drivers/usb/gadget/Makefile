#
# USB peripheral controller drivers
#
obj-$(CONFIG_USB_DUMMY_HCD)	+= dummy_hcd.o
obj-$(CONFIG_USB_NET2280)	+= net2280.o
obj-$(CONFIG_USB_PXA2XX)	+= pxa2xx_udc.o
obj-$(CONFIG_USB_GOKU)		+= goku_udc.o
obj-$(CONFIG_USB_OMAP)		+= omap_udc.o
obj-$(CONFIG_USB_LH7A40X)	+= lh7a40x_udc.o
#obj-$(CONFIG_USB_GADGET_SL2312)        += FTC_FOTG200_udc.o 
obj-$(CONFIG_USB_GADGET_SL2312_1)        += FTC_FOTG200_udc_1.o 

#
# USB gadget drivers
#
ifeq ($(CONFIG_USB_GADGET_SL2312_1),y)
g_zero-objs			:= FTC_zero.o 
else
g_zero-objs			:= zero.o usbstring.o config.o epautoconf.o
endif
g_ether-objs			:= ether.o usbstring.o config.o epautoconf.o
g_serial-objs			:= serial.o usbstring.o config.o epautoconf.o
gadgetfs-objs			:= inode.o
ifeq ($(CONFIG_USB_GADGET_SL2312_1),y)
g_file_storage-objs		:= file_storage.o usbstring.o config.o epautoconf.o
else
g_file_storage-objs		:= file_storage.o usbstring.o config.o \
					epautoconf.o
endif

ifeq ($(CONFIG_USB_ETH_RNDIS),y)
	g_ether-objs		+= rndis.o
endif
 
obj-$(CONFIG_USB_ZERO)		+= g_zero.o
obj-$(CONFIG_USB_ETH)		+= g_ether.o
obj-$(CONFIG_USB_GADGETFS)	+= gadgetfs.o
obj-$(CONFIG_USB_FILE_STORAGE)	+= g_file_storage.o
obj-$(CONFIG_USB_G_SERIAL)	+= g_serial.o

