﻿<?
$m_title_ap_mode	= "Modalità punto di accesso";
$m_desc_ap_mode		= "Questa opzione consente di disabilitare NAT nel router e di convertirlo in un punto di accesso.";
$m_enable_ap_mode	= "Abilita modalità punto di accesso";

$m_title_wan_type	= "Tipo di connessione Internet";
$m_desc_wan_type	= "Scegliere la modalità utilizzata dal router per la connessione a Internet.";

$m_wan_type	= "La connessione Internet è";
$m_static_ip	= "IP statico";
$m_dhcp		= "IP dinamico (DHCP)";
$m_pppoe	= "PPPoE (nome utente/password)";
$m_pptp		= "PPTP (nome utente/password)";
$m_l2tp		= "L2TP (nome utente/password)";
$m_russia_pptp		= "PPTP Russia (Dual Access)";
$m_russia_pppoe		= "PPPoE Russia (Dual Access)";
$m_mppe		="MPPE";
$m_wwan 	="Adapter USB 3G";

$m_title_static	= "Tipo di connessione Internet con indirizzo IP statico";
$m_desc_static	= "Immettere l'indirizzo IP statico fornito dall'Internet Service Provider (ISP).";

$m_comment_isp	= "(assegnato dall'ISP)";
$m_subnet	= "Subnet mask";
$m_isp_gateway	= "Indirizzo gateway ISP";
$m_macaddr	= "Indirizzo MAC";
$m_optional	= "(facoltativo)";
$m_clone_mac	= "Clona indirizzo MAC";
$m_primary_dns	= "Indirizzo DNS primario";
$m_secondary_dns= "Indirizzo DNS secondario";
$m_mtu		= "MTU";

$m_title_dhcp	= "Tipo di connessione Internet con IP dinamico (DHCP)";
$m_desc_dhcp	= "Utilizzare questo tipo di connessione Internet se l'Internet Service Provider (ISP) ".
								"non fornisce le informazioni relative all'indirizzo IP e/o il nome utente e la password.";

$m_host_name		= "Nome host";
$m_ppp_idle_time	= "Tempo massimo di inattività";
$m_ppp_connect_mode	= "Selezione modalità di connessione";
$m_always_on		= "Sempre attiva";
$m_manual		= "Manuale";
$m_on_demand		= "Connessione a richiesta";

$__info_from_isp	= "Immettere le informazioni fornite dall'Internet Service Provider (ISP).";

$m_title_pppoe	= "PPPoE";
$m_title_russia_pppoe	= "PPPoE Russia (DUAL Access)";
$m_desc_pppoe	= $__info_from_isp;
$m_title_physical	= "Impostazioni fisiche WAN";

$m_dynamic_pppoe	= "PPPoE dinamico";
$m_static_pppoe		= "PPPoE statico";
$m_retype_pwd		= "Conferma password";
$m_pppoe_svc_name	= "Nome servizio";
$m_minutes		= "Minuti";
$m_auto_dns		= "Ricevi DNS da ISP";
$m_manual_dns	= "Immetti DNS manualmente";

$m_title_pptp	= "PPTP";
$m_title_russia_pptp	= "PPTP Russia (DUAL Access)";
$m_desc_pptp	= $__info_from_isp;

$m_title_l2tp	= "L2TP";
$m_desc_l2tp	= $__info_from_isp;

$m_dynamic_ip		= "IP dinamico";
$m_static_ip		= "IP statico";
$m_gateway		= "Gateway";
$m_dns			= "DNS";
$m_server_ip		= "Nome/IP server";
$m_pptp_account		= "Account PPTP";
$m_pptp_password	= "Password PPTP";
$m_pptp_retype_pwd	= "Conferma password PPTP";
$m_l2tp_account		= "Account L2TP";
$m_l2tp_password	= "Password L2TP";
$m_l2tp_retype_pwd	= "Conferma password L2TP";

