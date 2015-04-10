# vi: set sw=4 ts=4:
#####################################################################
#
# Makefile for hostapd - Wifi Simple Config implementation.
#
#####################################################################

-include ../../arch.mk
-include ../../../path.mk
-include ../../../.config

#####################################################################
# This config file is for hostapd.wps WPS implementation.
#-include .config

# WPA2/IEEE 802.11i RSN pre-authentication
CONFIG_RSN_PREAUTH:=y
# Integrated EAP server
CONFIG_EAP:=y
# Wifi Protected Setup for the integrated EAP authenticator
CONFIG_EAP_WPS:=y
# Supports new WPS IEs
CONFIG_WPS_IE:=y

ifeq ($(strip $(CONFIG_WPSTOOLS_RADIUS_SERVER_ON_BOARD)),y)
ifeq ($(strip $(CONFIG_WPSTOOLS_USE_SHARED_OPENSSL)),y)
LDFLAGS += -lssl -lcrypto -L$(OPENSSLDIR)
endif
CONFIG_EAP_PEAP:=y
CONFIG_EAP_TTLS:=y
CONFIG_EAP_TLS:=y
CONFIG_EAP_MSCHAPV2:=y
CONFIG_PKCS12:=y
endif

#####################################################################
# The following config is used in hostapd by includeing <elbox_config.h>
# Added by Enos, <2008/01/30>
# 1. ELBOX_PROGS_GPL_SYSLOGD_AP      : Log Message for AP security
# 2. ELBOX_PROGS_PRIV_WLAN_ALPHA_WDS : Hostapd support WDS, the major function is simply used as log message.
# 3. CONFIG_WPSTOOLS_ALPHA_BACKUP_RADIUS_SERVER : Use the new backup radius server rule.
# 4. CONFIG_WPSTOOLS_RADIUS_SERVER_ON_BOARD : Enable the internal radius server support

######################################################################
# dtrace debug
ifeq ($(strip $(DEBUG)),y)
DDEBUG=y
DDEBUG_LEVEL=0
endif

ifeq ($(strip $(DDEBUG)),y)
CFLAGS += -DDDEBUG
ifdef DDEBUG_LEVEL
CFLAGS += -DDBG_DEFAULT=$(DDEBUG_LEVEL)
endif
else
CFLAGS += -DCONFIG_NO_STDOUT_DEBUG=y
endif

#####################################################################

APPLET		:= hostapd
LOCAL_SRCS	:= hostapd.c eloop.c ieee802_1x.c eapol_sm.c radius.c md5.c rc4.c \
				common.c ieee802_11.c config.c ieee802_11_auth.c accounting.c \
				sta_info.c radius_client.c sha1.c wpa.c aes_wrap.c driver_conf.c \
				eap.c eap_identity.c
CMLIB_SRCS	:= dtrace.c # libxmldbc.o
CPLUS_SRCS	:=

#####################################################################

ifndef CFLAGS
CFLAGS = -MMD -O2 -Wall -D_BYTE_ORDER=_BIG_ENDIAN -g
endif

ifeq ($(strip $(CONFIG_WPSTOOLS_ALPHA_UNSUPPORT_PRAGMA_PACK)),y)
CFLAGS += -DUNSUPP_PRAGMA_PACK
endif

# define HOSTAPD_DUMP_STATE to include SIGUSR1 handler for dumping state to
# a file (undefine it, if you want to save in binary size)
#CFLAGS += -DHOSTAPD_DUMP_STATE

# Include directories for CVS version
CFLAGS += -I $(TOPDIR)/include

# Driver configuration

ifeq ($(strip $(ELBOX_PROGS_PRIV_BROADCOM_WIFI)),y)
# Driver interface for bcm5354
CONFIG_DRIVER_BROADCOM:=y
CFLAGS += -DCONFIG_DRIVER_BROADCOM
CFLAGS += -I$(TOPDIR)/kernel/broadcom_rc/include
LOCAL_SRCS += driver_broadcom.c
CONFIG_L2_PACKET:=y
endif

