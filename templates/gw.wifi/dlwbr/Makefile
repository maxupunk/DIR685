#
# Makefile for gw.wifi dlwbr
#

-include arch.mk
-include path.mk
-include .config
-include $(TOPDIR)/Vars.mk
-include $(TOPDIR)/.config 
-include $(TOPDIR)/progs.board/customer.mk

#####################################################################
# targets for main Makefile
MYNAME:=D-Link DIR series

ifeq ($(strip $(ELBOX_CREATE_LANGUAGE_PACK)),y)
LANG_TARGET:=$(TOPDIR)/language
else
LANG_TARGET:=$(TARGET)/www/locale
endif

ifeq ($(strip $(ELBOX_MODEL_DIR300_ORANGE)), y)
ELBOX_MODEL_NAME_NOW = "dir300Orange"
else
ELBOX_MODEL_NAME_NOW = $(ELBOX_MODEL_NAME)
endif
#####################################################################
# build brand dependent programs
all:
	@echo -e "\033[32mBuilding brand related programs for $(MYNAME) ...\033[0m"

# install brand dependent programs
install:
	@echo -e "\033[32mInstalling brand related programs for $(MYNAME) ...\033[0m"
	$(Q)[ -d $(LANG_TARGET) ] || mkdir -p $(LANG_TARGET)
	$(Q)cp -rf www $(TARGET)/.
	$(Q)cp $(ELBOX_MODEL_NAME_NOW)/submit $(TARGET)/usr/sbin/.
	$(Q)cp -r --remove-destination $(ELBOX_MODEL_NAME_NOW)/www $(TARGET)/.
	$(Q)for i in $(LANGUAGE); do \
		echo -e "\033[32mInstall language $$i ...\033[0m" ; \
		cp -r --remove-destination locale/$$i $(LANG_TARGET)/. ; \
		if [ -d $(ELBOX_MODEL_NAME_NOW)/locale/$$i ]; then \
			cp -r --remove-destination $(ELBOX_MODEL_NAME_NOW)/locale/$$i $(LANG_TARGET)/. ; \
		fi; \
		echo $$i > $(LANG_TARGET)/$$i/langcode ; \
		done
	$(Q)find $(LANG_TARGET) -name .svn -type d | xargs rm -rf
	$(Q)find $(LANG_TARGET) -name CVS -type d | xargs rm -rf
ifeq ($(strip $(ELBOX_SAMBA)),y)
	$(Q)ln -s /var/portal_share $(TARGET)/www/portal_share
endif
# Sam: Add generate verification code for WEB login
ifeq ($(strip $(ELBOX_PROGS_PRIV_VERIFICATION_CODE)),y)
	$(Q)if [ ! -L $(TARGET)/www/auth_img ]; then\
			ln -s /var/auth/auth_img $(TARGET)/www/auth_img;\
		fi
endif
# hendry: the copy over will overwrite any files with the same filename 
# 		but not destroy the original scripts directory or any of its contents
	$(Q)if [ -d $(ELBOX_MODEL_NAME_NOW)/scripts ]; then\
			cp -rf $(ELBOX_MODEL_NAME_NOW)/scripts $(TARGET)/etc/.;\
		fi
# mark: guest zone file overwrite
	$(Q)if [ -f $(ELBOX_MODEL_NAME_NOW)/templates/extensions/enable_gzone_run.php ]; then\
			cp -rf $(ELBOX_MODEL_NAME_NOW)/templates/extensions/enable_gzone_run.php $(TARGET)/etc/templates/extensions/enable_gzone_run.php;\
		fi
# mark: 3g file overwrite
	$(Q)if [ -f $(ELBOX_MODEL_NAME_NOW)/templates/wan_ppp3g.php ]; then\
			cp -rf $(ELBOX_MODEL_NAME_NOW)/templates/wan_ppp3g.php $(TARGET)/etc/templates/wan_ppp3g.php;\
			cp -rf $(ELBOX_MODEL_NAME_NOW)/templates/runtime/wan $(TARGET)/usr/sbin/wan;\
		fi
# mark: qos file overwrite
	$(Q)if [ -f $(ELBOX_MODEL_NAME_NOW)/templates/extensions/trafficmanager_run.php ]; then\
			cp -rf $(ELBOX_MODEL_NAME_NOW)/templates/extensions/trafficmanager_run.php $(TARGET)/etc/templates/extensions/qos_run.php;\
			cp -rf $(ELBOX_MODEL_NAME_NOW)/templates/rg.sh $(TARGET)/etc/templates/rg.sh;\
			cp -rf $(ELBOX_MODEL_NAME_NOW)/templates/rg/flush_main.php $(TARGET)/etc/templates/rg/flush_main.php;\
			cp -rf $(ELBOX_MODEL_NAME_NOW)/templates/rg/flush_qos.php $(TARGET)/etc/templates/rg/flush_qos.php;\
			cp -rf $(ELBOX_MODEL_NAME_NOW)/templates/rg/rg_qos.php $(TARGET)/etc/templates/rg/rg_qos.php;\
			cp -rf $(ELBOX_MODEL_NAME_NOW)/templates/rg/rg_start.php $(TARGET)/etc/templates/rg/rg_start.php;\
			cp -rf $(ELBOX_MODEL_NAME_NOW)/templates/rg/rg_flushall.php $(TARGET)/etc/templates/rg/rg_flushall.php;\
		fi
	$(Q)if [ -f  $(ELBOX_MODEL_NAME_NOW)/templates/rg/flush_misc.php ]; then \
		    cp -rf $(ELBOX_MODEL_NAME_NOW)/templates/rg/flush_misc.php $(TARGET)/etc/templates/rg/flush_misc.php;\
		fi
	$(Q)if [ -f $(ELBOX_MODEL_NAME_NOW)/templates/misc/ntp_run.php ]; then\
			cp -rf $(ELBOX_MODEL_NAME_NOW)/templates/misc/ntp_run.php $(TARGET)/etc/templates/misc/ntp_run.php;\
		fi
