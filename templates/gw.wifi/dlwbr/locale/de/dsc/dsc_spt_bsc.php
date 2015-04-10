<h1>SUPPORTMENU</h1>
<table border=0 cellspacing=0 cellpadding=0 width=750>
<tr>
	<td height=40>
		<p><font size=4><strong>Setup</strong></font></p>
		<p>
			<a name=01><strong>Internet-Setup</strong></a><br>
			Wenn Sie das Gerät zum ersten Mal konfigurieren, empfehlen wir, auf die Schaltfläche „Setup-Assistent für den Internetzugang“ zu klicken und den Anweisungen auf dem Bildschirm zu folgen. 
			Wenn Sie die Geräteeinstellungen manuell ändern oder konfigurieren möchten, klicken Sie auf „Manuelles Einrichten der Internetverbindung“.
		</p>
	</td>
</tr>
<tr>
	<td height=59>
		<p>
			<strong>Setup-Assistenten für den Internetzugang starten </strong><br>
			Klicken Sie auf diese Schaltfläche, um Ihren Router schnell und einfach in wenigen Schritten mit dem Internet zu verbinden.<br>
			<strong>Setup-Assistenten für die WLAN-Sicherheit starten </strong><br>
			Klicken Sie auf diese Schaltfläche, um Schritt für Schritt die Einstellungen für das drahtlose Netzwerk einschließlich der Sicherheitseinstellungen vorzunehmen.
		</p>
	</td>
