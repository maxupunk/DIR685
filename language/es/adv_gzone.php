﻿<?
$m_gz_title_select			= "Selección de zona de invitados";
$m_gz_title_router			= "Parámetro del router para la Zona de invitados";
$m_gz_title_isolate			= "Aislamiento de clientes en la Zona de invitados";
$m_gz_title_to_host_routing	= "Enrutamiento entre la Zona de host y la Zona de invitados";
$m_gz_title_dhcp_server		= "Parámetros del servidor DHCP para la Zona de invitados";
$m_gz_title_dhcp_client		= "Lista de clientes DHCP para la Zona de invitados";
$m_gz_title_lock_client		= "Lista de clientes bloqueados para la Zona de invitados";

$m_gz_desc_router	=	"Utilice esta sección para configurar los parámetros de la zona de invitados del router. ".
										"La zona de invitados ofrece una zona de red separada para que los invitados accedan a Internet.";

$m_gz_desc_isolate	=	"Active la función para evitar que los clientes invitados accedan a otros clientes invitados en la Zona de invitados. ".
											"Los clientes invitados sólo pueden acceder a Internet.";

$m_gz_desc_to_host_routing	=	"Use esta sección para activar el encaminamiento entre la Zona de host y la Zona de invitados, ".
															"Los clientes invitados no pueden acceder a los datos de los clientes host sin activar esta función.";

$m_gz_desc_dhcp_server	=	"Utilice esta sección para configurar el servidor DHCP incorporado para asignar las direcciones IP a ".
													"los ordenadores de su red.";

$m_gz_desc_lock_client	=	"La función se utiliza para bloquear a todos los clientes PC que están en la Zona de invitados ".
													"en una lista del conjunto de direcciones IP/MAC; sólo los PC de esta lista pueden acceder a la red ".
													"después de activar la función. Esto asegura que no pueda acceder ningún cliente adicional ".
													"a la Zona de invitados independientemente de si están utilizando una conexión cableada o inalámbrica.";

$m_enable_gzone			= "Activar zona de invitados";
$m_include_lan_port		= "Incluir puerto LAN";
$m_include_wireless		= "Incluir red inalámbrica";
$m_wireless_name		= "Nombre de la red inalámbrica";
$m_ssid_comment			= "(También denominada SSID";
$m_security_mode		= "Modo de seguridad";
$m_router_ip			= "Dirección IP del router";
$m_router_netmask		= "Máscara de subred predeterminada";
$m_enable_gzone_iso		= "Activar aislamiento de clientes en la zona de invitados";
$m_enable_gzone_route	= "Activar el enrutamiento entre zonas";
$m_enable_dhcp_server	= "Activar el servidor DHCP";
$m_dhcp_ip_range		= "Intervalo de dirección IP de DHCP";
$m_to					= "para";
$m_dhcp_ip_range_comment	= "(direcciones dentro de la subred de LAN)";
$m_dhcp_lease_time		= "Tiempo de validez de DHCP";
$m_dhcp_lease_time_comment	= "(minutos)";
$m_lock_client			= "Activar LISTA DE CLIENTES BLOQUEADOS";

$m_host_name		= "Nombre de host";
$m_expired_time		= "Tiempo de caducidad";

$m_encr_none	= "Desactivar seguridad inalámbrica (no recomendado)";
$m_encr_wep		= "Activar seguridad inalámbrica WEP (básica)";
$m_encr_wpa		= "Activar sólo seguridad inalámbrica WPA (mejorada)";
$m_encr_wpa2	= "Activar sólo seguridad inalámbrica WPA2 (mejorada)";
$m_encr_wpaauto	= "Activar seguridad inalámbrica WPA/WPA2 (mejorada)";

$m_title_wep	= "WEP";
$m_auth_type	= "Autenticación";
$m_open			= "Abrir";
$m_shared_key	= "Clave compartida";
$m_wep_key_len	= "Cifrado WEP";
$m_64bit_wep	= "64 bits";
$m_128bit_wep	= "128 bits";
$m_hex			= "HEX";
$m_ascii		= "ASCII";
$m_key_type		= "Tipo de clave";
$m_def_wep_key	= "Clave WEP predeterminada";
$m_wep_key		= "Clave WEP";
$m_hint_wep64	= "(5 ASCII o 10 HEX)";
$m_hint_wep128	= "(13 ASCII o 26 HEX)";

$m_title_wpa	= "Sólo WPA";
$m_dsc_wpa		= "WPA sólo requiere que las estaciones utilicen cifrado y autenticación de grado alto.";
$m_title_wpa2	= "Sólo WPA2";
$m_dsc_wpa2		= "WPA2 sólo requiere que las estaciones utilicen cifrado y autenticación de grado alto.";
$m_title_wpa_2	= "WPA/WPA2";
$m_dsc_wpa_2	= "WPA/WPA2 sólo requiere que las estaciones utilicen cifrado y autenticación de grado alto.";

$m_cipher_type	= "Tipo de cifrado";
$m_tkip			= "TKIP";
$m_aes			= "AES";
$m_psk			= "PSK";
$m_eap			= "EAP";
$m_passphrase	= "Clave de red";
$m_confirm_passphrase   ="Clave de red confirmada";
$m_psk_hint		= "(8~63 ASCII o 64 HEX)";

$m_8021x		= "802.1X";
$m_radius_srvr	= "Servidor RADIUS";
$m_shared_sec	= "Secreto compartido";

$m_days	= "día(s)";
$m_hrs	= "horas(s)";
$m_mins	= "min(s)";
$m_secs	= "segundo(s)";

$a_invalid_ip			= "¡Dirección IP no válida!";
$a_invalid_netmask		= "¡Máscara de subred no válida!";
$a_network_conflict		= "¡La red de zona de invitados debe ser distinta a la zona de host!";
$a_invalid_ip_range		= "¡Rango de dirección IP no válido para el servidor DHCP!";
$a_invalid_lease_time	= "¡Tiempo de validez de DHCP no válido!";

$a_empty_ssid	= "El campo SSID no puede estar en blanco.";
$a_invalid_ssid	= "Existen algunos caracteres no válidos en el campo SSID. Compruébelo.";
$a_invalid_wep_128_wep_key		= "La clave no es válida. La clave debe tener 13 caracteres o 26 números hexadecimales.";
$a_invalid_wep_64_wep_key		= "La clave no es válida. La clave debe tener 5 caracteres o 10 números hexadecimales.";
$a_invalid_wep_128_ascii_wep_key= "La clave no es válida. La clave debe tener 13 caracteres.";
$a_invalid_wep_128_hex_wep_key	= "La clave no es válida. La clave debe tener 26 números hexadecimales.";
$a_invalid_wep_64_ascii_wep_key	= "La clave no es válida. La clave debe tener 5 caracteres.";
$a_invalid_wep_64_hex_wep_key	= "La clave no es válida. La clave debe tener 10 números hexadecimales.";
$a_invalid_passphrase_len		= "La longitud de la frase secreta debe ser de 8~63.";
$a_invalid_passphrase			= "La frase secreta debe estar en caracteres ASCII.";
$a_invalid_psk					= "La PSK debe ser Hex.";
$a_invalid_radius_ip			= "Servidor RADIUS no válido.";
$a_invalid_radius_port			= "Número de puerto no válido.";
$a_invalid_radius_sec			= "Secreto no válido.";


?>
