
-include ../arch.mk
-include ../../path.mk

TGT:=portt trigger

all: $(TGT)
	@echo -e "\033[32mBuilding portt ...\033[0m"

%: %.c
	$(Q)$(CC) $(CFLAGS) -o $@ $<

install:
	@echo -e "\033[32mInstalling portt ...\033[0m"
	$(Q)[ -d $(TARGET)/usr/sbin ] || mkdir -p $(TARGET)/usr/sbin
	$(Q)cp portt	$(TARGET)/usr/sbin/.
	$(Q)cp trigger	$(TARGET)/usr/sbin/.

clean:
#	@echo -e "\033[32mCleaning portt ...\033[0m"
#	$(Q)rm -f *.o $(TGT)

.PHONY: all install clean
