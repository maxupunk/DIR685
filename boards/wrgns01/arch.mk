.EXPORT_ALL_VARIABLES:
Q?=@
ifeq ($(strip $(V)),y)
Q:=
endif
Q:=
############################################################################
ifdef TPATH_UC
CC_PATH := $(TPATH_UC)
else
CC_PATH :=
endif
CROSS_COMPILE = arm-linux-
#ZEBRA_HOSTYPE = arm-linux-
CC	= $(CC_PATH)/bin/$(CROSS_COMPILE)gcc
CXX = $(CC_PATH)/bin/$(CROSS_COMPILE)g++
AS	= $(CC_PATH)/bin/$(CROSS_COMPILE)as
AR	= $(CC_PATH)/bin/$(CROSS_COMPILE)ar
LD	= $(CC_PATH)/bin/$(CROSS_COMPILE)ld
RANLIB	= $(CC_PATH)/bin/$(CROSS_COMPILE)ranlib
STRIP	= $(CC_PATH)/bin/$(CROSS_COMPILE)strip 

CFLAGS	= -Os -Wall -D__UCLIBC_HAS_MMU__ -D__UCLIBC__ -DLOGNUM=1 -DRGDB_BLOCK_OFFSET=0 
LDFLAGS =

# hendry add for default fs
# set DEFAULT_STORAGE_FS to EXT2, EXT3 or NTFS
CFLAGS += -DDEFAULT_STORAGE_FS=\"EXT3\"

#NET80211_BUILDIN_KERNEL=1
#CONFIG_JUMPSTART=y

ifdef TPATH_KC
KCC_PATH := $(TPATH_KC)/bin
else
KCC_PATH :=
endif
KCC	= $(KCC_PATH)/arm-linux-gcc
KLD	= $(KCC_PATH)/arm-linux-ld
HOST_TYPE = mipsel-uclibc 
#CHIP_RTL8366RB=y

