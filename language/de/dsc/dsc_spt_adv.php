<div class="box">
<a name="port_forwarding"><h2>Portweiterleitung</h2></a>
	<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=228>
		<p>
			Mithilfe der erweiterten Portweiterleitungsoption können Internetbenutzer auf Dienste in Ihrem LAN zugreifen. Sie dient dazu, Online-Dienste wie FTP, Web- oder Spieleserver als Host bereitzustellen. Dazu legen Sie für jeden Eintrag einen öffentlichen (Public) Port auf Ihrem Router zur Weiterleitung an eine interne LAN-IP-Adresse und einen LAN-Port fest.
		</p>
		<p>
			Erweiterte Portweiterleitungsparameter<br>
			<strong><em>Name</em></strong> -
			Weisen Sie dem virtuellen Server einen aussagefähigen Namen zu, z. B. Webserver. Auf der Dropdown-Liste "Anwendungsname" stehen Ihnen einige virtuelle Servertypen zur Auswahl zu Verfügung. Bei Wahl eines Eintrags werden einige Parameter automatisch mit Standardwerten für diesen Servertyp angegeben.<br>
			<strong><em>IP-Adresse </em></strong> -
			Die IP-Adresse des Systems in Ihrem internen Netz, das den virtuellen Dienst liefert. Die Adresse könnte z. B. 192.168.0.50 sein. Sie können einen Computer aus der Liste von DHCP-Clients im Dropdown-Menü "Computername" auswählen oder manuell die IP-Adresse des Servercomputers eingeben.<br>
			<strong><em>Anwendungsname  </em></strong> -
			Eine Liste vordefinierter populärer Anwendungen, die Benutzer zur schnelleren Konfiguration wählen können.<br>
			<strong><em>Computername </em></strong> - Eine Liste der DHCP-Clients.<br>
			<strong><em>Datenverkehrstyp</em></strong> -
			Wählen Sie das vom System verwendete Protokoll. Die allgemein gebräuchlichen Optionen -- UDP, TCP und beide UDP und TCP -- können von dem Dropdown-Menü gewählt werden.<br>
			<strong><em>Privater Port </em></strong> -
			Der Port, der auf Ihrem internen Netz verwendet werden soll.<br>
			<strong><em>Öffentlicher Port </em></strong> -
			Der Port, auf den vom Internet aus zugegriffen wird.<br>
		</p>
	</td>
</tr>
 </table>
 </div>
 
 
<div class="box">
<a name="application_rules"><h2>Anwendungsregeln</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=64> 
Bestimmte Anwendungen, wie z. B. Internetspiele, Videokonferenzen, Internettelefonie und andere, erfordern mehrere Verbindungen. Diese Anwendungen funktionieren nicht richtig über NAT (Network Address Translation). Wenn Sie solche Anwendungen ausführen müssen, geben Sie den Port ein, der einer Anwendung in der Regel im Feld "Trigger Port" zugeordnet ist, wählen Sie den Protokolltyp TCP (Transmission Control Protocol) oder UDP (User Datagram Protocol) und geben Sie die öffentlichen Ports an, die dem Trigger Port im Feld "Firewall-Port" zugeordnet sind, um sie für den eingehenden Datenverkehr zu öffnen. Im Anwendungsnamen-Dropdown-Menü finden Sie bereits festgelegte und bekannte Anwendungen.
 <br>

<strong><em>Name </em></strong> -Der Name, der auf die Anwendung verweist. <br>
<strong><em>Trigger Port </em></strong>- Der zum Start der Anwendung verwendete Port. Es kann sich dabei um einen einzelnen Port oder um Portbereiche handeln. <br>
<strong><em>Datenverkehrstyp </em></strong> - Dies ist das zum Auslösen der Anwendung verwendete Protokoll. <br>
<strong><em>Firewall-Port </em></strong> - Der Port auf der WAN-Seite, der zum Zugriff auf die Anwendung verwendet wird. Sie können einen einzelnen Port oder Portbereiche angeben. Trennen Sie beim Hinzufügen mehrerer Ports oder Portbereiche die einzelnen Eingaben durch Kommata voneinander. <br>
<strong><em>Datenverkehrstyp </em></strong> - Dies ist das für die Anwendung verwendete Protokoll. </td>

 </tr>
 </table>
 </div>
 
 
<div class="box">
<a name="qos_engine"><h2>QoS Engine</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
<td height=64>
		<p>
			Diese Smart QoS verbessert die VoIP-Sprachqualität und das Streaming, indem sichergestellt wird, dass Ihr VoIP- oder Streaming-Datenverkehr gegenüber anderen Datenverkehr im Netz, wie FTP- oder Web-Daten, priorisiert wird. Um die beste Leistung zu erzielen, markieren Sie die Option "Lag eliminated" (Verzögerung eliminieren), um die Priorität für Ihre Anwendungen anzugeben.
			<br>
		</p>
</td>
</tr>
</table>
</div>
 
 
<div class="box">
<a name="access_control"><h2>Netzwerkfilter</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=99>
		<p>
			Filter werden dazu verwendet, den Zugriff von LAN-Computern auf das Internet sowie auf Ihr Netzwerk zu verweigern oder zuzulassen. Innerhalb Ihres Netzwerks kann der Internetzugang von Computern mithilfe ihrer MAC-Adressen zugelassen oder verweigert werden.
		</p>
		<p>
			<strong>MAC-Filter</strong><br>
			Verwenden Sie MAC-Filter, um Computern innerhalb des LAN den Zugang zum Internet zu verweigern. Das ist entweder manuell möglich, indem Sie eine MAC-Adresse hinzufügen, oder Sie wählen die MAC-Adresse von der Liste der Clients, die zum aktuellen Zeitpunkt mit der Einheit verbunden sind.
			<br>
			Wählen Sie "Turn MAC Filtering ON and ALLOW computers with MAC address listed below to access the network" (MAC-Filterung EINSCHALTEN und Zugriff auf das Netzwerk für Computer mit den unten aufgelisteten MAC-Adressen ZULASSEN), wenn nur ausgewählte Computer Netzwerkzugriff haben sollen, und alle anderen Computer nicht.
			<br>
			Wählen Sie "Turn MAC Filtering ON and DENY computers with MAC addresses listed below to access the network" (MAC-Filterung EINSCHALTEN und Zugriff auf das Netzwerk für Computer mit den unten aufgelisteten MAC-Adressen VERWEIGERN), wenn alle Computer Zugriff auf das Netzwerk haben sollen, außer jene, die in der Liste aufgeführt sind.
			<br>
			<strong><em>MAC -Adresse</em></strong> -
			Die MAC-Adresse des Geräts im Netzwerk, das der MAC-Filterliste hinzugefügt werden soll.<br>
			<strong><em>DHCP-Client-Liste</em></strong> -
			DHCP-Clients werden über ihren Hostnamen im Dropdown-Menü "Computername" aufgelistet. Sie können den Client-Computer auswählen, den Sie der MAC-Filterliste hinzufügen möchten. Klicken Sie dann auf die Pfeilschaltfläche. Damit wird die MAC-Adresse dieses Computers automatisch dem entsprechenden Feld hinzugefügt.
		</p>
		<p>
			Benutzer können das Dropdown-Menü <strong>Immer</strong> verwenden, um einen bereits erstellten Zeitplan zu wählen, oder auf <strong>Neuen Zeitplan hinzufügen</strong> klicken, um einen neuen hinzuzufügen.
		</p>
		<p>
			Das Kontrollkästchen dient dazu, einen bestimmten Eintrag zu aktivieren oder zu deaktivieren.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="parental_control"><h2>Website-Filter</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=44>
		<p>
			Außer der Möglichkeit, Geräte vom Zugang zu Ihrem Netz und dem Internet auszuschließen, kann der <?query("/sys/modelname");?> auch so konfiguriert werden, dass der Zugriff für Computer im Netz auf "ungeeignet erachtete" Websites entweder mithilfe von Domänennamen oder Schlüsselwörter zugelassen oder verweigert wird.
		</p>
		<p>
			<strong>Kinderschutz</strong><br>
			Der Kinderschutz wird verwendet, um Computern in Ihrem Netz den Zugriff auf ganz bestimmte Websites mithilfe von Schlüsselwörtern oder spezifischen Domänennamen zu erlauben oder zu verweigern. Markieren Sie "Turn Website Filtering ON and ALLOW computers access to ONLY these sites" (Website-Filterung EINSCHALTEN und Zugriff auf AUSSCHLIESSLICH diese Websites für aufgelistete Computer ZULASSEN), um nur den Computern in Ihrem Netz den Zugriff auf die angegebenen URLs und Domänennamen zu erlauben. Markieren Sie "Turn Website Filtering ON and DENY computers access to ONLY these sites" (Website-Filterung EINSCHALTEN und Zugriff auf das Netzwerk für aufgelistete Computer VERWEIGERN), um Computern in Ihrem Netz den Zugriff auf die angegebenen URLs und Domänennamen zu verweigern.
		</p>
		<p>
			<span class="style1">Beispiel 1:</span><br>
			Wenn Sie LAN-Benutzer von irgendeiner Website fernhalten wollten, die einen URL enthält, der sich auf beispielsweise auf 'Shopping' bezieht, müssten Sie "Website-Filterung EINSCHALTEN und Zugriff auf das Netzwerk für aufgelistete Computer VERWEIGERN" wählen und dann das Wort 'Shopping' in die Liste mit Regeln für die Website-Filterung eingeben. LAN-Benutzern wird dann der Zugriff auf Websites wie diese verweigert, weil sie das Schlüsselwort im URL enthalten.
			<br>
			<a href="http://www.yahoo.com/shopping/stores.html">http://www.yahoo.com/shopping/stores.html</a><br>
			<a href="http://www.msn.com/search/shopping-spree.html">http://www.msn.com/search/shopping-spree.html</a>
		</p>
		<p>
			<span class="style1">Beispiel 2:</span><br>
			Wenn Sie wünschen, das Ihre Kinder nur bestimmte Websites aufrufen, würden Sie "Website-Filterung EINSCHALTEN und Zugriff auf AUSSCHLIESSLICH diese Websites für aufgelistete Computer ZULASSEN" wählen und die Domänen eingeben, auf die Ihre Kinder zugreifen dürfen.
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
<a name="firewall_dmz"><h2>Firewall-Einstellungen</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			Im Teil für die Firewall-Einstellungen steht Ihnen eine Option zur Konfiguration eines DMZ-Host zur Verfügung.
		</p>
		<p>
			<strong>SPI aktivieren</strong><br>
			SPI ("Stateful Packet Inspection", auch als "Dynamic packet filtering" bezeichnet) ist eine dynamische Paketfiltertechnik zur Verhinderung von Angriffen aus dem Internet, bei dem an Hand von dynamischen Zustandstabellen und auf der Basis des Vergleichs von mehreren Datenpaketen und durch die Ermittlung der Korrelation zwischen zusammengehörenden Datenpaketen Entscheidungen für die Weiterleitung der Datenpakete getroffen werden. Dabei wird geprüft, ob die Datenpakete dem Protokoll entsprechen und bestimmten Kriterien zugeordnet werden können. Bei dem TCP-Protokoll prüft SPI, ob die Paketsequenznummern sich im gültigen Bereich für die Sitzung befinden. Es werden dann die Datenpakete verworfen, bei denen keine gültigen Sequenznummern gefunden werden. Gleich, ob SPI aktiviert ist oder nicht, verfolgt der Router immer TCP-Verbindungszustände und stellt sicher, dass die Flags jedes TCP-Pakets für den aktuellen Zustand gültig sind.
		</p>
		<p>
			<strong>DMZ </strong><br>
			Wenn Sie einen Computer haben, der Internetanwendungen nicht ordnungsgemäß hinter dem <?query("/sys/modelname");?> ausführen kann, können Sie diesem Computer uneingeschränkten Internetzugang einräumen. Geben Sie dazu die IP-Adresse dieses Computers als DMZ-Host (Demilitarized Zone) mit uneingeschränktem Internetzugang ein. Das Platzieren eines Client in die DMZ kann diesen Computer allerdings einer Vielfalt von Sicherheitsrisiken aussetzen. Sie sollten diese Option deshalb nur als letzten Ausweg verwenden.
		</p>
		<p>
			<strong>Firewall-Regeln</strong><br>
			Firewall-Regeln werden dazu verwendet, Datenverkehr von und zum Router zuzulassen oder zu verhindern, und basieren auf den Quell- und Ziel-IP-Adressen sowie auf dem Datenverkehrstyp und dem spezifischen Port, auf dem die Daten ausgeführt werden.
			<br>
			<strong><em>Name</em></strong> - Benutzer können einer Firewall-Regel einen Namen geben.<br>
			<strong><em>Aktion</em></strong> - Datenverkehr kann zugelassen oder verweigert werden.<br>
			<strong>Schnittstelle</strong><br>
			<strong><em>Quelle</em></strong> -
			 Verwenden Sie das Dropdown-Menü <strong>Quelle</strong>, um auszuwählen, ob der Startpunkt des Datenverkehrs, der zugelassen oder verweigert werden soll, von der LAN- oder WAN-Schnittstelle ist.
			 <br>
			<strong><em>Ziel</em></strong> -
			Verwenden Sie das Dropdown-Menü <strong>Ziel</strong>, um auszuwählen, ob der Endpunkt des Datenverkehrs, der zugelassen oder verweigert werden soll, an der LAN- oder WAN-Schnittstelle ankommt.<br>
			<strong><em>IP-Adresse</em></strong> -
			Hier können Sie eine einzelne Quell- oder Ziel-IP-Adresse im obersten Feld angeben oder einen Bereich für die IP-Adressen eingeben, indem Sie die erste IP-Adresse des Bereichs im oberen und die letzte IP-Adresse des Bereichs im unteren Feld eingeben.<br>
			<strong><em>Protokoll</em></strong> -
			Verwenden Sie das Dropdown-Menü <strong>Protokoll</strong>, um den Datenverkehrstyp zu wählen.<br>
			<strong><em>Portbereich</em></strong> -
			Geben Sie die gleiche Portnummer in beiden Feldern ein, um einen einzelnen Port anzugeben, oder geben Sie den ersten Port des Bereichs im oberen und den letzten des Bereichs im unteren ein, um einen Portbereich anzugeben.<br>
			<strong><em>Zeitplan</em></strong> -
			Verwenden Sie das Dropdown-Menü <strong>Immer</strong>, um einen bereits erstellten Zeitplan zu wählen, oder klicken Sie auf <strong>Neuen Zeitplan hinzufügen</strong> klicken, um einen neuen hinzuzufügen.
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
echo "		Die Routing-Option ermöglicht Ihnen, statische Routen zu bestimmten Zielen anzugeben.<br>\n";
echo "		<strong><em>Aktivieren </em></strong> - Gibt an, ob der Eintrag aktiviert oder deaktiviert wird.<br>\n";
echo "		<strong><em>Schnittstelle </em></strong> - Gibt die Schnittstelle an -- WAN oder WAN Physisch --, die das \n";
echo "		IP-Paket verwenden muss, um bei Verwendung dieser Route den Datenverkehr aus dem Router zu leiten.<br>\n";
echo "		<strong><em>Schnittstelle (WAN)</em></strong> - Die Schnittstelle für den Empfang der IP-Adresse \n";
echo "		vom Internetdienstanbieter für den Zugang zum Internet.<br>\n";
echo "		<strong><em>Schnittstelle (WAN Physisch) </em></strong> - Die Schnittstelle für den Empfang der IP-Adresse \n";
echo "		vom Internetdienstanbieter für den Zugang zum Internet.<br>\n";
echo "		<strong><em>Ziel </em></strong> - Geben Sie die IP-Adresse der Datenpakete ein, die diese Route nehmen werden.<br>\n";
echo "		<strong><em>Subnetzmaske </em></strong> - Eine Subnetzmaske ist genau so lang wie die IP-Adresse, auf die sie \n";
echo "		angewendet wird, also 32 Bit. Alle Bits des Netzwerkteils sind auf 1 gesetzt und geben an welche Bits der IP-Adresse entsprechen müssen. <br>\n";
echo "		<strong><em>Gateway  </em></strong> - Gibt den nächsten Hop (Übergang von einem Netzknoten zum nächsten) \n";
echo "		an, wenn diese Route verwendet wird. Ein Gateway 0.0.0.0 kennzeichnet, dass es kein nächster Hop existiert und die entsprechende IP-Adresse \n";
echo "		direkt mit dem Router auf der angegebenen Schnittstelle verbunden ist: WAN oder WAN Physisch. \n";
echo " </td>\n";
echo " </tr>\n";
}
?>
</table>
</div>


