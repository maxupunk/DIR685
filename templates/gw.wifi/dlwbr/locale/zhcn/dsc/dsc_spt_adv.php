<h1>支持菜单</h1>
	<table border=0 cellspacing=0 cellpadding=0 width=750 height=1103>
 <tr>
 <td width="750" height=40><font size=4><b>高级</b></font></td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>

 </tr>
<tr>
	<td height=228>
		<p>
			<a name=05><strong>高级端口转发</strong></a><br>
			高级端口转发功能给予了因特网用户访问您的LAN的权限。
			这个功能对于用作在线服务的主机来说是很有用的，例如FTP，网页或游戏服务器。
			每个条目您都可以在您的路由器上定义一个公共端口或者端口范围来转接到内部LAN IP地址和LAN端口。
		</p>
		<p>
			高级端口转发参数<br>
			<strong><em>Name </em></strong> -
			为虚拟服务器分配一个有意义的名称，例如Web Server。
			有些著名的虚拟服务器类型可在&quot;Application Name&quot;下拉菜单中找到。
			选择这些条目之一然后用该类服务器标准的值来填入剩余的参数。<br>
			<strong><em>IP地址 </em></strong> -
			您内部网络上将提供虚拟服务系统的IP地址，例如192.168.0.50。
			您可以在&quot;Computer Name&quot;下拉菜单中的DHCP客户端中选择一台计算机，
			或者您也可以手动输入一个服务器的IP地址。<br>
			<strong><em>应用程序名称 </em></strong> -
			预先定义好的经常使用的应用程序名称。用户可用来进行快速配置。<br>
			<strong><em>计算机名称 </em></strong> - DHCP客户端列表。<br>
			<strong><em>协议类型</em></strong> -
			选择服务使用的协议。常用的选择—UDP，TCP和任意—可从下拉菜单中选取。
			要指定其他的协议，从列表中选择&quot;Other&quot;，
			然后在协议对话框输入相应的协议名称（该名称有IANA分配）。<br>
			<strong><em>私有端口</em></strong> -
			将会在您的内部网使用的端口。<br>
			<strong><em>公共端口</em></strong> -
			将通过因特网被访问的端口。<br>
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
 <td height=64> <strong>应用规则<font size=4><b><a name=06></a></b></font> </strong><br>
一些应用程序要求多重连接，例如网络游戏，视频会议等。这些应用程序通过NAT(网络地址转换)工作有困难。 如果你想运行需要多重连接的应用程序，在&quot;Trigger Port&quot;字段指定与某个应用程序相关联的端口号，选择协议类型为TCP（传输控制协议）或UDP（用户数据报文协议），然后输入与防火墙触发端口相关联的公共端口号以打开进入的通道。我们已经在应用程序下拉列表中定义了一些众所周知的应用程序。<br>

