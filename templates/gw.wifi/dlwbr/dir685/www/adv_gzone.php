<?
/* vi: set sw=4 ts=4: -------------------------------------------------------- */
$MY_NAME		= "adv_gzone";
$MY_MSG_FILE	= $MY_NAME.".php";
$CATEGORY		= "adv";
/* --------------------------------------------------------------------------- */
$DEFPASSWD	= "XxXxXxXx";
$router	= query("/runtime/router/enable");
if ($ACTION_POST!="" && $router=="1")
{
	require("/www/model/__admin_check.php");
	$dirty = 0;
	$enable_dirty = 0;
	$layout_dirty = 0;
	$wlan_dirty = 0;
	$SUBMIT_STR = "";

/*
	echo "<!--\n";
	echo "gzone_enable=".$gzone_enable."\n";
	echo "gzone_sch=".$qzone_sch."\n";
	echo "lan1=".$lan1."\n";
	echo "lan2=".$lan2."\n";
	echo "lan3=".$lan3."\n";
	echo "lan4=".$lan4."\n";
	echo "wlan=".$wlan."\n";
	echo "ssid=".$ssid."\n";
	echo "ipaddr=".$ipaddr."\n";
	echo "netmask=".$netmask."\n";
	echo "gz_iso=".$gz_iso."\n";
	echo "gz_route=".$gz_route."\n";
	echo "dhcp_server=".$dhcp_server."\n";
	echo "startipaddr=".$startipaddr."\n";
	echo "endipaddr=".$endipaddr."\n";
	echo "leasetime=".$leasetime."\n";
	echo "lockclient=".$lockclient."\n";
	echo "wlan_authtype=".$wlan_authtype."\n";
	echo "wlan_encrtype=".$wlan_encrtype."\n";
	echo "wlan_wep_length=".$wlan_wep_length."\n";
	echo "wlan_wep_format=".$wlan_wep_format."\n";
	echo "wlan_wep_defkey=".$wlan_wep_defkey."\n";
	echo "wlan_wep_key=".$wlan_wep_key."\n";
	echo "wlan_wpa_format=".$wlan_wpa_format."\n";
	echo "wlan_wpa_key=".$wlan_wpa_key."\n";
	echo "wlan_wpa_rs1_host=".$wlan_wpa_rs1_host."\n";
	echo "wlan_wpa_rs1_port=".$wlan_wpa_rs1_port."\n";
	echo "wlan_wpa_rs1_secret=".$wlan_wpa_rs1_secret."\n";
*/
	if (query("/gzone/enable")!=$gzone_enable)	{$layout_dirty++; $enable_dirty++; set("/gzone/enable", $gzone_enable);}
	anchor("/gzone/members");
//	if (query("lan:1/enable")!=$lan1)	{$layout_dirty++; set("lan:1/enable", $lan1); }
//	if (query("lan:2/enable")!=$lan2)	{$layout_dirty++; set("lan:2/enable", $lan2); }
//	if (query("lan:3/enable")!=$lan3)	{$layout_dirty++; set("lan:3/enable", $lan3); }
//	if (query("lan:4/enable")!=$lan4)	{$layout_dirty++; set("lan:4/enable", $lan4); }
//	if (query("wlan:2/enable")!=$wlan)	{$wlan_dirty++; $enable_dirty++; set("wlan:2/enable", $wlan); }
	if (query("wlan:2/enable")!=$gzone_enable)	{$layout_dirty++; $wlan_dirty++; $enable_dirty++; set("wlan:2/enable", $gzone_enable); }
	if ($gzone_enable==1)
	{
		if (query("/gzone/schedule/id")!=$gzone_sch)	{$enable_dirty++; set("/gzone/schedule/id", $gzone_sch); }
//		if ($wlan==1)
//		{
			anchor("/wlan/inf:2");
			if (query("ssid")!=$ssid)					{$wlan_dirty++; set("ssid", $ssid); }
			if (query("authtype")!=$wlan_authtype)		{$wlan_dirty++; set("authtype", $wlan_authtype); }
			if (query("encrypttype")!=$wlan_encrtype)	{$wlan_dirty++; set("encrypttype", $wlan_encrtype); }

			/* WEP */
			if ($wlan_encrtype=="1")
			{
				anchor("/wlan/inf:2/wep");
				$wepkey = "key:".$wlan_wep_defkey;
				if (query("length")!=$wlan_wep_length)	{$wlan_dirty++; set("length", $wlan_wep_length);}
				if (query("format")!=$wlan_wep_format)	{$wlan_dirty++; set("format", $wlan_wep_format); }
				if (query("defkey")!=$wlan_wep_defkey)	{$wlan_dirty++; set("defkey", $wlan_wep_defkey); }
				if (query($wepkey)!=$wlan_wep_key)		{$wlan_dirty++; set($wepkey, $wlan_wep_key);	}
			}
			/* WPA/WPA2 */
			if ($wlan_authtype == "2" || $wlan_authtype == "4" || $wlan_authtype == "6")
			{
				anchor("/wlan/inf:2/wpa/radius:1");
				if (query("host")!=$wlan_wpa_rs1_host)	{$wlan_dirty++; set("host", $wlan_wpa_rs1_host); }
				if (query("port")!=$wlan_wpa_rs1_port)	{$wlan_dirty++; set("port", $wlan_wpa_rs1_port); }
				if ($DEFPASSWD != $wlan_wpa_rs1_secret)	{$wlan_dirty++; set("secret", $wlan_wpa_rs1_secret); }
			}
			/* WPA/WPA2 PSK */
			else if ($wlan_authtype == "3" || $wlan_authtype == "5" || $wlan_authtype == "7")
			{
				anchor("/wlan/inf:2/wpa");
				if (query("format")!=$wlan_wpa_format)	{$wlan_dirty++; set("format", $wlan_wpa_format); }
				if (query("key")!=$wlan_wpa_key)		{$wlan_dirty++; set("key", $wlan_wpa_key); }
			}
//		}

		/* ethernet settings */
		anchor("/gzone/ethernet");
		if (query("ip")!=$ipaddr)					{$dirty++; set("ip", $ipaddr); }
		if (query("netmask")!=$netmask)				{$dirty++; set("netmask", $netmask); }

		/* DHCP server */
		anchor("/gzone/dhcp/server");
		if (query("enable")!=$dhcp_server)		{$dirty++; set("enable", $dhcp_server); }
		if ($dhcp_server==1)
		{
			anchor("/gzone/dhcp/server/pool:1");
			$lt = $leasetime * 60;
			if (query("startip")!=$startipaddr)	{$dirty++; set("startip", $startipaddr); }
			if (query("endip")!=$endipaddr)		{$dirty++; set("endip", $endipaddr); }
			if (query("leasetime")!=$lt)		{$dirty++; set("leasetime", $lt); }
		}
		
		/* others */
		anchor("/gzone");
		if (query("route2host")!=$gz_route)			{$dirty++; set("route2host", $gz_route); }
		if (query("isolation")!=$gz_iso)
		{
			$layout_dirty++;	set("isolation", $gz_iso); 
			$wlan_dirty++;
			if($gz_iso=="1")	{set("/wlan/inf:2/bridge/wlan2wlan", "0");}
			else				{set("/wlan/inf:2/bridge/wlan2wlan", "1");}
		}
		if ($lockclient==""){$lockclient=0;}
		if (query("lockclient/enable")!=$lockclient)
		{
			$dirty++;
			set("lockclient/enable", $lockclient);

			/* set/del the dhcp client into static dhcp list and mac filter list. */
			$LOCK_CLIENT_TYPE	="gzone"; 
			$ENABLE_LOCK_CLIENT	=$lockclient;
			require("/www/__set_lock_client_rules.php");
		}
	}
	if	($layout_dirty>0)		{$SUBMIT_STR=$SUBMIT_STR.";submit GZONE_LAYOUT";}
	else
	{
		if	($dirty>0)				{$SUBMIT_STR=$SUBMIT_STR.";submit GZONE";}
		if	($wlan_dirty>0)			{$SUBMIT_STR=$SUBMIT_STR.";submit WLAN";}
		if	($enable_dirty>0)		{$SUBMIT_STR=$SUBMIT_STR.";submit GZONE_ENABLE";}
	}

/*
	echo "SUBMIT_STR=".$SUBMIT_STR."\n";
	echo "-->\n";
*/
	$NEXT_PAGE = $MY_NAME;
	if ($SUBMIT_STR!="")	{require($G_SAVING_URL);}
	else					{require($G_NO_CHANGED_URL);}
}
/* --------------------------------------------------------------------------- */
require("/www/model/__html_head.php");
require("/www/comm/__js_ip.php");
require("/www/model/__count_rules.php");
/* --------------------------------------------------------------------------- */
$wlan_enable		= query("/wireless/enable");
$gzone_enable		= query("/gzone/enable");
//$gzone_lan1		= query("/gzone/members/lan:1/enable");
//$gzone_lan2		= query("/gzone/members/lan:2/enable");
//$gzone_lan3		= query("/gzone/members/lan:3/enable");
//$gzone_lan4		= query("/gzone/members/lan:4/enable");
//$gzone_wlan		= query("/gzone/members/wlan:2/enable");

