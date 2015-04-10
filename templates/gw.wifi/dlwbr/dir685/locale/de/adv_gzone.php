﻿<?
$m_gz_title_select			= "Wahl der Gastzone";
$m_gz_title_router			= "Routereinstellung für die Gastzone";
$m_gz_title_isolate			= "Gastzonen-Client-Isolation";
$m_gz_title_to_host_routing	= "Routing zwischen Host- und Gastzone";
$m_gz_title_dhcp_server		= "DHCP-Servereinstellungen für Gastzone";
$m_gz_title_dhcp_client		= "DHCP-Client-Liste für Gastzone";
$m_gz_title_lock_client		= "Gesperrte Client-Liste für Gastzone";

$m_gz_desc_router	=	"In diesem Abschnitt können Sie die Einstellungen der Gastzone Ihres Routers konfigurieren. ".
										"Sie bietet einen gesonderten Netzwerkbereich für einen Gast zum Zugriff auf das Internet.";

$m_gz_desc_isolate	=	"Aktivieren Sie die Funktion, um zu verhindern, dass Gast-Clients auf andere Clients in der Gastzone zugreifen. ".
											"Gast-Clients können nur auf das Internet zugreifen.";

$m_gz_desc_to_host_routing	=	"Verwenden Sie diese Funktion dazu, um das Routing der Daten zwischen der Host- und der Gastzone zu ermöglichen.".
															"Gast-Clients können nicht ohne Aktivierung dieser Funktion auf die Daten von Host-Clients zugreifen.";

$m_gz_desc_dhcp_server	=	"In diesem Abschnitt können Sie den integrierten DHCP-Server einrichten, sodass er ".
													"Computern in Ihrem Netzwerk IP-Adressen zuweist.";

$m_gz_desc_lock_client	=	"Die Funktion wird verwendet, um alle PC-Clients, die in der Gastzone sind, ".
													"einer IP/MAC-Adressensammelliste zuzuweisen; nur PCs auf der Liste können auf das Netzwerk zugreifen,".
													"nachdem die Funktion aktiviert wurde. Das stellt sicher, dass kein zusätzlicher Client auf die ".
													"Gastzone zugreifen kann, egal, ob es sich um eine verkabelte oder drahtlose Verbindung handelt.";

$m_enable_gzone			= "Gastzone aktivieren";
$m_include_lan_port		= "LAN-Port einbeziehen";
$m_include_wireless		= "Funk einbeziehen";
$m_wireless_name		= "Name des Funknetzes";
$m_ssid_comment			= "(Auch SSID genannt)";
$m_security_mode		= "Sicherheitsmodus";
$m_router_ip			= "Router IP-Adresse";
$m_router_netmask		= "Standard-Subnetzmaske";
$m_enable_gzone_iso		= "Gastzonen-Client-Isolation aktivieren";
$m_enable_gzone_route	= "Routing zwischen Zonen aktivieren";
$m_enable_dhcp_server	= "DHCP-Server aktivieren";
$m_dhcp_ip_range		= "DHCP-IP-Adressbereich";
$m_to					= "bis";
$m_dhcp_ip_range_comment	= "(Adressen innerhalb des LAN-Subnetzes)";
$m_dhcp_lease_time		= "DHCP Lease-Zeit";
$m_dhcp_lease_time_comment	= "(Minuten)";
$m_lock_client			= "CLIENT-SPERRLISTE aktivieren";

$m_host_name		= "Hostname";
$m_expired_time		= "Abgelaufene Zeit";

$m_encr_none	= "Funksicherheit deaktivieren (nicht empfohlen)";
$m_encr_wep		= "WEP-Funksicherheit (einfach) aktivieren";
$m_encr_wpa		= "WPA Only-Funksicherheit (erweitert) aktivieren";
$m_encr_wpa2	= "WPA2 Only-Funksicherheit (erweitert) aktivieren";
$m_encr_wpaauto	= "WPA/WPA2-Funksicherheit (erweitert) aktivieren";

