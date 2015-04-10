<div class="box">
<a name="port_forwarding"><h2>Direccionamiento de puerto</h2></a>
	<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=228>
		<p>
			La opción Direccionamiento de puerto avanzado proporciona a los usuarios de Internet acceso a servicios de su LAN. Esta funcionalidad es útil para alojar servicios on line como Servidores FTP, Web o de juegos. Para cada entrada, defina un puerto público en su router para la redirección a una Dirección IP de LAN interna y a un puerto LAN.
		</p>
		<p>
			Parámetros del Direccionamiento de puerto avanzado<br>
			<strong><em>Nombre</em></strong> -
			Asigne un nombre significativo al servidor virtual, por ejemplo, Servidor Web. Tiene a su disposición varios tipos bien conocidos de servidor virtual en la lista desplegable "Nombre de la aplicación". Si selecciona una de estas entrada asignará valores estándar a algunos de los parámetros restantes para ese tipo de servidor.
			<br>
			<strong><em>Dirección IP </em></strong> -
			La dirección IP del sistema en su red interna que proporcionará el servicio virtual, por ejemplo 192.168.0.50. Puede seleccionar un ordenador de la lista de clientes DHCP en el menú desplegable "Nombre de ordenador", o puede introducir manualmente la dirección IP del ordenador servidor.
			<br>
			<strong><em>Nombre de la aplicación </em></strong> -
			Una lista de aplicaciones comunes predefinidas que los usuarios pueden seleccionar para una configuración más rápida.<br>
			<strong><em>Nombre de ordenador </em></strong> - Una lista de clientes DHCP.<br>
			<strong><em>Tipo de tráfico</em></strong> -
			Seleccione el protocolo utilizado por el servicio. Las opciones comunes -- UDP, TCP y ambas -- se pueden seleccionar desde un menú desplegable.
			<br>
			<strong><em>Puerto privado</em></strong> -
			El puerto que se utilizará en su red interna.<br>
			<strong><em>Puerto público</em></strong> -
			El puerto al que se accederá desde Internet.<br>
		</p>
	</td>
</tr>
 </table>
 </div>
 
 
<div class="box">
<a name="application_rules"><h2>Reglas de las aplicaciones</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=64> 
Algunas aplicaciones requieren múltiples conexiones, como por ejemplo, juegos en Internet, videoconferencia, telefonía sobre Internet y otros. Estas aplicaciones tienen dificultades para trabajar a través del NAT (Traducción de direcciones de red). Si necesitara ejecutar aplicaciones que requieren múltiples conexiones, especifique el puerto que se asocie normalmente con una aplicación en el campo "Puerto de activación", seleccione el tipo de protocolo como TCP (Protocolo de control de transmisión) o UDP (Protocolo de datagramas de usuario), e introduzca los puertos públicos asociados con el puerto de activación en el campo Puerto de cortafuegos para abrirlos para el tráfico entrante. Existen aplicaciones bien definidas en el menú desplegable Nombre de la aplicación.
<br>

<strong><em>Nombre </em></strong> - Este es el nombre de referencia de la aplicación. <br>
<strong><em>Puerto de activación </em></strong>- Este es el puerto utilizado para activar la aplicación. Puede ser un puerto único o un rango de puertos. <br>
<strong><em>Tipo de tráfico </em></strong> - Este es el protocolo utilizado para activar la aplicación. <br>
<strong><em>Puerto de cortafuegos </em></strong> - Este es el número de puerto en el lado WAN que se utilizará para acceder a la aplicación. Puede definir un puerto único o un rango de puertos. Puede utilizar una coma para añadir múltiples puertos o rangos de puertos.<br>
<strong><em>Tipo de tráfico </em></strong> - Este es el protocolo utilizado para la aplicación. </td>

 </tr>
 </table>
 </div>
 
 
