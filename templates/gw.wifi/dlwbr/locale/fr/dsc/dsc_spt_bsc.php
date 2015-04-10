<h1>MENU ASSISTANCE</h1>
<table border=0 cellspacing=0 cellpadding=0 width=750>
<tr>
	<td height=40>
		<p><font size=4><strong>Configuration</strong></font></p>
		<p>
			<a name=01><strong>Configuration Internet</strong></a><br>
			Si c'est la première fois que vous configurez le périphérique, 
			nous vous recommandons d'ouvrir l'Assistant de configuration de 
			la connexion Internet et de suivre les instructions qui s'affichent. 
			Pour configurer le périphérique ou modifier ses paramètres manuellement, 
			cliquez sur Configuration manuelle de la connexion Internet.
		</p>
	</td>
</tr>
<tr>
	<td height=59>
		<p>
			<strong>Lancer l'assistant de configuration de la connexion Internet  </strong><br>
			Cliquez sur ce bouton pour que le routeur vous aide à établir la connexion avec 
			Internet en quelques étapes simples.<br>
			<strong>Lancer l'assistant de configuration de la sécurité sans fil </strong><br>
			Cliquez sur ce bouton pour que le routeur vous aide à configurer les paramètres 
			de votre réseau sans fil et notamment la sécurité.
		</p>
	</td>