<strong><em>名称 </em></strong> - 应用程序的名字。<br>
<strong><em>触发端口 </em></strong>- 用来触发应用程序的端口。可以是一个端口或一系列端口。 <br>
<strong><em>协议类型 </em></strong> - 用来触发应用程序的协议。<br>
<strong><em>防火墙端口 </em></strong> - 将用来访问应用程序的WAN端端口号。您可以定义一个或一系列端口。您可以使用逗号来添加多个端口或端口范围。<br>
<strong><em>协议类型 </em></strong> - 使用程序的协议。</td>

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
			<a name=07><strong>访问控制</strong></a><br>
			过滤器被用来拒绝或允许LAN计算机访问因特网和您的网络。
			在您的网络中，可使用计算机的MAC地址来拒绝或允许因特网访问到计算机。
		</p>
		<p>
			<strong>MAC过滤器</strong><br>
			使用MAC过滤器来拒绝局域网中的计算机访问因特网。
			您可以手动添加MAC地址，也可以在当前连接到设备的客户端列表中选取。<br>
			如果您希望只有被选中的计算机拥有访问因特网权限的话，
			请选择&quot;打开MAC过滤，允许列表上的计算机访问网络&quot;。<br>
			如果您希望除了列表中的计算机外其余计算机都拥有访问网络的权限的话，
			请选择&quot;打开MAC过滤，禁止列表上的计算机访问网络&quot;。<br>
			<strong><em>MAC 地址</em></strong> -
			将被添加到MAC过滤器列表中的网络设备的MAC地址。<br>
			<strong><em>DHCP Client List</em></strong> -
			DHCP客户端将在计算机名称下拉菜单中获取它们的主机名。
		</p>
		<p>
			用户也可使用<strong>总是</strong>下拉菜单来选择预先定义的计划表
			或点击<strong>添加新的</strong>按钮来添加新的计划表。
		</p>
		<p>
			复选框是用来开启或禁用一个特定的条目。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<a name=08><strong>防火墙和DMZ</strong></a><br>
			防火墙设置选项包含了配置DMZ主机的选项。
		</p>
		<p>
			<strong>开启SPI</strong><br>
			SPI (&quot;数据包状态检验&quot; 也被成为&quot;动态数据包过滤&quot;)
			可通过追踪每段会话的多个状态来防止网络攻击。它确保通过该段会话的流量与协议相符。
			当协议为TCP时，SPI会检查数据包的序号是否在会话的正确序号范围内，并丢弃包含不合法序号的数据包。
			无论SPI是否被开启，路由器始终会追踪TCP连接状态，并确保每个TCP数据包的标记对于当前状态来说是有效的。
		</p>
		<p>
			<strong>DMZ </strong><br>
			如果你有台在<?query("/sys/modelname");?>后的电脑不能完全运行网络应用程序，
			这时你可以输入这台电脑的IP地址作为DMZ（非武装区）主机。
			允许这台电脑无限制地访问因特网。将一台电脑作为DMZ主机会带来一系列的安全隐患，
			所以应该将这个选项作为最后的选择。
		</p>
		<p>
			<strong>防火墙规则</strong><br>
			防火墙规则被用于允许或阻止进出路由器的数据流量，其规则基于源IP地址和目的IP地址，协议类型以及指定的数据端口。<br>
			<strong><em>名称</em></strong> - 用户指定的防火墙规则名称。<br>
			<strong><em>动作</em></strong> - 用户指定的允许或阻止动作。<br>
			<strong>界面</strong><br>
			<strong><em>源</em></strong> -
			使用<strong>目的</strong>下拉菜单来选择从LAN或WAN端发起的被允许或阻止的流量起始点。<br>
			<strong><em>目的</em></strong> -
			用<strong>目的</strong>下拉菜单来选择到达LAN或WAN端的被允许或阻止的流量终止点。<br>
			<strong><em>IP地址</em></strong> -
			在这里你可以指定一个单独的源或目的IP地址，你可以在上面的文本框中输入单独的IP地址；
			或者是在上面的框中输入一个IP地址范围的开始IP，并在下面的框中输入终止IP地址以指定一个IP范围。<br>
			<strong><em>协议</em></strong> -
			使用<strong>协议</strong>下拉菜单来选择流量类型。<br>
			<strong><em>端口范围</em></strong> -
			在两个框中都输入相同的端口号以指定一个单独的端口号；
			或在上面的框中输入一个端口范围的开始端口号，并在下面的框中输入结束端口号以指定一个端口范围。<br>
			<strong><em>调度进程</em></strong> -
			用户也可使用<strong>总是</strong>下拉菜单来选择预先定义的计划表
			或点击<strong>添加新的</strong>按钮来添加新的计划表。
 </p>
	</div></td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
 <tr>
 <td height=20><p><strong>高级无线设置 <a name=09></a></strong></p>

 <p>在此页中的选项应该被高级用户改变，或在我们的技术支持人员的指导下更改。因为如果这些选项配置不恰当，可能会影响到你的路由器性能。</p>
 <p><strong><em>Transmission (TX) Rates - </em></strong> 基于在WLAN（无线局域网）中无线网卡的速度选择基本的传输速率。</p>
 <p><strong><em>传输功率 - </em></strong>你可以通过选择较低的传输功率百分比值来降低<?query("/sys/modelname");?>的输出功率。你的选择有：100%, 50%, 25%, 和 12.5%。 </p>
 <p><strong><em>信标间隔 - </em></strong> 信标是由访问节点发送来同步无线网络的数据包。指定一个在20到1000之间的信标间隔值。默认值为100毫秒。 </p>

 <p><strong><em>RTS阀值 - </em></strong> 这个值应该保留其默认设置2346。如果你遇到不一致的数据流，你只需要将其值在256到2346之间作轻微的修改。RTS阀的默认值为2346。 </p>
 <p><strong><em>分段阀值 - </em></strong> 这个值应该保留其默认设置2346。如果你遇到很高的数据包错误率，你可以在范围1500到2346之间轻微的增加你的&quot;Fragmentation&quot;值。将分片值设置过小会导致性能降低。 </p>
 <p><strong><em>DTIM间隔 - </em></strong> 为DTIM设置的值应该在1到255之间。DTIM是告知到下一个侦听广播和多播的倒计时数。当访问节点已经为相关的客户缓存了广播或多播信息，它在一个DTIM间隔时间后发送下一个DTIM。AP客户收到信标并且被唤醒以接收广播和多播信息。DITM间隔的默认值为1。 </p>

 <p><strong><em>前导帧模式 - </em></strong> 前导帧模式定义了访问节点和漫游的无线适配器之间通讯的CRC块长度。请选择合适的前导帧模式并且点击应用按钮。</p>
 <p><span class="style2">注意： </span>高速网络流量的区域应该使用较短的前导帧模式。CRC是检测传输错误的常用技术。 </p>
 <p><strong><em>CTS模式 - </em></strong>选择None以禁止此项特性。选择Auto强制路由器要求网络上的每个无线设备都在允许传输数据前执行RTS/CTS握手。选择Auto以允许路由器决定什么时候执行RTS/CTS握手是必要的。 </p>
 <?if(query("/runtime/func/ieee80211n")!="1")
 { 
 	echo "<p><strong><em>802.11g Only Mode - </em></strong>如果你的无线网络只由802.11g设备组成，激活此种模式。如果你同时有802.11b和802.11g无线客户端，禁止此种模式。 </p> </td>\n";
 }
 ?>

 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=20><p><strong>高级网络设置 <a name=10></a></strong></p>

 <p>这部分包括可以改变路由器处理某些类型流量的方式的相关设置。我们建议你不要改变这些设置的任何部分，除非你对它们很熟悉或者曾经被我们的技术支持人员指导过改变它们。 </p>

