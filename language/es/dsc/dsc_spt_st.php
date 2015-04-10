<div class="box">
<a name="device_info"><h2>Información del dispositivo</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=39> 
Esta página muestra información actual para el <?query("/sys/modelname");?>. La página mostrará la versión del firmware que se cargó actualmente en el dispositivo.
 <br>

&nbsp;<br>
<strong><em>LAN (Red de área local) - </em></strong>Visualiza la Dirección MAC de la interfaz LAN Ethernet, la Dirección IP y la Máscara de subred de la interfaz LAN, y si el servidor DHCP integrado del router está activado o desactivado. <br>
<strong><em>WAN (Red de área amplia) - </em></strong>This displays the MAC Address of the WAN interface, as well as the IP Address, Subnet Mask, Default Gateway, and DNS server information that the <?query("/sys/modelname");?> has obtained from your ISP. It will also display the connection type (Dynamic, Static, or PPPoE) that is used to establish a connection with your ISP. If the router is configured for Dynamic, then there will be buttons for releasing and renewing the IP Address assigned to the WAN interface. If the router is configured for PPPoE, there will be buttons for connecting and disconnecting the PPPoE session.<br> 
<strong><em>
802.11 
<? if(query("/runtime/func/ieee80211n") != "1") { echo "g"; } else { echo "n"; }?>
inalámbrico
 - 
</em></strong>Muestra el SSID, Canal, y si el Cifrado está activado en la interfaz inalámbrica. </td>
</tr>
</table>
</div>


<div class="box">
<a name="log"><h2>Registro</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=26>
 El <?query("/sys/modelname");?> mantiene un registro actualizado de eventos y actividades que se producen en todo momento. El registro mostrará hasta 400 registros recientes. La actividades de registro más actuales sobrescribirán los registros antiguos.
 <br>

 <strong><em>Primera página - </em></strong> Haga clic en este botón para ir a la primera página del registro. <br>
 <strong><em>Última página - </em></strong> Haga clic en este botón para ir a la última página del registro. <br>
 <strong><em>Anterior - </em></strong> Retrocede una página de registro. <br>
 <strong><em>Siguiente - </em></strong> Avanza una página de registro. <br>

 <strong><em>Borrar - </em></strong> Borra los registros completamente. </td>
 </tr>
 </table>
 </div>
 
 
<div class="box">
<a name="statistics"><h2>Estadísticas</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=2>
 El <?query("/sys/modelname");?> mantiene las estadísticas del tráfico de datos que maneja. Será capaz de ver la cantidad de paquetes que el router ha recibido y transmitido en Internet (WAN), LAN, y en interfaces inalámbricas.
<br>
<strong><em>Actualizar - </em></strong>Haga clic en este botón para actualizar los contadores. <br>
<strong><em>Restablecer - </em></strong>Haga clic en este botón para poner a cero los contadores. El contador de tráfico se restablecerá cuando se reinicie el dispositivo. </td>
</tr>
</table>
</div>


<div class="box">
<a name="internet_session"><h2>Sesión de Internet</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=2>
 Sesión de Internet muestra paquetes origen y destino que pasan a través del <?query("/sys/modelname");?>. <br>
 <strong><em>Dirección IP - </em></strong> La dirección IP origen de donde se han originado los paquetes. <br>
 <strong><em>Sesión TCP - </em></strong> Muestra el número de paquetes TCP que se están enviando desde la dirección IP origen. <br>
 <strong><em>Sesión UDP - </em></strong> Muestra el número de paquetes UDP que se están enviando desde la dirección IP origen. <br>
 <strong><em>Protocolo - </em></strong> Este es el tipo de paquetes transmitidos entre IP origen y destino. <br>
 Dirección IP - Muestra la dirección IP de donde se originaron los paquetes. <br>
 Puerto de origen - Muestra el puerto que se está utilizando para transmitir paquetes hasta el IP destino. <br>
 IP destino - Muestra la dirección IP hacia donde se destinaron los paquetes. <br>
 Puerto destino - Muestra el puerto que se está utilizando para recibir paquetes desde el IP origen. 
</td>
 </tr>
 </tr>
</table>
</div>
 
 
<div class="box">
<a name="wireless"><h2>Inalámbrico</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=2>
 Use esta página para ver cómo se han asociado muchos clientes inalámbricos con el <?query("/sys/modelname");?>. Esta página muestra la dirección MAC de cada cliente asociado, cuánto tiempo hace que se han asociado, y el modo en el que se conectan (802.11b, 802.11g, 802.11a o 802.11n).
</td>
 </tr>
</table>
</div> 
