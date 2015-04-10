# vi: set sw=4 ts=4:
####################################################################################
#
# Makefile for wpstools in elbox
#
# by david_hsieh@alphanetworks.com
#
####################################################################################
USE_BRCM_TOOLS?=n
-include ../../path.mk
-include ../arch.mk
-include ../../.config

####################################################################################

MYNAME		:= wpstools
CURRDIR		:= $(shell pwd)
HOSTAPDDIR	:= hostapd
WPSDIR		:= wps

# The following exports are for openssl.
export TOOLPREFIX=$(Q)$(CROSS_COMPILE)
ifeq ($(strip $(CONFIG_WPSTOOLS_BIG_ENDIAN)),y)
export CONFIG_OPENSSL_B_ENDIAN=y
endif

##################################################################################
ifeq ($(strip $(CONFIG_WPSTOOLS_USE_SHARED_OPENSSL)),y)
all: hostapd wps
clean:
#clean: wps_clean hostapd_clean
else
OPENSSLDIR	:= openssl-0.9.8a
all: openssl hostapd wps
clean:
#clean: wps_clean hostapd_clean openssl_clean
endif

.PHONY: all clean

##########################################################################

openssl:
	@echo -e "\033[32mBuilding openssl library ...\033[0m"
	$(Q)cd $(OPENSSLDIR); make

openssl_clean:
	@echo -e "\033[32mCleaning openssl library ...\033[0m"
	$(Q)cd $(OPENSSLDIR); make clean

##########################################################################

hostapd:
	@echo -e "\033[32mBuilding hostapd program ...\033[0m"
	$(Q)cd $(HOSTAPDDIR); make V=$(V)

hostapd_clean:
	@echo -e "\033[32mCleaning hostapd program ...\033[0m"
	$(Q)cd $(HOSTAPDDIR); make clean V=$(V)

##########################################################################

wps:
	@echo -e "\033[32mBuilding wps program ...\033[0m"
	$(Q)cd $(WPSDIR); make V=$(V)

wps_clean:
	@echo -e "\033[32mCleaning wps program ...\033[0m"
	$(Q)cd $(WPSDIR); make clean V=$(V)

.PHONY: openssl openssl_clean hostapd hostapd_clean wps wps_clean

##########################################################################

install:
	@echo -e "\033[32mInstall $(MYNAME) ...\033[0m"
ifneq ($(strip $(CONFIG_WPSTOOLS_DISABLE_HOSTAPD)),y)
	$(Q)make -C $(HOSTAPDDIR) install V=$(V)
endif
	$(Q)make -C $(WPSDIR) install V=$(V)

.PHONY: install

##########################################################################
