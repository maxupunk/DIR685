<?
/* --------------------------------------------------------- */
//$TITLE=$m_pre_title."SETUP";
/* --------------------------------------------------------- */
$m_title_router_setting	= "Router-Einstellungen";
$m_desc_router_setting	=
  "In diesem Abschnitt können Sie die Router-Einstellungen für das interne Netzwerk ".
  "vornehmen.  Mit der hier eingerichteten IP-Adresse greifen Sie auf das webbasierte ".
  "Verwaltungsprogramm zu. Wenn Sie diese IP-Adresse ändern, müssen Sie unter Umständen ".
  "die Netzwerkeinstellungen der PCs anpassen, um weiterhin auf das Netzwerk zuzugreifen.";

$m_router_ipaddr	= "Router-IP-Adresse";
$m_subnet_mask		= "Standard-Subnetzmaske";
$m_domain_name		= "Lokaler Domänenname";
$m_enable_dnsr		= "DNS-Relay aktivieren";

$m_title_dhcp_svr	= "Einstellungen für DHCP-Server";
$m_desc_dhcp_svr	=
  "In diesem Abschnitt können Sie den integrierten DHCP-Server konfigurieren, um den ".
  "Computern in Ihrem Netzwerk entsprechende IP-Adressen zuzuweisen.";

$m_enable_dhcp		= "DHCP-Server aktivieren";
$m_dhcp_range		= "IP-Adressbereich für DHCP";
$m_to			= "bis";
$m_range_comment	= "(Adressen innerhalb des LAN-Subnetzes)";
$m_lease_time		= "DHCP-Laufzeit";
$m_minutes		= "(Minuten)";

$m_title_add_client	= "DHCP-Reservierung";
$m_computer_name	= "Computername";
$m_clone_mac		= "MAC-Adresse Ihres PC kopieren";

$m_title_static_client_list = "Liste der DHCP-Reservierungen";
$remaining_wording	="Anzahl noch möglicher Clients";

$m_title_client_list	= "Liste der DHCP-Clients";
$m_host_name		= "Hostname";
$m_ipaddr		= "IP-Adresse";
$m_macaddr		= "MAC-Adresse";
$m_expired_time		= "Gültigkeit";

$m_days	= "Tag(e)";
$m_hrs	= "Stunde(n)";
$m_mins	= "Minute(n)";
$m_secs	= "Sekunde(n)";

$a_invalid_ip		= "Ungültige IP-Adresse!";
$a_invalid_netmask	= "Ungültige Subnetzmaske!";
$a_network_conflict	= "Gastzonennetz muss sich von Host-Zone unterscheiden !";
$a_invalid_domain_name	= "Ungültiger Domänenname!";
$a_invalid_ip_range	= "Ungültiger IP-Adressbereich für den DHCP-Server!";
$a_invalid_lease_time	= "Ungültige DHCP-Laufzeit!";
$a_del_confirm		= "Sind Sie sicher, dass Sie diesen Eintrag löschen möchten?";
$a_same_static_mac	= "Es besteht bereits ein Eintrag mit derselben MAC-Adresse. Ändern Sie die MAC-Adresse.";
$a_same_static_ip	= "Es besteht bereits ein Eintrag mit derselben IP-Adresse. Ändern Sie die IP-Adresse.";
$a_same_static_hostname = "Es besteht bereits ein Eintrag mit demselben Computernamen. Ändern Sie den Computernamen.";
$a_same_with_lan_ip	= "Die IP-Adresse darf nicht mit der LAN-IP-Adresse identisch sein!";
$a_invalid_computer_name= "Ungültiger Computername!";
$a_invalid_mac		= "Ungültige MAC-Adresse!";
?>
