#
# Makefile for lld2d.
#

ifneq ($(strip $(I386)),y)
-include ../arch.mk
endif
-include ../../path.mk
-include ../../.config
###########################################################################
OS_LAYER := osl-linux.c

# Files for the Daemon and the Test-Tool
DCFILES := $(OS_LAYER) main.c event.c util.c packetio.c band.c \
	state.c sessionmgr.c enumeration.c mapping.c seeslist.c \
	tlv.c qospktio.c

TCFILES := $(OS_LAYER) ctmain.c event.c util.c ctpacketio.c ctstate.c

DOBJFILES := $(patsubst %c,%o,$(DCFILES))
TOBJFILES := $(patsubst %c,%o,$(TCFILES))

###########################################################################
ifeq ($(ELBOX_MODEL_DIR685),y)
CFLAGS += -DDIR685
endif

ifeq ($(strip $(BUILD_TEST)),y)
# Source for test
APPLET		:= lld2test
LOCAL_SRCS	:= $(TCFILES)
CMLIB_SRCS	:= mem_helper.c dtrace.c libxmldbc.c
else
# Source for daemon
APPLET		:= lld2d
LOCAL_SRCS	:= $(DCFILES)
CMLIB_SRCS	:= mem_helper.c dtrace.c libxmldbc.c
endif

###########################################################################

ifeq ($(strip $(V)),y)
Q :=
else
Q := @
endif

###########################################################################

ifeq ($(strip $(DEBUG)),y)
DDEBUG:=y
DDEBUG_LEVEL:=0
endif

# dtarce debug
ifeq ($(strip $(DDEBUG)),y)
CFLAGS += -DDDEBUG -D__DEBUG__
ifdef DDEBUG_LEVEL
CFLAGS += -DDBG_DEFAULT=$(DDEBUG_LEVEL)
endif
endif

ifeq ($(strip $(DEBUG_LIBXMLDBC)),y)
CFLAGS += -DDEBUG_LIBXMLDBC
endif

ifeq ($(strip $(LOCAL_TEST)),y)
CFLAGS += -DLOCAL_TEST=y
endif

###########################################################################

-include $(TOPDIR)/Rules.mk

showconfig:
	@echo APPLET     = $(APPLET)
	@echo LOCAL_SRCS = $(LOCAL_SRCS)
	@echo CMLIB_SRCS = $(CMLIB_SRCS)

clean:
#	rm -f -- .depend *~ lld2d lld2test conftest *.o

install:
	@echo -e "\033[32mInstalling APPLET: $(APPLET) ...\033[0m"
	[ -d $(TARGET)/usr/sbin ] || mkdir -p $(TARGET)/usr/sbin
	[ -z "$(STRIP)" ] || $(STRIP) $(APPLET)
	cp $(APPLET) $(TARGET)/usr/sbin

.PHONY: showconfig all clean install
