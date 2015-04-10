<?
/* vi: set sw=4 ts=4: ---------------------------------------------------------*/
$MY_NAME		="nas_ftp";
$MY_MSG_FILE	=$MY_NAME.".php";
$CATEGORY		="nas";
/* --------------------------------------------------------------------------- */

if ($ACTION_POST!="")
{
	require("/www/model/__admin_check.php");
	if($ACTION_POST=="ADD")
	{
		/* if root path is selected, let it be blank */
		if($f_root=="ON") {$f_dir = "";}
		
		/* add user/group/anonymous settings if filled */
		if($user_list=="anonymous")
		{	
			$dirty++;	
			set("/nas/ftp/path" , $f_dir);
			set("/nas/ftp/permission" , $read_write);
		} 
		if($user_list!="NONE" && $user_list!="" && $user_list!="anonymous")
		{
			/*check if user belong to a group, check if the group 
			has ftp setting that overrides user setting*/
			$i = 1;
			$tmp_in_group = query("/nas/user:".$user_list."/group"); 
			
			for("/nas/group")
			{	/* find group */
				if($tmp_in_group == query("name"))
				{
					/* check if group has ftp setting */
					if(query("ftp/permission") != "")
					{
						$user_settings_is_overriden = "yes";	
					}
				}	
			}
			
			if($user_settings_is_overriden == "yes")
			{
				echo "<script>alert(\"$a_invalid_modify\")</script>";
			//	echo "<script>alert(\"Can't modify. User is a member of a group that already have ftp settings\")</script>";
			}
			else
			{
				$dirty++;
				set("/nas/user:".$user_list."/ftp/path" , $f_dir);
				set("/nas/user:".$user_list."/ftp/permission" , $read_write);	
			}
		}
		if($f_groupname!="NONE" && $f_groupname!="")
		{
			$dirty++;
			set("/nas/group:".$f_groupname."/ftp/path" , $f_dir);
			set("/nas/group:".$f_groupname."/ftp/permission" , $read_write);
			
			/* update the path of all members in the group */
			$tmp_group_name = query("/nas/group:".$f_groupname."/name");
			for("/nas/user")
			{
				$tmp_in_group = query("group");
				if($tmp_in_group == $tmp_group_name)
				{	
					$dirty++;				
					/*if user is a member of the group, update the user's path */
					set("ftp/path" , $f_dir);
					set("ftp/permission" , $read_write);
				}
			}
		}
		if($all_user=="ON" && $all_user!="")
		{
			/* modify all users settings */
			for ("/nas/user")
			{
				$dirty++;			
				set("/nas/user:".$@."/ftp/path" , $f_dir);
				set("/nas/user:".$@."/ftp/permission" , $read_write);
			}
		}
	} /*end of ADD*/
	else if($ACTION_POST == "DELETE")
	{
		if($del_id!="")
		{
			require("/www/model/__admin_check.php");
			
			/* delete user/group with index == del_id */
			if($del_type=="user")
			{
				$dirty++;
				del("/nas/user:".$del_id."/ftp");	
			} else if($del_type=="group")
			{
				$dirty++;
				del("/nas/group:".$del_id."/ftp");	
				
				//+++jana
				$tmp_group_name = query("/nas/group:".$del_id."/name");
				for("/nas/user")
				{			
					$tmp_in_group = query("group");
					if($tmp_in_group == $tmp_group_name)
					{	
						$dirty++;
						/*if user is a member of the group, remove the user's path */
						del("/ftp");
					}
				}			
			 	//---jana
				
				
			} else if($del_type=="anonymous")
			{
				$dirty++;
				del("/nas/ftp/path");	
				del("/nas/ftp/permission");	
			}
		}
	} /*end of DELETE*/
	else if($ACTION_POST =="MODIFY")
	{
		require("/www/model/__admin_check.php");
		if($f_root=="ON") {$f_dir = "";}
		
		
		if($modify_type == "anonymous")
		{
			if(query("/nas/ftp/path")!=$f_dir)				{$dirty++;set("/nas/ftp/path" , $f_dir);}
			if(query("/nas/ftp/permission")!=$read_write) 	{$dirty++;set("/nas/ftp/permission" , $read_write);}
		}else
		{
			if(query("/nas/".$modify_type.":".$modify_user_id."/ftp/path")!=$f_dir)				{$dirty++;set("/nas/".$modify_type.":".$modify_user_id."/ftp/path" , $f_dir);}
			if(query("/nas/".$modify_type.":".$modify_user_id."/ftp/permission")!=$read_write)	{$dirty++;set("/nas/".$modify_type.":".$modify_user_id."/ftp/permission" , $read_write);}
		}
		
		/*for group modify, also update all the members ftp path */
		/* update the path of all members in the group */
		if($modify_type == "group")
		{
			$tmp_group_name = query("/nas/group:".$modify_user_id."/name");
			for("/nas/user")
			{
				$tmp_in_group = query("group");
				if($tmp_in_group == $tmp_group_name)
				{	
					/*if user is a member of the group, update the user's path */
					if(query("/nas/ftp/path")!=$f_dir)				{$dirty++;set("ftp/path" , $f_dir);}
					if(query("/nas/ftp/permission")!=$read_write) 	{$dirty++;set("ftp/permission" , $read_write);}
				}
			}
		}	
	} /*end of MODIFY*/
/*	else if($ACTION_POST=="ENABLE_DISABLE_FTP")
	{
		anchor("/nas/ftp");
		if($enable_ftp=="1")
		{
			set("enable","1");
			$SUBMIT_STR=";submit PURE-FTPD";
		}
		else
		{
			set("enable","0");
			$SUBMIT_STR=";submit PURE-FTPD_STOP";
		}
		$NEXT_PAGE=$MY_NAME;
		if($SUBMIT_STR!="")	{require($G_SAVING_URL);}
		else				{require($G_NO_CHANGED_URL);}
		
		/*warning.., when ftp start or stop, it doesn't save the general settings !!! 
		  (it doesn't continue to execute below codes) 
	}*/
	
	/* save general settings for ftp */
	anchor("/nas/ftp");
	
	$flow=query("flow_control");
	if($flow==0){$flow="";}
	
	if($flow!=$f_flow_k)
	{
		if($f_flow_k=="")	/* means unlimited selected */
		{
			$dirty++;
			set("flow_control", 0);	
		}else
		{
			$dirty++;
			set("flow_control", $f_flow_k);	
		}
	}
	/*echo "<script>alert(\"Enter 1 here\")</script>";
	echo "<script>alert(\"f_maxuser : ".$f_maxuser." idle_time : ".$f_idle_time." port :".$f_port." language :".$f_client_char."\")</script>";*/
	if(query("/nas/ftp/max_user")!=$f_maxuser) 		{$dirty++; set("/nas/ftp/max_user", $f_maxuser);}
	if(query("/nas/ftp/idle_time")!=$f_idle_time) 	{$dirty++; set("/nas/ftp/idle_time", $f_idle_time);}
	if(query("/nas/ftp/port")!=$f_port) 			{$dirty++; set("/nas/ftp/port", $f_port);}
	if(query("/nas/ftp/language")!=$f_client_char) 	{$dirty++; set("/nas/ftp/language", $f_client_char);}
	if(query("/nas/ftp/mode")!=$f_mode) 			{$dirty++; set("/nas/ftp/mode", $f_mode);}
	
	$ftp_enable=query("enable");
	if($ftp_enable!=$f_start)
	{
		if($f_start=="1")
		{
			$dirty++;
			set("enable","1");
		}
		else
		{
			$dirty++;
			set("enable","2");
		}
	}

	if($f_start=="1")
	{
		$SUBMIT_STR=";submit PURE-FTPD";
	}
	else
	{
		$SUBMIT_STR=";submit PURE-FTPD_STOP";
	}

/*	echo "<script>alert(\"dirty: ".$dirty."  SUBMIT_STR: ".$SUBMIT_STR."\")</script>";
*/
	$NEXT_PAGE=$MY_NAME;	
	if($dirty >0 && $SUBMIT_STR!="")	{require($G_SAVING_URL);}
	else				{require($G_NO_CHANGED_URL);}
}

