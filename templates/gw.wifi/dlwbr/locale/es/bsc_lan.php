<?
/* --------------------------------------------------------- */
//$TITLE=$m_pre_title."CONFIGURACIÓN";
/* --------------------------------------------------------- */
$m_title_router_setting	= "Parámetros del router";
$m_desc_router_setting	=
	"Utilice esta sección para configurar los parámetros de red interna de su router.  La dirección IP que está configurada aquí es la dirección IP que utiliza para acceder a la interfaz de gestión basada en la web. Si cambia aquí la dirección IP, puede que necesite ajustar los parámetros de red del PC para acceder de nuevo a la red.";

$m_router_ipaddr	= "Dirección IP del router";
$m_subnet_mask		= "Máscara de subred predeterminada";
$m_domain_name		= "Nombre de dominio local";
$m_enable_dnsr		= "Activar DNS Relay";

$m_title_dhcp_svr	= "Parámetros del servidor DHCP";
$m_desc_dhcp_svr	=
	"Utilice esta sección para configurar el servidor DHCP integrado a fin de que asigne la dirección IP a los ordenadores de su red.";

$m_enable_dhcp		= "Activar el servidor DHCP";
$m_dhcp_range		= "Intervalo de dirección IP de DHCP";
$m_to			= "a";
$m_range_comment	= "(direcciones dentro de la subred de LAN)";
$m_lease_time		= "Tiempo de validez de DHCP";
$m_minutes		= "(minutos)";

$m_title_add_client	= "Reserva DHCP";
$m_computer_name	= "Nombre del ordenador";
$m_clone_mac		= "Copiar la dirección MAC del PC";

$m_title_static_client_list = "Lista de reservas DHCP";
$remaining_wording	="Número de clientes restantes que se pueden configurar";

$m_title_client_list	= "Lista de clientes DHCP";
$m_host_name		= "Nombre de host";
$m_ipaddr		= "Dirección IP";
$m_macaddr		= "Dirección MAC";
$m_expired_time		= "Tiempo de caducidad";

$m_days	= "día(s)";
$m_hrs	= "hora(s)";
$m_mins	= "min(s)";
$m_secs	= "seg(s)";

$a_invalid_ip		= "Dirección IP no válida.";
$a_invalid_netmask	= "Máscara de subred no válida.";
$a_network_conflict	= "La red de la zona de invitados debe ser diferente de la de la zona de host !";
$a_invalid_domain_name	= "INombre de dominio no válido!";
$a_invalid_ip_range	= "Rango de dirección IP no válido para el servidor DHCP !";
$a_invalid_lease_time	= "Tiempo de validez de DHCP no válido.!";
$a_del_confirm		= "¿Está seguro de que desea eliminar esta entrada?";
$a_same_static_mac	= "Hay una entrada existente con la misma dirección MAC. Cambie la dirección MAC.";
$a_same_static_ip	= "Hay una entrada existente con la misma dirección IP. Cambie la dirección IP.";
$a_same_static_hostname = "Hay una entrada existente con el mismo Nombre de ordenador. Cambie el nombre del ordenador.";
$a_same_with_lan_ip	= "La dirección IP no puede ser igual a la dirección IP de LAN!";
$a_invalid_computer_name= "Nombre de ordenador no válido!";
$a_invalid_mac		= "Dirección MAC no válida!";
?>
