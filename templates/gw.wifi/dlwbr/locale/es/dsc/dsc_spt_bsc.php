<h1>MENÚ DE SOPORTE</h1>
<table border=0 cellspacing=0 cellpadding=0 width=750>
<tr>
	<td height=40>
		<p><font size=4><strong>Configuración</strong></font></p>
		<p>
			<a name=01><strong>Configuración de Internet</strong></a><br>
			Si está configurando por primera vez este dispositivo, se recomienda hacer clic en el Asistente de configuración de conexión a Internet y seguir las instrucciones en pantalla. Si desea modificar o configurar manualmente los parámetros del dispositivo, haga clic en Configuración manual de la conexión a Internet.
		</p>
	</td>
</tr>
<tr>
	<td height=59>
		<p>
			<strong>Ejecutar el asistente para la configuración de la conexión a Internet </strong><br>
			Haga clic en este botón para que el router le lleve a través de varios pasos sencillos para ayudarle a conectar el router a Internet.<br>
			<strong>Ejecutar el asistente para la configuración de seguridad inalámbrica </strong><br>
			Haga clic en este botón para que el router le lleve a través de la configuración de los parámetros de su red inalámbrica, incluida la seguridad.
		</p>
	</td>
</tr>
<tr><td height=32>&nbsp;</td></tr>
<tr>
	<td height=46>
		<p>
			<strong>Configuración manual de la conexión a Internet</strong><br>
			Elija esta opción si desea introducir los parámetros necesarios para conectar manualmente el router a Internet.<br>
			<strong>Modo de punto de acceso</strong><br>
			Activar "Modo de punto de acceso" hará que el dispositivo funcione como un AP inalámbrico. Se desactivarán todas las funciones de NAT excepto los parámetros relacionados con la red inalámbrica.<br>
			<strong>Tipo de conexión a Internet  </strong><br>
			Los parámetros de conexión a Internet se utilizan para conectar el<?query("/sys/modelname");?> a Internet. Toda la información que necesita introducir en esta página se la suministrará su ISP y, en ocasiones, se denominará &quot;parámetros públicos&quot;. Seleccione la opción adecuada para su ISP específico. Si no está seguro de la opción que debe seleccionar, póngase en contacto con su ISP.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=61>
		<p>
			<strong>Dirección IP estática</strong><br>
			Seleccione esta opción si su ISP (Proveedor de servicios de Internet) le ha proporcionado una dirección IP, máscara de subred, puerta de enlace predeterminada y una dirección de servidor DNS. Introduzca esta información en los campos adecuados. Si no está seguro de lo que debe introducir en estos campos, póngase en contacto con su ISP.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=142>
		<p>
			<strong>Dirección IP dinámica</strong><br>
			Seleccione esta opción si su ISP (Proveedor de servicios de Internet) le proporciona una dirección IP automáticamente. Los proveedores de módem por cable utilizan normalmente la asignación dinámica de dirección IP.
		</p>
		<p>
			<strong><em>Nombre de host </em></strong> (opcional) -
			el campo Nombre de host es opcional pero puede ser necesario para algunos Proveedores de servicios de Internet. El nombre de host predeterminado es el número de modelo del router.<br>
			<strong><em>Dirección MAC</em></strong> (opcional) -
			el campo Dirección MAC (Control de acceso a medios) es necesario para algunos Proveedores de servicios de Internet (ISP). La dirección MAC predeterminada se establece en la dirección MAC de la interfaz WAN en el <?query("/sys/modelname");?>. Puede utilizar el botón &quot;Clonar dirección MAC&quot; para copiar automáticamente la dirección MAC de la tarjeta Ethernet instalada en el ordenador que se utiliza para configurar el dispositivo. Sólo es necesario rellenar el campo si su ISP lo necesita.<br>
			<strong><em>Dirección DNS principal</em></strong> -
			introduzca dirección IP del servidor DNS (Servicio de nombre de dominio) principal suministrada por su ISP.<br>
			<strong><em>Dirección DNS secundaria</em></strong> (opcional) -
			 si su ISP le ha proporcionado una dirección IP de servidor DNS secundario, introdúzcala en este campo.<br>
			<strong><em>MTU </em></strong> -
			MTU (Unidad de transmisión/transferencia máxima) es el tamaño de paquete más grande que se puede enviar a través de una red. Los mensajes que sean más grandes que la MTU se dividen en paquetes más pequeños. 1500 es el valor predeterminado para esta opción. Cambiar este número puede afectar negativamente al rendimiento de su router. Únicamente cambie este número si así se lo indica uno de los representantes de nuestro Servicio técnico o su ISP.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=47>
		<p>
			<strong>PPPoE</strong><br>
			Seleccione esta opción si su ISP le pide que utilice una conexión PPPoE (Protocolo de punto a punto a través de Ethernet). Normalmente, los proveedores de DSL utilizan esta opción. Seleccione PPPoE dinámico para obtener automáticamente una dirección IP para su conexión PPPoE (utilizada por la mayoría de las conexiones PPPoE). Seleccione PPPoE estático para utilizar una dirección IP estática para su conexión PPPoE.
		</p>
		<p>
			<strong><em>Nombre de usuario</em></strong> - introduzca su nombre de usuario PPPoE.<br>
			<strong><em>Contraseña </em></strong> - introduzca su contraseña PPPoE.<br>
			<strong><em>Nombre del servicio </em></strong> (opcional) -
			si su ISP utiliza un nombre de servicio para la conexión PPPoE, introduzca aquí el nombre del servicio.<br>
			<strong><em>Dirección IP</em></strong> -
			esta opción sólo está disponible para PPPoE estático. Introduzca la dirección IP estática para la conexión PPPoE.<br>
			<strong><em>Dirección MAC</em></strong> (opcional) -
			 el campo Dirección MAC (Control de acceso a medios) es necesario para algunos Proveedores de servicios de Internet (ISP). La dirección MAC predeterminada se establece en la dirección MAC de la interfaz WAN en el <?query("/sys/modelname");?>. Puede utilizar el botón &quot;Clonar dirección MAC&quot; para copiar automáticamente la dirección MAC de la tarjeta Ethernet instalada en el ordenador que se utiliza para configurar el dispositivo. Sólo es necesario rellenar el campo si su ISP lo necesita.<br>
			<strong><em>Dirección DNS principal</em></strong> -
			dirección IP del servidor DNS (Sistema de nombre de dominio) principal, que puede suministrarle su ISP. Sólo debe necesitar introducir esta información si ha seleccionado PPPoE estático. Si se elige PPPoE dinámico, deje este campo con su valor predeterminado ya que su ISP le proporcionará esta información automáticamente.<br>
			<strong><em>Dirección DNS secundaria</em></strong> (opcional) -
			si su ISP le ha proporcionado una dirección IP de servidor DNS secundario, introdúzcala en este campo.<br>
			<strong><em>Tiempo de inactividad máximo </em></strong> -
			 la cantidad de tiempo de inactividad antes de que el dispositivo desconecte la sesión PPPoE. Introduzca un Tiempo de inactividad máximo (en minutos) para definir el periodo de tiempo máximo durante el que se mantiene la conexión a Internet durante la inactividad. Si la conexión está inactiva durante un periodo superior al Tiempo de inactividad máximo definido, se interrumpirá la conexión. Esta opción sólo se aplica al modo de conexión Conexión a petición.<br>
			<strong><em>MTU </em></strong> -
			 MTU (Unidad de transmisión/transferencia máxima) es el tamaño de paquete más grande que se puede enviar a través de una red. Los mensajes que sean más grandes que la MTU se dividen en paquetes más pequeños. 1492 es el valor predeterminado para esta opción. Cambiar este número puede afectar negativamente al rendimiento de su router. Únicamente cambie este número si así se lo indica uno de los representantes de nuestro Servicio técnico o su ISP.<br>
			<strong><em>Seleccionar modo de conexión</em></strong> -
			seleccione Siempre activado si desea que el router no desconecte nunca la sesión PPPoE. Seleccione Manual si desea controlar cuando está conectado y desconectado el router de Internet. La opción Conexión a petición permite al router establecer una conexión a Internet únicamente cuando un dispositivo de la red intenta acceder a un recurso en Internet.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>PPTP</strong><br>
			Seleccione esta opción si su ISP utiliza una conexión PPTP (Protocolo de tunelación de punto a punto) y le ha asignado un nombre de usuario y una contraseña para acceder a Internet. Seleccione PPTP dinámico para obtener automáticamente una dirección IP para su conexión PPTP. Seleccione PPTP estático para utilizar una dirección IP estática para su conexión PPTP.
		</p>
		<p>
			<strong><em>Dirección IP</em></strong> - introduzca la dirección IP que le ha asignado su ISP.<br>
			<strong><em>Máscara de subred </em></strong> -  introduzca la máscara de subred que le ha asignado su ISP.<br>
			<strong><em>Puerta de enlace</em></strong> -  introduzca la dirección IP de la puerta de enlace que le ha asignado su ISP.<br>
			<strong><em>DNS - </em></strong>introduzca la dirección DNS que le ha asignado su ISP.<br>
			<strong><em>IP del servidor</em></strong> -
			 introduzca la dirección IP del servidor al que se conectará, que le suministrará su ISP.<br>
			<strong><em>Cuenta </em></strong> - introduzca su nombre de usuario PPTP.<br>
			<strong><em>Contraseña </em></strong> - introduzca su contraseña PPTP.<br>
			<strong><em>Tiempo de inactividad máximo </em></strong> -
			 la cantidad de tiempo de inactividad antes de que el dispositivo desconecte la sesión PPTP. Introduzca un Tiempo de inactividad máximo (en minutos) para definir el periodo de tiempo máximo durante el que se mantiene la conexión a Internet durante la inactividad. Si la conexión está inactiva durante un periodo superior al Tiempo de inactividad máximo definido, se interrumpirá la conexión. Esta opción sólo se aplica al modo de conexión Conexión a petición.<br>
			<strong><em>MTU </em></strong> -
			MTU (Unidad de transmisión/transferencia máxima) es el tamaño de paquete más grande que se puede enviar a través de una red. Los mensajes que sean más grandes que la MTU se dividen en paquetes más pequeños. 1.400 es el valor predeterminado para esta opción. Cambiar este número puede afectar negativamente al rendimiento de su router. Únicamente cambie este número si así se lo indica uno de los representantes de nuestro Servicio técnico o su ISP.<br>
			<strong><em>Seleccionar modo de conexión</em></strong> -
			seleccione Siempre activado si desea que el router no desconecte nunca la sesión PPTP. Seleccione Manual si desea controlar cuando está conectado y desconectado el router de Internet. La opción Conexión a petición permite al router establecer una conexión a Internet únicamente cuando un dispositivo de la red intenta acceder a un recurso en Internet.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>L2TP </strong><br>
			Seleccione esta opción si su ISP utiliza una conexión L2TP (Protocolo de tunelación de capa 2) y le ha asignado un nombre de usuario y una contraseña para acceder a Internet. Seleccione L2TP dinámico para obtener automáticamente una dirección IP para su conexión L2TP. Seleccione L2TP estático para utilizar una dirección IP estática para su conexión L2TP.
		</p>
		<p>
			<strong><em>Dirección IP </em></strong> - introduzca la dirección IP que le ha asignado su ISP.<br>
			<strong><em>Máscara de subred</em></strong> -  introduzca la máscara de subred que le ha asignado su ISP.<br>
			<strong><em>Puerta de enlace</em></strong> - introduzca la dirección IP de la puerta de enlace que le ha asignado su ISP.<br>
			<strong><em>DNS</em></strong> - introduzca la dirección DNS que le ha asignado su ISP.<br>
			<strong><em>IP del servidor</em></strong> -
			introduzca la dirección IP del servidor al que se conectará, que le suministrará su ISP.<br>
			<strong><em>Cuenta L2TP </em></strong> -introduzca su nombre de usuario L2TP.<br>
			<strong><em>Contraseña L2TP:</em></strong> -  introduzca su contraseña L2TP.<br>
			<strong><em>Tiempo de inactividad máximo</em></strong> -
			 la cantidad de tiempo de inactividad antes de que el dispositivo desconecte la sesión L2TP. Introduzca un Tiempo de inactividad máximo (en minutos) para definir el periodo de tiempo máximo durante el que se mantiene la conexión a Internet durante la inactividad. Si la conexión está inactiva durante un periodo superior al Tiempo de inactividad máximo definido, se interrumpirá la conexión. Esta opción sólo se aplica al modo de conexión Conexión a petición.<br>
			<strong><em>MTU</em></strong> -
			MTU (Unidad de transmisión/transferencia máxima) es el tamaño de paquete más grande que se puede enviar a través de una red. Los mensajes que sean más grandes que la MTU se dividen en paquetes más pequeños. 1.400 es el valor predeterminado para esta opción. Cambiar este número puede afectar negativamente al rendimiento de su router. Únicamente cambie este número si así se lo indica uno de los representantes de nuestro Servicio técnico o su ISP. 
			<strong><em>Seleccionar modo de conexión</em></strong> -
			seleccione Siempre activado si desea que el router no desconecte nunca la sesión L2TP. Seleccione Manual si desea controlar cuando está conectado y desconectado el router de Internet. La opción Conexión a petición permite al router establecer una conexión a Internet únicamente cuando un dispositivo de la red intenta acceder a un recurso en Internet.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>PPTP para Rusia (acceso doble)</strong><br>
			 Para configurar una conexión a Internet PPTP para Rusia, realice la configuración según la descripción anterior para las conexiones PPTP.   Si su ruta estática necesita ser configurada por su ISP, consulte la función &quot;Enrutamiento&quot; en el menú &quot;OPCIONES AVANZADAS&quot; para ver más configuraciones.

		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>PPPoE para Rusia (acceso doble) </strong><br>
			Algunas conexiones PPPoE utilizan una ruta IP estática además de los parámetros IP globales para la conexión. Esto requiere un paso añadido para definir los parámetros IP para el puerto WAN físico.   Para configurar la conexión a Internet PPPoE para Rusia, realice la configuración según la descripción anterior para las conexiones PPPoE y añada el parámetro IP de la WAN física de acuerdo con las instrucciones del ISP.   Si su ruta estática necesita ser configurada por su ISP, consulte la función &quot;Enrutamiento&quot; en el menú &quot;OPCIONES AVANZADAS&quot; para ver más configuraciones.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<a name=02><strong>Configuración inalámbrica</strong></a><br>
			La página Configuración inalámbrica contiene los parámetros para la parte (punto de acceso) del <?query("/sys/modelname");?>. Esta página permite personalizar su red inalámbrica o configurar el <?query("/sys/modelname");?> para adaptar una red inalámbrica existente que puede que ya haya configurado.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Configuración protegida Wi-Fi (también denominada WCN 2.0 en Windows Vista)</strong><br>
			TEsta característica proporciona a los usuarios una forma más intuitiva de configurar la seguridad inalámbrica. Viene en dos formatos: número de PIN y botón de pulsación. Introducir el número de PIN que viene con el dispositivo en la utilidad de tarjeta inalámbrica o en la utilidad de clientes inalámbricos de Windows Vista, si la tarjeta inalámbrica tiene un controlador Windows Vista certificado, puede configurar la seguridad inalámbrica entre el router y el cliente. La tarjeta inalámbrica deberá ser compatible con la configuración protegida Wi-Fi en cualquier formato para poder aprovechar las ventajas de dicha característica.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Nombre de la red inalámbrica</strong><br>
			Conocido también como SSID (Identificador configurado de servicio), este es el nombre de su red de área local inalámbrica (WLAN). De forma predeterminada, el SSID del <?query("/sys/modelname");?> es &quot;dlink&quot;. Esto se puede cambiar fácilmente para establecer una nueva red inalámbrica o para añadir el <?query("/sys/modelname");?> a una red inalámbrica existente.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Canal inalámbrico</strong><br>
			Indica el canal en el que está funcionando el <?query("/sys/modelname");?>. De forma predeterminada, el canal se establece en 6. Esto se puede cambiar para adaptar el parámetro del canal a una red inalámbrica existente o para personalizar su red inalámbrica nueva. Haga clic en la casilla de verificación Activar búsqueda automática para que el <?query("/sys/modelname");?> seleccione automáticamente el canal en el que funcionará. Se recomienda esta opción porque el router elegirá el canal con la menor cantidad de interferencias.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>WMM</strong><br>
			Seleccione Activar para activar la QoS para la interfaz inalámbrica del <?query("/sys/modelname");?>.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Activar red inalámbrica oculta  </strong><br>
			Seleccione Activado si no desea que el <?query("/sys/modelname");?> difunda el SSID de su red inalámbrica. Si esta opción está Activada, el SSID del <?query("/sys/modelname");?> no será visto por las utilidades de Estudio del sitio, de modo que, al configurar los clientes inalámbricos, deberá conocer el SSID de su <?query("/sys/modelname");?> e introducirlo manualmente para poder conectar con el router. Esta opción está activada de forma predeterminada.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Modo de seguridad inalámbrica</strong><br>
			Es importante hacer más segura su red inalámbrica ya que se utiliza para proteger la integridad de la información que se transmite a través de la red inalámbrica. El <?query("/sys/modelname");?> admite 4 tipos de seguridad inalámbrica; WEP, Sólo WPA, Sólo WPA2 y WPA/WPA2 (detección automática)
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
			 la autenticación es un proceso mediante el cual el <?query("/sys/modelname");?> comprueba la identidad de un dispositivo de red que está intentando unirse a la red inalámbrica. Al utilizar WEP, existen dos tipos de autenticación para este dispositivo.<br> 
			<strong><em>Sistema abierto</em></strong> -
			seleccione esta opción para permitir que todos los dispositivos inalámbricos se comuniquen con el <?query("/sys/modelname");?> antes de que se les pida la clave de cifrado necesaria para acceder a la red.<br>
			<strong><em>Clave compartida</em></strong> -
			 seleccione esta opción para solicitar a cualquier dispositivo inalámbrico que intente comunicar con el <?query("/sys/modelname");?> que proporcione la clave de cifrado necesaria para acceder a la red antes de que se le permita comunicarse con el <?query("/sys/modelname");?>..<br>
			<strong><em>Cifrado WEP</em></strong> -
			seleccione el nivel de nivel de cifrado WEP que desee utilizar en su red. Los dos niveles de cifrado WEP admitidos son 64 bits y 128 bits.<br>
			<strong><em>Tipo de clave</em></strong> -
			 los tipos de clave que admite el <?query("/sys/modelname");?> son HEX (Hexadecimal) y ASCII (American Standard Code for Information Interchange.) El tipo de clave se puede cambiar para adaptarla a una red inalámbrica existente o para personalizar su red inalámbrica.<br>
			<strong><em>Claves</em></strong> -
			las claves 1-4 permiten cambiar fácilmente la configuración de la codificación inalámbrica para mantener una red segura. Simplemente, seleccione la clave específica que se debe utilizar para codificar los datos inalámbricos en la red.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>WPA-Personal</strong><br>
			El acceso protegido Wi-Fi autoriza y autentifica usuarios para acceder a la red inalámbrica. WPA utiliza una seguridad más potente que WEP y se basa en una clave que cambia automáticamente a intervalos regulares.
		</p>
		<p>
			<strong><em>Tipo de cifrado</em></strong> -
			el <?query("/sys/modelname");?> admite dos tipos de cifrado diferentes cuando se utiliza WPA como tipo de seguridad. Estas dos opciones son TKIP (Protocolo de integridad de clave temporal) y AES (Estándar de cifrado avanzado).<br>
			<strong><em>PSK/EAP</em></strong> -
			cuando está seleccionado PSK, los clientes inalámbricos deberán proporcionar una frase secreta para la autenticación. Cuando está seleccionado EAP, necesitará disponer de un servidor RADIUS en la red que le permitirá manejar la autenticación de todos sus clientes inalámbricos.<br>
			<strong><em>Frase secreta</em></strong> -
			 es lo que necesitarán todos sus clientes inalámbricos para comunicar con su <?query("/sys/modelname");?>, cuando está seleccionado PSK. Introduzca de 8 a 63 caracteres alfanuméricos. Asegúrese de escribir la frase secreta ya que necesitará introducirla en cualquiera de los dispositivos inalámbricos que intente añadir a la red.<br>
			<strong><em>802.1X</em></strong> -
			esto implica que la autenticación WPA se utiliza junto con un servidor RADIUS, que debe estar presente en la red. Introduzca la dirección IP, el puerto y el secreto compartido para los que está configurado el servidor RADIUS. También tiene la opción de introducir información para un segundo servidor RADIUS, en el caso de que su red disponga de dos, que esté utilizando para autentificar clientes inalámbricos.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>WPA2</strong><br>
			El acceso protegido Wi-Fi 2 autoriza y autentifica usuarios para acceder a la red inalámbrica. WPA2 utiliza una seguridad más potente que WEP y se basa en una clave que cambia automáticamente a intervalos regulares.
		</p>
		<p>
			<strong><em>Tipo de cifrado</em></strong> -
			 el <?query("/sys/modelname");?> admite dos tipos de cifrado diferentes cuando se utiliza WPA como tipo de seguridad. Estas dos opciones son TKIP (Protocolo de integridad de clave temporal) y AES (Estándar de cifrado avanzado).<br>
			<strong><em>PSK/EAP</em></strong> -
			cuando está seleccionado PSK, los clientes inalámbricos deberán proporcionar una frase secreta para la autenticación. Cuando está seleccionado EAP, necesitará disponer de un servidor RADIUS en la red que le permitirá manejar la autenticación de todos sus clientes inalámbricos.<br>
			<strong><em>Frase secreta</em></strong> -
			es lo que necesitarán todos sus clientes inalámbricos para comunicar con su <?query("/sys/modelname");?>, cuando está seleccionado PSK. Introduzca de 8 a 63 caracteres alfanuméricos. Asegúrese de escribir la frase secreta ya que necesitará introducirla en cualquiera de los dispositivos inalámbricos que intente añadir a la red.<br>
			<strong><em>802.1X</em></strong> -
			esto implica que la autenticación WPA2 se utiliza junto con un servidor RADIUS, que debe estar presente en la red. Introduzca la dirección IP, el puerto y el secreto compartido para los que está configurado el servidor RADIUS. También tiene la opción de introducir información para un segundo servidor RADIUS, en el caso de que su red disponga de dos, que esté utilizando para autentificar clientes inalámbricos.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
 	<td height=20>
		<p>
			<strong>WPA2-Auto</strong><br>
			Esta opción permite que el <?query("/sys/modelname");?> tenga clientes WPA2 y WPA conectados simultáneamente.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<a name=03><strong>Configuración de LAN</strong></a><br>
			Estos son los parámetros de la interfaz de LAN (Red de área local) para el dispositivo. Estos parámetros se denominan &quot;parámetros privados&quot;. Puede cambiar la dirección IP de LAN si es necesario. La dirección IP de LAN es privada para su red interna y no se puede ver en Internet. La dirección IP predeterminada es 192.168.0.1, con una máscara de subred de 255.255.255.0.<br><br>
			<strong><em>Dirección IP</em></strong> -
			la dirección IP del <?query("/sys/modelname");?>, el valor predeterminado es 192.168.0.1.<br>
			<strong><em>Máscara de subred</em></strong> -
			a máscara de subred de <?query("/sys/modelname");?>, el valor predeterminado es 255.255.255.0.<br>
			<strong><em>Nombre de dominio local</em></strong> (opcional) - introduzca el nombre de dominio local para su red.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong><em>DNS Relay</em></strong> -
			 cuando está activado DNS Relay, se asignará la dirección IP de LAN del router a los clientes DHCP como su servidor DNS. Todas las solicitudes de DNS que recibe el router se enviarán a los servidores DNS de su ISP. Cuando está desactivado DNS relay, se asignará el servidor DNS del ISP a todos los clientes DHCP del router
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Servidor DHCP</strong><br>
			DHCP son las siglas de Protocolo de configuración de host dinámico. El servidor DHCP asigna las direcciones IP a los dispositivos en la red que las solicitan. Estos dispositivos se deben establecer en &quot;Conseguir automáticamente la dirección IP&quot;. De forma predeterminada, el servidor DHCP está activado en el <?query("/sys/modelname");?>. El grupo de direcciones DHCP contiene el rango de la dirección IP que se asignará automáticamente a los clientes en la red.
		</p>
		<p>
			<strong>Reserva DHCP</strong><br>
			Introduzca manualmente el &quot;Nombre de ordenador&quot;, la &quot;Dirección IP&quot; y la &quot;Dirección MAC&quot; para el PC al que desea que el router asigne estáticamente la misma IP o elija el PC del menú desplegable que muestra los clientes DHCP actuales.
		</p>
		<p>
			<strong><em>Dirección IP de inicio</em></strong> La dirección IP de inicio para la asignación IP del servidor DHCP.<br>
			<strong><em>Dirección IP final</em></strong>  La dirección IP final para la asignación IP del servidor DHCP.<br>
			<strong><em>Tiempo de validez</em></strong> La cantidad de tiempo en minutos para la concesión IP.
		</p>
		<p>
			Los ordenadores de cliente DHCP dinámico conectados a la unidad mostrarán su información en la tabla de cliente DHCP dinámico. La tabla mostrará el Nombre de host, la Dirección IP, la Dirección MAC y el Tiempo de caducidad de la concesión DHCP para cada ordenador cliente.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=33>
		<p>
			<strong><a name=04>Fecha y hora</a></strong>
		</p>
		<p>
			El router utiliza los parámetros de Configuración de la hora para sincronizar los servicios programados y las actividades de registro del sistema. Necesitará establecer la zona horaria correspondiente a su ubicación. La hora se puede establecer manualmente o se puede conectar el dispositivo a un servidor de NTP (Protocolo de hora de red) para recuperar la hora. Asimismo, puede establecer las fechas del horario de verano y el tiempo del sistema se ajustará automáticamente a dichas fechas.
		</p>
		<p>
			<strong><em>Zona horaria</em></strong> - seleccione la zona horaria de la región en la que se encuentra.<br>
			<strong><em>Horario de verano</em></strong> -
			si la región en la que se encuentra respeta el horario de verano, active esta opción y especifique el mes, semana, día y hora de inicio y final de dicho horario de verano.<br>
			<strong><em>Configuración automática de la hora</em></strong> -
			seleccione un servidor de hora D-Link con el que desea que el <?query("/sys/modelname");?> sincronice su hora. El intervalo al que el <?query("/sys/modelname");?> se comunicará con el servidor NTP de D-Link se establece en 7 días.<br>
			<strong><em>Establecer manualmente la fecha y la hora</em></strong> -
			 seleccione esta opción si desea especificar manualmente la hora. Debe especificar el año, el mes, el día, la hora, el minuto y el segundo o puede hacer clic en el botón Copiar los parámetros temporales de su ordenador para copiar la hora del sistema desde el ordenador que se está utilizando para acceder a la interfaz de gestión
		</p>
	</td>
