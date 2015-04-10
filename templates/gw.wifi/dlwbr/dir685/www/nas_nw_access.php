<?
/* vi: set sw=4 ts=4: ---------------------------------------------------------*/
$MY_NAME		="nas_nw_access";
$MY_MSG_FILE	=$MY_NAME.".php";
$CATEGORY		="nas";
/* --------------------------------------------------------------------------- */

if ($ACTION_POST!="")
{
	require("/www/model/__admin_check.php");
	$dirty=0;
	/*
		/nas/network_access/mode
		0: disable mode
		1: open mode
		2: security Mode
	*/
	if($ACTION_POST =="CHG_MODE")
	{
		
		if( query("/nas/network_access/mode") != "2")	{	$dirty++; 	}
		set("/nas/network_access/mode","2"); 
		$SUBMIT_STR=";submit NET_ACCESS_RELOAD";
	}
	else if($ACTION_POST =="DISABLE_MODE")
	{	
		
		if(query("/nas/network_access/mode")!= "0")		{	$dirty++; 	}
		set("/nas/network_access/mode","0");
		$SUBMIT_STR=";submit NET_ACCESS_STOP";
	}
	else if($ACTION_POST =="OPEN_MODE")
	{	
		
		if(query("/nas/network_access/mode")!= "1")		{	$dirty++;	}
		set("/nas/network_access/mode","1"); 
			
		/*if it is open mode , we need to delete other path */	
		anchor("/nas/network_access_open_mode/share_path:1");
		$tmp_path=query("path");
		if($tmp_path!=$f_folder) 
		{ set("path" , $f_dir);set("folder" , $f_folder);set("device_name" , $f_device_name);}
		set("permission" , $read_only);
		set("comment" , $f_comment);
		set("oplocks" , $f_oplocks);
		set("map_archive" , $f_maparchive);
		set("comment" , $f_comment);
		set("share" , $f_share);
		set("open_mode" , "1");
		if ($dirty > 0)
			{$SUBMIT_STR=";submit NET_ACCESS_RELOAD";}
		else
		{$SUBMIT_STR="";}	
	}
	else 
	{
		/* the actions of security mode*/
		if($ACTION_POST == "ADD")
		{
			set("/nas/network_access/mode","2");
			/* add new user/group settings if requested */
			if($user_list!="NONE" && $user_list!="")
			{	/*USER*/
				/*echo "<script>alert(\"Add user for network access settings\")</script>";*/
				/*echo "<script>alert(\"user_list is ".$user_list."\")</script>";*/
				/*echo "<script>alert(\"share is ".$f_share."\")</script>";*/
					
				/* find the index of share_path (perhaps user already has other share_path) */
				$i = 1;		//index for "network_access/share_path" node
				$share_path= query("/nas/user:".$user_list."/network_access/share_path:".$i."/path");
				while($share_path != "")
				{
					$i++;
					$share_path= query("/nas/user:".$user_list."/network_access/share_path:".$i."/path");
				}
					
				//now $i is the correct index 
				anchor("/nas/user:".$user_list."/network_access/share_path:".$i);
			} else if($f_groupname!="NONE" && $f_groupname!="")
			{	/*GROUP*/
				/*echo "<script>alert(\"Add group for network access settings\")</script>";*/
				/* find the index of share_path (perhaps group already has other share_path) */
				$i = 1;		//index for "network_access/share_path" node
				$share_path= query("/nas/group:".$f_groupname."/network_access/share_path:".$i."/path");
				while($share_path != "")
				{
					$i++;
					$share_path= query("/nas/group:".$f_groupname."/network_access/share_path:".$i."/path");
				}
					
				//now $i is the correct index 
				anchor("/nas/group:".$f_groupname."/network_access/share_path:".$i);
			} else if($all_user=="ON")
			{	/*ALL*/
				/*echo "<script>alert(\"Add ALL ACCOUNT for network access settings\")</script>";*/
				$i = 1;		//index for "network_access/share_path" node
				$share_path = query("/nas/network_access_all_user/share_path:".$i."/path");
				while($share_path != "")
				{
					$i++;
					$share_path= query("/nas/network_access_all_user/share_path:".$i."/path");
				}
				anchor("/nas/network_access_all_user/share_path:".$i);
			}
			else if($allow_guest=="ON")
			{
				$i = 1;     //index for "network_access/share_path" node
				$share_path = query("/nas/network_access_allow_guest/share_path:".$i."/path");
				while($share_path != "")
				{
				  $i++;
					$share_path= query("/nas/network_access_allow_guest/share_path:".$i."/path");
				}
				anchor("/nas/network_access_allow_guest/share_path:".$i);
			} 
			else 
			{
				$save = "no";
			}
			
			if($save != "no")
			{
					if( query("path")!=$f_dir){$dirty++;	set("path" , $f_dir);set("folder" , $f_folder); set("device_name" , $f_device_name);}
					if( query("permission" )!= $read_only){$dirty++;set("permission" , $read_only);}
					if( query("oplocks" )!= $f_oplocks){$dirty++;set("oplocks" , $f_oplocks);}
					if( query("map_archive" )!= $f_maparchive){$dirty++;set("map_archive" , $f_maparchive);}
					if( query("comment" )!= $f_comment){$dirty++;set("comment" , $f_comment);}
					/*if( query("share" )!= $f_share){$dirty++;set("share" , $f_share);}*/
					if( query("share" )!= $f_share_name){$dirty++;set("share" , $f_share_name);}
					if ($dirty > 0)
						{$SUBMIT_STR=";submit NET_ACCESS_RELOAD";}
					else
						{$SUBMIT_STR="";}	
			}
				
		} /*end of ADD*/
		else if($ACTION_POST=="DELETE")
		{
				if($del_id!="")
				{
					/* delete user/group with index == del_id */
					if($del_type=="user")
					{
						/*echo "<script>alert(\"Deleting user".$del_id." with pathIndex ".$del_data_id."\")</script>";*/
					$dirty++;
						del("/nas/user:".$del_id."/network_access/share_path:".$del_data_id);	
						
					} else if($del_type=="group")
					{
						/*echo "<script>alert(\"Deleting group".$del_id."\")</script>";*/
					$dirty++;
						del("/nas/group:".$del_id."/network_access/share_path:".$del_data_id);	
					} else if($del_type=="ALL")
					{
						/*echo "<script>alert(\"Deleting ALL\")</script>";*/
					$dirty++;
						del("/nas/network_access_all_user/share_path:".$del_data_id);	
					}
					else if($del_type=="OPEN")
					{
						/*echo "<script>alert(\"Deleting ALL\")</script>";*/
					$dirty++;
						del("/nas/network_access_open_mode/share_path:".$del_data_id);	
					}
					else if($del_type=="GUEST")
					{
						/*echo "<script>alert(\"Deleting ALL\")</script>";*/
					$dirty++;
						del("/nas/network_access_allow_guest/share_path:".$del_data_id);	
					}
				}
				
				$SUBMIT_STR=";submit NET_ACCESS_RELOAD";
		} /*end of DELETE*/
		else if($ACTION_POST =="MODIFY")
		{
				if($modify_type == "user" || $modify_type == "group")
				{
					/* modify_type can be "user" or "group" */
					/*echo "<script>alert(\"Modify ".$modify_type." ".$modify_user_id." with data_index : ".$modify_data_id."\");</script>";*/
					anchor("/nas/".$modify_type.":".$modify_user_id."/network_access/share_path:".$modify_data_id);
				} 
				else //($modify_type == "network_access_all_user") || ($modify_type == "network_access_allow_guest")
				{
					/*echo "<script>alert(\"Modify ".$modify_type." with data_index : ".$modify_data_id."\")</script>";*/
					anchor("/nas/".$modify_type."/share_path:".$modify_data_id);
				}

				if( query("/nas/network_access/mode") != 2){$dirty++;set("/nas/network_access/mode","2");} //jana added
				if( query("path")!=$f_dir){$dirty++;	set("path" , $f_dir);set("folder" , $f_folder); set("device_name" , $f_device_name); }
				if( query("permission" )!= $read_only){$dirty++;set("permission" , $read_only);}
				if( query("oplocks" )!= $f_oplocks){$dirty++;set("oplocks" , $f_oplocks);}
				if( query("map_archive" )!= $f_maparchive){$dirty++;set("map_archive" , $f_maparchive);}
				if( query("comment" )!= $f_comment){$dirty++;set("comment" , $f_comment);}
				/*if( query("share" )!= $f_share){$dirty++;set("share" , $f_share);}*/
				if( query("share" )!= $f_share_name){$dirty++;set("share" , $f_share_name);}
				if ($dirty > 0)
					{$SUBMIT_STR=";submit NET_ACCESS_RELOAD";}
				else
					{$SUBMIT_STR="";}	
		}
	}
			
		/*save to db and to flash*/
		$NEXT_PAGE=$MY_NAME;
		if($dirty > 0 && $SUBMIT_STR!="")	{require($G_SAVING_URL);}
		else				{require($G_NO_CHANGED_URL);}	
}

