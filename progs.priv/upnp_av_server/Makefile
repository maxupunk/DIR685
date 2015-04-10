-include ../arch.mk
-include ../../path.mk
HOST=$(CROSS_COMPILE)gnu
all:
	make -C zlib-1.2.1/
	if test ! -s "sqlite-3.5.8/Makefile"; \
	then cd sqlite-3.5.8 && /bin/sh configure --host=$(HOST) CC=$(CC) AS=$(AS) AR=$(AR) \
	LD=$(LD) RANLIB=$(RANLIB) STRIP=$(STRIP) ;\
	fi	
	make -C sqlite-3.5.8 	
	if test ! -s "libiconv-1.9.1/Makefile"; \
	then cd libiconv-1.9.1 && /bin/sh configure --host=$(HOST) CC=$(CC) AS=$(AS) AR=$(AR) \
	LD=$(LD) RANLIB=$(RANLIB) STRIP=$(STRIP) ;\
	fi	
	cp libiconv-1.9.1/srclib/Makefile_1 libiconv-1.9.1/srclib/Makefile
	make -C libiconv-1.9.1	
	if test ! -s "libid3tag-0.15.0b/Makefile"; \
	then cd libid3tag-0.15.0b && /bin/sh configure --host=$(HOST) CC=$(CC) AS=$(AS) AR=$(AR) \
	LD=$(LD) RANLIB=$(RANLIB) STRIP=$(STRIP) CPPFLAGS=-I../zlib-1.2.1/ LDFLAGS=-L../zlib-1.2.1/ ;\
	fi
	make -C gdbm-1.8.3
	make -C libid3tag-0.15.0b
	make -C upnp_av
	make -C media_type
	make -C inotify-tools-3.13
	make -C ScanMedia
	make -C UpdateMediaDB
	
install:
	if test ! -s "$(TARGET)/lib/libz.a"; \
	then make -C zlib-1.2.1/ install ;\
	fi
		
	if test ! -s "$(TARGET)/lib/libiconv.so.2.2.0"; \
	then cp libiconv-1.9.1/lib/.libs/libiconv.so.2.2.0 $(TARGET)/lib/. ;\
	ln -s /lib/libiconv.so.2.2.0 $(TARGET)/lib/libiconv.so.2 ;\
	fi
	
	if test ! -s "$(TARGET)/lib/libid3tag.so.0"; \
	then make -C libid3tag-0.15.0b/ install ;\
	fi
	
	cp sqlite-3.5.8/.libs/libsqlite3.so.0.8.6 $(TARGET)/lib/.
	ln -s /lib/libsqlite3.so.0.8.6 $(TARGET)/lib/libsqlite3.so.0
	
	if test ! -s "$(TARGET)/lib/libgdbm.so.3"; \
	then make -C gdbm-1.8.3/ install ;\
	fi
	
	cp upnp_av/upnp $(TARGET)/usr/sbin/.
	ln -s /var/shared_name $(TARGET)/etc/shared_name
	ln -s /var/upnpav.conf $(TARGET)/etc/upnpav.conf
	ln -s /tmp/storage_dev $(TARGET)/mnt/HD_a2
	cp ScanMedia/ScanMedia $(TARGET)/usr/sbin/.
	cp inotify-tools-3.13/src/.libs/inotifywait $(TARGET)/usr/sbin/.
	ln -s /usr/sbin/inotifywait $(TARGET)/usr/sbin/inotify_uPNP
	ln -s /usr/sbin/inotifywait $(TARGET)/usr/sbin/inotify_iTune
	cp UpdateMediaDB/UpdateMediaDB $(TARGET)/bin/.
	cp inotify-tools-3.13/libinotifytools/src/.libs/libinotifytools.so.0 $(TARGET)/lib/.
	cp ScanMedia/set_scan_media_db $(TARGET)/usr/sbin/.
clean:
#	make -C zlib-1.2.1/ clean
#	make -C sqlite-3.5.8/ clean 
#	make -C libiconv-1.9.1 clean
#	make -C upnp_av/ clean 
#	make -C libid3tag-0.15.0b/ clean
#	make -C media_type clean
#	make -C UpdateMediaDB clean
#	make -C inotify-tools-3.13 clean
#	make -C ScanMedia clean	
#	make -C gdbm-1.8.3 clean
