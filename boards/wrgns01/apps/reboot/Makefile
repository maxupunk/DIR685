
EXEC = reboot
OBJS = reboot.o

all: $(EXEC)

#CFLAGS += -I/opt/toolchain_mips/mips-linux/include

reboot: reboot.c
	@echo -e "\033[32mBuilding reboot ...\033[0m"
	$(Q)$(CC) $(CFLAGS) -o reboot reboot.c
	

install:
	@echo -e "\033[32mInstalling reboot apps ...\033[0m"
	$(Q)[ -d $(TARGET)/usr/sbin ] || mkdir -p $(TARGET)/usr/sbin
	$(Q)cp $(EXEC) $(TARGET)/usr/sbin/.
	$(Q)chmod +x $(TARGET)/usr/sbin/$(EXEC)

clean:
	-rm -f $(EXEC) *.elf *.gdb *.o