$gzone_dhcp			= query("/gzone/dhcp/server/enable");
$gzone_dhcp_startip	= query("/gzone/dhcp/server/pool:1/startip");
$gzone_dhcp_endip	= query("/gzone/dhcp/server/pool:1/endip");
$gzone_dhcp_lease	= query("/gzone/dhcp/server/pool:1/leasetime");
if ($gzone_dhcp_lease=="") {$gzone_dhcp_lease=604800;}

$gzone_r2h	= query("/gzone/route2host");
$gzone_iso	= query("/gzone/isolation");
$gzone_lock	= query("/gzone/lockclient/enable");

anchor("/wlan/inf:2");
$wl_authtype	= query("authtype");	if ($wl_authtype=="") {$wl_authtype=0;}
$wl_encrtype	= query("encrypttype");	if ($wl_encrtype=="") {$wl_encrtype=0;}
$wl_wep_length	= query("wep/length");
$wl_wep_format	= query("wep/format");
$wl_wep_defkey	= query("wep/defkey");
$wep_path		= "wep/key:".$wl_wep_defkey;
$wl_wep_key		= get("j", $wep_path);
/*$wl_wep_key		= query("wep/key:".$wl_wep_defkey);*/
$wl_wpa_format	= query("wpa/format");
$wl_wpa_key		= get("j", "wpa/key");
/*$wl_wpa_key		= query("wpa/key");*/
$wl_rs1_host	= query("wpa/radius:1/host");
$wl_rs1_port	= query("wpa/radius:1/port");

