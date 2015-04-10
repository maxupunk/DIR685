-include ../arch.mk
-include ../../path.mk

HOST=$(CROSS_COMPILE)gnu

all:
#if libiconv makefile exist , then it runs configure already, so we can build it
#else we run configure and the build
	if test ! -s "libiconv-1.9.1/Makefile"; \
	then cd libiconv-1.9.1 && /bin/sh configure --host=$(HOST) CC=$(CC) AS=$(AS) AR=$(AR) \
	LD=$(LD) RANLIB=$(RANLIB) STRIP=$(STRIP); \
	fi
	cp libiconv-1.9.1/srclib/Makefile_1 libiconv-1.9.1/srclib/Makefile
	make -C libiconv-1.9.1/ 
	make -C samba-3.0.25a/

install:
#for libiconv, we need it share lib only
	if test ! -s "$(TARGET)/lib/libiconv.so.2.2.0"; \
	then cp libiconv-1.9.1/lib/.libs/libiconv.so.2.2.0 $(TARGET)/lib/. ;\
	ln -s /lib/libiconv.so.2.2.0 $(TARGET)/lib/libiconv.so.2 ;\
	fi

#	cp samba-3.0.25a/source/bin/nmbd  $(TARGET)/bin/.
	cp samba-3.0.25a/source/bin/smbd $(TARGET)/bin/.
	$(Q)ln -fs /bin/smbd $(TARGET)/usr/sbin/nmbd
	$(Q)ln -fs /bin/smbd $(TARGET)/usr/sbin/smbpasswd
#	cp samba-3.0.25a/source/bin/smbpasswd $(TARGET)/bin/.
#	$(Q)$(STRIP) $(TARGET)/bin/nmbd
	$(Q)$(STRIP) $(TARGET)/bin/smbd
#	$(Q)$(STRIP) $(TARGET)/bin/smbpasswd

clean:
	make -C libiconv-1.9.1/ clean
	rm libiconv-1.9.1/Makefile
	make -C samba-3.0.25a/ clean
	

