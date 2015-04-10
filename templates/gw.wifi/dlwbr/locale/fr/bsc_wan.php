<?
$m_title_ap_mode	= "Mode Point d'accès";
$m_desc_ap_mode		= "Utilisez cette option pour désactiver la fonction NAT sur le routeur et le transformer en point d'accès.";
$m_enable_ap_mode	= "Activer le mode Point d'accès";

$m_title_wan_type	= "Type de connexion Internet";
$m_desc_wan_type	= "Choisissez le mode de connexion à Internet que le routeur utilisera.";

$m_wan_type	= "Ma connexion à Internet est du type";
$m_static_ip	= "IP statique";
$m_dhcp		= "IP dynamique (DHCP)";
$m_pppoe	= "PPPoE (nom d'utilisateur / mot de passe)";
$m_pptp		= "PPTP (nom d'utilisateur / mot de passe)";
$m_l2tp		= "L2TP (nom d'utilisateur / mot de passe)";
$m_russia_pptp		= "PPTP Russie (double accès)";
$m_russia_pppoe		= "PPPoE Russie (double accès)";
$m_mppe         ="MPPE";


$m_title_static	= "Connexion Internet de type adresse IP statique";
$m_desc_static	= "Saisissez l'adresse IP statique indiquée par votre fournisseur d'accès (FAI).";

$m_comment_isp	= "(attribuée par votre FAI)";
$m_subnet	= "Masque de sous-réseau";
$m_isp_gateway	= "Adresse de la passerelle du FAI";
$m_macaddr	= "Adresse MAC";
$m_optional	= "(facultatif)";
$m_clone_mac	= "Adresse MAC clone";
$m_primary_dns	= "Adresse DNS principal";
$m_secondary_dns= "Adresse DNS secondaire";
$m_mtu		= "MTU";

$m_title_dhcp	= "Connexion Internet de type IP dynamique (DHCP)";
$m_desc_dhcp	= "Sélectionnez ce type de connexion Internet si votre fournisseur d'accès (FAI) ".
		"ne vous a pas fourni d'adresse IP ni de nom d'utilisateur ni de mot de passe.";

$m_host_name		= "Nom d'hôte";
$m_ppp_idle_time	= "Temps d'inactivité maximum";
$m_ppp_connect_mode	= "Sélection du mode de connexion";
$m_always_on		= "Toujours activé";
$m_manual		= "Manuel";
$m_on_demand		= "Connexion à la demande";

$__info_from_isp	= "Saisissez les informations indiquées par votre fournisseur d'accès (FAI).";

$m_title_pppoe	= "PPPoE";
$m_title_russia_pppoe	= "PPPOE Russie (double accès)";
$m_desc_pppoe	= $__info_from_isp;
$m_title_physical	= "Paramètre physique du WAN";

$m_dynamic_pppoe	= "PPPoE dynamique";
$m_static_pppoe		= "PPPoE statique";
$m_retype_pwd		= "Ressaisir le mot de passe";
$m_pppoe_svc_name	= "Nom du service";
$m_minutes		= "Minutes";
$m_auto_dns             = "Obtenir les serveurs DNS du FAI";
$m_manual_dns   = "Entrer les serveurs DNS manuellement";



$m_title_pptp	= "PPTP";
$m_title_russia_pptp	= "PPTP Russie (double accès)";
$m_desc_pptp	= $__info_from_isp;

$m_title_l2tp	= "L2TP";
$m_desc_l2tp	= $__info_from_isp;

$m_dynamic_ip		= "IP dynamique";
$m_static_ip		= "IP statique";
$m_gateway		= "Passerelle";
$m_dns			= "DNS";
$m_server_ip		= "Adresse IP/nom du serveur";
$m_pptp_account		= "Compte PPTP";
$m_pptp_password	= "Mot de passe PPTP";
$m_pptp_retype_pwd	= "Ressaisir le mot de passe PPTP";
$m_l2tp_account		= "Compte L2TP";
$m_l2tp_password	= "Mot de passe L2TP";
$m_l2tp_retype_pwd	= "Ressaisir le mot de passe L2TP";
$m_auth_server  = "Serveur d'authentification";


$m_auth_server	= "Serveur d'authentification";
$m_login_server = "Adresse IP/nom du serveur de connexion";

/*----------802.1x------------*/

$m_8021x_setting                = "802.1x";
$m_8021x_setting_description = "Saisissez les informations fournies par votre fournisseur d'accès Internet (FAI).";

$m_8021x_eap_type               = "Type de protocole EAP";
$m_8021x_md5                    = "MD5";
$m_8021x_peap                   = "PEAP";
$m_8021x_ttls                   = "TTLS";

$m_8021x_authentication = "Authentification";
$m_8021x_pap                    = "PAP";
$m_8021x_chap                   = "CHAP";
$m_8021x_mschap                 = "MSCHAP";
$m_8021x_mschapv2               = "MSCHAP version 2";

$m_8021x_identity               = "Nom d'utilisateur";
$m_8021x_pass           = "Mot de passe";
$m_8021x_pass2          = "Mot de passe confirmé";


$a_invalid_ip		= "Adresse IP incorrecte.";
$a_invalid_netmask	= "Masque de sous-réseau incorrect.";
$a_invalid_mac		= "Adresse MAC incorrecte.";
$a_invalid_mtu		= "Valeur MTU incorrecte.";
$a_invalid_hostname	= "Nom d'hôte incorrect.";
$a_invalid_username	= "Nom d'utilisateur incorrect.";
$a_password_mismatch	= "La confirmation du mot de passe ne correspond pas au nouveau mot de passe.";
$a_invalid_idletime	= "Temps d'inactivité incorrect.";


$a_srv_in_different_subnet	= "Adresse IP du serveur incorrecte. Les adresses du serveur et du routeur doivent se trouver sur le même réseau.";
$a_gw_in_different_subnet	= "Adresse IP de la passerelle incorrecte. Les adresses de la passerelle et du routeur doivent se trouver sur le même réseau.";
$a_server_empty		= "L'adresse IP/le nom du serveur ne doit pas être vide.";
$a_account_empty	= "Le compte ne doit pas être vide.";
/*---------------802.1x alert message---------------*/
$a_empty_username               = "Le nom d'utilisateur ne peut pas être vide. ";
$a_empty_password               = "Le mot de passe ne peut pas être vide. ";
$a_empty_password_v             = "Le mot de passe confirmé ne peut pas être vide. ";
$a_diff_password                = "Les deux mots de passe sont différents. ";
$a_empty_field                  = "Le champ ne peut pas être vide. ";
/*--------------------------------------------------*/

?>
