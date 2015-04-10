<?
/* vi: set sw=4 ts=4: ---------------------------------------------------------*/
$MY_NAME		="st_device";
$MY_MSG_FILE	=$MY_NAME.".php";
$CATEGORY		="st";
/* --------------------------------------------------------------------------- */
require("/www/model/__html_head.php");
/* --------------------------------------------------------------------------- */
if(query("/lan/dhcp/server/enable")==1) {$dhcp_en=$m_enabled;}
else                                    {$dhcp_en=$m_disabled;}

/* transfer wan cable link type */
$cable_link_type	= query("/runtime/switch/wan_port/linktyp");
$msg_cable_link_type="";
if($cable_link_type==1)			{$msg_cable_link_type="100 Full";}
else if($cable_link_type==2)	{$msg_cable_link_type="100 Half";}
else if($cable_link_type==3)	{$msg_cable_link_type="10 Full";}
else if($cable_link_type==4)	{$msg_cable_link_type="10 Half";}
else if($cable_link_type==5)	{$msg_cable_link_type="1000 Full";}
else if($cable_link_type==6)	{$msg_cable_link_type="1000 Half";}
else 							{$msg_cable_link_type="Disconnect";}


anchor("/runtime/wan/inf:1");
if (query("connectstatus") == "connected")
{
	$wan_status = $m_connected;
	$wanipaddr	= query("ip");
	$wansubnet	= query("netmask");
	$wangateway	= query("gateway");
	$wandns		= query("primarydns")."&nbsp;".query("secondarydns");
}
else
{
	$wan_status = $m_disconnected;
	$wanipaddr	= $m_null_ip;
	$wansubnet	= $m_null_ip;
	$wangateway	= $m_null_ip;
	$wandns		= $m_null_ip;
}
$router=query("/runtime/router/enable");
if($router == "1")
{
	$wanmode = query("/wan/rg/inf:1/mode");
}
else
{
	$wanmode = query("/runtime/wan/inf:1/connecttype");
}
$autodns = query("/wan/rg/inf:1/pppoe/autodns");
if ($wanmode == 1)
{
	$msg_wanmode	= $m_static_ip;
	if($msg_cable_link_type=="Disconnect")	{$msg_wanstatus	= $m_disconnected;}
	else									{$msg_wanstatus	= $m_connected;}
	$msg_connect	= "";
	$msg_disconnect	= "";
}
else if ($wanmode == 2)
{
	$msg_wanmode	= $m_dhcp_client;
	$msg_wanstatus	= $wan_status;
	$msg_connect	= $m_dhcp_renew;
	$msg_disconnect	= $m_dhcp_release;
}
else if ($wanmode == 3)
{
	$msg_wanmode	= $m_pppoe;
	$msg_wanstatus  = $wan_status;
	$msg_connect	= $m_connect;
	$msg_disconnect	= $m_disconnect;
	$wangateway		= $wanipaddr;
	if ($wandns == $m_null_ip && $autodns == "0")
	{
		anchor("/dnsrelay/server");
		$wandns = query("primarydns")."&nbsp;".query("secondarydns");
	}
}
else if ($wanmode == 4)
{
	$msg_wanmode	= $m_pptp;
	$msg_wanstatus	= $wan_status;
	$msg_connect	= $m_connect;
	$msg_disconnect	= $m_disconnect;
	$wangateway		= $wanipaddr;
	if ($wandns == $m_null_ip || $wandns == "" || $wandns == "&nbsp;")
	{
		anchor("/runtime/wan/inf:2");
		$wandns = query("primarydns")."&nbsp;".query("secondarydns");
	}
	if ($wandns == $m_null_ip || $wandns == "" || $wandns == "&nbsp;")
	{
		anchor("/dnsrelay/server");
		$wandns = query("primarydns")."&nbsp;".query("secondarydns");
	}
}
else if ($wanmode == 5)
{
	$msg_wanmode	= $m_l2tp;
	$msg_wanstatus	= $wan_status;
	$msg_connect	= $m_connect;
	$msg_disconnect	= $m_disconnect;
	$wangateway		= $wanipaddr;
	if ($wandns == $m_null_ip || $wandns == "" || $wandns == "&nbsp;")
	{
		anchor("/runtime/wan/inf:2");
		$wandns = query("primarydns")."&nbsp;".query("secondarydns");
	}
	if ($wandns == $m_null_ip || $wandns == "" || $wandns == "&nbsp;")
	{
		anchor("/dnsrelay/server");
		$wandns = query("primarydns")."&nbsp;".query("secondarydns");
	}
}
else if ($wanmode == 6)
{
	$msg_wanmode = $m_wwan;
	$msg_wanstatus = $wan_status;
	$msg_connect = $m_connect;
	$msg_disconnect = $m_disconnect;
	$wangateway		= $wanipaddr;
}

