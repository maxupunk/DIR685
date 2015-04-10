<?
/* --------------------------------------------------------- */
//$TITLE=$m_pre_title."安装";
/* --------------------------------------------------------- */
$m_title_router_setting	="路由器设置";
$m_desc_router_setting	="通过该部分来配置您路由器的内部网络设置。".
													"这儿配置的IP地址为您用于进行访问的IP地址。".
													"Web管理界面。如果您在这儿更改了IP地址，您可能需要调整您PC的网络设置，再次访问网络。";							

$m_router_ipaddr	="路由器IP地址";
$m_subnet_mask		="默认子网掩码";
$m_domain_name		="本地域名";
$m_enable_dnsr		="启用DNS中继";

$m_title_dhcp_svr	="DHCP服务器设置";
$m_desc_dhcp_svr	="使用该部分来配置内置DHCP服务器，将IP地址分配给您网络上的计算机。";

$m_enable_dhcp		="启用DHCP服务器";
$m_dhcp_range		="DHCP IP地址范围";
$m_to			="至";
$m_range_comment	="（LAN子网中的地址）";
$m_lease_time		="DHCP租赁时间";
$m_netbios	="NetBIOS宣告";
$m_netbios_learn	="从WAN处学习NetBIOS";
$m_netbios_scope	="NetBIOS范围";
$m_optional	="（可选）";
$m_netbios_type	="NetBIOS节点类型";
$m_broadcast	="只能广播（在没有配置WINS服务器时使用）";
$m_ptop	="点到点（无广播）";
$m_mix_mode	="组合模式（先广播，再点到点）";
$m_hybrid	="组合（先点到点，再广播）";
$m_primary_wins	="首选WINS IP地址";
$m_secondary_wins	="备用WINSIP地址";

$m_minutes		="（分钟）";

$m_title_add_client	="DHCP保留";
$m_computer_name	="计算机名称";
$m_clone_mac		="克隆您PC的MAC地址";

$m_title_static_client_list ="DHCP保留列表";
$remaining_wording	="能配置的余下客户端号";

$m_title_client_list	="DHCP客户端列表";
$m_host_name		="主机名称";
$m_ipaddr		="IP地址";
$m_macaddr		="MAC地址";
$m_expired_time		="失效时间";

$m_days	="天";
$m_hrs	="小时";
$m_mins	="分钟";
$m_secs	="秒";

$a_invalid_ip		="无效IP地址！";
$a_invalid_netmask	="无效子网掩码！";
$a_network_conflict	="来宾区网络必须不同于主机区网络";
$a_lan_wan_conflict ="WAN网络必须与LAN网络不同！";
$a_invalid_domain_name	="无效域名！";
$a_invalid_ip_range	="DHCP服务器的IP地址范围无效！";
$a_invalid_lease_time	="无效DHCP租赁时间！";
$a_del_confirm		="您确定要删除该条目？";
$a_same_static_mac	="已存在相同MAC地址的条目。\\n请更改MAC地址。";
$a_same_static_ip	="已存在相同IP地址的条目。\\n请更改IP地址。";
$a_same_static_hostname ="已存在相同计算机名的条目。\\n请更改计算机名称。";
$a_same_with_lan_ip	="IP地址不能于LAN IP地址相同！";
$a_invalid_computer_name="无效计算机名称！";
$a_invalid_mac		="无效MAC地址！";

$a_invalid_form         ="NetBIOS范围不是有效格式！";
$a_invalid_primaywins	="无效netbios首选成功！";
$a_invalid_secondaywins	="无效netbios备用成功！";
$a_primary_null		="如果指定了备用WINS IP地址，则也必须指定首选WINS IP地址！";
?>

