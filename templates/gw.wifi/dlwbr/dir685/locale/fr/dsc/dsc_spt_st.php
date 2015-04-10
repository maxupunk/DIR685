<div class="box">
<a name="device_info"><h2>Informations sur le périphérique</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=39> 
Cette page affiche les informations actuelles sur le <?query("/sys/modelname");?>, ainsi que la version du microprogramme chargé sur le périphérique.
 <br>

&nbsp;<br>
<strong><em>LAN (Local Area Network)(Réseau local) - </em></strong>Affiche l'adresse MAC de l'interface Ethernet du réseau local, l'adresse IP et le masque de sous-réseau de l'interface du réseau local et indique si le serveur DHCP intégré au routeur est activé ou désactivé. <br>
<strong><em>WAN (Wide Area Network)(Réseau étendu)  - </em></strong>Affiche l'adresse MAC de l'interface du réseau étendu, ainsi que les informations sur l'adresse IP, le masque de sous-réseau, la passerelle par défaut et le serveur DNS que le <?query("/sys/modelname");?> a obtenu de votre FAI. Cette option affiche également le type de connexion (dynamique, statique ou PPPoE) utilisé pour établir une connexion avec votre FAI. Si le routeur est configuré pour Dynamic (Dynamique), certains boutons permettent de libérer et de renouveler l'adresse IP attribuée à l'interface du réseau étendu. Si le routeur est configuré pour PPPoE, certains boutons permettent de connecter et de déconnecter la session PPPoE.<br> 
<strong><em>
802.11
<? if(query("/runtime/func/ieee80211n") != "1") { echo "g"; } else { echo "n"; }?>
sans fil
 - 
</em></strong>Affiche le SSID, le canal et indique si Encryption (Chiffrement) est activé ou non sur l'interface sans fil. </td>
</tr>
</table>
</div>


<div class="box">
<a name="log"><h2>Journal</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=26>
 Le <?query("/sys/modelname");?> continue à exécuter le journal d'événements et d'activités survenus sans interruption. Le journal affiche jusqu'à 400 événements récents. Les nouvelles activités du journal écrasent les anciennes.
 <br>

 <strong><em>Première page - </em></strong> Cliquez sur ce bouton pour accéder à la première page du journal. <br>
 <strong><em>Dernière page - </em></strong> Cliquez sur ce bouton pour accéder à la dernière page du journal. <br>
 <strong><em>Précédent - </em></strong> Renvoie à la page précédente. <br>
 <strong><em>Suivant - </em></strong> Renvoie à la page suivante. <br>

 <strong><em>Effacer - </em></strong> Efface tous les journaux. </td>
 </tr>
 </table>
 </div>
 
 
<div class="box">
<a name="statistics"><h2>Statistiques</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=2>
 Le <?query("/sys/modelname");?> conserve le statistiques du trafic de données qu'il gère. Vous pouvez voir la quantité de paquets que le routeur a reçu et transmis sur Internet (réseau étendu), sur le réseau local et sur les interface sans fil.
<br>
<strong><em>Actualiser - </em></strong>Cliquez sur ce bouton pour mettre les compteurs à jour. <br>
<strong><em>Réinitialiser - </em></strong>Cliquez sur ce bouton pour effacer les compteurs. Le compteur de trafic se réinitialise lorsque le périphérique est redémarré. </td>
</tr>
</table>
</div>


<div class="box">
<a name="internet_session"><h2>Session Internet</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=2>
 La session Internet affiche les paquets sources et cibles passant par le <?query("/sys/modelname");?>. <br>
 <strong><em>Adresse IP - </em></strong> L'adresse IP source d'où proviennent les paquets. <br>
 <strong><em>Session TCP - </em></strong> Affiche le nombre de paquets TCP envoyés depuis l'adresse IP source. <br>
 <strong><em>Session UDP - </em></strong> Affiche le nombre de paquets UDP envoyés depuis l'adresse IP source. <br>
 <strong><em>Protocole - </em></strong> Type de paquets transmis entre les adresses IP source et cible. <br>
 Adresse IP source - L'adresse IP d'où proviennent les paquets. <br>
 Port source - Affiche le port servant à transmettre des paquets à l'adresse IP cible. <br>
 Adresse IP cible - L'adresse IP à laquelle les paquets sont destinés. <br>
 Port cible - Affiche le port servant à recevoir des paquets de l'adresse IP source. 
</td>
 </tr>
 </tr>
</table>
</div>
 
 
<div class="box">
<a name="wireless"><h2>Sans fil</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=2>
 Cette page permet de voir le nombre de clients sans fil associés au <?query("/sys/modelname");?>. Elle affiche l'adresse MAC de chaque client associé, le temps pendant lequel il est associé, ainsi que son mode de connexion (802.11b, 802.11g, 802.11a ou 802.11n).
</td>
 </tr>
</table>
</div> 
