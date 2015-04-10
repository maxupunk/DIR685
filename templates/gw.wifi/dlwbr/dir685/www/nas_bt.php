<?
/* vi: set sw=4 ts=4: ---------------------------------------------------------*/
$MY_NAME		="nas_bt";
$MY_MSG_FILE	=$MY_NAME.".php";
$CATEGORY		="nas";
/* --------------------------------------------------------------------------- */
if ($ACTION_POST!="")
{
	require("/www/model/__admin_check.php");

	$dirty=0;
	anchor("/nas/bt");
	if (query("enable")	!=$BT_ENABLE)	{set("enable",	$BT_ENABLE);$dirty++;}
	if (query("path_header")	!=$BT_PATH_HEADER)		{set("path_header", 	$BT_PATH_HEADER);	$dirty++;}
	if (query("path")	!=$BT_PATH)		{set("path", 	$BT_PATH);	$dirty++;}
	if($dirty>0 && $BT_ENABLE=="1")		{$SUBMIT_STR=";submit BT_START";}
	elseif($dirty>0 && $BT_ENABLE=="0")	{$SUBMIT_STR=";submit BT_STOP";}
	
	$NEXT_PAGE=$MY_NAME;
	if($SUBMIT_STR!="")	{require($G_SAVING_URL);}
	else				{require($G_NO_CHANGED_URL);}
}

/* --------------------------------------------------------------------------- */
require("/www/model/__html_head.php");
/* --------------------------------------------------------------------------- */
// get the variable value from rgdb.
require("/www/portal/comm/drag.php");
require("/www/portal/comm/overlay.php");
require("/www/portal/comm/event.php");
require("/www/portal/comm/scoot.php");
require("/www/portal/comm/fade.php");

$cfg_bt_enable=query("/nas/bt/enable");
$devname = query("/runtime/nas/store_dev/devname");
$bt_path_header = query("/nas/bt/path_header");
$bt_path_body = query("/nas/bt/path");
$dev_mount_name = query("/runtime/nas/store_dev/mount");
/* --------------------------------------------------------------------------- */
?>

<script>
function init()
{
	var frm=get_obj("frm");

	frm.f_dir.value="<?=$bt_path_header?>"+"<?=$bt_path_body?>";
	
	if("<?=$cfg_bt_enable?>"=="1")
	{
		frm.bt_enb.checked=true;
		
		var f=get_obj("bt_frame");
		if("<?=$devname?>"=="")
		{
			get_obj("div_nodisk").style.display="";
		}
		else if("<?=$bt_path_header?>"!="<?=$dev_mount_name?>" && "<?=$bt_path_header?>"!="")
		{
			get_obj("div_chgdisk").style.display="";
		}
		else
		{
			f.className="box";
			var frameDiv = document.createElement('iframe');
			frameDiv.name="bt_iframe";
			frameDiv.vspace=0;
			frameDiv.hspace=0;
			frameDiv.width=670;
			frameDiv.height=650;
			//frameDiv.frameborder=0;
			frameDiv.setAttribute("frameborder","0");
			frameDiv.scrolling="yes";
			frameDiv.src="nas_bt_index.php";
			f.appendChild(frameDiv);
		}
	}
	
	/* initialization for explorer.php */
	initOverlay("white");
	
	check_enable_bt();
}

function do_cancel()
{
	self.location.href="<?=$MY_NAME?>.php?random_str="+generate_random_str();
}

function check()
{
	var f=get_obj("frm");
	if(f.bt_enb.checked)
	{
		f.BT_ENABLE.value=1;
		if(is_blank(f.f_dir.value))
		{
			alert("<?=$a_invalid_path?>");
			field_focus(f.f_dir, "**");
			return false; 
		}
	}
	
	var dir_array=f.f_dir.value.split("/");
	var dir_array_size=dir_array.length;
	if(dir_array_size>1)
	{
		f.BT_PATH_HEADER.value=f.f_dir.value.substring(0,f.f_dir.value.search("/"));
		f.BT_PATH.value=f.f_dir.value.substring(f.f_dir.value.search("/"),f.f_dir.value.length);
	}
	else
	{
		f.BT_PATH_HEADER.value=f.f_dir.value;
	}
	return true;
}

function open_browser()
{
	/* call explorer.php */
	window_make_new(-1, -1, 500, 400, "/portal/explorer.php?path=/&page=bt","Explorer");
}

function check_enable_bt()
{
	var f=get_obj("frm");
	if(f.bt_enb.checked)
	{
		f.f_dir.disabled=false;
		f.btn_path.disabled=false;
	}
	else
	{
		f.f_dir.disabled=true;
		f.btn_path.disabled=true;
	}
}
</script>


<body onload="init();" <?=$G_BODY_ATTR?>>
<form name="frm" id="frm" method="post" action="<?=$MY_NAME?>.php" onsubmit="return check();";>
<input type="hidden" name="ACTION_POST"		value="1">
<input type="hidden" name="BT_ENABLE"		value="0">
<input type="hidden" name="BT_PATH_HEADER"		value="">
<input type="hidden" name="BT_PATH"		value="">

<!-- css for calling explorer.php -->
<link rel="stylesheet" href="/portal/comm/smbb.css" type="text/css"> 

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
		?>
		</div>
<!-- ________________________________ Main Content Start ______________________________ -->
		<div class="box">
			<h2><?=$m_setting_title?></h2>
<?
$td_width0="width=\"180\" align=\"right\"";
$td_width1="width=\"50\" align=\"center\"";
$td_width2="width=\"350\"";
?>
			<table border=0>
			<tr>
				<td <?=$td_width0?>><?=$m_enable_bt?>&nbsp;:</td>
				<td <?=$td_width2?> colspan=2>&nbsp;<input type="checkbox" name="bt_enb" id="bt_enb" value="1" onclick="check_enable_bt();"></td>
			</tr>
			<tr>
				<td <?=$td_width0?>><?=$m_bt_path?>&nbsp;:</td>
				<td <?=$td_width2?>>&nbsp;<input type="text" name="f_dir" id="f_dir" size=50 onclick="open_browser();">
					<input type="button" name="btn_path" id="btn_path" value="<?=$m_select_path?>" onclick="open_browser();">
				</td>
			</tr>
			<tr>
				<td <?=$td_width0?>>&nbsp;</td>
				<td <?=$td_width2?>>&nbsp;<input type="submit" name="bt_btn" id=bt_btn value="<?=$m_save_settings?>"></td>
			</tr>
			</table>
		</div>
		<div id="bt_frame">
			<!--<iframe vspace="0" name="FRAME1" src="bt_ui/fe01.html" width="670" height="650" frameborder="0" scrolling="yes"></iframe>-->
		</div>
		<div class="box" id="div_nodisk" style="display:none">
			<h2><?=$m_bt_frame_title?></h2><br>
			<div class=bc_tb>
				<font color="red"><?=$a_nodisk?></font>
			</div>
		</div>
		<div class="box" id="div_chgdisk" style="display:none">
			<h2><?=$m_bt_frame_title?></h2><br>
			<div class=bc_tb>
				<font color="red"><?=$a_chgdisk?></font>
			</div>
		</div>
<!-- ________________________________  Main Content End _______________________________ -->
	</td>
 	<!-- <td <?=$G_HELP_TABLE_ATTR?>><?require($LOCALE_PATH."/help/h_".$MY_NAME.".php");?></td> -->
</tr>
</table>
<?require("/www/model/__tailer.php");?>
</form>
</body>
</html>
