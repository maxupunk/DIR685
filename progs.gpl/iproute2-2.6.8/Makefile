#####################################################

-include ../arch.mk
-include ../../path.mk
-include $(TOPDIR)/.config

PREFIX = /usr/sbin

#####################################################

DESTDIR=
SBINDIR=/usr/sbin
CONFDIR=/etc/iproute2
DOCDIR=/usr/doc/iproute2
KERNEL_INCLUDE=$(KERNELDIR)/include

# Path to db_185.h include
DBM_INCLUDE:=$(TPATH_UC)/include

DEFINES= -DRESOLVE_HOSTNAMES

#options if you have a bind>=4.9.4 libresolv (or, maybe, glibc)
LDLIBS=-lresolv
ADDLIB=

#options for decnet
ADDLIB+=dnet_ntop.o dnet_pton.o

#options for ipx
ADDLIB+=ipx_ntop.o ipx_pton.o

#CC = gcc
CCOPTS = -D_GNU_SOURCE -O2 -Wstrict-prototypes -Wall -g
CFLAGS += $(CCOPTS) -I../include $(DEFINES)

LDLIBS += -L../lib -lnetlink -lutil

#SUBDIRS=lib ip tc misc
SUBDIRS=lib ip

###-------------------------------------------------------------------------###
ifeq ($(strip $(ELBOX_PROGS_PRIV_TURBONAT_QOS)),y)
	SUBDIRS=lib ip tc
endif
###-------------------------------------------------------------------------###
###-------------------------------------------------------------------------###
ifeq ($(strip $(ELBOX_PROGS_GPL_TC_FOR_AP)),y)
	SUBDIRS=lib tc
endif
###-------------------------------------------------------------------------###

LIBNETLINK=../lib/libnetlink.a ../lib/libutil.a

all: Config
	@for i in $(SUBDIRS); \
	do $(MAKE) $(MFLAGS) -C $$i; done

Config:
	#./configure $(KERNEL_INCLUDE)
	echo "# DO NOT use ATM !!" > Config

install: all
	[ -d $(TARGET)$(PREFIX) ] || mkdir -p $(TARGET)$(PREFIX)
#	install -d $(TARGET)$(PREFIX)
#	install -m 0755 -d $(DESTDIR)$(CONFDIR)
#	install -m 0755 -d $(DESTDIR)$(DOCDIR)/examples
#	install -m 0755 -d $(DESTDIR)$(DOCDIR)/examples/diffserv
#	install -m 0644 README.iproute2+tc $(shell find examples -type f -maxdepth 1) \
		$(DESTDIR)$(DOCDIR)/examples
#	install -m 0644 $(shell find examples/diffserv -type f -maxdepth 1) \
		$(DESTDIR)$(DOCDIR)/examples/diffserv
	@for i in $(SUBDIRS) ; do $(MAKE) -C $$i install; done
#	install -m 0644 $(shell find etc/iproute2 -type f -maxdepth 1) $(DESTDIR)$(CONFDIR)


clean:
	@for i in $(SUBDIRS) doc; \
	do $(MAKE) $(MFLAGS) -C $$i clean; done
	rm -f Config

clobber: clean
	rm -f Config


.EXPORT_ALL_VARIABLES:
