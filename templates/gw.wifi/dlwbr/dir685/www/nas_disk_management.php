<?
/* vi: set sw=4 ts=4: ---------------------------------------------------------*/
$MY_NAME		="nas_disk_management";
$MY_MSG_FILE	=$MY_NAME.".php";
$CATEGORY		="nas";
/* --------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------- */
require("/www/model/__html_head.php");
require("/www/portal/comm/drag.php");
require("/www/portal/comm/overlay.php");
require("/www/portal/comm/event.php");
require("/www/portal/comm/scoot.php");
require("/www/portal/comm/fade.php");

//+++jana
if ($ACTION_POST!="")
{
	require("/www/model/__admin_check.php");
	$hd_dirty = 0;
	$SUBMIT_STR = "";

	echo "<!--\n";
	
	echo "hd_sleep_timeout = ".$hd_sleep_timeout."\n";
		
	if (query("/nas/store_dev/sleep_time")!=$hd_sleep_timeout)	
	{
		$dirty++; 
		set("/nas/store_dev/sleep_time", $hd_sleep_timeout);
		if(query("/runtime/nas/store_dev/devname")!="")	{$hd_dirty++;}
	}
	
	echo "-->\n";

	if ($hd_dirty > 0)		
	{	
		$SUBMIT_STR="submit HD_RESTART_SLEEPTIME;";
	}
	/* hendry modify : submit only when changes is made */
	if($dirty > 0)
	{
	$SUBMIT_STR=$SUBMIT_STR."submit LCD_SET_TIMEOUT;";
	}
	
	$NEXT_PAGE = $MY_NAME;
	if ($SUBMIT_STR!="")	{require($G_SAVING_URL);}
	else					{require($G_NO_CHANGED_URL);}
}
//---jana

if($AUTH_GROUP!="0")
{
	require("/www/permission_deny.php");
	exit;
}
else
{
	$disk_path="/tmp/disk_status";
	$prev_time = query($disk_path);
	$curr_time = query("/runtime/sys/uptime");

	$delta_time = $curr_time - $prev_time;
	if ($delta_time > 15)
	{
		set($disk_path, $curr_time);
		$disk_do_xgi=1;
	}
	else
	{
		$disk_do_xgi=0;
	}
}

$hd_time	= query("/nas/store_dev/sleep_time"); //jana added
if($hd_time=="")
{
	$hd_time=0;
}
/* --------------------------------------------------------------------------- */
?>

<script>

function format_status(flag)
{
	if(flag=="start")
	{
		get_obj("format").disabled=true;
		get_obj("format_status").innerHTML="<?=$m_format_status?>&nbsp;:&nbsp;<font color=red><?=$a_format_wait?></font>";
	}
	else	//(flag=="end")
	{
		get_obj("format").disabled=false;
		get_obj("format_status").innerHTML="<?=$m_format_status?>&nbsp;:&nbsp;<font color=red><?=$a_format_success?></font>";
	}
}

function start_format()
{
	if (confirm("<?=$a_format_confirm?>")==true)
	{
		format_status('start');
		window_make_new(-1, -1, 450, 200, "/portal/__nas_format.php","Information");
	}
}

//+++jana
//function click_checkbox(obj,input_name)
//{
//	var f = get_obj("frm");
//	
//	if(obj.checked)
//		eval("f."+input_name+".disabled=false");
//	else
//		eval("f."+input_name+".disabled=true");
//}

//function init_checkbox(stime,checkbox_obj,input_obj)
//{
//	if(stime == 0)	//0 is NEVER_Timeout
//	{
//		checkbox_obj.checked=false;
//		input_obj.disabled=true;
//	}
//	else
//	{
//		checkbox_obj.checked=true;
//		input_obj.disabled=false;
//	}
//	input_obj.value=stime/60;	//minute
//}

