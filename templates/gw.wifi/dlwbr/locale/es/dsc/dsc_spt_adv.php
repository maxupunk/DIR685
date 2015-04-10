<h1>MENÚ DE SOPORTE</h1>
	<table border=0 cellspacing=0 cellpadding=0 width=750 height=1103>
 <tr>
 <td width="750" height=40><font size=4><b>Opciones avanzadas</b></font></td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>

 </tr>
<tr>
	<td height=228>
		<p>
			<a name=05><strong>Direccionamiento de puerto avanzado </strong></a><br>
			La opción Direccionamiento de puerto avanzado permite a los usuarios de Internet acceder a los servicios en su LAN. Esta característica resulta útil para alojar servicios en línea como servidores de FTP, Web o juegos. Para cada entrada, se define un puerto público en el router para el redireccionamiento a una dirección IP de LAN y un puerto de LAN en Internet.
		</p>
		<p>
			Parámetros de Direccionamiento de puerto avanzadobr>
			<strong><em>Nombre</em></strong> -
			Asigne un nombre que signifique algo para usted a un servidor virtual como, por ejemplo, Servidor de Web. Existen varios tipos de servidores virtuales bien conocidos disponibles en la lista desplegable "Nombre de la aplicación". Al seleccionar una de estas entradas se rellenan algunos de los parámetros restantes con los valores estándar para ese tipo de servidor.<br>
			<strong><em>Dirección IP  </em></strong> -
			La dirección IP del sistema en su red interna que proporcionará el servicio virtual como, por ejemplo, 192.168.0.50. Puede seleccionar un ordenador de la lista de clientes DHCP en el menú desplegable "Nombre de ordenador" o puede introducir manualmente la dirección IP del ordenador del servidor.<br>
			<strong><em>Nombre de la aplicación </em></strong> -
			Una lista de aplicaciones conocidas predefinidas entre las que los usuarios pueden elegir para una configuración más rápida.<br>
			<strong><em>Nombre de ordenador</em></strong> -Una lista de clientes DHCP.<br>
			<strong><em>Tipo de tráfico</em></strong> -
			Seleccione el protocolo utilizado por el servicio. Se pueden seleccionar las opciones habituales, UDP, TCP y ambos UDP y TCP, del menú desplegable. Para especificar cualquier otro protocolo, seleccione "Otros" en la lista y, a continuación, introduzca el número de protocolo correspondiente (según lo asignado por el IANA) en el cuadro Protocolo.<br>
			<strong><em>Puerto privado </em></strong> -
			El puerto que se utilizará en su red interna.<br>
			<strong><em>Puerto público </em></strong> -
			El puerto al que se accederá desde Internet.<br>
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
 <td height=64> <strong>Reglas de las aplicaciones <font size=4><b><a name=06></a></b></font> </strong><br>
Algunas aplicaciones requieren varias conexiones como, por ejemplo, los juegos de Internet, la videoconferencia, la telefonía por Internet y otras. Estas aplicaciones tienen dificultades para trabajar a través del NAT (Traducción de direcciones de red). Si necesita ejecutar aplicaciones que requieren varias conexiones, especifique el puerto asociado normalmente con una aplicación en el campo "Puerto de activación", seleccione el tipo de protocolo como TCP (Protocolo de control de transmisión) o UDP (Protocolo de datagramas de usuario) y, a continuación, introduzca  los puertos públicos asociados con el puerto de activación en el campo Puerto de cortafuegos para abrirlos para el tráfico entrante. Ya existen aplicaciones bien conocidas definidas en el menú desplegable Nombre de la aplicación.<br>

