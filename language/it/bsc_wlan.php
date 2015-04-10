<?
/* ---------------------------------- */
//$TITLE=$m_pre_title."CONFIGURAZIONE";
/* ---------------------------------- */
$a_empty_ssid		= "Specificare un valore nel campo SSID.";
$a_invalid_ssid		= "Il campo SSID contiene alcuni caratteri non validi. Controllarlo.";
$a_invalid_wlan_band = "Selezionare un'opzione per la banda 802.11.";

$a_invalid_wep_128_wep_key	= "Chiave non valida. La chiave deve essere composta da 13 caratteri o 26 numeri esadecimali.";
$a_invalid_wep_64_wep_key	= "Chiave non valida. La chiave deve essere composta da 5 caratteri o 10 numeri esadecimali.";
$a_invalid_wep_128_ascii_wep_key= "Chiave non valida. La chiave deve essere composta da 13 caratteri.";
$a_invalid_wep_128_hex_wep_key	= "Chiave non valida. La chiave deve essere composta da 26 numeri esadecimali.";
$a_invalid_wep_64_ascii_wep_key	= "Chiave non valida. La chiave deve essere composta da 5 caratteri.";
$a_invalid_wep_64_hex_wep_key	= "Chiave non valida. La chiave deve essere composta da 10 numeri esadecimali.";

$a_empty_defkey			= "Specificare una chiave WEP di default.";
$a_valid_hex_char		= "I caratteri ammessi sono i numeri da 0 a 9, le lettere da A a F o da a a f.";
$a_valid_asc_char		= "I caratteri ammessi sono ASCII.";

$a_invalid_radius_ip1		= "Indirizzo IP del server RADIUS non valido.";
$a_invalid_radius_port1		= "Porta del server RADIUS non valida.";
$a_empty_radius_sec1		= "Specificare un valore per il segreto condiviso del server RADIUS.";
$a_invalid_radius_sec1		= "Il segreto condiviso del server RADIUS deve essere composto da caratteri ASCII.";
$a_invalid_passphrase_len	= "La lunghezza della passphrase deve essere compresa tra 8 e 63 caratteri.";
$a_invalid_psk_len		= "Il PSK deve essere composto da 64 caratteri.";
$a_psk_not_match		= "La passphrase confermata non corrisponde alla passphrase.";
$a_invalid_passphrase	= "La passphrase deve essere composta da caratteri ASCII.";
$a_invalid_psk			= "Il PSK deve essere composto da numeri esadecimali.";
$a_unknown_auth= "Tipo di autenticazione sconosciuto.";

$a_reset_wps_pin		= "Ripristinare le impostazioni di default del PIN?";
$a_gen_new_wps_pin		= "Creare un nuovo PIN?";
$a_reset_wps_unconfig	= "Reimpostare il dispositivo in modo che non sia configurato?";
$a_enable_wps_first		= "WPS non ancora abilitato. Premere \\\"Salva impostazioni\\\" per abilitare prima WPS.";

$m_title_wireless_setting	= "Impostazioni rete wireless";

$m_enable_wireless	= "Abilita wireless";
$m_wlan_name		= "Nome rete wireless";
$m_wlan_name_comment	= "(noto anche come SSID)";

$m_wlan_band 	= "Banda 802.11";
$m_wlan_band_2g = "2,4 GHz";
$m_wlan_band_5g = "5 GHz";
$m_11g_only		= "Modalità solo 802.11g";
$m_11a_only		= "Modalità solo 802.11a";
//for support 11n
$m_wlan_mode_set        ="Modalità 802.11";
$m_wlan_mode_11b        ="Solo 802.11b";
$m_wlan_mode_11g        ="Solo 802.11g";
$m_wlan_mode_11n        ="Solo 802.11n";
$m_wlan_mode_mix        ="Combinazione 802.11 (b/g)";
$m_wlan_mode_mixn       ="Combinazione 802.11 (b/g/n)";
//for support 11a
$m_wlan_mode_11a		="Solo 802.11a";
$m_wlan_mode_11an 		="Combinazione 802.11a (a/n)";

