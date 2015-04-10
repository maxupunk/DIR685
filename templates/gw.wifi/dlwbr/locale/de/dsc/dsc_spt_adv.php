<h1>SUPPORTMENÜ</h1>
	<table border=0 cellspacing=0 cellpadding=0 width=750 height=1103>
 <tr>
 <td width="750" height=40><font size=4><b>Erweitert</b></font></td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>

 </tr>
<tr>
	<td height=228>
		<p>
			<a name=05><strong>Erweiterte Portweiterleitung </strong></a><br>
      Mit der Option „Erweiterte Portweiterleitung“ erhalten Internetbenutzer Zugriff auf Dienste in 
      Ihrem LAN. Dies ist hilfreich beim Anbieten von Onlinediensten wie FTP-, Web- oder Spielservern. 
      Für jeden Eintrag definieren Sie einen öffentlichen Port auf Ihrem Router, der auf einen LAN-Port 
      an einer internen LAN-IP-Adresse weitergeleitet wird.
		</p>
		<p>
			Parameter für die erweiterte Portweiterleitung<br>
			<strong><em>Name</em></strong> -
      Weisen Sie dem virtuellen Server einen aussagekräftigen Namen zu, z. B. Web Server. In der Dropdown-Liste 
      „Anwendungsname“ stehen mehrere bekannte virtuelle Server zur Auswahl. Durch Auswahl einer dieser Einträge 
      werden einige der verbleibenden Parameter mit Standardwerten für den ausgewählten Server ausgefüllt.<br>
			<strong><em>IP-Adresse </em></strong> -
      Die IP-Adresse des Systems in Ihrem lokalen Netzwerks, das den virtuellen Dienst bereitstellt, z. B. 
      192.168.0.50. Sie können entweder einen Computer aus der Liste der DHCP-Clients im Dropdown-Menü 
      „Computername“ auswählen oder die IP-Adresse des Server-Computers manuell eingeben.<br>
			<strong><em>Anwendungsname </em></strong> -
      Eine Liste vordefinierter Anwendungen, die den Benutzern zur schnelleren Konfiguration zur Auswahl stehen.<br>
			<strong><em>Computername </em></strong> - Eine Liste der DHCP-Clients.<br>
			<strong><em>Datenverkehrstyp</em></strong> -
      Wählen Sie das vom Dienst verwendete Protokoll aus. Eine gebräuchliche Auswahl (UDP, TCP und UDP und TCP) 
      können im Dropdown-Menü getroffen werden. Um ein weiteres Protokoll anzugeben, wählen Sie in der Liste die 
      Option „Andere“ aus. Geben Sie anschließend die entsprechende Protokollnummer (wie von IANA zugewiesen) in 
      das Feld „Protokoll“ ein.
			<strong><em>Privater Port</em></strong> -
			Der in Ihrem lokalen Netzwerk verwendete Port.<br>
			<strong><em>Öffentlicher Port</em></strong> -
			Der Port, auf den vom Internet aus zugegriffen wird.<br>
		</p>
	</td>
</tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>

 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=64> <strong>Regeln für Anwendungen<font size=4><b><a name=06></a></b></font> </strong><br>
Einige Anwendungen, z. B. Internetspiele, Videokonferenzen oder Internettelefonie, benötigen Mehrfachverbindungen. Bei diesen Anwendungen treten Schwierigkeiten auf, wenn Sie über NAT (Network Address Translation) ausgeführt werden. Wenn Sie Anwendungen ausführen müssen, die Mehrfachverbindungen benötigen, geben Sie im Feld „Trigger-Port“ den Port an, der einer Anwendung zugeordnet ist. Wählen Sie als Protokoll TCP (Transmission Control Protocol) oder UDP (User Datagram Protocol) aus, und geben Sie die dem Trigger-Port zugeordneten öffentlichen Ports im Feld „Firewall-Port“ ein, um sie für eingehenden Datenverkehr zu öffnen. Im Dropdown-Menü „Anwendungsname“ sind bereits einige häufig verwendete Anwendungen definiert.<br>
<strong><em>Name </em></strong> - Bezeichnung der Anwendung. <br>
<strong><em>Triggerport </em></strong>- Port, der für die Anwendung verwendet wird. Dabei kann es sich um einen einzelnen Port oder um einen Portbereich handeln. <br>
<strong><em>Datenverkehrstyp </em></strong> - Protokoll, das für die Anwendung verwendet wird. <br>
<strong><em>Firewall-Port </em></strong> - Die für den Anwendungszugriff verwendete Portnummer auf der WAN-Seite. Sie können einen einzelnen Port oder einen Portbereich angeben. Verwenden Sie Kommas, um mehrere Ports oder Portbereiche anzugeben. <br>
<strong><em>Datenverkehrstyp </em></strong> - Protokoll, das für die Anwendung verwendet wird. </td>

 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
<tr>
	<td height=99>
		<p>
			<a name=07><strong>Zugangskontrolle</strong></a><br>
      Filter werden verwendet, um LAN-Computern den Zugriff auf das Internet und das lokale Netzwerk zu verweigern oder zu gestatten. 
      Innerhalb Ihres Netzwerks kann der Router so eingerichtet werden, dass Computern anhand der MAC-Adresse der Zugriff auf das 
      Internet gestattet oder verweigert wird.
		</p>
		<p>
			<strong>MAC-Filter</strong><br>
      Mit MAC-Filtern können Sie den Internetzugriff für bestimmte Computer im LAN sperren. 
      Die MAC-Adresse kann entweder manuell eingegeben oder aus einer Liste mit Clients ausgewählt werden, 
      die mit dem System verbunden sind.<br>
			Wählen Sie &quot;MAC-Filterung aktivieren und den Netzwerkzugriff für die Computer mit unten aufgeführter 
			MAC-Adresse zulassen&quot; wenn nur bestimmte Computer Internetzugriff haben sollen und alle anderen nicht.<br>
			Wählen Sie &quot;MAC-Filterung aktivieren und den Netzwerkzugriff für die Computer mit unten aufgeführter 
			MAC-Adresse verweigern&quot; wenn Sie einzelne Computer für den Internetzugriff sperren möchten.<br>
			<strong><em>MAC-Adresse</em></strong> -
			Die MAC-Adresse des Netzwerkgeräts, das Sie zur Liste für den MAC-Filter hinzufügen möchten.<br>
			<strong><em>Liste der DHCP-Clients</em></strong> -
      Die Hostnamen der DHCP-Clients werden im Dropdown-Menü „Computername“ angezeigt. Wählen Sie den 
      Client-Computer, den Sie zur Liste für den MAC-Filter hinzufügen möchten, und klicken Sie auf 
      die Pfeilschaltfläche. Dadurch wird die MAC-Adresse des Computers automatisch zum entsprechenden 
      Feld hinzugefügt.
		</p>
		<p>
      Benutzer können über das Dropdown-Menü <strong>„Immer“</strong> einen bereits vorher definierten 
      Zeitplan auswählen oder über die Schaltfläche <strong>„Neu“</strong> einen neuen Zeitplan hinzufügen.
		</p>
		<p>
			Über das Kontrollkästchen wird ein bestimmter Eintrag aktiviert bzw. deaktiviert.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<a name=08><strong>Firewall und DMZ</strong></a><br>
      Der Bereich „Firewall-Einstellungen“ enthält die Optionen zur Konfiguration eines DMS-Hosts.
		</p>
		<p>
			<strong>SPI aktivieren</strong><br>
      SPI („Stateful Packet Inspection“, auch als „dynamische Paketfilterung“ bekannt) hilft bei der Verhinderung 
      von Hacker-Angriffen, indem mehr als ein Zustand pro Sitzung verfolgt wird. Die Funktion überprüft, ob der 
      durch diese Sitzung verlaufende Verkehr protokollkonform ist. Ist die Art des Protokolls TCP, überprüft SPI, 
      dass sich die Paketsequenznummern im gültigen Bereich für die Sitzung befinden und ignoriert die Pakete, die 
      über keine gültige Sequenznummer verfügen. Unabhängig davon, ob SPI aktiviert ist oder nicht, verfolgt der 
      Router immer den TCP-Verbindungsstatus und sorgt dafür, dass alle „Flags“ des TCP-Pakets für den aktuellen 
      Status gültig sind.			
		</p>
		<p>
			<strong>DMZ </strong><br>
			Wenn Sie einen Computer haben, auf dem Anwendungen aus dem Internet hinter dem <? query("/sys/modelname");?> 
			nicht richtig ausgeführt werden, können Sie diesem Computer uneingeschränkten Internetzugriff gewähren. Geben 
			Sie die IP-Adresse dieses Computers als DMZ-Host (DMZ = Demilitarisierte Zone) mit uneingeschränktem 
			Internetzugriff ein. Wenn Sie einen Computer zur DMZ hinzufügen, ist dieser Computer vielen Sicherheitsrisiken 
			ausgesetzt. Sie sollten diese Option also nur verwenden, wenn es unumgänglich ist.
		</p>
		<p>
			<strong>Firewall-Regeln</strong><br>
			Die Firewall-Regeln gestatten oder sperren eingehenden oder vom Router ausgehenden Datenverkehr, 
			basierend sowohl auf der Quell- und Ziel-IP-Adresse als auch der Art des Datenverkehrs und dem 
			bestimmten Port, auf dem die Daten ausgeführt werden.<br>
			<strong><em>Name</em></strong> - Benutzer können für eine Firewall-Regel einen Namen angeben.<br>
			<strong><em>Aktion</em></strong> - Benutzer können Datenverkehr gestatten oder sperren.<br>
			<strong>Schnittstelle</strong><br>
			<strong><em>Quelle</em></strong> -
			Wählen Sie im Dropdown-Menü <strong>Quelle</strong> den Startpunkt für den Datenverkehr aus, der 
			über die LAN- oder WLAN-Schnittstelle gestattet oder gesperrt wird.<br>
			<strong><em>Ziel</em></strong> -
			Wählen Sie im Dropdown-Menü <strong>Ziel</strong> den Endpunkt für den Datenverkehr aus, der 
			über die LAN- oder WLAN-Schnittstelle gestattet oder gesperrt wird.<br>
			<strong><em>IP-Adresse</em></strong> -
			Hier können Sie eine einzelne Quelle oder Ziel-IP angeben, indem Sie die IP-Adresse 
			im obersten Feld eingeben oder einen IP-Bereich mit der ersten IP-Adresse des Bereichs 
			im oberen Feld und der letzten IP-Adresse im untersten Feld.<br>
			<strong><em>Protokoll</em></strong> -
			Wählen Sie im Dropdown-Menü <strong>Protokoll</strong> den Datenverkehrstyp aus.<br>
			<strong><em>Port-Bereich</em></strong> -
			Geben Sie für einen einzelnen Port in beiden Feldern dieselbe Portnummer ein, und für einen Portbereich 
			den ersten Port im obersten Feld und den letzten Port im untersten Feld.<br>
			<strong><em>Zeitplan</em></strong> -
			Über das Dropdown-Menü <strong>Immer</strong> können Sie einen bereits vorher definierten Zeitplan 
			auswählen oder über die Schaltfläche <strong>Hinzufügen</strong> einen neuen Zeitplan hinzufügen.
 </p>
	</div></td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
 <tr>
 <td height=20><p><strong>Erweitertes WLAN <a name=09></a></strong></p>

 <p>Die Optionen auf dieser Seite sollten nur von fortgeschrittenen Benutzern geändert werden oder wenn Sie vom technischen Support entsprechend dazu angewiesen werden. Bei falscher Konfiguration können diese Einstellungen die Leistung Ihres Routers nachteilig beeinflussen. </p>
 <p><strong><em>Übertragungsraten (TX-Raten) -  </em></strong> Legen Sie die Basisübertragungsraten entsprechend der Geschwindigkeit der drahtlosen Adapter im WLAN fest. </p>
 <p><strong><em>Übertragungsleistung - </em></strong>Sie können die Ausgangsleistung des <?query("/sys/modelname");?> verringern, indem Sie für die Übertragungsleistung einen niedrigeren Prozentsatz aus dem Dropdown-Menü wählen. Zur Wahl stehen: 100 %, 50 %, 25 % und 12,5 %. </p>
 <p><strong><em>Beacon-Intervall - </em></strong> Beacon-Pakete sind Signale, die zum Synchronisieren eines drahtlosen Netzwerks von einem Access Point gesendet werden. Geben Sie ein Beacon-Intervall zwischen 20 und 1000 ein. Standardmäßig ist ein Wert von 100 Millisekunden eingestellt. </p>

 <p><strong><em>RTS-Schwelle - </em></strong> Die Standardeinstellung 2346 für diesen Wert muss beibehalten werden. Bei Unregelmäßigkeiten in der Datenübertragung können geringfügige Änderungen im Bereich zwischen 256 und 2346 vorgenommen werden. Standardmäßig ist die RTS-Schwelle auf 2346 eingestellt. </p>
 <p><strong><em>Fragmentierung - </em></strong> Dieser Wert sollte bei der Standardeinstellung von 2346 belassen werden. Im Falle einer hohen Paketfehlerrate können Sie den &quot;Fragmentierungswert&quot; im Bereich zwischen 1500 und 2346 etwas erhöhen. Ist der Fragmentierungswert zu niedrig eingestellt, kann sich dies negativ auf die Leistung auswirken. </p>
 <p><strong><em>DTIM-Intervall - </em></strong> Geben Sie als DTIM (Delivery Traffic Indication Message) einen Wert zwischen 1 und 255 ein. Ein DTIM ist ein Countdown, der Clients über das nächste Fenster zum Empfang von Broadcast- und Multicast-Meldungen informiert. Wenn der Zugriffspunkt Broadcast- oder Multicast-Nachrichten für verbundene Clients in den Puffer gestellt hat, wird die nächste DTIM mit einem DTIM-Intervallwert gesendet. Die Access Point-Clients „hören“ die Beacons und „wachen auf“, um die Broadcast- und Multicast-Meldungen zu empfangen. Standardmäßig ist das DTIM-Intervall auf 1 eingestellt. </p>

 <p><strong><em>Präambeltyp - </em></strong> Der Präambeltyp legt die Länge des CRC-Blocks (CRC, Cyclic Redundancy Check) fest, der für die Kommunikation zwischen dem Zugriffspunkt und angeschlossenen drahtlosen Adaptern verwendet wird. Überprüfen Sie, ob Sie den richtigen Präambeltyp ausgewählt haben, und klicken Sie auf die Schaltfläche Übernehmen. </p>
 <p><span class="style2">Hinweis: </span>In Bereichen mit hohem Netzwerkverkehr sollte der kurze Präambeltyp verwendet werden. Bei CRC handelt es sich um eine häufig eingesetzte Technik zur Erkennung von Datenübertragungsfehlern. </p>
 <p><strong><em>CTS-Modus - </em></strong>Wählen Sie die Option Keine, um diese Funktion zu deaktivieren. Wählen Sie Automatisch, wenn Sie möchten, dass der Router von jedem drahtlosen Netzwerkgerät vor dem Datentransfer einen RTS/CTS-Handshake verlangt. Wählen Sie Automatisch, wenn Sie möchten, dass der Router entscheidet, wann ein RTS/CTS-Handshake erforderlich ist. </p>
<?if(query("/runtime/func/ieee80211n")!="1"){
 echo "<p><strong><em>Nur 802.11g-Modus - </em></strong>Aktivieren Sie diesen Modus, wenn Ihr Netzwerk ausschließlich aus Geräten aufgebaut ist, die den 802.11g-Standard unterstützen. Wenn Ihr Netzwerk sowohl aus 802.11b- als auch aus 802.11g-Clients besteht, deaktivieren Sie diesen Modus. </p> </td>";
}?>

 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=20><p><strong>Erweiterte Netzwerkeinstellungen <a name=10></a></strong></p>

 <p>Mit diesen Einstellungen können Sie festlegen, wie der Router bestimmte Arten von Datenverkehr behandelt. Es wird empfohlen, diese Einstellungen nicht zu ändern, außer Sie sind damit vertraut oder werden von einem Mitarbeiter des technischen Supports dazu angewiesen. </p>

<!--
 <p><strong>VPN Passthrough </strong><br>The device supports VPN (Virtual Private Network) passthrough for PPTP (Point-to-Point Tunneling Protocol) and IPSec (IP Security). Once VPN passthrough is enabled, there is no need to create any Virtual Server or Port Forwarding entries in order for outbound VPN sessions to establish properly. Multiple VPN connections can be made through the device. This is useful when you have many VPN clients on the Local Area Network. </p>
-->

 <p><strong>UPnP </strong><br>Bei UPnP (Universal Plug and Play) handelt es sich um ein Netzwerkprotokoll, das für Kompatibilität zwischen Netzwerkkomponenten, Software und Peripheriegeräten sorgt. Der <?query("/sys/modelname");?> ist ein UPnP-fähiges Gerät, das mit anderen UPnP-Geräten und -Programmen verwendet werden kann. Wenn Sie die UPnP-Funktion nicht nutzen möchten, können Sie UPnP deaktivieren, indem Sie &quot;Deaktiviert&quot; auswählen. </p>
 <p><strong>WAN-Ping </strong><br>Wenn Sie Antwort auf WAN-Ping aktivieren, reagiert der Router mit seiner öffentlichen WAN-IP-Adresse auf Ping-Befehle aus dem Internet. Das Testen öffentlicher WAN-IP-Adressen mit dem Ping-Befehl ist eine verbreitete Methode von Hackern zum Überprüfen gültiger WAN-IP-Adressen. </p>
 <p><strong>WAN-Port-Geschwindigkeit </strong><br>Mit dieser Option können Sie die Geschwindigkeit des <?query("/sys/modelname");?> wählen. Wählen Sie zwischen 100 Mbit/s, 10 Mbit/s oder 10/100 Mbit/s Auto. </p>

 <p><strong>Spielemodus </strong><br>Falls Sie Probleme bei Online-Spielen oder Anwendungen mit Sprachübertragung haben, müssen Sie evtl. den Spielemodus aktivieren, damit diese Anwendungen ordnungsgemäß funktionieren. Es wird empfohlen, den Spielemodus nur während dieser Online-Spiele und Sprachanwendungen zu aktivieren und ihn ansonsten zu deaktivieren. </p>
<!--
 <p><strong>Multicast-Streams</strong><br>Aktivieren Sie diese Option, um einen effektiveren Multicast-Datenverkehr vom Internet zu Ihrem Netzwerk zu erreichen. </p> </td>
-->
 </tr>

<?if(query("/runtime/func/dis_multicast_stream")!="1"){
echo "<tr><td height=20>&nbsp;</td></tr>\n";
echo "<tr>\n";
echo "	<td height=20>\n";
echo "		<p>\n"
echo "			<strong>Multicast-Datenströme aktivieren</strong><br>\n";
echo "			Aktivieren Sie diese Option, wenn Sie Videoabrufdienste aus dem Internet erhalten. Der Router verwenden das \n";
echo "			IGMP-Protokoll zur Unterstützung einer effizienten Multicasting-Übertragung identischer Inhalte, wie z. B. \n";
echo "			Multimedia von einer einzelnen Quelle an mehrere Empfänger. Diese Option muss aktiviert sein, wenn eine \n";
echo "			Anwendung im LAN an einer Multicast-Gruppe teilnimmt. Wenn eine Ihrer Multimedia-LAN-Anwendungen Inhalte \n";
echo "			nicht wie erwartet erhält, deaktivieren Sie diese Option.\n";
echo "		</p>\n";
echo "	</td>\n";
echo "</tr>\n";
}
?>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
<?if(query("/runtime/func/dis_routing")!="1"){
echo "<tr>\n";
echo "	<td height=99><strong>Routing </strong><a name=11></a><br>\n";
echo "		Über die Option „Routing“ können Sie feste Routen zu bestimmten Zielen angeben.<br>\n";
echo "		<strong><em>Aktivieren </em></strong> - Gibt an, ob der Eintrag aktiviert oder deaktiviert werden soll.<br>\n";
echo "		<strong><em>Schnittstelle </em></strong> - Legt die Schnittstelle (WAN oder WAN (physikalisch))\n"; 
echo "		fest, die das IP-Paket verwenden muss, um bei Verwendung dieser Route den Router zu verlassen.<br>\n";
echo "		<strong><em>Schnittstelle (WAN)</em></strong> - Die Schnittstelle, die vom Internetdiensteanbieter\n"; 
echo "		die IP-Adresse für den Internetzugriff erhält.<br>\n";
echo "		<strong><em>Schnittstelle (WAN physisch)</em></strong> - Die Schnittstelle, die vom Internetdiensteanbieter \n";
echo "		die IP-Adresse für den Zugriff auf den Internetdiensteanbieter erhält.<br><br>\n";
echo "		<strong><em>Ziel </em></strong> - IP-Adresse der Pakete, die diese Route verwenden.<br>\n";
echo "		<strong><em>Subnetzmaske </em></strong> - Ein-Bit in der Maske geben an, welche\n"; 
echo "		Bit der IP-Adresse übereinstimmen müssen. <br>\n";
echo "		<strong><em>Gateway </em></strong> - Gibt den nächsten Punkt (Hop) an, der bei Verwendung dieser \n";
echo "		Route angesprungen wird. Wenn die Adresse 0.0.0.0 als Gateway verwendet wird, bedeutet dies, dass \n";
echo "		es keinen nächsten Hop gibt und die passende IP-Adresse direkt mit dem Router auf der angegebenen \n";
echo "		Schnittstelle verbunden ist: WAN oder WAN physisch. \n";
echo " </td>\n";
echo " </tr>\n";
}
?>

 <tr>
 <td height=20>&nbsp;</td>
 </tr>

 </table>
