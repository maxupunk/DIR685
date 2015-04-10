<div class="box">
<a name="disk_management"><h2>Gestione disco</h2></a>
	<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			La pagina Gestione disco contiene informazioni e impostazioni relative a disco fisso locale attualmente installato nel dispositivo.
			<br>
			<br>
			<strong><em>Informazioni disco fisso</em></strong> -
			 Visualizza informazioni dettagliate sul disco fisso installato nel dispositivo.<br>
			<strong><em>Impostazione formattazione</em></strong> -
			Questo pulsante consente di formattare il disco fisso attualmente installato nel dispositivo.<br>
			AVVISO: questa azione implica la cancellazione del contenuto del disco fisso. Tutti i dati presenti nel disco andranno persi.<br>
			<strong><em>Impostazione disco fisso</em></strong> -
			Quando questa impostazione è abilitata, una volta trascorso il numero di minuti specificato il disco fisso passerà alla modalità standby se non vengono eseguite operazioni di lettura/scrittura per ridurre il consumo energetico.<br>
		</p>
	</td>
</tr>
 </table>
</div>

<div class="box">
<a name="users_groups"><h2>Utenti/Gruppi</h2></a>
	<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=228>
		<p>
			<strong>Utenti</strong><br>
			In questa pagina è possibile creare utenti. Gli account creati possono essere aggiunti alle regole nelle sezioni relative all'accesso alla rete e al server FTP. Ogni utente creato potrà inoltre accedere alla sezione dei download pianificati.
		</p>
		<p>
			<strong><em>Nome utente</em></strong> -
			Immettere il nome utente.<br>
			<strong><em>Password</em></strong> -
			Immettere la password.<br>
			<strong><em>Conferma password</em></strong> -
			Immettere nuovamente la password. Fare clic su 'Salva impostazioni' per aggiungere l'utente.<br>
			<br>
			Gli utenti creati verranno visualizzati in un elenco nella parte inferiore della pagina unitamente all'eventuale gruppo cui sono assegnati. È possibile modificare le password dell'utente facendo clic sull'icona del blocco note con la matita. Per eliminare gli utenti, è invece possibile fare clic sull'icona del cestino a destra della regola.			
		</p>
		<p>
			<strong>Gruppi</strong><br>
			In questa pagina è possibile creare gruppi. Una volta creato, il gruppo sarà disponibile nella sezione Gruppo della pagina Utenti.
			<br>
			<br>
			I gruppi creati verranno visualizzati in un elenco nella parte inferiore della pagina. Verranno inoltre visualizzati gli utenti inclusi in tali gruppi.
			<br>
		</p>
	</td>
</tr>
 </table>
</div>
 
 
<div class="box">
<a name="storage_access"><h2>Accesso archiviazione</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=64> 
		<p>
			<strong><em>Categoria</em></strong> -
			Selezionare Utente o Gruppo.<br>
			<strong><em>Utente o gruppo</em></strong> -
			Selezionare un utente o un gruppo dall'elenco a discesa. Selezionare 'Tutti gli account' se si desidera creare una regola valida per tutti gli utenti.<br>
			<strong><em>Cartella</em></strong> -
			Fare clic su "Sfoglia" per selezionare una cartella. Tale cartella deve essere reperibile nelle unità interne.<br>
			<strong><em>Autorizzazione</em></strong> -
			Assegnare le autorizzazioni "Sola lettura" o "Lettura/scrittura" alla cartella selezionata per l'utente o il gruppo selezionato.<br>
			<strong><em>Oplock</em></strong> -
			Gli oplock (Opportunistic Lock, blocchi opportunistici) sono una caratteristica del protocollo di rete di LAN Manager implementato nella famiglia di sistemi operativi Windows a 32 bit. Gli oplock sono in pratica le garanzie che un server assegna ai propri client per l'accesso a un volume logico condiviso. Tali garanzie informano il client che il contenuto di un file non potrà essere modificato dal server oppure, se sono previste modifiche, inviano notifica al client prima di procedere con la modifica. Gli oplock sono studiati in modo da ottimizzare le prestazioni della rete in relazione alla condivisione dei file di rete. Quando tuttavia si utilizzano applicazioni di database basate su file, è consigliabile impostare gli oplock di condivisione su <strong>No (disattivato)</strong>. <br>
			<br>
			Sistemi operativi interessati dagli oplock?<br>
			<br>
			Per default, gli oplock sono abilitati in Vista e non possono essere disabilitati. In caso di problemi di prestazioni con le applicazioni per la condivisione di file dal dispositivo DIR-685, possibile provare a impostare l'opzione Oplock su <strong>No (disattivato)</strong>.
			<br>
			<strong><em>Mappa archivio</em></strong> -
			Quando questa opzione è abilitata, l'attributo dei file -"Archivio" verrà copiato quando si memorizza il file nel dispositivo DIR-685. Alcuni software di backup aggiungono questo attributo ai file che vengono memorizzati come backup.<br>
			<strong><em>Commento</em></strong> -
			Ulteriori commenti sulla regola. Opzione facoltativa senza effetto funzionale.<br>
			<br>
			Fare clic su 'Salva impostazioni' per salvare la regola. Tutte le regole salvate verranno visualizzate nell'elenco nella parte inferiore della pagina. È possibile modificare le regole facendo clic sull'icona del blocco note con la matita. Per eliminare le regole, è invece possibile fare clic sull'icona del cestino a destra della regola.
			<br>
		</p>
 </tr>
