<div class="box">
<a name="admin"><h2>管理</h2></a>
<table border=0 cellspacing=0 cellpadding=0>

<tr>
	<td height=20>
		
		<p>
			<strong><em>管理员登录名</em></strong> -
			输入以管理权限访问路由器的用户名。
		</p>
		<p>
			<strong><em>管理员密码</em></strong> -
			输入和确认<strong>admin</strong>帐户用于访问路由器管理界面的密码。
		</p>
		<p>
			<strong>远程管理</strong><br>
			远程管理允许使用web浏览器通过WAN口从Internet对设备进行配置。访问路由器管理界面仍需要用户名和密码。
			<br>
			<strong><em>允许访问的IP</em></strong> -
			此选项允许用户指定一个特定的IP地址可以从Internet远程访问路由器。此框缺省为空，即当启用远程管理后，Internet上的任何IP地址都可以远程访问路由器。
			<br>
			<strong><em>端口</em></strong> - 选择用于访问<?query("/sys/modelname");?>的端口。
		</p>
		<p>
			<strong><em>示例：</em></strong><br>
			<a href="http://192.168.0.1/help_tools.html">http://x.x.x.x:8080 </a> 
			，x.x.x.x是<?query("/sys/modelname");?>的WAN口IP地址，8080是web管理界面的端口。
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="time"><h2>时间</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=33>
		<p>
			时间配置设置用于路由器对计划的服务和系统日志活动进行同步。您需要根据您所在的地区对时区进行设置。可以手动设置或设备可以连接到一个NTP（网络时间协议）服务器以获取时间。您也可以设置夏令时，这样可以在特定的日期自动调整系统时间。
		</p>
		<p>
			<strong><em>时区</em></strong> - 选择您所在地区的时区。<br>
			<strong><em>夏令时</em></strong> -
			如果您所在的地区使用夏令时，启用此选项并设定夏令时的起始和结束月份，周，日和时间。<br>
			<strong><em>自动时间配置</em></strong> -
			选择一个D-Link时间服务器用于<?query("/sys/modelname");?>进行时间同步。
			<?query("/sys/modelname");?>和D-Link NTP服务器进行通信的间隔设置为7天。
			<br>
			<strong><em>手动设置日期和时间</em></strong> -
			选择此项，如果您想手动指定时间。您必须指定年，月，日，小时，分钟和秒，或单击复制您的计算机的时间设置按钮复制访问管理界面的计算机的系统时间。
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="log_settings"><h2>日志设置</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			您可以保存日志文件到本地硬盘上，稍后可以发送给网络管理员用于故障分析。
			<br>
			<strong><em>保存</em></strong> - 单击此按钮保存日志记录为文本文件。<br>
			<strong><em>日志类型</em></strong> - 选择您要<?query("/sys/modelname");?>记录的信息类型。
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="email_settings"><h2>Email设置</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			Email设置允许您发送设备日志文件到一个特定的email地址。<br>
			<br>
			<strong><em>源Email地址</em></strong> - 
			发送email的email地址。多数SMTP服务都要求这是一个有效的email地址，并且对它的真实性进行测试。<br>
			<strong><em>目的Email地址</em></strong> - 
			设备日志文件被发送到的email地址。访问此email帐户的个人可以查看此日志文件。<br>
			<strong><em>Email主题</em></strong> - 
			email的标题。<br>
			<strong><em>SMTP服务器地址</em></strong> - 
			mail服务器的IP地址和域名，此服务器用于转发设备日志文件到指定email帐户。<br>
			<strong><em>SMTP服务器端口</em></strong> - 
			mail服务器使用的端口。<br>
			<strong><em>启用认证</em></strong> - 
			出于安全原因，一些SMTP服务器需检测帐户名和密码以确认正在处理的email是他的客户之一。<br>
			<strong><em>帐户名</em></strong> - 
			用于和SMTP服务器进行认证的帐户名。<br>
			<strong><em>密码</em></strong> - 
			用于和SMTP服务器进行认证的密码。<br>
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="system"><h2>系统</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=40>
	可以把当前系统设置作为文件保存到本地硬盘。设备可以加载由设备创建并保存的文件和其它保存的配置文件。
	如需重新加载系统配置文件，单击<strong>浏览</strong>，在本地硬盘上搜索需使用的文件。
	单击<strong>复位</strong>，设备可以恢复设备到出产默认值。只有在需要时才使用复位特性。
	这将删除先前设备保存的设置。进行出厂复位前确保保存了您的系统设置。
	<br>
		<strong><em>保存</em></strong> - 单击此按钮从路由器上保存配置。<br>
		<strong><em>浏览</em></strong> -
		单击浏览查找一个已保存的配置文件然后单击上传，在路由器上应用保存的设置。<br>
		<strong><em>复位设备</em></strong> -
		单击此按钮恢复路由器到出厂默认值。
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="firmware"><h2>固件</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=51>
	您可以使用此工具升级设备的固件。确保您要使用的固件保存在计算机的本地硬盘上。
	单击<strong>浏览</strong>在本地硬盘上搜索用于升级的固件。升级固件不会更改任何您的系统设置，
	但是推荐您在升级固件前保存您的系统设置。
	请检查D-Link<a href=<?query("/sys/supporturl");?>>支持站点</a>上的固件升级或单击<strong>现在检查</strong>按钮让路由器自动检查新的固件。
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="dynamic_dns"><h2>动态DNS</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=2>
		<p>
		动态DNS（域名服务）是一种关联域名和动态IP地址的方式。
		大多数线缆和DSL连接都会分配给您一个动态的IP地址，此地址只能在特定连接期间使用。
		使用<?query("/sys/modelname");?>，您可以设置DDNS服务，
		<?query("/sys/modelname");?>在每次接收到一个新的WAN口IP地址后都会自动更新您的DDNS服务器。	
		<br>
			<strong><em>服务器地址</em></strong> - 从下拉菜单中选择您的DDNS供应商。<br>
			<strong><em>主机名</em></strong> - 输入您在DDNS服务供应商上注册的主机名。<br>
			<strong><em>用户名</em></strong> - 输入您DDNS帐户的用户名。<br>
			<strong><em>密码</em></strong> - 输入您DDNS帐户的密码。
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="system_check"><h2>系统检测</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			此工具用于验证LAN和Internet(WAN)接口的物理连通性。此高级特征在路由器上的每个以太网端口上整合了一个LAN线缆测试器。通过图形用户界面（GUI），可以进行远程线缆测试诊断和报告线缆错误如开路，短路，反接和阻抗不匹配。此特性允许用户轻松地对他们的线缆连接进行故障分析，极大地减少了服务请求和反馈。
		</p>
		<p>
			<strong>Ping测试</strong><br>
			此有用的诊断工具用于检测一台计算机是否在Internet上。
			它向特定主机发送ping数据包并侦听响应。
			输入您要ping（Packet Internet Groper）的主机名或IP地址然后单击<strong>Ping</strong>。
			Ping尝试的状态将会显示在Ping结果框中。
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="schedules"><h2>计划</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>	
			此页用于对路由器配置全局计划。一旦定义，这些计划稍后将应用到路由器上支持计划的特性上。
			<br>
			<strong><em>名字</em></strong> - 定义计划的名字。<br>
			<strong><em>日</em></strong> -
			选择一个日期，日期范围或选择所有周复选框以便每天都应用此计划。<br>
			<strong><em>全天 - 24小时</em></strong> -
			选择此框，在指定日期内24小时应用计划。<br>
			<strong><em>起始时间</em></strong> -
			选择计划开始的时间。<br>
			<strong><em>结束时间</em></strong> -
			选择计划停止的时间。<br>
			<strong><em>计划规则列表</em></strong> -
			这里显示所有定义的计划。
		</p>
	</td>
</tr>
</table>
</div>

						   