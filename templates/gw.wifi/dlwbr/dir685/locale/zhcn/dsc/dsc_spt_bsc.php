<div class="box">
<a name="internet_setup"><h2>Internet设置</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=40>
		<p>
			如果这是您第一次配置设备，我们建议您单击Internet连接设置向导，然后按照屏幕上的指示进行操作。如果您希望手动修改或配置设备的设置，单击手动设置Internet连接。
		</p>
	</td>
</tr>
<tr>
	<td height=59>
		<p>
			<strong>启动Internet连接设置向导</strong><br>
			单击此按钮，然后通过几个简单的步骤连接您的路由器到Internet。<br>
			<strong>启动无线安全设置向导</strong><br>
			单击此按钮对您路由器的无线网络进行设置，包括网络安全。
		</p>
	</td>
</tr>
<tr><td height=32>&nbsp;</td></tr>
<tr>
	<td height=46>
		<p>
			<strong>手动设置Internet连接</strong><br>
			选择此项，如果您想手动输入连接路由器到Internet的所需参数。
			<br>
			<strong>接入点模式</strong><br>
			启动&quot;接入点模式&quot;将使设备以无线AP的模式工作。此模式下，除了和无线连接相关的设置外，其它所有的NAT功能都将被禁用。
			<br>
			<strong>Internet连接类型</strong><br>
			Internet连接设置用于连接<?query("/sys/modelname");?>
			到Internet。您的ISP会向您提供在本页所需要输入的所有信息，通常为&quot;公共设置&quot;。
			请为您的自己ISP选择相应的选项。如果您不知道如何选择，请联系您的ISP。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=61>
		<p>
			<strong>静态IP地址</strong><br>
			如果您的ISP（Internet服务供应商）提供给您一个IP地址，子网掩码，缺省网关和一个DNS服务器地址，选择此项。请在相应的框中输入此信息。如果您不确定如何填写这些框，请联系您的ISP。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=142>
		<p>
			<strong>动态IP地址</strong><br>
			如果您的ISP（Internet服务供应商）提供给您的是动态IP地址，请选择此项。线缆调制解调器通常都使用动态分配IP地址。
		</p>
		<p>
			<strong><em>主机名</em></strong> （可选） -
			主机名框为可选，但是一些Internet服务供应商会要求输入此信息。缺省主机名为路由器的型号数字。
			<br>
			<strong><em>MAC地址</em></strong> （可选） -
			一些Internet服务供应商（ISP）会要求MAC（媒介访问控制）地址。
			缺省MAC地址是<?query("/sys/modelname");?>的WAN接口的MAC地址。
			您可以使用&quot;克隆MAC地址&quot;按钮复制正在配置此设备的计算机的网卡的MAC地址。只有在您的ISP要求时，才填写此框。
			<br>
			<strong><em>首选DNS地址</em></strong> -
			输入您的ISP提供给您的首选DNS（域名服务）服务器的IP地址。
			<br>
			<strong><em>备用DNS地址</em></strong> （可选） -
			如果您的ISP提供了备用DNS服务器的IP地址，在此填写。
			<br>
			<strong><em>MTU </em></strong> -
			MTU（最大传输/传送单元）是网络上能够传输的最大数据包大小。比MTU大的数据包将被分割为小的数据包。此项的缺省值为1500。改变此值将影响您的路由器的性能。只有在我们的技术支持代表或您的ISP指导下才能更改此数字。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=47>
		<p>
			<strong>PPPoE</strong><br>
			如果您的ISP要求您使用PPPoE（以太网上的点对点协议）连接，请选择此项。DSL供应商通常都使用此项。选择动态PPPoE，自动从您的PPPoE连接（用于大多数PPPoE连接）获取一个IP地址。选择静态PPPoE，为您的PPPoE连接设置一个静态的IP地址。
		</p>
		<p>
			<strong><em>用户名</em></strong> - 输入您的PPPoE用户名。<br>
			<strong><em>密码</em></strong> - 输入您的PPPoE密码。<br>
			<strong><em>服务名</em></strong> （可选） -
			如果您的ISP为PPPoE连接使用了一个服务名，请在此输入此服务名。<br>
			<strong><em>IP地址</em></strong> -
			此项只有在静态PPPoE时可用。为PPPoE连接输入静态IP地址。<br>
			<strong><em>MAC地址</em></strong> （可选） -
			一些Internet服务供应商（ISP）会要求MAC（媒介访问控制）地址。
			缺省MAC地址是<?query("/sys/modelname");?>的WAN接口的MAC地址。
			您可以使用&quot;克隆MAC地址&quot;按钮复制正在配置此设备的计算机的网卡的MAC地址。只有在您的ISP要求时，才填写此框。
			<br>
			<strong><em>首选DNS地址</em></strong> -
			首选DNS（域名服务）服务器IP地址，您的ISP可能会提供此信息。只有在您选择静态PPPoE时才需输入此信息。如果您选择动态PPPoE，保留此值不变，您的ISP会自动提供此信息。<br>
			<strong><em>备用DNS地址</em></strong> （可选） -
			如果您的ISP提供了备用DNS服务器的IP地址，在此填写。<br>
			<strong><em>最大空闲时间</em></strong> -
			设备断开PPPoE会话前，没有活动连接的时间（分钟）。输入一个最大空闲时间（分钟）来定义Internet连接在没有活动连接情况下保持的最长时间。如果连接没有活动会话的时间大于定义的最大空闲时间，连接将被断开。此选项只应用于按需连接模式下。
			<br>
			<strong><em>MTU </em></strong> -
			MTU（最大传输/传送单元）是网络上能够传输的最大数据包大小。比MTU大的数据包将被分割为小的数据包。此项的缺省值为1500。改变此值将影响您的路由器的性能。只有在我们的技术支持代表或您的ISP指导下才能更改此数字。
			<br>
			<strong><em>连接模式选择</em></strong> -
			选择始终在线，如果您希望路由器不断开PPPoE会话。选择手动，如果您希望控制路由器和Internet的连接和断开。按需连接选项允许路由器在有设备尝试访问Internet资源时自动建立连接。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>PPTP</strong><br>
			如果您的ISP使用PPTP（点对点隧道协议）连接并且分配给你一个用户名和密码用于访问Internet，选择此项。选择动态PPTP从您的PPTP连接动态获取一个IP地址。选择静态PPTP为您的PPTP连接使用一个静态IP地址。
		</p>
		<p>
			<strong><em>IP地址</em></strong> - 输入您的ISP分配给您的IP地址。<br>
			<strong><em>子网掩码</em></strong> - 输入您的ISP分配给你的子网掩码。<br>
			<strong><em>网关</em></strong> - 输入您的ISP分配给您的网关IP地址。<br>
			<strong><em>DNS - </em></strong>输入您的ISP分配给您的DNS地址。<br>
			<strong><em>服务器IP</em></strong> -
			输入你的ISP提供的用于连接的服务器IP地址。<br>
			<strong><em>帐户</em></strong> - 输入您的PPTP用户名。<br>
			<strong><em>密码</em></strong> - 输入您的PPTP密码。<br>
			<strong><em>最大空闲时间</em></strong> -
			设备断开PPPoE会话前，没有活动连接的时间（分钟）。输入一个最大空闲时间（分钟）来定义Internet连接在没有活动连接情况下保持的最长时间。如果连接没有活动会话的时间大于定义的最大空闲时间，连接将被断开。此选项只应用于按需连接模式下。
			<br>
			<strong><em>MTU </em></strong> -
			MTU（最大传输/传送单元）是网络上能够传输的最大数据包大小。比MTU大的数据包将被分割为小的数据包。此项的缺省值为1500。改变此值将影响您的路由器的性能。只有在我们的技术支持代表或您的ISP指导下才能更改此数字。
			<br>
			<strong><em>连接模式选择</em></strong> -
			选择始终在线，如果您希望路由器不断开PPPoE会话。选择手动，如果您希望控制路由器和Internet的连接和断开。按需连接选项允许路由器在有设备尝试访问Internet资源时自动建立连接。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>L2TP </strong><br>
			如果您的ISP使用L2TP（2层隧道协议）连接并且分配给你一个用户名和密码用于访问Internet，选择此项。选择动态L2TP从您的L2TP连接动态获取一个IP地址。选择静态L2TP为您的L2TP连接使用一个静态IP地址。
			</p>
		<p>
			<strong><em>IP地址</em></strong> - 输入您的ISP分配给您的IP地址。<br>
			<strong><em>子网掩码</em></strong> - 输入您的ISP分配给你的子网掩码。<br>
			<strong><em>网关</em></strong> - 输入您的ISP分配给您的网关IP地址。<br>
			<strong><em>DNS</em></strong> - 输入您的ISP分配给您的DNS地址。<br>
			<strong><em>服务器IP</em></strong> -
			输入你的ISP提供的用于连接的服务器IP地址。<br>
			<strong><em>L2TP帐户</em></strong> - 输入您的L2TP用户名。<br>
			<strong><em>L2TP密码</em></strong> - 输入您的L2TP密码。<br>
			<strong><em>最大空闲时间</em></strong> -
			设备断开PPPoE会话前，没有活动连接的时间（分钟）。输入一个最大空闲时间（分钟）来定义Internet连接在没有活动连接情况下保持的最长时间。如果连接没有活动会话的时间大于定义的最大空闲时间，连接将被断开。此选项只应用于按需连接模式下。
			<br>
			<strong><em>MTU</em></strong> -
			MTU（最大传输/传送单元）是网络上能够传输的最大数据包大小。比MTU大的数据包将被分割为小的数据包。此项的缺省值为1500。改变此值将影响您的路由器的性能。只有在我们的技术支持代表或您的ISP指导下才能更改此数字。
			<strong><em>连接模式选择</em></strong> -
			选择始终在线，如果您希望路由器不断开L2TP会话。选择手动，如果您希望控制路由器和Internet的连接和断开。按需连接选项允许路由器在有设备尝试访问Internet资源时自动建立连接。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>俄罗斯PPTP（双接入）</strong><br>
			配置俄罗斯PPTP Internet连接和先前描述的PPTP连接一致。如果您的ISP需要您配置静态路由，请参考&quot;高级&quot;菜单下的&quot;路由&quot;功能进行更多设置。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>俄罗斯PPPoE（双接入）</strong><br>
			一些PPPoE连接在连接的全局IP设置外使用一条静态的IP路由到ISP。这就需要一个添加步骤来为物理WAN端口定义IP设置。配置俄罗斯PPPoE Internet连接和先前描述的PPPoE连接一致，按照您ISP的指示来添加物理WAN IP设置。如果您的ISP需要您配置静态路由，请参考&quot;高级&quot;菜单下的&quot;路由&quot;功能进行更多设置。
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="wireless_setup"><h2>无线设置</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
		无线设置页面包含<?query("/sys/modelname");?>接入点部分的设置。
		此页面允许您自定义无线网络或配置<?query("/sys/modelname");?>以适合您现有的无线网络。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Wi-Fi保护设置（Windows Vista下也叫WCN 2.0）</strong><br>
			此特性为用户提供了一种比较直观的方式来设置无线安全。它有两种格式：PIN码和Push按钮。输入无线网卡工具或Windows Vista无线客户端工具（无线网卡需通过认证）上此设备的PIN码。Windows Vista将会自动设置路由器和客户端之间的无线安全。如需使用此特性，无线网卡需要支持Wi-Fi保护设置的任何一种格式。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>无线网络名</strong><br>
			也叫SSID（服务集标识），是您无线局域网（WLAN）的名字。
			<?query("/sys/modelname");?>的缺省SSID为“dlink”。
			可以轻松改变此值以创建一个新的无线网络或添加<?query("/sys/modelname");?>到已有的无线网络。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>无线信道</strong><br>
			指示<?query("/sys/modelname");?>的工作信道。缺省信道为6。
			可以改变此值以适应已有的无线网络或自定义您的新无线网络。
			单击启用自动扫描复选框，<?query("/sys/modelname");?>将自动选择工作的信道。
			推荐此项，路由器将选择干扰最小的信道。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>	
 		<p>
 			<strong>传输（TX）率</strong><br>
 			根据WLAN（无线局域网）上无线网卡的速率来选择基本的传输率。 
 		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>WMM</strong><br>
			选择启用，为<?query("/sys/modelname");?>的无线接口打开QoS。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>启用隐藏无线</strong><br>
			选择启用，如果您不希望<?query("/sys/modelname");?>广播您的无线网络SSID。
			如果启用此项，站点搜索工具将不能搜索到<?query("/sys/modelname");?>的SSID，
			所以当您设置无线客户端时，您需要知道您<?query("/sys/modelname");?>的SSID，
			然后在客户端上手动输入才能连接到路由器。此项缺省为启用。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>无线安全模式</strong><br>
			保护您的无线网络安全是非常重要的，因为它保护无线网络上所传输信息的完整性。
			<?query("/sys/modelname");?>提供4种类型的无线安全：WEP，仅使用WPA，仅使用WPA2和WPA/WPA2（自动）
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>WEP </strong><br>
			有线等效协议（WEP）是无线局域网（WLAN）上的一种无线安全协议。
			WEP通过加密为WLAN上传输的数据提供安全。
			<?query("/sys/modelname");?>支持2个等级的WEP加密：64位和128位。WEP缺省为禁用。
			可以更改WEP设置以适应现有的无线网络或自定义您的无线网络。
		</p>
		<p>
			<strong><em>认证</em></strong> -
			认证是<?query("/sys/modelname");?>对尝试加入无线网络的网络设备进行确认的过程。使用WEP时，此设备提供两种类型的认证。
			<br> 
			<strong><em>开放系统</em></strong> -
			选择此项允许所有无线设备在被提示输入访问网络所需加密密钥前可以和<?query("/sys/modelname");?>通信。<br>
			<strong><em>共享密钥</em></strong> -
			选择此项将在和<?query("/sys/modelname");?>通信前提示任何尝试访问<?query("/sys/modelname");?>的无线设备输入访问网络所需的加密密钥。<br>
			<strong><em>WEP加密</em></strong> -
			选择您网络所需的WEP加密等级。支持两种等级的WEP加密，64位和128位。<br>
			<strong><em>密钥类型</em></strong> -
			<?query("/sys/modelname");?>支持的密钥类型有HEX（十六进制）和ASCII（美国标准信息交换码）。可以更改密钥类型以适应已有的无线网络或自定义您的无线网络。
			<br>
			<strong><em>密钥</em></strong> -
			密钥1-4允许您轻松地改变无线加密设置以保持网络的安全。只需简单地选择用于在网络上对无线数据进行加密的密钥即可。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>WPA/WPA2</strong><br>
			Wi-Fi保护访问（或Wi-Fi保护访问2）对访问无线网络的用户进行认证和授权。WPA使用比WEP更强的加密安全，它基于一个定期自动更换的密钥。
		</p>
		<p>
			<strong><em>加密类型</em></strong> -
			使用WPA为安全类型时，<?query("/sys/modelname");?>支持两种不同的加密类型。两种类型为TKIP（临时密钥完整性协议）和AES（高级加密标准）。
			<br>
			<strong><em>PSK/EAP</em></strong> -
			选择PSK时，您的无线客户端需要提供一个密码短语用于认证。选择EAP时，您网络上需要一个RADIUS服务器用于处理所有无线客户端的认证。
			<br>
			<strong><em>密码短语</em></strong> -
			当选择PSK时，您的无线客户端需要输入一个8-63位的字符串用于和<?query("/sys/modelname");?>进行通信。
			请记下这个密码短语，因为当您添加其它无线设备到您的网络时，您需要输入此密码短语。
			<br>
			<strong><em>802.1X</em></strong> -
			这表示WPA认证将和网络上的RADIUS服务器配合使用。输入您RADIUS服务器配置的IP地址，端口和共享密钥。如果您网络上有两个RADIUS服务器用于认证无线客户，您也可以输入第二个RADIUS服务器的信息。
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="lan_setup"><h2>网络设置</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			这些是设备LAN（局域网）接口的设置。这些设置也叫&quot;私有设置&quot;。如果需要，您可以改变LAN IP地址。LAN IP地址在您的内部网络是私有的，不能从Internet上看到。缺省IP地址为192.168.0.1，子网掩码255.255.255.0。
			<br><br>
			<strong><em>IP地址</em></strong> -
			<?query("/sys/modelname");?>的IP地址，缺省为192.168.0.1。<br>
			<strong><em>子网掩码</em></strong> -
			<?query("/sys/modelname");?>的子网掩码，缺省为255.255.255.0。<br>
			<strong><em>本地域名</em></strong> (可选）- 为您的网络输入本地域名。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong><em>DNS中继</em></strong> -
			启用DNS中继后，路由器DHCP客户端的DNS服务器将被分配为路由器LAN的IP地址。路由器接收到的所有DNS请求都会被转发到您ISP的DNS服务器上。如果禁用DNS中继，路由器所有DHCP客户端会被分配ISP的DNS服务器。	
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>DHCP服务器</strong><br>
			DHCP是动态主机控制协议。DHCP服务器分配IP地址给网络上请求IP地址的设备。
			这些设备必须被设置为&quot;自动获取IP地址&quot;。
			缺省下，<?query("/sys/modelname");?>的DHCP服务器为启用。
			DHCP地址池包括一组可以动态分配给网络上客户端的IP地址。
		</p>
		<p>
			<strong>DHCP保留</strong><br>
			手动为需要静态分配相同IP的计算机输入&quot;计算机名&quot;，
			&quot;IP地址&quot;和&quot;MAC地址&quot;或从显示当前DHCP客户端的下拉菜单里选择PC。
		</p>
		<p>
			<strong><em>起始IP地址</em></strong> DHCP服务器IP分配的起始IP地址。<br>
			<strong><em>结束IP地址</em></strong> DHCP服务器IP分配的结束IP地址。<br>
			<strong><em>租约时间</em></strong> IP租用的时间长。
		</p>
		<p>
			动态DHCP客户表将会显示连接到设备上的动态DHCP客户计算机的相关信息。此表将显示每个客户计算机的主机名，IP地址，MAC地址和DHCP租约剩余时间。
		</p>
	</td>
</tr>
</table>
</div>

<div class="box">
<a name="lcd_setup"><h2>LCD设置</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			LCD设置页面控制您的<?query("/sys/modelname");?>设备的显示面板设置。
			此页面允许您控制屏保和调整LCD屏幕关闭前设备需要空闲的时间长。
		<br><br>
			<strong><em>屏保设置</em></strong> -
			屏保将会在背景上显示存储在内置硬盘根目录下的&quot;screen_bg.jpg&quot;图片，
			并且在图片上随机移动显示当前日期和时间。如果没有找到此图片，
			背景将保持黑色。&quot;超时&quot;设置显示了设备空闲时，进入屏保模式所需要的时间。
			如果触摸板上的任何按钮被按下，设备将退出屏保模式。
			<br>
			<strong><em>显示设置</em></strong> -
			当设备空闲时间达到&quot;超时&quot;框中配置的时间值后，
			此设置将关闭LCD显示以节省电源。
			如果任何触摸按钮被按下，LCD显示屏将重新开启。
			<br>
		</p>
	</td>
</tr>
</table>
</div>
