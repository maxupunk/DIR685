<?
$m_context_title_stats	="Traffic 통계";
$m_receive		="받음";
$m_transmit		="보냄";
$m_wan			="인터넷";
$m_lan			="LAN";
$m_wired		="유선";
if(query("/runtime/func/ieee80211n")==1){ $m_wlan_11g = "무선 11n";}
 else { $m_wlan_11g = "무선 11g"; }
$m_packets		="패킷";
$m_b_refresh		="새로고침";
$m_b_reset		="초기화";
$a_only_admin_account_can_clear_the_statistics="관리자(admin)만 통계를 초기화 할 수 있습니다!";
?>

