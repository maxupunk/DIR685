<?
/* --------------------------------------------------------- */
//$TITLE=$m_pre_title."CONFIGURAZIONE";
/* --------------------------------------------------------- */
$m_title_router_setting	= "Impostazioni router";
$m_desc_router_setting	=
	"In questa sezione ¨¨ possibile configurare le impostazioni della rete interna per il router.  L'indirizzo IP configurato in questo contesto corrisponde all'indirizzo IP utilizzato per accedere all'interfaccia di gestione basata sul Web. Se si modifica l'indirizzo IP, ¨¨ necessario aggiornare le impostazioni di rete del PC per poter accedere nuovamente alla rete.";

$m_router_ipaddr	= "Indirizzo IP router";
$m_subnet_mask		= "Subnet mask di default";
$m_domain_name		= "Nome di dominio locale";
$m_enable_dnsr		= "Abilita relay DNS";

$m_title_dhcp_svr	= "Impostazioni server DHCP";
$m_desc_dhcp_svr	=
	"In questa sezione ¨¨ possibile configurare il server DHCP incorporato in modo che assegni automaticamente l'indirizzo IP ai computer della rete.";

$m_enable_dhcp		= "Abilita server DHCP";
$m_dhcp_range		= "Intervallo di indirizzi IP DHCP";
$m_to			= "a";
$m_range_comment	= "(indirizzi compresi nella subnet LAN)";
$m_lease_time		= "Tempo di validit¨¤ DHCP";
$m_minutes		= "(minuti)";

$m_title_add_client	= "Prenotazione DHCP";
$m_computer_name	= "Nome computer";
$m_clone_mac		= "Copia indirizzo MAC PC";

$m_title_static_client_list = "Elenco prenotazioni DHCP";
$remaining_wording	="Numero rimanente di client configurabili";

$m_title_client_list	= "Elenco client DHCP";
$m_host_name		= "Nome host";
$m_ipaddr		= "Indirizzo IP";
$m_macaddr		= "Indirizzo MAC";
$m_expired_time		= "Ora di scadenza";

$m_days	= "giorno/i";
$m_hrs	= "ora/e";
$m_mins	= "minuto/i";
$m_secs	= "secondo/i";

$a_invalid_ip		= "Indirizzo IP non valido.";
$a_invalid_netmask	= "Subnet mask non valida.";
$a_network_conflict	= "La rete della zona guest deve essere diversa dalla zona host ";
$a_invalid_domain_name	= "Nome di dominio non valido.";
$a_invalid_ip_range	= "Intervallo di indirizzi IP non valido per il server DHCP.";
$a_invalid_lease_time	= "Tempo di validit¨¤ DHCP non valido.";
$a_del_confirm		= "Eliminare questa voce?";
$a_same_static_mac	= "Esiste gi¨¤ una voce con lo stesso indirizzo MAC. Modificare l'indirizzo MAC.";
$a_same_static_ip	= "Esiste gi¨¤ una voce con lo stesso indirizzo IP. Modificare l'indirizzo IP.";
$a_same_static_hostname = "Esiste gi¨¤ una voce con lo stesso nome computer. Modificare il nome computer.";
$a_same_with_lan_ip	= "L'indirizzo IP non pu¨° essere identico a quello della LAN.";
$a_invalid_computer_name= "Nome di computer non valido.";
$a_invalid_mac		= "Indirizzo MAC non valido.";
?>
