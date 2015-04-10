<h1>支持菜单</h1>
<table border=0 cellspacing=0 cellpadding=0 width=750>
<tr>
	<td height=40>
		<p><font size=4><strong>安装</strong></font></p>
		<p>
			<a name=01><strong>安装因特网</strong></a><br>
			如果您是第一次配置设备，我们强烈推荐您点击因特网连接安装向导，
			跟随屏幕上的步骤来进行。如果您想手动配置或修改设备的设定，请点击手动因特网连接安装。
		</p>
	</td>
</tr>
<tr>
	<td height=59>
		<p>
			<strong>运行因特网连接安装向导 </strong><br>
			点击该按钮让您通过几个简单的步骤将您的路由器连接到因特网。<br>
			<strong>运行无线连接安装向导 </strong><br>
			点击该按钮让您的路由器通过配置您无线网络的设置来建立无线安全。
		</p>
	</td>
</tr>
<tr><td height=32>&nbsp;</td></tr>
<tr>
	<td height=46>
		<p>
			<strong>手动因特网连接安装</strong><br>
			如果您想通过手动输入需要的设置来将您的路由器连接到因特网，请选择该选项。<br>
			<strong>接入点模式</strong><br>
			开启&quot;接入点模式&quot;将会使设备具有无线AP的功能。除了无线所需的相关设定外，所有的NAT功能将被禁用。<br>
			<strong>因特网连接类型 </strong><br>
			因特网连接设置被用于将<?query("/sys/modelname");?>连接到因特网。
			在此页面上的任何信息都会由你的因特网服务商给您提供，并且经常被作为&quot;公共设置&quot;。
			请为您指定的因特网服务商选择合适的选项。如果你不能确定选择哪些项目，请联系您的因特网服务商。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=61>
		<p>
			<strong>静态IP地址</strong><br>
			如果您的ISP（因特网服务商）已经给你提供了一个IP地址，子网掩码，默认网关，以及一个DNS服务器地址，请选择这一项。
			将这些信息填入相应的区域。如果你不能确定这些区域该如何填入，请联系您的因特网服务商。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=142>
		<p>
			<strong>动态IP地址</strong><br>
			如果您的ISP（因特网服务商）给你提供的是自动获取的IP地址，请选择这一项。
			宽带调制解调器提供商通常使用动态获取IP地址。
		</p>
		<p>
			<strong><em>主机名 </em></strong> (可选) -
			主机名是一个可选字段，但是有一些因特网服务商需要它。
			默认的主机名是这个路由器的模块编号。<br>
			<strong><em>MAC地址</em></strong> (可选) -
			一些因特网服务商（ISP）需要MAC（媒体访问控制）地址字段。
			默认的MAC地址被设置为<?query("/sys/modelname");?> WAN端接口的MAC地址。
			您可以使用&quot;复制MAC地址&quot;按钮自动地将您电脑上安装的以太网卡MAC地址复制到设备以用于配置。
			除非您的因特网服务商要求，你才有必要填充该字段。<br>
			<strong><em>首选DNS地址 </em></strong> -
			输入由您的因特网服务商提供的首选DNS（域名服务）服务器IP地址。<br>
			<strong><em>备选DNS地址 </em></strong> (可选) -
			如果您的因特网服务商给您提供了一个备选DNS服务器IP地址，请将其填入此域。<br>
			<strong><em>MTU </em></strong> -
			MTU（最大传输单元）是网络上可传输的最大报文尺寸。
			当传输的报文大于MTU，报文会被分成更小的包。1500是此选项的默认值。
			改变MTU的数值可能会给您的路由器性能带来负面影响。
			仅当在我们的技术支持人员或您的因特网服务商指导下更改此数值。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=47>
		<p>
			<strong>PPPoE</strong><br>
			如果您的因特网服务商要求您使用PPPoE（以太网上的点到点协议）连接，请选择此选项。
			DSL提供商通常会使用此项。选择动态PPPoE为您的PPPoE连接自动获取一个IP地址（大多数PPPoE连接使用）。
			选择静态PPPoE为您的PPPoE连接使用一个静态IP地址。
		</p>
		<p>
			<strong><em>用户名 </em></strong> - 输入您的PPPoE用户名。<br>
			<strong><em>密码 </em></strong> - 输入您的PPPoE密码。<br>
			<strong><em>服务名称 </em></strong> (可选) -
			如果您的因特网服务商为PPPoE连接使用了一个服务名称，请将服务名称在这里输入。<br>
			<strong><em>IP地址 </em></strong> -
			此选项只对静态PPPoE有效。请为PPPoE连接输入静态IP地址。<br>
			<strong><em>MAC地址 </em></strong> (可选) -
			一些因特网服务商（ISP）需要MAC（媒体访问控制）地址字段。
			默认的MAC地址被设置为<?query("/sys/modelname");?> WAN端接口的MAC地址。
			您可以使用&quot;复制MAC地址&quot;按钮自动地将您电脑上安装的以太网卡MAC地址复制到设备以用于配置。
			除非您的因特网服务商要求，你才有必要填充该字段。<br>
			<strong><em>首选DNS地址 </em></strong> -
			输入由您的因特网服务商提供的首选DNS（域名服务）服务器IP地址。
			仅当您选择了静态PPPoE时，才应该需要输入此域。
			如果动态PPPoE被选中，请保持此域为默认值，因为您的因特网服务商会自动为您提供。<br>
			<strong><em>备选DNS地址 </em></strong> (可选) -
			如果您的因特网服务商给您提供了一个备选DNS服务器IP地址，请将其填入此域。<br>
			<strong><em>最大空闲时间 </em></strong> -
			设备断开您的PPPoE会话的空闲最大时间数。
			输入最大空闲时间（分钟）以定义因特网连接保持在空闲状态的最长时间。
			如果连接保持在空闲状态的时间大于定义的最大空闲时间，连接将会断开。
			此选项仅应用于连接需求模式。<br>
			<strong><em>MTU </em></strong> -
			MTU（最大传输单元）是网络上可传输的最大报文尺寸。
			当传输的报文大于MTU，报文会被分成更小的包。1492是此选项的默认值。
			改变MTU的数值可能会给您的路由器性能带来负面影响。
			仅当在我们的技术支持人员或您的因特网服务商指导下更改此数值。<br>
			<strong><em>连接模式选择</em></strong> -
			选择总是连接，如果你希望路由器永远不断开PPPoE连接。
			选择手动，如果你希望手动控制路由器连接或断开连接到因特网。
			连接需求模式允许路由器建立到因特网的连接，仅当在您的网络上的一个设备试图访问因特网上的资源时。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>PPTP</strong><br>
			选择此选项，如果您的因特网服务商使用PPTP（点到点隧道协议）连接并且给您分配了一个用户名和密码以访问因特网。
			选择动态PPTP自动地从您的PPTP连接上获取一个IP地址。
			选择静态PPTP为您的PPTP连接使用一个静态IP地址。
		</p>
		<p>
			<strong><em>IP地址 </em></strong> - 输入由您的因特网服务商分配给您的IP地址。<br>
			<strong><em>子网掩码 </em></strong> - 输入由您的因特网服务商分配给您的子网掩码。<br>
			<strong><em>网关</em></strong> - 输入由您的因特网服务商分配给您的网关。<br>
			<strong><em>DNS - </em></strong>输入由您的因特网服务商分配给您的DNS地址。<br>
			<strong><em>服务IP </em></strong> -
			输入由您的因特网服务商提供的服务器IP地址，您将会连接到此地址。<br>
			<strong><em>帐号 </em></strong> - 输入您的PPTP用户名。<br>
			<strong><em>密码 </em></strong> - 输入您的PPTP密码。<br>
			<strong><em>最大空闲时间 </em></strong> -
			设备断开您的PPTP会话的空闲最大时间数。
			输入最大空闲时间（分钟）以定义因特网连接保持在空闲状态的最长时间。
			如果连接保持在空闲状态的时间大于定义的最大空闲时间，连接将会断开。
			此选项仅应用于连接需求模式。<br>
			<strong><em>MTU </em></strong> -
			MTU（最大传输单元）是网络上可传输的最大报文尺寸。
			当传输的报文大于MTU，报文会被分成更小的包。1400是此选项的默认值。
			改变MTU的数值可能会给您的路由器性能带来负面影响。
			仅当在我们的技术支持人员或您的因特网服务商指导下更改此数值。<br>
			<strong><em>连接模式选择</em></strong> -
			选择总是连接，如果你希望路由器永远不断开PPTP会话。
			选择手动，如果你希望手动控制路由器连接或断开连接到因特网。
			连接需求模式允许路由器建立到因特网的连接，仅当在您的网络上的一个设备试图访问因特网上的资源时。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>L2TP </strong><br>
			选择此选项，如果您的因特网服务商使用L2TP（二层隧道协议）连接并且给您分配了一个用户名和密码以访问因特网。
			选择动态L2TP自动地从您的L2TP连接上获取一个IP地址。
			选择静态L2TP为您的L2TP连接使用一个静态IP地址。
		</p>
		<p>
			<strong><em>IP地址 </em></strong> -输入由您的因特网服务商分配给您的IP地址。<br>
			<strong><em>子网掩码 </em></strong> -输入由您的因特网服务商分配给您的子网掩码。<br>
			<strong><em>网关</em></strong> - 输入由您的因特网服务商分配给您的网关。<br>
			<strong><em>DNS</em></strong> - 输入由您的因特网服务商分配给您的DNS地址。<br>
			<strong><em>服务IP </em></strong> -
			输入由您的因特网服务商提供的服务器IP地址，您将会连接到此地址。<br>
			<strong><em>L2TP 帐号 </em></strong> - 输入您的L2TP用户名。<br>
			<strong><em>L2TP 密码 </em></strong> - 输入您的L2TP密码。<br>
			<strong><em>最大空闲时间 </em></strong> -
			设备断开您的L2TP会话的空闲最大时间数。
			输入最大空闲时间（分钟）以定义因特网连接保持在空闲状态的最长时间。
			如果连接保持在空闲状态的时间大于定义的最大空闲时间，连接将会断开。
			此选项仅应用于连接需求模式。<br>
			<strong><em>MTU</em></strong> -
			MTU（最大传输单元）是网络上可传输的最大报文尺寸。
			当传输的报文大于MTU，报文会被分成更小的包。1400是此选项的默认值。
			改变MTU的数值可能会给您的路由器性能带来负面影响。
			仅当在我们的技术支持人员或您的因特网服务商指导下更改此数值。
			<strong><em>连接模式选择</em></strong> -
			选择总是连接，如果你希望路由器永远不断开L2TP会话。
			选择手动，如果你希望手动控制路由器连接或断开连接到因特网。
			连接需求模式允许路由器建立到因特网的连接，仅当在您的网络上的一个设备试图访问因特网上的资源时。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<a name=02><strong>无线安装</strong></a><br>
			无线安装页面包括对<?query("/sys/modelname");?>（访问节点）部分的设置。
			此页面允许你定制您的无线网络或配置<?query("/sys/modelname");?>到一个已经安装好的无线网络中。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Wi-Fi保护安装 (也叫Windows Vista中的WCN 2.0)</strong><br>
			这个特性为用户提供了设置无线安全更直观的方法。
			它由两种格式组成：PIN号和按钮。如果无线网卡有被认证的Windows Vista驱动，
			输入无线网卡工具或Windows Vista无线客户端工具附带的PIN号，可以自动
			地在路由器和客户端之间设置无线安全。无线网卡将不得不用两种格式之一
			支持Wi-Fi保护安装以利用这个特性。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>无线网络名称</strong><br>
			也被叫做SSID（服务集标志符），这是您的无线局域网（WLAN）的名称。
			<?query("/sys/modelname");?>默认的SSID为&quot;dlink&quot;。
			此字段可以很容易被改变以建立一个新的无线网络或将<?query("/sys/modelname");?>添加到一个存在的无线网络中。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>无线信道</strong><br>
			指定了<?query("/sys/modelname");?>通信的信道。默认的信道是6。
			此字段可以被改变以适应一个已存在的无线网络的信道设置，或用于定制您自己的新的无线网络。
			点击启动自动信道选择框让<?query("/sys/modelname");?>自动地选择其通信的信道。
			推荐选择此选项，因为路由器会选择有最少冲突的信道。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>WMM</strong><br>
			选择启用为<?query("/sys/modelname");?>的无线接口打开QoS。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>启用隐藏无线 </strong><br>
			选择启用，如果您不希望您的无线网络SSID被<?query("/sys/modelname");?>广播。&nbsp;
			如果此选项被启用，<?query("/sys/modelname");?>的SSID将不会被站点检测工具所看见，
			所以当设置您的无线客户端时，您不得不知晓<?query("/sys/modelname");?>的SSID，然后手动地
			输入以连接到路由器上。这个选项默认被启用。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>无线安全模式</strong><br>
			安全化您的无线网络是很重要的，其被用于保护您的无线网络上信息传输的完整性。
			<?query("/sys/modelname");?>具有4种类型的无线安全；
			WEP,仅有WPA，仅有WPA2，以及WPA/WPA2（自动检测）
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>WEP </strong><br>
			有线等效保密协议（WEP）是为无线局域网（WLAN）提供的一种无线安全协议。
			WEP通过加密在WLAN上传送的数据来提供安全保护。
			<?query("/sys/modelname");?>支持两种级别的WEP加密：64位和128位。WEP默认是被禁用的。
			WEP设置可以被改变以适应一个已存在的无线网络，或用于定制您自己的无线网络。
		</p>
		<p>
			<strong><em>认证</em></strong> -
			认证是<?query("/sys/modelname");?>用于检验试图加入无线网络的无线网卡身份的一个过程。
			当使用WEP时，有两种类型的认证方式。<br> 
			<strong><em>开放系统</em></strong> -
			选择此选项，允许所有的无线设备在被要求提供加密密钥访问之前，都可以和<?query("/sys/modelname");?>通讯。<br>
			<strong><em>共享密钥</em></strong> -
			选择此选项，要求任何想和<?query("/sys/modelname");?>通讯的无线设备都要提供加密密钥，
			才能允许与<?query("/sys/modelname");?>通讯。<br>
			<strong><em>WEP加密</em></strong> -
			选择用于您网络上的WEP加密的级别。
			这两种支持的WEP加密级别是64位和128位。<br>
			<strong><em>密钥类型</em></strong> -
			<?query("/sys/modelname");?>支持的密钥类型是HEX（十六进制）和ASCII（美国标准信息交换码）。
			密钥类型可以被改变以适应一个已存在的无线网络，或用于定制您自己的无线网络。<br>
			<strong><em>密钥</em></strong> -
			密钥1到密钥4允许你很容易地改变加密设置以维护一个安全的网络。
			简单地选择指定的用于加密无线网络数据的密钥。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>个人WPA</strong><br>
			Wi-Fi保护访问 认证和授权无线网络上的用户。
			WPA使用了比WEP更强的安全机制，它基于在一个常规时间间隔自动改变的密钥。
		</p>
		<p>
			<strong><em>密码类型</em></strong> -
			当WPA被用作安全类型时，<?query("/sys/modelname");?>支持两种不同类型的密码类型。
			这两种类型是：TKIP（临时密钥完整性协议）和AES（高级加密标准）。<br>
			<strong><em>PSK/EAP</em></strong> -
			当PSK被选择，您的无线客户端需要提供一个网络密钥用于认证。
			当EAP被选择，您需要在您的网络上有一个RADIUS服务器用于处理所有无线客户端的认证。<br>
			<strong><em>网络密钥</em></strong> -
			当选择了PSK时，您的无线客户端需要网络密钥来连接您的<?query("/sys/modelname");?>。
			请确定您输入的网络密钥，您也需要在任何其他您想加入此网络的无线设备上将其输入。<br>
			<strong><em>802.1X</em></strong> -
			这意味着WPA认证也可以和您网络上存在的RADIUS服务器协同使用。
			输入您为RADIUS服务器配置的IP地址，端口号，以及共享秘密。
			甚至如果在您的网络上有两个用于无线客户认证的RADIUS服务器，您也可以输入第二个RADIUS服务器的相关信息。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>WPA2</strong><br>
			Wi-Fi保护访问2 认证和授权无线网络上的用户。
			WPA2使用了比WEP更强的安全机制，它基于在一个常规时间间隔自动改变的密钥。
		</p>
		<p>
			<strong><em>密码类型</em></strong> -
			当WPA被用作安全类型时，<?query("/sys/modelname");?>支持两种不同类型的密码类型。
			这两种类型是：TKIP（临时密钥完整性协议）和AES（高级加密标准）。<br>
			<strong><em>PSK/EAP</em></strong> -
			当PSK被选择，您的无线客户端需要提供一个网络密钥用于认证。
			当EAP被选择，您需要在您的网络上有一个RADIUS服务器用于处理所有无线客户端的认证。<br>
			<strong><em>网络密钥</em></strong> -
			当选择了PSK时，您的无线客户端需要网络密钥来连接您的<?query("/sys/modelname");?>。
			输入8到63个数字字母字符。
			请确定您输入的网络密钥，您也需要在任何其他您想加入此网络的无线设备上将其输入。 
			<strong><em>802.1X</em></strong> -
			这意味着WPA2认证也可以和您网络上存在的RADIUS服务器协同使用。
			输入您为RADIUS服务器配置的IP地址，端口号，以及共享秘密。
			甚至如果在您的网络上有两个用于无线客户认证的RADIUS服务器，您也可以输入第二个RADIUS服务器的相关信息。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
 	<td height=20>
		<p>
			<strong>自动WPA2</strong><br>
			此选项允许<?query("/sys/modelname");?>让WPA2和WPA客户端都可以同时连接到它。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<a name=03><strong>局域网安装</strong></a><br>
			这些是设备的LAN（局域网）接口设置。
			这些设置也被称作&quot;私有设置&quot;。如果需要你可以改变LAN端IP地址。
			LAN端IP地址对您的内部网络是私有的，并且在因特网上不可见。
			默认的IP地址是192.168.0.1，子网掩码是255.255.255.0。<br><br>
			<strong><em>IP地址</em></strong> -
			<?query("/sys/modelname");?>的IP地址，默认是192.168.0.1。<br>
			<strong><em>子网掩码</em></strong> -
			<?query("/sys/modelname");?>子网掩码，默认是255.255.255.0。<br>
			<strong><em>本地域名</em></strong> (可选) - 输入您的网络的本地域名。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong><em>DNS中继</em></strong> -
			当DNS中继被启用，路由器的DHCP客户端将会被赋予路由器的LAN端IP地址作为它们的DNS服务器。
			路由器收到的所有的DNS请求将会被转发到您的因特网提供商的DNS服务器上。
			当DNS中继被禁用，路由器的所有的DHCP客户端将会被赋予因特网服务商的DNS服务器作为它们的DNS服务器。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>DHCP服务器</strong><br>
			DHCP即动态主机控制协议。DHCP服务器为网络上的设备分配IP地址。
			这些设备必须被设置为&quot;自动获取IP地址&quot;。
			默认的，DHCP服务器在<?query("/sys/modelname");?>上被启用。
			DHCP地址池包括自动分配给网络上客户端的IP地址范围。
		</p>
		<p>
			<strong>DHCP保留</strong><br>
			手动输入您希望路由器静态分配IP的PC的&quot;计算机名&quot;，&quot;IP地址&quot;以及&quot;MAC地址&quot;，
			或者从显示当前DHCP客户端的下拉菜单中选择PC。
		</p>
		<p>
			<strong><em>开始IP地址</em></strong> DHCP服务器分配的IP地址的开始IP地址。<br>
			<strong><em>结束IP地址</</em></strong> DHCP服务器分配的IP地址的结束IP地址。<br>
			<strong><em>租用时间</em></strong> IP租用时长，分钟数。
		</p>
		<p>
			连接到路由器的动态DHCP客户端计算机将会在DHCP客户端表中显示它们的信息。
			这个表会为每个客户端计算机显示主机名称，IP地址，MAC地址，终止时间。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=33>
		<p>
			<strong><a name=04>时间和日期</a></strong>
		</p>
		<p>
			时间配置设置被用于同步计划表服务和系统日志活动。
			你需要设置与您的位置对应的时区。
			时间可以被手动设置，或者由设备连接到NTP（网络时间协议）服务器来得到。
			你也可以设置夏时制，系统时间会就会自动调整。
		</p>
		<p>
			<strong><em>时区</em></strong> - 选择您所在区域的时区。<br>
			<strong><em>夏时制</em></strong> -
			如果你所在区域有夏时制，激活此选项并且指定开始和结束月，周，日，以及时间。<br>
			<strong><em>自动时间配置</em></strong> -
			选择你要<?query("/sys/modelname");?>同步时间的D-Link时间服务器。
			<?query("/sys/modelname");?>与D-Link NTP服务器通讯的时间间隔是7天。<br>
			<strong><em>手动设置日期和时间</em></strong> -
			如果你想手动指定时间，选择此选项。你必须指定年，月，日，时，分，以及秒，
			或者点击复制您计算机的时间设置按钮，复制用于访问当前管理界面的计算机上的系统时间。
		</p>
	</td>
