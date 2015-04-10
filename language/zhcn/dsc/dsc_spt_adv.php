<div class="box">
<a name="port_forwarding"><h2>端口转发</h2></a>
	<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=228>
		<p>
			高级端口转发选项使Internet用户可以访问您LAN上的服务。此特性在提供在线服务如FTP，WEB或游戏服务器时非常有用。对于每项，您在路由器上定义一个公共端口用于重定向到内部LAN IP地址和LAN端口上。
		</p>
		<p>
			高级端口转发参数<br>
			<strong><em>名字</em></strong> -
			为虚拟服务器分配一个有意义的名字，如web服务器。
			在&quot;应用程序名&quot;下拉列表中提供了多种常见的虚拟服务类型。
			选择其中一项，以此种服务的标准值来填写剩余的参数。
			<br>
			<strong><em>IP地址</em></strong> -
			您内部网络上提供虚拟服务的系统的IP地址，如192.168.0.50。
			您可以通过&quot;计算机名&quot;下拉菜单从DHCP客户端列表中选择一台计算机，
			或者手动输入服务器计算机的IP地址。
			<br>
			<strong><em>应用程序名</em></strong> -
			用户可以从预定义的常见应用列表中进行选择以便快速配置。<br>
			<strong><em>计算机名</em></strong> - DHCP客户端列表。<br>
			<strong><em>流量类型</em></strong> -
			选择服务使用的协议。下拉菜单中的常见选项有- UDP，TCP与UDP和TCP。<br>
			<strong><em>私有端口</em></strong> -
			内部网络上使用的端口。<br>
			<strong><em>公共端口</em></strong> -
			Internet上可以访问的端口。<br>
		</p>
	</td>
</tr>
 </table>
 </div>
 
 
<div class="box">
<a name="application_rules"><h2>应用程序规则</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=64> 
	一些应用程序需要多条连接，如Internet游戏，视频会议，Internet电话等。
	这些程序在通过NAT（网络地址转换）时非常困难。如果您运行需要多条连接的程序，
	在&quot;触发端口&quot;中指定和程序相关的端口，
	选择协议类型为TCP（传输控制协议）或UDP（用户数据报协议），
	然后在防火墙端口框中输入和触发端口相关联的公共端口，以便为入站流量打开端口。
	在应用程序名下拉菜单中已有一些预定义的常用程序。
	<br>

<strong><em>名字</em></strong> - 应用程序的名字。<br>
<strong><em>触发端口</em></strong>- 触发程序的端口。可以是单个端口或一个端口组。<br>
<strong><em>流量类型</em></strong> - 触发程序的协议。<br>
<strong><em>防火墙端口</em></strong> - WAN侧用于访问程序的端口号。您可以定义一个端口或一组端口。您可以使用逗号添加多个端口或端口组。<br>
<strong><em>流量类型</em></strong> - 程序使用的协议。</td>

 </tr>
 </table>
 </div>
 
 
<div class="box">
<a name="qos_engine"><h2>QoS引擎</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
<td height=64>
		<p>
			智能QoS通过确保VoIP或流数据的优先级高于其它网络数据，如FTP或web，
			来提高VoIP通话质量或流数据传输。如要使用最佳性能，
			请点击&quot;lag eliminated&quot;选项为您的应用自动设置优先级。
			<br>
		</p>
