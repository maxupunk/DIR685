<h1>支持菜单</h1>
<table border=0 cellspacing=0 cellpadding=0 width=750>
<tr>
<td height=2><b><font size=4>维护</font></b></td>
</tr>
<tr>
<td height=16><p><br>
</td>
</tr>
<tr>
	<td height=20>
		<strong>设备管理</strong><a name=12></a><br>
		<p>
			<strong><em>登录名称</em></strong> -
			输入登录到路由器的管理员的名称。
		</p>
		<p>
			<strong><em>新的密码</em></strong> -
			输入管理员帐号访问路由器管理页面的密码和确认密码。
		</p>
		<p>
			<strong>远程管理</strong><br>
			远程管理允许使用网页浏览器从因特网通过WAN端口来配置设备。
			访问路由器的管理页面仍然需要一个用户名和密码。<br>
			<strong><em>允许访问的IP</em></strong> -
			该选项允许用户指定一个特定的IP地址，可通过因特网对路由器进行远程访问。
			该字段的缺省值为空，这意味着当远程管理被开启后，因特网上的所有IP都可以访问路由器。<br>
			<strong><em>端口</em></strong> - 选择将用来访问<?query("/sys/modelname");?>的端口。
		</p>
		<p>
			<strong><em>例如：</em></strong><br>
			在http://x.x.x.x:8080 中， x.x.x.x是
			<?query("/sys/modelname");?>的WAN IP地址，8080是用来访问网页管理界面的端口。
		</p>
	</td>
</tr>
<tr><td height=10>&nbsp;</td></tr>
<tr><td height=10>&nbsp;</td></tr>
<tr>
	<td height=40>
		<a name=14><strong>保存并恢复</strong></a><br>
		当前系统设定可作为一个文件被保存在本地硬盘上。保存的文件或设备创建的其他设置文件可加载到设备中。
		要加载系统设置文件，点击"浏览"在本地硬盘中搜索要使用的文件。设备也可通过点击<strong>恢复出厂设置</strong>被恢复到出厂设置。
		只有在必要的时候才使用恢复出厂设置。它会清除掉设备上所有预先的设置。在恢复到出厂设置之前请确保已将系统的设定进行了保存。<br>
		<strong><em>保存</em></strong> - 点击该按钮将保存路由器的配置文件。<br>
		<strong><em>浏览</em></strong> -
		点击浏览定位配置文件，然后点击上传将这些设定应用到路由器。<br>
		<strong><em>恢复出厂设置</em></strong> -
		点击该按钮将设备恢复到出厂缺省设置。
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=51>
		<b>固件更新</b><a name=15></a><br> 
		您可以使用此工具来更新设备的固件。
		请确保您想用来升级的固件已保存在了计算机的本地硬盘上。点击<strong>浏览</strong>
		在本地硬盘中搜索要用来更新的固件。
		更新固件将不会对您系统的设置造成任何更改，但推荐您在更新之前将您系统的设置进行保存。
		请在D-Link<a href=<?query("/sys/supporturl");?>>技术支持站点</a>
		查询相关固件的更新，或者您也可以点击<strong>立即检测</strong>按钮让设备自动检查新的固件。
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=2>
		<p>
			<strong>DDNS 设置 </strong><a name=16></a><br>
			动态DNS（域名服务器）可让域名随着变换的（动态）IP地址而变化。
			大多数使用线缆或DSL连接时，您都被分配了一个动态的IP地址，
			且这个IP地址仅用于当前此次的连接。通过<?query("/sys/modelname");?>，
			您可以设置您的DDNS服务在每次接收到新的WAN IP地址时自动更新你的DDNS服务器。<br>
			<strong><em>服务器地址</em></strong> - 从下拉菜单中选择您的DDNS提供商。<br>
			<strong><em>主机名称</em></strong> - 输入通过您的DDNS服务提供商注册的主机名。<br>
			<strong><em>用户名称</em></strong> - 输入您DDNS帐号的用户名。<br>
			<strong><em>密码</em></strong> - 输入您DDNS帐号的密码。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height="197">
		<p>
			<strong>系统检查</strong><a name=17></a><br>
			该工具可用来检查LAN和WAN接口的物理连接。
			这是一个在路由器的每个以太网端口上结合一个LAN线缆测试器的高级功能。
			通过图形用户界面（GUI），线缆测试可用来远程诊断并报告线缆的故障，诸如断开，短路，交换和阻抗失配。
			该功能显著降低了服务电话的通讯量，并让用户可以轻松的解决线缆连接问题。
		</p>
		<p>
			<strong>Ping 测试</strong><br>
			这是一个十分有用的诊断性功能，可用来确定一台计算机是否在因特网上。
			它向一台指定的主机发送ping数据包，并接收回复。
			输入您想ping的主机名或IP地址然后点击<strong>Ping </strong>。
			Ping的状态将会在ping结果对话框中显示出来。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td>
		<p>
			<strong>调试进程<a name=18></a></strong></p>
			该页用来配置路由器的全局计划表。
			定义好后，这些计划表将被应用于路由器上支持计划表的功能上。<br>
			<strong><em>名称</em></strong> - 定义的计划表的名称。<br>
			<strong><em>天</em></strong> -
			选择天（数），或选择“整个星期”复选框让该计划表应用到每一天。<br>
			<strong><em>全天 - 24 小时</em></strong> -
			选择该选项让计划表在指定的天数全天24小时都生效。<br>
			<strong><em>开始时间</em></strong> -
			选择您希望该计划表生效的时间。<br>
			<strong><em>结束时间</em></strong> -
			选择您希望该计划表失效的时间。<br>
			<strong><em>调度进程规则表</em></strong> -
			显示定义好的所有计划表。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td>
		<p>
			<strong>日志设置</strong><strong><a name=19></a></strong><br>
			您可以将日志文件保存到本地硬盘中，该日志可被发送到网络管理员处以进行故障排查。<br>
			<strong><em>保存</em></strong> - 点击该按钮将日志条目保存为文本文件。<br>
			<strong><em>日志类型</em></strong> - 选择您希望<?query("/sys/modelname");?>记录的信息类型。<br>
			<strong><em>日志等级</em></strong> - 选择<?query("/sys/modelname");?>上日志信息的等级。
		</p>
	</td>
</tr>

</table>
						   
