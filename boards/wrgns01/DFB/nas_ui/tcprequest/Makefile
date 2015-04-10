-include ../../../arch.mk
-include ../../../../../path.mk

CFLAGS += -I./include 
all: tcprequest
objs = web_tcpreq.o main.o

tcprequest: $(objs)
	$(CC) $(CFLAGS) -o web_tcpreq $(objs)

install:
	$(Q)cp web_tcpreq $(TARGET)/directfb
	
clean:
	rm -f *.o *~ *.gdb *.elf web_tcpreq

.PHONY: all objects install clean