</td>
</tr>
</table>
</div>
 
 
<div class="box">
<a name="access_control"><h2>网络过滤</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=99>
		<p>
			过滤器用于允许或禁止LAN计算机访问Internet和您的网络。在您的网络中，可以设置设备允许或禁止Internet访问特定MAC地址的计算机。
		</p>
		<p>
			<strong>MAC过滤</strong><br>
			使用MAC过滤拒绝局域网内的计算机访问Internet。您可以手动输入MAC地址或从当前连接到设备的客户端列表中选择MAC地址。
			<br>
			选择&quot;启用MAC过滤并允许下列MAC地址的计算机访问网络&quot;，
			如果您只希望选择的计算机可以访问网络而其它所有的计算机不能访问网络。
			<br>
			选择&quot;启用MAC过滤并拒绝下列MAC地址的计算机访问网络&quot;，
			如果您希望除列表外的计算机都可以访问网络。
			<br>
			<strong><em>MAC地址</em></strong> -
			添加到MAC过滤列表的网络设备的MAC地址。<br>
			<strong><em>DHCP客户端列表</em></strong> -
			计算机名下拉菜单将显示DHCP客户端的主机名。您可以选择添加到MAC过滤列表的客户计算机然后单击箭头按钮。这样可以自动添加该计算机的MAC地址到相应的框中。
		</p>
		<p>
			用户可以使用<strong>总是</strong>下拉菜单来选择一个预定义的计划或单击<strong>新建</strong>按钮来添加一个新的计划。
		</p>
		<p>
			此复选框用于启用或禁用特定的项。
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="parental_control"><h2>web站点过滤</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=44>
		<p>
			除了过滤可访问网络和Internet的设备外，对于网络上的计算机，
			<?query("/sys/modelname");?>也可配置为使用域名或密码允许或拒绝访问特殊站点。
		</p>
		<p>
			<strong>家长控制</strong><br>
			家长控制使用密码或特定域名来允许或拒绝网络上的计算机访问特定站点。
			选择&quot;打开站点过滤和仅允许计算机访问这些站点&quot;将只允许网络上的计算机访问特定URL和域名。
			&quot;打开站点过滤和 仅拒绝计算机访问这些站点&quot;用于拒绝网络上计算机访问特定URL和域名。
		</p>
		<p>
			<span class="style1">例1：</span><br>
			如果您想要阻止任何LAN用户访问任何关联到购物站点的URL，
			您需要选择&quot;打开站点过滤和仅拒绝计算机访问这些站点&quot;
			然后在web站点过滤规则列表中输入&quot;购物&quot;。
			诸如此类的站点由于URL中具有该关键字不能被LAN用户访问。
			<br>
			<a href="http://www.yahoo.com/shopping/stores.html">http://www.yahoo.com/shopping/stores.html</a><br>
			<a href="http://www.msn.com/search/shopping-spree.html">http://www.msn.com/search/shopping-spree.html</a>
		</p>
		<p>
			<span class="style1">例2：</span><br>
			如果您希望孩子只能访问一些特殊站点，
			可以选择&quot;打开站点过滤和仅允许计算机访问这些站点&quot;，
			然后输入允许孩子访问的域名。
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
<a name="firewall_dmz"><h2>防火墙设置</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			防火墙设置部分包含一个用于配置DMZ主机的选项。
		</p>
		<p>
			<strong>启用SPI</strong><br>
			SPI（数据包状态检测，也称作动态数据包过滤）可帮助您通过跟踪每段会话的更多状态来阻止黑客攻击。
			通过会话的流量需符合相关协议。当协议为TCP时，SPI将检测会话有效范围内的数据包序列号，
			丢弃无有效序列号的数据包。不论是否启用SPI，
			路由器将始终跟踪TCP连接状态并保证每个TCP数据包的标记对当前状态有效。
		</p>
		<p>
			<strong>DMZ </strong><br>
			如果您的计算机不能从<?query("/sys/modelname");?>后运行Internet应用程序，您可以允许该计算机具有不受限制的Internet访问权限。输入该计算机的IP地址作为一个DMZ(非限制区)主机，具有无限制Internet访问。将该客户端添加到DMZ将使该计算机暴露于多种安全危险中。请只在不得已的情况下采用此操作。
		</p>
		<p>
			<strong>防火墙规则</strong><br>
			防火墙规则根据源IP地址、目的IP地址、流量类型、数据通过的特定端口，用于允许或拒绝流量通过路由器。
			<br>
			<strong><em>名称</em></strong> - 用户可以为防火墙规则指定一个名称<br>
			<strong><em>活动</em></strong> - 用户可以选择允许或拒绝流量<br>
			<strong>接口</strong><br>
			<strong><em>源</em></strong> -
			使用<strong>源</strong>下拉菜单以选择被允许或拒绝流量的起始位置是否来自LAN或WAN接口
			<br>
			<strong><em>目的</em></strong> -
			使用<strong>目的</strong>下拉菜单以选择被允许或拒绝流量的终止位置是否为LAN或WAN接口
			<br>
			<strong><em>IP地址</em></strong> -
			您可以在这里输入单个源IP地址或目的IP地址。请在顶部输入框输入IP地址，或通过在顶部输入框输入IP地址范围内的首个IP地址，并在底部输入框输入IP地址范围的最后一个IP地址来确定端口范围。
			<br>
			<strong><em>协议</em></strong> -
			使用<strong>协议</strong>下拉菜单选择特定流量类型<br>
			<strong><em>端口范围</em></strong> -
			在两个输入框内输入同一个端口号以指定单一端口，或通过在顶部输入框输入IP地址范围内的首个IP地址，并在底部输入框输入IP地址范围内的最后一个IP地址来确定端口范围。
			<br>
			<strong><em>计划</em></strong> -
			使用<strong>总是</strong>下拉框菜单来选择一个之前定义的计划或点击<strong>新建</strong>按钮来增加一个新计划
 </p>
