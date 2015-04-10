<div class="box">
<a name="port_forwarding"><h2>Redirection de port</h2></a>
	<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=228>
		<p>
			L'option Advanced Port Forwarding (Redirection de port avancée) permet aux Internautes d'accéder aux services de votre réseau local. Cette option est utile pour accueillir les services en ligne, comme les serveurs FTP, Web ou de jeux. Pour chaque entrée, définissez un port public sur votre routeur afin de le rediriger vers une adresse IP du réseau local interne et un port du réseau local.
		</p>
		<p>
			Paramètres de redirection de port avancée
			<br>
			<strong><em>Nom</em></strong> -
			Attribuez un nom significatif au serveur virtuel (par ex. serveur Web). Plusieurs types connus de serveurs virtuels sont disponibles dans la liste déroulante « Application Name » (Nom de l'application). Si vous sélectionnez l'une de ces entrées, cela remplit certains paramètres restant avec des valeurs standards pour ce type de serveur.
			<br>
			<strong><em>Adresse IP </em></strong> -
			L'adresse IP du système présent sur votre réseau interne et qui fournit le service virtuel (par ex. 192.168.0.50). Vous pouvez sélectionner un ordinateur dans la liste de clients DHCP du menu déroulant « Computer Name » (Nom de l'ordinateur) ou saisir l'adresse IP de l'ordinateur serveur manuellement.<br>
			<strong><em>Nom d'application </em></strong> -
			Liste d'applications courantes prédéfinie dans laquelle les utilisateurs peuvent choisir une configuration.<br>
			<strong><em>Nom de l'ordinateur </em></strong> -  Liste de clients DHCP.<br>
			<strong><em>Type de trafic</em></strong> -
			Sélectionnez le protocole utilisé par le service. Les choix courants (UDP, TCP et UDP plus TCP) peuvent être sélectionnés dans le menu déroulant.<br>
			<strong><em>Port privé</em></strong> -
			Port utilisé sur votre réseau interne.<br>
			<strong><em>Port public</em></strong> -
			Port accessible sur Internet.<br>
		</p>
	</td>
</tr>
 </table>
 </div>
 
 
<div class="box">
<a name="application_rules"><h2>Règles d'application</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=64> 
Certaines applications nécessitent plusieurs connexions, notamment les jeux sur Internet, les vidéoconférences et la téléphonie par Internet. Ces applications fonctionnent difficilement via la traduction d'adresses de réseau (NAT). Si vous devez exécuter des applications nécessitant plusieurs connexions, précisez le port généralement associé à une application dans le champ « Trigger Port » (Port de déclenchement), sélectionnez le type de protocole : TCP (Transmission Control Protocol) ou UDP (User Datagram Protocol), puis saisissez les ports publics associés au port de déclenchement dans le champ Firewall Port (Port du pare-feu) afin de les ouvrir pour le trafic entrant. Certaines applications connues sont déjà définies dans le menu déroulant Application Name (Nom de l'application).
 <br>

<strong><em>Nom </em></strong> - Nom faisant référence à l'application. <br>
<strong><em>Port de déclenchement </em></strong>- Ce port sert à déclencher l’application. Il peut s’agir d’un seul port ou d’une plage de ports. <br>
<strong><em>Type de trafic </em></strong> - Ce protocole sert à déclencher l’application. <br>
<strong><em>Port du pare-feu </em></strong> - Ce numéro de port, situé du côté du réseau étendu, sert à accéder à l’application. Vous pouvez définir un seul port ou une plage de ports. Vous pouvez utiliser une virgule pour ajouter plusieurs ports ou une plage de ports. <br>
<strong><em>Type de trafic </em></strong> - Ce protocole sert pour l’application. </td>

 </tr>
 </table>
 </div>
 
 
<div class="box">
<a name="qos_engine"><h2>Moteur QoS</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
<td height=64>
		<p>
			Smart QoS améliore la qualité du système de voix sur IP ou la diffusion en garantissant que le trafic de voix sur IP ou de diffusion a la priorité sur le reste du trafic réseau (par ex. FTP ou Web). Pour optimiser les performances, cochez l'option « lag eliminated » (décalage éliminé) qui vous permet de définir la priorité de vos applications automatiquement.
			<br>
		</p>
