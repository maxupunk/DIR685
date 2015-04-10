<?
/* --------------------------------------------------------- */
//$TITLE=$m_pre_title."設定";
/* --------------------------------------------------------- */
$m_title_router_setting	="路由器設定";
$m_desc_router_setting	="使用此選項指定路由器的內部網路設定".
													"在此指定的 IP 位址是用來存取的 IP 位址".
													"以 Web 為主的短理介面。如果您在此變更 IP 位址，您可能".
													"需要調整 PC 的網路設定再次存取網路";

$m_router_ipaddr	="路由器 IP 位址";
$m_subnet_mask		="預設的子網路遮罩";
$m_domain_name		="區域網域名稱";
$m_enable_dnsr		="啟用 DNS 轉送";

$m_title_dhcp_svr	="DHCP 伺服器設定";
$m_desc_dhcp_svr	="使用此選項指定內建的 DHCP 伺服器，將 IP 位址指定給".
										"在您網路上的電腦";

$m_enable_dhcp		="啟用 DHCP 伺服器";
$m_dhcp_range		="DHCP IP 位址範圍";
$m_to			="至";
$m_range_comment	="(在區域網路子網路內的位址)";
$m_lease_time		="DHCP 租用時間";
$m_netbios	="NetBIOS 通告";
$m_netbios_learn	="從 WAN 學習 NetBIOS";
$m_netbios_scope	="NetBIOS 範疇";
$m_optional	="(可選擇)";
$m_netbios_type	="NetBIOS  節點類型";
$m_broadcast	="僅廣播 (如果未指定 WINS 伺服器則可使用)";
$m_ptop	="點對點 (沒有廣播服務)";
$m_mix_mode	="混合模式 (廣播後點對點)";
$m_hybrid	="混合模式 (點對點後廣播)";
$m_primary_wins	="主要的 WINS IP 位址";
$m_secondary_wins	="輔助的 WINS IP 位址";

$m_minutes		="(分)";

$m_title_add_client	="DHCP 預留";
$m_computer_name	="電腦名稱";
$m_clone_mac		="複製您個人電腦的 MAC 位址";

$m_title_static_client_list ="DHCP 預留清單";
$remaining_wording	="可以指定的其餘用戶端數";

$m_title_client_list	="DHCP 用戶端清單";
$m_host_name		="主機名稱";
$m_ipaddr		="IP 位址";
$m_macaddr		="MAC 位址";
$m_expired_time		="逾時";

$m_days	="日";
$m_hrs	="時";
$m_mins	="分";
$m_secs	="秒";

$a_invalid_ip		="無效的 IP 位址！";
$a_invalid_netmask	="無效的子網路遮罩！";
$a_network_conflict	="無線客訪問區域網路必須與主機區不同！";
$a_lan_wan_conflict ="WAN 網路必須與 LAN 網路不同！";
$a_invalid_domain_name	="無效的網域名稱！";
$a_invalid_ip_range	="無效的 DHCP 伺服器 IP 位址範圍！";
$a_invalid_lease_time	="無效的 DHCP 租用時間！";
$a_del_confirm		="您是否確定要刪除此登錄？";
$a_same_static_mac	="已有相同的 MAC 位址。\\n 請變更此 MAC 位址。";
$a_same_static_ip	="已有相同的 IP 位址。\\n 請變更此 IP 位址。";
$a_same_static_hostname ="已有相同的電腦名稱。\\n 請變更此電腦名稱。";
$a_same_with_lan_ip	="IP 位址不能與 LAN IP 位址相同！";
$a_invalid_computer_name="無效的電腦名稱！";
$a_invalid_mac		="無效的 MAC 位址！";

$a_invalid_form         ="無效的 NetBIOS 範疇格式！ ";
$a_invalid_primaywins	="無效的 NetBIOS 主要 WINS！";
$a_invalid_secondaywins	="無效的 NetBIOS 輔助 WINS！";
$a_primary_null		="如果指定輔助的 WINS IP 位址，必須同時指定主要的 WINS IP 位址";
?>