ifeq ($(strip $(ELBOX_PROGS_PRIV_MADWIFI_520112)),y)
CONFIG_DRIVER_MADWIFI:=y
CFLAGS += -DCONFIG_DRIVER_MADWIFI
CFLAGS += -I$(TOPDIR)/progs.priv/madwifi.LSDK-WLAN5.2.0.112/build/src/802_11/madwifi/madwifi
LOCAL_SRCS += driver_madwifi.c
CONFIG_L2_PACKET:=y
endif

ifeq ($(strip $(ELBOX_PROGS_PRIV_MADWIFI_53145)),y)
CONFIG_DRIVER_MADWIFI:=y
CFLAGS += -DCONFIG_DRIVER_MADWIFI
CFLAGS += -I$(TOPDIR)/progs.priv/madwifi.LSDK-WLAN5.3.1.45/build/src/802_11/madwifi/madwifi
LOCAL_SRCS += driver_madwifi.c
CONFIG_L2_PACKET:=y
endif


ifeq ($(strip $(ELBOX_BOARD_WMXRG01E)),y)
CONFIG_DRIVER_MADWIFI:=y
CFLAGS += -DCONFIG_DRIVER_MADWIFI
CFLAGS += -I$(TOPDIR)/progs.board/apps/wireless/build/src/802_11/madwifi/madwifi
LOCAL_SRCS += driver_madwifi.c
CONFIG_L2_PACKET:=y
endif

ifeq ($(strip $(ELBOX_PROGS_PRIV_MADWIFI_AP83)),y)
CONFIG_DRIVER_MADWIFI:=y
CFLAGS += -DCONFIG_DRIVER_MADWIFI
CFLAGS += -D_BYTE_ORDER=_BIG_ENDIAN
CFLAGS += -I$(TOPDIR)/progs.priv/madwifi_ap83/_build/wlan
CFLAGS += -I$(TOPDIR)/progs.priv/madwifi_ap83/_build/wlan/linux
LOCAL_SRCS += driver_madwifi.c
CONFIG_L2_PACKET:=y
endif

ifeq ($(strip $(ELBOX_PROGS_PRIV_MADWIFI_CAVIUM)),y)
CONFIG_DRIVER_MADWIFI:=y
CFLAGS += -DCONFIG_DRIVER_MADWIFI
CFLAGS += -D_BYTE_ORDER=_BIG_ENDIAN
#CFLAGS += -I$(TOPDIR)/progs.priv/madwifi_cavium/_build/wlan/madwifi/madwifi
CFLAGS += -I$(TOPDIR)/progs.priv/madwifi_cavium/_build/wlan/core
LOCAL_SRCS += driver_madwifi.c
CONFIG_L2_PACKET:=y
endif

ifeq ($(strip $(ELBOX_PROGS_PRIV_MADWIFI_FUSION_CAVIUM)),y)
CONFIG_DRIVER_MADWIFI:=y
CFLAGS += -DCONFIG_DRIVER_MADWIFI
CFLAGS += -D_BYTE_ORDER=_BIG_ENDIAN
CFLAGS += -I$(TOPDIR)/progs.priv/madwifi_fusion_cavium/_build/wlan/linux
CFLAGS += -I$(TOPDIR)/progs.priv/madwifi_fusion_cavium/_build/wlan
LOCAL_SRCS += driver_madwifi.c
CONFIG_L2_PACKET:=y
endif

ifeq ($(strip $(ELBOX_PROGS_PRIV_RT2860V2)),y)
CONFIG_DRIVER_RALINK:=y
CFLAGS += -DCONFIG_DRIVER_RALINK
CFLAGS += -I$(TOPDIR)/progs.priv/rt2860v2/build/rt2860v2/os/linux
LOCAL_SRCS += driver_ralink.c
CONFIG_L2_PACKET:=y
endif

