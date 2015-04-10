<h1>MENU SUPPORTO</h1>
	<table border=0 cellspacing=0 cellpadding=0 width=750 height=1103>
 <tr>
 <td width="750" height=40><font size=4><b>Avanzate</b></font></td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>

 </tr>
<tr>
	<td height=228>
		<p>
			<a name=05><strong>Inoltro porte avanzato  </strong></a><br>
			L'opzione Inoltro porte avanzato consente agli utenti Internet di accedere ai servizi disponibili tramite la LAN. Questa funzionalit¨¤ ¨¨ utile per l'hosting di servizi online quali FTP, Web o server di gioco. Per ogni voce viene definita una porta pubblica sul router per il reindirizzamento a un indirizzo IP e a una porta LAN interna.
		</p>
		<p>
			Port Forwarding Parameters<br>
		------------------------------------------------------------
			<strong><em>Nome</em></strong> -
			Consente di assegnare un nome significativo al server virtuale, ad esempio Server Web. Nell'elenco a discesa "Nome applicazione" sono disponibili diversi tipi noti di server virtuale. Selezionare una delle voci dell'elenco per inserire automaticamente gli altri parametri con i valori standard per il tipo di server.<br>
			<strong><em>Indirizzo IP </em></strong> -
			Indirizzo IP del sistema della rete locale che fornir¨¤ il servizio virtuale, ad esempio 192.168.0.50. ¨¨ possibile selezionare un computer dall'elenco di client DHCP nel menu a discesa "Nome computer" oppure immettere manualmente l'indirizzo IP del computer server.<br>
			<strong><em>Nome applicazione </em></strong> -
			Elenco di applicazioni note predefinite da cui gli utenti possono effettuare una selezione per una pi¨´ rapida configurazione.<br>
			<strong><em>Nome computer </em></strong> - Elenco di client DHCP.<br>
			<strong><em>Tipo di traffico</em></strong> -
			Consente di selezionare il protocollo utilizzato dal servizio. ¨¨ possibile selezionare le opzioni pi¨´ comuni, ovvero UDP, TCP, UDP e TCP, dal menu a discesa. Per specificare un qualsiasi altro protocollo, selezionare "Altro" dall'elenco, quindi immettere il numero di protocollo corrispondente (assegnato da IANA) nella casella Protocollo.<br>
			<strong><em>Porta privata</em></strong> -
			Porta che verr¨¤ utilizzata nella rete interna.<br>
			<strong><em>Porta pubblica</em></strong> -
			Porta accessibile da Internet.<br>
		</p>
	</td>
</tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>

 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=64> <strong>Regole applicazione <font size=4><b><a name=06></a></b></font> </strong><br>
Alcune applicazioni, ad esempio i giochi su Internet, le applicazioni per videoconferenza o la telefonia Internet e altre ancora, richiedono l'uso di pi¨´ connessioni. Con tali applicazioni potrebbe risultare difficoltoso utilizzare la funzione NAT (Network Address Translation). Se ¨¨ necessario eseguire applicazioni che richiedono pi¨´ connessioni, specificare la porta normalmente associata a un'applicazione nel campo "Porta di trigger", selezionare il tipo di protocollo TCP (Transmission Control Protocol) o UDP (User Datagram Protocol), quindi immettere le porte pubbliche associate alla porta di trigger nel campo Porta del firewall per aprirle per il traffico in ingresso. Il menu a discesa Nome applicazione contiene nomi di applicazioni note gi¨¤ definite.<br>

<strong><em>Nome </em></strong> - Nome che fa riferimento all'applicazione. <br>
<strong><em>Porta di trigger </em></strong> -  Porta utilizzata per attivare l'applicazione. Pu¨° essere una porta singola o un intervallo di porte. <br>
<strong><em>Tipo di traffico </em></strong> - Protocollo utilizzato per attivare l'applicazione. <br>
<strong><em>Porta del firewall </em></strong> - Numero di porta sul lato WAN che verr¨¤ utilizzato per accedere all'applicazione. ¨¨ possibile definire una porta singola o un intervallo di porte. Utilizzare una virgola per aggiungere pi¨´ porte o intervalli di porte.<br>
<strong><em>Tipo di traffico </em></strong> - Protocollo utilizzato per l'applicazione.</td>

 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
