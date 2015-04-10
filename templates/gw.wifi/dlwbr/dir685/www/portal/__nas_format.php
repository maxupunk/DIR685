<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<meta http-equiv="Pragma" content="no-cache"> 
<meta http-equiv="Cache-Control" content="no-cache"> 
<link rel="stylesheet" type="text/css" href="./style.css" title="HomePortal PDA VERSION" />
<title>Network</title>
<?
$AJAX_NAME		="ajax_format";

require("/www/comm/__js_comm.php");
query("/runtime/nas/doformat/harddrive");
?>
<script type="text/javascript" language="JavaScript">
//----------------------------------------------

function bodyStyle()
{
	var ieorff = (navigator.appName=="Microsoft Internet Explorer"?"IE":"FF"); //default
	var main=document.getElementById("mainDIV");
	main.style.padding='0px';
	if(ieorff=="FF")
		main.style.width='98%';
	else	//IE
		main.style.width='104%';
	main.style.position='absolute';
	main.style.left='0px';
	main.style.top='0px';
	//padding:0px; width:99%; position: absolute; left:0px; top:0px;
	return;
}

//initial 	
function init()
{
	//to set div width from IE and Firefox.
	bodyStyle();	
}

function close_me()
{
	window.parent.window_destroy_singlet(true);
}
</script>
</head>
<body onload="init();">
<DIV id="mainDIV"><!--style="padding:0px; width:99%; position: absolute; left:0px; top:0px; z-index:2" >-->
	<table width="100%" height="150">
		<tr><td><H3>Please follow the instructions on the LCD panel.</H3></td></tr>
		<tr><td align="center"><input type="button" name="close_me" size=10 value="Close" onclick="close_me();"></td></tr>
	</table>
</DIV>
</body>
</html>