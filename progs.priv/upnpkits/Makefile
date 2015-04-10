#
# Mainfile for UPnP kits
#

-include ../arch.mk
-include ../../path.mk
-include ../../.config

##########################################################################
# source for UPnP kit

MYNAME		:= UPnP kits
APPLET		:= upnpkits
LOCAL_SRCS	:= main.c
CMLIB_SRCS	:= dtrace.c libxmldbc.c mem_helper.c sloop.c

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

ifeq ($(strip $(CONFIG_UPNPKITS_HNAP)),y)
LOCAL_SRCS+=hnap.c
REQUIRE_LIBIXML=y
CMDS+=hnap
endif

ifeq ($(strip $(CONFIG_UPNPKITS_UPNPKITS)),y)
LOCAL_SRCS+=upnpkits.c
endif

ifeq ($(strip $(CONFIG_UPNPKITS_UPNPDEV)),y)
LOCAL_SRCS+=upnpdev.c
REQUIRE_LIBIXML=y
REQUIRE_LIBUSOCK=y
CMDS+=upnpdev
endif

ifeq ($(strip $(CONFIG_UPNPKITS_UPNPCP)),y)
LOCAL_SRCS+=upnpcp.c
REQUIRE_LIBIXML=y
CMDS+=upnpcp
endif

ifeq ($(strip $(CONFIG_UPNPKITS_WFADEV)),y)
LOCAL_SRCS+=wfadev.c
REQUIRE_LIBIXML=y
REQUIRE_BASE64=y
CMDS+=wfadev
endif

ifeq ($(strip $(CONFIG_UPNPKITS_WFANOTIFY)),y)
LOCAL_SRCS+=wfanotify.c
REQUIRE_BASE64=y
CMDS+=wfanotify
endif

ifeq ($(strip $(CONFIG_UPNPKITS_GENUUID)),y)
LOCAL_SRCS+=genuuid.c
REQUIRE_MD5=y
REQUIRE_HEXSTRING=y
CMDS+=genuuid
endif

ifeq ($(strip $(CONFIG_UPNPKITS_COREGA_ROUTER)),y)
LOCAL_SRCS+=cgrouter.c
REQUIRE_LIBIXML=y
CMDS+=cgrouter
endif
##########################################################################

ifeq ($(strip $(REQUIRE_LIBIXML)),y)
CFLAGS += -I./ixml/inc
LDFLAGS += -L./ixml/src/obj -lixml
PREBUILD += libixml
endif

ifeq ($(strip $(REQUIRE_MD5)),y)
CMLIB_SRCS += md5.c
endif

ifeq ($(strip $(REQUIRE_HEXSTRING)),y)
CMLIB_SRCS += hexstring.c
endif

ifeq ($(strip $(REQUIRE_LIBUSOCK)),y)
CMLIB_SRCS += unixsock.c
endif

ifeq ($(strip $(REQUIRE_BASE64)),y)
CMLIB_SRCS += base64.c
endif

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
#	$(Q)make -C ixml clean
#	$(Q)rm -f *~

libixml:
	@echo -e "\033[32mBuilding ixml library ...\033[0m"
	$(Q)make -C ixml

install:
	@echo -e "\033[32mInstalling $(MYNAME) ...\033[0m"
	$(Q)[ -d $(TARGET)/etc/templates/upnpd ] || mkdir -p $(TARGET)/etc/templates/upnpd
	$(Q)cp -r templates/upnpd/* $(TARGET)/etc/templates/upnpd/.
	$(Q)$(STRIP) $(APPLET)
	$(Q)[ -d $(TARGET)/usr/sbin ] || mkdir -p $(TARGET)/usr/sbin
	$(Q)cp $(APPLET) $(TARGET)/usr/sbin
	$(Q)for i in $(CMDS) ; do \
		[ ! -f $(TARGET)/usr/sbin/$$i ] || rm -f $(TARGET)/usr/sbin/$$i ; \
		ln -s ./$(APPLET) $(TARGET)/usr/sbin/$$i ; \
	done
ifeq ($(CONFIG_UPNPKITS_HNAP),y)
	@echo -e "\033[32mInstalling HNAP support ...\033[0m"
	$(Q)[ -d $(TARGET)/www/HNAP1 ] || mkdir -p $(TARGET)/www/HNAP1
	$(Q)touch $(TARGET)/www/HNAP1/index.hnap
endif

.PHONY: showconfig clean libixml install