<div class="box">
<a name="advanced_wireless"><h2>Erweiterter Funk</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=20>

 <p>Die Optionen auf dieser Seite sollten von erfahrenen Benutzern oder nach genauer Anweisung durch einen Mitarbeiter des Support-Personals von D-Link geändert werden, weil sich eine unsachgemäße Konfiguration auf die Leistung Ihres Routers negativ auswirken könnte.
 </p>
 <p><strong><em>Übertragungsleistung - </em></strong>Sie können die Ausgangsleistung des <?query("/sys/modelname");?> senken, indem Sie niedrigere Werte für die Übertragungsleistung von der Dropdown-Liste wählen. Sie können unter folgenden Werten wählen: 100%, 50%, 25% und 12,5%. </p>
 <p><strong><em>Beacon-Intervall - </em></strong> Beacon-Signale sind Datenpakete, die von einem Access Point gesendet werden, um ein Funknetzwerk zu synchronisieren. Geben Sie einen Wert zwischen 20 und 1000 für den Signalisierungszeitraum ein. Der Standardwert ist auf 100 Millisekunden eingestellt. </p>

 <p><strong><em>RTS-Schwellenwert - </em></strong> Die Standardeinstellung 2346 sollte übernommen werden. Falls ein uneinheitlicher Datenfluss auftritt, kann ggf. eine kleine Änderung des Wertbereichs zwischen 256 und 2346 vorgenommen werden. Standardwert für den RTS-Schwellenwert ist 2346. </p>
 <p><strong><em>Fragmentierung - </em></strong> Dieser Wert sollte als Standardwert von 2346 Bytes unverändert bleiben. Tritt eine hohe Datenpaketfehlerrate auf, können Sie Ihren "Fragmentierungswert" innerhalb des Bereichs von 1500 and 2346 geringfügig ändern. Wenn Sie den Fragmentierungswert jedoch zu niedrig einstellen, kann das zu einer schlechten Leistung führen. </p>
 <p><strong><em>DTIM-Intervall - </em></strong>  Geben Sie einen Wert zwischen 1 und 255 für die DTIM (Delivery Traffic Indication Message) ein. Ein DTIM ist eine Countdown-Signalliste zum Aufnehmen von Broadcast- und Multicast-Nachrichten, über die Clients über das nächste Fenster informiert werden. Wenn der Access Point Broadcast- oder Multicast-Nachrichten für zugeordnete Clients gepuffert hat, sendet er den nächsten DTIM mit einem DTIM-Intervallwert. AP-Clients erkennen die Beacons (Funk- oder Signalfeuer) und wachen auf, um die Broadcast- oder Multicast-Nachrichten zu empfangen. Standardwert für das DTIM-Intervall ist 1. </p>

 <p><strong><em>Präambeltyp - </em></strong> Der Präambeltyp legt die Länge des CRC-Blocks (Cyclic Redundancy Check/Zyklische Redundanzprüfung) für die Kommunikation zwischen dem Access Point und den Roaming-Funkadaptern fest. Achten Sie darauf, dass Sie den passenden Präambeltyp wählen und klicken Sie dann auf "Übernehmen". </p>
 <p><span class="style2">Hinweis: </span>Für Bereiche mit hohem Netzwerkdatenverkehr sollte die kürzere Präambel gewählt werden. Bei der zyklischen Redundanzprüfung (CRC) handelt es sich um eine gebräuchliche Technologie zur Aufdeckung von Datenübertragungsfehlern. </p>
 <p><strong><em>CTS Modus  - </em></strong>Wählen Sie "Kein", um diese Funktion zu deaktivieren. Wählen Sie "Immer", um den Router zu zwingen, dass jedes drahtlose Gerät im Netzwerk aufgefordert wird, das RTS/CTS-Handshake-Protokoll (Request to Send/Clear to Send) zu verwenden, bevor sie Daten übertragen können. Wählen Sie "Auto", um den Router die Entscheidung zu ermöglichen, wann RTS/CTS-Handshakes erforderlich sind. </p>