$ipaddr= query("/lan/ethernet/ip");

/* --------------------------------------------------------------------------- */
require("/www/model/__html_head.php");
/* --------------------------------------------------------------------------- */
// get the variable value from rgdb.
require("/www/portal/comm/drag.php");
require("/www/portal/comm/overlay.php");
require("/www/portal/comm/event.php");
require("/www/portal/comm/scoot.php");
require("/www/portal/comm/fade.php");

$mode=query("/nas/network_access/mode");//jana added
if($mode=="") {$mode=1;}
/* --------------------------------------------------------------------------- */
?>

<script>
var original_name, original_path, original_share_name;

/* page init function */
function init()
{
<?
	$hvn_first=0;
	echo "g_share_array=[";
	for("/nas/network_access_all_user/share_path")
	{
		if($@!=1)	{echo ",";}
		echo "'".query("share")."'";
		$hvn_first++;
	}
	for ("/nas/user")
	{
		for("network_access/share_path")
		{
			if($hvn_first>0)	{echo ",";}
			echo "'".query("share")."'";
			$hvn_first++;
		}
	}
	for ("/nas/group")
	{
		for("network_access/share_path")
		{
			if($hvn_first>0)	{echo ",";}
			echo "'".query("share")."'";		
			$hvn_first++;
		}
	}
	for("/nas/network_access_allow_guest/share_path")
	{
		if($hvn_first>0)	{echo ",";}
		echo "'".query("share")."'";	
		$hvn_first++;	
	}
	echo "];";
?>

	<?
	echo "network_access_list_array=[";
	for("/nas/user")
	{
		$i = 1;		//index for "network_access/share_path" node			
		$temp_permission = query("/nas/user:".$@."/network_access/share_path:".$i."/permission");
		while($temp_permission != "")
		{
			echo "['".query("name")."',";	
			echo "'".get("j","/nas/user:".$@."/network_access/share_path:".$i."/path")."']";//jana modified	
			echo ",";	
			$i++;
			$temp_permission = query("/nas/user:".$@."/network_access/share_path:".$i."/permission");
		}
	}
	for("/nas/group")
	{
		$i = 1;		//index for "network_access/share_path" node			
		$temp_permission = query("/nas/group:".$@."/network_access/share_path:".$i."/permission");
		while($temp_permission != "")
		{
			echo "['".query("name")."',";	
			echo "'".get("j","/nas/group:".$@."/network_access/share_path:".$i."/path")."']";	//jana modified
			echo ",";	
			$i++;
			$temp_permission = query("/nas/group:".$@."/network_access/share_path:".$i."/permission");
		}
	}
	for ("/nas/network_access_all_user/share_path")
	{
		$temp_permission = query("/nas/network_access_all_user/share_path:".$@."/permission");
		if($temp_permission != "")
		{
			echo "['ALL',";	
			echo "'".get("j","/nas/network_access_all_user/share_path:".$@."/path")."']";	
			echo ",";	
		}
	}
	for ("/nas/network_access_allow_guest/share_path")
	{
		$temp_permission = query("/nas/network_access_allow_guest/share_path:".$@."/permission");
		if($temp_permission != "")
		{
			echo "['Public',";	
			echo "'".get("j","/nas/network_access_allow_guest/share_path:".$@."/path")."']";	
			echo ",";	
		}
	}
	
	echo "];\n";
	?>

	/* initialization for explorer.php */
	initOverlay("white");

	/* for user/group selection */
	showfield();
	/*document.form1.f_mode[0].checked;*/
		
	showfield_mode();
}

