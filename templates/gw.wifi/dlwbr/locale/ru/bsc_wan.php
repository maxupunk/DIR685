<?
$m_title_ap_mode	= "Режим точки доступа (AP mode)";
$m_desc_ap_mode		= "Позволяет выключить NAT на маршрутизаторе и использовать это устройство в качестве точки доступа.";
$m_enable_ap_mode	= "Включить режим точки доступа (AP mode)";

$m_title_wan_type	= "Тип Интернет-соединения";
$m_desc_wan_type	= "Выберите используемый маршрутизатором режим для подключения к Интернет.";

$m_wan_type	= "Используется Интернет-соединение";
$m_static_ip	= "Статический IP-адрес";
$m_dhcp		= "Динамический IP-адрес (DHCP)";
$m_pppoe	= "PPPoE (Имя пользователя / Пароль)";
$m_pptp		= "PPTP (Имя пользователя / Пароль)";
$m_l2tp		= "L2TP (Имя пользователя / Пароль)";
$m_russia_pptp		= "PPTP (Dual Access)";
$m_russia_pppoe		= "PPPoE (Dual Access)";
$m_mppe		="MPPE";

$m_title_static	= "Тип Интернет-соединения - статический IP-адрес";
$m_desc_static	= "Введите статический IP-адрес, полученный от провайдера.";

$m_comment_isp	= "(назначается провайдером)";
$m_subnet	= "Маска подсети";
$m_isp_gateway	= "Адрес шлюза провайдера";
$m_macaddr	= "MAC-адрес";
$m_optional	= "(дополнительно)";
$m_clone_mac	= "Клонирование MAC-адреса";
$m_primary_dns	= "Первичный DNS-адрес";
$m_secondary_dns= "Вторичный DNS-адрес";
$m_mtu		= "MTU";

$m_title_dhcp	= "Тип Интернет-соединения - динамический IP-адрес (DHCP)";
$m_desc_dhcp	= "Выберите этот тип Интернет-соединения в случае, если провайдер  ".
		"не предоставил информацию об IP-адресе и/или имени пользователя и пароля.";

$m_host_name		= "Имя Хоста";
$m_ppp_idle_time	= "Максимальное время ожидания (idle time)";
$m_ppp_connect_mode	= "Выберите режим подключения";
$m_always_on		= "Режим \"Always-on\"";
$m_manual		= "Вручную";
$m_on_demand		= "Подключение по требованию";

$__info_from_isp	= "Введите информацию, полученную от провайдера.";
//$m_wwan                 = "USB-адаптер 3G";
//$m_dial_num             = "Номер набора";
//$__info_from_isp        = "Введите информацию, предоставленную провайдером.";
//$m_desc_wwan            = "Введите информацию, предоставленную провайдером.";
//$m_auth_proto                       = "Протокол аутентификации";
//$m_wwan_pap                         = "Только PAP";
//$m_wwan_chap                        = "Только CHAP";
//$m_country                                = "Страна";



$m_title_pppoe	= "PPPoE";
$m_title_russia_pppoe	= "PPPOE (DUAL Access)";
$m_desc_pppoe	= $__info_from_isp;
$m_title_physical	= "Физические настройки WAN";

$m_dynamic_pppoe	= "Динамический PPPoE";
$m_static_pppoe		= "Статический PPPoE";
$m_retype_pwd		= "Повторный ввод пароля";
$m_pppoe_svc_name	= "Имя Сервиса";
$m_minutes		= "Минут";
$m_auto_dns		= "Получение DNS от провайдера";
$m_manual_dns	= "Задание DNS вручную";

$m_title_pptp	= "PPTP";
$m_title_russia_pptp	= "PPTP (DUAL Access)";
$m_desc_pptp	= $__info_from_isp;

$m_title_l2tp	= "L2TP";
$m_desc_l2tp	= $__info_from_isp;

$m_dynamic_ip		= "Динамический IP-адрес";
$m_static_ip		= "Статический IP-адрес";
$m_gateway		= "Шлюз";
$m_dns			= "DNS";
$m_server_ip		= "IP-адрес/Имя Сервера";
$m_pptp_account		= "Учетная запись PPTP ";
$m_pptp_password	= "Пароль PPTP";
$m_pptp_retype_pwd	= "Повторный ввод пароля PPTP";
$m_l2tp_account		= "Учетная запись L2TP ";
$m_l2tp_password	= "Пароль L2TP";
$m_l2tp_retype_pwd	= "Повторный ввод пароля L2TP";

$m_auth_server	= "Сервер аутентификации";
$m_login_server = "IP-адрес/Имя Сервера";

$a_invalid_ip		= "Некорректный IP-адрес !";
$a_invalid_netmask	= "Некорректная маска подсети !";
$a_invalid_mac		= "Некорректный MAC-адрес !";
$a_invalid_mtu		= "Некорректное значение MTU !";
$a_invalid_hostname	= "Некорректное Имя хоста !";
$a_invalid_username	= "Некорректное Имя пользователя !";
$a_password_mismatch	= "Пароли, указанные в полях для ввода пароля и повторного ввода для подтверждения, не совпадают !";
$a_invalid_idletime	= "Некорректное время ожидания (idle time) !";

$a_srv_in_different_subnet	= "Некорректный IP-адрес сервера ! IP-адреса сервера  и маршрутизатора должны принадлежать одной сети.";
$a_gw_in_different_subnet	= "Некорректный IP-адрес шлюза ! IP-адреса шлюза  и маршрутизатора должны принадлежать одной сети.";
$a_server_empty		= "Поле IP-адрес/Имя Сервера не может быть пустым !";
$a_account_empty	= "Поле Учетная запись не может быть пустым !";

$m_8021x_setting_description	= "Введите информацию, выданную провайдером";
//$m_8021x_setting_description = "Введите информацию, предоставленную провайдером.";
$m_8021x_eap_type	= "тип EAP";
$m_8021x_authentication	= "Аутентификация";
$m_8021x_identity	= "Имя пользователя";
$m_8021x_pass		= "Пароль";
$m_8021x_pass2		= "Подтвердите пароль";
$a_empty_username	= "Имя пользователя не может быть пустым!";
$a_empty_password = "Пароль не может быть пустым!";
$a_empty_password_v	= "Подтверждение пароля не может быть пустым";
$a_diff_password		= "Пароль и подтверждение не совпадают";
$a_empty_field		= "Поле не может быть пустым";

?>
