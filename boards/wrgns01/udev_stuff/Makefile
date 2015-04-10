-include ../arch.mk
-include ../path.mk

APPLET		:= mnt_dev
LOCAL_SRCS	:= mnt_dev.c
CMLIB_SRCS	:= 
CPLUS_SRCS	:=

OTHER_TARGETS := umnt_dev usb_printer_hotplug sata_hotplug

-include $(TOPDIR)/Rules.mk

install:
	@echo -e "\033[32mInstalling mnt_dev ...\033[0m"
	$(Q)[ -d $(TARGET)/usr/sbin ] || mkdir -p $(TARGET)/usr/sbin
	$(Q)cp $(APPLET) $(TARGET)/usr/sbin/.
	$(Q)cp $(OTHER_TARGETS) $(TARGET)/usr/sbin/.
	$(Q)chmod +x $(TARGET)/usr/sbin/$(APPLET)
	$(Q)chmod +x $(TARGET)/usr/sbin/$(OTHER_TARGETS)
	$(Q)[ -d $(TARGET)/lib/modules ] || mkdir -p $(TARGET)/lib/modules
	$(Q)cp ufsd.ko $(TARGET)/lib/modules/.
	$(Q)[ -d $(TARGET)/etc/udev/rules.d ] || mkdir -p $(TARGET)/etc/udev/rules.d
	$(Q)cp 00-me.rules $(TARGET)/etc/udev/rules.d/.
	if test ! -s "$(TARGET)/sys"; \
	then $(Q)mkdir $(TARGET)/sys;\
	fi
#	hendry add for ext3 journal
	ln -s /proc/mounts $(TARGET)/etc/mtab

clean:
	-rm -f $(APPLET) $(OTHER_TARGETS) *.elf *.gdb *.o .depend

