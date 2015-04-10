<div class="box">
<a name="internet_setup"><h2>Configuration Internet</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=40>
		<p>
			Si vous configurez le périphérique pour la première fois, nous vous conseillons de cliquer sur le bouton Assistant de configuration de connexion Internet et de suivre les instructions qui s'affichent à l'écran. Si vous voulez modifier ou configurer manuellement les paramètres du périphérique, cliquez sur Configuration manuelle de connexion Internet.
		</p>
	</td>
</tr>
<tr>
	<td height=59>
		<p>
			<strong>Lancer l'assistant de configuration de connexion Internet </strong><br>
			Cliquez sur ce bouton pour que le routeur réalise quelques étapes simples de connexion à Internet.
			<br>
			<strong>Lancer l'assistant de configuration de sécurité sans fil </strong><br>
			Cliquez sur ce bouton pour que le routeur configure les paramètres de votre réseau sans fil, y compris la sécurité.
		</p>
	</td>
</tr>
<tr><td height=32>&nbsp;</td></tr>
<tr>
	<td height=46>
		<p>
			<strong>Configuration manuelle de connexion Internet</strong><br>
			Choisissez cette option pour entrer les paramètres nécessaires pour connecter votre routeur à Internet manuellement.
			<br>
			<strong>Mode Point d'accès</strong><br>
			Activez « Access Point Mode » (Mode Point d'accès) pour que le périphérique fonctionne comme un PA sans fil. Toutes les fonctions de la NAT sont désactivées, sauf les paramètres liés à la connexion sans fil.
			<br>
			<strong>Type de connexion Internet </strong><br>
			Les paramètres de connexion Internet servent à connecter le <?query("/sys/modelname");?> à Internet. Toutes les informations à saisir sur cette page vous sont fournies par votre FAI et sont souvent désignées par « Paramètres publics ». Sélectionnez l'option correspondant à votre FAI. Si vous avez des doutes concernant l'option à sélectionner, contactez votre FAI.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=61>
		<p>
			<strong>Adresse IP statique</strong><br>
			Sélectionnez cette option si votre FAI (fournisseur d'accès Internet) vous a fourni une adresse IP, un masque de sous-réseau, une passerelle par défaut et une adresse de serveur DNS. Saisissez ces informations dans les champs correspondants. Si vous avez des doutes concernant les données à saisir dans ces champs, contactez votre FAI.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=142>
		<p>
			<strong>Adresse IP dynamique</strong><br>
			Sélectionnez cette option si votre FAI (fournisseur d'accès Internet) vous a fourni une adresse IP automatiquement. En général, les fournisseurs de modems câblés utilisent des adresses IP dynamiques.
		</p>
		<p>
			<strong><em>Nom d'hôte </em></strong> (facultatif) -
			Le champ Host Name (Nom d'hôte) est facultatif, mais certains fournisseurs d'accès Internet exigent qu'il soit renseigné. Le nom d'hôte par défaut correspond au numéro de modèle du routeur.
			<br>
			<strong><em>Adresse MAC </em></strong> (facultatif) -
			Certains fournisseurs d'accès Internet (FAI) exigent que vous renseigniez le champ MAC Address (Adresse MAC - Media Access Control). L'adresse MAC par défaut correspond à celle de l'interface du réseau étendu du <?query("/sys/modelname");?>. Vous pouvez utiliser le bouton « Clone MAC Address » (Cloner l'adresse MAC) pour copier automatiquement l'adresse MAC de la carte Ethernet installée sur l'ordinateur servant à configurer le périphérique. Vous ne devez remplir ce champ que si votre FAI le demande.
			<br>
			<strong><em>Adresse DNS principale </em></strong> -
			Saisissez l'adresse IP principale du serveur DNS (Domain Name Service) fournie par votre FAI.<br>
			<strong><em>Adresse DNS secondaire </em></strong> (facultative) -
			Si votre FAI vous a fourni une adresse IP secondaire de serveur DNS, saisissez-la dans ce champ.<br>
			<strong><em>MTU (Unité de transmission/transfert maximale) </em></strong> -
			La plus grande taille de paquet pouvant être envoyée sur un réseau. Les messages plus volumineux que la MTU sont divisés en plus petits paquets. 1 500 correspond à la valeur par défaut de cette option. Si vous la modifiez, cela risque de nuire aux performances de votre routeur. Ne la modifiez que si l'un de nos représentants de support technique ou votre FAI vous l'indique.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=47>
		<p>
			<strong>PPPoE</strong><br>
			Sélectionnez cette option si votre FAI vous demande d'utiliser une connexion PPPoE (Protocole Point à Point sur Ethernet). Les fournisseurs DSL utilisent généralement cette option. Sélectionnez Dynamic PPPoE (PPPoE dynamique) pour obtenir une adresse IP automatiquement en vue d'établir votre connexion PPPoE (la plupart des connexions PPPoE l'utilisent). Sélectionnez Static PPPoE (PPPoE statique) pour utiliser une adresse IP statique en vue d'établir votre connexion PPPoE.
		</p>
		<p>
			<strong><em>Nom d'utilisateur </em></strong> - Saisissez votre nom d'utilisateur PPPoE.<br>
			<strong><em>Mot de passe </em></strong> - Saisissez votre mot de passe PPPoE.<br>
			<strong><em>Nom de service </em></strong> (facultatif) -
			Si votre FAI utilise un nom de service pour la connexion PPPoE, saisissez-le ici.<br>
			<strong><em>Adresse IP </em></strong> -
			Cette option n'est que disponible pour Static PPPoE (PPPoE statique). Saisissez l'adresse IP statique de votre connexion PPPoE.<br>
			<strong><em>Adresse MAC </em></strong> (facultatif) -
			Certains fournisseurs d'accès Internet (FAI) exigent que vous renseigniez le champ MAC Address (Adresse MAC - Media Access Control). L'adresse MAC par défaut correspond à celle de l'interface du réseau étendu du <?query("/sys/modelname");?>. Vous pouvez utiliser le bouton « Clone MAC Address » (Cloner l'adresse MAC) pour copier automatiquement l'adresse MAC de la carte Ethernet installée sur l'ordinateur servant à configurer le périphérique. Vous ne devez remplir ce champ que si votre FAI le demande.<br>
			<strong><em>Adresse DNS principale </em></strong> -
			Adresse IP principale du serveur DNS (Domain Name System) pouvant être fournie par votre FAI. Vous ne devez l'indiquer que si vous avez sélectionné Static PPPoE (PPPoE statique). Si vous avez choisi Dynamic PPPoE (PPPoE dynamique), vous devez laisser la valeur par défaut dans ce champ car votre FAI vous fournira ces informations automatiquement.<br>
			<strong><em>Adresse DNS secondaire </em></strong> (facultative) -
			Si votre FAI vous a fourni une adresse IP secondaire de serveur DNS, saisissez-la dans ce champ.<br>
			<strong><em>Temps d'inactivité maximum </em></strong> -
			Durée d'inactivité (en minutes) avant que le périphérique ne déconnecte votre session PPPoE. Saisissez un Maximum Idle Time (Temps d'inactivité maximum), en minutes, pour définir un délai maximum pendant lequel la connexion Internet est maintenue pendant l'inactivité. Si la connexion reste inactive pendant plus longtemps que le Maximum Idle Time (Temps d'inactivité maximum) défini, la connexion est interrompue. Cette option ne s'applique qu'au mode Connect-on-demand Connection (Connexion à la demande).<br>
			<strong><em>MTU (Unité de transmission/transfert maximale)  </em></strong> -
			La plus grande taille de paquet pouvant être envoyée sur un réseau. Les messages plus volumineux que la MTU sont divisés en plus petits paquets. 1492 correspond à la valeur par défaut de cette option. Si vous la modifiez, cela risque de nuire aux performances de votre routeur. Ne la modifiez que si l'un de nos représentants de support technique ou votre FAI vous l'indique.<br>
			<strong><em>Sélection du mode de connexion</em></strong> -
			Sélectionnez Always-on (Toujours activé) pour que le routeur ne déconnecte jamais la session PPPoE. Sélectionnez Manual (Manuel) pour préciser le moment où le routeur se connecte et se déconnecte d'Internet. L'option Connect-on-demand (Connexion à la demande) permet au routeur d'établir une connexion à Internet quand le périphérique sur le réseau tente d'accéder à une ressource Internet uniquement.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>PPTP</strong><br>
			Sélectionnez cette option si votre FAI utilise une connexion PPTP (protocole de tunnel point à point) et vous a attribué un nom d'utilisateur et un mot de passe pour accéder à Internet. Sélectionnez Dynamic PPTP (PPTP dynamique) pour obtenir une adresse IP automatiquement en vue d'établir une connexion PPTP. Sélectionnez Static PPTP (PPTP statique) pour utiliser une adresse IP statique en vue d'établir votre connexion PPTP.
		</p>
		<p>
			<strong><em>Adresse IP </em></strong> - Saisissez l'adresse IP que votre FAI vous a attribuée.<br>
			<strong><em>Masque de sous-réseau </em></strong> - Saisissez le masque de sous-réseau que votre FAI vous a attribué.<br>
			<strong><em>Passerelle</em></strong> - Saisissez l'adresse IP de passerelle que votre FAI vous a attribuée.<br>
			<strong><em>DNS - </em></strong>Saisissez l'adresse de DNS que votre FAI vous a attribuée.<br>
			<strong><em>IP du serveur </em></strong> -
			Saisissez l'adresse IP du serveur auquel vous allez vous connecter (elle est fournie par votre FAI).<br>
			<strong><em>Compte </em></strong> - Saisissez votre nom d'utilisateur PPTP.<br>
			<strong><em>Mot de passe </em></strong> - Saisissez votre mot de passe PPTP.<br>
			<strong><em>Temps d'inactivité maximum </em></strong> -
			Durée d'inactivité avant que le périphérique ne déconnecte votre session PPTP. Saisissez un Maximum Idle Time (Temps d'inactivité maximum), en minutes, pour définir un délai maximum pendant lequel la connexion Internet est maintenue pendant l'inactivité. Si la connexion reste inactive pendant plus longtemps que le Maximum Idle Time (Temps d'inactivité maximum) défini, la connexion est interrompue. Cette option ne s'applique qu'au mode Connect-on-demand Connection (Connexion à la demande).
			<br>
			<strong><em>MTU (Unité de transmission/transfert maximale) </em></strong> -
			 La plus grande taille de paquet pouvant être envoyée sur un réseau. Les messages plus volumineux que la MTU sont divisés en plus petits paquets. 1400 correspond à la valeur par défaut de cette option. Si vous la modifiez, cela risque de nuire aux performances de votre routeur. Ne la modifiez que si l'un de nos représentants de support technique ou votre FAI vous l'indique.<br>
			<strong><em>Sélection du mode de connexion</em></strong> -
			Sélectionnez Always-on (Toujours activé) pour que le routeur ne déconnecte jamais la session PPTP. Sélectionnez Manual (Manuel) pour préciser le moment où le routeur se connecte et se déconnecte d'Internet. L'option Connect-on-demand (Connexion à la demande) permet au routeur d'établir une connexion à Internet quand le périphérique sur le réseau tente d'accéder à une ressource Internet uniquement.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>L2TP </strong><br>
			Sélectionnez cette option si votre FAI utilise une connexion L2TP (Layer 2 Tunneling Protocol) et vous a attribué un nom d'utilisateur et un mot de passe pour accéder à Internet. Sélectionnez Dynamic L2TP (L2TP dynamique) pour obtenir une adresse IP automatiquement en vue d'établir une connexion L2TP. Sélectionnez Static L2TP (L2TP statique) pour utiliser une adresse IP statique en vue d'établir votre connexion L2TP.
		</p>
		<p>
			<strong><em>Adresse IP </em></strong> - Saisissez l'adresse IP que votre FAI vous a attribuée.<br>
			<strong><em>Masque de sous-réseau </em></strong> - Saisissez le masque de sous-réseau que votre FAI vous a attribué.<br>
			<strong><em>Passerelle</em></strong> - Saisissez l'adresse IP de passerelle que votre FAI vous a attribuée.<br>
			<strong><em>DNS</em></strong> - Saisissez l'adresse de DNS que votre FAI vous a attribuée.<br>
			<strong><em>IP du serveur </em></strong> -
			Saisissez l'adresse IP du serveur auquel vous allez vous connecter (elle est fournie par votre FAI).<br>
			<strong><em>Compte L2TP </em></strong> -  Saisissez votre nom d'utilisateur L2TP.<br>
			<strong><em>Mot de passe L2TP </em></strong> - Saisissez votre mot de passe L2TP.<br>
			<strong><em>Temps d'inactivité maximum </em></strong> -
			Durée d'inactivité (en minutes) avant que le périphérique ne déconnecte votre session L2TP. Saisissez un Maximum Idle Time (Temps d'inactivité maximum), en minutes, pour définir un délai maximum pendant lequel la connexion Internet est maintenue pendant l'inactivité. Si la connexion reste inactive pendant plus longtemps que le Maximum Idle Time (Temps d'inactivité maximum) défini, la connexion est interrompue. Cette option ne s'applique qu'au mode Connect-on-demand Connection (Connexion à la demande).<br>
			<strong><em>MTU (Unité de transmission/transfert maximale)</em></strong> -
			La plus grande taille de paquet pouvant être envoyée sur un réseau. Les messages plus volumineux que la MTU sont divisés en plus petits paquets. 1400 correspond à la valeur par défaut de cette option. Si vous la modifiez, cela risque de nuire aux performances de votre routeur. Ne la modifiez que si l'un de nos représentants de support technique ou votre FAI vous l'indique.
			<strong><em>Sélection du mode de connexion</em></strong> -
			Sélectionnez Always-on (Toujours activé) pour que le routeur ne déconnecte jamais la session L2TP. Sélectionnez Manual (Manuel) pour préciser le moment où le routeur se connecte et se déconnecte d'Internet. L'option Connect-on-demand (Connexion à la demande) permet au routeur d'établir une connexion à Internet quand le périphérique sur le réseau tente d'accéder à une ressource Internet uniquement.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>PPTP Russie (double accès)</strong><br>
			Pour configurer une connexion Internet Russian PPTP (PPTP Russie), procédez comme expliqué précédemment pour les connexions PPTP. Si votre FAI doit configurer l'accès statique, reportez-vous à la fonction « Routing » (Routage) du menu « ADVANED » (AVANCÉ) concernant la configuration avancée.

		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>PPPoE Russie (double accès)</strong><br>
			Certaines connexions PPPoE utilisent une route IP statique vers le FAI en sus des paramètres IP globaux pour la connexion. Ceci requiert une étape supplémentaire pour définir les paramètres IP du port physique de réseau étendu. Pour configurer une connexion Internet Russian PPPoE (PPPoE Russie), procédez comme expliqué précédemment pour les connexions PPPoE (comme expliqué précédemment), puis ajoutez des paramètres IP du réseau étendu physique, comme indiqué par votre fournisseur d’accès Internet. Si votre FAI doit configurer l'accès statique, reportez-vous à la fonction « Routing » (Routage) du menu « ADVANED » (AVANCÉ) concernant la configuration avancée.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="wireless_setup"><h2>Configuration du réseau sans fil</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			La page Wireless Setup (Configuration Internet) comporte les paramètres de la partie (Point d'accès) du <?query("/sys/modelname");?>. Elle vous permet de personnaliser votre réseau sans fil ou de configurer le <?query("/sys/modelname");?> pour qu'il s'adapte à un réseau sans fil existant ayant peut-être déjà été configuré.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>WPS (également appelé WCN 2.0 sous Windows Vista)</strong><br>
			Cette fonction vous permet de configurer la sécurité du réseau sans fil plus intuitivement. Elle existe en deux formats : code PIN et bouton Push (Envoyer). Saisissez le code PIN accompagnant le périphérique dans l'utilitaire de la carte ou du client sans fil Windows Vista, si la carte sans fil possède un pilote certifié Windows Vista, pour configurer automatiquement la sécurité du réseau sans fil entre le routeur et le client. La carte sans fil doit prendre en charge l'un des formats de ce protocole WPS afin que vous puissiez profiter de cette fonction.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Nom du réseau sans fil</strong><br>
			Également appelé SSID (Service Set Identifier), il s'agit du nom de votre réseau local sans fil. Par défaut, le SSID du <?query("/sys/modelname");?> est « dlink ». Vous pouvez le modifier simplement pour créer un nouveau réseau sans fil ou ajouter le <?query("/sys/modelname");?> à un réseau sans fil existant.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Canal sans fil</strong><br>
			Indique le canal sur lequel le <?query("/sys/modelname");?> fonctionne. Par défaut, il s'agit du canal 6. Vous pouvez le modifier afin qu'il corresponde au paramètre du canal d'un réseau sans fil existant ou pour personnaliser votre nouveau réseau sans fil. Cochez la case Enable Auto Scan (Activer le balayage automatique) pour que le <?query("/sys/modelname");?> sélectionne automatiquement le canal sur lequel il fonctionnera. Il est recommandé d'utiliser cette option car le routeur choisit le canal présentant le moins d'interférences.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>	
 		<p>
 			<strong>Débits de transfert (TX)</strong><br>
 			Sélectionnez les débits de transfert de base en fonction de la vitesse des adaptateurs sans fil du réseau local sans fil.
 		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>WMM</strong><br>
			Sélectionnez Enable (Activer) pour activer la QoS de l'interface sans fil du <?query("/sys/modelname");?>.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Activer le mode sans fil masqué </strong><br>
			Sélectionnez Enabled (Activé) si vous ne voulez pas que le <?query("/sys/modelname");?> diffuse le SSID de votre réseau sans fil. Si cette option est activée, les utilitaires Site Survey (Visite des lieux) ne voient pas le SSID du <?query("/sys/modelname");?>. Dans ce cas, vos clients du réseau sans fil doivent connaître le SSID de votre DIR-615 vous devez le saisir manuellement pour vous connecter au routeur. Cette option est activée par défaut.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Mode de sécurité sans fil</strong><br>
			Il est important de sécuriser votre réseau sans fil afin de protéger l'intégrité des informations qui y sont transmises. Le <?query("/sys/modelname");?> accepte 4 types de sécurité sans fil : WEP, WPA seulement, WPA2 seulement et WPA/WPA2 (détection automatique).
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>WEP </strong><br>
			Le WEP (Wired Equivalent Protocol) est un protocole de sécurité sans fil pour les réseaux locaux sans fil (WLAN). Le WEP vise à fournir une sécurité en chiffrant les données qui sont envoyées sur le WLAN. Le <?query("/sys/modelname");?> prend en charge 2 niveaux de chiffrement WEP : 64 bits et 128 bits. Le WEP est désactivé par défaut. Le paramètre WEP peut être modifié pour s'adapter à un réseau sans fil existant ou pour personnaliser votre réseau sans fil.
		</p>
		<p>
			<strong><em>Authentification</em></strong> -
			Processus par lequel le <?query("/sys/modelname");?> vérifie l'identité d'un périphérique réseau qui tente de joindre le réseau sans fil. Il existe deux types d'authentification pour ce périphérique lorsque vous utilisez le WEP.<br> 
			<strong><em>Système ouvert</em></strong> -
			Sélectionnez cette option pour autoriser tous les périphériques réseaux à communiquer avec le <?query("/sys/modelname");?> avant que la clé de chiffrement nécessaire pour pouvoir accéder au réseau ne leur soit demandée.<br>
			<strong><em>Clé partagée</em></strong> -
			Sélectionnez cette option pour demander à tous les périphériques réseaux tentant de communiquer avec le <?query("/sys/modelname");?> de fournir la clé de chiffrement nécessaire pour accéder au réseau avant qu'ils ne soient autorisés à communiquer avec le <?query("/sys/modelname");?>.<br>
			<strong><em>Chiffrement WEP</em></strong> -
			Sélectionnez le niveau de chiffrement WEP que vous souhaiteriez utiliser sur votre réseau. Les deux niveaux de chiffrement WEP pris en charge sont 64 bits et 128 bits.<br>
			<strong><em>Type de clé</em></strong> -
			Les types de clé qui sont pris en charge par le <?query("/sys/modelname");?> sont les formats HEX (Hexadécimal) et ASCII (American Standard Code for Information Interchange). Le type de clé peut être modifié pour s'adapter à un réseau sans fil existant ou pour personnaliser votre réseau sans fil.<br>
			<strong><em>Clés</em></strong> -
			Les clés 1 à 4 vous permettent de modifier facilement les paramètres de chiffrement sans fil pour maintenir un réseau sécurisé. Sélectionnez simplement la clé spécifique à utiliser pour chiffrer les données sans fil sur le réseau.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>WPA/WPA2</strong><br>
			Le WPA (ou WPA 2) permet d'autoriser et d'authentifier les utilisateurs sur le réseau sans fil. Le WPA est plus sécurisé que le WEP et repose sur une clé qui change automatiquement à intervalles réguliers.
		</p>
		<p>
			<strong><em>Type de chiffrement</em></strong> -
			Le <?query("/sys/modelname");?> prend en charge deux types de chiffrement différents lorsque le WPA est utilisé comme le type de sécurité. Ces deux options sont le TKIP (Temporal Key Integrity Protocol) et l'AES (Advanced Encryption Standard).<br>
			<strong><em>PSK/EAP</em></strong> -
			Lorsque le mode PSK est sélectionné, vos clients sans fil devront fournir une phrase de passe pour l'authentification. Lorsque le mode EAP est sélectionné, vous devrez disposer d'un serveur RADIUS sur votre réseau qui gérera l'authentification de tous vos clients sans fil.<br>
			<strong><em>Mot de passe</em></strong> -
			Il s'agit de ce dont vos clients sans fil auront besoin pour communiquer avec votre <?query("/sys/modelname");?>. Lorsque le mode PSK est sélectionné, saisissez entre 8 et 63 caractères alphanumériques. Veillez à noter cette phrase de passe étant donné que vous aurez besoin de l'entrer sur tout autre périphérique réseau que vous tentez d'ajouter à votre réseau.<br>
			<strong><em>802.1X</em></strong> -
			Cela signifie que l'authentification WPA est utilisée conjointement avec un serveur RADIUS qui doit être présent sur votre réseau. Entrez l'adresse IP, le port, et le secret partagé pour lesquels votre serveur RADIUS est configuré. Vous disposez également de l'option d'entrer des informations pour un deuxième serveur RADIUS dans le cas où il y en a deux sur votre réseau que vous utilisez pour authentifier les clients sans fil.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="lan_setup"><h2>Configuration du réseau</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			Ces paramètres permettent de configurer l'interface de réseau local du périphérique. Ces paramètres peuvent être qualifiés de « paramètres privés ». Vous pouvez modifier l'adresse IP du réseau local, si nécessaire. L'adresse IP du réseau local est propre à votre réseau interne et n'est pas visible sur Internet. L'adresse IP par défaut est 192.168.0.1, le masque de sous-réseau étant 255.255.255.0.
			<br><br>
			<strong><em>Adresse IP</em></strong> -
			L'adresse IP par défaut du <?query("/sys/modelname");?> est 192.168.0.1.<br>
			<strong><em>Masque de sous-réseau</em></strong> -
			Le masque de sous-réseau par défaut du <?query("/sys/modelname");?> est 255.255.255.0.<br>
			<strong><em>Nom de domaine local</em></strong> (facultatif) - Saisissez le nom de domaine local de votre réseau.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong><em>Relais du DNS</em></strong> -
			 Lorsque cette option est activée, l'adresse IP du réseau local du routeur est attribuée aux clients DHCP du routeur sous forme de serveur DNS. Toutes les demandes du DNS reçues par le routeur sont transmises aux serveurs DNS de votre FAI. Lorsque l'option DNS relay (Relais DNS) est activée, le serveur DNS du FAI est attribué à tous les clients DHCP du routeur.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Serveur DHCP</strong><br>
			DHCP (Dynamic Host Control Protocol) est un protocole de contrôle dynamique de l'hôte. Le serveur DHCP attribue des adresses IP aux périphériques du réseau qui en font la demande. Ces périphériques doivent être configurés sur « Obtenir une adresse IP automatiquement ». Par défaut, le serveur DHCP est activé sur le <?query("/sys/modelname");?>. Le groupe d'adresses DHCP contient la plage d'adresses IP qui seront automatiquement attribuées aux clients du réseau.
		</p>
		<p>
			<strong>Réservation DHCP</strong><br>
			Entrez manuellement le nom de l'ordinateur, l'adresse IP et l'adresse MAC du PC pour lequel vous souhaitez que le routeur attribue de façon statique la même adresse IP, ou bien choisissez le PC dans le menu déroulant qui montre les clients DHCP courants.
		</p>
		<p>
			<strong><em>Adresse IP de départ</em></strong> Adresse IP de départ pour l'attribution d'adresses IP au serveur DHCP.<br>
			<strong><em>Adresse IP finale</em></strong> Adresse IP finale pour l'attribution d'adresses IP au serveur DHCP.<br>
			<strong><em>Durée de concession</em></strong> Durée en minutes pendant laquelle est effective la concession IP.
		</p>
		<p>
			Les informations des clients DHCP dynamiques connectés au périphérique seront affichées dans le tableau des clients DHCP dynamiques. Le tableau affichera le nom de l'hôte, l'adresse IP, l'adresse MAC et l'heure d'expiration de la concession DHCP pour chaque client.
		</p>
	</td>
