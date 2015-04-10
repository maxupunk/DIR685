<div class="box">
<a name="internet_setup"><h2>Internet-Setup</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=40>
		<p>
			Wenn Sie dieses Gerät zum ersten Mal konfigurieren, empfiehlt D-Link, auf "Internet Connection Setup Wizard" (Setup-Assistent für die Internetverbindung) zu klicken und den Anweisungen auf dem Bildschirm zu folgen. Wenn Sie die Geräteeinstellungen manuell ändern oder konfigurieren möchten, klicken Sie auf die Schaltfäche "Manual Internet Connection Setup" (Manuelle Einrichtung der Internetverbindung).
		</p>
	</td>
</tr>
<tr>
	<td height=59>
		<p>
			<strong>Den Setup-Assistenten für die Internetverbindung starten</strong><br>
			Klicken Sie auf diese Schaltfläche, um anhand einiger einfacher Schritte Ihren Router mit dem Internet zu verbinden.
			<br>
			<strong>Den Setup-Assistenten für die Funksicherheit starten </strong><br>
			Klicken Sie auf diese Schaltfläche, um anhand der Anweisungen die Einstellungen Ihres Funknetzwerks, einschließlich der Sicherheitsmaßnahmen, zu konfigurieren.
		</p>
	</td>
</tr>
<tr><td height=32>&nbsp;</td></tr>
<tr>
	<td height=46>
		<p>
			<strong>Manuelle Einrichtung der Internetverbindung</strong><br>
			Wählen Sie diese Option, wenn Sie die Einstellungen für die Verbindung Ihres Routers mit dem Internet manuell vornehmen möchten.
			<br>
			<strong>Access Point-Modus</strong><br>
			Durch Aktivierung von "Access Point-Modus" übernimmt das Gerät die Funktion eines drahtlosen AP. Dabei werden alle NAT-Funktionen, außer jene, die sich auf die Funkverbindung beziehen, deaktiviert.
			<br>
			<strong>Internet-Verbindungstyp  </strong><br>
			Die Internetverbindungseinstellungen werden dazu verwendet, den <?query("/sys/modelname");?> mit dem Internet zu verbinden. Alle Informationen, die auf dieser Seite eingegeben werden müssen, erhalten Sie von Ihrem Internetdienstanbieter. Sie werden häufig auch als "öffentliche Einstellungen" bezeichnet. Wählen Sie die passende Option für Ihren spezifischen Internetanbieter. Wenden Sie sich an Ihren Internetdienstanbieter, wenn Sie nicht sicher sind, welche Option Sie wählen sollen.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=61>
		<p>
			<strong>Statische IP-Adresse</strong><br>
			Wählen Sie diese Option, wenn Ihr Internetdienstanbieter Ihnen eine IP-Adresse, Subnetzmaske, Standard-Gateway und eine DNS-Serveradresse mitgeteilt hat. Geben Sie diese Informationen in den entsprechenden Feldern ein. Wenden Sie sich an Ihren Internetdienstanbieter, wenn Sie nicht sicher sind, was Sie in diesen Feldern eingeben sollen.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=142>
		<p>
			<strong>Dynamische IP-Adresse</strong><br>
			Wählen Sie diese Option, wenn Ihr Internetdienstanbieter Ihnen automatisch eine IP-Adresse bereitstellt. Kabelmodemanbieter verwenden in der Regel eine dynamische Zuweisung der IP-Adressen.
		</p>
		<p>
			<strong><em>Host-Name </em></strong> (optional) -
			Eine Eingabe im Host-Namenfeld ist optional, wird aber möglicherweise von einigen Internetdienstanbietern gefordert. Der standardmäßige Host-Name ist die Modellnummer des Routers.<br>
			<strong><em>MAC-Adresse  </em></strong> (optional) -
			Eingaben im Feld "MAC-Adresse" (Media Access Control) werden von einigen Internetdienstanbietern verlangt. Die Standard-MAC-Adresse wird auf die MAC-Adresse der WAN-Schnittstelle auf dem <?query("/sys/modelname");?> gesetzt. Sie können die Schaltfläche "MAC-Adresse kopieren" verwenden, um die MAC-Adresse der Ethernet-Karte zu kopieren, die auf dem zum Konfigurieren des Geräts verwendeten Computer installiert ist. Sie müssen nur dann Angaben in dem Feld machen, wenn es von Ihrem Internetdienstanbieter gefordert wird.<br>
			<strong><em>Primäre DNS-Adresse </em></strong> -
			Geben Sie bei Bedarf die von Ihrem Internetdienstanbieter bereitgestellte IP-Adresse des primären DNS-Servers ein. Normalerweise wird die primäre DNS-Adresse automatisch bei der Verbindungsherstellung eingestellt.<br>
			<strong><em>Sekundäre DNS-Adresse </em></strong> (optional) -
			Wurde Ihnen von Ihrem Internetdienstanbieter eine IP-Adresse eines sekundären DNS-Servers mitgeteilt, geben Sie sie in diesem Feld ein.<br>
			<strong><em>MTU </em></strong> -
			MTU (Maximum Transmission/Transfer Unit) beschreibt die maximale Paketgröße, die über ein Netzwerk übertragen werden kann. Größere Pakete werden in kleinere Datenpakete geteilt. Der Standardwert für diese Option ist 1500. Ein Ändern dieser Größe könnte die Leistung Ihres Routers negativ beeinflussen. Ändern Sie sie deshalb nur, wenn Sie von einem Vertreter des technischen Support von D-Link oder von Ihrem Internetdienstanbieter dazu aufgefordert werden.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=47>
		<p>
			<strong>PPPoE</strong><br>
			Wählen Sie diese Option, wenn Ihr Internetdienstanbieter von Ihnen die Verwendung einer PPPoE-Verbindung (Point to Point Protocol over Ethernet) fordert. Diese Option wird in der Regel von DSL-Anbietern verwendet. Wählen Sie Dynamisches PPPoE, um automatisch eine IP-Adresse für Ihre PPPoE-Verbindung zu erhalten (von der Mehrzahl der PPPoE-Verbindungen verwendet). Wählen Sie Statisches PPPoE, um eine statische IP-Adresse für Ihre PPPoE-Verbindung zu verwenden.
		</p>
		<p>
			<strong><em>Benutzername </em></strong> - Geben Sie Ihren PPPoE-Benutzernamen ein.<br>
			<strong><em>Kennwort </em></strong> - Geben Sie Ihr PPPoE-Kennwort ein.<br>
			<strong><em>Dienstname  </em></strong> (optional) -
			Wenn Ihr Internetanbieter einen Dienstnamen für die PPPoE-Verbindung verwendet, geben Sie ihn hier ein.<br>
			<strong><em>IP-Adresse </em></strong> -
			Diese Option ist nur für Statisches PPPoE verfügbar. Geben Sie die statische IP-Adresse für die PPPoE-Verbindung ein.<br>
			<strong><em>MAC-Adresse </em></strong> (optional) -
			Eingaben im Feld "MAC-Adresse" (Media Access Control) werden von einigen Internetdienstanbietern verlangt. Die Standard-MAC-Adresse wird auf die MAC-Adresse der WAN-Schnittstelle auf dem <?query("/sys/modelname");?> gesetzt. Sie können die Schaltfläche "MAC-Adresse kopieren" verwenden, um die MAC-Adresse der Ethernet-Karte zu kopieren, die auf dem zum Konfigurieren des Geräts verwendeten Computer installiert ist. Sie müssen nur dann Angaben in diesem Feld machen, wenn es von Ihrem Internetdienstanbieter gefordert wird.<br>
			<strong><em>Primäre DNS-Adresse </em></strong> -
			Möglicherweise von Ihrem Internetdienstanbieter bereitgestellte IP-Adresse des primären DNS-Servers. Diese Information ist nur einzugeben, wenn Sie 'Statisches PPPoE' gewählt haben. Haben Sie 'Dynamisches PPPoE' gewählt, lassen Sie den Standardwert in diesem Feld. Ihr Internetanbieter wird Ihnen diese Information automatisch bereitstellen.<br>
			<strong><em>Sekundäre DNS-Adresse </em></strong> (optional) -
			Wurde Ihnen von Ihrem Internetdienstanbieter eine IP-Adresse eines sekundären DNS-Servers mitgeteilt, geben Sie sie in diesem Feld ein.<br>
			<strong><em>Maximale Leerlaufzeit </em></strong> -
			(Die Dauer der Inaktivität in Minuten), bevor das Gerät die Verbindung mit Ihrer PPPoE-Sitzung trennt. Geben Sie eine maximale Leerlaufzeit (in Minuten) ein, um damit festzulegen, wie lange die Internetverbindung während der Inaktivität bestehen bleiben soll. Ist die Verbindung länger als die angegebene maximale Leerlaufzeit inaktiv, wird die Verbindung abgebrochen. Diese Option gilt nur für den Bedarfsverbindungsmodus (Connect-on-demand/Bei Bedarf verbinden).<br>
			<strong><em>MTU </em></strong> -
			MTU (Maximum Transmission/Transfer Unit) beschreibt die maximale Paketgröße, die über ein Netzwerk übertragen werden kann. Größere Pakete in kleinere Datenpakete geteilt. Der Standardwert für diese Option ist 1492. Ein Ändern dieser Größe könnte die Leistung Ihres Routers negativ beeinflussen. Ändern Sie sie deshalb nur, wenn Sie von einem Vertreter des technischen Support von D-Link oder von Ihrem Internetdienstanbieter dazu aufgefordert werden.<br>
			<strong><em>Auswahl Verbindungsmodus</em></strong> -
			Wählen Sie "Immer an", wenn Sie wünschen, dass der Router die Verbindung der PPPoE-Sitzung nie abbricht. Wählen Sie "Manuell", wenn Sie steuern möchten, wann der Router eine Verbindung zum Internet herstellt und wann er sie abbricht. Die Option "Bei Bedarf verbinden" ermöglicht dem Router, eine Verbindung zum Internet nur dann herzustellen, wenn ein Gerät in Ihrem Netzwerk versucht, auf eine Ressource im Internet zuzugreifen.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>PPTP</strong><br>
			Wählen Sie diese Option, wenn Ihr Internetdienstanbeiter eine PPTP-Verbindung (Point to Point Tunneling Protocol) verwendet und Ihnen einen Benutzernamen und ein Kennwort zugewiesen hat, um auf das Internet zuzugreifen. Wählen Sie Dynamisches PPTP, um eine IP-Adresse automatisch für Ihre PPTP-Verbindung zu erhalten. Wählen Sie Statisches PPTP, um eine statische IP-Adresse für Ihre PPTP-Verbindung zu verwenden.
		</p>
		<p>
			<strong><em>IP-Adresse </em></strong> - Geben Sie die IP-Adresse ein, die Ihnen Ihr Internetdienstanbieter zugewiesen hat.<br>
			<strong><em>Subnetzmaske </em></strong> - Geben Sie die Subnetzmaske ein, die Ihnen Ihr Internetdienstanbieter zugewiesen hat.<br>
			<strong><em>Gateway</em></strong> - Geben Sie die Gateway-IP-Adresse ein, die Ihnen Ihr Internetdienstanbieter zugewiesen hat.<br>
			<strong><em>DNS - </em></strong>Geben Sie die DNS-Adresse ein, die Ihnen Ihr Internetdienstanbieter zugewiesen hat.<br>
			<strong><em>Server-IP  </em></strong> -
			Geben Sie die IP-Adresse des Servers ein, die Ihnen Ihr Internetdienstanbieter bereitstellen wird.<br>
			<strong><em>Konto </em></strong> - Geben Sie Ihren PPTP-Benutzernamen ein.<br>
			<strong><em>Kennwort </em></strong> - Geben Sie Ihr PPTP-Kennwort ein.<br>
			<strong><em>Maximale Leerlaufzeit </em></strong> -
			Die Dauer der Inaktivität, bevor das Gerät die Verbindung mit Ihrer PPTP-Sitzung abbricht. Geben Sie eine maximale Leerlaufzeit (in Minuten) ein, um damit festzulegen, wie lange die Internetverbindung während der Inaktivität bestehen bleiben soll. Ist die Verbindung länger als die angegebene maximale Leerlaufzeit inaktiv, wird die Verbindung abgebrochen. Diese Option gilt nur für den Bedarfsverbindungsmodus (Connect-on-demand/Bei Bedarf verbinden).<br>
			<strong><em>MTU </em></strong> -
			MTU (Maximum Transmission/Transfer Unit) beschreibt die maximale Paketgröße, die über ein Netzwerk übertragen werden kann. Größere Pakete werden in kleinere Datenpakete geteilt. Der Standardwert für diese Option ist 1400. Ein Ändern dieser Größe könnte die Leistung Ihres Routers negativ beeinflussen. Ändern Sie sie deshalb nur, wenn Sie von einem Vertreter des technischen Support von D-Link oder von Ihrem Internetdienstanbieter dazu aufgefordert werden.<br>
			<strong><em>Auswahl Verbindungsmodus</em></strong> -
			Wählen Sie "Immer an", wenn Sie wünschen, dass der Router die Verbindung der PPTP-Sitzung nie abbricht. Wählen Sie "Manuell", wenn Sie steuern möchten, wann der Router eine Verbindung zum Internet herstellt und wann er sie abbricht. Die Option "Bei Bedarf verbinden" ermöglicht dem Router, eine Verbindung zum Internet nur dann herzustellen, wenn ein Gerät in Ihrem Netzwerk versucht, auf eine Ressource im Internet zuzugreifen.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>L2TP </strong><br>
			Wählen Sie diese Option, wenn Ihr Internetdienstanbeiter eine L2TP-Verbindung (Layer 2 Tunneling Protocol) verwendet und Ihnen einen Benutzernamen und ein Kennwort zugewiesen hat, um auf das Internet zuzugreifen. Wählen Sie Dynamisches L2TP, um eine IP-Adresse automatisch für Ihre L2TP-Verbindung zu erhalten. Wählen Sie Statisches L2TP, um eine statische IP-Adresse für Ihre L2TP-Verbindung zu verwenden.
		</p>
		<p>
			<strong><em>IP-Adresse  </em></strong> - Geben Sie die IP-Adresse ein, die Ihnen Ihr Internetdienstanbieter zugewiesen hat.<br>
			<strong><em>Subnetzmaske </em></strong> - Geben Sie die Subnetzmaske ein, die Ihnen Ihr Internetdienstanbieter zugewiesen hat.<br>
			<strong><em>Gateway</em></strong> - Geben Sie die Gateway-IP-Adresse ein, die Ihnen Ihr Internetdienstanbieter zugewiesen hat.<br>
			<strong><em>DNS</em></strong> -  Geben Sie die DNS-Adresse ein, die Ihnen Ihr Internetdienstanbieter zugewiesen hat.<br>
			<strong><em>Server-IP </em></strong> -
			Geben Sie die IP-Adresse des Servers ein, die Ihnen Ihr Internetdienstanbieter bereitstellen wird.<br>
			<strong><em>L2TP-Konto </em></strong> - Geben Sie Ihren L2TP-Benutzernamen ein.<br>
			<strong><em>L2TP-Kennwort </em></strong> - Geben Sie Ihr L2TP-Kennwort ein.<br>
			<strong><em>Maximale Leerlaufzeit  </em></strong> -
			Die Dauer der Inaktivität in Minuten), bevor das Gerät die Verbindung mit Ihrer L2TP-Sitzung abbricht. Geben Sie eine maximale Leerlaufzeit (in Minuten) ein, um damit festzulegen, wie lange die Internetverbindung während der Inaktivität bestehen bleiben soll. Ist die Verbindung länger als die angegebene maximale Leerlaufzeit inaktiv, wird die Verbindung abgebrochen. Diese Option gilt nur für den Bedarfsverbindungsmodus (Connect-on-demand/Bei Bedarf verbinden).<br>
			<strong><em>MTU</em></strong> -
			MTU (Maximum Transmission/Transfer Unit) beschreibt die maximale Paketgröße, die über ein Netzwerk übertragen werden kann. Größere Pakete werden in kleinere Datenpakete geteilt. Der Standardwert für diese Option ist 1400. Ein Ändern dieser Größe könnte die Leistung Ihres Routers negativ beeinflussen. Ändern Sie sie deshalb nur, wenn Sie von einem Vertreter des technischen Support von D-Link oder von Ihrem Internetdienstanbieter dazu aufgefordert werden.
			<strong><em>Auswahl Verbindungsmodus</em></strong> -
			Wählen Sie "Immer an", wenn Sie wünschen, dass der Router die Verbindung der L2TP-Sitzung nie abbricht. Wählen Sie "Manuell", wenn Sie steuern möchten, wann der Router eine Verbindung zum Internet herstellt und wann er sie abbricht. Die Option "Bei Bedarf verbinden" ermöglicht dem Router, eine Verbindung zum Internet nur dann herzustellen, wenn ein Gerät in Ihrem Netzwerk versucht, auf eine Ressource im Internet zuzugreifen.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Russian PPTP (Dual Access)</strong><br>
			Um eine russische PPTP-Internetverbindung einzurichten, konfigurieren Sie die Einstellungen, wie vorher für PPTP-Verbindungen beschrieben, Wenn eine statische Route von Ihrem Internetanbieter eingerichtet werden muss, finden Sie nähere Informationen zur weiteren Einrichtung unter der "Routing"-Funktion im Menü "ERWEITERT".
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Russian PPPoE (Dual Access)</strong><br>
			Einige PPPoE-Verbindungen verwenden zusätzlich zu den globalen IP-Einstellungen eine statische IP-Route zum Internetdienstanbieter für die Verbindung. Das macht einen zusätzlichen Schritt erforderlich, in dem IP-Einstellungen für den physischen WAN-Port festgelegt werden. Um eine russische PPPoE Internetverbindung zu konfigurieren, gehen Sie, wie vorher für PPPoE beschrieben, vor und fügen Sie die physischen WAN IP-Einstellungen den Anweisungen Ihres Internetdienstanbieters entsprechend hinzu. Wenn eine statische Route von Ihrem Internetanbieter eingerichtet werden muss, finden Sie nähere Informationen zur weiteren Einrichtung unter der "Routing"-Funktion im Menü "ERWEITERT".
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="wireless_setup"><h2>Funk-Setup</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			Die Seite zum Einrichten eines Funknetzes enthält die Einstellungen für den Access Point-Teil des <?query("/sys/modelname");?>. Auf dieser Seite können Sie Ihr Funknetz Ihren Wünschen entsprechend einrichten oder den <?query("/sys/modelname");?> so konfigurieren, dass er in ein bereits bestehendes Funknetz integriert werden kann.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Wi-Fi Protected Setup (in Windows Vista auch WCN 2.0 genannt)</strong><br>
			Diese Funktion bietet Benutzern eine intuitivere Methode zum Einrichten drahtloser Sicherheitsfunktionen. Dazu stehen zwei Optionen zur Verfügung: Persönliche Identifikationsnummer (PIN) und Verschlüsselung per Tastendruck. Geben Sie die PIN ein, die zusammen mit dem Gerät im Funkkarten-Hilfsprogramm oder Windows Vistas Hilfsprogramm für drahtlose Clients bereitgestellt wird, wenn die Funkkarte einen zertifizierten Windows Vista-Treiber aufweist, um Funksicherheit zwischen dem Router und dem Client automatisch einzurichten. Die Funkkarte muss dazu WPS (Wi-Fi Protected Setup) in beiden Optionen unterstützen, um die Vorteile dieser Funktion nutzen zu können.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Name des Funknetzwerks</strong><br>
			Auch als SSID (Service Set Identifier) bezeichnet. Das ist der Name Ihres WLAN (Wireless Local Area Network). Für den <?query("/sys/modelname");?> ist sie standardmäßig "dlink". Die SSID kann geändert werden.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Funkkanal</strong><br>
			Gibt an, welchen Kanal der <?query("/sys/modelname");?> nutzt. Der Standardwert für den Kanal ist 6. Sie können ihn ändern, damit er dem Kanal für ein bereits vorhandenes Funknetz entspricht oder um Ihr eigenes neues Funknetz Ihren Wünschen und Erfordernissen entsprechend anzupassen. Markieren Sie das Kontrollkästchen "Enable Auto Scan" (Automatisches Kanalscanning aktivieren), damit <?query("/sys/modelname");?> den Kanal für seinen Betrieb automatisch auswählt. Die Wahl dieser Option wird deshalb empfohlen, weil der Router den Kanal mit den geringsten potentiellen Interferenzen wählt.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>	
 		<p>
 			<strong>Übertragungsraten (TX)</strong><br>
 			Wählen Sie die grundlegenden Übertragungsraten auf Grundlage der Geschwindigkeit der Funkadapter im WLAN (Wireless Local Area Network).
 		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>WMM</strong><br>
			Wählen Sie "Aktivieren", um QoS für die drahtlose Schnittstelle des <?query("/sys/modelname");?> einzuschalten.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Verborgenen Funk aktivieren  </strong><br>
			Wählen Sie "Aktiviert", wenn Sie nicht wünschen, dass die SSID Ihres Funknetzes vom <?query("/sys/modelname");?> gesendet wird. Bei Aktivierung dieser Option ist die SSID des <?query("/sys/modelname");?> nicht von den Site Survey-Hilfsprogrammen aus sichtbar. Wenn Sie also Ihre drahtlosen Clients einrichten, müssen Sie die SSID Ihres <?query("/sys/modelname");?> kennen, um sie manuell einzugeben und eine Verbindung mit dem Router herstellen zu können. Diese Option ist standardmäßig aktiviert.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Funksicherheitsmodus</strong><br>
			Es ist wichtig, dass Sie Ihr Funknetz sichern. Nur so kann die Integrität von Datenübertragungen in Ihrem Funknetz gewährleistet werden. Der <?query("/sys/modelname");?> bietet 4 Verschlüsselungsstandards für Ihr Funknetz: WEP, WPA only, WPA2 only und WPA/WPA2 (auto-detect).
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>WEP </strong><br>
			WEP (Wired Equivalent Protocol) ist ein drahtloses Sicherheitsprotokoll für WLANs (Wireless Local Area Networks). WEP bietet Sicherheit, indem es die über WLAN gesendeten Daten verschlüsselt. Der <?query("/sys/modelname");?> unterstützt die 64-Bit und 128-Bit WEP-Verschlüsselung. WEP ist standardmäßig deaktiviert. Sie können die WEP-Einstellungen ändern, um Ihr eigenes drahtloses Netz Ihren Wünschen entsprechend anzupassen.
		</p>
		<p>
			<strong><em>Authentifizierung</em></strong> -
			Authentifizierung ist ein Prozess, mit dessen Hilfe der <?query("/sys/modelname");?> die Identität eines Netzwerkgeräts prüft, das versucht, sich dem drahtlosen Netz anzuschließen. Bei der Verwendung des WEP-Sicherheitsprotokolls stehen Ihnen zwei Authentifizierungsmöglichkeiten für dieses Gerät zur Verfügung.<br> 
			<strong><em>Open System</em></strong> -
			Wählen Sie diese Option, damit alle drahtlosen Geräte mit dem <?query("/sys/modelname");?> kommunizieren können, bevor diese den für den Zugang zum Netzwerk erforderlichen Verschlüsselungsschlüssel bereitstellen müssen.<br>
			<strong><em>Shared Key</em></strong> -
			Wählen Sie diese Option, wenn drahtlose Geräte, die mit dem Router zu kommunizieren versuchen, den für den Zugang zum Netz erforderlichen Verschlüsselungsschlüssel bereitstellen müssen, bevor sie mit dem <?query("/sys/modelname");?> kommunizieren können.<br>
			<strong><em>WEP-Verschlüsselung</em></strong> -
			Wählen Sie die WEP-Verschlüsselungsstufe, die Sie auf Ihrem Netzwerk verwenden möchten. Unterstützt wird die 64-Bit und 128-Bit WEP-Verschlüsselung.<br>
			<strong><em>Schlüsseltyp</em></strong> -
			Die vom <?query("/sys/modelname");?> unterstützten Schlüsseltypen sind HEX (Hexadecimal) und ASCII (American Standard Code for Information Interchange). Sie können den Schlüsseltyp ändern, um Ihr eigenes drahtloses Netz Ihren Wünschen entsprechend anzupassen.<br>
			<strong><em>Schlüssel</em></strong> -
			Mithilfe der Schlüssel 1 - 4 können Sie drahtlose Verschlüsselungseinstellungen problemlos ändern, um ein sicheres Netzwerk zu gewährleisten. Wählen Sie einfach den spezifischen Schlüssel, der für die Verschlüsselung der drahtlosen Daten im Netzwerk verwendet werden soll.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>WPA/WPA2</strong><br>
			Wi-Fi Protected Access (oder Wi-Fi Protected Access 2) autorisiert und authentifiziert Benutzer im Funknetz. WPA verwendet eine leistungsstärkere Verschlüsselungsmethode als WEP und basiert auf einem Schlüssel, der in regelmäßigen zeitlichen Abständen automatisch geändert wird.
		</p>
		<p>
			<strong><em>Verschlüsselungstyp</em></strong> -
			Der <?query("/sys/modelname");?> unterstützt zwei verschiedene Verschlüsselungstypen, wenn WPA als Sicherheitstyp verwendet wird. Diese zwei Optionen sind TKIP (Temporal Key Integrity Protocol/Temporäres Schlüsselintegritätsprotokoll) und AES (Advanced Encryption Standard/Erweiterter Verschlüsselungsstandard).<br>
			<strong><em>PSK/EAP</em></strong> -
			Wird PSK gewählt, müssen Ihre drahtlosen Clients zur Authentifizierung einen Kennwortsatz angeben. Wird EAP gewählt, muss Ihr Netzwerk einen RADIUS-Server aufweisen, der die Authentifizierung Ihrer gesamten drahtlosen Clients handhabt.<br>
			<strong><em>Passphrase</em></strong> -
			(Kennwortsatz) - Ein solcher ist erforderlich, damit Ihre drahtlosen Clients mit Ihrem <?query("/sys/modelname");?> kommunizieren können. Wenn PSK gewählt wurde, geben Sie 8 bis 63 alphanumerische Zeichen ein. Schreiben Sie sich diesen Kennwortsatz unbedingt auf. Sie müssen ihn auf jedem anderen drahtlosen Gerät eingeben, das Sie Ihrem Netzwerk hinzufügen möchten.<br>
			<strong><em>802.1X</em></strong> -
			Bedeutet, dass die WPA-Authentifizierung in Verbindung mit einem RADIUS-Server verwendet wird, der in Ihrem Netzwerk vorhanden sein muss. Geben Sie die IP-Adresse, den Port und das "Shared Secret" ein, für das Ihr RADIUS-Server konfiguriert wurde. Darüber hinaus haben Sie die Option, Informationen für einen zweiten RADIUS-Server für den Fall einzugeben, dass Ihr Netzwerk zwei dieser Server aufweist, die Sie zur Authentifizierung drahtloser Clients verwenden.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="lan_setup"><h2>Netzwerk-Setup</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			Dies sind die Einstellungen der LAN-Schnittstelle des Geräts. Diese Einstellungen können als "private Einstellungen" angesehen werden. Sie können die LAN IP-Adresse nach Bedarf ändern. Die LAN-IP-Adresse ist privat für Ihr internes Netzwerk und im Internet nicht sichtbar. Die Standard-IP-Adresse ist 192.168.0.1 mit der Subnetzmaske 255.255.255.0.
			<br><br>
			<strong><em>IP-Adresse</em></strong> -
			 Die IP-Adresse des <?query("/sys/modelname");?>. Sie lautet standardmäßig 192.168.0.1.<br>
			<strong><em>Subnetzmaske</em></strong> -
			Die Subnetzmaske des <?query("/sys/modelname");?>, standardmäßig 255.255.255.0.<br>
			<strong><em>Lokaler Domänenname</em></strong> (optional) - Geben Sie den lokalen Domänennamen für Ihr Netzwerk ein.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong><em>DNS-Relais</em></strong> -
			Wenn DNS-Relais aktiviert ist, wird die LAN-IP-Adresse des Routers den DHCP-Clients des Routers als deren DNS-Server zugewiesen. Alle DNS-Anfragen, die bei dem Router eingehen, werden an Ihre DNS-Server des jeweiligen Internetdienstanbieters weitergeleitet. Ist DNS-Relais deaktiviert, wird der DNS-Server des Internetdienstanbieters allen DHCP-Clients zugewiesen.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>DHCP-Server</strong><br>
			DHCP ist die Abkürzung für Dynamic Host Configuration Protocol (Dynamisches Hostkonfigurationsprotokoll). Der DHCP-Server weist Geräten auf Anforderung IP-Adressen im Netz zu. Auf diesen Geräten muss dazu die Option "Obtain the IP address automatically" (IP-Adresse automatisch beziehen) gewählt sein. Standardmäßig ist der DHCP-Server auf dem <?query("/sys/modelname");?> aktiviert. Der DHCP-Adressenpool enthält den Bereich von IP-Adressen, der den Clients im Netzwerk automatisch zugewiesen wird.
		</p>
		<p>
			<strong>DHCP-Reservierung</strong><br>
			Geben Sie den "Computernamen", die "IP-Adresse" und die "MAC-Adresse" manuell für den PC ein, für den der Router die gleiche IP statisch zuweisen soll oder wählen Sie den PC von dem Dropdown-Menü, das aktuelle DHCP-Clients anzeigt.
		</p>
		<p>
			<strong><em>Start-IP-Adresse</em></strong> Die Start-IP-Adresse für die IP-Zuweisung des DHCP-Servers.<br>
			<strong><em>End-IP-Adresse</em></strong> Die End-IP-Adresse für die IP-Zuweisung des DHCP-Servers.<br>
			<strong><em>DHCP Lease</em></strong> Zeit Die Zeitdauer in Minuten für die IP-Lease.
		</p>
		<p>
			Die Informationen der dynamischen DHCP-Client-Computer, die mit der Einheit verbunden sind, werden in der Dynamischen DHCP Client-Tabelle angezeigt. In der Tabelle werden der Host-Name, die IP-Adresse, MAC-Addresse und abgelaufene Zeit des DHCP-Lease für jeden Client-Computer angezeigt.
		</p>
	</td>
