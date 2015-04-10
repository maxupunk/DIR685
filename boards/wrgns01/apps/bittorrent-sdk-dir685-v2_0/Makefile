
-include ../../path.mk
-include ../../arch.mk

all:
	make -C alpha_bt
	make -C memctrl
clean:
install_cpp_lib:
	$(Q)cp $(TPATH_UC)/lib/libstdc++.so.6.0.3 $(TARGET)/lib
	$(Q)cp $(TPATH_UC)/lib/librt-0.9.29.so $(TARGET)/lib
	$(Q)cd $(TARGET)/lib && ln -sf libstdc++.so.6.0.3 libstdc++.so.6 && ln -sf libstdc++.so.6.0.3 libstdc++.so.6.0
	$(Q)cd $(TARGET)/lib && ln -sf librt-0.9.29.so librt.so.0 && ln -sf librt.so.0 librt.so

install:install_cpp_lib
	$(Q)make -C alpha_bt install 
	$(Q)make -C memctrl install 
	$(Q)cp bin/bt $(TARGET)/usr/sbin && chmod +x $(TARGET)/usr/sbin/bt
	$(Q)cp bin/btdog $(TARGET)/usr/sbin && chmod +x $(TARGET)/usr/sbin/btdog
	$(Q)cp -rf webui/* $(TARGET)/www/
	
	
.PHONY: all clean install install_cpp_lib
