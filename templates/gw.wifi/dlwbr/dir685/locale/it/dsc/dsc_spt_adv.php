<div class="box">
<a name="port_forwarding"><h2>Inoltro porte</h2></a>
	<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=228>
		<p>
			L'opzione Inoltro porte avanzato consente agli utenti Internet di accedere ai servizi disponibili tramite la LAN. Questa funzionalità è utile per l'hosting di servizi online quali FTP, Web o server di gioco. Per ogni voce viene definita una porta pubblica sul router per il reindirizzamento a un indirizzo IP e a una porta LAN interni.
		</p>
		<p>
			Parametri per inoltro porte avanzato<br>
			<strong><em>Nome</em></strong> -
			Consente di assegnare un nome significativo al server virtuale, ad esempio Server Web. Nell'elenco a discesa "Nome applicazione" sono disponibili diversi tipi noti di server virtuale. Selezionare una delle voci dell'elenco per inserire automaticamente gli altri parametri con i valori standard per il tipo di server.<br>
			<strong><em>Indirizzo IP </em></strong> -
			Indirizzo IP del sistema della rete locale che fornirà il servizio virtuale, ad esempio 192.168.0.50. È possibile selezionare un computer dall'elenco di client DHCP nel menu a discesa "Nome computer" oppure immettere manualmente l'indirizzo IP del computer server.<br>
			<strong><em>Nome applicazione </em></strong> -
			Elenco di applicazioni note predefinite da cui gli utenti possono effettuare una selezione per una più rapida configurazione.<br>
			<strong><em>Nome computer </em></strong> - Elenco di client DHCP.<br>
			<strong><em>Tipo di traffico</em></strong> -
			Consente di selezionare il protocollo utilizzato dal servizio. È possibile selezionare le opzioni più comuni, ovvero UDP, TCP, UDP e TCP, dal menu a discesa.<br>
			<strong><em>Porta privata</em></strong> -
			Porta che verrà utilizzata nella rete interna.<br>
			<strong><em>Porta pubblica</em></strong> -
			Porta accessibile da Internet.<br>
		</p>
	</td>
</tr>
 </table>
 </div>
 
 
<div class="box">
<a name="application_rules"><h2>Regole applicazione</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=64> 
Alcune applicazioni, ad esempio i giochi su Internet, le applicazioni per videoconferenza o la telefonia Internet e altre ancora, richiedono l'uso di più connessioni. Con tali applicazioni potrebbe risultare difficoltoso utilizzare la funzione NAT (Network Address Translation). Se è necessario eseguire applicazioni che richiedono più connessioni, specificare la porta normalmente associata a un'applicazione nel campo "Porta di trigger", selezionare il tipo di protocollo TCP (Transmission Control Protocol) o UDP (User Datagram Protocol), quindi immettere le porte pubbliche associate alla porta di trigger nel campo Porta del firewall per aprirle per il traffico in ingresso. Il menu a discesa Nome applicazione contiene nomi di applicazioni note già definite.
 <br>

<strong><em>Nome </em></strong> - Nome che fa riferimento all'applicazione. <br>
<strong><em>Porta di trigger </em></strong>- Porta utilizzata per attivare l'applicazione. Può essere una porta singola o un intervallo di porte. <br>
<strong><em>Tipo di traffico </em></strong> - Protocollo utilizzato per attivare l'applicazione. <br>
<strong><em>Porta del firewall </em></strong> - Numero di porta sul lato WAN che verrà utilizzato per accedere all'applicazione. È possibile definire una porta singola o un intervallo di porte. Utilizzare una virgola per aggiungere più porte o intervalli di porte. <br>
<strong><em>Tipo di traffico </em></strong> - Protocollo utilizzato per l'applicazione. </td>

 </tr>
 </table>
 </div>
 
 
<div class="box">
<a name="qos_engine"><h2>Motore QoS</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
<td height=64>
		<p>
			Questo QoS intelligente consente di ottimizzare la qualità dei dati voce VoIP o dello streaming impostando una priorità maggiore per il traffico VoIP o streaming rispetto al normale traffico di rete, ad esempio FTP o Web. Per prestazioni ottimali, selezionare l'opzione "Attesa eliminata" per impostare automaticamente la priorità per le applicazioni.
			<br>
		</p>
