<?require("/www/model/__html_head.php");?>
<body <?=$G_BODY_ATTR?>>
<form name="frm" id="frm" method="post" action="<?=$SPT_FILE_NAME?>.php">
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
  <div id="box_header"><h1><?=$MY_TITLE?></h1>
  <?require($LOCALE_PATH."/dsc/dsc_".$SPT_FILE_NAME."_menu.php");?></div>
  
	<div id="box"><?require($LOCALE_PATH."/dsc/dsc_".$SPT_FILE_NAME.".php");?></div>
<!-- ________________________________  Main Content End _______________________________ -->
	</td>
</tr>
</table>
<?require("/www/model/__tailer.php");?>
</form>
</body>
</html>
