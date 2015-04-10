<div class="box">
<a name="admin"><h2>Administrador</h2></a>
<table border=0 cellspacing=0 cellpadding=0>

<tr>
	<td height=20>
		
		<p>
			<strong><em>Nombre de inicio de sesión del administrador</em></strong> -
			Introduzca el nombre que se utilizará para iniciar sesión con el acceso de Administrador.
		</p>
		<p>
			<strong><em>Contraseña del administrador</em></strong> -
			Introduzca y confirme la contraseña que la cuenta <strong>administrador</strong> utilizará para acceder a la interfaz de gestión del router.
		</p>
		<p>
			<strong>Gestión remota</strong><br>
			Gestión remota permitirá configurar el dispositivo a través del puerto WAN (Red de área amplia) desde Internet utilizando el explorador de web. Todavía se requieren un nombre de usuario y contraseña para acceder a la interfaz de gestión del router.
			<br>
			<strong><em>IP permitida para acceder</em></strong> -
			Esta opción permitirá a los usuarios especificar que se permite a una dirección IP particular acceder desde Internet al router de forma remota. Este campo se deja en blanco de forma predeterminada lo que significa que cualquier dirección IP desde Internet puede acceder al router de forma remota cuando se active la gestión remota.
			<br>
			<strong><em>Puerto</em></strong> - Seleccione el puerto que se utilizará para acceder al <?query("/sys/modelname");?>.
		</p>
		<p>
			<strong><em>Ejemplo: </em></strong><br>
			<a href="http://192.168.0.1/help_tools.html">http://x.x.x.x:8080 </a> donde x.x.x.x es la dirección IP de WAN del <?query("/sys/modelname");?> y 8080 es el puerto utilizado para la interfaz de Gestión de web.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="time"><h2>Hora</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=33>
		<p>
			El router utiliza los parámetros de Configuración de la hora para sincronizar los servicios programados y las actividades de registro del sistema. Necesitará establecer la zona horaria correspondiente a su ubicación. La hora se puede establecer manualmente o se puede conectar el dispositivo a un servidor de NTP (Protocolo de hora de red) para recuperar la hora. También puede establecer las fechas del Horario de verano, lo que ajustará automáticamente la hora del sistema en las fechas especificadas.
		</p>
		<p>
			<strong><em>Zona horaria</em></strong> - Seleccione la zona horaria de la región en la que se encuentra.<br>
			<strong><em>Horario de verano</em></strong> -
			Si la región en la que se encuentra respeta el horario de verano, active esta opción y especifique el mes, semana, día y hora de inicio y final de dicho horario de verano.<br>
			<strong><em>Configuración automática de la hora</em></strong> -
			Seleccione un servidor de hora D-Link con el que le gustaría sincronizar la hora del <?query("/sys/modelname");?>. El intervalo en el que el <?query("/sys/modelname");?> se comunicará con el servidor NTP D-Link se establece a 7 días.
			<br>
			<strong><em>Establecer manualmente la fecha y la hora</em></strong> -
			Seleccione esta opción si desea especificar manualmente la hora. Debe especificar el año, el mes, el día, la hora, el minuto y el segundo o puede hacer clic en el botón Copiar los parámetros temporales de su ordenador para copiar la hora del sistema desde el ordenador que se está utilizando para acceder a la interfaz de gestión.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="log_settings"><h2>Parámetros de registro</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			Puede guardar el archivo de registro en una unidad local y posteriormente enviarlo a un administrador de red para la resolución de problemas.
			<br>
			<strong><em>Guardar</em></strong> - Haga clic en este botón para guardar las entradas de registro en un archivo de texto.<br>
			<strong><em>Tipo de registro</em></strong> - Seleccione el tipo de información que desearía que registrara el <?query("/sys/modelname");?>.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="email_settings"><h2>Parámetros de correo electrónico</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			Los Parámetros de correo electrónico le permiten enviar un archivo de Registro del dispositivo a una dirección de correo electrónico especificada.<br>
			<br>
			<strong><em>Dirección de correo electrónico origen</em></strong> - 
			La dirección de correo electrónico desde la que se enviará el correo electrónico. Los servicios SMTP más modernos requieren que sea una dirección de correo electrónico válida y realizarán pruebas para ver si es genuina.<br>
			<strong><em>Dirección de correo electrónico destino</em></strong> - 
			La dirección de correo electrónico a la que se enviará el archivo de Registro del dispositivo. El archivo de registro será visto por la persona que acceda a esta cuenta de correo electrónico.<br>
			<strong><em>Asunto del correo electrónico</em></strong> - 
			El título del correo electrónico.<br>
			<strong><em>Dirección del servidor SMTP</em></strong> - 
			La dirección IP o Nombre de dominio del servidor de correo electrónico que enviará el archivo de registro del dispositivo a la cuenta de correo electrónico requerida.<br>
			<strong><em>Puerto del servidor SMTP</em></strong> - 
			El puerto que utilizará el servidor de correo electrónico.<br>
			<strong><em>Activar autenticación</em></strong> - 
			Por razones de seguridad, algunos servidores SMTP comprueban el nombre y contraseña de la cuenta para confirmar que el correo electrónico que se está procesando proviene de uno de los clientes.<br>
			<strong><em>Nombre de cuenta</em></strong> - 
			El nombre de cuenta utilizado para la autenticación con el Servidor SMTP.<br>
			<strong><em>Contraseña</em></strong> - 
			La contraseña de la cuenta utilizada para la autenticación con el Servidor SMTP.<br>
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="system"><h2>Sistema</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=40>
		Se pueden guardar los parámetros del sistema actual como un archivo en la unidad de disco duro local. El archivo guardado o cualquier otro archivo de parámetros guardado creado por el dispositivo, se puede cargar en la unidad. Para recargar un archivo de parámetros del sistema, haga clic en <strong>Examinar</strong> para buscar el disco duro local para el archivo que se utilizará. El dispositivo también puede volver a restablecerse con los parámetros predeterminados de fábrica haciendo clic en <strong>Restaurar dispositivo</strong>. Use la funcionalidad de restauración sólo en caso necesario. Esto eliminará los parámetros guardados previamente para la unidad. Asegúrese de guardar sus parámetros del sistema antes de realizar una restauración de fábrica.
		<br>
		<strong><em>Guardar</em></strong> - Haga clic en el botón para guardar el archivo de configuración desde el router.<br>
		<strong><em>Examinar</em></strong> -
		Haga clic en Examinar para ubicar un archivo de configuración guardado y a continuación haga clic para Cargar y aplicar los parámetros guardados en el router.<br>
		<strong><em>Restaurar dispositivo</em></strong> -
		Haga clic en este botón para restaurar el router con sus parámetros predeterminados de fábrica.
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="firmware"><h2>Firmware</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=51>
	Puede actualizar el firmware del dispositivo utilizando esta herramienta. Asegúrese de que el firmware que desea utilizar se guarde en el disco duro local del ordenador. Haga clic Examinar para buscar el disco duro local para el firmware que se utilizará para la actualización. La actualización del firmware no modificará ninguno de los parámetros de su sistema, aunque se recomienda que guarde los parámetros de su sistema antes de realizar una actualización del firmware. Compruebe el sitio de soporte de D-Link <a href=<?query("/sys/supporturl");?>>con respecto</a> a las actualizaciones del firmware, o puede hacer clic en el botón Comprobar ahora para comprobar el firmware automáticamente.
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="dynamic_dns"><h2>DNS dinámico</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=2>
		<p>
			DNS dinámico (Servicio de nombres de dominio) es un método para mantener un nombre de dominio vinculado con una dirección IP cambiante (dinámica). Con la mayoría de conexiones de Cable y DSL, se le asigna una dirección IP dinámica y esa dirección se utiliza sólo durante la duración de esa conexión específica. Con el <?query("/sys/modelname");?>, puede configurar su servicio DDNS y el <?query("/sys/modelname");?> actualizará automáticamente su servidor DDNS cada vez que reciba una nueva dirección IP de WAN.
			<br>
			<strong><em>Dirección del servidor</em></strong> - Seleccione su proveedor DDNS desde el menú desplegable.<br>
			<strong><em>Nombre de host</em></strong> - Introduzca el Nombre de host que registró con su proveedor de servicio DDNS.<br>
			<strong><em>Nombre de usuario</em></strong> - Introduzca el nombre de usuario para su cuenta DDNS.<br>
			<strong><em>Contraseña</em></strong> - Introduzca la contraseña para su cuenta DDNS.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="system_check"><h2>Comprobación del sistema</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			Esta herramienta se puede utilizar para verificar la conectividad física en las interfaces LAN e Internet (WAN). Esta es una funcionalidad avanzada que integra un probador de cables de LAN en cada puerto Ethernet del router. A través de la interfaz gráfica de usuario (GUI), se puede realizar una Prueba de cables para diagnosticar de forma remota e informar de fallos de cables como por ejemplo circuitos abiertos, cortocircuitos, cables intercambiados, e incompatibilidad de impedancias. Esta funcionalidad reduce significativamente las llamadas y devoluciones del servicio permitiendo a los usuarios solucionar fácilmente sus conexiones de cables.
		</p>
		<p>
			<strong>Prueba de ping</strong><br>
			Esta utilidad de diagnóstico se puede utilizar para comprobar si un ordenador está conectado a Internet. Envía paquetes ping  y escucha los ecos procedentes del host específico. Introduzca un nombre de host o la dirección IP a los que desea aplicar el ping (Buscador de paquetes de Internet) y haga clic en <strong>Ping</strong> . El estado de su intento de Ping se visualizará en el cuadro de Resultados del ping.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="schedules"><h2>Programas</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>	
			Esta página se utiliza para configurar programas globales para el router. Una vez definidos, estos programas pueden aplicarse posteriormente a las funcionalidades del router que permiten la programación.
			<br>
			<strong><em>Nombre</em></strong> - El nombre del programa que se está definiendo.<br>
			<strong><em>Día(s)</em></strong> -
			Seleccione un día, rango de días, o seleccione el cuadro de selección Toda la semana para disponer de este programa .apply todos los días.<br>
			<strong><em>Todo el día - 24 horas</em></strong> -
			Compruebe que este cuadro tenga activo el programa todas las 24 horas en los días especificados.<br>
			<strong><em>Hora de inicio</em></strong> -
			Seleccione la hora en la que desearía que el programa que se está definiendo pase a estar activo.<br>
			<strong><em>Hora final</em></strong> -
			Seleccione la hora en la que desearía que el programa que se está definiendo pase a estar inactivo.<br>
			<strong><em>Lista de reglas de programa</em></strong> -
			Visualiza todos los programas que se han definido.
		</p>
	</td>
</tr>
</table>
</div>

						   