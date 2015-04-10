#Makefile for schedule`

ifneq ($(strip $(I386)),y)
-include ../arch.mk
else
CFLAGS+=-Wall -g
endif
-include ../../path.mk

##########################################################################
# source for schedule

MYNAME      := scheduled
APPLET      := scheduled 
LOCAL_SRCS  := scheduled.c 
CMLIB_SRCS  := sloop.c dtrace.c dirutil.c unixsock.c mem_helper.c

##########################################################################

##########################################################################
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
###########################################################################

-include $(TOPDIR)/Rules.mk

clean:
#clean: clean_objs
#	@echo -e "\033[32mCleaning $(MYNAME) ...\033[0m"
#	$(Q)rm -f *~

install:
	@echo -e "\033[32mInstalling $(MYNAME) ...\033[0m"
	$(Q)$(STRIP) $(APPLET)
	$(Q)[ -d $(TARGET)/usr/sbin ] || mkdir -p $(TARGET)/usr/sbin
	$(Q)cp $(APPLET) $(TARGET)/usr/sbin
	
.PHONY: install clean						