/* cancel function (accessed in "Don't Save Settings" button */
function do_cancel()
{
	self.location.href="<?=$MY_NAME?>.php?random_str="+generate_random_str();
}

function disable_mode()
{	
	document.form1.ACTION_POST.value = "DISABLE_MODE";
}

function open_mode()
{	
	document.form1.f_method[0].checked=true;
	document.form1.f_dir.value="/";
	document.form1.read_only.selectedIndex="1";
	document.form1.f_oplocks.selectedIndex="0";
	document.form1.f_maparchive.selectedIndex="0";
	document.form1.f_comment.value="OPEN MODE";
	document.form1.f_share.value="1";
	document.form1.all_user.checked=true;
	document.form1.user_list.selectedIndex="0";
	document.form1.user_list.disabled=true;
	document.form1.f_share_name.value="OPEN MODE";
	document.form1.ACTION_POST.value = "OPEN_MODE";
}
function security_mode()
{	
	document.form1.f_method[0].checked=true;
	document.form1.f_dir.value="";
	document.form1.read_only.selectedIndex="1";
	document.form1.f_oplocks.selectedIndex="0";
	document.form1.f_maparchive.selectedIndex="0";
	document.form1.f_comment.value="";
	document.form1.f_share.value="1";
	document.form1.all_user.checked=false;
	document.form1.allow_guest.checked=false;
	document.form1.user_list.selectedIndex="0";
	document.form1.user_list.disabled=false;
	document.form1.f_share_name.value="";
	document.form1.ACTION_POST.value = "ADD";
	document.form1.f_groupname.selectedIndex="0";//jana added
	document.form1.f_groupname.disabled=false;//jana added
}
function showfield_mode()
{
	
	if(document.form1.f_mode.selectedIndex == 0) //disable mode
	{
		document.getElementById("security_mode").style.display = "none";
		disable_mode();
	}
	else if(document.form1.f_mode.selectedIndex == 1) //open mode
	{
		document.getElementById("security_mode").style.display = "none";
		open_mode();
	}
	else //security mode
	{
		document.getElementById("security_mode").style.display = "";
		security_mode();
	}
}
function showfield()
{
	if(document.form1.f_method[1].checked)	//group
	{
		document.getElementById("chamber3").style.display = "";
		document.getElementById("chamber4").style.display = "none";
	}
	else
	{
		document.getElementById("chamber3").style.display = "none";
		document.getElementById("chamber4").style.display = "";
	}
}

function setuser()
{
	if (document.form1.all_user.checked)
	{
		//document.form1.guest_ok.value="yes";
		document.form1.user_list[0].selected=true;
		document.form1.user_list.disabled=true;
		document.form1.allow_guest.disabled=true;
	}
	else if( document.form1.allow_guest.checked)
	{
		document.form1.user_list[0].selected=true;
		document.form1.user_list.disabled=true;
		document.form1.all_user.disabled=true;
	}
	else
	{
		//document.form1.guest_ok.value="no";
		document.form1.user_list.disabled=false;
		document.form1.all_user.disabled=false;
		document.form1.allow_guest.disabled=false;
	}
}

function open_browser()
{
	/* call explorer.php */
	window_make_new(-1, -1, 500, 400, "/portal/explorer.php?path=/","Explorer");
}

function checkinput()
{
	document.form1.f_dir.value=""
	alert("<?=$a_not_select_folder?>");
}

function delpath2(type,name,path_index,user_index)
{
	//type:1 del user	2:del group		3:del ALL 4:del Open Mode
	//name:username
	//path_index:which data u want to delete
	var f=get_obj("form1");
	if (confirm("You are about to delete this entry."))
	{
		//alert(index);
		if(type == 1)
		{
			f.del_type.value = "user";
			f.del_id.value = user_index;
		}
		else if(type == 2)
		{
			f.del_type.value = "group";
			f.del_id.value = user_index;
		}
		else if(type == 3)
		{
			f.del_type.value = "ALL";
			f.del_id.value = "something";
		}
		else if(type == 4)
		{
			f.del_type.value = "OPEN";
			f.del_id.value = "something";
		}
		else if(type == 5)
		{
			f.del_type.value = "GUEST";
			f.del_id.value = "something";
		}
		f.del_data_id.value = path_index;
	}
	f.ACTION_POST.value = "DELETE";
	f.submit();
}

function hide(obj)
{
	get_obj(obj).style.display = "none";
}

function show(obj)
{
	get_obj(obj).style.display = "";		
}

function disable(obj)
{
	/*warning : MAKE SURE THAT obj has id (id="obj) */
	get_obj(obj).disabled = true;		
}

function enable(obj)
{
	get_obj(obj).disabled = false;		
}

