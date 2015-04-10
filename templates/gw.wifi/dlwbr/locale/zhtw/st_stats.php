<?
$m_context_title_stats	="&nbsp";
$m_receive		="接收";
$m_transmit		="傳送";
$m_wan			="網際網路";
$m_lan			="區域網路";
$m_wired		="有線";
if(query("/runtime/func/ieee80211n")==1){ $m_wlan_11g = "無線 11n";} else { $m_wlan_11g = "無線 11g"; }
$m_packets		="封包";
$m_b_refresh		="重新整理";
$m_b_reset		="重設";
$a_only_admin_account_can_clear_the_statistics="只有 admin 帳號可清除這些統計數據!";
?>