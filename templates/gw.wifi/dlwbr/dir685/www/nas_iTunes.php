<?
/* vi: set sw=4 ts=4: ---------------------------------------------------------*/
$MY_NAME		="nas_iTunes";
$MY_MSG_FILE	=$MY_NAME.".php";
$CATEGORY		="nas";
/* --------------------------------------------------------------------------- */

/*
if($ACTION_REFRESH != "")
{
	require("/www/model/__admin_check.php");
	echo "<script>alert(\"Do refresh\")</script>";
	$NEXT_PAGE=$MY_NAME;
	if($ONLY_DO_SUBMIT_STR!="")	{require($G_SAVING_URL);}
	else				{require($G_NO_CHANGED_URL);}
}
*/

if ($ACTION_POST!="")
{
	require("/www/model/__admin_check.php");
	if($f_root=="ON") {$f_dir = "";}
	
	anchor("/nas/iTunes");
	set("path", $f_dir);
  //set("password", $f_Passwd);//jana removed
	set("rescan", $f_autorefresh);
	set("enable", $iTurnServ);
	set("/runtime/itunes/db_path",$DB_DIR);
	if($iTurnServ=="1")//enable
	{
		$NEXT_PAGE=$MY_NAME;
		$SUBMIT_STR=";submit ITUNES_START";
		if($SUBMIT_STR!="")	{require($G_SAVING_URL);}
		else				{require($G_NO_CHANGED_URL);}
	}
	else
	{
		$NEXT_PAGE=$MY_NAME;
		$SUBMIT_STR=";submit ITUNES_STOP";
		if($SUBMIT_STR!="")	{require($G_SAVING_URL);}
		else				{require($G_NO_CHANGED_URL);}
	}

	/*echo "<script>alert(\"Saved success\")</script>";*/
}

anchor("/nas/iTunes");
$iTunes_enable = query("enable");
if($iTunes_enable == "") {$iTunes_enable = 0 ;}
$iTunes_autorefresh = query("rescan");
/*default value*/
if($iTunes_autorefresh=="") {$iTunes_autorefresh = "0"; set("rescan","0");}	

$iTunes_path = query("path");
if($iTunes_path==""){$iTunes_path="/";}

/* --------------------------------------------------------------------------- */
require("/www/model/__html_head.php");
require("/www/portal/comm/drag.php");
require("/www/portal/comm/overlay.php");
require("/www/portal/comm/event.php");
require("/www/portal/comm/scoot.php");
require("/www/portal/comm/fade.php");
/* --------------------------------------------------------------------------- */
// get the variable value from rgdb.

/* --------------------------------------------------------------------------- */
?>

<script>

/* page init function */
function init()
{
	var f=get_obj("form1");
	<? 
	/* +++ Teresa, script iTunes check the device already.
	$devname = query("/runtime/nas/store_dev/devname");
	if ($devname=="") { echo "fields_disabled(f, true);\n\treturn;\n"; } 
	*/
	?>
	
	/* initialization for explorer.php */
	initOverlay("white");
	
	/* enable/disable initialization */
	if(<?=$iTunes_enable?> == "1")
	{
		document.form1.iTurnServ[0].checked = true;	
		disable_item(1);
	}else
	{
		document.form1.iTurnServ[1].checked = true;
		disable_item(0);
	}
	
	/* check if it is root initialization */
	if("<?=$iTunes_path?>" == "/")
	{
		f.f_root.checked = true;
	}else
	{
		f.f_root.checked = false;
		f.f_dir.value = "<?=$iTunes_path?>";
	}
	check_path(1);

	
	/* auto refresh initialization */
	select_index(document.form1.f_autorefresh, "<?=$iTunes_autorefresh?>");

}

function do_cancel()
{
	self.location.href="<?=$MY_NAME?>.php?random_str="+generate_random_str();
}

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

function disable_item(status)
{
	if(status==1)	//enable
	{
		document.form1.f_root.disabled=false;
		document.form1.f_dir.disabled=false;
		document.form1.f_autorefresh.disabled=false;
		document.form1.But_Browse.disabled=false;
		//document.form1.f_Passwd.disabled=false;//jana removed
		
	}
	else
	{
		document.form1.f_root.disabled=true;
		document.form1.f_dir.disabled=false;
		document.form1.f_autorefresh.disabled=true;
		document.form1.But_Browse.disabled=true;
		//document.form1.f_Passwd.disabled=true;//jana removed
	}
}

function open_browser()
{
	window_make_new(-1, -1, 500, 400, "/portal/explorer.php?path=/","Explorer");
}

function check_path(clear)
{
	if (document.form1.f_root.checked || clear!=1 )
	{	
		document.getElementById("chamber2").style.display = "none";
	}
	else
	{
		document.getElementById("chamber2").style.display = "";
	}
}

