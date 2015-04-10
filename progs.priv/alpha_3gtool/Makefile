
# Makefile Template

-include ../arch.mk
-include ../../path.mk
HOST=$(CROSS_COMPILE)gnu

APPLET      := alpha_3gtool
LOCAL_SRCS  := $(APPLET).c
CMLIB_SRCS  := libxmldbc.c

CFLAGS += -I$(TOPDIR)/include

-include $(TOPDIR)/Rules.mk

all: $(APPLET)

install:
#install: $(APPLET)
	@echo -e "\033[32mInstalling $(APPLET) ...\033[0m"
	$(Q)[ -d $(TARGET)/usr/sbin ] || mkdir -p $(TARGET)/usr/sbin
	$(Q)$(STRIP) $(APPLET)
	$(Q)install $(APPLET) $(TARGET)/usr/sbin/.

clean:
#	@echo -e "\033[32mCleaning $(APPLET) ...\033[0m"
#	$(Q)rm -f *.o *~ *.gdb *.elf $(APPLET)
.PHONY:	all install clean

