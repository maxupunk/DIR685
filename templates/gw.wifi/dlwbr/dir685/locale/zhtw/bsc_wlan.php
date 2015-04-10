﻿<?
/* ---------------------------------- */
//$TITLE=$m_pre_title."設定";
/* ---------------------------------- */
$a_empty_ssid		="SSID 欄位不能為空白";
$a_invalid_ssid		="SSID 欄位含有部分無效字元。請檢查";
$a_invalid_wlan_band ="必須選取 802.11 頻帶選擇";

$a_invalid_wep_128_wep_key	="無效的無線金鑰。無線金鑰必須為 13 個字元或 26 個十六進制數";
$a_invalid_wep_64_wep_key	="無效的無線金鑰。無線金鑰必須為 5 個字元或 10 個十六進制數";
$a_invalid_wep_128_ascii_wep_key="無效的無線金鑰。無線金鑰必須為 13 個字元";
$a_invalid_wep_128_hex_wep_key	="無效的無線金鑰。無線金鑰必須為 26 個十六進制數";
$a_invalid_wep_64_ascii_wep_key	="無效的無線金鑰。無線金鑰必須為 5 個字元";
$a_invalid_wep_64_hex_wep_key	="無效的無線金鑰。無線金鑰必須為 10 個十六進制數";

$a_empty_defkey			="預設的 WEP 無線金鑰不能為空白";
$a_valid_hex_char		="合法的字元為  0~9、A~F 或 a~f";
$a_valid_asc_char		="合法的字元為 ASCII";

$a_invalid_radius_ip1		="無效的 RADIUS 伺服器 IP 位址";
$a_invalid_radius_port1		="無效的 RADIUS 伺服器連接埠";
$a_empty_radius_sec1		="RADIUS 伺服器的共用金鑰不能是空白";
$a_invalid_radius_sec1		="RADIUS 伺服器的共用金鑰應為 ASCII 字元";
$a_invalid_passphrase_len	="通行碼的長度應為 8~63";
$a_invalid_psk_len		="PSK 的長度應為 64";
$a_psk_not_match		="確認的通行碼不符合此通行碼";
$a_invalid_passphrase	="通行碼應為 ASCII 字元";
$a_invalid_psk			="PSK 應為十六進制";
$a_unknown_auth="未知的認證類型";

$a_reset_wps_pin		="您是否確定要將 PIN 重新設定成出廠預設值？";
$a_gen_new_wps_pin		="您是否確定要產生新的 PIN？";
$a_reset_wps_unconfig	="您是否確定要將裝置重新設定為未指定？";
$a_enable_wps_first		="WPS 尚未啟用。請按下 [儲存設定] 先啟用 WPS";

$m_title_wireless_setting	="無線網路設定";

$m_enable_wireless	="啟用無線服務";
$m_wlan_name		="無線網路名稱";
$m_wlan_name_comment	="(亦稱為 SSID)";

$m_wlan_band 	="802.11 頻帶";
$m_wlan_band_2g ="2.4GHz";
$m_wlan_band_5g ="5GHz";
$m_11g_only		="僅 802.11g 模式";
$m_11a_only		="僅 802.11 模式";
//for support 11n
$m_wlan_mode_set        ="802.11 模式";
$m_wlan_mode_11b        ="僅 802.11b";
$m_wlan_mode_11g        ="僅 802.11g";
$m_wlan_mode_11n        ="僅 802.11n";
$m_wlan_mode_mix        ="802.11 混合式 (b/g)";
$m_wlan_mode_mixn       ="802.11 混合式 (b/g/n)";
//for support 11a
$m_wlan_mode_11a		="僅 802.11a";
$m_wlan_mode_11an 		="802.11a 混合式 (a/n)";

$m_wlan_band_width      ="頻道寬度";
$m_wlan_short_guard     ="短保護區間";
$m_mhz                  ="MHz";

$m_enable_wireless	="啟用無線服務";
$m_wlan_name		="無線網路名稱";
$m_wlan_name_comment	="(亦稱為 SSID)";
$m_wlan_channel		="無線頻道";
$m_enable_auto_channel	="啟用自動頻道選擇";
$m_super_g		="Super G 模式";
$m_super_g_without_turbo="無加速的 Super G 功能";
$m_super_g_with_d_turbo ="具動態加速的 Super G 功能";
$m_xr			="啟用擴充範圍模式";
$m_11g_only		="僅 802.11g 模式";
$m_txrate		="傳輸率";
$m_mcrate		="多重廣播率";
$m_best_auto	="最佳 (自動)";
$m_mbps			="(Mbit/s)";
$m_wmm_enable	="啟用 WMM";
$m_wlan_qos		="(無線 QoS)";
$m_enable_ap_hidden	="啟用隱藏無線服務";
$m_ap_hidden_comment	="(亦稱為\"停用 SSID 廣播\")";

$m_title_wireless_security	="無線安全模式";

$m_security_mode	="安全模式";
$m_disable_security	="停用無線安全 (不建議使用)";
$m_enable_wep		="啟用 WEP 無線安全 (基本型)";
$m_wpa_security		="僅啟用 WPA 無線安全 (增強型)";
$m_wpa2_security	="僅啟用 WPA2 無線安全 (增強型)";
$m_wpa2_auto_security	="僅啟用 WPA/WPA2 無線安全 (增強型)";

$m_title_wep		="WEP";
$m_auth_type		="認證";
$m_open			="開啟";
$m_shared_key		="共用無線金鑰";
$m_wep_key_len		="WEP 加密";
$m_64bit_wep		="64 位元";
$m_128bit_wep		="128 位元";
$m_hex			="HEX";
$m_ascii		="ASCII";
$m_key_type		="無線金鑰類型";
$m_default_wep_key	="預設的 WEP 無線金鑰";
$m_wep_key		="WEP 無線金鑰";
$m_wep64_hint_wording	="(5 ASCII 或 10 HEX)";
$m_wep128_hint_wording	="(13 ASCII 或 26 KEX)";

$m_title_wpa		="僅 WPA";
$m_dsc_wpa		="僅 WPA 需要工作站使用高級加密和認證";
$m_title_wpa2		="僅 WPA2";
$m_dsc_wpa2		="僅 WPA2 需要工作站使用高級加密和認證";
$m_title_wpa2_auto	="WPA/WPA2";
$m_dsc_wpa2_auto	="WPA/WPA2 需要工作站使用高級加密和認證";

$m_cipher_type		="密碼類型";
$m_tkip			="TKIP";
$m_aes			="AES";
$m_psk_eap		="PSK/EAP";
$m_psk			="PSK/EAP";
$m_eap			="EAP";
$m_passphrase		="網路無線金鑰";
$m_confirm_passphrase	="確認的網路無線金鑰";
$m_psk_hint_wording		="(8~63 ASCII 或 64 HEX)";

$m_8021x		="802.1X";
$m_radius1		="RADIUS 伺服器";
$m_shared_sec		="共用金鑰";
?>
