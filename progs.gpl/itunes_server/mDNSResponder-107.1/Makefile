-include ../../arch.mk
-include ../../../path.mk
all:
	@echo -e "\033[32mStart building mDNSResponder-107.1 ...\033[0m"
	make -C mDNSPosix os=linux all;
#	make -f Makefile.ori all;
#	(cd stunnel-4.06; make -f Makefile build-shared);

install:
	@echo -e "\033[32mInstalling mDNSResponder-107.1 ...\033[0m"
#	$(ROMFSINST) mDNSPosix/build/prod/mDNSClientPosix /bin/mDNSClientPosix
	cp mDNSPosix/build/prod/mDNSResponderPosix $(TARGET)/bin/mDNSResponderPosix
	cp rendezvous.conf $(TARGET)/etc/.
#	$(ROMFSINST) mDNSPosix/Bonjour.txt /etc/Bonjour.txt
#	$(ROMFSINST) mDNSPosix/alpha_hostname /bin/alpha_hostname
#	$(ROMFSINST) mDNSPosix/alpha_reg /bin/alpha_reg
#	$(ROMFSINST) install/stunnel /bin/stunnel
#	$(ROMFSINST) -s /var/ipsec.secrets /etc/ipsec.secrets
clean:
	@echo -e "\033[32mStart cleaning mDNSResponder-107.1 ...\033[0m"
	make -C mDNSPosix os=linux clean;
#	make -f Makefile.ori clean;

.PHONY: all romfs clean

