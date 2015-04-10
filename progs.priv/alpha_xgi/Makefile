#
# Makefile for the Alphanetworks Tag Parser
#  for the Linux OS
#

ifneq ($(strip $(I386)),y)
-include ../arch.mk
else
CFLAGS+=-Wall
endif
-include ../../path.mk
-include ../../.config

###########################################################################
# source of atp
MYNAME		:= ATP
APPLET		:= atp
LOCAL_SRCS	:= main.c alpha_tp.c alpha_xgi.c alpha_xf.c iconf.c session.c misc.c alpha_sgi.c
CMLIB_SRCS	:= dtrace.c
###########################################################################

CFLAGS+=-I$(TOPDIR)/include

###########################################################################
# define HOME_POTAL from ELBOX_SAMBA flag
ifeq ($(strip $(ELBOX_SAMBA)),y)
HOME_PORTAL:=y
CFLAGS+=-DHOME_PORTAL
endif


###########################################################################
# define configuration name as config.dcf
ifeq ($(strip $(ELBOX_TEMPLATE_AP_WIFI)),y)
CFLAGS+=-DCFG_DCF
endif

ifeq ($(strip $(ELBOX_TEMPLATE_AP_WIFI_WAN)),y)
CFLAGS+=-DCFG_DCF
endif

# dtrace debug
ifeq ($(strip $(DEBUG)),y)
DDEBUG:=y
DDEBUG_LEVEL:=0
endif

ifeq ($(strip $(DDEBUG)),y)
CFLAGS+=-DDDEBUG
ifdef DDEBUG_LEVEL
CFLAGS+=-DDBG_DEFAULT=$(DDEBUG_LEVEL)
endif
endif
#############################################################################

-include $(TOPDIR)/Rules.mk
showconfig:
	@echo "APPLET     = "$(APPLET)
	@echo "LOCAL_SRCS = "$(LOCAL_SRCS)
	@echo "CMLIB_SRCS = "$(CMLIB_SRCS)
	@echo "CFLAGS     = "$(CFLAGS)

install:
	@echo -e "\033[32mInstalling $(MYNAME) ...\033[0m"
	$(Q)$(STRIP) $(APPLET)
	$(Q)cp $(APPLET) $(TARGET)/sbin/.
	$(Q)ln -fs /sbin/atp $(TARGET)/sbin/xgi
	$(Q)ln -fs /sbin/atp $(TARGET)/sbin/sgi

clean:
#clean: clean_objs

.PHONY: showconfig install clean

#############################################################################
