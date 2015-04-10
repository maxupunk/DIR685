
-include ../../config.arch
-include ../../../config.path

CFLAGS += -I../include

PREFIX = /usr/sbin

IPOBJ=ip.o ipaddress.o iproute.o iprule.o \
    rtm_map.o iptunnel.o ipneigh.o iplink.o \
    ipmaddr.o ipmonitor.o ipmroute.o \
    ipxfrm.o xfrm_state.o xfrm_policy.o

RTMONOBJ=rtmon.o

ALLOBJ=$(IPOBJ) $(RTMONOBJ)
#TARGETS=ip rtmon
TARGETS=ip

all: $(TARGETS)
	$(STRIP) ./$(TARGETS)
	
ip: $(IPOBJ) $(LIBNETLINK) $(LIBUTIL)

rtmon: $(RTMONOBJ) $(LIBNETLINK)

install: all
	[ -d $(TARGET)$(PREFIX) ] || mkdir -p $(TARGET)$(PREFIX) 
	install ./$(TARGETS) $(TARGET)$(PREFIX)
	#install -m 0755 routel routef $(TARGET)$(PREFIX)

clean:
	rm -f $(ALLOBJ) $(TARGETS)

