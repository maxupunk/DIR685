-include ../../arch.mk
-include ../../path.mk
-include config.mk

pwd=$(shell pwd)
	
all:
	make -C tcprequest		
	make -C sam_toolkit	
ifdef UPNP_CONTROLLER	
	make -C upnp_control/Platinum
endif	

ifdef FRAMECHANNEL	
	make -C fcrss_server
else	
	make -C frameit_server	
endif

	make -C nas_app alpha_nas	

install:		
	make -C nas_app install
ifdef FRAMECHANNEL	
	make -C fcrss_server install	
else	
	make -C frameit_server install			
endif

ifdef ALWAYS_CHECK_DOMAIN_NAME
	make -C tcprequest install	
	make -C sam_toolkit install
endif	

ifdef UPNP_CONTROLLER	
	make -C upnp_control/Platinum install
endif

clean:	
	make -C nas_app clean
	make -C fcrss_server clean
	make -C frameit_server clean
	make -C sam_toolkit clean 
	make -C tcprequest clean
	make -C upnp_control/Platinum clean   	
