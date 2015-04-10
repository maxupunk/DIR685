<?
/* ---------------------------------- */
//$TITLE=$m_pre_title."설정";
/* ---------------------------------- */
$a_empty_ssid		= "SSID는 공란으로 설정 할 수 없습니다.";
$a_invalid_ssid		= "SSID의 문자가 잘못되어 있습니다. 확인하시기 바랍니다.";
$a_invalid_wlan_band = "802.11 band 를 선택하시기 바랍니다.";

$a_invalid_wep_128_wep_key	= "키 입력이 잘못 되었습니다. 13자리 또는 26자리의 16진수 값으로 넣어주시기 바랍니다.";
$a_invalid_wep_64_wep_key	= "키 입력이 잘못 되었습니다. 5자리 또는 10자리의 16진수 값으로 넣어주시기 바랍니다.";
$a_invalid_wep_128_ascii_wep_key= "키 입력이 잘못 되었습니다. 13자리의 문자 또는 숫자로 넣어주시기 바랍니다.";
$a_invalid_wep_128_hex_wep_key	= "키 입력이 잘못 되었습니다. 26자리의 16진수 값으로 넣어주시기 바랍니다.";
$a_invalid_wep_64_ascii_wep_key	= "키 입력이 잘못 되었습니다. 5자리의 문자 또는 숫자로 넣어주시기 바랍니다.";
$a_invalid_wep_64_hex_wep_key	= "키 입력이 잘못 되었습니다. 10자리의 16진수 값으로 넣어주시기 바랍니다.";

$a_empty_defkey			= "기본 WEP 키가 비어 있습니다.";
$a_valid_hex_char		= "0~9, A~F or a~f 사이의 포함이 되는 문자 또는 숫자.";
$a_valid_asc_char		= "상용문자(ASCII).";

$a_invalid_radius_ip1		= "잘못된 RADIUS 서버 IP주소 입니다.";
$a_invalid_radius_port1		= "잘못된 RADIUS 서버 포트번호 입니다.";
$a_empty_radius_sec1		= "RADIUS 서버의 보안키가 비어있습니다.";
$a_invalid_radius_sec1		= "RADIUS 서버의 보안키를 사용문자로 입력해 주시기 바랍니다.";
$a_invalid_passphrase_len	= "8~63 자리내로 공유키를 입력해 주시기 바랍니다.";
$a_invalid_psk_len		= "64 자리 길이의 PSK값을 입력해 주시기 바랍니다.";
$a_psk_not_match		= "공유키 와 공유키 재입력란이 일치하지 않습니다.";
$a_invalid_passphrase	= "공유키란에 상용문자로 입력해주시기 바랍니다.";
$a_invalid_psk			= "잘못된 Hex의 PSK 값입니다.";
$a_unknown_auth= "알수 없는 인증 방식 입니다.";

$a_reset_wps_pin		= "PIN 값을 초기화 하시겠습니까?";
$a_gen_new_wps_pin		= "새로운 PIN값을 생성 하시겠습니까?";
$a_reset_wps_unconfig	= "변경하지 않고, 초기화를 하시겠습니까?";
$a_enable_wps_first		= "WPS 설정 하지 않음.   \\\"설정저장\\\" 버튼을 클릭하여 WPS를 설정 합니다.";

$m_title_wireless_setting	= "무선 네트워크 설정";

$m_enable_wireless	= "무선 사용";
$m_wlan_name		= "무선 네트워크 이름";
$m_wlan_name_comment	= "(SSID)";

$m_wlan_band 	= "802.11 방식";
$m_wlan_band_2g = "2.4GHz";
$m_wlan_band_5g = "5GHz";
$m_11g_only		= "802.11g 전용 모드";
$m_11a_only		= "802.11a 전용 모드";
//for support 11n
$m_wlan_mode_set        ="802.11 모드";
$m_wlan_mode_11b        ="802.11b 전용";
$m_wlan_mode_11g        ="802.11g 전용";
$m_wlan_mode_11n        ="802.11n 전용";
$m_wlan_mode_mix        ="802.11 혼합모드(b/g)";
$m_wlan_mode_mixn       ="802.11 혼합모드(b/g/n)";
//for support 11a
$m_wlan_mode_11a		="802.11a 전용";
$m_wlan_mode_11an 		="802.11a 혼합모드(a/n)";

$m_wlan_band_width      ="채널 간격";
$m_wlan_short_guard     ="Short Guard Interval";
$m_mhz                  ="MHz";

$m_enable_wireless	= "무선 사용";
$m_wlan_name		= "무선 네트워크 이름";
$m_wlan_name_comment	= "(SSID)";
$m_wlan_channel		= "무선 채널";
$m_enable_auto_channel	= "자동 채널 선택 사용";
$m_super_g		= "Super G 모드";
$m_super_g_without_turbo= "Super G without Turbo";
$m_super_g_with_d_turbo = "Super G with Dynamic Turbo";
$m_xr			= "Enable Extended Range Mode";
$m_11g_only		= "802.11g 전용 모드";
$m_txrate		= "전송율";
$m_mcrate		= "멀티케스트 비율";
$m_best_auto	= "Best (자동)";
$m_mbps			= "(Mbit/s)";
$m_wmm_enable	= "WMM 사용";
$m_wlan_qos		= "(무선 QoS)";
$m_enable_ap_hidden	= "무선 숨김 모드 사용";
$m_ap_hidden_comment	= "(\"SSID 브로드캐스트 사용안함\")";

$m_title_wireless_security	= "무선 보안 모드";

$m_security_mode	= "보안 모드";
$m_disable_security	= "무선 보안 사용안함(권장하지 않음)";
$m_enable_wep		= "WEP 무선 보안 사용(기본)";
$m_wpa_security		= "WPA 단독 무선 보안 사용(고급)";
$m_wpa2_security	= "WPA2 단독 무선 보안 사용(고급)";
$m_wpa2_auto_security	= "WPA/WPA2 무선 보안 사용(고급)";

$m_title_wep		= "WEP";
$m_auth_type		= "인증";
$m_open			= "공개(Open)";
$m_shared_key		= "Shared Key";
$m_wep_key_len		= "WEP 암호화";
$m_64bit_wep		= "64Bit";
$m_128bit_wep		= "128Bit";
$m_hex			= "HEX";
$m_ascii		= "ASCII";
$m_key_type		= "Key Type";
$m_default_wep_key	= "기본 WEP Key";
$m_wep_key		= "WEP Key";
$m_wep64_hint_wording	="(5 ASCII or 10 HEX)";
$m_wep128_hint_wording	="(13 ASCII or 26 HEX)";

$m_title_wpa		="WPA 단독";
$m_dsc_wpa		="WPA 단독 모드는 높은 암호화 값을 요구 합니다.";
$m_title_wpa2		="WPA2 단독";
$m_dsc_wpa2		="WPA2 단독 모드는 높은 암호화 값을 요구 합니다.";
$m_title_wpa2_auto	="WPA/WPA2";
$m_dsc_wpa2_auto	="WPA/WPA2 단독 모드는 높은 암호화 값을 요구 합니다.";

$m_cipher_type		="암호화 종류";
$m_tkip			="TKIP";
$m_aes			="AES";
$m_psk_eap		="PSK / EAP";
$m_psk			="PSK";
$m_eap			="EAP";
$m_passphrase		="네트워크 Key";
$m_confirm_passphrase	="네트워크 키 재입력";
$m_psk_hint_wording		="(8~63 ASCII or 64 HEX)";

$m_8021x		="802.1X";
$m_radius1		="RADIUS 서버";
$m_shared_sec		="보안키";
?>