/* get data for FTP	SERVER STATUS in 3rd title */
anchor("/nas/ftp");
$ftp_port 				= query("port");		if($ftp_port == "") {$ftp_port = "21";}
$ftp_max_user 			= query("max_user");	if($ftp_max_user == "") {$ftp_max_user = "10";}
$ftp_flow_control 		= "";
$ftp_idle_time 			= query("idle_time");	if($ftp_idle_time == "") {$ftp_idle_time = "5";}
$ftp_status				= "";
$ftp_toogle_button		= "";
$ftp_language			= "";
$ftp_flow_control_val 	= "";
$ftp_mode 				= query("mode");if($ftp_mode==""){$ftp_mode="1";}if($ftp_mode == "1") {$ftp_mode = "LAN";}else if ($ftp_mode == "2") {$ftp_mode = "Internet/WAN";}else{$ftp_mode = "LAN + Internet/WAN";}
if(query("enable")=="1")
{
	$ftp_status="Started";
	$ftp_toogle_button="Stop FTP Server";
}else
{
	$ftp_status="Stopped";
	$ftp_toogle_button="Start FTP Server";
}
$enable_disable=query("/nas/ftp/enable");
if($enable_disable=="")
	{$enable_disable="0";}
$lan_or_wan=query("/nas/ftp/mode");
if($lan_or_wan=="")
	{$lan_or_wan="1";}
$ftp_flow_control_val = query("flow_control");	if($ftp_flow_control_val == "") {$ftp_flow_control_val = "0";}
if( $ftp_flow_control_val == "0")
{
	$ftp_flow_control = "Unlimited";
}else
{
	$ftp_flow_control = query("/nas/ftp/flow_control")."0 KBps";
}

$ftp_language_value = query("language");
if($ftp_language_value == "ISO8859-1") {	$ftp_language = "Western European" ; } 		else
if($ftp_language_value == "ISO8859-10")     {	$ftp_language = "Northern European" ; } 	else
if($ftp_language_value == "cp1250")    {	$ftp_language = "Central European" ; } 		else
if($ftp_language_value == "big5")      {	$ftp_language = "Traditional Chinese" ; } 	else
if($ftp_language_value == "gb2312")    {	$ftp_language = "Simplified Chinese" ; } 	else
if($ftp_language_value == "cp1251")    {	$ftp_language = "Cyrillic" ; } 				else 
{$ftp_language = "Unknown language" ; } /*default*/


/* --------------------------------------------------------------------------- */
require("/www/model/__html_head.php");
require("/www/portal/comm/drag.php");
require("/www/portal/comm/overlay.php");
require("/www/portal/comm/event.php");
require("/www/portal/comm/scoot.php");
require("/www/portal/comm/fade.php");
/* --------------------------------------------------------------------------- */
?>


<script>

