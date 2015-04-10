﻿<?
$m_title_firewall = "Paramètres du pare-feu";
$m_enable_spi="Activer SPI";
$m_title_rtsp="CONFIGURATION DE LA PASSERELLE DE NIVEAU APPLICATION (ALG)";
$m_enable_rtsp="Activer RTSP";
$m_enable_dos="Activer la prévention DoS";
$m_title_attack_prevention="Prévention d'attaque interne";
$m_desc_attack_prevention="Prévenir le type d'attaque";
$m_enable_arp_attack="Attaque ARP";
$m_enable_fake_dhcp="Faux serveur DHCP";
$m_title_firewall_rules = "Règles du pare-feu";
$m_action = "Action";
$m_allow = "Autoriser";
$m_deny = "Refuser";
$m_inf = "Interface";
$m_start_ip = "Adresse IP de départ";
$m_end_ip	="Adresse IP finale";
$m_protocol	="Protocole";
$m_port_range ="Plage de ports";
$m_src	="Source";
$m_dst = "Cible";
$m_schedule = "Calendrier";
$m_always_on = "Toujours activé";
$m_add_new_sch = "Ajouter un nouveau calendrier";
$m_title_fw_list="Liste de règles du pare-feu";
$m_allow_ping = "PING du réseau étendu";
$m_remote_management="Gestion à distance";


$m_title_dmz_rule = "HÔTE DMZ";
$m_desc_dmz =	"L'option DMZ (zone démilitarisée) vous permet ".
							"de configurer un seul ordinateur sur votre réseau pour qu'il soit ".
							"hors du routeur. Si votre ordinateur ne peut pas exécuter les applications ".
							"Internet derrière le routeur, placez ".
							"l'ordinateur dans la DMZ pour qu'il ait un accès illimité à Internet.";

$m_note_dmz =	"<strong>Remarque :</strong> Si vous placez un ordinateur dans la DMZ ".
							"il risque d'être exposé à divers risques pour sa sécurité. L'utilisation de cette option ".
							"est uniquement recommandée en dernier ressort.";

$m_enable_dmz_host = "Activer l'hôte DMZ";
$m_ip_addr_dmz = "Adresse IP de la DMZ"; 
$m_computer_name = "Nom de l'ordinateur";


$a_no_ip_selected	= "Commencez par sélectionner une machine !";
$a_invalid_ip		= "Adresse IP incorrecte !";
$a_confirm_to_del_fw= "Voulez-vous vraiment SUPPRIMER cette règle ?";
$a_invalid_port="Port incorrect !";
$a_invalid_port_range="Plage de ports incorrecte !";

$a_invalid_src_startip="Adresse IP de début source incorrecte !";
$a_src_startip_in_different_subnet   = "Adresse IP de départ source incorrecte ! L'adresse IP de départ source et l'adresse du routeur doivent être dans le même sous-réseau.";

$a_invalid_src_endip="Adresse IP finale source incorrecte !";
$a_src_endip_in_different_subnet   = "Adresse IP de fin source incorrecte ! L'adresse IP finale source et l'adresse du routeur doivent être dans le même sous-réseau.";

$a_invalid_dst_startip="Adresse IP de départ cible incorrecte !";
$a_dst_startip_in_different_subnet   = "Adresse IP de départ cible incorrecte ! L'adresse IP de départ cible et l'adresse du routeur doivent être dans le même sous-réseau.";

$a_invalid_dst_endip="Adresse IP finale cible incorrecte !";
$a_dst_endip_in_different_subnet   = "Adresse IP finale cible incorrecte ! L'adresse IP finale cible et l'adresse du routeur doivent être dans le même sous-réseau.";

$a_fw_name_cant_be_empty="Le nom du pare-feu ne peut pas être vide !";
$a_not_support_same_direction="Les interfaces source et cible ne peuvent pas être identiques !";
$a_invalid_src_ip_range="Plage d'adresses IP source incorrecte !";
$a_invalid_dst_ip_range="Plage d'adresses IP cible incorrecte !";
$a_confirm_swap_fw="Voulez-vous vraiment MODIFIER la priorité ?";
$a_dmzip_in_different_subnet = "Adresse IP de DMZ incorrecte ! L'adresse IP de la DMZ et l'adresse du routeur doivent être dans le même sous-réseau.";
$a_same_rule_exist = "Le nom '\"+get_obj(\"fw_description_\"+i).value+\"' est déjà utilisé.";
$a_not_select_inf = "Veuillez sélectionner une interface";
?>