</td>
</tr>
</table>
</div>
 
 
<div class="box">
<a name="access_control"><h2>Filtro di rete</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=99>
		<p>
			Per consentire o impedire ai computer LAN di accedere a Internet e alla rete vengono utilizzati dei filtri. All'interno della rete è possibile configurare l'unità per consentire o negare l'accesso a Internet ai computer che utilizzano i rispettivi indirizzi MAC.
		</p>
		<p>
			<strong>Filtri MAC</strong><br>
			Utilizzare i filtri MAC per impedire ai computer della rete locale LAN di accedere a Internet. È possibile aggiungere manualmente un indirizzo MAC oppure selezionarlo dall'elenco di client attualmente connessi all'unità.
			<br>
			Selezionare "Attiva filtro MAC e CONSENTI ai computer con l'indirizzo MAC in elenco di accedere alla rete" se si desidera consentire l'accesso alla rete ai soli computer selezionati.
			<br>
			Selezionare "Attiva filtro MAC e NON CONSENTIRE ai computer con gli indirizzi MAC in elenco di accedere alla rete" se si desidera consentire l'accesso alla rete a tutti i computer ad eccezione di quelli inclusi nell'elenco.
			<br>
			<strong><em>Indirizzo MAC</em></strong> -
			Indirizzo MAC del dispositivo di rete da aggiungere all'elenco del filtro MAC.<br>
			<strong><em>Elenco client DHCP</em></strong> -
			Il nome host dei client DHCP è disponibile nel menu a discesa Nome computer. È possibile selezionare il computer client da aggiungere all'elenco del filtro MAC e fare clic sul pulsante freccia. In tal modo l'indirizzo MAC del computer verrà aggiunto automaticamente al campo appropriato.
		</p>
		<p>
			È possibile utilizzare il menu a discesa <strong>Sempre</strong> per selezionare una pianificazione definita in precedenza oppure fare clic sul pulsante <strong>Aggiungi nuova</strong> per aggiungere una nuova pianificazione.
		</p>
		<p>
			Casella di controllo utilizzata per abilitare o disabilitare una voce specifica.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="parental_control"><h2>Filtro siti Web</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=44>
		<p>
			Oltre che per filtrare i dispositivi autorizzati ad accedere alla rete e a Internet, è possibile configurare il dispositivo <?query("/sys/modelname");?> anche per consentire o impedire ai computer della rete di accedere a siti Web non appropriati in base al nome di dominio o a parole chiave.
		</p>
		<p>
			<strong>Controllo parentale</strong><br>
			Il controllo parentale viene utilizzato per consentire o impedire ai computer della rete di accedere a siti Web specifici in base a parole chiave o a nomi di dominio specifici. Selezionare "Attiva filtro siti Web e CONSENTI ai computer di accedere SOLO a questi siti" per consentire ai computer della rete di accedere solo agli URL e ai nomi di dominio specificati. Selezionare "Attiva filtro siti Web e NON CONSENTIRE ai computer di accedere SOLO a questi siti" per non consentire ai computer della rete di accedere agli URL e ai nomi di dominio specificati.
		</p>
		<p>
			<span class="style1">Esempio 1:</span><br>
			Se si desidera impedire agli utenti della LAN di accedere a qualsiasi sito Web contenente un URL correlato agli acquisti, è necessario selezionare "Attiva filtro siti Web e NON CONSENTIRE ai computer di accedere SOLO a questi siti" e quindi immettere "acquisti" nell'elenco Regole di filtro siti Web. L'accesso a siti analoghi verrà impedito agli utenti della LAN poiché nell'URL di tali siti è contenuta la parola chiave specificata.
			<br>
			<a href="http://www.yahoo.com/shopping/stores.html">http://www.yahoo.com/shopping/stores.html</a><br>
			<a href="http://www.msn.com/search/shopping-spree.html">http://www.msn.com/search/shopping-spree.html</a>
		</p>
		<p>
			<span class="style1">Esempio 2:</span><br>
			Se si desidera che i propri bambini accedano solo a siti specifici, è opportuno scegliere "Attiva filtro siti Web e CONSENTI ai computer di accedere SOLO a questi siti" e quindi immettere i domini a cui i bambini possono accedere.
		</p>
		<ul>
			<li>Google.com </li>
			<li>Cartoons.com </li>
			<li>Discovery.com </li>
		</ul>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="firewall_dmz"><h2>Impostazioni firewall</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			La sezione Impostazioni firewall contiene un'opzione per configurare un host DMZ.
		</p>
		<p>
			<strong>Abilita SPI</strong><br>
			SPI (acronimo di "Stateful Packet Inspection", noto anche come "filtro dinamico dei pacchetti") consente di prevenire attacchi informatici tenendo traccia di più stati per sessione. Consente inoltre di verificare che il traffico in entrata e in uscita nella sessione sia conforme al protocollo. Quando il protocollo è TCP, SPI verifica che i numeri di sequenza dei pacchetti siano compresi nell'intervallo valido per la sessione, eliminando quelli che non presentano numeri di sequenza validi. Indipendentemente dall'abilitazione di SPI, il router tiene sempre traccia degli stati della connessione TCP e assicura che i flag dei singoli pacchetti TCP siano validi per lo stato corrente.
		</p>
		<p>
			<strong>DMZ </strong><br>
			Se si dispone di un computer che non è in grado di eseguire correttamente applicazioni Internet mascherate dal dispositivo <?query("/sys/modelname");?>, è possibile garantire al computer accesso illimitato a Internet. Immettere l'indirizzo IP di tale computer come host DMZ (Demilitarized Zone) con accesso illimitato a Internet. L'aggiunta di un client a DMZ può esporre il computer a una serie di rischi di sicurezza, pertanto utilizzare questa opzione solo in caso di reale necessità.
		</p>
		<p>
			<strong>Regole firewall</strong><br>
			Le regole firewall vengono utilizzate per consentire o impedire il traffico in ingresso o in uscita dal router sulla base degli indirizzi IP di origine e di destinazione, nonché del tipo di traffico e della porta specifica utilizzata per la gestione dei dati.
			<br>
			<strong><em>Nome</em></strong> - Consente di specificare un nome per la regola firewall.<br>
			<strong><em>Azione</em></strong> - Consente di scegliere se consentire o impedire il traffico.<br>
			<strong>Interfaccia</strong><br>
			<strong><em>Origine</em></strong> -
			Utilizzare il menu a discesa <strong>Origine</strong> per selezionare il punto iniziale del traffico da consentire o impedire dall'interfaccia LAN o WAN.<br>
			<strong><em>Destinaz.</em></strong> -
			Utilizzare il menu a discesa <strong>Destinaz.</strong> per selezionare il punto finale del traffico da consentire o impedire dall'interfaccia LAN o WAN.<br>
			<strong><em>Indirizzo IP</em></strong> -
			È possibile specificare un singolo indirizzo IP di origine o di destinazione immettendolo nella casella superiore oppure specificare un intervallo di indirizzi IP immettendo il primo indirizzo IP dell'intervallo nella casella superiore e l'ultimo indirizzo IP nella casella inferiore.<br>
			<strong><em>Protocollo</em></strong> -
			Utilizzare il menu a discesa <strong>Protocollo</strong> per selezionare il tipo di traffico.<br>
			<strong><em>Intervallo porte</em></strong> -
			Immettere lo stesso numero di porte in entrambe le caselle per specificare una porta singola oppure immettere la prima porta nella casella superiore e l'ultima porta nella casella inferiore per specificare un intervallo di porte.<br>
			<strong><em>Pianificazione</em></strong> -
			Utilizzare il menu a discesa <strong>Sempre</strong> per selezionare una pianificazione definita in precedenza oppure fare clic sul pulsante <strong>Aggiungi nuova</strong> per aggiungere una nuova pianificazione.
 </p>
