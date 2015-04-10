<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<meta http-equiv="Pragma" content="no-cache"> 
<meta http-equiv="Cache-Control" content="no-cache"> 
<link rel="stylesheet" type="text/css" href="./style.css" title="HomePortal PDA VERSION" />
<title>Network</title>
<?
$AJAX_NAME		="__ajax_explorer";

require("/www/comm/__js_comm.php");
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
	
	ShowPath("Loading...");
	AddWaitTable();
	var localURL = document.location.href;
	
	refresh("","my_test")
}

var current_path='';
var current_location='';
var up_level_path='';
var up_level_location='';
var dataview_type='';
var pathArray='';

var request=Create_Ajax_Obj();
var DIRECTORY=4;
var FILES=5;


//Ajax obj
function Create_Ajax_Obj(){

	try {
		return new XMLHttpRequest();
	} catch (trymicrosoft) {
		try {
			return new ActiveXObject("Msxml2.XMLHTTP");
		} catch (othermicrosoft) {
			try {
				return new ActiveXObject("Microsoft.XMLHTTP");
			} catch (failed) {
				return null;
			}
		}
	}
}

//refresh 
function refresh(path,location)
{
	ShowStatusBar(false,0,0,0,0);
	if(location=="my_test" || location=="Directory")
    {
    	var str=new String("<?=$AJAX_NAME?>.sgi?");
		
		//str+="action=getlist&path=&where=&date=";
		str+="action=getlist&path="+path+"&where=&date=";
		
		current_path=path;
		current_location=location;
		dataview_type=GetDataviewType(current_path,current_location);
	    //alert("dataview_type " + dataview_type);
	    ShowPath(current_path);
	    AddWaitTable();
	    
		freshData(str, "exec_getlist");
    }
}

//get the icon image that mapping to the file extend name 
function select_icon(fname)
{
	if(fname.substring(fname.length-4,fname.length).toLowerCase()=='.mp3' ||
	   fname.substring(fname.length-4,fname.length).toLowerCase()=='.wma' ||
	   fname.substring(fname.length-4,fname.length).toLowerCase()=='.mpg' ||
	   fname.substring(fname.length-5,fname.length).toLowerCase()=='.mpeg' ||
	   fname.substring(fname.length-4,fname.length).toLowerCase()=='.avi' ||
	   fname.substring(fname.length-4,fname.length).toLowerCase()=='.asf' ||
	   fname.substring(fname.length-4,fname.length).toLowerCase()=='.mpe' ||
	   fname.substring(fname.length-3,fname.length).toLowerCase()=='.qt' ||
	   fname.substring(fname.length-4,fname.length).toLowerCase()=='.mov' ||
	   fname.substring(fname.length-3,fname.length).toLowerCase()=='.mv' ||
	   fname.substring(fname.length-4,fname.length).toLowerCase()=='.wmv')
		return './images/player.gif';
	else
		return  './images/ukn.gif';
}

