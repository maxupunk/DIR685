<div class="box">
<a name="internet_setup"><h2>Configurazione Internet</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=40>
		<p>
			Se si sta configurando il dispositivo per la prima volta, si consiglia di fare clic su Configurazione guidata connessione Internet e di seguire le istruzioni visualizzate. Per modificare o configurare manualmente le impostazioni del dispositivo, fare clic su Configurazione manuale connessione Internet.
		</p>
	</td>
</tr>
<tr>
	<td height=59>
		<p>
			<strong>Avvia Configurazione guidata connessione Internet </strong><br>
			Fare clic su questo pulsante per eseguire una procedura strutturata in pochi passi che consentirà di connettere il router a Internet.
			<br>
			<strong>Avvia Configurazione guidata protezione wireless </strong><br>
			Fare clic su questo pulsante per eseguire una procedura strutturata in pochi passi che consentirà di configurare le impostazioni della rete wireless, inclusa la protezione.
		</p>
	</td>
</tr>
<tr><td height=32>&nbsp;</td></tr>
<tr>
	<td height=46>
		<p>
			<strong>Configurazione manuale connessione Internet</strong><br>
			Scegliere questa opzione se si desidera specificare manualmente le impostazioni necessarie per connettere il router a Internet.
			<br>
			<strong>Modalità punto di accesso</strong><br>
			Se si abilita l'opzione "Modalità punto di accesso", il dispositivo funzionerà in modo analogo a un punto di accesso wireless. Tutte le funzioni NAT verranno disabilitate ad eccezione di quelle correlate alla connessione wireless.
			<br>
			<strong>Tipo di connessione Internet  </strong><br>
			Le informazioni visualizzate in Impostazioni connessione Internet vengono utilizzati per connettere il dispositivo <?query("/sys/modelname");?> a Internet. Tutte le informazioni da immettere in questa pagina verranno fornite dall'ISP e vengono spesso definite "impostazioni pubbliche". Selezionare l'opzione appropriata per l'ISP specifico. Se non si è certi dell'opzione da selezionare, contattare l'ISP.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=61>
		<p>
			<strong>Indirizzo IP statico</strong><br>
			Selezionare questa opzione se l'ISP (Internet Service Provider) ha fornito i valori per l'indirizzo IP, la subnet mask, il gateway di default e l'indirizzo del server DNS. Immettere queste informazioni nei campi appropriati. Se non si è certi dei valori da immettere in questi campi, contattare l'ISP.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=142>
		<p>
			<strong>Indirizzo IP dinamico</strong><br>
			Selezionare questa opzione se l'ISP (Internet Service Provider) fornisce automaticamente un indirizzo IP. I fornitori di modem cavo utilizzano in genere l'assegnazione dinamica degli indirizzi IP.
		</p>
		<p>
			<strong><em>Nome host </em></strong> (facoltativo) -
			 Il campo Nome host è facoltativo ma può essere richiesto da alcuni ISP (Internet Service Provider). Il nome host di default corrisponde al numero di modello del router.<br>
			<strong><em>Indirizzo MAC </em></strong> (facoltativo) -
			Il campo Indirizzo MAC è richiesto da alcuni ISP (Internet Service Provider). L'indirizzo MAC di default è impostato sull'indirizzo MAC dell'interfaccia WAN del dispositivo <?query("/sys/modelname");?>. È possibile utilizzare il pulsante "Clona indirizzo MAC" per copiare automaticamente l'indirizzo MAC della scheda Ethernet installata nel computer utilizzato per configurare il dispositivo. È necessario compilare questo campo solo se richiesto dall'ISP.<br>
			<strong><em>Indirizzo DNS primario </em></strong> -
			Immettere l'indirizzo IP del server DNS (Domain Name Service) primario fornito dall'ISP.<br>
			<strong><em>Indirizzo DNS secondario </em></strong> (facoltativo) -
			Immettere in questo campo l'indirizzo IP di un eventuale server DNS secondario ricevuto dall'ISP.<br>
			<strong><em>MTU </em></strong> -
			Per MTU (Maximum Transmission/Transfer Unit) si intende la dimensione massima di un pacchetto che è possibile trasmettere nella rete. I messaggi di dimensioni maggiori rispetto a MTU vengono divisi in pacchetti più piccoli. Il valore di default per questa opzione è 1500. La modifica di questo valore potrebbe compromettere le prestazioni del router. Modificare questo valore solo se richiesto da un addetto del supporto tecnico D-Link o dall'ISP.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=47>
		<p>
			<strong>PPPoE</strong><br>
			Selezionare questa opzione se l'ISP richiede l'utilizzo di una connessione PPPoE (Point to Point Protocol over Ethernet) per accedere a Internet. Questa opzione viene in genere utilizzata dai provider DSL. Selezionare PPPoE dinamico per ottenere automaticamente un indirizzo IP per la connessione PPPoE (utilizzato dalla maggioranza delle connessioni PPPoE). Selezionare PPPoE statico per utilizzare un indirizzo IP statico per la connessione PPPoE.
		</p>
		<p>
			<strong><em>Nome utente </em></strong> - Immettere il proprio nome utente PPPoE.<br>
			<strong><em>Password  </em></strong> - Immettere la propria password PPPoE.<br>
			<strong><em>Nome servizio </em></strong> (facoltativo) -
			Immettere in questo campo il nome dell'eventuale servizio utilizzato dall'ISP per la connessione PPPoE.<br>
			<strong><em>Indirizzo IP </em></strong> -
			Questa opzione è disponibile solo per PPPoE statico. Immettere nel campo l'indirizzo IP statico per la connessione PPPoE.<br>
			<strong><em>Indirizzo MAC </em></strong> (facoltativo) -
			 Il campo Indirizzo MAC è richiesto da alcuni ISP (Internet Service Provider). L'indirizzo MAC di default è impostato sull'indirizzo MAC dell'interfaccia WAN del dispositivo <?query("/sys/modelname");?>. È possibile utilizzare il pulsante "Clona indirizzo MAC" per copiare automaticamente l'indirizzo MAC della scheda Ethernet installata nel computer utilizzato per configurare il dispositivo. È necessario compilare questo campo solo se richiesto dall'ISP.<br>
			<strong><em>Indirizzo DNS primario </em></strong> -
			 Indirizzo IP del server DNS (Domain Name System) primario, che può essere fornito dall'ISP. È necessario immettere queste informazioni solo se è stata selezionata l'opzione PPPoE statico. Se è stato scelto PPPoE dinamico, lasciare il campo impostato sul valore di default perché queste informazioni verranno fornite automaticamente dall'ISP.<br>
			<strong><em>Indirizzo DNS secondario </em></strong> (facoltativo) -
			 Immettere in questo campo l'indirizzo IP di un eventuale server DNS secondario ricevuto dall'ISP.<br>
			<strong><em>Tempo massimo di inattività </em></strong> -
			Periodo di inattività (in minuti) prima che il dispositivo disconnetta la sessione PPPoE. Immettere un valore in minuti per definire il tempo massimo durante il quale la connessione Internet viene mantenuta in caso di inattività. Se la connessione rimane inattiva per un periodo più lungo rispetto a quello definito in Tempo massimo di inattività, la connessione verrà interrotta. Questa opzione si applica solo alla modalità Connessione a richiesta.<br>
			<strong><em>MTU </em></strong> -
			Per MTU (Maximum Transmission/Transfer Unit) si intende la dimensione massima di un pacchetto che è possibile trasmettere nella rete. I messaggi di dimensioni maggiori rispetto a MTU vengono divisi in pacchetti più piccoli. Il valore di default per questa opzione è 1492. La modifica di questo valore potrebbe compromettere le prestazioni del router. Modificare questo valore solo se richiesto da un addetto del supporto tecnico D-Link o dall'ISP.<br>
			<strong><em>Selezione modalità di connessione</em></strong> -
			Selezionare Sempre attivo se si desidera che il router non disconnetta mai la sessione PPPoE. Selezionare Manuale se si desidera controllare la connessione/disconnessione del router da Internet. L'opzione Connessione a richiesta consente al router di stabilire una connessione a Internet solo quando un dispositivo della rete tenta di accedere a una risorsa disponibile in Internet.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>PPTP</strong><br>
			Selezionare questa opzione se l'ISP utilizza una connessione PPTP (Point to Point Tunneling Protocol) e ha assegnato un nome utente e una password per l'accesso a Internet. Selezionare PPTP dinamico per ottenere automaticamente un indirizzo IP per la connessione PPTP. Selezionare PPTP statico per utilizzare un indirizzo IP statico per la connessione PPTP.
		</p>
		<p>
			<strong><em>Indirizzo IP </em></strong> -  Immettere l'indirizzo IP assegnato dall'ISP.<br>
			<strong><em>Subnet mask </em></strong> - Immettere la subnet mask assegnata dall'ISP.<br>
			<strong><em>Gateway </em></strong> -  Immettere l'indirizzo IP del gateway assegnato dall'ISP.<br>
			<strong><em>DNS - </em></strong>Immettere l'indirizzo DNS assegnato dall'ISP.<br>
			<strong><em>IP server </em></strong> -
			 Immettere l'indirizzo IP del server che verrà fornito dall'ISP a cui si effettua la connessione.<br>
			<strong><em>Account  </em></strong> -  Immettere il proprio nome utente PPTP.<br>
			<strong><em>Password </em></strong> - Immettere la propria password PPTP.<br>
			<strong><em>Tempo massimo di inattività </em></strong> -
			Periodo di inattività prima che il dispositivo disconnetta la sessione PPTP. Immettere un valore in minuti per definire il tempo massimo durante il quale la connessione Internet viene mantenuta in caso di inattività. Se la connessione rimane inattiva per un periodo più lungo rispetto a quello specificato in Tempo massimo di inattività, la connessione verrà interrotta. Questa opzione si applica solo alla modalità Connessione a richiesta.<br>
			<strong><em>MTU </em></strong> -
			Per MTU (Maximum Transmission/Transfer Unit) si intende la dimensione massima di un pacchetto che è possibile trasmettere nella rete. I messaggi di dimensioni maggiori rispetto a MTU vengono divisi in pacchetti più piccoli. Il valore di default per questa opzione è 1400. La modifica di questo valore potrebbe compromettere le prestazioni del router. Modificare questo valore solo se richiesto da un addetto del supporto tecnico D-Link o dall'ISP.<br>
			<strong><em>Selezione modalità di connessione</em></strong> -
			Selezionare Sempre attivo se si desidera che il router non disconnetta mai la sessione PPTP. Selezionare Manuale se si desidera controllare la connessione/disconnessione del router da Internet. L'opzione Connessione a richiesta consente al router di stabilire una connessione a Internet solo quando un dispositivo della rete tenta di accedere a una risorsa disponibile in Internet.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>L2TP </strong><br>
			Selezionare questa opzione se l'ISP utilizza una connessione L2TP (Layer 2 Tunneling Protocol) e ha assegnato un nome utente e una password per l'accesso a Internet. Selezionare L2TP dinamico per ottenere automaticamente un indirizzo IP per la connessione L2TP. Selezionare L2TP statico per utilizzare un indirizzo IP statico per la connessione L2TP.
		</p>
		<p>
			<strong><em>Indirizzo IP </em></strong> - Immettere l'indirizzo IP assegnato dall'ISP.<br>
			<strong><em>Subnet mask </em></strong> - Immettere la subnet mask assegnata dall'ISP.<br>
			<strong><em>Gateway</em></strong> - Immettere l'indirizzo IP del gateway assegnato dall'ISP.<br>
			<strong><em>DNS</em></strong> - Immettere l'indirizzo DNS assegnato dall'ISP.<br>
			<strong><em>IP server </em></strong> -
			Immettere l'indirizzo IP del server che verrà fornito dall'ISP a cui si effettua la connessione.<br>
			<strong><em>Account L2TP </em></strong> - Immettere il proprio nome utente L2TP.<br>
			<strong><em>Password L2TP </em></strong> - Immettere la propria password L2TP.<br>
			<strong><em>Tempo massimo di inattività </em></strong> -
			Periodo di inattività (in minuti) prima che il dispositivo disconnetta la sessione L2TP. Immettere un valore in minuti per definire il tempo massimo durante il quale la connessione Internet viene mantenuta in caso di inattività. Se la connessione rimane inattiva per un periodo più lungo rispetto a quello definito in Tempo massimo di inattività, la connessione verrà interrotta. Questa opzione si applica solo alla modalità Connessione a richiesta.<br>
			<strong><em>MTU</em></strong> -
			Per MTU (Maximum Transmission/Transfer Unit) si intende la dimensione massima di un pacchetto che è possibile trasmettere nella rete. I messaggi di dimensioni maggiori rispetto a MTU vengono divisi in pacchetti più piccoli. Il valore di default per questa opzione è 1400. La modifica di questo valore potrebbe compromettere le prestazioni del router. Modificare questo valore solo se richiesto da un addetto del supporto tecnico D-Link o dall'ISP.
			<strong><em>Selezione modalità di connessione</em></strong> -
			Selezionare Sempre attivo se si desidera che il router non disconnetta mai la sessione L2TP. Selezionare Manuale se si desidera controllare la connessione/disconnessione del router da Internet. L'opzione Connessione a richiesta consente al router di stabilire una connessione a Internet solo quando un dispositivo della rete tenta di accedere a una risorsa disponibile in Internet.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>PPTP Russia (Dual Access)</strong><br>
			Per configurare una connessione Internet PPTP per la Russia, utilizzare la procedura di configurazione per le connessioni PPTP descritta in precedenza. Se l'ISP deve configurare un'eventuale route statica, fare riferimento alla funzione "Routing" nel menu "AVANZATE" per ulteriori opzioni di configurazione.

		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>PPPoE Russia (Dual Access)</strong><br>
			Alcune connessioni PPPoE utilizzano una route IP statica all'ISP in aggiunta alle impostazione IP globali della connessione. Ciò comporta un ulteriore passaggio per definire le impostazioni IP relative alla porta WAN fisica. Per configurare una connessione Internet PPPoE per la Russia, utilizzare la procedura di configurazione per le connessioni PPPoE descritta in precedenza e aggiungere le impostazioni IP relative alla porta WAN fisica come specificato dall'ISP. Se l'ISP deve configurare un'eventuale route statica, fare riferimento alla funzione "Routing" nel menu "AVANZATE" per ulteriori opzioni di configurazione.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="wireless_setup"><h2>Configurazione wireless</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			La pagina Configurazione wireless contiene le impostazioni relative alla parte (Punto di accesso) del dispositivo <?query("/sys/modelname");?>. Questa pagina consente di personalizzare la rete wireless o di configurare il dispositivo <?query("/sys/modelname");?> per adattare una rete wireless esistente già configurata.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Configurazione Wi-Fi protetta (denominata anche WCN 2.0 in Windows Vista)</strong><br>
			Questa funzionalità offre agli utenti un metodo più intuitivo per configurare la protezione wireless. È disponibile in due formati, ovvero numero PIN e pulsante. L'immissione del numero PIN fornito con il dispositivo nell'utilità della scheda o nell'utilità del client wireless di Windows Vista, se per la scheda wireless è disponibile un driver Windows Vista certificato, consente di configurare automaticamente la protezione wireless tra il router e il client. Per poter utilizzare questa funzionalità, la scheda wireless deve supportare uno dei due formati previsti dalla Configurazione Wi-Fi protetta.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Nome rete wireless</strong><br>
			Noto anche come SSID (Service Set Identifier), si tratta del nome della WLAN (Wireless Local Area Network). Per default il SSID del dispositivo <?query("/sys/modelname");?> è "dlink", ma può essere facilmente modificato per definire una nuova rete wireless oppure per aggiungere il dispositivo <?query("/sys/modelname");?> a una rete wireless esistente.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Canale wireless</strong><br>
			Indica il canale su cui opera il dispositivo <?query("/sys/modelname");?>. Per default, il canale è impostato su 6, ma è possibile modificarne l'impostazione per adattarla a una rete wireless esistente oppure per personalizzare la nuova rete wireless. Selezionare la casella di controllo Abilita scansione automatica canali per selezionare automaticamente il canale su cui opera il dispositivo <?query("/sys/modelname");?>. Questa opzione è consigliata perché il router sceglie il canale con meno interferenze.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>	
 		<p>
 			<strong>Velocità di trasmissione (TX)</strong><br>
 			Selezionare le velocità di trasmissione di base sulla base della velocità delle schede wireless della WLAN (Wireless Local Area Network).
 		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>WMM</strong><br>
			Selezionare Abilita per attivare QoS per l'interfaccia wireless del dispositivo <?query("/sys/modelname");?>.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Abilita wireless nascosta </strong><br>
			Selezionare Abilitato se si desidera che il SSID della rete wireless non venga trasmesso dal dispositivo <?query("/sys/modelname");?>. Se questa opzione è impostata su Abilitato, il SSID del dispositivo <?query("/sys/modelname");?> non verrà rilevato dalle utility di Site Survey, pertanto, per consentire la connessione al router, durante la configurazione dei client wireless sarà necessario conoscere il SSID del dispositivo <?query("/sys/modelname");?> e immetterlo manualmente. Per default, questa opzione è abilitata.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Modalità di protezione wireless</strong><br>
			È importante proteggere la rete wireless perché viene utilizzata per salvaguardare l'integrità delle informazioni trasmesse tramite la rete wireless. Il dispositivo <?query("/sys/modelname");?> supporta quattro tipi di protezione wireless: WEP, solo WPA, solo WPA2 e WPA/WPA2 (rilevazione automatica).
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>WEP </strong><br>
			WEP (Wired Equivalent Protocol) è un protocollo di protezione wireless per reti WLAN (Wireless Local Area Network). Per garantire la protezione, WEP crittografa i dati inviati tramite la WLAN. Il dispositivo <?query("/sys/modelname");?> supporta due livelli di crittografia WEP: a 64 bit e a 128 bit. Per default il protocollo WEP è disabilitato. È possibile modificarne l'impostazione per adattarla a una rete wireless esistente oppure per personalizzare la rete wireless in uso.
		</p>
		<p>
			<strong><em>Autenticazione</em></strong> -
			Per autenticazione si intende il processo in base al quale il dispositivo <?query("/sys/modelname");?> verifica l'identità di un dispositivo di rete che tenta di accedere alla rete wireless. Quando si utilizza il protocollo WEP, sono disponibili due tipi di autenticazione per questo dispositivo.<br> 
			<strong><em>Sistema aperto</em></strong> -
			Selezionare questa opzione per consentire a tutti i dispositivi wireless di comunicare con il dispositivo <?query("/sys/modelname");?> prima che venga richiesta la chiave di crittografia necessaria per accedere alla rete.<br>
			<strong><em>Chiave condivisa</em></strong> -
			Selezionare questa opzione per richiedere a qualsiasi dispositivo wireless che tenta di comunicare con il dispositivo <?query("/sys/modelname");?> di fornire la chiave di crittografia necessaria per accedere alla rete prima di consentire le comunicazioni con <?query("/sys/modelname");?>.<br>
			<strong><em>Crittografia WEP</em></strong> -
			Selezionare il livello di crittografia WEP da utilizzare nella rete. I due livelli supportati sono 64 bit e 128 bit.<br>
			<strong><em>Tipo chiave</em></strong> -
			I tipi di chiave supportati dal dispositivo <?query("/sys/modelname");?> sono HEX (Hexadecimal) e ASCII (American Standard Code for Information Interchange). È possibile modificare il tipo di chiave per adattarlo a una rete wireless esistente oppure per personalizzare la rete wireless in uso.<br>
			<strong><em>Chiavi</em></strong> -
			Le chiavi da 1 a 4 consentono di modificare facilmente le impostazioni di crittografia wireless per garantire la protezione della rete. È sufficiente selezionare la chiave specifica da utilizzare per crittografare i dati wireless nella rete.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>WPA/WPA2</strong><br>
			WPA (Wi-Fi Protected Access) o WPA2 consente di autorizzare e autenticare gli utenti nella rete wireless. Utilizza un livello di protezione più elevato rispetto a WEP e si basa su una chiave che cambia automaticamente a intervalli regolari.
		</p>
		<p>
			<strong><em>Tipo di cifratura</em></strong> -
			Quando il tipo di protezione utilizzato è WPA, il dispositivo <?query("/sys/modelname");?> supporta due diversi tipi di cifratura, ovvero TKIP (Temporal Key Integrity Protocol) e AES (Advanced Encryption Standard).<br>
			<strong><em>PSK/EAP</em></strong> -
			Quando si seleziona PSK, i client wireless devono fornire una passphrase per l'autenticazione. Quando si seleziona EAP, sarà necessario disporre nella rete di un server RADIUS che gestirà l'autenticazione di tutti i client wireless.<br>
			<strong><em>Passphrase</em></strong> -
			Viene utilizzata dai client wireless per comunicare con il dispositivo <?query("/sys/modelname");?>. Quando è selezionata l'opzione PSK, immettere da 8 a 63 caratteri alfanumerici. Assicurarsi di prendere nota della passphrase perché sarà necessario immetterla in qualsiasi altro dispositivo wireless che si tenta di aggiungere alla rete.<br>
			<strong><em>802.1X</em></strong> -
			Questo tipo di autenticazione WPA viene utilizzato congiuntamente a un server RADIUS che deve essere presente nella rete. Immettere l'indirizzo IP, la porta e il segreto condiviso per i quali è configurato il server RADIUS. È inoltre possibile scegliere di immettere le informazioni per un secondo server RADIUS qualora nella rete ne vengano utilizzati due per autenticare i client wireless.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="lan_setup"><h2>Configurazione rete</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			Impostazioni dell'interfaccia LAN (Local Area Network) del dispositivo. Tali impostazioni possono essere definite come "impostazioni private". Se necessario, è possibile modificare l'indirizzo IP della LAN. L'indirizzo IP della LAN è privato, ovvero riservato alla rete interna IP, pertanto non è visibile in Internet. L'indirizzo IP di default è 192.168.0.1, mentre la subnet mask è 255.255.255.0.
			<br><br>
			<strong><em>Indirizzo IP</em></strong> -
			Il valore dell'indirizzo IP di default del dispositivo <?query("/sys/modelname");?> è 192.168.0.1.<br>
			<strong><em>Subnet mask</em></strong> -
			Il valore della subnet mask di default del dispositivo <?query("/sys/modelname");?> è 255.255.255.0.<br>
			<strong><em>Nome di dominio locale</em></strong> (facoltativo) - Immettere il nome di dominio locale per la rete.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong><em>Relay DNS</em></strong> -
			Quando il relay DNS è abilitato, ai client DHCP del router verrà assegnato l'indirizzo IP LAN del router del rispettivo server DNS. Tutte le richieste DNS ricevute dal router verranno inoltrate ai server DNS dell'ISP. Quando il relay DNS è disabilitato, a tutti i client DHCP del router verrà assegnato il server DNS dell'ISP.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Server DHCP</strong><br>
			DHCP è l'acronimo di Dynamic Host Control Protocol. Il server DHCP assegna gli indirizzi IP ai dispositivi della rete che li richiedono. Tali dispositivi devono essere impostati su "Ottieni automaticamente un indirizzo IP". Per default, il server DHCP è abilitato nel dispositivo <?query("/sys/modelname");?>. Il pool di indirizzi DHCP contiene l'intervallo degli indirizzi IP che verranno assegnati automaticamente ai clienti in rete.
		</p>
		<p>
			<strong>Prenotazione DHCP</strong><br>
			Immettere manualmente il "Nome computer", l'"Indirizzo IP" e l'"Indirizzo MAC" relativi al PC al quale si desidera che il router assegni lo stesso IP in modo statico oppure scegliere il PC dal menu a discesa in cui sono elencati i clienti DHCP correnti.
		</p>
		<p>
			<strong><em>Indirizzo IP iniziale</em></strong> Indirizzo IP iniziale per l'assegnazione degli indirizzi IP del server DHCP.<br>
			<strong><em>Indirizzo IP finale</em></strong> Indirizzo IP finale per l'assegnazione degli indirizzi IP del server DHCP.<br>
			<strong><em>Tempo di validità</em></strong> Intervallo di validità dell'indirizzo IP espresso in minuti.
		</p>
		<p>
			Le informazioni relative ai computer client DHCP connessi all'unità verranno visualizzate nella tabella dei client DHCP dinamici. In tale tabella saranno indicati il nome host, l'indirizzo IP, l'indirizzo MAC e l'ora di scadenza dell'intervallo di validità DHCP per ogni computer client.
		</p>
	</td>
