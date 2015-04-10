
#-include ../path.mk
#-include ../arch.mk
##TARGET_DRV := i2c_alpha
#NOW_PWD := $(shell pwd)
#TARGET_DRV := i2c
#ifneq ($(KERNELRELEASE),)
obj-y := i2c.o
i2c-objs :=i2c_alpha.o key_handler.o 

#else
#all:
#	$(Q)make -C $(KERNELDIR) SUBDIRS=$(shell pwd) modules
#	$(Q)make -C $(KERNELDIR) M=`pwd` modules
#	$(CC) test_emu.c -o test_emu
#clean:
#	$(Q)rm -f *.o *.ko .i2c_alpha* i2c_alpha.mod.c Modules.symvers
#	$(Q)rm -rf .tmp_versions
#	$(Q)rm test_emu
#install:
#	$(Q)cp $(TARGET_DRV).ko $(TARGET)/lib/modules/.
#endif
#.PHONY: all clean install
