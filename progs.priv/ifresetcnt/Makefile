-include ../../arch.mk
-include ../../path.mk
-include ../../.config

ifeq ($(strip $(ELBOX_PROGS_PRIV_IFRESETCNT_26)),y)
BIN := ifresetcnt.ko
obj-m += ifresetcnt.o
all:
	@echo -e "\033[32mBuilding driver for kernel 2.6(Network interface reset count)...\033[0m"
	$(Q)make -C $(KERNELDIR) M=`pwd` modules

clean:
#	@echo -e "\033[32mCleaning driver (Network interface reset count)...\033[0m"
#	$(Q)make -C $(KERNELDIR) M=`pwd` clean
#	$(Q)rm -f *~

else
-include ../arch.mk
BIN := ifresetcnt.o
CFLAGS = $(KCFLAGS) -I$(KERNELDIR)/include
%.o:	%.c
	@echo -e "\033[32mBuilding driver for kernel 2.4(Network interface reset count)...\033[0m"
	$(Q)$(KCC) $(CFLAGS) -c $< -o $@

all:    $(BIN)

clean:
#	@echo -e "\033[32mCleaning driver (Network interface reset count)...\033[0m"
#	$(Q)rm -f *~ *.o

endif

install:
	@echo -e "\033[32mInstalling driver (Network interface reset count)...\033[0m"
	$(Q)[ -d $(TARGET)/lib/modules ] || mkdir -p $(TARGET)/lib/modules
	$(Q)[ -z $(STRIP) ] || $(STRIP) -g ./$(BIN)
	$(Q)cp -a ./$(BIN) $(TARGET)/lib/modules/

.PHONY: all install clean