</tr>
<tr><td height=2>&nbsp;</td></tr>
<tr><td height=2>&nbsp;</td></tr>
<tr>
	<td height=44>
		<p>
			<strong><a name=05>家长控制</a></strong>
		</p>
		<p>
			同过滤访问您的网络和因特网的网络设备一样的能力，<?query("/sys/modelname");?>也可以通过指定域名或关键字，
			允许或阻止您网路上的计算机访问不合适的网站。
		</p>
		<p>
			<strong>父母控制</strong><br>
			父母控制可以通过指定的关键字或域名，允许或阻止您网络上的计算机访问指定的网站。
			选择&quot;打开父母控制功能，允许计算机访问这些网站&quot;仅允许您网络上的计算机访问指定的URL和域名。
			选择&quot;打开父母控制功能，拒绝计算机访问这些网站&quot;阻止您网络上的计算机访问指定的URL和域名。
		</p>
		<p>
			<span class="style1">例 1：</span><br>
			如果您想阻止LAN用户访问任何与shopping有关的网站URL，您需要选择&quot;打开父母控制功能，拒绝计算机访问这些网站&quot;
			然后输入&quot;shopping&quot;到网站过滤规则列表中。这样，类似下面的网站LAN用户都不能访问，因为在URL中包含了关键字shopping。<br>
			http://shopping.yahoo.com/<br>
			http://shopping.msn.com/
		</p>
		<p>
			<span class="style1">例 2：</span><br>
			如果您想您的孩子只能访问特定的网站，您可以选择&quot;打开父母控制功能，允许计算机访问这些网站&quot;，
			然后输入您想让您的孩子只能访问的网站URL。
		</p>
		<ul>
			<li>Google.com </li>
			<li>Cartoons.com </li>
			<li>Discovery.com </li>
		</ul>
	</td>
</tr>
</table>
