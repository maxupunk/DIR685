<?
/* --------------------------------------------------------- */
//$TITLE=$m_pre_title."CONFIGURATION";
/* --------------------------------------------------------- */
$m_title_router_setting	= "Paramètres du routeur";
$m_desc_router_setting	=
	"Cette section vous aidera à configurer les paramètres réseau internes de votre routeur. ".
	"L’adresse IP configurée ici est celle que vous utilisez pour accéder à l'interface de gestion Web.".
	"Si vous la modifiez, il sera peut-être nécessaire d’ajuster les paramètres réseau ".
	"de votre PC pour pouvoir accéder à nouveau au réseau.";

$m_router_ipaddr	= "Adresse IP du routeur";
$m_subnet_mask		= "Masque de sous-réseau par défaut";
$m_domain_name		= "Nom du domaine local";
$m_enable_dnsr		= "Activer le relais DNS";

$m_title_dhcp_svr	= "Paramètres du serveur DHCP";
$m_desc_dhcp_svr	=
	"Cette section vous aidera à configurer le serveur DHCP intégré pour attribuer une ".
	"adresse IP aux ordinateurs de votre réseau.";

$m_enable_dhcp		= "Activer le serveur DHCP";
$m_dhcp_range		= "Plage d'adresses IP DHCP";
$m_to			= "à";
$m_range_comment	= "(adresses sur le sous-réseau local)";
$m_lease_time		= "Durée d’attribution DHCP";
$m_minutes		= "(minutes)";

$m_title_add_client	= "Réservation DHCP";
$m_computer_name	= "Nom d'ordinateur";
$m_clone_mac		= "Copier l'adresse MAC de votre PC";

$m_title_static_client_list = "Liste des réservations DHCP";
$remaining_wording	="Nombre de clients configurables restant";

$m_title_client_list	= "Liste des clients DHCP";
$m_host_name		= "Nom d'hôte";
$m_ipaddr		= "Adresse IP";
$m_macaddr		= "Adresse MAC";
$m_expired_time		= "Durée écoulée";

$m_days	= "jour(s)";
$m_hrs	= "heure(s)";
$m_mins	= "min(s)";
$m_secs	= "seconde(s)";

$a_invalid_ip		= "Adresse IP incorrecte.";
$a_invalid_netmask	= "Masque de sous-réseau incorrect.";
$a_network_conflict	= "Le réseau de la zone invité doit être différent de celui de la zone hôte. ";
$a_invalid_domain_name	= "Nom de domaine incorrect.";
$a_invalid_ip_range	= "Plage d'adresses IP incorrecte pour le serveur DHCP.";
$a_invalid_lease_time	= "Durée d'attribution DHCP incorrecte.";
$a_del_confirm		= "Voulez-vous vraiment supprimer cette entrée ?";
$a_same_static_mac	= "Une entrée existe avec la même adresse MAC. Veuillez changer l'adresse MAC.";
$a_same_static_ip	= "Une entrée existe avec la même adresse IP. Veuillez changer l'adresse IP.";
$a_same_static_hostname = "Une entrée existe avec le même nom d'ordinateur. Veuillez changer le nom d'ordinateur.";
$a_same_with_lan_ip	= "L'adresse IP ne doit pas être identique à l'adresse IP du LAN.";
$a_invalid_computer_name= "Nom d'ordinateur incorrect.";
$a_invalid_mac		= "Adresse MAC incorrecte.";
?>
