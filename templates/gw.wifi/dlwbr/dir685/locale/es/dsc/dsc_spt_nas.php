<div class="box">
<a name="disk_management"><h2>Gestión de disco</h2></a>
	<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			La página Gestión de disco contiene información y los parámetros para el disco duro local que está instalado actualmente en el dispositivo.<br>
			<br>
			<strong><em>Información del disco duro</em></strong> -
			Contiene detalles sobre el disco duro instalado en el dispositivo.<br>
			<strong><em>Ajuste de formato</em></strong> -
			Este botón le permite formatear el disco duro que está actualmente instalado en el dispositivo.<br>
			ADVERTENCIA: Esta acción limpiará el disco duro. ¡Se perderán todos los datos del disco duro!<br>
			<strong><em>Ajuste del disco duro</em></strong> -
			Cuando se activa este parámetro, el disco duro pasará a modo en espera después de los minutos especificados, si no se hubiera escrito o leído ningún dato en el disco duro, para reducir el consumo de energía.<br>
		</p>
	</td>
</tr>
 </table>
</div>

<div class="box">
<a name="users_groups"><h2>Usuarios/Grupos</h2></a>
	<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=228>
		<p>
			<strong>Usuarios</strong><br>
			Aquí se pueden crear los usuarios. Estas cuentas se pueden añadir a las reglas en las secciones Acceso de red y Servidor FTP. Cada usuario creado también tendrá acceso a la sección Descarga programada.
		</p>
		<p>
			<strong><em>Nombre de usuario</em></strong> -
			Introduzca el nombre de usuario.<br>
			<strong><em>Contraseña</em></strong> -
			Introduzca la contraseña.<br>
			<strong><em>Confirmar contraseña</em></strong> -
			Introduzca la contraseña nuevamente. Haga clic en 'Guardar parámetros' para añadir el usuario.<br>
			<br>
			Los usuarios creados aparecerán en una lista en la parte inferior de esta página junto con su grupo asignado (si hubiera). Las contraseñas de usuario se pueden editar haciendo clic en el icono 'cuaderno de notas con bolígrafo' o se pueden eliminar usuarios haciendo clic en el icono 'papelera" en la derecha de la regla.			
		</p>
		<p>
			<strong>Grupos</strong><br>
			Aquí se pueden crear los grupos. Una vez se haya creado un grupo, éste estará disponible en la selección Grupo en la página Usuarios.<br>
			<br>
			Los grupos creados aparecerán en una lista en la parte inferior de esta página. También se visualizarán los usuarios de estos grupos.<br>
		</p>
	</td>
</tr>
 </table>
</div>
 
 
<div class="box">
<a name="storage_access"><h2>Acceso de almacenamiento</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=64> 
		<p>
			<strong><em>Categoría</em></strong> -
			Seleccione Usuario o Grupo.<br>
			<strong><em>Usuario o Grupo</em></strong> -
			Seleccione un usuario o grupo de la lista desplegable. Seleccione 'Todas las cuentas' si deseara crear una regla que se aplique a todos los usuarios.<br>
			<strong><em>Carpeta</em></strong> -
			Haga clic en "Examinar" para seleccionar una carpeta. Esta carpeta debe estar ubicada en las unidades internas.<br>
			<strong><em>Permiso</em></strong> -
			Asigne permisos de "Sólo lectura" o de "Lectura / Escritura" a la carpeta seleccionada para el usuario o grupo especificados.<br>
			<strong><em>Oplocks</em></strong> -
			Los bloqueos oportunistas (oplocks) representan una característica del protocolo de conexión de red del Gestor de LAN implementado en la familia de entornos de sistemas operativos de Windows de 32 bits. Los oplocks son garantías realizadas por un servidor para un volumen lógico compartido para sus clientes. Estas garantías informan al Cliente que no se permitirá al servidor modificar el contenido de un archivo, o si algún cambio fuera inminente, este hecho se le notificará al cliente antes de que se permita continuar con el cambio. Los oplocks se diseñaron para aumentar el rendimiento de la red cuando se trata de compartir el archivo de red, aunque cuando se utilizan aplicaciones de bases de datos basadas en archivos, se recomienda establecer los oplocks a <strong>No(off)</strong>. <br>
			<br>
			¿Qué sistemas operativos se ven afectados por Oplocks?<br>
			<br>
			De forma predeterminada, Vista tiene Oplocks activados y no se pueden desactivar. Si tuviera problemas con el rendimiento de la red debido a aplicaciones que comparten archivos desde el DIR-685, puede intentar mejorar el rendimiento estableciendo los Oplocks a <strong>No(off)</strong>.<br>
			<strong><em>Archivo de mapa</em></strong> -
			Cuando se activa, el atributo del archivo--"Archivo" se copiará como el archivo que se está almacenando en el DIR-685. Cierto software de backup adjunta este atributo a los archivos que se están almacenando como backups.<br>
			<strong><em>Comentario</em></strong> -
			Comentarios adicionales sobre esta regla. Esto es opcional y no tiene ningún efecto funcional.<br>
			<br>
			Haga clic en 'Guardar parámetros' para guardar la regla. Todas las reglas guardadas aparecerán en una lista junto a la parte inferior de esta página. Las reglas se pueden editar o eliminar haciendo clic en el icono 'cuaderno de notas con bolígrafo' o en el de 'papelera' de la derecha de la regla.<br>
		</p>
 </tr>