$m_title_wep	= "WEP";
$m_auth_type	= "Authentifizierung";
$m_open			= "Offen";
$m_shared_key	= "Shared Key";
$m_wep_key_len	= "WEP-Verschlüsselung";
$m_64bit_wep	= "64 Bit";
$m_128bit_wep	= "128 Bit";
$m_hex			= "HEX";
$m_ascii		= "ASCII";
$m_key_type		= "Schlüsseltyp";
$m_def_wep_key	= "Standard-WEP-Schlüssel";
$m_wep_key		= "WEP-Schlüssel";
$m_hint_wep64	= "(5 ASCII oder 10 HEX)";
$m_hint_wep128	= "(13 ASCII oder 26 HEX)";

$m_title_wpa	= "WPA Only";
$m_dsc_wpa		= "WPA Only erfordert, dass Stationen hochgradige Verschlüsselung und Authentifizierung verwenden.";
$m_title_wpa2	= "WPA2 Only";
$m_dsc_wpa2		= "WPA2 Only erfordert, dass Stationen hochgradige Verschlüsselung und Authentifizierung verwenden.";
$m_title_wpa_2	= "WPA/WPA2";
$m_dsc_wpa_2	= "WPA/WPA2 erfordert, dass Stationen hochgradige Verschlüsselung und Authentifizierung verwenden.";

$m_cipher_type	= "Verschlüsselungstyp";
$m_tkip			= "TKIP";
$m_aes			= "AES";
$m_psk			= "PSK";
$m_eap			= "EAP";
$m_passphrase	= "Netzwerkschlüssel";
$m_confirm_passphrase   ="Bestätigter Netzwerkschlüssel";
$m_psk_hint		= "(8~63 ASCII oder 64 HEX)";

$m_8021x		= "802.1x";
$m_radius_srvr	= "RADIUS-Server";
$m_shared_sec	= "Shared Secret";

$m_days	= "Tag(e)";
$m_hrs	= "Stunde(n)";
$m_mins	= "Minute(n)";
$m_secs	= "Sekunde(n)";

$a_invalid_ip			= "Ungültige IP-Adresse.";
$a_invalid_netmask		= "Ungültige Subnetzmaske.";
$a_network_conflict		= "Gastzonennetz muss sich von Host-Zone unterscheiden.";
$a_invalid_ip_range		= "Ungültiger IP-Adressbereich für DHCP-Server";
$a_invalid_lease_time	= "Ungültige DHCP-Lease-Zeit";

$a_empty_ssid	= "Das Feld SSID darf nicht leer bleiben.";
$a_invalid_ssid	="Das Feld SSID enthält ungültige Zeichen. Bitte prüfen Sie dies.";
$a_invalid_wep_128_wep_key		= "Der Schlüssel ist ungültig. Er muss 13 Zeichen oder 26 hexadezimale Ziffern und Zahlen aufweisen.";
$a_invalid_wep_64_wep_key		= "Der Schlüssel ist ungültig. Er muss 5 Zeichen oder 10 hexadezimale Ziffern und Zahlen aufweisen.";
$a_invalid_wep_128_ascii_wep_key= "Der Schlüssel ist ungültig. Der Schlüssel muss 13 Zeichen aufweisen.";
$a_invalid_wep_128_hex_wep_key	= "Der Schlüssel ist ungültig. Der Schlüssel muss 26 hexadezimale Ziffern und Zahlen aufweisen.";
$a_invalid_wep_64_ascii_wep_key	= "Der Schlüssel ist ungültig. Der Schlüssel muss 5 Zeichen aufweisen.";
$a_invalid_wep_64_hex_wep_key	= "Der Schlüssel ist ungültig. Der Schlüssel muss 10 hexadezimale Ziffern und Zahlen aufweisen.";
$a_invalid_passphrase_len		= "Die Länge des Kennwortsatzes sollte 8 ~ 63 sein.";
$a_invalid_passphrase			= "Der Kennwortsatz sollte aus ASCII-Zeichen bestehen.";
$a_invalid_psk					= "PSK sollte Hexadezimal sein.";
$a_invalid_radius_ip			= "Ungültiger RADIUS-Server.";
$a_invalid_radius_port			= "Ungültige Portnummer.";
$a_invalid_radius_sec			= "Ungültiges Secret.";


?>