/* wireless part */
anchor("/wireless");
$wlan_en	= query("enable");
if($wlan_en == 1)
{
	$wep_len	= query("wep/length");
	$ssid		= get(h,"ssid");
	$str_sec	= "";
	$auth		= query("authtype");
	$sec		= query("encrypttype");
	
	if		($sec=="0")					{$security_type="0";}
	else if	($sec=="1")					{$security_type="1";$str_sec=$str_sec."&nbsp;".$m_title_wep;}
	if		($auth=="2" || $auth=="3")	{$security_type="2";$str_sec=$str_sec."&nbsp;".$m_title_wpa;}
	else if ($auth=="4" || $auth=="5")	{$security_type="3";$str_sec=$str_sec."&nbsp;".$m_title_wpa2;}
	else if ($auth=="6" || $auth=="7")	{$security_type="4";$str_sec=$str_sec."&nbsp;".$m_title_wpa2_auto;}

	if (query("autochannel")!=1 || $wlan_en==0)	{$channel = query("channel");}
	else {$channel = query("/runtime/stats/wireless/channel");}

	if		($sec==1)   {$str_sec = $str_sec."-".$wep_len."&nbsp;".$m_bits; }
	else if	($sec==2)   {$str_sec = $str_sec."-".$m_tkip; }
	else if	($sec==3)   {$str_sec = $str_sec."-".$m_aes; }
	else if	($sec==4)   {$str_sec = $str_sec."-".$m_cipher_auto; }
	else				{$str_sec = $str_sec."&nbsp;".$m_disabled; }
	
	if($security_type=="2" || $security_type=="3" || $security_type=="4")
	{
		if($auth=="2" || $auth=="4" || $auth=="6")	{$str_sec=$str_sec."-".$m_eap;}
		else										{$str_sec=$str_sec."-".$m_psk;}
	}
}

$cfg_wlanmode 	= query("wlanmode");
if($cfg_wlanmode=="8" || $cfg_wlanmode=="12")
{$msg_wlanmode="5GHz";}
else
{$msg_wlanmode="2.4GHz";}

?>


<script>
var DisplayTime = new Date();
var toffset ;  // diff betweeen PC and Server
var ReloadCount = 0;
var date = "<?query('/runtime/time/date');?>";
var time = "<?query('/runtime/time/time');?>";
var SysTime = new Date();

//wan connect time
var WANDisplayTime = new Date();
var wan_toffset ;  // diff betweeen PC and Server
<?
if(query("/runtime/wan/inf:1/uptime")=="")	{echo "var wan_up_time = 0;\n";}
else										{echo "var wan_up_time = ".query("/runtime/wan/inf:1/uptime").";\n";}
if(query("/runtime/sys/uptime")=="")		{echo "var sys_uptime = 0;\n";}
else										{echo "var sys_uptime = ".query("/runtime/sys/uptime").";\n";}
?>