</td>
</tr>
</table>
</div>


<div class="box">
<a name="routing"><h2>路由</h2></a>
<table>
<?if(query("/runtime/func/dis_routing")!="1"){
echo "<tr>\n";
echo "	<td height=99>\n";
echo "		路由选项允许您定义到指定目的地的静态路由。<br>\n";
echo "		<strong><em>启用</em></strong> - 指定路由项是否被启用或禁用<br>\n";
echo "		<strong><em>接口</em></strong> - 指定接口 -- WAN或WAN物理 -- \n";
echo "		当使用此路由时，IP数据包必须通过的端口。<br>\n";
echo "		<strong><em>接口（WAN）</em></strong> - 该接口用于接收来自ISP的IP地址\n";
echo "		以访问Internet<br>\n";
echo "		<strong><em>接口（WAN物理）</em></strong> - 该接口用于接收来自ISP的IP地址\n";
echo "		以访问Internet<br>\n";
echo "		<strong><em>目的</em></strong> - 数据包的IP地址将采用该路由。<br>\n";
echo "		<strong><em>子网掩码</em></strong> - 掩码中值为1的位指定了需与IP地址\n";
echo "		的哪些位进行匹配。<br>\n";
echo "		<strong><em>网关</em></strong> - 如使用此路由，指定需经过的下一跳。\n";
echo "		网关0.0.0.0表示没有下一跳，匹配的IP地址将直接\n";
echo "		连接到指定接口（WAN或WAN物理）的路由器。\n";
echo " </td>\n";
echo " </tr>\n";
}
?>
</table>
</div>


<div class="box">
<a name="advanced_wireless"><h2>高级无线</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=20>

 <p>本页的该选项应由高级用户更改，或者您由我们的技术支持人员指导，如果配置不正确，会对您的路由器性能产生负面影响。
 </p>
 <p><strong><em>传输电源 - </em></strong>
 您可以在下拉菜单中选择较低百分比的传输功耗值来降低<?query("/sys/modelname");?>的输出功耗。
 您的选择有100%、50%、25%和12.5%。
 </p>
 <p><strong><em>信标间隔 - </em></strong> 
 信标用于接入点同步发送数据包到无线网络。在20到1000之间指定一个信标间隔。默认值设置为100毫秒。 
 </p>

 <p><strong><em>RST阀值 - </em></strong> 
 该值应保持为默认设置的2346。如果您遇到不一致的数据流，建议最小修改值的范围为256到2346。RST阀值的默认值为2346。
 </p>
 <p><strong><em>分片 - </em></strong> 
 该值应保持为默认设置的2346。如果您经历了高数据包错误率，
 您可以在1500和2346范围内略微增加您的&quot;分片&quot;值。
 设置的分片值越低会使性能越低。
 </p>
 <p><strong><em>DTIM间隔 - </em></strong> 
 输入1到255之间的传输流量指示消息（DTIM）。DTIM是通知客户端下一个用于监听广播和组播信息的窗口的倒计时。当接入点为相关的客户端缓存广播或组播时，它将发送带有DTIM间隔值的DTIM。DTIM间隔的默认值设置为1。
 </p>

 <p><strong><em>前导码类型 - </em></strong> 
 前导码类型定义了CRC（循环冗余校验）区块的长度，便于在接入点和漫游无线适配器之间进行通信。请务必确认您选择的是正确类型并点击应用按钮。
 </p>
 <p><span class="style2">提示： </span>高网络流量区域应使用较短的前导码类型。CRC是检测数据传输错误的一项常用技术。</p>
 <p><strong><em>CTS 模式 - </em></strong>
 选择无，禁用该特性。选择总是，允许在传输数据前迫使路由器请求网络上的每台无线设备执行RTS/CTS握手。选择自动，允许路由器决定什么时候有必要执行RTS/CTS握手。
 </p>