#sonnia: inbound filter overwrite
ifeq ($(strip $(ELBOX_MODEL_DIR605D1)), y)
	$(Q)if [ -f  $(ELBOX_MODEL_NAME_NOW)/templates/rg/flush_inbound.php ]; then \
			cp -rf $(ELBOX_MODEL_NAME_NOW)/templates/rg/flush_inbound.php $(TARGET)/etc/templates/rg/flush_inbound.php;\
		fi
	$(Q)if [ -f  $(ELBOX_MODEL_NAME_NOW)/templates/rg/flush_vrtsrv.php ]; then \
			cp -rf $(ELBOX_MODEL_NAME_NOW)/templates/rg/flush_vrtsrv.php $(TARGET)/etc/templates/rg/flush_vrtsrv.php;\
		fi
	$(Q)if [ -f  $(ELBOX_MODEL_NAME_NOW)/templates/rg/rg_portf.php ]; then \
			cp -rf $(ELBOX_MODEL_NAME_NOW)/templates/rg/rg_portf.php $(TARGET)/etc/templates/rg/rg_portf.php;\
			cp -rf $(ELBOX_MODEL_NAME_NOW)/templates/rg/flush_portf.php $(TARGET)/etc/templates/rg/flush_portf.php;\
		fi		
	$(Q)if [ -f  $(ELBOX_MODEL_NAME_NOW)/templates/rg/flush_main.php ]; then \
			cp -rf $(ELBOX_MODEL_NAME_NOW)/templates/rg/flush_main.php $(TARGET)/etc/templates/rg/flush_main.php;\
		fi				
	$(Q)if [ -f  $(ELBOX_MODEL_NAME_NOW)/templates/rg.sh ]; then \
			cp -rf $(ELBOX_MODEL_NAME_NOW)/templates/rg.sh $(TARGET)/etc/templates/rg.sh;\
		fi	
	$(Q)if [ -f  $(ELBOX_MODEL_NAME_NOW)/templates/rg/flush_default.php ]; then \
			cp -rf $(ELBOX_MODEL_NAME_NOW)/templates/rg/flush_default.php $(TARGET)/etc/templates/rg/flush_default.php;\
			cp -rf $(ELBOX_MODEL_NAME_NOW)/templates/rg/rg_wanup.php $(TARGET)/etc/templates/rg/rg_wanup.php;\
			cp -rf $(ELBOX_MODEL_NAME_NOW)/templates/rg/rg_default.php $(TARGET)/etc/templates/rg/rg_default.php;\
		fi	
	$(Q)if [ -f  $(ELBOX_MODEL_NAME_NOW)/templates/rg/flush_passthrough.php ]; then \
			cp -rf $(ELBOX_MODEL_NAME_NOW)/templates/rg/flush_passthrough.php $(TARGET)/etc/templates/rg/flush_passthrough.php;\
		fi		
endif

#sam_pan : hnap overwrite
	$(Q)if [ -f $(ELBOX_MODEL_NAME_NOW)/templates/hnap/GetWanSettings.php ]; then\
             cp -rf $(ELBOX_MODEL_NAME_NOW)/templates/hnap/GetWanSettings.php $(TARGET)/etc/templates/hnap/GetWanSettings.php;\
        fi
	$(Q)if [ -f $(ELBOX_MODEL_NAME_NOW)/templates/hnap/SetWanSettings.php ]; then\
             cp -rf $(ELBOX_MODEL_NAME_NOW)/templates/hnap/SetWanSettings.php $(TARGET)/etc/templates/hnap/SetWanSettings.php;\
        fi

#sam_pan : advance dns overwirte
	$(Q)if [ -f $(ELBOX_MODEL_NAME_NOW)/templates/wan_static.php ]; then\
            cp -rf $(ELBOX_MODEL_NAME_NOW)/templates/wan_static.php $(TARGET)/etc/templates/wan_static.php;\
        fi

# clean board dependent programs
clean:
	@echo -e "\033[32mCleaning board related programs for $(MYNAME) ...\033[0m"

# setup brand dependent program configuration
prepare:
	@echo -e "\033[32mPreparing configuration for brand - $(MYNAME) ...\033[0m"

# build brand dependent rootfs
rootfs:
	@echo -e "\033[32mCreate rootfs for brand - $(MYNAME) ...\033[0m"
	$(Q)cp -rf defnodes						$(TARGET)/etc/.
	$(Q)cp -rf $(ELBOX_MODEL_NAME_NOW)/defnodes	$(TARGET)/etc/.
	$(Q)if [ -f $(ELBOX_MODEL_NAME_NOW)/freset_setnodes.sh ]; then\
			cp -rf $(ELBOX_MODEL_NAME_NOW)/freset_setnodes.sh $(TARGET)/etc/scripts/.;\
		fi
# teresa: for customer USA don't use b on wlan.
#ifeq ($(strip $(CUSTOMER_DUSA)),y)
#	$(Q)cp -rf $(ELBOX_MODEL_NAME_NOW)/customer_dusa/defnodes				$(TARGET)/etc/.
#endif

ifneq ($(strip $(ELBOX_DEFAULT_LANGUAGE)),)
ifneq ($(strip $(ELBOX_DEFAULT_LANGUAGE_NONE)),y)
	$(Q)echo "$(ELBOX_DEFAULT_LANGUAGE)" > $(TARGET)/etc/config/langcode
endif
endif

.PHONY: all install clean prepare rootfs

#####################################################################
