<?
/* vi: set sw=4 ts=4: -------------------------------------------------------- */
$MY_NAME		= "nas_frameit";
$MY_MSG_FILE	= $MY_NAME.".php";
$CATEGORY		= "nas";
/* --------------------------------------------------------------------------- */
if ($ACTION_POST!="")
{
	require("/www/model/__admin_check.php");
	$dirty = 0;
	$SUBMIT_STR = "";

	echo "<!--\n";
	echo "collection_id = ".$collection_id."\n";

	if (query("/nas_ui/frameit/collection_id")!=$collection_id)	{$dirty++; set("/nas_ui/frameit/collection_id", $collection_id);}
	
	echo "-->\n";

	if ($dirty > 0)	{$SUBMIT_STR="submit FRAMEIT_RESTART";}
	$NEXT_PAGE = $MY_NAME;
	if ($SUBMIT_STR!="")	{require($G_SAVING_URL);}
	else							{require($G_NO_CHANGED_URL);}
}
/* --------------------------------------------------------------------------- */
require("/www/model/__html_head.php");
/* --------------------------------------------------------------------------- */
$collection_id	= query("/nas_ui/frameit/collection_id");
?>
<script>
function init()
{
	var f = get_obj("frm");
	
}

function check()
{
	return true;
}

function do_cancel()
{
	self.location.href="<?=$MY_NAME?>.php?random_str="+generate_random_str();
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
<!-- ________________________________ Main Content Start ______________________________ -->
		<div class="box">
			<h2>FrameIt</h2>
			<p>
			<table width=525 border=0>
				<tr>
					<td class="r_tb" width=160>Collection ID&nbsp;:&nbsp;</td>
					<td class="l_tb">
						<input type="text" name="collection_id" id="collection_id" size=10 value="<?=$collection_id?>">
					</td>
				</tr>
			</table>
		</div>
		<div id="box_bottom">
		<? echo $G_APPLY_CANEL_BUTTON; ?>
		</div>
<!-- ________________________________  Main Content End _______________________________ -->
	</td>
	<td <?=$G_HELP_TABLE_ATTR?>><?
	$dummy = fread($LOCALE_PATH."/help/h_".$MY_NAME.".php");
	if ($dummy != "") { require($LOCALE_PATH."/help/h_".$MY_NAME.".php"); }
	else { require("/www/locale/en/help/h_".$MY_NAME.".php"); }
	?></td>
</tr>
</table>
<?require("/www/model/__tailer.php");?>
</form>
</body>
</html>