<tr>
	<td height=99>
		<p>
			<a name=07><strong>Controllo di accesso</strong></a><br>
			Per consentire o impedire ai computer LAN di accedere a Internet e alla rete vengono utilizzati dei filtri. All'interno della rete ¨¨ possibile configurare l'unit¨¤ per consentire o negare l'accesso a Internet ai computer che utilizzano i rispettivi indirizzi MAC
		</p>
		<p>
			<strong>Filtri MAC</strong><br>
			Utilizzare i filtri MAC per impedire ai computer della rete locale LAN di accedere a Internet. ¨¨ possibile aggiungere manualmente un indirizzo MAC oppure selezionarlo dall'elenco di client attualmente connessi all'unit¨¤.<br>
			Selezionare "Attiva filtro MAC e CONSENTI ai computer con l'indirizzo MAC in elenco di accedere alla rete" se si desidera consentire l'accesso alla rete ai soli computer selezionati.<br>
			Selezionare "Attiva filtro MAC e NON CONSENTIRE ai computer con l'indirizzo MAC in elenco di accedere alla rete" se si desidera consentire l'accesso alla rete a tutti i computer ad eccezione di quelli inclusi nell'elenco.<br>
			<strong><em>Indirizzo MAC </em></strong> -
			Indirizzo MAC del dispositivo di rete da aggiungere all'elenco del filtro MAC.<br>
			<strong><em>Elenco client DHCP </em></strong> -
			Il nome host dei client DHCP ¨¨ disponibile nel menu a discesa Nome computer. ¨¨ possibile selezionare il computer client da aggiungere all'elenco del filtro MAC e fare clic sul pulsante freccia. In tal modo l'indirizzo MAC del computer verr¨¤ aggiunto automaticamente al campo appropriato.
		</p>
		<p>
			¨¨ possibile utilizzare il menu a discesa Sempre per selezionare una pianificazione definita in precedenza oppure fare clic sul pulsante Aggiungi nuova per aggiungere una nuova pianificazione.
		</p>
		<p>
			Casella di controllo utilizzata per abilitare o disabilitare una voce specifica.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<a name=08><strong>Firewall e DMZ</strong></a><br>
			La sezione Impostazioni firewall contiene l'opzione per configurare un host DMS.
		</p>
		<p>
			<strong>Abilita SPI</strong><br>
			SPI (acronimo di "Stateful Packet Inspection", noto anche come "filtro dinamico dei pacchetti") consente di prevenire attacchi informatici tenendo traccia di pi¨´ stati per sessione. Consente inoltre di verificare che il traffico in entrata e in uscita nella sessione sia conforme al protocollo. Quando il protocollo ¨¨ TCP, SPI verifica che i numeri di sequenza dei pacchetti siano compresi nell'intervallo valido per la sessione, eliminando quelli che non presentano un numero di sequenza valido. Indipendentemente dall'abilitazione di SPI, il router tiene sempre traccia degli stati della connessione TCP e assicura che i flag dei singoli pacchetti TCP siano validi per lo stato corrente.
		</p>
		<p>
			<strong>DMZ </strong><br>
			Se si dispone di un computer che non ¨¨ in grado di eseguire correttamente applicazioni Internet mascherate da <?query("/sys/modelname");?>, ¨¨ possibile garantire al computer accesso illimitato a Internet. Immettere l'indirizzo IP di tale computer come host DMZ (Demilitarized Zone) con accesso illimitato a Internet. L'aggiunta di un client a DMZ pu¨° esporre il computer a una serie di rischi di sicurezza, pertanto utilizzare questa opzione solo in caso di reale necessit¨¤.
		</p>
		<p>
			<strong>Regole firewall</strong><br>
			Le regole firewall vengono utilizzate per consentire o impedire il traffico in ingresso o in uscita dal router sulla base degli indirizzi IP di origine e di destinazione, nonch¨¦ del tipo di traffico e della porta specifica utilizzata per la gestione dei dati.<br>
			<strong><em>Nome</em></strong> - Consente di specificare un nome per la regola firewall.<br>
			<strong><em>Azione</em></strong> - Consente di scegliere se consentire o impedire il traffico<br>
			<strong>Interfaccia</strong><br>
			<strong><em>Origine</em></strong> -
			Utilizzare il menu a discesa <strong>Origine</strong> per selezionare il punto iniziale del traffico da consentire o impedire dall'interfaccia LAN o WAN.<br>
			<strong><em>Destinaz</em></strong> -
			Utilizzare il menu a discesa <strong>Destinaz.</strong> per selezionare il punto finale del traffico da consentire o impedire dall'interfaccia LAN o WAN.<br>
			<strong><em>Indirizzo IP</em></strong> -
			¨¨ possibile specificare un singolo indirizzo IP di origine o di destinazione immettendolo nella casella superiore
 oppure specificare un intervallo di indirizzi IP immettendo il primo indirizzo IP dell'intervallo nella casella superiore e l'ultimo indirizzo IP nella casella inferiore.<br>
			<strong><em>Protocollo</em></strong> -
			Utilizzare il menu a discesa <strong>Protocollo</strong> per selezionare il tipo di traffico.<br>
			<strong><em>Intervallo porte</em></strong> -
			Immettere lo stesso numero di porte in entrambe le caselle per specificare una porta singola oppure immettere la prima porta nella casella superiore e l'ultima porta nella casella inferiore per specificare un intervallo di porte.<br>
			<strong><em>Pianificazione</em></strong> -
			Utilizzare il menu a discesa <strong>Sempre</strong> per selezionare una pianificazione definita in precedenza oppure fare clic sul pulsante <strong>Aggiungi nuova</strong> per aggiungere una nuova pianificazione.
 </p>
	</div></td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
 <tr>
 <td height=20><p><strong>Wireless avanzate <a name=09></a></strong></p>

 <p>Le opzioni di questa pagina devono essere modificate da utenti esperti o solo se richiesto da un tecnico del servizio di assistenza poich¨¦ se non vengono configurate correttamente possono influire negativamente sulle prestazioni del router.</p>
 <p><strong><em>Velocit¨¤ di trasmissione (TX) - </em></strong> Selezionare le velocit¨¤ di trasmissione di base sulla base della velocit¨¤ delle schede wireless della WLAN (Wireless Local Area Network). </p>
 <p><strong><em>Potenza di trasmissione - </em></strong>¨¨ possibile ridurre la potenza in uscita di <?query("/sys/modelname");?> selezionando valori pi¨´ bassi per Potenza di trasmissione dall'elenco a discesa. Le opzioni sono: 100%, 50%, 25% e 12,5%.</p>
 <p><strong><em>Intervallo beacon - </em></strong> I beacon sono pacchetti inviati da un punto di accesso per sincronizzare una rete wireless. Specificare per Intervallo beacon un valore compreso tra 20 e 1000. Il valore di default ¨¨ impostato su 100 millisecondi. </p>

 <p><strong><em>Soglia RTS - </em></strong> ¨¨ consigliabile non modificare l'impostazione di default di questo valore, pari a 2346. Se si rileva un flusso di dati incoerente, si consiglia di apportare solo lievi modifiche all'intervallo di valori compreso tra 1 e 2346. Il valore di default per Soglia RTS ¨¨ impostato su 2346. </p>
 <p><strong><em>Frammentazione - </em></strong> ¨¨ consigliabile non modificare l'impostazione di default di questo valore, pari a 2346. Se si nota una percentuale elevata di errori nei pacchetti, ¨¨ possibile aumentare leggermente il valore di
 &quot;Frammentazione&quot; specificando un numero compreso tra 256 e 2346. L'impostazione di un valore troppo basso per la frammentazione pu¨° causare un deterioramento delle prestazioni. </p>
 <p><strong><em>Intervallo DTIM - </em></strong> Immettere un valore compreso tra 1 e 255 per DTIM (Delivery Traffic Indication Message). Un DTIM ¨¨ un conto alla rovescia che informa i client della finestra successiva per l'ascolto di messaggi broadcast e multicast. Una volta memorizzati nel buffer i messaggi broadcast o multicast per i client associati, il punto di accesso invia il DTIM successivo in base al valore dell'intervallo DTIM specificato. I client del punto di accesso ascoltano i beacon e si attivano in modo da ricevere i messaggi broadcast e multicast. Il valore di default per Intervallo DTIM ¨¨ impostato su 1. </p>

 <p><strong><em>Tipo di preambolo - </em></strong> Il tipo di preambolo definisce la lunghezza del blocco CRC (Cyclic Redundancy Check) per le comunicazioni tra il punto di accesso e le schede wireless di roaming. Assicurarsi di selezionare il tipo di preambolo appropriato e fare clic sul pulsante Applica. </p>
 <p><span class="style2">Nota: </span>Nelle aree caratterizzate da un elevato traffico di rete ¨¨ opportuno utilizzare il tipo di preambolo pi¨´ breve. CRC ¨¨ una tecnica comune per la rilevazione degli errori di trasmissione dati. </p>
 <p><strong><em>Modalit¨¤ CTS - </em></strong>Selezionare Nessuno per disabilitare la funzionalit¨¤. Selezionare Automatico per forzare il router a richiedere a ogni dispositivo wireless della rete di eseguire un handshake RTS/CTS prima di consentire la trasmissione dei dati. Selezionare Automatico per fare in modo che sia il router a decidere quando ¨¨ necessario l'handshake RTS/CTS. </p>