<?if(query("/runtime/func/ieee80211n")!="1"){
 echo "<p><strong><em>802.11g Only Mode - </em></strong>Enable this mode if your network is made up of purely 802.11g devices. If you have both 802.11b and 802.11g wireless clients, disable this mode. </p> </td>";
}?>
 </tr>
 </tr>
 </table>
 </div>
 
 
<div class="box">
<a name="advanced_network"><h2>Erweitertes Netzwerk</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=20>

 <p>Dieser Teil enthält Einstellungen, mit deren Hilfe geändert werden kann, wie der Router bestimmte Datenverkehrstypen handhabt. Wir empfehlen, diese Einstellungen nur dann zu ändern, wenn Sie mit ihnen bereits vertraut sind oder von einem unserer Support-Mitarbeiter angeleitet wurden, sie zu ändern.
 </p>

<!--
 <p><strong>VPN Passthrough </strong><br>The device supports VPN (Virtual Private Network) passthrough for PPTP (Point-to-Point Tunneling Protocol) and IPSec (IP Security). Once VPN passthrough is enabled, there is no need to create any Virtual Server or Port Forwarding entries in order for outbound VPN sessions to be established properly. Multiple VPN connections can be made through the device. This is useful when you have many VPN clients on the Local Area Network. </p>
-->

 <p><strong>UPnP </strong><br>UPnP steht als Abkürzung für Universal Plug and Play. Dabei handelt es sich um eine Netzwerkarchitektur, die die Kompatibilität zwischen Netzwerkgeräten, Software und Peripheriegeräten sicherstellt. Der <?query("/sys/modelname");?> ist ein UPnP fähiger Router. Das bedeutet, dass er mit anderen UPnP-Geräten/anderer Software zusammen verwendet werden kann. Wenn Sie die UPnP-Funktion nicht verwenden möchten, wählen Sie "Deaktiviert".
 </p>
 <p><strong>WAN Ping </strong><br>Wenn Sie "WAN-Ping-Antwort aktivieren" wählen, hat das den Effekt, dass die Public WAN-IP-Adresse auf dem Gerät auf Ping-Befehle antwortet, die von Internetbenutzern gesendet wurden. Das Senden von Ping-Paketen an Public WAN-IP-Adressen ist eine allgemein von Hackern verwendete Methode, um die Gültigkeit Ihrer WAN-IP-Adresse zu prüfen.
 </p>
 <p><strong>WAN-Portgeschwindigkeit  </strong><br>Sie können die Geschwindigkeit der WAN-Schnittstelle des <?query("/sys/modelname");?> wählen. Wählen Sie 100 Mbit/s, 10 Mbit/s oder 10/100/1000 Mbit/s Auto.
 </p>

