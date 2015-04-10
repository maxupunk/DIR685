<?
/* vi: set sw=4 ts=4: ---------------------------------------------------------*/
$MY_NAME		="nas_upnp";
$MY_MSG_FILE	=$MY_NAME.".php";
$CATEGORY		="nas";
/* --------------------------------------------------------------------------- */

/*
if($ACTION_REFRESH != "")
{
	require("/www/model/__admin_check.php");
	echo "<script>alert(\"Do refresh\")</script>";
	$NEXT_PAGE=$MY_NAME;
	$ONLY_DO_SUBMIT_STR="submit UPNP_AV_REFRESH;"; 
	if($ONLY_DO_SUBMIT_STR!="")	{require($G_SAVING_URL);}
	else				{require($G_NO_CHANGED_URL);}
}
*/

if ($ACTION_POST!="")
{
	require("/www/model/__admin_check.php");
	/*echo "<script>alert(\"Saved success\")</script>";*/
	if($f_root=="ON") {$f_dir = "";}
	
	anchor("/nas/upnp");
	set("path", $f_dir);
	set("enable", $f_UPNPAVServ);	
	set("rescan", $f_autorefresh);
	if($f_UPNPAVServ==1)//enable
	{
		$NEXT_PAGE=$MY_NAME;
		$SUBMIT_STR=";submit UPNP_AV_START";
		if($SUBMIT_STR!="")	{require($G_SAVING_URL);}
		else				{require($G_NO_CHANGED_URL);}
	}
	else
	{
		$NEXT_PAGE=$MY_NAME;
		$SUBMIT_STR=";submit UPNP_AV_STOP";
		if($SUBMIT_STR!="")	{require($G_SAVING_URL);}
		else				{require($G_NO_CHANGED_URL);}
	}
}

anchor("/nas/upnp");
$upnp_enable = query("enable");
if($upnp_enable == ""){ $upnp_enable = 0; }	/* if db hasn't set, just disable */
$upnp_autorefresh = query("rescan");
/*default value*/
if($upnp_autorefresh=="") {$upnp_autorefresh = "0"; set("rescan","0");}	

$upnp_path = query("path");
if($upnp_path==""){$upnp_path="/";}

$scan_media = query("/runtime/scan_media/enable");

/* --------------------------------------------------------------------------- */
require("/www/model/__html_head.php");
require("/www/portal/comm/drag.php");
require("/www/portal/comm/overlay.php");
require("/www/portal/comm/event.php");
require("/www/portal/comm/scoot.php");
require("/www/portal/comm/fade.php");
/* --------------------------------------------------------------------------- */
?>

<script>

/* page init functoin */
function init()
{
	var f=get_obj("form1");
	<? 
	/* +++ Teresa, script upnp check the device already.
	$devname = query("/runtime/nas/store_dev/devname");
	if ($devname=="") { echo "fields_disabled(f, true);\n\treturn;\n"; } 
	*/
	?>
	
	/* initialization for explorer.php */
	initOverlay("white");
	
	/* enable/disable initialization */
	if(<?=$upnp_enable?> == "1")
	{
		document.form1.f_UPNPAVServ[0].checked = true;	
		disable_item(1);
	}else
	{
		document.form1.f_UPNPAVServ[1].checked = true;
		disable_item(0);
	}
	
	/* check if it is root initialization */
	if("<?=$upnp_path?>" == "/")
	{
		f.f_root.checked = true;	
		f.f_dir.value ="/";
	}else
	{
		f.f_root.checked = false;
		f.f_dir.value = "<?=$upnp_path?>";
	}
	check_path(1);
	if("<?=$scan_media?>" == "1")
	{
		window_make_new(-1, -1, 500, 110, "refresh.php?path=/","Now Scanning");
	}
	
	/* auto refresh initialization */
/*	select_index(document.form1.f_autorefresh, "<?=$upnp_autorefresh?>");*/
}

function check()
{
	var f=get_obj("form1");
	
	/* if upnp enabled, must fill the upnp path */
	if(f.f_UPNPAVServ[0].checked == true)
	{
		if(f.f_dir.value == "" && f.f_root.checked == false)
		{
			alert("<?=$a_not_select_folder?>");
			//alert("A folder must be selected.");
			return false;
		}
		else
			return true;
	}
}

