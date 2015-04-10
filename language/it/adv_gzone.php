﻿<?
$m_gz_title_select			= "Selezione zona guest";
$m_gz_title_router			= "Impostazione router per zona guest";
$m_gz_title_isolate			= "Isolamento client zona guest";
$m_gz_title_to_host_routing	= "Routing tra zona host e zona guest";
$m_gz_title_dhcp_server		= "Impostazioni server DHCP per zona guest";
$m_gz_title_dhcp_client		= "Elenco client DHCP per zona guest";
$m_gz_title_lock_client		= "Blocca elenco client per zona guest";

$m_gz_desc_router	=	"In questa sezione è possibile configurare le impostazioni della zona guest per il router. ".
										"Tale zona costituisce una zona di rete distinta per consentire ai dispositivi guest di accedere a Internet.";

$m_gz_desc_isolate	=	"Abilitare la funzione per impedire ai client guest di accedere ad altri client guest nella zona guest. ".
											"I client guest possono accedere solo a Internet.";

$m_gz_desc_to_host_routing	=	"	In questa sezione è possibile abilitare il routing tra la zona host e la zona guest. ".
															"Se la funzione non è abilitata, i client guest non possono accedere ai dati dei client host.";

$m_gz_desc_dhcp_server	=	"In questa sezione è possibile configurare il server DHCP incorporato in modo che assegni automaticamente gli indirizzi IP ai ".
													"computer della rete.";

$m_gz_desc_lock_client	=	"La funzione consente di bloccare tutti i client PC presenti nella zona guest ".
													"in base a un elenco di indirizzi IP/MAC. Dopo l'abilitazione della funzione l'accesso ".
													"alla rete sarà consentito solo ai PC inclusi nell'elenco. Garantisce che nessun client aggiuntivo possa accedere ".
													"alla zona guest sia che si tratti di una connessione cablata o di una connessione wireless.";

$m_enable_gzone			= "Abilita zona guest";
$m_include_lan_port		= "Includi porta LAN";
$m_include_wireless		= "Includi wireless";
$m_wireless_name		= "Nome rete wireless";
$m_ssid_comment			= "(noto anche come SSID)";
$m_security_mode		= "Modalità di protezione";
$m_router_ip			= "Indirizzo IP router";
$m_router_netmask		= "Subnet mask di default";
$m_enable_gzone_iso		= "Abilita isolamento client zona guest";
$m_enable_gzone_route	= "Abilita routing tra le zone";
$m_enable_dhcp_server	= "Abilita server DHCP";
$m_dhcp_ip_range		= "Intervallo di indirizzi IP DHCP";
$m_to					= "a";
$m_dhcp_ip_range_comment	= "(indirizzi compresi nella subnet LAN)";
$m_dhcp_lease_time		= "Tempo di validità DHCP";
$m_dhcp_lease_time_comment	= "(minuti)";
$m_lock_client			= "Abilita BLOCCO ELENCO CLIENT";

$m_host_name		= "Nome host";
$m_expired_time		= "Ora di scadenza";

$m_encr_none	= "Disabilita protezione wireless (opzione non consigliata)";
$m_encr_wep		= "Abilita protezione wireless WEP (di base)";
$m_encr_wpa		= "Abilita solo protezione wireless WPA (avanzata)";
$m_encr_wpa2	= "Abilita solo protezione wireless WPA2 (avanzata)";
$m_encr_wpaauto	= "Abilita protezione wireless WPA/WPA2 (avanzata)";

$m_title_wep	= "WEP";
$m_auth_type	= "Autenticazione";
$m_open			= "Aperta";
$m_shared_key	= "Chiave condivisa";
$m_wep_key_len	= "Crittografia WEP";
$m_64bit_wep	= "64 Bit";
$m_128bit_wep	= "128 Bit";
$m_hex			= "HEX";
$m_ascii		= "ASCII";
$m_key_type		= "Tipo chiave";
$m_def_wep_key	= "Chiave WEP di default";
$m_wep_key		= "Chiave WEP";
$m_hint_wep64	= "(5 ASCII o 10 HEX)";
$m_hint_wep128	= "(13 ASCII o 26 HEX)";

$m_title_wpa	= "Solo WPA";
$m_dsc_wpa		= "Con Solo WPA è necessario che le stazioni utilizzino funzioni di crittografia e autenticazione di alto livello.";
$m_title_wpa2	= "Solo WPA2";
$m_dsc_wpa2		= "Con Solo WPA2 è necessario che le stazioni utilizzino funzioni di crittografia e autenticazione di alto livello.";
$m_title_wpa_2	= "WPA/WPA2";
$m_dsc_wpa_2	= "Con WPA/WPA2 è necessario che le stazioni utilizzino funzioni di crittografia e autenticazione di alto livello.";

$m_cipher_type	= "Tipo di cifratura";
$m_tkip			= "TKIP";
$m_aes			= "AES";
$m_psk			= "PSK";
$m_eap			= "EAP";
$m_passphrase	= "Chiave di rete";
$m_confirm_passphrase   ="Chiave di rete confermata";
$m_psk_hint		= "(da 8 a 63 ASCII o 64 HEX)";

$m_8021x		= "802.1X";
$m_radius_srvr	= "Server RADIUS";
$m_shared_sec	= "Segreto condiviso";

$m_days	= "giorno/i";
$m_hrs	= "ora/e";
$m_mins	= "minuto/i";
$m_secs	= "secondo/i";

$a_invalid_ip			= "Indirizzo IP non valido.";
$a_invalid_netmask		= "Subnet mask non valida.";
$a_network_conflict		= "La rete della zona guest deve essere diversa dalla zona host.";
$a_invalid_ip_range		= "Intervallo di indirizzi IP non valido per il server DHCP.";
$a_invalid_lease_time	= "Tempo di validità DHCP non valido.";

$a_empty_ssid	= "Specificare un valore nel campo SSID.";
$a_invalid_ssid	= "Il campo SSID contiene alcuni caratteri non validi. Controllarlo.";
$a_invalid_wep_128_wep_key		= "Chiave non valida. La chiave deve essere composta da 13 caratteri o 26 numeri esadecimali.";
$a_invalid_wep_64_wep_key		= "Chiave non valida. La chiave deve essere composta da 5 caratteri o 10 numeri esadecimali.";
$a_invalid_wep_128_ascii_wep_key= "Chiave non valida. La chiave deve essere composta da 13 caratteri.";
$a_invalid_wep_128_hex_wep_key	= "Chiave non valida. La chiave deve essere composta da 26 numeri esadecimali.";
$a_invalid_wep_64_ascii_wep_key	= "Chiave non valida. La chiave deve essere composta da 5 caratteri.";
$a_invalid_wep_64_hex_wep_key	= "Chiave non valida. La chiave deve essere composta da 10 numeri esadecimali.";
$a_invalid_passphrase_len		= "La lunghezza della passphrase deve essere compresa tra 8 e 63 caratteri.";
$a_invalid_passphrase			= "La passphrase deve contenere caratteri ASCII.";
$a_invalid_psk					= "Il PSK deve essere composto da numeri esadecimali.";
$a_invalid_radius_ip			= "Server RADIUS non valido";
$a_invalid_radius_port			= "Numero di porta non valido.";
$a_invalid_radius_sec			= "Segreto non valido.";


?>