<div class="box">
<a name="qos_engine"><h2>Motor de QoS</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
<td height=64>
		<p>
			Este Smart QoS mejora la calidad o el streaming de VoIP asegurando la priorización de su tráfico de VoIP o de streaming con respecto a otro tráfico de red, como por ejemplo FTP o Web. Para lograr el mejor rendimiento, marque la opción "lag eliminated" para establecer automáticamente la prioridad de sus aplicaciones.
			<br>
		</p>
</td>
</tr>
</table>
</div>
 
 
<div class="box">
<a name="access_control"><h2>Filtro de red</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=99>
		<p>
			Los filtros se utilizan para denegar o permitir a ordenadores LAN el acceso a Internet y también a su red. En su red, la unidad se puede configurar para permitir o denegar el acceso a Internet a ordenadores utilizando sus direcciones MAC.
		</p>
		<p>
			<strong>Filtros MAC</strong><br>
			Utilice Filtros MAC para denegar a los ordenadores de la red de área local el acceso a Internet. Puede añadir manualmente una dirección MAC o seleccionar la dirección MAC de la lista de clientes que están conectados actualmente a la unidad.
			<br>
			Seleccione "Activar Filtrado MAC y PERMITIR a los ordenadores con direcciones MAC incluidas a continuación, acceder a la red" si sólo desea que tengan acceso a la red los ordenadores seleccionados y no todos los ordenadores.
			<br>
			Seleccione "Activar Filtrado MAC y DENEGAR a los ordenadores con direcciones MAC incluidas a continuación, acceder a la red" si desea que todos los ordenadores tengan acceso a la red excepto aquellos ordenadores de la lista.
			<br>
			<strong><em>Dirección MAC</em></strong> -
			La dirección MAC del dispositivo de red que se añadirá a la Lista de filtros MAC.<br>
			<strong><em>Lista de clientes DHCP</em></strong> -
			Los clientes DHCP tendrán sus nombres de host listados en el menú desplegable Nombre de ordenador. Puede seleccionar el ordenador cliente que desea añadir a la Lista de Filtros MAC y hacer clic en el botón de flecha. Esto añadirá automáticamente la dirección MAC de ese ordenador en el campo apropiado.
		</p>
		<p>
			Los usuarios pueden utilizar el menú desplegable <strong>Siempre</strong> para seleccionar un programa definido previamente o hacer clic en el botón <strong>Añadir nuevo</strong> para añadir un nuevo programa.
		</p>
		<p>
			El cuadro de selección se utiliza para activar o desactivar una entrada particular.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="parental_control"><h2>Filtro de sitio web</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=44>
		<p>
			Junto con la capacidad para filtrar dispositivos que accedan a su red y a Internet, el <?query("/sys/modelname");?> también se puede configurar para permitir o denegar el acceso, para los ordenadores de su red, a sitios web inadecuados utilizando un nombre de dominio o palabras clave.
		</p>
		<p>
			<strong>Control paterno</strong><br>
			El control paterno se utiliza para permitir o denegar a los ordenadores de su red acceder a sitios web específicos utilizando palabras clave o Nombres de dominio específicos. Seleccione "Activar Filtrado de sitio web y PERMITIR a los ordenadores acceder a SÓLO estos sitios" para permitir únicamente a los ordenadores de su red acceder a los Nombres de dominio o URLs especificados. "Activar Filtrado de sitio web y DENEGAR a los ordenadores acceder a SÓLO estos sitios" para denegar a los ordenadores de su red acceder a los Nombres de dominio o URLs especificados.
		</p>
		<p>
			<span class="style1">Ejemplo 1:</span><br>
			Si deseara bloquear a usuarios LAN cualquier sitio que contenga una URL asociada con compras, necesitaría seleccionar "Activar el filtrado de sitio web y DENEGAR a los ordenadores acceder a SÓLO estos sitios" y a continuación introducir "compras" en la lista de Reglas de filtrado de sitio web. A los usuarios LAN se les denegará el acceso a estos sitios porque contienen la palabra clave en la URL.
			<br>
			<a href="http://www.yahoo.com/shopping/stores.html">http://www.yahoo.com/shopping/stores.html</a><br>
			<a href="http://www.msn.com/search/shopping-spree.html">http://www.msn.com/search/shopping-spree.html</a>
		</p>
		<p>
			<span class="style1">Ejemplo 2:</span><br>
			Si desea que sus hijos sólo accedieran a sitios particulares, entonces tendría que seleccionar "Activar Filtrado de sitio web y PERMITIR a los ordenadores acceder SÓLO a estos sitios" y a continuación introducir los dominios a los que quiera que sus hijos tengan acceso.
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
<a name="firewall_dmz"><h2>Parámetros del cortafuegos</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			La sección Parámetros del cortafuegos contiene una opción para configurar un Host DMZ.
		</p>
		<p>
			<strong>Activar SPI</strong><br>
			SPI ("inspección de paquetes de estado" también conocido como "filtrado dinámico de paquetes") ayuda a evitar ataques por Internet haciendo el seguimiento de más estados por sesión. Esto valida que el tráfico que pasa a través de esa sesión esté conforme con el protocolo. Cuando el protocolo sea TCP, SPI comprueba que los números de secuencia de los paquetes estén dentro del rango válido para la sesión, descartando aquellos paquetes que no tengan números de secuencia válidos. Ya esté activado o no SPI, el router siempre hace el seguimiento de los estados de conexión TCP y asegura que los indicadores de cada paquete TCP sean válidos para el estado actual.
		</p>
		<p>
			<strong>DMZ </strong><br>
			Si tuviera un ordenador que no pudiera ejecutar aplicaciones de Internet adecuadamente desde detrás del <?query("/sys/modelname");?>, entonces puede permitir al ordenador tener acceso sin restricción a Internet. Introduzca la dirección IP de ese ordenador como un host DMZ (Zona desmilitarizada) con acceso sin restricción a Internet. Si añade un cliente al DMZ, podría exponer a ese ordenador a una gran variedad de riesgos de seguridad, por lo que debe utilizar únicamente esta opción como último recurso.
		</p>
		<p>
			<strong>Reglas de cortafuegos</strong><br>
			Las Reglas de cortafuegos se utilizan para permitir o impedir que el tráfico entre o salga del router en función de las direcciones IP origen y destino además del tipo de tráfico y el puerto específico por el que pasan los datos.
			<br>
			<strong><em>Nombre</em></strong> - Los usuarios pueden especificar un nombre para una Regla de cortafuegos.<br>
			<strong><em>Acción</em></strong> - Los usuarios pueden decidir permitir o denegar el tráfico.<br>
			<strong>Interfaz</strong><br>
			<strong><em>Origen</em></strong> -
			Utilice el menú desplegable <strong>Origen</strong> para seleccionar si el punto de inicio del tráfico que se permitirá o denegará procede de la interfaz LAN o WAN.
			<br>
			<strong><em>Destino</em></strong> -
			Utilice el menú desplegable <strong>Destino</strong> para seleccionar si el punto final del tráfico que se permitirá o denegará está llegando a la interfaz LAN o WAN.
			<br>
			<strong><em>Dirección IP</em></strong> -
			Aquí puede especificar una única dirección IP origen o destino introduciendo la dirección IP en el cuadro superior o introducir un rango de direcciones IP colocando la primera dirección IP del rango en el cuadro superior y la última dirección IP del rango en el cuadro de la parte inferior.
			<br>
			<strong><em>Protocolo</em></strong> -
			Utilice el menú desplegable <strong>Protocolo</strong> para seleccionar el tipo de tráfico.<br>
			<strong><em>Rango de puertos</em></strong> -
			Introduzca el mismo número de puerto en ambos cuadros para especificar un único puerto o introduzca el primer puerto del rango en el cuadro superior y el último puerto en el inferior para especificar un rango de puertos.
			<br>
			<strong><em>Programa</em></strong> -
			Utilice el menú desplegable <strong>Siempre</strong> para seleccionar un programa definido previamente o haga clic en el botón <strong>Añadir nuevo</strong> para añadir un nuevo programa.
 </p>