/* page init function */
function init()
{
	//+++jana
	<?
	echo "ftp_access_list_array=[";
	for("/nas/group")
	{
		$temp_permission = query("/nas/group:".$@."/ftp/permission");
		if($temp_permission != "")
		{
			echo "'".query("name")."'";	
			echo ",";	
		}
	}


	/* for anonymous setting */
	$temp_permission = query("/nas/ftp/permission");
	if($temp_permission!="")
	{
		echo "'Anonymous',";
	}	
	
	for("/nas/user")
	{
		$temp_permission = query("/nas/user:".$@."/ftp/permission");
		if($temp_permission != "")
		{
			echo "'".query("name")."'";	
			echo ",";	
		}
	}
	echo "];\n";
	?>
	//---jana
		
	/* initialization for explorer.php */
	initOverlay("white");
	
	var f=get_obj("frm");
	
	/* for user/group selection */
	showfield();	
	
	/* flow control initialization */
	if(<?=$ftp_flow_control_val?> == "0")
	{	
		document.frm.f_flow[0].checked = true;
	} else
	{
		document.frm.f_flow[1].checked = true;	
		document.frm.f_flow_k.value=<?=$ftp_flow_control_val?>;
	}
	if(<?=$enable_disable?> == "1")
	{	
		document.frm.f_start[0].checked = true;
	} else
	{
		document.frm.f_start[1].checked = true;			
	}
	
	if(<?=$lan_or_wan?> == "1")
	{	
		document.frm.f_mode[0].checked = true;
	}
	else if(<?=$lan_or_wan?> == "2")
	{	
		document.frm.f_mode[1].checked = true;
	}  
	else
	{
		document.frm.f_mode[2].checked = true;			
	}
	
	change();
	
	/* language initialization */
	select_index(f.f_client_char, "<?=$ftp_language_value?>");
	
	/* max user initialization */
	select_index(f.f_maxuser, "<?=$ftp_max_user?>");
	
	/* idle time initialization */
	document.frm.f_idle_time.value = "<?=$ftp_idle_time?>";

	/* port initialization */
	document.frm.f_port.value = <?=$ftp_port?>;
	
	document.frm.modify_type.value="";//jana added
}

/* cancel function */
function do_cancel()
{
	self.location.href="<?=$MY_NAME?>.php?random_str="+generate_random_str();
}

function showfield()
{
	var f = document.getElementById("frm");
	var user_select_row = document.getElementById("user_select");
	var group_select_row = document.getElementById("group_select");
	
	if(f.f_method[0].checked) 
	{
		/* select user */
		user_select_row.style.display = "";
		group_select_row.style.display = "none";
	}
	else
	{
		/* select group */
		user_select_row.style.display = "none";
		group_select_row.style.display = "";
	}
}

function setuser()
{
	if (document.frm.all_user.checked)
	{
		document.frm.user_list[0].selected=true;
		document.frm.user_list.disabled=true;
	}
	else
	{
		document.frm.user_list.disabled=false;
	}
}

function check_path(clear)
{
	if (document.frm.f_root.checked || clear==1)
	{
		document.frm.read_write.disabled=false
		document.getElementById("chamber2").style.display = "none";
	}
	else
	{
		if (document.frm.f_device_read_write.value=="0") //device is ntfs
		{
			document.frm.read_write.disabled=true
		}
		document.getElementById("chamber2").style.display = "";
	}
}

function open_browser()
{
	//alert(get_obj("sharing_dir").value);
	window_make_new(-1, -1, 500, 400, "/portal/explorer.php?path=/","Explorer");
	//enableOverlay();
}


function checkinput()
{
	if(document.frm.f_dir.value="")
		alert("<?=$a_not_select_folder?>");
		//alert("A folder must be selected.");	
}

function AddPath()
{	
	
	if (!document.frm.f_root.checked)
	{
		if (document.frm.f_dir.value=="")
		{
			alert("<?=$a_not_select_folder?>");
			//alert("A folder must be selected.");
			return;
		}
	}
	
	if(document.frm.f_method[0].checked)	//user
	{
		if (document.frm.all_user.checked==true)
		{
			document.add_path.f_username.value="alluser";
		}
		else
		{
			if (document.frm.user_list[0].selected)
			{
				alert("<?=$a_not_select_user?>");
				//alert("Please select an user.")
				return;
			}
			else
			{
				document.add_path.f_username.value=document.frm.user_list.value;
			}
		}
		document.add_path.f_type.value='0';
	}
	else		//group
	{
		if(document.frm.f_groupname[0].selected)
		{
				alert("<?=$a_not_select_group?>");		
				//alert("Please select a group.")
				return;
		}
		document.add_path.f_type.value='1';

		name=document.frm.f_groupname.value
	
		tmp=name.split(",");
		user=tmp[0];
		group=tmp[1];
		if(user=="NONE")
		{
			alert("<?=$a_invalid_user?>");	
			//alert("There is no user in this group.");
			return;
		}
		document.add_path.f_username.value=group;
		//document.add_path.f_username.value=document.frm.f_groupname.value;
	}
	
	document.add_path.f_read_write.value=document.frm.f_read_write.value;
	if (document.frm.f_root.checked)
	{
		document.add_path.f_path.value="/ftp_server";
	}
	else
	{
		document.add_path.f_path.value=document.frm.f_dir.value;
	}
	document.add_path.submit();
}

