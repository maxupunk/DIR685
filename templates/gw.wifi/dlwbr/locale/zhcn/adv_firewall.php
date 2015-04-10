<?
$m_title_firewall = "防火墙设置";
$m_enable_spi="启用SPI";
$m_enable_dos="启用DoS预防";
$m_title_attack_prevention="Internet 攻击预防";
$m_desc_attack_prevention="预防攻击类型";
$m_enable_arp_attack="ARP 攻击";
$m_enable_fake_dhcp="伪装DHCP服务器";
$m_title_firewall_rules = "防火墙规则";
$m_action = "动作";
$m_allow = "允许";
$m_deny = "拒绝";
$m_inf = "界面";
$m_start_ip = "开始IP地址";
$m_end_ip	="末端IP地址";
$m_protocol	="协议";
$m_port_range ="端口范围";
$m_src	="源";
$m_dst = "目的";
$m_schedule = "调度进程";
$m_always_on = "总是开着的";
$m_add_new_sch = "添加新的调度进程";
$m_title_fw_list="防火墙规则列表";
$m_allow_ping = "来自于WAN的PING";
$m_remote_management="远程管理";


$m_title_dmz_rule = "DMZ主机";
$m_desc_dmz =
	" DMZ（隔离区）选项使您可以选择地将您网络上的一台单独的计算机设置在路由器之外。".
	"如果您的计算机在路由器后面不能成功运行因特网应用程序，您可以将这台计算机放在DMZ中，对因特网进行无限制的访问。";
$m_note_dmz =
	"<strong>注意：</strong>将计算机放置在DMZ中可能会使该计算机暴露到不同的安全隐患中。".
	"不到万不得已请不要使用该选项。";
$m_enable_dmz_host = "启用DMZ主机";
$m_ip_addr_dmz = "DMZ IP地址"; 
$m_computer_name = "计算机名称";


$a_no_ip_selected	= "请首先选择一台设备！";
$a_invalid_ip		= "无效IP地址！";
$a_confirm_to_del_fw= "您确定要删除该规则？";
$a_invalid_port="无效端口！";
$a_invalid_port_range="无效端口范围！";

$a_invalid_src_startip="无效源起始IP地址！";
$a_src_startip_in_different_subnet   = "无效源起始IP地址！源起始IP地址和路由器地址应该在同一个网络中。";

$a_invalid_src_endip="无效源末端IP地址";
$a_src_endip_in_different_subnet   = "无效源末端IP地址！源末端IP地址和路由器地址应该在同一个网络中。";

$a_invalid_dst_startip="无效目的起始IP地址！";
$a_dst_startip_in_different_subnet   = "无效目的起始IP地址！目的起始IP地址和路由器地址应该在同一个网络中。";

$a_invalid_dst_endip="无效目的末端IP地址！";
$a_dst_endip_in_different_subnet   = "无效目的末端IP地址！目的末端IP地址和路由器地址应该在同一个网络中。";

$a_fw_name_cant_be_empty="防火墙名称不能为空白！";
$a_not_support_same_direction="源接口和目的接口不能相同！";
$a_invalid_src_ip_range="无效源IP地址范围！";
$a_invalid_dst_ip_range="无效目的IP地址范围！";
$a_confirm_swap_fw="您确定要更改优先级？";
$a_dmzip_in_different_subnet = "无效DMZ IP地址！DMZ IP地址和路由器地址应该在同一个网络中。";
$a_same_rule_exist = "相同的规则 '\"+get_obj(\"fw_description_\"+i).value+\"' 已经存在。";
?>