<?if(query("/runtime/func/ieee80211n")!="1"){
 echo "<p><strong><em>Modalit¨¤ solo 802.11g - </em></strong>Abilitare questa modalit¨¤ se la rete ¨¨ costituita esclusivamente da dispositivi 802.11g. Se la rete include sia client wireless 802.11b che 802.11g, disabilitare questa modalit¨¤. </p> </td>";
}?>

 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=20><p><strong>Rete avanzata <a name=10></a></strong></p>

 <p>Questa sezione contiene le impostazioni che consentono di modificare la modalit¨¤ di gestione di alcuni tipi di traffico da parte del router. Si consiglia di non modificare queste impostazioni a meno che non siano gi¨¤ note oppure non sia stato richiesto da un tecnico del servizio di assistenza. </p>

<!--
 <p><strong>Passthrough VPN </strong><br>Il dispositivo supporta il passthrough VPN (Virtual Private Network) per PPTP (Point-to-Point Tunneling Protocol) e IPSec (IP Security). Dopo aver abilitato il passthrough VPN, non ¨¨ necessario creare voci relative al server virtuale o all'inoltro porte per stabilire correttamente sessioni VPN in uscita. Tramite il dispositivo ¨¨ possibile stabilire pi¨´ connessioni VPN. Tale caratteristica ¨¨ utile quando la rete locale LAN include molti client VPN. </p>
