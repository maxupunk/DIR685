﻿<?
/* ---------------------------------- */
//$TITLE=$m_pre_title."CONFIGURACIÓN";
/* ---------------------------------- */
$a_empty_ssid		= "El campo SSID no puede estar en blanco.";
$a_invalid_ssid		= "Existen algunos caracteres no válidos en el campo SSID. Compruébelo.";
$a_invalid_wlan_band = "Debe seleccionar una banda de frecuencia de 802.11.";

$a_invalid_wep_128_wep_key	= "La clave no es válida. La clave debe tener 13 caracteres o 26 números hexadecimales.";
$a_invalid_wep_64_wep_key	= "La clave no es válida. La clave debe tener 5 caracteres o 10 números hexadecimales.";
$a_invalid_wep_128_ascii_wep_key= "La clave no es válida. La clave debe tener 13 caracteres.";
$a_invalid_wep_128_hex_wep_key	= "La clave no es válida. La clave debe tener 26 números hexadecimales.";
$a_invalid_wep_64_ascii_wep_key	= "La clave no es válida. La clave debe tener 5 caracteres.";
$a_invalid_wep_64_hex_wep_key	= "La clave no es válida. La clave debe tener 10 números hexadecimales.";

$a_empty_defkey			= "La clave WEP predeterminada no puede estar vacía.";
$a_valid_hex_char		= "Los caracteres legales son 0~9, A~F o a~f.";
$a_valid_asc_char		= "Los caracteres legales son ASCII.";

$a_invalid_radius_ip1		= "La dirección IP del servidor RADIUS no es válida.";
$a_invalid_radius_port1		= "El Puerto del servidor RADIUS no es válido.";
$a_empty_radius_sec1		= "El secreto compartido del servidor RADIUS no puede estar vacío.";
$a_invalid_radius_sec1		= "El secreto compartido del Servidor RADIUS está formado por caracteres ASCII.";
$a_invalid_passphrase_len	= "La longitud de la frase secreta debe ser de 8~63.";
$a_invalid_psk_len		= "La longitud de PSK debe ser 64.";
$a_psk_not_match		= "La frase secreta confirmada no coincide con la frase secreta.";
$a_invalid_passphrase	= "La frase secreta debe estar compuesta por caracteres ASCII.";
$a_invalid_psk			= "La PSK debe ser Hex.";
$a_unknown_auth= "Tipo de autenticación desconocido.";

$a_reset_wps_pin		= "¿Está seguro que desea restablecer el PIN con el valor predeterminado de fábrica?";
$a_gen_new_wps_pin		= "¿Está seguro de que desea generar un nuevo PIN?";
$a_reset_wps_unconfig	= "¿Está seguro que desea restablecer el dispositivo para que esté sin configurar?";
$a_enable_wps_first		= "WPS no está activado todavía.  Pulse el \\\"Guardar parámetros\\\" para activar primero el WPS.";

$m_title_wireless_setting	= "Parámetros de red inalámbrica";

$m_enable_wireless	= "Activar inalámbrica";
$m_wlan_name		= "Nombre de la red inalámbrica";
$m_wlan_name_comment	= "(También denominada SSID";

$m_wlan_band 	= "Banda de frecuencia 802.11";
$m_wlan_band_2g = "2,4 GHz";
$m_wlan_band_5g = "5 GHz";
$m_11g_only		= "Sólo para modo 802.11g";
$m_11a_only		= "Sólo para modo 802.11a";
//for support 11n
$m_wlan_mode_set        ="Modo 802.11";
$m_wlan_mode_11b        ="Sólo 802.11b";
$m_wlan_mode_11g        ="Sólo 802.11g";
$m_wlan_mode_11n        ="Sólo 802.11n";
$m_wlan_mode_mix        ="Mezcla 802.11(b/g)";
$m_wlan_mode_mixn       ="Mezcla 802.11(b/g/n)";
//for support 11a
$m_wlan_mode_11a		="Sólo 802.11a";
$m_wlan_mode_11an 		="Mezcla 802.11a(a/n)";

$m_wlan_band_width      ="Anchura de canal";
$m_wlan_short_guard     ="Intervalo de protección corto";
$m_mhz                  ="MHz";

$m_enable_wireless	= "Activar inalámbrica";
$m_wlan_name		= "Nombre de la red inalámbrica";
$m_wlan_name_comment	= "(También denominada SSID";
$m_wlan_channel		= "Canal inalámbrico";
$m_enable_auto_channel	= "Activar selección automática de canal";
$m_super_g		= "Modo súper G";
$m_super_g_without_turbo= "Súper G sin turbo";
$m_super_g_with_d_turbo = "Súper G con turbo dinámico";
$m_xr			= "Activar el modo de rango ampliado";
$m_11g_only		= "Sólo para modo 802.11g";
$m_txrate		= "Velocidad de transmisión";
$m_mcrate		= "Velocidad de multidifusión";
$m_best_auto	= "Mejor (automático)";
$m_mbps			= "(Mbit/s)";
$m_wmm_enable	= "Activar WMM";
$m_wlan_qos		= "(QoS inalámbrico)";
$m_enable_ap_hidden	= "Activar inalámbrico oculto";
$m_ap_hidden_comment	= "(También denominado \"Desactivar difusión SSID\")";

$m_title_wireless_security	= "Modo de seguridad inalámbrica";

$m_security_mode	= "Modo de seguridad";
$m_disable_security	= "Desactivar seguridad inalámbrica (no recomendado)";
$m_enable_wep		= "Activar seguridad inalámbrica WEP (básica)";
$m_wpa_security		= "Activar sólo seguridad inalámbrica WPA (mejorada)";
$m_wpa2_security	= "Activar sólo seguridad inalámbrica WPA2 (mejorada)";
$m_wpa2_auto_security	= "Activar seguridad inalámbrica WPA/WPA2 (mejorada)";

$m_title_wep		= "WEP";
$m_auth_type		= "Autenticación";
$m_open			= "Abrir";
$m_shared_key		= "Clave compartida";
$m_wep_key_len		= "Cifrado WEP";
$m_64bit_wep		= "64 bits";
$m_128bit_wep		= "128 bits";
$m_hex			= "HEX";
$m_ascii		= "ASCII";
$m_key_type		= "Tipo de clave";
$m_default_wep_key	= "Clave WEP predeterminada";
$m_wep_key		= "Clave WEP";
$m_wep64_hint_wording	="(5 ASCII o 10 HEX)";
$m_wep128_hint_wording	="(13 ASCII o 26 HEX)";

$m_title_wpa		="Sólo WPA";
$m_dsc_wpa		="WPA sólo requiere que las estaciones utilicen cifrado y autenticación de grado alto.";
$m_title_wpa2		="Sólo WPA2";
$m_dsc_wpa2		="WPA2 sólo requiere que las estaciones utilicen cifrado y autenticación de grado alto.";
$m_title_wpa2_auto	="WPA/WPA2";
$m_dsc_wpa2_auto	="WPA/WPA2 sólo requiere que las estaciones utilicen cifrado y autenticación de grado alto.";

$m_cipher_type		="Tipo de cifrado";
$m_tkip			="TKIP";
$m_aes			="AES";
$m_psk_eap		="PSK / EAP";
$m_psk			="PSK";
$m_eap			="EAP";
$m_passphrase		="Clave de red";
$m_confirm_passphrase	="Clave de red confirmada";
$m_psk_hint_wording		="(8~63 ASCII o 64 HEX)";

$m_8021x		="802.1X";
$m_radius1		="Servidor RADIUS";
$m_shared_sec		="Secreto compartido";
?>
