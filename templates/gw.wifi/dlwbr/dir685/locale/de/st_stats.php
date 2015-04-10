<?
$m_context_title_stats	="Datenverkehrstatistik";
$m_receive		="Empfangen";
$m_transmit		="Übertragen";
$m_wan			="Internet";
$m_lan			="LAN";
$m_wired		="VERKABELT";
if(query("/runtime/func/ieee80211n")==1){ $m_wlan_11g = "WIRELESS 11n";}
 else { $m_wlan_11g = "WIRELESS 11g"; }
$m_packets		="Pakete";
$m_b_refresh		="Aktualisieren";
$m_b_reset		="Zurücksetzen";
$a_only_admin_account_can_clear_the_statistics="Nur das Adminkonto kann die Statistik löschen";
?>
