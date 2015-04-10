#
#	Makefile for igmpproxy
#

ifneq ($(strip $(I386)),y)
-include ../arch.mk
else
CFLAGS+=-Wall
endif
-include ../../path.mk
-include ../../.config

###########################################################################
# source for igmpproxy
MYNAME		:= IGMP proxy
APPLET		:= igmpproxy
LOCAL_SRCS	:= main.c igmpproxy.c sioc.c mrtapi.c vifs.c igmp.c mrtable.c
CMLIB_SRCS	:= dtrace.c mem_helper.c sloop.c libxmldbc.c
###########################################################################

CFLAGS+=-DMPOOL_HAVE_EXTERNAL_INCREASE_TABLE=y
CFLAGS+=-I$(TOPDIR)/include

ifeq ($(strip $(ELBOX_PROGS_PRIV_IGMPPROXY_IGMPV3)),y)
CFLAGS+=-DPROGS_PRIV_IGMPPROXY_IGMPV3_ALPHA
endif

###########################################################################
# dtrace debug
#DEBUG:=y
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
	$(Q)cp $(APPLET) $(TARGET)/usr/sbin/.

clean:
#clean: clean_objs

.PHONY: showconfig install clean

#############################################################################
