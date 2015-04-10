<div class="box">
<a name="disk_management"><h2>Datenträgerverwaltung</h2></a>
	<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			Die Seite der Datenträgerverwaltung enthält Informationen und Einstellungen für die lokale Festplatte, die aktuell im Gerät installiert ist.
			<br>
			<br>
			<strong><em>Informationen zum Festplattenlaufwerk </em></strong> -
			Enthält Details zu der auf dem Gerät installierten Festplatte.<br>
			<strong><em>Formatierungseinstellung</em></strong> -
			Hier können Sie die Festplatte, die zum aktuellen Zeitpunkt im Gerät installiert ist, formatieren.<br>
			ACHTUNG: Diese Aktion löscht die gesamten Daten auf der Festplatte. Alle Daten gehen verloren!<br>
			<strong><em>Festplatteneinstellung</em></strong> -
			Wenn diese Einstellung aktiviert ist, wird die Festplatte nach der in Minuten angegebenen Zeit in den Standby-Modus versetzt, wenn keine Daten auf die Festplatte geschrieben oder von ihr gelesen werden, um den Stromverbrauch zu reduzieren.<br>
		</p>
	</td>
</tr>
 </table>
</div>

<div class="box">
<a name="users_groups"><h2>Benutzer/Gruppen</h2></a>
	<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=228>
		<p>
			<strong>Benutzer</strong><br>
			Hier können Sie Benutzerkonten erstellen. Diese können dann Regeln in den Bereichen für den Netzwerkzugriff und FTP-Server hinzugefügt werden. Jeder erstellte Benutzer hat Zugriff auf den Bereich zum Download nach einem bestimmten Zeitplan.
		</p>
		<p>
			<strong><em>Benutzername</em></strong> -
			Geben Sie den Benutzernamen ein.<br>
			<strong><em>Kennwort</em></strong> -
			Geben Sie das Kennwort ein.<br>
			<strong><em>Kennwort bestätigen </em></strong> -
			Geben Sie das Kennwort noch einmal ein. Klicken Sie auf 'Einstellungen speichern', um den Benutzer hinzuzufügen.<br>
			<br>
			Die erstellten Benutzer erscheinen in einer Liste im unteren Bereich dieser Seite zusammen mit ihrer zugeordneten Gruppe (sofern zutreffend). Die Kennwörter können durch Klicken auf das Symbol eines 'Notizblocks mit Bleistift' geändert werden. Benutzer können durch Klicken auf das 'Papierkorbsymbol' rechts neben der Regel gelöscht werden.
		</p>
		<p>
			<strong>Gruppen</strong><br>
			Hier können Sie Gruppen erstellen. Sobald eine Gruppe erstellt ist, steht sie in der Gruppenauswahl der Benutzerseite zur Verfügung.
			<br>
			<br>
			Die erstellten Gruppen erscheinen in einer Liste im unteren Bereich dieser Seite. Die Benutzer in diesen Gruppen werden ebenfalls angezeigt.
			<br>
		</p>
	</td>
</tr>
 </table>
