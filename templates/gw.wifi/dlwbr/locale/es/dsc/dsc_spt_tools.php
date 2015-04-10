<h1>MENÚ DE SOPORTE</h1>
<table border=0 cellspacing=0 cellpadding=0 width=750>
<tr>
<td height=2><b><font size=4>Mantenimiento</font></b></td>
</tr>
<tr>
<td height=16><p><br>
</td>
</tr>
<tr>
	<td height=20>
		<strong>Administración del dispositivo</strong><a name=12></a><br>
		<p>
			<strong><em>Nombre de inicio de sesión del administrador</em></strong> -
			 introduzca el nombre que se utilizará para iniciar sesión en el router con acceso de administrador.
		</p>
		<p>
			<strong><em>Contraseña del administrador</em></strong> -
			introduzca y confirme la contraseña que utilizará la cuenta admin para acceder a la interfaz de gestión del router.
		</p>
		<p>
			<strong>Gestión remota</strong><br>
			La gestión remota permite configurar el dispositivo a través del puerto de WAN (Red de área amplia) desde Internet utilizando un explorador de web. Sigue siendo necesario un nombre de usuario y una contraseña para acceder a la interfaz de gestión del router.<br>
			<strong><em>IP permitida para acceder:</em></strong> -
			esta opción permite a los usuarios especificar una dirección IP concreta desde Internet para que se les permita acceder al router de forma remota. Este campo se deja en blanco de forma predeterminada, lo que significa que cualquier dirección IP de Internet puede acceder de forma remota al router una vez activada la gestión remota.<br>
			<strong><em>Puerto</em></strong> - seleccione el puerto que se utilizará para acceder al <?query("/sys/modelname");?>.
		</p>
		<p>
			<strong><em>Ejemplo:  </em></strong><br>
			http://x.x.x.x:8080, donde x.x.x.x es la dirección IP de WAN del <?query("/sys/modelname");?> y 8080 es el puerto utilizado para la interfaz de gestión de web. 
		</p>
	</td>
