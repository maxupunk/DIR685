<?
/* vi: set sw=4 ts=4: ---------------------------------------------------------*/
$MY_NAME		="nas_disk_management";
$MY_MSG_FILE	=$MY_NAME.".php";
$CATEGORY		="nas";
/* --------------------------------------------------------------------------- */

if ($ACTION_POST!="")
{
	require("/www/model/__admin_check.php");
	anchor("/nas/upnp");
	set("enable", $f_UPNPAVServ);	
	set("refresh", $f_autorefresh);
	echo "<script>alert(\"Saved success\")</script>";
}

anchor("/nas/upnp");
$upnp_enable = query("enable");
$upnp_autorefresh = query("refresh");

/* --------------------------------------------------------------------------- */
require("/www/model/__html_head.php");
echo "<script>\n";
require("/www/comm/__js_select.php");
echo "</script>\n";
/* --------------------------------------------------------------------------- */
// get the variable value from rgdb.

/* --------------------------------------------------------------------------- */
?>

<script>

/* page init functoin */
function init()
{
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
	
	/* auto refresh initialization */
	select_index(document.form1.f_autorefresh, "<?=$upnp_autorefresh?>");

		
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
	}
	else
	{
		document.form1.f_root.disabled=true;
		document.form1.f_dir.disabled=true;
		document.form1.f_autorefresh.disabled=true;
		document.form1.But_Browse.disabled=true;
	}
}
</script>

<body onLoad="init();" <?=$G_BODY_ATTR?>>
<form name="form1" id="form1" method="post" action="<?=$MY_NAME?>.php" onSubmit="return check();";>

<input type="hidden" name="ACTION_POST"	value="1">

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
		<?$m_colon="&nbsp;:&nbsp;";?>
		<div class="box">
			<h2><?=$m_1st_upnp_title?></h2>
			<table border="0" cellpadding="0" cellspacing="0" style="border-collapse: collapse" bordercolor="#111111" id="AutoNumber1" height="74" width="500">
		
		        <tr>
                  <td width="31%" height="32">UPnP AV Server</td>
                  <td width="61%" height="32">
                  <input type="radio" value="1" onClick="disable_item(1)" name="f_UPNPAVServ" >Enable
                  <input type="radio" value="0" onClick="disable_item(0)" name="f_UPNPAVServ" >Disable
                  </td>
				</tr>
		        <tr>
                  <td height="32">Folder</td>
                  <td height="32">  
                  <input type="checkbox" name="f_root" value="ON" onClick="check_path(1)">root
                  </td>
				</tr>
		        <tr id="chamber2" style="display">
				  <td height="29">&nbsp;</td>
		          <td height="29">
	                <input type=text name=f_dir size=30 readonly>
	                <input type="button" name="But_Browse" value="Browse" onClick="opendir();">
	                <input type="hidden" name="f_flow_value" size="20">
	
	                <input type="hidden" name="f_device_read_write" size="2">
	                <input type="hidden" name="f_read_write" size="2">
				  </td>
		        </tr>
		        <tr>
		          <td height="23"></td>
		          <td id="avpath" height="23" style='word-break: break-all'>dlink-D41622_SHARE</td>
		        </tr>
		
		        <tr>
		          <td height="22">&nbsp;</td>
		          <td height="22">&nbsp;</td>
		        </tr>
		       	<tr>
		          <td height="22">Auto Refresh</td>
		          <td height="22">
			          <select size="1" name="f_autorefresh">
	
			          <option value="i" >none</option>
			          <option value="a" >5 minutes</option>
			          <option value="b" >15 minutes</option>
			          <option value="c" >30 minutes</option>
			          <option value="d" >1 Hour</option>
			          <option value="e" >2 Hours</option>
			          <option value="f" >6 Hours</option>
			          <option value="h" >12 Hours</option>
			          <option value="g" >1 Day</option>
			          </select>
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