</td>
</tr>
</table>
</div>


<div class="box">
<a name="routing"><h2>Enrutamiento</h2></a>
<table>
<?if(query("/runtime/func/dis_routing")!="1"){
echo "<tr>\n";
echo "	<td height=99>\n";
echo "		La opción Enrutamiento le permite definir rutas estáticas para destinos específicos.<br>\n";
echo "		<strong><em>Activar </em></strong> - Especifica si la entrada estará activada o desactivada.<br>\n";
echo "		<strong><em>Interfaz </em></strong> - Especifica la interfaz -- WAN o WAN física -- \n";
echo "		que el paquete IP debe utilizar para salir del router, cuando se utilice este router.<br>\n";
echo "		<strong><em>Interfaz (WAN)</em></strong> - Esta es la interfaz utilizada para\n";
echo "		recibir la Dirección IP del ISP para acceder a Internet.<br>\n";
echo "		<strong><em>Interfaz (WAN física)</em></strong> - Esta es la interfaz\n";
echo "		utilizada para recibir la Dirección IP del ISP para acceder a Internet.<br>\n";
echo "		<strong><em>Destino </em></strong> - La dirección IP de paquetes que tomará esta ruta.<br>\n";
echo "		<strong><em>Máscara de subred </em></strong> - Un bit en la máscara que especifica qué bits\n";
echo "		de la dirección IP deben coincidir. <br>\n";
echo "		<strong><em>Puerta de enlace </em></strong> - Especifica el siguiente punto de conexión al\n";
echo "		que se deberá acceder si se utilizara esta ruta. Una puerta de enlace de 0.0.0.0 implica que\n";
echo "		no hay un salto siguiente, y que la dirección IP que coincide está directamente conectada al router en la interfaz especificada: WAN o WAN física. \n";
echo " </td>\n";
echo " </tr>\n";
}
?>
</table>
</div>


