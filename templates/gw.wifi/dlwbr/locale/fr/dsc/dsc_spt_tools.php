<h1>MENU ASSISTANCE</h1>
<table border=0 cellspacing=0 cellpadding=0 width=750>
<tr>
<td height=2><b><font size=4>Maintenance</font></b></td>
</tr>
<tr>
<td height=16><p><br>
</td>
</tr>
<tr>
	<td height=20>
		<strong>Administration de périphérique</strong><a name=12></a><br>
		<p>
			<strong><em>Nom de connexion administrateur</em></strong> -
			Saisissez le nom qui vous permettra de vous connecter au routeur en tant qu'administrateur.
		</p>
		<p>
			<strong><em>Mot de passe administrateur</em></strong> -
			Saisissez puis confirmez le mot de passe que le compte <strong>admin </strong> utilisera pour accéder à l'interface de gestion du routeur.
		</p>
		<p>
			<strong>Gestion à distance</strong><br>
			La Gestion à distance permet de configurer l'appareil grâce au port WAN (réseau étendu), 
			à partir d'Internet et à l'aide d'un navigateur Web. Un nom d'utilisateur et un mot de passe 
			sont toujours nécessaires pour accéder à l'interface de gestion du routeur.<br>
			<strong><em>Adresse IP autorisée d'accès</em></strong> -
			Cette option permet aux utilisateurs de définir une adresse IP sur Internet, autorisée à accéder au routeur à
 			distance. Par défaut, cette option est vide. Cela signifie qu'une fois la gestion à distance activée, 
			toutes les adresses IP sur Internet pourront accéder au routeur à distance.<br>
			<strong><em>Port</em></strong> - Sélectionnez le port qui sera utilisé pour accéder au <?query("/sys/modelname");?>.
		</p>
		<p>
			<strong><em>Exemple: </em></strong><br>
			<a href="http://192.168.0.1/help_tools.html">http://x.x.x.x:8080 </a> où x.x.x.x est l'adresse IP WAN 
			du <?query("/sys/modelname");?> et 8080, le port utilisé pour l'interface de gestion Web.
		</p>
	</td>
