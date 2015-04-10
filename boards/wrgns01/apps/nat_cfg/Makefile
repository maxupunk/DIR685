#CC=arm-linux-gcc
-include ../../arch.mk
-include ../../path.mk 

ifndef CFLAGS
CFLAGS = -O2 -Wall -g
endif


OBJS =	nat_cfg.o  cli_add.o cli_del.o cli_set.o cli_show.o 
	

all: hw_nat_cfg

hw_nat_cfg: $(OBJS) cli_cfg.h  sl_nat_cfg.h
	$(CC) -o hw_nat_cfg $(OBJS)

install:
	$(Q)cp hw_nat_cfg $(TARGET)/usr/sbin/
	
.PHONY: all install clean 

clean:
	rm -f core *~ *.o hw_nat_cfg *.d


-include $(OBJS:%.o=%.d)

