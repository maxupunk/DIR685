-include ../../arch.mk
-include ../../path.mk

APPLET		:= wol
LOCAL_SRCS	:= wol.c
CMLIB_SRCS	:= 
CPLUS_SRCS	:=

#-include $(TOPDIR)/Rules.mk
all: $(APPLET)
	$(CC) $(LOCAL_SRCS) -o $(APPLET)

install: $(APPLET)
	@echo -e "\033[32mInstalling $(APPLET) ...\033[0m"
	$(Q)[ -d $(TARGET)/usr/sbin ] || mkdir -p $(TARGET)/usr/sbin
	$(Q)cp $(APPLET) $(TARGET)/usr/sbin/.
	$(Q)chmod +x $(TARGET)/usr/sbin/$(APPLET)

clean:
	-rm -f $(APPLET) *.elf *.gdb *.o
 