</td>
</tr>
</table>
</div>
 
 
<div class="box">
<a name="access_control"><h2>Filtre réseau</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=99>
		<p>
			Les filtres servent à empêcher ou autoriser les ordinateurs du réseau local à accéder à Internet, ainsi qu'à votre réseau. Sur le réseau, l'unité peut être configurée pour autoriser ou refuser l'accès à Internet aux ordinateurs utilisant leurs adresses MAC.
		</p>
		<p>
			<strong>Filtres MAC</strong><br>
			Utilisez les filtres MAC pour empêcher les ordinateurs du réseau local d'accéder à Internet. Vous pouvez ajouter une adresse MAC manuellement ou en sélectionner une dans la liste de clients actuellement connectés à l'unité.
			<br>
			Sélectionnez « Turn MAC Filtering ON and ALLOW computers with MAC address listed below to access the network » (ACTIVER le filtrage MAC et AUTORISER les ordinateurs dont les adresses MAC sont répertoriées ci-dessous à accéder au réseau) pour que seuls les ordinateurs sélectionnés aient accès au réseau et que tous les autres n'y aient pas accès.
			<br>
			Sélectionnez « Turn MAC Filtering ON and DENY computers with MAC address listed below to access the network » (ACTIVER le filtrage MAC et EMPÊCHER les ordinateurs dont les adresses MAC sont répertoriées ci-dessous d'accéder au réseau) pour que tous les ordinateurs aient accès au réseau, sauf ceux de la liste.
			<br>
			<strong><em>Adresse MAC</em></strong> -
			Adresse MAC du périphérique réseau à ajouter à la liste de filtrage MAC.<br>
			<strong><em>Liste de clients DHCP</em></strong> -
			 Les noms d'hôtes des clients DHCP sont répertoriés dans le menu déroulant Computer Name (Nom de l'ordinateur). Vous pouvez sélectionner l'ordinateur client à ajouter à la liste de MAC Filter (Filtre MAC), puis cliquer sur la touche fléchée. Vous ajoutez ainsi automatiquement l'adresse MAC de cet ordinateur dans le champ approprié.
		</p>
		<p>
			Les utilisateurs peuvent utiliser le menu déroulant <strong>Toujours</strong> pour sélectionner un calendrier précédemment défini ou cliquer sur le bouton <strong>Ajouter un nouveau</strong> pour ajouter un nouveau calendrier.
		</p>
		<p>
			La case à cocher sert à activer ou désactiver une entrée donnée.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="parental_control"><h2>Filtre Web</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=44>
		<p>
			Outre la capacité à filtrer les périphériques qui peuvent accéder à votre réseau et à Internet, le <?query("/sys/modelname");?> peut également être configuré pour autoriser ou refuser l'accès à des sites Web indésirables aux ordinateurs du réseau en utilisant un nom de domaine ou des mots clés.
		</p>
		<p>
			<strong>Contrôle parental</strong><br>
			Le contrôle parental sert à autoriser ou refuser aux ordinateurs du réseau l'accès à des sites Web donnés en utilisant des mots clés ou des noms de domaine spécifiques. Sélectionnez « Turn Website Filtering ON and ALLOW computers access to ONLY these sites » (Activer le filtrage de sites Web et AUTORISER les ordinateurs à accéder à ces sites UNIQUEMENT) pour que seuls les ordinateurs du réseau puissent accéder aux URL et aux noms de domaine indiqués. Sélectionnez « Turn Website Filtering ON and DENY computers access to ONLY these sites » (Activer le filtrage de sites Web et EMPÊCHER les ordinateurs d'accéder à ces sites UNIQUEMENT) pour que les ordinateurs du réseau ne puissent pas accéder aux URL et aux noms de domaine indiqués.
		</p>
		<p>
			<span class="style1">Exemple 1 :</span><br>
			Pour bloquer des utilisateurs du réseau local afin qu'ils ne puissent pas accéder à des sites Web contenant une URL liée au shopping, vous devez sélectionner « Turn Website Filtering ON and DENY computers access to ONLY these sites » (Activer le filtrage de sites Web et EMPÊCHER les ordinateurs d'accéder à ces sites UNIQUEMENT), puis saisir « shopping » dans la liste Website Filtering Rules (Règles de filtrage de sites Web). Les utilisateurs du réseau local ne peuvent pas accéder à ces sites car ils conviennent le mot clé dans l'URL.
			<br>
			<a href="http://www.yahoo.com/shopping/stores.html">http://www.yahoo.com/shopping/stores.html</a><br>
			<a href="http://www.msn.com/search/shopping-spree.html">http://www.msn.com/search/shopping-spree.html</a>
		</p>
		<p>
			<span class="style1">Exemple 2 :</span><br>
			Pour que vos enfants ne puissent qu'accéder à des sites particuliers, vous devez ensuite choisir « Turn Website Filtering ON and ALLOW computers access to ONLY these sites » (Activer le filtrage de sites Web et AUTORISER les ordinateurs à accéder à ces sites UNIQUEMENT).
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
<a name="firewall_dmz"><h2>Paramètres du pare-feu</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			La section Firewall Settings (Paramètres du pare-feu) comporte une option permettant de configurer un hôte DMZ.
		</p>
		<p>
			<strong>Activer SPI</strong><br>
			SPI (« Stateful Packet Inspection », également appelée « filtrage de paquets dynamique ») permet d'éviter les attaques Internet en suivant davantage d'états par session. Il atteste que le trafic passant par la session est conforme au protocole. Lorsque le protocole est TCP, le SPI contrôle que les numéros de séquence des paquets se trouvent dans la plage valide de la session et élimine ceux dont les numéros de séquence sont incorrects. Que le SPI soit activé ou non, le routeur suit toujours les états de connexion TCP et veille à ce que les indicateurs de paquets TCP soient valides pour l'état actuel.
		</p>
		<p>
			<strong>DMZ </strong><br>
			Si un ordinateur ne peut pas exécuter les applications Internet correctement derrière le <?query("/sys/modelname");?>, vous pouvez l'autoriser à avoir un accès illimité à Internet. Saisissez l'adresse IP de cet ordinateur en tant qu'hôte DMZ (zone démilitarisée) avec un accès Internet illimité. Si vous ajoutez un client à la DMZ, vous risquez d’exposer l'ordinateur à divers risques pour la sécurité. Veillez par conséquent à n’utiliser cette option qu’en dernier recours.
		</p>
		<p>
			<strong>Règles du pare-feu</strong><br>
			Les règles de pare-feu servent à autoriser ou refuser au trafic d'entrer ou sortir du routeur en fonction des adresses IP source et cible, ainsi que du type de trafic et du port sur lequel les données sont exécutées.
			<br>
			<strong><em>Nom</em></strong> - Les utilisateurs peuvent indiquer un nom de règle de pare-feu.<br>
			<strong><em>Action</em></strong> - Les utilisateurs peuvent choisir d'autoriser ou de refuser le trafic.<br>
			<strong>Interface</strong><br>
			<strong><em>Source</em></strong> -
			Utilisez le menu déroulant <strong>Source</strong> pour indiquer si le point de départ du trafic autorisé ou refusé provient de l'interface du réseau local ou étendu.<br>
			<strong><em>Cible</em></strong> -
			Utilisez le menu déroulant <strong>Cible</strong> pour sélectionner si le point final du trafic autorisé ou refusé provient de l'interface du réseau local ou étendu.<br>
			<strong><em>Adresse IP</em></strong> -
			Ici, vous pouvez indiquer une seule adresse IP source ou cible en la saisissant dans la case supérieure ou saisir une plage d'adresses IP en saisissant la première adresse IP de la plage dans la case supérieure et la dernière dans celle du bas.<br>
			<strong><em>Protocole</em></strong> -
			Utilisez le menu déroulant <strong>Protocole</strong> pour sélectionner le type de trafic.<br>
			<strong><em>Plage de ports</em></strong> -
			Saisissez le même numéro de port dans les deux cases pour indiquer un seul port ou saisissez le premier port de la plage dans la case supérieure et le dernier dans celle du bas pour indiquer qu'il y a une plage de ports.<br>
			<strong><em>Calendrier</em></strong> -
			Utilisez le menu déroulant <strong>Toujours</strong> pour sélectionner un calendrier précédemment défini ou cliquez sur le bouton <strong>Ajouter un nouveau</strong> pour ajouter un nouveau calendrier.
 </p>
