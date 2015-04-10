<h1>SUPPORTMENÜ</h1>
<table border=0 cellspacing=0 cellpadding=0 width=750>
<tr>
<td height=2><b><font size=4>Wartung</font></b></td>
</tr>
<tr>
<td height=16><p><br>
</td>
</tr>
<tr>
	<td height=20>
		<strong>Geräteadministration</strong><a name=12></a><br>
		<p>
			<strong><em>Administrator-Anmeldename</em></strong> -
			Geben Sie den Namen des Kontos für den Administrator-Zugriff ein.
		</p>
		<p>
			<strong><em>Administrator-Kennwort</em></strong> -
			Geben Sie das Kennwort für das Konto <strong>admin</strong>für den Zugriff auf die Verwaltungsoberfläche des Routers ein, und bestätigen Sie es.
		</p>
		<p>
			<strong>Remoteverwaltung</strong><br>
			Mit der Option Remoteverwaltung kann das Gerät über den WAN-Port mit Hilfe eines Webbrowsers vom Internet aus konfiguriert werden. Für den Zugriff auf die Verwaltungsoberfläche des Routers sind Benutzername und Kennwort erforderlich.<br>
			<strong><em>Erlaubter Zugriff für IP</em></strong> -
			Über diese Option können Benutzer eine bestimmte IP-Adresse aus dem Internet angeben, der Fernzugriff auf den Router erlaubt wird. Dieses Feld bleibt standardmäßig leer, d. h., dass beliebige IP-Adressen aus dem Internet über Fernzugriff auf den Router verfügen, sobald die Remoteverwaltung aktiviert wird.<br>
			<strong><em>Port</em></strong> - Wählen Sie den Port für den Zugriff auf den <?query("/sys/modelname");?> aus.
		</p>
		<p>
			<strong><em>Beispiel:  </em></strong><br>http://x.x.x.x:8080 </a> wobei x.x.x.x die WAN-IP-Adresse des
			<a href="http://192.168.0.1/help_tools.html"> <?query("/sys/modelname");?> und 8080 der Port für die Webverwaltungsoberfläche sind. 
		</p>
	</td>
