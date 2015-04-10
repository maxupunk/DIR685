-include ../path.mk
-include ../arch.mk
obj-m	:= emkey.o


PWD       := $(shell pwd)

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)

install:
	 $(Q)cp emkey.ko $(TARGET)/lib/modules/.

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions

