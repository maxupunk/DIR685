﻿<?
/* ---------------------------------- */
//$TITLE=$m_pre_title."SETUP";
/* ---------------------------------- */
$a_empty_ssid		= "Das Feld SSID darf nicht leer bleiben.";
$a_invalid_ssid		="Das Feld SSID enthält ungültige Zeichen. Bitte prüfen Sie dies.";
$a_invalid_wlan_band = "802.11 Bandauswahl treffen.";

$a_invalid_wep_128_wep_key	= "Der Schlüssel ist ungültig. Er muss 13 Zeichen oder 26 hexadezimale Ziffern und Zahlen aufweisen.";
$a_invalid_wep_64_wep_key	= "Der Schlüssel ist ungültig. Er muss 5 Zeichen oder 10 hexadezimale Ziffern und Zahlen aufweisen.";
$a_invalid_wep_128_ascii_wep_key= "Der Schlüssel ist ungültig. Der Schlüssel muss 13 Zeichen aufweisen.";
$a_invalid_wep_128_hex_wep_key	= "Der Schlüssel ist ungültig. Der Schlüssel muss 26 hexadezimale Ziffern und Zahlen aufweisen.";
$a_invalid_wep_64_ascii_wep_key	= "Der Schlüssel ist ungültig. Der Schlüssel muss 5 Zeichen aufweisen.";
$a_invalid_wep_64_hex_wep_key	= "Der Schlüssel ist ungültig. Der Schlüssel muss 10 hexadezimale Ziffern und Zahlen aufweisen.";

$a_empty_defkey			= "Der Standard-WEP-Schlüssel darf nicht leer sein.";
$a_valid_hex_char		= "Die gültigen Zeichen sind 0-9, A-F oder a-f.";
$a_valid_asc_char		= "Die gültigen Zeichen sind ASCII.";

$a_invalid_radius_ip1		= "Die IP-Adresse des RADIUS-Servers ist ungültig.";
$a_invalid_radius_port1		= "Der Port des RADIUS-Servers ist ungültig.";
$a_empty_radius_sec1		= "Das Shared Secret des RADIUS-Servers darf nicht leer sein.";
$a_invalid_radius_sec1		= "Das Shared Secret des RADIUS-Servers sollte aus ASCII-Zeichen bestehen.";
$a_invalid_passphrase_len	= "Die Länge des Kennwortsatzes sollte 8 ~ 63 sein.";
$a_invalid_psk_len		= "Die Länge des PSK sollte 64 sein.";
$a_psk_not_match		= "Der bestätigte Kennwortsatz stimmt nicht mit dem Kennwortsatz überein.";
$a_invalid_passphrase	= "Der Kennwortsatz sollte aus ASCII-Zeichen bestehen.";
$a_invalid_psk			= "PSK sollte Hexadezimal sein.";
$a_unknown_auth= "Unbekannter Authentifizierungstyp.";

$a_reset_wps_pin		= "Möchten Sie die PIN wirklich auf den werkseitig eingestellten Standard zurücksetzen?";
$a_gen_new_wps_pin		= "Möchten Sie wirklich eine neue PIN generieren?";
$a_reset_wps_unconfig	= "Möchten Sie das Gerät wirklich auf Unkonfiguriert zurücksetzen?";
$a_enable_wps_first		= "WPS ist noch nicht aktiviert. Klicken Sie auf \\\"Einstellungen speichern\\\", um WPS zu aktivieren.";

$m_title_wireless_setting	= "Funknetzeinstellungen";

$m_enable_wireless	= "Funk aktivieren";
$m_wlan_name		= "Name des Funknetzes";
$m_wlan_name_comment	= "(Auch SSID genannt)";

$m_wlan_band 	= "802.11 Band";
$m_wlan_band_2g = "2,4 GHz";
$m_wlan_band_5g = "5 GHz";
$m_11g_only		= "802.11g Only Modus";
$m_11a_only		= "802.11a Only Modus";
//for support 11n
$m_wlan_mode_set        ="802.11 Modus";
$m_wlan_mode_11b        ="802.11b only";
$m_wlan_mode_11g        ="802.11g only";
$m_wlan_mode_11n        ="802.11n only";
$m_wlan_mode_mix        ="802.11 Mixed (b/g)";
$m_wlan_mode_mixn       ="802.11 Mixed (b/g/n)";
//for support 11a
$m_wlan_mode_11a		="802.11a only";
$m_wlan_mode_11an 		="802.11a Mixed (a/n)";