//add dir into table
function Add_TR(type,list_info)
{
	
	var data;
	var tr_html='';
	var path;
	
	switch(type)
	{
		case DIRECTORY:
		case FILES:		
			
			if(list_info.substring(0,26)=='Anonymous login successful')
					list_info=list_info.substring(27,list_info.length-1);
		
			//First add ..(previous page)
			tr_html+='<tr>';
			tr_html+='<td width="20px">';
			tr_html+='<img border="0" src="images/fo.gif" width="16" height="16">';
			tr_html+='</td>';
			tr_html+='<td>';
			tr_html+='<a href=\"javascript:GoToUpLevel();\">';
			tr_html+='..</a>';
			tr_html+='</td>';
			tr_html+='<td width="57px"></td>';
			tr_html+='</tr>';
			
			data=escape(list_info);
			data=data.split('%0A');
			
			/*
			data[0], data[1] now is a line
			*/
			//alert("data[0] is " + data[0]);
			//alert("data[1] is " + data[1]);
			//alert("data[2] is " + data[2]);
			
			var stdata;
			var temp=new Array();
			var subtract_line=1;
			var my_j = 0;
			var temp = new Array();
			var count= 0;
			alert("data.length is " + data.length );
			
			/* parse each line */
			for (var j=0;j<data.length;j++)
			{
				
				temp[j] = new Array();
				//alert("data["+j+"] is : " + data[j]);				
				stdata=data[j].split('%20');
				
				/*
				"-rw-r--r--    1 0        0            5.5k Jan  1 02:58 nas_iTunes.php"
				"-rw-r--r--    1 0        0              96 Jan  1 02:58 wpsinfo.phpfo.php"
				*/
				
				/* store all values in temp[][] */
				count = 0;
				for (var i=stdata.length-1;i>=0;i--)
				{
					if(unescape(stdata[i])!='')
					{
						//alert("stdata["+i+"] in temp["+j+"]["+count+"] " + stdata[i]);
						temp[j][count] = stdata[i];
						count++;
					}
				}
				
				/* temp[j][0] now store the filename   (ex : nas_iTunes.php) */
				/* temp[j][8] now store the permission (ex : -rw-r--r--) */
				
			} //end of for (each line parsing)
			
			/* write html codes for DIRECTORIES 
			(check it from temp[j][8] --> permissions) */
			for (var j=0;j<data.length-subtract_line;j++)
			{
				if(temp[j][8].substring(0,1)=='d' && temp[j][0]!='.' && temp[j][0]!='..')
				{
					tr_html+='<tr>';
					tr_html+='<td width="20px">';
					tr_html+='<img border="0" src="images/fo.gif" width="16" height="16">';
					tr_html+='</td>';
					tr_html+='<td>';
					tr_html+='<a href=\"javascript:refresh(\'';
					tr_html+=current_path+'/'+temp[j][0];		
					tr_html+='\',\'my_test\');\">';
					tr_html+=temp[j][0]+'</a>';						
					tr_html+='</td>';
					tr_html+='<td width="57px"><input type=button value="Apply"';
					tr_html+=' onclick="LinkDir(\''+current_path+'/'+temp[j][0]+'\',\'SMBMount_F\');"';
					tr_html+='></td>';
					tr_html+='</tr>';
					
				}
			}
			
			/* write html codes for FILES 
			(check it from temp[j][8] --> permissions) */
			for (var j=0;j<data.length-subtract_line;j++)
			{
				if(temp[j][8].substring(0,1)=='-' && temp[j][1].search('H')!=1)
				{
					tr_html+='<tr>';
					tr_html+='<td width="20px">';
					tr_html+='<img border="0" width="16" height="16" src="';
					tr_html+=select_icon(temp[j][0]);
					tr_html+='" width="16" height="16">';
					tr_html+='</td>';
					tr_html+='<td style="word-break:break-word">';
					tr_html+=temp[j][0];
					tr_html+='</td>';
					tr_html+='<td width="58px" align="right">';
					tr_html+='</td>';
					tr_html+='</tr>';
				}
			}
			break;
		default:
			headertext=',,';
			break;
	}
	return tr_html;
}

//add table header	
function create_table_th(HeaderText)
{
	var THeader=new Array();
	THeader=HeaderText.split(",");
	var th_html='';
	th_html+='<tr>';
	for(var i=0;i<THeader.length;i++)
	{
		th_html+='<th>';
		th_html+=THeader[i];
		th_html+='</th>';		
	}
	th_html+='</tr>';
	return th_html;
}

//add file list table
function Add_Table(type,resText)
{	
	var headertext=',Name,Option';
	var file_table_html='';
	file_table_html+='<table border="0" width="100%" cellspacing="0" cellpadding="0" id="file_table" name="file_table"><tobdy>';
	
	if(type==DIRECTORY || type==FILES )
	{
		headertext=',Name,Option';
		file_table_html+=create_table_th(headertext);
	}
	file_table_html+=Add_TR(type,resText);
	file_table_html+='</tbody></table>';
	return file_table_html;
}

/*show alert message,
	display:display message,value=boolean,true or false ,
	txt:message,value=string,
	gif:images type,value=int, 1:information,2:attention,
	always:consistent display,value=boolean,true or false,
	timeout:consistent time,value=int, 1000= 1second.
*/
function ShowStatusBar(display,txt,gif,always,timeout)
{
	var attention_table_html='';
	if(!display)
	{
		statusBar.innerHTML=attention_table_html;
		return;
	}
	else
	{
		attention_table_html+='<table border="0" width="100%" cellspacing="0" cellpadding="0" id="attention_table" name="attention_table"><tbody>';		
		attention_table_html+='<tr><td width="20px"><img border="0" src="images/message_icon';
		attention_table_html+=gif;
		attention_table_html+='.gif" width="16" height="16"></td><td>';
		attention_table_html+='<div name="message" id="message" style="float:left;FONT-SIZE: 12px; COLOR:#FFFFCC; text-align:left; width:100%; height:14px">';
		attention_table_html+=txt;
		attention_table_html+='</div></td></tr></tbody></table>';
		statusBar.innerHTML=attention_table_html;
	}
	if(!always)
		setTimeout("ShowStatusBar(false,0,0,false,0)",timeout);
}

//Set Up Level Path variable
function SetUpLevelPath()
{	
	switch(dataview_type)
	{
		case DIRECTORY:
			up_level_path = "";
			//alert("current_path " + current_path);
			pathArray = current_path.split('/');
			//alert("pathArray.length "+pathArray.length);
			for(var i=0;i<pathArray.length-1;i++)
			{
				up_level_path+=pathArray[i];
				if(i!=pathArray.length-2)
					up_level_path+='/';
				
			}
			up_level_location='my_test';
			break;

		case FILES:
			up_level_path='';
			for(var i=0;i<pathArray.length-1;i++)
			{
				up_level_path+=pathArray[i];
				//if not the last element,the next char must be '/'
				if(i!=pathArray.length-2)
					up_level_path+='/';
			}
			up_level_location='Directory';
			break;
		
		default:
			up_level_path='/';
			up_level_location='my_test';
			break;
	}
	//alert("direc up_level_path "+ up_level_path + ", up_level_location "+up_level_location);
}

