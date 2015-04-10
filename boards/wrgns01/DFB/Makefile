-include ../arch.mk
-include ../path.mk

pwd=$(shell pwd)

all:
	if test ! -s "bin/";\
	then mkdir bin/;\
	fi
	if test ! -s "include/";\
        then mkdir include/;\
        fi
	if test ! -s "lib/";\
        then mkdir lib/;\
        fi
	make -C zlib-1.2.3
	make -C zlib-1.2.3 install
	make -C jpeg-6b  
	make -C jpeg-6b  install
	make -C libpng-1.2.25  
	make -C libpng-1.2.25  install
	if test ! -s "freetype-2.3.5/builds/unix/unix-cc.mk"; \
	then cd freetype-2.3.5/builds/unix/ && ./configure --host=$(CROSS_COMPILE)gnu CC=$(CC) AS=$(AS) AR=$(AR) LD=$(LD) \
	RANLIB=$(RANLIB) STRIP=$(STRIP) --prefix=$(pwd) CFLAGS=-I$(pwd)/include LDFLAGS=-L$(pwd)/lib ;\
	fi
	make -C freetype-2.3.5  
	make -C freetype-2.3.5 install
	if test ! -s "DirectFB-1.1.1/Makefile"; \
	then cd DirectFB-1.1.1 && ./configure --host=$(CROSS_COMPILE)gnu CC=$(CC) AS=$(AS) AR=$(AR) \
	LD=$(LD) RANLIB=$(RANLIB) STRIP=$(STRIP) --prefix=$(pwd) \
	--disable-x11 --disable-sdl --enable-shared --enable-static --with-gfxdrivers=none --enable-jpeg\
	--with-inputdrivers=linuxinput,keyboard CFLAGS="-I$(pwd)/include -I$(pwd)/include/freetype2" \
	LDFLAGS="-L$(pwd)/lib -lfreetype"; \
	fi
	make -C DirectFB-1.1.1
	make -C DirectFB-1.1.1 install
	make -C nas_ui
install:
	$(Q)mkdir -p $(TARGET)/directfb
	cp ./directfbrc $(TARGET)/directfb/.
	cp ./bin/djpeg $(TARGET)/directfb/.
	cp ./bin/cjpeg $(TARGET)/directfb/.
	make -C nas_ui install	
clean:
	make -C jpeg-6b  clean
	make -C libpng-1.2.25  clean
	make -C nas_ui clean	 
	make -C zlib-1.2.3 clean
	make -C freetype-2.3.5 clean
	rm -f freetype-2.3.5/builds/unix/unix-cc.mk
	make -C DirectFB-1.1.1 distclean
	rm bin -rf
	rm include -rf
	rm lib -rf	
	rm man -rf