if		($wl_encrtype==0)	{ $sectype="0"; }
else if	($wl_encrtype==1)	{ $sectype="1"; }
else if ($wl_authtype==2 || $wl_authtype==3) { $sectype="2"; }
else if ($wl_authtype==4 || $wl_authtype==5) { $sectype="3"; }
else if	($wl_authtype==6 || $wl_authtype==7) { $sectype="4"; }

$psk_eap = "psk";
if ($wl_authtype==2 || $wl_authtype==4 || $wl_authtype==6) { $psk_eap="eap";}

$dhcp_client_num=0;
for ("/runtime/dhcpserver:2/lease")
{
	if(query("expire")>0)	{$dhcp_client_num++;}
}
?>
<script>
function init()
{
	var f = get_obj("frm");
	var ipaddr;

	f.gzone_enable.checked = <? if ($gzone_enable==1) {echo "true";}else{echo "false";}?>;
//	f.lan1.checked = <? if ($gzone_lan1==1) {echo "true";}else{echo "false";}?>;
//	f.lan2.checked = <? if ($gzone_lan2==1) {echo "true";}else{echo "false";}?>;
//	f.lan3.checked = <? if ($gzone_lan3==1) {echo "true";}else{echo "false";}?>;
//	f.lan4.checked = <? if ($gzone_lan4==1) {echo "true";}else{echo "false";}?>;
//	f.wlan.checked = <? if ($gzone_wlan==1) {echo "true";}else{echo "false";}?>;
	/* TODO: wireless part is not done yet. */
	f.dhcp_server.checked = <? if ($gzone_dhcp==1) {echo "true";}else{echo "false";} ?>;
	ipaddr = get_ip("<?=$gzone_dhcp_startip?>");
	f.startip.value = ipaddr[4];
	ipaddr = get_ip("<?=$gzone_dhcp_endip?>");
	f.endip.value = ipaddr[4];
	f.leasetime.value = "<? $dummy=$gzone_dhcp_lease/60; echo $dummy; ?>";

//	if (f.wlan.checked) select_index(get_obj("security"), "<?=$sectype?>");
	if (f.gzone_enable.checked) select_index(get_obj("security"), "<?=$sectype?>");
	select_index(get_obj("auth_type"), "<?=$wl_authtype?>");
	select_index(get_obj("wep_key_len"), "<?=$wl_wep_length?>");
	select_index(get_obj("wep_def_key"), "<?=$wl_wep_defkey?>");
	
	get_obj("wepkey_64").value = "<?=$wl_wep_key?>";
	get_obj("wepkey_128").value = "<?=$wl_wep_key?>";
	
	select_index(get_obj("cipher_type"), "<?=$wl_encrtype?>");
	select_index(get_obj("psk_eap"), "<?=$psk_eap?>");
	get_obj("wpapsk1").value = "<?=$wl_wpa_key?>";
	get_obj("srv_ip1").value = "<?=$wl_rs1_host?>";
	get_obj("srv_port1").value = "<?=$wl_rs1_port?>";

	onclick_gzone_enable();
	<?if($router!=1 || $wlan_enable==0){echo "fields_disabled(f, true);\n";}?>
	return true;
}

function print_keys(key_name, max_length)
{
	var str;
	var field_size = decstr2int(max_length)+5;
	var hint = (max_length=="10") ? "<?=$m_hint_wep64?>" : "<?=$m_hint_wep128?>";
	
	str = "<table>";
	str+= "<tr>";
	str+= "		<td class='r_tb' width='200'><?=$m_wep_key?></td>";
	str+= "		<td class='l_tb'> :&nbsp;";
	str+= "			<input type='text' id='"+key_name+"' name='"+key_name+"' maxlength='"+max_length+"'";
	str+= "			size='"+field_size+"' value=''>&nbsp;"+hint;
	str+= "		</td>";
	str+= "</tr>";
	str+= "</table>";
	document.write(str);
}

function print_daytime(str_second)
{
	var time = second_to_daytime(str_second);
	var str =	(time[0]>0 ? time[0]+" <?=$m_days?> " : "") +
				(time[1]>0 ? time[1]+" <?=$m_hrs?> " : "") +
				(time[2]>0 ? time[2]+" <?=$m_mins?> " : "") +
				(time[3]>0 ? time[3]+" <?=$m_secs?> " : "");
	document.write(str);
}

function onclick_gzone_enable()
{
	var f = get_obj("frm");

	if (f.gzone_enable.checked)
	{
		f.gzone_sch.disabled = f.gzone_sch_btn.disabled =
//		f.wlan.disabled = f.ssid.disabled = f.security.disabled =
		f.ssid.disabled = f.security.disabled =
		f.ipaddr.disabled = f.netmask.disabled =
		f.gz_iso.disabled = f.gz_route.disabled =
		f.dhcp_server.disabled = f.startip.disabled = f.endip.disabled = f.leasetime.disabled = false;
		f.lockclient.disabled = <? if ($dhcp_client_num==0 && $gzone_lock!=1){echo "true";}else{echo "false";}?>;
		onclick_dhcp_server();
		/* port from onclick_wlan() */
		f.ssid.disabled = f.security.disabled = false;
	}
	else
	{
		
		f.gzone_sch.disabled = f.gzone_sch_btn.disabled =
//		f.wlan.disabled = f.ssid.disabled = f.security.disabled =
		f.ssid.disabled = f.security.disabled =
		f.ipaddr.disabled = f.netmask.disabled =
		f.gz_iso.disabled = f.gz_route.disabled =
		f.dhcp_server.disabled = f.startip.disabled = f.endip.disabled = f.leasetime.disabled =
		f.lockclient.disabled = true;
//		f.wlan.checked = false;
		/* port from onclick_wlan() */
		select_index(f.security, "0");
		f.ssid.disabled = f.security.disabled = true;
	}
//	onclick_wlan();
	onchange_security();
}