$m_wlan_band_width      ="Kanalbreite";
$m_wlan_short_guard     ="Kurzes Guard-Intervall";
$m_mhz                  ="MHz";

$m_enable_wireless	= "Funk aktivieren";
$m_wlan_name		= "Name des Funknetzes";
$m_wlan_name_comment	= "(Auch SSID genannt)";
$m_wlan_channel		= "Funkkanal";
$m_enable_auto_channel	= "Automatische Kanalsuche aktivieren";
$m_super_g		= "Super G-Modus";
$m_super_g_without_turbo= "Super G ohne Turbo";
$m_super_g_with_d_turbo = "Super G mit dynamischem Turbo";
$m_xr			= "Erweiterten Bereichsmodus aktivieren";
$m_11g_only		= "802.11g Only Modus";
$m_txrate		= "Übertragungsrate";
$m_mcrate		= "Multicast-Rate";
$m_best_auto	= "Best (Automatisch)";
$m_mbps			= "(MBit/s)";
$m_wmm_enable	= "WMM aktivieren";
$m_wlan_qos		= "(Wireless QoS)";
$m_enable_ap_hidden	= "Verborgenen Funk aktivieren";
$m_ap_hidden_comment	= "(Auch \"SSID Broadcast deaktivieren\" genannt)";

$m_title_wireless_security	= "Drahtloser Sicherheitsmodus";

$m_security_mode	= "Sicherheitsmodus";
$m_disable_security	= "Funksicherheit deaktivieren (nicht empfohlen)";
$m_enable_wep		= "WEP-Funksicherheit (einfach) aktivieren";
$m_wpa_security		= "WPA Only-Funksicherheit (erweitert) aktivieren";
$m_wpa2_security	= "WPA2 Only-Funksicherheit (erweitert) aktivieren";
$m_wpa2_auto_security	= "WPA/WPA2-Funksicherheit (erweitert) aktivieren";

$m_title_wep		= "WEP";
$m_auth_type		= "Authentifizierung";
$m_open			= "Offen";
$m_shared_key		= "Shared Key";
$m_wep_key_len		= "WEP-Verschlüsselung";
$m_64bit_wep		= "64 Bit";
$m_128bit_wep		= "128 Bit";
$m_hex			= "HEX";
$m_ascii		= "ASCII";
$m_key_type		= "Schlüsseltyp";
$m_default_wep_key	= "Standard-WEP-Schlüssel";
$m_wep_key		= "WEP-Schlüssel";
$m_wep64_hint_wording	="(5 ASCII oder 10 HEX)";
$m_wep128_hint_wording	="(13 ASCII oder 26 HEX)";

$m_title_wpa		="WPA Only";
$m_dsc_wpa		="WPA Only erfordert, dass Stationen hochgradige Verschlüsselung und Authentifizierung verwenden.";
$m_title_wpa2		="WPA2 Only";
$m_dsc_wpa2		="WPA2 Only erfordert, dass Stationen hochgradige Verschlüsselung und Authentifizierung verwenden.";
$m_title_wpa2_auto	="WPA/WPA2";
$m_dsc_wpa2_auto	="WPA/WPA2 erfordert, dass Stationen hochgradige Verschlüsselung und Authentifizierung verwenden.";

$m_cipher_type		="Verschlüsselungstyp";
$m_tkip			="TKIP";
$m_aes			="AES";
$m_psk_eap		="PSK / EAP";
$m_psk			="PSK";
$m_eap			="EAP";
$m_passphrase		="Netzwerkschlüssel";
$m_confirm_passphrase	="Bestätigter Netzwerkschlüssel";
$m_psk_hint_wording		="(8~63 ASCII oder 64 HEX)";

$m_8021x		="802.1x";
$m_radius1		="RADIUS-Server";
$m_shared_sec		="Shared Secret";
?>
