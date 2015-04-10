####################################################################
#
#	Makefile for rgbin
#
####################################################################
ifeq ($(ELBOX_MODEL_DIR320),y)
USE_BRCM_TOOLS=n
endif
-include ../arch.mk
-include ../../path.mk
-include ../../.config

###################################################################
# module configurations
###################################################################
ifeq (config.rgdb,$(wildcard config.rgdb))
-include config.rgdb
endif

####################################################################

PREBUILD	:=
APPLET		:= rgbin
LOCAL_SRCS	:= main.c lrgbin.c
CMLIB_SRCS	:= libxmldbc.c
CPLUS_SRCS	:=

# main object file
CMDS	=
DIRS	=
CFLAGS	+= -DRGBIN_BOX -I$(TOPDIR)/include -I.
ifeq ($(strip $(USE_BRCM_TOOLS)),n)
LDFLAGS += -static
endif
ifeq ($(ELBOX_PROGS_PRIV_CAPWAP),y)
CFLAGS	+= -I$(KERNELDIR)/include
CFLAGS	+= -DRGBIN_BRCTL_CAPTIVE_PORTAL 
CFLAGS	+= -DRGBIN_BRCTL_SET_PMTU 
endif

####################################################################
# Configuration for each module

# rgdb
ifeq ($(CONFIG_RGBIN_RGDB),y)
LOCAL_SRCS	+= src.rgdb/rgdb.c
CMDS		+= rgdb
endif

# scut
ifeq ($(CONFIG_RGBIN_SCUT),y)
LOCAL_SRCS	+= src.scut/scut.c
CMDS		+= scut
endif

# pfile
ifeq ($(CONFIG_RGBIN_PFILE),y)
LOCAL_SRCS	+= src.pfile/pfile.c
CMDS		+= pfile
endif

# ntpclient
ifeq ($(CONFIG_RGBIN_NTPCLIENT),y)
LOCAL_SRCS	+= src.ntpclient/ntpclient.c src.ntpclient/phaselock.c
CMDS		+= ntpclient
endif

# tcprequest
ifeq ($(CONFIG_RGBIN_TCPREQUEST),y)
LOCAL_SRCS	+= src.tcprequest/tcprequest.c
CMDS		+= tcprequest
endif

# brctl
ifeq ($(CONFIG_RGBIN_BRCTL),y)
REQUIRE_LIBBRIDGE:=y

LOCAL_SRCS	+= src.brctl/brctl.c src.brctl/brctl_cmd.c src.brctl/brctl_disp.c
CMDS		+= brctl
CFLAGS		+= -I./src.brctl/libbridge
LDFLAGS		+= -L./src.brctl/libbridge -lbridge
ifeq ($(CONFIG_RGBIN_BRCTL_BWCTRL),y)
CFLAGS		+= -DMULTICAST_BWCTRL
endif
ifeq ($(CONFIG_RGBIN_BRCTL_PORTFORWARD),y)
CFLAGS		+= -DFORWARD_CTRL
endif
ifeq ($(CONFIG_RGBIN_BRCTL_PORTDENYLIST),y)
CFLAGS		+=-DREJECT_FORWARD_LIST
endif
ifeq ($(CONFIG_RGBIN_BRCTL_AP_OPERATION_MODE),y)
CFLAGS		+= -DAP_OPERATION_MODE
endif
ifeq ($(CONFIG_RGBIN_BRCTL_IGMP),y)
CFLAGS		+= -DIGMP_SNOOP
endif
ifeq ($(CONFIG_RGBIN_BRCTL_APC_OPERATION_MODE),y)
CFLAGS      += -DAPC_OPERATION_MODE
endif
ifeq ($(CONFIG_RGBIN_BRCTL_IGMP),y)
CFLAGS      += -DIGMP_SNOOP
endif
ifeq ($(CONFIG_RGBIN_BRCTL_DHCP_SERVER_ENABLE),y)
CFLAGS      += -DDHCP_SERVER_ENABLE
endif
ifeq ($(CONFIG_RGBIN_BRCTL_E_PARTITION),y)
CFLAGS      += -DE_PARTITION
endif
ifeq ($(CONFIG_RGBIN_BRCTL_W_PARTITION),y)
CFLAGS      += -DW_PARTITION
endif
ifeq ($(CONFIG_RGBIN_BRCTL_ETHLINK),y)
CFLAGS      += -DETHLINK
endif
ifeq ($(CONFIG_RGBIN_BRCTL_MAC_CLONE),y)
CFLAGS      += -DMAC_CLONE
endif
ifeq ($(CONFIG_RGBIN_BRCTL_MACADDR_CLONE_ATH),y)
CFLAGS      += -DMACADDR_CLONE_ATH
endif
ifeq ($(CONFIG_RGBIN_LIMITED_ADMIN),y)
CFLAGS      += -DLIMITED_ADMIN
endif
ifeq ($(CONFIG_RGBIN_PING_CONTROL),y)
CFLAGS      += -DPING_CONTROL
endif
ifeq ($(CONFIG_RGBIN_MULTI_VLAN),y)
CFLAGS      += -DMULTI_VLAN
endif
ifeq ($(CONFIG_RGBIN_BRCTL_WEB_REDIRECT),y)
CFLAGS      += -DWEB_REDIRECT
endif
endif

