<?
$AJAX_NAME		="__login";
/* vi: set sw=4 ts=4: */
if ($ACTION_POST!="")
{
	require("/www/auth/__login.php");
	if		($AUTH_RESULT=="401")	{$HEADER_URL="login_fail.php"; require("/www/comm/__header.php");}
	else if ($AUTH_RESULT=="full")	{$HEADER_URL="session_full.php"; require("/www/comm/__header.php");}

	$HEADER_URL="index.php";
	require("/www/comm/__header.php");
}

/* ------------------------------------------------------------------------ */
$MY_NAME="login";
$MY_MSG_FILE=$MY_NAME.".php";
$NO_NEED_AUTH="1";
$NO_SESSION_TIMEOUT="1";
require("/www/model/__html_head.php");
$en_captcha=query("/sys/captcha");
if($en_captcha=="")	{$en_captcha=0;}
?>

<script>
var AjaxReq = null;
function send_request(url, update_func)
{
    if (AjaxReq == null) AjaxReq = createRequest();
    AjaxReq.open("GET", url, true);
    AjaxReq.onreadystatechange = update_func;
    AjaxReq.send(null);
}
function generate_img_ready()
{
	if (AjaxReq != null && AjaxReq.readyState == 4)
    {
		if(AjaxReq.responseText!="")
		{
			var idx = AjaxReq.responseText;
			var f=document.getElementById("auth_img");
			f.innerHTML="<img src='auth_img/"+idx+"?random_str="+generate_random_str()+"'>";
			document.getElementById("FILECODE").value=idx;
		}
	}
}
function generate_img()
{
	var f=document.getElementById("auth_img");
	f.innerHTML="<font color=red><?=$m_wait_msg?></font>";
	send_request("<?=$AJAX_NAME?>.php?random_str="+generate_random_str(),generate_img_ready);
}
/* page init functoin */
function init()
{
	var f=get_obj("frm");
	f.LOGIN_PASSWD.focus();
	if(<?=$en_captcha?>)
	{
		get_obj('div_vercode_submit').style.display='';
		get_obj('div_vercode_dsc').style.display='';
		get_obj('div_vercode_body').style.display='';
		generate_img();
	}
	else
		get_obj('div_submit').style.display='';
}
/* parameter checking */
function check()
{
	var f=get_obj("frm");
	/*if(f.LOGIN_USER.value=="")
	{
		alert("<?=$a_invalid_user_name?>");
		f.LOGIN_USER.focus();
		return false;
	}*/
	if(<?=$en_captcha?>)
	{
		if(f.VER_CODE.value=="")
		{
			alert("<?=$a_blank_vercode?>");
			f.VER_CODE.focus();
			return false;
		}
		else
		{
			f.VERIFICATION_CODE.value = f.VER_CODE.value.toUpperCase();
			f.VER_CODE.disabled = true;
		}
	}
	return true;
}

function keypress_ver_code(e)
{
	if(e.keyCode==13)
	{
		var f=get_obj("frm"); 
		if(check())		f.submit();
	}
}
</script>
<body onload="init();" <?=$G_BODY_ATTR?>>
<form name="frm" id="frm" method="post" action="login.php">
<input type="hidden" name="ACTION_POST" value="LOGIN">
<input type=hidden name="FILECODE" id="FILECODE" value="">
<input type=hidden name="VERIFICATION_CODE" id="VERIFICATION_CODE" value="">
<?require("/www/model/__banner.php");?>
<table <?=$G_MAIN_TABLE_ATTR?>>
<tr valign=middle align=center>
	<td>
	<br>
<!-- ________________________________ Main Content Start ______________________________ -->
	<table width=80%>
	<tr>
		<td id="box_header">
			<h1><?=$m_context_title?></h1>
			<?=$m_login_router?>
			<br><br><center>
			<table width=40%>
			<tr>
				<td><?=$m_user_name?></td>
				<td><!--<input type=text name="LOGIN_USER">-->
					<select size=1 name=LOGIN_USER id=LOGIN_USER>
					<?
					for("/sys/user")
					{
						echo "<option value='".query("name")."'>".query("name")."</option>";
					}
					?>
					</select>
				</td>
			</tr>
			<tr>
				<td><?=$m_password?></td>
				<td><input type=password name="LOGIN_PASSWD" maxlength=20></td>
				<td id="div_submit" style="display:none"><input type="submit" name="login" value="<?=$m_log_in?>" onclick="return check()"></td>
			</tr>
			<tr id="div_vercode_dsc" style="display:none">
				<td colspan=2><?=$m_vercode_dsc?>
					<textarea name="VER_CODE" cols="20" rows="1" style="overflow:hidden;" onkeypress="keypress_ver_code(event)"></textarea>
					</td>
			</tr>
			<tr id="div_vercode_body" style="display:none">
				<td colspan=2>
					<table><tr>
					<td><span id="auth_img"></span></td>
					<td><input type=button name="regen" onclick="generate_img();" value="<?=$m_gegenerate?>" valign="middle"></td>
					</tr></table>
				</td>
			</tr>
			<tr id="div_vercode_submit" style="display:none">
				<td colspan=2 align="center"><input type="submit" name="login" value="<?=$m_log_in?>" onclick="return check()" style="WIDTH: 150px;"></td>
			</tr>
			</table>
			</center><br>
		</td>
	</tr>
	</table>
<!-- ________________________________  Main Content End _______________________________ -->
	<br>
	</td>
</tr>
</table>
<?require("/www/model/__tailer.php");?>
</form>
</body>
</html>
