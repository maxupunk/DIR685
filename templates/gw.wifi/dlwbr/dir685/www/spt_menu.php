<?
/* vi: set sw=4 ts=4: ---------------------------------------------------------*/
$MY_NAME		="spt_menu";
$MY_MSG_FILE	=$MY_NAME.".php";
$CATEGORY		="spt";

$FILE_NAME_BSC		= "spt_bsc"; //jana
$FILE_NAME_ADV		= "spt_adv"; 
$FILE_NAME_STORAGE	= "spt_nas"; 
$FILE_NAME_TOOLS	= "spt_tools"; 
$FILE_NAME_ST		= "spt_st"; 


require("/www/model/__html_head.php");
?>
<script>
/* page init functoin */
function init()
{
	var f=get_obj("frm");
	// init here ...
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
<!-- ________________________________ Main Content Start ______________________________ -->
		<div id="box_header"><?require($LOCALE_PATH."/dsc/dsc_".$MY_NAME.".php");?></div>
		
		<div class="box"><a name="bsc"><H2><?=$m_menu_top_bsc?></H2></a>
			<?require($LOCALE_PATH."/dsc/dsc_".$FILE_NAME_BSC."_menu.php");?></div>
			
		<div class="box"><a name="adv"><H2><?=$m_menu_top_adv?></H2></a>
			<?require($LOCALE_PATH."/dsc/dsc_".$FILE_NAME_ADV."_menu.php");?></div>
			
		<div class="box"><a name="storage"><H2><?=$m_menu_top_storage?></H2></a>
			<?require($LOCALE_PATH."/dsc/dsc_".$FILE_NAME_STORAGE."_menu.php");?></div>
			
		<div class="box"><a name="tools"><H2><?=$m_menu_top_tools?></H2></a>
			<?require($LOCALE_PATH."/dsc/dsc_".$FILE_NAME_TOOLS."_menu.php");?></div>
		
		<div class="box"><a name="st"><H2><?=$m_menu_top_st?></H2></a>
			<?require($LOCALE_PATH."/dsc/dsc_".$FILE_NAME_ST."_menu.php");?></div>
				
<!-- ________________________________  Main Content End _______________________________ -->
	</td>
</tr>
</table>
<?require("/www/model/__tailer.php");?>
</form>
</body>
</html>