</tr>
<tr><td height=32>&nbsp;</td></tr>
<tr>
	<td height=46>
		<p>
			<strong>Manuelles Einrichten der Internetverbindung</strong><br>
			Wählen Sie diese Option, wenn Sie die Einstellungen selbst vornehmen und den Router manuell mit dem Internet verbinden möchten.<br>
			<strong>Access Point-Modus</strong><br>
			Wenn Sie den „Access Point-Modus“ aktivieren, funktioniert das Gerät als drahtloser AP. Mit Ausnahme der Einstellungen für die drahtlose Verbindung werden alle NAT-Funktionen deaktiviert.<br>
			<strong>Internetverbindungstyp</strong><br>
			Die Internetverbindungseinstellungen werden benötigt, um den <?query("/sys/modelname");?> 
			mit dem Internet zu verbinden. Sämtliche Informationen, die Sie auf dieser Seite eingeben 
			müssen, werden Ihnen von Ihrem Internetdiensteanbieter mitgeteilt und werden als 
			&quot;Öffentliche Einstellungen&quot; bezeichnet. Wählen Sie die passende Option für Ihren 
			Internetdiensteanbieter. Wenn Sie sich nicht sicher sind, welche Option für Sie richtig ist, 
			wenden Sie sich an Ihren Internetdiensteanbieter.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=61>
		<p>
			<strong>Statische IP-Adresse</strong><br>
			Wählen Sie diese Option, wenn Sie von Ihrem Internetdiensteanbieter IP-Adresse, Subnetzmaske, 
			Standard-Gateway und eine DNS-Server-Adresse erhalten haben. Geben Sie diese Informationen in 
			die entsprechenden Felder ein. Wenn Sie sich nicht sicher sind, was Sie in diese Felder 
			eingeben sollen, wenden Sie sich an Ihren Internetdiensteanbieter.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=142>
		<p>
			<strong>Dynamische IP-Adresse</strong><br>
			Wählen Sie diese Option, wenn Ihr Internetdiensteanbieter Ihnen automatisch eine IP-Adresse 
			zuweist. Dies ist zum Beispiel häufig bei Internetverbindungen über Kabelmodem der Fall.
		</p>
		<p>
			<strong><em>Hostname </em></strong> (optional) -
			Das Feld Hostname ist optional, kann jedoch bei einigen Internetdiensteanbietern 
			erforderlich sein. Standardmäßiger Hostname ist die Modellnummer des Geräts.<br>
			<strong><em>MAC-Adresse </em></strong> (optional) -
			Das Feld MAC-Adresse (MAC, Media Access Control) kann bei einigen Internetdiensteanbietern erforderlich sein. Als 
			Standard-MAC-Adresse ist die MAC-Adresse der WAN-Schnittstelle des <?query("/sys/modelname");?> eingestellt. Mit der 
			Schaltfläche &quot;MAC-Adresse übernehmen&quot; können Sie automatisch die MAC-Adresse der Ethernetkarte kopieren, die im 
			für die Konfiguration des Geräts verwendeten Computer installiert ist. Das Feld muss nur dann ausgefüllt werden, wenn dies 
			vom Internetdiensteanbieter verlangt wird.<br>
			<strong><em>Primäre DNS-Adresse </em></strong> -
			Primäre DNS-IP-Adresse (DNS, Domain Name Server), die Sie von Ihrem Internetdiensteanbieter erhalten haben.<br>
			<strong><em>Sekundäre DNS-Adresse </em></strong> (optional) -
			Wenn Ihr Internetdiensteanbieter eine IP-Adresse für einen sekundären DNS-Server angegeben hat, geben Sie sie in dieses Feld ein.<br>
			<strong><em>MTU </em></strong> -
			MTU (Maximum Transmission/Transfer Unit, größtmögliche Übertragungseinheit) ist die größtmögliche 
			Paketgröße, die über ein Netzwerk übertragen werden kann. Dateneinheiten, die größer als die MTU sind, 
			werden in kleinere Pakete aufgeteilt. Der Standardwert für diese Option ist 1500. Wenn Sie diesen Wert 
			ändern, kann sich das nachteilig auf die Leistung des Routers auswirken. Ändern Sie diesen Wert nur, wenn 
			Sie dazu von einem Mitarbeiter des technischen Supports oder Ihrem Internetdiensteanbieter ausdrücklich 
			aufgefordert werden.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=47>
		<p>
			<strong>PPPoE</strong><br>
			Wählen Sie diese Option, wenn Ihr Internetdiensteanbieter die Verwendung einer PPPoE-Verbindung (PPPoE, Point to 
			Point Protocol over Ethernet) verlangt. Diese Option wird normalerweise von DSL-Anbietern verwendet. Wählen Sie 
			Dynamisches PPPoE, um automatisch eine IP-Adresse für die PPPoE-Verbindung zu erhalten (bei den meisten 
			PPPoE-Verbindungen erforderlich). Wählen Sie Statisches PPPoE, um eine statische IP-Adresse für die 
			PPPoE-Verbindung zu verwenden.
		</p>
		<p>
			<strong><em>Benutzername </em></strong> - Geben Sie Ihren PPPoE-Benutzernamen ein.<br>
			<strong><em>Kennwort </em></strong> - Geben Sie Ihr PPPoE-Kennwort ein.<br>
			<strong><em>Servicename </em></strong> (optional) -
			Geben Sie hier den Servicenamen ein, wenn Ihr Internetdiensteanbieter einen Servicenamen für die 
			PPPoE-Verbindung verwendet.<br>
			<strong><em>IP-Adresse </em></strong> -
			Diese Option ist nur verfügbar, wenn Sie statisches PPPoE verwenden. Geben Sie die statische IP-Adresse 
			für die PPPoE-Verbindung ein.<br>
			<strong><em>MAC-Adresse </em></strong> (optional) -
			Das Feld MAC-Adresse (MAC, Media Access Control) kann bei einigen Internetdiensteanbietern erforderlich 
			sein. Als Standard-MAC-Adresse ist die MAC-Adresse der WAN-Schnittstelle des <?query("/sys/modelname");?> 
			eingestellt. Mit der Schaltfläche &quot;MAC-Adresse übernehmen&quot; können Sie automatisch die 
			MAC-Adresse der Ethernetkarte kopieren, die im für die Konfiguration des Geräts verwendeten Computer 
			installiert ist. Das Feld muss nur dann ausgefüllt werden, wenn dies vom Internetdiensteanbieter 
			verlangt wird.<br>
			<strong><em>Primäre DNS-Adresse </em></strong> -
			Primäre DNS-IP-Adresse (DNS, Domain Name Server), die Sie von Ihrem Internetdiensteanbieter erhalten 
			haben. Sie müssen diese Information nur dann eingeben, wenn Sie statisches PPPoE gewählt haben. Wenn 
			Sie dynamisches PPPoE gewählt haben, lassen Sie dieses Feld auf dem Standardwert. Ihr 
			Internetdiensteanbieter wird diese Information automatisch übermitteln.<br>
			<strong><em>Sekundäre DNS-Adresse </em></strong> (optional) -
			Wenn Ihr Internetdiensteanbieter eine IP-Adresse für einen sekundären DNS-Server angegeben hat, geben 
			Sie sie in dieses Feld ein.<br>
			<strong><em>Maximale Leerlaufzeit </em></strong> -
			Zeitdauer, nach der die PPPoE-Verbindung bei Inaktivität durch das Gerät getrennt wird. Geben Sie eine 
			maximale Leerlaufzeit (in Minuten) ein, für die eine ungenutzte Internetverbindung aufrechterhalten 
			werden soll. Wenn über einen längeren Zeitraum, als in der maximalen Leerlaufzeit definiert, keine 
			Aktivität festgestellt wird, wird die Verbindung getrennt. Diese Option gilt nur für den Verbindungsmodus 
			Verbinden bei Bedarf.<br>
			<strong><em>MTU </em></strong> -
			MTU (Maximum Transmission/Transfer Unit, größtmögliche Übertragungseinheit) ist die größtmögliche Paketgröße, 
			die über ein Netzwerk übertragen werden kann. Dateneinheiten, die größer als die MTU sind, werden in kleinere 
			Pakete aufgeteilt. Der Standardwert für diese Option ist 1492. Wenn Sie diesen Wert ändern, kann sich das 
			nachteilig auf die Leistung des Routers auswirken. Ändern Sie diesen Wert nur, wenn Sie dazu von einem Mitarbeiter 
			des technischen Supports oder Ihrem Internetdiensteanbieter ausdrücklich aufgefordert werden.<br>
			<strong><em>Verbindungsmodus</em></strong> -
			Wählen Sie Immer aktiv, wenn Sie möchten, dass die PPPoE-Verbindung niemals durch den Router getrennt wird. 
			Wählen Sie die Option Manuell, wenn Sie selbst steuern möchten, wann der Router mit dem Internet verbunden 
			bzw. getrennt werden soll. Die Option Verbinden bei Bedarf bewirkt, dass der Router nur dann eine Verbindung 
			mit dem Internet herstellt, wenn ein Gerät in Ihrem Netzwerk auf eine Internetressource zugreift.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>PPTP</strong><br>
			Wählen Sie diese Option, wenn Ihr Internetdiensteanbieter eine PPTP-Verbindung (PPTP, Point to Point Tunneling 
			Protocol) anbietet und Sie einen Benutzernamen sowie ein Kennwort für die Internetverbindung erhalten haben. 
			Aktivieren Sie das Kontrollkästchen Dynamisches PPTP, um automatisch eine IP-Adresse für die PPTP-Verbindung zu 
			beziehen. Wählen Sie Statisches PPTP, um eine statische IP-Adresse für die PPTP-Verbindung zu verwenden.
		</p>
		<p>
			<strong><em>IP-Adresse </em></strong> - Geben Sie die IP-Adresse ein, die Ihnen Ihr Internetdiensteanbieter zugeteilt hat.<br>
			<strong><em>Subnetzmaske </em></strong> - Geben Sie die Subnetzmaske ein, die Ihnen Ihr Internetdiensteanbieter mitgeteilt hat.<br>
			<strong><em>Gateway</em></strong> - Geben Sie die IP-Adresse des Gateways ein, die Ihnen Ihr Internetdiensteanbieter mitgeteilt hat.<br>
			<strong><em>DNS - </em></strong>Geben Sie die DNS-Adresse ein, die Sie von Ihrem Internetdiensteanbieter erhalten haben.<br>
			<strong><em>Server-IP </em></strong> -
			Geben Sie die IP-Adresse des von Ihrem Internetdiensteanbieter bereitgestellten Servers ein, mit dem Sie sich verbinden.<br>
			<strong><em>Konto </em></strong> - Geben Sie Ihren PPTP-Benutzernamen ein.<br>
			<strong><em>Kennwort </em></strong> - Geben Sie Ihr PPTP-Kennwort ein.<br>
			<strong><em>Maximale Leerlaufzeit </em></strong> -
			Zeitdauer, nach der die PPTP-Verbindung bei Inaktivität durch das Gerät getrennt wird. Geben Sie eine maximale 
			Leerlaufzeit (in Minuten) ein, für die eine ungenutzte Internetverbindung aufrechterhalten werden soll. Wenn 
			über einen längeren Zeitraum, als in der maximalen Leerlaufzeit definiert, keine Aktivität festgestellt wird, 
			wird die Verbindung getrennt. Diese Option gilt nur für den Verbindungsmodus Verbinden bei Bedarf.<br>
			<strong><em>MTU </em></strong> -
			MTU (Maximum Transmission/Transfer Unit, größtmögliche Übertragungseinheit) ist die größtmögliche Paketgröße, die über 
			ein Netzwerk übertragen werden kann. Dateneinheiten, die größer als die MTU sind, werden in kleinere Pakete aufgeteilt. 
			Der Standardwert für diese Option ist 1400. Wenn Sie diesen Wert ändern, kann sich das nachteilig auf die Leistung des 
			Routers auswirken. Ändern Sie diesen Wert nur, wenn Sie dazu von einem Mitarbeiter des technischen Supports oder Ihrem 
			Internetdiensteanbieter ausdrücklich aufgefordert werden.<br>
			<strong><em>Verbindungsmodus</em></strong> -
			Wählen Sie Immer aktiv, wenn Sie möchten, dass die PPTP-Verbindung niemals durch den Router getrennt wird. Wählen 
			Sie die Option Manuell, wenn Sie selbst steuern möchten, wann der Router mit dem Internet verbunden bzw. getrennt 
			werden soll. Die Option Verbinden bei Bedarf bewirkt, dass der Router nur dann eine Verbindung mit dem Internet 
			herstellt, wenn ein Gerät in Ihrem Netzwerk auf eine Internetressource zugreift.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>L2TP </strong><br>
			Wählen Sie diese Option, wenn Ihr Internetdiensteanbieter eine L2TP-Verbindung (L2TP, Layer 2 Tunneling Protocol) 
			anbietet und Sie einen Benutzernamen sowie ein Kennwort für die Internetverbindung erhalten haben. Aktivieren Sie 
			das Kontrollkästchen Dynamisches L2TP, um automatisch eine IP-Adresse für die L2TP-Verbindung zu beziehen. Wählen 
			Sie Statisches L2TP, um eine statische IP-Adresse für die L2TP-Verbindung zu verwenden.
		</p>
		<p>
			<strong><em>IP-Adresse </em></strong> - Geben Sie die IP-Adresse ein, die Ihnen Ihr Internetdiensteanbieter zugeteilt hat.<br>
			<strong><em>Subnetzmaske </em></strong> - Geben Sie die Subnetzmaske ein, die Ihnen Ihr Internetdiensteanbieter mitgeteilt hat.<br>
			<strong><em>Gateway</em></strong> - Geben Sie die IP-Adresse des Gateways ein, die Ihnen Ihr Internetdiensteanbieter mitgeteilt hat.<br>
			<strong><em>DNS</em></strong> - Geben Sie die DNS-Adresse ein, die Sie von Ihrem Internetdiensteanbieter erhalten haben.<br>
			<strong><em>Server-IP </em></strong> -
			Geben Sie die IP-Adresse des von Ihrem Internetdiensteanbieter bereitgestellten Servers ein, mit dem Sie sich verbinden.<br>
			<strong><em>L2TP-Konto </em></strong> - Geben Sie Ihren L2TP-Benutzernamen ein.<br>
			<strong><em>L2TP-Kennwort </em></strong> - Geben Sie Ihr L2TP-Kennwort ein.<br>
			<strong><em>Maximale Leerlaufzeit </em></strong> -
			Zeitdauer, nach der die L2TP-Verbindung bei Inaktivität durch das Gerät getrennt wird. Geben Sie eine maximale Leerlaufzeit 
			(in Minuten) ein, für die eine ungenutzte Internetverbindung aufrechterhalten werden soll. Wenn über einen längeren Zeitraum, 
			als in der maximalen Leerlaufzeit definiert, keine Aktivität festgestellt wird, wird die Verbindung getrennt. Diese Option 
			gilt nur für den Verbindungsmodus Verbinden bei Bedarf.<br>
			<strong><em>MTU</em></strong> -
			MTU (Maximum Transmission/Transfer Unit, größtmögliche Übertragungseinheit) ist die größtmögliche Paketgröße, die über ein 
			Netzwerk übertragen werden kann. Dateneinheiten, die größer als die MTU sind, werden in kleinere Pakete aufgeteilt. Der 
			Standardwert für diese Option ist 1400. Wenn Sie diesen Wert ändern, kann sich das nachteilig auf die Leistung des Routers 
			auswirken. Ändern Sie diesen Wert nur, wenn Sie dazu von einem Mitarbeiter des technischen Supports oder Ihrem 
			Internetdiensteanbieter ausdrücklich aufgefordert werden.  
			<strong><em>Verbindungsmodus</em></strong> -
			Wählen Sie Immer aktiv, wenn Sie möchten, dass 
			die L2TP-Verbindung zu keinem Zeitpunkt durch den Router getrennt werden soll. Wählen Sie die Option Manuell, wenn Sie 
			selbst steuern möchten, wann der Router mit dem Internet verbunden bzw. getrennt werden soll. Die Option Verbinden bei 
			Bedarf bewirkt, dass der Router nur dann eine Verbindung mit dem Internet herstellt, wenn ein Gerät in Ihrem Netzwerk 
			auf eine Internetressource zugreift.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Russia PPTP (Dual Access)</strong><br>
			Um eine Russia PPTP Internetverbindung zu konfigurieren, gehen Sie, wie vorher für 
			PPTP-Verbindungen beschrieben, vor.   Wenn eine statische Route von Ihrem Internetanbieter
			eingerichtet werden muss, finden Sie nähere Informationen zur weiteren Einrichtung unter der
			&quot;Routing&quot;-Funktion im Menü &quot;ERWEITERT&quot;.

		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Russia PPPoE (Dual Access)</strong><br>
			 Einige PPPoE-Verbindungen verwenden zusätzlich zu den globalen IP-Einstellungen eine statische 
			 IP-Route zum Internetdienstanbieter für die Verbindung. Das macht einen zusätzlichen Schritt
			 erforderlich, in dem IP-Einstellungen für den physischen WAN-Port festgelegt werden.   Um eine 
			 Russia PPPoE Internetverbindung zu konfigurieren, gehen Sie, wie vorher für PPPoE beschrieben, 
			 vor und fügen Sie die physischen WAN IP-Einstellungen den Anweisungen des Internetdienstanbieters
			 entsprechend hinzu.   Wenn eine statische Route von Ihrem Internetanbieter eingerichtet werden
			 muss, finden Sie nähere Informationen zur weiteren Einrichtung unter der &quot;Routing&quot;
			 -Funktion im Menü &quot;ERWEITERT&quot;.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<a name=02><strong>Einrichten der Drahtlosverbindung</strong></a><br>
			Die Seite Einrichten der Drahtlosverbindung beinhaltet die 
			Einstellungen für den Access Point-Teil des <?query("/sys/modelname");?>. 
			Auf dieser Seite können Sie Ihr drahtloses Netzwerk anpassen oder 
			den <?query("/sys/modelname");?> so konfigurieren, dass er sich in 
			ein bereits vorhandenes drahtloses Netzwerk einfügt.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Wi-Fi Protected Setup (unter Windows Vista auch WCN 2.0 genannt)</strong><br>
			Diese Funktion bietet einen intuitiveren Weg, die drahtlose Sicherheit zwischen dem Router und dem 
			drahtlosen Client einzurichten. Dafür gibt es zwei Möglichkeiten: Über die PIN-Nummer oder die Taste. 
			Die drahtlose Sicherheit zwischen dem Router und dem drahtlosen Client kann automatisch eingerichtet 
			werden, indem Sie die PIN-Nummer des Geräts in das Dienstprogramm der WLAN-Karte eingeben oder in das 
			Dienstprogramm von Windows Vista für drahtlose Clients, wenn die WLAN-Karte über einen zertifizierten 
			Windows Vista-Treiber verfügt. Die WLAN-Karte muss das Wi-Fi Protected Setup unterstützen, um den Vorteil 
			dieser Funktion nutzen zu können.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Name des drahtlosen Netzwerks</strong><br>
			Dies ist der Name für Ihr drahtloses Netzwerk, auch als SSID (Service Set Identifier) bezeichnet. Standardmäßig 
			lautet die SSID des <?query("/sys/modelname");?> &quot;dlink&quot;. Die SSID kann auf einfache Weise geändert 
			werden, um ein neues drahtloses Netzwerk einzurichten oder um den <?query("/sys/modelname");?> einem vorhandenen 
			drahtlosen Netzwerk hinzuzufügen.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Drahtloskanal</strong><br>
			Gibt an, auf welchem Kanal der <?query("/sys/modelname");?> betrieben wird. Standardmäßig ist Kanal 6 eingestellt. Sie können 
			die Kanaleinstellung ändern, um den Kanal an ein vorhandenes drahtloses Netzwerk anzupassen oder um ein neues drahtloses 
			Netzwerk zu konfigurieren. Aktivieren Sie das Kontrollkästchen Automatische Kanalerkennung aktivieren, damit der 
			<?query("/sys/modelname");?> den Kanal auswählt, in dem er betrieben wird. Dies ist die empfohlene Einstellung, da der Router 
			in diesem Fall den Kanal mit den geringsten Interferenzen wählt.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>WMM</strong><br>
			Wählen Sie Aktivieren, um QoS für die drahtlose Schnittstelle des <?query("/sys/modelname");?> zu aktivieren.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Verborgenes WLAN aktivieren </strong><br>
			Wählen Sie Aktiviert, wenn Sie nicht möchten, dass die SSID Ihres drahtlosen Netzwerks über den 
			<?query("/sys/modelname");?> gesendet wird. In diesem Fall wird die SSID des <?query("/sys/modelname");?> 
			nicht in Netzübersichten angezeigt, und Sie müssen die SSID Ihres <?query("/sys/modelname");?> selbst 
			kennen und manuell eingeben, wenn Sie Ihre drahtlosen Clients mit dem Router verbinden möchten. Diese 
			Option ist standardmäßig aktiviert.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>WLAN-Sicherheitsmodus</strong><br>
			Um die Integrität der über das drahtlose Netzwerk übermittelten Daten zu 
			schützen, ist es wichtig, Ihr drahtloses Netzwerk zu sichern. Für den 
			<?query("/sys/modelname");?> stehen vier WLAN-Sicherheitsmodi zur Verfügung: 
			WEP, Nur WPA, Nur WPA2 und WPA/WPA2 (automatische Erkennung).
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>WEP </strong><br>
			WEP steht für Wired Equivalent Protocol und ist ein gängiges Sicherheitsprotokoll für drahtlose lokale Netzwerke (WLAN). 
			Es bietet Sicherheit durch die Verschlüsselung der über das WLAN übertragenen Daten. Der <?query("/sys/modelname");?> 
			unterstützt zwei Stufen der WEP-Verschlüsselung: 64 Bit und 128 Bit. Standardmäßig ist WEP deaktiviert. Sie können die 
			WEP-Einstellung ändern, um sie an ein vorhandenes drahtloses Netzwerk anzupassen oder um ein drahtloses Netzwerk zu 
			konfigurieren.
		</p>
		<p>
			<strong><em>Authentifizierung</em></strong> -
			Unter Authentifizierung versteht man ein Verfahren, in dem die Identität des jeweiligen Netzwerkgeräts durch den 
			<?query("/sys/modelname");?> überprüft wird, mit dem eine Verbindung mit dem drahtlosen Netzwerk hergestellt werden 
			soll. Bei der Verwendung von WEP stehen für den Router zwei Arten der Authentifizierung zur Verfügung.<br> 
			<strong><em>Offenes System</em></strong> -
			Wählen Sie diese Option, wenn Sie möchten, dass alle drahtlosen Geräte mit dem <?query("/sys/modelname");?> 
			kommunizieren können, bevor sie den Verschlüsselungsschlüssel für den Netzwerkzugang übermitteln müssen.<br>
			<strong><em>Gemeinsamer Schlüssel</em></strong> -
			Wählen Sie diese Option, wenn jedes drahtlose Gerät, das mit dem <?query("/sys/modelname");?> kommunizieren möchte, 
			zuvor den Verschlüsselungsschlüssel für den Zugriff auf das Netzwerk übermitteln muss, bevor eine Kommunikation mit 
			dem <?query("/sys/modelname");?> möglich ist.<br>
			<strong><em>WEP-Verschlüsselung</em></strong> -
			Wählen Sie die gewünschte Stufe für die WEP-Verschlüsselung. Es wird die WEP-Verschlüsselung mit 64 Bit bzw. 128 Bit 
			unterstützt.<br>
			<strong><em>Schlüsselformat</em></strong> -
			Der <?query("/sys/modelname");?> unterstützt die Schlüsselformate HEX (hexadezimal) und ASCII (American Standard Code 
			for Information Interchange). Sie können das Schlüsselformat ändern, um es an ein vorhandenes drahtloses Netzwerk 
			anzupassen oder um ein neues drahtloses Netzwerk zu konfigurieren.<br>
			<strong><em>Schlüssel</em></strong> -
			Mit den Schlüsseln 1-4 können Sie die Verschlüsselungseinstellungen für drahtlose Netzwerke auf einfache Weise 
			ändern und so die Sicherheit des Netzwerks dauerhaft gewährleisten. Wählen Sie einfach den Schlüssel aus, der für 
			die Verschlüsselung der drahtlos übertragenen Daten verwendet werden soll.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>WPA-Personal</strong><br>
			WPA steht für Wi-Fi Protected Access. Bei dieser Verschlüsselungsmethode werden die Benutzer für das drahtlose 
			Netzwerk autorisiert und authentifiziert. WPA ist sicherer als WEP und basiert auf einem Schlüssel, der sich in 
			regelmäßigen Abständen automatisch ändert.
		</p>
		<p>
			<strong><em>Verschlüsselungstyp</em></strong> -
			Bei Verwendung von WPA unterstützt der <?query("/sys/modelname");?> zwei verschiedene Verschlüsselungstypen: 
			TKIP (Temporal Key Integrity Protocol) und AES (Advanced Encryption Standard).<br>
			<strong><em>PSK/EAP</em></strong> -
			Wenn Sie PSK wählen, müssen die drahtlosen Clients eine Passphrase zur Authentifizierung übermitteln. Wenn Sie EAP 
			wählen, muss sich in Ihrem Netzwerk ein RADIUS-Server befinden, der die Authentifizierung für sämtliche drahtlosen 
			Clients übernimmt.<br>
			<strong><em>Passphrase</em></strong> -
			Diese müssen Ihre drahtlosen Clients übermitteln, um mit dem <?query("/sys/modelname");?> zu kommunizieren, sofern Sie 
			die Option PSK gewählt haben. Geben Sie 8 bis 63 alphanumerische Zeichen ein. Schreiben Sie sich diese Passphrase auf, 
			da sie auf jedem einzelnen drahtlosen Gerät eingegeben werden muss, das mit dem drahtlosen Netzwerk verbunden werden 
			soll.<br>
			<strong><em>802.1X</em></strong> -
			Dieses Mittel zur WPA-Authentifizierung wird in Verbindung mit einem RADIUS-Server verwendet, der sich in Ihrem Netzwerk 
			befinden muss. Geben Sie die IP-Adresse, den Port und den gemeinsamen geheimen Schlüssel ein, für die der RADIUS-Server in 
			Ihrem Netzwerk konfiguriert ist. Für den Fall, dass sich in Ihrem Netzwerk zwei RADIUS-Server zur Authentifizierung der 
			drahtlosen Clients befinden, haben Sie die Möglichkeit, auch die Informationen für den zweiten RADIUS-Server einzugeben.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>WPA2</strong><br>
			Die Verschlüsselungsmethode WPA2 (Wi-Fi Protected Access 2) autorisiert und authentifiziert Benutzer für das drahtlose 
			Netzwerk. WPA2 ist sicherer als WEP und basiert auf einem Schlüssel, der sich in regelmäßigen Abständen automatisch 
			ändert.
		</p>
		<p>
			<strong><em>Verschlüsselungstyp</em></strong> -
			Bei Verwendung von WPA unterstützt der <?query("/sys/modelname");?> zwei verschiedene Verschlüsselungstypen: TKIP 
			(Temporal Key Integrity Protocol) und AES (Advanced Encryption Standard).<br>
			<strong><em>PSK/EAP</em></strong> -
			Wenn Sie PSK wählen, müssen die drahtlosen Clients eine Passphrase zur Authentifizierung übermitteln. Wenn Sie EAP 
			wählen, muss sich in Ihrem Netzwerk ein RADIUS-Server befinden, der die Authentifizierung für sämtliche drahtlosen 
			Clients übernimmt.<br>
			<strong><em>Passphrase</em></strong> -
			Diese müssen Ihre drahtlosen Clients übermitteln, um mit dem <?query("/sys/modelname");?> zu kommunizieren, sofern Sie 
			die Option PSK gewählt haben. Geben Sie 8 bis 63 alphanumerische Zeichen ein. Schreiben Sie sich diese Passphrase auf, 
			da sie auf jedem einzelnen drahtlosen Gerät eingegeben werden muss, das mit dem drahtlosen Netzwerk verbunden werden 
			soll.<br>
			<strong><em>802.1X</em></strong> -
			Diese Methode zur WPA2-Authentifizierung kann nur in Verbindung mit einem RADIUS-Server verwendet werden. Geben Sie die 
			IP-Adresse, den Port und den gemeinsamen geheimen Schlüssel ein, für die der RADIUS-Server in Ihrem Netzwerk konfiguriert 
			ist. Für den Fall, dass sich in Ihrem Netzwerk zwei RADIUS-Server zur Authentifizierung der drahtlosen Clients befinden, 
			haben Sie die Möglichkeit, auch die Informationen für den zweiten RADIUS-Server einzugeben.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
 	<td height=20>
		<p>
			<strong>WPA2-Auto</strong><br>
			Mit dieser Option können sich sowohl WPA2- als auch WPA-Clients gleichzeitig mit dem <?query("/sys/modelname");?> 
			verbinden.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<a name=03><strong>Einrichten eines LAN</strong></a><br>
			Hier werden die IP-Einstellungen der LAN-Schnittstelle des Geräts festgelegt. Diese Einstellungen werden auch als 
			&quot;Private Einstellungen&quot; bezeichnet. Sie können die LAN-IP-Adresse bei Bedarf ändern. Die LAN-IP-Adresse 
			wird nur intern verwendet und kann aus dem Internet nicht eingesehen werden. Die Standard-IP-Adresse ist 192.168.0.1, 
			die Subnetzmaske 255.255.255.0.<br><br>
			<strong><em>IP-Adresse</em></strong> -
			Die IP-Adresse des <?query("/sys/modelname");?>. Standardmäßig ist 192.168.0.1 eingestellt.<br>
			<strong><em>Subnetzmaske</em></strong> -
			Die Subnetzmaske des <?query("/sys/modelname");?>. Standardmäßig ist 255.255.255.0 eingestellt.<br>
			<strong><em>Lokaler Domänenname</em></strong> (optional) - Geben Sie den lokalen Domänennamen für das Netzwerk ein.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong><em>DNS-Relay</em></strong> -
			Wenn „DNS-Relay“ aktiviert ist, wird den DHCP-Clients die IP-Adresse des Routers als DNS-Server zugeteilt. 
			Alle DNS-Anfragen an den Router werden an die DNS-Server Ihres Internetdiensteanbieters weitergeleitet. 
			Wenn DNS-Relay deaktiviert ist, werden den DHCP-Clients vom Router die DNS-Server des 
			Internetdiensteanbieters zugewiesen.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>DHCP Server</strong><br>
			DHCP steht für Dynamic Host Configuration Protocol. Wenn Netzwerkgeräte im Netzwerk eine IP-Adresse anfordern, 
			teilt der DHCP-Server sie ihnen zu. Für die Geräte muss die Option &quot;IP-Adresse automatisch beziehen&quot; 
			aktiviert sein. Standardmäßig ist der DHCP-Server auf dem <?query("/sys/modelname");?> aktiviert. Der 
			DHCP-Adressenpool enthält die IP-Adressen, die den Netzwerk-Clients automatisch zugewiesen werden.
		</p>
		<p>
			<strong>DHCP-Reservierung</strong><br>
			Geben Sie den &quot;Computernamen&quot;, die &quot;IP-Adresse&quot; und die &quot;MAC-Adresse&quot; für 
			den Computer manuell ein, dem der Router statisch dieselbe IP-Adresse zuweisen soll, oder wählen Sie den 
			Computer im Dropdown-Menü aus, das die aktuellen DHCP-Clients anzeigt.
		</p>
		<p>
			<strong><em>Erste IP-Adresse</em></strong> Erste IP-Adresse des DHCP-Adresspools.<br>
			<strong><em>Letzte IP-Adresse</em></strong> Letzte IP-Adresse des DHCP-Adresspools.<br>
			<strong><em>Gültigkeitsdauer</em></strong> Die Gültigkeitsdauer in Minuten automatisch vergebener IP-Adressen.
		</p>
		<p>
			In der Liste der dynamischen DHCP-Clients werden die mit dem Gerät verbundenen dynamischen DHCP-Clients 
			angezeigt. Für jeden Client werden Hostname, IP-Adresse, MAC-Adresse und Ablaufzeit der IP-Adresse angezeigt.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=33>
		<p>
			<strong><a name=04>Uhrzeit und Datum</a></strong>
		</p>
		<p>
			Die Einstellungen der Zeitkonfiguration werden vom Router für die Synchronisation zeitgesteuerter 
			Dienste und zur Aufzeichnung von Systemmeldungen und -ereignissen verwendet. Wählen Sie die Ihrem 
			Standort entsprechende Zeitzone. Die Zeit kann manuell eingestellt werden, oder das Gerät stellt 
			eine Verbindung zu einem NTP-Server (NTP, Network Time Protocol) her, um die Uhrzeit abzurufen. 
			Unter Sommerzeit können Sie den Zeitraum für die Sommerzeit angeben, damit sich das System 
			automatisch anpasst.
		</p>
		<p>
			<strong><em>Zeitzone</em></strong> - Wählen Sie die Zeitzone für die Region, in der Sie sich befinden.<br>
			<strong><em>Sommerzeit</em></strong> -
			Wenn für Ihren Standort Sommerzeit gilt, aktivieren Sie diese Option und geben Sie Monat, Woche, 
			Tag und Zeit für Beginn und Ende dieser Periode ein.<br>
			<strong><em>Automatische Zeitkonfiguration</em></strong> -
			Wählen Sie einen D-Link-Zeitserver aus, mit dem der <?query("/sys/modelname");?> die Zeit 
			synchronisieren soll. Das Intervall für die Kommunikation des <?query("/sys/modelname");?> 
			mit dem D-Link-NTP-Server ist auf 7 Tage eingestellt.<br>
			<strong><em>Datum und Zeit manuell einstellen</em></strong> -
			Wählen Sie diese Option, wenn Sie die Zeit manuell angeben möchten. Geben Sie Jahr, Monat, Tag, 
			Stunde, Minute und Sekunden ein. Oder klicken Sie auf die Schaltfläche Zeiteinstellungen Ihres 
			Computers kopieren, um die Systemzeit von dem Computer zu kopieren, mit dem Sie auf die 
			Verwaltungsoberfläche zugreifen.
		</p>
	</td>
