<?
/* ---------------------------------- */
//$TITLE=$m_pre_title."安装";
/* ---------------------------------- */
$a_empty_ssid		="SSID栏不能为空白。";
$a_invalid_ssid		="SSID栏中有一些无效字符。请检查。";
$a_invalid_wlan_band ="必须选择802.11频段。";

$a_invalid_wep_128_wep_key	="密钥无效。该密钥必须为13个字符或26个十六进制数字。";
$a_invalid_wep_64_wep_key	="密钥无效。该密钥必须为5个字符或10个十六进制数字。";
$a_invalid_wep_128_ascii_wep_key="密钥无效。该密钥必须为13个字符";
$a_invalid_wep_128_hex_wep_key	="密钥无效。该密钥必须为26个十六进制数字。";
$a_invalid_wep_64_ascii_wep_key	="密钥无效。该密钥必须为5个字符。";
$a_invalid_wep_64_hex_wep_key	="密钥无效。该密钥必须为10个十六进制数字。";

$a_empty_defkey			="默认WEP密钥不能为空。";
$a_valid_hex_char		="合法字符为 0~9， A~F 或 a~f。";
$a_valid_asc_char		="合法字符为ASCII。";

$a_invalid_radius_ip1		="RADIUS服务器的IP地址为无效地址。";
$a_invalid_radius_port1		="RADIUS服务器的端口为无效端口。";
$a_empty_radius_sec1		="RADIUS服务器的共享密钥不能为空。";
$a_invalid_radius_sec1		="RADIUS服务器的共享密钥应为ASCII字符。";
$a_invalid_passphrase_len	="密码短语的长度应为8~63。";
$a_invalid_psk_len		="PSK的长度应为64。";
$a_psk_not_match		="确认密码短语与密码短语不匹配。";
$a_invalid_passphrase	="密码短语应为ASCII字符。";
$a_invalid_psk			="PSK应为十六进制。";
$a_unknown_auth="未知认证类型。";

$a_reset_wps_pin		="您确定要将PIN复位到出厂设置？";
$a_gen_new_wps_pin		="您确定要建立一个新的PIN？";
$a_reset_wps_unconfig	="您确定要将设备恢复到无配置？";
$a_enable_wps_first		="WPS还未启用。请按下 \\\"保存设置\\\"，首先启用WPS。";

$m_title_wireless_setting	="无线网络设置";

$m_enable_wireless	="启用无线";
$m_wlan_name		="无线网络名称";
$m_wlan_name_comment	="（也叫SSID）";

$m_wlan_band 	="802.11频段";
$m_wlan_band_2g ="2.4GHz";
$m_wlan_band_5g ="5GHz";
$m_11g_only		="仅使用802.11g模式";
$m_11a_only		="仅使用802.11a模式";
//for support 11n
$m_wlan_mode_set        ="802.11模式";
$m_wlan_mode_11b        ="仅使用802.11b";
$m_wlan_mode_11g        ="仅使用802.11g";
$m_wlan_mode_11n        ="仅使用802.11n";
$m_wlan_mode_mix        ="802.11组合（b/g）";
$m_wlan_mode_mixn       ="802.11组合（b/g/n）";
//for support 11a
$m_wlan_mode_11a		="仅使用802.11a";
$m_wlan_mode_11an 		="802.11a组合（a/n）";

$m_wlan_band_width      ="信道宽度";
$m_wlan_short_guard     ="窄化保护频带间隔";
$m_mhz                  ="MHz";

$m_enable_wireless	="启用无线";
$m_wlan_name		="无线网络名称";
$m_wlan_name_comment	="（也叫SSID）";
$m_wlan_channel		="无线信道";
$m_enable_auto_channel	="启用自动信道选择";
$m_super_g		="Super G模式";
$m_super_g_without_turbo="无Turbo的Super G";
$m_super_g_with_d_turbo ="带有动态Turbo的Super G";
$m_xr			="启用扩展范围模式";
$m_11g_only		="只有802.11g模式";
$m_txrate		="传输速率";
$m_mcrate		="组播速率";
$m_best_auto	="最好（自动）";
$m_mbps			="（Mbit/s）";
$m_wmm_enable	="启用WMM";
$m_wlan_qos		="（无线QoS）";
$m_enable_ap_hidden	="启用隐藏无线";
$m_ap_hidden_comment	="（也叫\"禁用SSID组播\）";

$m_title_wireless_security	="无线安全模式";

$m_security_mode	="安全模式";
$m_disable_security	="禁用无线安全（不推荐）";
$m_enable_wep		="启用WEP无线安全（基本）";
$m_wpa_security		="启用WPA无线安全（增强）";
$m_wpa2_security	="启用WPA2无线安全（增强）";
$m_wpa2_auto_security	="启用WPA/WPA2无线安全（增强）";

$m_title_wep		="WEP";
$m_auth_type		="认证";
$m_open			="开放";
$m_shared_key		="共享密钥";
$m_wep_key_len		="WEP加密";
$m_64bit_wep		="64位";
$m_128bit_wep		="128位";
$m_hex			="十六进制";
$m_ascii		="ASCII";
$m_key_type		="密钥类型";
$m_default_wep_key	="默认WEP密钥";
$m_wep_key		="WEP密钥";
$m_wep64_hint_wording	="（5 ASCII或10 HEX）";
$m_wep128_hint_wording	="（13 ASCII或 26 HEX）";

$m_title_wpa		="仅使用WPA";
$m_dsc_wpa		="WPA只要求站点使用高级加密和认证。";
$m_title_wpa2		="仅使用WPA2";
$m_dsc_wpa2		="WPA2只要求站点使用高级加密和认证。";
$m_title_wpa2_auto	="WPA/WPA2";
$m_dsc_wpa2_auto	="WPA/WPA2要求站点使用高级加密和认证。";

$m_cipher_type		="密码类型";
$m_tkip			="TKIP";
$m_aes			="AES";
$m_psk_eap		="PSK / EAP";
$m_psk			="PSK";
$m_eap			="EAP";
$m_passphrase		="网络密钥";
$m_confirm_passphrase	="确认网络密钥";
$m_psk_hint_wording		="（8~63 ASCII或64 HEX）";

$m_8021x		="802.1X";
$m_radius1		="RADIUS服务器";
$m_shared_sec		="共享密钥";
?>

