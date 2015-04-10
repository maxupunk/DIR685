<?
$m_title_firewall = "防火牆設定";
$m_enable_spi="啟用 SPI";
$m_enable_dos="啟用 DoS 防止";
$m_title_firewall_rules = "防火牆規則";
$m_action = "動作";
$m_allow = "允許";
$m_deny = "拒絕";
$m_inf = "介面";
$m_start_ip = "開始 IP 位址";
$m_end_ip	="結束 IP 位址";
$m_protocol	="協定";
$m_port_range ="服務埠範圍";
$m_src	="來源";
$m_dst = "目的";
$m_schedule = "排程";
$m_always_on = "永遠開啟";
$m_add_new_sch = "新增新排程";
$m_title_fw_list="防火牆規則清單t";
$m_allow_ping = "從 WAN 脈測 (PING)";
$m_remote_management="遠端管理";

$m_title_dmz_rule = "DMZ 主機";
$m_desc_dmz =
	"DMZ(非軍事區) 選項可讓您設定網路上路由器外的單一電腦。".
	"如果您有一部電腦無法成功從路由器後成功執行 Internet 應用程式，".
	"那麼可將該電腦置於 DMZ 區，以無限制存取 Internet。";
$m_note_dmz = "<strong>注意:</strong> 將電腦置於 DMZ 可能會讓該公司暴露於多種安全性風險中。建議將此選項當最後手段使用。";
$m_enable_dmz_host = "啟用 DMZ 主機";
$m_ip_addr_dmz = "DMZ IP 位址"; 
$m_computer_name = "電腦名稱";


$a_no_ip_selected	= "請先選取機器名稱!";
$a_invalid_ip		= "無效的 IP 位址!";
$a_confirm_to_del_fw= "您確定要刪除這個規則嗎?";
$a_invalid_port="無效的服務埠!";
$a_invalid_port_range="無效的服務埠範圍!";

$a_invalid_src_startip="無效的來源開始 IP 位址!";
$a_src_startip_in_different_subnet   = "無效的來源開始 IP 位址! 來源開始 IP 位址與路由器位址應該位在相同網路內。";

$a_invalid_src_endip="無效的來源結束 IP 位址!";
$a_src_endip_in_different_subnet   = "無效的來源結束 IP 位址! 來源結束 IP 位址與路由器位址應該位在相同網路內。";

$a_invalid_dst_startip="無效的目的開始 IP 位址!";
$a_dst_startip_in_different_subnet   = "無效的目的開始 IP 位址! 目的開始 IP 位址與路由器位址應該位在相同網路內。";

$a_invalid_dst_endip="無效的目的結束 IP 位址!";
$a_dst_endip_in_different_subnet   = "無效的目的結束 IP 位址! 目的結束 IP 位址與路由器位址應該位在相同網路內。";

$a_fw_name_cant_be_empty="防火牆名稱不能空白!";
$a_not_support_same_direction="來源介面與目的介面不能相同!";
$a_invalid_src_ip_range="無效的來源 IP 位址範圍!";
$a_invalid_dst_ip_range="無效的目的 IP 位址範圍!";
$a_confirm_swap_fw="您確定要變更優先順序嗎?";
$a_dmzip_in_different_subnet = "無效的DMZ IP位址！DMZ IP位址和路由器位址應該在同一個網路中。";
$a_same_rule_exist = "相同的規則 '\"+get_obj(\"fw_description_\"+i).value+\"' 已經存在。";
?>
