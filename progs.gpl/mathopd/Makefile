
-include ../arch.mk
-include ../../path.mk
-include ../../.config

BIN = mathopd
CFLAGS += -O -Wall -I$(TOPDIR)/include
CPPFLAGS =
LIBS = -lcrypt

# On Solaris, uncomment the following
# CPPFLAGS = -DNEED_INET_ATON -DHAVE_CRYPT_H
# LIBS = -lsocket -lnsl

# On Linux, uncomment the following
 CPPFLAGS = -DHAVE_CRYPT_H

OBJS = base64.o cgi.o config.o core.o log.o main.o \
	   request.o util.o stub.o internal.o \
       upload.o md5c.o web-session.o

ifeq ($(strip $(ELBOX_PROGS_GPL_SYSLOGD_AP)),y)
CFLAGS += -I$(TOPDIR)/progs.priv/rgbin
OBJS += ../../progs.priv/rgbin/lrgbin.o rgdb_getset.o
endif

DEPENDS = mathopd.h Makefile

# //------------------------------
# Added by Paul Liu 20061212
# Add support for user command from unix socket.
COMLIB		:= $(TOPDIR)/comlib
COMINC		:= $(TOPDIR)/include
CMLIB_SRCS	:= unixsock.c
ifeq ($(strip $(ELBOX_PROGS_GPL_MATHOPD_EXTERNAL_FILE)),y)
CMLIB_SRCS	+= libxmldbc.c
ifeq ($(ELBOX_PROGS_GPL_NET_SNMP),y)
TRAP_SRCS   := sendtrap.c
endif
endif
CMLIB_OBJS	:= $(patsubst %c,%o,$(CMLIB_SRCS))
TRAP_OBJS   := $(patsubst %c,%o,$(TRAP_SRCS))

# Added by Paul Liu 20040326
# Add condition compile for UID/GID
# CPPFLAGS = -DUSE_ID

# Add condition compile for IMAP/REDIRECT/DUMP
# CPPFLAGS = -DIMAP
# OBJS += imap.o

# CPPFLAGS = -DREDIRECT
# OBJS += redirect.o

# CPPFLAGS = -DDUMP
# OBJS += dump.o
# //------------------------------

# Uncomment the following if your system does not support the poll() function
 CPPFLAGS += -DPOLL_EMULATION
 OBJS += poll-emul.o

# Uncomment the following if your system does not have the socklen_t type
# CPPFLAGS += -DNEED_SOCKLEN_T

# //------------------------------
# Modified by Paul Liu 20040326
# Add condition compile from config.arch for vfork() function
# Modified by Paul Liu 20060116
# We don't want vfork anymore...
#ifndef NO_VFORK
#CPPFLAGS += -DHAVE_VFORK
#endif

# //----------------for HomePortal
ifeq ($(strip $(ELBOX_SAMBA)),y)
# HOME_PORTAL:=y
# CFLAGS += -DHOME_PORTAL
CPPFLAGS += -D_FILE_OFFSET_BITS=64
endif
# //----------------
# Currently, sendfile support is available in two flavours: Linux and FreeBSD
# Uncomment one of the following two to enable sendfile() support
# CPPFLAGS += -DLINUX_SENDFILE
# CPPFLAGS += -DFREEBSD_SENDFILE
# If you define any of the SENDFILE conditionals, make sure to uncomment
# the next line as well.
# OBJS += sendfile.o

all: $(BIN)

install: $(BIN)
	@echo -e "\033[32mInstalling $(BIN) ...\033[0m"
	$(Q)install -c $(BIN) $(TARGET)/sbin/httpd
	#$(Q)if [ ! -f $(TARGET)/etc/httpd.cfg ]; then echo "install -c httpd.cfg"; install -c httpd.cfg $(TARGET)/etc/; fi

uninstall:
	$(Q)rm -f $(TARGET)/sbin/httpd
	$(Q)rm -f $(TARGET)/etc/httpd.cfg
	$(Q)rm -f $(TARGET)/var/httpd.cfg $(TARGET)/var/httpasswd

# //------------------------------
# Modified by Paul Liu 20061212
# link binary of COMLIB
$(BIN): $(OBJS) $(CMLIB_OBJS) $(TRAP_OBJS)
	@echo -e "\033[32mBuilding $(BIN) ...\033[0m"
	$(Q)$(CC) $(LDFLAGS) -o $(BIN) $(OBJS) $(LIBS) $(CMLIB_OBJS) $(TRAP_OBJS)
	$(Q)[ -z "$(STRIP)" ] || $(STRIP) $(BIN)
# //------------------------------

$(OBJS): $(DEPENDS)
.c.o:
	$(Q)$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

# //------------------------------
# Added by Paul Liu 20061212
# build rule for source in comlib.
$(CMLIB_OBJS): %.o: $(COMLIB)/%.c
	$(Q)$(CC) -I$(COMINC) $(CFLAGS) -c -o $@ $<
ifeq ($(ELBOX_PROGS_GPL_NET_SNMP),y)	
$(TRAP_OBJS): %.o: $(COMLIB)/%.c
	$(Q)$(CC) -I$(COMINC) $(CFLAGS) -c -o $@ $<	
endif	
# //------------------------------

clean:
	@echo -e "\033[32mCleaning $(BIN) ...\033[0m"
	$(Q)rm -f *.o *~ *.gdb $(BIN)

.PHONY: all install uninstall clean
