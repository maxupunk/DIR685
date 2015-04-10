﻿<?
$m_gz_title_select			= "Sélection de la zone invité";
$m_gz_title_router			= "Paramètre du routeur pour la zone invité";
$m_gz_title_isolate			= "Isolation du client de la zone invité";
$m_gz_title_to_host_routing	= "Routage entre la zone hôte et la zone invité";
$m_gz_title_dhcp_server		= "Paramètres du serveur DHCP pour zone invité";
$m_gz_title_dhcp_client		= "Liste de clients DHCP pour zone invité";
$m_gz_title_lock_client		= "Liste de clients verrouillés pour zone invité";

$m_gz_desc_router	=	"Cette section vous permet de configurer les paramètres de la zone invité de votre routeur. ".
										"La zone invité est une zone réseau indépendante qui permet aux invités d'accéder à Internet.";

$m_gz_desc_isolate	=	"Activez cette fonction pour éviter que des clients invités n'accèdent à d'autres clients invités de la zone invité. ".
											"Les clients invités peuvent seulement accéder à Internet.";

$m_gz_desc_to_host_routing	=	"Cette section vous permet d'activer le routage entre la zone hôte et la zone invité, ".
															"Les clients invités ne peuvent pas accéder aux données des clients hôtes lorsque cette fonction n'est pas activée.";

$m_gz_desc_dhcp_server	=	"Cette section vous permet de configurer le serveur DHCP intégré et d'attribuer des adresses IP ".
													"aux ordinateurs de votre réseau.";

$m_gz_desc_lock_client	=	"La fonction sert à verrouiller tous les clients PC se trouvant dans la zone invité ".
													"dans une liste de regroupement d'adresses IP/MAC ; seuls les PC de cette liste peuvent accéder au réseau ".
													"après avoir activé la fonction. Vous avez ainsi la garantie qu'aucun client supplémentaire ne peut accéder ".
													"à la zone invité, qu'ils utilisent une connexion câblée ou sans fil.";

$m_enable_gzone			= "Activer la zone invité";
$m_include_lan_port		= "Inclure un port du réseau local";
$m_include_wireless		= "Inclure le mode sans fil";
$m_wireless_name		= "Nom du réseau sans fil";
$m_ssid_comment			= "(Également appelé SSID)";
$m_security_mode		= "Mode de sécurité";
$m_router_ip			= "Adresse IP du routeur";
$m_router_netmask		= "Masque de sous-réseau par défaut";
$m_enable_gzone_iso		= "Activer l'isolation du client de la zone invité";
$m_enable_gzone_route	= "Activer le routage entre les zones";
$m_enable_dhcp_server	= "Activer le serveur DHCP";
$m_dhcp_ip_range		= "Plage d'adresses IP DHCP";
$m_to					= "à";
$m_dhcp_ip_range_comment	= "(adresses dans le sous-réseau local)";
$m_dhcp_lease_time		= "Durée de la concession DHCP";
$m_dhcp_lease_time_comment	= "(minutes)";
$m_lock_client			= "Activer la LISTE DE CLIENTS VERROUILLÉS";

$m_host_name		= "Nom d'hôte";
$m_expired_time		= "Délai d'expiration";

$m_encr_none	= "Désactiver la sécurité sans fil (déconseillé)";
$m_encr_wep		= "(Activer la sécurité sans fil WEP (basique)";
$m_encr_wpa		= "Activer la sécurité sans fil WPA uniquement (améliorée)";
$m_encr_wpa2	= "Activer la sécurité sans fil WPA2 uniquement (améliorée)";
$m_encr_wpaauto	= "Activer la sécurité sans fil WPA/WPA2 uniquement (améliorée)";

$m_title_wep	= "WEP";
$m_auth_type	= "Authentification";
$m_open			= "Ouvrir";
$m_shared_key	= "Clé partagée";
$m_wep_key_len	= "Chiffrement WEP";
$m_64bit_wep	= "64 bits";
$m_128bit_wep	= "128 bits";
$m_hex			= "HEX";
$m_ascii		= "ASCII";
$m_key_type		= "Type de clé";
$m_def_wep_key	= "Clé WEP par défaut";
$m_wep_key		= "Clé WEP";
$m_hint_wep64	= "(5 ASCII ou 10 HEX)";
$m_hint_wep128	= "(13 ASCII ou 26 HEX)";

$m_title_wpa	= "WPA seulement";
$m_dsc_wpa		= "WPA seulement nécessite que les stations utilisent un chiffrement et une authentification très complexes.";
$m_title_wpa2	= "WPA2 seulement";
$m_dsc_wpa2		= "WPA2 seulement nécessite que les stations utilisent un chiffrement et une authentification très complexes.";
$m_title_wpa_2	= "WPA/WPA2";
$m_dsc_wpa_2	= "WPA/WPA2 nécessite que les stations utilisent un chiffrement et une authentification très complexes.";

$m_cipher_type	= "Type de chiffrement";
$m_tkip			= "TKIP";
$m_aes			= "AES";
$m_psk			= "PSK";
$m_eap			= "EAP";
$m_passphrase	= "Clé de réseau";
$m_confirm_passphrase   ="Clé de réseau confirmée";
$m_psk_hint		= "(8~63 ASCII ou 64 HEX)";

$m_8021x		= "802.1X";
$m_radius_srvr	= "Serveur RADIUS";
$m_shared_sec	= "Secret partagé";

$m_days	= "jour(s)";
$m_hrs	= "heure(s)";
$m_mins	= "min(s)";
$m_secs	= "sec(s)";

$a_invalid_ip			= "Adresse IP incorrecte !";
$a_invalid_netmask		= "Masque de sous-réseau incorrect !";
$a_network_conflict		= "Le réseau de la zone invité doit être différent de celui de la zone hôte !";
$a_invalid_ip_range		= "Plage d'adresses IP incorrecte pour le serveur DHCP !";
$a_invalid_lease_time	= "Durée de la concession DHCP incorrecte !";

$a_empty_ssid	= "Le champ SSID ne peut pas être vide.";
$a_invalid_ssid	= "Le champ SSID comprend des caractères incorrects. Vérifiez.";
$a_invalid_wep_128_wep_key		= "La clé n'est pas valide. La clé doit comporter 13 caractères ou 26 caractères hexadécimaux.";
$a_invalid_wep_64_wep_key		= "La clé n'est pas valide. La clé doit comporter 5 caractères ou 10 caractères hexadécimaux.";
$a_invalid_wep_128_ascii_wep_key= "La clé n'est pas valide. La clé doit comporter 13 caractères.";
$a_invalid_wep_128_hex_wep_key	= "La clé n'est pas valide. La clé doit comporter 26 caractères hexadécimaux.";
$a_invalid_wep_64_ascii_wep_key	= "La clé n'est pas valide. La clé doit comporter 5 caractères.";
$a_invalid_wep_64_hex_wep_key	= "La clé n'est pas valide. La clé doit comporter 10 caractères hexadécimaux.";
$a_invalid_passphrase_len		= "Le mot de passe doit comporter entre 8 et 63 caractères.";
$a_invalid_passphrase			= "La phrase de passe doit comporter des caractères ASCII.";
$a_invalid_psk					= "Le PSK doit se composer de caractères hexadécimaux.";
$a_invalid_radius_ip			= "Serveur RADIUS incorrect";
$a_invalid_radius_port			= "Numéro de port incorrect.";
$a_invalid_radius_sec			= "Secret incorrect.";


?>
