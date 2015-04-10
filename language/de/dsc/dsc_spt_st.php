<div class="box">
<a name="device_info"><h2>Geräteinfo</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=39> 
Auf dieser Seite werden die aktuellen Informationen für den <?query("/sys/modelname");?> sowie die Version der aktuell auf dem Gerät geladenen Firmware angezeigt.
 <br>

&nbsp;<br>
<strong><em>LAN (Local Area Network) - </em></strong> Zeigt die MAC-Adresse der Ethernet-LAN-Schnittstelle, die IP-Adresse und Subnetzmaske der LAN-Schnittstelle an und ob der integrierte DHCP-Server des Routers aktiviert oder deaktiviert ist. <br>
<strong><em>WAN (Wide Area Network)  - </em></strong>Zeigt die MAC-Adresse der WAN-Schnittstelle sowie die IP-Adresse, Subnetzmaske, Standard-Gateway und DNS-Serverinformationen an, die der <?query("/sys/modelname");?> von Ihrem Internetdienstanbieter erhalten hat. Darüber hinaus wird der Verbindungstyp (Dynamisch, Statisch oder PPPoE) angezeigt, der zum Aufbau der Verbindung mit dem Internetanbieter verwendet wird. Ist der Router für "Dynamisch" konfiguriert, stehen Schaltflächen zur Freigabe und Aktualisierung der IP-Adresse zur Verfügung, die der WAN-Schnittstelle zugewiesen wurde. Wurde der Router für PPPoE konfiguriert, stehen Schaltflächen für die Herstellung der Verbindung und das Trennen der Verbindung für die PPPoE-Sitzung zur Verfügung.<br> 
<strong><em>
Wireless 802.11
<? if(query("/runtime/func/ieee80211n") != "1") { echo "g"; } else { echo "n"; }?>
 - 
</em></strong>Zeigt die SSID und den Kanal an und ob eine Verschlüsselung für die drahtlose Schnittstelle aktiviert ist oder nicht. </td>
</tr>
</table>
</div>


<div class="box">
<a name="log"><h2>Protokoll</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=26>
 Der <?query("/sys/modelname");?> führt ein kontinuierlich laufendes eigenes Ereignis- und Aktivitätenprotokoll. Bis zu 400 der letzten Protokolle können angezeigt werden. Die neueren Protokollaktivitäten überschreiben die älteren Protokolle.
 <br>

 <strong><em>Erste Seite - </em></strong> Klicken Sie auf diese Schaltfläche, um die erste Seite des Protokolls aufzurufen. <br>
 <strong><em>Letzte Seite - </em></strong> Klicken Sie auf diese Schaltfläche, um die letzte Seite des Protokolls aufzurufen. <br>
 <strong><em>Vorherige - </em></strong> Zeigt die vorherige Protokollseite an. <br>
 <strong><em>Nächste - </em></strong> Zeigt die nächste Protokollseite an. <br>

 <strong><em>Löschen - </em></strong> Löscht die Protokolle. </td>
 </tr>
 </table>
 </div>
 
 
<div class="box">
<a name="statistics"><h2>Statistik</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=2>
 Der <?query("/sys/modelname");?> führt eine Statistik des von ihm abgewickelten Datenverkehrs. Sie können also die Datenpaketmenge anzeigen, die der Router im WAN, LAN und den Funkschnittstellen empfangen und übertragen hat.
<br>
<strong><em>Aktualisieren - </em></strong>Klicken Sie auf diese Schaltfläche, um die Zähler zu aktualisieren. <br>
<strong><em>Rücksetzen - </em></strong>Klicken Sie auf diese Schaltfläche, um Zählerinhalte zu löschen. Der Datenverkehrzähler wird beim Neustart des Geräts zurückgesetzt. </td>
</tr>
</table>
</div>


<div class="box">
<a name="internet_session"><h2>Internetsitzung</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=2>
 Die Internetsitzung zeigt die den <?query("/sys/modelname");?> passierenden Quellen- und Zielpakete an. <br>
 <strong><em>IP -Adresse - </em></strong> Die Quellen-IP-Adresse gibt an, woher die Datenpakete stammen. <br>
 <strong><em>TCP-Sitzung - </em></strong> Zeigt die Anzahl der TCP-Pakete, die von der Quellen-IP-Adresse gesendet werden. <br>
 <strong><em>UDP-Sitzung  - </em></strong> Zeigt die Anzahl der UDP-Pakete, die von der Quellen-IP-Adresse gesendet werden. <br>
 <strong><em>Protokoll - </em></strong> Die Art der zwischen der Quellen- und Ziel-IP-Adresse übertragenen Datenpakete. <br>
 Quellen-IP - Zeigt die IP-Adresse an, von der die Datenpakete stammen. <br>
 Quelle (Port) - Zeigt den Port, der zur Übertragung der Pakete an die Ziel-IP-Adresse verwendet wird.<br>
 Ziel-IP - Zeigt die IP-Adresse an, für die die Datenpakete bestimmt sind. <br>
 Ziel (Port) - Zeigt den Port, der zum Empfang der Pakete von der Quellen-IP-Adresse verwendet wird. 
</td>
 </tr>
 </tr>
</table>
</div>
 
 
<div class="box">
<a name="wireless"><h2>Funk</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=2>
 Verwenden Sie diese Seite, um anzuzeigen, wie viele Funk-Clients (auch drahtlose Clients genannt) dem <?query("/sys/modelname");?> zugeordnet sind. Sie zeigt die MAC-Adresse jedes zugeordneten Client, wie lange sie zugeordnet sind und den Verbindungsmodus, d. h. die IEEE-Norm für die Kommunikation in Funknetzwerken (802.11b, 802.11g, 802.11a oder 802.11n).
</td>
 </tr>
</table>
</div> 
