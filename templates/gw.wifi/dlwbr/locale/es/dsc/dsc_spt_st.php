<h1>MENÚ DE SOPORTE</h1>

	<table border=0 cellspacing=0 cellpadding=0 width=750 height=478>
 <tr>
 <td height=2><font size=4><b>Estado</b></font></td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>

 </tr>
 <tr>
 <td height=39> <a name=20><strong>Información del dispositivo </strong><br>
Esta página muestra la información actual del <?query("/sys/modelname");?>. La página mostrará la versión del firmware cargado actualmente en el dispositivo. <br>

&nbsp;<br>
<strong><em>LAN (Red de área local):  </em></strong>muestra la dirección MAC de la interfaz de LAN Ethernet, la dirección IP y la máscara de subred de la interfaz de LAN y si el servidor DHCP incorporado del router está Activado o Desactivado. <br>
<strong><em>WAN (Red de área amplia):  </em></strong>muestra la dirección MAC de la interfaz de WAN, así como la información de dirección IP, máscara de subred, puerta de enlace predeterminada y servidor DNS que el <?query("/sys/modelname");?> ha conseguido de su ISP. Mostrará asimismo el tipo de conexión (Dinámica, Estática o PPPoE) que se utiliza para establecer una conexión con su ISP. Si el router está configurado para Dinámica, existirán botones para liberar y renovar la dirección IP asignada a la interfaz de WAN. Si el router está configurado para PPPoE, existirán botones para conectar y desconectar la sesión PPPoE.<br> 
<strong><em>
Inalámbrica 802.11g:
<? if(query("/runtime/func/ieee80211n") != "1") { echo "g"; } else { echo "n"; }?>
 - 
</em></strong>muestra el SSID, el canal y si está activado o no el cifrado en la interfaz inalámbrica. </td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>

 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=26><a name=21><b>Registro</b></a><br>
El <?query("/sys/modelname");?> mantiene un registro continuo de los eventos y actividades que tienen lugar en el mismo en todo momento. El registro mostrará hasta 400 registros recientes. Las actividades de registro más actuales sobrescribirán los registros más antiguos. <br>

 <strong><em>Primera página: </em></strong> haga clic en este botón para ir a la primera página del registro. <br>
 <strong><em>Última página: </em></strong> haga clic en este botón para ir a la última página del registro. <br>
 <strong><em>Anterior:  </em></strong>  retrocede una página en el registro.  <br>
 <strong><em>Siguiente: </em></strong>avanza una página en el registro. <br>

 <strong><em>Borrar: </em></strong> borra completamente el registro.  </td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>

 </tr>
 <tr>
 <td height=2><a name=22><strong>Estadísticas</strong></a><br>
El <?query("/sys/modelname");?> mantiene estadísticas del tráfico de datos que maneja. Puede ver la cantidad de paquetes que ha recibido y transmitido el router en las interfaces de WAN, LAN e inalámbrica. 
<br>
<strong><em>Actualizar :</em></strong>haga clic en este botón para actualizar los contadores. <br>
<strong><em>Reiniciar :</em></strong>haga clic en este botón para borrar los contadores. El contador de tráfico se reiniciará cuando se reinicie el dispositivo. </td>

 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=2><a name=23><b>Sesión activa</b></a><br>
La sesión activa muestra los paquetes de Origen y Destino que pasan a través del <?query("/sys/modelname");?>. <br>
 <strong><em>Dirección IP: </em></strong> a dirección IP de origen desde donde se originan los paquetes.<br>
 <strong><em>Sesión TCP: </em></strong> muestra el número de paquetes TCP que se están enviando desde la dirección IP de origen.<br>
 <strong><em>Sesión UDP:  </em></strong> muestra el número de paquetes UDP que se están enviando desde la dirección IP de origen.<br>
 <strong><em>Protocolo:  </em></strong> se trata del tipo de paquetes transmitidos entre la IP de origen y de destino.<br>
IP de origen: muestra la dirección IP desde donde se originan los paquetes.<br>
 Puerto de origen: muestra el puerto que se está utilizando para transmitir paquetes a la IP de destino.<br>
 IP de destino: muestra la dirección IP a donde van destinados los paquetes.<br>
 Puerto de destino: muestra el puerto que se está utilizando para recibir los paquetes de la IP de origen.<br>
</td>

 </tr>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=2><a name=24><b>Inalámbrico</b></a><br>
Utilice esta página para ver la cantidad de clientes inalámbricos que tiene asociados con el <?query("/sys/modelname");?>. Esta página muestra la dirección MAC de cada cliente asociado, cuánto tiempo han estado asociados y el modo en que se conectan en (802.11b o 802.11g). 
</td>

 </tr>
 </table>