</div>
 
 
<div class="box">
<a name="storage_access"><h2>Speicherzugriff</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=64> 
		<p>
			<strong><em>Kategorie</em></strong> -
			Wählen Sie entweder 'Benutzer' oder 'Gruppe'.<br>
			<strong><em>Benutzer [oder Gruppe]</em></strong> -
			Wählen Sie einen Benutzer oder eine Gruppe von der Pulldown-Liste. Wählen Sie 'Alle Konten', wenn Sie eine für alle Benutzer geltende Regel erstellen möchten.<br>
			<strong><em>Ordner</em></strong> -
			Klicken Sie auf "Durchsuchen", um einen Ordner auszuwählen. Dieser Ordner muss sich auf den internen Laufwerken befinden.<br>
			<strong><em>Berechtigung</em></strong> -
			Weisen Sie dem ausgewählten Ordner für den ausgewählten Benutzer oder die Gruppe die Berechtigungen "Schreibgeschützt" oder "Lesen/Schreiben" zu.<br>
			<strong><em>Oplocks</em></strong> -
			Opportunistische Sperren (Oplocks) sind ein Merkmal des LAN-Manager-Netzwerkprotokolls, das in der 32-Bit-Windows-Familie von Betriebssystemumgebungen implementiert ist. Oplocks sind Garantien, die ein Server für einen gemeinsam genutzten logischen Datenträger für seine Clients erstellt. Diese Garantien informieren den Client, dass der Inhalt einer Datei vom Server nicht geändert werden darf, oder dass, wenn Änderungen anstehen, der Client benachrichtigt wird, bevor die Änderung durchgeführt werden darf. Oplocks wurden entwickelt, um die Netzwerkleistung bei Netzwerkdateifreigaben zu erhöhen. Wenn jedoch dateibasierte Datenbankanwendungen verwendet werden, wird empfohlen, die Freigabe-Oplocks auf <strong>Nein (Aus)</strong> zu setzen. <br>
			<br>
			Auf welche Betriebssysteme haben Oplocks einen Einfluss?<br>
			<br>
			In Windows Vista® sind Oplocks standardmäßig aktiviert und können nicht deaktiviert werden. Wenn Sie bei der Freigabe von Dateien über den DIR-685 Probleme mit der Netzwerkleistung haben, können Sie versuchen, die Leistung zu verbessern, indem Sie Oplocks auf  <strong>Nein (Aus)</strong> setzen.
			<br>
			<strong><em>Archiv zuordnen</em></strong> -
			Wenn diese Option aktiviert ist, wird das Dateiattribut 'Archiv' in dem Moment kopiert, in dem die Datei auf dem DNS-685 gespeichert wird. Bestimmte Backup-Softwareprogramme hängen dieses Attribut an Dateien an, die als Backups gespeichert werden.<br>
			<strong><em>Kommentar</em></strong> -
			Möglichkeit der Eingabe von Kommentaren zu dieser Regel. Sie ist optional und hat keine funktionalen Auswirkungen.<br>
			<br>
			Klicken Sie auf "Einstellungen speichern", um die Regel zu speichern. Die gespeicherten Regeln erscheinen in der Liste im unteren Bereich dieser Seite. Sie können bearbeitet oder gelöscht werden, indem Sie auf das Symbol 'Notizblock mit Bleistift' oder das Symbol 'Papierkorb' rechts neben der Regel klicken.
			<br>
		</p>
 </tr>
