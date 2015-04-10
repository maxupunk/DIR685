<h1>SUPPORT-MENÜ</h1>

	<table border=0 cellspacing=0 cellpadding=0 width=750 height=478>
 <tr>
 <td height=2><font size=4><b>Status</b></font></td>
 </tr>
 <tr>
 <td height=39> <a name=20><strong>Geräteinformationen </strong><br>
Auf dieser Seite werden die aktuellen Informationen über den <?query("/sys/modelname");?> angezeigt. Auf der Seite wird die Firmwareversion angezeigt, die zurzeit im Gerät geladen ist. <br>

&nbsp;<br>
<strong><em>LAN (Local Area Network) - </em></strong>Hier werden die MAC-Adresse der Ethnernet-LAN-Schnittstelle und die IP-Adresse und Subnetzmaske der LAN-Schnittstelle angegeben. Außerdem wird angezeigt, ob der integrierte DHCP-Server des Routers aktiviert oder deaktiviert ist. <br>
<strong><em>WAN (Wide Area Network) - </em></strong>Hier werden die MAC-Adresse der WAN-Schnittstelle sowie IP-Adresse, Subnetzmaske, Standard-Gateway und DNS-Server angezeigt, die dem <?query("/sys/modelname");?> von Ihrem Internet-Dienstanbieter zugewiesen wurden. Außerdem wird angegeben, welcher Verbindungstyp zum Herstellen einer Verbindung mit Ihrem Internetdienstanbieter dient (dynamisch, statisch oder PPPoE). Wenn der Router für eine dynamische IP-Adresse konfiguriert ist, werden Schaltflächen zum Freigeben und Aktualisieren der IP-Adresse eingeblendet, die der WAN-Schnittstelle zugewiesen wurde. Wenn der Router für PPPoE konfiguriert ist, werden Schaltflächen zum Herstellen und Trennen der PPPoE-Sitzung eingeblendet.<br> 
<strong><em>
Wireless 802.11
<? if(query("/runtime/func/ieee80211n") != "1") { echo "g"; } else { echo "n"; }?>
 - </em></strong>Hier erhalten Sie Informationen zu SSID und Kanal sowie dazu, ob die Verschlüsselung für die WLAN-Schnittstelle aktiviert ist. </td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>

 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=26><a name=21><b>Protokoll</b></a><br>
  Der <?query("/sys/modelname");?> erstellt ein ständig aktualisiertes Protokoll der Ereignisse und Aktivitäten. In dem Protokoll werden bis zu 400 aktuelle Protokolldatensätze angezeigt. Ältere Protokolle werden von neueren Protokollen überschrieben. <br>

 <strong><em>Erste Seite - </em></strong> Klicken Sie auf diese Schaltfläche, um zur ersten Seite des Protokolls zu gelangen. <br>
 <strong><em>Letzte Seite - </em></strong> Klicken Sie auf diese Schaltfläche, um zur letzten Seite des Protokolls zu gelangen. <br>
 <strong><em>Zurück - </em></strong> Blättert zur vorherigen Protokollseite. <br>
 <strong><em>Weiter - </em></strong> Blättert zur nächsten Protokollseite. <br>

 <strong><em>Löschen - </em></strong> Die Protokolldatensätze werden vollständig gelöscht. </td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>

 </tr>
 <tr>
 <td height=2><a name=22><strong>Statistik</strong></a><br>
 Der <?query("/sys/modelname");?> erstellt eine Statistik über den von ihm abgewickelten Datenverkehr. Die Anzahl der Pakete, die der Router auf der WAN-, LAN- und der drahtlosen Schnittstelle empfangen und übermittelt hat, wird angezeigt.
<br>
<strong><em>Aktualisieren - </em></strong>Klicken Sie auf diese Schaltfläche, um die Zähler zu aktualisieren. <br>
<strong><em>Zurücksetzen - </em></strong>Klicken Sie auf diese Schaltfläche, um die Zähler zu löschen. Der Zähler des Datenverkehrs wird bei einem Neustart des Geräts zurückgesetzt. </td>

 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=2><a name=23><b>Aktive Sitzung</b></a><br>
 In der aktiven Sitzung werden Quell- und Zielpakete angezeigt, die über den <?query("/sys/modelname");?> übertragen werden. <br>
 <strong><em>IP-Adresse - </em></strong> Die Quell-IP-Adresse, von der die Pakete gesendet wurden. <br>
 <strong><em>TCP-Sitzung - </em></strong> Zeigt die Anzahl der TCP-Pakete an, die von der Quell-IP-Adresse aus gesendet werden. <br>
 <strong><em>UDP-Sitzung - </em></strong> Zeigt die Anzahl der UDP-Pakete an, die von der Quell-IP-Adresse aus gesendet werden. <br>
 <strong><em>Protokoll - </em></strong> Hierbei handelt es sich um den Typ der zwischen der Quell- und der Ziel-IP-Adresse übertragenen Pakete. <br>
 Quell-IP-Adresse - Zeigt die IP-Adresse an, von der die Pakete gesendet wurden. <br>
 Quell-Port - Zeigt den Port an, der zur Übertragung der Pakete an die Ziel-IP-Adresse verwendet wird. <br>
 Ziel-IP-Adresse - Zeigt die IP-Adresse an, an welche die Pakete gesendet werden. <br>
 Ziel-Port - Zeigt den Port an, der zum Abrufen der Pakete von der Quell-IP-Adresse verwendet wird. 


</td>

 </tr>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=2><a name=24><b>Wireless (WLAN)</b></a><br>
 Auf dieser Seite werden die mit dem <?query("/sys/modelname");?> verbundenen drahtlosen Clients angezeigt. Auf dieser Seite werden die MAC-Adressen der verbundenen Clients angezeigt sowie deren Verbindungsdauer und -modus (802.11b oder 802.11g).
</td>

 </tr>
 </table>
