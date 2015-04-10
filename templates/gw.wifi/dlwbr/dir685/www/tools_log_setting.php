<?
/* vi: set sw=4 ts=4: ---------------------------------------------------------*/
$MY_NAME		="tools_log_setting";
$MY_MSG_FILE	=$MY_NAME.".php";
$CATEGORY		="tools";
/* --------------------------------------------------------------------------- */
if ($ACTION_POST!="")
{
	require("/www/model/__admin_check.php");
	
	echo "<!--\n";
	echo "log_sys=".$log_sys."\n";
	echo "log_dbg=".$log_dbg."\n";
	echo "log_att=".$log_att."\n";
	echo "log_drp=".$log_drp."\n";
	echo "log_ntc=".$log_ntc."\n";
	echo "-->\n";
	
	$log_dirty=0;
	if($log_sys!="1"){$log_sys="0";}
	if($log_dbg!="1"){$log_dbg="0";}
	if($log_att!="1"){$log_att="0";}
	if($log_drp!="1"){$log_drp="0";}
	if($log_ntc!="1"){$log_ntc="0";}
	
	anchor("/security/log");
	if(query("systemInfo")		!=$log_sys)		{set("systeminfo",		$log_sys);		$log_dirty++;}
	if(query("debugInfo")		!=$log_dbg)		{set("debuginfo",		$log_dbg);		$log_dirty++;}
	if(query("attackInfo")		!=$log_att)		{set("attackinfo",		$log_att);		$log_dirty++;}
	if(query("droppacketInfo")	!=$log_drp)		{set("droppacketinfo",	$log_drp);		$log_dirty++;}
	if(query("noticeInfo")		!=$log_ntc)		{set("noticeinfo",		$log_ntc);		$log_dirty++;}
	
	$SUBMIT_STR="";
	if($log_dirty>0)	{$SUBMIT_STR=";submit SYSLOG;submit RG";}

	$NEXT_PAGE=$MY_NAME;
	if($SUBMIT_STR!="" || $XGISET_AFTER_COMMIT_STR!="")	{require($G_SAVING_URL);}
	else												{require($G_NO_CHANGED_URL);}
}

/* --------------------------------------------------------------------------- */
require("/www/model/__html_head.php");
/* --------------------------------------------------------------------------- */
// get the variable value from rgdb.

/* --------------------------------------------------------------------------- */
?>

<script>
// Lily
Lists=[<?inclog("[\"%0\",\"%1\"],","/var/log/messages");?>["",""]];

//system, debug, att, drop, notice
syslog=['',<?
anchor("/security/log");
echo	"'".	query("systemInfo").		"','".query("debugInfo").	"','".query("attackInfo").
		"','".	query("dropPacketInfo").	"','".query("noticeInfo").	"'";
?>];
/* page init functoin */
function init()
{
	var f=get_obj("frm");
	f.log_sys.checked=(syslog[1]=="1" ?true:false);
	f.log_dbg.checked=(syslog[2]=="1" ?true:false);
	f.log_att.checked=(syslog[3]=="1" ?true:false);
	f.log_drp.checked=(syslog[4]=="1" ?true:false);
	f.log_ntc.checked=(syslog[5]=="1" ?true:false);
}
/* parameter checking */
function check(bmail)
{
	return true;
}
/* cancel function */
function do_cancel()
{
	self.location.href="<?=$MY_NAME?>.php?random_str="+generate_random_str();
}


</script>
<body onload="init();" <?=$G_BODY_ATTR?>>
<form name="frm" id="frm" method="post" action="<?=$MY_NAME?>.php" onsubmit="return check(0)">
<input type="hidden" name="ACTION_POST" value="SOMETHING">
<input type="hidden" name="send_mail" value="0">
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
			<h2><?=$m_savelog_title?></h2>
			<table borderColor=#ffffff cellSpacing=1 cellPadding=2 width=525 bgColor=#dfdfdf border=1>
			<tr>
				<td class=l_tb colspan=2><?=$m_save_log_cfg?>&nbsp;<input type=button name=save_log value="<?=$m_save?>" onClick="window.location.href='/tsyslog.rg';"></td>
			</tr>
		</table>
		</div>
		<div class="box">
			<h2><?=$m_context_title?></h2>
			<table borderColor=#ffffff cellSpacing=1 cellPadding=2 width=525 bgColor=#dfdfdf border=1>
			<tr>
				<td class=l_tb><?=$m_log_type?></td>
				<td class=l_tb><input type=checkbox name=log_sys value="1"><?=$m_log_sys?></td>
			</tr>
			<tr>
				<td>&nbsp;</td>
				<td class=l_tb><input type=checkbox name=log_dbg value="1"><?=$m_log_dbg?></td>
			</tr>
			<tr>
				<td>&nbsp;</td>
				<td class=l_tb><input type=checkbox name=log_att value="1"><?=$m_log_att?></td>
			</tr>
			<tr>
				<td>&nbsp;</td>
				<td class=l_tb><input type=checkbox name=log_drp value="1"><?=$m_log_drp?></td>
			</tr>
			<tr>
				<td>&nbsp;</td>
				<td class=l_tb><input type=checkbox name=log_ntc value="1"><?=$m_log_ntc?></td>
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
