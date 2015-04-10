<?
$m_gz_title_select			= "Guest Zone 설정";
$m_gz_title_router			= "Guest Zone을 공유기에서 설정 할 수 있습니다.";
$m_gz_title_isolate			= "Guest Zone을 분리 할 수 있습니다";
$m_gz_title_to_host_routing	= "Host Zone(메인 네트워크) 와 Guest Zone(손님 네트워크) 사이 네트워크로 만들 수 있습니다.";
$m_gz_title_dhcp_server		= "Guest Zone DHCP서버 설정";
$m_gz_title_dhcp_client		= "Guest Zone DHCP 클라이언트 할당 목록";
$m_gz_title_lock_client		= "Guest Zone 고정 클라이언트 목록";

$m_gz_desc_router	=	"Use this section to configure the guest zone settings of your router. ";

$m_gz_desc_isolate	=	"Enable the function to prevent guest clients accessing other guest clients in the Guest Zone. ";

$m_gz_desc_to_host_routing	=	"Use this section to enable routing between the Host Zone and Guest Zone, ";

$m_gz_desc_dhcp_server	=	"Use this section to configure the built-in DHCP server to assign IP addresses ";

$m_gz_desc_lock_client	=	"The function is used to lock all PC clients which are in the Guest Zone ";

$m_enable_gzone			= "Guest Zone 사용";
$m_include_lan_port		= "LAN Port 분리";
$m_include_wireless		= "무선 분리";
$m_wireless_name		= "무선 네트워크 이름";
$m_ssid_comment			= "(SSID)";
$m_security_mode		= "보안 모드";
$m_router_ip			= "공유기 IP 주소";
$m_router_netmask		= "서브넷 마스크";
$m_enable_gzone_iso		= "Guest Zone 클라이언트 분리 사용";
$m_enable_gzone_route	= "네트워크 공유 Zone 사용";
$m_enable_dhcp_server	= "DHCP 서버 사용";
$m_dhcp_ip_range		= "DHCP IP 주소 범위";
$m_to					= "부터";
$m_dhcp_ip_range_comment	= "(LAN 서브넷 대역에 주소가 포함되어야 합니다.)";
$m_dhcp_lease_time		= "DHCP 임대 시간";
$m_dhcp_lease_time_comment	= "(분)";
$m_lock_client			= "고정 클라이언트 목록 사용";

$m_host_name		= "Host 이름";
$m_expired_time		= "만료 시간";

$m_encr_none	= "무선 보안 사용안함(권장하지 않음)";
$m_encr_wep		= "WEP 무선 보안 사용(기본)";
$m_encr_wpa		= "WPA 단독 무선 보안 사용(고급)";
$m_encr_wpa2	= "WPA2 단독 무선 보안 사용(고급)";
$m_encr_wpaauto	= "WPA/WPA2 무선 보안 사용(고급)";

$m_title_wep	= "WEP";
$m_auth_type	= "인증";
$m_open			= "공개(Open)";
$m_shared_key	= "Shared Key";
$m_wep_key_len	= "WEP 암호화";
$m_64bit_wep	= "64Bit";
$m_128bit_wep	= "128Bit";
$m_hex			= "HEX";
$m_ascii		= "ASCII";
$m_key_type		= "Key Type";
$m_def_wep_key	= "기본 WEP Key";
$m_wep_key		= "WEP Key";
$m_hint_wep64	="(5 ASCII or 10 HEX)";
$m_hint_wep128	="(13 ASCII or 26 HEX)";

$m_title_wpa	="WPA 단독";
$m_dsc_wpa		="WPA 단독 모드는 높은 암호화 값을 요구 합니다.";
$m_title_wpa2	="WPA2 단독";
$m_dsc_wpa2		="WPA2 단독 모드는 높은 암호화 값을 요구 합니다.";
$m_title_wpa_2	="WPA/WPA2";
$m_dsc_wpa_2	="WPA/WPA2 단독 모드는 높은 암호화 값을 요구 합니다.";

$m_cipher_type	="암호화 종류";
$m_tkip			="TKIP";
$m_aes			="AES";
$m_psk			="PSK";
$m_eap			="EAP";
$m_passphrase	="네트워크 Key";
$m_confirm_passphrase   ="네트워크 키 재입력";
$m_psk_hint		="(8~63 ASCII or 64 HEX)";

$m_8021x		="802.1X";
$m_radius_srvr	="RADIUS 서버";
$m_shared_sec	="보안키";

$m_days	= "일";
$m_hrs	= "시간";
$m_mins	= "분";
$m_secs	= "초";

$a_invalid_ip			= "잘못된 IP 주소 입니다!";
$a_invalid_netmask		= "잘못된 서브넷 마스크 입니다!";
$a_network_conflict		= "Guest zone 네트워크가 Host Zone 네트워크 대역과 같습니다!";
$a_invalid_ip_range		= "DHCP서버에서 지원하지 않은 잘못된 IP 주소 범위 입니다!";
$a_invalid_lease_time	= "잘못된 DHCP 임대시간 입니다!";

$a_empty_ssid	= "SSID 는 공란으로 설정 할 수 없습니다.";
$a_invalid_ssid	= "SSID의 문자가 잘못되어 있습니다. 확인하시기 바랍니다.";
$a_invalid_wep_128_wep_key		= "키 입력이 잘못 되었습니다. 13자리 또는 26자리의 16진수 값으로 넣어주시기 바랍니다.";
$a_invalid_wep_64_wep_key		= "키 입력이 잘못 되었습니다. 5자리 또는 10자리의 16진수 값으로 넣어주시기 바랍니다.";
$a_invalid_wep_128_ascii_wep_key= "키 입력이 잘못 되었습니다. 13자리의 문자 또는 숫자로 넣어주시기 바랍니다.";
$a_invalid_wep_128_hex_wep_key	= "키 입력이 잘못 되었습니다. 26자리의 16진수 값으로 넣어주시기 바랍니다.";
$a_invalid_wep_64_ascii_wep_key	= "키 입력이 잘못 되었습니다. 5자리의 문자 또는 숫자로 넣어주시기 바랍니다.";
$a_invalid_wep_64_hex_wep_key	= "키 입력이 잘못 되었습니다. 10자리의 16진수 값으로 넣어주시기 바랍니다.";
$a_invalid_passphrase_len		= "8~63 자리내로 공유키를 입력해 주시기 바랍니다.";
$a_invalid_passphrase			= "RADIUS 서버의 보안키를 상용문자로 입력해 주시기 바랍니다.";
$a_invalid_psk					= "잘못된 Hex의 PSK 값입니다.";
$a_invalid_radius_ip			= "잘못된 RADIUS 서버 주소 입니다.";
$a_invalid_radius_port			= "잘못된 port 번호 입니다.";
$a_invalid_radius_sec			= "잘못된 보안키 입니다.";


?>