</td>
</tr>
</table>
</div>


<div class="box">
<a name="routing"><h2>Routage</h2></a>
<table>
<?if(query("/runtime/func/dis_routing")!="1"){
echo "<tr>\n";
echo "	<td height=99>\n";
echo "		L'option Routing (Routage) vous permet de définir les voies statiques menant à des cibles spécifiques.<br>\n";
echo "		<strong><em>Activer </em></strong> - Indique si l'entrée est activée ou désactivée.<br>\n";
echo "		<strong><em>Interface </em></strong> - Indique l'interface (réseau étendu ou réseau étendu physique) que \n";
echo "		le paquet IP doit utiliser pour sortir du routeur, lorsque cette voie est utilisée.<br>\n";
echo "		<strong><em>Interface (Réseau étendu)</em></strong> - Interface servant à recevoir l'adresse IP \n";
echo "		du FAI pour accéder à Internet.<br>\n";
echo "		<strong><em>Interface (Réseau étendu physique)</em></strong> - Interface servant à recevoir l'adresse \n";
echo "		IP du FAI pour accéder à Internet.<br>\n";
echo "		<strong><em>Cible </em></strong> - Adresse IP des paquets empruntant cette route.<br>\n";
echo "		<strong><em>Masque de sous-réseau </em></strong> - Un bit dans le masque qui indique \n";
echo "		quels bits de l'adresse IP doivent correspondre. <br>\n";
echo "		<strong><em>Passerelle </em></strong> - Définit le prochain bon à prendre si cette route est utilisée. \n";
echo "		Une passerelle de 0.0.0.0. indique qu'il n'y a pas de bon à prendre et que l'adresse IP correspondante \n";
echo "		est connectée directement au routeur sur l'interface indiquée : réseau étendu ou réseau étendu physique. \n";
echo " </td>\n";
echo " </tr>\n";
}
?>
</table>
</div>