<div class="box">
<a name="advanced_wireless"><h2>Opciones avanzadas inalámbricas</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=20>

 <p>Sólo usuarios avanzados pueden modificar las opciones de esta página o usted mismo si estuviera guiado por uno de los componentes de nuestro personal de soporte, ya que esto puede afectar negativamente al rendimiento de su router si lo configurara incorrectamente.
 </p>
 <p><strong><em>Potencia de transmisión - </em></strong>Puede reducir la potencia de salida del <?query("/sys/modelname");?> seleccionando un porcentaje menor de valores de la Potencia de transmisión del menú desplegable. Su opciones son: 100%, 50%, 25%, y 12,5%. </p>
 <p><strong><em>Intervalo de emisión de señales - </em></strong> Las emisiones de señales son paquetes enviados por un Punto de acceso para la sincronización con la red inalámbrica. Especifique un valor del intervalo de emisión de señales entre 20 y 1000. El valor predeterminado se establece en 100 milisegundos. </p>

 <p><strong><em>Umbral RTS - </em></strong> Este valor debe mantenerse como su parámetro predeterminado de 2346. Si detectara un flujo de datos inconsistente, sólo se recomiendan modificaciones menores del rango de valores entre 256 y 2346. El valor predeterminado para Umbral RTS se establece en 2346. </p>
 <p><strong><em>Fragmentación - </em></strong> Este valor debe mantenerse como su parámetro predeterminado de 2346. Si detectara una tasa de error de paquetes elevada, podría aumentar ligeramente su valor de "Fragmentación" dentro del rango de valores que se encuentra entre 1500 y 2346. Si el valor de Fragmentación fuera demasiado bajo, generaría un rendimiento deficiente. </p>
 <p><strong><em>Intervalo DTIM - </em></strong> Introduzca un valor entre 1 y 255 para el Mensaje de indicación del tráfico de envíos (DTIM). Un DTIM es una cuenta atrás que informa a los clientes de la siguiente ventana para escuchar la transmisión y multidifusión de mensajes. Cuando el Punto de acceso tiene mensajes de difusión o multidifusión en memoria para los clientes asociados, envía el siguiente DTIM con un valor de intervalo DTIM. Los clientes AP detectan la emisión de señales y se abren para recibir los mensajes de difusión y multidifusión. El valor predeterminado para Intervalo DTIM se establece en 1. </p>

 <p><strong><em>Tipo de preámbulo - </em></strong> El tipo de preámbulo define la longitud del bloque CRC (Comprobación de redundancia cíclica) para la comunicación entre el Punto de acceso y los adaptadores inalámbricos de roaming. Asegúrese de seleccionar el tipo de preámbulo apropiado y haga clic en el botón Aplicar. </p>
 <p><span class="style2">Nota: </span>Las áreas de tráfico de red elevado deben utilizar el tipo de preámbulo más corto. El CRC es una técnica común para detectar errores de transmisión de datos.</p>
 <p><strong><em>Modo CTS - </em></strong>Seleccione Ninguno para desactivar esta funcionalidad. Seleccione Siempre para forzar al router a requerir que cada dispositivo inalámbrico de la red realice un enlace RTS/CTS antes de que se les permita transmitir datos. Seleccione Auto para permitir al router decidir cuándo son necesarios los enlaces RTS/CTS. </p>