<strong><em>Nombre </em></strong> - Este es el nombre que hace referencia a la aplicación. <br>
<strong><em>Puerto de activación </em></strong>-Este es el puerto utilizado para activar la aplicación. Puede ser un puerto único o un rango de puertos. <br>
<strong><em>Tipo de tráfico </em></strong> -  Este es el protocolo utilizado para activar la aplicación. <br>
<strong><em>Puerto de cortafuegos </em></strong> - Este es el número de puerto en el lado de la WAN que se utilizará para acceder a la aplicación. Puede definir un puerto único o un rango de puertos. Puede utilizar una coma para añadir varios puertos o rangos de puertos.<br>
<strong><em>Tipo de tráfico  </em></strong> - Este es el protocolo utilizado para la aplicación. </td>

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
			<a name=07><strong>Control de acceso</strong></a><br>
			Se utilizan filtros para denegar o permitir el acceso de los ordenadores de la LAN a Internet y también a su red. Dentro de su red, se puede configurar la unidad para permitir o denegar a los ordenadores el acceso a Internet utilizando su dirección MAC.
		</p>
		<p>
			<strong>Filtros MAC</strong><br>
			Utilice los filtros MAC para denegar el acceso a Internet a los ordenadores que estén dentro de su red de área local. Puede añadir manualmente una dirección MAC o seleccionar la dirección MAC de la lista de clientes que están conectados actualmente a la unidad.<br>
			Seleccione "ACTIVE el filtrado MAC y PERMITA que los ordenadores con las direcciones MAC enumeradas a continuación accedan a la red"si sólo desea que los ordenadores seleccionados tengan acceso a la red y que el resto de los ordenadores no tengan acceso a la red.<br>
			Seleccione "ACTIVE el filtrado MAC y DENIEGUE el acceso a la red de los ordenadores con las direcciones MAC enumeradas a continuación"si desea que todos los ordenadores tengan acceso a la red excepto los ordenadores incluidos en la lista.<br>
			<strong><em>Dirección MAC </em></strong> -
			La dirección MAC del dispositivo de red que se va a añadir a la lista de filtros MAC.<br>
			<strong><em>Lista de clientes DHCP </em></strong> -
			Los clientes DHCP tendrán su nombre de host en el menú desplegable Nombre de ordenador. Puede seleccionar el ordenador del cliente que desea añadir a la lista de filtros MAC y hacer clic en el botón de flecha. Esto añadirá automáticamente la dirección MAC de dicho ordenador al campo adecuado.
		</p>
		<p>
			Los usuarios pueden utilizar el menú desplegable Siempre para seleccionar un programa definido con anterioridad o hacer clic en el botón Añadir nuevo para añadir un nuevo programa.
		</p>
		<p>
			La casilla de verificación se utiliza para activar o desactivar una entrada concreta.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<a name=08><strong>Cortafuegos y DMZ</strong></a><br>
			La sección Parámetros de cortafuegos contiene la opción para configurar un host DMS.
		</p>
		<p>
			<strong>Activar SPI</strong><br>
			La SPI ("inspección de paquetes de datos", conocida también como "filtrado dinámico de paquetes") ayuda a evitar los ciberataques haciendo el seguimiento de más estados por sesión. Valida que el tráfico que pasa a través de esa sesión cumple los requisitos del protocolo. Cuando el protocolo es TCP, la SPI comprueba que los números de secuencia del paquete están dentro del rango válido para la sesión, desechando los paquetes que no tienen un número de secuencia válido. Independientemente de si la SPI está activada o no, el router siempre realiza el seguimiento de los estados de la conexión TCP y se asegura de que los indicadores del paquete TCP son válidos para el estado actual.
		</p>
		<p>
			<strong>DMZ </strong><br>
			Si tiene un ordenador que no puede ejecutar correctamente aplicaciones de Internet desde detrás del <?query("/sys/modelname");?>, puede permitir que el ordenador tenga acceso a Internet sin restricciones. Introduzca la dirección IP de dicho ordenador como un host DMZ (Zona desmilitarizada) con acceso a Internet sin restricciones. Al añadir un ordenador a la DMZ puede exponer dicho ordenador a una serie de riesgos de seguridad; sólo utilice esta opción como último recurso.
		</p>
		<p>
			<strong>Reglas de cortafuegos</strong><br>
			Las reglas de cortafuegos se utilizan para permitir o denegar el tráfico que entra o sale del router, en función de las direcciones IP de  origen y destino, así como del tipo de tráfico y del puerto en que se ejecutan los datos.<br>
			<strong><em>Nombre</em></strong> - Los usuarios pueden especificar un nombre para la regla de cortafuegos.	<br>
			<strong><em>Acción</em></strong> - Los usuarios pueden elegir entre permitir o denegar el tráfico.<br>
			<strong>Interfaz</strong><br>
			<strong><em>Origen</em></strong> -
			Utilice el menú desplegable <strong>Origen</strong> para seleccionar si el punto de inicio del tráfico que se va a permitir o denegar procede de la LAN o de la interfaz de WAN.<br><br>
			<strong><em>Dest</em></strong> -
			Utilice el menú desplegable <strong>Dest</strong> para seleccionar si el punto final del tráfico que se va a permitir o denegar llega a la LAN o a la interfaz de WAN.<br><br>
			<strong><em>Dirección IP</em></strong> -
			Puede especificar aquí una IP única de origen o destino introduciendo la IP en el cuadro superior
 o bien, introduzca un rango de IP introduciendo la primera IP del rango en el cuadro superior y la última IP del rango en el inferior.<br>
			<strong><em>Protocolo</em></strong> -
			Utilice el menú desplegable <strong>Protocolo</strong> para seleccionar el tipo de tráfico.<br>
			<strong><em>Rango de puerto</em></strong> -
			Introduzca el mismo número de puerto en ambos cuadros para especificar un puerto único o introduzca el primer puerto del rango en el cuadro superior y el último puerto del rango en el inferior para especificar un rango de puertos.<br>
			<strong><em>Programa</em></strong> -
			Utilice el menú desplegable <strong>Siempre</strong> para seleccionar un programa definido con anterioridad o haga clic en el botón <strong>Añadir nuevo</strong>para añadir un nuevo programa.
 </p>
	</div></td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
 <tr>
 <td height=20><p><strong>Opciones avanzadas inalámbricas <a name=09></a></strong></p>

 <p>Las opciones de esta página deben ser cambiadas por usuarios avanzados o si así se lo indica el personal de soporte, ya que pueden afectar negativamente el rendimiento del router si se configuran incorrectamente.</p>
 <p><strong><em>Velocidades de transmisión (TX):  </em></strong> seleccione las velocidades de transferencia básicas en función de los adaptadores inalámbricos en la WLAN (red de área local inalámbrica). </p>
 <p><strong><em>Potencia de transmisión:</em></strong>puede disminuir la potencia de salida del <?query("/sys/modelname");?> seleccionando porcentajes más bajos de los valores de Potencia de transmisión en el menú desplegable. Las opciones son: 100%, 50%, 25% y 12,5%. </p>
 <p><strong><em>Intervalo de emisión de señales: </em></strong> las emisiones de señales son paquetes enviados por un punto de acceso para sincronizar una red inalámbrica. Especifique un intervalo de emisión de señales entre 20 y 1.000. El valor predeterminado se establece en 100 milisegundos.</p>

 <p><strong><em>Umbral RTS:</em></strong> este valor debe permanecer en su valor predeterminado de 2.346. Si encuentra flujos de datos incoherentes, sólo se recomienda realizar modificaciones en el rango de valor entre  1 y 2.346. El valor predeterminado para Umbral RTS se establece en 2.346. </p>
 <p><strong><em>Fragmentación:</em></strong> este valor debe permanecer en su valor predeterminado de 2.346. Si experimenta una tasa elevada de errores de paquete, puede aumentar ligeramente su valor de
 &quot;Fragmentación&quot; dentro del rango de valor de 256 a 2.346. Establecer el valor de fragmentación demasiado bajo puede dar como resultado un rendimiento defectuoso.</p>
 <p><strong><em>Intervalo DTIM:</em></strong> introduzca un valor entre 1 y 255 para el Mensaje de indicación del tráfico de envíos (DTIM). Un DTIM es una cuenta atrás que informa a los clientes de la siguiente ventana para escuchar la transmisión y multidifusión de mensajes. Cuando el punto de acceso tiene mensajes de difusión o multidifusión en memoria para los clientes asociados, envía el siguiente DTIM con un valor de intervalo DTIM. Los clientes AP escuchan la emisión de señales y se abren para recibir los mensajes de difusión y multidifusión. El valor predeterminado para intervalo DTIM se establece en 1. </p>

 <p><strong><em>Tipo de preámbulo:</em></strong>el Tipo de preámbulo define la duración del bloqueo CRC (Comprobación de redundancia cíclica) para la comunicación entre el punto de acceso y los adaptadores inalámbricos itinerantes. Asegúrese de seleccionar el tipo de preámbulo adecuado y haga clic en el botón Aplicar. </p>
 <p><span class="style2">Nota:</span>las áreas de tráfico de red elevado deben utilizar el tipo de preámbulo más corto. La CRC es una técnica habitual para detectar errores de transmisión de datos.</p>
 <p><strong><em>Modo CTS: </em></strong>seleccione Ninguno para desactivar esta característica. Seleccione Automático para forzar al router a necesitar todos los dispositivos inalámbricos en la red para funcionar y realizar el enlace RTS/CTS antes de que se les permita transmitir datos. Seleccione Automático para permitir que el router decida cuándo son necesarios los enlaces RTS/CTS.</p>
