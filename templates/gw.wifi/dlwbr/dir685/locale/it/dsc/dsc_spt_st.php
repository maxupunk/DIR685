<div class="box">
<a name="device_info"><h2>Info dispositivo</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=39> 
In questa pagina sono visualizzate le informazioni correnti relative al dispositivo <?query("/sys/modelname");?> ed è indicata la versione del firmware attualmente caricato nel dispositivo.
 <br>

&nbsp;<br>
<strong><em>LAN (Local Area Network)  - </em></strong>Visualizza l'indirizzo MAC dell'interfaccia LAN Ethernet, l'indirizzo IP e la subnet mask dell'interfaccia LAN. Viene inoltre indicato se il server DHCP incorporato del router è abilitato o disabilitato. <br>
<strong><em>WAN (Wide Area Network)  - </em></strong>Visualizza l'indirizzo MAC dell'interfaccia WAN, nonché l'indirizzo IP, la subnet mask, il gateway di default e le informazioni sul server DNS che il dispositivo <?query("/sys/modelname");?> ha ottenuto dall'ISP. Viene inoltre visualizzato il tipo di connessione (dinamica, statica o PPPoE) utilizzata per stabilire una connessione con l'ISP. Se il router è configurato per la connessione dinamica, saranno presenti pulsanti per rilasciare e rinnovare l'indirizzo IP assegnato all'interfaccia WAN. Se il router è configurato per la connessione PPPoE, saranno presenti pulsanti per connettere e disconnettere la sessione PPPoE.<br> 
<strong><em>
Wireless 802.11
<? if(query("/runtime/func/ieee80211n") != "1") { echo "g"; } else { echo "n"; }?>
 - 
</em></strong>Visualizza il SSID e il canale. Viene inoltre indicato se la crittografia è abilitata per l'interfaccia wireless. </td>
</tr>
</table>
</div>


<div class="box">
<a name="log"><h2>Log</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=26>
 Nel dispositivo <?query("/sys/modelname");?> viene mantenuto un log degli eventi e delle attività eseguite nel router. Nel log vengono visualizzate fino a 400 attività recenti. Le attività più recenti sovrascriveranno quelle meno recenti.
 <br>

 <strong><em>Prima pagina - </em></strong> Fare clic su questo pulsante per passare alla prima pagina del log. <br>
 <strong><em>Ultima pagina - </em></strong> Fare clic su questo pulsante per passare all'ultima pagina del log. <br>
 <strong><em>Precedente - </em></strong> Torna alla pagina precedente del log. <br>
 <strong><em>Successiva - </em></strong> Passa alla pagina successiva del log. <br>

 <strong><em>Cancella - </em></strong> Cancella completamente i log. </td>
 </tr>
 </table>
 </div>
 
 
<div class="box">
<a name="statistics"><h2>Statistiche</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=2>
 Il dispositivo <?query("/sys/modelname");?> mantiene le statistiche del traffico dati gestito. È possibile visualizzare il numero di pacchetti che il router ha ricevuto e trasmesso nelle interfacce Internet (WAN), LAN e wireless.
<br>
<strong><em>Aggiorna - </em></strong>Fare clic su questo pulsante per aggiornare i contatori. <br>
<strong><em>Ripristina - </em></strong>Fare clic su questo pulsante per azzerare i contatori. Il contatore del traffico verrà ripristinato al riavvio del dispositivo. </td>
</tr>
</table>
</div>


<div class="box">
<a name="internet_session"><h2>Sessione Internet</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=2>
 Visualizza i pacchetti di origine e di destinazione trasmessi tramite il dispositivo <?query("/sys/modelname");?>.
 <br>
 <strong><em>Indirizzo IP - </em></strong> Indirizzo IP di origine dei pacchetti. <br>
 <strong><em>Sessione TCP - </em></strong> Visualizza il numero di pacchetti TCP inviati dall'indirizzo IP di origine. <br>
 <strong><em>Sessione UDP - </em></strong> Visualizza il numero di pacchetti UDP inviati dall'indirizzo IP di origine. <br>
 <strong><em>Protocollo - </em></strong> Tipo di pacchetti trasmessi tra l'IP di origine e di destinazione. <br>
 IP di origine - Visualizza l'indirizzo IP di origine dei pacchetti. <br>
 Porta origine - Visualizza la porta utilizzata per trasmettere i pacchetti all'IP di destinazione. <br>
 IP destinaz. - Visualizza l'indirizzo IP di destinazione dei pacchetti. <br>
 Porta destinaz. - Visualizza la porta utilizzata per ricevere i pacchetti dall'IP di origine. 
</td>
 </tr>
 </tr>
</table>
</div>
 
 
<div class="box">
<a name="wireless"><h2>Wireless</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=2>
 Utilizzare questa pagina per visualizzare il numero di client wireless associati al dispositivo <?query("/sys/modelname");?>. In questa pagina sono indicati l'indirizzo MAC di ogni client associato, il periodo in cui sono rimasti associati e la modalità utilizzata per la connessione (802.11b, 802.11g, 802.11a o 802.11n).
</td>
 </tr>
</table>
</div> 
