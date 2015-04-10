<?
/* --------------------------------------------------------- */
//$TITLE=$m_pre_title."CONFIGURAZIONE";
/* --------------------------------------------------------- */
$m_title_router_setting	= "Impostazioni router";
$m_desc_router_setting	=	"In questa sezione è possibile configurare le impostazioni della rete interna per il router. ".
													"L'indirizzo IP configurato in questo contesto corrisponde all'indirizzo IP utilizzato per accedere ".
													"all'interfaccia di gestione basata sul Web. Se si modifica l'indirizzo IP, è necessario ".
													"aggiornare le impostazioni di rete del PC per poter accedere nuovamente alla rete.";

$m_router_ipaddr	= "Indirizzo IP router";
$m_subnet_mask		= "Subnet mask di default";
$m_domain_name		= "Nome di dominio locale";
$m_enable_dnsr		= "Abilita relay DNS";

$m_title_dhcp_svr	= "Impostazioni server DHCP";
$m_desc_dhcp_svr	=	"In questa sezione è possibile configurare il server DHCP incorporato in modo che assegni automaticamente l'indirizzo IP ai client ".
										"computer della rete.";

$m_enable_dhcp		= "Abilita server DHCP";
$m_dhcp_range		= "Intervallo di indirizzi IP DHCP";
$m_to			= "a";
$m_range_comment	= "(indirizzi compresi nella subnet LAN)";
$m_lease_time		= "Tempo di validità DHCP";
$m_netbios	= "Annuncio NetBIOS";
$m_netbios_learn	=	"Rileva NetBIOS da WAN";
$m_netbios_scope	=	"Ambito NetBIOS";
$m_optional	=	"(facoltativo)";
$m_netbios_type	=	"Tipo di nodo NetBIOS";
$m_broadcast	=	"Solo broadcast (da utilizzare quando non sono configurati server WINS)";
$m_ptop	=	"Point-to-point (broadcast non disponibile)";
$m_mix_mode	=	"Modalità mista (prima broadcast, quindi point-to-point)";
$m_hybrid	=	"Ibrido (prima point-to-point, quindi broadcast)";
$m_primary_wins	=	"Indirizzo IP WINS primario";
$m_secondary_wins	=	"Indirizzo IP WINS secondario";

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
$a_network_conflict	= "La rete della zona guest deve essere diversa dalla zona host.";
$a_lan_wan_conflict = "La rete WAN deve essere diversa dalla rete LAN.";
$a_invalid_domain_name	= "Nome di dominio non valido.";
$a_invalid_ip_range	= "Intervallo di indirizzi IP non valido per il server DHCP.";
$a_invalid_lease_time	= "Tempo di validità DHCP non valido.";
$a_del_confirm		= "Eliminare questa voce?";
$a_same_static_mac	= "Esiste già una voce con lo stesso Indirizzo MAC.\\n Modificare l'Indirizzo MAC.";
$a_same_static_ip	= "Esiste già una voce con lo stesso Indirizzo IP.\\n Modificare l'Indirizzo IP.";
$a_same_static_hostname = "Esiste già una voce con lo stesso Nome computer.\\n Modificare il Nome computer.";
$a_same_with_lan_ip	= "L'indirizzo IP non può essere identico a quello della LAN.";
$a_invalid_computer_name= "Nome di computer non valido.";
$a_invalid_mac		= "Indirizzo MAC non valido.";

$a_invalid_form         = "Formato di Ambito NetBIOS non valido.";
$a_invalid_primaywins	= "WINS primario NetBios non valido.";
$a_invalid_secondaywins	= "WINS secondario NetBios non valido.";
$a_primary_null		= "Se si specifica l'indirizzo IP WINS secondario, è necessario specificare anche quello primario.";
?>