function fillValues(type, user_index, path, comment, oplock, map, permission,share_name)
{
	var f=get_obj("form1");
	if(type == "1")
	{
		f.user_list.selectedIndex = user_index;
	}else if (type == "2")
	{
		f.f_groupname.selectedIndex = user_index;
	}
	
	select_index(f.read_only,permission);
	select_index(f.f_oplocks,oplock);
	select_index(f.f_maparchive,map);
	f.f_comment.value = comment;
	f.f_dir.value = path;
	f.f_share_name.value = share_name;
}

function ModifySession(type, user_index, path, comment, oplock, map, permission, data_index,share_name)
{
	var f=get_obj("form1");
	f.all_user.checked = false;
	f.allow_guest.checked = false;
			
	//type 1 user
	//type 2 group
	//type 3 network_access_all_user
	//type 4 guest account	
	switch (type)
	{
		case "1": /* user type */
			f.f_method[0].checked = true;
			showfield();
			fillValues(type, user_index, path, comment, oplock, map, permission,share_name);
			f.modify_type.value = "user";
			original_name=f.user_list.options[user_index].text;
			break;

		case "2": /* group type */
			f.f_method[1].checked = true;
			showfield();
			fillValues(type, user_index, path, comment, oplock, map, permission,share_name);
			f.modify_type.value = "group";
			original_name=f.f_groupname.options[user_index].text;
			break;
			
		case "3": /* all user type */
			f.f_method[0].checked = true;
			showfield();
			f.all_user.checked = true;
			fillValues(type, user_index, path, comment, oplock, map, permission,share_name);
			f.modify_type.value = "network_access_all_user";
			original_name="ALL";
			break;
			
		case "4": /* guest type */
			f.f_method[0].checked = true;
			showfield();
			f.allow_guest.checked = true;
			fillValues(type, user_index, path, comment, oplock, map, permission,share_name);
			f.modify_type.value = "network_access_allow_guest";
			original_name="Public";
			break;	
		default: 
			break;
	}
	f.f_method[0].disabled = true;
	f.f_method[1].disabled = true;
	disable("user_list");
	disable("all_user");
	disable("allow_guest");
			
	f.modify_user_id.value = user_index;
	f.modify_data_id.value = data_index;
	
	f.ACTION_POST.value = "MODIFY";

	original_path=f.f_dir.value;
	original_share_name=share_name;	
}

//+++jana
function check()
{
	if(document.form1.ACTION_POST.value == "DISABLE_MODE" || document.form1.ACTION_POST.value == "OPEN_MODE")
	{return true;}

	/*if only change mode, no add rule*/
	if( 
		document.form1.f_method[0].checked && 
		document.form1.f_dir.value=="" && 
		document.form1.read_only.selectedIndex==1 && 
		document.form1.f_oplocks.selectedIndex==0 && 
		document.form1.f_maparchive.selectedIndex==0 && 
		document.form1.f_comment.value=="" && 
		document.form1.f_share.value=="1" && 
		document.form1.all_user.checked==false && 
		document.form1.allow_guest.checked==false && 
		document.form1.user_list.selectedIndex==0 && 
		document.form1.f_share_name.value=="")
	{
		document.form1.ACTION_POST.value = "CHG_MODE";
		return true;;
	}
			
	if(!document.form1.all_user.checked && !document.form1.allow_guest.checked && document.form1.user_list.selectedIndex==0 
		&& document.form1.f_groupname.selectedIndex == 0)
	{
		alert("<?=$a_not_select_user_group?>");
		//field_focus(document.form1.user_list, "**");
		return false;
	}
	if(document.form1.f_share_name.value=="")
	{
		alert("<?=$a_not_enter_sharename?>");
		field_focus(document.form1.f_share_name, "**");
		return false;
	}
	if(is_include_special_chars(document.form1.f_share_name.value,"%&\|'*\\:\/?<\">]["))//jana modified
	{
		alert("<?=$a_invalid_enter_sharename?>");
		field_focus(document.form1.f_share_name, "**");		
		return false;		
	}		
		
	var x;
	document.form1.f_share_name.value=document.form1.f_share_name.value.toLowerCase();
	for (x in g_share_array)
	{
		if(document.form1.f_share_name.value == g_share_array[x])
		{
			if(document.form1.ACTION_POST.value == "MODIFY" && document.form1.f_share_name.value == original_share_name)
			{break;}
			alert("<?=$a_sharename_be_used?>");
			return false;
		}
	}
		
	if(document.form1.f_dir.value=="")
	{
		alert("<?=$a_not_select_folder?>");
		field_focus(document.form1.But_Browse, "**");
		return false;
	}
	if(is_include_special_chars(document.form1.f_comment.value,"%&'<\">"))
	{
		alert("<?=$a_invalid_enter_comment?>");
		field_focus(document.form1.f_comment, "**");		
		return false;		
	}	
	var path = document.form1.f_dir.value;
	var share = path.substring(path.lastIndexOf("/")+1);
	document.form1.f_share.value = share;
	
	/*check whether a duplicate rule*/
	var user_name;
	if(document.form1.all_user.checked) //All accounts
	{user_name="ALL";}
	else if(document.form1.allow_guest.checked) //Allow Guests
	{user_name="Public";}
	else if(document.form1.f_method[0].checked) //user
	{user_name=document.form1.user_list.options[document.form1.user_list.selectedIndex].text;}
	else //group
	{user_name=document.form1.f_groupname.options[document.form1.f_groupname.selectedIndex].text;}
	for (i in network_access_list_array)
		{	
			if(user_name == network_access_list_array[i][0] && document.form1.f_dir.value == network_access_list_array[i][1])
			{	
				if(document.form1.ACTION_POST.value == "MODIFY" && 
				user_name==original_name && document.form1.f_dir.value==original_path)
				{break;}
				alert("<?=$a_rule_existed?>");
				return false;
			}
		}
		
	/*+++ hendry*/
	/* separate the path to be : "path = device_name + folder"*/
	var str = document.form1.f_dir.value;
	var pos = str.indexOf('/');
	var token1 = str.substring(0,pos);
	var token2 = str.substring(pos+1,str.length);
	if (token2 == "")
		token2 = "/";
	
	if(token1=="")
	{
		document.form1.f_device_name.value = token2;
		document.form1.f_folder.value = "/";
	}else 
	{
		document.form1.f_device_name.value = token1;
		document.form1.f_folder.value = token2;
	}
	/*--- hendry*/
}
//---jana



