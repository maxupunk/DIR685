#############################################################################

-include ../../arch.mk
-include ../../../path.mk

APPLET=dnrd
PREFIX=/usr/sbin

############################################################################

#NOMASTERMODE=y

#sources = args.c cache.c common.c dns.c lib.c main.c query.c relay.c sig.c udp.c
OBJS = main.o args.o cache.o common.o dns.o lib.o query.o relay.o sig.o udp.o tcp.o

#LDFLAGS += -lpthread

ifndef NOMASTERMODE
#sources += master.c
OBJS += master.o
else
CFLAGS+=-DNOMASTERMODE
endif

#CFLAGS+= -mapcs-32 -mtune=arm9tdmi -mshort-load-bytes

# add DEBUG flag by peterwu
#CFLAGS += -DDEBUG

.PHONY: all install clean

all: $(APPLET)

clean:
	@echo -e "\033[32mCleaning $(APPLET) ...\033[0m"
	$(Q)rm -f dnrd core tags ID *.o *.d *~ *.bak *.gdb *.elf

install:
	@echo -e "\033[32mInstalling $(APPLET) ...\033[0m"
	$(Q)[ -d $(TARGET)$(PREFIX) ] || mkdir -p $(TARGET)$(PREFIX)
	$(Q)install ./$(APPLET) $(TARGET)$(PREFIX)
	$(Q)chmod +x $(TARGET)$(PREFIX)/$(APPLET)

$(APPLET): $(OBJS)
	@echo -e "\033[32mBuilding $(APPLET) ...\033[0m"
	$(Q)$(CC)  $(LDFLAGS) $(OBJS) -o $(APPLET)
	$(Q)$(STRIP) $(APPLET)

main.o: main.c
	$(Q)$(CC) -c $(CFLAGS) main.c

args.o: args.c
	$(Q)$(CC) -c $(CFLAGS) args.c

cache.o: cache.c
	$(Q)$(CC) -c $(CFLAGS) cache.c

common.o: common.c
	$(Q)$(CC) -c $(CFLAGS) common.c
dns.o: dns.c
	$(Q)$(CC) -c $(CFLAGS) dns.c
lib.o: lib.c
	$(Q)$(CC) -c $(CFLAGS) lib.c
query.o: query.c
	$(Q)$(CC) -c $(CFLAGS) query.c
relay.o: relay.c
	$(Q)$(CC) -c $(CFLAGS) relay.c
sig.o: sig.c
	$(Q)$(CC) -c $(CFLAGS) sig.c
udp.o: udp.c
	$(Q)$(CC) -c $(CFLAGS) udp.c
master.o: master.c
	$(Q)$(CC) -c $(CFLAGS) master.c
tcp.o: tcp.c
	$(Q)$(CC) -c $(CFLAGS) tcp.c
