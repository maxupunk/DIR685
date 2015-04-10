<div class="box">
<a name="admin"><h2>Admin</h2></a>
<table border=0 cellspacing=0 cellpadding=0>

<tr>
	<td height=20>
		
		<p>
			<strong><em>[Administrator] Anmeldename</em></strong> -
			Geben Sie den Namen ein, der zur Anmeldung beim Router mit Administratorzugriff verwendet wird.
		</p>
		<p>
			<strong><em>[Administrator] Kennwort</em></strong> -
			Geben Sie das Kennwort ein, dass das Konto admin zum Zugriff auf die Verwaltungsbenutzeroberfläche des Routers verwenden wird, und bestätigen Sie es.
		</p>
		<p>
			<strong>Fernmanagement</strong><br>
			Mithilfe der Fernmanagementsfunktionen können Sie das Gerät über den WAN-Port (Wide Area Network) vom Internet unter Verwendung eines Webbrowsers konfigurieren. Zum Zugriff auf die Managementbenutzeroberfläche des Routers ist die Eingabe eines Benutzernamens und Kennworts erforderlich.
			<br>
			<strong><em>Zugriff auf diese IP erlaubt</em></strong> -
			Hier können Benutzer eine bestimmte IP-Adresse angeben, auf die vom Internet aus der Fernzugriff auf den Router erlaubt wird. Standardmäßig ist dieses Feld leer. Das bedeutet, das der Fernzugriff jeder IP-Adresse vom Internet aus auf den Router möglich ist, sobald das Fernmanagement aktiviert ist.<br>
			<strong><em>Port</em></strong> - Wählen Sie den Port, der zum Zugriff auf den <?query("/sys/modelname");?> verwendet werden soll.
		</p>
		<p>
			<strong><em>Beispiel: </em></strong><br>
			<a href="http://192.168.0.1/help_tools.html">http://x.x.x.x:8080 </a> , wobei x.x.x.x die WAN-IP-Adresse des <?query("/sys/modelname");?> und 8080 der für die Web-Managementschnittstelle verwendete Port ist.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="time"><h2>Zeit</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=33>
		<p>
			Die Einstellungen der Zeitkonfiguration werden vom Router verwendet, um geplante Dienste und Systemprotokollaktivitäten zu synchronisieren. Sie müssen die Zeitzone in Übereinstimmung mit Ihrem Standort einstellen. Die Zeit kann manuell eingestellt werden oder das Gerät kann mit einem NTP-Server (Network Time Protocol) verbunden werden, um die Zeit dort abzurufen. Sie können auch Daten für die Zeitumstellung festlegen. Die Systemzeit wird dann an angegebenen Daten automatisch angepasst.
		</p>
		<p>
			<strong><em>Zeitzone</em></strong> - Wählen Sie die Zeitzone für die Region, in der Sie sich befinden.<br>
			<strong><em>Sommerzeit</em></strong> -
			Aktivieren Sie diese Option und geben Sie Anfangs- und Endmonat, -woche, -tag und -uhrzeit für diese Zeit des Jahres ein, wenn die Region, in der Sie sich befinden, die Sommerzeit einhält.<br>
			<strong><em>Automatische Zeitkonfiguration</em></strong> -
			Wählen Sie einen D-Link-Time Server, über den der <?query("/sys/modelname");?> seine Zeit synchronisieren soll. Das Intervall, mit dem der <?query("/sys/modelname");?> mit dem D-Link NTP Server kommuniziert, ist auf 7 Tage gesetzt.<br>
			<strong><em>Datum und Zeit manuell einstellen</em></strong> -
			Wählen Sie diese Option, wenn Sie die Zeit manuell einstellen möchten. Sie müssen Jahr, Monat, Tag, Stunde, Minute und Sekunde angeben, oder Sie können auf die Schaltfläche "Zeiteinstellungen des Computers kopieren" klicken, um die Systemzeit des für den Zugriff auf die Verwaltungsschnittstelle verwendeten Computers zu übernehmen.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="log_settings"><h2>Protokolleinstellungen</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			Sie können die Protokolldatei auf einer lokalen Festplatte speichern, um sie zu einem späteren Zeitpunkt nach Bedarf an einen Netzwerkadministrator zur Fehlerdiagnose und -behebung zu senden.
			<br>
			<strong><em>Speichern</em></strong> - Klicken Sie auf diese Schaltfläche, um die Protokolleinträge in einer Textdatei zu speichern.<br>
			<strong><em>Protokolltyp</em></strong> - Wählen Sie die Art von Informationen, die der <?query("/sys/modelname");?> erfassen und protokollieren soll.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="email_settings"><h2>E-Mail-Einstellungen</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			Verwenden Sie die E-Mail-Einstellungen, um die Geräteprotokolldatei an eine angegebene E-Mail-Adresse zu senden.
			<br>
			<br>
			<strong><em>Von (E-Mail-Adresse) </em></strong> - 
			Die E-Mail-Adresse des Senders. Die Mehrzahl der heutigen SMTP-Dienste fordern die Angabe einer gültigen E-Mail-Adresse und führen entsprechende Tests durch, um deren Echtheit zu prüfen.<br>
			<strong><em>An (E-Mail-Adresse) </em></strong> - 
			Die E-Mail-Adresse, an die die Geräteprotokolldatei gesendet wird. Die Protokolldatei wird von der Person empfangen, die Zugriff auf dieses E-Mail-Konto hat.<br>
			<strong><em>Betreff (E-Mail)</em></strong> - 
			Der Titel oder ein kurzer Verweis auf den Inhalt der E-Mail.<br>
			<strong><em>SMTP-Serveradresse</em></strong> - 
			Die IP-Adresse oder der Domänenname des Mailservers, der die Geräteprotokolldatei an das gewünschte E-Mail-Konto weiterleitet.<br>
			<strong><em>SMTP-Serverport</em></strong> - 
			Der Port, den der Mailserver verwendet.<br>
			<strong><em>Authentifizierung aktivieren</em></strong> - 
			Einige SMTP-Server prüfen aus Gründen der Sicherheit den Kontonamen und das Kennwort, um zu bestätigen, dass die E-Mail, die von ihnen verarbeitet wird, auch tatsächlich von einem ihrer Clients stammt.<br>
			<strong><em>Kontoname</em></strong> - 
			Der zur Authentifizierung mit dem SMTP-Server verwendete Kontoname.<br>
			<strong><em>Kennwort</em></strong> - 
			Das Kennwort des Kontos, das zur Authentifizierung mit dem SMTP-Server verwendet wird.<br>
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="system"><h2>System</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=40>
		Die aktuellen Systemeinstellungen können als Datei auf der lokalen Festplatte gespeichert werden. Die gespeicherte Datei oder eine andere vom Gerät erstellte, gespeicherte Einstellungsdatei kann in das Gerät geladen werden. Um eine Systemeinstellungendatei neu zu laden, klicken Sie auf <strong>Durchsuchen</strong>, um auf der lokalen Festplatte nach dieser Datei zu suchen. Sie können auch die Einstellungen des Geräts auf die werkseitigen Einstellungen zurücksetzen, indem Sie auf <strong>Geräteeinstellungen wiederherstellen</strong> klicken. Sie sollten diese Rücksetzfunktion nur wenn unbedingt nötig verwenden, weil bei ihrer Verwendung die vorher gespeicherten Einstellungen des Geräts gelöscht werden. Sie sollten deshalb vor Verwendung dieser Funktion unbedingt Ihre aktuellen Systemeinstellungen speichern.
		<br>
		<strong><em>Speichern</em></strong> -  Klicken Sie auf diese Schaltfläche, um die Konfigurationsdatei von dem Router zu speichern.<br>
		<strong><em>Durchsuchen</em></strong> -
		Klicken Sie auf diese Schaltfläche, um eine gespeicherte Konfigurationsdatei zu suchen. Laden Sie sie dann auf den Router und übernehmen Sie die gespeicherten Einstellungen.<br>
		<strong><em>Geräteeinstellungen wiederherstellen</em></strong> -
		Klicken Sie auf diese Schaltfläche, um die werkseitigen Standardvoreinstellungen des Routers wiederherzustellen.
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="firmware"><h2>Firmware</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=51>
		Mithilfe dieses Tools können Sie die Firmware des Routers aktualisieren. Vergewissern Sie sich, dass die gewünschte Firmware auf der lokalen Festplatte des Computers gespeichert ist. Klicken Sie auf „Browse“ (Durchsuchen), um die Firmware-Datei auf der Festplatte zu suchen, die für die Aktualisierung verwendet werden soll. Eine Aktualisierung der Firmware ändert Ihre Systemeinstellungen nicht. Es ist trotzdem ratsam, dass Sie Ihre Systemeinstellungen sichern, bevor Sie ein Firmware-Upgrade durchführen. Sehen Sie auf der Support-Seite von D-Link für Firmware-Aktualisierungen nach oder klicken Sie auf "Check Now" (Jetzt prüfen), damit der Router automatisch nach neuer Firmware sucht.
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="dynamic_dns"><h2>Dynamischer DNS</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=2>
		<p>
			Bei dem Dynamischen DNS (Domain Name Service) handelt es sich um eine Methode, bei der ein Domänenname mit einer sich ändernden (dynamischen ) IP-Adresse verbunden bleibt. Bei den meisten Kabel- und DSL-Verbindungen wird Ihnen eine dynamische IP-Adresse zugewiesen. Diese ist aber nur für die Dauer dieser speziellen Verbindung gültig. Bei dem <?query("/sys/modelname");?> können Sie Ihren DDNS-Service einrichten. Er aktualisiert dann jedes Mal automatisch Ihren DDNS-Server, sobald er eine neue WAN IP-Adresse empfängt.
			<br>
			<strong><em>Serveradresse</em></strong> - Wählen Sie Ihren DDNS-Anbieter vom Dropdown-Menü.<br>
			<strong><em>Hostname </em></strong> - Geben Sie den Hostnamen ein, den Sie bei Ihrem DDNS-Dienstanbieter registriert haben.<br>
			<strong><em>Benutzername oder Schlüssel </em></strong> - Geben Sie den Benutzernamen für Ihr DDNS-Konto ein.<br>
			<strong><em>Kennwort </em></strong> - Geben Sie das Kennwort für Ihr DDNS-Konto ein.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="system_check"><h2>Systemprüfung</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			Dieses Hilfsprogramm kann zur Prüfung der physischen Verbindung sowohl der LAN- als auch der Internet (WAN)-Schnittstellen verwendet werden. Es handelt sich dabei um eine spezielle Funktion, die auf jedem Ethernet-Port auf dem Router einen LAN-Kabeltester integriert. Mit ihrer Hilfe kann über die grafische Benutzeroberfläche (GUI) ein Kabeltest zur Ferndiagnose und Meldung von Kabelfehlern als Ursache für unterbrochene Stromkreise und Kurzschlüsse sowie Tests zu Austauschkonflikten oder fehlender Impedanzübereinstimmung durchgeführt werden. Dank dieser Funktion werden Serviceanfragen und Rücksendungen beträchtlich reduziert, indem sie Benutzern die Möglichkeit bietet, ihre Kabelverbindungen problemlos auf mögliche Fehler hin selbst zu prüfen.
		</p>
		<p>
			<strong>Ping-Test</strong><br>
			Dieses nützliche Diagnosehilfsprogramm kann verwendet werden, um zu prüfen, ob sich ein bestimmter Computer im Internet befindet. Es sendet Ping-Datenpakete und empfängt dann entsprechende Antworten von dem spezifischen Host. Geben Sie einen Hostnamen oder die IP-Adresse an, an die Sie einen Ping (Packet Internet Groper) senden möchten und klicken Sie auf <strong>Ping</strong>. Status und Ergebnisse der Ping-Tests werden unter „Ping Result“ (Ping-Ergebnis) angezeigt.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="schedules"><h2>Zeitpläne</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>	
			Auf dieser Seite werden globale Zeitpläne für den Router konfiguriert. Sie können nach ihrer Erstellung auf Zeitplaneinstellungen unterstützende Funktionen des Routers angewandt werden.
			<br>
			<strong><em>Name</em></strong> - Der Name des Zeitplans, der festgelegt wird.<br>
			<strong><em>Tag(e)</em></strong> -
			Wählen Sie einen bestimmten Tag, einen Bereich von Tagen oder die ganze Woche, auf den/die dieser Zeitplan Anwendung finden soll.<br>
			<strong><em>Ganzer Tag - 24 Stunden</em></strong> -
			Markieren Sie dieses Kontrollkästchen, damit der Zeitplan die gesamten 24 Stunden an den angegebenen Tagen aktiv ist.<br>
			<strong><em>Startzeit</em></strong> -
			Wählen Sie die Uhrzeit, an der der Zeitplan aktiv werden soll.<br>
			<strong><em>Endzeit</em></strong> -
			Wählen Sie die Uhrzeit, an der der Zeitplan inaktiv werden soll.<br>
			<strong><em>Zeitplanregelliste</em></strong> -
			Sie zeigt alle festgelegten Zeitpläne an.
		</p>
	</td>
</tr>
</table>
</div>

						   