</tr>
</table>
</div>

<div class="box">
<a name="lcd_setup"><h2>LCD-Setup</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			Die LCD-Setup-Seite steuert die Einstellungen des Anzeigebedienfeldes auf Ihrem <?query("/sys/modelname");?>. Auf ihr können Sie den Bildschirmschoner steuern und die Zeit festlegen, die Ihr Gerät inaktiv sein muss, bevor sich der LCD-Bildschirm ausschaltet.
			<br><br>
			<strong><em>Bildschirmschoner-Einstellung</em></strong> -
			Der Bildschirmschoner zeigt das Bild "screen_bg.jpg". Es ist im Stammverzeichnis der internen Festplattenlaufwerks abgelegt und zeigt das aktuelle Datum und die Uhrzeit, die sich nach dem Zufallsprinzip über das Bild bewegen. Wird dieses Bild nicht gefunden, bleibt der Hintergrund schwarz. Die "Timeout"-Einstellung gibt die Zeit in Minuten an, die es dauert, bevor das Gerät in den Bildschirmschoner-Modus wechselt, sofern es inaktiv ist. Sobald eine beliebige Taste auf dem Touchpad gedrückt wird, beendet das Gerät den Bildschirmschoner-Modus.<br>
			<strong><em>Anzeigeeinstellung</em></strong> -
			Diese Einstellung schaltet den LCD-Bildschirm aus, um Strom zu sparen, sobald das Gerät für eine bestimmte, im Feld "Timeout" angegebene Zeit inaktiv ist. Der LCD-Bildschirm wie wieder eingeschaltet, sobald eine beliebige Taste auf dem Touchpad gedrückt wird.<br>
		</p>
	</td>
</tr>
</table>
</div>