function onclick_dhcp_server()
{
	var f = get_obj("frm");
	f.startip.disabled = f.endip.disabled = f.leasetime.disabled = (f.dhcp_server.checked ? false : true);
}

//function onclick_wlan()
//{
//	var f = get_obj("frm");
//
//	if (f.wlan.checked)
//	{
//		f.ssid.disabled = f.security.disabled = false;
//	}
//	else
//	{
//		select_index(f.security, "0");
//		f.ssid.disabled = f.security.disabled = true;
//	}
//	onchange_security();
//}
function onchange_security()
{
	var obj = get_obj("security");

	get_obj("show_wep").style.display = "none";
	get_obj("show_wpa").style.display = "none";
	get_obj("title_wpa").style.display = "none";
	get_obj("title_wpa2").style.display = "none";
	get_obj("title_wpa_2").style.display = "none";

	if (obj.value == "1")
	{
		get_obj("show_wep").style.display = "";
		onchange_wep_key_len();
	}
	else if (obj.value != "0")
	{
		get_obj("show_wpa").style.display = "";
		switch (obj.value)
		{
		case "2": get_obj("title_wpa").style.display = ""; break;
		case "3": get_obj("title_wpa2").style.display = ""; break;
		case "4": get_obj("title_wpa_2").style.display = ""; break;
		}
		onchange_psk_eap();
	}
}
function onchange_wep_key_len()
{
	var obj = get_obj("wep_key_len");

	get_obj("wep_64").style.display = "none";
	get_obj("wep_128").style.display = "none";
	if (obj.value=="128")	get_obj("wep_128").style.display = "";
	else					get_obj("wep_64").style.display = "";
}
function onchange_psk_eap()
{
	var obj = get_obj("psk_eap");
	get_obj("psk_setting").style.display = "none";
	get_obj("eap_setting").style.display = "none";
	if (obj.value=="psk")	get_obj("psk_setting").style.display = "";
	else					get_obj("eap_setting").style.display = "";
					
}

function check()
{
	var f = get_obj("frm");
	var ip;
	var min, max;
	var hzone, gzone;

	if (f.gzone_enable.checked)
	{
		if (is_valid_ip(f.ipaddr.value, 0)==false)
		{
			alert("<?=$a_invalid_ip?>");
			field_focus(f.ipaddr, "**");
			return false;
		}
		if (is_valid_mask(f.netmask.value)==false)
		{
			alert("<?=$a_invalid_netmask?>");
			field_focus(f.netmask, "**");
			return false;
		}
		if (!is_valid_ip2(f.ipaddr.value, f.netmask.value))
		{
			alert("<?=$a_invalid_ip?>");
			field_focus(f.ipaddr, "**");
			return false;
		}		
		gzone = get_network_id(f.ipaddr.value, f.netmask.value);
		hzone = get_network_id("<?query("/lan/ethernet/ip");?>", f.netmask.value);
		if (gzone[0] == hzone[0])
		{
			alert("<?=$a_network_conflict?>");
			field_focus(f.ipaddr, "**");
			return false;
		}
		if (f.dhcp_server.checked)
		{
			ip = get_ip(f.ipaddr.value);
			dhcp_range_ip = get_host_range_ip(f.ipaddr.value, f.netmask.value);			
			min = parseInt(f.startip.value, [10]);
			max = parseInt(f.endip.value, [10]);

			if (!is_digit(f.startip.value))
			{
				alert("<?=$a_invalid_ip_range?>");
				field_focus(f.startip, "**");
				return false;
			}
			if (!is_digit(f.endip.value))
			{
				alert("<?=$a_invalid_ip_range?>");
				field_focus(f.endip, "**");
				return false;
			}
			if (!is_digit(f.leasetime.value))
			{
				alert("<?=$a_invalid_lease_time?>");
				field_focus(f.leasetime, "**");
				return false;
			}
			/*
			if (!is_in_range(min, 1, 254) || !is_in_range(max, 1, 254) || min > max || is_in_range(ip[4], min, max))
			{
				alert("<?=$a_invalid_ip_range?>");
				field_focus(f.startip, "**");
				return false;
			}*/
			/*
			  Use is_in_range function to determine the range is right or error
			*/
			if( !is_in_range(min, 1, 254) || !is_in_range(max, 1, 254) || min > max ||
			    min < dhcp_range_ip[0] || max > dhcp_range_ip[1] || is_in_range(ip[4], min, max))
			{
				alert("<?=$a_invalid_ip_range?>");
				field_focus(f.startip, "**");
				return false;
			}			
			if (is_blank(f.leasetime.value)||f.leasetime.value==0)
			{
				alert("<?=$a_invalid_lease_time?>");
				field_focus(f.leasetime, "**");
				return false;
			}
			ip = get_ip(f.ipaddr.value);
			f.startipaddr.value = ip[1]+"."+ip[2]+"."+ip[3]+"."+f.startip.value;
			f.endipaddr.value = ip[1]+"."+ip[2]+"."+ip[3]+"."+f.endip.value;
		}

//		if (f.wlan.checked && !check_wireless()) return false;
		if (!check_wireless()) return false;
	}

	f.submit();
	return true;
}

