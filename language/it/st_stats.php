<?
$m_context_title_stats	="Statistiche traffico";
$m_receive		="Ricezione";
$m_transmit		="Trasmissione";
$m_wan			="Internet";
$m_lan			="LAN";
$m_wired		="CABLATA";
if(query("/runtime/func/ieee80211n")==1){ $m_wlan_11g = "WIRELESS 11n";}
 else { $m_wlan_11g = "WIRELESS 11g"; }
$m_packets		="Pacchetti";
$m_b_refresh		="Aggiorna";
$m_b_reset		="Ripristina";
$a_only_admin_account_can_clear_the_statistics="Solo l'account admin può cancellare le statistiche.";
?>
