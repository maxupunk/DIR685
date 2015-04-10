<?
/* ---------------------------------- */
//$TITLE=$m_pre_title."SETUP";
/* ---------------------------------- */
$a_empty_ssid		= "Das Feld SSID darf nicht leer sein.";
$a_invalid_ssid		= "Das Feld SSID enthält ungültige Zeichen. Überprüfen Sie Ihre Eingabe.";

$a_invalid_wep_128_wep_key	= "Der Schlüssel ist ungültig. Der Schlüssel muss aus 13 Zeichen bestehen oder eine 26-stellige Hexadezimalzahl sein.";
$a_invalid_wep_64_wep_key	= "Der Schlüssel ist ungültig. Der Schlüssel muss aus 5 Zeichen bestehen oder eine 10-stellige Hexadezimalzahl sein.";
$a_invalid_wep_128_ascii_wep_key= "Der Schlüssel ist ungültig. Der Schlüssel muss aus 13 Zeichen bestehen.";
$a_invalid_wep_128_hex_wep_key	= "Der Schlüssel ist ungültig. Der Schlüssel muss eine 26-stellige Hexadezimalzahl sein.";
$a_invalid_wep_64_ascii_wep_key	= "Der Schlüssel ist ungültig. Der Schlüssel muss aus 5 Zeichen bestehen.";
$a_invalid_wep_64_hex_wep_key	= "Der Schlüssel ist ungültig. Der Schlüssel muss eine 10-stellige Hexadezimalzahl sein.";

$a_empty_defkey			= "Der standardmäßige WEP-Schlüssel darf nicht leer sein.";
$a_valid_hex_char		= "Zulässige Zeichen sind 0-9, A-F oder a-f.";
$a_valid_asc_char		= "Zulässig sind nur ASCII-Zeichen.";

$a_invalid_radius_ip1		= "Die IP-Adresse von RADIUS-Server 1 ist ungültig.";
$a_invalid_radius_ip2		= "Die IP-Adresse von RADIUS-Server 2 ist ungültig.";
$a_invalid_radius_port1		= "Der Port für RADIUS-Server 1 ist ungültig.";
$a_invalid_radius_port2		= "Der Port für RADIUS-Server 2 ist ungültig.";
$a_empty_radius_sec1		= "Der gemeinsame geheime Schlüssel für RADIUS-Server 1 darf nicht leer sein.";
$a_empty_radius_sec2		= "Der gemeinsame geheime Schlüssel für RADIUS-Server 2 darf nicht leer sein.";
$a_invalid_radius_sec1		= "Der gemeinsame geheime Schlüssel für RADIUS-Server 1 muss aus ASCII-Zeichen bestehen.";
$a_invalid_radius_sec2		= "Der gemeinsame geheime Schlüssel für RADIUS-Server 2 muss aus ASCII-Zeichen bestehen.";
$a_invalid_passphrase_len	= "Die Länge der Passphrase muss zwischen 8 und 63 liegen.";
$a_invalid_psk_len		= "Der PSK muss aus 64 Zeichen bestehen.";
$a_psk_not_match		= "Die bestätige Passphrase stimmt nicht mit der Passphrase überein.";
$a_invalid_passphrase	= "Die Passphrase muss aus ASCII-Zeichen bestehen.";
$a_invalid_psk			= "Der PSK muss hexadezimal sein.";

$a_reset_wps_pin		= "Möchten Sie die PIN wirklich auf den Standardwert zurücksetzen?";
$a_gen_new_wps_pin		= "Möchten Sie wirklich eine neue PIN erstellen?";
$a_reset_wps_unconfig	= "Möchten Sie das Gerät wirklich auf „Nicht konfiguriert“ zurücksetzen?";
$a_enable_wps_first		= "WPS wurde noch nicht aktiviert.  Drücken Sie zuerst auf \"Einstellungen speichern\", um WPS zu aktivieren.";

$m_title_wireless_setting	= "Einstellungen für drahtlose Netzwerke";

