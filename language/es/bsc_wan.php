﻿<?
$m_title_ap_mode	= "Modo de punto de acceso";
$m_desc_ap_mode		= "Utilícelo para desactivar NAT en el router y convertirlo en un punto de acceso.";
$m_enable_ap_mode	= "Activar modo de punto de acceso";

$m_title_wan_type	= "Tipo de conexión a Internet";
$m_desc_wan_type	= "Elija el modo que va a utilizar el router para conectarse a Internet.";

$m_wan_type	= "Mi conexión a Internet es";
$m_static_ip	= "IP estática";
$m_dhcp		= "IP dinámica (DHCP)";
$m_pppoe	= "PPPoE (Nombre de usuario / Contraseña)";
$m_pptp		= "PPTP (Nombre de usuario / Contraseña)";
$m_l2tp		= "L2TP (Nombre de usuario / Contraseña)";
$m_russia_pptp		= "PPTP ruso (acceso doble)";
$m_russia_pppoe		= "PPPoE ruso (acceso doble)";
$m_mppe		="MPPE";
$m_wwan 	="Adaptador para USB 3G";

$m_title_static	= "Tipo de conexión de Dirección IP estática a Internet";
$m_desc_static	= "Introduzca la información de la dirección IP estática suministrada por su proveedor de servicios de Internet (ISP).";

$m_comment_isp	= "(asignado por su ISP)";
$m_subnet	= "Máscara de subred";
$m_isp_gateway	= "Dirección de la puerta de enlace ISP";
$m_macaddr	= "Dirección MAC";
$m_optional	= "(opcional)";
$m_clone_mac	= "Clonar dirección MAC";
$m_primary_dns	= "Dirección DNS primaria";
$m_secondary_dns= "Dirección DNS secundaria";
$m_mtu		= "MTU";

$m_title_dhcp	= "Tipo de conexión de IP dinámica (DHCP) a Internet";
$m_desc_dhcp	= "Use este tipo de conexión a Internet si su Proveedor de servicios de Internet (ISP) ".
								"no le proporcionara información de la Dirección IP y/o un nombre de usuario y contraseña.";

$m_host_name		= "Nombre de host";
$m_ppp_idle_time	= "Tiempo de inactividad máximo";
$m_ppp_connect_mode	= "Seleccionar modo de conexión";
$m_always_on		= "Siempre activado";
$m_manual		= "Manual";
$m_on_demand		= "Conexión a petición";

$__info_from_isp	= "Introduzca la información suministrada por su proveedor de servicios de Internet (ISP).";

$m_title_pppoe	= "PPPoE";
$m_title_russia_pppoe	= "PPPoE ruso (acceso doble)";
$m_desc_pppoe	= $__info_from_isp;
$m_title_physical	= "Parámetros físicos de WAN";

$m_dynamic_pppoe	= "PPPoE dinámico";
$m_static_pppoe		= "PPPoE estático";
$m_retype_pwd		= "Contraseña de confirmación";
$m_pppoe_svc_name	= "Nombre del servicio";
$m_minutes		= "Minutos";
$m_auto_dns		= "Recibir DNS del ISP";
$m_manual_dns	= "Introducir DNS manualmente";

$m_title_pptp	= "PPTP";
$m_title_russia_pptp	= "PPTP ruso (acceso doble)";
$m_desc_pptp	= $__info_from_isp;

$m_title_l2tp	= "L2TP";
$m_desc_l2tp	= $__info_from_isp;

$m_dynamic_ip		= "IP dinámica";
$m_static_ip		= "IP estática";
$m_gateway		= "Puerta de enlace";
$m_dns			= "DNS";
$m_server_ip		= "IP/Nombre del servidor";
$m_pptp_account		= "Cuenta PPTP";
$m_pptp_password	= "Contraseña PPTP";
$m_pptp_retype_pwd	= "Contraseña de confirmación PPTP";
$m_l2tp_account		= "Cuenta L2TP";
$m_l2tp_password	= "Contraseña L2TP";
$m_l2tp_retype_pwd	= "Contraseña de confirmación L2TP";