# base64: b64enc b64enc b64dec
ifeq ($(CONFIG_RGBIN_BASE64),y)
LOCAL_SRCS	+= src.base64/base64.c
CMDS		+= b64enc b64dec
endif

# smtpclient: smtpclient
ifeq ($(CONFIG_RGBIN_SMTPCLIENT),y)
LOCAL_SRCS	+= src.smtpclient/smtpclient_main.c
CMDS		+= smtpclient
endif

# tlogs
ifeq ($(CONFIG_RGBIN_TLOGS),y)
LOCAL_SRCS	+= src.tlogs/tlogs.c
CMDS		+= tlogs
endif

# vconfig 
ifeq ($(CONFIG_RGBIN_VCONFIG),y)
LOCAL_SRCS	+= src.vconfig/vconfig.c
CMDS		+= vconfig
endif

# rgcfg / rgcfg2
ifeq ($(CONFIG_RGBIN_RGCFG),y)
LOCAL_SRCS	+= src.rgcfg/rgcfg.c
CMDS		+= rgcfg
else
ifeq ($(CONFIG_RGBIN_RGCFG2),y)
LOCAL_SRCS	+= src.rgcfg2/rgcfg2.c
CMDS		+= rgcfg
endif
endif	# endof ifeq ($(CONFIG_RGBIN_RGCFG),y)

# asession
ifeq ($(CONFIG_RGBIN_ASESSION),y)
LOCAL_SRCS	+= src.asession/asession.c
CMDS		+= asession
endif

# mpconvert
ifeq ($(CONFIG_RGBIN_MPCONVERT),y)
LOCAL_SRCS	+= src.mpconvert/mpconvert.c
CMDS		+= mpconvert
endif

# dayconvert
ifeq ($(CONFIG_RGBIN_DAYCONVERT),y)
LOCAL_SRCS	+= src.dayconvert/dayconvert.c
CMDS		+= dayconvert
endif

# chnet
ifeq ($(CONFIG_RGBIN_CHNET),y)
LOCAL_SRCS	+= src.chnet/chnet.c
CMDS		+= chnet
endif

# routetable
ifeq ($(CONFIG_RGBIN_ROUTETABLE),y)
LOCAL_SRCS	+= src.routetable/routetable.c
CMDS		+= routetable
endif

# parseinfo
ifeq ($(CONFIG_RGBIN_PARSEINFO),y)
LOCAL_SRCS	+= src.parseinfo/parseinfo.c
CMDS		+= parseinfo
endif

# login
ifeq ($(CONFIG_RGBIN_LOGIN),y)
LOCAL_SRCS	+= src.login/login.c
CMDS		+= login
endif

# arpping
ifeq ($(CONFIG_RGBIN_ARPPING),y)
LOCAL_SRCS	+= src.arpping/arpping.c
CMDS		+= arpping
endif

# gethostip
ifeq ($(CONFIG_RGBIN_GETHOSTIP),y)
LOCAL_SRCS	+= src.gethostip/gethostip.c
CMDS		+= gethostip
endif

# corede
ifeq ($(CONFIG_RGBIN_COREDE),y)
LOCAL_SRCS	+= src.corede/corede.c
CMDS		+= corede
endif

# usockc
ifeq ($(CONFIG_RGBIN_USOCKC),y)
REQUIRE_UNIX_SOCKET:=y
LOCAL_SRCS	+= src.usockc/usockc.c
CMDS		+= usockc
endif

