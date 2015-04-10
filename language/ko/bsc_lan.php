<?
/* --------------------------------------------------------- */
//$TITLE=$m_pre_title."설정";
/* --------------------------------------------------------- */
$m_title_router_setting	= "공유기 설정";
$m_desc_router_setting	=	"공유기의 내부 네트워크 설정을 할 수 있습니다".
											"IP주소를 설정하고, 변경한 IP 주소로 접속할 수 있습니다".
											"설정하신 IP주소는 Web관리 인터페이스로 접속하는데 사용됩니다. 만약 이 IP주소를 변경 한다면,".
											"네트워크에 다시 접속하기 위해서 PC의 네트워크 설정을 변경하신 네트워크 주소에 맞추어 주시기 바랍니다.";

$m_router_ipaddr	= "공유기 IP주소";
$m_subnet_mask		= "서브넷 마스크";
$m_domain_name		= "로컬 도메인 이름";
$m_enable_dnsr		= "DNS 릴레이 사용";

$m_title_dhcp_svr	= "DHCP Server 설정";
$m_desc_dhcp_svr	=	"내장된 DHCP 서버를 설정하여 네트워크에 연결되어 있는 PC 들에게".
									"IP 주소를 할당할 수 있습니다.";

$m_enable_dhcp		= "DHCP Server 사용";
$m_dhcp_range		= "DHCP IP 주소 범위";
$m_to			= "부터";
$m_range_comment	= "(LAN subnet 범위 이내 주소)";
$m_lease_time		= "DHCP 임대 시간";
$m_netbios	= "NetBIOS 알림";
$m_netbios_learn	=	"WAN NetBIOS 알림";
$m_netbios_scope	=	"NetBIOS 범위";
$m_optional	=	"(옵션)";
$m_netbios_type	=	"NetBIOS node 종류";
$m_broadcast	=	"브로드캐스트 전용(WINS 서버가 설정되지 않은 경우)";
$m_ptop	=	"Point-to-Point (no broadcast)";
$m_mix_mode	=	"혼합 모드 (Broadcast then Point-to-Point)";
$m_hybrid	=	"Hybrid (Point-to-Point then Broadcast)";
$m_primary_wins	=	"1차 WINS IP 주소";
$m_secondary_wins	=	"2차 WINS IP 주소";

$m_minutes		= "(분)";

$m_title_add_client	= "DHCP 보유(Resrtvation)";
$m_computer_name	= "컴퓨터 이름";
$m_clone_mac		= "사용자 PC의 MAC 주소 복사";

$m_title_static_client_list = "DHCP 주소 보유 목록";
$remaining_wording	="남은 주소로 컴퓨터를 설정 할 수 있습니다";

$m_title_client_list	= "동적 DHCP 클라이언트 수";
$m_host_name		= "Host 이름";
$m_ipaddr		= "IP 주소";
$m_macaddr		= "MAC 주소";
$m_expired_time		= "기간 만료";

$m_days	= "일";
$m_hrs	= "시간";
$m_mins	= "분";
$m_secs	= "초";

$a_invalid_ip		= "잘못된 IP 주소 입니다!";
$a_invalid_netmask	= "잘못된 서브넷 마스크 입니다!";
$a_network_conflict	= "Guest zone 네트워크와 host zone 을 분리 해야 합니다!";
$a_lan_wan_conflict = "WAN 네트워크와 LAN 네트워크를 분리 해야 합니다!";
$a_invalid_domain_name	= "잘못된 domain 이름 입니다!";
$a_invalid_ip_range	= "잘못된 DHCP server 주소 대역 입니다!";
$a_invalid_lease_time	= "잘못된 DHCP 임대 시간 입니다!";
$a_del_confirm		= "정말로 삭제 하시길 원하십니까?";
$a_same_static_mac	= "목록에 있는 MAC 주소 입니다.\\MAC 주소를 변경해주세요.";
$a_same_static_ip	= "목록에 있는 IP 주소 입니다.\\IP 주소를 변경해주세요.";
$a_same_static_hostname = "목록에 있는 컴퓨터 이름 입니다.\\컴퓨터 이름을 변경해주세요.";
$a_same_with_lan_ip	= "LAN IP주소와 같은 IP 주소는 사용할 수 없습니다!";
$a_invalid_computer_name= "잘못된 컴퓨터 이름 입니다!";
$a_invalid_mac		= "잘못된 MAC 주소 입니다!";

$a_invalid_form         = "NetBIOS 범위 Scope is not in a valid form !";
$a_invalid_primaywins	= "잘못된 1차 Wins 주소 입니다!";
$a_invalid_secondaywins	= "잘못된 2차 Wins 주소 입니다!";
$a_primary_null		= "1차 WINS IP주소를 정확히 입력 하시고, 2차 WINS IP 주소도 확인해 주시기 바랍니다!";
?>

