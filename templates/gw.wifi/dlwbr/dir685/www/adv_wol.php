<?
/* vi: set sw=4 ts=4: ---------------------------------------------------------*/
$MY_NAME		="adv_wol";
$MY_MSG_FILE	=$MY_NAME.".php";
$CATEGORY		="adv";
/* --------------------------------------------------------------------------- */
$router=query("/runtime/router/enable");
if ($ACTION_POST!="" && $router=="1")
{
	require("/www/model/__admin_check.php");

	echo "<!--\n";
	echo "enable_wol = ".$enable_wol."\n";
	echo "udp_port = ".$udp_port."\n";
//	echo "tcp_port = ".$tcp_port."\n";
//	echo "option_inf = ".$option_inf."\n";

	$dirty = 0;
	if($enable_wol		!= query("/wol/enable"))	{ $dirty++; set("/wol/enable", $enable_wol); }
	if($udp_port		!= query("/wol/udp/port"))	{ $dirty++; set("/wol/udp/port", $udp_port); }
//	if($tcp_port		!= query("/wol/tcp/port"))	{ $dirty++; set("/wol/tcp/port", $tcp_port); }

//	if($option_inf		!= query("/wol/interface"))	{ $dirty++; set("/wol/interface", $option_inf); }		
//	$option_inf = query("/wol/interface");
//	if($option_inf=="")
//	{
//		$option_inf="br0"; //LAN:br0- default interface
//		set("/wol/interface", $option_inf);
//	}
		
	/* Check dirty */
	echo "dirty = ".$dirty."\n";
	$SUBMIT_STR="";
	if ($dirty > 0)			{$SUBMIT_STR="submit WOL";}
	
	echo "-->\n";

	$NEXT_PAGE=$MY_NAME;
	if($SUBMIT_STR!="")	{require($G_SAVING_URL);}
	else				{require($G_NO_CHANGED_URL);}
}

/* --------------------------------------------------------------------------- */
require("/www/model/__html_head.php");
require("/www/comm/__js_ip.php");
/* --------------------------------------------------------------------------- */
// get the variable value from rgdb.
$cfg_wol_enable		= query("/wol/enable");
$cfg_udp_port		= query("/wol/udp/port");
//$cfg_tcp_port		= query("/wol/tcp/port");
//$cfg_interface		= query("/wol/interface");
/* --------------------------------------------------------------------------- */
?>

<script>
/* page init functoin */
function init()
{
	var f=get_obj("frm");

	// init here ...
	f.enable_wol.checked = <? if ($cfg_wol_enable == "1") {echo "true";} else {echo "false";} ?>;
	f.udp_port.value = "<?=$cfg_udp_port?>";
	
	//f.tcp_port.value = "<?=$cfg_tcp_port?>";
	//select_index(f.option_inf, "<?=$cfg_interface?>");
	show_input_port();
}
/* parameter checking */
function check()
{
	var f=get_obj("frm");
	if(f.enable_wol.checked)
	{
		if (is_blank(f.udp_port.value))
		{
			alert('<?=$a_cant_blank?>');
			field_focus(f.udp_port, "**");
			return false;
		}	
/*
		if (is_blank(f.udp_port.value) && is_blank(f.tcp_port.value))
		{
			alert('<?=$a_cant_both_blank?>');
			field_focus(get_obj("udp_port"), "**");
			return false;
		}	
*/
		if (!is_valid_port_str(f.udp_port.value))
		{
			alert('<?=$a_invalid_udp_port?>');
			field_focus(f.udp_port, "**");
			return false;
		}	

/*		if (!is_valid_port_str(f.tcp_port.value))
		{
			alert('<?=$a_invalid_tcp_port?>');
			field_focus(get_obj("tcp_port"), "**");
			return false;
		}	*/

	}
	f.udp_port.disabled=false;
	//f.tcp_port.disabled=false;
	return true;
}
/* cancel function */
function do_cancel()
{
	self.location.href="<?=$MY_NAME?>.php?random_str="+generate_random_str();
}

function show_input_port()
{
	var f=get_obj("frm");
	if(f.enable_wol.checked)
	{
		f.udp_port.disabled=false;
		//f.tcp_port.disabled=false;
	}
	else
	{
		f.udp_port.disabled=true;
		//f.tcp_port.disabled=true;
	}
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
		<?
		require($LOCALE_PATH."/dsc/dsc_".$MY_NAME.".php");
		echo $G_APPLY_CANEL_BUTTON;
		?>
		</div>
<!-- ________________________________ Main Content Start ______________________________ -->
		<div class="box">
			<h2><?=$m_title_wol?></h2>
			<table cellSpacing=1 cellPadding=1 width=525 border=0>			
			<tr>
				<td class="r_tb" width=160><?=$m_enable_wol?>&nbsp;:&nbsp;</td>
				<td class="l_tb">&nbsp;
					<input type="checkbox" name="enable_wol" value=1 onclick="show_input_port();">
				</td>
			</tr>
			<tr>	
				<td class="r_tb"><?=$m_udp_port?>&nbsp;:&nbsp;</td>
				<td class="l_tb">&nbsp;
					<input type="text" name="udp_port" id="udp_port" maxlength="5">
				</td>
			</tr>				
			<!--
			<tr>	
				<td class="r_tb"><?=$m_tcp_port?>&nbsp;:&nbsp;</td>
				<td class="l_tb">&nbsp;
					<input type="text" name="tcp_port" id="tcp_port" maxlength="5">
				</td>
			</tr>	
			
			<tr>
				<td class="r_tb" width=160><?=$m_option_inf_title?>&nbsp;:&nbsp;</td>
				<td class="l_tb">&nbsp;
					<select name="option_inf" id="option_inf">
						<option value="br0"><?=$m_option_inf_lan?></option>
					</select>
				</td>
			</tr>
			-->
			
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
