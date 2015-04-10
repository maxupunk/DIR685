#################################################################################
 # Ralink Technology, Inc.	                                         	#
 # 4F, No. 2 Technology 5th Rd.                                          	#
 # Science-based Industrial Park                                         	#
 # Hsin-chu, Taiwan, R.O.C.                                              	#
 #                                                                       	#
 # (c) Copyright 2005, Ralink Technology, Inc.                           	#
 #                                                                       	#
 # All rights reserved. Ralink's source code is an unpublished work and the	#
 # use of a copyright notice does not imply otherwise. This source code		#
 # contains confidential trade secret material of Ralink Tech. Any attempt	#
 # or participation in deciphering, decoding, reverse engineering or in any	#
 # way altering the source code is stricitly prohibited, unless the prior	#
 # written consent of Ralink Technology, Inc. is obtained.			#
#################################################################################
CONFIG_MII=
#
# Please enable CONFIG_EXTRA_CFLAG=y on 2.6.25 or above 
#
CONFIG_EXTRA_CFLAG=

CONFIG_NM_SUPPORT=
CONFIG_MC_SUPPORT=
#PLATFORM = PC
#PLATFORM  = RT2880
#PLATFORM = TWINPASS
#PLATFORM = 5VT
PLATFORM = STORLINK
#PLATFORM = STAR
#PLATFORM = VITESSE
#PLATFORM = RDC
#PLATFORM = SIGMA
#PLATFORM = BRCM
#PLATFORM = IKANOS_VX160
#PLATFORM = IKANOS_VX180
#PLATFORM = PIKA
#PLATFORM = MNDSPEED
#PLATFORM = MNDSPEED2
ifeq ($(PLATFORM),STORLINK)
#LINUX_SRC = /opt/fvt_11N_SDK_0807/fvt131x_SDK_11n/linux-2.6.17
CROSS_COMPILE = /opt/storlink_arm_920t_le_uclibc/bin/arm-linux-
LINUX_SRC = $(KERNELDIR)
endif


ifeq ($(PLATFORM),PC)
#
# Linux 2.6
#
LINUX_SRC = /lib/modules/$(shell uname -r)/build

#
# Linux 2.4 Change to your local setting
#
#LINUX_SRC = /usr/src/linux-2.4
#CFLAGS := -D__KERNEL__ -I$(LINUX_SRC)/include -O2 -fomit-frame-pointer -fno-strict-aliasing -fno-common -pipe -mpreferred-stack-boundary=2 -march=i686 -DMODULE -DMODVERSIONS -include $(LINUX_SRC)/include/linux/modversions.h $(WFLAGS)
CROSS_COMPILE =
endif


ifeq ($(PLATFORM),RT2880)
LINUX_SRC = /opt/SDK/RT288x_SDK/source/linux-2.4.x
CROSS_COMPILE = /opt/buildroot-gdb/bin/mipsel-linux-
CFLAGS :=  -D__KERNEL__ -I$(LINUX_SRC)/include -Wall -Wstrict-prototypes -Wno-trigraphs -O2 -fno-strict-aliasing -fno-common -fomit-frame-pointer -I $(LINUX_SRC)/include/asm/gcc -G 0 -mno-abicalls -fno-pic -pipe  -finline-limit=100000 -march=mips2 -mabi=32 -Wa,--trap -DMODULE -mlong-calls -DWIRELESS_THROUGHPUT_TEST=1 -DCONFIG_RALINK_RT2880_VER_B -nostdinc -iwithprefix include 
endif

ifeq ($(PLATFORM),SIGMA)
LINUX_SRC = /opt/sigma/kernel/smp86xx_kernel_source_2.7.172.0/linux-2.6.15
#LINUX_SRC = /home/snowpin/Sigma/SMP863x/172/smp86xx_kernel_source_2.7.172.0/linux-2.6.15
CROSS_COMPILE = /opt/sigma/toolchain/smp86xx_toolchain_2.7.172.0/build_mipsel_nofpu/staging_dir/bin/mipsel-linux-
#CROSS_COMPILE = /home/snowpin/Sigma/SMP863x/172/smp86xx_toolchain_2.7.172.0/build_mipsel_nofpu/staging_dir/bin/mipsel-linux-
endif

ifeq ($(PLATFORM),5VT)
LINUX_SRC = /home/5VT_SDK/linux-2.6.17
CROSS_COMPILE = /opt/crosstool/uClibc_v5te_le_gcc_4_1_1/bin/arm-linux-
endif

ifeq ($(PLATFORM),MNDSPEED)
LINUX_SRC = /opt/Vitesse/linux-2.6-grocx
CROSS_COMPILE = /hd2/mndspeed/tools/bin/arm-linux-
endif

ifeq ($(PLATFORM),MNDSPEED2)
LINUX_SRC = /hd2/mndspeed2/linux-2.6.21.1
CROSS_COMPILE = /hd2/mndspeed2/staging_dir_arm/bin/arm-linux-
MAKE_FLAGS:=ARCH="arm" 
endif



