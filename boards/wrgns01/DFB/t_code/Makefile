-include ../../arch.mk
-include ../../../path.mk

#LDFLAGS = -static -L../lib -ldirectfb -lpthread -ldl -lz -lfusion -ldirectla -ljpeg -lpng12 -lpng
#LDFLAGS =-static -L../lib -ldirectfb -lpthread -lz -lfusion -ldirectla -ljpeg -lpng12 -lpng -ldirect -lfreetype -lm

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
#LDFLAGS2 +=  $(pwd)/lib/directfb-1.1-0/inputdrivers/libdirectfb_keyboard.a
LDFLAGS2 += $(pwd)/lib/directfb-1.1-0/interfaces/IDirectFBImageProvider/libidirectfbimageprovider_gif.a 
LDFLAGS2 += -ljpeg -lpng12 -lpng  -lfreetype -lm

CFLAGS = -I../include/directfb

#RPATH = -Wl,--rpath -Wl,../lib
objects = showimg.o

all: $(objects)
	$(CC) $(RPATH) $(CFLAGS) -o showimg $(objects) $(LDFLAGS2) $(LDFLAGS)
	$(CC) $(RPATH) $(CFLAGS) -o showimg_ok showimg_ok.c  $(LDFLAGS2) $(LDFLAGS)
	
install:
	cp showimg $(TARGET)/usr/sbin/.

clean:
	rm -rf *.o
	rm showimg
	rm showimg_ok