</td>
</tr>
</table>
</div>


<div class="box">
<a name="routing"><h2>Routing</h2></a>
<table>
<?if(query("/runtime/func/dis_routing")!="1"){
echo "<tr>\n";
echo "	<td height=99>\n";
echo "		L'opzione Routing consente di definire route statiche per destinazioni specifiche.<br>\n";
echo "		<strong><em>Abilita </em></strong> - Specifica se la voce sarà abilitata o disabilitata.<br>\n";
echo "		<strong><em>Interfaccia </em></strong> - Specifica l'interfaccia, ovvero WAN o WAN fisica, che il pacchetto \n";
echo "		IP deve utilizzare per essere trasmesso dal router quando si utilizza questa route.<br>\n";
echo "		<strong><em>Interfaccia (WAN)</em></strong> - Interfaccia utilizzata per ricevere dall'ISP \n";
echo "		l'indirizzo IP per accedere a Internet.<br>\n";
echo "		<strong><em>Interfaccia (WAN fisica)</em></strong> - Interfaccia utilizzata per ricevere dall'ISP \n";
echo "		l'indirizzo IP per accedere a Internet.<br>\n";
echo "		<strong><em>Destinazione </em></strong> -  Indirizzo IP dei pacchetti per i quali verrà utilizzata questa route.<br>\n";
echo "		<strong><em>Subnet mask </em></strong> -  I bit uno nella mask indicano quali bit dell'indirizzo \n";
echo "		IP devono corrispondere. <br>\n";
echo "		<strong><em>Gateway </em></strong> - Specifica l'hop successivo da utilizzare con questa route. \n";
echo "		Il gateway 0.0.0.0 indica l'assenza di un hop successivo, pertanto l'indirizzo IP corrispondente viene \n";
echo "		direttamente collegato al router sull'interfaccia specificata, ovvero WAN o WAN fisica. \n";
echo " </td>\n";
echo " </tr>\n";
}
?>
</table>
</div>


