<?
$m_title_firewall = "Firewall-Einstellung";
$m_enable_spi="SPI aktivieren";
$m_enable_dos="DoS-Schutz aktivieren";
$m_title_attack_prevention="Verhinderung interner Angriffe";
$m_desc_attack_prevention="Verhinderung des Angriffstyps";
$m_enable_arp_attack="ARP-Angriff";
$m_enable_fake_dhcp="Fake DHCP-Server";
$m_title_firewall_rules = "Firewall-Regeln";
$m_action = "Aktion";
$m_allow = "Zulassen";
$m_deny = "Verweigern";
$m_inf = "Schnittstelle";
$m_start_ip = "Erste IP-Adresse";
$m_end_ip	="Letzte IP-Adresse";
$m_protocol	="Protokoll";
$m_port_range ="Port-Bereich";
$m_src	="Quelle";
$m_dst = "Ziel";
$m_schedule = "Zeitplan";
$m_always_on = "Immer an";
$m_add_new_sch = "Neuen Zeitplan hinzufügen";
$m_title_fw_list="Liste der Firewall-Regeln";
$m_allow_ping = "PING aus dem WAN";
$m_remote_management="Remote Management (Remoteverwaltung)";
$m_title_dmz_rule = "DMZ-HOST";

$m_desc_dmz =
  "Mit der Option DMZ (Demilitarisierte Zone) haben Sie die Möglichkeit, ".
  "einen einzelnen Computer in Ihrem Netzwerk außerhalb des Routers einzurichten. ".
  "Wenn Sie einen Computer hinter dem Router haben, auf dem Anwendungen aus dem ".
  "Internet nicht richtig ausgeführt werden, können Sie diesen Computer in der DMZ ".
  "unterbringen und ihm uneingeschränkten Internetzugriff gewähren.";
  
$m_note_dmz = "<strong>Hinweis:</strong> Wenn Sie einen Computer in der DMZ platzieren, setzen Sie ihn einer Reihe von Sicherheitsrisiken aus. Die Verwendung dieser Option wird nur als letzter Ausweg empfohlen.";
$m_enable_dmz_host = "DMZ-Host aktivieren";
$m_ip_addr_dmz = "DMZ-IP-Adresse"; 
$m_computer_name = "Computername";

$a_no_ip_selected	= "Wählen Sie zuerst einen Rechner!";
$a_invalid_ip		= "Ungültige IP-Adresse!";
$a_confirm_to_del_fw= "Möchten Sie diese Regel wirklich LÖSCHEN?";
$a_invalid_port="Ungültiger Port!";
$a_invalid_port_range="Ungültiger Portbereich!";

$a_invalid_src_startip="Ungültige erste Quell-IP-Adresse!";
$a_src_startip_in_different_subnet   = "Ungültige erste Quell-IP-Adresse! Die erste Quell-IP-Adresse und die Router-Adresse müssen sich im selben Netzwerk befinden.";

$a_invalid_src_endip="Ungültige letzte Quell-IP-Adresse!";
$a_src_endip_in_different_subnet   = "Ungültige letzte Quell-IP-Adresse! Die letzte Quell-IP-Adresse und die Router-Adresse müssen sich im selben Netzwerk befinden.";

$a_invalid_dst_startip="Ungültige erste Ziel-IP-Adresse!";
$a_dst_startip_in_different_subnet   = "Ungültige erste Ziel-IP-Adresse! Die erste Ziel-IP-Adresse und die Router-Adresse müssen sich im selben Netzwerk befinden.";

$a_invalid_dst_endip="Ungültige letzte Ziel-IP-Adresse!";
$a_dst_endip_in_different_subnet   = "Ungültige letzte Ziel-IP-Adresse! Die letzte Ziel-IP-Adresse und die Router-Adresse müssen sich im selben Netzwerk befinden.";

$a_fw_name_cant_be_empty="Der Firewall-Name darf nicht leer sein!";
$a_not_support_same_direction="Die Quellschnittstelle und die Zielschnittstelle dürfen nicht identisch sein!";
$a_invalid_src_ip_range="Ungültiger Quell-IP-Adressbereich!";
$a_invalid_dst_ip_range="Ungültiger Ziel-IP-Adressbereich!";
$a_confirm_swap_fw="Möchten Sie die Priorität wirklich ändern?";
$a_dmzip_in_different_subnet = "Ungültige DMZ IP-Adresse. Die DMZ IP-Adresse und die Routeradresse sollten im gleichen Netzwerk sein.";
$a_same_rule_exist = "Der Name '\"+get_obj(\"fw_description_\"+i).value+\"' wird bereits verwendet.";
?> 