</table>
</div>
 
 
<div class="box">
<a name="ftp_server"><h2>FTP-Server</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=99>
		<p>
			<strong><em>Kategorie</em></strong> -
			Wählen Sie entweder 'Benutzer' oder 'Gruppe'.<br>
			<strong><em>Benutzer</em></strong> -
			Wählen Sie einen Benutzer oder eine Gruppe von der Pulldown-Liste. Wählen Sie 'Alle Konten', wenn Sie eine für alle geltende Regel erstellen möchten. 'Anonymous' (Anonym) wird immer als ein Benutzer aufgelistet.<br>
			<strong><em>Ordner</em></strong> -
			Klicken Sie auf "Durchsuchen", um einen Ordner zu wählen und diesen Ordner dem ausgewählten Benutzer zuzuweisen. Dieser Ordner muss sich auf den internen Laufwerken befinden. Wenn Sie Zugriff auf den Stamm (root) aller Laufwerke gleichzeitig zuweisen möchten, markieren Sie das Kästchen 'Stamm'.<br>
			<strong><em>Berechtigung</em></strong> -
			Weisen Sie dem ausgewählten Ordner für den ausgewählten Benutzer oder die Gruppe die Berechtigungen "Schreibgeschützt" oder "Lesen/Schreiben" zu. Klicken Sie auf 'Hinzufügen', um die Regel der Liste hinzuzufügen. Die gespeicherten Regeln erscheinen in der Liste im unteren Bereich dieser Seite. Sie können bearbeitet oder gelöscht werden, indem Sie auf das Symbol 'Notizblock mit Bleistift' oder das Symbol 'Papierkorb' rechts neben der Regel klicken.<br>
			<strong><em>Benutzerhöchstzahl </em></strong> -
			Geben Sie die maximale Anzahl an Benutzern ein, denen gleichzeitig Zugriff auf den FTP-Server erlaubt sein soll. Der Standardwert ist 10.<br>
			<strong><em>Leerlaufzeit</em></strong> -
			Der FTP-Server sperrt einen Benutzer aus, sobald er die angegebene Leerlaufzeit überschreitet.<br>
			<strong><em>Port</em></strong> -
			Wenn Sie den Port ändern möchten, den der FTP-Server verwendet, geben Sie die neue Nummer hier ein. Es handelt sich hierbei um eine spezielle Einstellung, bei der eine Änderung - hinter einem Router - Komplikationen zur Folge haben kann. Es ist deshalb ratsam, die Einstellung auf dem vorgegebenen Standardwert 21 zu lassen, es sei denn, Sie verfügen bezüglich der Änderung des FTP-Ports über die erforderliche Erfahrung und technischen Kenntnisse.<br>
			<strong><em>Datenflusssteuerung</em></strong> -
			Diese Funktion ermöglicht die Anpassung und Steuerung des Datenflusses durch den FTP-Server. Wenn Sie hier einen Grenzwert eingeben, verlangsamt das möglicherweise den Download-Vorgang vom FTP-Server, Sie werden aber andererseits lokale Bandbreitenkapazität einsparen.<br>
			<strong><em>Client-Sprache</em></strong> -
			Die meisten Standard-FTP-Clients wie Windows FTP unterstützen beim Übertragen von Dateien nur westeuropäische Kodeseiten. Es wurden deshalb nordeuropäische, mitteleuropäische, traditionell und vereinfacht chinesische sowie kyrillische Kodeseiten für Nicht-Standard-FTP-Clients hinzugefügt, die diese Zeichensätze unterstützen können.<br>
			<br>
			Klicken Sie auf 'Einstellungen speichern', wenn Sie sie vorgenommen haben.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="upnp_av_server"><h2>UPnP AV-Server</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=44>
		<p>
			Der DIR-685 bietet einen integrierten UPnPAV-Medienserver, der mit UPnP AV kompatiblen Medienabspielprogrammen verwendet werden kann.
			<br>
			<br>
			<strong><em>UPnP AV-Server</em></strong> -
			Aktivieren oder deaktivieren Sie den UPnP AV-Server.<br>
			<strong><em>Ordner</em></strong> -
			Klicken Sie auf 'Durchsuchen', um das Stammverzeichnis Ihrer Mediendateien (Musik, Fotos und Video) zu lokalisieren. Das Stammverzeichnis (root) kann gewählt werden, wenn Sie Zugriff auf alle Inhalte des DIR-685 wünschen.<br>
			<strong><em>Autom. aktualisieren</em></strong> -
			Konfigurieren Sie diese Option, um Ihre zur gemeinsamen Nutzung freigegebenen UPNP AV-Daten automatisch alle 5, 15 oder 30 Minuten oder in 1, 2, 6, 12 oder 24 Stundenintervallen zu aktualisieren.<br>
			<br>
			Klicken Sie auf 'Einstellungen speichern', wenn Sie sie vorgenommen haben.<br>
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="itunes_server"><h2>iTunes-Server</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			Der iTunes-Server ermöglicht der iTunes-Software die automatische Erkennung und das Abspielen von Musik vom DIR-685.
			<br>
			<br>
			<strong><em>iTunes-Server</em></strong> -
			Aktivieren oder deaktivieren Sie den iTunes-Server.<br>
			<strong><em>Ordner</em></strong> -
			Klicken Sie auf 'Durchsuchen', um den Ordner zu suchen, der Ihre Musikdateien enthält. Das Stammverzeichnis (root) kann gewählt werden, wenn Sie Zugriff auf alle Ordner des DIR-685 wünschen.<br>
			<strong><em>Autom. aktualisieren</em></strong> -
			Konfigurieren Sie diese Option, um Ihre zur gemeinsamen Nutzung freigegebenen Daten der iTunes automatisch alle 5, 15 oder 30 Minuten oder in 1, 2, 6, 12 oder 24 Stundenintervallen zu aktualisieren.<br>
			<br>
			Klicken Sie auf 'Einstellungen speichern', wenn Sie sie vorgenommen haben.<br>
		</p>
