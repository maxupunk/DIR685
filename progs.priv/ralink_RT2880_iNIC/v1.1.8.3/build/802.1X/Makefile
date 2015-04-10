include ../../../../arch.mk
include ../../../../../path.mk
include ../../../../../.config
#PLATFORM = 5VT
#PLATFORM = PC
#PLATFORM = STAR
#PLATFORM =  TWINPASS
#PLATFORM = SIGMA
#PLATFORM =  RT2880
PLATFORM = STORLINK
ifeq ($(PLATFORM),STORLINK)
CROSS_COMPILE = /opt/storlink_arm_920t_le_uclibc/bin/arm-linux-
endif

ifeq ($(PLATFORM),RT2880)
CROSS_COMPILE = /opt/buildroot-gdb/bin/mipsel-linux-
endif

ifeq ($(PLATFORM),TWINPASS)
CROSS_COMPILE = /opt/uclibc-toolchain/ifx-lxdb-1-1/gcc-3.3.6/toolchain-mips/bin/mips-linux-
CFLAGS +=  -DTMP_ROOT
POSFIX=_tw
endif

ifeq ($(PLATFORM),SIGMA)
CROSS_COMPILE = /opt/sigma/toolchain/smp86xx_toolchain_2.7.172.0/build_mipsel_nofpu/staging_dir/bin/mipsel-linux-
CFLAGS +=  -DTMP_ROOT
POSFIX=_sigma
endif

ifeq ($(PLATFORM),5VT)
CROSS_COMPILE = /opt/crosstool/uClibc_v5te_le_gcc_4_1_1/bin/arm-linux-
endif

ifeq ($(PLATFORM),STAR)
CROSS_COMPILE = /opt/star/tools/arm-linux/bin/arm-linux-
CFLAGS +=  -DTMP_ROOT
POSFIX=_star
endif

ifeq ($(PLATFORM),PC)
CROSS_COMPILE =
POSFIX=_pc
endif

CC = $(CROSS_COMPILE)gcc

ifndef CFLAGS
CFLAGS = -O2 -Wall -g -DDBG
endif


# If you want to support multiple radius server for multiple bssid, add following line
CFLAGS +=  -DMULTIPLE_RADIUS

OBJS =	rt2880apd.o eloop.o eapol_sm.o radius.o md5.o  \
	config.o ieee802_1x.o  \
	sta_info.o   radius_client.o

all: rt2880apd

rt2880apd: $(OBJS)
	$(CC) -o rt2880apd $(OBJS)
#	cp rt2880apd /tftpboot

clean:
	rm -f core *~ *.o rt2880apd *.d

-include $(OBJS:%.o=%.d)