function check_wepkey(obj_name, key_type, key_len)
{
	var key_obj = get_obj(obj_name);
	if (key_type == 1)	/* ASCII */
	{
		if (strchk_unicode(key_obj.value))
		{
			if (key_len==13) alert("<?=$a_invalid_wep_128_ascii_wep_key?>");
			else alert("<?=$a_invalid_wep_64_ascii_wep_key?>");
			key_obj.select();
			return false;
		}
	}
	else	/* HEX */
	{
		var test_char, i;
		for (i=0; i<key_obj.value.length; i++)
		{
			test_char = key_obj.value.charAt(i);
			if ((test_char >= '0' && test_char <= '9') ||
				(test_char >= 'a' && test_char <= 'h') ||
				(test_char >= 'A' && test_char <= 'H')) continue;

			if (key_len==26) alert("<?=$a_invalid_wep_128_hex_wep_key?>");
			else alert("<?=$a_invalid_wep_64_hex_wep_key?>");
			key_obj.select();
			return false;
		}
	}
	return true;
}

function check_wireless()
{
	var f = get_obj("frm");
	var authtype="";
	var encrtype="";
	var wep_length="";
	var wep_format="";
	var wep_defkey="";
	var wep_key="";
	var wpa_format="";
	var wpa_key="";
	var rs1_host="";
	var rs1_port="";
	var rs1_secret="";
	var rs2_host="";
	var rs2_port="";
	var rs2_secret="";
	var obj, key_type;

	if (is_blank(f.ssid.value))
	{
		alert("<?=$a_empty_ssid?>");
		field_focus(f.ssid, "**");
		return false;
	}
	if (strchk_unicode(f.ssid.value))
	{
		alert("<?=$a_invalid_ssid?>");
		field_focus(f.ssid, "**");
		return false;
	}
	switch (f.security.value)
	{
	default:
	case "0":
		authtype = 0;
		encrtype = 0;
		break;
	case "1":
		authtype = f.auth_type.value == "0" ? 0 : 1;
		encrtype = 1;
		wep_defkey = f.wep_def_key.value;
		wep_length = f.wep_key_len.value;
		if (wep_length == "128")
		{
			obj = get_obj("wepkey_128");
			if (obj.value.length !=13 && obj.value.length != 26)
			{
				alert("<?=$a_invalid_wep_128_wep_key?>");
				obj.select();
				return false;
			}
			key_type = (obj.value.length == 13) ? 1:2;
			if (check_wepkey("wepkey_128", key_type, obj.value.length)==false) return false;
		}
		else
		{
			obj = get_obj("wepkey_64");
			if (obj.value.length != 5 && obj.value.length != 10)
			{
				alert("<?=$a_invalid_wep_64_wep_key?>");
				obj.select();
				return false;
			}
			key_type = (obj.value.length == 5) ? 1:2;
			if (check_wepkey("wepkey_64", key_type, obj.value.length)==false) return false;
		}
		wep_format = key_type;
		wep_key = obj.value;
		break;

	case "2":
	case "3":
	case "4":

		encrtype = get_obj("cipher_type").value;
		if (get_obj("psk_eap").value == "psk")
		{
			switch (f.security.value)
			{
			case "2": authtype = 3; break;
			case "3": authtype = 5; break;
			case "4": authtype = 7; break;
			}
			wpa_key = get_obj("wpapsk1").value;
			if (wpa_key.length == 64)
			{
				var test_char,j;
				for (j=0; j<wpa_key.length; j++)
				{
					test_char = wpa_key.charAt(j);
					if ((test_char >= '0' && test_char <= '9') ||
						(test_char >= 'a' && test_char <= 'h') ||
						(test_char >= 'A' && test_char <= 'H')) continue;
					alert("<?=$a_invalid_psk?>");
					field_focus(get_obj("wpapsk1"), "**");
					return false;
				}
				wpa_format = 2;
			}
			else
			{
				if (wpa_key.length <8 || wpa_key.length > 63)
				{
					alert("<?=$a_invalid_passphrase_len?>");
					field_focus(get_obj("wpapsk1"), "**");
					return false;
				}
				if(strchk_unicode(wpa_key))
				{
					alert("<?=$a_invalid_passphrase?>");
					field_focus(get_obj("wpapsk1"), "**");
					return false;
				}
				wpa_format = 1;
			}
		}
		else
		{
			switch (f.security.value)
			{
			case "2": authtype = 2; break;
			case "3": authtype = 4; break;
			case "4": authtype = 6; break;
			}
			obj = get_obj("srv_ip1");
			if (!is_valid_ip(obj.value, 0))
			{
				alert("<?=$a_invalid_radius_ip?>");
				field_focus(obj, "**");
				return false;
			}

			obj = get_obj("srv_port1");
			if (is_blank(obj.value) || !is_valid_port_str(obj.value))
			{
				alert("<?=$a_invalid_radius_port?>");
				field_focus(obj, "**");
				return false;
			}

			obj = get_obj("srv_sec1");
			if (is_blank(obj.value) || strchk_unicode(obj.value))
			{
				alert("<?=$a_invalid_radius_sec?>");
				field_focus(obj, "**");
				return false;
			}

			rs1_host	= get_obj("srv_ip1").value;
			rs1_port	= get_obj("srv_port1").value;
			rs1_secret	= get_obj("srv_sec1").value;
		}
		break;
	}

	get_obj("wlan_authtype").value		= authtype;
	get_obj("wlan_encrtype").value		= encrtype;
	get_obj("wlan_wep_length").value	= wep_length;
	get_obj("wlan_wep_format").value	= wep_format;
	get_obj("wlan_wep_defkey").value	= wep_defkey;
	get_obj("wlan_wep_key").value		= wep_key;
	get_obj("wlan_wpa_format").value	= wpa_format;
	get_obj("wlan_wpa_key").value		= wpa_key;
	get_obj("wlan_wpa_rs1_host").value	= rs1_host;
	get_obj("wlan_wpa_rs1_port").value	= rs1_port;
	get_obj("wlan_wpa_rs1_secret").value= rs1_secret;
	return true;
}

