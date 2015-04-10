﻿<?
$m_gz_title_select			="無線訪客區選擇";
$m_gz_title_router			="無線訪客區的路由器選擇";
$m_gz_title_isolate			="無線訪客區用戶端隔離";
$m_gz_title_to_host_routing	="主機域和無線訪客區之間的路由";
$m_gz_title_dhcp_server		="無線訪客區的 DHCP 伺服器設定";
$m_gz_title_dhcp_client		="無線訪客區的 DHCP 用戶端清單";
$m_gz_title_lock_client		="無線訪客區的鎖定用戶端清單";

$m_gz_desc_router	="使用此選項指定路由器的無線訪客區設定".
										"無線訪客區可以為臨時來客提供個別的網路區進行網路存取";

$m_gz_desc_isolate	="啟用此功能避免臨時來客用戶端存取在無線訪客區的其他臨時來客用戶端".
											"臨時來客用戶端只能存取網際網路";

$m_gz_desc_to_host_routing	="使用此選擇可以啟用主機域和無線訪客區之間的路由".
															"未啟用此功能前，臨時來客用戶端無法存取主機用戶端的資料";

$m_gz_desc_dhcp_server	="使用此選擇指定內建的 DHCP 伺服器，將 IP 位址指定給".
													"在您網路上的電腦";

$m_gz_desc_lock_client	="此功能是用來鎖定在無線訪客區中的全部 PC 用戶端".
													"至 IP/MAC 位址綁定清單；只有在此清單中的 PC 可以存取網路".
													"在啟用功能後。此可以確保沒有其他用戶端可以存取".
													"無線訪客區，不管這些是否使用有線或無線連線";

$m_enable_gzone			="啟用無線訪客區";
$m_include_lan_port		="包括 LAN 連接埠";
$m_include_wireless		="包括無線";
$m_wireless_name		="無線網路名稱";
$m_ssid_comment			="(亦稱為 SSID)";
$m_security_mode		="安全模式";
$m_router_ip			="路由器 IP 位址";
$m_router_netmask		="預設的子網路遮罩";
$m_enable_gzone_iso		="啟用無線訪客區用戶端隔離";
$m_enable_gzone_route	="啟用區域間的路由";
$m_enable_dhcp_server	="啟用 DHCP 伺服器";
$m_dhcp_ip_range		="DHCP IP 位址範圍";
$m_to					="至";
$m_dhcp_ip_range_comment	="(LAN 子網路內的位址)";
$m_dhcp_lease_time		="DHCP 租用時間";
$m_dhcp_lease_time_comment	="(分)";
$m_lock_client			="啟用鎖定用戶端清單";

$m_host_name		="主機名稱";
$m_expired_time		="逾時";

$m_encr_none	="停用無線安全 (不建議使用)";
$m_encr_wep		="啟用 WEP 無線安全 (基本型)";
$m_encr_wpa		="僅啟用 WPA 無線安全 (增強型)";
$m_encr_wpa2	="僅啟用 WPA2 無線安全 (增強型)";
$m_encr_wpaauto	="僅啟用 WPA/WPA2 無線安全 (增強型)";

$m_title_wep	="WEP";
$m_auth_type	="認證";
$m_open			="開啟";
$m_shared_key	="共用無線金鑰";
$m_wep_key_len	="WEP 加密";
$m_64bit_wep	="64 位元";
$m_128bit_wep	="128 位元";
$m_hex			="HEX";
$m_ascii		="ASCII";
$m_key_type		="無線金鑰類型";
$m_def_wep_key	="預設的 WEP 無線金鑰";
$m_wep_key		="WEP 無線金鑰";
$m_hint_wep64	="(5 ASCII 或 10 HEX)";
$m_hint_wep128	="(13 ASCII 或 26 HEX)";

$m_title_wpa	="僅 WPA";
$m_dsc_wpa		="僅 WPA 需要工作站使用高級加密和認證";
$m_title_wpa2	="僅 WPA2";
$m_dsc_wpa2		="僅 WPA2 需要工作站使用高級加密和認證";
$m_title_wpa_2	="WPA/WPA2";
$m_dsc_wpa_2	="WPA/WPA2 需要工作站使用高級加密和認證";

$m_cipher_type	="密碼類型";
$m_tkip			="TKIP";
$m_aes			="AES";
$m_psk			="PSK";
$m_eap			="EAP";
$m_passphrase	="網路無線金鑰";
$m_confirm_passphrase   ="確認的網路無線金鑰";
$m_psk_hint		="(8~63 ASCII 或 64 HEX)";

$m_8021x		="802.1X";
$m_radius_srvr	="RADIUS 伺服器";
$m_shared_sec	="共用金鑰";

$m_days	="日";
$m_hrs	="時";
$m_mins	="分";
$m_secs	="秒";

$a_invalid_ip			="無效的 IP 位址！";
$a_invalid_netmask		="無效的子網路遮罩！";
$a_network_conflict		="無線訪客區網路必須與主機區不同！";
$a_invalid_ip_range		=" DHCP 伺服器的 IP 位址範圍無效！";
$a_invalid_lease_time	="無效的 DHCP 租用時間";

$a_empty_ssid	="SSID 欄位不能為空白";
$a_invalid_ssid	="SSID 欄位存在部分無效位元。請檢查";
$a_invalid_wep_128_wep_key		="無線金鑰無效。無線金鑰必須為 13 個字元或 26 個十六進位數";
$a_invalid_wep_64_wep_key		="無線金鑰無效。無線金鑰必須為 5 個字元或 10 個十六進位數 ";
$a_invalid_wep_128_ascii_wep_key="無線金鑰無效。無線金鑰必須為 13 個字元";
$a_invalid_wep_128_hex_wep_key	="無線金鑰無效。無線金鑰必須為 26 個十六進位數 ";
$a_invalid_wep_64_ascii_wep_key	="無線金鑰無效。無線金鑰必須為 5 個字元";
$a_invalid_wep_64_hex_wep_key	="無線金鑰無效。無線金鑰必須為 10 個十六進位數 ";
$a_invalid_passphrase_len		="通行碼的長度必須為 8~63";
$a_invalid_passphrase			="通行碼應為 ASCII 字元";
$a_invalid_psk					="PSK 應為十六進制";
$a_invalid_radius_ip			="無效的 RADIUS 伺服器";
$a_invalid_radius_port			="無效的連接埠編號";
$a_invalid_radius_sec			="無效的金鑰";


?>
