
-include ../../path.mk
-include ../../arch.mk

obj-m := nas_gpio_access.o

all:
	$(Q)make -C $(KERNELDIR) SUBDIRS=$(shell pwd) modules

clean:
	$(Q)rm -f *.o *.ko .nas_gpio_access* nas_gpio_access.mod.c Modules.symvers
	$(Q)rm -rf .tmp_versions

install:
	$(Q)cp nas_gpio_access.ko $(TARGET)/lib/modules/.

.PHONY: all clean install