<div class="box">
<a name="advanced_wireless"><h2>Paramètres sans fil avancés</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=20>

 <p>Les options de cette page doivent être modifiées par les utilisateurs avancés ou si un membre de notre personnel d'assistance vous le demande, car cela risque de nuire aux performances de votre routeur s'il est mal configuré.
 </p>
 <p><strong><em>Puissance de transmission - </em></strong>Vous pouvez diminuer la puissance de sortie du <?query("/sys/modelname");?> en sélectionnant un pourcentage de valeurs de puissance de transfert inférieur dans le menu déroulant. Vous avez le choix entre : 100 %, 50 %, 25 % et 12,5 %. </p>
 <p><strong><em>Intervalle de balise - </em></strong> Les balises sont de paquets envoyés par un point d’accès pour synchroniser le réseau sans fil. Indiquez une valeur d'intervalle de balise située comprise entre 20 et 1000. Elle est par défaut définie sur 100 millisecondes. </p>

 <p><strong><em>Seuil RTS - </em></strong> Vous devez conserver la valeur par défaut (2 346). Si votre débit de données fluctue, il est recommandé d'appliquer des modifications mineures seulement à la plage de valeurs située entre 256 et 2 346. La valeur par défaut du seuil RTS est définie sur 2 346. </p>
 <p><strong><em>Fragmentation - </em></strong> Vous devez conserver la valeur par défaut (2 346). Si vous subissez des taux d'erreur de paquets élevés, vous pouvez augmenter légèrement la valeur « Fragmentation » dans la plage de valeurs comprise entre 1 500 et 2 346. Si vous réglez cette valeur trop basse, vous risquez de nuire aux performances. </p>
 <p><strong><em>Intervalle DTIM - </em></strong> Saisissez une valeur comprise entre 1 et 255 pour DTIM (Delivery Traffic Indication Message). Un DTIM est un compte à rebours qui informe les clients de la fenêtre suivante pour écouter les messages de diffusion générale et de multidiffusion. Après avoir tamponné le point d'accès ou de multidiffusion pour les clients associés, le point d'accès sans fil envoie le DTIM suivant, accompagné d'une valeur d'intervalle DTIM. Les clients AP entendent les balises et s'activent pour recevoir des messages de diffusion générale et de multidiffusion. La valeur par défaut de l'intervalle DTIM est définie sur 1. </p>

 <p><strong><em>Type de préambule - </em></strong> Le type de préambule définit la longueur du bloc CRC (Cyclic Redundancy Check) destiné à la communication entre le point d'accès et les adaptateurs sans fil itinérants. Veillez à sélectionner le type de préambule adapté, puis cliquez sur le bouton Apply (Appliquer). </p>
 <p><span class="style2">Remarque :  </span>dans le cas d'un trafic élevé, utilisez le préambule court. Le CRC est une technique courante de détection des erreurs de transmission des données. </p>
 <p><strong><em>Mode CTC - </em></strong>Sélectionnez None (Aucun) pour désactiver cette fonction. Sélectionnez Always (Toujours) pour obliger le routeur à exiger que chaque périphérique sans fil du réseau réalise une liaison RTS/CTS avant de pouvoir transmettre des données. Sélectionnez Auto pour autoriser le routeur à décider quand des liaisons RTS/CTS sont nécessaires. </p>
