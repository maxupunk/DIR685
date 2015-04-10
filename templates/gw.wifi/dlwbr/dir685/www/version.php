<?
/* vi: set sw=4 ts=4: */
$MY_NAME	= "version";
$MY_MSG_FILE	= $MY_NAME.".php";
/* ------------------------------------------------------------------------- */
//$NO_NEED_AUTH="1";
$NO_SESSION_TIMEOUT="1";

if ($ACTION_POST!="")
{
	require("/www/model/__admin_check.php");
	$db_dirty=0;
	if(query("/wireless/auth_logo") != $f_auth_logo) { set("/wireless/auth_logo", $f_auth_logo); $db_dirty++; }

	if($db_dirty > 0)	{$SUBMIT_STR="submit WLAN";}
	$NEXT_PAGE=$MY_NAME;
	if($SUBMIT_STR!="")	{require($G_SAVING_URL);}
	else				{require($G_NO_CHANGED_URL);}
}
/* ------------------------------------------------------------------------- */
// get the variable value from rgdb.
$cfg_auth_logo = query("/wireless/auth_logo");

require("/www/model/__html_head.php");

$HW_VER = query("/sys/hwversion");
$FW_VER = fread("/etc/config/buildver");
?>
<script>
function shortTime()
{
	t="<?query("/runtime/sys/uptime");?>";

	var str=new String("");
	var tmp=parseInt(t, [10]);
	var sec=0,min=0,hr=0,day=0;
	sec=t % 60;  //sec
	min=parseInt(t/60, [10]) % 60; //min
	hr=parseInt(t/(60*60), [10]) % 24; //hr
	day=parseInt(t/(60*60*24), [10]); //day

	if(day>=0 || hr>=0 || min>=0 || sec >=0)
		str=(day >0? day+" <?=$m_days?>, ":"0 <?=$m_days?>, ")+(hr >0? hr+":":"00:")+(min >0? min+":":"00:")+(sec >0? sec :"00");
	return str;
}

function getQueryUrl()
{
	var fwver = "<?=$FW_VER?>";
	var hwstr = "<?=$HW_VER?>";
	var hwver = "Ax";
	var LangCode = "EN";
	// Get sw ver
	fwstr = fwver.split(".");
	fwver = "0" + fwstr[0] + fwstr[1]; //0112

	// Get hw revision
	for(i=0; i<hwstr.length; i++)
	{
			char_code = hwstr.charAt(i);
			if ((char_code >= 'a' && char_code <= 'z') ||
					(char_code >= 'A' && char_code <= 'Z'))
			{
					hwver=char_code.toUpperCase()+"x";
					break;
			}
	}


	// Get query url
	QueryUrl ="http:\/\/"+"<?=$fwinfo_srv?>"+"<?=$fwinfo_path?>"+"?model="+"<?=$model_name?>"+"_"+hwver+"_Default_FW_"+fwver;
	return QueryUrl;
}

var digitArray = new Array('0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f');

function toHex( n ) {

        var result = ''
        var start = true;

        for ( var i=32; i>0; ) {
                i -= 4;
                var digit = ( n >> i ) & 0xf;

                if (!start || digit != 0) {
                        start = false;
                        result += digitArray[digit];
                }
        }

        return ( result == '' ? '0' : result );
}
function pad( str, len, pad ) {
        var result = str;

        for (var i=str.length; i<len; i++){
                result = pad + result;
        }

        //return '\\x' + result;
		return  result;

}


function EncodeHex( formet ) {

        var str = "<?=$build_datetime?>";		
        var result = "";

        for( var i=0; i<str.length; i++ ) {

                if( str.substring(i,i+1).match(/[^\x00-\xff]/g) != null ) {
                        result += escape(str.substring(i,i+1), 1).replace(/%/g,'\\');
                } else {
                        result += pad(toHex(str.substring(i,i+1).charCodeAt(0)&0xff),2,'0');
                }
        }
		var tmp = "";
		tmp = result.substring(result.length-8,result.length);

        return tmp;
}

function init()
{
	var f=get_obj("frm");
	f.auth_logo.checked = <? if ($cfg_auth_logo=="1") {echo "true";} else {echo "false";} ?>;
	f.bt.focus();
}
function click_bt()
{
	self.location.href="<?=$G_HOME_PAGE?>.php";
}
function check()
{
	var f = get_obj("frm");
	var f_final = get_obj("final_form");

	f_final.f_auth_logo.value = "";
	if (f.auth_logo.checked) { f_final.f_auth_logo.value = "1"; }
	f_final.submit();
}
</script>

<form name="final_form" id="final_form" method="post" action="<?=$MY_NAME?>.php">
<input type="hidden" name="ACTION_POST"			value="final">
<input type="hidden" name="f_auth_logo"			value="">
</form>

<?
$USE_BUTTON="1";
$USE_SAVE_BUTTON="1";
require("/www/model/__show_vista_logo.php");
?>
