<?
/* --------------------------------------------------------- */
//$TITLE=$m_pre_title."設定";
/* --------------------------------------------------------- */
$m_title_router_setting	= "路由器設定";
$m_desc_router_setting	=
	"使用本節來組態路由器的內部網路設定。此處組態的 IP 位址即為您用來存取 Web 架構管理介面的 IP 位址。".
	"如果您變更此處的 IP 位址，可能即必須調整 PC 的網路設定，才能正確存取網路。";
	
$m_router_ipaddr	= "路由器 IP 位址";
$m_subnet_mask		= "預設子網路遮罩";
$m_domain_name		= "本機網域名稱";
$m_enable_dnsr		= "開啟 DNS 中繼";

$m_title_dhcp_svr	= "DHCP 伺服器設定";
$m_desc_dhcp_svr	= "使用此節來組態內建的 DHCP 伺服器，以指定網路上電腦的 IP 位址。";

$m_enable_dhcp		= "啟用 DHCP 伺服器";
$m_dhcp_range		= "DHCP IP 位址範圍";
$m_to			= "到";
$m_range_comment	= "(LAN 子網路內的位址)";
$m_lease_time		= "DHCP 租用時間";
$m_minutes		= "(分)";

$m_title_add_client	= "DHCP 保留";
$m_computer_name	= "電腦名稱";
$m_clone_mac		= "複製您 PC 的 MAC 位址";

$m_title_static_client_list = "DHCP 保留清單";
$remaining_wording	="可以組態的剩餘用戶端數";

$m_title_client_list	= "DHCP 用戶端清單";
$m_host_name		= "主機名稱";
$m_ipaddr		= "IP 位址";
$m_macaddr		= "MAC 位址";
$m_expired_time		= "過期時間";

$m_days	= "日";
$m_hrs	= "時";
$m_mins	= "分";
$m_secs	= "秒";

$a_invalid_ip		= "無效的 IP 位址!";
$a_invalid_netmask	= "無效的子網路遮罩 !";
$a_invalid_domain_name	= "無效的網域名稱!";
$a_invalid_ip_range	= "無效的的 DHCP 伺服器 IP 位址範圍!";
$a_invalid_lease_time	= "無效的 DHCP 租用時間!";
$a_del_confirm		= "您確定要刪除這個項目嗎?";
$a_same_static_mac	= "相同的 MAC 位址已存在項目。請變更 MAC 位址";
$a_same_static_ip	= "相同的 IP 位址已存在項目。請變更 IP 位址";
$a_same_static_hostname = "相同的電腦名稱已存在項目。請變更電腦名稱";
$a_same_with_lan_ip	= "IP 位址不能與 LAN IP 位址相同!";
$a_invalid_computer_name= "無效的電腦名稱!";
$a_invalid_mac		= "無效的 MAC 位址!";
?>
