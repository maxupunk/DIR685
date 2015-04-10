<?
$m_gz_title_select			="来宾区选择";
$m_gz_title_router			="来宾区的路由器设置";
$m_gz_title_isolate			="来宾客户端隔离区";
$m_gz_title_to_host_routing	="主机区和来宾区之间的路由";
$m_gz_title_dhcp_server		="来宾区的DHCP服务器设置";
$m_gz_title_dhcp_client		="来宾区的DHCP客户端列表";
$m_gz_title_lock_client		="来宾区的锁定客户端列表";

$m_gz_desc_router	="使用该项配置您路由器的来宾区设置。".
										"来宾区为来宾提供一个单独的网络区域，方便来宾访问Internet。";

$m_gz_desc_isolate	="启用该功能阻止来宾客户端访问来宾区中的其它来宾客户端。".
											"来宾客户端只能访问Internet。";

$m_gz_desc_to_host_routing	="使用该部分启用主机区和来宾区之间的路由。".
														"如果没有启用该功能，来宾客户端不能访问主机客户端的数据。";

$m_gz_desc_dhcp_server	="使用该部分来配置内置DHCP服务器，将IP地址分配给您网络中的计算机。";

$m_gz_desc_lock_client	="该功能用于将宾区中的所有PC客户端锁定在一张IP/MAC地址绑定列表中;启用该功能后，只有该列表中的PC才能访问网络。这样确保其它客户端无论是通过有线或无线连接，都不能访问来宾区。";

$m_enable_gzone			="启用来宾区";
$m_include_lan_port		="包括LAN端口";
$m_include_wireless		="包括无线";
$m_wireless_name		="无线网络名称";
$m_ssid_comment			="（也叫SSID）";
$m_security_mode		="安全模式";
$m_router_ip			="路由器IP地址";
$m_router_netmask		="默认子网掩码";
$m_enable_gzone_iso		="启用来宾区客户端隔离";
$m_enable_gzone_route	="启用区域之间的路由";
$m_enable_dhcp_server	="启用DHCP服务器";
$m_dhcp_ip_range		="DHCP IP地址范围";
$m_to					="至";
$m_dhcp_ip_range_comment	="（LAN子网内的地址）";
$m_dhcp_lease_time		="DHCP租赁时间";
$m_dhcp_lease_time_comment	="（分钟）";
$m_lock_client			="启用锁定客户端列表";

$m_host_name		="主机名称";
$m_expired_time		="失效时间";

$m_encr_none	="禁用无线安全（不推荐）";
$m_encr_wep		="启用WEP无线安全（基本）";
$m_encr_wpa		="启用WPA无线安全（增强）";
$m_encr_wpa2	="启用WPA2无线安全（增强）";
$m_encr_wpaauto	="启用WPA/WPA2 无线安全（增强）";

$m_title_wep	="WEP";
$m_auth_type	="认证";
$m_open			="开放";
$m_shared_key	="共享密钥";
$m_wep_key_len	="WEP加密";
$m_64bit_wep	="64位";
$m_128bit_wep	="128位";
$m_hex			="十六进制";
$m_ascii		="ASCII";
$m_key_type		="密钥类型";
$m_def_wep_key	="默认WEP密钥";
$m_wep_key		="WEP密钥";
$m_hint_wep64	="（5 ASCII 或 10 HEX）";
$m_hint_wep128	= "（13 ASCII 或 26 HEX）";

$m_title_wpa	="仅使用WPA";
$m_dsc_wpa		="WPA只要求站点使用高级加密和认证。";
$m_title_wpa2	="仅使用WPA2";
$m_dsc_wpa2		="WPA2只要求站点使用高级加密和认证。";
$m_title_wpa_2	= "WPA/WPA2";
$m_dsc_wpa_2	="WPA/WPA2只要求站点使用高级加密和认证。";

$m_cipher_type	="密码类型";
$m_tkip			="TKIP";
$m_aes			="AES";
$m_psk			="PSK";
$m_eap			="EAP";
$m_passphrase	="网络密钥";
$m_confirm_passphrase   ="确认网络密钥";
$m_psk_hint		="（8~63 ASCII 或 64 HEX）";

$m_8021x		= "802.1X";
$m_radius_srvr	="RADIUS服务器";
$m_shared_sec	="共享密钥";

$m_days	="天";
$m_hrs	="小时";
$m_mins	="分钟";
$m_secs	="秒";

$a_invalid_ip			="无效IP地址！";
$a_invalid_netmask		="无效子网掩码！";
$a_network_conflict		="来宾区网络必须与主机区不同！";
$a_invalid_ip_range		="DHCP服务器的无效IP地址范围！";
$a_invalid_lease_time	="无效DHCP租赁时间！";

$a_empty_ssid	="SSID栏不能为空白。";
$a_invalid_ssid	="SSID栏中有一些无效字符。请检查。";
$a_invalid_wep_128_wep_key		="密钥无效。密钥必须为13个字符或26个十六进制数字。";
$a_invalid_wep_64_wep_key		="密钥无效。密钥必须为5个字符或10个十六进制数字。";
$a_invalid_wep_128_ascii_wep_key="密钥无效。密钥必须为13个字符。";
$a_invalid_wep_128_hex_wep_key	="密钥无效。密钥必须为26个十六进制数字。";
$a_invalid_wep_64_ascii_wep_key	="密钥无效。密钥必须为5个字符。";
$a_invalid_wep_64_hex_wep_key	="密钥无效。密钥必须10个十六进制数字。";
$a_invalid_passphrase_len		="密码短语的长度介于8~63之间。";
$a_invalid_passphrase			="密码短语应为ASCII字符。";
$a_invalid_psk					="PSK应为十六进制。";
$a_invalid_radius_ip			="无效RADIUS服务器。";
$a_invalid_radius_port			="无效端口号。";
$a_invalid_radius_sec			="无效密钥。";

?>