$m_title_wwan			= "TIPO DI CONNESSIONE INTERNET WWAN:";
$m_desc_wwan			= "Immettere le informazioni fornite dall'Internet Service Provider (ISP).";
$m_card_device			= "Scheda";
$m_driver				= "Driver";
$m_manufacturer			= "Produttore";
$m_product 				= "Prodotto";
$m_pin_code				= "PIN";
$m_username				= "Nome utente";
$m_password				= "Password";
$m_dial_num				= "Numero di telefono";
$m_auth_proto			= "Protocollo di autenticazione";
$m_wwan_auth_auto 		= "Automatico (PAP+CHAP)";
$m_wwan_pap				= "Solo PAP";
$m_wwan_chap			= "Solo CHAP";
$m_auto_reconn 			= "Riconnessione automatica";
$m_apn					= "APN";
$m_enable 				= "Abilitato";
$m_disable				= "Disabilitato";
$m_keep_alive_int 		= "Intervallo keep-alive";
$m_seconds 				= "(secondi)";
$m_keep_alive_server1 	= "Server keep-alive 1";
$m_keep_alive_server2 	= "Server keep-alive 2";
$m_wwan_reconn_mode		= "Modalità di riconnessione";
$m_wwan_minutes			= "(minuti, 0=infinito)";
$m_wwan_bytes			= "(byte)";
$m_country				= "Paese";
$m_isp					= "ISP";
$m_choice_country		= "selezionare il proprio paese";
$m_choice_isp			= "selezionare il proprio ISP";

$m_auth_server	= "Server di autenticazione";
$m_login_server = "Nome/IP server di accesso";

/*----------802.1x------------*/

$m_8021x_setting	   	= "802.1x";
$m_8021x_setting_description = "Immettere le informazioni fornite dall'Internet Service Provider (ISP).";

$m_8021x_eap_type		= "Tipo EAP";
$m_8021x_md5			= "MD5";
$m_8021x_peap			= "PEAP";
$m_8021x_ttls			= "TTLS";

$m_8021x_authentication	= "Autenticazione";
$m_8021x_pap			= "PAP";
$m_8021x_chap			= "CHAP";
$m_8021x_mschap			= "MSCHAP";
$m_8021x_mschapv2		= "MSCHAP versione 2";

$m_8021x_identity		= "Nome utente";
$m_8021x_pass		= "Password";
$m_8021x_pass2		= "Password confermata";

/*------------------------------*/


$a_invalid_ip		= "Indirizzo IP non valido.";
$a_invalid_netmask	= "Subnet mask non valida.";
$a_invalid_mac		= "Indirizzo MAC non valido.";
$a_invalid_mtu		= "Valore MTU non valido.";
$a_invalid_hostname	= "Nome host non valido.";
$a_invalid_username	= "Nome utente non valido.";
$a_password_mismatch	= "La password di conferma non corrisponde a quella nuova.";
$a_invalid_idletime	= "Tempo di inattività non valido.";

$a_srv_in_different_subnet	= "Indirizzo IP del server non valido. Gli indirizzi del server e del router devono appartenere alla stessa rete.";
$a_gw_in_different_subnet	= "Indirizzo IP del gateway non valido. Gli indirizzi del gateway e del router devono appartenere alla stessa rete.";
$a_server_empty		= "Specificare un nome/IP per il server.";
$a_account_empty	= "Specificare un account.";

$a_card_device_not_selected = "Scheda non selezionata.";
$a_dial_num_empty 			= "Specificare un numero di telefono.";
$a_auth_proto_not_selected 	= "Protocollo di autenticazione non selezionato.";
$a_apn_empty 				= "Specificare un nome APN.";
$a_keep_alive_int_empty 	= "Se è selezionata l'opzione per la riconnessione automatica, è necessario specificare un intervallo keep-alive.";
$a_invalid_keep_alive_int 	= "L'intervallo keep-alive deve essere un numero compreso tra 20 e 3600.";

/*---------------802.1x alert message---------------*/
$a_empty_username		= "Specificare un nome utente.";
$a_empty_password		= "Specificare una password.";
$a_empty_password_v		= "Specificare una password confermata.";
$a_diff_password		= "Le due password sono diverse.";
$a_empty_field			= "Il campo non può essere vuoto.";
/*--------------------------------------------------*/

?>