function do_cancel()
{
	self.location.href = "<?=$MY_NAME?>.php?randome_str="+generate_random_str();
}
</script>
<body onload="init();" <?=$G_BODY_ATTR?>>
<form name="frm" id="frm" method="post" action="<?=$MY_NAME?>.php"  onsubmit="return check()">
<input type="hidden" name="ACTION_POST" value="SOMETHING">
<?require("/www/model/__banner.php");?>
<?require("/www/model/__menu_top.php");?>
<table <?=$G_MAIN_TABLE_ATTR?> height="100%">
<tr valign=top>
	<td <?=$G_MENU_TABLE_ATTR?>>
	<?require("/www/model/__menu_left.php");?>
	</td>
	<td id="maincontent">
		<div id="box_header">
		<? require($LOCALE_PATH."/dsc/dsc_".$MY_NAME.".php"); ?>
		<script>apply('check()'); echo("&nbsp;"); cancel('');</script>
		</div>
<!-- ________________________________ Main Content Start ______________________________ -->
		<div class="box">
			<h2><?=$m_gz_title_select?></h2>
			<table cellpadding="1" cellspacing="1" border="0" width="525">
			<tr>
				<td class="r_tb" width="200"><?=$m_enable_gzone?> :</td>
				<td class="l_tb">&nbsp;
					<input type="checkbox" name="gzone_enable" id="gzone_enable" value="1"
					onClick="onclick_gzone_enable()">&nbsp;
<?						$PREFIX		= "\t\t\t\t\t";
						$OBJID		= "gzone_sch";
						$OBJNAME	= "gzone_sch";
						$UNIQUEID	= query("/gzone/schedule/id");
						require("/www/__schedule_combobox.php"); ?>
				</td>
			</tr>
<!--
			<tr>
				<td class="r_tb"><?=$m_include_lan_port?> :</td>
				<td class="l_tb">&nbsp;
					<input type="checkbox" name="lan1" id="lan1" value="1">&nbsp;1
					<input type="checkbox" name="lan2" id="lan2" value="1">&nbsp;2
					<input type="checkbox" name="lan3" id="lan3" value="1">&nbsp;3
					<input type="checkbox" name="lan4" id="lan4" value="1">&nbsp;4
				</td>
			</tr>			
			<tr>
				<td class="r_tb"><?=$m_include_wireless?> :</td>
				<td class="l_tb">&nbsp;
					<input type="checkbox" name="wlan" id="wlan" value="1"
					onclick="onclick_wlan()">
				</td>
			</tr>
-->
			<tr>
				<td class="r_tb"><?=$m_wireless_name?> :</td>
				<td class="l_tb">&nbsp;&nbsp;
					<input type="text" name="ssid" id="ssid" size="20" maxlength="32" value="<?
					get("h","/wlan/inf:2/ssid");?>">&nbsp;<?=$m_ssid_comment?>
				</td>
			</tr>
			<tr>
				<td class="r_tb"><?=$m_security_mode?> :</td>
				<td class="l_tb">&nbsp;&nbsp;
					<select id="security" onchange="onchange_security()">
						<option value="0"><?=$m_encr_none?></option>
						<option value="1"><?=$m_encr_wep?></option>
						<option value="2"><?=$m_encr_wpa?></option>
						<option value="3"><?=$m_encr_wpa2?></option>
						<option value="4"><?=$m_encr_wpaauto?></option>
					</select>
				</td>
			</tr>
			</table>
			<input type="hidden" value="" id="wlan_authtype"		name="wlan_authtype">
			<input type="hidden" value="" id="wlan_encrtype"		name="wlan_encrtype">
			<input type="hidden" value="" id="wlan_wep_length"		name="wlan_wep_length">
			<input type="hidden" value="" id="wlan_wep_format"		name="wlan_wep_format">
			<input type="hidden" value="" id="wlan_wep_defkey"		name="wlan_wep_defkey">
			<input type="hidden" value="" id="wlan_wep_key"			name="wlan_wep_key">
			<input type="hidden" value="" id="wlan_wpa_format"		name="wlan_wpa_format">
			<input type="hidden" value="" id="wlan_wpa_key"			name="wlan_wpa_key">
			<input type="hidden" value="" id="wlan_wpa_rs1_host"	name="wlan_wpa_rs1_host">
			<input type="hidden" value="" id="wlan_wpa_rs1_port"	name="wlan_wpa_rs1_port">
			<input type="hidden" value="" id="wlan_wpa_rs1_secret"	name="wlan_wpa_rs1_secret">
		</div>
		<!-- WEP -->
		<div class="box" id="show_wep" style="display:none">
			<h2><?=$m_title_wep?></h2>
