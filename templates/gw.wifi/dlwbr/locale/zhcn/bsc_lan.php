<?
/* --------------------------------------------------------- */
//$TITLE=$m_pre_title."安装";
/* --------------------------------------------------------- */
$m_title_router_setting	= "路由器设置";
$m_desc_router_setting	=
	"在这部分中可以为您的路由器配置内部网络设置。".
	"在这里配置的IP地址就是您用来访问基于web的管理界面的IP地址。".
	"如果你更改了这个IP地址，".
	"您就需要对您的PC的网络设置再进行一些调整，然后再次访问网络。";

$m_router_ipaddr	= "路由器IP地址";
$m_subnet_mask		= "缺省子网掩码";
$m_domain_name		= "本地域名";
$m_enable_dnsr		= "启用DNS中继";

$m_title_dhcp_svr	= "DHCP服务器设置";
$m_desc_dhcp_svr	=
	"在这部分中配置内置DHCP服务器，".
	"将IP地址分配给您网络上的计算机。";

$m_enable_dhcp		= "启用DHCP服务器";
$m_dhcp_range		= "DHCP  IP地址范围";
$m_to			= "到";
$m_range_comment	= "（LAN子网内的地址）";
$m_lease_time		= "DHCP租用时间";
$m_minutes		= "（分钟）";

$m_title_add_client	= "DHCP保留";
$m_computer_name	= "计算机名称";
$m_clone_mac		= "复制您的PC的MAC地址";

$m_title_static_client_list = "DHCP保留表";
$remaining_wording	="配置好了的剩余客户端数量";

$m_title_client_list	= "DHCP客户端表";
$m_host_name		= "主机名称";
$m_ipaddr		= "IP地址";
$m_macaddr		= "MAC地址";
$m_expired_time		= "终止时间";

$m_days	= "日";
$m_hrs	= "小时";
$m_mins	= "分钟";
$m_secs	= "秒";

$a_invalid_ip		= "无效IP地址！";
$a_invalid_netmask	= "无效子网掩码！";
$a_network_conflict	= "Guest zone network must be different from host zone !";
$a_invalid_domain_name	= "无效域名！";
$a_invalid_ip_range	= "DHCP服务器的无效IP地址范围！";
$a_invalid_lease_time	= "无效DHCP租用时间！";
$a_del_confirm		= "您确定您想删除这条目录？";
$a_same_static_mac	= "已经有一条相同MAC地址的现存目录了，\\n 请更改MAC地址。";
$a_same_static_ip	= "已经有一条相同IP地址的现存目录了，\\n 请更改IP地址。";
$a_same_static_hostname = "已经有一条相同计算机名称的现存目录了，\\n 请更改计算机名称。";
$a_same_with_lan_ip	= "IP地址不能与LAN IP地址相同！";
$a_invalid_computer_name= "无效计算机名称！";
$a_invalid_mac		= "无效MAC地址！";
?>