ifeq ($(strip $(ELBOX_PROGS_PRIV_RT2860V2_V1900)),y)
CONFIG_DRIVER_RALINK:=y
CFLAGS += -DCONFIG_DRIVER_RALINK
CFLAGS += -DWPA_IE_CAPABILITIES_NOT_INCLUDED
CFLAGS += -I$(TOPDIR)/progs.priv/rt2860v2/build/rt2860v2/os/linux
LOCAL_SRCS += driver_ralink.c
CONFIG_L2_PACKET:=y
endif

ifeq ($(strip $(ELBOX_PROGS_PRIV_RT2860V2_V3200)),y)
CONFIG_DRIVER_RALINK:=y
CFLAGS += -DCONFIG_DRIVER_RALINK
CFLAGS += -DWPA_IE_CAPABILITIES_NOT_INCLUDED
CFLAGS += -I$(TOPDIR)/progs.priv/rt2860v2/build/rt2860v2/os/linux
LOCAL_SRCS += driver_ralink.c
CONFIG_L2_PACKET:=y
endif

ifeq ($(strip $(ELBOX_PROGS_PRIV_RALINK_INIC_RT2880_1183)),y)
CONFIG_DRIVER_RALINK:=y
CFLAGS += -DCONFIG_DRIVER_RALINK 
CFLAGS += -DWPA_IE_CAPABILITIES_NOT_INCLUDED
CFLAGS += -DREVERSE_ENCRYP_IN_WPA_IE
CFLAGS += -I$(TOPDIR)/progs.priv/ralink_RT2880_iNIC/v1.1.8.3/build/module-v1.1.8.3/comm
LOCAL_SRCS += driver_ralink_inic.c
CONFIG_L2_PACKET:=y
endif

#ifdef CONFIG_EAP
#CFLAGS += -DEAP_SERVER
#LOCAL_SRCS += eap.c eap_identity.c
#endif

ifdef CONFIG_IAPP
CFLAGS += -DCONFIG_IAPP
LOCAL_SRCS += iapp.c
endif

ifdef CONFIG_RSN_PREAUTH
CFLAGS += -DCONFIG_RSN_PREAUTH
CONFIG_L2_PACKET:=y
endif

ifdef CONFIG_DRIVER_HOSTAP
CFLAGS += -DCONFIG_DRIVER_HOSTAP
LOCAL_SRCS += driver.c
endif

ifdef CONFIG_DRIVER_WIRED
CFLAGS += -DCONFIG_DRIVER_WIRED
LOCAL_SRCS += driver_wired.c
endif

ifdef CONFIG_DRIVER_PRISM54
CFLAGS += -DCONFIG_DRIVER_PRISM54
LOCAL_SRCS += driver_prism54.c
endif

ifdef CONFIG_DRIVER_BSD
CFLAGS += -DCONFIG_DRIVER_BSD
OBJS += driver_bsd.o
CONFIG_L2_PACKET:=y
CONFIG_DNET_PCAP:=y
CONFIG_L2_FREEBSD:=y
endif

ifdef CONFIG_DRIVER_TEST
CFLAGS += -DCONFIG_DRIVER_TEST
LOCAL_SRCS += driver_test.c
endif

ifdef CONFIG_L2_PACKET
ifdef CONFIG_DNET_PCAP
CFLAGS += -DUSE_DNET_PCAP
ifdef CONFIG_L2_FREEBSD
LIBS += -lpcap
LOCAL_SRCS += l2_packet_freebsd.c
else
LIBS += -ldnet -lpcap
LOCAL_SRCS += l2_packet_pcap.c
endif
else
LOCAL_SRCS += l2_packet_linux.c
endif
endif


ifdef CONFIG_EAP_MD5
CFLAGS += -DEAP_MD5
LOCAL_SRCS += eap_md5.c
endif

