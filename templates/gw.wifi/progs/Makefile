# vi: set sw=4 ts=4:
#
# Makefile for elbox's template.
#

-include path.mk
-include arch.mk
-include $(TOPDIR)/.config
MYNAME:=Gateway With Wifi
#####################################################################
# check for some special cases
ifeq ($(strip $(ELBOX_PROGS_PRIV_MADWIFI_EWC)),y)
	HALTDEMAND_SH:=scripts/haltdemand.sh.ewc
else
	HALTDEMAND_SH:=scripts/haltdemand.sh
endif

DEFAULT_NODES := S20setnodes.php S22setext.sh S20upnp_igd.sh

ifeq ($(strip $(CONFIG_UPNPKITS_WFADEV)),y)
DEFAULT_NODES += S21upnp_wfa.sh
endif

ifeq ($(strip $(ELBOX_CREATE_LANGUAGE_PACK)),y)
DEFAULT_NODES += S23langpack.sh
endif

#hendry 
ifeq ($(strip $(ELBOX_PROGS_GPL_BUSYBOX_1_00_ADVANCED_CONFIG)),y)
CONFIG_FILE = busybox-1.00.advanced.config
else
CONFIG_FILE = busybox-1.00.config
endif

			
#####################################################################
# targets for main Makefile

# build template dependent programs
all:
	@echo -e "\033[32mBuilding template related programs for $(MYNAME) ...\033[0m"

# install template dependent programs
install: uclibc
	@echo -e "\033[32mInstalling template related programs for $(MYNAME) ...\033[0m"
	$(Q)make -C templates install
	$(Q)make -C htdocs install
	$(Q)[ -d $(TARGET)/etc/scripts ] || mkdir -p $(TARGET)/etc/scripts
	$(Q)[ -d $(TARGET)/etc/scripts/misc ] || mkdir -p $(TARGET)/etc/scripts/misc
	$(Q)[ -d $(TARGET)/etc/init.d ] || mkdir -p $(TARGET)/etc/init.d
	$(Q)cp scripts/system.sh			$(TARGET)/etc/scripts/.
	$(Q)cp scripts/preupgrade.sh		$(TARGET)/etc/scripts/misc/.
ifeq ($(strip $(ELBOX_PROGS_PRIV_MADWIFI_EWC)),)
	$(Q)cp scripts/haltdemand.sh		$(TARGET)/etc/scripts/misc/.
else
	$(Q)cp scripts/haltdemand.sh.ewc	$(TARGET)/etc/scripts/misc/haltdemand.sh
endif
	$(Q)ln -sf /etc/scripts/system.sh	$(TARGET)/etc/init.d/S10system.sh

# clean template dependent programs
clean:
	@echo -e "\033[32mCleaning template related programs for $(MYNAME) ...\033[0m"

# setup template dependent program configuration
prepare:
	@echo -e "\033[32mPreparing configuration for template - $(MYNAME) ...\033[0m"
ifeq ($(strip $(ELBOX_PROGS_GPL_BUSYBOX_1_11_1)),y)
	@make bb_setup_1_11_1
else
	@make bb_setup V=$(V) DEBUG=$(DEBUG)
endif

# build template dependent rootfs
rootfs:
	@echo -e "\033[32mCreate rootfs for template - $(MYNAME) ...\033[0m"
	$(Q)cp -rf defnodes $(TARGET)/etc/.

.PHONY: all install clean prepare rootfs

#####################################################################

bb_setup:
	@echo -e "\033[32mSetup busybox v1.00 configuration ...\033[0m"
	$(Q)cp $(CONFIG_FILE) .tmp
ifeq ($(strip $(BUSYBOX_CC_PREFIX)),)
	$(Q)sed -e 's|@@CROSS_COMPILER@@|$(TPATH_UC)/bin/$(CROSS_COMPILE)|' .tmp > .tmp1
else
	$(Q)sed -e 's|@@CROSS_COMPILER@@|$(BUSYBOX_CC_PREFIX)|' .tmp > .tmp1
