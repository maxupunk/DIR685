#
# Makefile for xmldb_v2
#

ifneq ($(strip $(I386)),y)
-include ../arch.mk
endif
-include ../../path.mk

#############################################################################
# sources for xmldb
ifeq ($(strip $(XMLNODE)),y)
CFLAGS += -DXMLNODE_STANDALONE
APPLET     := xmlnode
LOCAL_SRCS := xmlnode.c
CMLIB_SRCS := sloop.c mem_helper.c dirutil.c dtrace.c libxmldbc.c
else
APPLET     := xmldb
LOCAL_SRCS := main.c xmldb.c xmlnode.c strconv.c ephp.c xmldbc.c
CMLIB_SRCS := sloop.c mem_helper.c dirutil.c dtrace.c libxmldbc.c
endif
#
#############################################################################

CFLAGS += -DMPOOL_HAVE_EXTERNAL_INCREASE_TABLE

ifeq ($(strip $(DEBUG)),y)
DDEBUG:=y
DDEBUG_LEVEL:=0
endif

#############################################################################
# dtrace debug
ifeq ($(strip $(DDEBUG)),y)
CFLAGS += -DDDEBUG
ifdef DDEBUG_LEVEL
CFLAGS += -DDBG_DEFAULT=$(DDEBUG_LEVEL)
endif
endif

#############################################################################
ifeq ($(strip $(DEBUG_SLOOP)),y)
CFLAGS += -DDEBUG_SLOOP
endif
ifeq ($(strip $(DEBUG_LIBXMLDBC)),y)
CFLAGS += -DDEBUG_LIBXMLDBC
endif
ifeq ($(strip $(DEBUG_XMLNODE)),y)
CFLAGS += -DDEBUG_XMLNODE
endif
ifeq ($(strip $(DEBUG_EPHP)),y)
CFLAGS += -DDEBUG_EPHP
endif
ifeq ($(strip $(DEBUG_EPHP_SBLIST)),y)
CFLAGS += -DDEBUG_EPHP -DDEBUG_EPHP_SBLIST
endif

#############################################################################

-include $(TOPDIR)/Rules.mk

showconfig:
	@echo APPLET     = $(APPLET)
	@echo LOCAL_SRCS = $(LOCAL_SRCS)
	@echo CMLIB_SRCS = $(CMLIB_SRCS)

clean:
#clean: clean_objs
#	@echo -e "\033[32mCleaning xmldb version 2 ...\033[0m"

install:
	@echo -e "\03[32mInstalling xmldb version 2 ...\033[0m"
	$(Q)[ -d $(TARGET)/usr/sbin ] || mkdir -p $(TARGET)/usr/sbin
	$(Q)[ -z "$(STRIP)" ] || $(STRIP) $(APPLET)
	$(Q)cp $(APPLET) $(TARGET)/usr/sbin
	$(Q)ln -s ./xmldb $(TARGET)/usr/sbin/xmldbc
ifeq ($(strip $(ELBOX_CREATE_RGDB_LINK_TO_XMLDBC)),y)
	$(Q)ln -s ./xmldb $(TARGET)/usr/sbin/rgdb
endif

.PHONY: showconfig all clean install

#############################################################################
# For Debugging ...

links:
	ln -s ./xmldb xmldbc
	ln -s ./xmldb rgdb

.PHONY: link

#############################################################################