</tr>
<tr><td height=10>&nbsp;</td></tr>
<tr><td height=10>&nbsp;</td></tr>
<tr>
	<td height=40>
		<a name=14><strong>Speichern und wiederherstellen</strong></a><br>
		Die aktuellen Systemeinstellungen können als Datei auf der lokalen Festplatte gespeichert werden. 
		Einstellungen aus Einstellungsdateien, die vom Gerät erstellt wurden, können in das System geladen werden. 
		Um eine Einstellungsdatei neu zu laden, klicken Sie auf <strong><em>Durchsuchen<em></strong>, und suchen Sie auf der lokalen Festplatte nach der gewünschten Datei. 
		Durch Klicken auf die Schaltfläche<strong><em>Gerät zurücksetzen<em></strong> kann das Gerät wieder auf die Standardeinstellungen zurückgesetzt werden. 
		Verwenden Sie die Funktion zum Zurücksetzen nur, wenn es unbedingt erforderlich ist. 
		Alle bestehenden Geräteeinstellungen werden dabei gelöscht. 
		Sichern Sie daher Ihre konfigurierten Systemeinstellungen, bevor Sie das Gerät auf die Werkseinstellungen zurücksetzen.<br>
		<strong><em>Speichern</em></strong> - Klicken Sie auf diese Schaltfläche, um die Konfigurationsdatei des Routers zu speichern.<br>
		<strong><em>Durchsuchen</em></strong> -
		 Klicken Sie auf diese Schaltfläche, um eine gespeicherte Konfigurationsdatei auszuwählen. Klicken Sie anschließend auf „Laden“, um die gespeicherten Einstellungen für den Router zu übernehmen.<br>
		<strong><em>Gerät zurücksetzen</em></strong> -
		Klicken Sie auf diese Schaltfläche, um den Router auf die Werkseinstellungen zurückzusetzen.
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=51>
		<b>Firmware-Aktualisierung</b><a name=15></a><br> 	
		Mit Hilfe dieser Funktion können Sie die Firmware des Gerätes aktualisieren. 
		Stellen Sie sicher, dass die gewünschte Firmware auf der Festplatte des Computers gespeichert ist.
		Klicken Sie auf <strong>Durchsuchen</strong>, um die Datei für die Firmware-Aktualisierung auf der Festplatte zu suchen.
		Bei der Aktualisierung der Firmware werden keine Systemeinstellungen geändert, es wird jedoch empfohlen, die Systemeinstellungen vor einer Firmware-Aktualisierung zu sichern.
		Firmware-Aktualisierungen finden Sie auf der D-Link <a href=<?query("/sys/supporturl");?>>Supportwebsite</a> , oder klicken Sie auf die Schaltfläche „Jetzt überprüfen“, damit der Router automatisch nach neuer Firmware sucht. 
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=2>
		<p>
			<strong>DDNS-Einstellungen </strong><a name=16></a><br>
			Dynamisches DNS (Domain Name Service) ist ein Service, 
			über den ein Computer trotz wechselnder (dynamischer) IP-Adresse immer unter demselben Domänennamen erreichbar ist.
			Bei den meisten Kabel- und DSL-Anschlüssen wird dem Teilnehmer eine dynamische IP-Adresse zugewiesen, 
			die nur für die Dauer der jeweiligen Verbindung gilt. Mit dem <?query("/sys/modelname");?> können Sie Ihren Router für den DDNS-Dienst konfigurieren. 
			Sobald dem Router eine neue WAN-IP-Adresse zugewiesen wird, erfolgt automatisch eine Aktualisierung des DDNS-Servers.<br>
			<strong><em>Serveradresse</em></strong> - Wählen Sie im Dropdown-Menü Ihren DDNS-Anbieter aus.<br>
			<strong><em>Hostname</em></strong> - Geben Sie den Hostnamen ein, mit dem Sie bei Ihrem DDNS-Diensteanbieter registriert sind.<br>
			<strong><em>Benutzernamee</em></strong> - Geben Sie den Benutzernamen Ihres DDNS-Kontos ein.<br>
			<strong><em>Kennwort</em></strong> - Geben Sie das Kennwort Ihres DDNS-Kontos ein.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height="197">
		<p>
			<strong>Systemüberprüfung</strong><a name=17></a><br>
			Mit diesem Tool können Sie die physische Konnektivität der LAN- und WAN-Schnittstellen überprüfen. 
			Dabei handelt es sich um eine erweiterte Funktion, mit der an jedem Ethernet-Anschluss des Routers ein LAN-Kabeltester integriert wird. 
			Über die grafische Benutzeroberfläche wird VCT (Virtual Cable Tester) dafür eingesetzt, Kabelfehler wie Leitungsunterbrechungen, Kurzschlüsse, Überlagerungen und Impedanz-Fehlanpassungen per Ferndiagnose zu erkennen und zu melden. 
			Mit dieser Funktion können fehlerhafte Kabelverbindungen durch den Benutzer selbst leicht identifiziert werden. Wartungsaufwand und -kosten werden somit verringert.
		</p>
		<p>
			<strong>Ping-Test</strong><br>
			Mit diesem hilfreichen Diagnoseprogramm können Sie überprüfen, ob ein Computer mit dem Internet verbunden ist. 
			Das Programm sendet Ping-Pakete an einen bestimmten Host und wartet auf dessen Antworten. 
			Geben Sie einen Hostnamen oder eine IP-Adresse ein, an den/die Sie ein Ping-Paket senden möchten (Packet Internet Groper), und klicken Sie auf <strong>Ping</strong>. 
			Der Status Ihres Ping-Versuchs wird im Feld „Ping-Ergebnis“ angezeigt.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td>
		<p>
			<strong>Zeitpläne<a name=18></a></strong></p>
			Auf dieser Seite werden die globalen Zeitpläne für den Router konfiguriert. Nachdem die Zeitpläne definiert wurden, können diese später auf Routerfunktionen angewendet werden, sofern diese Funktionen Zeitpläne unterstützen.<br>
			<strong><em>Name</em></strong> - Der Name des zu definierenden Zeitplans.<br>
			<strong><em>Tage</em></strong> -
			Wählen Sie einen Tag, mehrere Tage oder das Kontrollkästchen „Ganze Woche“ aus, um diesen Zeitplan täglich zu aktivieren.<br>
			<strong><em>Ganzer Tag - 24 Stunden</em></strong> -
			Aktivieren Sie dieses Kontrollkästchen, um den Zeitplan an den angegebenen Tagen für 24 Stunden zu aktivieren.<br>
			<strong><em>Startzeit</em></strong> -
			Wählen Sie die Zeit, zu der der Zeitplan aktiviert werden soll.<br>
			<strong><em>Endzeit</em></strong> -
			Wählen Sie die Zeit, zu der der Zeitplan deaktiviert werden soll.<br>
			<strong><em>Liste der Regeln für Zeitpläne</em></strong> -
			Hier werden alle definierten Zeitpläne angezeigt.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td>
		<p>
			<strong>Protokolleinstellungen</strong><strong><a name=19></a></strong><br>
			Sie können die Protokolldatei auf einem lokalen Laufwerk speichern, damit diese später zur Fehlerbehebung an einen Netzwerkadministrator geschickt werden kann.<br>
			<strong><em>Speichern</em></strong> - Klicken Sie diese Schaltfläche, um die Protokolle als Textdatei zu speichern.<br>
			<strong><em>Protokolltyp</em></strong> -Wählen Sie die Informationen aus, die der <?query("/sys/modelname");?> protokollieren soll.
		</p>
	</td>
</tr>

</table>
						   
