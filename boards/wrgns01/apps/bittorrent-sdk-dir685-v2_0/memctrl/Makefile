#
# Mainfile for BT
#

-include ../../../../../arch.mk
-include ../../../../../path.mk
-include ../../../../../.config

##########################################################################
# source for BT
OTHER_TARGETS:= 
MYNAME		:= MEMCTRL
APPLET		:= memctrl
LOCAL_SRCS	:= memctrl.c
CMLIB_SRCS	:= 
##########################################################################

CMDS=
CFLAGS+=-I$(TOPDIR)/include

##########################################################################

-include $(TOPDIR)/Rules.mk

clean: clean_objs
	@echo -e "\033[32mCleaning $(MYNAME) ...\033[0m"
	$(Q)rm -f *~ *.o

install:
	@echo -e "\033[32mInstalling $(MYNAME) ...\033[0m"
	$(Q)cp $(APPLET) $(TARGET)/sbin && chmod +x $(TARGET)/sbin/$(APPLET)

.PHONY: clean install
