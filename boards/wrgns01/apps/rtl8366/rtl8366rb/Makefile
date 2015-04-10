-include ../../../arch.mk
-include ../../../path.mk

TOPDIR=$(KERNELDIR)
RTL8366_OBJS	:= rtl8366rb.o gpio.o smi.o rtl8366rb_api.o rtl8368s_asicdrv.o alpha_igmp_snoop.o

obj-m           := switch.o
switch-objs := $(RTL8366_OBJS)


all:
	@echo -e "\033[32mBuilding Software module for RTL8366...\033[0m"
#	$(Q)make -C $(KERNELDIR) M=`pwd` modules 

install:
	@echo -e "\033[32mInstalling Software module for RTL8366...\033[0m"
	$(Q)[ -d $(TARGET)/lib/modules ] || mkdir -p $(TARGET)/lib/modules
	$(Q)cp switch.ko $(TARGET)/lib/modules

clean:
#	@echo -e "\033[32mCleaning Software module for RTL8366...\033[0m"
#	$(Q)find . \( -name '*.[oas]' -o -name core -o -name '.*.flags' \) -type f -print \
	        	| xargs rm -f
#	rm -rf *.o *.ko Module.symvers *.mod.* .*.cmd .tmp_versions tags
	
.PHONY: all install clean 
