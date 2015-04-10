-include ../arch.mk
-include ../../path.mk

EXEC	= rndimage
OBJS	= main.o jpeg_file.o graphics.o
CFLAGS	+= -DLINUX -Wall -Wno-char-subscripts

all: $(EXEC)
	@echo -e "\033[32m$(EXEC): generating binary executioin files ...\033[0m"

$(EXEC): Makefile $(OBJS)
	$(Q)$(CC) -o $(EXEC) $(CFLAGS) $(LDFLAGS) $(OBJS)
	$(Q)[ -z "$(STRIP)" ] || $(STRIP) $(EXEC)

install:
#install: $(EXEC)
	@echo -e "\033[32m$(EXEC): installing binary executioin files ...\033[0m"
	$(Q)install -c $(EXEC) $(TARGET)/usr/sbin/$(EXEC)
	$(Q)cp -r fonts $(TARGET)/usr/sbin/.

.c.o: Makefile
	$(Q)$(CC) -c -o $@ $(CFLAGS) $<

clean:
#	@echo -e "\033[32m$(EXEC): cleaning binary executioin files ...\033[0m"
#	$(Q)rm -f *.o *.gdb *~ *.elf $(EXEC)
