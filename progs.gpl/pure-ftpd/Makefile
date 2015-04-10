-include ../arch.mk
-include ../../path.mk
HOST=$(CROSS_COMPILE)gnu
all:
	if test ! -s "libiconv-1.9.1/Makefile"; \
	then cd libiconv-1.9.1 && /bin/sh configure --host=$(HOST) CC=$(CC) AS=$(AS) AR=$(AR) \
	LD=$(LD) RANLIB=$(RANLIB) STRIP=$(STRIP) ;\
	fi
	cp libiconv-1.9.1/srclib/Makefile_1 libiconv-1.9.1/srclib/Makefile
	make -C libiconv-1.9.1	
	make -C pure-ftpd-1.0.21
	
install:
	if test ! -s "$(TARGET)/lib/libiconv.so.2.2.0"; \
	then cp libiconv-1.9.1/lib/.libs/libiconv.so.2.2.0 $(TARGET)/lib/. ;\
	ln -s /lib/libiconv.so.2.2.0 $(TARGET)/lib/libiconv.so.2 ;\
	fi
	cp pure-ftpd-1.0.21/src/pure-ftpd $(TARGET)/sbin/.
	ln -s /var/ftp_tbl $(TARGET)/etc/ftp_tbl
	ln -s /var/ftpgroup $(TARGET)/etc/ftpgroup
clean:
	make -C libiconv-1.9.1/ clean ; \
	make -C pure-ftpd-1.0.21/ clean ;\
