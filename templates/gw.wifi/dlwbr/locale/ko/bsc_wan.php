<?
$m_title_ap_mode	= "액세스 포인트 모드";
$m_desc_ap_mode		= "공유기의 NAT 기능을 중지시키고 액세스 포인트 모드로 동작 시킵니다.";
$m_enable_ap_mode	= "액세스 포인트 모드 설정";

$m_title_wan_type	= "인터넷 연결 종류";
$m_desc_wan_type	= "인터넷에 연결하기 위한 공유기 모드를 선택하십시오.";

$m_wan_type	= "내 인터넷 연결";
$m_static_ip	= "고정 IP";
$m_dhcp		= "유동 IP(DHCP)";
$m_pppoe	= "PPPoE(사용자명/비밀번호)";
$m_pptp		= "PPTP(사용자명/비밀번호)";
$m_l2tp		= "L2TP(사용자명/비밀번호)";
$m_russia_pptp		= "러시아 PPTP(듀얼 접속)";
$m_russia_pppoe		= "러시아 PPPoE(듀얼 접속)";

$m_title_static	= "고정 IP 주소 인터넷 연결 종류";
$m_desc_static	= "인터넷 서비스 공급 업체(ISP)에서 제공 받은 고정 IP 주소 정보를 입력하십시오. ";

$m_comment_isp	= "(ISP에서 제공)";
$m_subnet	= "서브넷 마스크";
$m_isp_gateway	= "ISP 게이트웨이 주소";
$m_macaddr	= "MAC 주소";
$m_optional	= "(선택)";
$m_clone_mac	= "MAC 주소 복사";
$m_primary_dns	= "1차 DNS 주소";
$m_secondary_dns= "2차 DNS 주소";
$m_mtu		= "MTU";

$m_title_dhcp	= "유동 IP(DHCP) 주소 인터넷 연결 종류";
$m_desc_dhcp	= "인터넷 서비스 공급업체(ISP)에서 IP 주소 정보나 사용자 명 또는 비밀번호를 받지 못한 경우에는 이 인터넷 연결을 사용하십시오.";

$m_host_name		= "호스트 명";
$m_ppp_idle_time	= "최대 휴지 시간";
$m_ppp_connect_mode	= "연결 모드 선택 ";
$m_always_on		= "항상 연결";
$m_manual		= "수동";
$m_on_demand		= "필요시 연결";

$__info_from_isp	= "인터넷 서비스 공급 업체(ISP)에서 제공한 정보를 입력하십시오. ";

$m_title_pppoe	= "PPPoE";
$m_title_russia_pppoe	= "러시아 PPPoE(듀얼 접속)";
$m_desc_pppoe	= $__info_from_isp;
$m_title_physical	= "WAN Physical 설정";

$m_dynamic_pppoe	= "동적 PPPoE";
$m_static_pppoe		= "정적 PPPoE";
$m_retype_pwd		= "비밀번호 확인";
$m_pppoe_svc_name	= "서비스 명";
$m_minutes		= "분";

$m_title_pptp	= "PPTP";
$m_title_russia_pptp	= "러시아 PPTP(듀얼 접속)";
$m_desc_pptp	= $__info_from_isp;

$m_title_l2tp	= "L2TP ";
$m_desc_l2tp	= $__info_from_isp;

$m_dynamic_ip		= "동적 IP";
$m_static_ip		= "고정 IP";
$m_gateway		= "게이트웨이";
$m_dns			= "DNS";
$m_server_ip		= "서버 IP/명";
$m_pptp_account		= "PPTP 계정";
$m_pptp_password	= "PPTP 비밀번호";
$m_pptp_retype_pwd	= "PPTP 비밀번호 확인";
$m_l2tp_account		= "L2TP 계정";
$m_l2tp_password	= "L2TP 비밀번호";
$m_l2tp_retype_pwd	= "L2TP 비밀번호 확인";


$m_auth_server	= "인증 서버";
$m_login_server = "로긴 서버 IP/명";

$a_invalid_ip		= "유효하지 않은 IP 주소!";
$a_invalid_netmask	= "유효하지 않은 서브넷 마스크!";
$a_invalid_mac		= "유효하지 않은 MAC 주소!";
$a_invalid_mtu		= "유효하지 않은 MTU 값!";
$a_invalid_hostname	= "유효하지 않은 호스트 명!";
$a_invalid_username	= "유효하지 않은 사용자!";
$a_password_mismatch	= "확인 비밀번호와 새 비밀번호가 맞지 않습니다!";
$a_invalid_idletime	= "유효하지 않은 휴지 시간!";

$a_srv_in_different_subnet	= "서버 IP 주소가 맞지 않습니다! 서버 주소와 공유기 주소는 같은 네트워크에 있어야 합니다. ";
$a_gw_in_different_subnet	= "게이트웨이 주소가 잘못되었습니다! 게이트웨이 주소와 공유기 주소는 같은 네트워크에 있어야 합니다. ";
$a_server_empty		= "서버 IP/명이 공백이어서는 안됩니다!";
$a_account_empty	= "계정이 공백이어서는 안됩니다!";

$m_mppe = "MPPE";
$m_auto_dns = "DNS를 ISP에서 받으세요";
$m_manual_dns = "수동으로 DNS 입력하세요";
$m_8021x_setting = "802.1x";
$m_8021x_setting_description = "인터넷 서비스 프로바이더(ISP)의 정보를 입력하세요";
$m_8021x_eap_type = "EAP Type";
$m_8021x_md5 = "MD5";
$m_8021x_peap = "PEAP";
$m_8021x_ttls = "TTLS";
$m_8021x_authentication = "인증";
$m_8021x_pap = "PAP";
$m_8021x_chap = "CHAP";
$m_8021x_mschap = "MSCHAP";
$m_8021x_mschapv2 = "MACHAP 버전 2";
$m_8021x_identity = "사용자 이름";
$m_8021x_pass = "패스워드";
$m_8021x_pass2 = "패스워드 재확인";
$a_empty_username = "사용자 이름을 입력해야 합니다.";
$a_empty_password = "패스워드를 입력해야 합니다.";
$a_empty_password_v = "패스워드 재확인을 해야 합니다.";
$a_diff_password = "두개의 패스워드가 다릅니다.";
$a_empty_field = "필드에 입력해야 합니다.";

?>