<!--
 <p><strong>VPN Passthrough </strong><br>The device supports VPN (Virtual Private Network) passthrough for PPTP (Point-to-Point Tunneling Protocol) and IPSec (IP Security). Once VPN passthrough is enabled, there is no need to create any Virtual Server or Port Forwarding entries in order for outbound VPN sessions to establish properly. Multiple VPN connections can be made through the device. This is useful when you have many VPN clients on the Local Area Network. </p>
-->

 <p><strong>UPnP </strong><br>UPnP是通用即插即用的简称，它是为网络设备，软件和外围设备之间提供兼容性的一种网络架构。<?query("/sys/modelname");?>是支持UPnP的路由器，这意味着它可以同其他UPnP设备/软件协同工作。如果你不想使用UPnP功能，你可以选择&quot;不启用&quot;来禁用它。 </p>
 <p><strong>WAN Ping </strong><br>当你激活WAN Ping响应，你触使设备上的公共WAN端IP地址可以响应因特网用户的ping命令发出的数据包。ping公共的WAN端IP地址是被黑客们利用来检测WAN IP地址是否有效的常用手段。 </p>
 <p><strong>WAN端口速率 </strong><br>此选项允许你选择<?query("/sys/modelname");?>WAN端的速度：选择10Mbps, 100Mbps, or 10/100Mbps自动。 </p>
<!--
 <p><strong>Gaming Mode </strong><br>当你玩在线游戏或使用某些语音程序遇到困难时，你可能需要激活游戏模式以使这些应用程序正确地工作。当你不玩游戏或使用语音程序时，我们建议你将游戏模式禁用。 </p>
-->
 </tr>

<?if(query("/runtime/func/dis_multicast_stream")!="1"){
echo "<tr><td height=20>&nbsp;</td></tr>\n";
echo "<tr>\n";
echo "	<td height=20>\n";
echo "		<p>\n";
echo "			<strong>激活多播流</strong><br>\n";
echo "			激活此选项如果你从因特网上收到某些类型的视频服务。\n";
echo "			路由器使用IGMP协议支持有效的多播 －－传输同样的内容，比如说多媒体，从一个源到多个接收者。 \n";
echo "			如果任何程序在一个多播组中共享LAN，此选项就必须被激活。 \n";
echo "			如果你有一个多媒体应用程序没有按照期望的那样接收到内容，请尝试激活此选项。\n";
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
echo "	<td height=99><strong>路由 </strong><a name=11></a><br>\n";
echo "		这个路由选项允许你为指定的目的地址定义静态路由。<br>\n";
echo "		<strong><em>Enable </em></strong> - 指定此条目被激活或禁止。<br>\n";
echo "		<strong><em>Interface </em></strong> - 指定接口 －－WAN或物理WAN －－当路由被使用时，IP报文必须利用此接口发送出路由器<br>\n";
echo "		<strong><em>Interface (WAN)</em></strong> - 此接口接收从ISP分配的IP地址以访问因特网。<br>\n";
echo "		<strong><em>Interface (WAN Physical)</em></strong> - 此接口接收从ISP分配的IP地址以访问ISP。<br>\n";
echo "		<strong><em>Destination </em></strong> - 利用此路由的报文的IP地址。<br>\n";
echo "		<strong><em>Subnet Mask </em></strong> - IP地址子网掩码。 <br>\n";
echo "		<strong><em>Gateway </em></strong> - 指定此路由的下一跳。地址为0.0.0.0的网关意味着没有下一跳，匹配的IP地址被直接连接到WAN或物理WAN接口指定的路由器上。 \n";
echo " </td>\n";
echo " </tr>\n";
}
?>

 <tr>
 <td height=20>&nbsp;</td>
 </tr>

 </table>
