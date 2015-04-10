<?
$m_title_ap_mode	= "AP(Access Point)모드";
$m_desc_ap_mode		= "이 기능을 사용하면 AP모드(무선허브 모드)로 동작을 하며, 사용을 하지 않으면 공유기로 동작합니다.";
$m_enable_ap_mode	= "AP(Access Point)모드 사용";

$m_title_wan_type	= "인터넷 연결 방식";
$m_desc_wan_type	= "인터넷에 연결되어 있는 공유기에서 사용되는 모드를 선택하십시오.";

$m_wan_type	= "내 인터넷 연결 방식";
$m_static_ip	= "고정 IP";
$m_dhcp		= "유동IP (DHCP)";
$m_pppoe	= "PPPoE (Username / Password)";
$m_pptp		= "PPTP (Username / Password)";
$m_l2tp		= "L2TP (Username / Password)";
$m_russia_pptp		= "Russia PPTP (Dual Access)";
$m_russia_pppoe		= "Russia PPPoE (Dual Access)";
$m_mppe		="MPPE";
$m_wwan 	="3G USB Adapter";

$m_title_static	= "고정 IP 주소 인터넷 방식";
$m_desc_static	= "인터넷 제공업체(ISP) 로부터 할당받은 IP 주소 정보를 입력하십시오.";

$m_comment_isp	= "(ISP에서의 할당)";
$m_subnet	= "서브넷 마스크";
$m_isp_gateway	= "ISP 기본 게이트웨이";
$m_macaddr	= "MAC 주소";
$m_optional	= "(옵션)";
$m_clone_mac	= "MAC 주소 복사";
$m_primary_dns	= "1차 DNS 주소";
$m_secondary_dns= "2차 DNS 주소";
$m_mtu		= "MTU";

$m_title_dhcp	= "동적IP(DHCP) 인터넷 연결 종류";
$m_desc_dhcp	= "인터넷 서비스 제공업체(ISP) 에서 IP 주소 정보 또는".
								"사용자명과 비밀번호를 받지 못한 경우, 이 인터넷 연결 유형을 사용하십시오.";

$m_host_name		= "호스트 이름";
$m_ppp_idle_time	= "최대 유지 시간";
$m_ppp_connect_mode	= "연결 상태 선택";
$m_always_on		= "항상 연결";
$m_manual		= "수동으로 연결";
$m_on_demand		= "접속 요청시에만 연결";

$__info_from_isp	= "인터넷 서비스 업체에서(ISP) 제공된 정보를 입력 하십시오.";

$m_title_pppoe	= "PPPoE";
$m_title_russia_pppoe	= "Russia PPPoE (DUAL Access)";
$m_desc_pppoe	= $__info_from_isp;
$m_title_physical	= "WAN 설정";

$m_dynamic_pppoe	= "동적 PPPoE";
$m_static_pppoe		= "고정 PPPoE";
$m_retype_pwd		= "암호 재입력";
$m_pppoe_svc_name	= "서비스 이름";
$m_minutes		= "분";
$m_auto_dns		= "자동 DNS 주소";
$m_manual_dns	= "수동 DNS 설정";

$m_title_pptp	= "PPTP";
$m_title_russia_pptp	= "Russia PPTP (DUAL Access)";
$m_desc_pptp	= $__info_from_isp;

$m_title_l2tp	= "L2TP";
$m_desc_l2tp	= $__info_from_isp;

$m_dynamic_ip		= "동적 IP";
$m_static_ip		= "고정 IP";
$m_gateway		= "게이트웨이";
$m_dns			= "DNS";
$m_server_ip		= "서버IP/이름";
$m_pptp_account		= "PPTP ID";
$m_pptp_password	= "PPTP 암호";
$m_pptp_retype_pwd	= "PPTP 암호 재입력";
$m_l2tp_account		= "L2TP ID";
$m_l2tp_password	= "L2TP 암호";
$m_l2tp_retype_pwd	= "L2TP 암호 재입력";

