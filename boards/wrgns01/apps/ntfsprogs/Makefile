-include ../../arch.mk
-include ../../path.mk
HOST=$(CROSS_COMPILE)gnu
#CPP	= /opt/storlink_920t_le/bin/arm_920t_le-g++
CXX	= /opt/storlink_920t_le/bin/arm_920t_le-g++

all:
	if test ! -s "ntfsprogs-2.0.0/Makefile"; \
	then cd ntfsprogs-2.0.0 && /bin/sh configure --host=$(HOST) CC=$(CC) AS=$(AS) AR=$(AR) \
	LD=$(LD) RANLIB=$(RANLIB) STRIP=$(STRIP) --enable-really-static CXX=$(CXX) ;\
	fi	

	make -C ntfsprogs-2.0.0 
	$(STRIP) ntfsprogs-2.0.0/ntfsprogs/mkntfs
	
install:
	cp ntfsprogs-2.0.0/ntfsprogs/mkntfs $(TARGET)/usr/sbin/.

clean:
	if test -s "ntfsprogs-2.0.0/Makefile"; \
	then make -C ntfsprogs-2.0.0 clean && rm -rf ntfsprogs-2.0.0/Makefile;\
	fi