<?
			$dummy=fread($LOCALE_PATH."/bsc_wlan_msg1.php");
			if ($dummy=="")	{ require("/www/locale/en/bsc_wlan_msg1.php"); }
			else			{ require($LOCALE_PATH."/bsc_wlan_msg1.php"); }
?>
			<table cellpadding="1" cellspacing="1" border="0" width="525">
			<tr>
				<td class='r_tb' width='200'><?=$m_auth_type?></td>
				<td class='l_tb'> :&nbsp;
					<select id="auth_type">
						<option value="0"><?=$m_open?></option>
						<option value="1"><?=$m_shared_key?></option>
					</select>
				</td>
			</tr>
			<tr>
				<td class='r_tb' width='200'><?=$m_wep_key_len?></td>
				<td class='l_tb'> :&nbsp;
					<select id="wep_key_len" size=1 onchange="onchange_wep_key_len()">
						<option value="64"><?=$m_64bit_wep?></option>
						<option value="128"><?=$m_128bit_wep?></option>
					</select>
				</td>
			</tr>
			<tr>
				<td class='r_tb' width='200'><?=$m_def_wep_key?></td>
				<td class='l_tb'> :&nbsp;
					<select id="wep_def_key">
						<option value="1"><?=$m_wep_key?> 1</option>
						<option value="2"><?=$m_wep_key?> 2</option>
						<option value="3"><?=$m_wep_key?> 3</option>
						<option value="4"><?=$m_wep_key?> 4</option>
					</select>
				</td>
			</tr>
			</table>
			<div id="wep_64" style="display:none"><script>print_keys("wepkey_64","10");</script></div>
			<div id="wep_128" style="display:none"><script>print_keys("wepkey_128","26");</script></div>
		</div>
		<!-- WPA, WPA2, WPA/WPA2 -->
		<div class="box" id="show_wpa" style="display:none">
			<div id="title_wpa" style="display:none"><h2><?=$m_title_wpa?></h2><p><?=$m_dsc_wpa?></p></div>
			<div id="title_wpa2" style="display:none"><h2><?=$m_title_wpa2?></h2><p><?=$m_dsc_wpa2?></p></div>
			<div id="title_wpa_2" style="display:none"><h2><?=$m_title_wpa_2?></h2><p><?=$m_dsc_wpa_2?></p></div>
			<div>
				<table>
				<tr>
					<td class='r_tb' width='200'><?=$m_cipher_type?></td>
					<td class='l_tb'> :&nbsp;
						<select id="cipher_type">
							<option value="2"><?=$m_tkip?></option>
							<option value="3"><?=$m_aes?></option>
							<option value="4"><?=$m_both?></option>
						</select>
					</td>
				</tr>
				<tr>
					<td class='r_tb' width='200'><?=$m_psk?> / <?=$m_eap?></td>
					<td class='l_tb'> :&nbsp;
						<select id="psk_eap" onchange="onchange_psk_eap()">
							<option value="psk"><?=$m_psk?></option>
							<option value="eap"><?=$m_eap?></option>
						</select>
					</td>
				</tr>
			</table>
			</div>
			<!-- PSK -->
			<div id="psk_setting" style="display:none">
				<table id=passphrase>
				<tr>
					<td class='r_tb' width='150'><?=$m_passphrase?></td>
					<td class='l_tb'> :&nbsp;
						<input type="text" id="wpapsk1" size="40" maxlength="64" value="">
						<?=$m_psk_hint?>
					</td>
				</tr>
				</table>
			</div>
			<!-- EAP -->
			<div id="eap_setting" style="display:none">
			<table>
				<tr><td class=l_tb><?=$m_8021x?></td></tr>
				<tr>
					<td>
						<table>
						<tr>
							<td class='r_tb' width='120'><?=$m_radius_srvr?></td>
							<td class='l_tb'><?=$m_ipaddr?></td>
							<td class='l_tb'> :&nbsp;
								<input type="text" id="srv_ip1" maxlength=15 size=15 value="">
							</td>
						</tr>
						<tr>
							<td class='r_tb' width='120'></td>
							<td class='l_tb'><?=$m_port?></td>
							<td class='l_tb'> :&nbsp;
								<input type="text" id="srv_port1" size="8" maxlength="5" value="">
							</td>
						</tr>
						<tr>
							<td class='r_tb' width='120'></td>
							<td class='l_tb'><?=$m_shared_sec?></td>
							<td class='l_tb'> :&nbsp;
								<input type="password" id="srv_sec1" size="50" maxlength="64" value="<?=$DEFPASSWD?>">
							</td>
						</tr>
						</table>
					</td>
				</tr>
			</table>
			</div>
		</div>
		<!-- end wireless -->
		<div class="box">
			<h2><?=$m_gz_title_router?></h2>
			<p><?=$m_gz_desc_router?></p>
			<table cellpadding="1" cellspacing="1" border="0" width="525">
			<tr>
				<td class="r_tb" width="200"><?=$m_router_ip?> :</td>
				<td class="l_tb">&nbsp;&nbsp;
					<input type="text" name="ipaddr" id="ipaddr" size="20" maxlength="15" value="<?
					query("/gzone/ethernet/ip");?>">
				</td>
			</tr>
			<tr>
				<td class="r_tb" width="200"><?=$m_router_netmask?> :</td>
				<td class="l_tb">&nbsp;&nbsp;
					<input type="text" name="netmask" id="netmask" size="20" maxlength="15" value="<?
					query("/gzone/ethernet/netmask");?>">
				</td>
			</tr>
			</table>
		</div>
		<div class="box">
			<h2><?=$m_gz_title_isolate?></h2>
			<p><?=$m_gz_desc_isolate?></p>
			<table cellpadding="1" cellspacing="1" border="0" width="525">
			<tr>
				<td class="r_tb" width="200"><?=$m_enable_gzone_iso?> :</td>
				<td class="l_tb">&nbsp;
					<input type="checkbox" name="gz_iso" id="gz_iso" value="1"<?
					if ($gzone_iso==1) {echo " checked";}
					?>>
				</td>
			</tr>
			</table>
		</div>
		<div class="box">
			<h2><?=$m_gz_title_to_host_routing?></h2>
			<p><?=$m_gz_desc_to_host_routing?></p>
			<table cellpadding="1" cellspacing="1" border="0" width="525">
			<tr>
				<td class="r_tb" width="200"><?=$m_enable_gzone_route?> :</td>
				<td class="l_tb">&nbsp;
					<input type="checkbox" name="gz_route" id="gz_route" value="1"<?
					if ($gzone_r2h==1) {echo " checked";}
					?>>
				</td>
			</tr>
			</table>
		</div>
		<div class="box">
			<h2><?=$m_gz_title_dhcp_server?></h2>
			<p><?=$m_gz_desc_dhcp_server?></p>
			<table cellpadding="1" cellspacing="1" border="0" width="525">
			<tr>
				<td class="r_tb" width="200"><?=$m_enable_dhcp_server?> :</td>
				<td class="l_tb">&nbsp;
					<input type="checkbox" name="dhcp_server" id="dhcp_server"
					onclick="onclick_dhcp_server()" value="1">
				</td>
			</tr>
			<tr>
				<td class="r_tb"><?=$m_dhcp_ip_range?> :</td>
				<td class="l_tb">&nbsp;&nbsp;
					<input type="text" id="startip" size="3" maxlength="3" value="">
					&nbsp;<?=$m_to?>&nbsp;
					<input type="text" id="endip" size="3" maxlength="3" value="">
					&nbsp;<?=$m_dhcp_ip_range_comment?>
					<input type="hidden" name="startipaddr" id="startipaddr" value="">
					<input type="hidden" name="endipaddr" id="endipaddr" value="">
				</td>
			</tr>
			<tr>
				<td class="r_tb"><?=$m_dhcp_lease_time?> :</td>
				<td class="l_tb">&nbsp;&nbsp;
					<input type="text" name="leasetime" id="leasetime" size="6" maxlength="6" value="">
					&nbsp;<?=$m_dhcp_lease_time_comment?>
				</td>
			</tr>
			</table>
		</div>
		<div class="box">
			<h2><?=$m_gz_title_dhcp_client?></h2>
			<table width="525" border=0 cellPadding=1 cellSpacing=1>
			<tr>
				<td class="l_tb"><?=$m_host_name?></td>
				<td class="l_tb"><?=$m_ipaddr?></td>
				<td class="l_tb"><?=$m_macaddr?></td>
				<td class="l_tb"><?=$m_expired_time?></td>
				<td></td>
			</tr>
			<tr><td></td><td></td><td></td></tr>