function check()
{

	//port
	if (document.frm.f_port.value=="")
	{
		alert("<?=$a_not_enter_port?>");	
		//alert("Please enter a port.");
		document.frm.f_port.select();
		document.frm.f_port.focus();
		return false;
	}
	
	if (document.frm.f_port.value.indexOf(" ") != -1) 
 	{
 		alert("<?=$a_port_contain_space?>");	
 		//alert("Port can not contain spaces");
 		document.frm.f_port.select();
		document.frm.f_port.focus();
 		return false;
 	}
	
 	if (isNaN(document.frm.f_port.value))
 	{
 		alert("<?=$a_port_not_number?>");	
		//alert("Port must be a number.");
 		document.frm.f_port.select();
		document.frm.f_port.focus();
		return false;
 	}	

	if (document.frm.f_port.value<=0 | document.frm.f_port.value>65535)
	{
		alert("<?=$a_port_out_range?>");	
		//alert("The port number must be between 1~65535.");
		document.frm.f_port.select();
		document.frm.f_port.focus();
		return false;
	}
	
  //+++jana
	if (document.frm.f_port.value.indexOf(".") > -1)
	{
		alert("<?=$a_port_not_integer?>");	
		//alert("The port number must be an integer.");
		document.frm.f_port.select();
		document.frm.f_port.focus();
		return false;
	}
	//---jana
	
	//flow
	if (document.frm.f_flow[1].checked==true)
	{
		if (document.frm.f_flow_k.value=="")
		{
			alert("<?=$a_not_enter_flow?>");
			//alert("Please enter a Flow.");
			document.frm.f_flow_k.select();
			document.frm.f_flow_k.focus();
			return false;
		}

		if (document.frm.f_flow_k.value.indexOf(".") != -1) 
 		{
 			alert("<?=$a_flow_contain_decimal_point?>");
 			//alert("Flow can not contain decimal point.");
 			document.frm.f_flow_k.select();
			document.frm.f_flow_k.focus();
 			return false;
 		}
		
		if (document.frm.f_flow_k.value.indexOf(" ") != -1) 
 		{
 			alert("<?=$a_flow_contain_space?>");	
 			//alert("Flow can not contain space");
 			document.frm.f_flow_k.select();
			document.frm.f_flow_k.focus();
 			return false;
 		}
 			
 		if (isNaN(document.frm.f_flow_k.value))
 		{
 			alert("<?=$a_flow_not_number?>");	
			//alert("Flow control must be a number.");
 			document.frm.f_flow_k.select();
			document.frm.f_flow_k.focus();
			return false;
 		}
 		if(document.frm.f_flow_k.value>16384)
 		{
 			alert("<?=$a_flow_out_range?>");	
			//alert("Flow control cannot exceed 16384.");
 			document.frm.f_flow_k.select();
			document.frm.f_flow_k.focus();
			return false;
		}
 		document.frm.f_flow_value.value=document.frm.f_flow_k.value*10;
		//alert("Flow control: "+document.frm.f_flow_value.value);		
	}
	else
	{
		document.frm.f_flow_value.value="oo";
	}
	
	//idle time
	if (document.frm.f_idle_time.value=="")
	{
		alert("<?=$a_not_enter_idle_time?>");
		alert("Please enter an idle time.")
		document.frm.f_idle_time.select();
		document.frm.f_idle_time.focus();
		return false;
	}
	
	if (isNaN(document.frm.f_idle_time.value))
	{
		alert("<?=$a_idle_time_out_range?>");	
		//alert("The idle time must be between 1~10 minutes.");
		document.frm.f_idle_time.select();
		document.frm.f_idle_time.focus();
		return false;
	}
	
	if (document.frm.f_idle_time.value < 1 || document.frm.f_idle_time.value >10)
	{
		alert("<?=$a_idle_time_out_range?>");	
		//alert("The idle time must be between 1~10 minutes");
		document.frm.f_idle_time.select();
		document.frm.f_idle_time.focus();
		return false;
	}

	if (document.frm.f_idle_time.value.indexOf(" ") != -1) 
 	{
 		alert("<?=$a_idle_time_contain_space?>");	
 		//alert("Idle time can not contain space");
 		document.frm.f_idle_time.select();
		document.frm.f_idle_time.focus();
 		return false;
 	}	
	
	//+++jana
	if (document.frm.f_idle_time.value.indexOf(".") > -1)
	{
		alert("<?=$a_idle_time_not_integer?>");	
		//alert("The number of idle time must be an integer.")
		document.frm.f_idle_time.select();
		document.frm.f_idle_time.focus();
		return false;
	}
	//---jana
	
	//Dir
	if(document.frm.f_dir.value.length > 128)
	{
		alert("<?=$a_invalid_path_length?>");	
		//alert("The path length cannot exceed 128 characters. Please try again.");
 		document.frm.f_dir.select();
		document.frm.f_dir.focus();
 		return false;		
	}
	
	//+++jana
	if(document.frm.modify_type.value == ""){
	if(document.frm.f_method[0].checked)//user
	{
			var i;
		for (i in ftp_access_list_array)
		{				
			if(document.frm.user_list.value == "anonymous")
			{
				if("Anonymous" == ftp_access_list_array[i])
				{
					alert("<?=$a_anonymous_existed?>");	
					//alert("This Anonymous user is already in the FTP access list.");
					return false;
				}
			}						
			else if(document.frm.user_list.options[document.frm.user_list.selectedIndex].text == ftp_access_list_array[i])
			{		
				alert("<?=$a_user_existed?>");	
				//alert("This user is already in the FTP access list.");
				return false;
			}
		}
	}
	else //group
	{
			var i;
		for (i in ftp_access_list_array)
		{
			if(document.frm.f_groupname.options[document.frm.f_groupname.selectedIndex].text == ftp_access_list_array[i])
			{
				alert("<?=$a_group_existed?>");	
				//alert("This group is already in the FTP access list.");
				return false;
			}
		}
	}
	}
	//---jana
	
	//check path include ..
	/*
	if(document.frm.f_dir.value.indexOf("/..") != -1)
	{
		alert("The path format is not correct. Please try again.");
 		document.frm.f_dir.select();
		document.frm.f_dir.focus();
 		return false;	
	}	
	*/
	
	//fix bug in modify. These fields MUST be enabled if we want to write it to DB.
	//Any "disabled field" will have blank value in php script. 
	if(document.frm.ACTION_POST.value == "MODIFY")
	{
		
	}
	return true;
}