</table>
</div>
 
 
<div class="box">
<a name="ftp_server"><h2>Servidor Ftp</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=99>
		<p>
			<strong><em>Categoría</em></strong> -
			Seleccione Usuario o Grupo.<br>
			<strong><em>Usuario</em></strong> -
			Seleccione un usuario o grupo de la lista desplegable. Seleccione 'Todas las cuentas' si deseara crear una regla que se aplique a todos los usuarios. Anónimo siempre se listará como un usuario.<br>
			<strong><em>Carpeta</em></strong> -
			Haga clic en "Examinar" para seleccionar una carpeta y asignarla al usuario seleccionado. Esta carpeta debe estar ubicada en las unidades internas. Si deseara asignar simultáneamente el acceso a la raíz de todas las unidades, ponga una marca en el cuadro 'raíz'.<br>
			<strong><em>Permiso</em></strong> -
			Asigne permisos de "Sólo lectura" o de "Lectura / Escritura" a la carpeta seleccionada para el usuario o grupo especificados. Haga clic en 'Añadir' para añadir la regla a la lista. Todas las reglas guardadas aparecerán en una lista junto a la parte inferior de esta página. Las reglas se pueden editar o eliminar haciendo clic en el icono 'cuaderno de notas con bolígrafo' o en el de 'papelera' de la derecha de la regla.<br>
			<strong><em>Usuario máx</em></strong> -
			Introduzca el número máximo de usuarios a los que se les permitirá acceder al servidor FTP a la vez. El valor predeterminado es 10.<br>
			<strong><em>Tiempo de inactividad</em></strong> -
			El servidor FTP finalizará la sesión de un usuario que supere el tiempo de inactividad especificado.<br>
			<strong><em>Puerto</em></strong> -
			Si deseara cambiar el puerto que utiliza el servidor FTP, introduzca aquí el nuevo número. Este es un parámetro avanzado y un cambio en él puede provocar complicaciones cuando está detrás de un router. Se recomienda dejarlo en el valor predeterminado de 21 a menos que tuviera experiencia con el cambio del puerto FTP.<br>
			<strong><em>Control de flujo</em></strong> -
			Esta función ajustará el flujo de datos a través del servidor FTP. Si estableciera un límite aquí, los usuarios podrían descargar del servidor FTP a una velocidad menor; aunque conservará el ancho de banda local.<br>
			<strong><em>Idioma del cliente</em></strong> -
			La mayoría de los clientes FTP estándar como Windows FTP, sólo permiten la página de códigos de Europa Occidental al transferir archivos. También se han añadido páginas de códigos de Europa del Norte, Europa Central, Chino tradicional y simplificado y Cirílico para clientes FTP no estándar que son capaces de admitir estos conjuntos de caracteres.<br>
			<br>
			Haga clic en 'Guardar parámetros' cuando termine.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="upnp_av_server"><h2>Servidor AV UPnP</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=44>
		<p>
			El DIR-685 tiene un servidor multimedia AV UPnP integrado que se puede utilizar con reproductores multimedia compatibles con AV UPnP.<br>
			<br>
			<strong><em>Servidor AV UPnP</em></strong> -
			Active o desactive el Servidor AV UPnP.<br>
			<strong><em>Carpeta</em></strong> -
			Haga clic en 'Analizar' para ubicar la carpeta raíz de sus archivos multimedia (música, fotos, y vídeo). La raíz se puede elegir si desea tener acceso a todo el contenido del DIR-685.<br>
			<strong><em>Actualización automática</em></strong> -
			Configure su actualización automática para actualizar automáticamente sus datos AV UPNP compartidos cada 5, 15 o 30 minutos o desde intervalos de 1, 2, 6, 12 o 24 horas.<br>
			<br>
			Haga clic en 'Guardar parámetros' cuando termine.<br>
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="itunes_server"><h2>Servidor iTunes</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			El servidor iTunes permitirá al software iTunes detectar automáticamente y reproducir música procedente del DIR-685.<br>
			<br>
			<strong><em>Servidor iTunes</em></strong> -
			Active o desactive el Servidor iTunes.<br>
			<strong><em>Carpeta</em></strong> -
			Haga clic en 'Examinar' para ubicar la carpeta que contiene sus archivos de música. La raíz se puede elegir si desea tener acceso a todas las carpetas del DIR-685.<br>
			<strong><em>Actualización automática</em></strong> -
			Configure su actualización automática para actualizar automáticamente sus datos compartidos de la Biblioteca iTunes cada 5, 15 o 30 minutos o desde intervalos de 1, 2, 6, 12 o 24 horas.<br>
			<br>
			Haga clic en 'Guardar parámetros' cuando termine.<br>
		</p>