<?
for ("/runtime/dhcpserver:2/lease")
{ echo
"			<tr>\n".
"				<td class=\"l_tb\">".get(h,"hostname")."</td>\n".
"				<td class=\"l_tb\">".query("ip")."</td>\n".
"				<td class=\"l_tb\">".query("mac")."</td>\n".
"				<td class=\"l_tb\"><script>print_daytime(\"".query("expire")."\");</script></td>\n".
"			</tr>\n";
}
?>			</table>
		</div>
		<div class="box">
			<h2><?=$m_gz_title_lock_client?></h2>
			<p><?=$m_gz_desc_lock_client?></p>
			<table cellpadding="1" cellspacing="1" border="0" width="525">
			<tr>
				<td class="r_tb" width="200"><b><?=$m_lock_client?></b> :</td>
				<td class="l_tb">&nbsp;&nbsp;
					<input type="checkbox" name="lockclient" id="lockclient" value="1"<?
					if ($gzone_lock==1) {echo " checked";}
					?>>
				</td>
			</tr>
			</table>
		</div>
		<div id="box_bottom">
		<script>apply('check()'); echo("&nbsp;"); cancel('');</script>
		</div>
<!-- ________________________________  Main Content End _______________________________ -->
	</td>
	<td <?=$G_HELP_TABLE_ATTR?>><?require($LOCALE_PATH."/help/h_".$MY_NAME.".php");?></td>
</tr>
</table>
<?require("/www/model/__tailer.php");?>
</form>
</body>
</html>
