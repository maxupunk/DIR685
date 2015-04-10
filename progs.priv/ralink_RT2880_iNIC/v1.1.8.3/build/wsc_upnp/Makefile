#############################################################
# Makefile for WSC upnp module
#############################################################
-include ../../../../arch.mk
-include ../../../../path.mk

#CROSS_COMPILE = 
TARGET_HOST = arm-linux
#CC = $(CROSS_COMPILE)gcc
#LD = $(CROSS_COMPILE)ld
#STRIP = $(CROSS_COMPILE)strip
WIRELESS_H_INCLUDE_PATH = $(KERNELDIR)/include/

PWD = $(shell pwd)
LIBUPNP_SRC_PATH = libupnp-1.3.1
LIBUPNP_LIB_PATH = $(PWD)/$(LIBUPNP_SRC_PATH)

INCLUDE_PATH := -I. -I$(LIBUPNP_SRC_PATH) -I$(LIBUPNP_SRC_PATH)/upnp/inc -I$(LIBUPNP_SRC_PATH)/upnp/src/inc
INCLUDE_PATH += -I$(LIBUPNP_SRC_PATH)/ixml/inc -I$(LIBUPNP_SRC_PATH)/ixml/src/inc  -I$(LIBUPNP_SRC_PATH)/threadutil/inc
INCLUDE_PATH += -I$(WIRELESS_H_INCLUDE_PATH)

INCLUDE_LIBS := -static -L$(LIBUPNP_LIB_PATH)/upnp/.libs/ -lupnp -L$(LIBUPNP_LIB_PATH)/ixml/.libs/ -lixml -L$(LIBUPNP_LIB_PATH)/threadutil/.libs -lthreadutil -lpthread
#INCLUDE_LIBS := -L$(PWD) -lupnp -lixml -lthreadutil -lpthread

OBJS = wsc_main.o wsc_common.o wsc_ioctl.o wsc_netlink.o wsc_upnp_device.o wsc_upnp_cp.o sample_util.o wsc_msg.o

EXEC = wscd

CFLAGS += -O2 -Wall -D_REENTRANT $(INCLUDE_PATH)
CFLAGS += -DRT_DEBUG
###
#if you want to build the wscd for multiple card support, add following flag to CFALGS
###
#CFLAGS += -DMULTIPLE_CARD_SUPPORT

all: $(EXEC)

$(LIBUPNP_SRC_PATH)/Makefile:
	chmod +x $(LIBUPNP_SRC_PATH)/configure
	if test ! -s "$(LIBUPNP_SRC_PATH)/Makefile"; \
	    then cd $(LIBUPNP_SRC_PATH) && /bin/sh configure  --host=$(TARGET_HOST) CC=$(CC) AS=$(AS) AR=$(AR) \
		    LD=$(LD) RANLIB=$(RANLIB) STRIP=$(STRIP) ;\
	fi
	make -C $(LIBUPNP_SRC_PATH) -f Makefile.src TARGET_HOST=$(TARGET_HOST)

$(EXEC): libupnp $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS) $(LIBS) $(INCLUDE_LIBS)
	$(STRIP) -s $(EXEC)

libupnp: $(LIBUPNP_SRC_PATH)/Makefile 
	make -C $(LIBUPNP_SRC_PATH)
	cp $(LIBUPNP_LIB_PATH)/upnp/.libs/libupnp.a .
	cp $(LIBUPNP_LIB_PATH)/ixml/.libs/libixml.a .
	cp $(LIBUPNP_LIB_PATH)/threadutil/.libs/libthreadutil.a .

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf *.o *~ *.bak $(LIBUPNP_SRC_PATH)/Makefile $(EXEC)

cleanall: clean
	$(Q)if [ -f $(LIBUPNP_SRC_PATH)/Makefile ]; then \
		make -C $(LIBUPNP_SRC_PATH) clean; \
		rm -f *.a; \
		rm -f libupnp-1.3.1/Makefile; \
	fi