</td>
</tr>
</table>
</div>

<div class="box">
<a name="bt_download_manager"><h2>BT Download Manager</h2></a>
	<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			Die Seite BT Download Manager enthält Einstellungen zum Einrichten Ihres Geräts, sodass so genannte 'BitTorrent'-Dateien aus dem Internet heruntergeladen werden können, ohne dass Sie Ihren PC einschalten müssen (Filesharing über das Bittorrent-Protokoll).
			<br>
			<br>
			<strong><em>BT-Einstellung</em></strong> -
			Ermöglicht das Ein- und Ausschalten des BT Download Manager-Dienstes. Mithilfe des Verzeichnispfades können Sie angeben, in welchem Verzeichnis/Ordner Sie Ihre heruntergeladenen Dateien speichern möchten. Alle heruntergeladenen Dateien werden dann dort abgelegt, wobei alle fertig gestellten Elemente in einem Verzeichnis mit der Bezeichnung "Completed" (Fertig gestellt) und alle in Bearbeitung befindlichen Elemente in einem Verzeichnis mit dem Namen "incomplete" (Nicht fertig gestellt) gespeichert werden. Die Dateiorganisation für jeden Download bleibt exakt die gleiche wie bei den ursprünglich heruntergeladenen Dateien.<br>
			<strong><em>Torrent Downloads</em></strong> -
			Im Fenster des BT Download Managers können Sie wählen, ob Sie neue Download-Elemente über einen URL oder von einer einzelnen Torrent-Datei hinzufügen möchten.<br>
			Alle Elemente, die Sie herunterladen, werden unten in dem Fenster aufgelistet. Jedem heruntergeladenen Element ist eine Zeile zugeordnet, sodass Sie jedes Element, dass Sie herunterladen, sehen und kontrollieren können.
			<br>
			<strong><em>Tabelle der heruntergeladenen Elemente</em></strong> -
			Für jedes Element, das heruntergeladen wird, können Sie über einen entsprechenden Link weitere Details zu den aktuellen Downloads anzeigen.<br>
			<strong><em>Stoppen</em></strong> -
			Der Benutzer kann den Download-Prozess stoppen/anhalten, um so anderen Elementen, die heruntergeladen werden, mehr Bandbreite zur Verfügung zu stellen.<br>
			<strong><em>Entfernen</em></strong> -
			Mithilfe dieser rechts neben jedem einzelnen Element befindlichen Schaltfläche können Benutzer, falls ein Fehler gemacht wurde, den Download-Vorgang abbrechen oder das Element löschen.<br>
			<br>
			Wenn das gelöschte Element bereits heruntergeladen wurde, wird nur der Eintrag gelöscht. Die bereits heruntergeladenen Dateien werden im Verzeichnis "completed" (Fertig gestellt) abgelegt.
			<br>
			<strong><em>Entfernen aus der Tabelle</em></strong> -
			Diese Schaltfläche im oberen rechten Bereich der Element-Download-Tabelle bietet Benutzern die Möglichkeit, alle heruntergeladenen Elemente aus der Tabelle zu entfernen, ohne dabei die heruntergeladenen Dateien selbst zu löschen.<br>			
		</p>
	</td>
</tr>
 </table>
</div>
