<?
$m_context_title_stats	="Estadísticas de tráfico";
$m_receive		="Recibir";
$m_transmit		="Transmitir";
$m_wan			="Internet";
$m_lan			="LAN";
$m_wired		="CON CABLES";
if(query("/runtime/func/ieee80211n")==1){ $m_wlan_11g = "11n INALÁMBRICO";}
 else { $m_wlan_11g = "11g INALÁMBRICO"; }
$m_packets		="Paquetes";
$m_b_refresh		="Actualizar";
$m_b_reset		="Reiniciar";
$a_only_admin_account_can_clear_the_statistics="¡Sólo la cuenta admin puede eliminar las estadísticas!";
?>
