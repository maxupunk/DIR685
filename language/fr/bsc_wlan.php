﻿<?
/* ---------------------------------- */
//$TITLE=$m_pre_title."CONFIGURATION";
/* ---------------------------------- */
$a_empty_ssid		= "Le champ SSID ne peut pas être vide.";
$a_invalid_ssid		= "Le champ SSID comprend des caractères incorrects. Vérifiez.";
$a_invalid_wlan_band = "Doit sélectionner une bande 802.11.";

$a_invalid_wep_128_wep_key	= "La clé n'est pas valide. La clé doit comporter 13 caractères ou 26 caractères hexadécimaux.";
$a_invalid_wep_64_wep_key	= "La clé n'est pas valide. La clé doit comporter 5 caractères ou 10 caractères hexadécimaux.";
$a_invalid_wep_128_ascii_wep_key= "La clé n'est pas valide. La clé doit comporter 13 caractères.";
$a_invalid_wep_128_hex_wep_key	= "La clé n'est pas valide. La clé doit comporter 26 caractères hexadécimaux.";
$a_invalid_wep_64_ascii_wep_key	= "La clé n'est pas valide. La clé doit comporter 5 caractères.";
$a_invalid_wep_64_hex_wep_key	= "La clé n'est pas valide. La clé doit comporter 10 caractères hexadécimaux.";

$a_empty_defkey			= "La clé WEP par défaut ne peut pas être vide.";
$a_valid_hex_char		= "Les caractères acceptés sont 0 à 9 et A à F ou a à f.";
$a_valid_asc_char		= "Les caractères acceptés sont les caractères ASCII.";

$a_invalid_radius_ip1		= "L'adresse IP du serveur RADIUS est incorrecte.";
$a_invalid_radius_port1		= "Le port du serveur RADIUS est incorrect.";
$a_empty_radius_sec1		= "Le secret partagé du serveur RADIUS ne peut pas être vide.";
$a_invalid_radius_sec1		= "Le secret partagé du serveur RADIUS doit se composer de caractères ASCII.";
$a_invalid_passphrase_len	= "Le mot de passe doit comporter entre 8 et 63 caractères.";
$a_invalid_psk_len		= "La longueur du PSK doit être de 64.";
$a_psk_not_match		= "Le mot de passe confirmé ne correspond pas au nouveau.";
$a_invalid_passphrase	= "Le mot de passe doit comporter des caractères ASCII.";
$a_invalid_psk			= "Le PSK doit se composer de caractères hexadécimaux.";
$a_unknown_auth= "Type d'authentification inconnu.";

$a_reset_wps_pin		= "Voulez-vous vraiment réinitialiser le PIN aux valeurs d'usine ?";
$a_gen_new_wps_pin		= "Voulez-vous vraiment générer un nouveau PIN ?";
$a_reset_wps_unconfig	= "Voulez-vous vraiment réinitialiser le périphérique pour qu'il ne soit pas configuré ?";
$a_enable_wps_first		= "Le WPS n'est pas encore activé. Appuyez sur \\\"Save Settings\\\" (Enregistrer les paramètres) pour activer le WPS en premier.";

$m_title_wireless_setting	= "Paramètres du réseau sans fil";

$m_enable_wireless	= "Activer le réseau sans fil";
$m_wlan_name		= "Nom du réseau sans fil";
$m_wlan_name_comment	= "(Également appelé SSID)";

$m_wlan_band 	= "Bande 802.11";
$m_wlan_band_2g = "2,4 GHz";
$m_wlan_band_5g = "5 GHz";
$m_11g_only		= "Mode 802.11g seulement";
$m_11a_only		= "Mode 802,11a seulement";
//for support 11n
$m_wlan_mode_set        ="Mode 802.11";
$m_wlan_mode_11b        ="Mode 802.11b seulement";
$m_wlan_mode_11g        ="Mode 802.11g seulement";
$m_wlan_mode_11n        ="Mode 802.11n seulement";
$m_wlan_mode_mix        ="802.11 mixte (b/g)";
$m_wlan_mode_mixn       ="802.11 mixte (b/g/n)";
//for support 11a
$m_wlan_mode_11a		="Mode 802,11a seulement";
$m_wlan_mode_11an 		="802.11a mixte (a/n)";

