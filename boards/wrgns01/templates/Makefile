#
# Makefile for the template of board dependent part.
#
-include ../arch.mk
-include ../path.mk
-include ../.config

TMPS=$(TARGET)/etc/templates

all:

install:
	@echo -e "\033[32mInstalling templates for WRG-NS01 board dependent part...\033[0m"
	$(Q)[ -d $(TMPS) ] || mkdir -p $(TMPS)
	$(Q)cp *.sh         $(TMPS)/.
	$(Q)cp *.php         $(TMPS)/.
	$(Q)chmod +x		$(TMPS)/*.sh
	$(Q)[ -d $(TMPS)/wifi ] || mkdir -p $(TMPS)/wifi
	$(Q)cp wifi/*.php   $(TMPS)/wifi/.
	$(Q)cp wifi/*.sh 	$(TMPS)/wifi/.
	$(Q)chmod +x		$(TMPS)/wifi/*.sh
	$(Q)[ -d $(TMPS)/misc ] || mkdir -p $(TMPS)/misc
	$(Q)cp misc/*.php   $(TMPS)/misc/.
	$(Q)[ -d $(TMPS)/runtime ] || mkdir -p $(TMPS)/runtime
	$(Q)cp runtime/diskinfo   $(TARGET)/usr/sbin/.

clean:

.PHONY: all install clean
