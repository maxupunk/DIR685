# Makefile for dyndns
# Kevin Huang @ Alpha Networks, Feb. 2004.

-include ../arch.mk
-include ../../path.mk
-include ../../.config


##########################################################################
# source for dyndns

MYNAME      := DynDNS
APPLET      := dyndns
LOCAL_SRCS  := dyndns.c
CMLIB_SRCS  := dtrace.c libxmldbc.c base64.c

##########################################################################

CFLAGS+=-I$(TOPDIR)/include

##########################################################################
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
endif

##########################################################################

-include $(TOPDIR)/Rules.mk

showconfig:
	@echo "APPLET     = "$(APPLET)
	@echo "LOCAL_SRCS = "$(LOCAL_SRCS)
	@echo "CMLIB_SRCS = "$(CMLIB_SRCS)
	@echo "CMDS       = "$(CMDS)
	@echo "CFLAGS     = "$(CFLAGS)

install:
	@echo -e "\033[32mInstalling $(MYNAME) ...\033[0m"
	$(Q)[ -d $(TARGET)/usr/sbin ] || mkdir -p $(TARGET)/usr/sbin
	$(Q)[ -z "$(STRIP)" ] || $(STRIP) dyndns
	$(Q)cp dyndns $(TARGET)/usr/sbin

clean:
#clean:	clean_objs
#	@echo -e "\033[32mCleaning $(MYNAME) ...\033[0m"

.PHONY: all objects clean