function freshTime(){
  var dateStr = date+" "+time;
  DisplayTime.setTime(Date.parse(dateStr));
  toffset = DisplayTime - SysTime;
  
  wan_toffset = sys_uptime - wan_up_time;
  
  showTime();
}   
function showTime(){
	toffset+=1000;
	DisplayTime.setTime(SysTime.getTime() + toffset);
	/*var clock = "" +  DisplayTime.getFullYear() + "/" + (DisplayTime.getMonth()+1) + "/" + DisplayTime.getDate() + 
	" " + DisplayTime.getHours() + ":" + DisplayTime.getMinutes() + ":" +  DisplayTime.getSeconds();*/
	var str_year = "" +  DisplayTime.getFullYear();
	var str_month = "" + (DisplayTime.getMonth()+1);
	var str_date = "" + DisplayTime.getDate();
	var str_hour = "" + DisplayTime.getHours();
	var str_min = "" + DisplayTime.getMinutes();
	var str_second = "" + DisplayTime.getSeconds();
	var clock = str_year + "/" + (str_month.length<2?"0":"") + str_month + "/" + (str_date.length<2?"0":"") + str_date + " " +
		(str_hour.length<2?"0":"") + str_hour + ":" + (str_min.length<2?"0":"") + str_min + ":" + (str_second.length<2?"0":"") + str_second;
	
	document.getElementById("Timer_session").innerHTML = clock;
	if (ReloadCount++ >= (60*5)){//5 min reload again
    	location.reload();
    }
    
    //wan connect time
	wan_toffset+=1;
	//if("<?=$wanipaddr?>"=="<?=$m_null_ip?>")//jana removed
	if("<?=$wanipaddr?>"=="<?=$m_null_ip?>" || document.frm.connstate.value == "<?=$m_disconnected?>")//jana added
	{
		document.getElementById("WANTimer_session").innerHTML = "0 Days, 00:00:00";
	}
	else
	{
		document.getElementById("WANTimer_session").innerHTML = calculate_wan_time(wan_toffset);
		//setTimeout("showTime();",1000);//jana removed
	}
	setTimeout("showTime();",1000);//jana added
}
function calculate_wan_time(total)
{
	hour=parseInt(total/3600,10);
	sec=total-hour*3600;
	if(sec>=60)
	{
		min=parseInt(sec/60,10);
		sec=sec-min*60;
	}
	else
		min=0;
	if(hour>=24)
	{
		day=parseInt(hour/24,10);
		hour=hour-day*24;
	}
	else
		day=0;
	var wstr_hour = "" + hour;
	var wstr_min = "" + min;
	var wstr_sec = "" + sec;
	var str=""+day+" Days, "+(wstr_hour.length<2?"0":"")+wstr_hour+":"+(wstr_min.length<2?"0":"")+wstr_min+":"+(wstr_sec.length<2?"0":"")+wstr_sec;
	return str;
}

function do_connect()
{
	get_obj("bt_connect").disabled = true;
	send_request("conninfo.xgi?r="+generate_random_str()+"&set/runtime/wan/inf:1/connect=1");
	//self.location.href="<?=$MY_NAME?>.xgi?set/runtime/wan/inf:1/connect=1";
}

function do_disconnect()
{
	get_obj("bt_disconnect").disabled = true;
	send_request("conninfo.xgi?r="+generate_random_str()+"&set/runtime/wan/inf:1/disconnect=1");
	//self.location.href="<?=$MY_NAME?>.xgi?set/runtime/wan/inf:1/disconnect=1";
}

var AjaxReq = null;

function send_request(url)
{
	if (AjaxReq == null) AjaxReq = createRequest();
	AjaxReq.open("GET", url, true);
	AjaxReq.onreadystatechange = update_page;
	AjaxReq.send(null);
}

function update_state()
{
	send_request("/conninfo.php?r="+generate_random_str());
}

/* var count = 0; */
var period = 3000;

