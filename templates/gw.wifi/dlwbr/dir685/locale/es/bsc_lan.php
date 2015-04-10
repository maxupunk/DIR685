<?
/* --------------------------------------------------------- */
//$TITLE=$m_pre_title."CONFIGURACIÓN";
/* --------------------------------------------------------- */
$m_title_router_setting	= "Parámetros del router";
$m_desc_router_setting	=  "Utilice esta sección para configurar los parámetros de red interna de su router. ".
														"La dirección IP que está configurada aquí es la dirección IP que utiliza para acceder ".
														"a la interfaz de gestión disponible en la web. Si cambia aquí la dirección IP, podría ".
														"necesitar ajustar los parámetros de red de su PC para acceder a la red nuevamente.";

$m_router_ipaddr	= "Dirección IP del router";
$m_subnet_mask		= "Máscara de subred predeterminada";
$m_domain_name		= "Nombre de dominio local";
$m_enable_dnsr		= "Activar DNS Relay";

$m_title_dhcp_svr	= "Parámetros del servidor DHCP";
$m_desc_dhcp_svr	=	"Utilice esta sección para configurar el servidor DHCP incorporado para asignar la dirección IP a ".
										"los ordenadores de su red.";

$m_enable_dhcp		= "Activar el servidor DHCP";
$m_dhcp_range		= "Intervalo de dirección IP de DHCP";
$m_to			= "para";
$m_range_comment	= "(direcciones dentro de la subred de LAN)";
$m_lease_time		= "Tiempo de validez de DHCP";
$m_netbios	= "Anuncio de NetBIOS";
$m_netbios_learn	=	"Aprender NetBIOS de WAN";
$m_netbios_scope	=	"Alcance de NetBIOS";
$m_optional	=	"(opcional)";
$m_netbios_type	=	"Tipo de nodo de NetBIOS";
$m_broadcast	=	"Sólo difusión (úsela cuando no haya ningún servidor WINS configurado)";
$m_ptop	=	"Punto a punto (sin difusión)";
$m_mix_mode	=	"Modo mezclado (Difusión y punto a punto)";
$m_hybrid	=	"Híbrido (Punto a punto y difusión)";
$m_primary_wins	=	"Dirección IP de WINS primario";
$m_secondary_wins	=	"Dirección IP de WINS secundario";

$m_minutes		= "(minutos)";

$m_title_add_client	= "Reserva DHCP";
$m_computer_name	= "Nombre del ordenador";
$m_clone_mac		= "Copiar la dirección MAC de su PC";

$m_title_static_client_list = "Lista de reservas DHCP";
$remaining_wording	="Número de clientes restantes que se pueden configurar";

$m_title_client_list	= "Lista de clientes DHCP";
$m_host_name		= "Nombre de host";
$m_ipaddr		= "Dirección IP";
$m_macaddr		= "Dirección MAC";
$m_expired_time		= "Tiempo de caducidad";

$m_days	= "día(s)";
$m_hrs	= "horas(s)";
$m_mins	= "min(s)";
$m_secs	= "segundo(s)";

$a_invalid_ip		= "¡Dirección IP no válida!";
$a_invalid_netmask	= "¡Máscara de subred no válida!";
$a_network_conflict	= "¡La red de zona de invitados debe ser distinta a la zona de host!";
$a_lan_wan_conflict = "¡La red WAN debe ser diferente de la red LAN!";
$a_invalid_domain_name	= "¡Nombre de dominio no válido!";
$a_invalid_ip_range	= "¡Rango de dirección IP no válido para el servidor DHCP!";
$a_invalid_lease_time	= "¡Tiempo de validez de DHCP no válido!";
$a_del_confirm		= "¿Está seguro de que desea eliminar esta entrada?";
$a_same_static_mac	= "Ya hay una entrada con la misma dirección MAC.\\n Cambie la dirección MAC.";
$a_same_static_ip	= "Ya hay una entrada con la misma dirección IP.\\n Cambie la dirección IP.";
$a_same_static_hostname = "Ya hay una entrada con el mismo Nombre de ordenador.\\n Cambie el Nombre de ordenador.";
$a_same_with_lan_ip	= "¡La dirección IP no puede ser igual que la dirección IP de LAN!";
$a_invalid_computer_name= "¡Nombre de ordenador no válido!";
$a_invalid_mac		= "¡Dirección MAC no válida!";

$a_invalid_form         = "¡Alcance de NetBIOS no es una forma válida!";
$a_invalid_primaywins	= "¡Wins primario de netbios no válido!";
$a_invalid_secondaywins	= "¡Wins secundario de netbios no válido!";
$a_primary_null		= "¡La dirección IP de WINS primario debe especificarse si también se especificó el secundario!";
?>