</td>
</tr>
</table>
</div>

<div class="box">
<a name="bt_download_manager"><h2>Gestor de descargas de BT</h2></a>
	<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			La página Gestor de descargas de BT contiene parámetros para configurar su dispositivo para que los archivos BT (Torrente de bits) puedan descargarse desde Internet, sin tener que encender su PC.<br>
			<br>
			<strong><em>Ajuste de BT</em></strong> -
			Esto le permitirá activar/desactivar el servicio del Gestor de descargas de BT. La ruta del directorio le permitirá indicar el directorio/carpeta en el que le gustaría guardar sus archivos descargados. Todas las descargas se almacenarán en el directorio indicado, con todos los elementos completados almacenados en un directorio denominado "completado" y todos los elementos pendientes almacenados en un directorio denominado "incompleto". La organización de archivos para cada descarga seguirá siendo exactamente la misma que los archivos descargados originales.<br>
			<strong><em>Descargas de torrentes</em></strong> -
			En la pantalla del Gestor de descargas de BT (torrente de bits) se le permitirá determinar si desea añadir nuevos elementos de descarga a través de una URL o desde un archivo semilla de BT individual.<br>
			Todos los elementos que se están descargando se listarán en la parte inferior de la pantalla, una descarga por fila, por lo que podrá visualizar y controlar claramente cada elemento que se esté descargando.<br>
			<strong><em>Tabla de elementos de descarga</em></strong> -
			Para cada elemento que se esté descargando, haga clic en el vínculo 'más detalles' para ver más información sobre las descargas actuales.<br>
			<strong><em>Detener</em></strong> -
			Los usuarios pueden utilizar este botón para detener el proceso de descarga, permitiendo a otros elementos que se están descargando disponer de más ancho de banda.<br>
			<strong><em>Retirar</em></strong> -
			Los usuarios pueden utilizar el botón en el lado derecho de cada elemento que se esté descargando para cancelar/eliminar el elemento que se está descargando, si se hubiera producido un error.<br>
			<br>
			Si ya se hubiera completado el elemento eliminado, sólo se eliminará la entrada, aunque los archivos que ya se han descargado se guardarán en el directorio "completado".<br>
			<strong><em>Retirar completado</em></strong> -
			Este botón en la esquina superior derecha de la tabla de elementos descargados permitirá a los usuarios retirar de la tabla todos los elementos de descarga finalizados, sin eliminar los archivos descargados.<br>			
		</p>
	</td>
</tr>
 </table>
</div>
