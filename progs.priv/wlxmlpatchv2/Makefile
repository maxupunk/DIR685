#
# Makefile for wlxmlpatchv2.
#

-include ../arch.mk
-include ../../path.mk
-include ../../.config

#############################################################


WIRELESS_TOOLS_PATH=$(TOPDIR)/progs.gpl/wireless_tools

ifeq ($(strip $(ELBOX_PROGS_PRIV_MADWIFI_AP83)),y)
WIRELESS_TOOLS_PATH=$(TOPDIR)/progs.priv/madwifi_ap83/_build/apps/wireless_tools.28
endif

ifeq ($(strip $(ELBOX_PROGS_PRIV_MADWIFI_CAVIUM)),y)
WIRELESS_TOOLS_PATH=$(TOPDIR)/progs.priv/madwifi_cavium/_build/apps/wireless_tools.28
endif

ifeq ($(strip $(ELBOX_PROGS_PRIV_MADWIFI_FUSION_CAVIUM)),y)
WIRELESS_TOOLS_PATH=$(TOPDIR)/progs.priv/madwifi_fusion_cavium/_build/apps/wireless_tools.28
endif

ifeq ($(strip $(DEBUG_CLIENT_LIST)),y)
CFLAGS+=-DDEBUG_CLIENT_LIST
endif

#DEBUG:=y
#DEBUG_LEVEL:=3

ifeq ($(strip $(DEBUG)),y)
CFLAGS+=-DDDEBUG
ifdef DEBUG_LEVEL
CFLAGS+=-DDBG_DEFAULT=$(DEBUG_LEVEL)
endif
endif

APPLET     := wlxmlpatch
LOCAL_SRCS := wlxmlpatch.c defmod.c

ifeq ($(strip $(ELBOX_PROGS_PRIV_WLXMLPATCHV2_RALINK_RT2800)),y)
LOCAL_SRCS := $(LOCAL_SRCS) rt2800.c
endif

ifeq ($(strip $(ELBOX_PROGS_PRIV_WLXMLPATCHV2_RALINK_RT2880)),y)
LOCAL_SRCS := $(LOCAL_SRCS) rt2880.c
endif

ifeq ($(strip $(ELBOX_PROGS_PRIV_WLXMLPATCHV2_RALINK_RT2880_v1183)),y)
CFLAGS+=-DRT2880_V1183=1
endif

ifeq ($(strip $(ELBOX_PROGS_PRIV_WLXMLPATCHV2_RALINK_RT61)),y)
LOCAL_SRCS := $(LOCAL_SRCS) rt61.c
endif

ifeq ($(strip $(ELBOX_PROGS_PRIV_WLXMLPATCHV2_MADWIFI)),y)

# Setup madwifi driver path.
ifeq ($(strip $(ELBOX_PROGS_PRIV_MADWIFI_50120)),y)
MADWIFI_PATH:=$(TOPDIR)/progs.priv/madwifi.LSDK-WLAN5.0.1.20/build/src/802_11/madwifi/madwifi
endif
ifeq ($(strip $(ELBOX_PROGS_PRIV_MADWIFI_50246)),y)
MADWIFI_PATH:=$(TOPDIR)/progs.priv/madwifi.LSDK-WLAN5.0.2.46/build/src/802_11/madwifi/madwifi
endif
ifeq ($(strip $(ELBOX_PROGS_PRIV_MADWIFI_520112)),y)
MADWIFI_PATH:=$(TOPDIR)/progs.priv/madwifi.LSDK-WLAN5.2.0.112/build/src/802_11/madwifi/madwifi
endif
ifeq ($(strip $(ELBOX_PROGS_PRIV_MADWIFI_EWC)),y)
MADWIFI_PATH:=$(TOPDIR)/progs.priv/madwifi.ewc/_build/src/802_11/madwifi/madwifi
CFLAGS+=-D_BYTE_ORDER=_BIG_ENDIAN
endif

ifeq ($(strip $(ELBOX_PROGS_PRIV_MADWIFI_AP83)),y)
MADWIFI_PATH:=$(TOPDIR)/progs.priv/madwifi_ap83/_build/wlan/linux
CFLAGS+=-D_BYTE_ORDER=_BIG_ENDIAN
endif

ifeq ($(strip $(ELBOX_PROGS_PRIV_MADWIFI_CAVIUM)),y)
#MADWIFI_PATH:=$(TOPDIR)/progs.priv/madwifi_cavium/_build/wlan/madwifi/madwifi
MADWIFI_PATH:=$(TOPDIR)/progs.priv/madwifi_cavium/_build/wlan/core
CFLAGS+=-D_BYTE_ORDER=_BIG_ENDIAN
endif

ifeq ($(strip $(ELBOX_PROGS_PRIV_MADWIFI_FUSION_CAVIUM)),y)
MADWIFI_PATH:=$(TOPDIR)/progs.priv/madwifi_fusion_cavium/_build/wlan/linux
CFLAGS+=-D_BYTE_ORDER=_BIG_ENDIAN
endif

ifeq ($(strip $(ELBOX_PROGS_PRIV_MADWIFI_WPS)),y)
MADWIFI_PATH:=$(TOPDIR)/progs.priv/madwifi.WPS/build/src/802_11/madwifi/madwifi
endif

LOCAL_SRCS := $(LOCAL_SRCS) madwifi.c
endif

CMLIB_SRCS := libxmldbc.c dtrace.c

ifeq ($(strip $(ELBOX_PROGS_PRIV_WLXMLPATCHV2_MADWIFI)),y)
CFLAGS+=-I$(WIRELESS_TOOLS_PATH) -I$(MADWIFI_PATH)
else
CFLAGS+=-I$(WIRELESS_TOOLS_PATH)
endif

LDFLAGS:=-L$(WIRELESS_TOOLS_PATH) -liw

ifeq ($(wildcard $(WIRELESS_TOOLS_PATH)/libiw.a),)
all:
	@echo -e "\033[31mwlxmlpatchv2:\033[0m"
	@echo -e "\033[31mlibrary iw is not available, please build wireless tools first!\033[0m"
	$(Q)exit 9
else
-include $(TOPDIR)/Rules.mk
endif

install:
	@echo -e "\033[32mInstalling wlxmlpatchv2 ...\033[0m"
	$(Q)[ -d $(TARGET)/usr/sbin ] || mkdir -p $(TARGET)/usr/sbin
	$(Q)$(STRIP) $(APPLET)
	$(Q)cp -f $(APPLET) $(TARGET)/usr/sbin/.

clean:
#	$(Q)rm -f *.o .depend $(APPLET) *~

.PHONY: all install clean

showconfig:
	@echo cflags=$(CFLAGS)
