<div class="box">
<a name="disk_management"><h2>Gestion du disque</h2></a>
	<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			La page Disk Management (Gestion du disque) comporte des informations et des paramètres relatifs au disque dur local actuellement installé sur le périphérique.
			<br>
			<br>
			<strong><em>Informations sur le disque dur</em></strong> -
			Contient les détails relatifs au disque dur installé sur le périphérique.<br>
			<strong><em>Définition du format</em></strong> -
			Ce bouton vous permet de formater le disque dur actuellement installé sur le périphérique.<br>
			AVERTISSEMENT : Cette action nettoie le disque dur. Toutes les données du disque dur seront perdues !
			<br>
			<strong><em>Configuration du disque dur</em></strong> -
			Une fois ce paramètre activé, le disque dur entre en mode veille après le nombre de minutes indiqué si aucune donnée n'est écrite ou lue dessus, pour réduire la consommation d'énergie.<br>
		</p>
	</td>
</tr>
 </table>
</div>

<div class="box">
<a name="users_groups"><h2>Utilisateurs / Groupes</h2></a>
	<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=228>
		<p>
			<strong>Utilisateurs</strong><br>
			Vous pouvez créer les utilisateurs ici. Ces comptes peuvent être ajoutés aux règles dans les sections Network Access (Accès au réseau) et FTP Server (Serveur FTP). Chaque utilisateur créé a également accès à la section Scheduled Download (Téléchargement planifié).
		</p>
		<p>
			<strong><em>Nom d'utilisateur</em></strong> -
			 Saisissez votre nom d'utilisateur.<br>
			<strong><em>Mot de passe</em></strong> -
			Saisissez votre mot de passe.<br>
			<strong><em>Confirmer le mot de passe</em></strong> -
			Saisissez de nouveau votre mot de passe. Cliquez sur « Save Settings » (Enregistrer les paramètres) pour ajouter l'utilisateur.<br>
			<br>
			Les utilisateurs créés apparaissent dans une liste en bas de la page, avec le groupe auquel ils sont affectés (le cas échéant). Les mots de passe des utilisateurs peuvent être modifiés en cliquant sur l'icône de « bloc-notes avec crayon » et les utilisateurs peuvent être supprimés en cliquant sur l'icône « corbeille » à droite de la règle.		
		</p>
		<p>
			<strong>Groupes</strong><br>
			Vous pouvez créer les groupes ici, puis les sélectionner dans Group (Groupe) sur la page Users (Utilisateurs).
			<br>
			<br>
			Les groupes créés apparaissent dans une liste à la fin de cette page. Les utilisateurs de ces groupes s'affichent également.
			<br>
		</p>
	</td>
</tr>
 </table>
</div>
 
 
<div class="box">
<a name="storage_access"><h2>Accès au stockage</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=64> 
		<p>
			<strong><em>Catégorie</em></strong> -
			Sélectionnez User (Utilisateur) ou Group (Groupe).<br>
			<strong><em>Utilisateur ou Groupe</em></strong> -
			Sélectionnez un utilisateur ou un groupe dans le menu déroulant. Sélectionnez « All Accounts » (Tous les comptes) pour créer une règle applicable à tous les utilisateurs.<br>
			<strong><em>Dossier</em></strong> -
			Cliquez sur « Browse » (Parcourir) pour sélectionner un dossier. Ce dossier doit se trouver sur les disques internes.<br>
			<strong><em>Permission</em></strong> -
			Attribuez des permissions « Read Only » (Lecture seule) ou « Read / Write » (Lire / Écrire) du dossier sélectionné à l'utilisateur ou au groupe sélectionné.<br>
			<strong><em>Oplocks</em></strong> -
			Le verrouillage opportuniste (oplock) est une caractéristique du protocole de mise en réseau du gestionnaire de réseau local mis en œuvre dans la famille de système d'exploitation Windows 32 bits. Les oplocks sont des garanties accordées par un serveur pour un volume logique partagé avec ses clients. Ces garanties informent le client que le contenu d’un fichier ne peut pas être modifié par le serveur ou, si certains changements sont imminents, le client est averti avant que le changement ne puisse être réalisé. Les oplocks sont destinés à améliorer les performances du réseau en cas de partage de fichiers sur le réseau. Cependant, lorsque des applications de bases de données basées sur les fichiers sont utilisées, il est recommandé de définir les oplocks de partage sur <strong>Non(désactivé)</strong>. <br>
			<br>
			Quels systèmes d'exploitation sont affectés par les oplocks ?
			<br>
			<br>
			Par défaut, Vista active les oplocks et vous ne pouvez pas les désactiver. Si vous rencontrez des problèmes de performances du réseau avec les applications de partage de fichiers provenant du DIR-685, vous pouvez tenter de les améliorer en définissant les oplocks sur <strong>Non(désactivé)</strong>.<br>
			<strong><em>Connecter les archives</em></strong> -
			Lorsque cette option est activée, l’attribut « Archive » du fichier est copié à mesure que le fichier est stocké sur le DIR-685. Certains logiciels de sauvegarde joignent cet attribut aux fichiers en cours de stockage sous forme de sauvegardes.<br>
			<strong><em>Commentaire</em></strong> -
			Commentaires supplémentaires sur cette règle. Cette option est facultative et n'a aucune effet sur le fonctionnement.<br>
			<br>
			Cliquez sur Save Settings (Enregistrer les paramètres) pour enregistrer la règle. Toutes les règles enregistrées apparaissent dans la liste à la fin de cette page. Elles peuvent être modifiées ou supprimées en cliquant sur l'icône de « bloc-notes avec crayon » ou de « corbeille » à droite de la règle.
			<br>
		</p>
 </tr>
