<div class="box">
<a name="admin"><h2>Admin</h2></a>
<table border=0 cellspacing=0 cellpadding=0>

<tr>
	<td height=20>
		
		<p>
			<strong><em>Nom de connexion de l'administrateur</em></strong> -
			Saisissez le nom utilisé pour connecter le routeur avec un accès Admin.
		</p>
		<p>
			<strong><em>Mot de passe administrateur</em></strong> -
			Saisissez et confirmez le mot de passe que le compte <strong>admin</strong> utilisera pour accéder à l'interface de gestion du routeur.
		</p>
		<p>
			<strong>Gestion à distance</strong><br>
			La gestion à distance permet de configurer les périphériques via le port de réseau étendu, depuis Internet, en utilisant un navigateur Web. Un nom d’utilisateur et un mot de passe restent nécessaires pour accéder à l'interface de gestion du routeur.
			<br>
			<strong><em>IP autorisée à accéder</em></strong> -
			Cette option permet aux utilisateurs d'indiquer une adresse IP autorisée à accéder au routeur à distance. Ce champ reste vierge par défaut : toutes les adresses IP provenant d'Internet peuvent accéder au routeur à distance une fois la gestion à distance activée.
			<br>
			<strong><em>Port</em></strong> - Sélectionnez le port utilisé pour accéder au <?query("/sys/modelname");?>.
		</p>
		<p>
			<strong><em>Exemple :  </em></strong><br>
			<a href="http://192.168.0.1/help_tools.html">http://x.x.x.x:8080 </a> , x.x.x.x correspondant à l’adresse IP du réseau étendu du <?query("/sys/modelname");?> et 8080, au port utilisé pour l’interface de gestion Web.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="time"><h2>Heure</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=33>
		<p>
			Le routeur utilise les paramètres Configuration de l'heure pour synchroniser les services programmés et les activités de consignation du système. Vous devrez régler le fuseau horaire correspondant à votre zone. Vous pouvez régler l'heure manuellement ou le périphérique peut se connecter à un serveur NTP (Network Time Protocol) pour la récupérer. Vous pouvez également régler les dates de l'heure d'été pour que le système s'adapte automatiquement.
		</p>
		<p>
			<strong><em>Fuseau horaire</em></strong> - Sélectionnez le fuseau horaire de votre zone.<br>
			<strong><em>Heure d'été</em></strong> -
			Si la région dans laquelle vous vous trouvez respecte l'heure d'été, activez cette option et précisez le mois, la semaine, le jour et l'heure de début et de fin de cette heure de l'année.<br>
			<strong><em>Configuration automatique de l'heure</em></strong> -
			Sélectionnez un serveur horaire D-Link avec lequel vous souhaiteriez synchroniser l'heure du <?query("/sys/modelname");?>. L'intervalle auquel le <?query("/sys/modelname");?> communique avec le serveur NTP D-Link est défini sur 7 jours.<br>
			<strong><em>Régler la date et l'heure manuellement</em></strong> -
			sélectionnez cette option pour régler l'heure manuellement. Vous devez indiquer l'année, le mois, le jour, l'heure, la minute et la seconde ou cliquer sur le bouton Copier les paramètres de temps de votre ordinateur pour copier l'heure du système de l'ordinateur utilisée pour accéder à l'interface de gestion.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="log_settings"><h2>Paramètres du journal</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			Vous pouvez enregistrer le fichier journal sur un disque local qui pourra être envoyé ultérieurement à un administrateur réseau à des fins de dépannage.
			<br>
			<strong><em>Enregistrer</em></strong> - Cliquez sur ce bouton pour enregistrer les entrées du journal dans un fichier texte.<br>
			<strong><em>Type de journal</em></strong> - Sélectionnez le type d'informations que le <?query("/sys/modelname");?> doit consigner.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="email_settings"><h2>Paramètres du courrier électronique</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			Les paramètres des courriers électroniques vous permettent d'envoyer le fichier journal du périphérique à une adresse électronique donnée.
			<br>
			<br>
			<strong><em>Adresse électronique De</em></strong> - 
			Adresse électronique d'où le courrier électronique a été envoyé. La plupart des services SMTP modernes requiert qu'il s'agisse d'une adresse électronique valide et de réaliser des tests pour vérifier si elle est authentique.<br>
			<strong><em>Adresse électronique À</em></strong> - 
			Adresse électronique à laquelle le fichier journal du périphérique est envoyé. Le fichier journal est visualisé par la personne qui accède à ce compte de messagerie.<br>
			<strong><em>Sujet du courrier électronique</em></strong> - 
			Titre du courrier électronique.<br>
			<strong><em>Adresse du serveur SMTP</em></strong> - 
			Adresse IP ou nom de domaine du serveur de messagerie qui transmet le fichier journal du périphérique au compte de messagerie requis.<br>
			<strong><em>Port du serveur SMTP</em></strong> - 
			Port que le serveur de messagerie utilise.<br>
			<strong><em>Activer l'authentification</em></strong> - 
			Pour des raisons de sécurité, certains serveurs SMTP contrôlent le nom et le mot de passe du compte pour confirmer que le courrier électronique qu'il traite provient de l'un de ses clients.<br>
			<strong><em>Nom du compte</em></strong> - 
			 Nom du compte utilisé pour authentifier le serveur SMTP.<br>
			<strong><em>Mot de passe</em></strong> - 
			Mot de passe du compte servant à authentifier le serveur SMTP.<br>
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="system"><h2>Système</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=40>
		La configuration actuelle du système peut être enregistrée sous forme de fichier sur le disque dur local. Le fichier enregistré ou tout autre fichier de configuration enregistré et créé par le périphérique peut être chargé sur la machine. Pour recharger un fichier de configuration système, cliquez sur <strong>Parcourir</strong> pour rechercher le fichier di disque dur local à utiliser. Le périphérique peut également être réinitialisé aux paramètres d'usine en cliquant sur <strong>Restaurer le périphérique</strong>. Utilisez cette fonction si nécessaire uniquement, car les paramètres précédemment enregistrés sur l'unité seront effacés. Veillez à enregistrer vos paramètres système avant de réaliser une restauration aux paramètres d'usine.
		<br>
		<strong><em>Enregistrer</em></strong> - Cliquez sur ce bouton pour enregistrer le fichier de configuration depuis le routeur.<br>
		<strong><em>Parcourir</em></strong> -
		Cliquez sur Browse (Parcourir) pour localiser un fichier de configuration enregistré, puis sur Load (Charger) pour appliquer les paramètres enregistrés au routeur.<br>
		<strong><em>Restaurer le périphérique</em></strong> -
		Cliquez sur ce bouton pour restaurer les paramètres par défaut du routeur.
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="firmware"><h2>Microprogramme</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=51>
	Cet outil vous permet de mettre le microprogramme du périphérique à jour. Vérifiez que le microprogramme que vous voulez utiliser est enregistré sur le disque dur local de l’ordinateur. Cliquez sur Browse (Parcourir) pour rechercher le microprogramme à utiliser pour la mise à jour sur le disque dur local. La mise à jour du microprogramme ne modifiera aucun paramètre de votre système, mais il est recommandé de sauvegarder la configuration de votre système avant d'effectuer cette mise à jour. Veuillez consulter le site d'assistance de D-Link <a href=<?query("/sys/supporturl");?>>concernant les</a> mises à jour du microprogramme. Vous pouvez également cliquer sur le bouton Check Now (Vérifier maintenant) pour que le routeur recherche automatiquement tout nouveau microprogramme éventuel.
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="dynamic_dns"><h2>DNS dynamique</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=2>
		<p>
			Le DNS (Domain Name Service) dynamique est une méthode permettant de maintenir le lien entre un nom de domaine et une adresse IP (dynamique) variable. Avec la plupart des connexions par câble ou DSL, on vous attribue une adresse IP dynamique qui est utilisée uniquement pendant la durée de cette connexion spécifique. Avec la <?query("/sys/modelname");?>, vous pouvez configurer votre service DDNS et la caméra fera une mise à jour automatique de votre serveur DDNS à chaque fois qu’elle recevra une nouvelle adresse IP de réseau étendu.
			<br>
			<strong><em>Adresse du serveur</em></strong> - Sélectionnez votre fournisseur DDNS dans le menu déroulant.<br>
			<strong><em>Nom d'hôte</em></strong> - Saisissez le nom d'hôte que vous avez enregistré avec votre fournisseur de service DDNS.<br>
			<strong><em>Nom d'utilisateur</em></strong> - Saisissez le nom d'utilisateur correspondant à votre compte DDNS.<br>
			<strong><em>Mot de passe</em></strong> - Saisissez le mot de passe correspondant à votre compte DDNS.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="system_check"><h2>Contrôle du système</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			Cet outil peut servir à vérifier la connectivité physique sur les interfaces du réseau local et Internet (réseau étendu). Cette fonction avancée intègre un testeur de câble de réseau local sur chaque port Ethernet du routeur. Grâce à l’interface graphique, le testeur de câble virtuel peut servir à diagnostiquer et signaler à distance des problèmes de câbles (par ex. ouvertures, court—circuit, permutations et discordance d’impédance). Cette fonction réduit considérablement les appels de maintenance et les renvois car elle permet aux utilisateurs de résoudre facilement leurs problèmes de connexions câblées.
		</p>
		<p>
			<strong>Test de ping</strong><br>
			Cet utilitaire de diagnostic utile peut servir à contrôler si un ordinateur est sur Internet. Il envoie des paquets de ping et écoute les réponses de l'hôte concerné. Saisissez un nom d'hôte ou l'adresse IP à laquelle vous voulez envoyer un ping (Packet Internet Groper), puis cliquez sur <strong>Ping</strong>. L'état de votre tentative de ping s'affiche dans la zone Ping Result (Résultat du ping).
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="schedules"><h2>Calendriers</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>	
			Cette page sert à configurer les calendriers globaux du routeur. Une fois définis, ils peuvent être appliqués ultérieurement aux fonctions du routeur qui prennent en charge la planification.
			<br>
			<strong><em>Nom</em></strong> - Nom du calendrier en cours de définition.<br>
			<strong><em>Jour(s)</em></strong> -
			Sélectionnez un jour, une plage de jours ou cochez la case All Week (Toute la semaine) pour que ce calendrier s'applique quotidiennement.<br>
			<strong><em>Toute la journée - 24 h</em></strong> -
			 Cochez cette case pour que le calendrier soit actif 24/24 h les jours indiqués.<br>
			<strong><em>Heure de départ</em></strong> -
			Sélectionnez l'heure à laquelle vous souhaitez que le calendrier en cours de définition devienne actif.<br>
			<strong><em>Heure de fin</em></strong> -
			Sélectionnez l'heure à laquelle vous souhaitez que le calendrier en cours de définition devienne inactif.<br>
			<strong><em>Liste de règles de planification</em></strong> -
			Cette liste affiche tous les calendriers définis.
		</p>
	</td>
</tr>
</table>
</div>

						   