-->

 <p><strong>UPnP </strong><br>UPnP ¨¨ l'acronimo di Universal Plug and Play, un'architettura di rete che garantisce la compatibilit¨¤ tra apparecchiature di rete, software e periferiche. <?query("/sys/modelname");?> ¨¨ un router abilitato per UPnP, pertanto ¨¨ compatibile con altri dispositivi/software UPnP. Se non si desidera utilizzare la funzionalit¨¤ UPnP, disabilitarla selezionando &quot;Disabilitato&quot;. </p>
 <p><strong>Ping WAN </strong><br>Quando si abilita la risposta ping WAN, l'indirizzo IP pubblici della WAN (Wide Area Network) del dispositivo risponder¨¤ ai comandi ping inviati da utenti Internet. Il ping degli indirizzi IP pubblici della WAN viene in genere utilizzato dai pirati informatici per testare la validit¨¤ dell'indirizzo IP della WAN. </p>
 <p><strong>Velocit¨¤ porte WAN </strong><br>Consente di selezionare la velocit¨¤ dell'interfaccia WAN di <?query("/sys/modelname");?>. Scegliere tra 100 Mbps, 10 Mbps o 10/100 Mbps auto. </p>

<!--
 <p><strong>Modalit¨¤ gioco</strong><br>Se si riscontrano problemi durante l'utilizzo di giochi online o persino con alcune applicazioni che utilizzano dati vocali, potrebbe essere necessario abilitare la modalit¨¤ gioco per consentire il corretto funzionamento di tali applicazioni. Quando non si utilizzano giochi o applicazioni vocali, ¨¨ consigliabile che la modalit¨¤ gioco sia disabilitata. </p>