function do_cancel()
{
	self.location.href="<?=$MY_NAME?>.php?random_str="+generate_random_str();
}
/*
function select_index(obj, val)
{
	var i=0;
	for(i=0; i<obj.length;i++)
	{
		if(eval("obj["+i+"].value")==val)
		{
			obj.selectedIndex=i;
			break;
		}
	}
}
*/

function disable_item(status)
{
	if(status==1)	//enable
	{
		document.form1.f_root.disabled=false;
		document.form1.f_dir.disabled=false;
		document.form1.But_Browse.disabled=false;
	}
	else
	{
		document.form1.f_root.disabled=true;
		document.form1.f_dir.disabled=false;
		document.form1.But_Browse.disabled=true;
	}
}

function open_browser()
{
	//alert(get_obj("sharing_dir").value);
	window_make_new(-1, -1, 500, 400, "/portal/explorer.php?path=/","Explorer");
	//enableOverlay();
}

function check_path(clear)
{
	if (document.form1.f_root.checked || clear!=1)
	{
		document.getElementById("chamber2").style.display = "none";
		document.form1.f_dir.value="/";
	}
	else
	{
		document.getElementById("chamber2").style.display = "";
	}
	
}

function refresh()
{
	/*
	//JUST do refresh
	document.form1.ACTION_POST.value = "";
	document.form1.ACTION_REFRESH.value = "something";
	document.form1.submit();
	*/
	
	var str="<?=$MY_NAME?>.xgi?set/runtime/set_scan_media_db/enable=1&random_num="+generate_random_str(); 

	if( "<?=$upnp_path?>"!=document.form1.f_dir.value)
	{
		//alert("The folder is changed. Please save setting before Refresh");
		alert("<?=$a_change_folder?>");
	}
	else
	{
<?
	$ONLY_DO_SUBMIT_STR="submit UPNP_AV_REFRESH;"; 
	echo "	str+=exe_str(\"".$ONLY_DO_SUBMIT_STR."\");\n";
?>
	self.location.href=str;
	}
	
}

</script>

<!-- css for calling explorer.php -->
<link rel="stylesheet" href="/portal/comm/smbb.css" type="text/css"> 


<body onLoad="init();" <?=$G_BODY_ATTR?>>
<form name="form1" id="form1" method="post" action="<?=$MY_NAME?>.php" onSubmit="return check();";>

<input type="hidden" name="ACTION_POST"	value="1">
<!--<input type="hidden" name="ACTION_REFRESH" value="">-->

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
		<input type="button" name="But_Refresh" value="Refresh" onclick="refresh();">
		</div>
<!-- ________________________________ Main Content Start ______________________________ -->
		<?$m_colon="&nbsp;:&nbsp;";?>
		<div class="box">
			<h2><?=$m_1st_upnp_title?></h2>
			<table border="0" cellpadding="0" cellspacing="0" style="border-collapse: collapse" bordercolor="#111111" id="AutoNumber1" height="74" width="500">
		        <tr>
                  <td width="31%" height="32"><?=$m_upnp_name?></td>
                  <td width="61%" height="32">
                  <input type="radio" value="1" onClick="disable_item(1)" name="f_UPNPAVServ" ><?=$m_upnp_enable?>
                  <input type="radio" value="0" onClick="disable_item(0)" name="f_UPNPAVServ" ><?=$m_upnp_disable?>
                  </td>
				</tr>
		        <tr>
                  <td height="32"><?=$m_folder?></td>
                  <td height="32">  
                  <input type="checkbox" name="f_root" value="ON" onClick="check_path(1)"><?=$m_root?>
                  </td>
				</tr>
		        <tr id="chamber2" style="display">
				  <td height="29">&nbsp;</td>
		          <td height="29">
	                <input type=text name="f_dir" id="f_dir" size=30 readonly>
	                <input type="button" name="But_Browse" value="Browse" onClick="open_browser();">
	                <input type="hidden" name="f_flow_value" size="20">
	
	                <input type="hidden" name="f_device_read_write" size="2">
	                <input type="hidden" name="f_read_write" size="2">
				  </td>
		        </tr>
		    </table>
		</div>
	</td>
	<td <?=$G_HELP_TABLE_ATTR?>><?require($LOCALE_PATH."/help/h_".$MY_NAME.".php");?></td>
</tr>
</table>
<?require("/www/model/__tailer.php");?>
</form>
</body>
</html>