function check()
{
//	var f = get_obj("frm");
//	if(f.hd_sleep_enable.checked)
//	{
//		if (is_blank(get_obj("in_hd_timeout").value))
//		{
//			alert("<?=$a_empty_timeout?>");
//			field_focus(get_obj("in_hd_timeout"), "**");
//			return false;
//		} 
//		if(parseInt(f.in_hd_timeout.value,10)>=15 || parseInt(f.in_hd_timeout.value,10)<1)
//		{
//			alert("<?=$a_time_range_error?>");
//			field_focus(f.in_hd_timeout, "**");
//			return false;
//		}
//		f.hd_sleep_timeout.value=parseInt(f.in_hd_timeout.value,10)*60;
//	}
//	else
//	{
//		f.hd_sleep_timeout.value=0;
//		f.in_hd_timeout.disabled=true;
//	}
//	
//	f.in_hd_timeout.disabled=true;
	return true;
}

function do_cancel()
{
	self.location.href="<?=$MY_NAME?>.php?random_str="+generate_random_str();
}
//---jana

/* page init functoin */
function init()
{
	var f = get_obj("frm");//jana added
	
	select_index(f.hd_sleep_timeout,"<? map("/nas/store_dev/sleep_time", "","900"); ?>");		
//	init_checkbox(<?=$hd_time?>,f.hd_sleep_enable,f.in_hd_timeout);//jana added

	/* initialization for explorer.php */
	initOverlay("white");
<?
$dummy = fread("/var/format_pgrs");
$devname = query("/runtime/nas/store_dev/devname");
if($devname=="" || $dummy!="")
{
	echo "	get_obj('nodisk').style.display='';\n";
	echo "  get_obj('format').disabled=true;\n";
	if($dummy!="")	{echo "format_status('start');\n";}
}
else
{
	if ($disk_do_xgi == "1")
	{
		echo "	get_obj('refreshing').style.display='';\n";
		echo "	self.location.href='".$MY_NAME.".xgi?set/runtime/diskinfo/status=1';\n";
	}
	else
	{
		echo "	get_obj('disk_info_main').style.display='';\n";
	}
	if($dummy!="")
	{
		echo "format_status('start');\n";
	}
}
?>
}

</script>
<!-- css for calling explorer.php -->
<link rel="stylesheet" href="/portal/comm/smbb.css" type="text/css"> 

<body onLoad="init();" <?=$G_BODY_ATTR?>>
<form name="frm" id="frm" method="post" action="<?=$MY_NAME?>.php" onSubmit="return check();";>
<input type="hidden" name="ACTION_POST"	value="1">  

<!-- <input type="hidden" name="hd_sleep_timeout" value="0"> <!-- jana added-->

<?require("/www/model/__banner.php");?>
<?require("/www/model/__menu_top.php");?>
<table <?=$G_MAIN_TABLE_ATTR?> height="100%">
<tr valign=top>
	<td <?=$G_MENU_TABLE_ATTR?>>
	<?require("/www/model/__menu_left.php");?>
	</td>
	<td id="maincontent">
		<div id="box_header">

		<?require($LOCALE_PATH."/dsc/dsc_".$MY_NAME.".php");?>
		<br /><!-- jana added -->
		<? echo $G_APPLY_CANEL_BUTTON; ?><!-- jana added -->
	
		</div>
