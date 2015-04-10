<h1>MENU SUPPORTO</h1>
<table border=0 cellspacing=0 cellpadding=0 width=750>
<tr>
<td height=2><b><font size=4>Manutenzione</font></b></td>
</tr>
<tr>
<td height=16><p><br>
</td>
</tr>
<tr>
	<td height=20>
		<strong>Amministrazione dispositivi</strong><a name=12></a><br>
		<p>
			<strong><em>Nome di accesso amministratore</em></strong> -
			Immettere il nome che verr¨¤ utilizzato per accedere al router con i privilegi di amministratore.
		</p>
		<p>
			<strong><em>Password amministratore </em></strong> -
			Immettere e confermare la password che verr¨¤ utilizzata dall'account admin per accedere all'interfaccia di gestione del router.
		</p>
		<p>
			<strong>Gestione remota</strong><br>
			Gestione remota consente di configurare il dispositivo tramite la porta WAN (Wide Area Network) da Internet utilizzando un browser Web. Per accedere all'interfaccia di gestione del router, sono comunque necessari nome utente e password.<br>
			<strong><em>IP consentito per accesso</em></strong> -
			Questa opzione consente di specificare un determinato indirizzo IP da Internet al quale sar¨¤ consentito accedere al router in modalit¨¤ remota. Per default questo campo viene lasciato vuoto per indicare che qualsiasi indirizzo IP da Internet pu¨° accedere al router in modalit¨¤ remota dopo l'abilitazione della funzionalit¨¤ di gestione remota.<br>
			<strong><em>Porta</em></strong> - Selezionare la porta che verr¨¤ utilizzata per accedere a <?query("/sys/modelname");?>.
		</p>
		<p>
			<strong><em>Esempio: </em></strong><br>
			http://x.x.x.x:8080 whereas x.x.x.x is the
			http://x.x.x.x:8080 dove x.x.x.x ¨¨ l'indirizzo IP WAN di <?query("/sys/modelname");?> e 8080 ¨¨ la porta utilizzata dall'interfaccia di gestione Web. 
		</p>
	</td>
</tr>
<tr><td height=10>&nbsp;</td></tr>
<tr><td height=10>&nbsp;</td></tr>
<tr>
	<td height=40>
		<a name=14><strong>Salva e ripristina</strong></a><br>
		¨¨ possibile salvare le attuali impostazioni di sistema in un file del disco fisso locale.
		Il file salvato o qualsiasi altro file di impostazioni salvato creato dal dispositivo pu¨° quindi essere caricato nell'unit¨¤. 
		Per ricaricare un file di impostazioni di sistema, 
		fare clic su <strong><em>Sfoglia</em></strong> per individuare nell'unit¨¤ disco locale il file da utilizzare. 
		¨¨ inoltre possibile ripristinare le impostazioni di default del dispositivo facendo clic <strong><em>su Ripristina</em></strong> dispositivo.
		Utilizzare la funzionalit¨¤ di ripristino solo in caso di necessit¨¤, 
		poich¨¦ implica la cancellazione delle impostazioni precedentemente salvate per l'unit¨¤. 
		Assicurarsi di salvare le impostazioni del sistema prima di procedere al ripristino delle impostazioni di default.
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=51>
		<b>Aggiornamento firmware</b><a name=15></a><br> 
		Questo strumento consente di aggiornare il firmware del dispositivo. Assicurarsi che il firmware da utilizzare sia salvato nell'unit¨¤ disco locale del computer. 
		Fare clic su Sfoglia per individuare nell'unit¨¤ disco locale il firmware da utilizzare per l'aggiornamento. 
		L'aggiornamento del firmware non implica la modifica delle impostazioni del sistema, tuttavia si consiglia di salvare tali impostazioni prima di procedere all'aggiornamento.
		Visitare il sito del supporto tecnico D-Link per verificare la disponibilit¨¤ di aggiornamenti del firmware oppure fare clic sul pulsante Verifica ora per effettuare automaticamente tale verifica. 
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=2>
		<p>
			<strong>Impostazione DDNS </strong><a name=16></a><br>
			Per DDNS (Dynamic DNS) si intende il metodo che consente di collegare un nome di dominio a un indirizzo IP dinamico, 
			ovvero soggetto a modifica. 
			Con la maggior parte delle connessioni via cavo e DSL viene assegnato un indirizzo IP dinamico che viene utilizzato solo per la durata di una specifica connessione. 
			Con <?query("/sys/modelname");?> ¨¨ possibile configurare il servizio DDNS in modo da aggiornare automaticamente il server DDNS ogni volta che viene ricevuto un nuovo indirizzo IP WAN.<br>
			<strong><em>Indirizzo server</em></strong> - Selezionare il provider DDNS dal menu a discesa.<br>
			<strong><em>Nome host</em></strong> - Immettere il nome host registrato con il provider di servizi DDNS.<br>
			<strong><em>Nome utente</em></strong> - Immettere il nome utente dell'account DDNS.<br>
			<strong><em>Password</em></strong> - mmettere la password dell'account DDNS.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height="197">
		<p>
			<strong>Verifica sistema</strong><a name=17></a><br>
			¨¨ possibile utilizzare questo strumento per verificare la connettivit¨¤ fisica nelle interfacce LAN e WAN. Si tratta di una funzionalit¨¤ avanzata che integra un tester per cavo LAN in ogni porta Ethernet del router. Tramite l'interfaccia utente grafica (GUI), ¨¨ possibile utilizzare Test cavo per diagnosticare e segnalare in remoto problemi relativi al cavo, ad esempio cavi aperti, corti, invertiti, nonch¨¦ errori di mancata impedenza. Questa funzionalit¨¤ consente di ridurre significativamente gli interventi del supporto tecnico poich¨¦ permette agli utenti di risolvere facilmente le problematiche correlate alle connessioni via cavo.
		</p>
		<p>
			<strong>Test ping</strong><br>
			Questa utilit¨¤ diagnostica consente di verificare se un computer ha accesso a Internet. Invia pacchetti ping e rimane in ascolto della risposta inviata dall'host specifico. Immettere il nome host o l'indirizzo IP di cui eseguire il ping (Packet Internet Groper), quindi fare clic su <strong>Ping</strong> . Lo stato del tentativo di esecuzione del comando ping verr¨¤ visualizzato nella casella Risultato ping.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td>
		<p>
			<strong>Pianificazion<a name=18></a></strong></p>
			In questa pagina ¨¨ possibile configurare pianificazioni globali per il router. Una volta definite, tali pianificazioni possono essere successivamente applicate alle funzionalit¨¤ del router che supportano la pianificazione.<br>
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
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td>
		<p>
			<strong>Impostazioni log</strong><strong><a name=19></a></strong><br>
			¨¨ possibile salvare il file di log in un'unit¨¤ disco locale e inviarlo in un secondo momento a un amministratore della rete ai fini della procedura di risoluzione dei problemi.<br>
			<strong><em>Salva</em></strong> - Fare clic su questo pulsante per salvare le voci del log in un file di testo.<br>
			<strong><em>Tipo di log</em></strong> - Selezionare il tipo di informazioni da inserire nel log di <?query("/sys/modelname");?>.
		</p>
	</td>
</tr>

</table>
						   
