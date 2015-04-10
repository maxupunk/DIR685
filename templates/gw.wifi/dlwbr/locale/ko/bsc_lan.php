<?
/* --------------------------------------------------------- */
//$TITLE=$m_pre_title."설정";
/* --------------------------------------------------------- */
$m_title_router_setting	= "공유기 설정";
$m_desc_router_setting	=
	"이 옵션을 사용하여 공유기의 내부 네트워크를 설정할 수 있습니다. 여기에서 설정한 IP 주소는 웹기반 관리 인터페이스로 접속할 때 사용하는 ".
	"IP 주소입니다. 여기에서 IP 주소를 변경하시면, 네트워크에 다시 접속하기 위해 PC의 네트워크 설정을 변경해야 할 경우도 있습니다.";
$m_router_ipaddr	= "공유기 IP 주소";
$m_subnet_mask		= "기본 서브넷 마스크";
$m_domain_name		= "로컬 도메인 명";
$m_enable_dnsr		= "DNS 릴레이 설정";

$m_title_dhcp_svr	= "DHCP 서버 설정";
$m_desc_dhcp_svr	=
	"PC에 IP 주소를 자동으로 할당하도록 DHCP 서버를 설정하십시오.";
$m_enable_dhcp		= "DHCP 서버 설정";
$m_dhcp_range		= "DHCP IP 주소 범위";
$m_to			= "to";
$m_range_comment	= "(LAN 서브넷 내부 주소)";
$m_lease_time		= "DHCP 주소 임대 시간";
$m_minutes		= "(분)";

$m_title_add_client	= "DHCP 주소 예약  ";
$m_computer_name	= "컴퓨터 명";
$m_clone_mac		= "PC MAC 주소 복사";

$m_title_static_client_list = "DHCP 주소 예약 목록";
$remaining_wording	="설정 가능한 클라이언트 수 ";

$m_title_client_list	= "DHCP 클라이언트 목록";
$m_host_name		= "호스트 명";
$m_ipaddr		= "IP 주소";
$m_macaddr		= "MAC 주소";
$m_expired_time		= "시간 만료";

$m_days	= "일";
$m_hrs	= "시간";
$m_mins	= "분";
$m_secs	= "초";

$a_invalid_ip		= "유효하지 않은 IP 주소!";
$a_invalid_netmask	= "유효하지 않은 서브넷 마스크!";
$a_network_conflict	= "게스트(guest) 네트워크와 호스트(host) 네트워크가 같아서는 안됩니다!";
$a_invalid_domain_name	= "유효하지 않은 도메인 명!";
$a_invalid_ip_range	= "유효하지 않은 DHCP 서버의 IP 주소 범위!";
$a_invalid_lease_time	= "유효하지 않은 DHCP 임대 시간!";
$a_del_confirm		= "이 엔트리를 정말로 삭제하시겠습니까?";
$a_same_static_mac	= "기존 MAC 주소와 동일합니다.\\n MAC 주소를 변경하십시오. ";
$a_same_static_ip	= "기존 IP 주소와 동일합니다.\\n IP 주소를 변경하십시오. ";
$a_same_static_hostname = "기존 컴퓨터 명과 동일합니다.\\n 컴퓨터 명을 변경하십시오. ";
$a_same_with_lan_ip	= "IP 주소와 LAN IP 주소와 같아서는 안됩니다! ";
$a_invalid_computer_name= "유효하지 않은 컴퓨커 명!";
$a_invalid_mac		= "유효하지 않은 MAC 주소!";
?>