</table>
</div>
 
 
<div class="box">
<a name="ftp_server"><h2>Serveur FTP</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=99>
		<p>
			<strong><em>Catégorie</em></strong> -
			Sélectionnez User (Utilisateur) ou Group (Groupe).<br>
			<strong><em>Utilisateur</em></strong> -
			Sélectionnez un utilisateur ou un groupe dans le menu déroulant. Sélectionnez « All Accounts » (Tous les comptes) pour créer une règle applicable à tous. Anonymous (Anonyme) est toujours répertorié en tant qu'utilisateur.<br>
			<strong><em>Dossier</em></strong> -
			Cliquez sur « Browse » (Parcourir) pour sélectionner un dossier et lui attribuer l'utilisateur sélectionné. Ce dossier doit se trouver sur les disques internes. Si vous souhaitez autoriser l'accès à la racine de tous les lecteurs simultanément, cochez la case « root » (racine).<br>
			<strong><em>Permission</em></strong> -
			Attribuez des permissions « Read Only » (Lecture seule) ou « Read / Write » (Lire / Écrire) du dossier sélectionné à l'utilisateur ou au groupe sélectionné. Cliquez sur « Add » (Ajouter) pour ajouter la règle dans la liste. Toutes les règles enregistrées apparaissent dans la liste à la fin de cette page. Elles peuvent être modifiées ou supprimées en cliquant sur l'icône de « bloc-notes avec crayon » ou de « corbeille » à droite de la règle.<br>
			<strong><em>Nombre d'utilisateurs max.</em></strong> -
			Saisissez le nombre d'utilisateurs maximum autorisés à accéder simultanément au serveur FTP. La valeur par défaut est 10.<br>
			<strong><em>Temps d'inactivité</em></strong> -
			Le serveur FTP déconnecte un utilisateur s'il dépasse le temps d'inactivité indiqué.<br>
			<strong><em>Port</em></strong> -
			Si vous souhaitez modifier le port utilisé par le serveur FTP, saisissez le nouveau numéro ici. Il peut s'agir d'un paramètre avancé ; un changement peut alors entraîner des complications lorsque vous êtes derrière le routeur. Il est recommandé de le laisser à sa valeur par défaut (21), sauf si vous maîtrisez les changements de port FTP.<br>
			<strong><em>Contrôle du débit</em></strong> -
			Cette fonction ajuste le débit de données passant par le serveur FTP. Si vous définissez une limite ici, les utilisateurs pourront télécharger des données du serveur FTP à une vitesse plus lente, mais conserveront la largeur de bande locale.<br>
			<strong><em>Langue du client</em></strong> -
			La plupart des clients FTP standards (par ex. FTP Windows) ne prennent en charge que les pages de code d’Europe Occidentale pour transférer les fichiers. La prise en charge des pages de code d'Europe du Nord, d'Europe Centrale, de chinois traditionnel et simplifié a été ajoutée pour les clients FTP non standards capables de prendre en charge ces ensembles de caractères.<br>
			<br>
			Cliquez sur « Save Settings » (Enregistrer les paramètres) lorsque vous avez terminé.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="upnp_av_server"><h2>Serveur UPnP AV</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=44>
		<p>
			Le DIR-685 possède un serveur multimédia UPnP AV pouvant être utilisé avec les lecteurs multimédia UPnP AV compatibles.
			<br>
			<br>
			<strong><em>Serveur UPnP AV</em></strong> -
			Active ou désactive le serveur AV UPnP.<br>
			<strong><em>Dossier</em></strong> -
			Cliquez sur « Browse » (Parcourir) pour localiser le dossier racine de vos fichiers multimédia (musique, photos et vidéo). Vous pouvez choisir Root (Racine) pour accéder à tout le contenu du DIR-685.<br>
			<strong><em>Actualisation auto</em></strong> -
			Configure l'actualisation automatique pour mettre vos données UPNP AV partagées automatiquement à jour toutes les 5, 15 ou 30 minutes ou à intervalles de 1, 2, 6, 12 ou 24 heures.<br>
			<br>
			Cliquez sur « Save Settings » (Enregistrer les paramètres) lorsque vous avez terminé.<br>
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="itunes_server"><h2>Serveur iTunes</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			Le serveur iTunes permet au logiciel iTunes de détecter automatiquement et de lire la musique sur le DIR-685.
			<br>
			<br>
			<strong><em>Serveur iTunes</em></strong> -
			Active ou désactive le serveur iTunes.<br>
			<strong><em>Dossier</em></strong> -
			 Cliquez sur « Browse » (Parcourir) pour localiser le dossier contenant vos fichiers de musique. Vous pouvez choisir Root (Racine) pour accéder à tous les dossiers du DIR-685.<br>
			<strong><em>Actualisation auto</em></strong> -
			Configure l'actualisation automatique pour mettre les données de votre bibliothèque iTunes partagées automatiquement à jour toutes les 5, 15 ou 30 minutes ou à intervalles de 1, 2, 6, 12 ou 24 heures.<br>
			<br>
			Cliquez sur « Save Settings » (Enregistrer les paramètres) lorsque vous avez terminé.<br>
		</p>
