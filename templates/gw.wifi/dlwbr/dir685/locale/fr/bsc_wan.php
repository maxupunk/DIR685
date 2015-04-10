﻿<?
$m_title_ap_mode	= "Mode Point d'accès";
$m_desc_ap_mode		= "Utilisez cette option pour désactiver la NAT sur le routeur et la transformer en point d'accès.";
$m_enable_ap_mode	= "Activer le Mode point d'accès";

$m_title_wan_type	= "Type de connexion Internet";
$m_desc_wan_type	= "Choisissez le mode que le routeur doit utiliser pour se connecter à Internet.";

$m_wan_type	= "Ma connexion Internet est";
$m_static_ip	= "IP statique";
$m_dhcp		= "IP dynamique (DHCP)";
$m_pppoe	= "PPPoE (nom d'utilisateur / mot de passe)";
$m_pptp		= "PPTP (nom d'utilisateur / mot de passe)";
$m_l2tp		= "L2TP (nom d'utilisateur / mot de passe)";
$m_russia_pptp		= "PPTP Russie (double accès)";
$m_russia_pppoe		= "PPPoE Russie (double accès)";
$m_mppe		="MPPE";
$m_wwan 	="Adapter USB 3G";

$m_title_static	= "Connexion Internet de type adresse IP statique";
$m_desc_static	= "Saisissez les informations concernant l'adresse IP statique fournies par votre fournisseur d'accès Internet (FAI).";

$m_comment_isp	= "(attribué par votre FAI)";
$m_subnet	= "Masque de sous-réseau";
$m_isp_gateway	= "Adresse de passerelle du FAI";
$m_macaddr	= "Adresse MAC";
$m_optional	= "(facultatif)";
$m_clone_mac	= "Cloner l'adresse MAC";
$m_primary_dns	= "Adresse DNS principale";
$m_secondary_dns= "Adresse DNS secondaire";
$m_mtu		= "MTU";

$m_title_dhcp	= "Type de connexion Internet à IP dynamique (DHCP)";
$m_desc_dhcp	= "Utilisez ce type de connexion Internet si votre fournisseur d'accès Internet (FAI) ".
								"ne vous a fourni aucune information sur l'adresse IP ni de nom d'utilisateur et de mot de passe.";

$m_host_name		= "Nom d'hôte";
$m_ppp_idle_time	= "Temps d'inactivité maximum";
$m_ppp_connect_mode	= "Sélection du mode de connexion";
$m_always_on		= "Toujours activé";
$m_manual		= "Manuel";
$m_on_demand		= "Connecter sur demande";

$__info_from_isp	= "Saisissez les informations fournies par votre fournisseur d'accès Internet (FAI).";

$m_title_pppoe	= "PPPoE";
$m_title_russia_pppoe	= "PPPoE Russie (double accès)";
$m_desc_pppoe	= $__info_from_isp;
$m_title_physical	= "Paramètres physiques du réseau étendu";

$m_dynamic_pppoe	= "PPPoE dynamique";
$m_static_pppoe		= "PPPoE statique";
$m_retype_pwd		= "Confirmer le mot de passe";
$m_pppoe_svc_name	= "Nom du service";
$m_minutes		= "Minutes";
$m_auto_dns		= "Obtenir les serveurs DNS du FAI";
$m_manual_dns	= "Entrer les serveurs DNS manuellement";

$m_title_pptp	= "PPTP";
$m_title_russia_pptp	= "PPTP Russie (double accès)";
$m_desc_pptp	= $__info_from_isp;

$m_title_l2tp	= "L2TP";
$m_desc_l2tp	= $__info_from_isp;

$m_dynamic_ip		= "IP dynamique";
$m_static_ip		= "IP statique";
$m_gateway		= "Passerelle";
$m_dns			= "DNS";
$m_server_ip		= "IP/nom du serveur";
$m_pptp_account		= "Compte PPTP";
$m_pptp_password	= "Mot de passe PPTP";
$m_pptp_retype_pwd	= "Confirmer le mot de passe PPTP";
$m_l2tp_account		= "Compte L2TP";
$m_l2tp_password	= "Mot de passe L2TP";
$m_l2tp_retype_pwd	= "Confirmer le mot de passe L2TP";

