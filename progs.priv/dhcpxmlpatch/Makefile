
-include ../arch.mk
-include ../../path.mk

PREFIX:=/usr/sbin

all: dhcpxmlpatch
objects: dhcpxmlpatch.o lrgdb.o

dhcpxmlpatch: Makefile dhcpxmlpatch.o lrgdb.o
	@echo -e "\033[32mBuilding dhcpxmlpatch ...\033[0m"
	$(Q)$(CC) -o dhcpxmlpatch dhcpxmlpatch.o lrgdb.o

dhcpxmlpatch.o: Makefile dhcpxmlpatch.c
	$(Q)$(CC) -c $(CFLAGS) dhcpxmlpatch.c

lrgdb.o: Makefile lrgdb.c
	$(Q)$(CC) -c $(CFLAGS) lrgdb.c

install:
	@echo -e "\033[32mInstalling dhcpxmlpatch ...\033[0m"
	$(Q)[ -d $(TARGET)$(PREFIX) ] || mkdir -p $(TARGET)$(PREFIX)
	$(Q)$(STRIP) ./dhcpxmlpatch
	$(Q)install ./dhcpxmlpatch $(TARGET)$(PREFIX)
	$(Q)chmod +x $(TARGET)$(PREFIX)/dhcpxmlpatch

clean:
#	@echo -e "\033[32mCleaning dhcpxmlpatch ...\033[0m"
#	$(Q)rm -f *.o *.gdb *.elf *~ dhcpxmlpatch

.PHONY: all objects clean