</script>
<body onload="init();" <?=$G_BODY_ATTR?>>
<form name="form1" id="form1" method="post" action="<?=$MY_NAME?>.php" onsubmit="return check();";>

<input type="hidden" name="ACTION_POST"	value="ADD">
<input type="hidden" name="f_share" id="f_share">
<!-- we now use device_name and folder (f_device_name + f_folder = f_dir) -->
<input type="hidden" name="f_device_name" id="f_device_name">	
<input type="hidden" name="f_folder" id="f_folder">
<!-- for modify function -->
<input type="hidden" name="modify_user_id">
<input type="hidden" name="modify_data_id">
<input type="hidden" name="modify_type">
<!-- for delete function -->
<input type="hidden" name="del_type">
<input type="hidden" name="del_id">
<input type="hidden" name="del_data_id">

<!-- css for calling explorer.php -->
<link rel="stylesheet" href="/portal/comm/smbb.css" type="text/css"> 

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
		echo $G_APPLY_CANEL_BUTTON;
		?>
		</div>
<!-- ________________________________ Main Content Start ______________________________ -->
		<?$m_colon="&nbsp;:&nbsp;";?>
		<div class="box" id="open_mode">
			<!--jana removed <h2>Network Access Mode</h2> -->
			<h2><?=$m_mode_title?></h2><!--jana added-->
		<table border="0" cellpadding="0" cellspacing="0" style="border-collapse: collapse" bordercolor="#111111"  width="421">
			<tr>
				<td width="52" height="27"><?=$m_mode_name?></td>
				<td width="371" height="27">  
					<select size="1" name="f_mode" id="f_mode" onChange="showfield_mode()"> 
              <option value="0" <? if($mode == 0){echo "Selected";} ?>><?=$m_disable_mode?></option>
              <option value="1" <? if($mode == 1){echo "Selected";} ?>><?=$m_open_mode?></option>
              <option value="2" <? if($mode == 2){echo "Selected";} ?>><?=$m_security_mode?></option>
          </select>				
	      </td>
				
		<!--	<input type="button" name="But_Open" value="Open Mode" onclick="open_mode();">		-->
			</tr>		
		</table>
		</div>
		<div id="security_mode">
		<div class="box" >
			<h2><?=$m_1st_nw_access_title?></h2>

		
		<table border="0" cellpadding="0" cellspacing="0" style="border-collapse: collapse" bordercolor="#111111" id="setting_table" width="421">
		      
        <tr>
         
          <td width="76" height="27"><?=$m_category?></td>

          <td width="221" height="27">  
                  <input type="radio" name="f_method" id="f_method" value="1" onclick="showfield();" checked><?=$m_user?>  
                  <input type="radio" name="f_method" id="f_method" value="0" onclick="showfield();"><?=$m_group?></td>
                  
        </tr>
        
        <tr id="chamber3" style="display">
          <td width="76" height="27"><?=$m_group?></td>
          <td width="221" height="27">
          <!-- <select size="1" name="f_groupname" onchange="ShowGroupOfUser();"> jana removed -->
          <select size="1" name="f_groupname"> <!--jana added-->
          	<option value="NONE"><?=$a_not_select_group?></option>
<?
				for ("/nas/group")
				{
					echo "<option value=".$@;
					echo ">".get(h,"name")."</option>\n";
				}
?>
          </select>
          </td>
        </tr>

        <tr id="chamber4" style="display">
	        <td width="76" height="27"><?=$m_user?></td>
	        <td width="260" height="27">
	        <SELECT name=user_list id=user_list>
				<option value="NONE"><?=$a_not_select_user?></option>
<?
					for ("/nas/user")
					{
						echo "<option value=".$@;
						echo ">".query("name")."</option>\n";
					}