function update_page()
{
/*
	count++;
	get_obj("connstate").value = count + " r="+AjaxReq.readyState+",t="+AjaxReq.responseText;
 */
	if (AjaxReq != null && AjaxReq.readyState == 4)
	{
		if (AjaxReq.responseText.substring(0,3)=="var")
		{
			eval(AjaxReq.responseText);
/*
			get_obj("connstate").value = count + " r:"+result[0]+","+result[1];
 */
			switch (result[0])
			{
			case "OK":
				if (result[1] == "connected")
				{
					/* jana removed
					<?
					if ($wanmode == "3" || $wanmode == "4" || $wanmode == "5")
					{	echo "result[4] = result[2];\n";	}
					?>
					get_obj("connstate").value		= "<?=$m_connected?>";
					get_obj("wanipaddr").innerHTML	= "&nbsp;"+result[2];
					get_obj("wansubnet").innerHTML	= "&nbsp;"+result[3];
					get_obj("wangateway").innerHTML	= "&nbsp;"+result[4];
					get_obj("wandns").innerHTML		= "&nbsp;"+result[5];
					*/
					self.location.href="<?=$MY_NAME?>.php";//jana added
					
					get_obj("bt_connect").disabled = true;
					get_obj("bt_disconnect").disabled = false;
					//showTime();//jana removed
				}
					else if(result[1] == "disconnected")
					{
						get_obj("connstate").value		= "<?=$m_disconnected?>";
						get_obj("wanipaddr").innerHTML	= "&nbsp;<?=$m_null_ip?>";
						get_obj("wansubnet").innerHTML	= "&nbsp;<?=$m_null_ip?>";
						get_obj("wangateway").innerHTML	= "&nbsp;<?=$m_null_ip?>";
						get_obj("wandns").innerHTML		= "&nbsp;<?=$m_null_ip?>";
						
						get_obj("bt_connect").disabled = false;
						get_obj("bt_disconnect").disabled = true;
					}
					else if(result[1] == "connecting" || result[1] == "disconnecting")
					{
						if(result[1] == "connecting")
							connstate = "<?=$m_connecting?>";
						else
							connstate = "<?=$m_disconnecting?>";
						get_obj("connstate").value		= connstate;
						get_obj("wanipaddr").innerHTML	= "&nbsp;<?=$m_null_ip?>";
						get_obj("wansubnet").innerHTML	= "&nbsp;<?=$m_null_ip?>";
						get_obj("wangateway").innerHTML	= "&nbsp;<?=$m_null_ip?>";
						get_obj("wandns").innerHTML		= "&nbsp;<?=$m_null_ip?>";
						
						get_obj("bt_connect").disabled = true;
						get_obj("bt_disconnect").disabled = true;
	
					}
				setTimeout("update_state()", period);
				break;
			case "WAIT":
				setTimeout("update_state()", period);
				break;
			}
			delete result;
		}
	}
}

/* page init functoin */
function init()
{
	freshTime();
	<?
	if ($router!="1")
	{
		echo "get_obj('show_lan').style.display = 'none';\n";
	}
	anchor("/runtime/wan/inf:1");
	$connstatus = query("connectstatus");
	if($connstatus == "connected")
	{
		$bt_con    = "true";
		$bt_discon = "false";
	}
	else if($connstatus == "disconnected")
	{
		$bt_con    = "false";
		$bt_discon = "true";
	}
	else if($connstatus == "connecting" || $connstatus == "disconnecting")
	{
		$bt_con    = "true";
		$bt_discon = "true";
		if($connstatus == "connecting")
		{
			$msg_wanstatus = $m_connecting;
		}
		else
		{
			 $msg_wanstatus = $m_disconnecting;
		}
	}
	else // "on demand" or empty
	{
		$bt_con    = "false";
		$bt_discon = "true";
	}
	if ($AUTH_GROUP=="0" && $msg_connect!="" && $router=="1")
	{
		if($bt_con!="" && $bt_discon!="")
		{
		echo "get_obj(\"bt_connect\").disabled = ".$bt_con.";\n";
		echo "get_obj(\"bt_disconnect\").disabled = ".$bt_discon.";\n";
		}
	}
	if (query("connectstatus")!="connected")
	{
		echo "setTimeout(\"update_state()\", period);\n";
	}
	else if ($wanmode == 3)	{$msg_wanstatus=$wan_status;}
	
	if(query("connectstatus")=="connected" && $msg_connect!="" && $router=="1")
	{
		echo "get_obj('bt_connect').disabled = true;\n";
	}
	?>
}
/* parameter checking */
function check()
{
}
/* cancel function */
function do_cancel()
{
	self.location.href="<?=$MY_NAME?>.php?random_str="+generate_random_str();
}

</script>
<body onload="init();" <?=$G_BODY_ATTR?>>
<form name="frm" id="frm" method="post" action="<?=$MY_NAME?>.php">
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
		</div>
