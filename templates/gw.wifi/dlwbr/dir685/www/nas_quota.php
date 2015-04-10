<?
/* vi: set sw=4 ts=4: ---------------------------------------------------------*/
$MY_NAME		="nas_quota";
$MY_MSG_FILE	=$MY_NAME.".php";
$CATEGORY		="nas";
/* --------------------------------------------------------------------------- */
if($ACTION_ENABLE_QUOTA!="")
{
	require("/www/model/__admin_check.php");
	anchor("/nas/quota");
	if($enable_quota=="1")
	{
		set("enable","1");
		
		$NEXT_PAGE=$MY_NAME;
		$SUBMIT_STR=";submit QUOTA";
		if($SUBMIT_STR!="")	{require($G_SAVING_URL);}
		else				{require($G_NO_CHANGED_URL);}
	}
	else
	{
		set("enable","0");
		
		$NEXT_PAGE=$MY_NAME;
		$SUBMIT_STR=";submit QUOTA_STOP";
		if($SUBMIT_STR!="")	{require($G_SAVING_URL);}
		else				{require($G_NO_CHANGED_URL);}
	}
}

$quota_status				= "";
if(query("/nas/quota/enable")=="1")
{
	$quota_status="Started";
	$quota_toogle_button="Disabled";
}else
{
	$quota_status="Stopped";
	$quota_toogle_button="Enabled";
}
echo "<script>var user_name=new Array;</script>";
echo "<script>var gp_name=new Array;</script>";
for ("/nas/user")
{
	$user=query("/nas/user:".$@."/name");
	echo "<script>user_name[".$@."] =\"".$user."\";</script>";
}
for ("/nas/group")
{
	$user=query("/nas/group:".$@."/name");
	echo "<script>gp_name[".$@."] =\"".$user."\";</script>";
}
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


function refresh()
{
	//JUST do refresh
	document.form1.ACTION_POST.value = "";
	document.form1.ACTION_REFRESH.value = "something";
	
	document.form1.submit();
}
var g_AjaxReq = null;
var g_result;
function send_request(url)
{
	g_AjaxReq = createRequest();
	if (g_AjaxReq != null)
	{
		if(url==0)
			url = "/set_temp_nodes.sgi?action=check_quota&d="+Date();
		
		g_AjaxReq.open("GET", url, true);
		g_AjaxReq.onreadystatechange = gen_item;
		g_AjaxReq.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
		g_AjaxReq.send(null);
	}
}
function enable_quota_js()/*need implement*/
{
	if( "<?=$quota_toogle_button?>" == "Enabled")
	{
		self.location.href="<?=$MY_NAME?>.php?enable_quota=1&ACTION_ENABLE_QUOTA=something"; 	
		
	} 
	else
	{
		self.location.href="<?=$MY_NAME?>.php?enable_quota=0&ACTION_ENABLE_QUOTA=something"; 	
	}
}
function submit_quota(quota_value,name,user_or_gp)
{
	
	var url =new String("/set_temp_nodes.sgi?");
	if(user_or_gp=="user")
	{
		url +="action=set_quota_u&f_name="+name+"&size="+quota_value+"&d="+Date();	
	}
	else
	{
		url +="action=set_quota_g&f_name="+name+"&size="+quota_value+"&d="+Date();
	}
	
	send_request(url);
	send_request(0);
	
}
function Check(tmp)
{
	if(tmp.name=="b2")/*user*/
	{
		if (isNaN(document.form1.f1_available.value) || document.form1.f1_available.value < 0 )
		{
			alert("The Quota Amount is invalid. Please enter a valid number.");
			document.form1.f1_available.select();
			document.form1.f1_available.focus();	
			return;
		}
		if(!parseInt(document.form1.f1_available.value))/* >  parseInt(document.form1.f_HDSetMaxSize.value))*/
		{
			alert("This number is higher than the maximum capacity of the hard drives.\nPlease enter a real number or leave the setting at 'unlimited'.");
			document.form1.f1_available.select();
			document.form1.f1_available.focus();
			return;
		}
		submit_quota(document.form1.f1_available.value*1000,document.form1.f1_username.value,'user');
	}
	else if(tmp.name=="b3")/*gp*/
	{
		if (isNaN(document.form1.f1_g_available.value) || document.form1.f1_g_available.value < 0)
		{
			alert("The Quota Amount is invalid. Please enter a valid number.");
			document.form1.f1_g_available.select();
			document.form1.f1_g_available.focus();	
			return;
		}
		if(!parseInt(document.form1.f1_g_available.value)) /*>  parseInt(document.form1.f_HDSetMaxSize.value))*/
		{
			alert("This number is higher than the maximum capacity of the hard drives.\nPlease enter a real number or leave the setting at 'unlimited'.");
			document.form1.f1_g_available.select();
			document.form1.f1_g_available.focus();
			return;
		}
		submit_quota(document.form1.f1_g_available.value*1000,document.form1.f1_gpname.value,'group');
	}		

}

