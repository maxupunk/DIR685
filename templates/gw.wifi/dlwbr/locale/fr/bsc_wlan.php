<?
/* ---------------------------------- */
//$TITLE=$m_pre_title."CONFIGURATION";
/* ---------------------------------- */
$a_empty_ssid		= "Le champ SSID ne doit pas être vide.";
$a_invalid_ssid		= "Le champ SSID comporte des caractères incorrects. Vérifiez-le.";

$a_invalid_wep_128_wep_key	= "La clé est incorrecte. La clé doit compter 13 caractères ou 26 nombres hexadécimaux.";
$a_invalid_wep_64_wep_key	= "La clé est incorrecte. La clé doit compter 5 caractères ou 10 nombres hexadécimaux.";
$a_invalid_wep_128_ascii_wep_key= "La clé est incorrecte. La clé doit compter 13 caractères.";
$a_invalid_wep_128_hex_wep_key	= "La clé est incorrecte. La clé doit compter 26 nombres hexadécimaux.";
$a_invalid_wep_64_ascii_wep_key	= "La clé est incorrecte. La clé doit compter 5 caractères.";
$a_invalid_wep_64_hex_wep_key	= "La clé est incorrecte. La clé doit compter 10 nombres hexadécimaux.";

$a_empty_defkey			= "La clé WEP par défaut ne doit pas être vide.";
$a_valid_hex_char		= "Les caractères autorisés sont 0~9, A~F ou a~f.";
$a_valid_asc_char		= "Les caractères doivent être au format ASCII.";

$a_invalid_radius_ip1		= "L'adresse IP du serveur RADIUS 1 est incorrecte.";
$a_invalid_radius_port1		= "Le port du serveur RADIUS 1 est incorrect.";
$a_empty_radius_sec1		= "Le secret partagé du serveur RADIUS 1 ne doit pas être vide.";
$a_invalid_radius_sec1		= "Le secret partagé du serveur RADIUS 1 doit être exprimé en caractères ASCII.";
$a_invalid_passphrase_len	= "La longueur de la phrase de passe doit être comprise entre 8 et 63 caractères.";
$a_invalid_psk_len		= "La longueur de la clé pré-partagée passe doit être de 64 caractères.";
$a_psk_not_match		= "La phrase de passe confirmée ne correspond pas à la phrase de passe.";
$a_invalid_passphrase	= "La phrase de passe doit être exprimée en caractères ASCII.";
$a_invalid_psk			= "La clé pré-partagée doit être exprimée en caractères hexadécimaux.";

$a_reset_wps_pin		= "Voulez-vous vraiment réinitialiser le code PIN ?";
$a_gen_new_wps_pin		= "Voulez-vous vraiment générer un nouveau code PIN ?";
$a_reset_wps_unconfig	= "Voulez-vous vraiment redéfinir l'appareil sur non configuré ?";
$a_enable_wps_first		= "La technologie WPS n'est pas encore activée.  Commencez par appuyer sur \\\"Enregistrer les paramètres\\\" pour activer la technologie WPS.";

$m_title_wireless_setting	= "Paramètres réseau sans fil";

$m_enable_wireless	= "Activer le sans fil";
$m_wlan_name		= "Nom du réseau sans fil";
$m_wlan_name_comment	= "(ou SSID)";
$m_wlan_channel		= "Canal sans fil";
$m_enable_auto_channel	= "Activer la sélection automatique des canaux";
$m_super_g		= "Mode Super G";
$m_super_g_without_turbo= "Super G sans turbo";
$m_super_g_with_d_turbo = "Super G avec turbo dynamique";
$m_xr			= "Activer le mode Plage étendue";
$m_11g_only		= "Mode 802.11g uniquement";
$m_txrate		= "Débit de transmission";
$m_mcrate		= "Taux de multidiffusion";
$m_best_auto	= "Optimal (automatique)";
$m_mbps			= "(Mbit/s)";
$m_wmm_enable	= "Compatible WMM";
$m_wlan_qos		= "(Qos sans fil)";
$m_enable_ap_hidden	= "Activer le sans fil dissimulé";
$m_ap_hidden_comment	= "(ou Diffusion SSID)";

$m_title_wireless_security	= "Mode Sécurité sans fil";

$m_security_mode	= "Mode Sécurité";
$m_disable_security	= "Désactiver la sécurité sans fil (déconseillé)";
$m_enable_wep		= "Activer la sécurité sans fil WEP (standard)";
$m_wpa_security		= "Activer la sécurité sans fil WPA uniquement (avancée)";
$m_wpa2_security	= "Activer la sécurité sans fil WPA2 uniquement (avancée)";
$m_wpa2_auto_security	= "Activer la sécurité sans fil WPA/WPA2 (avancée)";

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
$m_wep64_hint_wording	="(5 caractères ASCII ou 10 nombres hexadécimaux)";
$m_wep128_hint_wording	="(13 caractères ASCII ou 26 nombres hexadécimaux)";

$m_title_wpa		="WPA uniquement";
$m_dsc_wpa		="En mode WPA uniquement, les stations doivent appliquer un chiffrement et une authentification de haut niveau.";
$m_title_wpa2		="WPA2 uniquement";
$m_dsc_wpa2		="En mode WPA2 uniquement, les stations doivent appliquer un chiffrement et une authentification de haut niveau.";
$m_title_wpa2_auto	="WPA/WPA2";
$m_dsc_wpa2_auto	="En mode WPA/WPA2, les stations doivent appliquer un chiffrement et une authentification de haut niveau.";

$m_cipher_type		="Type de chiffrement";
$m_tkip			="TKIP";
$m_aes			="AES";
$m_psk_eap		="PSK / EAP";
$m_psk			="PSK";
$m_eap			="EAP";
$m_passphrase		="Clé réseau";
$m_confirm_passphrase	="Clé réseau confirmée";
$m_psk_hint_wording		="(8~63 caractères ASCII ou 64 nombres hexadécimaux)";

$m_8021x		="802.1X";
$m_radius1		="Serveur RADIUS";
$m_shared_sec		="Secret partagé";
?>