function check()
{
	var f=get_obj("form1");
	//alert("Password " + f.f_Passwd.value );
	/*jana removed
	if(f.iTurnServ[0].checked == true)
	{
		if(f.f_Passwd.value == "")
		{
			alert("Password can't be blank ..");
			return false;
		}	
	}
	*/
	var index;
	index=f.f_dir.value.indexOf('/');
	//alert(index);
	if(index>0)
	{
		f.DB_DIR.value=f.DB_DIR.value.concat("/tmp/storage_dev/",f.f_dir.value.substring(0,index));
	}
	
	return true;
}

function refresh()
{
	//JUST do refresh
	//alert("refresh");
	/*
	document.form1.ACTION_POST.value = "";
	document.form1.ACTION_REFRESH.value = "something";
	document.form1.submit();
	*/

	var str="<?=$MY_NAME?>.xgi?random_num="+generate_random_str(); 
<?
	$ONLY_DO_SUBMIT_STR="submit ITUNES_REFRESH;"; 
	echo "	str+=exe_str(\"".$ONLY_DO_SUBMIT_STR."\");\n";
?>
	self.location.href=str;
}

</script>


<!-- css for calling explorer.php -->
<link rel="stylesheet" href="/portal/comm/smbb.css" type="text/css"> 

<body onload="init();" <?=$G_BODY_ATTR?>>
<form name="form1" id="form1" method="post" action="<?=$MY_NAME?>.php" onsubmit="return check();";>
<input type="hidden" name="DB_DIR">
<input type="hidden" name="ACTION_POST"		value="1">
<!--<input type="hidden" name="ACTION_REFRESH"	value="">-->

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
		<!--jana removed   <input type="button" name="But_Refresh" value="Refresh" onclick="refresh();">  -->
		</div>
<!-- ________________________________ Main Content Start ______________________________ -->
		<?$m_colon="&nbsp;:&nbsp;";?>
		<div class="box">
			<h2><?=$m_1st_iTunes_title?></h2>
			<table border="0" cellpadding="0" cellspacing="0" style="border-collapse: collapse" bordercolor="#111111" id="AutoNumber1" width="500" height="196">
	        <tr>
			<td width="31%" height="32"><?=$m_iTunes_name?></td>
			<td width="61%" height="32">
			<input type="radio" value="1" onclick="disable_item(1);" name="iTurnServ" ><?=$m_iTunes_enable?>
			<input type="radio" value="0" onclick="disable_item(0);" name="iTurnServ" ><?=$m_iTunes_disable?>                     
			</td>
			</tr>
	
	        <tr>
			<td width="31%" height="32"><?=$m_folder?></td>
			<td width="61%" height="32">
				<input type="checkbox" name="f_root" value="ON" onclick="check_path(1)"><?=$m_root?></td>
			
			</tr>
	        			
			<tr id="chamber2" style="display">                     
			<td width="31%" height="33"></td>	                     
			<td width="61%" height="33"> 
				<input type="text" name="f_dir" id="f_dir" size="30"  readonly >
				<input type="hidden" name="read_write" size="30"  value="" > 
				<input type="hidden" name="ntfs_flag" size="30">
				<input type="button" name="But_Browse" value="Browse" onclick="open_browser();" onkeyup="checkinput(this.form);">&nbsp;
				<input type="hidden" name="Is_Root" size="30"  value="1">
			</td>
			</tr>
			<!--
	        <tr>	
			<td width="31%" height="33"></td>
			<td id="itunes_path" width="61%" height="33" style='word-break: break-all'><?=$iTunes_path?></td>
			</tr>
	        -->
	        <!-- jana removed
	        <tr>
			 <td width="31%" height="33">Password</td> 
			<td width="61%" height="33">
				<input type="password" name="f_Passwd" id="f_Passwd" size="17" maxLength=16 value="" >
			</td>
	        </tr>
	        -->
		        
			<tr>
			<td height="33"><?=$m_auto_refresh?></td>
				<td height="33">
					<select size="1" name="f_autorefresh">
					<option value="0" ><?=$m_refresh_none?></option>
					<option value="300" &nbsp;><?=$m_refresh_5min?></option>
					<option value="900" &nbsp;><?=$m_refresh_15min?></option>
					<option value="1800" &nbsp;><?=$m_refresh_30min?></option>
					<option value="3600" &nbsp;><?=$m_refresh_1hr?></option>
					<option value="7200" &nbsp;><?=$m_refresh_2hr?></option>
					<option value="21600" &nbsp;><?=$m_refresh_6hr?></option>
					<option value="43200"&nbsp;><?=$m_refresh_12hr?></option>
					
					<option value="86400"&nbsp;><?=$m_refresh_1day?></option>
					</select>
				</td>
			</tr>
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