?>
			</SELECT>		
			<input type="checkbox" name="all_user" id="all_user" value="ON" onclick="setuser();"><?=$m_all_accounts?>
			<input type="checkbox" name="allow_guest" id="allow_guest" value="ON" onclick="setuser();"><?=$m_allow_guests?></td>
        </tr>

        <tr> <td width="76" height="27"><?=$m_share_name?></td> 
			<td width="221" height="1"> 
			<input type="text" name="f_share_name" size="16" maxlength="12" > 
		</td> </tr>		

        <tr>
          <td width="76" height="27"><?=$m_folder?></td>
          <td width="321" height="27">
            <input type="text" name="f_dir" id="f_dir" size=30 onclick="open_browser();" onkeyup="checkinput();">&nbsp;
            <input type="button" name="But_Browse" value="Browse" onclick="open_browser();"></td>
        </tr>   


        <tr>
          <td width="76" height="30"><?=$m_permission?></td>
          <td width="221" height="1">
            <select size="1" name="read_only"> <!-- jana modified-->
              <option value="0"><?=$m_read_only?></option>
              <option value="1"><?=$m_read_write?></option>
            </select>
          </td>
        </tr>
        
        <tr>
          <td width="76" height="30"><?=$m_oplocks?></td>
          <td width="221" height="1">
          <select size="1" name="f_oplocks">
	          <option value="yes"><?=$m_select_yes?></option>
    	      <option value="no"><?=$m_select_no?></option>
          </select></td>
        </tr>
        
        <tr>
          <td width="76" height="30"><?=$m_map_archive?></td>
          <td width="221" height="1">
          <select size="1" name="f_maparchive">
          <option value="yes"><?=$m_select_yes?></option>
          <option value="no"><?=$m_select_no?></option>
          </select></td>
        </tr>
        
        <tr>
          <td width="76" height="30"><?=$m_comment?></td>
          <td width="221" height="1">
          	<input type="text" name="f_comment" size="16" maxlength="50" >
          	</td>
        </tr>
        
        <tr>
          <td width="76">&nbsp;</td>
          <td width="221">&nbsp;</td>
        </tr>
       
      </table>
		</div>
	
	
	<div class="box">
	<h2><?=$m_2nd_nw_access_title?></h2>
	
	<table border="0" cellpadding="3" cellspacing="0" style="border-collapse: collapse" bordercolor="#C0C0C0" width="528">

        <tr>
   			 <td width="526" height="20" style="border-style: none; border-width: medium" colspan="8" align="right">
    			<img border="0" src="../pic/edit2.jpg">:<?=$m_read_write?>&nbsp; 
			    <img border="0" src="../pic/edit1.jpg">:<?=$m_read_only?>&nbsp; 
			    <img border="0" src="../pic/edit.jpg">: <?=$m_modify_setting?> 
			    <img border="0" src="../pic/release.gif">: <?=$m_delete?>
   			</td>
        </tr>
        <tr class="FSCol_Hdr" height="20">
		    <td width="80" align="left"><?=$m_share_name?></td>

		    <td width="165" align="left"><?=$m_list_folder?></td>
		    <td width="90" align="left"><?=$m_list_user_group?></td>
		    <td width="50" align="left"><?=$m_list_comment?></td>
		    <td width="55" align="center"><?=$m_list_oplocks?></td>
		    <td width="36" align="center"><?=$m_list_map?></td>
		    <td width="37" align="center"><?=$m_list_read_write?></td>
    		<td width="52" bgcolor="#B7DCFB" height="20">&nbsp;</td>
        </tr>
        
<?        	
        	for ("/nas/user")
			{
				/*echo "<script>alert(\"User ".$@."\")</script>";*/
				$i = 1;		//index for "network_access/share_path" node
				$temp_name = query("name");
				
				$temp_permission = query("/nas/user:".$@."/network_access/share_path:".$i."/permission");
				while($temp_permission != "")
				{
					/*echo "<script>alert(\"user ".$@."share path ".$i." is : ".$share_path."\")</script>";*/
					$temp_comment = query("/nas/user:".$@."/network_access/share_path:".$i."/comment");
					$temp_oplocks = query("/nas/user:".$@."/network_access/share_path:".$i."/oplocks");
					$temp_map_archive = query("/nas/user:".$@."/network_access/share_path:".$i."/map_archive");
					$temp_share= query("/nas/user:".$@."/network_access/share_path:".$i."/share");	
					//$temp_share_dir = query("/nas/user:".$@."/network_access/share_path:".$i."/share_web"); 
					//$temp_path = query("/nas/user:".$@."/network_access/share_path:".$i."/path");//jana removed
					$temp_path = get("j","/nas/user:".$@."/network_access/share_path:".$i."/path");//jana added
					$temp_folder = get("j","/nas/user:".$@."/network_access/share_path:".$i."/path");//jana added
					$temp_devname = get("j","/nas/user:".$@."/network_access/share_path:".$i."/device_name");//hendry add

					if($temp_permission == "0")
					{
						$temp_pic = "../pic/edit1.jpg";
					}
					else
					{
						$temp_pic = "../pic/edit2.jpg";
					}
					
					echo "<TR>\n";
					/*echo "<td id=\'0str1\' style=\'word-break: break-all\' height=\"20\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\"><a href=".$temp_share_dir."/>Browse</td>";\n*/
					echo "<td id=\'0str1\' style=\'word-break: break-all\' height=\"20\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\" NOWRAP>".$temp_share."</td>\n";					
					echo "<td id=\'0str2\' style=\'word-break: break-all\' width=\"149\" height=\"20\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\">".$temp_path."</td>\n";
					echo "<td id=\'0str3\' style=\'word-break: break-all\' width=\"79\" height=\"20\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\">".$temp_name."</td>\n";
					echo "<td id=\'0str4\' style=\'word-break: break-all\' width=\"138\" height=\"20\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\"><pre>".$temp_comment."</pre></td>\n";	//hendry modify : add <pre> to fix whitespaces
					
					echo "<td style='word-break: break-all' width=\"28\" height=\"20\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\" valign=\"top\"><p align=\"center\">".$temp_oplocks."</td>\n";
					echo "<td style='word-break: break-all' width=\"28\" height=\"20\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\" valign=\"top\"><p align=\"center\">".$temp_map_archive."</td>\n";
					echo "<td style='word-break: break-all' width=\"28\" height=\"20\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\" valign=\"top\"><p align=\"center\">\n";
					echo "<img border=\"0\" src=\"".$temp_pic."\" width=\"15\" height=\"17\"></td><td style='word-break: break-all' width=\"38\" height=\"20\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\" valign=\"top\" NOWRAP><p align=\"left\">\n";
//					echo "<a href=\"javascript:ModifySession('1','".$@."','".$temp_path."','".$temp_comment."','".$temp_oplocks."','".$temp_map_archive."','".$temp_permission."','".$i."','".$temp_share."');\">\n";
//					echo "<img border=\"0\" src=\"../pic/edit.jpg\" width=\"15\" height=\"17\"></a>\n";

					echo "<a href=\"javascript:void(0)\">\n";
					echo "<img border=\"0\" src=\"../pic/edit.jpg\" width=\"15\" height=\"17\"  onclick=\"ModifySession('1','".$@."','".$temp_path."','".$temp_comment."','".$temp_oplocks."','".$temp_map_archive."','".$temp_permission."','".$i."','".$temp_share."');\"></a>\n";
					
					echo "<a href=\"javascript:delpath2('1','".$temp_name."','".$i."','".$@."');\">\n";
					echo "<img border=\"0\" src=\"../pic/release.gif\" width=\"15\" height=\"18\"></a></td>\n";								
					
					echo "</TR>\n";
					$i++;
					$temp_permission = query("/nas/user:".$@."/network_access/share_path:".$i."/permission");
				}
			}
