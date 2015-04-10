<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<meta http-equiv="Pragma" content="no-cache"> 
<meta http-equiv="Cache-Control" content="no-cache"> 

<title>Network</title>
<?
require("/www/comm/__js_comm.php");
?>
<script type="text/javascript" language="JavaScript">
var AjaxReq = null;
var period = 3000;
function setSB(v)
{
	document.getElementById("sbChild1").style.width= parseInt(v)*2 + "px";		
	document.getElementById("percent").innerHTML = v + "%";	
	if(v=="100")
	{
		document.getElementById("scan").innerHTML = "Scan Successful";	
	}
	else
	{
		document.getElementById("scan").innerHTML = "Please wait a moment";	
	}

}
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

function init()
{
	//to set div width from IE and Firefox.
	bodyStyle();
	
	update_state();	
}
function send_request(url)
{
	AjaxReq = createRequest();
	AjaxReq.open("GET", url, true);
	AjaxReq.onreadystatechange = update_page;
	AjaxReq.send(null);
}

function update_state()
{
	send_request("/processbar.php?r="+generate_random_str());
}
function ShowPath(txt,done)
{
	var process_html = "";

	if( done != "1" && txt >1)
	{		
		txt=txt-1;	
	}

	/* fix bug : hendry : scan media process can reach 103% */
	if(done=="1" || (parseInt(txt) >= 100))
	{
		txt = "100";
		<? set("/runtime/scan_media/enable","0"); ?>
	}
	setSB(txt);
}	
function update_page()
{
/*
	count++;
	get_obj("connstate").value = count + " r="+AjaxReq.readyState+",t="+AjaxReq.responseText;
 */
 
	if (AjaxReq != null && AjaxReq.readyState == 4 )
	{
		if (AjaxReq.responseText.substring(0,3)=="var")
			
			eval(AjaxReq.responseText);
			ShowPath( Math.round(result[1]/result[0]*100,2),result[2]  );
			
			/*delete result;*/
			/*setTimeout('update_state()', period);	*/
			window.setTimeout("update_state()", period);	
	}
}

</script>
</head>
<body onload="init();" bgcolor="#FFFFFF">
<form name="mainform" id="mainform" method="post">

<DIV id="scan" style=" TOP: 40px; LEFT: 0px;COLOR:#000000; FONT: Arial;font-weight: bold;" ></DIV>
<DIV id="mainDIV" >
<DIV align=center style=" TOP: 40px; LEFT: 150px;">

			<DIV id="sb" style="BACKGROUND:#FFFFFF; TOP: 40px;LEFT: 150px;POSITION: absolute;BORDER-RIGHT: lightgrey 0px inset; BORDER-TOP: white 0px inset; BACKGROUND: write; BORDER-LEFT: white 0px inset; WIDTH: 200px; BORDER-BOTTOM: white 0px inset; HEIGHT: 19px; TEXT-ALIGN: left; visibility:visible">
							<DIV id="sbChild1" style=" WIDTH: 0%; POSITION: absolute; HEIGHT: 20px">
										<DIV style="FONT-SIZE: 1px;BACKGROUND:#9c9a9c; WIDTH: 100%; HEIGHT: 100%"></DIV>
							</DIV>

							<DIV id="percent" style="border-color:#CC6600;solid;border-style:solid; border-width:1;FONT-SIZE: 12px; WIDTH: 200px; POSITION: absolute;COLOR: black; FONT-FAMILY: arial; POSITION: absolute; TEXT-ALIGN: center; HEIGHT: 19px;"></DIV>
		  </DIV>
</DIV> 

</DIV>

</form>
</body>
</html>