//Go To Up Level
function GoToUpLevel()
{
	SetUpLevelPath();
	refresh(up_level_path,up_level_location);
}	

function initFileList()
{
	if (request!=null && request.readyState == 4) 
    {
    	//alert(request.responseText);
    	//alert(escape(request.responseText));
		__reList = request.responseText;
		filelist.innerHTML=Add_Table(dataview_type,__reList);
	}
}

function SaveLinkDir()
{
	var topDiv=window.parent.document.getElementById("s_all_dir");
	var link_text=document.getElementById("link_text");
	topDiv.value=link_text.value;
	
	window.parent.window_destroy_singlet(true);
}

function LinkDir(path,flag)
{
	var link_text=document.getElementById("link_text");
		
	if(flag=="SMBMount_D")
		link_text.value="/"+path;
	else
		link_text.value=path.substring(path.indexOf("/"),path.length);;
}

//show current path ,flag=true or false,txt=message
function GetPathGif()
{
	var gifname='';
	switch(dataview_type)
	{
		case DIRECTORY:
			gifname='nfo.gif';
			break;
		case FILES:
			gifname='nfo.gif';
			break;
		default:
			gifname='nfo.gif';
			break;
	}
	return gifname;
}

//show current path
function ShowPath(txt)
{
	var path_area_html;
	path_area_html = '<TABLE border="0" width="100%" cellspacing="0" cellpadding="0">';
    path_area_html +='<TBODY>';
    path_area_html +='<TR><TD width="20px" ><img border="0" src="images/';
    path_area_html +=GetPathGif();				
  	path_area_html +='" width="20" height="20"></TD>';
	path_area_html +='<TD style="float:left;text-align: left;">';
	path_area_html +='<div name="path_text" id="path_text" style="float:left;text-align: left; width:100%;">';
	path_area_html +=txt;
	path_area_html +='</div></TD></TR>';
	path_area_html +='<TR><TD colspan="2" height="2px"  bgcolor="#455866"></TD></TR>';
    path_area_html +='</TBODY></TABLE>';
    
    path_area.innerHTML=path_area_html;
}

/*Get Current Data View Type by path and location
	Data View Type :
		WORKGROUPS : path='',location=='Network'
		COMPUTERS : path='workgroup1',location=='Network'
		FOLDERLIST : path='workgroup1/pc1',location=='Network'
		DIRECTORY : path='workgroup1/pc1/images',location=='FolderList'
		FILES : path='workgroup1/pc1/images/123',location=='Directory'
*/
function GetDataviewType(path,location)
{
	pathArray=path.split('/');
	var type='';
	//+++ hendry modify
	if(location=='my_test')
		type=DIRECTORY;

	return type;		
}

//data request function (ajax)
function freshData(path,location)
{	
	var url='';
	var readyFunc;
	
	if(location=="exec_getlist")
	{
		ShowPath(current_path);
		AddWaitTable();
		var url=path;	
		readyFunc = initFileList;
	}
	
	request.open("GET", url, true);
	request.onreadystatechange = readyFunc;
	request.send(null);
}

//Show waitting images
function AddWaitTable()
{
	filelist.innerHTML='<TABLE width="100%" height="100%"><TBODY>';
	filelist.innerHTML+='<TR><TD><p align="center"><img src="images/wait.gif" align="center"></TD></TR></TBODY></TABLE>';
}
</script>
</head>
<body onload="init();">
<form name="mainform" id="mainform" method="post">
<DIV id="mainDIV"><!--style="padding:0px; width:99%; position: absolute; left:0px; top:0px; z-index:2" >-->
	<H2>Connect : <input id="link_text" type=text size=40 maxlength=100>  <input type=button value="Save" onclick="SaveLinkDir();"></H2>
	<TABLE cellSpacing=0 cellPadding=0 width="100%" height="97%" border=0>
		<TBODY>
			<TR>
				<TD vAlign=top width="100%" style="word-break:break-all;">
					<div id="statusBar"  name="statusBar" style="float:left;display:block;position:relative; width:100%;text-align: left;"></div>
					<div id="path_area" name="path_area" style="float:left;display:block;position:relative; width:100%;text-align: left" ></div>
					<div id="filelist"  style="float:left;display:block;position:relative; width:100%;text-align: left"></div>
            	</TD>
            </TR>
		</TBODY>
	</TABLE>
</DIV>
</form>

</body>
</html>