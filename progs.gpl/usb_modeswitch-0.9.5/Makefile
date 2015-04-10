USE_BRCM_TOOLS=n
-include ../arch.mk
-include ../../path.mk
HOST=i686-redhat-linux-gnu

BIN = usb_modeswitch
OBJS = usb_modeswitch.c
LIBNAME = libusb.a
LIBDIR = libusb-0.1.12
SCRIPTNAME = usb_mode_switch.sh

#CFLAGS = -O1 -Wall
LIBTAEGETDIR = $(LIBDIR)/.libs
MYLDFLAG = -I./$(LIBDIR)
MYLIBS = -L./$(LIBTAEGETDIR) -lusb -static

all: libusb
	$(Q)$(CC) $(CFLAGS) -o ${BIN} $(OBJS) $(MYLDFLAG) $(MYLIBS)
	$(Q)[ -z "$(STRIP)" ] || $(STRIP) $(BIN) usb_modeswitch

install: libusb-install
	cp ./$(BIN) $(TARGET)/usr/sbin/.
	cp ./$(SCRIPTNAME) $(TARGET)/etc/.
	chmod +x $(TARGET)/etc/$(SCRIPTNAME)

clean:
	make -C $(LIBDIR) clean
	rm ./$(LIBDIR)/Makefile
	rm ./$(BIN)

libusb:
	if test ! -s "$(LIBDIR)/Makefile"; \
	then cd $(LIBDIR) && /bin/sh configure --quiet --target=$(HOST_CPU) --host=$(HOST) \
	CC=$(CC) CXX=$(CXX) ;\
	fi	
	$(Q)make -C $(LIBDIR)
	

libusb-install:
	cp $(LIBTAEGETDIR)/libusb-0.1.so.4 $(TARGET)/lib/.

.PHONY: libusb libusb-install clean
