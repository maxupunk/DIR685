<?
$m_title_firewall = "방화벽 설정";
$m_enable_spi="SPI 사용";
$m_title_rtsp="어플리케이션 계층 게이트웨이(ALG) 설정";
$m_enable_rtsp="RTSP 사용";
$m_enable_dos="DoS 방지 사용";
$m_title_attack_prevention="내부 공격 방지";
$m_desc_attack_prevention="공격 예방 타입";
$m_enable_arp_attack="ARP 공격";
$m_enable_fake_dhcp="가상 DHCP 서버";
$m_title_firewall_rules = "방화벽 규칙";
$m_action = "동작";
$m_allow = "허용(Allow)";
$m_deny = "허용안함(Deny)";
$m_inf = "인터페이스";
$m_start_ip = "시작 IP 주소";
$m_end_ip	="마지막 IP 주소";
$m_protocol	="프로토콜";
$m_port_range ="Port 범위";
$m_src	="Source";
$m_dst = "목적지";
$m_schedule = "스케줄";
$m_always_on = "항상사용";
$m_add_new_sch = "스케쥴 추가";
$m_title_fw_list="방화벽 규칙 목록";
$m_allow_ping = "WAN 에 대한 PING";
$m_remote_management="원격관리";

$m_title_dmz_rule = "DMZ HOST";
$m_desc_dmz = "DMZ(Demilitarized Zone)기능으로 PC를 공유기의 외부에 ".
							"두는 것처럼 설정할 수 있습니다. 공유기 밑에서".
							"제대로 동작하지 않는 응용프로그램이 있는 경우".
							"인터넷 접속을 제한을 받진 않는 ".
 							"DMZ 구간에 PC를 두십시오. ";

$m_note_dmz =	"<strong>주의:</strong> DMZ를 설정하면 ".
							"여러 가지 보안 위험에 노출 될 수 있습니다. 다른 방법이 없는 경우  ".
							" 마지막 수단으로 이 옵션을 사용하십시오. ";

$m_enable_dmz_host = "DMZ Host 사용";
$m_ip_addr_dmz = "DMZ IP 주소"; 
$m_computer_name = "컴퓨터 이름";

$a_no_ip_selected	= "첫번째 장비를 선택 하시기 바랍니다!";
$a_invalid_ip		= "잘못된 IP 주소 입니다!";
$a_confirm_to_del_fw= "해당 정책을 삭제 하시겠습니까?";
$a_invalid_port="잘못된 포트번호 입니다!";
$a_invalid_port_range="잘못된 포트 범위 입니다!";

$a_invalid_src_startip="잘못된 Source 시작 IP 주소 입니다!";
$a_src_startip_in_different_subnet   = "잘못된 Source 시작 IP 주소 입니다! Source 시작 IP 주소와 공유기의 주소가 같은 서브넷 네트워크 대역에 포함되어 있어야 합니다.";

$a_invalid_src_endip="잘못된 Source 마지막 IP 입니다!";
$a_src_endip_in_different_subnet   = "잘못된 Source 마지막 IP 입니다! Source 마지막 IP 주소와 공유기의 주소가 같은 서브넷 네트워크 대역에 포함되어 있어야 합니다.";

$a_invalid_dst_startip="잘못된 목적지(destination) 시작 IP 주소 입니다!";
$a_dst_startip_in_different_subnet   = "잘못된 목적지(destination) 시작 IP 주소 입니다! 목적지(destination) 시작 IP 주소와 공유기의 주소가 같은 서브넷 네트워크 대역에 포함되어 있어야 합니다.";

$a_invalid_dst_endip="잘못된 목적지(destination) 마지막 IP 주소 입니다!";
$a_dst_endip_in_different_subnet   = "잘못된 목적지(destination) 마지막 IP 주소 입니다! 목적지(destination) 마지막 IP 주소와 공유기의 주소가 같은 서브넷 네트워크 대역에 포함되어 있어야 합니다.";

$a_fw_name_cant_be_empty="방화벽 이름이 비어 있습니다!";
$a_not_support_same_direction="Source 인터페이스 와 목적지(destination) 인터페이스가 같을 수 없습니다!";
$a_invalid_src_ip_range="잘못된 Source IP 주소 범위!";
$a_invalid_dst_ip_range="잘못된 목적지(Destination) IP 주소 범위 입니다!";
$a_confirm_swap_fw="해당 정책을 변경 하시겠습니까?";
$a_dmzip_in_different_subnet = "잘못된 DMZ IP주소 입니다! DMZ IP 주소와 공유기의 주소가 같은 서브넷 네트워크 대역에 포함 되어있어야 합니다.";
$a_same_rule_exist = "이름 '\"+get_obj(\"fw_description_\"+i).value+\"' 가(이) 사용 중 입니다.";
$a_not_select_inf = "인터페이스를 선택 하십시오";
?>