<!-- ________________________________ Main Content Start ______________________________ -->
		<div class="box">
			<h2><?=$m_general?></h2>
			<table cellpadding="1" cellspacing="1" border="0" width="525">
			<tr>
				<td class="r_tb" width="198"><?=$m_time?>&nbsp;:</td>
				<td class="l_tb" width=320><span id="Timer_session"></span></td>
			</tr>
			<tr>
				<td class="r_tb" width="198"><strong><?=$m_fw_ver?>&nbsp;:</strong></td>
				<td class="l_tb" width=320><strong>&nbsp;<?query("/runtime/sys/info/firmwareversion");?>&nbsp;,&nbsp;
					<?query("/runtime/sys/info/firmwarebuildate");?></strong></td>
			</tr>
			</table>
		</div>
		<div class="box">
			<h2><?if($router!="1"){echo $m_wired;}else{echo $m_wan;}?></h2>
			<table cellpadding="1" cellspacing="1" border="0" width="525">
			<tr>
				<td class="r_tb" width="198"><?=$m_connection_type?>&nbsp;:</td>
				<td class="l_tb" width=320>&nbsp;<?=$msg_wanmode?></td>
			</tr>
			<tr>
				<td class="r_tb" width="198"><?=$m_cable_status?>&nbsp;:</td>
				<td class="l_tb" width=320>&nbsp;<?=$msg_cable_link_type?></td>
			</tr>
			<tr>
				<td class="r_tb" width="198"><?=$m_network_status?>&nbsp;:</td>
				<td class="l_tb" width=320>&nbsp;<input class="l_tb" type="text" readonly id="connstate" value="<?=$msg_wanstatus?>" style="border-width:0;">
				</td>
			</tr>
			<tr>
				<td class="r_tb"><?=$m_connection_time?>&nbsp;:</td>
				<td class="l_tb">&nbsp;<span id="WANTimer_session"></span></td>
			</tr>
<?
if ($AUTH_GROUP=="0" && $msg_connect!="" && $router=="1")
{
	echo "\t\t\t<tr><td class='r_tb'>&nbsp;</td><td class='l_tb'>";
	echo "\t\t\t\t\t<input type=button onclick=do_connect(); name=bt_connect id=bt_connect value=\"".$msg_connect."\">&nbsp;\n";
	echo "\t\t\t\t\t<input type=button onclick=do_disconnect(); name=bt_disconnect id=bt_disconnect value=\"".$msg_disconnect."\">\n";
	echo "\t\t\t</td></tr>";
}
?>
			<tr>
				<td class="r_tb" width="198"><?=$m_macaddr?>&nbsp;:</td>
				<td class="l_tb" width=320>&nbsp;<?
				if($router!="1") {echo query("/runtime/sys/info/lanmac");}
				else {echo query("/runtime/wan/inf:1/mac");}?>
				</td>
			</tr>
			<tr>
				<td class="r_tb"><?=$m_ipaddr?>&nbsp;:</td>
				<td class="l_tb"><div id="wanipaddr">&nbsp;<?=$wanipaddr?></div></td>
			</tr>
			<tr>
				<td class="r_tb"><?=$m_netmask?>&nbsp;:</td>
				<td class="l_tb"><div id="wansubnet">&nbsp;<?=$wansubnet?></div></td>
			</tr>
			<tr>
				<td class="r_tb"><?=$m_default_gw?>&nbsp;:</td>
				<td class="l_tb"><div id="wangateway">&nbsp;<?=$wangateway?></div></td>
			</tr>
			<tr>
				<td class="r_tb"><?=$m_dns?>&nbsp;:</td>
				<td class="l_tb"><div id="wandns">&nbsp;<?=$wandns?></div></td>
			</tr>
			</table>
		</div>
		<div class="box" id="show_lan">
			<h2><?=$m_lan?></h2>
			<table cellpadding="1" cellspacing="1" border="0" width="525">
			<tr>
				<td class="r_tb" width="200"><?=$m_macaddr?>&nbsp;:</td>
				<td class="l_tb">&nbsp;<?query("/runtime/sys/info/lanmac");?></td>
			</tr>
			<tr>
				<td class="r_tb"><?=$m_ipaddr?>&nbsp;:</td>
				<td class="l_tb">&nbsp;<?query("/lan/ethernet/ip");?></td>
			</tr>
			<tr>
				<td class="r_tb"><?=$m_netmask?>&nbsp;:</td>
				<td class="l_tb">&nbsp;<?query("/lan/ethernet/netmask");?></td>
			</tr>
			<tr>
				<td class="r_tb"><?=$m_dhcp_server?>&nbsp;:</td>
				<td class="l_tb">&nbsp;<?=$dhcp_en?></td>
			</tr>
			</table>
		</div>
		<div class="box">
			<h2><?=$m_wlan_title?></h2>
			<table cellpadding="1" cellspacing="1" border="0" width="525">
			<tr>
				<td class="r_tb" width="200"><?=$m_wlan_radio?>&nbsp;:</td>
				<td class="l_tb">&nbsp;<?
				if(query("/wireless/enable")=="0")	{echo $m_disable;}
				else								{echo $m_enable;}
				?>
				</td>
			</tr>
			<tr>
				<td class="r_tb" width="200"><?=$m_macaddr?>&nbsp;:</td>
				<td class="l_tb">&nbsp;<?query("/runtime/layout/wlanmac");?></td>
			</tr>
			<tr>
				<td class="r_tb" width="200"><?=$m_wlan_band?>&nbsp;:</td>
				<td class="l_tb">&nbsp;<?=$msg_wlanmode?></td>
			</tr>
			<tr>
				<td class="r_tb" width="200"><?=$m_ssid?>&nbsp;:</td>
				<td class="l_tb">&nbsp;<?=$ssid?></td>
			</tr>
			<tr>
				<td class="r_tb"><?=$m_channel?>&nbsp;:</td>
				<td class="l_tb">&nbsp;<?=$channel?></td>
			</tr>
			<tr>
				<td class="r_tb"><?=$m_privacy?>&nbsp;:</td>
				<td class="l_tb"><?=$str_sec?></td>
			</tr>
			</table>
		</div>
		<div class="box">
			<h2><?=$m_lan_computer?></h2>
			<table borderColor=#ffffff cellSpacing=1 cellPadding=2 width=525 bgColor=#dfdfdf border=1>
			<tr>
				<td class="l_tb"><?=$m_ip_addr?></td>
				<td class="l_tb"><?=$m_lan_name?></td>
				<td class="l_tb"><?=$m_mac?></td>
			</tr>
