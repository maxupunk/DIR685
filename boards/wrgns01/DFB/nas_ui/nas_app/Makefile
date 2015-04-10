-include ../../../arch.mk
-include ../../../../../path.mk
-include ../config.mk

pwd=$(shell pwd)/../../
LDFLAGS +=-static
LDFLAGS += $(pwd)/lib/directfb-1.1-0/systems/libdirectfb_fbdev.o
LDFLAGS += $(pwd)/lib/directfb-1.1-0/wm/libdirectfbwm_default.o
LDFLAGS += $(pwd)/lib/directfb-1.1-0/inputdrivers/libdirectfb_linux_input.o
LDFLAGS += -L$(pwd)/lib -ldirectfb -lfusion -ldirect -lpthread -lz -ldl 
LDFLAGS2 = $(pwd)/lib/directfb-1.1-0/interfaces/IDirectFBImageProvider/libidirectfbimageprovider_png.a
LDFLAGS+= $(pwd)/lib/directfb-1.1-0/interfaces/IDirectFBImageProvider/libidirectfbimageprovider_dfiff.a
LDFLAGS2 +=  $(pwd)/lib/directfb-1.1-0/interfaces/IDirectFBImageProvider/libidirectfbimageprovider_jpeg.a
LDFLAGS2 +=  $(pwd)/lib/directfb-1.1-0/interfaces/IDirectFBImageProvider/libidirectfbimageprovider_mpeg2.a
LDFLAGS2 +=  $(pwd)/lib/directfb-1.1-0/interfaces/IDirectFBFont/libidirectfbfont_default.a
LDFLAGS2 +=  $(pwd)/lib/directfb-1.1-0/interfaces/IDirectFBFont/libidirectfbfont_ft2.a
LDFLAGS2 += $(pwd)/lib/directfb-1.1-0/interfaces/IDirectFBImageProvider/libidirectfbimageprovider_gif.a
LDFLAGS2 += -ljpeg -lpng12 -lpng  -lfreetype -lm -L$(TOPDIR)/comlib

CFLAGS += -I../../include/directfb -I./include -I../sam_toolkit/include -I../fcrss_server/include -I$(TOPDIR)/include \
		-I../tcprequest/include -I../frameit_server/include -I../include -I../upnp_control/Platinum/Alpha_MediaController/include

#ugly flag for 8366rb switch joel
include $(TOPDIR)/progs.board/customer.mk
ifdef CHIP_RTL8366SR
else
CFLAGS += -DRTL8366RB
endif

CFLAGS += -I$(TOPDIR)/kernel

#hendry add for default storage filesystem
#CFLAGS += -DDEFAULT_STORAGE_FS=\"EXT3\"

#RPATH = -Wl,--rpath -Wl,/usr/local/lib
VPATH = ../sam_toolkit:../fcrss_server

objs_all := $(patsubst %.c, %.o, $(wildcard *.c)) ../sam_toolkit/file_tool.o ../sam_toolkit/str_tool.o \
			../fcrss_server/fcrss_parser.o ../fcrss_server/fcrss_serialize.o $(TOPDIR)/comlib/libxmldbc.o \
			../tcprequest/web_tcpreq.o upnp_controller/upnp_cmd_handler.o upnp_controller/packet_serialize.o \
			upnp_controller/upnp_media_server.o upnp_controller/upnp_media_renderer.o upnp_controller/upnp_media_center.o \
			frameIt/frameit_display_app.o frameIt/frameit_handler.o
			
alpha_nas: $(objs_all)
	$(CC) $(RPATH) $(CFLAGS) $^ -o $@ $(LDFLAGS2) $(LDFLAGS) 
	
install:
	$(Q)mkdir -p $(TARGET)/directfb
	$(Q)cp -rf ./images $(TARGET)/directfb
ifndef UPNP_CONTROLLER
	rm -rf $(TARGET)/directfb/images/M 
endif
	$(Q)cp -rf ./font $(TARGET)/directfb
	$(Q)cp alpha_nas $(TARGET)/directfb	
	
clean: 
	rm -f *.o alpha_nas
	rm -f frameIt/*.o
	rm -f upnp_controller/*.o
	rm -f ../fcrss_server/*.o ../fcrss_server/fcrss_server	
	rm -f ../framit_server/*.o ../framit_server/framit_server	
	rm -f ../sam_toolkit/*.o
	rm -f ../tcprequest/*.o web_tcpreq	
.PHONY: all install clean