endif
	$(Q)sed -e 's|@@TARGET@@|$(TARGET)|' .tmp1 > $(TOPDIR)/progs.gpl/busybox-1.00/.config
	$(Q)rm -f .tmp .tmp1
	$(Q)make -C $(TOPDIR)/progs.gpl/busybox-1.00 oldconfig

bb_setup_1_11_1:
	@echo -e "\033[32mSetup busybox v1.11.1 configuration ...\033[0m"
	$(Q)cp busybox-1.11.1.config .tmp
	$(Q)sed -e 's|@@CROSS_COMPILER@@|$(TPATH_UC)/bin/$(CROSS_COMPILE)|' .tmp > .tmp1
	$(Q)sed -e 's|@@TARGET@@|$(TARGET)|' .tmp1 > $(TOPDIR)/progs.gpl/busybox-1.11.1/.config
	$(Q)rm -f .tmp .tmp1
	$(Q)make -C $(TOPDIR)/progs.gpl/busybox-1.11.1 oldconfig
	

uclibc:
	@echo -e "\033[32mInstalling uClibc ...\033[0m"
	$(Q)[ -d $(TARGET)/lib ] || mkdir -p $(TARGET)/lib
	@# ld-uClibc.so.0
	$(Q)cp -f $(CC_PATH)/lib/ld-uClibc.so.0	$(TARGET)/lib/.
	@# libc.so libc.so.0
	$(Q)cp -f $(CC_PATH)/lib/libc.so.0		$(TARGET)/lib/.
	$(Q)[ ! -f $(TARGET)/lib/libc.so ] || rm -f $(TARGET)/lib/libc.so
	$(Q)ln -s libc.so.0						$(TARGET)/lib/libc.so
	@# libcrypt.so libcrypt.so.0
	$(Q)cp -f $(CC_PATH)/lib/libcrypt.so.0	$(TARGET)/lib/.
	$(Q)[ ! -f $(TARGET)/lib/libcrypt.so ] || rm -f $(TARGET)/lib/libcrypt.so
	$(Q)ln -s libcrypt.so.0					$(TARGET)/lib/libcrypt.so
	@# libdl.so libdl.so.0
	$(Q)cp -f $(CC_PATH)/lib/libdl.so.0		$(TARGET)/lib/.
	$(Q)[ ! -f $(TARGET)/lib/libdl.so ] || rm -f $(TARGET)/lib/libdl.so
	$(Q)ln -s libdl.so.0					$(TARGET)/lib/libdl.so
	@# libm.so libm.so.0
	$(Q)cp -f $(CC_PATH)/lib/libm.so.0		$(TARGET)/lib/.
	$(Q)[ ! -f $(TARGET)/lib/libm.so ] || rm -f $(TARGET)/lib/libm.so
	$(Q)ln -s libm.so.0						$(TARGET)/lib/libm.so
	@# libnsl.so libnsl.so.0
	$(Q)cp -f $(CC_PATH)/lib/libnsl.so.0	$(TARGET)/lib/.
	$(Q)[ ! -f $(TARGET)/lib/libnsl.so ] || rm -f $(TARGET)/lib/libnsl.so
	$(Q)ln -s libnsl.so.0					$(TARGET)/lib/libnsl.so
	@# libresolv.so libresolv.so.0
	$(Q)cp -f $(CC_PATH)/lib/libresolv.so.0	$(TARGET)/lib/.
	$(Q)[ ! -f $(TARGET)/lib/libresolv.so ] || rm -f $(TARGET)/lib/libresolv.so
	$(Q)ln -s libresolv.so.0				$(TARGET)/lib/libresolv.so
ifeq ($(strip $(ELBOX_INSTALL_LIBGCC_A_SO)),y)
	@# libgcc_s.so libgcc_s.so.1
	$(Q)cp -f $(CC_PATH)/lib/libgcc_s.so.1	$(TARGET)/lib/.
	$(Q)[ ! -f $(TARGET)/lib/libgcc_s.so ] || rm -f $(TARGET)/lib/libgcc_s.so
	$(Q)ln -s libgcc_s.so.1					$(TARGET)/lib/libgcc_s.so
endif

.PHONY: bb_setup bb_setup_1_11_1 uclibc
