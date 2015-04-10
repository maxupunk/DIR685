<div class="box">
<a name="disk_management"><h2>磁盘管理</h2></a>
	<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			磁盘管理页面包含设备上本地硬盘的信息和设置。
			<br>
			<br>
			<strong><em>硬盘信息</em></strong> -
			这里包含设备上所安装硬盘的详细信息。<br>
			<strong><em>格式化设置</em></strong> -
			此按钮允许您格式化当前安装在设备上的硬盘。<br>
			警告：此操作将清除硬盘。硬盘上所有数据都将丢失。<br>
			<strong><em>硬盘设置</em></strong> -
			如果启用此设置，如果在一个时间段内没有数据的写入和读写，硬盘将会进入休眠模式，以减少功耗。
			<br>
		</p>
	</td>
</tr>
 </table>
</div>

<div class="box">
<a name="users_groups"><h2>用户/组</h2></a>
	<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=228>
		<p>
			<strong>用户</strong><br>
			在此创建用户。这些帐号可以添加到网络访问和FTP服务器的规则中。这里创建的所有用户同样可以访问计划下载内容。
		</p>
		<p>
			<strong><em>用户名</em></strong> -
			 输入用户名。<br>
			<strong><em>密码</em></strong> -
			输入密码。<br>
			<strong><em>确认密码</em></strong> -
			再次输入密码。单击“保存设置”添加用户。<br>
			<br>
			此页底部的列表中将会显示创建的用户和它们所属的组（如果有）。可以单击规则右侧的“编辑”图标对用户的密码进行修改，或单击“回收站”图标删除用户。			
		</p>
		<p>
			<strong>组</strong><br>
			在此创建组。一旦创建了组，将显示在用户页面的组选择中。
			<br>
			<br>
			此页底部的列表中将显示创建的组。同时也将显示属于它们的用户。
			<br>
		</p>
	</td>
</tr>
 </table>
</div>
 
 
<div class="box">
<a name="storage_access"><h2>存储访问</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=64> 
		<p>
			<strong><em>类别</em></strong> -
			选择用户或组<br>
			<strong><em>用户或组</em></strong> -
			从下拉列表中选择一个用户或组。如果您希望创建一个规则应用到所有的用户，选择“所有帐户”。<br>
			<strong><em>文件夹</em></strong> -
			单击“浏览”选择一个文件夹。此文件夹位于内置硬盘上。<br>
			<strong><em>权限</em></strong> -
			分配所选文件夹的“只读”或“读/写”权限给所选的用户或组。<br>
			<strong><em>Oplocks</em></strong> -
			伺机锁定（oplocks）是32位Windows操作系统环境所实施的一种LAN管理网络协议特征。
			Oplocks是服务器向其客户端针对共享逻辑卷提供的保证。这些保证通知客户端，
			服务器不能更改文件内容，或者如果文件内容需要进行更改，客户端得到提示前此更改进程不能继续。
			Oplocks设计用于在网络文件共享时提高网络性能，但是如果您使用基于文件的数据库应用，
			推荐<strong>关闭</strong>共享oplocks。
			<br>
			<br>
			什么系统会受Oplocks的影响？<br>
			<br>
			缺省下，Vista的Oplocks为启用，不能被禁止。
			如果您的应用程序使用DIR-685的共享文件且又遇到网络性能问题，
			您可以通过<strong>关闭</strong>Oplocks来尝试提高性能。
			<br>
			<strong><em>映射文档</em></strong> -
			当启动时，文件属性＂Archive＂会被拷贝成文件存贮在DIR-685。某些备份软件会把此属性附加到要存贮成备份的文件里。<br>
			<strong><em>备注</em></strong> -
			关于此规则的额外批注。此可选项没有功能作用。<br>
			<br>
			单击“保存设置”保存规则。所有保存的规则将会显示到此页底部的列表中。可以单击规则右侧的“编辑”或“回收站”图标对规则进行编辑和删除。
			<br>
		</p>
 </tr>