$m_enable_wireless	= "Drahtlose Netzwerke aktivieren";
$m_wlan_name		= "Name des drahtlosen Netzwerks";
$m_wlan_name_comment	= "(auch bekannt als SSID)";
$m_wlan_channel		= "Drahtloskanal";
$m_enable_auto_channel	= "Automatische Kanalauswahl aktivieren";
$m_super_g		= "Super-G-Modus";
$m_super_g_without_turbo= "Super-G ohne Turbo";
$m_super_g_with_d_turbo = "Super G mit dynamischem Turbo";
$m_xr			= "Vergrößerte Reichweite aktivieren";
$m_11g_only		= "Nur 802.11g-Modus";
$m_txrate		= "Übertragungsrate";
$m_mcrate		= "Multicast-Rate";
$m_best_auto	= "Beste (automatisch)";
$m_mbps			= "(Mbit/s)";
$m_wmm_enable	= "WMM aktivieren";
$m_wlan_qos		= "(QoS für drahtlose Netzwerke)";
$m_enable_ap_hidden	= "Verborgenes WLAN aktivieren";
$m_ap_hidden_comment	= "(auch bekannt als SSID-Übertragung)";

$m_title_wireless_security	= "WLAN-Sicherheitsmodus";

$m_security_mode	= "Sicherheitsmodus";
$m_disable_security	= "WLAN-Sicherheit deaktivieren (nicht empfohlen)";
$m_enable_wep		= "WLAN-Sicherheit mit WEP aktivieren (Standard)";
$m_wpa_security		= "WLAN-Sicherheit nur mit WPA aktivieren (erweitert)";
$m_wpa2_security	= "WLAN-Sicherheit nur mit WPA2 aktivieren (erweitert)";
$m_wpa2_auto_security	= "WLAN-Sicherheit mit WPA/WPA2 aktivieren (erweitert)";

$m_title_wep		= "WEP";
$m_auth_type		= "Authentifizierung";
$m_open			= "Offen";
$m_shared_key		= "Gemeinsamer Schlüssel";
$m_wep_key_len		= "WEP-Verschlüsselung";
$m_64bit_wep		= "64Bit";
$m_128bit_wep		= "128Bit";
$m_hex			= "HEX";
$m_ascii		= "ASCII";
$m_key_type		= "Schlüsseltyp";
$m_default_wep_key	= "Standard-WEP-Schlüssel";
$m_wep_key		= "WEP-Schlüssel";
$m_wep64_hint_wording	="(5 ASCII- oder 10 HEX-Zeichen)";
$m_wep128_hint_wording	="(13 ASCII- oder 26 HEX-Zeichen)";

$m_title_wpa		="Nur WPA";
$m_dsc_wpa		="Für „Nur WPA“ müssen die Stationen Verschlüsselung und Authentifizierung höchster Stufe anwenden.";
$m_title_wpa2		="Nur WPA2";
$m_dsc_wpa2		="Für „Nur WPA2“ müssen die Stationen Verschlüsselung und Authentifizierung höchster Stufe anwenden.";
$m_title_wpa2_auto	="WPA/WPA2";
$m_dsc_wpa2_auto	="Für WPA/WPA2 müssen die Stationen Verschlüsselung und Authentifizierung höchster Stufe anwenden.";

$m_cipher_type		="Verschlüsselungstyp";
$m_tkip			="TKIP";
$m_aes			="AES";
$m_psk_eap		="PSK / EAP";
$m_psk			="PSK";
$m_eap			="EAP";
$m_passphrase		="Netzwerkschlüssel";
$m_confirm_passphrase	="Bestätigter Netzwerkschlüssel";
$m_psk_hint_wording		="(8-63 ASCII- oder 64 HEX-Zeichen)";

$m_8021x		="802.1X";
$m_radius1		="RADIUS-Server 1";
$m_radius2		="RADIUS-Server 2";
$m_shared_sec		="Gemeinsamer geheimer Schlüssel";
?>
