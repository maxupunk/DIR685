#
# Mainfile for Widget kits
#

-include ../arch.mk
-include ../../path.mk
-include ../../.config

##########################################################################
# source for Widget kits

MYNAME		:= Widget kits
APPLET		:= widget
LOCAL_SRCS	:= main.c
CMLIB_SRCS	:= md5.c

##########################################################################

CMDS=
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

clean:
#clean: clean_objs
#	@echo -e "\033[32mCleaning $(MYNAME) ...\033[0m"
#	$(Q)rm -f *~

install:
	@echo -e "\033[32mInstalling $(MYNAME) ...\033[0m"
	$(Q)$(STRIP) $(APPLET)
	$(Q)[ -d $(TARGET)/usr/sbin ] || mkdir -p $(TARGET)/usr/sbin
	$(Q)cp $(APPLET) $(TARGET)/usr/sbin

.PHONY: showconfig clean install