ifdef CONFIG_EAP_TLS
CFLAGS += -DEAP_TLS
LOCAL_SRCS += eap_tls.c
TLS_FUNCS=y
endif

ifdef CONFIG_EAP_PEAP
CFLAGS += -DEAP_PEAP
LOCAL_SRCS += eap_peap.c
TLS_FUNCS=y
CONFIG_EAP_TLV=y
CONFIG_EAP_MSCHAPV2=y
endif

ifdef CONFIG_EAP_TTLS
CFLAGS += -DEAP_TTLS
LOCAL_SRCS += eap_ttls.c
TLS_FUNCS=y
endif

ifdef CONFIG_EAP_MSCHAPV2
CFLAGS += -DEAP_MSCHAPv2
LOCAL_SRCS += eap_mschapv2.c
MS_FUNCS=y
endif

ifdef CONFIG_EAP_GTC
CFLAGS += -DEAP_GTC
LOCAL_SRCS += eap_gtc.c
endif

ifdef CONFIG_EAP_SIM
CFLAGS += -DEAP_SIM
LOCAL_SRCS += eap_sim.c eap_sim_common.c
# Example EAP-SIM interface for GSM authentication. This can be replaced with
# another file implementating the interface specified in eap_sim_db.h.
LOCAL_SRCS += eap_sim_db.c
endif

ifdef CONFIG_EAP_PAX
CFLAGS += -DEAP_PAX
LOCAL_SRCS += eap_pax.c eap_pax_common.c
endif

ifdef CONFIG_EAP_PSK
CFLAGS += -DEAP_PSK
LOCAL_SRCS += eap_psk.c eap_psk_common.c
endif

ifdef CONFIG_EAP_TLV
CFLAGS += -DEAP_TLV
LOCAL_SRCS += eap_tlv.c
endif

ifdef TLS_FUNCS
# Shared TLS functions (needed for EAP_TLS, EAP_PEAP, and EAP_TTLS)
CFLAGS += -DEAP_TLS_FUNCS
LOCAL_SRCS += eap_tls_common.c tls_openssl.c
LIBS += -lcrypto
LIBS_p += -lcrypto
REQUIRE_OPENSSL=y
endif

ifdef CONFIG_PKCS12
CFLAGS += -DPKCS12_FUNCS
endif

ifdef MS_FUNCS
ifndef TLS_FUNCS
LIBS += -lcrypto
endif
LOCAL_SRCS += ms_funcs.c crypto.c
endif

ifdef CONFIG_RADIUS_SERVER
CFLAGS += -DRADIUS_SERVER
LOCAL_SRCS += radius_server.c
endif

ifdef CONFIG_IPV6
CFLAGS += -DCONFIG_IPV6
endif

ifdef CONFIG_EAP_WPS
CFLAGS += -DEAP_WPS
LOCAL_SRCS += eap_wps.c
LIBS += -lcrypto
REQUIRE_OPENSSL=y
REQUIRE_UNIXSOCK=y
endif

ifdef CONFIG_WPS_IE
CFLAGS += -DWPS_NEW_IE -DLISTEN_PROBE_REQUEST
LOCAL_SRCS += wps_ie.c
REQUIRE_UNIXSOCK=y
endif

ifdef REQUIRE_OPENSSL
ifeq ($(strip $(CONFIG_WPSTOOLS_USE_SHARED_OPENSSL)),y)
CFLAGS += -I$(OPENSSLDIR)/include
LIBS += -lssl -L$(OPENSSLDIR)
else
CFLAGS += -I../openssl-0.9.8a/include
#LIBS += -lssl -L../openssl-0.9.8a
endif
endif

ifdef REQUIRE_UNIXSOCK
CMLIB_SRCS += unixsock.c
endif

ifeq ($(strip $(ELBOX_PROGS_PRIV_CAPWAP)),y)
CMLIB_SRCS += libxmldbc.c
endif

-include $(TOPDIR)/Rules.mk