$m_title_wwan			= "WWAN 인터넷 연결 타입 :";
$m_desc_wwan			= "인터넷 서비스 업체에서(ISP) 제공된 정보를 입력 하십시오.";
$m_card_device			= "Card";
$m_driver				= "Driver";
$m_manufacturer			= "Manufacturer";
$m_product 				= "Product";
$m_pin_code				= "PIN 번호";
$m_username				= "사용자 ID";
$m_password				= "암호";
$m_dial_num				= "Dial Number";
$m_auth_proto			= "암호화 프로토콜";
$m_wwan_auth_auto 		= "자동 (PAP + CHAP)";
$m_wwan_pap				= "PAP only";
$m_wwan_chap			= "CHAP only";
$m_auto_reconn 			= "자동 재 접속";
$m_apn					= "APN";
$m_enable 				= "사용";
$m_disable				= "사용암함";
$m_keep_alive_int 		= "대기시간";
$m_seconds 				= "(초)";
$m_keep_alive_server1 	= "대기 서버1";
$m_keep_alive_server2 	= "대기 서버2";
$m_wwan_reconn_mode		= "재접속 모드";
$m_wwan_minutes			= "(분,0=무한대)";
$m_wwan_bytes			= "(bytes)";
$m_country				= "Country";
$m_isp					= "ISP";
$m_choice_country		= "지역 선택";
$m_choice_isp			= "ISP 선택";

$m_auth_server	= "인증서버";
$m_login_server = "로그인 서버 IP/이름";

/*----------802.1x------------*/

$m_8021x_setting	   	= "802.1x";
$m_8021x_setting_description = "인터넷 서비스 업체에서(ISP) 제공된 정보를 입력 하십시오.";

$m_8021x_eap_type		= "EAP Type";
$m_8021x_md5			= "MD5";
$m_8021x_peap			= "PEAP";
$m_8021x_ttls			= "TTLS";

$m_8021x_authentication	= "인증";
$m_8021x_pap			= "PAP";
$m_8021x_chap			= "CHAP";
$m_8021x_mschap			= "MSCHAP";
$m_8021x_mschapv2		= "MSCHAP Version 2";

$m_8021x_identity		= "사용자 이름(ID)";
$m_8021x_pass		= "암호";
$m_8021x_pass2		= "암호 재입력";

/*------------------------------*/


$a_invalid_ip		= "잘못된 IP 주소 입니다!";
$a_invalid_netmask	= "잘못된 서브넷 마스크 입니다!";
$a_invalid_mac		= "잘못된 MAC 주소 입니다!";
$a_invalid_mtu		= "잘못된 MTP 값 입니다!";
$a_invalid_hostname	= "잘못된 호스트 이름 입니다!";
$a_invalid_username	= "잘못된 사용자이름(ID) 입니다!";
$a_password_mismatch	= "암호값이 틀림니다. 새로 입력해 주세요!";
$a_invalid_idletime	= "잘못된 대기 시간 입니다!";

$a_srv_in_different_subnet	= "잘못된 서버IP 주소 입니다! 같은 네트워크 안에 서버 또는 공유기의 주소가 포함되어 있어야 합니다.";
$a_gw_in_different_subnet	= "잘못된 게이트웨이 주소 입니다! 같은 네트워크 안에 서버 또는 공유기의 주소가 포함되어 있어야 합니다.";
$a_server_empty		= "서버IP주소/이름 비어 있습니다!";
$a_account_empty	= "ID가 비어 있습니다!";

$a_card_device_not_selected = "카드를 선택하지 않았습니다!";
$a_dial_num_empty 			= "Dial 번호가 비어 있습니다!";
$a_auth_proto_not_selected 	= "인증 프로토콜이 선택되지 않았습니다!";
$a_apn_empty 				= "APN이 비어 있습니다!";
$a_keep_alive_int_empty 	= "대기 시간이 비어있거나 자동 재접속으로 선택 되어있지 않습니다!";
$a_invalid_keep_alive_int 	= "대기 시간이 20 ~ 3600 사이에 설정 되어 있지 않습니다!";

/*---------------802.1x alert message---------------*/
$a_empty_username		= "사용자 이름(ID)이 비어 있습니다!";
$a_empty_password		= "암호가 비어 있습니다!";
$a_empty_password_v		= "암호 재입력 란이 비어 있습니다!";
$a_diff_password		= "2개의 암호가 서로 틀립니다!";
$a_empty_field			= "field가 비어 있습니다!";
/*--------------------------------------------------*/

?>

