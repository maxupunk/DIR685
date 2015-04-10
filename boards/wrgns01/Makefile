#
# Makefile for board related.
#

-include arch.mk
-include path.mk
-include .config

SCRIPTS_DIR:=$(TARGET)/etc/scripts

# target for main Makefile
MYNAME:=WRG-N15

# build board dependent programs
all:
#	@echo -e "\033[32mBuilding board releated programs for $(MYNAME) ...\033[0m"
	$(Q)make -C apps
	$(Q)make -C udev_stuff
#	$(Q)make -C emulate_keyborad
#	$(Q)make -C i2c
	$(Q)make -C DFB
# install board dependent programs
install:
	@echo -e "\033[32mInstalling board related program for $(MYNAME) ...\033[0m"
	$(Q)[ -d $(SCRIPTS_DIR) ] || mkdir -p $(SCRIPTS_DIR)
	$(Q)[ -d $(SCRIPTS_DIR)/misc ] || mkdir -p $(SCRIPTS_DIR)/misc
	$(Q)[ -d $(TARGET)/etc/init.d ] || mkdir -p $(TARGET)/etc/init.d
	$(Q)cp scripts/config.sh		$(SCRIPTS_DIR)/.
	$(Q)cp scripts/layout.sh		$(SCRIPTS_DIR)/.
	$(Q)cp scripts/layout_run.php	$(SCRIPTS_DIR)/.
	$(Q)cp scripts/layout_gzone_run.php	$(TARGET)/etc/scripts/.
	$(Q)cp scripts/layout_gzone.sh	$(TARGET)/etc/scripts/.
#sam_pan add 
	$(Q)cp scripts/network_usb.sh  $(TARGET)/etc/scripts/.
	$(Q)cp scripts/enlan.sh			$(SCRIPTS_DIR)/.
	$(Q)cp scripts/dislan.sh		$(SCRIPTS_DIR)/.
	$(Q)chmod +x					$(SCRIPTS_DIR)/*.sh
	$(Q)ln -sf /etc/scripts/config.sh $(TARGET)/etc/init.d/S03config.sh
	$(Q)cp scripts/cabletest:?		$(TARGET)/usr/sbin/.
	$(Q)cp scripts/switch			$(TARGET)/usr/sbin/.
	$(Q)cp scripts/setwantype.sh	$(SCRIPTS_DIR)/misc/.
	$(Q)cp scripts/startburning.sh	$(SCRIPTS_DIR)/.
	$(Q)make -C apps install
	$(Q)make -C templates install
	$(Q)make -C udev_stuff install
	$(Q)cp lib/*	$(TARGET)/lib/.
#+++Teresa, for auth login
	$(Q)ln -s /var/auth/auth_img $(TARGET)/www/auth_img
#	$(Q)make -C emulate_keyborad install
#	$(Q)make -C i2c install
	$(Q)make -C DFB install
# clean board dependent programs
clean:
#	@echo -e "\033[32mCleaning board related programs for $(MYNAME) ...\033[0m"
	$(Q)make -C apps clean
	$(Q)make -C udev_stuff clean
	$(Q)make -C DFB clean
prepare:
	@echo -e "\033[32mPreparing configuration for board - $(MYNAME) ...\033[0m"

# build board dependent rootfs
rootfs:
	@echo -e "\033[32mCreate rootfs for board - $(MYNAME) ...\033[0m"
	$(Q)echo "/dev/mtdblock/2" >> $(TARGET)/etc/config/rgdb
	$(Q)echo "/dev/mtdblock/3" >> $(TARGET)/etc/config/nvram
	$(Q)echo "/dev/mtdblock/5" >> $(TARGET)/etc/config/langpack
	$(Q)cp -rf defnodes $(TARGET)/etc/.

.PHONY: all install clean prepare rootfs