function change()
{
	if (document.frm.f_flow[0].checked)
	{
		//document.frm.f_flow_k.value="0";
		document.frm.f_flow_k.disabled=true;		
	}
	else
	{
		document.frm.f_flow_k.disabled=false;
		document.frm.f_flow_k.select();
		document.frm.f_flow_k.focus();	
	}	
}

function select_index(obj, val)
{
	var i=0;
	for(i=0; i<obj.length;i++)
	{
		if(eval("obj["+i+"].value")==val)
		{
			obj.selectedIndex=i;
			break;
		}
	}
}

function delpath2(type,name,flag,index)
{
	//type:1 del user	2:del group  3:anonymous
	//name:username
	var f=get_obj("frm");
	if (confirm("You are about to delete this entry."))
	{
		//alert(index);
		if(type == 1)
		{
			f.del_type.value = "user";
			f.del_id.value = index;
		}
		else if(type == 2)
		{
			f.del_type.value = "group";
			f.del_id.value = index;
		}
		else if(type == 3)
		{
			f.del_type.value = "anonymous";
			f.del_id.value = "something";
		}
	}
	f.ACTION_POST.value = "DELETE";
	f.submit();
}

function generate_random_str()
{
	var d = new Date();
	var str=d.getFullYear()+"."+(d.getMonth()+1)+"."+d.getDate()+"."+d.getHours()+"."+d.getMinutes()+"."+d.getSeconds();
	return str;
}
/*marco
function enable_ftp_js()
{
	
	var f=get_obj("frm");
	if( "<?=$ftp_toogle_button?>" == "Start Ftp Server")
	{
		//self.location.href="<?=$MY_NAME?>.php?enable_ftp=1&ACTION_ENABLE_FTP=something"; 	
		f.enable_ftp.value = "1";
	} else
	{
		//self.location.href="<?=$MY_NAME?>.php?enable_ftp=0&ACTION_ENABLE_FTP=something"; 	
		f.enable_ftp.value = "0";
	}
	f.ACTION_POST.value = "ENABLE_DISABLE_FTP";
	f.submit();
}
*/

function fillValues(type, user_index, path, permission)
{
	var f=get_obj("frm");
	if(type == "1")
	{
		f.user_list.value = user_index;
	}else if (type == "2")
	{
		f.f_groupname.value = user_index;
	}else if (type == "3")
	{
		f.user_list.value = "anonymous";
	}
	
	f.read_write.value = permission;
	
	if(path == "/")
	{
		f.f_root.checked = true;
		check_path(1);
	}else
	{
		//f.f_root.checked = true;//jana removed
		f.f_root.checked = false;//jana added
		//check_path(1);//jana removed
		check_path();//jana added
	}
	
	f.f_dir.value = path;
}

