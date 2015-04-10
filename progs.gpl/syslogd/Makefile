# Makefile for syslogd

-include ../arch.mk
-include ../../path.mk
-include ../../.config
ifeq ($(strip $(ELBOX_PROGS_GPL_SYSLOGD_SMTP_SCHEDULE)),y)
SCHEDULE_SMTP := schedule_smtp
SCHEDULE_SRCS := schedule_smtp.c ../../comlib/sloop.c
SCHEDULE_OBJS := $(patsubst %c,%o,$(SCHEDULE_SRCS))
endif
SYSLOGD := syslogd
SRCS := syslogd.c

ifeq ($(strip $(ELBOX_PROGS_GPL_SYSLOGD_AP)),y)
RGBIN_PATH := $(shell pwd)/../../progs.priv/rgbin
CFLAGS += -I$(RGBIN_PATH) -DSYSLOG_AP
SRCS += $(RGBIN_PATH)/lrgbin.c
endif
OBJS:=$(patsubst %c,%o,$(SRCS))
DEPENDS = Makefile
CFLAGS += -I$(TOPDIR)/include

ifeq ($(strip $(ELBOX_PROGS_GPL_SYSLOGD_REMOTELOG)),y)
	CFLAGS += -DREMOTE_LOG #-DALPHA_DBG
endif
ifeq ($(strip $(ELBOX_PROGS_GPL_SYSLOGD_SMTP)),y)
	CFLAGS += -DAP_SMTP
endif
ifeq ($(strip $(ELBOX_PROGS_GPL_SYSLOGD_SMTP_SCHEDULE)),y)
	CFLAGS += -DAP_SMTP_SCHEDULE
endif

# enable syslogd -R remotehost
#CFLAGS+= -DREMOTE_LOG
#CFLAGS+= -DALPHA_DBG

# enable syslogd -C
#CFLAGS+= -DIPC_SYSLOG

##########################################################################

all:	$(SYSLOGD) $(SCHEDULE_SMTP)

install:
	@echo -e "\033[32mInstalling syslogd ...\033[0m"
	$(Q)[ -d $(TARGET)/sbin ] || mkdir -p $(TARGET)/sbin
	$(Q)install $(SYSLOGD) $(TARGET)/sbin/.
ifeq ($(strip $(ELBOX_PROGS_GPL_SYSLOGD_SMTP_SCHEDULE)),y)	
	@echo -e "\033[32mInstalling schedule_smtp ...\033[0m"
	$(Q)install $(SCHEDULE_SMTP) $(TARGET)/sbin/.
endif

$(SYSLOGD): $(OBJS)
	@echo -e "\033[32mBuilding syslogd ...\033[0m"
	@$(CC) $(CFLAGS) -o $@ $(OBJS)
	$(Q)$(STRIP) $(SYSLOGD)

$(OBJS): $(DEPENDS)
.c.o:
	$(CC) -c $(CFLAGS) $< -o $@
syslogd.o: Makefile syslogd.c
	$(Q)$(CC) -c $(CFLAGS) syslogd.c

ifeq ($(strip $(ELBOX_PROGS_GPL_SYSLOGD_SMTP_SCHEDULE)),y)
$(SCHEDULE_SMTP): $(SCHEDULE_OBJS) 
	@echo -e "\033[32mBuilding schedule_smtp ...\033[0m"
	@$(CC) $(CFLAGS) -o $@ $(SCHEDULE_OBJS)
	$(Q)$(STRIP) $(SCHEDULE_SMTP)
$(SCHEDULE_OBJS): $(DEPENDS)
schedule_smtp.o: Makefile schedule_smtp.c
	$(Q)$(CC) -c $(CFLAGS) schedule_smtp.c
endif

clean:
	@echo -e "\033[32mCleaning syslogd and schedule_smtp ...\033[0m"
	$(Q)rm -f *.o *~ *.gdb *.elf $(SYSLOGD)
ifeq ($(strip $(ELBOX_PROGS_GPL_SYSLOGD_SMTP_SCHEDULE)),y)
	@echo -e "\033[32mCleaning schedule_smtp ...\033[0m"
	$(Q)rm -f *.o *~ *.gdb *.elf $(SCHEDULE_SMTP)
endif
.PHONY:	all install clean
