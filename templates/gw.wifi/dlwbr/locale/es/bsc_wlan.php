<?
/* ---------------------------------- */
//$TITLE=$m_pre_title."CONFIGURACIÓN";
/* ---------------------------------- */
$a_empty_ssid		= "El campo SSID no puede estar en blanco.";
$a_invalid_ssid		= "Existen algunos caracteres no válidos en el campo SSID. Compruébelo.";

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
$a_invalid_radius_port1		= "El puerto del servidor RADIUS no es válido.";
$a_empty_radius_sec1		= "El secreto compartido del servidor RADIUS no puede estar vacío.";
$a_invalid_radius_sec1		= "El secreto compartido del servidor RADIUS debe estar en caracteres ASCII.";
$a_invalid_passphrase_len	= "La longitud de la frase secreta debe ser de 8~63.";
$a_invalid_psk_len		= "La longitud de la PSK debe ser 64.";
$a_psk_not_match		= "La frase secreta confirmada no coincide con la frase secreta.";
$a_invalid_passphrase	= "La frase secreta debe estar en caracteres ASCII.";
$a_invalid_psk			= "La PSK debe ser hexadecimal.";

$a_reset_wps_pin		= "¿Está seguro de que desea restablecer el PIN en predeterminado?";
$a_gen_new_wps_pin		= "¿Está seguro de que desea generar un nuevo PIN?";
$a_reset_wps_unconfig	= "¿Está seguro de que desea reiniciar el dispositivo en Sin configurar?";
$a_enable_wps_first		= "La función WPS no está activada todavía.  Pulse \"Guardar parámetros\" para activar antes la función WPS.";

$m_title_wireless_setting	= "Parámetros de red inalámbrica";

$m_enable_wireless	= "Activar inalámbrica";
$m_wlan_name		= "Nombre de la red inalámbrica";
$m_wlan_name_comment	= "(También denominada SSID)";
$m_wlan_channel		= "Canal inalámbrico";
$m_enable_auto_channel	= "Activar selección automática de canal";
$m_super_g		= "Modo súper G";
$m_super_g_without_turbo= "Súper G sin turbo";
$m_super_g_with_d_turbo = "Súper G con turbo dinámico";
$m_xr			= "Activar el modo de rango ampliado";
$m_11g_only		= "Modo Sólo 802.11g";
$m_txrate		= "Velocidad de transmisión";
$m_mcrate		= "Velocidad de multidifusión";
$m_best_auto	= "Mejor (automático)";
$m_mbps			= "(Mbit/s)";
$m_wmm_enable	= "Activar WMM";
$m_wlan_qos		= "(Qos inalámbrico)";
$m_enable_ap_hidden	= "Activar red inalámbrica oculta";
$m_ap_hidden_comment	= "(También denominada difusión SSID)";

$m_title_wireless_security	= "Modo de seguridad inalámbrica";

$m_security_mode	= "Modo de seguridad";
$m_disable_security	= "Desactivar seguridad inalámbrica (no recomendado)";
$m_enable_wep		= "Activar seguridad inalámbrica WEP (básica)";
$m_wpa_security		= "Activar seguridad inalámbrica Sólo WPA (mejorada)";
$m_wpa2_security	= "Activar seguridad inalámbrica Sólo WPA2 (mejorada)";
$m_wpa2_auto_security	= "Activar seguridad inalámbrica WPA/WPA2 (mejorada)";

$m_title_wep		= "WEP";
$m_auth_type		= "Autenticación";
$m_open			= "Abrir";
$m_shared_key		= "Clave compartida";
$m_wep_key_len		= "Cifrado WEP";
$m_64bit_wep		= "64Bit";
$m_128bit_wep		= "128Bit";
$m_hex			= "HEXADECIMAL";
$m_ascii		= "ASCII";
$m_key_type		= "Tipo de clave";
$m_default_wep_key	= "Clave WEP predeterminada";
$m_wep_key		= "Clave WEP";
$m_wep64_hint_wording	="(5 ASCII o 10 HEXADECIMALES)";
$m_wep128_hint_wording	="(13 ASCII o 26 HEXADECIMALES)";

$m_title_wpa		="Sólo WPA";
$m_dsc_wpa		="Sólo WPA requiere que las estaciones utilicen cifrado y autenticación de grado alto.";
$m_title_wpa2		="Sólo WPA2";
$m_dsc_wpa2		="Sólo WPA2 requiere que las estaciones utilicen cifrado y autenticación de grado alto.";
$m_title_wpa2_auto	="WPA/WPA2";
$m_dsc_wpa2_auto	="WPA/WPA2 requiere que las estaciones utilicen cifrado y autenticación de grado alto.";

$m_cipher_type		="Tipo de cifrado";
$m_tkip			="TKIP";
$m_aes			="AES";
$m_psk_eap		="PSK / EAP";
$m_psk			="PSK";
$m_eap			="EAP";
$m_passphrase		="Clave de red";
$m_confirm_passphrase	="Clave de red confirmada";
$m_psk_hint_wording		="(8~63 ASCII o 64 HEXADECIMALES)";

$m_8021x		="802.1X";
$m_radius1		="Servidor RADIUS 1";
$m_shared_sec		="Secreto compartido";
?>
