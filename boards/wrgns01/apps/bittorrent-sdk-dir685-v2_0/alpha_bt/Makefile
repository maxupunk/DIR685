#
# Mainfile for BT
#

-include ../../../../../arch.mk
-include ../../../../../path.mk
-include ../../../../../.config

##########################################################################
# source for BT
OTHER_TARGETS:= 
MYNAME		:= BT
APPLET		:= btgi
LOCAL_SRCS	:= main.c alpha_bt.c
CMLIB_SRCS	:= dtrace.c

##########################################################################

CMDS=
CFLAGS+=-I$(TOPDIR)/include

##########################################################################

#DEBUG=y

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

-include $(TOPDIR)/Rules.mk

clean: clean_objs
	@echo -e "\033[32mCleaning $(MYNAME) ...\033[0m"
	$(Q)rm -f *~

install:
	@echo -e "\033[32mInstalling $(MYNAME) ...\033[0m"
	$(Q)cp $(APPLET) $(TARGET)/sbin

.PHONY: clean install
