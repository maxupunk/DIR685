-include ../../path.mk
-include ../../arch.mk
TARGET_DRV := sata
ifneq ($(KERNELRELEASE),)
obj-m	:= sata.o
sata-objs:=sata0_storlink.o

CFLAGS+=-I$(NOW_PWD) -I$(KERNELDIR)/include
PWD       := $(shell pwd)
else
all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)/sata_driver/

install:
	 $(Q)cp $(TARGET_DRV).ko $(TARGET)/lib/modules/.

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions
endif