$m_title_wwan			= "TIPO DE CONEXIÓN A INTERNET WWAN :";
$m_desc_wwan			= "Introduzca la información suministrada por su proveedor de servicios de Internet (ISP).";
$m_card_device			= "Tarjeta";
$m_driver				= "Unidad";
$m_manufacturer			= "Fabricante";
$m_product 				= "Producto";
$m_pin_code				= "PIN";
$m_username				= "Nombre de usuario";
$m_password				= "Contraseña";
$m_dial_num				= "Número de marcación";
$m_auth_proto			= "Protocolo de autenticación";
$m_wwan_auth_auto 		= "Auto (PAP + CHAP)";
$m_wwan_pap				= "Sólo PAP";
$m_wwan_chap			= "Sólo CHAP";
$m_auto_reconn 			= "Reconexión automática";
$m_apn					= "APN";
$m_enable 				= "Activado";
$m_disable				= "Desactivado";
$m_keep_alive_int 		= "Intervalo activo";
$m_seconds 				= "(segundos)";
$m_keep_alive_server1 	= "Servidor 1 activo";
$m_keep_alive_server2 	= "Servidor 2 activo";
$m_wwan_reconn_mode		= "Modo de reconexión";
$m_wwan_minutes			= "(minutos,0=infinito)";
$m_wwan_bytes			= "(bytes)";
$m_country				= "País";
$m_isp					= "ISP";
$m_choice_country		= "seleccione su país";
$m_choice_isp			= "seleccione su isp";

$m_auth_server	= "Servidor de autenticación";
$m_login_server = "IP/Nombre del servidor de inicio de sesión";

/*----------802.1x------------*/

$m_8021x_setting	   	= "802.1x";
$m_8021x_setting_description = "Introduzca la información suministrada por su proveedor de servicios de Internet (ISP).";

$m_8021x_eap_type		= "Tipo de EAP";
$m_8021x_md5			= "MD5";
$m_8021x_peap			= "PEAP";
$m_8021x_ttls			= "TTLS";

$m_8021x_authentication	= "Autenticación";
$m_8021x_pap			= "PAP";
$m_8021x_chap			= "CHAP";
$m_8021x_mschap			= "MSCHAP";
$m_8021x_mschapv2		= "MSCHAP Versión 2";

$m_8021x_identity		= "Nombre de usuario";
$m_8021x_pass		= "Contraseña";
$m_8021x_pass2		= "Contraseña confirmada";

/*------------------------------*/


$a_invalid_ip		= "¡Dirección IP no válida!";
$a_invalid_netmask	= "¡Máscara de subred no válida!";
$a_invalid_mac		= "¡Dirección MAC no válida!";
$a_invalid_mtu		= "¡Valor MTU no válido!";
$a_invalid_hostname	= "¡Nombre de host no válido!";
$a_invalid_username	= "¡Nombre de usuario no válido!";
$a_password_mismatch	= "¡La contraseña de confirmación no coincide con la nueva contraseña!";
$a_invalid_idletime	= "¡Tiempo de inactividad no válido!";

$a_srv_in_different_subnet	= "¡Dirección IP del servidor no válida! Las direcciones del servidor y del router deben estar en la misma red.";
$a_gw_in_different_subnet	= "¡Dirección de puerta de enlace no válida! Las direcciones de la puerta de enlace y del router deben estar en la misma red.";
$a_server_empty		= "¡IP/Nombre del servidor no puede estar vacío!";
$a_account_empty	= "¡La cuenta no puede estar vacía!";

$a_card_device_not_selected = "¡Tarjeta no seleccionada!";
$a_dial_num_empty 			= "¡Número de marcación no puede estar vacío!";
$a_auth_proto_not_selected 	= "¡Protocolo de autenticación no seleccionado!";
$a_apn_empty 				= "¡APN no puede estar vacío!";
$a_keep_alive_int_empty 	= "¡Intervalo activo no puede estar vacío cuando se selecciona reconexión automática!";
$a_invalid_keep_alive_int 	= "¡El Intervalo activo debe ser un número entre 20 y 3600!";

/*---------------802.1x alert message---------------*/
$a_empty_username		= "¡El nombre de usuario no puede estar vacío!";
$a_empty_password		= "¡La contraseña no puede estar vacía!";
$a_empty_password_v		= "¡La contraseña confirmada no puede estar vacía!";
$a_diff_password		= "¡Las dos contraseñas son diferentes!";
$a_empty_field			= "¡El campo no puede estar vacío!";
/*--------------------------------------------------*/

?>