function ModifySetting(type, user_index, path, permission )
{
	var f=get_obj("frm");
		//type 1 user
		//type 2 group
		//type 3 anonymous
		
	switch (type)
	{
		case "1": /* user type */
			//f.user_list.focus();//jana removed
			f.f_root.focus();//jana added
			f.f_method[0].disabled = false;
			f.f_method[0].checked = true;
			f.f_method[1].disabled = true;
			showfield();
			fillValues(type, user_index, path, permission);
			f.modify_type.value = "user";
			disable("user_list");
			//f.all_user.checked = false;
			disable("all_user");
		
			break;

		case "2": /* group type */
			//f.f_groupname.focus();//jana removed
			f.f_root.focus();//jana added
			f.f_method[1].disabled = false;
			f.f_method[1].checked = true;
			f.f_method[0].disabled = true;
			showfield();
			fillValues(type, user_index, path, permission);
			f.modify_type.value = "group";
			disable("f_groupname");
			
			break;
		
		case "3": /* anonymous type */
			f.user_list.focus();
			f.f_method[0].disabled = false;
			f.f_method[0].checked = true;
			f.f_method[1].disabled = true;
			showfield();
			fillValues(type, user_index, path, permission);
			f.modify_type.value = "anonymous";
			disable("user_list");
			//f.all_user.checked = false;
			disable("all_user");
			
			break;
			
		default: 
			break;
	}
			
	/*
	//TODO : error here..
	//after disable, then enable, the charset and flow limit is broken
	disable("all_user");
	disable("f_maxuser");
	disable("f_idle_time");
	disable("f_port");
	disable("f_flow");
	f.f_flow[1].disabled = true;
	disable("f_flow_k");
	disable("f_client_char");
	
	enable("all_user");
		enable("f_maxuser");
		enable("f_idle_time");
		enable("f_port");
		enable("f_flow");
		enable("f_flow_k");
		enable("f_client_char");
		f.f_flow[1].disabled = false;
	*/
	
	
	f.modify_user_id.value = user_index;
	f.ACTION_POST.value = "MODIFY";
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

</script>

<!-- css for calling explorer.php -->
<link rel="stylesheet" href="/portal/comm/smbb.css" type="text/css"> 

<body onLoad="init();" <?=$G_BODY_ATTR?>>
<form name="frm" id="frm" method="post" action="<?=$MY_NAME?>.php" onSubmit="return check()">

<input type="hidden" name="ACTION_POST"	value="ADD">
<!-- for modify function -->
<input type="hidden" name="modify_type">
<input type="hidden" name="modify_user_id">
<!-- for delete function -->
<input type="hidden" name="del_type">
<input type="hidden" name="del_id">
<!-- for enable/disable ftp -->
<input type="hidden" name="enable_ftp">


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
		<div class="box">
			<h2><?=$m_1st_ftp_title?></h2>
			<table border="0" cellpadding="0" cellspacing="0" style="border-collapse: collapse" bordercolor="#111111" width="524" >                           
	            <tr>
	              <td width="95" height="23"><?=$m_category?></td>
	              <td width="417" height="23" colspan="2">
	              <input type="radio" name="f_method" value="1" checked onClick="showfield();"><?=$m_user?>
	              <input type="radio" name="f_method" value="0" onClick="showfield();"><?=$m_group?></td>
	            </tr>
	            
                <tr id="group_select">
                  <td width="95" height="23"><?=$m_group?></td>
                  <td width="417" height="23" colspan="2">
                  <select size="1" name="f_groupname" id="f_groupname">
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
                
                <tr id="user_select">
                  <td width="95" height="23"><?=$m_user?></td>
                  <td width="417" height="23" colspan="2">
                  <select size="1" name="user_list" id="user_list">
					<option value="NONE"><?=$a_not_select_user?></option>
<?
					echo "<option value=\"anonymous\">Anonymous</option>\n";
					for ("/nas/user")
					
					{
						echo "<option value=".$@;
						echo ">".query("name")."</option>\n";
					}
?>
				  </select>
                  <input type="checkbox" name="all_user" id="all_user" value="ON" onClick="setuser();"><?=$m_all_accounts?></td>
                </tr>
                
                <tr>
                  <td width="95" height="23"><?=$m_folder?></td>
                  <td width="417" height="23" colspan="2">
                  <input type="checkbox" name="f_root" value="ON" onClick="check_path()"><?=$m_root?></td>
                </tr>
                
                <tr id="chamber2" style="display">
                  <td width="95" height="23"></td>
                  <td width="417" height="23" colspan="2">
                	<input type=text name="f_dir" id="f_dir" size=30 onClick="open_browser();" onKeyUp="checkinput();">
                	<input type=button name=f_Browse value="Browse" onClick="open_browser();">
                  </td>
                </tr>
                
                <tr>
                  <td width="95" height="23"><?=$m_permission?></td>
                  <td width="203" height="23">
                  	<select size="1" name="read_write" id="read_write" >
              		<option selected value="0"><?=$m_read_only?></option>
              		<option value="1"><?=$m_read_write?></option>
           			</select>
					<input type="hidden" name="f_read_write" size="2">
            		<input type="hidden" name="f_device_read_write" size="2">
            	  </td>
                </tr>
            </table>
            <hr />
			<table border="0" cellpadding="0" cellspacing="0" style="border-collapse: collapse" bordercolor="#111111" width="524">                                          
			  <tr>
	              <td width="95" height="23"><?=$m_enable_ftp_name?></td>
	              <td width="417" height="23" colspan="2">
	              <input type="radio" name="f_start" value="1"  ><?=$m_ftp_enable?>
	              <input type="radio" name="f_start" value="2" ><?=$m_ftp_disable?>             
	          </tr>
              <tr>
	              <td width="95" height="23"><?=$m_mode_name?></td>
	              <td width="417" height="23" colspan="2">
	              <input type="radio" name="f_mode" value="1" ><?=$m_mode_lan?>
	              <input type="radio" name="f_mode" value="2" ><?=$m_mode_wan?>
	              <input type="radio" name="f_mode" value="3" ><?=$m_mode_lan_wan?></td>
	           </tr>
              <tr>
              <td width="95" height="23"><?=$m_max_user_name?></td>
              <td width="417" height="23" colspan="2">
              	<select size="1" name="f_maxuser" id="f_maxuser">
                      <option value="1" >01</option>
                      <option value="2" >02</option>
                      <option value="3" >03</option>
                      <option value="4" >04</option>
                      <option value="5" >05</option>
                      <option value="6" >06</option>
                      <option value="7" >07</option>
                      <option value="8" >08</option>
                      <option value="9" >09</option>
                      <option value="10">10</option>
                </select>
              </td>
            </tr>
            <tr>
              <td width="95" height="24"><?=$m_idle_time_name?></td>

              <td width="417" height="24" colspan="2">
              
              <input type="text" name="f_idle_time" id="f_idle_time" size="2" value=""><?=$m_idle_time_name?>
              </td>
            </tr>
            <tr>
              <td width="95" height="24"><?=$m_port_name?></td>
              <td width="417" height="24" colspan="2">
              <input type="text" name="f_port" id="f_port" size="2" value=""><?=$m_port_limit?></td>

            </tr>
            <tr>
              <td width="95" height="24"><?=$m_flow_control_name?></td>
              <td width="204" height="24">
	              <input type="radio" name="f_flow" id="f_flow" value="1" onClick="change();" ><?=$m_flow_unlimited?>
	              <input type="radio" name="f_flow" id="f_flow" value="0" onClick="change();" >
	              <input type="text" name="f_flow_k" id="f_flow_k" size="4" value="1"><?=$m_flow_unit?>
	              <input type="hidden" name="f_flow_value" id="f_flow_value" size="20">
              </td>
              <td width="213" height="24">&nbsp;</td>
            </tr>
            <tr>
              <td width="95" height="24"><?=$m_client_language_name?></td>
              <td width="204" height="24">
              <select size="1" name="f_client_char" id="f_client_char">
				<option value="ISO8859-1"><?=$m_western_european?></option>
				<option value="ISO8859-10" ><?=$m_northern_european?></option>
				<option value="cp1250"><?=$m_central_european?></option>
				<option value="big5"  ><?=$m_traditional_chinese?></option>
				<option value="gb2312"><?=$m_simplified_chinese?></option>
				<option value="cp1251"><?=$m_cyrillic?></option>
              </select>

              <td width="213" height="24">&nbsp;&nbsp;
              </td>
			  
            </tr>
            </table>  
		</div>

		<div class="box">
			<h2><?=$m_2nd_ftp_title?></h2>
			<table border="1" cellpadding="0" cellspacing="0" style="border-width:0; border-collapse: collapse; " bordercolor="#C6CBCE" width="90%" height="11">
            <tr>

            <td id="chamber1" style="border-style:none; border-width:medium; " style="border-style:none; border-width:medium; " height="1" colspan="3">
            </td>
            </tr>
			<table width="90%" border="1" cellpadding="3" cellspacing="0" align="center" style="border-width: 0; border-color:#DDDDDD; border-collapse:collapse;"><tr align="right">
			</td>&nbsp;</td>
			<td style="border-style:none; border-width:medium; " height="1" colspan="5" align="right"><img border="0" src="../pic/edit2.jpg">:<?=$m_read_write?>&nbsp; <img border="0" src="../pic/edit1.jpg">:<?=$m_read_only?>&nbsp; <img border="0" src="../pic/edit.jpg">:<?=$m_modify_setting?> <img border="0" src="../pic/release.gif">:<?=$m_delete?></td>
			</tr>

			<tr class="FSCol_Hdr" >
			<td width="28%" style="border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1" height="11"><?=$m_list_path?></td>
			<td width="67%" style="border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1" height="11"><?=$m_list_user_group?></td>
			<td width="5%"  style="border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1" height="11"><?=$m_list_read_write?></td>
			<td width="5%"  style="border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1" height="11">&nbsp;</td>
			<td width="5%"  style="border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1" height="11">&nbsp;</td>
			</tr>

<? 
			$group_display_index = "1";
			for ("/nas/group")
			{
				$temp_name = get(h,"name");
				//$temp_path = query("/nas/group:".$@."/ftp/path");//jana removed
				$temp_path = get("j","/nas/group:".$@."/ftp/path");//jana added
				$temp_permission = query("/nas/group:".$@."/ftp/permission");
				/*$temp_group = get(h,"in_group");*/
				
				if($temp_permission == "0")
				{
					$temp_pic = "../pic/edit1.jpg";
				}
				else
				{
					$temp_pic = "../pic/edit2.jpg";
				}
				if($temp_path == "") {$temp_path = "/";}	/*root is blank for now*/
				
				if($temp_permission!="")
				{
					echo "<tr>";
					echo "<td id=\'2str1\' width=\"67%\" style=\"word-break: break-all;border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\" height=\"17\">".$temp_path."</td>";
			   		echo "<td width=\"28%\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\" height=\"17\">".$temp_name."&nbsp;&nbsp;</td>";
			   		echo "<td width=\"5%\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\" height=\"17\"><img border=\"0\" src=\"".$temp_pic."\"></td>";
			   		echo "<td width=\"5%\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\" height=\"17\">";
			   		echo "<a href=\"javascript:ModifySetting('2','".$@."','".$temp_path."','".$temp_permission."');\"><img border=\"0\" src=\"../pic/edit.jpg\"></a></td>";
			   		echo "<td width=\"5%\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\" height=\"17\">";
			   		echo "<a href=\"javascript:delpath2('2','".$temp_name."','0','".$@."');\"><img border=\"0\" src=\"../pic/release.gif\"></a></td>";
					echo "</tr>";
				
					/* store displayed group settings in php variables (for patch in user's display) 
					   group names that displayed will be stored in 
					   variables "GROUP_DISPLAY1" , "GROUP_DISPLAY2" and so on */
					$group_display = "GROUP_DISPLAY".$group_display_index;
					$$group_display = $temp_name;
					//$group_display = $temp_name;
					$group_display_index++;
				}
			}
?>
<? 
			for ("/nas/user")
			{
				$temp_name = get(h,"name");
				//$temp_path = query("/nas/user:".$@."/ftp/path");//jana removed
				$temp_path = get("j","/nas/user:".$@."/ftp/path");//jana added
				$temp_permission = query("/nas/user:".$@."/ftp/permission");
				/*$temp_group = get(h,"in_group");*/
				
				if($temp_permission == "0")
				{
					$temp_pic = "../pic/edit1.jpg";
				}else
				{
					$temp_pic = "../pic/edit2.jpg";
				}
				
				if($temp_path == "") {$temp_path = "/";}	/*root is blank for now*/
				
				/* use permission to decide if data valid */
				/* find if user belong to above group "that has already ftp setting", if yes, user's ftp setting 
				   is overriden by group's ftp setting, so don't display user's setting again.
				   We just need to search for match from "GROUP_DISPLAY1", "GROUP_DISPLAY2" and so on */
				$temp_group = query("/nas/user:".$@."/group");
				$counter = "1";
				
				
				while($counter < $group_display_index)
				{
					$my_display = "GROUP_DISPLAY".$counter;
					if($$my_display == $temp_group)
					{
						$user_setting_overriden_by_group_setting = "yes";
						/*echo "<script>alert(\"Override exist\")</script>";*/
					}
					$counter++;
				}				
				
				if($temp_permission!="" && $user_setting_overriden_by_group_setting!="yes")
				{
					echo "<tr>";
					echo "<td id=\'2str1\' width=\"67%\" style=\"word-break: break-all;border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\" height=\"17\">".$temp_path."</td>";
			   		echo "<td width=\"28%\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\" height=\"17\">".$temp_name."&nbsp;&nbsp;</td>";
	   				echo "<td width=\"5%\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\" height=\"17\"><img border=\"0\" src=\"".$temp_pic."\"></td>";
	   				echo "<td width=\"5%\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\" height=\"17\">";
	   				echo "<a href=\"javascript:ModifySetting('1','".$@."','".$temp_path."','".$temp_permission."');\"><img border=\"0\" src=\"../pic/edit.jpg\"></a></td>";
	   				echo "<td width=\"5%\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\" height=\"17\">";
	   				echo "<a href=\"javascript:delpath2('1','".$temp_name."','0','".$@."');\"><img border=\"0\" src=\"../pic/release.gif\"></a></td>";
					echo "</tr>";		
				}
				$user_setting_overriden_by_group_setting = "";
			}
?>
<?			
			/* for anonymous setting */
			$temp_permission = query("/nas/ftp/permission");
			if($temp_permission!="")
			{
				$temp_name = "Anonymous";
				//$temp_path = query("/nas/ftp/path");//jana removed
				$temp_path = get("j","/nas/ftp/path");//jana added
				if($temp_permission == "0")
				{
					$temp_pic = "../pic/edit1.jpg";
				}else
				{
					$temp_pic = "../pic/edit2.jpg";
				}
				
				if($temp_path == "") {$temp_path = "/";}	/*blanks mean root*/
				if($temp_permission!="")
				{
					echo "<tr>";
					echo "<td id=\'2str1\' width=\"67%\" style=\"word-break: break-all;border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\" height=\"17\">".$temp_path."</td>";
			   		echo "<td width=\"28%\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\" height=\"17\">".$temp_name."&nbsp;&nbsp;</td>";
	   				echo "<td width=\"5%\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\" height=\"17\"><img border=\"0\" src=\"".$temp_pic."\"></td>";
	   				echo "<td width=\"5%\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\" height=\"17\">";
	   				echo "<a href=\"javascript:ModifySetting('3','".$@."','".$temp_path."','".$temp_permission."');\"><img border=\"0\" src=\"../pic/edit.jpg\"></a></td>";
	   				echo "<td width=\"5%\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\" height=\"17\">";
	   				echo "<a href=\"javascript:delpath2('3','".$temp_name."','0','".$@."');\"><img border=\"0\" src=\"../pic/release.gif\"></a></td>";
					echo "</tr>";		
				}
			}

?>
			</table>
			
			<input type="hidden" name="count" value="2">    
		</div>
		
		<div class="box">
		<h2><?=$m_3rd_ftp_title?></h2>
			<table border="0" cellpadding="0" cellspacing="0" style="border-collapse: collapse" bordercolor="#111111" width="450" id="AutoNumber8" height="46">
			<TR>
			<td width="3%" height="29">&nbsp;</td>
			<td width="20%" height="29" style="color:#111111"><?=$m_statue_name?> </td>
			<td width="70%" height="29" style="color:#111111"><?=$ftp_status?></td>
			</TR>
			
			<TR>
			<td width="3%" height="29">&nbsp;</td>
			<td width="24%" height="29" style="color:#111111"><?=$m_mode_name?></td>
			<td width="70%" height="29" style="color:#111111"><?=$ftp_mode?></td>
			</TR>			
			
			<TR>
			<td width="3%" height="29">&nbsp;</td>
			<td width="24%" height="29" style="color:#111111"><?=$m_port_name?></td>
			<td width="70%" height="29" style="color:#111111"><?=$ftp_port?></td>
			</TR>
			
			<TR>
			<td width="3%" height="29">&nbsp;</td>
			<td width="24%" height="29" style="color:#111111"><?=$m_max_user_name?></td>
			<td width="70%" height="29" style="color:#111111"><?=$ftp_max_user?></td>
			</TR>
			<TR>
				<td width="3%" height="29">&nbsp;</td>
				<td width="24%" height="29" style="color:#111111"><?=$m_flow_control_name?></td>
				<td width="70%" height="29" style="color:#111111"><?=$ftp_flow_control?></td>
			</TR>
			<TR>
				<td width="3%" height="29">&nbsp;</td>
				<td width="24%" height="29" style="color:#111111"><?=$m_idle_time_name?></td>
				
				<td width="70%" height="29" style="color:#111111"><?=$ftp_idle_time?> </td>
			</TR>
			<TR>
				<td width="3%" height="29">&nbsp;</td>
				<td width="24%" height="29" style="color:#111111"><?=$m_client_language_name?></td>
				<td width="70%" height="29" style="color:#111111"><?=$ftp_language?></td>
			</TR>
			<TR>
				<td width="3%" height="29">&nbsp;</td>
				<td width="90%" colSpan="2" height="1"><b><hr></b></td>
			</TR>

	        <tr>
	          <td width="3%" height="5"></td>
	          <td width="15%" height="5"></td>
	          <td width="80%" height="5">&nbsp;</td>
	        </tr>
	        <tr>
	          <td width="3%" height="2"></td>
	          <td width="15%" height="2"></td>
	          <td width="80%" height="2"></td>
	        </tr>
	      	</table>
		</div>
<!-- ________________________________  Main Content End _______________________________ -->
	</td>
	<td <?=$G_HELP_TABLE_ATTR?>><?require($LOCALE_PATH."/help/h_".$MY_NAME.".php");?></td>
</tr>
</table>
<?require("/www/model/__tailer.php");?>
</form>
</body>
</html>


