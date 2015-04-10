<?
$m_title_ap_mode	="接入点模式";
$m_desc_ap_mode		="禁用路由器上的NAT，进入接入点模式";
$m_enable_ap_mode	="启用接入点模式";

$m_title_wan_type	="Internet连接类型";
$m_desc_wan_type	="选择路由器采用的模式，连接到Internet上";

$m_wan_type	="我的Internet连接为";
$m_static_ip	="静态IP";
$m_dhcp		="动态IP（DHCP）";
$m_pppoe	="PPPoE（用户名/密码）";
$m_pptp		="PPTP（用户名/密码）";
$m_l2tp		="L2TP（用户名/密码）";
$m_russia_pptp		="Russia PPTP（双访问）";
$m_russia_pppoe		="Russia PPPoE（双访问）";
$m_mppe		="MPPE";
$m_wwan 	="3G USB数据卡";

$m_title_static	="静态IP地址Internet连接类型";
$m_desc_static	="输入您Internet服务供应商提供的静态IP地址信息。";

$m_comment_isp	="（由您的ISP分配）";
$m_subnet	="子网掩码";
$m_isp_gateway	="ISP网关地址";
$m_macaddr	="MAC地址";
$m_optional	="（可选）";
$m_clone_mac	="克隆MAC地址";
$m_primary_dns	="首选DNS地址";
$m_secondary_dns="备用DNS地址";
$m_mtu		="MTU";

$m_title_dhcp	="动态IP（DHCP）Internet连接类型";
$m_desc_dhcp	="如果您的Internet服务供应商（ISP）没有提供IP地址信息或用户名和密码，请使用这个Internet连接类型。";

$m_host_name		="主机名称";
$m_ppp_idle_time	="最大闲置时间";
$m_ppp_connect_mode	="连接模式选择";
$m_always_on		="始终开启";
$m_manual		="手动";
$m_on_demand		="按需连接";

$__info_from_isp	="输入您Internet服务供应商提供的信息";

$m_title_pppoe	="PPPoE";
$m_title_russia_pppoe	="Russia PPPoE（双访问）";
$m_desc_pppoe	= $__info_from_isp;
$m_title_physical	="WAN物理设置";

$m_dynamic_pppoe	="动态PPPoE";
$m_static_pppoe		="静态PPPoE";
$m_retype_pwd		="确认密码";
$m_pppoe_svc_name	="服务名称";
$m_minutes		="分钟";
$m_auto_dns		="从ISP处获得DNS";
$m_manual_dns	="手动输入DNS";

$m_title_pptp	="PPTP";
$m_title_russia_pptp	="Russia PPTP（双访问）";
$m_desc_pptp = $__info_from_isp;	

$m_title_l2tp	="L2TP";
$m_desc_l2tp	= $__info_from_isp;	

$m_dynamic_ip		="动态IP";
$m_static_ip		="静态IP";
$m_gateway		="网关";
$m_dns			="DNS";
$m_server_ip		="服务器 IP/名称";
$m_pptp_account		="PPTP账号";
$m_pptp_password	="PPTP密码";
$m_pptp_retype_pwd	="PPTP确认密码";
$m_l2tp_account		="L2TP账户";
$m_l2tp_password	="L2TP密码";
$m_l2tp_retype_pwd	="L2TP确认密码";

$m_title_wwan			="WWAN INTERNET连接类型：";
$m_desc_wwan			="输入您Internet服务供应商（ISP）提供的信息。";
$m_card_device			="卡片";
$m_driver				="驱动器";
$m_manufacturer			="厂商";
$m_product 				="产品";
$m_pin_code				="PIN";
$m_username				="用户名";
$m_password				="密码";
$m_dial_num				="拨号码";
$m_auth_proto			="认证协议";
$m_wwan_auth_auto 		="自动（PAP+CHAP）";
$m_wwan_pap				="仅使用PAP";
$m_wwan_chap			="仅使用CHAP";
$m_auto_reconn 			="自动重新连接";
$m_apn					="APN";
$m_enable 				="启用";
$m_disable				="禁用";
$m_keep_alive_int 		="保持连接间隔";
$m_seconds 				="（秒数）";
$m_keep_alive_server1 	="保持连接服务器1";
$m_keep_alive_server2 	="保持连接服务器2";
$m_wwan_reconn_mode		="重新连接模式";
$m_wwan_minutes			="（分钟，0=无限）";
$m_wwan_bytes			="（字节）";
$m_country				="国家";
$m_isp					="ISP";
$m_choice_country		="选择您的国家";
$m_choice_isp			="选择您的isp";

$m_auth_server	="认证服务器";
$m_login_server ="登录服务器IP/名称";

/*----------802.1x------------*/

$m_8021x_setting	   	="802.1X";
$m_8021x_setting_description ="输入您Internet服务供应商（ISP）提供的信息。";

$m_8021x_eap_type		="EAP类型";
$m_8021x_md5			="MD5";
$m_8021x_peap			="PEAP";
$m_8021x_ttls			="TTLS";

$m_8021x_authentication	="认证";
$m_8021x_pap			="PAP";
$m_8021x_chap			="CHAP";
$m_8021x_mschap			="MSCHAP";
$m_8021x_mschapv2		="MSCHAP版本2";

$m_8021x_identity		="用户名";
$m_8021x_pass		="密码";
$m_8021x_pass2		="确认密码";

/*------------------------------*/


$a_invalid_ip		="无效IP地址！";
$a_invalid_netmask	="无效子网掩码！";
$a_invalid_mac		="无效MAC地址！";
$a_invalid_mtu		="无效MTU值！";
$a_invalid_hostname	="无效主机名！";
$a_invalid_username	="无效用户名！";
$a_password_mismatch	="确认密码与新密码不匹配！";
$a_invalid_idletime	="无效闲置时间！";

$a_srv_in_different_subnet	="无效服务器IP地址！服务器和路由器地址应在同一网段。";
$a_gw_in_different_subnet	="无效网关IP地址！网关和路由器地址应在同一网段。";
$a_server_empty		="服务器IP/名称不能为空！";
$a_account_empty	="账户不能为空！";

$a_card_device_not_selected ="不能选择卡片！";
$a_dial_num_empty 			="拨号码不能为空！";
$a_auth_proto_not_selected 	="不能选择认证协议！";
$a_apn_empty 				="APN不能为空！";
$a_keep_alive_int_empty 	="选择自动重新连接时，保持连接间隔不能为空！";
$a_invalid_keep_alive_int 	="保持连接间隔应为介于20和3600之间的数字！";

/*---------------802.1x alert message---------------*/
$a_empty_username		="用户名不能为空！";
$a_empty_password		="密码不能为空！";
$a_empty_password_v		="确认密码不能为空！";
$a_diff_password		="两个密码是不同的！";
$a_empty_field			="该栏不能为空！";
/*--------------------------------------------------*/

?>

