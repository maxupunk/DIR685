﻿<?
$m_title_firewall = "Firewall-Einstellung";
$m_enable_spi="SPI aktivieren";
$m_title_rtsp="ALG (APPLICATION LEVEL GATEWAY)-KONFIGURATION";
$m_enable_rtsp="RTSP aktivieren";
$m_enable_dos="DoS-Schutz aktivieren";
$m_title_attack_prevention="Schutz gegen internen Angriff";
$m_desc_attack_prevention="Verhinderung des Angriffstyps";
$m_enable_arp_attack="ARP-Angriff";
$m_enable_fake_dhcp="Fake-DHCP-Server";
$m_title_firewall_rules = "Firewall-Regeln";
$m_action = "Aktion";
$m_allow = "Zulassen";
$m_deny = "Verweigern";
$m_inf = "Schnittstelle";
$m_start_ip = "Start-IP-Adresse";
$m_end_ip	="End-IP-Adresse";
$m_protocol	="Protokoll";
$m_port_range ="Portbereich";
$m_src	="Quelle";
$m_dst = "Ziel";
$m_schedule = "Zeitplan";
$m_always_on = "Immer an";
$m_add_new_sch = "Neuen Zeitplan hinzufügen";
$m_title_fw_list="Firewall-Regelliste";
$m_allow_ping = "PING vom WAN";
$m_remote_management="Fernmanagement";


$m_title_dmz_rule = "DMZ-HOST";
$m_desc_dmz =	"Die DMZ (Demilitarized Zone) Option erlaubt es Ihnen, ".
							"einen einzelnen Computer in Ihrem Netz außerhalb ".
							"des Routers zu platzieren. Wenn Sie einen Computer haben, der Internetanwendungen ".
							"nicht erfolgreich hinter dem Router ausführen kann, können Sie ".
							"den Computer für uneingeschränkten Internet-Zugriff in der DMZ platzieren.";

$m_note_dmz =	"<strong>Hinweis:</strong> Wenn ein Computer in die DMZ gesetzt wird, ".
							"ist dieser Computer möglicherweise zahlreichen Sicherheitsrisiken ausgesetzt. Diese Option sollte daher nur ".
							"als letzter Ausweg genutzt werden.";

$m_enable_dmz_host = "DMZ-Host aktivieren";
$m_ip_addr_dmz = "DMZ IP-Adresse"; 
$m_computer_name = "Computername";


$a_no_ip_selected	= "Wählen Sie bitte erst einen Rechner";
$a_invalid_ip		= "Ungültige IP-Adresse.";
$a_confirm_to_del_fw= "Möchten Sie diese Regel wirklich LÖSCHEN?";
$a_invalid_port="Ungültiger Port";
$a_invalid_port_range="Ungültiger Portbereich";

$a_invalid_src_startip="Ungültige Quellen-IP-Startadresse";
$a_src_startip_in_different_subnet   = "Ungültige Quellen-IP-Startadresse. Die Quellen-IP-Startadresse und die Routeradresse sollten im gleichen Subnetz des Netzwerks sein.";

$a_invalid_src_endip="Ungültige Quellen-IP-Endadresse";
$a_src_endip_in_different_subnet   = "Ungültige Quellen-IP-Endadresse. Die Quellen-IP-Endadresse und die Routeradresse sollten im gleichen Subnetz des Netzwerks sein.";

$a_invalid_dst_startip="Ungültige Ziel-IP-Startadresse";
$a_dst_startip_in_different_subnet   = "Ungültige Ziel-IP-Startadresse. Die Ziel-IP-Startadresse und die Routeradresse sollten im gleichen Subnetz des Netzwerks sein.";

$a_invalid_dst_endip="Ungültige Ziel-IP-Endadresse";
$a_dst_endip_in_different_subnet   = "Ungültige Ziel-IP-Endadresse. Die Ziel-IP-Endadresse und die Routeradresse sollten im gleichen Subnetz des Netzwerks sein.";

$a_fw_name_cant_be_empty="Der Firewall-Name muss angegeben werden.";
$a_not_support_same_direction="Schnittstelle zur Quelle und zum Ziel dürfen nicht gleich sein.";
$a_invalid_src_ip_range="Ungültiger Quellen-IP-Adressbereich.";
$a_invalid_dst_ip_range="Ungültiger Ziel-IP-Adressbereich.";
$a_confirm_swap_fw="Möchten Sie die Priorität wirklich ÄNDERN?";
$a_dmzip_in_different_subnet = "Ungültige DMZ IP-Adresse. Die DMZ IP-Adresse und die Routeradresse sollten im gleichen Subnetz des Netzwerks sein.";
$a_same_rule_exist = "Der Name '\"+get_obj(\"fw_description_\"+i).value+\"' wird bereits verwendet.";
$a_not_select_inf = "Wählen Sie die Schnittstelle.";
?>
