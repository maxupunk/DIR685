-include ../../../arch.mk
-include ../../../../../path.mk

pwd=$(shell pwd)/../../
LDFLAGS +=-static
LDFLAGS += -L$(pwd)/lib -lpthread -lz -ldl -L$(TOPDIR)/comlib
CFLAGS += -I./include -I../sam_toolkit/include -I../nas_app/include -I../tcprequest/include -I$(TOPDIR)/include -I../include
VPATH = ../sam_toolkit

objs_server := fcrss_parser_server.o fcrss_parser.o fcrss_serialize.o ../sam_toolkit/str_tool.o \
			../tcprequest/web_tcpreq.o ../sam_toolkit/file_tool.o $(TOPDIR)/comlib/libxmldbc.o
objs_install = fcrss_parser.o fcress_serialize.o str_tool.o file_tool.o  

fcrss_server: $(objs_server)	
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) 
	
fcrss_client: $(objs_client)
	$(CC) $(LDFLAGS) $(CFLAGS) $^ -o $@
		
install:
	$(Q)mkdir -p $(TARGET)/directfb
	$(Q)cp fcrss_server $(TARGET)/directfb
	
clean: 
	rm -f *.o fcrss_server 
	rm -f ../sam_toolkit/*.o
	rm -f ../tcprequest/*.o	

.PHONY: fcrss_server install clean	
