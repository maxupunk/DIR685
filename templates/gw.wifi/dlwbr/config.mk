# cutomized config for D-Link WBR-XXX
ifeq (buildno,$(wildcard buildno))
BUILDNO:=$(shell cat buildno)
ifeq ($(strip $(ELBOX_DEFAULT_LANGUAGE)),)
PREDEFINE_RELIMAGE:=$(shell echo $(ELBOX_MODEL_NAME)_v$(ELBOX_FIRMWARE_VERSION)_$(BUILDNO))
else
PREDEFINE_RELIMAGE:=$(shell echo $(ELBOX_MODEL_NAME)_v$(ELBOX_FIRMWARE_VERSION)_$(BUILDNO)_$(ELBOX_DEFAULT_LANGUAGE))
endif
endif
