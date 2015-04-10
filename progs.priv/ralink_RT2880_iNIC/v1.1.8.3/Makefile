#
# Makefile for Ralink ewc driver.
#
#

include ../../arch.mk
include ../../../path.mk
include ../../../.config

#############################################################################


ifeq ($(strip $(ELBOX_PROGS_PRIV_RALINK_INIC_RT2880_1183)),y)
REVISION	?=2008_1110
TARBALL		:=$(REVISION)_RT2880_iNIC_v1.1.8.3.tar.bz2
TARNAME		:=$(REVISION)_RT2880_Linux_SoftAP_v1.1.8.3
REATEPATH	:= $(basename)/QA_ATE
endif
#REDRVPATH	:= $(basename)/Module
#REAPDPATH	:= $(basename)/802.1X
#REUPNPPATH	:= $(basename)/WSC_UPNP
#REDRVPATH	:= module
REDRVPATH 	:= module-v1.1.8.3
REAPDPATH	:= 802.1X
REUPNPPATH	:= wsc_upnp
REWPASUPPPATH :=wpa-supplicant
#############################################################################

Q	?= @
CURRDIR := $(shell pwd)
BDIR	:= build/
MODS	:= $(BDIR)bin
SRC		:= $(CURRDIR)/sources
DRVPATH	:= $(CURRDIR)/$(BDIR)$(REDRVPATH)
APDPATH := $(CURRDIR)/$(BDIR)$(REAPDPATH)
WPSSTR	:= $(DRVPATH)/include/wps_str.h
UPNPPATH := $(CURRDIR)/$(BDIR)$(REUPNPPATH)
SUPP:= $(CURRDIR)/$(BDIR)$(REWPASUPPPATH)
MYNAME	:= Ralink RT2860 ewc driver
PATCH	:= alpha.$(REVISION).diff
DECOMPRESS	:= tar xfvz
FIRM_SRC := $(SRC)/iNIC_firmware
FIRM_DST := $(BDIR)/module-v1.1.8.3/firmware
iNIC_FW := iNIC_ap_eapol_bypass20090310.bin

#############################################################################

all: prepare_source driver_build rt2860apd_build wsc_upnp_build
	@echo -e "\033[32mBuilding Ralink ewc driver ...\033[0m"
	
my_build: driver_build rt2860apd_build wsc_upnp_build

my_clean: driver_clean rt2860apd_clean wsc_upnp_clean

showconfig:
	@echo -e "\033[32msource tarball : \033[33m$(TARBALL)\033[0m"
	@echo -e "\033[32mpatch file     : \033[33m$(PATCH)\033[0m"
ifeq ($(BDIR), $(wildcard $(BDIR)))
	@echo -e "\033[32msource is prepared.\033[0m"
else
	@echo -e "\033[32msource is not ready.\033[0m"
endif

clean:
	$(Q) make -C $(DRVPATH) clean
	$(Q) make -C $(APDPATH) clean
	$(Q) make -C $(UPNPPATH) clean
	$(Q) make -C $(SUPP) clean
#	$(Q)rm -rf $(BDIR)
#	$(Q)rm -rf $(MODS)

	
ifeq ($(BDIR), $(wildcard $(BDIR)))
prepare_source:
else
prepare_source: 
	@echo -e "\033[32mPreparing the source code for  $(MYNAME)\033[0m"
	$(Q) if [ -d $(BDIR) ]; then rm -rf $(BDIR); fi
ifeq ($(strip $(ELBOX_PROGS_PRIV_RALINK_INIC_RT2880_1183)),y)
	$(Q) mkdir $(BDIR)
	$(Q) cd $(BDIR) && $(DECOMPRESS) $(SRC)/$(TARBALL) 