ifeq ($(PLATFORM),RDC)
# Linux 2.6
#LINUX_SRC = /lib/modules/$(shell uname -r)/build
# Linux 2.4 Change to your local setting
LINUX_SRC = /home/RDC/linux_2.4.25
CFLAGS := -I$(LINUX_SRC)/include -O2 -fomit-frame-pointer -fno-strict-aliasing -fno-common -pipe -mpreferred-stack-boundary=2 -march=i386 -nostdinc -iwithprefix include -DKBUILD_BASEN -DMODULE -DMODVERSIONS $(WFLAGS)
CROSS_COMPILE =/export/tools/bin/i386-linux-
endif


ifeq ($(PLATFORM),STAR)
LINUX_SRC = /opt/star/kernel/linux-2.4.27-star
CROSS_COMPILE = /opt/star/tools/arm-linux/bin/arm-linux-
CFLAGS := -I$(LINUX_SRC)/include -Wall -Wstrict-prototypes -Wno-trigraphs -O2 -fno-strict-aliasing -fno-common -Uarm -fno-common -pipe -mapcs-32 -D__LINUX_ARM_ARCH__=4 -march=armv4  -mshort-load-bytes -msoft-float -Uarm -DMODULE -DMODVERSIONS -include $(LINUX_SRC)/include/linux/modversions.h 
endif

ifeq ($(PLATFORM),VITESSE)
LINUX_SRC = /opt/Vitesse/linux-2.6-grocx
CROSS_COMPILE = /opt/Vitesse/arm-uclibc-3.4.6/bin/arm-linux-
CFLAGS := -I$(LINUX_SRC)/include -Wall -Wstrict-prototypes -Wno-trigraphs -O2 -fno-strict-aliasing -fno-common -Uarm -fno-common -pipe -mapcs-32 -D__LINUX_ARM_ARCH__=4 -march=armv4  -msoft-float -Uarm -DMODULE -DMODVERSIONS 
endif


ifeq ($(PLATFORM),TWINPASS)
LINUX_SRC = /opt/twinpass/release/2.0.1/source/kernel/opensource/linux-2.4.31
CROSS_COMPILE = /opt/uclibc-toolchain/ifx-lxdb-1-1/gcc-3.3.6/toolchain-mips/bin/mips-linux-
CFLAGS := -DMODULE -DTWINPASS -I$(LINUX_SRC)/include -Wall -Wstrict-prototypes -Wno-trigraphs -O2 -fno-strict-aliasing -fno-common -fomit-frame-pointer -DIFX_SMALL_FOOTPRINT -I$(LINUX_SRC)/include/asm/gcc -G 0 -mno-abicalls -fno-pic -pipe  -finline-limit=100000 -mabi=32 -march=mips32 -Wa,-32 -Wa,-march=mips32 -Wa,-mips32 -Wa,--trap  -mlong-calls  -nostdinc -iwithprefix include 
endif

ifeq ($(PLATFORM),BRCM)
BRCM_ROOT = /opt/BRCM
LINUX_SRC = $(BRCM_ROOT)/kernel/linux
CROSS_COMPILE = $(BRCM_ROOT)/toolchains/uclibc-crosstools/bin/mips-linux-uclibc-
CFLAGS  += -Wall -DMODULE -DBCM63XX -D__MIPSEB__ -mabi=32 -march=mips32 -Wa,-32 -Wa,-march=mips32 -Wa,-mips32 -Wa,--trap -fomit-frame-pointer -fno-common -mlong-calls -mno-abicalls -fno-pic -pipe -G 0 -I$(LINUX_SRC)/include/asm-mips/mach-bcm963xx  -I$(LINUX_SRC)/include/asm-mips/mach-generic -I$(LINUX_SRC)/include
export KERNELDIR CROSS_COMPILE CC AS LD
endif


ifeq ($(PLATFORM),IKANOS_VX160)
LINUX_SRC = /opt/ikanos/linux-2.6.18
#CROSS_COMPILE = /opt/ikanos/buildroot/build_mips_nofpu/staging_dir/bin/mips-linux-
CROSS_COMPILE = mips-linux-
CFLAGS := -D__KERNEL__ -DIKANOS_VX_1X0 -I$(LINUX_SRC)/include -I$(LINUX_SRC)/include/asm/gcc -I$(LINUX_SRC)/include/asm-mips/mach-tango2 -I$(LINUX_SRC)/include/asm-mips/mach-tango2 -I$(LINUX_SRC)/include/asm-mips/mach-generic -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -ffreestanding -O2 -fomit-frame-pointer -G 0 -mno-abicalls -fno-pic -pipe -march=lx4189 -Wa, -DMODULE $(WFLAGS) 
PLATFORM_OBJ := platform/vr_ikans.o
endif