function ModifySetting(username,user_or_gp,quota)
{
	if(user_or_gp==1)//user
	{
		document.form1.f1_username.value=username;
		document.form1.f1_available.value=quota;
        	document.getElementById("uhd1").style.display = "";
	}
	else
	{
		document.form1.f1_gpname.value=username;
		document.form1.f1_g_available.value=quota;
		document.getElementById("ghd1").style.display = "";
	}
}
function is_set_quota(name)/*if in user list, retun 1, group list return 2, else 0*/
{
	for(var y=0;y<g_result.length-1;y+=3)
        {
        	if(name==g_result[y])
                	return y+1;                  
        }
	return 0;
}
function gen_item()
{
	var index;
	var select_row_index = 1;
	var str="";
	var user_or_gp;
	if (g_AjaxReq != null && g_AjaxReq.readyState == 4)
	{	
		g_result=g_AjaxReq.responseText.split(" ");	
	
		str = "";
		str+="<div class='box'>";
		str+="<h2><?=$m_1st_quota_title?></h2>";
		str+="<table border='0' id='uhd1' cellpadding='0' cellspacing='0' style='border-collapse: collapse' bordercolor='#111111' id='AutoNumber1'  width='500'>";
    str+="<tr >";
    str+="<td width='205' height='27'>Username</td>";
    str+="<td width='186' height='27' >";
    str+="<input type='text' readonly name='f1_username' size='20' value='0'></td>";
    str+="<td width='238' height='27' ><p align='left'></td></tr>";

    str+="<tr><td width='205' height='27'>Quota Amount</td>";
    str+="<td width='186' height='27' >";
    str+="<input type='text' name='f1_available' size='20' value='0'>MB</td>";
    str+="<td width='238' height='27' ><p align='left'></td>";
    str+="<td><input type='button' value='Apply' name='b2' onclick='Check(this);'></td></tr></table>";	
    	
		str+="<table border='1' cellpadding='0' cellspacing='0' style='border-collapse: collapse' bordercolor='#111111' id='AutoNumber1'  width='500'>";

		str += "<tr class=FSCol_Hdr>";
		str += "<td class=bc_tb width=10%>ID</td>";
		str += "<td class=bc_tb width=20%>User Name</td>";
		str += "<td class=bc_tb width=30%>Used </td>";
		str += "<td class=bc_tb width=30%>Limited </td>";
		str += "<td class=bc_tb width=10%> Edit</td>";
		str += "</tr>";
		
		for(var i=1;i<user_name.length;i++)
		{
			index=is_set_quota(user_name[i]);
			if(index>0)
			{
				str += "<tr>";
		    str += "<td class=bc_tb width=10% >"+i+"</td>";
        str += "<td class=bc_tb width=20% >"+g_result[index-1]+"</td>";
        str += "<td class=bc_tb width=30% >"+g_result[index]/1000+"</td>";
        str += "<td class=bc_tb width=30% >"+g_result[index+1]/1000+"</td>";
        str += "<td class=bc_tb width=10%><a href=\"javascript:ModifySetting('"+g_result[index-1]+"','1','"+g_result[index+1]/1000+"');\"><img border=\"0\" src=\"../pic/edit.jpg\"></a></td>";
        str += "</tr>";

			}
			else
			{
				str += "<tr>";
        str += "<td class=bc_tb width=10% >"+i+"</td>";
        str += "<td class=bc_tb width=20% >"+user_name[i]+"</td>";
        str += "<td class=bc_tb width=60% colspan=2>Unlimited</td>";
        str += "<td class=bc_tb width=10%><a href=\"javascript:ModifySetting('"+user_name[i]+"','1','0');\"><img border=\"0\" src=\"../pic/edit.jpg\"></a></td>";
        str += "</tr>";
			}
		}
		str += "</table>";
		str += "</div>";
		
		
		str+="<div class='box'>";
		str+="<h2><?=$m_2nd_quota_title?></h2>"
		str+="<table border='0' id='ghd1' cellpadding='0' cellspacing='0' style='border-collapse: collapse' bordercolor='#111111' id='AutoNumber1'  width='500'>";
		str+="<tr >";
    str+="<td width='205' height='27'>Groupname</td>";
    str+="<td width='186' height='27' >";
    str+="<input type='text' readonly name='f1_gpname' size='20' value='0'></td>";
    str+="<td width='238' height='27' ><p align='left'></td></tr>";

    str+="<tr><td width='205' height='27'>Quota Amount</td>";
    str+="<td width='186' height='27' >";
    str+="<input type='text' name='f1_g_available' size='20' value='0'>MB</td>";
    str+="<td width='238' height='27' ></td>";
  	str+="<td><input type='button' value='Apply' name='b3' onclick='Check(this);'></td></tr></table>";
				            
     
		str+="<table border='1' cellpadding='0' cellspacing='0' style='border-collapse: collapse' bordercolor='#111111' id='AutoNumber2' width='500'>"

		str += "<tr class=FSCol_Hdr>";
		str += "<td class=bc_tb width=10%>ID</td>";
		str += "<td class=bc_tb width=20%>Group Name</td>";
		str += "<td class=bc_tb width=30%>Used </td>";
		str += "<td class=bc_tb width=30%>Limited </td>";
		str += "<td class=bc_tb width=10%> Edit</td>";
		str += "</tr>";
		for(i=1;i<gp_name.length;i++)
                {
                        index=is_set_quota(gp_name[i]);
                        if(index>0)
                        {
                                str += "<tr>";
                                str += "<td class=bc_tb width=10% >"+i+"</td>";
                                str += "<td class=bc_tb width=20% >"+g_result[index-1]+"</td>";
                                str += "<td class=bc_tb width=30% >"+g_result[index]/1000+"</td>";
                                str += "<td class=bc_tb width=30% >"+g_result[index+1]/1000+"</td>";
                                str += "<td class=bc_tb width=10%><a href=\"javascript:ModifySetting('"+g_result[index-1]+"','2','"+g_result[index+1]/1000+"');\"><img border=\"0\" src=\"../pic/edit.jpg\"></a></td>";
                                str += "</tr>";

                        }
                        else
                        {
                                str += "<tr>";
                                str += "<td class=bc_tb width=10% >"+i+"</td>";
                                str += "<td class=bc_tb width=20% >"+gp_name[i]+"</td>";
                                str += "<td class=bc_tb width=60% colspan=2>Unlimited</td>";
                                str += "<td class=bc_tb width=10%><a href=\"javascript:ModifySetting('"+gp_name[i]+"','2','0');\"><img border=\"0\" src=\"../pic/edit.jpg\"></a></td>";
                                str += "</tr>";
                        }
               }
		str += "</table>";
		str += "</div>";
		
		
		document.getElementById('row_list').innerHTML = str;
		document.getElementById("uhd1").style.display = "none";
		document.getElementById("ghd1").style.display = "none";
	}
}
</script>

<!-- css for calling explorer.php -->
<link rel="stylesheet" href="/portal/comm/smbb.css" type="text/css"> 


<body onLoad="send_request(0);"<?=$G_BODY_ATTR?>>
<form name="form1" id="form1" method="post" action="<?=$MY_NAME?>.php" onSubmit="return check();";>

<input type="hidden" name="ACTION_POST"	value="1">
<input type="hidden" name="ACTION_REFRESH" value="">

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
		?>
		</div>
<!-- ________________________________ Main Content Start ______________________________ -->
		<?$m_colon="&nbsp;:&nbsp;";?>
		<div name="row_list" id="row_list">
		
		</div>
		
		<div class="box">
		<h2><?=$m_3rd_quota_title?></h2>
			<table border="0" cellpadding="0" cellspacing="0" style="border-collapse: collapse" bordercolor="#111111" id="AutoNumber1" height="46" width="500" >
			<tr><td width="5" height="29" align="left">Status : <?=$quota_status?></td>
			</tr>
			<td>
			<input type="button" value="<?=$quota_toogle_button?>" name="But_quota" onClick="enable_quota_js()">
			</td>
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