</table>
</div>
 
 
<div class="box">
<a name="ftp_server"><h2>Server FTP</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=99>
		<p>
			<strong><em>Categoria</em></strong> -
			Selezionare Utente o Gruppo.<br>
			<strong><em>Utente</em></strong> -
			Selezionare un utente o un gruppo dall'elenco a discesa. Selezionare 'Tutti gli account' se si desidera creare una regola valida per tutti gli utenti. L'account Anonimo sarà sempre indicato come un utente.<br>
			<strong><em>Cartella</em></strong> -
			Fare clic su "Sfoglia" per selezionare una cartella e assegnarla all'utente selezionato. Tale cartella deve essere reperibile nelle unità interne. Se si desidera assegnare l'accesso alla directory radice di tutte le unità contemporaneamente, porre un segno di spunta nella casella 'radice'.<br>
			<strong><em>Autorizzazione</em></strong> -
			Assegnare le autorizzazioni "Sola lettura" o "Lettura/scrittura" alla cartella selezionata per l'utente o il gruppo selezionato. Fare clic su 'Aggiungi' per aggiungere la regola all'elenco. Tutte le regole salvate verranno visualizzate nell'elenco nella parte inferiore della pagina. È possibile modificare le regole facendo clic sull'icona del blocco note con la matita. Per eliminare le regole, è invece possibile fare clic sull'icona del cestino a destra della regola.<br>
			<strong><em>N. max utenti</em></strong> -
			Immettere il numero massimo di utenti a cui sarà consentito accedere al server FTP contemporaneamente. Il valore di default è 10.<br>
			<strong><em>Tempo di inattività</em></strong> -
			Il server FTP disconnetterà l'utente se viene superato il tempo di inattività specificato.<br>
			<strong><em>Porta</em></strong> -
			In questo campo è possibile immettere il nuovo numero della porta utilizzata dal server. Si tratta di un'impostazione avanzata la cui modifica può comportare problemi quando si utilizza un router. Si consiglia di non modificare il valore di default pari a 21 a meno che non si sia esperti nella modifica della porta FTP.<br>
			<strong><em>Controllo flusso</em></strong> -
			Questa funzione consente di regolare il flusso di dati gestito tramite il server FTP. Se si imposta un limite, gli utenti potranno riscontrare un rallentamento nel download dal server FTP, tuttavia si risparmierà larghezza di banda locale.<br>
			<strong><em>Lingua del client</em></strong> -
			La maggior parte dei client FTP standard, ad esempio Windows FTP, supportano solo la tabella codici dell'Europa occidentale per il trasferimento dei file. È stato quindi aggiunto il supporto per le tabelle codici del Nordeuropa, dell'Europa Centrale, del cinese tradizionale e semplificato, nonché del cirillico per i client FTP non standard in grado di supportare tali set di caratteri.<br>
			<br>
			Al termine fare clic su 'Salva impostazioni'.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="upnp_av_server"><h2>Server AV UPnP</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=44>
		<p>
			Il dispositivo DIR-685 incorpora un server multimediale AV UPnP che può essere utilizzato con lettori multimediali compatibili dello stesso tipo.
			<br>
			<br>
			<strong><em>Server AV UPnP</em></strong> -
			Consente di abilitare o disabilitare il server AV UPnP.<br>
			<strong><em>Cartella</em></strong> -
			Fare clic su 'Sfoglia' per individuare la cartella radice dei file multimediali (musica, foto e video). È possibile scegliere la cartella radice se si desidera poter accedere all'intero contenuto memorizzato nel dispositivo DIR-685.<br>
			<strong><em>Aggiornamento automatico</em></strong> -
			Consente di configurare l'aggiornamento automatico dei dati AV UPNP condivisi ogni 5, 15 o 30 minuti o a intervalli di 1, 2, 6, 12 o 24 ore.<br>
			<br>
			Al termine fare clic su 'Salva impostazioni'.<br>
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="itunes_server"><h2>Server iTunes</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			Il server iTunes consente al software iTunes di rilevare e riprodurre automaticamente file musicali dal dispositivo DIR-685.<br>
			<br>
			<strong><em>Server iTunes</em></strong> -
			Consente di abilitare o disabilitare il server iTunes.<br>
			<strong><em>Cartella</em></strong> -
			Fare clic su 'Sfoglia' per individuare la cartella contenente i file musicali. È possibile scegliere la cartella radice se si desidera poter accedere a tutte le cartelle memorizzate nel dispositivo DIR-685.<br>
			<strong><em>Aggiornamento automatico</em></strong> -
			Consente di configurare l'aggiornamento automatico della libreria iTunes condivisa ogni 5, 15 o 30 minuti o a intervalli di 1, 2, 6, 12 o 24 ore.<br>
			<br>
			Al termine fare clic su 'Salva impostazioni'.<br>
		</p>
