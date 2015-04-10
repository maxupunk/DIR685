<?
/* ---------------------------------- */
//$TITLE=$m_pre_title."SETUP";
/* ---------------------------------- */
$a_empty_ssid		= "SSID 欄位不能空白!";
$a_invalid_ssid		= "SSID 欄位內含無效的字元。請檢查。";

$a_invalid_wep_128_wep_key	= "鑰匙無效。 鑰匙必須為 13 字元或 26 個十六進位數字。";
$a_invalid_wep_64_wep_key	= "鑰匙無效。 鑰匙必須為 5 字元或 10 個十六進位數字。";
$a_invalid_wep_128_ascii_wep_key= "鑰匙無效。 鍵值必須為 13 字元。";
$a_invalid_wep_128_hex_wep_key	= "鑰匙無效。 鑰匙必須為 26 個十六進位數字。";
$a_invalid_wep_64_ascii_wep_key	= "鑰匙無效。 鑰匙必須為 5 字元。";
$a_invalid_wep_64_hex_wep_key	= "鑰匙無效。 鑰匙必須為 10 個十六進位數字。";


$a_empty_defkey			= "預設 WEP 鑰匙不能空白!";
$a_valid_hex_char		= "合法字元為 0~9, A~F 或 a~f。";
$a_valid_asc_char		= "合法字元為 ASCII。";

$a_invalid_radius_ip1		= "RADIUS 伺服器 1 的 IP 位址無效。";
$a_invalid_radius_ip2		= "RADIUS 伺服器 2 的 IP 位址無效。";
$a_invalid_radius_port1		= "RADIUS 伺服器 1 的接埠無效。";
$a_invalid_radius_port2		= "RADIUS 伺服器 2 的接埠無效。";
$a_empty_radius_sec1		= "RADIUS 伺服器 1 的共用密碼不能空白。";
$a_empty_radius_sec2		= "RADIUS 伺服器 2 的共用密碼不能空白。";
$a_invalid_radius_sec1		= "RADIUS 伺服器 1 的共用密碼應為 ASCII 字元。";
$a_invalid_radius_sec2		= "RADIUS 伺服器 2 的共用密碼應為 ASCII 字元。";
$a_invalid_passphrase_len	= "通行字組的長度應該在 8~63 之間。";
$a_invalid_psk_len		= "PSK 的長度應該為 64。";
$a_psk_not_match		= "確認通行字組與通行字組不符";
$a_invalid_passphrase	= "通行字組必須為 ASCII 字元。";
$a_invalid_psk			= "PSK 應該為十六進位。";

$a_reset_wps_pin		= "您確定要重設 PIN 為預設值嗎?";
$a_gen_new_wps_pin		= "您確定產生新 PIN 嗎?";
$a_reset_wps_unconfig	= "您確定要重設裝置為未組態嗎?";
$a_enable_wps_first		= "WPS功能尚未被啟用, 請先按儲存按鍵來啟用WPS。";


$m_title_wireless_setting	= "無線網路設定";

$m_enable_wireless	= "啟用無線";
$m_wlan_name		= "無線網路名稱";
$m_wlan_name_comment	= "(也稱為 SSID)";
$m_wlan_channel		= "無線頻道";
$m_enable_auto_channel	= "啟用自動頻道選取";
$m_super_g		= "Super G 模式";
$m_super_g_without_turbo= "無快速 (Turbo) 的 Super G";
$m_super_g_with_d_turbo = "動態快速 (Turbo) 的 Super G";
$m_xr			= "啟用延伸範圍模式";
$m_11g_only		= "僅 802.11g 模式";
$m_txrate		= "傳輸率";
$m_mcrate		= "Multicast Rate";
$m_best_auto	= "最佳 (自動)";
$m_mbps			= "(Mbit/s)";
$m_wmm_enable	= "WMM 啟用";
$m_wlan_qos		= "(無線 QoS)";
$m_enable_ap_hidden	= "啟用隱藏無線";
$m_ap_hidden_comment	= "(也稱為 SSID 廣播)";

$m_title_wireless_security	= "無線安全性模式";

$m_security_mode	= "安全性模式";
$m_disable_security	= "關閉無線安全性 (不建議)";
$m_enable_wep		= "啟用 WEP 無線安全性 (基本)";
$m_wpa_security		= "啟用僅 WPA 無線安全性 (增強)";
$m_wpa2_security	= "啟用僅 WPA2 無線安全性 (增強)";
$m_wpa2_auto_security	= "啟用僅 WPA/WPA2 無線安全性 (增強)";


$m_title_wep		= "WEP";
$m_auth_type		= "驗證";
$m_open			= "開放";
$m_shared_key		= "共享鑰匙";
$m_wep_key_len		= "WEP 加密";
$m_64bit_wep		= "64位元";
$m_128bit_wep		= "128位元";
$m_hex			= "十六進位";
$m_ascii		= "ASCII";
$m_key_type		= "鑰匙類型";
$m_default_wep_key	= "預設 WEP 鑰匙";
$m_wep_key		= "WEP 鑰匙";
$m_wep64_hint_wording	="(5 ASCII 或 10 十六進位)";
$m_wep128_hint_wording	="(13 ASCII 或 26 十六進位)";

$m_title_wpa		="僅 WPA";
$m_dsc_wpa		="WPA 只要求基地台使用高等級加密與驗證技術。";
$m_title_wpa2		="僅 WPA2";
$m_dsc_wpa2		="WPA2 只要求基地台使用高等級加密與驗證技術。";
$m_title_wpa2_auto	="WPA/WPA2";
$m_dsc_wpa2_auto	="WPA/WPA2 要求基地台使用高等級加密與驗證技術。";

$m_cipher_type		="密碼類型";
$m_tkip			="TKIP";
$m_aes			="AES";
$m_tkipandaes       ="自動(TKIP/AES)";
$m_psk_eap		="PSK / EAP";
$m_psk			="PSK";
$m_eap			="EAP";
$m_passphrase		="網路鑰匙";
$m_confirm_passphrase	="確認的網路鑰匙";
$m_psk_hint_wording		="(8~63 ASCII 或 64 十六進位)";

$m_8021x		="802.1X";
$m_radius1		="RADIUS 伺服器 1";
$m_radius2		="RADIUS 伺服器 2";
$m_shared_sec		="共享密碼";
?>
