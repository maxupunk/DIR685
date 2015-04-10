﻿<?
$m_title_firewall ="防火牆設定";
$m_enable_spi="啟用 SPI";
$m_title_rtsp="應用層級閘道器 (ALG) 組態";
$m_enable_rtsp="啟用 RTSP";
$m_enable_dos="啟用防 DoS 分佈式攻擊";
$m_title_attack_prevention="內部攻擊防範";
$m_desc_attack_prevention="攻擊類型防範";
$m_enable_arp_attack="ARP 攻擊";
$m_enable_fake_dhcp="偽裝 DHCP 伺服器";
$m_title_firewall_rules ="防火牆規則";
$m_action ="動作";
$m_allow ="許可";
$m_deny ="拒絕";
$m_inf ="介面";
$m_start_ip ="起始 IP 位址";
$m_end_ip	="結束 IP 位址";
$m_protocol	="通訊協定";
$m_port_range ="連接埠範圍";
$m_src	="來源";
$m_dst ="目的地";
$m_schedule ="排程";
$m_always_on ="永遠啟動";
$m_add_new_sch ="新增新的排程";
$m_title_fw_list="防火牆規則清單";
$m_allow_ping ="來自WAN 的PING";
$m_remote_management="遠端管理";


$m_title_dmz_rule ="DMZ 主機";
$m_desc_dmz ="隔離區 (DMZ) 選項讓您".
							"可以在路由器外部的網路上設定單一電腦。".
							"如果您有擁有一部無法從路由器成功執行網際網路".
							"應用程式的電腦，則將".
							"電腦安置在DMZ，作為非限制網際網路存取";

$m_note_dmz ="<strong>註解：</strong> 將電腦安置在DMZ".
							"可能使電腦暴露在各種安全風險".
							"才建議使用此選項";

$m_enable_dmz_host ="啟用 DMZ 主機";
$m_ip_addr_dmz ="DMZ IP 位址";
$m_computer_name ="電腦名稱";


$a_no_ip_selected	="請先選擇一部機器！";
$a_invalid_ip		="無效的 IP 位址！";
$a_confirm_to_del_fw="您是否確定要刪除此規則？";
$a_invalid_port="無效的連接埠！";
$a_invalid_port_range="無效的連接埠範圍！";

$a_invalid_src_startip="無效的來源起始 IP 位址！";
$a_src_startip_in_different_subnet   ="無效的來源起始 IP 位址！來源起始 IP 位址和路由器位址應在相同的子網路！";

$a_invalid_src_endip="無效的來源結束 IP 位址！";
$a_src_endip_in_different_subnet   ="無效的來源結束 IP 位址！來源結束 IP 位址和路由器位址應在相同的子網路！";

$a_invalid_dst_startip="無效的目的地起始 IP 位址！";
$a_dst_startip_in_different_subnet   ="無效的目的地起始 IP 位址！目的地起始 IP 位址和路由器位址應在相同的子網路！";

$a_invalid_dst_endip="無效的目的地結束 IP 位址！";
$a_dst_endip_in_different_subnet   ="無效的目的地結束 IP 位址！目的地結束 IP 位址和路由器位址應在相同的子網路！";

$a_fw_name_cant_be_empty="不能夠沒有防火牆名稱";
$a_not_support_same_direction="來源介面和目的地介面不能相同";
$a_invalid_src_ip_range="無效的來源 IP 位址範圍！";
$a_invalid_dst_ip_range="無效的目的地 IP 位址範圍！";
$a_confirm_swap_fw="您是否確定變更優先權？";
$a_dmzip_in_different_subnet ="無效的 DMZ IP 位址！DMZ IP 位址和路由器位址應在相同的子網路";
$a_same_rule_exist ="名稱'\"+get_obj(\"fw_description_\"+i).value+\"' 已使用";
$a_not_select_inf ="請選擇介面";
?>