--> 
<?if(query("/runtime/func/dis_multicast_stream")!="1"){
echo " <p><strong>Flussi multicast</strong><br>Abilitare questa opzione per consentire un passaggio pi¨´ efficiente del traffico multicast da Internet alla rete.  </p> </td>\n";
}
?>
 </tr>

<?if(query("/runtime/func/dis_multicast_stream")!="1"){
echo "<tr><td height=20>&nbsp;</td></tr>\n";
echo "<tr>\n";
echo "	<td height=20>\n";
echo "		<p>\n";
echo "			<strong>Abilita flussi multicast</strong><br>\n";
echo "			Abilitare questa opzione se si ricevono servizi di tipo video a richiesta da Internet.\n";
echo "			Il router utilizza il protocollo IGMP per garantire prestazioni ottimali per il multicasting,\n";
echo "			ovvero la trasmissione di contenuti identici, ad esempio multimediali, da un'origine unica a pi¨´ destinatari.\n"; 
echo "			¨¨ necessario abilitare questa opzione se eventuali applicazioni nella LAN partecipano a un gruppo multicast.\n"; 
echo "			Se un'applicazione LAN multimediale non riceve contenuti come previsto, provare ad abilitare questa opzione.\n";
echo "		</p>\n";
echo "	</td>\n";
echo "</tr>\n";
}
?>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
<?if(query("/runtime/func/dis_routing")!="1"){
echo "<tr>\n";
echo "	<td height=99><strong>Routing </strong><a name=11></a><br>\n";
echo "		L'opzione Routing consente di definire route fisse per destinazioni specificate.<br>\n";
echo "		<strong><em>Abilita </em></strong> - Specifica se la voce sar¨¤ abilitata o disabilitata.<br>\n";
echo "		<strong><em>Interfaccia </em></strong> - Consente di specificare l'interfaccia, ovvero WAN o WAN fisica, che\n";
echo "		il pacchetto IP deve utilizzare per essere trasmesso dal router quando si utilizza questa route.<br>\n";
echo "		<strong><em>Interfaccia (WAN)</em></strong> - Interfaccia su cui ricevere dall'ISP l'indirizzo IP per accedere a Internet.<br>\n";
echo "		<strong><em>Interfaccia (WAN fisica)</em></strong> - Interfaccia su cui ricevere dall'ISP l'indirizzo IP per accedere agli ISP.<br>\n";
echo "		<strong><em>Destinazione </em></strong> - Indirizzo IP dei pacchetti per i quali verr¨¤ utilizzata questa route.<br>\n";
echo "		<strong><em>Subnet mask </em></strong> - I bit uno nella mask indicano quali bit dell'indirizzo IP devono corrispondere. <br>\n";
echo "		<strong><em>Gateway </em></strong> - Specifica l'hop successivo da utilizzare con questa route.  Il gateway 0.0.0.0 indica l'assenza di un hop successivo, pertanto l'indirizzo IP corrispondente viene direttamente collegato al router sull'interfaccia specificata, ovvero WAN o WAN fisica.\n";
echo " </td>\n";
echo " </tr>\n";
}
?>

 <tr>
 <td height=20>&nbsp;</td>
 </tr>

 </table>