<div class="box">
<a name="advanced_wireless"><h2>Wireless avanzate</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=20>

 <p>Le opzioni di questa pagina devono essere modificate da utenti esperti o solo se richiesto da un tecnico del servizio di assistenza poiché se non vengono configurate correttamente possono influire negativamente sulle prestazioni del router.
 </p>
 <p><strong><em>Potenza di trasmissione - </em></strong>È possibile ridurre la potenza in uscita del dispositivo <?query("/sys/modelname");?> selezionando valori più bassi per Potenza di trasmissione dall'elenco a discesa. Le opzioni sono: 100%, 50%, 25% e 12,5%. </p>
 <p><strong><em>Intervallo beacon - </em></strong> I beacon sono pacchetti inviati da un punto di accesso per la sincronizzazione con la rete wireless. Specificare un valore compreso tra 20 e 1000 per l'intervallo beacon. Il valore predefinito è impostato su 100 millisecondi. </p>

 <p><strong><em>Soglia RTS - </em></strong> È consigliabile non modificare l'impostazione di default di questo valore, pari a 2346. Se si rileva un flusso di dati incoerente, si consiglia di apportare solo lievi modifiche all'intervallo di valori compreso tra 256 e 2346. Il valore di default per Soglia RTS è impostato su 2346. </p>
 <p><strong><em>Frammentazione - </em></strong> È consigliabile lasciare non modificare il valore di default di questa impostazione, pari a 2346. Se si nota una percentuale elevata di errori nei pacchetti, è possibile aumentare leggermente il valore di "Frammentazione" specificando un numero compreso tra 1500 e 2346. L'impostazione di un valore troppo basso per la frammentazione può causare un deterioramento delle prestazioni. </p>
 <p><strong><em>Intervallo DTIM - </em></strong> Immettere un valore compreso tra 1 e 255 per DTIM (Delivery Traffic Indication Message). Un DTIM è un conto alla rovescia che informa i client della finestra successiva per l'ascolto di messaggi broadcast e multicast. Una volta memorizzati nel buffer i messaggi broadcast o multicast per i client associati, il punto di accesso invia il DTIM successivo in base al valore dell'intervallo DTIM specificato. I client del punto di accesso ascoltano i beacon e si attivano in modo da ricevere i messaggi broadcast e multicast. Il valore di default per Intervallo DTIM è impostato su 1. </p>

 <p><strong><em>Tipo di preambolo - </em></strong>  Il tipo di preambolo definisce la lunghezza del blocco CRC (Cyclic Redundancy Check) per le comunicazioni tra il punto di accesso e le schede wireless di roaming. Assicurarsi di selezionare il tipo di preambolo appropriato e fare clic sul pulsante Applica. </p>
 <p><span class="style2">Nota: </span>nelle aree caratterizzate da un elevato traffico di rete è opportuno utilizzare il tipo di preambolo più breve. CRC è una tecnica comune per la rilevazione degli errori di trasmissione dati. </p>
 <p><strong><em>Modalità CTS - </em></strong>Selezionare Nessuno per disabilitare la funzionalità. Selezionare Sempre per forzare il router a richiedere a ogni dispositivo wireless della rete di eseguire un handshake RTS/CTS prima di consentire la trasmissione dei dati. Selezionare Automatico per fare in modo che sia il router a decidere quando è necessario l'handshake RTS/CTS. </p>