<?if(query("/runtime/func/ieee80211n")!="1"){
 echo "<p><strong><em>802.11g Only Mode - </em></strong>Enable this mode if your network is made up of purely 802.11g devices. If you have both 802.11b and 802.11g wireless clients, disable this mode. </p> </td>";
}?>
 </tr>
 </tr>
 </table>
 </div>
 
 
<div class="box">
<a name="advanced_network"><h2>Red avanzada</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=20>

 <p>Esta sección contiene parámetros que pueden cambiar la forma en la que el router maneja ciertos tipos de tráfico. Recomendamos que no cambie ninguno de estos parámetros a menos que ya esté familiarizado con ellos o que uno de los componentes de nuestro personal de soporte le haya dado instrucciones para modificarlos.
 </p>

<!--
 <p><strong>VPN Passthrough </strong><br>The device supports VPN (Virtual Private Network) passthrough for PPTP (Point-to-Point Tunneling Protocol) and IPSec (IP Security). Once VPN passthrough is enabled, there is no need to create any Virtual Server or Port Forwarding entries in order for outbound VPN sessions to be established properly. Multiple VPN connections can be made through the device. This is useful when you have many VPN clients on the Local Area Network. </p>
-->

 <p><strong>UPnP </strong><br>UPnP es la abreviatura de Plug and Play universal, una arquitectura de red que proporciona compatibilidad entre equipos de conexión en red, software y periféricos. El <?query("/sys/modelname");?> es un router activado UPnP, lo que significa que funcionará con otros dispositivos/software UPnP. Si no deseara utilizar la función UPnP, ésta se puede desactivar seleccionando "Desactivado".
 </p>
 <p><strong>Ping WAN </strong><br>Cuando activa la respuesta Ping WAN, estará provocando que la dirección IP de WAN pública (Red de área amplia) en el dispositivo, responda a los comandos ping enviados por los usuarios de Internet. El ping de las direcciones IP de WAN pública es un método habitual utilizado por los piratas informáticos para probar si su dirección IP de WAN es válida.
 </p>
 <p><strong>Velocidad de puerto WAN </strong><br>Esto le permite seleccionar la velocidad de la interfaz WAN del <?query("/sys/modelname");?>: Seleccione 100 Mbps, 10 Mbps, o 10/100/1000 Mbps Auto.
 </p>

