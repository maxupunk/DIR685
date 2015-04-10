<?
$m_gz_title_select			= "Guest Zone Selection";
$m_gz_title_router			= "Router Setting for the Guest Zone";
$m_gz_title_isolate			= "Guest Zone Client Isolation";
$m_gz_title_to_host_routing	= "Routing Between Host Zone And Guest Zone";
$m_gz_title_dhcp_server		= "DHCP Server Settings For Guest Zone";
$m_gz_title_dhcp_client		= "DHCP Client List For Guest Zone";
$m_gz_title_lock_client		= "Locked Client List For Guest Zone";

$m_gz_desc_router	=
	"Use this section to configure the guest zone settings of your router. ".
	"The guest zone provides a separate network zone for guests to access the Internet.";

$m_gz_desc_isolate	=
	"Enable the function to prevent guest clients accessing other guest clients in the Guest Zone. ".
	"Guest clients can only access the Internet.";

$m_gz_desc_to_host_routing	=
	"Use this section to enable routing between the Host Zone and Guest Zone, ".
	"Guest clients can not access Host clients' data without enabling this function.";

$m_gz_desc_dhcp_server	=
	"Use this section to configure the built-in DHCP server to assign IP addresses ".
	"to computers on your network.";

$m_gz_desc_lock_client	=
	"The function is used to lock all PC clients which are in the Guest Zone ".
	"to an IP/MAC address bundle list; only PCs in this list can access the network ".
	"after enabling the function. This makes sure that no additional clients can access ".
	"the Guest Zone regardless of whether they are using a wired or wireless connection.";

$m_enable_gzone			= "Enable Guest Zone";
$m_include_lan_port		= "Include LAN Port";
$m_include_wireless		= "Include Wireless";
$m_wireless_name		= "Wireless Network Name";
$m_ssid_comment			= "(Also called the SSID)";
$m_security_mode		= "Security Mode";
$m_router_ip			= "Router IP Address";
$m_router_netmask		= "Default Subnet Mask";
$m_enable_gzone_iso		= "Enable Guest Zone Client Isolation";
$m_enable_gzone_route	= "Enable Routing Between Zones";
$m_enable_dhcp_server	= "Enable DHCP Server";
$m_dhcp_ip_range		= "DHCP IP Address Range";
$m_to					= "to";
$m_dhcp_ip_range_comment	= "(addresses within the LAN subnet)";
$m_dhcp_lease_time		= "DHCP Lease Time";
$m_dhcp_lease_time_comment	= "(minutes)";
$m_lock_client			= "Enable LOCK CLIENT LIST";

$m_host_name		= "Host Name";
$m_expired_time		= "Expired Time";

$m_encr_none	= "Disable Wireless Security (not recommended)";
$m_encr_wep		= "Enable WEP Wireless Security (basic)";
$m_encr_wpa		= "Enable WPA Only Wireless Security (enhanced)";
$m_encr_wpa2	= "Enable WPA2 Only Wireless Security (enhanced)";
$m_encr_wpaauto	= "Enable WPA/WPA2 Wireless Security (enhanced)";

$m_title_wep	= "WEP";
$m_auth_type	= "Authentication";
$m_open			= "Open";
$m_shared_key	= "Shared Key";
$m_wep_key_len	= "WEP Encryption";
$m_64bit_wep	= "64Bit";
$m_128bit_wep	= "128Bit";
$m_hex			= "HEX";
$m_ascii		= "ASCII";
$m_key_type		= "Key Type";
$m_def_wep_key	= "Default WEP Key";
$m_wep_key		= "WEP Key";
$m_hint_wep64	= "(5 ASCII or 10 HEX)";
$m_hint_wep128	= "(13 ASCII or 26 HEX)";

$m_title_wpa	= "WPA Only";
$m_dsc_wpa		= "WPA Only requires stations to use high grade encryption and authentication.";
$m_title_wpa2	= "WPA2 Only";
$m_dsc_wpa2		= "WPA2 Only requires stations to use high grade encryption and authentication.";
$m_title_wpa_2	= "WPA/WPA2";
$m_dsc_wpa_2	= "WPA/WPA2 requires stations to use high grade encryption and authentication.";

$m_cipher_type	= "Cipher Type";
$m_tkip			= "TKIP";
$m_aes			= "AES";
$m_psk			= "PSK";
$m_eap			= "EAP";
$m_passphrase	= "Network Key";
$m_confirm_passphrase   ="Confirmed Network Key";
$m_psk_hint		= "(8~63 ASCII or 64 HEX)";

$m_8021x		= "802.1X";
$m_radius_srvr	= "RADIUS Server";
$m_shared_sec	= "Shared Secret";

$m_days	= "day(s)";
$m_hrs	= "hr(s)";
$m_mins	= "min(s)";
$m_secs	= "sec(s)";

$a_invalid_ip			= "Invalid IP Address !";
$a_invalid_netmask		= "Invalid subnet mask !";
$a_network_conflict		= "Guest zone network must be different from host zone !";
$a_invalid_ip_range		= "Invalid IP address range for DHCP server !";
$a_invalid_lease_time	= "Invalid DHCP Lease Time !";

$a_empty_ssid	= "The SSID field cannot be blank.";
$a_invalid_ssid	= "There are some invalid characters in the SSID field. Please check it.";
$a_invalid_wep_128_wep_key		= "The Key is invalid. The Key must be 13 characters or 26 hexadecimal number.";
$a_invalid_wep_64_wep_key		= "The Key is invalid. The Key must be 5 characters or 10 hexadecimal numbers.";
$a_invalid_wep_128_ascii_wep_key= "The Key is invalid. The Key must be 13 characters.";
$a_invalid_wep_128_hex_wep_key	= "The Key is invalid. The Key must be 26 hexadecimal numbers.";
$a_invalid_wep_64_ascii_wep_key	= "The Key is invalid. The Key must be 5 characters.";
$a_invalid_wep_64_hex_wep_key	= "The Key is invalid. The Key must be 10 hexadecimal numbers.";
$a_invalid_passphrase_len		= "The length of the Passphrase should be 8~63.";
$a_invalid_passphrase			= "The Passphrase should be ASCII characters.";
$a_invalid_psk					= "The PSK should be Hex.";
$a_invalid_radius_ip			= "Invalid RADIUS server.";
$a_invalid_radius_port			= "Invalid port number.";
$a_invalid_radius_sec			= "Invalid secret.";


?>