</tr>
<tr><td height=2>&nbsp;</td></tr>
<tr><td height=2>&nbsp;</td></tr>
<tr>
	<td height=44>
		<p>
			<strong><a name=05>Control paterno</a></strong>
		</p>
		<p>
			Junto con la capacidad para filtrar el acceso de los dispositivos a su red y a Internet, el <?query("/sys/modelname");?> se puede configurar también para permitir o denegar el acceso, para los ordenadores en su red, a sitios web inadecuados por nombre de dominio o por palabras clave.
		</p>
		<p>
			<strong>Control paterno</strong><br>
			El control paterno se utiliza para permitir o denegar a los ordenadores en su red el acceso a sitios Web específicos mediante palabras clave o nombres de dominio específicos. Seleccione &quot;ACTIVE el filtrado de sitio web y PERMITA el acceso de los ordenadores ÚNICAMENTE a dichos sitios&quot; para permitir que los ordenadores en su red accedan únicamente a las URL y nombres de dominio especificados. &quot;ACTIVE el filtrado de sitio web y DENIEGUE el acceso de los ordenadores ÚNICAMENTE a dichos sitios&quot; para denegar a los ordenadores en su red el permiso de acceso a las URL y nombres de dominio especificados.
		</p>
		<p>
			<span class="style1">Ejemplo 1:</span><br>
			Si desea bloquear los usuarios de LAN de cualquier sitio Web que contiene una URL relacionada con ventas, necesitará seleccionar &quot;ACTIVE el filtrado de sitio web y DENIEGUE el acceso de los ordenadores ÚNICAMENTE a dichos sitios&quot; y, a continuación, introduzca &quot;ventas&quot; en la lista de Reglas de filtrado de sitio web. A los usuarios de la LAN se les denegará el acceso a los sitios de ese tipo porque contienen la palabra clave en la URL.<br>
			<a href="http://shopping.yahoo.com/">http://shopping.yahoo.com/</a><br>
			<a href="http://shopping.msn.com/">http://shopping.msn.com/</a>
		</p>
		<p>
			<span class="style1">Ejemplo 2:</span><br>
			Si desea que sus hijos accedan únicamente a determinados sitios, elegirá &quot; ACTIVE el filtrado de sitio web y PERMITA el acceso de los ordenadores ÚNICAMENTE a dichos sitios&quot; y, a continuación, introduzca los dominios a los que desea que sus hijos tengan acceso.
		</p>
		<ul>
			<li>Google.com </li>
			<li>Cartoons.com </li>
			<li>Discovery.com </li>
		</ul>
	</td>
</tr>
</table>
