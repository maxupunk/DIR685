<?
$m_title_firewall ="防火墙设置";
$m_enable_spi="启用SPI";
$m_title_rtsp="应用层网关（ALG）配置";
$m_enable_rtsp="启用RTSP";
$m_enable_dos="启用DoS阻止";
$m_title_attack_prevention="内部攻击阻止";
$m_desc_attack_prevention="阻止攻击类型";
$m_enable_arp_attack="ARP攻击";
$m_enable_fake_dhcp="欺骗DHCP服务器";
$m_title_firewall_rules ="防火墙规则";
$m_action ="活动";
$m_allow ="允许";
$m_deny ="拒绝";
$m_inf ="接口";
$m_start_ip ="起始IP地址";
$m_end_ip	="结束IP地址";
$m_protocol	="协议";
$m_port_range ="端口范围";
$m_src	="源";
$m_dst ="目的";
$m_schedule ="计划";
$m_always_on ="始终";
$m_add_new_sch ="添加新的计划";
$m_title_fw_list="防火墙规则列表";
$m_allow_ping ="从WAN处PING";
$m_remote_management="远程管理";

$m_title_dmz_rule ="DMZ主机";
$m_desc_dmz ="DMZ（非限制区）选项允许在您的网络中，路由器外设置一台计算机。如果您有一台计算机不能在路由器后面成功运行Internet应用程序，请把这台计算机放在DMZ中，无限制地访问Internet。";

$m_note_dmz ="<strong>注意：</strong>将一台计算机放在DMZ中可能会使这台计算机暴露在各种危险下。因此建议不到万不得已请不要使用该项。";

$m_enable_dmz_host ="启用DMZ主机";
$m_ip_addr_dmz ="DMZ IP地址";
$m_computer_name ="计算机名称";

$a_no_ip_selected	="请首先选择一台设备！";
$a_invalid_ip		="无效IP地址！";
$a_confirm_to_del_fw="您确定要删除这条规则？";
$a_invalid_port="无效端口！";
$a_invalid_port_range="无效端口范围！";

$a_invalid_src_startip="无效源IP地址！";
$a_src_startip_in_different_subnet   ="无效源起始IP地址！源起始IP地址和路由器IP地址应处于同一子网。";

$a_invalid_src_endip="无效源结束IP地址！";
$a_src_endip_in_different_subnet   ="无效源结束IP地址！源结束IP地址和路由器地址应处于同一子网。";

$a_invalid_dst_startip="无效目的起始IP地址！";
$a_dst_startip_in_different_subnet   ="无效目的起始IP地址！目的起始IP地址和路由器地址应处于同一子网。";

$a_invalid_dst_endip="无效目的结束IP地址！";
$a_dst_endip_in_different_subnet   ="无效目的结束IP地址！目的结束IP地址和路由器地址应处于同一子网。";

$a_fw_name_cant_be_empty="防火墙名称不能为空！";
$a_not_support_same_direction="源接口和目的接口不能相同！";
$a_invalid_src_ip_range="无效源IP地址范围！";
$a_invalid_dst_ip_range="无效目的IP地址范围！";
$a_confirm_swap_fw="您确定要更改优先级？";
$a_dmzip_in_different_subnet ="无效DMZ IP地址！DMZ IP地址和路由器地址应处于同一子网。";
$a_same_rule_exist ="名称 '\"+get_obj(\"fw_description_\"+i).value+\"'已使用。";
$a_not_select_inf ="请选择接口";
?>

