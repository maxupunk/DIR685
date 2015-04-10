<h1>MENU ASSISTANCE</h1>
	<table border=0 cellspacing=0 cellpadding=0 width=750 height=1103>
 <tr>
 <td width="750" height=40><font size=4><b>Avancé</b></font></td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>

 </tr>
<tr>
	<td height=228>
		<p>
			<a name=05><strong>Redirection avancée de port </strong></a><br>
			L'option de redirection avancée de port permet aux utilisateurs Internet d'accéder à des services 
			sur votre réseau local. Elle est utile pour les services d'hébergement en ligne (par exemple, serveurs FTP, 
			Web ou de jeux). Pour chaque élément, vous devez définir un port public sur votre routeur destiné à rediriger 
			le trafic vers une adresse IP et un port du réseau local.
		</p>
		<p>
			Paramètres de redirection avancée de port<br>
			<strong><em>Nom</em></strong> -
			Affectez un nom parlant pour vous au serveur virtuel. Par exemple, Serveur Web. Plusieurs types courants de
 			serveurs virtuels sont disponibles dans la liste déroulante &quot;Nom d'application&quot;. Si vous sélectionnez 
			l'une de ces entrées, des valeurs standard sont automatiquement définies pour certains des paramètres 
			restants correspondant au type de serveur.<br>
			<strong><em>Adresse IP  </em></strong> -
			Adresse IP du système sur votre réseau interne qui fournit le service virtuel. 
			Par exemple, 192.168.0.50. Vous pouvez sélectionner un ordinateur dans la liste de clients DHCP du menu 
			déroulant &quot;Nom d'ordinateur&quot; ou saisir manuellement l'adresse IP de l'ordinateur.<br>
			<strong><em>Nom d'application  </em></strong> -
			Liste d'applications prédéfinies que les utilisateurs peuvent choisir pour accélérer la configuration.<br>
			<strong><em>Nom d'ordinateur </em></strong> - Liste de clients DHCP.<br>
			<strong><em>Type de trafic</em></strong> -
			Sélectionnez le protocole utilisé par le service. Les types les plus courants (UDP, TCP ou les deux à la fois)
 			peuvent être sélectionnés dans le menu déroulant. Pour spécifier un autre protocole, sélectionnez "Autre" dans
 			la liste, puis saisissez le numéro de protocole (attribué par l'IANA) dans la zone Protocole.<br>
			<strong><em>Port privé </em></strong> -
			Port qui sera utilisé sur votre réseau interne.<br>
			<strong><em>Port public</em></strong> -
			Port qui sera accessible depuis Internet.<br>
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
 <td height=64> <strong>Règles d'application<font size=4><b><a name=06></a></b></font> </strong><br>
Certaines applications requièrent plusieurs connexions, notamment les jeux en ligne, la vidéo-conférence ou la téléphonie sur Internet. Ces applications fonctionnent parfois mal avec la traduction d'adresses de réseau (NAT, Network Address Translation). Si vous devez exécuter des applications qui requièrent plusieurs connexions, spécifiez le port normalement associé à une application dans le champ &quot;Port déclencheur&quot;, sélectionnez le type de protocole TCP (Transmission Control Protocol) ou UDP (User Datagram Protocol), puis saisissez les ports publics associés au port déclencheur dans le champ du port de firewall pour les ouvrir au trafic entrant. Le menu déroulant Nom d'application répertorie des applications courantes déjà définies. <br>

<strong><em>Nom </em></strong> - Le nom associé à l'application. <br>
<strong><em>Port déclencheur  </em></strong>- Le port utilisé pour déclencher l'application. Il peut s'agir d'un port unique ou d'une plage de ports. <br>
<strong><em>Type de trafic </em></strong> - Le protocole utilisé pour déclencher l'application. <br>
<strong><em>Port de firewall </em></strong> - Le numéro de port côté WAN qui sera utilisé pour accéder à l'application. Vous pouvez définir un port unique ou une plage de ports. Utilisez une virgule pour ajouter plusieurs ports ou des plages de ports. <br>
<strong><em>Type de trafic </em></strong> - Le protocole utilisé pour l'application. </td>

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
			<a name=07><strong>Contrôle d'accès</strong></a><br>
			Les filtres permettent de refuser ou d'autoriser l'accès à Internet et à votre réseau à des ordinateurs du réseau 			local.Au sein de votre réseau, vous pouvez configurer l'unité pour autoriser ou refuser l'accès Internet à des 			ordinateurs en fonction de leur adresse MAC.
		</p>
		<p>
			<strong>Filtres MAC</strong><br>
			Les filtres MAC permettent de refuser l'accès Internet à des ordinateurs du réseau local. 
			Vous pouvez soit ajouter manuellement une adresse MAC, soit sélectionner l'adresse MAC dans 
			la liste des clients actuellement connectés à l'appareil.<br>
			Sélectionnez ACTIVER le filtrage MAC et AUTORISER les ordinateurs de la liste à accéder au réseau, 
			si vous souhaitez autoriser uniquement les ordinateurs sélectionnés à accéder au réseau et en interdire 
			l'accès à tous les autres ordinateurs.<br>
			Sélectionnez ACTIVER le filtrage MAC et REFUSER l'accès au réseau aux ordinateurs de la liste si vous 
			souhaitez que tous les ordinateurs, à l'exception de ceux figurant dans la liste, puissent accéder au réseau.<br>
			<strong><em>Adresse MAC</em></strong> -
			L'adresse MAC du périphérique réseau à ajouter à la liste de filtrage MAC.<br>
			<strong><em>Liste des clients DHCP </em></strong> -
			Le nom d'hôte des clients DHCP est indiqué dans le menu déroulant Nom d'ordinateur. 
			Sélectionnez l'ordinateur client à ajouter au filtre MAC, puis cliquez sur la flèche. 
			Cela ajoute automatiquement l'adresse MAC de l'ordinateur dans le champ approprié.
		</p>
		<p>
			Vous pouvez utiliser le menu déroulant <strong>Toujours</strong> pour sélectionner une programmation 
			précédemment définie ou cliquez sur le bouton <strong>Ajouter nouvelle</strong> pour ajouter une nouvelle 				programmation.
		</p>
		<p>
			La case à cocher permet d'activer ou de désactiver un élément.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<a name=08><strong>Firewall et zone démilitarisée</strong></a><br>
			La section Paramètres du firewall contient l'option de configuration d'un hôte DMS.
		</p>
		<p>
			<strong>Activer SPI</strong><br>
			SPI (&quot;stateful packet inspection&quot; ou fonction de filtrage dynamique des paquets) contribue à éviter 
			les attaques électroniques en suivant davantage d'états par session. Cette fonction vérifie la conformité au
 			protocole du trafic qui traverse la session. Lorsqu'il s'agit du protocole TCP, SPI vérifie que les numéros
 			d'ordre des paquets se trouvent dans la plage autorisée pour la session. Les paquets ne possédant pas de numéro
	 		valide sont ignorés. Que l'option SPI soit activée ou non, le routeur surveille toujours les états de connexion
	 		TCP et s'assure que les drapeaux des paquets TCP sont corrects pour l'état actuel.
		</p>
		<p>
			<strong>DMZ (Zone démilitarisée) </strong><br>
			Si vous avez un ordinateur qui ne peut pas exécuter d'applications Internet correctement derrière le
			<?query("/sys/modelname");?>, vous pouvez autoriser pour cet ordinateur un accès Internet illimité. 
			Saisissez-en l'adresse IP en tant qu'hôte DMZ (Demilitarized Zone, zone démilitarisée) avec accès Internet
 			illimité. L'ajout d'un client à la DMZ peut exposer cet ordinateur à plusieurs risques en terme de sécurité;
 			n'utilisez donc cette option qu'en dernier recours.
		</p>
		<p>
			<strong>Règles du firewall</strong><br>
			Les règles du firewall sont utilisées pour autoriser ou refuser le trafic entrant ou sortant du routeur, 
			selon les adresses IP source et cible, le type de trafic et le port spécifique sur lequel les données
 			circulent.<br>
			<strong><em>Nom</em></strong> - Les utilisateurs peuvent donner un nom à chaque règle de firewall.<br>
			<strong><em>Action</em></strong> - Les utilisateurs ont le choix entre autoriser ou refuser le trafic.<br>
			<strong>Interface</strong><br>
			<strong><em>Source</em></strong> -
			Utilisez le menu déroulant <strong>Source</strong> pour sélectionner le point de départ du trafic à autoriser 
			ou à refuser depuis l'interface LAN ou WAN.<br>
			<strong><em>Destination</em></strong> -
			Utilisez le menu déroulant <strong>Destination</strong> pour sélectionner le point final du trafic à autoriser 
			ou à refuser sur l'interface LAN ou WAN.<br>
			<strong><em>Adresse IP</em></strong> -
			Vous pouvez définir ici une adresse IP source ou cible unique dans la zone supérieure
  			ou une plage d'adresses IP en saisissant la première adresse IP de la plage dans la zone supérieure et
 			la dernière adresse IP de la plage dans la zone inférieure.<br>
			<strong><em>Protocole</em></strong> -
			Utilisez le menu déroulant <strong>Protocole</strong> pour sélectionner le type de trafic.<br>
			<strong><em>Plage de ports</em></strong> -
			Entrez le même numéro de port dans les deux zones pour définir un seul port ou entrez le premier port de 
			la plage dans la zone supérieure et le dernier port de la plage dans la zone inférieure pour définir une 
			plage de ports.<br>
			<strong><em>Programmation</em></strong> -
			Utilisez le menu déroulant <strong>Toujours</strong> pour sélectionner une programmation précédemment 
			définie ou cliquez sur le bouton <strong>Ajouter nouvelle</strong> pour ajouter une nouvelle programmation.
 </p>
	</div></td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
 <tr>
 <td height=20><p><strong>Paramètres avancés - Connexion sans fil <a name=09></a></strong></p>

 <p>Il est conseillé de ne modifier les options de cette page que si vous êtes un utilisateur avancé ou sur les instructions de nos agents d'assistance, car une mauvaise configuration de votre routeur risque d'altérer ses performances. </p>
 <p><strong><em>Vitesses de transmission (TX)  - </em></strong> Sélectionnez les vitesses de transmission de base en fonction de la vitesse des adaptateurs sans fil du réseau local sans fil (WLAN). </p>
 <p><strong><em>Gain à l'émission - </em></strong>Vous pouvez réduire la puissance de sortie du <?query("/sys/modelname");?> en diminuant le pourcentage de gain à l'émission dans ce menu déroulant. Les valeurs disponibles sont : 100%, 50%, 25% et 12,5%. </p>
 <p><strong><em>Intervalle balise - </em></strong> Les balises sont des paquets envoyés par un Point d’accès pour synchroniser un réseau sans fil. Indiquez une valeur d'Intervalle de balise comprise entre 20 et 1000. La valeur par défaut est 100 millisecondes. </p>

 <p><strong><em>Seuil RTS - </em></strong> Cette valeur doit rester à son réglage par défaut de 2346. Si vous êtes confronté à des flux de données irréguliers, nous vous conseillons de n'apporter que des modifications mineures de la plage de valeurs entre 1 et 2346. La valeur par défaut du Seuil RTS est 2346. </p>
 <p><strong><em>Fragmentation - </em></strong> Cette valeur doit rester à son réglage par défaut de 2346. Si vous êtes confronté à un taux d'erreur des paquets élevé, vous pouvez augmenter légèrement votre
 valeur &quot;Fragmentation&quot; à l'intérieur de la plage de valeurs comprise entre 256 et 2346. Avec une valeur de Fragmentation trop faible, les performances risquent d'être médiocres. </p>
 <p><strong><em>Intervalle DTIM - </em></strong> Saisissez une valeur comprise entre 1 et 255 pour le DTIM (Delivery Traffic Indication Message, message d'indication du trafic livré). Un DTIM est un décompte qui informe les clients de la fenêtre d'écoute suivante pour les messages à diffusion générale ou à multidiffusion. Quand le Point d'accès a mis en mémoire tampon les messages à diffusion générale ou à multidiffusion pour les clients associés, il envoie le DTIM suivant avec une valeur d'Intervalle DTIM. Les clients du point d'accès &quot;entendent&quot; les balises et se mettent à l'écoute pour recevoir les messages à diffusion générale ou à multidiffusion. La valeur par défaut de l'Intervalle DTIM est 1. </p>

 <p><strong><em>Type de préambule - </em></strong> Le Type de préambule définit la longueur du bloc CRC (Cyclic Redundancy Check, contrôle par redondance cyclique) pour la communication entre le Point d'accès et les adaptateurs sans fil itinérants. Veillez à sélectionner le type de préambule approprié, puis cliquez sur le bouton Appliquer. </p>
 <p><span class="style2">Remarque : </span>les zones à trafic réseau élevé doivent utiliser le type de préambule le plus court possible. Le CRC est une technique courante de détection des erreurs de transmission de données. </p>
 <p><strong><em>Mode CTS - </em></strong>Sélectionnez Aucun pour désactiver cette fonction. Sélectionnez Auto pour que le routeur demande à tous les périphériques sans fil du réseau de procéder à un établissement de liaison RTS/CTS avant de les autoriser à transmettre des données. Sélectionnez Auto pour autoriser le routeur à décider des cas nécessitant un établissement de liaison RTS/CTS. </p>
 <p><strong><em>Mode 802.11g uniquement - </em></strong>Activez ce mode si votre réseau est constitué uniquement d'appareils 802.11g. Si vous possédez à la fois des clients sans fil 802.11b et  802.11g, désactivez ce mode. </p> </td>

 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=20><p><strong>Réseau avancé <a name=10></a></strong></p>

 <p>Certains paramètres de cette section peuvent modifier la manière dont le routeur gère certains types de trafic. Nous vous conseillons de ne pas modifier ces paramètres à moins de bien les maîtriser ou d'en avoir reçu l'instruction de l'un de nos agents d'assistance. </p>

<!--
 <p><strong>Interconnexion VPN </strong><br>L'appareil prend en charge l'interconnexion VPN (Virtual Private Network, réseau privé virtuel) pour les protocoles PPTP (Point-to-Point Tunneling Protocol) et IPSec (IP Security). Lorsque l'interconnexion VPN est activée, il est inutile de créer des entrées de serveur virtuel ou de redirection de port pour que les sessions VPN sortantes s'établissent correctement. Il est possible de réaliser plusieurs connexions VPN par l'intermédiaire de l'appareil. Cela est utile quand vous avez de nombreux clients VPN sur le réseau local. </p>
-->

 <p><strong>UPnP </strong><br>UPnP est l'acronyme d'Universal Plug and Play, une architecture de mise en réseau qui assure la compatibilité entre les équipements réseau, les logiciels et les périphériques. Le <?query("/sys/modelname");?> est un routeur compatible UPnP et fonctionne, à ce titre, avec d'autres appareils/logiciels UPnP. Si vous ne souhaitez pas utiliser la fonctionnalité UPnP, vous pouvez la désactiver en sélectionnant &quot;Désactivée&quot;. </p>
 <p><strong>Ping WAN </strong><br>Lorsque vous activez la réponse aux Ping WAN, l'adresse IP WAN (réseau étendu) publique de l'appareil répond aux commandes Ping envoyées par les utilisateurs Internet. Le ping d'adresses IP WAN publiques est une méthode généralement utilisée par les pirates informatiques pour vérifier la validité de votre adresse IP WAN. </p>
 <p><strong>Débit port WAN </strong><br>Cette option permet de spécifier le débit de l'interface WAN du <?query("/sys/modelname");?> : 100 Mbps, 10 Mbps ou 10/100 Mbps Auto. </p>

<!-- <p><strong>Mode jeu </strong><br>Si vous rencontrez des difficultés lorsque vous jouez en ligne ou même lorsque vous utilisez certaines applications qui utilisent des données vocales, vous pouvez essayer d'activer le Mode jeu pour que ces applications fonctionnent correctement. Lorsque vous ne jouez pas ou que vous n'utilisez pas ces applications vocales, nous vous recommandons de désactiver le Mode jeu. </p> -->
<!--
 <p><strong>Multicast Streams</strong><br>Enable this option to allow Multicast traffic to pass from the Internet to your network more efficiently. </p> </td>
-->
<?if(query("/runtime/func/dis_multicast_stream")!="1"){
echo " <p><strong>Flux de données en multidiffusion</strong><br>Activez cette option pour autoriser le trafic en multidiffusion à circuler plus efficacement d'Internet à votre réseau.  </p> </td>\n";
}
?>
 </tr>

<?if(query("/runtime/func/dis_multicast_stream")!="1"){
echo "<tr><td height=20>&nbsp;</td></tr>\n";
echo "<tr>\n";
echo "	<td height=20>\n";
echo "		<p>\n";
echo "			<strong>Activer les flux de multidiffusion</strong><br>\n";
echo "			Activez cette option si vous recevez des services Internet de type vidéo à la demande. \n";
echo "			Le routeur utilise le protocole IGMP pour offrir une multidiffusion efficace (transmission de contenu identique,\n";
echo " 			multimédia, par exemple, d'une source vers plusieurs destinataires). Cette option doit être activée si des\n";
echo " 			applications du LAN participent à un groupe de multidiffusion.  Si l'une des applications multimédia de votre \n";
echo "			LAN ne reçoit pas normalement du contenu, essayez d'activer cette option.\n";
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
echo "	<td height=99><strong>Routage </strong><a name=11></a><br>\n";
echo "		L'option Routage vous permet de définir des routes fixes vers les cibles définies.<br>\n";
echo "		<strong><em>Activer </em></strong> - Indique si l'élément est activé ou désactivé.<br>\n";
echo "		<strong><em>Interface </em></strong> - Définit l'interface -- WAN ou WAN physique -- que\n";
echo "  		le paquet IP doit utiliser pour sortir du routeur, lorsque cette route est utilisée.<br>\n";
echo "		<strong><em>Interface (WAN)</em></strong> - Interface qui reçoit l'adresse IP fournie par \n";
echo "		le FAI pour accéder à Internet.<br>\n";
echo "		<strong><em>Interface (WAN physique)</em></strong> - Interface qui reçoit l'adresse IP fournie par \n";
echo "		le FAI pour accéder à Internet.<br>\n";
echo "		<strong><em>Cible </em></strong> - Adresse IP des paquets qui empruntent cette route.<br>\n";
echo "		<strong><em>Masque de sous-réseau </em></strong> - Les 1 du masque correspondent aux bits de \n";
echo "		l'adresse IP à conserver. <br>\n";
echo "		<strong><em>Passerelle </em></strong> - Indique le prochain saut si cette route est utilisée.  Dans une passerelle\n";
echo "	 	0.0.0.0, il n'y a pas de saut et l'adresse IP correspondante est directement connectée au routeur de l'interface\n";
 echo "		définie : WAN ou WAN physique.\n";
echo " </td>\n";
echo " </tr>\n";
}
?>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>

 </table>