endif
	$(Q) patch -p0 < $(SRC)/$(PATCH)
	$(Q) cp $(FIRM_SRC)/*.bin $(FIRM_DST)/
#	$(Q)echo "#define WSC_MANUFACTURE \"$(ELBOX_PROGS_PRIV_RALINK_WPS_MANUFACTURE_NAME)\"" > $(WPSSTR)
#	$(Q)echo "#define WSC_MODEL_NAME \"$(ELBOX_PROGS_PRIV_RALINK_WPS_MODEL_NAME)\""		>> $(WPSSTR)
#	$(Q)echo "#define WSC_MODEL_NUMBER \"$(ELBOX_PROGS_PRIV_RALINK_WPS_MODEL_NUMBER)\""	>> $(WPSSTR)
#	$(Q)echo "#define WSC_MODEL_SERIAL \"$(ELBOX_PROGS_PRIV_RALINK_WPS_MODEL_SERIAL)\""	>> $(WPSSTR)
#	$(Q)echo "#define WSC_DEVICE_NAME \"$(ELBOX_PROGS_PRIV_RALINK_WPS_DEVICE_NAME)\""	>> $(WPSSTR)
endif

diff: driver_clean rt2860apd_clean wsc_upnp_clean
	@echo -e "\033[32mGenerating diff file ...\033[0m"
	$(Q)if [ -d org ]; then rm -rf org; fi
	$(Q)if [ -d $(MODS) ]; then rm -rf $(MODS); fi

ifeq ($(strip $(ELBOX_PROGS_PRIV_RALINK_INIC_RT2880_1183)),y)
	$(Q)mkdir org
	$(Q)cd org && $(DECOMPRESS) $(SRC)/$(TARBALL)
	$(Q)rm -rf $(UPNPPATH)/libupnp-1.3.1
	$(Q)mv org/wsc_upnp/libupnp-1.3.1 .
endif
#	$(Q)rm -f $(WPSSTR)
	$(Q)./mkdiff org $(BDIR) > sources/$(PATCH)
#	$(Q)echo "#define WSC_MANUFACTURE \"$(ELBOX_PROGS_PRIV_RALINK_WPS_MANUFACTURE_NAME)\"" > $(WPSSTR)
#	$(Q)echo "#define WSC_MODEL_NAME \"$(ELBOX_PROGS_PRIV_RALINK_WPS_MODEL_NAME)\""		>> $(WPSSTR)
#	$(Q)echo "#define WSC_MODEL_NUMBER \"$(ELBOX_PROGS_PRIV_RALINK_WPS_MODEL_NUMBER)\""	>> $(WPSSTR)
#	$(Q)echo "#define WSC_MODEL_SERIAL \"$(ELBOX_PROGS_PRIV_RALINK_WPS_MODEL_SERIAL)\""	>> $(WPSSTR)
#	$(Q)echo "#define WSC_DEVICE_NAME \"$(ELBOX_PROGS_PRIV_RALINK_WPS_DEVICE_NAME)\""	>> $(WPSSTR)

	$(Q)mv libupnp-1.3.1 $(UPNPPATH)/.
	$(Q)rm -rf org 

.PHONY: all showconfig clean prepare_source diff

driver_build:
	@echo -e "\033[32mBuild driver ..\033[0m"
	$(Q)cd $(DRVPATH) && make V=1

rt2860apd_build:
	@echo -e "\033[32mBuild 802.1X Authenticator..\033[0m"
	$(Q)cd $(APDPATH) && make
	$(Q)cd $(SUPP) && make
wsc_upnp_build:
	@echo -e "\033[32mBuild WSC_UPNP ...\033[0m"
	$(Q)cd $(UPNPPATH) && make

driver_clean:
	@echo -e "\033[32mClean driver ..\033[0m"
	$(Q)cd $(DRVPATH) && make clean

rt2860apd_clean:
	@echo -e "\033[32mClean 802.1X Authenticator..\033[0m"
	$(Q)cd $(APDPATH) && make clean

wsc_upnp_clean:
	@echo -e "\033[32mClean WSC_UPNP ..\033[0m"
	$(Q)cd $(UPNPPATH) && make cleanall

.PHONY: driver_build driver_clean

strip_target:
	@echo -e "\033[32mStripping target objects ...\033[0m"
	$(Q)if [ -d $(MODS) ]; then rm -rf $(MODS); fi
	$(Q)mkdir $(MODS)
	@echo -e "\033[32m...$(CURRDIR)/$(BDIR) ...\033[0m"
	$(Q)cp $(DRVPATH)/os/linux/rt2860ap.ko	$(MODS)/.
#	$(Q)$(STRIP) -g $(MODS)/*.ko
	$(Q)cp $(APDPATH)/rt2860apd				$(MODS)/.
	$(Q)cp $(UPNPPATH)/wscd					$(MODS)/.
	$(Q)cp -r $(UPNPPATH)/xml					$(MODS)/.

#install: strip_target
install: 
	@echo -e "\033[32mInstalling Ralink ewc driver ...\033[0m"
	@echo -e "\033[32mCopy driver to $(TARGET)/lib/modules\033[0m"
	$(Q)[ -d $(TARGET)/lib/modules ] || mkdir -p $(TARGET)/lib/modules
#	$(Q)cp $(MODS)/*.ko						$(TARGET)/lib/modules
#	$(Q)cp $(MODS)/rt2860apd				$(TARGET)/usr/sbin
#	$(Q)cp $(MODS)/wscd						$(TARGET)/usr/sbin
#	$(Q)cp -r $(MODS)/xml					$(TARGET)/etc/templates/wsc_upnp_xml
	$(Q)cp $(DRVPATH)/rt2880_iNIC.ko	$(TARGET)/lib/modules
	$(Q)cp $(APDPATH)/rt2880apd				$(TARGET)/usr/sbin
	$(Q)cp $(UPNPPATH)/wscd							$(TARGET)/usr/sbin
	$(Q)cp -r $(UPNPPATH)/xml		$(TARGET)/etc/templates/wsc_upnp_xml
	if test ! -d  $(TARGET)/etc/Wireless/RT2880/; \
	then mkdir -p $(TARGET)/etc/Wireless/RT2880/;\
	fi
	$(Q)cp $(DRVPATH)/firmware/$(iNIC_FW) 	$(TARGET)/etc/Wireless/RT2880/iNIC_ap.bin
#	$(Q)cp $(DRVPATH)/firmware/iNIC_ap.bin     $(TARGET)/etc/Wireless/RT2880/iNIC_ap.bin
	[-f /var/run] || mkdir -p $(TARGET)/var/run
	$(Q)ln -s /var/run/RT2880AP.dat 		$(TARGET)/etc/Wireless/RT2880/iNIC_ap.dat 
#	mkdir -p $(TARGET)/var/run
#	$(Q)cp -f $(DRVPATH)/firmware/iNIC_ap.dat	$(TARGET)/var/.
	if test ! -d $(TARGET)/etc/xml/;\
	then mkdir -p $(TARGET)/etc/xml/;\
	fi
	$(Q)cp $(UPNPPATH)/xml/*.xml	 	$(TARGET)/etc/xml/.
#	$(Q)cp module/firmware/iNIC_sta.bin	$(TARGET)/etc/Wireless/RT2880/.
#	$(Q)cp module/firmware/iNIC_sta.dat 	$(TARGET)/etc/Wireless/RT2880/.
.PHONY: strip_target install

