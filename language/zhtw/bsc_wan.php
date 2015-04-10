﻿<?
$m_title_ap_mode	="存取點模式";
$m_desc_ap_mode		="使用此功能停用路由器的 NAT，並轉變為存取點。";
$m_enable_ap_mode	="啟用存取點模式";

$m_title_wan_type	="網際網路連線類型";
$m_desc_wan_type	="選擇可供路由器連線至網際網路的模式。";

$m_wan_type	="我的網際網路連線是";
$m_static_ip	="靜態 IP ";
$m_dhcp		="動態 IP (DHCP)";
$m_pppoe	="PPPoE (使用者名稱/密碼)";
$m_pptp		="PPTP (使用者名稱/密碼)";
$m_l2tp		="L2TP (使用者名稱/密碼)";
$m_russia_pptp		="PPTP 雙重存取(僅俄羅斯地區)";
$m_russia_pppoe		="PPPoE 雙重存取(僅俄羅斯地區)";
$m_mppe		="MPPE";
$m_wwan 	="3G USB 網路卡";

$m_title_static	="靜態 IP 位址網際網路連線類型";
$m_desc_static	="輸入由您網際網路服務提供者 (ISP) 提供的靜態 IP 位址資訊";

$m_comment_isp	="(由您的 ISP 指定)";
$m_subnet	="子網路遮罩";
$m_isp_gateway	="ISP 閘道器位址";
$m_macaddr	="MAC 位址";
$m_optional	="(可選擇使用)";
$m_clone_mac	="修改重設 MAC 位址";
$m_primary_dns	="主要的 DNS 位址";
$m_secondary_dns="輔助的 DNS 位址";
$m_mtu		="MTU";

$m_title_dhcp	="動態 IP (DHCP) 網際網路連線類型";
$m_desc_dhcp	="如果您的網際網路服務提供者".
								"未提供您有關 IP 位址資訊及/或使用者名稱和密碼，則使用此網際網路連線類型";

$m_host_name		="主機名稱";
$m_ppp_idle_time	="最大閒置時間";
$m_ppp_connect_mode	="連線模式選擇";
$m_always_on		="永遠啟動";
$m_manual		="手動連線";
$m_on_demand		="視需求連線";

$__info_from_isp	="輸入由您網際網路服務提供者 (ISP) 提供的資訊";

$m_title_pppoe	="PPPoE";
$m_title_russia_pppoe	="PPPoE 雙重存取(僅俄羅斯地區)";
$m_desc_pppoe	= $__info_from_isp;
$m_title_physical	="WAN 實體介面設定";

$m_dynamic_pppoe	="動態 PPPoE";
$m_static_pppoe		="靜態 PPPoE";
$m_retype_pwd		="確認密碼";
$m_pppoe_svc_name	="服務名稱";
$m_minutes		="分";
$m_auto_dns		="從 ISP 端取得 DNS";
$m_manual_dns	="手動輸入 DNS";

$m_title_pptp	="PPTP";
$m_title_russia_pptp	="PPTP 雙重存取(僅俄羅斯地區)";
$m_desc_pptp	= $__info_from_isp;

$m_title_l2tp	="L2TP";
$m_desc_l2tp	= $__info_from_isp;

$m_dynamic_ip		="動態 IP";
$m_static_ip		="靜態 IP";
$m_gateway		="閘道器";
$m_dns			="DNS";
$m_server_ip		="伺服器 IP/名稱";
$m_pptp_account		="PPTP 帳號";
$m_pptp_password	="PPTP 密碼";
$m_pptp_retype_pwd	="PPTP 確認密碼";
$m_l2tp_account		="L2TP 帳號";
$m_l2tp_password	="L2TP 密碼";
$m_l2tp_retype_pwd	="L2TP 確認密碼";

$m_title_wwan			="WWAN 網際網路連線類型";
$m_desc_wwan			="輸入由您網際網路服務提供者 (ISP) 提供的資訊";
$m_card_device			="介面卡";
$m_driver				="驅動程程式";
$m_manufacturer			="廠商";
$m_product 				="產品";
$m_pin_code				="PIN";
$m_username				="使用者名稱";
$m_password				="密碼";
$m_dial_num				="撥號";
$m_auth_proto			="任證通訊協定";
$m_wwan_auth_auto 		="自動 (PAP + CHAP)";
$m_wwan_pap				="僅 PAP";
$m_wwan_chap			="僅 CHAP";
$m_auto_reconn 			="自動重新連線";
$m_apn					="APN";
$m_enable 				="啟用";
$m_disable				="停用";
$m_keep_alive_int 		="保持動作的時間間隔";
$m_seconds 				="(秒)";
$m_keep_alive_server1 	="保持動作的伺服器 1";
$m_keep_alive_server2 	="保持動作的伺服器 2";
$m_wwan_reconn_mode		="重新連線模式";
$m_wwan_minutes			="(分，0=無限時間)";
$m_wwan_bytes			="(位元組)";
$m_country				="國別";
$m_isp					="ISP";
$m_choice_country		="選擇國別";
$m_choice_isp			="選擇您的 ISP";

$m_auth_server	="認證伺服器";
$m_login_server ="登入伺服器 IP/名稱";

/*----------802.1x------------*/

$m_8021x_setting	   	="802.1x";
$m_8021x_setting_description ="請輸入由您網際網路服務提供者 (ISP) 提供的資訊";

$m_8021x_eap_type		="EAP 類型";
$m_8021x_md5			="MD5";
$m_8021x_peap			="PEAP";
$m_8021x_ttls			="TTLS";

$m_8021x_authentication	="認證";
$m_8021x_pap			="PAP";
$m_8021x_chap			="CHAP";
$m_8021x_mschap			="MSCHAP";
$m_8021x_mschapv2		="MSCHAP V2";

$m_8021x_identity		="使用者名稱";
$m_8021x_pass		="密碼";
$m_8021x_pass2		="確認的密碼";

/*------------------------------*/


$a_invalid_ip		="無效的 IP 位址！";
$a_invalid_netmask	="無效的子網路遮罩！";
$a_invalid_mac		="無效的 MAC 位址！";
$a_invalid_mtu		="無效的 MTU 值！";
$a_invalid_hostname	="無效的主機名稱！";
$a_invalid_username	="無效的使用者名稱！";
$a_password_mismatch	="確認密碼不符合新的密碼！";
$a_invalid_idletime	="無效的閒置時間！";

$a_srv_in_different_subnet	="無效的伺服器 IP 位址！閘道器和路由器位址應在相同的網路";
$a_gw_in_different_subnet	="無效的 IP 位址！閘道器和路由器位址應在相同的網路";
$a_server_empty		="伺服器 IP/名稱不能為空白！";
$a_account_empty	="帳號不能為空白！";

$a_card_device_not_selected ="未選定介面卡！";
$a_dial_num_empty 			="撥號不能為空白！";
$a_auth_proto_not_selected 	="未選定認證通訊協定！";
$a_apn_empty 				="APN 不能為空白！";
$a_keep_alive_int_empty 	="如果選定自動重新連線，保持動作的時間間隔不能為空白！";
$a_invalid_keep_alive_int 	="保持動作的時間間隔應為數值，且介於 20 和 3600 之間！";

/*---------------802.1x alert message---------------*/
$a_empty_username		="使用者名稱不能為空白！";
$a_empty_password		="密碼不能為空白！";
$a_empty_password_v		="確認的密碼不能為空白！";
$a_diff_password		="兩個密碼不同！";
$a_empty_field			="此欄位不能為空白！";
/*--------------------------------------------------*/

?>
