#-include ../arch.mk
#-include ../path.mk
#NOW_PWD := $(shell pwd)
#KERNEL_SRC := $(NOW_PWD)/../../../kernel
#KERNEL_SRC :=$(KERNELDIR)
#TARGET_DRV := tve200fb
#ifneq ($(KERNELRELEASE),)
obj-y := tve200fb.o

tve200fb-objs := tve200-fb.o ffb-lib.o sl35xx_tve.o fmem.o
#tve200fb-objs := tve200-fb.o ffb-lib.o fmem.o
#CFLAGS+=-I$(NOW_PWD) -I/home/marco/0527_nas_nearly_final/boards/wrgns01/tve200fb
#CFLAGS+=-I$(NOW_PWD) -I./
#else
#all: 
#	make  -C  /source/kernel/linux SUBDIRS=/source/tve200fb modules
#	$(MAKE) V=1 -Wall -C $(KERNEL_SRC) M=/home/marco/joely_test/kernels/storm3516/drivers/tve200fb/ modules
#	arm_920t_le-gcc -o fbtest fbtest.c
#	$(CC) -o fbtest fbtest.c
#	$(CC) -o fbfiles fbfiles.c
#install:
#	cp $(TARGET_DRV).ko $(TARGET)/lib/modules/.
#clean:
#	rm -rf *.o 
#	rm -rf *.ko
#	rm -f fbtest
#endif
