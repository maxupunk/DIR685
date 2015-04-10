<?
/* vi: set sw=4 ts=4: -------------------------------------------------------- */
$MY_NAME		= "nas_lcd_setup";
$MY_MSG_FILE	= $MY_NAME.".php";
//$CATEGORY		= "nas";//jana removed
$CATEGORY		= "bsc";//jana added
/* --------------------------------------------------------------------------- */
if ($ACTION_POST!="")
{
	require("/www/model/__admin_check.php");
	$dirty = 0;
	$hd_dirty = 0;
	$SUBMIT_STR = "";

	echo "<!--\n";
	echo "screen_saver_timeout = ".$screen_saver_timeout."\n";
	echo "screen_saver_timeout = ".query("/nas/ui/Lcd/sleep_time")."\n";
//	echo "hd_sleep_timeout = ".$hd_sleep_timeout."\n";
	echo "display_sleep_timeout = ".$display_sleep_timeout."\n";
	echo "display_sleep_timeout = ".query("/nas/ui/screen_saver/sleep_time")."\n";
	
	if (query("/nas/ui/Lcd/sleep_time")!=$display_sleep_timeout)	{$dirty++; set("/nas/ui/Lcd/sleep_time", $display_sleep_timeout);}
	if (query("/nas/ui/screen_saver/sleep_time")!=$screen_saver_timeout)	{$dirty++; set("/nas/ui/screen_saver/sleep_time", $screen_saver_timeout);}
/*
	if (query("/nas/store_dev/sleep_time")!=$hd_sleep_timeout)	
	{
		$dirty++; 
		set("/nas/store_dev/sleep_time", $hd_sleep_timeout);
		if(query("/runtime/nas/store_dev/devname")!="")	{$hd_dirty++;}
	}
*/
	
	echo "-->\n";

//	if ($hd_dirty > 0)		{$SUBMIT_STR="submit HD_RESTART_SLEEPTIME;";}
	if ($dirty > 0)	{$SUBMIT_STR="submit LCD_SET_TIMEOUT;";}
	$NEXT_PAGE = $MY_NAME;
	if ($SUBMIT_STR!="")	{require($G_SAVING_URL);}
	else					{require($G_NO_CHANGED_URL);}
}
/* --------------------------------------------------------------------------- */
require("/www/model/__html_head.php");
/* --------------------------------------------------------------------------- */
//$never_timeout	= 15*60;//15 minutes
$lcd_time	= query("/nas/ui/Lcd/sleep_time");
//$hd_time	= query("/nas/store_dev/sleep_time");
$ss_time	= query("/nas/ui/screen_saver/sleep_time");
?>
<script>
/*
function click_checkbox(obj,input_name)
{
	var f = get_obj("frm");
	
	if(obj.checked)
		eval("f."+input_name+".disabled=false");
	else
		eval("f."+input_name+".disabled=true");
}
*/
/*
function init_checkbox(stime,checkbox_obj,input_obj)
{
	if(stime == 0)	//0 is NEVER_Timeout
	{
		checkbox_obj.checked=false;
		input_obj.disabled=true;
	}
	else
	{
		checkbox_obj.checked=true;
		input_obj.disabled=false;
	}
	input_obj.value=stime/60;	//minute
}
*/
/* page init functoin */
function init()
{
	var f = get_obj("frm");

	select_index(f.screen_saver_timeout,"<? map("/nas/ui/screen_saver/sleep_time", "","180"); ?>");		
	select_index(f.display_sleep_timeout,"<? map("/nas/ui/Lcd/sleep_time", "","300"); ?>");
		
//	init_checkbox(<?=$ss_time?>,f.screen_saver_enable,f.in_screensaver_timeout);
	//init_checkbox(<?=$hd_time?>,f.hd_sleep_enable,f.in_hd_timeout);//jana removed
//	init_checkbox(<?=$lcd_time?>,f.display_sleep_enable,f.in_display_timeout);
}

