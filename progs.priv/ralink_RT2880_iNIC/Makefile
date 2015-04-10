#
# Makefile for Ralink ewc driver.
#
#

include ../arch.mk
include ../../path.mk
include ../../.config

#############################################################################

Q	?= @
BUILDPATH 			:= $(shell pwd)
ifeq ($(strip $(ELBOX_PROGS_PRIV_RALINK_INIC_RT2880_1170)),y)
BUILDPATH_VER       := $(BUILDPATH)/v1.1.7.0
endif
ifeq ($(strip $(ELBOX_PROGS_PRIV_RALINK_INIC_RT2880_1180)),y)
BUILDPATH_VER 		:= $(BUILDPATH)/v1.1.8.0
endif
ifeq ($(strip $(ELBOX_PROGS_PRIV_RALINK_INIC_RT2880_1181)),y)
BUILDPATH_VER       := $(BUILDPATH)/v1.1.8.1
endif
ifeq ($(strip $(ELBOX_PROGS_PRIV_RALINK_INIC_RT2880_1183)),y)
BUILDPATH_VER       := $(BUILDPATH)/v1.1.8.3
endif

all:
	$(Q) make -C $(BUILDPATH_VER)
	
showconfig:
	$(Q) make -C $(BUILDPATH_VER) showconfig
	
install:
	$(Q) make -C $(BUILDPATH_VER) install
	
clean:
#	$(Q) make -C $(BUILDPATH_VER) clean
	
.PHONY: all showconfig install clean
