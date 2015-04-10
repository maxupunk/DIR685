#
# Makefile for WRG-N15, board dependents
#

##############################################################################

-include ../arch.mk
-include ../path.mk
-include ../customer.mk
-include ../../../kernel/.config
##############################################################################
# source files

APPLET		:= fresetd
LOCAL_SRCS	:= fresetd.c
CMLIB_SRCS	:= sloop.c dtrace.c unixsock.c libxmldbc.c
CPLUS_SRCS	:=

OTHER_TARGETS:= subdirs
ifeq ($(strip $(CUSTOMER_DUSA)),y)
NETWORK_USB := deviceserver-1.1.2 
else
NETWORK_USB := kcode
endif
APPSSUBDIRS := get_device_name nat_cfg reboot hdparm smartmontools nas_gpio_access ntfsprogs sata_driver ssignal e2fsprogs $(NETWORK_USB) wol 
#for bt corp. process
APPSSUBDIRS +=  bittorrent-sdk-dir685-v2_0

CFLAGS += -DSLOOP_USR_GETTIMEOFDAY -DDEBUG_SLOOP=0 -I$(TOPDIR)/kernel

include $(TOPDIR)/progs.board/customer.mk
ifdef SWITCH_MODULE
ifdef CHIP_RTL8366SR
eror not support 8366sr module
else
APPSSUBDIRS += rtl8366/rtl8366rb
endif
endif

ifdef CHIP_RTL8366SR
else
CFLAGS += -DRTL8366RB
endif

##############################################################################
# flags to turn on debug mode

ifeq ($(strip $(DEBUG)),y)
DDEBUG:=y
DDEBUG_LEVEL:=0
endif

ifeq ($(strip $(DDEBUG)),y)
CFLAGS += -DDDEBUG
ifdef DDEBUG_LEVEL
CFLAGS += -DDBG_DEFAULT=$(DDEBUG_LEVEL)
endif
endif

##############################################################################

-include $(TOPDIR)/Rules.mk

.PHONY: all install clean freset_install

install: freset_install
	@echo -e "\033[32mInstalling board dependent apps ...\033[0m"
	$(Q)cp fresetd $(TARGET)/usr/sbin/.
	$(Q)cp mfc $(TARGET)/usr/sbin/.
	$(Q)for i in $(APPSSUBDIRS); do make -C $$i install ; done 
ifeq "$(strip $(CONFIG_USB_SL2312))" "m"
	make -C $(KERNELDIR) modules
	cp $(KERNELDIR)/drivers/usb/host/ehci-hcd-FOTG2XX-1.ko $(TARGET)/lib/modules/.
	cp $(KERNELDIR)/drivers/usb/host/ehci-hcd-FOTG2XX.ko $(TARGET)/lib/modules/.
	cp restart_usb $(TARGET)/usr/sbin/.
	chmod 777  $(TARGET)/usr/sbin/restart_usb
endif

freset_install:
	@echo -e "\033[32mInstalling freset related programs ...\033[0m"
	$(Q)$(STRIP) fresetd	
	$(Q)cp fresetd $(TARGET)/usr/sbin/.
	$(Q)[ ! -f $(TARGET)/usr/sbin/ctest ] || rm -f $(TARGET)/usr/sbin/ctest
	$(Q)ln -s fresetd $(TARGET)/usr/sbin/ctest
	$(Q)[ ! -f $(TARGET)/usr/sbin/psts ] || rm -f $(TARGET)/usr/sbin/psts
	$(Q)ln -s fresetd $(TARGET)/usr/sbin/psts
	$(Q)[ ! -f $(TARGET)/usr/sbin/slinktype ] || rm -f $(TARGET)/usr/sbin/slinktype
	$(Q)ln -s fresetd $(TARGET)/usr/sbin/slinktype
	$(Q)[ ! -f $(TARGET)/usr/sbin/ptmod ] || rm -f $(TARGET)/usr/sbin/ptmod
	$(Q)ln -s fresetd $(TARGET)/usr/sbin/ptmod
	$(Q)[ ! -f $(TARGET)/usr/sbin/gether ] || rm -f $(TARGET)/usr/sbin/gether
	$(Q)ln -s fresetd $(TARGET)/usr/sbin/gether

clean: clean_objs
	@echo -e "\033[32mCleaning board dependent apps ...\033[0m"
	$(Q)for i in $(APPSSUBDIRS); do make -C $$i clean ; done 

##############################################################################

#KERNEL_FLAGS = $(KCFLAGS) -I$(KERNELDIR)/include -I$(KERNELDIR)/arch/mips/ar531x
subdirs:
	@echo -e "\033[32mBuilding programs in sub-directories ...\033[0m"
	$(Q)for i in $(APPSSUBDIRS); do make -C $$i ; done 

.PHONY: subdirs

##############################################################################

uclibc:
	@echo -e "\033[32mInstalling pthread library ...\033[0m"
	@# libpthread.so.0
	$(Q)cp -f $(CC_PATH)/lib/libpthread.so.0	$(TARGET)/lib/.
	$(Q)[ ! -f $(TARGET)/lib/libpthread.so ] || rm -f $(TARGET)/lib/libpthread.so
	$(Q)ln -s libpthread.so.0					$(TARGET)/lib/libpthread.so

.PHONY: uclibc
