-include ../../arch.mk
-include ../../path.mk

HOST=$(CROSS_COMPILE)gnu
CPP	= /opt/storlink_920t_le/bin/arm_920t_le-g++
#CPP 	= $(CXX)
LDFLAGS	= -static
CPPFLAGS = -I$(KERNELDIR)/include

APPLET		:= smartmon
LOCAL_SRCS	:= smartmon.c
COMLIB		:= $(TOPDIR)/comlib
COMINC		:= $(TOPDIR)/include
CMLIB_SRCS	:= libxmldbc.c
CMLIB_OBJS	:= $(patsubst %c,%o,$(CMLIB_SRCS))

-include $(TOPDIR)/Rules.mk

all: $(APPLET)
	if test ! -s "smartmontools-5.38/Makefile"; \
	then cd smartmontools-5.38 && /bin/sh configure --host=$(HOST) CXX=$(CPP) AS=$(AS) AR=$(AR) \
	LD=$(LD) LDFLAGS=$(LDFLAGS) RANLIB=$(RANLIB) STRIP=$(STRIP) CPPFLAGS=$(CPPFLAGS) ;\
	fi	
	make -C smartmontools-5.38/
	$(STRIP) smartmontools-5.38/smartctl
	
install:
	cp smartmontools-5.38/smartctl $(TARGET)/usr/sbin/.

	@echo -e "\033[32mInstalling $(APPLET) ...\033[0m"
	$(Q)[ -d $(TARGET)/usr/sbin ] || mkdir -p $(TARGET)/usr/sbin
	$(Q)cp $(APPLET) $(TARGET)/usr/sbin/.
	$(Q)chmod +x $(TARGET)/usr/sbin/$(APPLET)

clean:
	if test -s "smartmontools-5.38/Makefile"; \
	then make -C smartmontools-5.38/ clean && rm -rf smartmontools-5.38/Makefile;\
	fi	
	-rm -f $(APPLET) *.elf *.gdb *.o