</table>
</div>
 
 
<div class="box">
<a name="ftp_server"><h2>Ftp服务器</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=99>
		<p>
			<strong><em>类别</em></strong> -
			选择用户或组<br>
			<strong><em>用户或组</em></strong> -
			从下拉列表中选择一个用户或组。如果您希望创建一个规则应用到所有的用户，选择“所有帐户”。匿名将会显示为一个用户。<br>
			<strong><em>文件夹</em></strong> -
			单击“浏览”选择一个文件夹。此文件夹位于内置硬盘上。如果您希望同时分配所有硬盘的根目录访问，选中“root”复选框。<br>
			<strong><em>权限</em></strong> -
			分配所选文件夹的“只读”或“读/写”权限给所选的用户或组。单击“添加”添加规则到列表。所有保存的规则将会显示到此页底部的列表中。可以单击规则右侧的“编辑”或“回收站”图标对规则进行编辑和删除。
			<br>
			<strong><em>最大用户数</em></strong> -
			输入可以同时访问FTP服务器的最大用户数。缺省值为10。<br>
			<strong><em>空闲时间</em></strong> -
			如果超过特定的空闲时间，FTP服务器将会退出一个用户的登录。<br>
			<strong><em>端口</em></strong> -
			如果您要改变FTP服务器使用的端口，在此输入新的数字。这是一个高级设置，如果您的设备处于一个路由器后面，对此作出更改可能会产生复杂情况。推荐保持缺省设置21，除非您有更改FTP端口的经验。
			<br>
			<strong><em>流量控制</em></strong> -
			此功能将调整通过FTP服务器的数据流。如果您在此设置了限制，用户将使用较低的速度从FTP服务器进行下载，这样您可以保留本地的带宽。<br>
			<strong><em>客户端语言</em></strong> -
			大多数标准FTP客户端如Windows FTP，传输文件时只支持西欧编码。这里为非标准FTP客户端添加了北欧，中欧，中文简体和繁体和斯拉夫语编码支持。
			<br>
			<br>
			完成后，单击“保存设置”。
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="upnp_av_server"><h2>UPnP AV服务器</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=44>
		<p>
			DIR-685拥有内置的UPnPAV媒体服务器，可以用于UPnPAV兼容的媒体播放机。<br>
			<br>
			<strong><em>UPnPAV服务器</em></strong> -
			启用或禁用UPnPAV服务器。<br>
			<strong><em>文件夹</em></strong> -
			单击“浏览”查找媒体文件（音乐，图片和视频）的根目录。如果您想访问DIR-685上的所有内容可以选择Root。<br>
			<strong><em>自动刷新</em></strong> -
			配置自动更新可以每5，15或30分钟或1，2，6，12或24小时间隔自动更新您共享的UPnPAV数据。<br>
			<br>
			完成后单击“保存设置”。<br>
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="itunes_server"><h2>iTunes服务器</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			iTunes服务器将允许iTunes软件自动检测和播放DIR-685上的音乐。<br>
			<br>
			<strong><em>iTunes服务器</em></strong> -
			启用或禁用iTunes服务器。<br>
			<strong><em>文件夹</em></strong> -
			单击“浏览”查找音乐文件的目录。如果您想访问DIR-685上的所有文件夹可以选择Root。<br>
			<strong><em>自动刷新</em></strong> -
			配置自动更新可以每5，15或30分钟或1，2，6，12或24小时间隔自动更新您共享的UPnPAV数据。<br>
			<br>
			完成后，单击“保存设置”。<br>
		</p>
</td>
</tr>
</table>
</div>

<div class="box">
<a name="bt_download_manager"><h2>BT下载服务器</h2></a>
	<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			BT下载管理器页面可以对设备进行设置，以便从Internet下载Bit文件而不用打开PC。
			<br>
			<br>
			<strong><em>BT设置</em></strong> -
			这里允许您开启或关闭BT下载管理服务。目录路径允许您指定保存下载文件的目录/文件夹。所有下载都将存储在指定的目录，所有完成的任务都存储在“完成”文件夹，所有正在下载的任务都存储在“未完成”文件夹。文件管理将保持每个下载文件的原始属性。
			<br>
			<strong><em>Torrent下载</em></strong> -
			在BT下载管理屏幕，您可以选择是否通过URL或单独的BT种子文件来添加新的下载。
			<br>
			所有正在下载的任务都将显示在窗口里，每行显示一个下载任务，这样您可以清晰地查看和控制每个正在下载的任务。
			<br>
			<strong><em>下载任务表</em></strong> -
			对于每个正在下载的任务，单击“更多信息”连接将查看当前下载的更多信息。<br>
			<strong><em>停止</em></strong> -
			使用此按钮停止/暂停下载进程，使其它下载任务获取更多带宽。
			<br>
			<strong><em>删除</em></strong> -
			如果下载发生错误，使用任务右侧的按钮来取消/删除下载的任务。
			<br>
			<br>
			如果被删除的任务已完成，仅任务被删除，已下载的文件将仍保留在“完成”文件夹。
			<br>
			<strong><em>移除已完成</em></strong> -
			下载任务表右侧的此按钮允许用户从表中删除已完成下载的任务，而不删除已下载的文件。
			<br>			
		</p>
	</td>
</tr>
 </table>
</div>