<?if(query("/runtime/func/ieee80211n")!="1"){
 echo "<p><strong><em>802.11g Only Mode - </em></strong>Enable this mode if your network is made up of purely 802.11g devices. If you have both 802.11b and 802.11g wireless clients, disable this mode. </p> </td>";
}?>
 </tr>
 </tr>
 </table>
 </div>
 
 
<div class="box">
<a name="advanced_network"><h2>Rete avanzata</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=20>

 <p>Questa sezione contiene le impostazioni che consentono di modificare la modalità di gestione di alcuni tipi di traffico da parte del router. Si consiglia di non modificare queste impostazioni a meno che non siano già note oppure non sia stato richiesto da un tecnico del servizio di assistenza.
 </p>

<!--
 <p><strong>VPN Passthrough </strong><br>The device supports VPN (Virtual Private Network) passthrough for PPTP (Point-to-Point Tunneling Protocol) and IPSec (IP Security). Once VPN passthrough is enabled, there is no need to create any Virtual Server or Port Forwarding entries in order for outbound VPN sessions to be established properly. Multiple VPN connections can be made through the device. This is useful when you have many VPN clients on the Local Area Network. </p>
-->

 <p><strong>UPnP </strong><br>UPnP è l'acronimo di Universal Plug and Play, un'architettura di rete che garantisce la compatibilità tra apparecchiature di rete, software e periferiche. Il dispositivo <?query("/sys/modelname");?> è un router abilitato per UPnP, pertanto è compatibile con altri dispositivi/software UPnP. Se non si desidera utilizzare la funzione UPnP, è possibile disabilitarla selezionato "Disabilitato".
 </p>
 <p><strong>Ping WAN </strong><br>Quando si abilita la risposta ping WAN, l'indirizzo IP pubblici della WAN (Wide Area Network) del dispositivo risponderà ai comandi ping inviati da utenti Internet. Il ping degli indirizzi IP pubblici della WAN viene in genere utilizzato dai pirati informatici per testare la validità dell'indirizzo IP della WAN.
 </p>
 <p><strong>Velocità porte WAN  </strong><br>Consente di selezionare la velocità dell'interfaccia WAN del dispositivo <?query("/sys/modelname");?>. Scegliere tra 100 Mbps, 10 Mbps o 10/100/1000 Mbps auto.
 </p>

<!--
 <p><strong>Gaming Mode </strong><br>If you are experiencing difficulties when playing online games or even certain applications that use voice data, you may need to enable Gaming Mode in order for these applications to work correctly. When not playing games or using these voice applications, it is recommended that Gaming Mode is disabled. </p>
--> 

<?if(query("/runtime/func/dis_multicast_stream")!="1"){
echo " <p><strong>Flussi multicast</strong><br>Abilitare questa opzione per consentire un passaggio più efficiente del traffico multicast da Internet alla rete. </p> </td>\n";
}
?>

 </tr>
