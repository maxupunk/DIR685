<?
$m_title_ap_mode	= "無線存取點模式";
$m_desc_ap_mode		= "使用此功能將關閉路由器的 NAT功能，並將之轉變為無線存取點裝置。";
$m_enable_ap_mode	= "啟用無線存取點模式";

$m_title_wan_type	= "Internet 連線類型";
$m_desc_wan_type	= "選取路由器連接 Internet 使用的模式。";

$m_wan_type	= "我的 Internet 連線設定為";
$m_static_ip	= "靜態 IP";
$m_dhcp		= "動態 IP (DHCP)";
$m_pppoe	= "PPPoE (使用者名稱/密碼)";
$m_pptp		= "PPTP (使用者名稱/密碼)";
$m_l2tp		= "L2TP (使用者名稱/密碼)";
$m_russia_pptp		= "多重服務存取PPTP (俄羅斯地區專用)";
$m_russia_pppoe		= "多重服務存取 PPPoE (俄羅斯地區專用)";

$m_title_static	= "靜態 IP 管理 Internet 連線類型";
$m_desc_static	= "輸入Internet 服務提供者 (ISP) 提供的靜態位址資訊。";

$m_comment_isp	= "(您的 ISP 所指定)";
$m_subnet	= "子網路遮罩";
$m_isp_gateway	= "ISP 閘道位址";
$m_macaddr	= "MAC 位址";
$m_optional	= "(選擇性)";
$m_clone_mac	= "複製 MAC 位址";
$m_primary_dns	= "主要 DNS 位址";
$m_secondary_dns= "次要 DNS 位址";
$m_mtu		= "MTU";

$m_title_dhcp	= "動態 IP (DHCP)  Internet 連線類型";
$m_desc_dhcp	= "使用此 Internet 連線類型－如果您的Internet 服務提供者未提供您 IP 位址和/或使用者名稱與密碼。";

$m_host_name		= "主機名稱";
$m_ppp_idle_time	= "最大閒置時間";
$m_ppp_connect_mode	= "連線模式選取";
$m_always_on		= "永遠開啟";
$m_manual		= "手動";
$m_on_demand		= "視需求連線";

$__info_from_isp	= "輸入您 Internet 服務提供者 (ISP) 提供的資訊。";

$m_title_pppoe	= "PPPoE";
$m_title_russia_pppoe	= "多重服務存取 PPPoE (俄羅斯地區專用)";
$m_desc_pppoe	= $__info_from_isp;
$m_title_physical	= "WAN 實體設定";

$m_dynamic_pppoe	= "動態 PPPoE";
$m_static_pppoe		= "靜態 PPPoE";
$m_retype_pwd		= "重新輸入密碼";
$m_pppoe_svc_name	= "服務名稱";
$m_minutes		= "分";
$m_auto_dns		= "從ISP取得DNS";
$m_manual_dns	= "手動輸入DNS";

$m_title_pptp	= "PPTP";
$m_title_russia_pptp	= "多重服務存取PPTP (俄羅斯地區專用)";
$m_desc_pptp	= $__info_from_isp;

$m_title_l2tp	= "L2TP";
$m_desc_l2tp	= $__info_from_isp;

$m_dynamic_ip		= "動態 IP";
$m_static_ip		= "靜態 IP";
$m_gateway		= "閘道";
$m_dns			= "DNS";
$m_server_ip		= "伺服器 IP/名稱";
$m_pptp_account		= "PPTP 帳號";
$m_pptp_password	= "PPTP 密碼";
$m_pptp_retype_pwd	= "PPTP 重新輸入密碼";
$m_l2tp_account		= "L2TP 帳號";
$m_l2tp_password	= "L2TP 密碼";
$m_l2tp_retype_pwd	= "L2TP 重新輸入密碼";


$m_auth_server	= "驗證伺服器";
$m_login_server = "登入伺服器 IP/名稱";

/*----------802.1x------------*/

$m_8021x_setting	   	= "802.1x";
$m_8021x_setting_description = "輸入寬頻服務系統業者提供的訊息.";

$m_8021x_eap_type		= "EAP 類型";
$m_8021x_md5			= "MD5";
$m_8021x_peap			= "PEAP";
$m_8021x_ttls			= "TTLS";

$m_8021x_authentication	= "認證";
$m_8021x_pap			= "PAP";
$m_8021x_chap			= "CHAP";
$m_8021x_mschap			= "MSCHAP";
$m_8021x_mschapv2		= "MSCHAP Version 2";

$m_8021x_identity		= "使用者名稱";
$m_8021x_pass		= "密碼";
$m_8021x_pass2		= "確認密碼";

/*------------------------------*/

$a_invalid_ip		= "無效的 IP 位址!";
$a_invalid_netmask	= "無效的子網路遮罩!";
$a_invalid_mac		= "無效的 MAC 位址!";
$a_invalid_mtu		= "無效的 MTU 值!";
$a_invalid_hostname	= "無效的主機名稱!";
$a_invalid_username	= "無效的使用者名稱!";
$a_password_mismatch	= "確認密碼與新密碼不符!";
$a_invalid_idletime	= "無效的閒置時間!";

$a_srv_in_different_subnet	= "無效的伺服器 IP 位址！伺服器與路由器位址應該位在相同網路內。";
$a_gw_in_different_subnet	= "無效的閘道 IP 位址！閘道與路由器位址應該位在相同網路內。";
$a_server_empty		= "伺服器 IP/名稱不能空白!";
$a_account_empty	= "帳號不能空白!";

/*---------------802.1x alert message---------------*/
$a_empty_username		= "使用者名稱不可空白!";
$a_empty_password		= "密碼欄位不可空白!";
$a_empty_password_v		= "確認密碼欄位不可空白!";
$a_diff_password		= "輸入兩個密碼不相同!";
$a_empty_field			= "欄位不可以空白!";
/*--------------------------------------------------*/

?>
