# Makefile for klogd

-include ../arch.mk
-include ../../path.mk

APPLET = klogd

CFLAGS+= -I$(TOPDIR)/include

all:	$(APPLET)

install:
	@echo -e "\033[32mInstalling klogd ...\033[0m"
	$(Q)[ -d $(TARGET)/sbin ] || mkdir -p $(TARGET)/sbin
	$(Q)install $(APPLET) $(TARGET)/sbin/.

$(APPLET): klogd.o
	@echo -e "\033[32mBuilding klogd ...\033[0m"
	$(Q)$(CC) $(LDFLAGS) klogd.o -o $(APPLET)
	$(Q)$(STRIP) $(APPLET)

klogd.o: Makefile klogd.c
	$(Q)$(CC) -c $(CFLAGS) klogd.c

clean:
	@echo -e "\033[32mCleaning klogd ...\033[0m"
	$(Q)rm -f *.o *~ *.gdb *.elf $(APPLET)

.PHONY:	all install clean
