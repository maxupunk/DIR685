all:
ifeq ($(strip $(ELBOX_IPTABLES_L7_EXT)),y)	
	@echo Nothing to compile, just run \'make install\'
	@echo \(This simply copies this directory into $(TARGET)/etc/l7-protocols \)
	$(Q)mkdir -p $(TARGET)/etc/l7-protocols
	$(Q)cp -R ./l7-protocols-2008-10-04/* $(TARGET)/etc/l7-protocols
	$(Q)find $(TARGET) -name .svn -type d | xargs rm -rf
endif
