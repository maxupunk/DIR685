<?
$m_title_firewall = "방화벽 설정";
$m_enable_spi="SPI 설정";
$m_enable_dos="DoS 방어 설정 ";
$m_title_firewall_rules = "방화벽 규칙";
$m_action = "동작";
$m_allow = "허용";
$m_deny = "거부";
$m_inf = "인터페이스";
$m_start_ip = "시작 IP 주소";
$m_end_ip	="마지막 IP 주소";
$m_protocol	="프로토콜";
$m_port_range ="포트 범위";
$m_src	="출발지";
$m_dst = "목적지";
$m_schedule = "스케쥴";
$m_always_on = "항상 연결";
$m_add_new_sch = "새 스케쥴 추가";
$m_title_fw_list="방화벽 규칙 리스트 ";
$m_allow_ping = "WAN 으로 부터의 PING ";
$m_remote_management="원격 관리";


$m_title_dmz_rule = "DMZ 호스트 ";
$m_desc_dmz =
	"DMZ(비무장 지대) 기능으로 PC 한 대를 공유기 외부에 두는 것처럼 설정할 수 있습니다. ".
	"공유기 아래에서 인터넷 애플리케이션이 제대로 동작하지 않는 경우, 인터넷 접속에 제한이 없는 DMZ 구간에 PC를 배치할 ".
	"수 있습니다.";
$m_note_dmz =
	"<strong>주의:</strong> DMZ에 PC를 배치하면 ".
	"PC는 여러 가지 보안 위협에 노출 될 수 있음에 주의하십시오. 이 기능은 최후의 수단으로만 사용하시기 바랍니다.";
$m_enable_dmz_host = "DMZ 호스트 활성";
$m_ip_addr_dmz = "DMZ IP 주소"; 
$m_computer_name = "컴퓨터 명";


$a_no_ip_selected	= "PC를 먼저 선택하십시오!";
$a_invalid_ip		= "IP 주소가 잘못되었습니다!";
$a_confirm_to_del_fw= "이 규칙을 정말로 삭제하시겠습니까?";
$a_invalid_port="포트가 잘못되었습니다!";
$a_invalid_port_range="포트 범위가 잘못되었습니다!";

$a_invalid_src_startip="출발지 시작 주소가 잘못되었습니다!";
$a_src_startip_in_different_subnet   = "출발지 시작 IP 주소가 잘못되었습니다! 출발지 시작 IP 주소와 공유기 주소는 반드시 같은 네트워크에 있어야 합니다. ";

$a_invalid_src_endip="출발지 마지막 주소가 잘못되었습니다!";
$a_src_endip_in_different_subnet   = "출발지 마지막 IP 주소가 잘못되었습니다! 출발지 마지막 IP 주소와 공유기 주소는 반드시 같은 네트워크에 있어야 합니다. ";

$a_invalid_dst_startip="목적지 시작 IP 주소가 잘못되었습니다!";
$a_dst_startip_in_different_subnet   = "목적지 시작 IP 주소가 잘못되었습니다! 목적지 시작 IP 주소와 공유기 주소는 반드시 같은 네트워크에 있어야 합니다.";

$a_invalid_dst_endip="목적지 마지막 주소가 잘못되었습니다!";
$a_dst_endip_in_different_subnet   = "목적지 마지막 IP 주소가 잘못되었습니다! 목적지 마지막 IP 주소와 공유기 주소는 반드시 같은 네트워크에 있어야 합니다.";

$a_fw_name_cant_be_empty="방화벽  이름이 공백이어서는 안됩니다!";
$a_not_support_same_direction="출발지 인터페이스와 목적지 인터페이스가 같아서는 안됩니다!";
$a_invalid_src_ip_range="출발지 IP 주소 범위가 잘못되었습니다!";
$a_invalid_dst_ip_range="목적지 IP 주소 범위가 잘못되었습니다!";
$a_confirm_swap_fw="우선 순위를 정말로 변경하시겠습니까?";
?>
