<?
$m_title_firewall = "Paramètre de firewall";
$m_enable_spi="Activer SPI";
$m_enable_dos="Activer la prévention DoS";
$m_title_attack_prevention="Prévention des attaques internes";
$m_desc_attack_prevention="Prévenir les attaques de type";
$m_enable_arp_attack="Attaques ARP";
$m_enable_fake_dhcp="Faux serveur DHCP";
$m_title_firewall_rules = "Règles du firewall";
$m_action = "Action";
$m_allow = "Autoriser";
$m_deny = "Refuser";
$m_inf = "Interface";
$m_start_ip = "Adresse IP de début";
$m_end_ip	="Adresse IP de fin";
$m_protocol	="Protocole";
$m_port_range ="Plage de ports";
$m_src	="Source";
$m_dst = "Destination";
$m_schedule = "Programmation";
$m_always_on = "Toujours activé";
$m_add_new_sch = "Ajouter nouvelle programmation";
$m_title_fw_list="Liste des règles de firewall";
$m_allow_ping = "PING du WAN";
$m_remote_management="Gestion à distance";


$m_title_dmz_rule = "HÔTE DMZ";
$m_desc_dmz =
	"L'option DMZ (zone démilitarisée) permet de placer un ordinateur de ".
	"votre réseau hors de la couverture du routeur. Si un ordinateur ".
	"rencontre des difficultés avec certaines applications Internet ".
	"lorsqu'il est derrière le routeur, vous pouvez le placer dans la zone ".
	"démilitarisée pour lui conférer un accès illimité à Internet.";
$m_note_dmz = "<strong>Remarque:</strong> La mise d'un ordinateur dans le DMZ peut l’exposer à une variété de risques de sécurité. L'utilisation de cette option est seulement recommandée en tant que dernier recours.";
$m_enable_dmz_host = "Activer l'hôte DMZ";
$m_ip_addr_dmz = "Adresse IP de l'hôte DMZ"; 
$m_computer_name = "Nom d'ordinateur";


$a_no_ip_selected	= "Commencez par sélectionner une machine.";
$a_invalid_ip		= "Adresse IP incorrecte.";
$a_confirm_to_del_fw= "Voulez-vous vraiment SUPPRIMER cette règle ?";
$a_invalid_port="Port incorrect";
$a_invalid_port_range="Plage de ports incorrecte !";

$a_invalid_src_startip="Adresse IP source de début incorrecte !";
$a_src_startip_in_different_subnet   = "Adresse IP source de début incorrecte. L'adresse IP source de début et l'adresse du routeur doivent se trouver sur le même réseau.";

$a_invalid_src_endip="Adresse IP source de fin incorrecte !";
$a_src_endip_in_different_subnet   = "Adresse IP source de fin incorrecte. L'adresse IP source de fin et l'adresse du routeur doivent se trouver sur le même réseau.";

$a_invalid_dst_startip="Adresse IP cible de début incorrecte !";
$a_dst_startip_in_different_subnet   = "Adresse IP cible de début incorrecte. L'adresse IP cible de début et l'adresse du routeur doivent se trouver sur le même réseau.";

$a_invalid_dst_endip="Adresse IP cible de fin incorrecte !";
$a_dst_endip_in_different_subnet   = "Adresse IP cible de fin incorrecte. L'adresse IP cible de fin et l'adresse du routeur doivent se trouver sur le même réseau.";

$a_fw_name_cant_be_empty="Le nom d'utilisateur ne doit pas être vide.";
$a_not_support_same_direction="L'interface source et l'interface cible ne peuvent pas être identiques !";
$a_invalid_src_ip_range="Plage d'adresses IP source incorrecte.";
$a_invalid_dst_ip_range="Plage d'adresses IP cible incorrecte.";
$a_confirm_swap_fw="Voulez-vous vraiment CHANGER la priorité ?";
$a_dmzip_in_different_subnet = "Adresse IP de DMZ incorrecte ! L'adresse IP de la DMZ et l'adresse du routeur doivent être sur le même réseau.";
$a_same_rule_exist = "Ce nom '\"+get_obj(\"fw_description_\"+i).value+\"' est déjà utilisé.";
?>
