#
#  Makefile for install log template.
#

-include ../arch.mk
-include ../../path.mk

all:

install:
	@echo -e "\033[32mInstall English log messages ...\033[0m"
	$(Q)[ -d $(TARGET)/etc/tlogs ] || mkdir -p $(TARGET)/etc/tlogs
	$(Q)cp *.tmp $(TARGET)/etc/tlogs

clean:

.PHONY: all install clean
