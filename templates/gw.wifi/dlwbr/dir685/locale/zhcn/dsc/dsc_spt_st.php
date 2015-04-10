<div class="box">
<a name="device_info"><h2>设备信息</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=39> 
此页显示<?query("/sys/modelname");?>的当前信息。此页将显示设备当前加载的固件版本。
<br>

&nbsp;<br>
<strong><em>LAN（局域网） - </em></strong>这里显示LAN接口的MAC地址，IP地址和子网掩码，以及路由器内置的DHCP服务器是否启用。<br>
<strong><em>WAN（广域网） - </em></strong> 这里显示WAN接口的MAC地址，以及<?query("/sys/modelname");?>从ISP获取的IP地址，子网掩码，缺省网关和DNS服务器信息。它同时显示和ISP连接的类型（动态，静态或PPPoE）。如果路由器配置为动态，那会有一个按钮用于释放和更新分配给WAN口的IP地址。如果路由器配置为PPPoE，将会有按钮用于连接和断开PPPoE会话。<br> 
<strong><em>
无线802.11n
<? if(query("/runtime/func/ieee80211n") != "1") { echo "g"; } else { echo "n"; }?>
 - 
</em></strong>这里显示无线接口上的SSID，信道和是否启用加密。</td>
</tr>
</table>
</div>


<div class="box">
<a name="log"><h2>日志</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=26>
 <?query("/sys/modelname");?>保留了它所有发生的事件和活动的记录。日志将显示最近的400个记录。新的日志活动将覆盖旧的日志。
 <br>

 <strong><em>第一页 - </em></strong> 单击此按钮跳转到日志的第一页。 <br>
 <strong><em>最后一页 - </em></strong> 单击此按钮跳转到日志的最后一页。 <br>
 <strong><em>前一页 - </em></strong> 向后移动日志一页。 <br>
 <strong><em>下一页 - </em></strong> 向后移动日志一页。 <br>

 <strong><em>清除 - </em></strong> 全部清除日志。 </td>
 </tr>
 </table>
 </div>
 
 
<div class="box">
<a name="statistics"><h2>统计</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=2>
 <?query("/sys/modelname");?>保留它处理的数据流量的统计信息。您可以查看路由器上Internet（WAN），LAN和无线接口上发送和接收的数据包总数。
<br>
<strong><em>刷新 - </em></strong>单击此按钮更新计数器。 <br>
<strong><em>复位 - </em></strong>单击此按钮清除计数器。设备重启时，流量计数器将被复位。 </td>
</tr>
</table>
</div>


<div class="box">
<a name="internet_session"><h2>Interent会话</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=2>
 Internet会话将显示通过<?query("/sys/modelname");?>的源和目的数据包。 <br>
 <strong><em>IP地址 - </em></strong> 数据包的源IP地址。 <br>
 <strong><em>TCP会话 - </em></strong> 这里显示源IP地址发送的TCP数据包的数量。 <br>
 <strong><em>UDP会话 - </em></strong> 这里显示源IP地址发送的UDP数据包的数量。 <br>
 <strong><em>协议 - </em></strong> 这是源和目的IP之间传输的数据包的类型。 <br>
 源IP - 这里显示数据包的来源IP地址。 <br>
 源端口 - 这里显示用于传输数据到目的IP的端口。 <br>
 目的IP - 这里显示数据包的目的地IP地址。 <br>
 目的端口 - 这里显示用户接收源IP数据包的端口。 
</td>
 </tr>
 </tr>
</table>
</div>
 
 
<div class="box">
<a name="wireless"><h2>无线</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=2>
 使用此页查看连接到<?query("/sys/modelname");?>的无线客户端数量。此页显示每个连接客户端的MAC地址，连接了多长时间和连接的模式（802.11b，802.11g或802.11n）。
</td>
 </tr>
</table>
</div> 
