-include ../arch.mk
-include ../../path.mk

HOST=$(CROSS_COMPILE)gnu

all:
	make -C zlib-1.2.1/
	make -C gdbm-1.8.3/
	make -C libid3tag-0.15.0b/
#if libiconv makefile exist , then it runs configure already, so we can build it
#else we run configure and the build
	if test ! -s "libiconv-1.9.1/Makefile"; \
	then cd libiconv-1.9.1 && /bin/sh configure --host=$(HOST) CC=$(CC) AS=$(AS) AR=$(AR) \
	LD=$(LD) RANLIB=$(RANLIB) STRIP=$(STRIP); \
	fi
	cp libiconv-1.9.1/srclib/Makefile_1 libiconv-1.9.1/srclib/Makefile
	make -C libiconv-1.9.1/ 
	make -C mt-daapd-0.2.4/
	make -C mDNSResponder-107.1

install:
	if test ! -s "$(TARGET)/lib/libz.a"; \
	then make -C zlib-1.2.1/ install ;\
	fi
	make -C gdbm-1.8.3/ install
	if test ! -s "$(TARGET)/lib/libid3tag.so.0"; \
	then make -C libid3tag-0.15.0b/ install ;\
	fi
#for libiconv, we need it share lib only
	if test ! -s "$(TARGET)/lib/libiconv.so.2.2.0"; \
	then cp libiconv-1.9.1/lib/.libs/libiconv.so.2.2.0 $(TARGET)/lib/. ;\
	ln -s /lib/libiconv.so.2.2.0 $(TARGET)/lib/libiconv.so.2 ;\
	fi

	cp -rf mt-daapd-0.2.4/admin-root/ $(TARGET)/etc/admin-root
	cp mt-daapd-0.2.4/src/mt-daapd $(TARGET)/sbin/.
	cp mt-daapd-0.2.4/contrib/mt-daapd.conf $(TARGET)/var/.
	ln -s /var/mt-daapd.conf $(TARGET)/etc/mt-daapd.conf


#	make mt-daapd-0.2.4/ install	
	make -C  mDNSResponder-107.1/ install

clean:
	make -C zlib-1.2.1/ clean
	make -C gdbm-1.8.3/ clean
	make -C libid3tag-0.15.0b/ clean
	make -C libiconv-1.9.1/ clean
	make -C mt-daapd-0.2.4/ clean
	make -C mDNSResponder-107.1/ clean
	