ifeq ($(PLATFORM),IKANOS_VX180)
LINUX_SRC = /opt/LX_BSP_VX180_5_4_0r1_ALPHA_26DEC07/linux-2.6.18
#CROSS_COMPILE = /opt/ikanos/buildroot/build_mips_nofpu/staging_dir/bin/mips-linux-uclibc
CROSS_COMPILE = mips-linux-uclibc-
CFLAGS := -D__KERNEL__  -DIKANOS_VX_1X0 -mips32r2 -I$(LINUX_SRC)/include -I$(LINUX_SRC)/include/asm/gcc -I$(LINUX_SRC)/include/asm-mips/mach-tango2 -I$(LINUX_SRC)/include/asm-mips/mach-tango2 -I$(LINUX_SRC)/include/asm-mips/mach-generic -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -ffreestanding -O2 -fomit-frame-pointer -G 0 -mno-abicalls -fno-pic -pipe -Wa, -DMODULE $(WFLAGS)
PLATFORM_OBJ := platform/vr_ikans.o
endif

ifeq ($(PLATFORM),PIKA)
KSRC = /opt/alpha_pika/linux-2.4.22
LINUX_SRC = /opt/alpha_pika/linux-2.4.22
CROSS_COMPILE = /opt/toolchain-89/bin/arm-elf-
CFLAGS := -D__KERNEL__ -I$(KSRC)/include -Wall -Wstrict-prototypes -Wno-trigraphs -O2 -fno-strict-aliasing -fno-common -Uarm -fno-common -pipe -mapcs-32 -D__LINUX_ARM_ARCH__=4 -march=armv4  -mshort-load-bytes -msoft-float -Uarm -DMODULE -DMODVERSIONS -include $(KSRC)/include/linux/modversions.h
endif


CC := $(CROSS_COMPILE)gcc
LD := $(CROSS_COMPILE)ld
AS := $(CROSS_COMPILE)as


_CFLAGS += -I$(PWD)/comm
_CFLAGS += -D__KERNEL__
_CFLAGS += -O2 -Wall -Wstrict-prototypes -Wno-trigraphs 
_CFLAGS += -DDBG #-DINBAND_DEBUG
_CFLAGS += $(WFLAGS)

PCI_OBJS := pci/rt_pci_dev.o
MII_OBJS := mii/rt_mii_dev.o
COMM_OBJS:= comm/rt_profile.o comm/raconfig.o comm/iwhandler.o \
            comm/ioctl.o comm/iwreq_stub.o comm/mbss.o comm/wds.o \
            comm/apcli.o comm/crc32.o 

obj-m := rt2880_iNIC.o
rt2880_iNIC-objs := $(COMM_OBJS) $(PLATFORM_OBJ)

ifeq ($(CONFIG_NM_SUPPORT), y)
_CFLAGS += -DNM_SUPPORT
endif
ifeq ($(CONFIG_MC_SUPPORT), y)
_CFLAGS += -DMULTIPLE_CARD_SUPPORT
endif

ifeq ($(CONFIG_MII), y)
rt2880_iNIC-objs += $(MII_OBJS)
_CFLAGS += -I$(PWD)/mii -DCONFIG_RT2880_INIC_MII
else
rt2880_iNIC-objs += $(PCI_OBJS)
_CFLAGS += -I$(PWD)/pci
endif

ifneq ($(PLATFORM_OBJ), )
_CFLAGS += -I$(PWD)/platform
endif

ifeq ($(CONFIG_EXTRA_CFLAG), y)
EXTRA_CFLAGS += $(_CFLAGS)
else
CFLAGS += $(_CFLAGS)
endif

export LINUX_SRC CROSS_COMPILE CFLAGS EXTRA_CFLAGS


ifneq (,$(findstring 2.4,$(LINUX_SRC)))
	#linux 2.4
all: $(obj-m)
ifneq ($(subdir-m), )
	for d in $(subdir-m);                 \
	do                                    \
	  make --directory=$(subdir-m) all;   \
	done
endif

$(obj-m): $(rt2880_iNIC-objs)
	$(LD) -r $^ -o $@ -g -G 0 -n -Map rt2880_iNIC.map	
else
	#linux 2.6
all: 
	make -C $(LINUX_SRC) SUBDIRS=$(PWD) $(MAKE_FLAGS) modules
endif

ifeq ($(PLATFORM),BRCM)
	cp ./firmware/iNIC_ap.bin $(BRCM_ROOT)/targets/fs.src/lib/
	cp ./firmware/iNIC_ap.dat $(BRCM_ROOT)/targets/fs.src/lib/
	cp ./rt2880_iNIC.ko $(BRCM_ROOT)/targets/fs.src/lib/
endif
	
clean:
	rm -f $(COMM_OBJS) $(MII_OBJS) $(PCI_OBJS) $(PLATFORM_OBJS) Module.symvers *~ .*.cmd *.map *.o *.ko *.mod.c
	for d in $(subdir-m); \
    do                       \
      $(MAKE) --directory=$$d $@; \
    done


