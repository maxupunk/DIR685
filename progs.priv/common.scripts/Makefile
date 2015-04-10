#

-include ../arch.mk
-include ../../path.mk
-include ../../.config

all:

install:
	@echo -e "\033[32mInstall common scripts ...\033[0m"
	$(Q)[ -d $(TARGET)/etc/scripts/misc ] || mkdir $(TARGET)/etc/scripts/misc
	$(Q)cp nreboot.sh		$(TARGET)/etc/scripts/misc/.
	$(Q)cp defnodes.sh		$(TARGET)/etc/scripts/misc/.
	$(Q)cp ver.sh			$(TARGET)/etc/scripts/misc/.
	$(Q)cp freset.sh		$(TARGET)/etc/scripts/misc/.
	$(Q)cp rcS				$(TARGET)/etc/init.d/.
ifeq ($(strip $(CONFIG_RGBIN_DEVCONF)),y)
	$(Q)cp profile.devconf.sh	$(TARGET)/etc/scripts/misc/profile.sh
else
	$(Q)cp profile.sh			$(TARGET)/etc/scripts/misc/.
endif


ifeq ($(strip $(ELBOX_PROGS_GPL_TELNETD_GET_DATABASE)),y)
	@sed -e "s/@@USERNAME@@/\`rgdb -g \/sys\/user:1\/name\`/g" -e "s/@@PASSWORD@@/\`rgdb -g \/sys\/user:1\/password\`/g" telnetd_database.sh > telnetd.tmp

ifeq ($(strip $(ELBOX_PROGS_PRIV_CLI)),y)
		@sed -e "s/@@SHELL@@/-s \"-l\/usr\/sbin\/cli\" -t 0/g" ./telnetd.tmp > $(TARGET)/etc/scripts/misc/telnetd.sh
endif 

	rm -f telnetd.tmp
	chmod 755 $(TARGET)/etc/scripts/misc/telnetd.sh
else 
#	$(Q)cp telnetd.sh		$(TARGET)/etc/scripts/misc/.
endif

ifeq ($(strip $(ELBOX_PROGS_PRIV_COMMON_SCRIPTS_3G_PLUG_AND_PLAY)),y)
	$(Q)cp plugplay.sh		$(TARGET)/etc/scripts/misc/.
endif

ifeq ($(strip $(ELBOX_PROGS_PRIV_COMMON_SCRIPTS_UDEV_USB_3G_HOTPLUG)),y)
	$(Q)cp usb3ghotplug.sh		$(TARGET)/etc/scripts/misc/.
endif

clean:

.PHONY: all install clean
