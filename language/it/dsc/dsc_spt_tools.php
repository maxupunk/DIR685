<div class="box">
<a name="admin"><h2>Admin</h2></a>
<table border=0 cellspacing=0 cellpadding=0>

<tr>
	<td height=20>
		
		<p>
			<strong><em>Nome di accesso amministratore</em></strong> -
			Immettere il nome che verrà utilizzato per accedere al router con i privilegi di amministratore.
		</p>
		<p>
			<strong><em>Password amministratore</em></strong> -
			Immettere e confermare la password che verrà utilizzata dall'account <strong>admin</strong> per accedere all'interfaccia di gestione del router.
		</p>
		<p>
			<strong>Gestione remota</strong><br>
			Gestione remota consente di configurare il dispositivo tramite la porta WAN (Wide Area Network) da Internet utilizzando un browser Web. Per accedere all'interfaccia di gestione del router, sono comunque necessari nome utente e password.
			<br>
			<strong><em>IP consentito per accesso</em></strong> -
			Questa opzione consente di specificare un determinato indirizzo IP da Internet al quale sarà consentito accedere al router in modalità remota. Per default questo campo viene lasciato vuoto per indicare che qualsiasi indirizzo IP da Internet può accedere al router in modalità remota dopo l'abilitazione della funzionalità di gestione remota.<br>
			<strong><em>Porta</em></strong> - Selezionare la porta che verrà utilizzata per accedere al dispositivo <?query("/sys/modelname");?>.
		</p>
		<p>
			<strong><em>Esempio: </em></strong><br>
			<a href="http://192.168.0.1/help_tools.html">http://x.x.x.x:8080 </a> dove x.x.x.x è l'indirizzo IP WAN del dispositivo <?query("/sys/modelname");?> e 8080 è la porta utilizzata dall'interfaccia di gestione Web.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="time"><h2>Ora</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=33>
		<p>
			Le impostazioni di configurazione dell'ora vengono utilizzate dal router per sincronizzare servizi pianificati e attività di registrazione del sistema. È necessario impostare il fuso orario corrispondente al paese in cui ci si trova. È possibile impostare l'ora manualmente oppure recuperarla connettendo il dispositivo a un server NTP (Network Time Protocol). È inoltre possibile impostare le date per il passaggio automatico all'ora legale.
		</p>
		<p>
			<strong><em>Fuso orario</em></strong> - Selezionare il fuso per la regione in cui ci si trova.<br>
			<strong><em>Aggiornamento ora legale</em></strong> -
			Se nella propria zona è prevista l'ora legale, abilitare questa opzione e specificare il mese, la settimana, il giorno e l'ora di inizio e fine per questo periodo dell'anno.<br>
			<strong><em>Configurazione ora automatica</em></strong> -
			Selezionare un server di riferimento ora D-Link da utilizzare per la sincronizzazione dell'ora del dispositivo <?query("/sys/modelname");?>. L'intervallo con cui il dispositivo <?query("/sys/modelname");?> comunicherà con il server NTP D-Link è impostato su 7 giorni.<br>
			<strong><em>Impostazione manuale di data e ora</em></strong> -
			Selezionare questa opzione se si desidera specificare l'ora manualmente. È necessario specificare l'anno, il mese, il giorno, l'ora, il minuto e il secondo oppure è possibile fare clic sul pulsante Copia ora dal computer per copiare l'ora di sistema dal computer utilizzato per l'accesso all'interfaccia di gestione.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="log_settings"><h2>Impostazioni log</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			È possibile salvare il file di log in un'unità disco locale e inviarlo in un secondo momento a un amministratore della rete ai fini della procedura di risoluzione dei problemi.
			<br>
			<strong><em>Salva</em></strong> - Fare clic su questo pulsante per salvare le voci del log in un file di testo.<br>
			<strong><em>Tipo di log</em></strong> - Selezionare il tipo di informazioni da inserire nel log del dispositivo <?query("/sys/modelname");?>.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="email_settings"><h2>Impostazioni e-mail</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			L'opzione Impostazioni e-mail consente di inviare il file di log del dispositivo a un indirizzo e-mail specificato.
			<br>
			<br>
			<strong><em>Indirizzo e-mail mittente</em></strong> - 
			Indirizzo e-mail utilizzato per inviare il messaggio e-mail. Con la maggior parte dei moderni servizi SMTP deve trattarsi di un indirizzo e-mail valido e verranno eseguiti test per verificarne l'autenticità.<br>
			<strong><em>Indirizzo e-mail destinatario</em></strong> - 
			Indirizzo e-mail a cui verrà inviato il file di log del dispositivo. Il file di log potrà essere visualizzato dall'utente che accede a tale account e-mail.<br>
			<strong><em>Oggetto e-mail</em></strong> - 
			Titolo del messaggio e-mail.<br>
			<strong><em>Indirizzo server SMTP</em></strong> - 
			Indirizzo IP o nome di dominio del server di posta che inoltrerà il file di log del dispositivo all'account e-mail richiesto.<br>
			<strong><em>Porta server SMTP</em></strong> - 
			Porta che verrà utilizzata dal server di posta.<br>
			<strong><em>Abilita autenticazione </em></strong> - 
			Per motivi di sicurezza alcuni server SMTP verificano nome e password dell'account per confermare che il messaggio e-mail da elaborare proviene da uno dei propri client.<br>
			<strong><em>Nome account</em></strong> - 
			Nome dell'account utilizzato per l'autenticazione con il server SMTP.<br>
			<strong><em>Password</em></strong> - 
			Password dell'account utilizzato per l'autenticazione con il server SMTP.<br>
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="system"><h2>Sistema</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=40>
		È possibile salvare le attuali impostazioni di sistema in un file del disco fisso locale. 
		Il file salvato o qualsiasi altro file di impostazioni salvato creato dal dispositivo può 
		quindi essere caricato nell'unità. Per ricaricare un file di impostazioni di sistema, fare 
		clic su <strong>Sfoglia</strong> per individuare nell'unità disco locale il file da utilizzare. È inoltre possibile 
		ripristinare le impostazioni di default del dispositivo facendo clic su <strong>Ripristina dispositivo</strong>. 
		Utilizzare la funzionalità di ripristino solo in caso di necessità, poiché implica la cancellazione 
		delle impostazioni precedentemente salvate per l'unità. Assicurarsi di salvare le impostazioni del 
		sistema prima di procedere al ripristino delle impostazioni di default.
		<br>
		<strong><em>Salva</em></strong> - Fare clic su questo pulsante per salvare il file di configurazione dal router.<br>
		<strong><em>Sfoglia</em></strong> -
		Fare clic su questo pulsante per individuare un file di configurazione salvato. Fare quindi clic su Carica e applicare le impostazioni salvate al router.<br>
		<strong><em>Ripristina dispositivo</em></strong> -
		Fare clic su questo pulsante per ripristinare le impostazioni di default del router.
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="firmware"><h2>Firmware</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=51>
		Questo strumento consente di aggiornare il firmware del dispositivo. Assicurarsi che il firmware da utilizzare sia salvato nell'unità disco locale del computer. Fare clic su Sfoglia per individuare nell'unità disco locale il firmware da utilizzare per l'aggiornamento. L'aggiornamento del firmware non implica la modifica delle impostazioni del sistema, tuttavia si consiglia di salvare tali impostazioni prima di procedere all'aggiornamento. Visitare il sito del supporto tecnico D-Link per verificare la disponibilità di aggiornamenti del firmware oppure fare clic sul pulsante Verifica ora per effettuare automaticamente tale verifica.
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="dynamic_dns"><h2>DNS dinamico</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=2>
		<p>
			Per DDNS (Dynamic DNS) si intende il metodo che consente di collegare un nome di dominio a un indirizzo IP dinamico, ovvero soggetto a modifica. Con la maggior parte delle connessioni via cavo e DSL viene assegnato un indirizzo IP dinamico che viene utilizzato solo per la durata di una specifica connessione. Con il dispositivo <?query("/sys/modelname");?> è possibile configurare il servizio DDNS in modo da aggiornare automaticamente il server DDNS ogni volta che viene ricevuto un nuovo indirizzo IP WAN.
			<br>
			<strong><em>Indirizzo server</em></strong> - Selezionare il provider DDNS dal menu a discesa.<br>
			<strong><em>Nome host</em></strong> - Immettere il nome host registrato con il provider di servizi DDNS.<br>
			<strong><em>Nome utente</em></strong> - Immettere il nome utente dell'account DDNS.<br>
			<strong><em>Password</em></strong> - Immettere la password dell'account DDNS.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="system_check"><h2>Verifica sistema</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			È possibile utilizzare questo strumento per verificare la connettività fisica nelle interfacce LAN e Internet (WAN). Si tratta di una funzionalità avanzata che integra un tester per cavo LAN in ogni porta Ethernet del router. Tramite l'interfaccia utente grafica (GUI), è possibile eseguire un test cavo per diagnosticare e segnalare in remoto problemi relativi al cavo, ad esempio circuiti aperti, cortocircuiti, coppie invertite, nonché errori di mancata impedenza. Questa funzionalità consente di ridurre significativamente gli interventi del supporto tecnico poiché permette agli utenti di risolvere facilmente le problematiche correlate alle connessioni via cavo.
		</p>
		<p>
			<strong>Test ping</strong><br>
			Questa utilità diagnostica consente di verificare se un computer ha accesso a Internet. Invia pacchetti ping e rimane in ascolto della risposta inviata dall'host specifico. Immettere il nome host o l'indirizzo IP di cui eseguire il ping (Packet Internet Groper), quindi fare clic su <strong>Ping</strong>. Lo stato del tentativo di esecuzione del comando ping verrà visualizzato nella casella Risultato ping.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="schedules"><h2>Pianificazioni</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>	
			In questa pagina è possibile configurare pianificazioni globali per il router. Una volta definite, tali pianificazioni possono essere successivamente applicate alle funzionalità del router che supportano la pianificazione.
			<br>
			<strong><em>Nome</em></strong> - Nome della pianificazione da definire.<br>
			<strong><em>Giorno/i</em></strong> -
			Selezionare un giorno, un intervallo di giorni oppure la casella di controllo Tutta la settimana per applicare la pianificazione ogni giorno.<br>
			<strong><em>Tutto il giorno (24 ore)</em></strong> -
			Selezionare questa casella per rendere la pianificazione attiva per tutte le 24 ore nei giorni specificati.<br>
			<strong><em>Ora di inizio</em></strong> -
			Selezionare l'ora in cui si desidera rendere attiva la pianificazione definita.<br>
			<strong><em>Ora di fine</em></strong> -
			Selezionare l'ora in cui si desidera rendere inattiva la pianificazione definita.<br>
			<strong><em>Elenco regole di pianificazione</em></strong> -
			Consente di visualizzare tutte le pianificazioni definite.
		</p>
	</td>
</tr>
</table>
</div>

						   