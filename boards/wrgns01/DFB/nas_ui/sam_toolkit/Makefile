-include ../../../arch.mk
-include ../../../../../path.mk
-include ../config.mk
CFLAGS += -I$(TOPDIR)/include -I./include -I../fcrss_server/include -I../nas_app/include -I../tcprequest/include 

objs_all :=  $(patsubst %.c, %.o, $(wildcard *.c)) ../tcprequest/web_tcpreq.o   
objs_install = file_tool.o str_tool.o ../tcprequest/web_tcpreq.o

all: $(objs_all)
	$(CC) $(LDFLAGS) $(CFLAGS) -o check_domain_name $(objs_all)	-lpthread
install:
	$(Q)cp check_domain_name $(TARGET)/directfb	
clean: 
	rm -f *.o check_domain_name 