$m_wlan_band_width      ="Largeur de canal";
$m_wlan_short_guard     ="Intervalle de garde court";
$m_mhz                  ="MHz";

$m_enable_wireless	= "Activer le réseau sans fil";
$m_wlan_name		= "Nom du réseau sans fil";
$m_wlan_name_comment	= "(Également appelé SSID)";
$m_wlan_channel		= "Canal sans fil";
$m_enable_auto_channel	= "Activer la sélection automatique du canal";
$m_super_g		= "Mode Super G";
$m_super_g_without_turbo= "Super G sans turbo";
$m_super_g_with_d_turbo = "Super G avec turbo dynamique";
$m_xr			= "Activer le Mode plage étendue";
$m_11g_only		= "Mode 802.11g seulement";
$m_txrate		= "Vitesse de transmission";
$m_mcrate		= "Vitesse de multidiffusion";
$m_best_auto	= "La meilleure (automatique)";
$m_mbps			= "(Mbit/s)";
$m_wmm_enable	= "Activation de WMM";
$m_wlan_qos		= "Qualité de service du réseau sans fil";
$m_enable_ap_hidden	= "Activer le mode sans fil masqué";
$m_ap_hidden_comment	= "(également appelée \"Désactiver la diffusion SSID\")";

$m_title_wireless_security	= "Mode de sécurité sans fil";

$m_security_mode	= "Mode de sécurité";
$m_disable_security	= "Désactiver la sécurité sans fil (déconseillé)";
$m_enable_wep		= "(Activer la sécurité sans fil WEP (basique)";
$m_wpa_security		= "Activer la sécurité sans fil WPA uniquement (améliorée)";
$m_wpa2_security	= "Activer la sécurité sans fil WPA2 uniquement (améliorée)";
$m_wpa2_auto_security	= "Activer la sécurité sans fil WPA/WPA2 uniquement (améliorée)";

$m_title_wep		= "WEP";
$m_auth_type		= "Authentification";
$m_open			= "Ouvrir";
$m_shared_key		= "Clé partagée";
$m_wep_key_len		= "Chiffrement WEP";
$m_64bit_wep		= "64 bits";
$m_128bit_wep		= "128 bits";
$m_hex			= "HEX";
$m_ascii		= "ASCII";
$m_key_type		= "Type de clé";
$m_default_wep_key	= "Clé WEP par défaut";
$m_wep_key		= "Clé WEP";
$m_wep64_hint_wording	="(5 ASCII ou 10 HEX)";
$m_wep128_hint_wording	="(13 ASCII ou 26 HEX)";

$m_title_wpa		="WPA seulement";
$m_dsc_wpa		="WPA seulement nécessite que les stations utilisent un chiffrement et une authentification très complexes.";
$m_title_wpa2		="WPA2 seulement";
$m_dsc_wpa2		="WPA2 seulement nécessite que les stations utilisent un chiffrement et une authentification très complexes.";
$m_title_wpa2_auto	="WPA/WPA2";
$m_dsc_wpa2_auto	="WPA/WPA2 nécessite que les stations utilisent un chiffrement et une authentification très complexes.";

$m_cipher_type		="Type de chiffrement";
$m_tkip			="TKIP";
$m_aes			="AES";
$m_psk_eap		="PSK / EAP";
$m_psk			="PSK";
$m_eap			="EAP";
$m_passphrase		="Clé de réseau";
$m_confirm_passphrase	="Clé de réseau confirmée";
$m_psk_hint_wording		="(8~63 ASCII ou 64 HEX)";

$m_8021x		="802.1X";
$m_radius1		="Serveur RADIUS";
$m_shared_sec		="Secret partagé";
?>