</tr>
</table>
</div>

<div class="box">
<a name="lcd_setup"><h2>Configuration LCD</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			La page LCD Setup (Configuration LCD) permet de gérer les paramètres du panneau d'affichage de votre périphérique <?query("/sys/modelname");?>, ainsi que l'économiseur d'écran, et de régler la durée pendant laquelle le périphérique doit être inactif avant que l'écran LCD ne s'éteigne.
			<br><br>
			<strong><em>Réglage de l'économiseur d'écran</em></strong> -
			L'économiseur d'écran affiche l'image « screen_bg.jpg » enregistrée dans le répertoire racine du disque dur interne en arrière plan, la date et l'heure actuelles se déplaçant de manière aléatoire au-dessus de l'image. Si l'image est introuvable, l'arrière plan reste noir. Le paramètre « Timeout » (Expiration du délai) indique le nombre de minutes requises avant que le périphérique n'entre en mode d'économie d'écran s'il reste inactif. Le périphérique quitte le mode d'économiseur d'écran lorsque vous appuyez sur le Touch Pad.<br>
			<strong><em>Paramètre d'affichage</em></strong> -
			 Ce paramètre éteint l'écran LCD pour économiser de l'énergie si le périphérique reste inactif pendant le nombre de minutes configuré dans le champ « Timeout » (Expiration du délai). L'écran LCD se rallume si vous appuyez sur le Touch Pad.<br>
		</p>
	</td>
</tr>
</table>
</div>