?>

<?        	
        	for ("/nas/group")
			{
				/*echo "<script>alert(\"User ".$@."\")</script>";*/
				$i = 1;		//index for "network_access/share_path" node
				$temp_name = query("name");
				
				$temp_permission = query("/nas/group:".$@."/network_access/share_path:".$i."/permission");
				while($temp_permission != "")
				{
					/*echo "<script>alert(\"user ".$@."share path ".$i." is : ".$share_path."\")</script>";*/
					$temp_comment = query("/nas/group:".$@."/network_access/share_path:".$i."/comment");
					$temp_oplocks = query("/nas/group:".$@."/network_access/share_path:".$i."/oplocks");
					$temp_map_archive = query("/nas/group:".$@."/network_access/share_path:".$i."/map_archive");
					$temp_share= query("/nas/group:".$@."/network_access/share_path:".$i."/share");
					//$temp_share_dir = query("/nas/group:".$@."/network_access/share_path:".$i."/share_web"); 
					//$temp_path = query("/nas/group:".$@."/network_access/share_path:".$i."/path");//jana removed
					$temp_path = get("j","/nas/group:".$@."/network_access/share_path:".$i."/path");//jana added
					
					//$temp_share_dir = "\\\\".$ipaddr."\\".$temp_share_dir;
					if($temp_permission == "0")
					{
						$temp_pic = "../pic/edit1.jpg";
					}
					else
					{
						$temp_pic = "../pic/edit2.jpg";
					}
					
					echo "<TR>\n";
					echo "<td id=\'0str1\' style=\'word-break: break-all\' height=\"20\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\" NOWRAP>".$temp_share."</td>\n";					
					echo "<td id=\'0str2\' style=\'word-break: break-all\' width=\"149\" height=\"20\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\">".$temp_path."</td>\n";
					echo "<td id=\'0str3\' style=\'word-break: break-all\' width=\"79\" height=\"20\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\">".$temp_name."</td>\n";
					echo "<td id=\'0str4\' style=\'word-break: break-all\' width=\"138\" height=\"20\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\"><pre>".$temp_comment."</pre></td>\n";
					
					echo "<td style='word-break: break-all' width=\"28\" height=\"20\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\" valign=\"top\"><p align=\"center\">".$temp_oplocks."</td>\n";
					echo "<td style='word-break: break-all' width=\"28\" height=\"20\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\" valign=\"top\"><p align=\"center\">".$temp_map_archive."</td>\n";
					echo "<td style='word-break: break-all' width=\"28\" height=\"20\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\" valign=\"top\"><p align=\"center\">\n";
					echo "<img border=\"0\" src=\"".$temp_pic."\" width=\"15\" height=\"17\"></td><td style='word-break: break-all' width=\"38\" height=\"20\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\" valign=\"top\" NOWRAP><p align=\"left\">\n";
//					echo "<a href=\"javascript:ModifySession('2','".$@."','".$temp_path."','".$temp_comment."','".$temp_oplocks."','".$temp_map_archive."','".$temp_permission."','".$i."','".$temp_share."');\">\n";
//					echo "<img border=\"0\" src=\"../pic/edit.jpg\" width=\"15\" height=\"17\"></a>\n";

					echo "<a href=\"javascript:void(0)\">\n";
					echo "<img border=\"0\" src=\"../pic/edit.jpg\" width=\"15\" height=\"17\"  onclick=\"ModifySession('2','".$@."','".$temp_path."','".$temp_comment."','".$temp_oplocks."','".$temp_map_archive."','".$temp_permission."','".$i."','".$temp_share."');\"></a>\n";

					echo "<a href=\"javascript:delpath2('2','".$temp_name."','".$i."','".$@."');\">\n";
					echo "<img border=\"0\" src=\"../pic/release.gif\" width=\"15\" height=\"18\"></a></td>\n";								
					
					echo "</TR>\n";
					$i++;
					$temp_permission = query("/nas/group:".$@."/network_access/share_path:".$i."/permission");
				}
			}
?>	

