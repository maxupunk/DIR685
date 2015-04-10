﻿<?
$m_title_firewall = "Parámetro del cortafuegos";
$m_enable_spi="Activar SPI";
$m_title_rtsp="CONFIGURACIÓN DE PUERTA DE ENLACE A NIVEL DE APLICACIÓN (ALG)";
$m_enable_rtsp="Activar RTSP";
$m_enable_dos="Activar prevención DoS";
$m_title_attack_prevention="Prevención de ataques internos";
$m_desc_attack_prevention="Evitar tipo de ataque";
$m_enable_arp_attack="Ataque ARP";
$m_enable_fake_dhcp="Falsear el servidor DHCP";
$m_title_firewall_rules = "Reglas de cortafuegos";
$m_action = "Acción";
$m_allow = "Permitir";
$m_deny = "Denegar";
$m_inf = "Interfaz";
$m_start_ip = "Dirección IP de inicio";
$m_end_ip	="Dirección IP final";
$m_protocol	="Protocolo";
$m_port_range ="Rango de puertos";
$m_src	="Origen";
$m_dst = "Destino";
$m_schedule = "Programa";
$m_always_on = "Siempre activado";
$m_add_new_sch = "Añadir nuevo programa";
$m_title_fw_list="Lista de reglas de cortafuegos";
$m_allow_ping = "PING desde WAN";
$m_remote_management="Gestión remota";


$m_title_dmz_rule = "HOST DMZ";
$m_desc_dmz =	"La opción DMZ (Zona desmilitarizada) le permite ".
							"configurar un único ordenador en su red para sacarlo".
							"del router. Si tuviera un ordenador que no pudiera ejecutar aplicaciones de ".
							"Internet satisfactoriamente desde detrás del router, ponga  ".
							"el ordenador en el DMZ para un acceso a Internet sin restricciones.";

$m_note_dmz =	"<strong>Nota:</strong> Poner un ordenador en el DMZ ".
							"podría exponer a ese ordenador a una gran variedad de riesgos de seguridad. El uso de esta opción ".
							"sólo se recomienda como el último recurso.";

$m_enable_dmz_host = "Activar host DMZ";
$m_ip_addr_dmz = "Dirección IP de DMZ"; 
$m_computer_name = "Nombre del ordenador";


$a_no_ip_selected	= "¡Seleccione antes un equipo!";
$a_invalid_ip		= "¡Dirección IP no válida!";
$a_confirm_to_del_fw= "¿Está seguro de que desea ELIMINAR esta regla?";
$a_invalid_port="¡Puerto no válido!";
$a_invalid_port_range="¡Rango de puertos no válido!";

$a_invalid_src_startip="¡Dirección IP de inicio de origen no válida!";
$a_src_startip_in_different_subnet   = "¡Dirección IP de inicio de origen no válida! La dirección IP de inicio de origen y la dirección del router deben estar en la misma subred de la red.";

$a_invalid_src_endip="¡Dirección IP final de origen no válida!";
$a_src_endip_in_different_subnet   = "¡Dirección IP final de origen no válida! La dirección IP final de origen y la dirección del router deben estar en la misma subred de la red.";

$a_invalid_dst_startip="¡Dirección IP de inicio de destino no válida!";
$a_dst_startip_in_different_subnet   = "¡Dirección IP de inicio de destino no válida! La dirección IP de inicio de destino y la dirección del router deben estar en la misma subred de la red.";

$a_invalid_dst_endip="¡Dirección IP final de destino no válida!";
$a_dst_endip_in_different_subnet   = "¡Dirección IP final de destino no válida! La dirección IP final de destino y la dirección del router deben estar en la misma subred de la red.";

$a_fw_name_cant_be_empty="¡El Nombre de cortafuegos no puede estar vacío!";
$a_not_support_same_direction="¡La interfaz de origen y la interfaz de destino no pueden ser la misma!";
$a_invalid_src_ip_range="¡Rango de dirección IP de origen no válido!";
$a_invalid_dst_ip_range="¡Rango de dirección IP de destino no válido!";
$a_confirm_swap_fw="¿Está seguro que quiere CAMBIAR la prioridad?";
$a_dmzip_in_different_subnet = "¡Dirección IP de DMZ no válida! La Dirección IP de DMZ y la dirección del router deben ser las mismas que la subred de la red.";
$a_same_rule_exist = "El nombre '\"+get_obj(\"fw_description_\"+i).value+\"' ya se ha utilizado.";
$a_not_select_inf = "Seleccione la interfaz";
?>