</tr>
<tr><td height=2>&nbsp;</td></tr>
<tr><td height=2>&nbsp;</td></tr>
<tr>
	<td height=44>
		<p>
			<strong><a name=05>Kindersicherung</a></strong>
		</p>
		<p>
			Neben der Möglichkeit, bestimmte Geräte vom Zugriff auf Ihr Netzwerk und das Internet auszuschließen, 
			kann der <?query("/sys/modelname");?> auch so konfiguriert werden, dass den Computern in Ihrem 
			Netzwerk der Zugriff auf bestimmte Websites anhand des Domänennamens oder bestimmter Schlüsselwörter 
			gestattet bzw. verweigert wird.
		</p>
		<p>
			<strong>Kindersicherung</strong><br>
			Mit Hilfe der Kindersicherung können Sie den Computern in Ihrem Netzwerk den Zugriff auf bestimmte Websites 
			anhand bestimmter Schlüsselwörter oder Domänennamen gestatten bzw. verweigern. Wählen Sie 
			&quot;Website-Filterung aktivieren und für Computer den Zugang nur zu diesen Sites zulassen&quot;, um den 
			Computern in Ihrem Netzwerk nur den Zugriff auf die angegebenen URLs und Domänennamen zu gestatten. Wählen Sie 
			&quot;Website-Filterung aktivieren und für Computer den Zugang nur zu diesen Websites verweigern&quot;, um den 
			Computern in Ihrem Netzwerk den Zugriff auf die angegebenen URLs und Domänennamen zu verweigern.
		</p>
		<p>
			<span class="style1">Beispiel 1:</span><br>
			Wenn Sie LAN-Benutzern den Zugriff auf alle Websites mit einer URL, die „shopping“ enthält, 
			verweigern möchten, müssen Sie &quot;Website-Filterung aktivieren und für Computer den Zugang 
			nur zu diesen Sites verweigern&quot; wählen. Tragen Sie anschließend &quot;shopping&quot; in 
			die Liste der Website-Filterregeln ein. Folgende Websites wären dann zum Beispiel für die 
			LAN-Benutzer gesperrt, da in der URL das Schlüsselwort enthalten ist:<br>
			<a href="http://shopping.yahoo.com/">http://shopping.yahoo.com/</a><br>
			<a href="http://shopping.msn.com/">http://shopping.msn.com/</a>
		</p>
		<p>
			<span class="style1">Beispiel 2:</span><br>
			Wenn Sie möchten, dass Ihre Kinder nur auf bestimmte Websites zugreifen können, wählen Sie 
			&quot;Website-Filterung aktivieren und für Computer den Zugang nur zu diesen Websites zulassen&quot;. 
			Geben Sie anschließend die Domänen ein, auf die Ihre Kinder zugreifen dürfen.
		</p>
		<ul>
			<li>Google.com </li>
			<li>Cartoons.com </li>
			<li>Discovery.com </li>
		</ul>
	</td>
</tr>
</table>