showconfig:
	@echo -e "\033[32mLOCAL_SRCS : \033[0m$(LOCAL_SRCS)"
	@echo -e "\033[32mCMLIB_SRCS : \033[0m$(CPLUS_SRCS)"
	@echo -e "\033[32mCMLIB_SRCS : \033[0m$(CMLIB_SRCS)"

driver_conf.c: Makefile .config
	$(Q)rm -f driver_conf.c
	$(Q)echo '/* THIS FILE AUTOMATICALLY GENERATED, DO NOT EDIT! */' > driver_conf.c
	$(Q)echo '#include <stdlib.h>'		>> driver_conf.c
	$(Q)echo '#include <stdio.h>'		>> driver_conf.c
	$(Q)echo '#include <sys/types.h>'	>> driver_conf.c
	$(Q)echo '#include <netinet/in.h>'	>> driver_conf.c
	$(Q)echo '#include "hostapd.h"'		>> driver_conf.c
	$(Q)echo '#include "driver.h"'		>> driver_conf.c
ifdef CONFIG_DRIVER_HOSTAP
	$(Q)echo "void hostap_driver_register(void);"	>> driver_conf.c
endif
ifdef CONFIG_DRIVER_WIRED
	$(Q)echo "void wired_driver_register(void);"	>> driver_conf.c
endif
ifdef CONFIG_DRIVER_MADWIFI
	$(Q)echo "void madwifi_driver_register(void);"	>> driver_conf.c
endif
ifdef CONFIG_DRIVER_PRISM54
	$(Q)echo "void prism54_driver_register(void);"	>> driver_conf.c
endif
ifdef CONFIG_DRIVER_BSD
	$(Q)echo "void bsd_driver_register(void);"		>> driver_conf.c
endif
ifdef CONFIG_DRIVER_TEST
	$(Q)echo "void test_driver_register(void);"		>> driver_conf.c
endif
ifdef CONFIG_DRIVER_BROADCOM
	$(Q)echo "void broadcom_driver_register(void);"	>> driver_conf.c
endif
ifdef CONFIG_DRIVER_RALINK
	$(Q)echo "void ralink_driver_register(void);"	>> driver_conf.c
endif

	$(Q)echo 'void register_drivers(void) {'	>> driver_conf.c
ifdef CONFIG_DRIVER_HOSTAP
	$(Q)echo "hostap_driver_register();"		>> driver_conf.c
endif
ifdef CONFIG_DRIVER_WIRED
	$(Q)echo "wired_driver_register();"			>> driver_conf.c
endif
ifdef CONFIG_DRIVER_MADWIFI
	$(Q)echo "madwifi_driver_register();"		>> driver_conf.c
endif
ifdef CONFIG_DRIVER_PRISM54
	$(Q)echo "prism54_driver_register();"		>> driver_conf.c
endif
ifdef CONFIG_DRIVER_BSD
	$(Q)echo "bsd_driver_register();"			>> driver_conf.c
endif
ifdef CONFIG_DRIVER_TEST
	$(Q)echo "test_driver_register();"			>> driver_conf.c
endif
ifdef CONFIG_DRIVER_BROADCOM
	$(Q)echo "broadcom_driver_register();"		>> driver_conf.c
endif
ifdef CONFIG_DRIVER_RALINK
	$(Q)echo "ralink_driver_register();"		>> driver_conf.c
endif
	$(Q)echo '}'						>> driver_conf.c

clean: clean_objs
	$(Q)rm -f core *~ *.o hostapd hostapd_cli *.d driver_conf.c

install:
	@echo -e "\033[32mInstall hostapd ...\033[0m"
	$(Q)[ -d $(TARGET)/usr/sbin ] || mkdir -p $(TARGET)/usr/sbin
	$(Q)$(STRIP) hostapd
	$(Q)cp hostapd $(TARGET)/usr/sbin/.

.PHONY: clean install
