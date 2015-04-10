<?
/* ---------------------------------- */
//$TITLE=$m_pre_title."설정";
/* ---------------------------------- */
$a_empty_ssid		= "SSID 란이 공백이어서는 안됩니다.";
$a_invalid_ssid		= "SSID 란에 일부 유효하지 않은 문자가 있습니다. 다시 한번 확인해 주십시오. ";

$a_invalid_wep_128_wep_key	= "Key 가 잘못되었습니다. Key 길이는 13 자리 또는 16진수 26 자리여야 합니다. ";
$a_invalid_wep_64_wep_key	= "Key 가 잘못되었습니다. Key 길이는 5 자리 문자 또는 16진수 10 자리여야 합니다. ";
$a_invalid_wep_128_ascii_wep_key= "Key 가 잘못되었습니다. Key 길이는 13 자리 문자여야 합니다. ";
$a_invalid_wep_128_hex_wep_key	= "Key 가 잘못되었습니다. Key 길이는 16진수 26 자리여야 합니다. ";
$a_invalid_wep_64_ascii_wep_key	= "Key 가 잘못되었습니다. Key 길이는 5 자리 문자여야 합니다. ";
$a_invalid_wep_64_hex_wep_key	= "Key 가 잘못되었습니다. Key 길이는 16진수 10 자리여야 합니다. ";

$a_empty_defkey			= "기본 WEP Key 값이 공백이어서는 안됩니다. ";
$a_valid_hex_char		= "허용되는 문자는 0~9, A~F, a~f 입니다. ";
$a_valid_asc_char		= "허용되는 문자는 ASCII 입니다. ";

$a_invalid_radius_ip1		= "RADIUS 서버 1의 IP 주소가 잘못되었습니다.";
$a_invalid_radius_ip2		= "RADIUS 서버 2의 IP 주소가 잘못되었습니다.";
$a_invalid_radius_port1		= "RADIUS 서버 1의 포트가 잘못되었습니다.";
$a_invalid_radius_port2		= "RADIUS 서버 2의 포트가 잘못되었습니다.";
$a_empty_radius_sec1		= "RADIUS 서버 1의 공유 키(Shared Secret) 란이 공백이어서는 안됩니다. ";
$a_empty_radius_sec2		= "RADIUS 서버 2의 공유 키(Shared Secret) 란이 공백이어서는 안됩니다. ";
$a_invalid_radius_sec1		= "RADIUS 서버 1의 공유 키(Shared Secret) 값은 ASCII 문자여야 합니다. ";
$a_invalid_radius_sec2		= "RADIUS 서버 2의 공유 키(Shared Secret) 값은 ASCII 문자여야 합니다. ";
$a_invalid_passphrase_len	= "비밀번호(Passphrase) 길이는 반드시 8~63 자리입니다. ";
$a_invalid_psk_len		= "PSK 길이는 64 자리입니다. ";
$a_psk_not_match		= "확인한 비밀번호(Passphrase)가 비밀번호(Passphrase)와 일치하지 않습니다. ";
$a_invalid_passphrase	= "비밀번호(Passphrase) 길이는 ASCII 문자여야 합니다. ";
$a_invalid_psk			= "PSK 는 16 진수여야 합니다. ";

$a_reset_wps_pin		= "PIN을 기본 값으로 리셋하시겠습니까?";
$a_gen_new_wps_pin		= "새 PIN을 생성하시겠습니까?";
$a_reset_wps_unconfig	= "공유기를 설정하지 않은 상태로 리셋하시겠습니까?";
$a_enable_wps_first		= "WPS가 아직 설정되지 않았습니다. WPS 설정하기 위해 먼저 \"설정 저장\"을 눌러 주십시오. ";

$m_title_wireless_setting	= "무선 네트워크 설정";

$m_enable_wireless	= "무선 설정 ";
$m_wlan_name		= "무선 네트워크 이름";
$m_wlan_name_comment	= "(SSID)";
$m_wlan_channel		= "무선 채널";
$m_enable_auto_channel	= "채널 자동 선택 설정";
$m_super_g		= "Super G Mode";
$m_super_g_without_turbo= "Super G without Turbo";
$m_super_g_with_d_turbo = "Super G with Dynamic Turbo";
$m_xr			= "확장 모드 설정";
$m_11g_only		= "802.11g 단독 모드";
$m_txrate		= "전송률";
$m_mcrate		= "멀티캐스트 률";
$m_best_auto	= "Best (automatic)";
$m_mbps			= "(Mbit/s)";
$m_wmm_enable	= "WMM 설정";
$m_wlan_qos		= "(무선 QoS)";
$m_enable_ap_hidden	= "무선 숨김 기능 설정";
$m_ap_hidden_comment	= "(SSID 브로캐스트)";

$m_title_wireless_security	= "무선 보안 모드";

$m_security_mode	= "보안 모드";
$m_disable_security	= "무선 보안 기능 중지(권장하지 않음)";
$m_enable_wep		= "WEP 무선 보안 설정(기본)";
$m_wpa_security		= "WPA 단독 무선 보안 설정(고급)";
$m_wpa2_security	= "WPA2 단독 무선 보안 설정(고급)";
$m_wpa2_auto_security	= "WPA/WPA2 무선 보안 설정(고급)";

$m_title_wep		= "WEP";
$m_auth_type		= "인증";
$m_open			= "공개(Open)";
$m_shared_key		= "공유키(Shared Key)";
$m_wep_key_len		= "WEP 암호화";
$m_64bit_wep		= "64Bit";
$m_128bit_wep		= "128Bit";
$m_hex			= "HEX";
$m_ascii		= "ASCII";
$m_key_type		= "Key 종류";
$m_default_wep_key	= "기본 WEP Key";
$m_wep_key		= "WEP Key";
$m_wep64_hint_wording	="(5 ASCII or 10 HEX)";
$m_wep128_hint_wording	="(13 ASCII or 26 HEX)";

$m_title_wpa		="WPA 단독";
$m_dsc_wpa		="WPA 단독 모드는 고급 암호화와 인증을 사용하는 PC에서 필요합니다. ";
$m_title_wpa2		="WPA2 단독";
$m_dsc_wpa2		="WPA2 단독 모드는 고급 암호화와 인증을 사용하는 PC에서 필요합니다. ";
$m_title_wpa2_auto	="WPA/WPA2";
$m_dsc_wpa2_auto	="WPA/WPA2 혼용 모드는 고급 암호화와 인증을 사용하는 PC에서 필요합니다. ";

$m_cipher_type		="암호화 종류";
$m_tkip			="TKIP";
$m_aes			="AES";
$m_psk_eap		="PSK / EAP";
$m_psk			="PSK";
$m_eap			="EAP";
$m_passphrase		="네트워크 Key";
$m_confirm_passphrase	="네트워크 Key 확인";
$m_psk_hint_wording		="(8~63 ASCII or 64 HEX)";

$m_8021x		="802.1X";
$m_radius1		="RADIUS 서버 1";
$m_radius2		="RADIUS 서버 2";
$m_shared_sec		="공유 비밀번호";
?>
