<?
$m_context_title_stats	="Statistiques sur le trafic";
$m_receive		="Recevoir";
$m_transmit		="Transmettre";
$m_wan			="Internet";
$m_lan			="Réseau local";
$m_wired		="CÂBLÉ";
if(query("/runtime/func/ieee80211n")==1){ $m_wlan_11g = "11n SANS FIL";}
 else { $m_wlan_11g = "11g SANS FIL"; }
$m_packets		="Paquets";
$m_b_refresh		="Actualiser";
$m_b_reset		="Réinitialisation";
$a_only_admin_account_can_clear_the_statistics="Seul un compte admin peut effacer les statistiques !";
?>
