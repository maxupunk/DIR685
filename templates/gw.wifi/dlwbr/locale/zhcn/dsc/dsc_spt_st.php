<h1>支持菜单</h1>

	<table border=0 cellspacing=0 cellpadding=0 width=750 height=478>
 <tr>
 <td height=2><font size=4><b>状态</b></font></td>
 </tr>
 <tr>
 <td height=39> <a name=20><strong>设备信息 </strong><br>
该页面显示了<?query("/sys/modelname");?>的当前信息。该页面将会显示当前设备上加载的固件版本信息。<br>

&nbsp;<br>
<strong><em>LAN (局域网) - </em></strong>显示以太网LAN接口的MAC地址，IP地址和子网掩码，以及路由器的内置DHCP服务器是否被开启。<br>
<strong><em>WAN (因特网) - </em></strong>显示了WAN接口的MAC地址，IP地址，子网掩码，缺省网管以及<?query("/sys/modelname");?> 从您的因特网服务商获取的DNS服务器信息。也会显示用来与您的ISP建立连接的连接类型（动态，静态，PPPoE）。如果路由器被配置为动态，那么会出现用来释放或更新分配给WAN接口的IP地址的按钮。如果路由器被配置为PPPoE，则将会出现连接和断开PPPoE连接的按钮。<br> 
<strong><em>
无线 802.11
<? if(query("/runtime/func/ieee80211n") != "1") { echo "g"; } else { echo "n"; }?>
 - </em></strong>显示无线接口的SSID，信道以及是否开启加密。</td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>

 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=26><a name=21><b>日志</b></a><br>
 <?query("/sys/modelname");?>会一直对所发生的事件进行记录。最多可显示最近400条记录。新的记录会覆盖旧的。<br>

 <strong><em>第一页 - </em></strong> 点击该按钮进入日志的第一页。 <br>
 <strong><em>最后一页 - </em></strong> 点击该按钮进入日志的最后一页。 <br>
 <strong><em>上一页 - </em></strong> 回到上一页日志。<br>
 <strong><em>下一页 - </em></strong> 进入下一页日志。<br>

 <strong><em>清除 - </em></strong> 完全清除日志。 </td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>

 </tr>
 <tr>
 <td height=2><a name=22><strong>统计</strong></a><br>
 <?query("/sys/modelname");?>会保留它处理过的数据流的统计数据。您可以查看路由器接收并转发到WAN,LAN以及无线接口的数据包数目。
<br>
<strong><em>刷新 - </em></strong>点击此按钮更新计数器。 <br>
<strong><em>复位 - </em></strong>点击此按钮清空计数器。设备重启后流量计数器将会重置。 </td>

 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=2><a name=23><b>活动会话</b></a><br>
 激活会话显示了通过<?query("/sys/modelname");?>的源和目的数据包。<br>
 <strong><em>IP 地址 - </em></strong> 数据包来源的源IP地址。 <br>
 <strong><em>TCP 会话 - </em></strong> 显示从源IP地址发送出的TCP数据包的数目。 <br>
 <strong><em>UDP 会话 - </em></strong> 显示从源IP地址发送出的UDP数据包的数目。 <br>
 <strong><em>协议 - </em></strong> 在源和目的IP之间转发的数据包的类型。 <br>
 源 IP - 数据包来源的源IP地址。<br>
 源端口 - 显示用来发送数据包到目的IP的端口。 <br>
 目的 IP - 显示数据包的目的IP地址。<br>
 目的端口 - 显示用来接收来自源IP数据包的端口。<br> 
 超时 - 路由器上会话终止时的空闲时间。其初始值由连接的类型和状态决定。<br>
 状态 - 采用TCP协议进行会话的状态。<br>
 方向 - 会话开始时的方向：<br>
 出站 - 开始时从LAN至WAN <br>
 入站 - 开始时从WAN至LAN。<br> 
 优先级 - QoS引擎逻辑对该会话出去的数据包分配一个优先级。数值越小，优先级也就越高。<br>

</td>

 </tr>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=2><a name=24><b>无线</b></a><br>
 此页面显示了有多少无线客户与<?query("/sys/modelname");?>相关联。该页显示了相关客户的MAC地址，加入的时间以及连接的类型（802.11b或802.11g）。
</td>

 </tr>
 </table>
