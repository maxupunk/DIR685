<?
/* --------------------------------------------------------- */
//$TITLE=$m_pre_title."SETUP";
/* --------------------------------------------------------- */
$m_title_router_setting	= "Routereinstellungen";
$m_desc_router_setting	=	"In diesem Abschnitt können Sie die internen Netzwerkeinstellungen Ihres Routers konfigurieren.".
													"Die IP-Adresse, die hier konfiguriert wird, wird ebenfalls für den Zugriff auf die ".
													"webbasierte Verwaltungsschnittstelle genutzt. Wenn Sie hier die IP-Adresse ändern, müssen Sie möglicherweise ".
													"Ihre PC-Netzwerkeinstellungen anpassen, um wieder auf das Netzwerk zugreifen zu können.";

$m_router_ipaddr	= "Router IP-Adresse";
$m_subnet_mask		= "Standard-Subnetzmaske";
$m_domain_name		= "Lokaler Domänenname";
$m_enable_dnsr		= "DNS-Relais aktivieren";

$m_title_dhcp_svr	= "DHCP-Servereinstellungen";
$m_desc_dhcp_svr	=	"In diesem Abschnitt können Sie den integrierten DHCP-Server einrichten, sodass er ".
										"den Computern in Ihrem Netzwerk IP-Adressen zuweist.";

$m_enable_dhcp		= "DHCP-Server aktivieren";
$m_dhcp_range		= "DHCP-IP-Adressbereich";
$m_to			= "bis";
$m_range_comment	= "(Adressen innerhalb des LAN-Subnetzes)";
$m_lease_time		= "DHCP Lease-Zeit";
$m_netbios	= "NetBIOS-Announcement";
$m_netbios_learn	=	"NetBIOS vom WAN übernehmen";
$m_netbios_scope	=	"NetBIOS-Bereich";
$m_optional	=	"(optional)";
$m_netbios_type	=	"NetBIOS-Knotentyp";
$m_broadcast	=	"Broadcast only (verwenden, wenn keine WINS-Server konfiguriert sind)";
$m_ptop	=	"Point-to-Point (kein Broadcast)";
$m_mix_mode	=	"Gemischter Modus (Broadcast dann Point-to-Point)";
$m_hybrid	=	"Hybrid (Point-to-Point dann Broadcast)";
$m_primary_wins	=	"Primäre WINS IP-Adresse";
$m_secondary_wins	=	"Sekundäre WINS IP-Adresse";

$m_minutes		= "(Minuten)";

$m_title_add_client	= "DHCP-Reservierung";
$m_computer_name	= "Computername";
$m_clone_mac		= "MAC-Adresse des PCs kopieren";

$m_title_static_client_list = "DHCP-Reservierungsliste";
$remaining_wording	="Restliche Anzahl von Clients, die konfiguriert werden können";

$m_title_client_list	= "DHCP Client-Liste";
$m_host_name		= "Hostname";
$m_ipaddr		= "IP-Adresse";
$m_macaddr		= "MAC-Adresse";
$m_expired_time		= "Abgelaufene Zeit";

$m_days	= "Tag(e)";
$m_hrs	= "Stunde(n)";
$m_mins	= "Minute(n)";
$m_secs	= "Sekunde(n)";

$a_invalid_ip		= "Ungültige IP-Adresse.";
$a_invalid_netmask	= "Ungültige Subnetzmaske.";
$a_network_conflict	= "Gastzonennetz muss sich von Host-Zone unterscheiden.";
$a_lan_wan_conflict = "WAN-Netz muss sich vom LAN-Netz unterscheiden.";
$a_invalid_domain_name	= "Ungültiger Domänenname";
$a_invalid_ip_range	= "Ungültiger IP-Adressbereich für DHCP-Server";
$a_invalid_lease_time	= "Ungültige DHCP-Lease-Zeit";
$a_del_confirm		= "Möchten Sie diesen Eintrag wirklich löschen?";
$a_same_static_mac	= "Es besteht ein Eintrag mit derselben MAC-Adresse.\\n Ändern Sie bitte die MAC-Adresse.";
$a_same_static_ip	= "Es besteht ein Eintrag mit derselben IP-Adresse.\\n Ändern Sie bitte die IP-Adresse.";
$a_same_static_hostname = "	Es besteht ein Eintrag mit demselben Computernamen.\\n Ändern Sie bitte den Namen.";
$a_same_with_lan_ip	= "Die IP-Adresse darf nicht gleich der LAN-IP-Adresse sein.";
$a_invalid_computer_name= "Ungültiger Computername";
$a_invalid_mac		= "Ungültige MAC-Adresse";

$a_invalid_form         = "NetBIOS-Bereich ist nicht in einem gültigen Format.";
$a_invalid_primaywins	= "Ungültige NetBIOS primäre Namensauflösung (WINS)";
$a_invalid_secondaywins	= "Ungültige NetBIOS sekundäre Namensauflösung (WINS)";
$a_primary_null		= "Primäre WINS IP-Adresse muss angegeben werden, wenn auch eine sekundäre angegeben ist.";
?>
