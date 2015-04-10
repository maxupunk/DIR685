<?
/* --------------------------------------------------------- */
//$TITLE=$m_pre_title."CONFIGURATION";
/* --------------------------------------------------------- */
$m_title_router_setting	= "Paramètres du routeur";
$m_desc_router_setting	=	"Cette section vous permet de configurer les paramètres du réseau interne de votre routeur. ".
													"L'adresse IP qui est configurée ici est l'adresse IP que vous utilisez pour accéder ".
													"à l'interface de gestion Web. Si vous modifiez l'adresse IP ici, vous devrez peut-être ".
													"régler les paramètres réseau de votre PC pour accéder de nouveau au réseau.";

$m_router_ipaddr	= "Adresse IP du routeur";
$m_subnet_mask		= "Masque de sous-réseau par défaut";
$m_domain_name		= "Nom de domaine local";
$m_enable_dnsr		= "Activer le relais DNS";

$m_title_dhcp_svr	= "Paramètres du serveur DHCP";
$m_desc_dhcp_svr	=	"Utilisez cette section pour configurer le serveur DHCP intégré et attribuer une adresse IP aux ".
										"ordinateurs de votre réseau.";

$m_enable_dhcp		= "Activer le serveur DHCP";
$m_dhcp_range		= "Plage d'adresses IP DHCP";
$m_to			= "à";
$m_range_comment	= "(adresses dans le sous-réseau local)";
$m_lease_time		= "Durée de la concession DHCP";
$m_netbios	= "Avis NetBIOS";
$m_netbios_learn	=	"Acquérir les informations NetBIOS à partir du réseau étendu";
$m_netbios_scope	=	"Portée de NetBIOS";
$m_optional	=	"(facultatif)";
$m_netbios_type	=	"Type de nœud NetBIOS";
$m_broadcast	=	"Diffusion uniquement (utilisez cette option lorsqu'aucun serveur WINS n'est configuré)";
$m_ptop	=	"Point à point (pas de diffusion)";
$m_mix_mode	=	"Mode mixte (Diffusion puis Point à point)";
$m_hybrid	=	"Hybride (Point à point puis Diffusion)";
$m_primary_wins	=	"Adresse IP principale du WINS";
$m_secondary_wins	=	"Adresse IP secondaire du WINS";

$m_minutes		= "(minutes)";

$m_title_add_client	= "Réservation DHCP";
$m_computer_name	= "Nom de l'ordinateur";
$m_clone_mac		= "Copier l'adresse MAC de votre PC";

$m_title_static_client_list = "Liste de réservations DHCP";
$remaining_wording	="Nombre d'entrées restantes qui peuvent être configurées";

$m_title_client_list	= "Liste de clients DHCP";
$m_host_name		= "Nom d'hôte";
$m_ipaddr		= "Adresse IP";
$m_macaddr		= "Adresse MAC";
$m_expired_time		= "Délai d'expiration";

$m_days	= "jour(s)";
$m_hrs	= "heure(s)";
$m_mins	= "min(s)";
$m_secs	= "sec(s)";

$a_invalid_ip		= "Adresse IP incorrecte !";
$a_invalid_netmask	= "Masque de sous-réseau incorrect !";
$a_network_conflict	= "Le réseau de la zone invité doit être différent de celui de la zone hôte !";
$a_lan_wan_conflict = "Le réseau étendu doit être différent du réseau local !";
$a_invalid_domain_name	= "Nom de domaine incorrect !";
$a_invalid_ip_range	= "Plage d'adresses IP incorrecte pour le serveur DHCP !";
$a_invalid_lease_time	= "Durée de la concession DHCP incorrecte !";
$a_del_confirm		= "Voulez-vous vraiment supprimer cette entrée ?";
$a_same_static_mac	= "Une entrée existante comporte la même adresse MAC.\\nVeuillez la modifier.";
$a_same_static_ip	= "Une entrée existante comporte la même adresse IP.\\nVeuillez la modifier.";
$a_same_static_hostname = "Une entrée existante comporte le même nom d'ordinateur.\\nVeuillez le modifier.";
$a_same_with_lan_ip	= "L'adresse IP ne peut pas être identique à celle du réseau local !";
$a_invalid_computer_name= "Nom d'ordinateur incorrect !";
$a_invalid_mac		= "Adresse MAC incorrecte !";

$a_invalid_form         = "Portée NetBIOS n'est pas un formulaire valide !";
$a_invalid_primaywins	= "Wins principal de netbios incorrect !";
$a_invalid_secondaywins	= "Wins secondaire de netbios incorrect !";
$a_primary_null		= "L'adresse IP du WINS principal doit être indiquée si l'adresse du WINS secondaire l'est aussi !";
?>