<?if(query("/runtime/func/ieee80211n")!="1"){
 echo "<p><strong><em>802.11g Only Mode - </em></strong>Enable this mode if your network is made up of purely 802.11g devices. If you have both 802.11b and 802.11g wireless clients, disable this mode. </p> </td>";
}?>
 </tr>
 </tr>
 </table>
 </div>
 
 
<div class="box">
<a name="advanced_network"><h2>Réseau avancé</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=20>

 <p>Cette section comporte les paramètres pouvant modifier la manière dont le routeur gère certains types de trafics. Nous recommandons de ne pas les modifier, sauf si vous les maîtrisez déjà ou si un membre de notre personnel d'assistance vous l'a demandé.
 </p>

<!--
 <p><strong>VPN Passthrough </strong><br>The device supports VPN (Virtual Private Network) passthrough for PPTP (Point-to-Point Tunneling Protocol) and IPSec (IP Security). Once VPN passthrough is enabled, there is no need to create any Virtual Server or Port Forwarding entries in order for outbound VPN sessions to be established properly. Multiple VPN connections can be made through the device. This is useful when you have many VPN clients on the Local Area Network. </p>
-->

 <p><strong>UPnP </strong><br>UPnP est l'acronyme de Universal Plug and Play, une architecture de réseau qui assure la compatibilité entre es équipements, logiciels ou périphériques connectés en réseau. Le <?query("/sys/modelname");?> est un routeur UPnP ; il est donc compatible avec les autres périphériques/logiciels UPnP. Si vous ne voulez pas utiliser la fonction UPnP, vous pouvez la désactiver en sélectionnant « Disabled » (Désactivé).
 </p>
 <p><strong>Ping du réseau étendu </strong><br>Lorsque vous utilisez Enable WAN Ping respond (Activer la réponse au ping du réseau étendu), l'adresse IP du réseau public étendu du périphérique répond aux commandes ping envoyées par les Internautes. L'envoi de pings aux adresses IP publiques du réseau étendu est une méthode fréquemment utilisée par les pirates pour vérifier si l'adresse IP de votre réseau étendu est valide.
 </p>
 <p><strong>Vitesse du port du réseau étendu </strong><br>Cela vous permet de sélectionner la vitesse de l'interface du réseau étendu du <?query("/sys/modelname");?> : sélectionnez 100Mbps, 10Mbps ou 10/100/1000Mbps Auto.
 </p>