</tr>
<tr><td height=10>&nbsp;</td></tr>
<tr><td height=10>&nbsp;</td></tr>
<tr>
	<td height=40>
		<a name=14><strong>Guardar y restablecer</strong></a><br>
		Se pueden guardar los parámetros del sistema actual como un archivo en la unidad de disco duro local. El archivo guardado o cualquier otro archivo de parámetros guardado creado por el dispositivo, se puede cargar en la unidad. Para volver a cargar un archivo de parámetros del sistema, haga clic en Examinar para buscar en el disco duro local el archivo que se va a utilizar. También se puede volver a restablecer el dispositivo en los parámetros predeterminados de fábrica haciendo clic en Restablecer dispositivo. Sólo utilice la caracteristica de restablecer si es necesario. Esto borrará los parámetros guardados con anterioridad para la unidad. Asegúrese de guardar los parámetros del sistema antes de realizar un restablecimiento de los valores de fábrica.<br>
		<strong><em>Guardar</em></strong> - haga clic en este botón para guardar el archivo de configuración del router.<br>
		<strong><em>Examinar</em></strong> -
		 haga clic en Examinar para localizar un archivo de configuración guardado y, a continuación, haga clic en Cargar para aplicar estos parámetros guardados en el router.<br>
		<strong><em>Restablecer dispositivo</em></strong> -
		 haga clic en este botón para restablecer el router en sus parámetros predeterminados de fábrica.
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=51>
		<b>Actualización del firmware</b><a name=15></a><br> 
		Puede actualizar el firmware del dispositivo utilizando esta herramienta. Asegúrese de que el firmware que desea utilizar está guardado en el disco duro local del ordenador. Haga clic en Examinar para buscar en el disco duro local el firmware que se va a utilizar para la actualización. La actualización de firmware no cambiará ninguno de sus parámetros del sistema, aunque se recomienda guardar los parámetros del sistema antes de realizar una actualización de firmware. Consulte el sitio de soporte de D-Link para obtener actualizaciones de firmware o haga clic en el botón Comprobar ahora para que el router compruebe automáticamente el nuevo firmware. 
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=2>
		<p>
			<strong>Configuración de DDNS </strong><a name=16></a><br>
			El DNS (Servicio de nombre de dominio) dinámico es un método para mantener un nombre de dominio vinculado a una dirección IP que cambia (dinámica). Con la mayoría de las conexionoes por cable y DSL, se le asigna una dirección de IP dinámica y dicha dirección sólo se utiliza mientras dura dicha conexión específica. Con el <?query("/sys/modelname");?>, puede configurar su servicio DDNS y el router actualizará automáticamente el servidor DDNS cada vez que reciba una nueva dirección IP de WAN.<br>
			<strong><em>Dirección del servidor:</em></strong> -  elija su proveedor de DDNS del menú desplegable.<br>
			<strong><em>Nombre de host </em></strong> - introduzca el nombre de host que ha registrado con su proveedor de servicios DDNS.<br>
			<strong><em>Nombre de usuario</em></strong> -  introduzca el nombre de usuario para su cuenta DDNS..<br>
			<strong><em>Contraseña</em></strong> -  introduzca la contraseña para su cuenta DDNS.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height="197">
		<p>
			<strong>Comprobación del sistema</strong><a name=17></a><br>
			Esta herramienta se puede utilizar para comprobar la conexión física en las interfaces de LAN y de WAN. Es una característica avanzada que integra un probador de cable de LAN en cada puerto Ethernet del router. A través de la interfaz gráfica de usuario (GUI), se puede utilizar Prueba de cable para diagnosticar de forma remota y notificar los fallos de cable como aperturas, cortos, cambios y falta de coincidencia de impedancia. Esta característica reduce considerablemente las llamadas y las respuestas del servicio técnico permitiendo a los usuarios solucionar fácilmente sus problemas con las conexiones de cable.
		</p>
		<p>
			<strong>Prueba de Ping</strong><br>
			Esta práctica utilidad de diagnostico se puede utilizar para comprobar si un ordenador está en Internet. Envía paquetes ping y escucha las respuestas del host específico. Introduzca un nombre de host o la dirección IP a la que desea enviar una solicitud ping (Packet Internet Groper) y haga clic en Ping. El estado de su intento de Ping se mostrará en el cuadro Resultado de Ping.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td>
		<p>
			<strong>Programas<a name=18></a></strong></p>
			Esta página se utiliza para configurar programas globales para el router. Una vez definidos, estos programas se pueden aplicar después a las características del router que admita la programación.<br>
			<strong><em>Nombre</em></strong> - el nombre del programa que se está definiendo.<br>
			<strong><em>Día(s)</em></strong> -
			seleccione un día, un intervalo de días o seleccione la casilla de comprobación Toda la semana para que este programa se aplique cada día.<br>
			<strong><em>Todo el día, 24 horas</em></strong> -
			marque esta casilla para que el programa esté activo las 24 horas en los días especificados.<br>
			<strong><em>Hora de inicio</em></strong> -
			 seleccione la hora a la que desea que el programa que se está definiendo se active.<br>
			<strong><em>Hora final</em></strong> -
			seleccione la hora a la que desea que el programa que se está definiendo se desactive.<br>
			<strong><em>Lista de reglas de programa</em></strong> -
			muestra todos los programas que se han definido.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td>
		<p>
			<strong>Parámetros de registro</strong><strong><a name=19></a></strong><br>
			Puede guardar el archivo de registro en un disco local que se puede utilizar después para enviarlo al administrador de una red para solucionar el problema.<br>
			<strong><em>Guardar</em></strong> - haga clic en este botón para guardar las entradas de registro en un archivo de texto.<br>
			<strong><em>Tipo de registro</em></strong> - seleccione el tipo de información que desea que registre el <?query("/sys/modelname");?>.
		</p>
	</td>
</tr>

</table>
						   