<?
for ("/runtime/dhcpserver/lease")
{
echo
"			<tr>\n".
"				<td class=\"l_tb\">".query("ip")."</td>\n".
"				<td class=\"l_tb\">".get(h,"hostname")."</td>\n".
"				<td class=\"l_tb\">".query("mac")."</td>\n".
"			</tr>\n";
}
?>
			</table>
		</div>
		<div class="box">
			<h2><?=$m_igmp_title?></h2>
			<table borderColor=#ffffff cellSpacing=1 cellPadding=2 width=525 bgColor=#dfdfdf border=1>
			<tr>
				<td class="l_tb"><?=$m_group_ip?></td>
				<td class="l_tb"><?=$m_member_ip?></td>
			</tr>
<?
for ("/runtime/igmpproxy/group")
{
	$g_addr=query("ipaddr");
	for ("/runtime/igmpproxy/group:".$@."/member")
	{
echo
"			<tr>\n".
"				<td class=\"l_tb\" width=\"50%\">".$g_addr."</td>\n".
"				<td class=\"l_tb\">".query("ipaddr")."</td>\n".
"			</tr>\n";
	}
}
?>
			</table>
		</div>		
		<div class="box">
			<h2><?=$m_upnp_title?></h2>
			<table borderColor=#ffffff cellSpacing=1 cellPadding=2 width=525 bgColor=#dfdfdf border=1>
			<tr>
				<td class="l_tb"><?=$m_upnp_name?></td>
				<td class="l_tb"><?=$m_upnp_ip?></td>
				<td class="l_tb"><?=$m_upnp_port1?></td>
				<td class="l_tb"><?=$m_upnp_port2?></td>
				<td class="l_tb"><?=$m_upnp_protocol?></td>
			</tr>
<?
for ("/runtime/upnp/wan:1/entry")
{
	$upnp_protocol=query("protocol");
	if($upnp_protocol==1)	{$upnp_promsg="TCP";}
	else					{$upnp_promsg="UDP";}
echo
"		<tr>\n".
"			<td class=\"l_tb\">".query("description")."</td>\n".
"			<td class=\"l_tb\">".query("ip")."</td>\n".
"			<td class=\"l_tb\">".query("port1")."</td>\n".
"			<td class=\"l_tb\">".query("port2")."</td>\n".
"			<td class=\"l_tb\">".$upnp_promsg."</td>\n".
"		</tr>\n";
}
?>
			</table>
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