<!--
 <p><strong>Gaming Mode </strong><br>If you are experiencing difficulties when playing online games or even certain applications that use voice data, you may need to enable Gaming Mode in order for these applications to work correctly. When not playing games or using these voice applications, it is recommended that Gaming Mode is disabled. </p>
--> 

<?if(query("/runtime/func/dis_multicast_stream")!="1"){
echo " <p><strong>Flux de données en multidiffusion</strong><br>Activez cette option pour que le trafic de multidiffusion passe d'Internet à votre réseau plus efficacement. </p> </td>\n";
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
<a name="guest_zone"><h2>Zone invité</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			Sélection de la zone invité<br>
			La sélection vous aide à définir l'échelle de la zone invité.<br>
			<strong><em>Activer la zone invité</em></strong>  - Indique si la zone invité est activée ou désactivée.<br>
			<strong><em>Inclure le port du réseau local</em></strong>  - Indique quel port du réseau local sera inclus dans la zone invité.<br>
			<strong><em>Inclure le réseau sans fil</em></strong>  -  Indique si une zone sans fil supplémentaire est utilisée pour la zone invité ou non.<br>
			<strong><em>Nom du réseau sans fil</em></strong> -  Nommez un réseau sans fil pour la zone invité. <br>
		</p>
		<p>
			<strong><em>Mode de sécurité sans fil</em></strong><br>
			Il est important de sécuriser votre réseau sans fil afin de protéger l'intégrité des informations qui y sont transmises. Le <?query("/sys/modelname");?> accepte 4 types de sécurité sans fil : WEP, WPA seulement, WPA2 seulement et WPA/WPA2 (détection automatique).
			 <br>
		</p>
		<p>
			<strong><em>WEP</em></strong><br>
			Le WEP (Wired Equivalent Protocol) est un protocole de sécurité sans fil pour les réseaux locaux sans fil (WLAN). Le WEP vise à fournir une sécurité en chiffrant les données qui sont envoyées sur le WLAN. Le <?query("/sys/modelname");?> prend en charge 2 niveaux de chiffrement WEP : 64 bits et 128 bits. Le WEP est désactivé par défaut. Le paramètre WEP peut être modifié pour s'adapter à un réseau sans fil existant ou pour personnaliser votre réseau sans fil.
		 <br>
		</p>
		<p>
			<strong><em>Authentification</em></strong> - Processus par lequel le <?query("/sys/modelname");?> vérifie l'identité d'un périphérique réseau qui tente de joindre le réseau sans fil. Il existe deux types d'authentification pour ce périphérique lorsque vous utilisez le WEP. <br>
			<strong><em>Système ouvert</em></strong> -Sélectionnez cette option pour autoriser tous les périphériques réseaux à communiquer avec le <?query("/sys/modelname");?> avant que la clé de chiffrement nécessaire pour pouvoir accéder au réseau ne leur soit demandée. <br>
			<strong><em>Clé partagée </em></strong> - Sélectionnez cette option pour demander à tous les périphériques réseaux tentant de communiquer avec le <?query("/sys/modelname");?> de fournir la clé de chiffrement nécessaire pour accéder au réseau avant qu'ils ne soient autorisés à communiquer avec le <?query("/sys/modelname");?>. <br>
			<strong><em>Chiffrement WEP</em></strong> -  Sélectionnez le niveau de chiffrement WEP que vous souhaiteriez utiliser sur votre réseau. Les deux niveaux de chiffrement WEP pris en charge sont 64 bits et 128 bits.<br>
			<strong><em>Type de clé </em></strong> -  Les types de clé qui sont pris en charge par le <?query("/sys/modelname");?> sont les formats HEX (Hexadécimal) et ASCII (American Standard Code for Information Interchange). Le type de clé peut être modifié pour s'adapter à un réseau sans fil existant ou pour personnaliser votre réseau sans fil. <br>
			<strong><em>Clés</em></strong> -  Les clés 1 à 4 vous permettent de modifier facilement les paramètres de chiffrement sans fil pour maintenir un réseau sécurisé. Sélectionnez simplement la clé spécifique à utiliser pour chiffrer les données sans fil sur le réseau. <br>
		</p>
		<p>
			<strong><em>WPA personnel</em></strong><br>
			Le WPA (Wi-Fi Protected Access) permet d'autoriser et d'authentifier les utilisateurs sur le réseau sans fil. Le WPA est plus sécurisé que le WEP et repose sur une clé qui change automatiquement à un intervalle régulier.
			 <br>
		</p>
		<p>
			<strong><em>Type de chiffrement</em></strong> - Le <?query("/sys/modelname");?> prend en charge deux types de chiffrement différents lorsque le WPA est utilisé comme le type de sécurité. Ces deux options sont le TKIP (Temporal Key Integrity Protocol) et l'AES (Advanced Encryption Standard). <br>
			<strong><em>PSK/EAP</em></strong> -Lorsque le mode PSK est sélectionné, vos clients sans fil devront fournir une phrase de passe pour l'authentification. Lorsque le mode EAP est sélectionné, vous devrez disposer d'un serveur RADIUS sur votre réseau qui gérera l'authentification de tous vos clients sans fil. <br>
			<strong><em>Mot de passe </em></strong> -  Il s'agit de ce que vos clients sans fil auront besoin pour communiquer avec votre <?query("/sys/modelname");?>, lorsque le mode PSK est sélectionné. Entrez 8 à 63 caractères alphanumériques. Veillez à noter cette phrase de passe étant donné que vous aurez besoin de l'entrer sur tout autre périphérique réseau que vous tentez d'ajouter à votre réseau. <br>
			<strong><em>802.1X </em></strong> - Cela signifie que l'authentification WPA est utilisée conjointement avec un serveur RADIUS qui doit être présent sur votre réseau. Entrez l'adresse IP, le port, et le secret partagé pour lesquels votre serveur RADIUS est configuré. Vous disposez également de l'option d'entrer des informations pour un deuxième serveur RADIUS dans le cas où il y en a deux sur votre réseau que vous utilisez pour authentifier les clients sans fil.<br>
		</p>
		<p>
			<strong><em>WPA2</em></strong><br>
			Le WPA (Wi-Fi Protected Access) 2 permet d'autoriser et d'authentifier les utilisateurs sur le réseau sans fil. Le WPA2 est plus sécurisé que le WEP et repose sur une clé qui change automatiquement à un intervalle régulier.
		 <br>
		</p>
		<p>
			<strong><em>Type de chiffrement</em></strong> - Le <?query("/sys/modelname");?> prend en charge deux types de chiffrement différents lorsque le WPA est utilisé comme le type de sécurité. Ces deux options sont le TKIP (Temporal Key Integrity Protocol) et l'AES (Advanced Encryption Standard). <br>
			<strong><em>PSK/EAP</em></strong> -  Lorsque le mode PSK est sélectionné, vos clients sans fil devront fournir une phrase de passe pour l'authentification. Lorsque le mode EAP est sélectionné, vous devrez disposer d'un serveur RADIUS sur votre réseau qui gérera l'authentification de tous vos clients sans fil. <br>
			<strong><em>Mot de passe</em></strong> -  Il s'agit de ce que vos clients sans fil auront besoin pour communiquer avec votre <?query("/sys/modelname");?>, lorsque le mode PSK est sélectionné. Entrez 8 à 63 caractères alphanumériques. Veillez à noter cette phrase de passe étant donné que vous aurez besoin de l'entrer sur tout autre périphérique réseau que vous tentez d'ajouter à votre réseau. <br>
			<strong><em>802.1X </em></strong> -  Cela signifie que l'authentification WPA2 est utilisée conjointement avec un serveur RADIUS qui doit être présent sur votre réseau. Entrez l'adresse IP, le port, et le secret partagé pour lesquels votre serveur RADIUS est configuré. Vous disposez également de l'option d'entrer des informations pour un deuxième serveur RADIUS dans le cas où il y en a deux sur votre réseau que vous utilisez pour authentifier les clients sans fil. <br>
		</p>
		<p>
			<strong><em>WPA2-Auto</em></strong> <br>
			Cette option permet au <?query("/sys/modelname");?> de connecter les clients WPA2 et WPA simultanément.<br>
		</p>
		<p>
			<strong><em>Configuration du réseau local pour la zone invité</em></strong><br> 
			Ces paramètres permettent de configurer l'interface de réseau local de la zone invité du périphérique. Ces paramètres peuvent être qualifiés de « paramètres privés ». Vous pouvez modifier l'adresse IP, si nécessaire. L'adresse IP est propre à votre réseau interne et n'est pas visible sur Internet. L'adresse IP par défaut est 192.168.1.1, le masque de sous-réseau étant 255.255.255.0.
			<br>
		</p>
		<p>
			<strong><em>Adresse IP</em></strong> -  L'adresse IP par défaut du <?query("/sys/modelname");?> est 192.168.1.1. <br>
			<strong><em>Masque de sous-réseau</em></strong> - Le masque de sous-réseau par défaut du <?query("/sys/modelname");?> est 255.255.255.0. <br>
		</p>
		<p>
			<strong><em>Activer l'isolation du client dans la zone invité</em></strong> : <br>
			Activez cette fonction pour éviter qu'un client invité n'accède à d'autres clients de la zone invité. Le client invité peut uniquement accéder à Internet.
			 <br>
		</p>
		<p>
			<strong><em>Activer le routage entre les zones</em></strong> : <br>
			Utilisez cette section pour activer le routage entre la zone hôte et la zone invité ; les clients invités ne peuvent pas accéder aux données des clients hôtes sans activer cette fonction.
			 <br>
		</p>
		<p>
			<strong><em>Serveur DHCP pour zone invité</em></strong> <br>
			DHCP (Dynamic Host Control Protocol) est un protocole de contrôle dynamique de l'hôte. Le serveur DHCP attribue des adresses IP aux périphériques du réseau qui en font la demande. Ces périphériques doivent être configurés sur « Obtenir une adresse IP automatiquement ». Par défaut, le serveur DHCP est activé sur le <?query("/sys/modelname");?>. Le groupe d'adresses DHCP contient la plage d'adresses IP qui seront automatiquement attribuées aux clients du réseau.
		 <br>
		</p>
		<p>
			<strong><em>Adresse IP de départ</em></strong> - Adresse IP de départ pour l'attribution d'adresses IP au serveur DHCP. <br>
			<strong><em>Adresse IP finale</em></strong> -Adresse IP finale pour l'attribution d'adresses IP au serveur DHCP. <br>
			<strong><em>Durée de concession</em></strong> - Durée en minutes pendant laquelle est effective la concession IP. Les informations des clients DHCP dynamiques connectés au périphérique seront affichées dans le tableau des clients DHCP dynamiques. Le tableau affichera le nom de l'hôte, l'adresse IP, l'adresse MAC et l'heure d'expiration de la concession DHCP pour chaque client. <br>
		</p>
</td>
</tr>
</table>
</div>
 
<div class="box">
<a name="wake_on_lan"><h2>Réveil à distance</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			La fonction Wake on LAN (Réveil à distance) peut servir à allumer un PC connecté au côté réseau local du routeur à distance. Indiquez le port UDP utilisé par le paquet magique Wake on LAN (Réveil à distance) pour éviter que le routeur ne pense que la demande Wake on LAN (Réveil à distance) est une attaque hostile et la bloque.
			<br>
			<br>
			<strong><em>Port UDP</em></strong> - 
			Le seul port que le <?query("/sys/modelname");?> utilise pour écouter les paquets magiques qui allument le PC.<br>
			<strong><em>Interface</em></strong> - 
			 (Actuellement, ce paramètre ne peut pas être modifié. il sera peut-être modifiable dans des versions ultérieures du microprogramme).<br>		
		</p>
	</td>
</tr>
</table>
</div>