<?if(query("/runtime/func/ieee80211n")!="1"){
 echo "<p><strong><em>802.11g Only Mode - </em></strong>Enable this mode if your network is made up of purely 802.11g devices. If you have both 802.11b and 802.11g wireless clients, disable this mode. </p> </td>";
}?>
 </tr>
 </tr>
 </table>
 </div>
 
 
<div class="box">
<a name="advanced_network"><h2>高级网络</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=20>

 <p>本部分包含了更改路由器处理通信量类型方式的设置。我们建议您不要更改这些设置，除非您对它们非常熟悉，或者由我们的技术支持人员指导您进行更改。
 </p>

<!--
 <p><strong>VPN Passthrough </strong><br>The device supports VPN (Virtual Private Network) passthrough for PPTP (Point-to-Point Tunneling Protocol) and IPSec (IP Security). Once VPN passthrough is enabled, there is no need to create any Virtual Server or Port Forwarding entries in order for outbound VPN sessions to be established properly. Multiple VPN connections can be made through the device. This is useful when you have many VPN clients on the Local Area Network. </p>
-->

 <p><strong>通用即插即用 </strong><br>
 UPnP 是通用即插即用的缩写，能在网络设备、软件和外围设备间提供兼容的网络架构。
 <?query("/sys/modelname");?> 是启用了UPnP的路由器，也就是说它能和其它UPnP设备/软件协同工作。
 如果您不想使用UPnP功能，选择"禁用"可禁用它。
 </p>
 <p><strong>WAN Ping </strong><br>如果您启用WAN Ping 响应，将使得设备的公共WAN（广域网）IP 地址响应Internet用户发送的ping命令。Ping公共WAN IP 地址是黑客测试您的WAN IP 地址是否有效的常用方法。
 </p>
 <p><strong>WAN端口速率</strong><br>
 允许您选择<?query("/sys/modelname");?>WAN接口速率：选择100Mbps, 10Mbps或10/100/1000Mbps自适应。
 </p>

<!--
 <p><strong>Gaming Mode </strong><br>If you are experiencing difficulties when playing online games or even certain applications that use voice data, you may need to enable Gaming Mode in order for these applications to work correctly. When not playing games or using these voice applications, it is recommended that Gaming Mode is disabled. </p>
--> 