<?        	
        	for ("/nas/network_access_all_user/share_path")
			{
				/*echo "<script>alert(\"User ".$@."\")</script>";*/
				$temp_name = "ALL";
				$temp_path = get("j","/nas/network_access_all_user/share_path:".$@."/path");
				$temp_comment = query("/nas/network_access_all_user/share_path:".$@."/comment");
				$temp_oplocks = query("/nas/network_access_all_user/share_path:".$@."/oplocks");
				$temp_map_archive = query("/nas/network_access_all_user/share_path:".$@."/map_archive");
				$temp_permission = query("/nas/network_access_all_user/share_path:".$@."/permission");
				$temp_share = query("/nas/network_access_all_user/share_path:".$@."/share");
				//$temp_share_dir = query("/nas/network_access_all_user/share_path:".$@."/share_web");
					
				//$temp_share_dir = "\\\\".$ipaddr."\\".$temp_share_dir;	
				if($temp_permission == "0")
				{
					$temp_pic = "../pic/edit1.jpg";
				}
				else
				{
					$temp_pic = "../pic/edit2.jpg";
				}
					
				echo "<TR>\n";
				echo "<td id=\'0str1\' style=\'word-break: break-all\' height=\"20\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\" NOWRAP>".$temp_share."</td>\n";					
				echo "<td id=\'0str2\' style=\'word-break: break-all\' width=\"149\" height=\"20\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\">".$temp_path."</td>\n";
				echo "<td id=\'0str3\' style=\'word-break: break-all\' width=\"79\" height=\"20\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\">".$temp_name."</td>\n";
				echo "<td id=\'0str4\' style=\'word-break: break-all\' width=\"138\" height=\"20\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\"><pre>".$temp_comment."</pre></td>\n";
				
				echo "<td style='word-break: break-all' width=\"28\" height=\"20\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\" valign=\"top\"><p align=\"center\">".$temp_oplocks."</td>\n";
				echo "<td style='word-break: break-all' width=\"28\" height=\"20\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\" valign=\"top\"><p align=\"center\">".$temp_map_archive."</td>\n";
				echo "<td style='word-break: break-all' width=\"28\" height=\"20\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\" valign=\"top\"><p align=\"center\">\n";
				echo "<img border=\"0\" src=\"".$temp_pic."\" width=\"15\" height=\"17\"></td><td style='word-break: break-all' width=\"38\" height=\"20\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\" valign=\"top\" NOWRAP><p align=\"left\">\n";
//				echo "<a href=\"javascript:ModifySession('3','NULL','".$temp_path."','".$temp_comment."','".$temp_oplocks."','".$temp_map_archive."','".$temp_permission."','".$@."','".$temp_share."');\">\n";
//				echo "<img border=\"0\" src=\"../pic/edit.jpg\" width=\"15\" height=\"17\"></a>\n";

				echo "<a href=\"javascript:void(0)\">\n";
				echo "<img border=\"0\" src=\"../pic/edit.jpg\" width=\"15\" height=\"17\"  onclick=\"ModifySession('3','".$@."','".$temp_path."','".$temp_comment."','".$temp_oplocks."','".$temp_map_archive."','".$temp_permission."','".$@."','".$temp_share."');\"></a>\n";//jana modified

				echo "<a href=\"javascript:delpath2('3','".$temp_name."','".$@."','0');\">\n";
				echo "<img border=\"0\" src=\"../pic/release.gif\" width=\"15\" height=\"18\"></a></td>\n";								
				echo "</TR>\n";
			}
?>	
<?        	
        	for ("/nas/network_access_allow_guest/share_path")
			{
				/*echo "<script>alert(\"User ".$@."\")</script>";*/
				$temp_name = "Public";
				$temp_path = get("j","/nas/network_access_allow_guest/share_path:".$@."/path");
				$temp_comment = query("/nas/network_access_allow_guest/share_path:".$@."/comment");
				$temp_oplocks = query("/nas/network_access_allow_guest/share_path:".$@."/oplocks");
				$temp_map_archive = query("/nas/network_access_allow_guest/share_path:".$@."/map_archive");
				$temp_permission = query("/nas/network_access_allow_guest/share_path:".$@."/permission");
				$temp_share = query("/nas/network_access_allow_guest/share_path:".$@."/share");
				//$temp_share_dir = query("/nas/network_access_allow_guest/share_path:".$@."/share_web");
					
				//$temp_share_dir = "\\\\".$ipaddr."\\".$temp_share_dir;	
				if($temp_permission == "0")
				{
					$temp_pic = "../pic/edit1.jpg";
				}
				else
				{
					$temp_pic = "../pic/edit2.jpg";
				}

				echo "<TR>\n";
				echo "<td id=\'0str1\' style=\'word-break: break-all\' height=\"20\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\" NOWRAP>".$temp_share."</td>\n";//jana modified					
				echo "<td id=\'0str2\' style=\'word-break: break-all\' width=\"149\" height=\"20\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\">".$temp_path."</td>\n";
				echo "<td id=\'0str3\' style=\'word-break: break-all\' width=\"79\" height=\"20\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\">".$temp_name."</td>\n";
				echo "<td id=\'0str4\' style=\'word-break: break-all\' width=\"138\" height=\"20\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\"><pre>".$temp_comment."</pre></td>\n";
				
				echo "<td style='word-break: break-all' width=\"28\" height=\"20\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\" valign=\"top\"><p align=\"center\">".$temp_oplocks."</td>\n";
				echo "<td style='word-break: break-all' width=\"28\" height=\"20\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\" valign=\"top\"><p align=\"center\">".$temp_map_archive."</td>\n";
				echo "<td style='word-break: break-all' width=\"28\" height=\"20\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\" valign=\"top\"><p align=\"center\">\n";
				echo "<img border=\"0\" src=\"".$temp_pic."\" width=\"15\" height=\"17\"></td><td style='word-break: break-all' width=\"38\" height=\"20\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\" valign=\"top\" NOWRAP><p align=\"left\">\n";
//				echo "<a href=\"javascript:ModifySession('4','NULL','".$temp_path."','".$temp_comment."','".$temp_oplocks."','".$temp_map_archive."','".$temp_permission."','".$@."','".$temp_share."');\">";
//				echo "<img border=\"0\" src=\"../pic/edit.jpg\" width=\"15\" height=\"17\"></a>\n";

				echo "<a href=\"javascript:void(0)\">\n";
				echo "<img border=\"0\" src=\"../pic/edit.jpg\" width=\"15\" height=\"17\"  onclick=\"ModifySession('4','".$@."','".$temp_path."','".$temp_comment."','".$temp_oplocks."','".$temp_map_archive."','".$temp_permission."','".$@."','".$temp_share."');\"></a>\n";//jana modified
	
				echo "<a href=\"javascript:delpath2('5','".$temp_name."','".$@."','0');\">\n";
				echo "<img border=\"0\" src=\"../pic/release.gif\" width=\"15\" height=\"18\"></a></td>\n";								
				echo "</TR>\n";
			}
?>	
      </table>
      </div>
    </div>
      </td>
      <td <?=$G_HELP_TABLE_ATTR?>><?require($LOCALE_PATH."/help/h_".$MY_NAME.".php");?></td>
</tr>
</table>
<?require("/www/model/__tailer.php");?>
</form>
</body>
</html>