# susockc
ifeq ($(CONFIG_RGBIN_SUSOCKC),y)
REQUIRE_STREAM_UNIX_SOCKET:=y
REQUIRE_MEM_HELPER:=y
REQUIRE_STROBJ:=y
REQUIRE_XSTREAM:=y
LOCAL_SRCS	+= src.susockc/susockc.c
CMDS		+= susockc
endif

# devdata
ifeq ($(CONFIG_RGBIN_DEVDATA),y)
LOCAL_SRCS	+= src.devdata/devdata.c
CMDS		+= devdata
endif

# devconf
ifeq ($(CONFIG_RGBIN_DEVCONF),y)
LOCAL_SRCS	+= src.devconf/devconf.c
CMDS		+= devconf
endif

# rstrcmp
ifeq ($(CONFIG_RGBIN_RSTRCMP),y)
LOCAL_SRCS	+= src.rstrcmp/rstrcmp.c
CMDS		+= rstrcmp
endif

# getsys
ifeq ($(CONFIG_RGBIN_GETSYS),y)
LOCAL_SRCS	+= src.getsys/getsys.c
CMDS		+= getsys
endif

# httpc
ifeq ($(CONFIG_RGBIN_HTTPC),y)
LOCAL_SRCS	+= src.httpc/httpc.c
CMDS		+= httpc
endif

# genuuid
ifeq ($(CONFIG_RGBIN_GENUUID),y)
LOCAL_SRCS	+= src.genuuid/genuuid.c
CMDS		+= genuuid
REQUIRE_HEXSTRING	:= y
REQUIRE_MD5			:= y
endif

# seama
ifeq ($(CONFIG_RGBIN_SEAMA),y)
LOCAL_SRCS	+= src.seama/seama.c
CMDS		+= seama
REQUIRE_MD5	:= y
endif

#####################################################################

ifeq ($(REQUIRE_LIBBRIDGE),y)
PREBUILD	+= libbridge
endif

#####################################################################
# modules in comlib.

ifeq ($(strip $(REQUIRE_SLOOP)),y)
CMLIB_SRCS	+= sloop.c
endif
ifeq ($(strip $(REQUIRE_UNIX_SOCKET)),y)
CMLIB_SRCS	+= unixsock.c
endif
ifeq ($(strip $(REQUIRE_STREAM_UNIX_SOCKET)),y)
CMLIB_SRCS	+= susock.c
endif
ifeq ($(strip $(REQUIRE_HEXSTRING)),y)
CMLIB_SRCS += hexstring.c
endif
ifeq ($(strip $(REQUIRE_MD5)),y)
CMLIB_SRCS += md5.c
endif
ifeq ($(strip $(REQUIRE_MEM_HELPER)),y)
CMLIB_SRCS += mem_helper.c
endif
ifeq ($(strip $(REQUIRE_STROBJ)),y)
CMLIB_SRCS += strobj.c
endif
ifeq ($(strip $(REQUIRE_XSTREAM)),y)
CMLIB_SRCS += xstream.c
endif
ifeq ($(strip $(ELBOX_PROGS_GPL_NET_SNMP)),y)
CMLIB_SRCS += sendtrap.c
endif

#####################################################################

-include $(TOPDIR)/Rules.mk

install:
	@echo -e "\033[32mInstalling $(APPLET) ...\033[0m"
	$(Q)$(STRIP) $(APPLET)
	$(Q)[ -d $(TARGET)/usr/sbin ] || mkdir -p $(TARGET)/usr/sbin
	$(Q)install $(APPLET) $(TARGET)/usr/sbin/.
	$(Q)for i in $(CMDS) ; do [ ! -f $(TARGET)/usr/sbin/$$i ] || rm -f $(TARGET)/usr/sbin/$$i ; ln -s ./$(APPLET) $(TARGET)/usr/sbin/$$i ; done

clean:
#clean: clean_objs
#	@echo -e "\033[32mCleaning $(APPLET) ...\033[0m"
#ifeq ($(REQUIRE_LIBBRIDGE),y)
#	$(Q)make -C src.brctl clean
#endif

.PHONY: install clean

libbridge:
	@echo -e "\033[32mBuilding libbridge.a ...\033[0m"
	$(Q)make -C src.brctl libbridge/libbridge.a

.PHONY: libbridge

