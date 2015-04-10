<?
/* ---------------------------------- */
//$TITLE=$m_pre_title."SETUP";
/* ---------------------------------- */
$a_empty_ssid		= "Поле SSID не может быть пустым.";
$a_invalid_ssid		= "В поле SSID есть некорректные символы. Проверьте его.";

$a_invalid_wep_128_wep_key	= "Ключ некорректен. Ключ должен содержать 13 символов или 26 шестнадцатеричных чисел";
$a_invalid_wep_64_wep_key	= "Ключ некорректен. Ключ должен содержать 5 символов или 10 шестнадцатеричных чисел.";
$a_invalid_wep_128_ascii_wep_key= "Ключ некорректен. Ключ должен содержать 13 символов.";
$a_invalid_wep_128_hex_wep_key	= "Ключ некорректен.  Ключ должен содержать 26 шестнадцатеричных чисел";
$a_invalid_wep_64_ascii_wep_key	= "НКлюч некорректен. Ключ должен содержать 5 символов.";
$a_invalid_wep_64_hex_wep_key	= "Ключ некорректен. Ключ должен содержать 10 шестнадцатеричных символов.";

$a_empty_defkey			= "WEP-ключ по умолчанию не может быть пустым.";
$a_valid_hex_char		= "Допустимые символы 0~9, A~F or a~f.";
$a_valid_asc_char		= "Допустимы только символы ASCII.";

$a_invalid_radius_ip1		= "Некорректный IP-адрес RADIUS-сервера.";
$a_invalid_radius_port1		= "Некорректный порт RADIUS-сервера.";
$a_empty_radius_sec1		= "Shared Secret для RADIUS-сервера не может быть пустым.";
$a_invalid_radius_sec1		= "Shared Secret RADIUS-сервера должен быть задан в формате ASCII.";
$a_invalid_passphrase_len	= "Допустимая длина парольной фразы 8~63.";
$a_invalid_psk_len		= "Длина PSK должна быть 64.";
$a_psk_not_match		= "Подтверждение парольной фразы не совпадает с парольной фразой.";
$a_invalid_passphrase	= "Парольная фраза должна состоять из символов ASCII.";
$a_invalid_psk			= "PSK должен быть в шестнадцатеричной форме";

$a_reset_wps_pin		= "Действительно необходимо сбросить PIN к значению по умолчанию?";
$a_gen_new_wps_pin		= "Действительно необходимо сгенерировать новый PIN?";
$a_reset_wps_unconfig	= "Действительно необходимо сбросить настройки устройства к исходным?";
$a_enable_wps_first		= "WPS не включен. Нажмите \\\Сохранить настройки\\\", чтобы включить WPS.";

$m_title_wireless_setting	= "Настройки беспроводной сети";

$m_enable_wireless	= "Включить Беспроводной доступ";
$m_wlan_name		= "Имя беспроводной сети";
$m_wlan_name_comment	= "(Также называется SSID)";
$m_wlan_channel		= "Беспроводной канал";
$m_enable_auto_channel	= "Включить Автовыбор канала";
$m_super_g		= "Режим Super G";
$m_super_g_without_turbo= "Super G без Turbo";
$m_super_g_with_d_turbo = "Super G с Dynamic Turbo";
$m_xr			= "Включить режим расширенного радиуса действия сети";
$m_11g_only		= "Режим только 802.11g";
$m_txrate		= "Скорость передачи";
$m_mcrate		= "Скорость Многоадресной рассылки";
$m_best_auto	= "Лучший (автоматически)";
$m_mbps			= "(Мбит/с)";
$m_wmm_enable	= "Включение WMM";
$m_wlan_qos		= "(Беспроводное QoS)";
$m_enable_ap_hidden	= "Включить Hidden Wireless";
$m_ap_hidden_comment	= "(Также называется SSID Broadcast)";

$m_title_wireless_security	= "Режм беспроводной безопасности";

$m_security_mode	= "Режим безопасности";
$m_disable_security	= "Отключить беспроводную безопасность (не рекомендуется)";
$m_enable_wep		= "Включить Беспроводную безопасность WEP (основная)";
$m_wpa_security		= "Включить Беспроводную безопасность Только WPA (расширенная)";
$m_wpa2_security	= "Включить Беспроводную безопасность WPA2 (расширенная)";
$m_wpa2_auto_security	= "Включить Беспроводную безопасность WPA/WPA2 (расширенная)";

$m_title_wep		= "WEP";
$m_auth_type		= "Аутентификация";
$m_open			= "Открыть";
$m_shared_key		= "Shared Key";
$m_wep_key_len		= "WEP-шифрование";
$m_64bit_wep		= "64 Бит";
$m_128bit_wep		= "128 Бит";
$m_hex			= "HEX";
$m_ascii		= "ASCII";
$m_key_type		= "Тип ключа";
$m_default_wep_key	= "WEP-ключ по умолчанию";
$m_wep_key		= "WEP-ключ";
$m_wep64_hint_wording	="(5 ASCII или 10 HEX)";
$m_wep128_hint_wording	="(13 ASCII или 26 HEX)";

$m_title_wpa		="Только WPA";
$m_dsc_wpa		="Режим Только WPA требует, чтобы станции использовать высококачественное шифрование и аутентификацию.";
$m_title_wpa2		="Только WPA2";
$m_dsc_wpa2		="Режим Только WPA2 требует, чтобы станции использовали высококачественное шифрование и аутентификацию.";
$m_title_wpa2_auto	="WPA/WPA2";
$m_dsc_wpa2_auto	="Режим WPA/WPA2 требует, чтобы станции использовали высококачественное шифрование и аутентификацию.";

$m_cipher_type		="Тип шифра";
$m_tkip			="TKIP";
$m_aes			="AES";
$m_tkipandaes	="AUTO(TKIP/AES)"
$m_psk_eap		="PSK / EAP";
$m_psk			="PSK";
$m_eap			="EAP";
$m_passphrase		="Сетевой ключ";
$m_confirm_passphrase	="Подтверждение сетевого ключа";
$m_psk_hint_wording		="(8~63 ASCII или 64 HEX)";

$m_8021x		="802.1X";
$m_radius1		="RADIUS-сервер";
$m_shared_sec		="Shared Secret";
?>
