###############################################################

ARCH_CONFIG = ../../config.arch
PATH_CONFIG = ../../../config.path
-include $(ARCH_CONFIG)
-include $(PATH_CONFIG)

APPLET = tc
PREFIX = /usr/sbin

###############################################################
TCOBJ= tc.o tc_qdisc.o tc_class.o tc_filter.o tc_util.o \
       m_police.o m_estimator.o m_action.o

include ../Config

TCMODULES :=
TCMODULES += q_fifo.o
TCMODULES += q_sfq.o
TCMODULES += q_red.o
TCMODULES += q_prio.o
TCMODULES += q_tbf.o
TCMODULES += q_cbq.o
TCMODULES += f_rsvp.o
TCMODULES += f_u32.o
TCMODULES += f_route.o
TCMODULES += f_fw.o
TCMODULES += q_dsmark.o
TCMODULES += q_gred.o
TCMODULES += f_tcindex.o
TCMODULES += q_ingress.o
TCMODULES += q_hfsc.o
TCMODULES += q_htb.o

TCOBJ += $(TCMODULES)

TCLIB := tc_core.o
TCLIB += tc_red.o
TCLIB += tc_cbq.o
TCLIB += tc_estimator.o

TCSO :=
TCSO += q_netem.so
ifeq ($(TC_CONFIG_ATM),y)
  TCSO += q_atm.so
endif

LDLIBS += -L. -ltc -lm -ldl
LDFLAGS += -Wl,-export-dynamic
CFLAGS = $(CCOPTS) -I../include $(DEFINES)

%.so: %.c
	$(CC) $(CFLAGS) -shared -fpic $< -o $@

all: libtc.a tc $(TCSO)
	$(STRIP) ./tc


tc: $(TCOBJ) $(LIBNETLINK) $(LIBUTIL) $(TCLIB)

libtc.a: $(TCLIB)
	$(AR) rcs $@ $(TCLIB)

install: all
	[ -d $(TARGET)$(PREFIX) ] || mkdir -p $(TARGET)$(PREFIX)
	install -m 0755 ./$(APPLET) $(TARGET)$(PREFIX)
	[ -d $(TARGET)/usr/lib/tc ] || mkdir -p $(TARGET)/usr/lib/tc
	for i in $(TCSO); do install -m 755 $$i $(TARGET)/usr/lib/tc; done

clean:
	rm -f $(TCOBJ) $(TCLIB) libtc.a tc *.so

q_atm.so: q_atm.c
	$(CC) $(CFLAGS) -shared -fpic -o q_atm.so q_atm.c -latm