<?if(query("/runtime/func/ieee80211n")!="1"){
 echo "<p><strong><em>Modo Sólo 802.11g: </em>active este modo si su red está compuesta únicamente por dispositivos 802.11g. Si tiene clientes inalámbricos 802.11b y 802.11g, desactive este modo.</p> </td>";
}?>

 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=20><p><strong>Red avanzada<a name=10></a></strong></p>

 <p>Esta sección contiene los parámetros que pueden cambiar el modo en que el router maneja ciertos tipos de tráfico. Se recomienda no cambiar ninguno de estos parámetros a menos que ya esté familiarizado con los mismos o que así se lo haya indicado nuestro personal de soporte. </p>

<!--
 <p>Transferencia VPN<br>El dispositivo admite la transferencia VPN (Red privada virtual) para PPTP (Protocolo de tunelación de punto a punto) e IPSec (Seguridad IP). Una vez activada la transferencia VPN, no es necesario crear ninguna entrada de Servidor virtual o Direccionamiento de puerto para que se establezcan correctamente las sesiones VPN de salida. Pueden realizarse varias conexiones VPN a través del dispositivo. Esto resulta útil cuando tiene muchos clientes de VPN en la red de área local.</p>
-->

 <p><strong>UPnP </strong><br>UPnP es la abreviatura de Plug and Play universal, una arquitectura de red que proporciona compatibilidad entre equipos de conexión en red, software y periféricos. El <?query("/sys/modelname");?> es un router compatible con UPnP, lo que significa que funcionará con otros dispositivos o software UPnP. Si no desea utilizar la funcionalidad, se puede desactivar seleccionando &quot;Desactivado&quot;.</p>
 <p><strong>Ping WAN </strong><br>Al Activar Responder al ping WAN, está provocando que la dirección IP de la WAN (Red de área amplia) en el dispositivo responda a los comandos ping enviados por los usuarios de Internet. Enviar solicitudes ping a las direcciones IP de la WAN pública es un método habitual utilizado por los piratas informáticos para comprobar si su dirección IP de WAN es válida.</p>
 <p><strong>Velocidad de puerto WAN </strong><br>Permite seleccionar la velocidad de la interfaz WAN del <?query("/sys/modelname");?>: Elija 100 Mbps, 10 Mbps o 10/100 Mbps automático.</p>

