<h1>MENU ASSISTANCE</h1>

	<table border=0 cellspacing=0 cellpadding=0 width=750 height=478>
 <tr>
 <td height=2><font size=4><b>État</b></font></td>
 </tr>
 <tr>
 <td height=39> <a name=20><strong>Informations sur l'appareil </strong><br>
Cette page affiche les informations actuelles du DIR-300. Elle indique la version du firmware actuellement chargé dans l'appareil. <br>

&nbsp;<br>
<strong><em>LAN (Connexion au réseau local)  - </em></strong>Affiche l'adresse MAC de l'interface Ethernet du réseau local, l'adresse IP et le masque de sous-réseau de l'interface de réseau local et précise si le serveur DHCP intégré au routeur est activé ou désactivé. <br>
<strong><em>WAN (Connexion au réseau étendu)  - </em></strong>Affiche l'adresse MAC de l'interface WAN ainsi que l'adresse IP, le masque de sous-réseau, la passerelle par défaut et le serveur DNS communiqués au DIR-300 par votre fournisseur d’accès. Cette page indique également le type de connexion (dynamique, statique ou PPPoE) utilisé avec le fournisseur d'accès. Si le routeur est configuré pour une connexion dynamique, des boutons permettant de libérer et de renouveler l'adresse IP attribuée à l'interface WAN apparaissent. Si le routeur est configuré pour une connexion PPPoE, des boutons permettant de connecter et de déconnecter la session PPPoE apparaissent.<br> 
<strong><em>
Sans fil 802.11
<? if(query("/runtime/func/ieee80211n") != "1") { echo "g"; } else { echo "n"; }?>
  - 
</em></strong>Affiche le SSID et le canal et précise si le chiffrement est activé ou non sur l'interface sans fil. </td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>

 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=26><a name=21><b>Consignation</b></a><br>
  Le <?query("/sys/modelname");?> tient un journal des événements et des activités en permanence. Le journal affiche jusqu'à 400 journaux récents. Les activités de journalisation les plus récentes écrasent les plus anciennes. <br>

 <strong><em>Première page - </em></strong> Cliquez sur ce bouton pour atteindre la première page du journal. <br>
 <strong><em>Dernière page - </em></strong> Cliquez sur ce bouton pour atteindre la dernière page du journal. <br>
 <strong><em>Précédente - </em></strong> Recule d'une page dans le journal.  <br>
 <strong><em>Suivante - </em></strong> Avance d'une page dans le journal. <br>

 <strong><em>Vider - </em></strong> Efface complètement les journaux.  </td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>

 </tr>
 <tr>
 <td height=2><a name=22><strong>Statistiques</strong></a><br>
 Le <?query("/sys/modelname");?> conserve des statistiques sur le trafic de données qu'il est amené à gérer. Vous pouvez afficher la quantité de paquets reçus et transmis par le routeur sur les interfaces de réseau étendu, de réseau local et sans fil. 
<br>
<strong><em>Actualiser - </em></strong>Cliquez sur ce bouton pour mettre à jour les compteurs. <br>
<strong><em>Réinitialiser - </em></strong>Cliquez sur ce bouton pour remettre les compteurs à zéro. Le compteur de trafic est réinitialisé lors du redémarrage de l'appareil. </td>

 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=2><a name=23><b>Session active</b></a><br>
 L'option Session active affiche les paquets source et cible transmis par le <?query("/sys/modelname");?>. <br>
 <strong><em>Adresse IP - </em></strong> Adresse IP source d'où les paquets proviennent. <br>
 <strong><em>Session TCP - </em></strong> Nombre de paquets TCP transmis depuis l'adresse IP source. <br>
 <strong><em>Session UDP - </em></strong> Nombre de paquets UDP transmis depuis l'adresse IP source. <br>
 <strong><em>Protocole - </em></strong> Type de paquets transmis entre l'adresse IP source et l'adresse IP cible. <br>
 IP source - Adresse IP source d'où les paquets proviennent. <br>
 Port source - Port utilisé pour transmettre les paquets à l'adresse IP cible. <br>
 IP cible - Adresse IP à laquelle les paquets sont envoyés. <br>
 Port cible - Port utilisé pour recevoir les paquets envoyés par l'adresse IP source.


</td>

 </tr>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=2><a name=24><b>Sans fil</b></a><br>
 Cette page affiche le nombre de clients sans fil associés au <?query("/sys/modelname");?>. Elle indique l'adresse MAC de chaque client associé, la durée d'association de chacun et le mode de connexion utilisé (802.11b ou 802.11g). 
</td>

 </tr>
 </table>