<?if(query("/runtime/func/dis_multicast_stream")!="1"){
echo " <p><strong>组播流</strong><br>启用该选项，使组播流量更有效地从Internet传输到您的网络。</p> </td>\n";
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
<a name="guest_zone"><h2>Guest区</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			Guest区选择<br>
			这种选择帮助您定义Guest区规模。<br>
			<strong><em>启用Guest区</em></strong>  - 指定是否启用或禁用Guest区。<br>
			<strong><em>包含LAN端口</em></strong>  - 指定哪个LAN端口将包含在Guest区内。<br>
			<strong><em>包含无线</em></strong>  - 指定是否使用Guest区的无线区域。<br>
			<strong><em>无线网络名</em></strong> -  为Guest区无线网络提供名称。 <br>
		</p>
		<p>
			<strong><em>无线安全模式</em></strong><br>
			保护您的无线网络安全是非常重要的，因为它保护无线网络上所传输信息的完整性。
			<?query("/sys/modelname");?>提供4种类型的无线安全：WEP，仅使用WPA，仅使用WPA2和WPA/WPA2（自动）
		<br>
		</p>
		<p>
			<strong><em>WEP</em></strong><br>
			有线等效协议（WEP）是无线局域网（WLAN）上的一种无线安全协议。
			WEP通过加密为WLAN上传输的数据提供安全。
			<?query("/sys/modelname");?>支持2个等级的WEP加密：64位和128位。
			WEP缺省为禁用。可以更改WEP设置以适应已有的无线网络或自定义您的无线网络。
		<br>
		</p>
		<p>
			<strong><em>认证</em></strong> - 
			认证是<?query("/sys/modelname");?>对尝试加入无线网络的网络设备进行确认的过程。
			使用WEP时，此设备提供两种类型的认证。
			<br>
			<strong><em>开放系统</em></strong> -
			选择此项允许所有无线设备在被提示输入访问网络所需加密密钥前可以和<?query("/sys/modelname");?>通信。
			<br>
			<strong><em>共享密钥 </em></strong> - 
			选择此项将提示任何尝试访问<?query("/sys/modelname");?>的无线设备输入访问网络所需的加密密钥。
			<br>
			<strong><em>WEP加密</em></strong> - 
			选择您网络所需的WEP加密等级。支持两种等级的WEP加密，64位和128位。
			<br>
			<strong><em>密钥类型 </em></strong> - 
			<?query("/sys/modelname");?>支持的密钥类型有HEX（十六进制）和ASCII（美国标准信息交换码）。可以更改密钥类型以适应已有的无线网络或自定义您的无线网络。
			<br>
			<strong><em>密钥</em></strong> - 密钥1-4允许您轻松地改变无线加密设置以保持网络的安全。只需简单地选择用于在网络上对无线数据进行加密的密钥即可。
			<br>
		</p>
		<p>
			<strong><em>WPA-Personal</em></strong><br>
			Wi-Fi 保护访问会授权和认证无线网络上的用户。WPA与WEP相比具有更强的安全性，所使用的密钥会定期自动更改。
			<br>
		</p>
		<p>
			<strong><em>加密类型</em></strong> - 
			使用WPA为安全类型时，<?query("/sys/modelname");?>支持两种不同的加密类型。两种类型为TKIP（临时密钥完整性协议）和AES（高级加密标准）。
			<br>
			<strong><em>PSK/EAP</em></strong> -选择PSK时，您的无线客户端需要提供一个密码短语用于认证。选择EAP时，您网络上需要一个RADIUS服务器用于处理所有无线客户端的认证。
			<br>
			<strong><em>密码短语 </em></strong> - 
			当选择PSK时，您的无线客户端需要输入一个8-63位的字符串用于和<?query("/sys/modelname");?>进行通信。请记下这个密码短语，因为当您添加其它无线设备到您的网络时，您需要输入此密码短语。
			<br>
			<strong><em>802.1X </em></strong> -  这表示WPA2认证将和网络上的RADIUS服务器配合使用。输入您RADIUS服务器配置的IP地址，端口和共享密钥。如果您网络上有两个RADIUS服务器用于认证无线客户，您也可以输入第二个RADIUS服务器的信息。
			<br>
		</p>
		<p>
			<strong><em>WPA2</em></strong><br>
			Wi-Fi保护访问2会授权和认证无线网络上的用户。WPA2与WEP相比具有更强的安全性，所使用的密钥会定期自动更改。
			<br>
		</p>
		<p>
			<strong><em>加密类型</em></strong> - 
			使用WPA为安全类型时，<?query("/sys/modelname");?>支持两种不同的加密类型。两种类型为TKIP（临时密钥完整性协议）和AES（高级加密标准）。
			<br>
			<strong><em>PSK/EAP</em></strong> - 选择PSK时，您的无线客户端需要提供一个密码短语用于认证。选择EAP时，您网络上需要一个RADIUS服务器用于处理所有无线客户端的认证。
			<br>
			<strong><em>密码短语</em></strong> - 
			当选择PSK时，您的无线客户端需要输入一个8-63位的字符串用于和<?query("/sys/modelname");?>进行通信。请记下这个密码短语，因为当您添加其它无线设备到您的网络时，您需要输入此密码短语。
			<br>
			<strong><em>802.1X </em></strong> - 这表示WPA2认证将和网络上的RADIUS服务器配合使用。输入您RADIUS服务器配置的IP地址，端口和共享密钥。如果您网络上有两个RADIUS服务器用于认证无线客户，您也可以输入第二个RADIUS服务器的信息。
			<br>
		</p>
		<p>
			<strong><em>WPA2-Auto</em></strong> <br>
			该选项允许<?query("/sys/modelname");?>同时连接WPA2 和WPA客户端。
			<br>
		</p>
		<p>
			<strong><em>Guest区的LAN设置</em></strong><br> 
			这些是设备客户区LAN（局域网）接口的设置。这些设置也叫“私有设置”。如果需要，您可以改变LAN IP地址。LAN IP地址在您的内部网络是私有的，不能从Internet上看到。缺省IP地址为192.168.0.1，子网掩码255.255.255.0。
			<br>
		</p>
		<p>
			<strong><em>IP地址</em></strong> - <?query("/sys/modelname");?>的IP地址，缺省为192.168.0.1。<br>
			<strong><em>子网掩码</em></strong> - <?query("/sys/modelname");?>的子网掩码，缺省为255.255.255.0。<br>
		</p>
		<p>
			<strong><em>启用Guest区客户端隔离：</em></strong> : <br>
			启用该功能将阻止guest区中的客户端访问其它客户端。该客户端仅能访问Internet.
			<br>
		</p>
		<p>
			<strong><em>在区域中启用路由：</em></strong> : <br>
			使用本部分将在主机去和guest区之间启用路由。未启用该功能，客户端不能访问主机客户端的数据。
			<br>
		</p>
		<p>
			<strong><em>Guest区的DHCP服务器</em></strong> <br>
			DHCP是动态主机控制协议。DHCP服务器分配IP地址给网络上请求IP地址的设备。
			这些设备必须被设置为&quot;自动获取IP地址&quot;。
			缺省下，<?query("/sys/modelname");?>的DHCP服务器为启用。
			DHCP地址池包括一组可以动态分配给网络上客户端的IP地址。
			<br>
		</p>
		<p>
			<strong><em>起始IP地址</em></strong> - DHCP服务器IP分配的起始IP地址。<br>
			<strong><em>结束IP地址</em></strong> -DHCP服务器IP分配的结束IP地址。<br>
			<strong><em>租约时间</em></strong> -IP租用的时间长。动态DHCP客户表将会显示连接到设备上的动态DHCP客户计算机的相关信息。此表将显示每个客户计算机的主机名，IP地址，MAC地址和DHCP租约剩余时间。
			<br>
		</p>
</td>
</tr>
</table>
</div>
 
<div class="box">
<a name="wake_on_lan"><h2>LAN唤醒</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			LAN唤醒功能用于远程开启与路由器LAN端连接的PC 。指定LAN唤醒 magic数据包使用的UDP端口，防止路由器把LAN唤醒请求误认为是敌意攻击而阻止它。
			<br>
			<br>
			<strong><em>UDP端口</em></strong> - 
			这个唯一的端口是<?query("/sys/modelname");?>用于监听开启PC的magic数据包。
			<br>
			<strong><em>接口</em></strong> - 
			（当前不能更改该设置。在以后的固件版本中可能会更改该设置。）<br>		
		</p>
	</td>
</tr>
</table>
</div>
