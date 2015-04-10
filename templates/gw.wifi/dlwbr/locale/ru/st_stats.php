<?
$m_context_title_stats	="&nbsp";
$m_receive		="Принято";
$m_transmit		="Передано";
$m_wan			="Интернет";
$m_lan			="LAN";
$m_wired		="ПРОВОДНОЕ ПОДКЛЮЧЕНИЕ";
if(query("/runtime/func/ieee80211n")==1){ $m_wlan_11g = "Беспроводной доступ 11n";} else { $m_wlan_11g = "Беспроводной доступ 11g"; }
//$m_wlan_11g		="БЕСПРОВОДНОЙ ДОСТУП 11g";
$m_packets		="Пакетов";
$m_b_refresh		="Обновить";
$m_b_reset		="Сбросить";
$a_only_admin_account_can_clear_the_statistics="Очистить статистику может только администратор!";
?>