<!--
 <p><strong>Gaming Mode </strong><br>If you are experiencing difficulties when playing online games or even certain applications that use voice data, you may need to enable Gaming Mode in order for these applications to work correctly. When not playing games or using these voice applications, it is recommended that Gaming Mode is disabled. </p>
--> 

<?if(query("/runtime/func/dis_multicast_stream")!="1"){
echo " <p><strong>Secuencias de multidifusión</strong><br>Active esta opción para permitir que el tráfico multidifusión pase más eficientemente desde Internet a su red. </p> </td>\n";
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
<a name="guest_zone"><h2>Zona de invitados</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			Selección de zona de invitados<br>
			La selección ayuda a definir la escala de la zona de invitados.<br>
			<strong><em>Activar zona de invitados</em></strong>  - Especifica si la Zona de invitados se activará o desactivará.<br>
			<strong><em>Incluir puerto LAN</em></strong>  - Especifica el puerto LAN que se incluirá en la Zona de invitados.<br>
			<strong><em>Incluir inalámbrico</em></strong>  - Especifica si se utiliza una zona adicional para la Zona de invitados.<br>
			<strong><em>Nombre de la red inalámbrica</em></strong> -  Proporciona un nombre para la red inalámbrica de la Zona de invitados. <br>
		</p>
		<p>
			<strong><em>Modo de seguridad inalámbrica</em></strong><br>
			Es importante hacer más segura su red inalámbrica ya que se utiliza para proteger la integridad de la información que se transmite a través de la red inalámbrica. El <?query("/sys/modelname");?> admite 4 tipos de seguridad inalámbrica; WEP, sólo WPA, sólo WPA2 y WPA/WPA2 (detección automática)
			<br>
		</p>
		<p>
			<strong><em>WEP</em></strong><br>
			El protocolo equivalente con cables (WEP) es un protocolo de seguridad inalámbrico para las redes de área local inalámbricas (WLAN). WEP proporciona seguridad mediante el cifrado de los datos que se envía a través de la WLAN. El <?query("/sys/modelname");?> admite 2 niveles de cifrado WEP: 64 bits y 128 bits. El protocolo WEP está desactivado de manera predeterminada. La configuración de WEP se puede cambiar para adaptarla a una red inalámbrica existente o para personalizar su red inalámbrica.
		 <br>
		</p>
		<p>
			<strong><em>Autenticación</em></strong> - La autenticación es un proceso por el que el <?query("/sys/modelname");?> verifica la identidad de un dispositivo de red que está intentando unirse a la red inalámbrica. Al utilizar WEP, existen dos tipos de autenticación para este dispositivo.
			 <br>
			<strong><em>Sistema abierto</em></strong> -Seleccione esta opción para permitir que todos los dispositivos se comuniquen con el <?query("/sys/modelname");?> antes de que se les pida la clave de cifrado necesaria para acceder a la red. <br>
			<strong><em>Clave compartida </em></strong> - Seleccione esta opción para solicitar a cualquier dispositivo inalámbrico que intente comunicarse con el <?query("/sys/modelname");?> la clave de cifrado necesaria para acceder a la red antes de que se les permita comunicarse con el <?query("/sys/modelname");?>. <br>
			<strong><em>Cifrado WEP</em></strong> - Seleccione el nivel de Cifrado WEP que le gustaría utilizar en su red. Los dos niveles de cifrado WEP admitidos son 64 bits y 128 bits.<br>
			<strong><em>Tipo de clave </em></strong> - Los tipos de clave que admite el <?query("/sys/modelname");?> son HEX (hexadecimal) y ASCII (American Standard Code for Information Interchange). El tipo de clave se puede cambiar para adaptarla a una red inalámbrica existente o para personalizar su red inalámbrica. <br>
			<strong><em>Claves</em></strong> - Las claves 1-4 permiten cambiar fácilmente la configuración de la codificación inalámbrica para mantener una red segura. Simplemente, seleccione la clave específica que se debe utilizar para codificar los datos inalámbricos en la red. <br>
		</p>
		<p>
			<strong><em>WPA-Personal</em></strong><br>
			El acceso protegido Wi-Fi autoriza y autentifica usuarios para acceder a la red inalámbrica. WPA utiliza una seguridad más potente que WEP y se basa en una clave que cambia automáticamente a intervalos regulares.
		 <br>
		</p>
		<p>
			<strong><em>Tipo de cifrado</em></strong> - El <?query("/sys/modelname");?> admite dos tipos de cifrado diferentes cuando se utiliza WPA como tipo de seguridad.. Estas dos opciones son TKIP (Protocolo de integridad de clave temporal) y AES (Estándar de cifrado avanzado). <br>
			<strong><em>PSK/EAP</em></strong> -Cuando está seleccionado PSK, los clientes inalámbricos deberán proporcionar una frase secreta para la autenticación. Cuando está seleccionado EAP, necesitará disponer de un servidor RADIUS en la red que le permitirá manejar la autenticación de todos sus clientes inalámbricos. <br>
			<strong><em>Frase secreta </em></strong> - Es lo que necesitarán todos sus clientes inalámbricos para comunicarse con su <?query("/sys/modelname");?>, cuando está seleccionado PSK. Introduzca de 8 a 63 caracteres alfanuméricos. Asegúrese de escribir la frase secreta ya que necesitará introducirla en cualquiera de los dispositivos inalámbricos que intente añadir a la red. <br>
			<strong><em>802.1X </em></strong> - Esto implica que la autenticación WPA se utiliza junto con un servidor RADIUS, que debe estar presente en la red. Introduzca la dirección IP, el puerto y el secreto compartido para los que está configurado el servidor RADIUS. También tiene la opción de introducir información para un segundo servidor RADIUS, en el caso de que su red disponga de dos, que esté utilizando para autentificar clientes inalámbricos. <br>
		</p>
		<p>
			<strong><em>WPA2</em></strong><br>
			El acceso protegido Wi-Fi 2 autoriza y autentifica usuarios para acceder a la red inalámbrica. WPA2 utiliza una seguridad más potente que WEP y se basa en una clave que cambia automáticamente a intervalos regulares.
		 <br>
		</p>
		<p>
			<strong><em>Tipo de cifrado</em></strong> - El <?query("/sys/modelname");?> admite dos tipos de cifrado diferentes cuando se utiliza WPA como tipo de seguridad.. Estas dos opciones son TKIP (Protocolo de integridad de clave temporal) y AES (Estándar de cifrado avanzado). <br>
			<strong><em>PSK/EAP</em></strong> - Cuando está seleccionado PSK, los clientes inalámbricos deberán proporcionar una frase secreta para la autenticación. Cuando está seleccionado EAP, necesitará disponer de un servidor RADIUS en la red que le permitirá manejar la autenticación de todos sus clientes inalámbricos. <br>
			<strong><em>Frase secreta</em></strong> - Es lo que necesitarán todos sus clientes inalámbricos para comunicarse con su <?query("/sys/modelname");?>, cuando está seleccionado PSK. Introduzca de 8 a 63 caracteres alfanuméricos. Asegúrese de escribir la frase secreta ya que necesitará introducirla en cualquiera de los dispositivos inalámbricos que intente añadir a la red. <br>
			<strong><em>802.1X </em></strong> - Esto implica que la autenticación WPA2 se utiliza junto con un servidor RADIUS, que debe estar presente en la red. Introduzca la dirección IP, el puerto y el secreto compartido para los que está configurado el servidor RADIUS. También tiene la opción de introducir información para un segundo servidor RADIUS, en el caso de que su red disponga de dos, que esté utilizando para autentificar clientes inalámbricos. <br>
		</p>
		<p>
			<strong><em>WPA2-Auto</em></strong> <br>
			Esta opción permite al <?query("/sys/modelname");?> tener clientes WPA2 y WPA conectados a él simultáneamente.
			<br>
		</p>
		<p>
			<strong><em>Configuración de la LAN para la Zona de invitados</em></strong><br> 
			Estos son los parámetros de la interfaz de la LAN (Red de área local) de la Zona de invitados para el dispositivo. A estos parámetros se les hace referencia como "parámetros privados". Puede modificar la dirección IP si fuera necesario. La dirección IP es privada para su red interna y no se puede ver en Internet. La dirección IP predeterminada es 192.168.1.1 con una máscara de subred de 255.255.255.0.
			<br>
		</p>
		<p>
			<strong><em>Dirección IP</em></strong> - La dirección IP predeterminada del <?query("/sys/modelname");?> es 192.168.1.1. <br>
			<strong><em>Máscara de subred</em></strong> - La Máscara de subred predeterminada de <?query("/sys/modelname");?> es 255.255.255.0. <br>
		</p>
		<p>
			<strong><em>Activar Aislamiento de clientes en la zona de invitados</em></strong> : <br>
			Active la función para evitar que un cliente invitado acceda a otros clientes en la Zona de invitados. El cliente invitado puede acceder únicamente a Internet.
		 <br>
		</p>
		<p>
			<strong><em>Activar el enrutamiento entre zonas</em></strong> : <br>
			Utilice esta sección para permitir el enrutamiento entre la zona de host y la zona de invitados; los clientes invitados no pueden acceder a los datos de clientes de host si la función no está habilitada.
			 <br>
		</p>
		<p>
			<strong><em>Servidor DHCP para la Zona de invitados</em></strong> <br>
			DHCP son las siglas en inglés de Protocolo de configuración de host dinámico. El servidor DHCP asigna direcciones IP a los dispositivos de la red que lo solicitan. Los dispositivos deben haberse establecido como "Obtener la dirección IP automáticamente". El servidor DHCP está activado de forma predeterminada en el <?query("/sys/modelname");?>. El grupo de direcciones DHCP contiene el rango de la dirección IP que se asignará automáticamente a los clientes de la red.
			<br>
		</p>
		<p>
			<strong><em>Dirección IP inicial</em></strong> - La dirección IP inicial para la asignación IP del servidor DHCP. <br>
			<strong><em>Dirección IP final</em></strong> -La dirección IP final para la asignación IP del servidor DHCP. <br>
			<strong><em>Tiempo de validez</em></strong> -El lapso temporal, en minutos, de validez de la IP. Los ordenadores de clientes DHCP dinámicos conectados a la unidad verán su información en la tabla de clientes DHCP dinámicos. Esta tabla muestra el nombre de host, la dirección IP, la dirección MAC y el tiempo de caducidad de la concesión DHCP para cada ordenador de cliente.
			 <br>
		</p>
</td>
</tr>
</table>
</div>
 
<div class="box">
<a name="wake_on_lan"><h2>Wake on LAN</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			La función Wake on LAN se puede utilizar para activar remotamente un PC conectado en el lado de la LAN del router. Especifique el puerto UDP que utilizará el paquete mágico Wake on LAN para evitar que el router piense que la petición de Wake on LAN es un ataque hostil y la bloquee.
			<br>
			<br>
			<strong><em>Puerto UDP</em></strong> - 
			Este es el único puerto que el <?query("/sys/modelname");?> utilizará para escuchar los paquetes mágicos que activarán el PC.<br>
			<strong><em>Interfaz</em></strong> - 
			(Este parámetro no se puede modificar actualmente. Podría ser posible modificar este parámetros en versiones posteriores del firmware).<br>		
		</p>
	</td>
</tr>
</table>
</div>