</tr>
<tr><td height=32>&nbsp;</td></tr>
<tr>
	<td height=46>
		<p>
			<strong>Configuration manuelle de la connexion Internet</strong><br>
			Sélectionnez cette option si vous souhaitez entrer manuellement les paramètres 
			nécessaires à la connexion de votre routeur à Internet.<br>
			<strong>Mode Point d'accès</strong><br>
			Si vous activez le mode &quot;Point d'accès&quot;, l'appareil fonctionnera comme un point d'accès sans fil. 
			Toutes les fonctions NAT seront désactivées sauf les paramètres sans fil.<br>
			<strong>Type de connexion Internet  </strong><br>
			Les paramètres de connexion Internet permettent de connecter le <?query("/sys/modelname");?> à Internet. 
			Toutes les informations à saisir dans cette page seront fournies par votre fournisseur d'accès. 
			Elles sont souvent appelées &quot;paramètres publics&quot;. Veuillez sélectionner l'option appropriée 
			pour votre fournisseur d'accès. Si vous n'êtes pas sûr de l'option à choisir, contactez votre fournisseur d'accès.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=61>
		<p>
			<strong>Adresse IP statique</strong><br>
			Sélectionnez cette option si votre FAI (fournisseur d'accès à Internet) vous a fourni une adresse IP, 
			un masque de sous-réseau, une passerelle par défaut et une adresse de serveur DNS. 
			Entrez ces informations dans les champs correspondants. Si vous n'êtes pas sûr de savoir renseigner ces champs, 
			contactez votre fournisseur d'accès.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=142>
		<p>
			<strong>Adresse IP dynamique</strong><br>
			Sélectionnez cette option si votre fournisseur d'accès vous communique automatiquement une adresse IP. 
			Les fournisseurs de modems câble utilisent généralement l'attribution dynamique.
		</p>
		<p>
			<strong><em>Nom d'hôte </em></strong> (facultatif) -
			Le champ Nom d'hôte est facultatif, mais peut être exigé par certains fournisseurs d'accès. 
			Le nom d'hôte par défaut est la référence du routeur.<br>
			<strong><em>Adresse MAC </em></strong> (facultative) -
			Le champ Adresse MAC (Media Access Control) est exigé par certains fournisseurs d'accès. 
			L'adresse MAC par défaut est l'adresse MAC de l'interface WAN du <?query("/sys/modelname");?>. 
			Vous pouvez utiliser le bouton &quot;Cloner l'adresse MAC&quot; pour copier automatiquement l'adresse MAC 
			de la carte Ethernet installée sur l'ordinateur utilisé pour configurer l'appareil. 
			Ne renseignez ce champ que si votre fournisseur d'accès l'exige.<br>
			<strong><em>Adresse DNS principal </em></strong> -
			Saisissez l'adresse IP du serveur DNS (Domain Name Service) principal communiquée par votre fournisseur d'accès.<br>
			<strong><em>Adresse DNS secondaire </em></strong> (facultative) -
			Si votre fournisseur d'accès vous a communiqué une adresse IP de serveur DNS secondaire, indiquez-la dans ce champ.<br>
			<strong><em>MTU </em></strong> -
			La valeur MTU (Maximum Transmission/Transfer Unit) est la taille maximale des paquets qui peuvent être 
			transmis sur un réseau. Les messages dont la taille est supérieure à la valeur MTU sont divisés en paquets 
			plus petits. La valeur par défaut de cette option est 1500. Modifier cette valeur peut altérer les performances 
			de votre routeur. Ne la modifiez que sur les instructions d'un de nos agents d'assistance ou de votre 
			fournisseur d'accès.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=47>
		<p>
			<strong>PPPoE</strong><br>
			Sélectionnez cette option si votre fournisseur d'accès exige que vous utilisiez une connexion PPPoE 
			(Point to Point Protocol over Ethernet). Les fournisseurs de lignes DSL utilisent généralement cette option.
			Sélectionnez PPPoE dynamique pour obtenir une adresse IP automatiquement pour votre connexion PPPoE 
			(utilisée par la plupart des connexions PPPoE). Sélectionnez PPPoE statique pour utiliser une adresse IP 
			statique pour votre connexion PPPoE.
		</p>
		<p>
			<strong><em>Nom d'utilisateur </em></strong> - Saisissez votre nom d'utilisateur PPPoE.<br>
			<strong><em>Mot de passe </em></strong> - Saisissez votre mot de passe PPPoE.<br>
			<strong><em>Nom de service </em></strong> (facultatif) -
			Si votre fournisseur d'accès utilise un nom de service pour la connexion PPPoE, saisissez-le ici.<br>
			<strong><em>Adresse IP </em></strong> -
			Cette option n'est disponible que pour PPPoE statique. Saisissez l'adresse IP statique pour la connexion PPPoE.<br>
			<strong><em>Adresse MAC </em></strong> (facultative) -
			Le champ Adresse MAC (Media Access Control) est exigé par certains fournisseurs d'accès. L'adresse MAC par défaut
 			est l'adresse MAC de l'interface WAN du <?query("/sys/modelname");?>. Vous pouvez utiliser le bouton &quot;Cloner
 			l'adresse MAC&quot; pour copier automatiquement l'adresse MAC de la carte Ethernet installée sur l'ordinateur
 			utilisé pour configurer l'appareil. Ne renseignez ce champ que si votre fournisseur d'accès l'exige.<br>
			<strong><em>Adresse DNS principal </em></strong> -
			Adresse IP du serveur DNS (Domain Name System) principal communiquée par votre fournisseur d'accès. 
			Ne renseignez ce champ que si vous avez sélectionné l'option PPPoE statique. Si vous avez opté pour 
			PPPoE dynamique, conservez la valeur par défaut renseignée automatiquement par votre fournisseur d'accès.<br>
			<strong><em>Adresse DNS secondaire </em></strong> (facultative) -
			Si votre fournisseur d'accès vous a communiqué une adresse IP de serveur DNS secondaire, indiquez-la dans ce champ.<br>
			<strong><em>Temps d'inactivité maximum </em></strong> -
			Le temps d'inactivité avant la déconnexion de votre appareil de votre session PPPoE. Saisissez un Temps
 			d'inactivité maximum (en minutes) pour définir une période maximale de temps pendant laquelle la connexion
 			Internet est maintenue, même en cas d'inactivité. Si la connexion est inactive pendant plus longtemps que 
			le Temps d'inactivité maximum, elle est interrompue. Cette option ne s'applique qu'au mode de connexion 
			à la demande.<br>
			<strong><em>MTU </em></strong> -
			La valeur MTU (Maximum Transmission/Transfer Unit) est la taille maximale des paquets qui peuvent être 
			transmis sur un réseau. Les messages dont la taille est supérieure à la valeur MTU sont divisés en paquets 
			plus petits. La valeur par défaut de cette option est 1492. Modifier cette valeur peut altérer les performances 
			de votre routeur. Ne la modifiez que sur les instructions d'un de nos agents d'assistance ou de votre 
			fournisseur d'accès.<br>
			<strong><em>Sélection du mode de connexion</em></strong> -
			Sélectionnez Toujours activé pour que le routeur ne déconnecte jamais la session PPPoE. 
			Choisissez le mode manuel pour contrôler la connexion et la déconnexion d'Internet du routeur. 
			Avec l'option Connexion à la demande, le routeur n'établit une connexion à Internet que lorsqu'un 
			périphérique de votre réseau tente d'accéder à une ressource sur Internet.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>PPTP</strong><br>
			Sélectionnez cette option si votre fournisseur d'accès utilise une connexion PPTP 
			(Point to Point Tunneling Protocol) et vous a attribué un nom d'utilisateur et un mot de passe pour 
			accéder à Internet. Sélectionnez PPTP dynamique pour obtenir une adresse IP automatiquement pour votre 
			connexion PPTP. Sélectionnez PPTP statique pour utiliser une adresse IP statique pour votre connexion PPTP.
		</p>
		<p>
			<strong><em>Adresse IP </em></strong> - Indiquez l'adresse IP que votre fournisseur d'accès vous a attribuée.<br>
			<strong><em>Masque de sous-réseau </em></strong> - Indiquez le masque de sous-réseau que votre fournisseur d'accès vous a attribué.<br>
			<strong><em>Passerelle</em></strong> - Indiquez l'adresse IP de la passerelle que votre fournisseur d'accès vous a attribuée.<br>
			<strong><em>DNS - </em></strong>Indiquez l'adresse DNS que votre fournisseur d'accès vous a attribuée.<br>
			<strong><em>Adresse IP du serveur </em></strong> -
			Indiquez l'adresse IP du serveur auquel vous vous connecterez. Cette information vous sera communiquée par votre fournisseur d'accès.<br>
			<strong><em>Compte </em></strong> - Saisissez votre nom d'utilisateur PPTP.<br>
			<strong><em>Mot de passe </em></strong> - Saisissez votre mot de passe PPTP.<br>
			<strong><em>Temps d'inactivité maximum </em></strong> -
			Le temps d'inactivité avant la déconnexion de votre appareil de votre session PPTP. 
			Saisissez un Temps d'inactivité maximum (en minutes) pour définir une période maximale de temps pendant 
			laquelle la connexion Internet est maintenue, même en cas d'inactivité. Si la connexion est inactive pendant 
			plus longtemps que le Temps d'inactivité maximum, elle est interrompue. Cette option ne s'applique qu'au mode 
			de connexion à la demande.<br>
			<strong><em>MTU </em></strong> -
			La valeur MTU (Maximum Transmission/Transfer Unit) est la taille maximale des paquets qui peuvent être transmis
 			sur un réseau. Les messages dont la taille est supérieure à la valeur MTU sont divisés en paquets plus petits. 
			La valeur par défaut de cette option est 1400. Modifier cette valeur peut altérer les performances de votre
 			routeur. Ne la modifiez que sur les instructions d'un de nos agents d'assistance ou de votre 
			fournisseur d'accès.<br>
			<strong><em>Sélection du mode de connexion</em></strong> -
			Sélectionnez Toujours activé pour que le routeur ne déconnecte jamais la session PPTP. 
			Choisissez le mode manuel pour contrôler la connexion et la déconnexion d'Internet du routeur. 
			Avec l'option Connexion à la demande, le routeur n'établit une connexion à Internet que lorsqu'un 
			périphérique de votre réseau tente d'accéder à une ressource sur Internet.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>L2TP </strong><br>
			Sélectionnez cette option si votre fournisseur d'accès utilise une connexion L2TP (Layer 2 Tunneling Protocol) 
			et vous a attribué un nom d'utilisateur et un mot de passe pour accéder à Internet. Sélectionnez L2TP dynamique
	 		pour obtenir une adresse IP automatiquement pour votre connexion L2TP. Sélectionnez L2TP statique pour utiliser
 			une adresse IP statique pour votre connexion L2TP.
		</p>
		<p>
			<strong><em>Adresse IP </em></strong> - Indiquez l'adresse IP que votre fournisseur d'accès vous a attribuée.<br>
			<strong><em>Masque de sous-réseau </em></strong> - Indiquez le masque de sous-réseau que votre fournisseur d'accès vous a attribué.<br>
			<strong><em>Passerelle</em></strong> - Indiquez l'adresse IP de la passerelle que votre fournisseur d'accès vous a attribuée.<br>
			<strong><em>DNS</em></strong> - Indiquez l'adresse DNS que votre fournisseur d'accès vous a attribuée.<br>
			<strong><em>Adresse IP du serveur </em></strong> -
			Indiquez l'adresse IP du serveur auquel vous vous connecterez. Cette information vous sera communiquée par votre fournisseur d'accès.<br>
			<strong><em>Compte L2TP </em></strong> - Saisissez votre nom d'utilisateur L2TP.<br>
			<strong><em>Mot de passe L2TP </em></strong> - Saisissez votre mot de passe L2TP.<br>
			<strong><em>Temps d'inactivité maximum </em></strong> -
			Le temps d'inactivité avant la déconnexion de votre appareil de votre session L2TP. Saisissez un Temps
 			d'inactivité maximum (en minutes) pour définir une période maximale de temps pendant laquelle la connexion
 			Internet est maintenue, même en cas d'inactivité. Si la connexion est inactive pendant plus longtemps que le 
			Temps d'inactivité maximum, elle est interrompue. Cette option ne s'applique qu'au mode de connexion 
			à la demande.<br>
			<strong><em>MTU</em></strong> -
			La valeur MTU (Maximum Transmission/Transfer Unit) est la taille maximale des paquets qui peuvent être transmis sur un réseau. 
			Les messages dont la taille est supérieure à la valeur MTU sont divisés en paquets plus petits. 
			La valeur par défaut de cette option est 1400. Modifier cette valeur peut altérer les performances de votre routeur. 
			Ne la modifiez que sur les instructions d'un de nos agents d'assistance ou de votre fournisseur d'accès. 
			<strong><em>Sélection du mode de connexion</em></strong> -
			Sélectionnez Toujours activé pour que le routeur ne déconnecte jamais la session L2TP. 
			Choisissez le mode manuel pour contrôler la connexion et la déconnexion d'Internet du routeur. 
			Avec l'option Connexion à la demande, le routeur n'établit une connexion à Internet que lorsqu'un 
			périphérique de votre réseau tente d'accéder à une ressource sur Internet.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>PPTP Russie (accès double)</strong><br>
			Pour configurer une connexion Internet PPTP en Russie, procédez comme décrit précédemment pour les connexions PPTP. Si une route statique doit être configurée par votre FAI, reportez-vous à la fonction &quot;Routage&quot; du menu &quot;AVANCÉ&quot;pour accéder à la configuration avancée.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>PPPoE Russie (accès double)</strong><br>
			Certaines connexions PPPoE utilisent une route IP statique vers le FAI en plus des paramètres IP globaux pour la connexion. Une étape supplémentaire est alors requise pour définir les paramètres IP du port WAN physique. Pour configurer une connexion Internet PPPoE en Russie, procédez comme décrit précédemment pour les connexions PPPoE, puis ajoutez les paramètres IP WAN physiques en suivant les instructions données par votre FAI. Si une route statique doit être configurée par votre FAI, reportez-vous à la fonction &quot;Routage&quot; du menu &quot;AVANCÉ&quot; pour accéder à la configuration avancée.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<a name=02><strong>Configuration sans fil</strong></a><br>
			La page Configuration sans fil affiche les paramètres de la partie point d'accès du <?query("/sys/modelname");?>. 			Vous pouvez y personnaliser votre réseau sans fil ou configurer le <?query("/sys/modelname");?> pour un réseau 			sans fil existant et déjà paramétré.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Technologie Wi-Fi Protected Setup (ou WCN 2.0 sous Windows Vista)</strong><br>
			Cette fonction offre aux utilisateurs une méthode encore plus intuitive pour configurer la sécurité sans fil. 
			Elle se décline en deux formats : un code PIN et un bouton. Vous pouvez configurer automatiquement la sécurité 			sans fil entre le routeur et le client en saisissant le code PIN de l'appareil dans l'utilitaire de carte sans 
			fil ou, si la carte sans fil est dotée d'un pilote certifié Windows Vista, dans l'utilitaire de client sans fil
 			Windows Vista. Pour pouvoir bénéficier de cette fonction, la carte sans fil doit prendre en charge l'un des 
			deux formats Wi-Fi Protected Setup.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Nom du réseau sans fil</strong><br>
			Ou SSID (Service Set Identifier) ; il s'agit du nom de votre réseau local sans fil (WLAN). 
			Par défaut le SSID du <?query("/sys/modelname");?> est &quot;dlink&quot;. Il est très facile de 
			le modifier pour créer un nouveau réseau sans fil ou ajouter le <?query("/sys/modelname");?> à un réseau 
			sans fil existant.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Canal sans fil</strong><br>
			Spécifie le canal utilisé par le <?query("/sys/modelname");?>. Par défaut, il s'agit du canal 6. 
			Vous pouvez le modifier pour adopter le canal d'un réseau sans fil existant ou pour personnaliser 
			votre nouveau réseau sans fil. Cochez la case Activer le balayage automatique pour que le 
			<?query("/sys/modelname");?> sélectionne automatiquement son canal d'activité. Cette option est recommandée car le 				routeur choisit alors le canal qui présente le moins d'interférences.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>WMM (Wi-Fi Multimedia)</strong><br>
			Sélectionnez Activer pour activer la qualité de service pour l'interface sans fil du <?query("/sys/modelname");?>.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Activer le sans fil dissimulé </strong><br>
			Sélectionnez Activé(e) si vous ne souhaitez pas que le <?query("/sys/modelname");?> diffuse le SSID de votre
 			réseau sans fil. Dans ce cas, le SSID du <?query("/sys/modelname");?> ne sera pas visible par les utilitaires de 				détection. Vous devrez alors connaître ce SSID pour pouvoir le saisir manuellement lors de la configuration de vos 				clients sans fil, afin de les connecter au <?query("/sys/modelname");?>. Par défaut, cette option est activée.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Mode Sécurité sans fil</strong><br>
			Il est essentiel de sécuriser votre réseau sans fil pour protéger l'intégrité des informations qu'il transporte. 				Le <?query("/sys/modelname");?> prend en charge 4 types de sécurité sans fil : WEP, WPA uniquement, WPA2
 			uniquement et WPA/WPA2 (auto-détection)
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>WEP </strong><br>
			Le protocole WEP (Wireless Equivalent Protocol) est un protocole de sécurité sans fil pour les réseaux locaux sans 				fil (WLAN). Le protocole WEP garantit la sécurité grâce au chiffrement des données envoyées sur le WLAN. 
			Le <?query("/sys/modelname");?> prend en charge 2 niveaux de chiffrement WEP : 64 bits et 128 bits. 
			WEP est désactivé par défaut. Vous pouvez modifier le paramètre WEP pour vous adapter à un réseau sans fil 				existant ou pour personnaliser votre réseau sans fil.
		</p>
		<p>
			<strong><em>Authentification</em></strong> -
			L'authentification est le processus par lequel le <?query("/sys/modelname");?> vérifie l'identité d'un
 			périphérique réseau qui tente d'accéder au réseau sans fil. Avec le protocole WEP, il existe deux types 
			d'authentification.<br> 
			<strong><em>Système ouvert</em></strong> -
			Sélectionnez cette option pour permettre à tous les périphériques sans fil de communiquer avec le 
			<?query("/sys/modelname");?> avant de devoir fournir la clé de chiffrement requise pour accéder au réseau.<br>
			<strong><em>Clé partagée</em></strong> -
			Sélectionnez cette option pour que tous les périphériques sans fil fournissent obligatoirement la clé de
 			chiffrement requise pour l'accès au réseau avant d'être autorisés à communiquer avec 
			le <?query("/sys/modelname");?>.<br>
			<strong><em>Chiffrement WEP</em></strong> -
			Sélectionnez le niveau de chiffrement WEP à utiliser sur votre réseau. Deux niveaux de chiffrement WEP 
			sont pris en charge : 64 bits et 128 bits.<br>
			<strong><em>Type de clé</em></strong> -
			Les types de clés pris en charge par le <?query("/sys/modelname");?> sont HEX (hexadécimal) et ASCII 
			(American Standard Code for Information Interchange). Vous pouvez modifier le type de clé pour vous 
			adapter à un réseau sans fil existant ou pour personnaliser votre réseau sans fil.<br>
			<strong><em>Clés</em></strong> -
			Les clés 1 à 4 vous permettent de modifier aisément les paramètres de chiffrement sans fil, 
			afin de conserver un réseau sécurisé. Il vous suffit de sélectionner la clé spécifique à utiliser 
			pour chiffrer les données sans fil sur le réseau.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>WPA-Personal</strong><br>
			Le WPA (Wi-Fi Protected Access, accès protégé Wi-Fi) autorise et authentifie les utilisateurs sur 
			le réseau sans fil.Le mode WPA offre une sécurité supérieure au WEP et est fondé sur une clé modifiée 
			automatiquement, à intervalles réguliers.
		</p>
		<p>
			<strong><em>Type de chiffrement</em></strong> -
			Le <?query("/sys/modelname");?> prend en charge deux types de chiffrement différents avec le type de sécurité WPA.
 			Il s'agit de TKIP (Temporal Key Integrity Protocol) et d'AES (Advanced Encryption Standard).<br>
			<strong><em>PSK/EAP</em></strong> -
			Avec l'option PSK, vos clients sans fil doivent fournir une phrase de passe pour s'authentifier. 
			Si l'option EAP est sélectionnée, votre réseau doit comporter un serveur RADIUS qui assure l'authentification 
			de tous les clients sans fil.<br>
			<strong><em>Phrase de passe</em></strong> -
			Il s'agit des informations que les clients sans fil doivent fournir pour pouvoir communiquer avec 
			votre <?query("/sys/modelname");?> lorsque l'option PSK est sélectionnée. Saisissez entre 8 et 63 caractères
 			alphanumériques. Notez soigneusement cette phrase de passe car vous devrez la saisir à nouveau sur tous les
 			périphériques sans fil que vous ajouterez à votre réseau.<br>
			<strong><em>802.1X</em></strong> -
			Cela signifie que l'authentification WPA est associée à un serveur RADIUS qui doit se trouver sur votre réseau.
 			Saisissez l'adresse IP, le port et le secret partagé pour lesquels votre serveur RADIUS est configuré. 
			Vous pouvez également saisir les informations d'un second serveur RADIUS dans le cas où votre réseau en comporte
 			deux, pour authentifier les clients sans fil.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>WPA2</strong><br>
			Le WPA2 (Wi-Fi Protected Access, accès protégé Wi-Fi 2) autorise et authentifie les utilisateurs sur le réseau
 			sans fil. Le mode WPA2 offre une sécurité supérieure au WEP et est fondé sur une clé modifiée automatiquement, 
			à intervalles réguliers.
		</p>
		<p>
			<strong><em>Type de chiffrement</em></strong> -
			Le <?query("/sys/modelname");?> prend en charge deux types de chiffrement différents avec le type de sécurité WPA. 				Il s'agit de TKIP (Temporal Key Integrity Protocol) et d'AES (Advanced Encryption Standard).<br>
			<strong><em>PSK/EAP</em></strong> -
			Avec l'option PSK, vos clients sans fil doivent fournir une phrase de passe pour s'authentifier. 
			Si l'option EAP est sélectionnée, votre réseau doit comporter un serveur RADIUS qui assure l'authentification 
			de tous les clients sans fil.<br>
			<strong><em>Phrase de passe</em></strong> -
			Il s'agit des informations que les clients sans fil doivent fournir pour pouvoir communiquer avec 
			votre <?query("/sys/modelname");?> lorsque l'option PSK est sélectionnée. Saisissez entre 8 et 63 caractères
 			alphanumériques. Notez soigneusement cette phrase de passe car vous devrez la saisir à nouveau sur tous les
			périphériques sans fil que vous ajouterez à votre réseau.<br>
			<strong><em>802.1X</em></strong> -
			Cela signifie que l'authentification WPA2 est associée à un serveur RADIUS qui doit se trouver sur votre réseau.
 			Saisissez l'adresse IP, le port et le secret partagé pour lesquels votre serveur RADIUS est configuré. 
			Vous pouvez également saisir les informations d'un second serveur RADIUS dans le cas où votre réseau en comporte
 			deux, pour authentifier les clients sans fil.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
 	<td height=20>
		<p>
			<strong>WPA2-Auto</strong><br>
			Cette option permet de connecter simultanément des clients WPA2 et WPA au <?query("/sys/modelname");?>.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<a name=03><strong>Configuration du LAN</strong></a><br>
			Il s'agit des paramètres de l'interface LAN (réseau local) de l'appareil. 
			Ces paramètres sont également appelés &quot;paramètres privés&quot;. 
			Vous pouvez modifier l'adresse IP LAN si nécessaire. L'adresse IP LAN est privée au sein 
			de votre réseau interne et ne peut être vue sur Internet. L'adresse IP par défaut est 
			192.168.0.1 avec un masque de sous-réseau de 255.255.255.0.<br><br>
			<strong><em>Adresse IP</em></strong> -
			Adresse IP du <?query("/sys/modelname");?>, par défaut : 192.168.0.1.<br>
			<strong><em>Masque de sous-réseau</em></strong> -
			Masque de sous-réseau du <?query("/sys/modelname");?>, par défaut : 255.255.255.0.<br>
			<strong><em>Nom de domaine local</em></strong> (facultatif) - Saisissez le nom de domaine local pour le réseau.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong><em>Relais DNS</em></strong> -
			Lorsque l'option Relais DNS est activée, les clients DHCP du routeur se voient attribuer l'adresse IP du 
			réseau local du routeur en tant que serveur DNS. Toutes les demandes DNS reçues par le routeur sont 
			transmises aux serveurs DNS de votre fournisseur d'accès. Lorsque l'option Relais DNS est désactivée, 
			tous les clients DHCP du routeur se voient attribuer le serveur DNS du fournisseur d'accès.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Serveur DHCP</strong><br>
			DHCP est l'acronyme de Dynamic Host Control Protocol. Le serveur DHCP attribue des adresses IP aux 
			périphériques du réseau qui le demandent. Ces périphériques doivent être configurés pour obtenir 
			une adresse IP automatiquement. Par défaut, le serveur DHCP est activé sur le <?query("/sys/modelname");?>. 
			Le groupe d'adresses DHCP contient la plage des adresses IP qui seront automatiquement attribuées aux clients sur le réseau.
		</p>
		<p>
			<strong>Réservation DHCP</strong><br>
			Saisissez manuellement le &quot;Nom d'ordinateur&quot;, l'&quot;Adresse IP&quot; et l'&quot;Adresse MAC&quot; 
			de l'ordinateur auquel vous souhaitez que le routeur affecte statiquement la même adresse IP ou choisissez
 			l'ordinateur dans le menu déroulant des clients DHCP actuels.
		</p>
		<p>
			<strong><em>Adresse IP de début</em></strong> La première adresse IP de l'attribution d'adresses IP du serveur DHCP.<br>
			<strong><em>Adresse IP de fin</em></strong> La dernière adresse IP de l'attribution d'adresses IP du serveur DHCP.<br>
			<strong><em>Durée d'attribution</em></strong> La durée, en minutes, pendant laquelle l'adresse IP est attribuée.
		</p>
		<p>
			Les informations des ordinateurs client DHCP dynamique connectés à l'appareil sont affichées dans la table des
 			clients DHCP dynamique. Celle-ci indique pour chaque ordinateur client le nom d'hôte, l'adresse IP, 
			l'adresse MAC et la durée écoulée de l'attribution DHCP.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=33>
		<p>
			<strong><a name=04>Horodatage</a></strong>
		</p>
		<p>
			Le routeur utilise les paramètres de configuration de l'heure pour synchroniser les services planifiés et 
			les activités de journalisation du système. Vous devrez choisir le fuseau horaire qui correspond à votre 
			lieu géographique. Vous pouvez définir l'heure manuellement ou l'appareil peut se connecter à un serveur 
			NTP (Network Time Protocol) pour récupérer l'heure. Vous pouvez également définir des dates pour l'application 
			de l'heure d'été. L'heure système s'ajustera automatiquement en fonction de ces dates.
		</p>
		<p>
			<strong><em>Fuseau horaire</em></strong> - Sélectionnez le fuseau horaire correspondant à votre région.<br>
			<strong><em>Heure d'été</em></strong> -
			Si votre région pratique le passage à l'heure d'été, activez cette option et spécifiez le mois, la semaine, 
			le jour et l'heure de début et de fin de son application.<br>
			<strong><em>Configuration automatique de la date et de l'heure</em></strong> -
			Sélectionnez le serveur horaire D-Link avec lequel vous souhaitez que le <?query("/sys/modelname");?> 
			synchronise son heure. Par défaut, le <?query("/sys/modelname");?> communique avec le serveur NTP de 
			D-Link tous les 7 jours.<br>
			<strong><em>Configurer manuellement la date et l'heure</em></strong> -
			Sélectionnez cette option pour indiquer l'heure manuellement. Vous devez indiquer l'année, le mois, le jour,
 			l'heure, les minutes et les secondes ; vous pouvez aussi cliquer sur Copier les paramètres d'heure de votre
 			ordinateur pour copier l'heure système de l'ordinateur utilisé pour accéder à l'interface de gestion.
		</p>
	</td>
</tr>
<tr><td height=2>&nbsp;</td></tr>
<tr><td height=2>&nbsp;</td></tr>
<tr>
	<td height=44>
		<p>
			<strong><a name=05>Contrôle parental</a></strong>
		</p>
		<p>
			Outre la possibilité de filtrer les périphériques qui accèdent au réseau et à Internet, 
			le <?query("/sys/modelname");?> peut être configuré pour autoriser ou refuser l'accès des 
			ordinateurs de votre réseau à des sites Web inappropriés, en fonction du nom de domaine ou de mots-clés.
		</p>
		<p>
			<strong>Contrôle parental</strong><br>
			La fonction de contrôle parental permet d'autoriser ou de refuser l'accès des ordinateurs de votre réseau à des
 			sites Web spécifiques, par mots-clés ou par nom de domaine. Sélectionnez &quot;Activer le filtrage de site WEB 
			et AUTORISER les ordinateurs à accéder UNIQUEMENT à ces sites&quot; pour autoriser les ordinateurs de votre 
			réseau à n'accéder qu'aux URL et noms de domaine spécifiés. Sélectionnez &quot;Activer le filtrage de site WEB 
			et REFUSER l'accès des ordinateurs à ces sites UNIQUEMENT&quot; pour refuser l'accès des ordinateurs de votre
 			réseau aux URL et noms de domaine spécifiés.
		</p>
		<p>
			<span class="style1">Exemple 1:</span><br>
			Pour interdire l'accès des utilisateurs du réseau local à tous les sites Web dont l'URL 
			comprend le mot &quot;shopping&quot;, sélectionnez &quot;Activer le filtrage de site Web et 
			REFUSER l'accès des ordinateurs à ces sites UNIQUEMENT&quot;, puis indiquez &quot;shopping&quot; 
			dans la liste des règles de filtrage de site Web. Les utilisateurs du réseau local se verront 
			refuser l'accès aux sites dont l'URL contient le mot-clé spécifié.<br>
			<a href="http://www.yahoo.com/shopping/stores.html">http://www.yahoo.com/shopping/stores.html</a><br>
			<a href="http://www.msn.com/search/shopping-spree.html">http://www.msn.com/search/shopping-spree.html</a>
		</p>
		<p>
			<span class="style1">Exemple 2:</span><br>
			Si vous souhaitez que vos enfants visitent uniquement certains sites particuliers, 
			sélectionnez &quot;Activer le filtrage de site Web et AUTORISER les ordinateurs à accéder 
			UNIQUEMENT à ces sites&quot;, puis spécifiez les domaines auxquels vos enfants seront autorisés à accéder.
		</p>
		<ul>
			<li>Google.com </li>
			<li>Cartoons.com </li>
			<li>Discovery.com </li>
		</ul>
	</td>
</tr>
</table>