<!--
<?if(query("/runtime/func/dis_multicast_stream")!="1"){
echo "<tr><td height=20>&nbsp;</td></tr>\n";
echo "<tr>\n";
echo "	<td height=20>\n";
echo "		<p>\n";
echo "			<strong>Multicast Streams</strong><br>\n";
echo "			Enable this option if you are receiving a Video On Demand type service from the Internet.\n";
echo "			The router uses the IGMP protocol to support efficient multicasting -- transmission of identical content,\n";
echo "			such as multimedia, from a source to a number of recipients.\n"; 
echo "			This option must be enabled if any applications on the LAN participate in a multicast group.\n"; 
echo "			If you have a multimedia LAN application that is not receiving content as expected, try enabling this option.\n";
echo "		</p>\n";
echo "	</td>\n";
echo "</tr>\n";
}
?>
--> 
</table>
</div>
 

<div class="box">
<a name="guest_zone"><h2>Zona guest</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			Selezione zona guest<br>
			La selezione consente di definire la scala della zona guest.<br>
			<strong><em>Abilita zona guest</em></strong>  - Specifica se la zona guest sarà abilitata o disabilitata.<br>
			<strong><em>Includi porta LAN</em></strong> -  Specifica la porta LAN che verrà inclusa nella zona guest. <br>
			<strong><em>Includi wireless</em></strong> -  Specifica se utilizzare o meno una zona wireless aggiuntiva per la zona guest. <br>
			<strong><em>Nome rete wireless</em></strong> -  Specificare un nome per la rete wireless della zona guest. <br>
		</p>
		<p>
			<strong><em>Modalità di protezione wireless</em></strong><br>
			È importante proteggere la rete wireless perché viene utilizzata per salvaguardare l'integrità delle informazioni trasmesse tramite la rete wireless. Il dispositivo <?query("/sys/modelname");?> supporta quattro tipi di protezione wireless: WEP, solo WPA, solo WPA2 e WPA/WPA2 (rilevazione automatica).
		 <br>
		</p>
		<p>
			<strong><em>WEP</em></strong><br>
			WEP (Wired Equivalent Protocol) è un protocollo di protezione wireless per reti WLAN (Wireless Local Area Network). Per garantire la protezione, WEP crittografa i dati inviati tramite la WLAN. Il dispositivo <?query("/sys/modelname");?> supporta due livelli di crittografia WEP: a 64 bit e a 128 bit. Per default il protocollo WEP è disabilitato. È possibile modificarne l'impostazione per adattarla a una rete wireless esistente oppure per personalizzare la rete wireless in uso.
		 <br>
		</p>
		<p>
			<strong><em>Autenticazione</em></strong> - Per autenticazione si intende il processo in base al quale il dispositivo <?query("/sys/modelname");?> verifica l'identità di un dispositivo di rete che tenta di accedere alla rete wireless. Quando si utilizza il protocollo WEP, sono disponibili due tipi di autenticazione per questo dispositivo.<br>
			<strong><em>Sistema aperto</em></strong> -Selezionare questa opzione per consentire a tutti i dispositivi wireless di comunicare con il dispositivo <?query("/sys/modelname");?> prima che venga richiesta la chiave di crittografia necessaria per accedere alla rete. <br>
			<strong><em>Chiave condivisa </em></strong> -  Selezionare questa opzione per richiedere a qualsiasi dispositivo wireless che tenta di comunicare con il dispositivo <?query("/sys/modelname");?> di fornire la chiave di crittografia necessaria per accedere alla rete prima di consentire le comunicazioni con <?query("/sys/modelname");?>. <br>
			<strong><em>Crittografia WEP</em></strong> - Selezionare il livello di crittografia WEP da utilizzare nella rete. I due livelli supportati sono 64 bit e 128 bit.<br>
			<strong><em>Tipo chiave </em></strong> - I tipi di chiave supportati dal dispositivo <?query("/sys/modelname");?> sono HEX (Hexadecimal) e ASCII (American Standard Code for Information Interchange). È possibile modificare il tipo di chiave per adattarlo a una rete wireless esistente oppure per personalizzare la rete wireless in uso. <br>
			<strong><em>Chiavi</em></strong> - Le chiavi da 1 a 4 consentono di modificare facilmente le impostazioni di crittografia wireless per garantire la protezione della rete. È sufficiente selezionare la chiave specifica da utilizzare per crittografare i dati wireless nella rete. <br>
		</p>
		<p>
			<strong><em>WPA personale</em></strong><br>
			WPA (Wi-Fi Protected Access) consente di autorizzare e autenticare gli utenti nella rete wireless. Utilizza un livello di protezione più elevato rispetto a WEP e si basa su una chiave che cambia automaticamente a intervalli regolari.
		 <br>
		</p>
		<p>
			<strong><em>Tipo di cifratura</em></strong> - Quando il tipo di protezione utilizzato è WPA, il dispositivo <?query("/sys/modelname");?> supporta due diversi tipi di cifratura, ovvero TKIP (Temporal Key Integrity Protocol) e AES (Advanced Encryption Standard). <br>
			<strong><em>PSK/EAP</em></strong> -Quando si seleziona PSK, i client wireless devono fornire una passphrase per l'autenticazione. Quando si seleziona EAP, sarà necessario disporre nella rete di un server RADIUS che gestirà l'autenticazione di tutti i client wireless. <br>
			<strong><em>Passphrase </em></strong> - Viene utilizzata dai client wireless per comunicare con il dispositivo <?query("/sys/modelname");?> quando è selezionata l'opzione PSK. Immettere da 8 a 63 caratteri alfanumerici. Assicurarsi di prendere nota della passphrase perché sarà necessario immetterla in qualsiasi altro dispositivo wireless che si tenta di aggiungere alla rete. <br>
			<strong><em>802.1X </em></strong> - Questo tipo di autenticazione WPA viene utilizzato congiuntamente a un server RADIUS che deve essere presente nella rete. Immettere l'indirizzo IP, la porta e il segreto condiviso per i quali è configurato il server RADIUS. È inoltre possibile scegliere di immettere le informazioni per un secondo server RADIUS qualora nella rete ne vengano utilizzati due per autenticare i client wireless. <br>
		</p>
		<p>
			<strong><em>WPA2</em></strong><br>
			WPA (Wi-Fi Protected Access) 2 consente di autorizzare e autenticare gli utenti nella rete wireless. Utilizza un livello di protezione più elevato rispetto a WEP e si basa su una chiave che cambia automaticamente a intervalli regolari.
		 <br>
		</p>
		<p>
			<strong><em>Tipo di cifratura </em></strong> - Quando il tipo di protezione utilizzato è WPA, il dispositivo <?query("/sys/modelname");?> supporta due diversi tipi di cifratura, ovvero TKIP (Temporal Key Integrity Protocol) e AES (Advanced Encryption Standard). <br>
			<strong><em>PSK/EAP</em></strong> - Quando si seleziona PSK, i client wireless devono fornire una passphrase per l'autenticazione. Quando si seleziona EAP, sarà necessario disporre nella rete di un server RADIUS che gestirà l'autenticazione di tutti i client wireless. <br>
			<strong><em>Passphrase</em></strong> - Viene utilizzata dai client wireless per comunicare con il dispositivo <?query("/sys/modelname");?> quando è selezionata l'opzione PSK. Immettere da 8 a 63 caratteri alfanumerici. Assicurarsi di prendere nota della passphrase perché sarà necessario immetterla in qualsiasi altro dispositivo wireless che si tenta di aggiungere alla rete. <br>
			<strong><em>802.1X </em></strong> - Questo tipo di autenticazione WPA2 viene utilizzato congiuntamente a un server RADIUS che deve essere presente nella rete. Immettere l'indirizzo IP, la porta e il segreto condiviso per i quali è configurato il server RADIUS. È inoltre possibile scegliere di immettere le informazioni per un secondo server RADIUS qualora nella rete ne vengano utilizzati due per autenticare i client wireless. <br>
		</p>
		<p>
			<strong><em>WPA2-Auto</em></strong> <br>
			Questa opzione consente la connessione simultanea di client WPA2 e WPA al dispositivo <?query("/sys/modelname");?>.<br>
		</p>
		<p>
			<strong><em>Configurazione LAN per zona guest</em></strong><br> 
			Impostazioni dell'interfaccia LAN (Local Area Network) della zona guest per il dispositivo. Tali impostazioni possono essere definite come "impostazioni private". Se necessario, è possibile modificare l'indirizzo IP. L'indirizzo IP è privato, ovvero riservato alla rete interna, pertanto non è visibile in Internet. L'indirizzo IP di default è 192.168.1.1, mentre la subnet mask è 255.255.255.0.
			<br>
		</p>
		<p>
			<strong><em>Indirizzo IP</em></strong> - Il valore dell'indirizzo IP di default del dispositivo <?query("/sys/modelname");?> è 192.168.1.1. <br>
			<strong><em>Subnet mask</em></strong> - Il valore della subnet mask di default del dispositivo <?query("/sys/modelname");?> è 255.255.255.0. <br>
		</p>
		<p>
			<strong><em>Abilita isolamento client zona guest</em></strong> : <br>
			Abilitare la funzione per impedire a un client guest di accedere ad altri client nella zona guest. Il client guest può accedere solo a Internet.
			 <br>
		</p>
		<p>
			<strong><em>Abilita routing tra le zone</em></strong> : <br>
			In questa sezione è possibile abilitare il routing tra la zona host e la zona guest. Se la funzione non è abilitata, i client guest non possono accedere ai dati dei client host.
		 <br>
		</p>
		<p>
			<strong><em>Server DHCP per zona guest</em></strong> <br>
			DHCP è l'acronimo di Dynamic Host Control Protocol. Il server DHCP assegna gli indirizzi IP ai dispositivi della rete che li richiedono. Tali dispositivi devono essere impostati su "Ottieni automaticamente un indirizzo IP". Per default, il server DHCP è abilitato nel dispositivo <?query("/sys/modelname");?>. Il pool di indirizzi DHCP contiene l'intervallo degli indirizzi IP che verranno assegnati automaticamente ai clienti in rete.
		 <br>
		</p>
		<p>
			<strong><em>Indirizzo IP iniziale</em></strong> - Indirizzo IP iniziale per l'assegnazione degli indirizzi IP del server DHCP. <br>
			<strong><em>Indirizzo IP finale </em></strong> - Indirizzo IP finale per l'assegnazione degli indirizzi IP del server DHCP. <br>
			<strong><em>Tempo di validità</em></strong> -Intervallo di validità dell'indirizzo IP espresso in minuti. Le informazioni relative ai computer client DHCP connessi all'unità verranno visualizzate nella tabella dei client DHCP dinamici. In tale tabella saranno indicati il nome host, l'indirizzo IP, l'indirizzo MAC e l'ora di scadenza dell'intervallo di validità DHCP per ogni computer client. <br>
		</p>
</td>
</tr>
</table>
</div>
 
<div class="box">
<a name="wake_on_lan"><h2>Wake on LAN</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			È possibile utilizzare la funzionalità Wake on LAN per accendere a distanza un PC collegato al lato LAN del router. Specificare la porta UDP che verrà utilizzata dal "pacchetto magico" Wake on LAN per impedire al router di considerare la richiesta Wake on LAN un attacco ostile e conseguentemente di bloccarla.
			<br>
			<br>
			<strong><em>Porta UDP</em></strong> - 
			Speciale porta che verrà utilizzata dal dispositivo <?query("/sys/modelname");?> per rimanere in ascolto dei "pacchetti magici" per l'accensione del PC.<br>
			<strong><em>Interfaccia</em></strong> - 
			( Impostazione non modificabile. Questa impostazione potrà essere modificabile in versioni successive del firmware.).<br>		
		</p>
	</td>
</tr>
</table>
</div>