$m_wlan_band_width      ="Ampiezza canale";
$m_wlan_short_guard     ="Intervallo di guardia breve";
$m_mhz                  ="MHz";

$m_enable_wireless	= "Abilita wireless";
$m_wlan_name		= "Nome rete wireless";
$m_wlan_name_comment	= "(noto anche come SSID)";
$m_wlan_channel		= "Canale wireless";
$m_enable_auto_channel	= "Abilita selezione automatica canali";
$m_super_g		= "Modalità Super G";
$m_super_g_without_turbo= "Super G senza Dynamic Turbo";
$m_super_g_with_d_turbo = "Super G con Dynamic Turbo";
$m_xr			= "Abilita modalità intervallo avanzata";
$m_11g_only		= "Modalità solo 802.11g";
$m_txrate		= "Velocità di trasmissione";
$m_mcrate		= "Velocità multicast";
$m_best_auto	= "Ottimale (automatico)";
$m_mbps			= "(Mbit/s)";
$m_wmm_enable	= "Abilitazione WMM";
$m_wlan_qos		= "(QoS wireless)";
$m_enable_ap_hidden	= "Abilita wireless nascosta";
$m_ap_hidden_comment	= "(nota anche come \"Disabilita trasmissione SSID\")";

$m_title_wireless_security	= "Modalità di protezione wireless";

$m_security_mode	= "Modalità di protezione";
$m_disable_security	= "Disabilita protezione wireless (opzione non consigliata)";
$m_enable_wep		= "Abilita protezione wireless WEP (di base)";
$m_wpa_security		= "Abilita solo protezione wireless WPA (avanzata)";
$m_wpa2_security	= "Abilita solo protezione wireless WPA2 (avanzata)";
$m_wpa2_auto_security	= "Abilita protezione wireless WPA/WPA2 (avanzata)";

$m_title_wep		= "WEP";
$m_auth_type		= "Autenticazione";
$m_open			= "Aperta";
$m_shared_key		= "Chiave condivisa";
$m_wep_key_len		= "Crittografia WEP";
$m_64bit_wep		= "64 Bit";
$m_128bit_wep		= "128 Bit";
$m_hex			= "HEX";
$m_ascii		= "ASCII";
$m_key_type		= "Tipo chiave";
$m_default_wep_key	= "Chiave WEP di default";
$m_wep_key		= "Chiave WEP";
$m_wep64_hint_wording	="(5 ASCII o 10 HEX)";
$m_wep128_hint_wording	="(13 ASCII o 26 HEX)";

$m_title_wpa		="Solo WPA";
$m_dsc_wpa		="Con Solo WPA è necessario che le stazioni utilizzino funzioni di crittografia e autenticazione di alto livello.";
$m_title_wpa2		="Solo WPA2";
$m_dsc_wpa2		="Con Solo WPA2 è necessario che le stazioni utilizzino funzioni di crittografia e autenticazione di alto livello.";
$m_title_wpa2_auto	="WPA/WPA2";
$m_dsc_wpa2_auto	="Con WPA/WPA2 è necessario che le stazioni utilizzino funzioni di crittografia e autenticazione di alto livello.";

$m_cipher_type		="Tipo di cifratura";
$m_tkip			="TKIP";
$m_aes			="AES";
$m_psk_eap		="PSK/EAP";
$m_psk			="PSK";
$m_eap			="EAP";
$m_passphrase		="Chiave di rete";
$m_confirm_passphrase	="Chiave di rete confermata";
$m_psk_hint_wording		="(da 8 a 63 ASCII o 64 HEX)";

$m_8021x		="802.1X";
$m_radius1		="Server RADIUS";
$m_shared_sec		="Segreto condiviso";
?>