</tr>
<tr><td height=10>&nbsp;</td></tr>
<tr><td height=10>&nbsp;</td></tr>
<tr>
	<td height=40>
		<a name=14><strong>Enregistrer et restaurer</strong></a><br>
		Vous pouvez enregistrer les paramètres système actuels dans un fichier sur le disque dur local. 
		Le fichier enregistré ou tout autre fichier de configuration enregistré créé par l'appareil peut 
		être chargé sur l'appareil. Pour charger de nouveau un fichier de paramètres système, 
		cliquez sur <strong>Parcourir</strong> pour localiser le fichier à utiliser sur le disque dur local. 
		Il est également possible de réinitialiser l'appareil aux paramètres d'usine par défaut en cliquant 
		sur <strong>Restaurer le périphérique</strong>. N'utilisez la fonctionnalité de restauration que si 
		cela est nécessaire. Elle efface en effet les paramètres préalablement enregistrés pour l'appareil. 
		Assurez-vous d'avoir enregistré vos paramètres système avant de procéder à la restauration des paramètres d'usine.<br>
		<strong><em>Enregistrer</em></strong> - Cliquez sur ce bouton pour enregistrer le fichier de configuration à partir du routeur.<br>
		<strong><em>Parcourir</em></strong> -
		Cliquez sur Parcourir pour rechercher un fichier de configuration enregistré, 
		puis sur Charger pour appliquer au routeur les paramètres enregistrés.<br>
		<strong><em>Restaurer le périphérique</em></strong> -
		Cliquez sur ce bouton pour restaurer les paramètres d'usine par défaut du routeur.
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=51>
		<b>Mise à jour du firmware</b><a name=15></a><br> 
		Cet outil vous permet de mettre à niveau le firmware de l'appareil. Assurez-vous que le firmware 
		que vous souhaitez utiliser est enregistré sur le disque dur local de l'ordinateur. 
		Cliquez sur <strong>Parcourir </strong> pour rechercher le firmware à utiliser pour la mise à jour 
		sur le disque dur local. La mise à niveau du firmware ne modifie aucun des paramètres système, 
		mais nous vous recommandons de sauvegarder vos paramètres système avant de procéder à ce type de mise à niveau. 
		Vous pouvez vérifier la présence de mises à jour du firmware sur le site d'assistance D-Link 
		ou cliquer sur le bouton Vérifier maintenant pour que le routeur recherche automatiquement les mises à jour. 
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=2>
		<p>
			<strong>Paramètre DDNS </strong><a name=16></a><br>
			Le DNS (Domain Name Service, service de noms de domaines) dynamique est une méthode qui 
			consiste à conserver l'association d'un nom de domaine avec une adresse IP qui varie (dynamique). 
			Dans la plupart des connexions par câble ou ligne DSL, une adresse IP dynamique vous est attribuée. 
			Celle-ci n'est utilisée que pendant la durée de cette connexion spécifique. 
			Grâce au <?query("/sys/modelname");?>, vous pouvez configurer le service DDNS ; le <?query("/sys/modelname");?>
			met automatiquement à jour votre serveur DDNS à chaque fois qu’il reçoit une nouvelle adresse IP WAN.<br>
			<strong><em>Adresse du serveur</em></strong> - Dans le menu déroulant, sélectionnez votre fournisseur de DDNS.<br>
			<strong><em>Nom d'hôte</em></strong> - Entrez le nom d'hôte enregistré chez votre fournisseur de services DDNS.<br>
			<strong><em>Nom d'utilisateur</em></strong> - Indiquez le nom d'utilisateur de votre compte DDNS.<br>
			<strong><em>Mot de passe</em></strong> - Indiquez le mot de passe de votre compte DDNS.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height="197">
		<p>
			<strong>Vérification système</strong><a name=17></a><br>
			Cet outil permet de vérifier la connectivité physique des interfaces de réseau local et étendu. 
			Il s'agit d'une fonctionnalité avancée qui intègre un testeur de câble LAN sur chaque port Ethernet 
			du routeur. Grâce à son interface utilisateur graphique, le test du câble permet d'effectuer des 
			diagnostics à distance et de signaler les défauts de câble tels que les coupures, les courts-circuits, 
			les permutations et les défauts d'adaptation d'impédance. Cette fonctionnalité permet de réduire de 
			manière significative les appels de service et les retours, puisqu'elle permet aux utilisateurs de 
			dépanner facilement leurs connexions par câble.
		</p>
		<p>
			<strong>Test Ping</strong><br>
			Il s'agit d'un utilitaire de diagnostic que vous pouvez utiliser pour vérifier si un ordinateur se 
			trouve sur Internet. Il envoie des paquets Ping et écoute les réponses en provenance de l'hôte 
			considéré. Saisissez le nom d'hôte ou l'adresse IP que vous souhaitez vérifier par un Ping 
			(Packet Internet Groper), puis cliquez sur <strong>Ping </strong>. L'état de votre test Ping apparaît 
			dans la zone Résultat du Ping.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td>
		<p>
			<strong>Programmation<a name=18></a></strong></p>
			Cette page permet de configurer des programmations globales pour le routeur. Une fois définies, 
			ces programmations peuvent ensuite être appliquées aux fonctionnalités du routeur qui prennent 
			en charge les programmations.<br>
			<strong><em>Nom</em></strong> - Nom de la programmation en cours de définition.<br>
			<strong><em>Jour(s)</em></strong> -
			Sélectionnez un jour, une plage de jours ou cochez la case Toute la semaine pour appliquer la 
			programmation tous les jours.<br>
			<strong><em>Toute la journée - 24 h </em></strong> -
			Cochez cette case pour que la programmation reste activée toute la journée les jours spécifiés.<br>
			<strong><em>Heure de début</em></strong> -
			Sélectionnez l'heure à laquelle vous souhaitez que la programmation en cours de définition s'active.<br>
			<strong><em>Heure de fin</em></strong> -
			Sélectionnez l'heure à laquelle vous souhaitez que la programmation en cours de définition se désactive.<br>
			<strong><em>Liste des règles de programmation</em></strong> -
			Affiche toutes les programmations définies.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td>
		<p>
			<strong>Paramètres de consignation</strong><strong><a name=19></a></strong><br>
			Vous pouvez enregistrer le fichier journal sur un disque dur local et l'envoyer par la suite 
			à un administrateur réseau à des fins de dépistage des pannes.<br>
			<strong><em>Enregistrer</em></strong> - Cliquez sur ce bouton pour enregistrer les entrées de journal dans un fichier texte.<br>
			<strong><em>Type de journal</em></strong> - Sélectionnez le type d'informations que vous souhaitez que le <?query("/sys/modelname");?> enregistre.
		</p>
	</td>
</tr>

</table>
						   
