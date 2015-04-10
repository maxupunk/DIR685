# Makefile for smtp-client
#USE_BRCM_TOOLS=n

-include ../../.config
-include ../arch.mk
-include ../../path.mk

# compiler flags
LIBGSASL_DIR = $(TOPDIR)/progs.gpl/libgsasl/
LIBGSASL_PATH = $(LIBGSASL_DIR)/libgsasl-0.2.6

ifeq ($(strip $(ELBOX_MODEL_DAP2590)),y)
CFLAGS += -Wall -Os
else 
ifeq ($(strip $(ELBOX_MODEL_DAP2690)),y)
CFLAGS += -Wall -Os
else
CFLAGS += -static -Wall -Os
endif
endif
CFLAGS += -I$(LIBGSASL_PATH)/src

# enable syslogd -R remotehost
#CFLAGS+= -DREMOTE_LOG
#CFLAGS+= -DALPHA_DBG

# enable syslogd -C
#CFLAGS+= -DIPC_SYSLOG
LDFLAGS+= -lresolv

APPLET=sendmail
OBJ = $(APPLET).o

all: $(APPLET)

clean:
#	rm -f *.o *~ core $(APPLET)

$(APPLET): $(OBJ)
	$(Q)if [ ! -f $(LIBGSASL_PATH)/src/.libs/libgsasl.a ]; then make -C $(LIBGSASL_DIR); fi;
	$(Q)$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJ) $(LIBGSASL_PATH)/src/.libs/libgsasl.a

install:
#install: all
	$(Q)[ -z "$(STRIP)" ] || $(STRIP) $(APPLET)
	cp $(APPLET) $(TARGET)/usr/sbin
