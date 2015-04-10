#
# Makefile for the Alphanetworks Tag Parser
#  for the Linux OS
#

-include ../arch.mk
-include ../../path.mk
#-include ../../Rules.mk


#CFLAGS += -DDDEBUG
APPLET     := cm.cgi
LOCAL_SRCS := cm_cgi.c data_chk.c
CMLIB_SRCS := libxmldbc.c

#
#	Primary link
#
-include $(TOPDIR)/Rules.mk

clean:
#	@echo -e "\033[32mCleaning $(APPLET) ...\033[0m"
#	$(Q)rm -f $(APPLET) $(DEPEND_FILES) *~ *.o .depend cm.cgi

install: 
	@echo -e "\033[32mInstalling $(APPLET) ...\033[0m"
	$(Q)cp cm.cgi $(TARGET)/usr/sbin

.PHONY: install clean all