function check()
{
//	var f = get_obj("frm");
	
//	if(f.screen_saver_enable.checked)
//	{
//		if (is_blank(get_obj("in_screensaver_timeout").value))
//		{
//			alert("<?=$a_empty_timeout?>");
//			field_focus(get_obj("in_screensaver_timeout"), "**");
//			return false;
//		} 
//		if(!is_digit(get_obj("in_screensaver_timeout").value))
//		{
//			alert("<?=$a_not_digit_error?>");
//			field_focus(f.in_screensaver_timeout, "**");
//			return false;		
//		}
//		if(parseInt(f.in_screensaver_timeout.value,10)>=15 || parseInt(f.in_screensaver_timeout.value,10)<1)
//		{
//			alert("<?=$a_time_range_error?>");
//			field_focus(f.in_screensaver_timeout, "**");
//			return false;
//		}
//		f.screen_saver_timeout.value=parseInt(f.in_screensaver_timeout.value,10)*60;
//	}
//	else
//	{
//		f.screen_saver_timeout.value=0;
//		f.in_screensaver_timeout.disabled=true;
//	}
	/*jana removed
	if(f.hd_sleep_enable.checked)
	{
		if (is_blank(get_obj("in_hd_timeout").value))
		{
			alert("<?=$a_empty_timeout?>");
			field_focus(get_obj("in_hd_timeout"), "**");
			return false;
		} 
		if(parseInt(f.in_hd_timeout.value,10)>=15 || parseInt(f.in_hd_timeout.value,10)<1)
		{
			alert("<?=$a_time_range_error?>");
			field_focus(f.in_hd_timeout, "**");
			return false;
		}
		f.hd_sleep_timeout.value=parseInt(f.in_hd_timeout.value,10)*60;
	}
	else
	{
		f.hd_sleep_timeout.value=0;
		f.in_hd_timeout.disabled=true;
	}
	*/
	
//	if(f.display_sleep_enable.checked)
//	{
//		if (is_blank(get_obj("in_display_timeout").value))
//		{
//			alert("<?=$a_empty_timeout?>");
//			field_focus(get_obj("in_display_timeout"), "**");
//			return false;
//		} 
//		if(!is_digit(get_obj("in_display_timeout").value))
//		{
//			alert("<?=$a_not_digit_error?>");
//			field_focus(f.in_display_timeout, "**");
//			return false;		
//		}
//		if(parseInt(f.in_display_timeout.value,10)>=15 || parseInt(f.in_display_timeout.value,10)<1)
//		{
//			alert("<?=$a_time_range_error?>");
//			field_focus(f.in_display_timeout, "**");
//			return false;
//		}
//		f.display_sleep_timeout.value=parseInt(f.in_display_timeout.value,10)*60;
//	}
//	else
//	{
//		f.display_sleep_timeout.value=0;
//		f.in_display_timeout.disabled=true;
//	}
	
//	f.in_screensaver_timeout.disabled=true;
	//f.in_hd_timeout.disabled=true;//jana removed
//	f.in_display_timeout.disabled=true;
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
<!--
<input type="hidden" name="screen_saver_timeout" value="0">
jana removed  <input type="hidden" name="hd_sleep_timeout" value="0">  
<input type="hidden" name="display_sleep_timeout" value="0">
-->
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
		$dummy = fread($LOCALE_PATH."/dsc/dsc_".$MY_NAME.".php");
		if ($dummy != "") { require($LOCALE_PATH."/dsc/dsc_".$MY_NAME.".php"); }
		else { require("/www/locale/en/dsc/dsc_".$MY_NAME.".php"); }
		echo $G_APPLY_CANEL_BUTTON;
		?>
		</div>
<!-- ________________________________ Main Content Start ______________________________ -->
		<div class="box">
			<h2><?=$m_title_screen_saver?></h2>
			<p>
			<table width=525 border=0>
				<!--
				<tr>
					<td class="r_tb" width=160><?=$m_enable?>&nbsp;:&nbsp;</td>
					<td class="l_tb">
						<input type="checkbox" name="screen_saver_enable" id="screen_saver_enable" onclick="click_checkbox(this,'in_screensaver_timeout');">
					</td>
				</tr>
				-->
				<tr>
					<td class="r_tb" width=160><?=$m_timeout?>&nbsp;:&nbsp;</td>
					<td class="l_tb">
					<!-- 1, 3, 5, 10, 15, 30, 60 min -->
					<select name="screen_saver_timeout" id="screen_saver_timeout">
						<option value=60>1</option>
						<option value=180>3</option>
						<option value=300>5</option>
						<option value=600>10</option>
						<option value=900>15</option>
						<option value=1800>30</option>						
						<option value=3600>60</option>		
						<option value=0><?=$m_timeout_never?></option>				
					</select>
						<!--
						<input type="text" name="in_screensaver_timeout" id="in_screensaver_timeout" size=10 maxlength=2>&nbsp;
						-->
						<?=$m_minute?> 
					</td>
				</tr>
			</table>
		</div>
	<!--jana removed
		<div class="box">
			<h2><?=$m_title_hd?></h2>
			<?=$m_hd_dsc?>
			<table width=525 border=0>
				<tr>
					<td class="r_tb" width=160><?=$m_enable?>&nbsp;:&nbsp;</td>
					<td class="l_tb">
						<input type="checkbox" name="hd_sleep_enable" id="hd_sleep_enable" onclick="click_checkbox(this,'in_hd_timeout');">
					</td>
				</tr>
				<tr>
					<td class="r_tb" width=160><?=$m_timeout?>&nbsp;:&nbsp;</td>
					<td class="l_tb">
						<input type="text" name="in_hd_timeout" id="in_hd_timeout" size=10 maxlength=2>&nbsp;<?=$m_minute?> 
					</td>
				</tr>
			</table>
		</div>
	-->
		<div class="box">
			<h2><?=$m_title_display?></h2>
			<?=$m_display_dsc?>
			<table width=525 border=0>
			<!--
				<tr>
					<td class="r_tb" width=160><?=$m_enable?>&nbsp;:&nbsp;</td>
					<td class="l_tb">
						<input type="checkbox" name="display_sleep_enable" id="display_sleep_enable" onclick="click_checkbox(this,'in_display_timeout');">
					</td>
				</tr>
			-->
				<tr>
					<td class="r_tb" width=160><?=$m_timeout?>&nbsp;:&nbsp;</td>
					<td class="l_tb">
					<!-- 5, 10, 15, 30, 60, 90, 120 min -->
					<select name="display_sleep_timeout" id="display_sleep_timeout">
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
						<input type="text" name="in_display_timeout" id="in_display_timeout" size=10 maxlength=2>&nbsp;
					-->	
						<?=$m_minute?> 
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