<!-- ________________________________ Main Content Start ______________________________ -->
		<div class="box" id="refreshing" style="display:none">
			<h2><?=$m_disk_mngmnt_title?></h2><br>
			<div class=bc_tb>
				<font color="blue"><?=$m_refreshing?></font>
			</div>
			<p />
		</div>
		<div class="box" id="nodisk" style="display:none">
			<h2><?=$m_disk_mngmnt_title?></h2><br>
			<div class=bc_tb>
				<font color="red">
				<?
					if($dummy!="")	{echo $a_formatting;}
					else			{echo $a_nodisk;}
				?></font>
			</div>
			<p />
		</div>
		<div class="box" id="disk_info_main" style="display:none">
			<h2><?=$m_disk_mngmnt_title?></h2>
			<table cellSpacing=1 cellPadding=2 width=525 border=0>
		        <tr>
                  <td class=r_tb width=40%><?=$m_disk_name?>&nbsp;:</td>
                  <td class=l_tb><?query("/runtime/nas/store_dev/name");?></td>
				</tr>
		        <tr>
                  <td class=r_tb><?=$m_disk_format?>&nbsp;:</td>
                  <td class=l_tb><?query("/runtime/nas/store_dev/fsname");?></td>
				</tr>
		        <tr>
                  <td class=r_tb><?=$m_disk_capacity?>&nbsp;:</td>
                  <td class=l_tb><?query("/runtime/nas/store_dev/capacity");?></td>
				</tr>
		        <tr>
                  <td class=r_tb><?=$m_disk_used?>&nbsp;:</td>
                  <td class=l_tb><?query("/runtime/nas/store_dev/used");?></td>
				</tr>
		        <tr>
                  <td class=r_tb><?=$m_disk_available?>&nbsp;:</td>
                  <td class=l_tb><?query("/runtime/nas/store_dev/available");?></td>
				</tr>
		        <tr>
                  <td class=r_tb><?=$m_disk_health?>&nbsp;:</td>
                  <td class=l_tb><?query("/runtime/nas/store_dev/health");?></td>
				</tr>
		        <tr>
                  <td class=r_tb><?=$m_disk_temp?>&nbsp;:</td>
                  <td class=l_tb><?query("/runtime/nas/store_dev/temp/celsius");?><sup>o</sup>C&nbsp;/
                  	<?query("/runtime/nas/store_dev/temp/fahrenheit");?><sup>o</sup>F</td>
				</tr>
		    </table>
		</div>
		<div class="box">
			<h2><?=$m_format_title?></h2>
			<?=$m_format_dsc?><p>
			<center><input type=button name="format" id="format" value="<?=$m_format?>" onclick="start_format();"></center><p />
			<div id="format_status" style="text-align:center;font-weight: bold;"></div>
		</div>
		<!-- +++jana 	-->
		<div class="box">
			<h2><?=$m_title_hd?></h2>
			<?=$m_hd_dsc?>
			<table width=525 border=0>
			<!--
				<tr>
					<td class="r_tb" width=160><?=$m_enable?>&nbsp;:&nbsp;</td>
					<td class="l_tb">
						<input type="checkbox" name="hd_sleep_enable" id="hd_sleep_enable" onclick="click_checkbox(this,'in_hd_timeout');">
					</td>
				</tr>
			-->
				<tr>
					<td class="r_tb" width=160><?=$m_timeout?>&nbsp;:&nbsp;</td>
					<td class="l_tb">
					<!-- 5, 10, 15, 30, 60, 90, 120 min -->
					<select name="hd_sleep_timeout" id="hd_sleep_timeout">
						<option value=300>5</option>
						<option value=600>10</option>
						<option value=900>15</option>
						<option value=1800>30</option>
						<option value=3600>60</option>
						<option value=5400>90</option>						
						<option value=7200>120</option>						
						<option value=0><?=$m_timeout_never?></option>	
					</select>
			<!--	
						<input type="text" name="in_hd_timeout" id="in_hd_timeout" size=10 maxlength=2>&nbsp;
			-->							
						<?=$m_minute?> 
			
					</td>
				</tr>
			</table>
		</div>
		<div id="box_bottom">
		<? echo $G_APPLY_CANEL_BUTTON; ?>
		</div>
		<!-- ---jana 	-->
<!-- ________________________________  Main Content End _______________________________ -->
	</td>
	<td <?=$G_HELP_TABLE_ATTR?>><?require($LOCALE_PATH."/help/h_".$MY_NAME.".php");?></td>
</tr>
</table>
<?require("/www/model/__tailer.php");?>
</form>
</body>
</html>
