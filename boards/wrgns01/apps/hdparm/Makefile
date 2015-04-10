-include ../../arch.mk
-include ../../path.mk
HOST=$(CROSS_COMPILE)gnu

APPLET		:= smart_spindown
LOCAL_SRCS	:= smart_spindown.c
CMLIB_SRCS	:= libxmldbc.c

-include $(TOPDIR)/Rules.mk

all: $(APPLET)
	make -C hdparm-8.9/	
#	cp smart_spindown /nfsroot/hendry/elbox/sb/smart
	
install:
	cp hdparm-8.9/hdparm $(TARGET)/usr/sbin/.
	cp $(APPLET) $(TARGET)/usr/sbin/.

clean:
	make -C hdparm-8.9/ clean ;
	-rm -f $(APPLET) *.elf *.gdb *.o

