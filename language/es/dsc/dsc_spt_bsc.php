<div class="box">
<a name="internet_setup"><h2>Configuración de Internet</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=40>
		<p>
			Si está configurando por primera vez el dispositivo, recomendamos hacer clic en el Asistente de configuración de conexión de Internet y seguir las instrucciones que aparecen en la pantalla. Si deseara modificar o configurar manualmente los parámetros del dispositivo, haga clic en Configuración manual de la conexión de Internet.
		</p>
	</td>
</tr>
<tr>
	<td height=59>
		<p>
			<strong>Ejecutar el asistente para la configuración de la conexión a Internet  </strong><br>
			Haga clic en este botón para llevar a cabo algunos pasos simples para ayudarle a conectar su router a Internet.
			<br>
			<strong>Ejecutar el asistente para la configuración de seguridad inalámbrica  </strong><br>
			Haga clic en el botón para llevar a cabo la configuración de los parámetros de su red inalámbrica, incluyendo la seguridad.
		</p>
	</td>
</tr>
<tr><td height=32>&nbsp;</td></tr>
<tr>
	<td height=46>
		<p>
			<strong>Configuración manual de la conexión de Internet</strong><br>
			Seleccione esta opción si desea introducir los parámetros necesarios para conectar manualmente su router a Internet.
			<br>
			<strong>Modo de punto de acceso</strong><br>
			Si activa el "Modo de punto de acceso" hará que la función del dispositivo sea como la de un AP inalámbrico. Todas las funciones NAT se desactivarán excepto los parámetros asociados con la conexión inalámbrica.
			<br>
			<strong>Tipo de conexión a Internet  </strong><br>
			Los Parámetros de conexión a Internet se utilizan para conectar el <?query("/sys/modelname");?> a Internet. Su ISP le proporcionará cualquier información que sea necesario introducir en esta página, y en muchas ocasiones se hará referencia a ella como "parámetros públicos". Seleccione la opción apropiada para su ISP específico. Si no estuviera seguro de la opción a seleccionar, póngase en contacto con su ISP.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=61>
		<p>
			<strong>Dirección IP estática</strong><br>
			Seleccione esta opción si su ISP (Proveedor de servicios de Internet) le hubiera proporcionado una dirección IP, Máscara de subred, Puerta de enlace predeterminada, y una dirección de servidor DNS. Introduzca esta información en los campos correspondientes. Si no estuviera seguro de qué introducir en estos campos, póngase en contacto con su ISP.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=142>
		<p>
			<strong>Dirección IP dinámica</strong><br>
			Seleccione esta opción si su ISP (Proveedor de servicios de Internet) le proporcionara una dirección IP automáticamente. Los proveedores de módems por cable utilizan asignación dinámica de direcciones IP.
		</p>
		<p>
			<strong><em>Nombre de host </em></strong> (opcional) -
			El campo Nombre de host es opcional aunque algunos Proveedores de servicios de Internet podrían requerirlo. El nombre de host predeterminado es el número de modelo del router.<br>
			<strong><em>Dirección MAC </em></strong> (opcional) -
			Algunos Proveedores de servicios de Internet (ISP) requieren el campo Dirección MAC (Control de acceso al medio). La dirección MAC predeterminada se establece con la dirección MAC de la interfaz WAN en el <?query("/sys/modelname");?>. Puede utilizar el botón "Clonar dirección MAC" para copiar automáticamente la dirección MAC de la Tarjeta Ethernet instalada en el ordenador utilizada para configurar el dispositivo. Sólo es necesario rellenar el campo si su ISP lo requiriera.
			<br>
			<strong><em>Dirección de DNS primario </em></strong> -
			Introduzca la dirección IP del servidor DNS primario (Servicios de nombres de dominio) suministrada por su ISP.<br>
			<strong><em>Dirección de DNS secundario </em></strong> (opcional) -
			Si su ISP le proporcionara una dirección IP del servidor DNS secundario, introdúzcala en este campo.<br>
			<strong><em>MTU </em></strong> -
			MTU (Unidad de transmisión/transferencia máxima) es el máximo tamaño de paquete que se puede enviar sobre una red. Los mensajes mayores que la MTU se dividen en paquetes menores. 1500 es el valor predeterminado para esta opción. La modificación de este número podría afectar negativamente al rendimiento de su router. Cambie únicamente este número si se lo indica uno de nuestros Representantes de soporte técnico o si lo hiciera su ISP.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=47>
		<p>
			<strong>PPPoE</strong><br>
			Seleccione esta opción si su ISP requiriera utilizar una conexión PPPoE (Protocolo de punto a punto a través de Ethernet). Normalmente, los proveedores de DSL utilizan esta opción. Seleccione PPPoE dinámico para obtener automáticamente una dirección IP para su conexión PPPoE (utilizada por la mayoría de conexiones PPPoE). Seleccione PPPoE estático para utilizar una dirección IP estática para su conexión PPPoE.
		</p>
		<p>
			<strong><em>Nombre de usuario </em></strong> - Introduzca su nombre de usuario de PPPoE.<br>
			<strong><em>Contraseña </em></strong> - Introduzca su contraseña de PPPoE.<br>
			<strong><em>Nombre del servicio </em></strong> (opcional) -
			Si su ISP utilizara un nombre de servicio para la conexión PPPoE, introduzca aquí el nombre del servicio.<br>
			<strong><em>Dirección IP </em></strong> -
			Esta opción sólo está disponible para PPPoE estático. Introduzca la dirección IP estática para la conexión PPPoE.<br>
			<strong><em>Dirección MAC </em></strong> (opcional) -
			Algunos Proveedores de servicios de Internet (ISP) requieren el campo Dirección MAC (Control de acceso al medio). La dirección MAC predeterminada se establece con la dirección MAC de la interfaz WAN en el <?query("/sys/modelname");?>. Puede utilizar el botón "Clonar dirección MAC" para copiar automáticamente la dirección MAC de la Tarjeta Ethernet instalada en el ordenador que se está utilizando para configurar el dispositivo. Sólo es necesario rellenar este campo si su ISP lo requiriera.
			<br>
			<strong><em>Dirección de DNS primario </em></strong> -
			Dirección IP del servidor DNS primario (Servicios de nombres de dominio), que podría proporcionarle su ISP. Sólo necesita introducir esta información si seleccionó el PPPoE estático. Si seleccionase PPPoE dinámico, deje este campo con su valor predeterminado ya que su ISP le proporcionará esta información automáticamente.
			<br>
			<strong><em>Dirección de DNS secundario </em></strong> (opcional) -
			Si su ISP le proporcionara una dirección IP del servidor DNS secundario, introdúzcala en este campo.<br>
			<strong><em>Tiempo de inactividad máximo </em></strong> -
			La cantidad de tiempo de inactividad (en minutos) antes de que el dispositivo desconecte su sesión PPPoE. Introduzca un Tiempo de inactividad máximo (en minutos) para definir un periodo máximo de tiempo para el que se mantenga la conexión de Internet durante la inactividad. Si la conexión estuviera inactiva durante más tiempo que el Tiempo de inactividad máximo definido, entonces la conexión se interrumpirá. Esta opción sólo se aplica al modo Conexión a petición.
			<br>
			<strong><em>MTU </em></strong> -
			MTU (Unidad de transmisión/transferencia máxima) es el máximo tamaño de paquete que se puede enviar sobre una red. Los mensajes mayores que la MTU se dividen en paquetes menores. 1492 es el valor predeterminado para esta opción. La modificación de este número podría afectar negativamente al rendimiento de su router. Cambie únicamente este número si se lo indica uno de nuestros Representantes de soporte técnico o si lo hiciera su ISP.
			<br>
			<strong><em>Seleccionar modo de conexión</em></strong> -
			Seleccione Siempre activado si desea que el router nunca desconecte la sesión PPPoE. Seleccione Manual si deseara controlar cuándo se conecta y desconecta el router de Internet. La opción Conexión a petición permite al router establecer una conexión a Internet sólo cuando un dispositivo en su red intente acceder a un recurso en Internet.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>PPTP</strong><br>
			Seleccione esta opción si su ISP utilizara una conexión PPTT (Protocolo de túneles punto a punto) y se le hubiera asignado un nombre de usuario y contraseña para acceder a Internet. Seleccione PPTP dinámico para obtener automáticamente una dirección IP para su conexión PPTP. Seleccione PPTP estático para utilizar una dirección IP estática para su conexión PPTP.
		</p>
		<p>
			<strong><em>Dirección IP </em></strong> - Introduzca la dirección IP que su ISP le ha asignado.<br>
			<strong><em>Máscara de subred </em></strong> -  Introduzca la Máscara de subred que su ISP le ha asignado.<br>
			<strong><em>Puerta de enlace</em></strong> -  Introduzca la dirección IP de la puerta de enlace que le asignó su ISP.<br>
			<strong><em>DNS - </em></strong>Introduzca la dirección DNS que le asignó su ISP.<br>
			<strong><em>IP del servidor </em></strong> -
			Introduzca la dirección IP del servidor que le suministrará su ISP para conectarse con dicho servidor.<br>
			<strong><em>Cuenta </em></strong> - Introduzca su nombre de usuario de PPTP.<br>
			<strong><em>Contraseña </em></strong> - Introduzca su contraseña PPTP.<br>
			<strong><em>Tiempo de inactividad máximo </em></strong> -
			La cantidad de tiempo de inactividad antes de que el dispositivo desconecte su sesión PPTP. Introduzca un Tiempo de inactividad máximo (en minutos) para definir un periodo máximo de tiempo para el que se mantenga la conexión de Internet durante la inactividad. Si la conexión estuviera inactiva durante más tiempo que el Tiempo de inactividad máximo especificado, entonces la conexión se interrumpirá. Esta opción sólo se aplica al modo Conexión a petición.
			<br>
			<strong><em>MTU </em></strong> -
			MTU (Unidad de transmisión/transferencia máxima) es el máximo tamaño de paquete que se puede enviar sobre una red. Los mensajes mayores que la MTU se dividen en paquetes menores. 1400 es el valor predeterminado para esta opción. La modificación de este número podría afectar negativamente al rendimiento de su router. Cambie únicamente este número si se lo indica uno de nuestros Representantes de soporte técnico o si lo hiciera su ISP.
			<br>
			<strong><em>Seleccionar modo de conexión</em></strong> -
			Seleccione Siempre activado si desea que el router nunca desconecte la sesión PPTP. Seleccione Manual si deseara controlar cuándo se conecta y desconecta el router de Internet. La opción Conexión a petición permite al router establecer una conexión a Internet sólo cuando un dispositivo en su red intente acceder a un recurso en Internet.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>L2TP </strong><br>
			Seleccione esta opción si su ISP utilizara una conexión L2TP (Capa 2 del Protocolo de túneles) y se le hubiera asignado un nombre de usuario y contraseña para acceder a Internet. Seleccione L2TP dinámico para obtener automáticamente una dirección IP para su conexión L2TP. Seleccione L2TP estático para utilizar una dirección IP estática para su conexión L2TP.
		</p>
		<p>
			<strong><em>Dirección IP </em></strong> - Introduzca la dirección IP que su ISP le ha asignado.<br>
			<strong><em>Máscara de subred </em></strong> - Introduzca la Máscara de subred que su ISP le ha asignado.<br>
			<strong><em>Puerta de enlace</em></strong> - Introduzca la dirección IP de la puerta de enlace que le asignó su ISP.<br>
			<strong><em>DNS</em></strong> -  Introduzca la dirección DNS que le asignó su ISP.<br>
			<strong><em>IP del servidor </em></strong> -
			Introduzca la dirección IP del servidor que le suministrará su ISP para conectarse con dicho servidor.<br>
			<strong><em>Cuenta L2TP </em></strong> - Introduzca su nombre de usuario de L2TP.<br>
			<strong><em>Contraseña L2TP </em></strong> -  Introduzca su contraseña L2TP.<br>
			<strong><em>Tiempo de inactividad máximo </em></strong> -
			La cantidad de tiempo de inactividad (en minutos) antes de que el dispositivo desconecte su sesión L2TP. Introduzca un Tiempo de inactividad máximo (en minutos) para definir un periodo máximo de tiempo para el que se mantenga la conexión de Internet durante la inactividad. Si la conexión estuviera inactiva durante más tiempo que el Tiempo de inactividad máximo definido, entonces la conexión se interrumpirá. Esta opción sólo se aplica al modo Conexión a petición.
			<br>
			<strong><em>MTU</em></strong> -
			MTU (Unidad de transmisión/transferencia máxima) es el máximo tamaño de paquete que se puede enviar sobre una red. Los mensajes mayores que la MTU se dividen en paquetes menores. 1400 es el valor predeterminado para esta opción. La modificación de este número podría afectar negativamente al rendimiento de su router. Cambie únicamente este número si se lo indica uno de nuestros Representantes de soporte técnico o si lo hiciera su ISP.
			<strong><em>Seleccionar modo de conexión</em></strong> -
			Seleccione Siempre activado si desea que el router nunca desconecte la sesión L2TP. Seleccione Manual si deseara controlar cuándo se conecta y desconecta el router de Internet. La opción Conexión a petición permite al router establecer una conexión a Internet sólo cuando un dispositivo en su red intente acceder a un recurso en Internet.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>PPTP ruso (acceso doble)</strong><br>
			Para configurar una conexión a Internet PPTP ruso, realice la configuración de igual forma que la descrita para conexiones PPTP. Si fuera necesario que su ISP configurara alguna ruta estática, consulte la función "Enrutamiento" en el menú " OPCIONES AVANZADAS" para la configuración posterior.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>PPPoE ruso (acceso doble)</strong><br>
			Algunas conexiones PPPoE utilizan una ruta IP estática hasta el ISP además de los parámetros IP globales para la conexión. Esto requiere un paso añadido para definir los parámetros IP para el puerto WAN físico. Para configurar una conexión a Internet PPPoE ruso, realice la configuración como se describe previamente para conexiones PPPoE y añada los parámetros IP WAN física como le indique su ISP. Si fuera necesario que su ISP configurara alguna ruta estática, consulte la función "Enrutamiento" en el menú " OPCIONES AVANZADAS" para la configuración posterior.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="wireless_setup"><h2>Configuración inalámbrica</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			La página Configuración inalámbrica contiene los ajustes para la Parte del <?query("/sys/modelname");?> (Punto de acceso). Esta página le permite personalizar su red inalámbrica o configurar el <?query("/sys/modelname");?> para ajustarse a una red inalámbrica existente que ya haya configurado.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Configuración protegida Wi-Fi (también denominada WCN 2.0 en Windows Vista)</strong><br>
			Esta funcionalidad proporciona a los usuarios una forma más intuitiva de configuración de la seguridad inalámbrica. Está disponible en dos formatos: Número PIN y botón de pulsación. Introduzca el número PIN que viene con el dispositivo en la utilidad de la tarjeta inalámbrica o en la utilidad del cliente inalámbrico de Windows Vista si la tarjeta inalámbrica tuviera un controlador certificado de Windows Vista para configurar automáticamente la seguridad inalámbrica entre el router y el cliente. La tarjeta inalámbrica tendrá que dar soporte a la Configuración protegida Wi-Fi en cualquier formato para beneficiarse de esta funcionalidad.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Nombre de la red inalámbrica</strong><br>
			También conocido como el SSID (Identificador configurado del servicio), este es el nombre de su Red de área local inalámbrica (WLAN). Por defecto, el SSID del <?query("/sys/modelname");?> es "dlink". Esto se puede modificar fácilmente para establecer una nueva red inalámbrica o para añadir el <?query("/sys/modelname");?> a una red inalámbrica existente.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Canal inalámbrico</strong><br>
			Indica el canal sobre el que está operando el <?query("/sys/modelname");?>. De forma predeterminada, el canal se establece a 6. Esto se puede modificar para adecuar el parámetro del canal para una red inalámbrica existente o para personalizar su nueva red inalámbrica. Haga clic en el cuadro de selección Activar exploración automática para que el <?query("/sys/modelname");?> seleccione automáticamente el canal en el que operará. Se recomienda esta opción porque el router elegirá el canal con el mínimo nivel de interferencias.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>	
 		<p>
 			<strong>Tasas de transmisión (TX)</strong><br>
 			Seleccione las tasas básicas de transferencia en función de la velocidad de los adaptadores inalámbricos en la WLAN (red de área local inalámbrica).
 		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>WMM</strong><br>
			Seleccione Activar para activar QoS para la interfaz inalámbrica del <?query("/sys/modelname");?>.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Activar inalámbrico oculto </strong><br>
			Seleccione Activar si no quisiera que el SSID de su red inalámbrica se difundiera mediante el <?query("/sys/modelname");?>. Si se activara esta opción, el SSID del <?query("/sys/modelname");?> no será visto por las utilidades del Estudio del sitio, por lo que al configurar sus clientes inalámbricos, tendrá que conocer el SSID de su <?query("/sys/modelname");?> e introducirlo manualmente para conectarse al router. Esta opción está activada de forma predeterminada.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Modo de seguridad inalámbrica</strong><br>
			Es importante hacer más segura su red inalámbrica ya que se utiliza para proteger la integridad de la información que se transmite a través de la red inalámbrica. El <?query("/sys/modelname");?> admite 4 tipos de seguridad inalámbrica; WEP, sólo WPA, sólo WPA2 y WPA/WPA2 (detección automática)
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>WEP </strong><br>
			El protocolo equivalente con cables (WEP) es un protocolo de seguridad inalámbrico para las redes de área local inalámbricas (WLAN). WEP proporciona seguridad mediante el cifrado de los datos que se envía a través de la WLAN. El <?query("/sys/modelname");?> admite 2 niveles de cifrado WEP: 64 bits y 128 bits. El protocolo WEP está desactivado de manera predeterminada. La configuración de WEP se puede cambiar para adaptarla a una red inalámbrica existente o para personalizar su red inalámbrica.
		</p>
		<p>
			<strong><em>Autenticación</em></strong> -
			La autenticación es un proceso por el que el <?query("/sys/modelname");?> verifica la identidad de un dispositivo de red que está intentando unirse a la red inalámbrica. Al utilizar WEP, existen dos tipos de autenticación para este dispositivo.
			<br> 
			<strong><em>Sistema abierto</em></strong> -
			Seleccione esta opción para permitir que todos los dispositivos se comuniquen con el <?query("/sys/modelname");?> antes de que se les pida la clave de cifrado necesaria para acceder a la red.
			<br>
			<strong><em>Clave compartida</em></strong> -
			Seleccione esta opción para solicitar a cualquier dispositivo inalámbrico que intente comunicarse con el <?query("/sys/modelname");?> la clave de cifrado necesaria para acceder a la red antes de que se les permita comunicarse con el <?query("/sys/modelname");?>.
			<br>
			<strong><em>Cifrado WEP</em></strong> -
			Seleccione el nivel de Cifrado WEP que le gustaría utilizar en su red. Los dos niveles de cifrado WEP admitidos son 64 bits y 128 bits.
			<br>
			<strong><em>Tipo de clave</em></strong> -
			Los tipos de clave que admite el <?query("/sys/modelname");?> son HEX (hexadecimal) y ASCII (American Standard Code for Information Interchange). El tipo de clave se puede cambiar para adaptarla a una red inalámbrica existente o para personalizar su red inalámbrica.
			<br>
			<strong><em>Claves</em></strong> -
			Las claves 1-4 permiten cambiar fácilmente la configuración de la codificación inalámbrica para mantener una red segura. Simplemente, seleccione la clave específica que se debe utilizar para codificar los datos inalámbricos en la red.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>WPA/WPA2</strong><br>
			El acceso protegido Wi-Fi (o Acceso protegido Wi-Fi 2) autoriza y autentifica usuarios para acceder a la red inalámbrica. WPA utiliza una seguridad más potente que WEP y se basa en una clave que cambia automáticamente a intervalos regulares.
		</p>
		<p>
			<strong><em>Tipo de cifrado</em></strong> -
			El <?query("/sys/modelname");?> admite dos tipos de cifrado diferentes cuando se utiliza WPA como tipo de seguridad.. Estas dos opciones son TKIP (Protocolo de integridad de clave temporal) y AES (Estándar de cifrado avanzado).
			<br>
			<strong><em>PSK/EAP</em></strong> -
			 Cuando está seleccionado PSK, los clientes inalámbricos deberán proporcionar una frase secreta para la autenticación. Cuando está seleccionado EAP, necesitará disponer de un servidor RADIUS en la red que le permitirá manejar la autenticación de todos sus clientes inalámbricos.
			 <br>
			<strong><em>Frase secreta</em></strong> -
			Es lo que necesitarán todos sus clientes inalámbricos para comunicarse con su <?query("/sys/modelname");?>. Cuando se selecciona PSK, introduzca de 8-63 caracteres alfanuméricos. Asegúrese de escribir la frase secreta ya que necesitará introducirla en cualquiera de los dispositivos inalámbricos que intente añadir a la red.
			<br>
			<strong><em>802.1X</em></strong> -
			Esto implica que la autenticación WPA se utilizará junto con un servidor RADIUS que debe estar presente en su red. Introduzca la dirección IP, el puerto y el secreto compartido para los que está configurado su servidor RADIUS. También tiene la opción de introducir información para un segundo servidor RADIUS, en el caso de que su red disponga de dos, que esté utilizando para autentificar clientes inalámbricos.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="lan_setup"><h2>Configuración de red</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			Estos son los parámetros de la interfaz de LAN (Red de área local) para el dispositivo. A estos parámetros se les hace referencia como "parámetros privados". Puede modificar la dirección IP de LAN si fuera necesario. La dirección IP de LAN es privada para su red interna y no se puede ver en Internet. La dirección IP predeterminada es 192.168.0.1 con una máscara de subred de 255.255.255.0.
			<br><br>
			<strong><em>Dirección IP</em></strong> -
			La dirección IP predeterminada del <?query("/sys/modelname");?> es 192.168.0.1.<br>
			<strong><em>Máscara de subred</em></strong> -
			La Máscara de subred predeterminada de <?query("/sys/modelname");?> es 255.255.255.0.<br>
			<strong><em>Nombre de dominio local</em></strong> (opcional) - Introduzca el nombre de dominio local para su red.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong><em>DNS Relay</em></strong> -
			Cuando se activa DNS Relay, los clientes DHCP del router se asignarán a la dirección IP de LAN del router como su servidor DNS. Todas las peticiones de DNS que reciba el router se enviarán a sus servidores DNS del ISP. Cuando se desactiva DNS, todos los clientes DHCP del router se asignarán al servidor DNS del ISP.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Servidor DHCP</strong><br>
			DHCP son las siglas en inglés de Protocolo de configuración de host dinámico. El servidor DHCP asigna direcciones IP a los dispositivos de la red que lo solicitan. Los dispositivos deben haberse establecido como "Obtener la dirección IP automáticamente". El servidor DHCP está activado de forma predeterminada en el <?query("/sys/modelname");?>. El grupo de direcciones DHCP contiene el rango de las direcciones IP que se asignarán automáticamente a los clientes de la red.
		</p>
		<p>
			<strong>Reserva DHCP</strong><br>
			Introduzca manualmente los valores de "Nombre del ordenador", "Dirección IP" y "Dirección MAP" para el PC que quiera que disponga el router para asignar de forma estática la misma IP, o seleccione el PC desde el menú desplegable que muestra los clientes DHCP actuales.
		</p>
		<p>
			<strong><em>Dirección IP inicial</em></strong> La dirección IP inicial para la asignación IP del servidor DHCP.<br>
			<strong><em>Dirección IP final</em></strong> La dirección IP final para la asignación IP del servidor DHCP.<br>
			<strong><em>Tiempo de validez</em></strong> El lapso temporal, en minutos, de validez de la IP.
		</p>
		<p>
			Los ordenadores de clientes DHCP dinámicos conectados a la unidad verán su información en la tabla de clientes DHCP dinámicos. Esta tabla muestra el nombre de host, la dirección IP, la dirección MAC y el tiempo de caducidad de la concesión DHCP para cada ordenador de cliente.
		</p>
	</td>