<!--
 <p><strong>Gaming Mode </strong><br>If you are experiencing difficulties when playing online games or even certain applications that use voice data, you may need to enable Gaming Mode in order for these applications to work correctly. When not playing games or using these voice applications, it is recommended that Gaming Mode is disabled. </p>
--> 

<?if(query("/runtime/func/dis_multicast_stream")!="1"){
echo " <p><strong>Multicast-Streams</strong><br>Aktivieren Sie diese Option, um einen effektiveren Multicast-Datenverkehr vom Internet zu Ihrem Netzwerk zu erreichen. </p> </td>\n";
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
<a name="guest_zone"><h2>Gastzone</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			Wahl der Gastzone<br>
			Die Auswahl hilft Ihnen bei der Angabe der Gastzonenskala.<br>
			<strong><em>Gastzone aktivieren</em></strong>  - Gibt an, ob die Gastzone aktiviert oder deaktiviert wird.<br>
			<strong><em>LAN-Port einbeziehen</em></strong> -  Gibt an, welcher LAN-Port in der Gastzone enthalten sein soll. <br>
			<strong><em>Funk einbeziehen </em></strong> -  Gibt an, ob zusätzliche Funkzonen für die Gastzone verfügbar sein sollen oder nicht. <br>
			<strong><em>Name des Funknetzes</em></strong> -  Geben Sie einen Namen für die Gastzone des Funknetzes an. <br>
		</p>
		<p>
			<strong><em>Funksicherheitsmodus</em></strong><br>
			Es ist wichtig, dass Sie Ihr Funknetz sichern. Nur so kann die Integrität von Datenübertragungen in Ihrem Funknetz gewährleistet werden. Der <?query("/sys/modelname");?> bietet 4 Verschlüsselungsstandards für Ihr Funknetz: WEP, WPA only, WPA2 only und WPA/WPA2 (auto-detect).
			<br>
		</p>
		<p>
			<strong><em>WEP</em></strong><br>
			WEP (Wired Equivalent Protocol) ist ein drahtloses Sicherheitsprotokoll für WLANs (Wireless Local Area Networks). WEP bietet Sicherheit, indem es die über WLAN gesendeten Daten verschlüsselt. Der <?query("/sys/modelname");?> unterstützt die 64-Bit und 128-Bit WEP-Verschlüsselung. WEP ist standardmäßig deaktiviert. Sie können die WEP-Einstellungen ändern, um Ihr eigenes drahtloses Netz Ihren Wünschen entsprechend anzupassen.
		 <br>
		</p>
		<p>
			<strong><em>Authentifizierung</em></strong> - Authentifizierung ist ein Prozess, mit dessen Hilfe der <?query("/sys/modelname");?> die Identität eines Netzwerkgeräts prüft, das versucht, sich dem Funknetz anzuschließen. Bei der Verwendung des WEP-Sicherheitsprotokolls stehen Ihnen zwei Authentifizierungsmöglichkeiten für dieses Gerät zur Verfügung. <br>
			<strong><em>Open System</em></strong> - Wählen Sie diese Option, damit alle drahtlosen Geräte mit dem <?query("/sys/modelname");?> kommunizieren können, bevor diese den für den Zugang zum Netzwerk erforderlichen Verschlüsselungsschlüssel bereitstellen müssen. <br>
			<strong><em>Shared Key </em></strong> - Wählen Sie diese Option, wenn drahtlose Geräte, die mit dem Router zu kommunizieren versuchen, den für den Zugang zum Netz erforderlichen Verschlüsselungsschlüssel bereitstellen müssen, bevor sie mit dem <?query("/sys/modelname");?> kommunizieren können. <br>
			<strong><em>WEP-Verschlüsselung</em></strong> - Wählen Sie die WEP-Verschlüsselungsstufe, die Sie auf Ihrem Netzwerk verwenden möchten. Unterstützt wird die 64-Bit und 128-Bit WEP-Verschlüsselung.<br>
			<strong><em>Schlüsseltyp </em></strong> - Die vom <?query("/sys/modelname");?> unterstützten Schlüsseltypen sind HEX (Hexadecimal) und ASCII (American Standard Code for Information Interchange). Sie können den Schlüsseltyp ändern, um Ihr eigenes drahtloses Netz Ihren Wünschen entsprechend anzupassen. <br>
			<strong><em>Schlüssel</em></strong> - Mithilfe der Schlüssel 1 - 4 können Sie drahtlose Verschlüsselungseinstellungen problemlos ändern, um ein sicheres Netzwerk zu gewährleisten. Wählen Sie einfach den spezifischen Schlüssel, der für die Verschlüsselung der drahtlosen Daten im Netzwerk verwendet werden soll. <br>
		</p>
		<p>
			<strong><em>WPA-Personal</em></strong><br>
			Wi-Fi Protected Access autorisiert und authentifiziert Benutzer im Funknetz. WPA verwendet eine leistungsstärkere Verschlüsselungsmethode als WEP und basiert auf einem Schlüssel, der in regelmäßigen zeitlichen Abständen automatisch geändert wird.
			 <br>
		</p>
		<p>
			<strong><em>Verschlüsselungstyp</em></strong> -  Der <?query("/sys/modelname");?> unterstützt zwei verschiedene Verschlüsselungstypen, wenn WPA als Sicherheitstyp verwendet wird. Diese zwei Optionen sind TKIP (Temporal Key Integrity Protocol/Temporäres Schlüsselintegritätsprotokoll) und AES (Advanced Encryption Standard/Erweiterter Verschlüsselungsstandard). <br>
			<strong><em>PSK/EAP</em></strong> -Wird PSK gewählt, müssen Ihre drahtlosen Clients zur Authentifizierung einen Kennwortsatz angeben. Wird EAP gewählt, muss Ihr Netzwerk einen RADIUS-Server aufweisen, der die Authentifizierung Ihrer gesamten drahtlosen Clients handhabt. <br>
			<strong><em>Kennwortsatz  </em></strong> - Ein solcher ist erforderlich, damit Ihre drahtlosen Clients mit Ihrem <?query("/sys/modelname");?> kommunizieren können, wenn PSK gewählt wurde. Geben Sie zwischen 8 - 63 alphanumerische Zeichen ein. Schreiben Sie sich diesen Kennwortsatz unbedingt auf. Sie müssen ihn auf jedem anderen drahtlosen Gerät eingeben, das Sie Ihrem Netzwerk hinzufügen möchten. <br>
			<strong><em>802.1X </em></strong> - Diese Methode der WPA-Authentifizierung wird in Verbindung mit einem RADIUS-Server verwendet, der in Ihrem Netzwerk vorhanden sein muss. Geben Sie die IP-Adresse, den Port und das "Shared Secret" ein, für das Ihr RADIUS-Server konfiguriert wurde. Darüber hinaus haben Sie die Option, Informationen für einen zweiten RADIUS-Server für den Fall einzugeben, dass Ihr Netzwerk zwei dieser Server aufweist, die Sie zur Authentifizierung drahtloser Clients verwenden. <br>
		</p>
		<p>
			<strong><em>WPA2</em></strong><br>
			Wi-Fi Protected Access 2 autorisiert und authentifiziert Benutzer im Funknetz. WPA2 verwendet eine leistungsstärkere Verschlüsselungsmethode als WEP und basiert auf einem Schlüssel, der in regelmäßigen zeitlichen Abständen automatisch geändert wird.
			 <br>
		</p>
		<p>
			<strong><em>Verschlüsselungstyp</em></strong> - Der <?query("/sys/modelname");?> unterstützt zwei verschiedene Verschlüsselungstypen, wenn WPA als Sicherheitstyp verwendet wird. Diese zwei Optionen sind TKIP (Temporal Key Integrity Protocol/Temporäres Schlüsselintegritätsprotokoll) und AES (Advanced Encryption Standard/Erweiterter Verschlüsselungsstandard). <br>
			<strong><em>PSK/EAP</em></strong> - Wird PSK gewählt, müssen Ihre drahtlosen Clients zur Authentifizierung einen Kennwortsatz angeben. Wird EAP gewählt, muss Ihr Netzwerk einen RADIUS-Server aufweisen, der die Authentifizierung Ihrer gesamten drahtlosen Clients handhabt.<br>
			<strong><em>Kennwortsatz</em></strong> - Ein solcher ist erforderlich, damit Ihre drahtlosen Clients mit Ihrem <?query("/sys/modelname");?> kommunizieren können, wenn PSK gewählt wurde. Geben Sie zwischen 8 - 63 alphanumerische Zeichen ein. Schreiben Sie sich diesen Kennwortsatz unbedingt auf. Sie müssen ihn auf jedem anderen drahtlosen Gerät eingeben, das Sie Ihrem Netzwerk hinzufügen möchten. <br>
			<strong><em>802.1X </em></strong> - Diese Methode der WPA2-Authentifizierung wird in Verbindung mit einem RADIUS-Server verwendet, der in Ihrem Netzwerk vorhanden sein muss. Geben Sie die IP-Adresse, den Port und das "Shared Secret" ein, für das Ihr RADIUS-Server konfiguriert wurde. Darüber hinaus haben Sie die Option, Informationen für einen zweiten RADIUS-Server für den Fall einzugeben, dass Ihr Netzwerk zwei dieser Server aufweist, die Sie zur Authentifizierung drahtloser Clients verwenden. <br>
		</p>
		<p>
			<strong><em>WPA2-Auto</em></strong> <br>
			Mithilfe dieser Option kann der <?query("/sys/modelname");?> sowohl mit WPA2- als auch WPA-Clients gleichzeitig verbunden sein.
			<br>
		</p>
		<p>
			<strong><em>LAN-Setup für Gastzone</em></strong><br> 
			Das sind die Einstellungen der Gastzonen-LAN-Schnittstelle für das Gerät. Diese Einstellungen können als "private Einstellungen" angesehen werden. Sie können die IP-Adresse nach Bedarf ändern. Die IP-Adresse ist privat für Ihr internes Netzwerk und im Internet nicht sichtbar. Die Standard-IP-Adresse ist 192.168.1.1 mit der Subnetzmaske 255.255.255.0.
			<br>
		</p>
		<p>
			<strong><em>IP-Adresse</em></strong> - Die IP-Adresse des <?query("/sys/modelname");?>. Sie lautet standardmäßig 192.168.1.1. <br>
			<strong><em>Subnetzmaske </em></strong> - Die Subnetzmaske des <?query("/sys/modelname");?>, standardmäßig 255.255.255.0. <br>
		</p>
		<p>
			<strong><em>Gastzonen-Client-Isolation aktivieren:</em></strong> : <br>
			Aktivieren Sie die Funktion, um zu verhindern, dass ein Gast-Client auf andere Clients in der Gastzone zugreift. Der Gast-Client kann nur auf das Internet zugreifen.
			 <br>
		</p>
		<p>
			<strong><em>Routing zwischen Zonen aktivieren:</em></strong> : <br>
			Verwenden Sie diesen Teil dazu, um das Routing der Daten zwischen der Host- und der Gastzone zu ermöglichen. Gast-Clients können nicht ohne Aktivierung dieser Funktion auf die Daten von Host-Clients zugreifen.
			 <br>
		</p>
		<p>
			<strong><em>DHCP-Server für Gastzone</em></strong> <br>
			DHCP ist die Abkürzung für Dynamic Host Configuration Protocol (Dynamisches Hostkonfigurationsprotokoll). Der DHCP-Server weist Geräten auf Anforderung IP-Adressen im Netz zu. Auf diesen Geräten muss dazu die Option "Obtain the IP address automatically" (IP-Adresse automatisch beziehen) gewählt sein. Standardmäßig ist der DHCP-Server auf dem <?query("/sys/modelname");?> aktiviert. Der DHCP-Adressenpool enthält den Bereich von IP-Adressen, der den Clients im Netzwerk automatisch zugewiesen wird.
		 <br>
		</p>
		<p>
			<strong><em>Start-IP-Adresse</em></strong> - Die Start-IP-Adresse für die IP-Zuweisung des DHCP-Servers. <br>
			<strong><em>End-IP-Adresse</em></strong> -Die End-IP-Adresse für die IP-Zuweisung des DHCP-Servers. <br>
			<strong><em>Lease-Zeit</em></strong> -Die Zeitdauer in Minuten für die IP-Lease. Die Informationen der dynamischen DHCP-Client-Computer, die mit der Einheit verbunden sind, werden in der Dynamischen DHCP Client-Tabelle angezeigt. In der Tabelle werden der Host-Name, die IP-Adresse, MAC-Addresse und abgelaufene Zeit des DHCP-Lease für jeden Client-Computer angezeigt. <br>
		</p>
</td>
</tr>
</table>
</div>
 
<div class="box">
<a name="wake_on_lan"><h2>WOL (Wake on LAN)</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			Die Funktion "Wake on LAN" kann dazu genutzt werden, einen LAN-seitig mit dem Router verbundenen PC im Fernzugriff einzuschalten. Geben Sie den UDP-Port an. Er wird vom 'WOL Magic Packet', einem speziellen Datenpaket, verwendet, um zu verhindern, dass der Router die WOL-Anfrage als feindlichen Angriff ansieht und sperrt.
			<br>
			<br>
			<strong><em>UDP-Port</em></strong> - 
			Dies ist der Port, den der <?query("/sys/modelname");?> speziell dazu nutzt, die 'Magic Packets' zu empfangen, die den PC einschalten.<br>
			<strong><em>Schnittstelle </em></strong> - 
			(Diese Einstellung kann zum aktuellen Zeitpunkt nicht geändert werden. Das ist in zukünftigen Firmware-Freigaben eventuell möglich.)<br>		
		</p>
	</td>
</tr>
</table>
</div>
