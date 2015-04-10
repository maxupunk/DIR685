<?
$m_title_ap_mode	= "Modo de punto de acceso";
$m_desc_ap_mode		= "Utilícelo para desactivar NAT en el router y convertirlo en un punto de acceso.";
$m_enable_ap_mode	= "Activar modo de punto de acceso";

$m_title_wan_type	= "Tipo de conexión a Internet";
$m_desc_wan_type	= "Elija el modo que va a utilizar el router para conectar a Internet.";

$m_wan_type	= "Mi conexión a Internet es";
$m_static_ip	= "IP estática";
$m_dhcp		= "IP dinámica (DHCP)";
$m_pppoe	= "PPPoE (Nombre de usuario / Contraseña)";
$m_pptp		= "PPTP (Nombre de usuario / Contraseña)";
$m_l2tp		= "L2TP (Nombre de usuario / Contraseña)";
$m_russia_pptp		= "PPTP para Rusia (doble acceso)";
$m_russia_pppoe		= "PPPoE para Rusia (doble acceso)";
$m_mppe		="MPPE";

$m_title_static	= "Tipo de conexión de Dirección IP estática a Internet";
$m_desc_static	= "Introduzca la información de la dirección estática suministrada por su proveedor de servicios de Internet (ISP).";

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
$m_desc_dhcp	= "Utilice este tipo de conexión a Internet si su proveedor de servicios de Internet (ISP) no le ha proporcionado la información de la dirección IP y/o un nombre de usuario y contraseña.";

$m_host_name		= "Nombre de host";
$m_ppp_idle_time	= "Tiempo de inactividad máximo";
$m_ppp_connect_mode	= "Seleccionar modo de conexión";
$m_always_on		= "Siempre activado";
$m_manual		= "Manual";
$m_on_demand		= "Conexión a petición";

$__info_from_isp	= "Introduzca la información suministrada por su proveedor de servicios de Internet (ISP).";

$m_title_pppoe	= "PPPoE";
$m_title_russia_pppoe	= "PPPOE para Rusia (DOBLE acceso)";
$m_desc_pppoe	= $__info_from_isp;
$m_title_physical	= "Configuración de WAN física";

$m_dynamic_pppoe	= "PPPoE dinámico";
$m_static_pppoe		= "PPPoE estático";
$m_retype_pwd		= "Reescribir contraseña";
$m_pppoe_svc_name	= "Nombre del servicio";
$m_minutes		= "Minutos";
$m_auto_dns		= "Recibir DNS del ISP";
$m_manual_dns	= "Introducir DNS manualmente";

$m_title_pptp	= "PPTP";
$m_title_russia_pptp	= "PPTP para Rusia (DOBLE acceso)";
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
$m_pptp_retype_pwd	= "Reescribir contraseña PPTP";
$m_l2tp_account		= "Cuenta L2TP";
$m_l2tp_password	= "Contraseña L2TP";
$m_l2tp_retype_pwd	= "Reescribir contraseña L2TP";

$m_auth_server	= "Servidor de autenticación";
$m_login_server = "IP/Nombre del servidor de inicio de sesión";

/*----------802.1x------------*/

$m_8021x_setting	   	= "802.1x";
$m_8021x_setting_description = "Introduzca la información suministrada por su proveedor de servicios de Internet (ISP).";

$m_8021x_eap_type		= "Tipo EAP";
$m_8021x_md5			= "MD5";
$m_8021x_peap			= "PEAP";
$m_8021x_ttls			= "TTLS";

$m_8021x_authentication	= "Autenticación";
$m_8021x_pap			= "PAP";
$m_8021x_chap			= "CHAP";
$m_8021x_mschap			= "MSCHAP";
$m_8021x_mschapv2		= "MSCHAP versión 2";

$m_8021x_identity		= "Nombre de usuario";
$m_8021x_pass		= "Contraseña";
$m_8021x_pass2		= "Confirmar contraseña";

/*------------------------------*/


$a_invalid_ip		= "IDirección IP no válida!";
$a_invalid_netmask	= "Máscara de subred no válida!";
$a_invalid_mac		= "Dirección MAC no válida!";
$a_invalid_mtu		= "Valor MTU no válido!";
$a_invalid_hostname	= "Nombre de host no válido!";
$a_invalid_username	= "Nombre de usuario no válido!";
$a_password_mismatch	= "La contraseña de confirmación no coincide con la nueva contraseña!";
$a_invalid_idletime	= "Tiempo de inactividad no válido!";

$a_srv_in_different_subnet	= "Dirección IP del servidor no válida. Las direcciones del servidor y del router deben estar en la misma red.";
$a_gw_in_different_subnet	= "Dirección de puerta de enlace no válida. Las direcciones de la puerta de enlace y del router deben estar en la misma red.";
$a_server_empty		= "IP/Nombre del servidor no puede estar vacío!";
$a_account_empty	= "La cuenta no puede estar vacía !";

/*---------------802.1x alert message---------------*/
$a_empty_username		= "TEl nombre de usuario no puede estar vacío!";
$a_empty_password		= "La contraseña no puede estar vacía !";
$a_empty_password_v		= "La contraseña confirmada no puede estar vacía !";
$a_diff_password		= "Las dos contraseñas son diferentes !";
$a_empty_field			= "El campo no puede estar vacío !";
/*--------------------------------------------------*/

?>