<!--
 <p><strong>Modo de juegos </strong><br>Si tiene dificultades al jugar con juegos en línea o incluso con ciertas aplicaciones que utilizan datos de voz, puede que necesite activar el Modo de juegos para que dichas aplicaciones funcionen correctamente. Cuando no esté jugando o utilizando dichas aplicaciones de voz, se recomienda que el Modo de juegos esté desactivado. </p>
--> 
<?if(query("/runtime/func/dis_multicast_stream")!="1"){
echo " <p><strong>Secuencias de multidifusión</strong><br>Active esta opción para permitir que el tráfico multidifusión pase más eficazmente desde Internet a su red. </p> </td>\n";
}
?>
 </tr>

<?if(query("/runtime/func/dis_multicast_stream")!="1"){
echo "<tr><td height=20>&nbsp;</td></tr>\n";
echo "<tr>\n";
echo "	<td height=20>\n";
echo "		<p>\n";
echo "			<strong>Activar secuencias de multidifusión</strong><br>\n";
echo "			Active esta opción si recibe el tipo de servicio vídeo a petición desde Internet.
El router utiliza el protocolo IGMP para proporcionar soporte para una multidifusión eficiente: transmisión de contenido idéntico, como multimedia, desde un origen hasta una serie de destinatarios. Esta opción debe estar activada si cualquiera de las aplicaciones de la LAN participa en un grupo de multidifusión.  Si tiene una aplicación LAN multimedia que no está recibiendo el contenido según lo previsto, intente activar esta opción.\n";
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
echo "	<td height=99><strong>Enrutamiento </strong><a name=11></a><br>\n";
echo "		La opción Enrutamiento permite definir rutas fijas hacia destinos definidos.<br>\n";
echo "		<strong><em>Activar </em></strong> - Especifica si la entrada estará activada o desactivada.<br>\n";
echo "		<strong><em>Interfaz </em></strong> - Especifica la interfaz, WAN o WAN física, que
  debe utilizar el paquete IP para salir del router cuando se utiliza esta ruta.<br>\n";
echo "		<strong><em>Interfaz (WAN)</em></strong> - Esta es la interfaz para recibir la dirección IP desde el ISP para acceder a Internet.<br>\n";
echo "		<strong><em>IInterfaz (WAN física)</em></strong> - Esta es la interfaz para recibir la dirección IP desde el ISP para acceder a la del ISP.<br>\n";
echo "		<strong><em>Destino </em></strong> - La dirección IP de los paquetes que utilizarán esta ruta.<br>\n";
echo "		<strong><em>Máscara de subred</em></strong> - Unos bits en la máscara especifican los bits de la dirección IP que deben coincidir. <br>\n";
echo "		<strong><em>Puerta de enlace </em></strong> - Especifica el siguiente salto que se debe hacer si se utiliza esta ruta.  Una puerta de enlace de 0.0.0.0 implica que no existe un salto siguiente y que la dirección IP que coincide está conectada directamente al router en la interfaz especificada: WAN o WAN física. \n";
echo " </td>\n";
echo " </tr>\n";
}
?>

 <tr>
 <td height=20>&nbsp;</td>
 </tr>

 </table>