</td>
</tr>
</table>
</div>

<div class="box">
<a name="bt_download_manager"><h2>Gestione download BT</h2></a>
	<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			La pagina Gestione download BT include le impostazioni per configurare il dispositivo in modo da consentire il download di file Bit Torrent da Internet senza dover accendere il PC.
			<br>
			<br>
			<strong><em>Impostazione BT</em></strong> -
			Consente di attivare/disattivare il servizio Gestione download BT. Il percorso della directory consente di indicare la directory/cartella in cui salvare i file scaricati. Tutti i download verranno memorizzati nella directory specificata. Tutti gli elementi completati verranno memorizzati in una directory denominata "completed", mentre quelli in corso in una directory denominata "incomplete". L'organizzazione dei file per ogni download rimarrà la stessa dei file originali scaricati.<br>
			<strong><em>Download Torrent</em></strong> -
			Nella schermata Gestione download BT è possibile scegliere se aggiungere nuovi elementi da scaricare tramite un URL o un singolo file seme (seed) BT.<br>
			Tutti gli elementi da scaricare verranno elencati nella parte inferiore della finestra, un download per riga, in modo da poterli visualizzare e controllare singolarmente.
			<br>
			<strong><em>Tabella degli elementi da scaricare</em></strong> -
			Per ogni elemento da scaricare fare clic sull'apposito collegamento per visualizzare ulteriori informazioni sui download correnti.<br>
			<strong><em>Arresta</em></strong> -
			Utilizzare questo pulsante per arrestare il processo di download, garantendo una maggior larghezza di banda agli elementi da scaricare.<br>
			<strong><em>Rimuovi</em></strong> -
			Utilizzare questo pulsante presente sul lato destro di ciascun elemento da scaricare per annullare/eliminare l'elemento in caso di errore.<br>
			<br>
			Se il download dell'elemento eliminato è già stato completato, verrà rimossa solo la voce in elemento mentre i file scaricati rimarranno nella directory "completed".
			<br>
			<strong><em>Rimuovi completati</em></strong> -
			Questo pulsante disponibile nell'angolo superiore destro della tabella degli elementi da scaricare consente di rimuovere tutti gli elementi scaricati dalla tabella senza eliminare i file scaricati.<br>			
		</p>
	</td>
</tr>
 </table>
</div>
