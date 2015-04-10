#
# Makefile for wcnufd
#

-include ../arch.mk
-include ../../path.mk


APPLET		:= wcnufd
LOCAL_SRCS	:= wcnufd.c ../xmldb/xmlnode.c
CMLIB_SRCS	:= libxmldbc.c dtrace.c sloop.c

#CFLAGS		+= -DDBG

include $(TOPDIR)/Rules.mk

install:
	$(Q)cp wcnufd $(TARGET)/sbin/.
	
clean:
#	$(Q)rm -f *.o .depend $(APPLET) *~