</tr>
</table>
</div>

<div class="box">
<a name="lcd_setup"><h2>Configuración de la pantalla LCD</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			La página Configuración de la pantalla LCD controla los parámetros del panel de visualización en su dispositivo <?query("/sys/modelname");?>. Esta página le permite controlar al salvapantallas y ajustar la cantidad de tiempo que necesita el dispositivo estar inactivo antes de que la Pantalla LCD se apague.
			<br><br>
			<strong><em>Parámetro del salvapantallas</em></strong> -
			El salvapantallas visualizará la imagen "screen_bg.jpg" en el fondo de pantalla y almacenada en el directorio raíz del disco duro interno, con la fecha y hora actuales moviéndose aleatoriamente por encima de la imagen. Si no se pudiera encontrar la imagen, el fondo de pantalla permanecerá en color negro. El parámetro "Tiempo de espera" indica la cantidad de minutos requeridos antes de que el dispositivo entre en modo salvapantallas, si se dejó inactivo. El dispositivo saldrá del modo salvapantallas si se pulsa cualquier botón en la pantalla táctil.<br>
			<strong><em>Parámetro de visualización</em></strong> -
			Este parámetro apagará la pantalla de visualización LCD para ahorrar energía si el dispositivo se dejara inactivo durante la cantidad de minutos configurada en el campo "Tiempo de espera". La pantalla de visualización LCD se encenderá nuevamente si se pulsara cualquiera de los botones de la pantalla táctil.<br>
		</p>
	</td>
</tr>
</table>
</div>