$m_title_wwan			= "TYPE DE CONNEXION INTERNET ÉTENDU SANS FIL :";
$m_desc_wwan			= "Saisissez les informations fournies par votre fournisseur d'accès Internet (FAI).";
$m_card_device			= "Carte";
$m_driver				= "Pilote";
$m_manufacturer			= "Fabricant";
$m_product 				= "Produit";
$m_pin_code				= "PIN";
$m_username				= "Nom d'utilisateur";
$m_password				= "Mot de passe";
$m_dial_num				= "Numéro de téléphone";
$m_auth_proto			= "Protocole d'identification";
$m_wwan_auth_auto 		= "Auto (PAP + CHAP)";
$m_wwan_pap				= "PAP uniquement";
$m_wwan_chap			= "CHAP uniquement";
$m_auto_reconn 			= "Reconnexion auto";
$m_apn					= "APN";
$m_enable 				= "Activé";
$m_disable				= "Désactivé";
$m_keep_alive_int 		= "Intervalle de maintien de connexion";
$m_seconds 				= "(secondes)";
$m_keep_alive_server1 	= "Maintien de connexion serveur 1";
$m_keep_alive_server2 	= "Maintien de connexion serveur 2";
$m_wwan_reconn_mode		= "Mode reconnexion";
$m_wwan_minutes			= "(minutes,0=infini)";
$m_wwan_bytes			= "(octets)";
$m_country				= "Pays";
$m_isp					= "FAI";
$m_choice_country		= "choisissez votre pays";
$m_choice_isp			= "choisissez votre fai";

$m_auth_server	= "Serveur d'authentification";
$m_login_server = "Serveur IP/nom de connexion";

/*----------802.1x------------*/

$m_8021x_setting	   	= "802.1x";
$m_8021x_setting_description = "Saisissez les informations fournies par votre fournisseur d'accès Internet (FAI).";

$m_8021x_eap_type		= "Type d'EAP";
$m_8021x_md5			= "MD5";
$m_8021x_peap			= "PEAP";
$m_8021x_ttls			= "TTLS";

$m_8021x_authentication	= "Authentification";
$m_8021x_pap			= "PAP";
$m_8021x_chap			= "CHAP";
$m_8021x_mschap			= "MSCHAP";
$m_8021x_mschapv2		= "MSCHAP Version 2";

$m_8021x_identity		= "Nom d'utilisateur";
$m_8021x_pass		= "Mot de passe";
$m_8021x_pass2		= "Mot de passe confirmé";

/*------------------------------*/


$a_invalid_ip		= "Adresse IP incorrecte !";
$a_invalid_netmask	= "Masque de sous-réseau incorrect !";
$a_invalid_mac		= "Adresse MAC incorrecte !";
$a_invalid_mtu		= "Valeur MTU incorrecte !";
$a_invalid_hostname	= "Nom d'hôte incorrect !";
$a_invalid_username	= "Nom d'utilisateur incorrect !";
$a_password_mismatch	= "Le mot de passe de confirmation ne correspond pas au nouveau mot de passe !";
$a_invalid_idletime	= "Temps d'inactivité incorrect !"

$a_srv_in_different_subnet	="Adresse IP du serveur incorrecte ! Les adresses du serveur et du routeur doivent se trouver sur le même réseau.";
$a_gw_in_different_subnet	= "Adresse IP de passerelle incorrecte ! Les adresses de la passerelle et du routeur doivent se trouver sur le même réseau.";
$a_server_empty		= "L'adresse IP et/ou le nom du serveur ne peuvent pas être vides !";
$a_account_empty	= "Le compte ne peut pas être vide !";

$a_card_device_not_selected = "Carte non sélectionnée !";
$a_dial_num_empty 			= "Le numéro de téléphone ne peut pas être vide !";
$a_auth_proto_not_selected 	= "Protocole d'identification non sélectionné !";
$a_apn_empty 				= "L'APN ne peut pas être vide !";
$a_keep_alive_int_empty 	= "L'intervalle de maintien de connexion ne peut pas être vide lorsqu'Auto-reconnect (reconnexion auto) est sélectionné !";
$a_invalid_keep_alive_int 	= "L'intervalle de maintien de connexion doit être un numéro compris entre 20 et 3 600 !";

/*---------------802.1x alert message---------------*/
$a_empty_username		= "Le nom d'utilisateur ne peut pas être vide !";
$a_empty_password		= "Le mot de passe ne peut pas être vide !";
$a_empty_password_v		= "Le mot de passe confirmé ne peut pas être vide !";
$a_diff_password		= "Les deux mots de passe sont différents !";
$a_empty_field			= "Le champ ne peut pas être vide !";
/*--------------------------------------------------*/

?>
