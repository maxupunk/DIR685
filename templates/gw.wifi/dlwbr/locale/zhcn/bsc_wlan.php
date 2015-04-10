<?
/* ---------------------------------- */
//$TITLE=$m_pre_title."安装";
/* ---------------------------------- */
$a_empty_ssid		= "SSID栏不能为空白。";
$a_invalid_ssid		= "SSID栏中有一些无效的字符。请检查。";

$a_invalid_wep_128_wep_key	= "密钥无效，密钥必须是13个字符或者26个十六进制数字。";
$a_invalid_wep_64_wep_key	= "密钥无效，密钥必须是5个字符或者10个十六进制数字。";
$a_invalid_wep_128_ascii_wep_key= "密钥无效，密钥必须是13个字符。";
$a_invalid_wep_128_hex_wep_key	= "密钥无效，密钥必须是26个十六进制数字。";
$a_invalid_wep_64_ascii_wep_key	= "密钥无效，密钥必须是5个字符。";
$a_invalid_wep_64_hex_wep_key	= "密钥无效，密钥必须是10个十六进制数字。";

$a_empty_defkey			= "缺省WEP密钥不能为空白。";
$a_valid_hex_char		= "合法字符为 0－9, A－F 或者a－f。";
$a_valid_asc_char		= "合法字符为 ASCII。";

$a_invalid_radius_ip1		= "RADIUS服务器1的IP地址无效。";
$a_invalid_radius_ip2		= "RADIUS服务器2的IP地址无效。";
$a_invalid_radius_port1		= "RADIUS服务器1的端口无效。";
$a_invalid_radius_port2		= "RADIUS服务器2的端口无效。";
$a_empty_radius_sec1		= "RADIUS服务器1的共享秘钥不能为空白。";
$a_empty_radius_sec2		= "RADIUS服务器2的共享秘钥不能为空白。";
$a_invalid_radius_sec1		= "RADIUS服务器1的共享秘钥应是ASCII字符。";
$a_invalid_radius_sec2		= "RADIUS服务器2的共享秘钥应是ASCII字符。";
$a_invalid_passphrase_len	= "短语密码的长度应该是 8－63。";
$a_invalid_psk_len		= "PSK的长度应为64。";
$a_psk_not_match		= "确认后的短语密码与短语密码不匹配。";
$a_invalid_passphrase	= "短语密码应是ASCII字符。";
$a_invalid_psk			= "PSK应是十六进制。";

$a_reset_wps_pin		= "您确定将PIN复位到缺省？";
$a_gen_new_wps_pin		= "您确定生成一个新的PIN？";
$a_reset_wps_unconfig	= "您确定将设备复位到无配置？";
$a_enable_wps_first		= "WPS还没有被激活。  请按 \\\"保存设置\\\" 首先将WPS激活。";

$m_title_wireless_setting	= "无线网路设置";

$m_enable_wireless	= "启用无线";
$m_wlan_name		= "无线网络名称";
$m_wlan_name_comment	= "（也叫SSID）";
$m_wlan_channel		= "无线信道";
$m_enable_auto_channel	= "启用自动信道选择";
$m_super_g		= "超好G模式";
$m_super_g_without_turbo= "没有Turbo的超好G";
$m_super_g_with_d_turbo = "有动态Turbo的超好G";
$m_xr			= "启用扩展范围模式";
$m_11g_only		= "仅有802.11g模式";
$m_txrate		= "传输速率";
$m_mcrate		= "多播速率";
$m_best_auto	= "最好（自动）";
$m_mbps			= "(Mbit/s)";
$m_wmm_enable	= "WMM启用";
$m_wlan_qos		= "（无线QoS）";
$m_enable_ap_hidden	= "启用隐藏无线";
$m_ap_hidden_comment	= "（也叫SSID广播）";

$m_title_wireless_security	= "无线安全模式";

$m_security_mode	= "安全模式";
$m_disable_security	= "禁用无线安全（不建议）";
$m_enable_wep		= "启用WEP无线安全（基本）";
$m_wpa_security		= "启用无线安全的WPA（增强）";
$m_wpa2_security	= "启用无线安全的WPA2（增强）";
$m_wpa2_auto_security	= "启用WPA/WPA2无线安全（增强）";

$m_title_wep		= "WEP";
$m_auth_type		= "认证";
$m_open			= "开放";
$m_shared_key		= "共享密钥";
$m_wep_key_len		= "WEP加密";
$m_64bit_wep		= "64位";
$m_128bit_wep		= "128位";
$m_hex			= "十六进制";
$m_ascii		= "ASCII";
$m_key_type		= "密钥类型";
$m_default_wep_key	= "缺省WEP密钥";
$m_wep_key		= "WEP密钥";
$m_wep64_hint_wording	="（5 ASCII或者10十六进制）";
$m_wep128_hint_wording	="（13 ASCII或者26十六进制）";

$m_title_wpa		="仅有WPA";
$m_dsc_wpa		="WPA仅要求站点使用高级别加密和认证。";
$m_title_wpa2		="仅有WPA2";
$m_dsc_wpa2		="WPA2仅要求站点使用高级别加密和认证。";
$m_title_wpa2_auto	="WPA/WPA2";
$m_dsc_wpa2_auto	="WPA/WPA2仅要求站点使用高级别加密和认证。";

$m_cipher_type		="密码类型";
$m_tkip			="TKIP";
$m_aes			="AES";
$m_tkipandaes       ="自动(TKIP/AES)";
$m_psk_eap		="PSK / EAP";
$m_psk			="PSK";
$m_eap			="EAP";
$m_passphrase		="网络密钥";
$m_confirm_passphrase	="确认后的网络密钥";
$m_psk_hint_wording		="(8－63 ASCII 或者 64 HEX)";

$m_8021x		="802.1X";
$m_radius1		="RADIUS服务器1";
$m_radius2		="RADIUS服务器2";
$m_shared_sec		="共享密钥";
?>
