# vi: set sw=4 ts=4:
#
# Makefile for the HTTP documents of gw.wifi.
#

-include ../arch.mk
-include ../path.mk
-include ../.config

all:

install:
	@echo -e "\033[32mInstalling HTTP documents for gw.wifi ...\033[0m"
	$(Q)[ -d $(TARGET)/htdocs ] || mkdir $(TARGET)/htdocs
	$(Q)cp -r upnp	$(TARGET)/htdocs/.
	$(Q)cp -r web	$(TARGET)/htdocs/.
	$(Q)rm -f $(TARGET)/htdocs/upnp/upnpdev.cgi
	$(Q)rm -f $(TARGET)/htdocs/upnp/wfadev.cgi
	$(Q)rm -f $(TARGET)/htdocs/upnp/xmldoc
	$(Q)ln -s /usr/sbin/upnpkits $(TARGET)/htdocs/upnp/upnpdev.cgi
	$(Q)ln -s /usr/sbin/upnpkits $(TARGET)/htdocs/upnp/wfadev.cgi
	$(Q)ln -s /var/upnp $(TARGET)/htdocs/upnp/xmldoc

clean:

.PHONY: all install clean
