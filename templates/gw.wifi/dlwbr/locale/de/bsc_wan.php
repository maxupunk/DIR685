<?
$m_title_ap_mode	= "Access Point-Modus";
$m_desc_ap_mode		= "Mit Hilfe dieser Option konnen Sie NAT auf dem Router deaktivieren und diesen zu einem Access Point machen.";
$m_enable_ap_mode	= "Access Point-Modus aktivieren";

$m_title_wan_type	= "Internetverbindungstyp";
$m_desc_wan_type	= "Wahlen Sie den Modus, in dem der Router eine Verbindung mit dem Internet herstellen soll.";

$m_wan_type	= "Eigene Internetverbindung:";
$m_static_ip	= "Statische IP-Adresse";
$m_dhcp		= "Dynamische IP-Adresse (DHCP)";
$m_pppoe	= "PPPoE (Benutzername/Kennwort)";
$m_pptp		= "PPTP (Benutzername/Kennwort)";
$m_l2tp		= "L2TP (Benutzername/Kennwort)";
$m_russia_pptp		= "Russland PPTP (Zweifachzugriff)";
$m_russia_pppoe		= "Russland PPoE (Zweifachzugriff)";
$m_mppe		="MPPE";

$m_title_static	= "Internetverbindungstyp mit statischer IP-Adresse";
$m_desc_static	= "Geben Sie die statischen Adressinformationen ein, die Sie von Ihrem Internetdiensteanbieter erhalten haben.";

$m_comment_isp	= "(von Ihrem Internetdiensteanbieter zugewiesen)";
$m_subnet	= "Subnetzmaske";
$m_isp_gateway	= "ISP-Gateway-Adresse";
$m_macaddr	= "MAC-Adresse";
$m_optional	= "(optional)";
$m_clone_mac	= "MAC-Adresse übernehmen";
$m_primary_dns	= "Primäre DNS-Adresse";
$m_secondary_dns= "Sekundäre DNS-Adresse";
$m_mtu		= "MTU";

$m_title_dhcp	= "Internetverbindungstyp mit dynamischer IP (DHCP)";
$m_desc_dhcp	= "Wählen Sie diesen Internetverbindungstyp, wenn Ihnen Ihr Internetdiensteanbieter".
		"keine IP-Adressinformationen und/oder keinen Benutzernamen und kein Kennwort zugewiesen hat.";

$m_host_name		= "Hostname";
$m_ppp_idle_time	= "Maximale Leerlaufzeit";
$m_ppp_connect_mode	= "Verbindungsmodus auswählen";
$m_always_on		= "Immer aktiv";
$m_manual		= "Manuell";
$m_on_demand		= "Verbinden bei Bedarf";

$__info_from_isp	= "Geben Sie die Informationen ein, die Sie von Ihrem Internetdiensteanbieter erhalten haben.";

$m_title_pppoe	= "PPPoE";
$m_title_russia_pppoe	= "Russland PPOE (Zweifachzugriff)";
$m_desc_pppoe	= $__info_from_isp;
$m_title_physical	= "Physische WAN-Einstellungen";

$m_dynamic_pppoe	= "Dynamisches PPPoE";
$m_static_pppoe		= "Statisches PPPoE";
$m_retype_pwd		= "Kennwort bestätigen";
$m_pppoe_svc_name	= "Servicename";
$m_minutes		= "Minuten";
$m_auto_dns		= "DNS von Internetdienstanbieter empfangen";
$m_manual_dns	= "DNS manuell eingeben";

$m_title_pptp	= "PPTP";
$m_title_russia_pptp	= "Russland PPTP (Zweifachzugriff)";
$m_desc_pptp	= $__info_from_isp;

$m_title_l2tp	= "L2TP";
$m_desc_l2tp	= $__info_from_isp;

$m_dynamic_ip		= "Dynamische IP-Adresse";
$m_static_ip		= "Statische IP-Adresse";
$m_gateway		= "Gateway";
$m_dns			= "DNS";
$m_server_ip		= "Server-IP/-Name";
$m_pptp_account		= "PPTP-Konto";
$m_pptp_password	= "PPTP-Kennwort";
$m_pptp_retype_pwd	= "PPTP-Kennwort bestätigen";
$m_l2tp_account		= "L2TP-Konto";
$m_l2tp_password	= "L2TP-Kennwort";
$m_l2tp_retype_pwd	= "L2TP-Kennwort bestätigen";

$m_auth_server	= "Authentifizierungsserver";
$m_login_server = "Anmeldeserver-IP/-Name";

/*----------802.1x------------*/

$m_8021x_setting	   	= "802.1X";
$m_8021x_setting_description = "Geben Sie die Informationen ein, die Sie von Ihrem Internetdienstanbieter erhalten haben.";

$m_8021x_eap_type		= "EAP-Typ";
$m_8021x_md5			= "MD5";
$m_8021x_peap			= "PEAP";
$m_8021x_ttls			= "TTLS";

$m_8021x_authentication	= "Authentifizierung";
$m_8021x_pap			= "PAP";
$m_8021x_chap			= "CHAP";
$m_8021x_mschap			= "MSCHAP";
$m_8021x_mschapv2		= "MSCHAP Version 2";

$m_8021x_identity		= "Benutzername";
$m_8021x_pass		= "Kennwort";
$m_8021x_pass2		= "Kennwort bestätigen";

/*------------------------------*/


$a_invalid_ip		= "Ungültige IP-Adresse!";
$a_invalid_netmask	= "Ungültige Subnetzmaske!";
$a_invalid_mac		= "Ungültige MAC-Adresse!";
$a_invalid_mtu		= "Ungültiger MTU-Wert!";
$a_invalid_hostname	= "Ungültiger Hostname!";
$a_invalid_username	= "Ungültiger Benutzername!";
$a_password_mismatch	= "Das neue und das bestätigte Kennwort stimmen nicht überein.";
$a_invalid_idletime	= "Ungültige Leerlaufzeit!";

$a_srv_in_different_subnet	= "Ungültige Server-IP-Adresse! Server- und Routeradresse müssen im selben Netzwerk liegen.";
$a_gw_in_different_subnet	= "Ungültige Gateway-IP-Adresse! Gateway- und Routeradresse müssen im selben Netzwerk liegen.";
$a_server_empty		= "Server-IP/-Name darf nicht leer sein!";
$a_account_empty	= "Konto darf nicht leer sein!";

/*---------------802.1x alert message---------------*/
$a_empty_username		= "Benutzername angeben !";
$a_empty_password		= "Kennwort angeben !";
$a_empty_password_v		= "Kennwort zur Bestätigung angeben !";
$a_diff_password		= "Die zwei Kennwörter unterscheiden sich !";
$a_empty_field			= "Das Feld darf nicht leer sein !";
/*--------------------------------------------------*/

?>
