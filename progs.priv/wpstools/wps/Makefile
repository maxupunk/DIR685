#
# Makefile for wps - Wifi Protected Setup implementation.
#

ifneq ($(strip $(I386)),y)
USE_BRCM_TOOLS=n
-include ../../arch.mk
endif
-include ../../../path.mk
-include ../../../.config

#####################################################################

APPLET		:= wps
LOCAL_SRCS	:= slist.c
CMLIB_SRCS	:= dtrace.c sloop.c dirutil.c unixsock.c libxmldbc.c base64.c
CPLUS_SRCS	:= main.cpp tutrace.cpp TlvBase.cpp RegProtoTlv.cpp \
				RegProtocol.cpp RegProtoMsgs.cpp StateMachine.cpp \
				MasterControl.cpp Info.cpp Transport.cpp \
				InbEap.cpp InbWlan.cpp InbUPnPDev.cpp

ifeq ($(strip $(CONFIG_WPSTOOLS_USE_SHARED_OPENSSL)),y)
CFLAGS += -I$(OPENSSLDIR)/include
#LDFLAGS	+= -L../openssl-0.9.8a -lssl -lcrypto -static -Wl,-Bdynamic
LDFLAGS	+= -L$(OPENSSLDIR) -lssl -lcrypto -static
else
CFLAGS += -I../openssl-0.9.8a/include
#LDFLAGS	+= -L../openssl-0.9.8a -lssl -lcrypto -static -Wl,-Bdynamic
LDFLAGS	+= -L../openssl-0.9.8a -lssl -lcrypto -static
endif

#####################################################################

ifeq ($(strip $(DEBUG)),y)
DDEBUG:=y
DDEBUG_LEVEL:=0
CFLAGS += -D_TUDEBUGTRACE
endif

ifeq ($(strip $(CONFIG_WPSTOOLS_ALPHA_UNSUPPORT_PRAGMA_PACK)),y)
CFLAGS += -DUNSUPP_PRAGMA_PACK
endif

ifeq ($(strip $(DDEBUG)),y)
CFLAGS += -DDDEBUG
#CFLAGS += -DDEBUG_SLOOP=1
ifdef DDEBUG_LEVEL
CFLAGS += -DDBG_DEFAULT=$(DDEBUG_LEVEL)
endif
endif

#####################################################################

-include $(TOPDIR)/Rules.mk

clean: clean_objs


install:
	@echo -e "\033[32mInstalling $(APPLET) ...\033[0m"
	$(Q)$(STRIP) wps
	$(Q)[ -d $(TARGET)/usr/sbin ] || mkdir -p $(TARGET)/usr/sbin
	$(Q)cp wps $(TARGET)/usr/sbin/.
	

showconfig:

dos2unix:
	$(Q)dos2unix *.cpp
	$(Q)dos2unix *.h

.PHONY: clean install showconfig dos2unix
