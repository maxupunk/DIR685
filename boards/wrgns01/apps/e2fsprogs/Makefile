-include ../../arch.mk
-include ../../path.mk

HOST=$(CROSS_COMPILE)gnu
PROG_DIR = e2fsprogs-1.41.3

all:
	if test ! -s "$(PROG_DIR)/Makefile"; \
	then cd $(PROG_DIR) && /bin/sh configure --host=$(HOST) CC=$(CC) AS=$(AS) AR=$(AR) \
	LD=$(LD) RANLIB=$(RANLIB) STRIP=$(STRIP) ;\
	fi	

	make -C $(PROG_DIR)
	$(STRIP) $(PROG_DIR)/misc/mke2fs
	
install:
	cp $(PROG_DIR)/misc/mke2fs $(TARGET)/usr/sbin/.

clean:
	if test -s "$(PROG_DIR)/Makefile"; \
	then make -C $(PROG_DIR) clean && rm -rf $(PROG_DIR)/Makefile;\
	fi