</td>
</tr>
</table>
</div>

<div class="box">
<a name="bt_download_manager"><h2>Gestionnaire de téléchargement BT</h2></a>
	<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			La page BT Download Manager (Gestionnaire de téléchargement BT) comporte les paramètres permettant de configurer votre périphérique pour que les fichiers Bit Torrent puissent être téléchargés sur Internet sans devoir allumer votre PC.
			<br>
			<br>
			<strong><em>Paramètre BT</em></strong> -
			Vous permet d'activer/désactiver le service de gestionnaire de téléchargement BT. Le chemin d'accès au répertoire vous permet d'indiquer dans quel répertoire/dossier vous souhaitez enregistrer vos fichiers téléchargés. Tous les téléchargements sont enregistrés dans le répertoire indiqué, tous les éléments terminés étant enregistrés dans le répertoire nommé « completed » (terminé) et tous les éléments en cours, enregistrés dans un répertoire nommé « incomplete » (incomplet). L'organisation des fichiers de chaque téléchargement reste strictement identique à celle des fichiers initialement téléchargés.<br>
			<strong><em>Téléchargements de torrents</em></strong> -
			À l'écran BT Download Manager (Gestionnaire de téléchargement BT), vous pouvez choisir d'ajouter de nouveaux éléments téléchargés via une URL ou à partir d'un fichier de distribution BT individuel.<br>
			Tous les éléments en cours de téléchargement sont répertoriés en bas de la fenêtre, à raison d'un téléchargement par ligne pour que vous puissiez voir clairement et gérer chaque élément en cours de téléchargement.
			<br>
			<strong><em>Tableau d'éléments en cours de téléchargement</em></strong> -
			Pour chaque élément en cours de téléchargement, cliquez sur le lien « more details » (plus de détails) pour obtenir des informations complémentaires sur les téléchargements en cours.<br>
			<strong><em>Arrêter</em></strong> -
			Les utilisateurs peuvent utiliser ce bouton pour arrêter/mettre en pause le processus de téléchargement, ce qui permet à d'autres éléments en cours de téléchargement de profiter d'une plus grande largeur de bande.<br>
			<strong><em>Supprimer</em></strong> -
			En cas d'erreur, les utilisateurs peuvent utiliser ce bouton, situé à droite de chaque élément en cours de téléchargement, pour annuler/supprimer l'élément en cours de téléchargement.<br>
			<br>
			Si l'élément supprimé a déjà été réalisé, seule l'entrée est supprimée ; les fichiers déjà téléchargés restent dans le répertoire « completed » (terminé).
			<br>
			<strong><em>Suppression terminée</em></strong> -
			Ce bouton, situé dans le coin supérieur droit du tableau d'éléments en cours de téléchargement, permet aux utilisateurs de supprimer du tableau tous les éléments dont le téléchargement est terminé, sans supprimer les fichiers téléchargés.<br>			
		</p>
	</td>
</tr>
 </table>
</div>
