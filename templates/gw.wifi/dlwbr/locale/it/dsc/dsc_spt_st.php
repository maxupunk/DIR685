<h1>MENU SUPPORTO</h1>

	<table border=0 cellspacing=0 cellpadding=0 width=750 height=478>
 <tr>
 <td height=2><font size=4><b>Stato</b></font></td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>

 </tr>
 <tr>
 <td height=39> <a name=20><strong>Info dispositivo </strong><br>
In questa pagina sono visualizzate le informazioni correnti relative a <?query("/sys/modelname");?> ed ¨¨ indicata la versione del firmware attualmente caricato nel dispositivo. <br>

&nbsp;<br>
<strong><em>LAN (Local Area Network) - </em></strong>Visualizza l'indirizzo MAC dell'interfaccia LAN Ethernet, l'indirizzo IP e la subnet mask dell'interfaccia LAN. Viene inoltre indicato se il server DHCP incorporato del router ¨¨ abilitato o disabilitato. <br>
<strong><em>WAN (Wide Area Network) - </em></strong>Visualizza l'indirizzo MAC dell'interfaccia WAN, nonch¨¦ l'indirizzo IP, la subnet mask, il gateway di default e le informazioni sul server DNS che DIR-300 ha ottenuto dall'ISP. Viene inoltre visualizzato il tipo di connessione (dinamica, statica o PPPoE) utilizzata per stabilire una connessione con l'ISP. Se il router ¨¨ configurato per la connessione dinamica, saranno presenti pulsanti per rilasciare e rinnovare l'indirizzo IP assegnato all'interfaccia WAN. Se il router ¨¨ configurato per la connessione PPPoE, saranno presenti pulsanti per connettere e disconnettere la sessione PPPoE.<br> 
<strong><em>
Wireless 802.11
<? if(query("/runtime/func/ieee80211n") != "1") { echo "g"; } else { echo "n"; }?>
 - 
</em></strong>Visualizza il SSID e  il canale. Viene inoltre indicato se la crittografia ¨¨ abilitata per l'interfaccia wireless.  </td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>

 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=26><a name=21><b>Log</b></a><br>
In <?query("/sys/modelname");?> viene mantenuto un log degli eventi e delle attivit¨¤ eseguite nel router. Nel log vengono visualizzate fino a 400 attivit¨¤ recenti. Le attivit¨¤ pi¨´ recenti sovrascriveranno quelle meno recenti.  <br>

 <strong><em>Prima pagina - </em></strong> Fare clic su questo pulsante per passare alla prima pagina del log. <br>
 <strong><em>Ultima pagina - </em></strong> Fare clic su questo pulsante per passare all'ultima pagina del log. <br>
 <strong><em>Precedente  - </em></strong> orna alla pagina precedente del log.  <br>
 <strong><em>Successiva - </em></strong> Passa alla pagina successiva del log. <br>

 <strong><em>Cancella - </em></strong> Cancella completamente i log.</td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>

 </tr>
 <tr>
 <td height=2><a name=22><strong>Statistiche</strong></a><br>
<?query("/sys/modelname");?> mantiene le statistiche del traffico dati gestito. ¨¨ possibile visualizzare il numero di pacchetti che il router ha ricevuto e trasmesso nelle interfacce WAN, LAN e wireless. 
<br>
<strong><em>Aggiorna - </em></strong>Fare clic su questo pulsante per aggiornare i contatori. <br>
<strong><em>Ripristina  - </em></strong>Fare clic su questo pulsante per azzerare i contatori. Il contatore del traffico verr¨¤ ripristinato al riavvio del dispositivo. </td>

 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=2><a name=23><b>Sessione attiva</b></a><br>
 Visualizza i pacchetti di origine e di destinazione trasmessi tramite <?query("/sys/modelname");?>. <br>
 <strong><em>Indirizzo IP  - </em></strong> Indirizzo IP di origine dei pacchetti. <br>
 <strong><em>Sessione TCP - </em></strong> Visualizza il numero di pacchetti TCP inviati dall'indirizzo IP di origine. <br>
 <strong><em>Sessione UDP - </em></strong> Visualizza il numero di pacchetti UDP inviati dall'indirizzo IP di origine. <br>
 <strong><em>Protocollo - </em></strong> Tipo di pacchetti trasmessi tra l'IP di origine e di destinazione. <br>
 IP di origine - Visualizza l'indirizzo IP di origine dei pacchetti. <br>
 Porta origine - Visualizza la porta utilizzata per trasmettere i pacchetti all'IP di destinazione.<br>
 IP destinaz. - Visualizza l'indirizzo IP di destinazione dei pacchetti. <br>
 Porta destinaz. - Visualizza la porta utilizzata per ricevere i pacchetti dall'IP di origine. <br>
</td>

 </tr>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=2><a name=24><b>Wireless</b></a><br>
 Utilizzare questa pagina per visualizzare il numero di client wireless associati a <?query("/sys/modelname");?>. In questa pagina sono indicati l'indirizzo MAC di ogni client associato, il periodo in cui sono rimasti associati e la modalit¨¤ utilizzata per la connessione (802.11b o 802.11g). 
</td>

 </tr>
 </table>