</tr>
</table>
</div>

<div class="box">
<a name="lcd_setup"><h2>Configurazione LCD</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			Nella pagina Configurazione LCD è possibile controllare le impostazioni del pannello del display del dispositivo <?query("/sys/modelname");?>. In questa pagina è possibile controllare lo screen saver e regolare l'intervallo di inattività del dispositivo prima dello spegnimento dello schermo LCD.
			<br><br>
			<strong><em>Impostazione screen saver</em></strong> -
			Se è attivato lo screen saver l'immagine "screen_bg.jpg" memorizzata nella directory radice del disco fisso interno viene visualizzata in background con la data e l'ora che si spostano in modo casuale sopra l'immagine. Se l'immagine non viene trovata, verrà visualizzato uno sfondo nero. L'impostazione "Timeout" indica l'intervallo in minuti prima che venga attivata la modalità screen saver quando il dispositivo rimane inattivo. Il dispositivo esce dalla modalità screen saver se si preme un pulsante qualsiasi del touchpad.<br>
			<strong><em>Impostazione display </em></strong> -
			Questa impostazione consente di spegnere il display LCD per risparmiare energia se il dispositivo rimane inattivo per il numero di minuti specificati nel campo "Timeout". Per riaccendere il display LCD, è sufficiente toccare uno dei pulsanti del touchpad.<br>
		</p>
	</td>
</tr>
</table>
</div>
