<?
/* vi: set sw=4 ts=4: ---------------------------------------------------------*/
$MY_NAME		="nas_user_group";
$MY_MSG_FILE	=$MY_NAME.".php";
$CATEGORY		="nas";
/* --------------------------------------------------------------------------- */

if ($ACTION_POST!="")
{
	require("/www/model/__admin_check.php");
	/*echo "<script>alert(\"Add type : ".$add_type."\")</script>";*/
	/* add new user/group (accessed when "Add" pressed)*/
	if($ACTION_ADD != "")
	{
		if($add_type == "user")
		{
			/*echo "<script>alert(\"Add new user\")</script>";*/
			/* find correct index for user to be filled in */
			/* check if exist old member with same name */
			$i = 1;
			for("/nas/user")
			{
				if($f_WEB_NAME == query("name"))
				{
					$member_already_exist = "1";
				}
				$i++;				
			}
			if($member_already_exist == "1")
			{
				echo "<script>alert(\"Error:".$a_user_exited."\")</script>";
			}
			else 
			{	/* add user */	
				set("/nas/user:".$i."/name" , $f_WEB_NAME);
				set("/nas/user:".$i."/password" , $f_WEB_PASSWD);
				
				$total_user = query("/nas/total_user");
				if($total_user==""){$total_user=0;}
				$total_user++;
				set("/nas/total_user", $total_user);
				
				if($total_user != $i)
				{	/*just warning if total user isn't set correctly*/
					echo "<script>alert(\"Total user in db wrong, db : ".$total_user." , index : ".$i."\")</script>";
				}
			}
		} 
		else if($add_type == "group")
		{
			/*echo "<script>alert(\"Add new GROUP \")</script>";*/
			$i = 1;
			for("/nas/group")
			{
				if($groupname == query("name"))
				{
					$group_already_exist = "1";
				}
				$i++;				
			}
			if($group_already_exist == "1")
			{
				echo "<script>alert(\"Error:".$a_group_exited."\")</script>";
			}
			else 
			{
				set("/nas/group:".$i."/name" , $groupname);
				
				$total_group = query("/nas/total_group");
				if($total_group==""){$total_group=0;}	/*if db don't have total group*/
				$total_group++;
				set("/nas/total_group", $total_group);
				
				if($total_group != $i)
				{	/*just warning if total group isn't set correctly*/
					echo "<script>alert(\"Total group in db wrong, db : ".$total_group." , index : ".$i."\")</script>";
				}
			}
		}
		$NEXT_PAGE=$MY_NAME;
		$ONLY_DO_SUBMIT_STR="submit USER_ADD; submit USER_ADD; submit COMMIT;"; 
		if($ONLY_DO_SUBMIT_STR!="")	{require($G_SAVING_URL);}
		else				{require($G_NO_CHANGED_URL);}		
	}
	else if($ACTION_MODIFY!="")
	{
		set("/nas/user:".$modify_id."/password" , $f_WEB_PASSWD);
		
		$NEXT_PAGE=$MY_NAME;
		//$ONLY_DO_SUBMIT_STR="submit USER_ADD; submit USER_ADD; submit COMMIT;"; //jana removed
		$ONLY_DO_SUBMIT_STR="submit USER_ADD; submit USER_ADD; submit COMMIT; submit NET_ACCESS_RELOAD;submit PURE-FTPD;";//jana added
		if($ONLY_DO_SUBMIT_STR!="")	{require($G_SAVING_URL);}
		else				{require($G_NO_CHANGED_URL);}					
		
	}
	else if($ACTION_DELETE!="")
	{	
		/* delete user / group */
		if($del_id!="")
		{
			require("/www/model/__admin_check.php");
			
			/* delete user/group with index == del_id */
			if($ACTION_DELETE=="user")
			{
				/*echo "<script>alert(\"Deleting user :".$del_id."\")</script>";*/
				$temp_user_name = query("/nas/user:".$del_id."/name");	
				del("/nas/user:".$del_id);	
				$total_user = query("/nas/total_user");
				$total_user--;
				set("/nas/total_user", $total_user);
				
				/* update other groups that have the deleted user */
				//$i = 1;//jana removed
				for("/nas/group")
				{
					$i = 1;//jana added
					$temp_member_in_group = query("member:".$i."");
					while($temp_member_in_group != "")
					{
						if($temp_member_in_group == $temp_user_name)
						{
							del("member:".$i."");	
						}
						$i++;
						$temp_member_in_group = query("member:".$i."");
					}
				}
	
			}
			else if($ACTION_DELETE=="group")
			{
				/*echo "<script>alert(\"Deleting group".$del_id."\")</script>";*/
				$tmp_group_name = query("/nas/group:".$del_id."/name");
				//if(query("/nas/group:".$del_id."/member:1") == "") /* make sure group has no member */ //jana remvoed
				//{ 
					del("/nas/group:".$del_id);	
					$total_group = query("/nas/total_group");
					$total_group--;
					set("/nas/total_group", $total_group);	
				/*
				}else
				{
					echo "<script>alert(\"Can't delete group. The group still have members in it. \")</script>";
				}
				*/
			}
		}
		$NEXT_PAGE=$MY_NAME;
		//$ONLY_DO_SUBMIT_STR="submit USER_ADD; submit USER_ADD; submit COMMIT;";//jana removed 
		$ONLY_DO_SUBMIT_STR="submit USER_ADD; submit USER_ADD; submit COMMIT; submit NET_ACCESS_RELOAD;submit PURE-FTPD;";//jana added
		if($ONLY_DO_SUBMIT_STR!="")	{require($G_SAVING_URL);}
		else				{require($G_NO_CHANGED_URL);}		
		
	}
}

if($ACTION_CHG_GROUP != "")
{
	require("/www/model/__admin_check.php");
	/*echo "<script>alert(\"Do change group \")</script>";
	echo "<script>alert(\"f_groupname : ".$f_groupname."\")</script>";
	echo "<script>alert(\"GUserList : ".$GUserList." \")</script>";
	*/
	/*
	echo "<script>alert(\"NewAdd : ".$NewAdd." \")</script>";
	echo "<script>alert(\"NewAdd1 : ".$NewAdd1." \")</script>";
	echo "<script>alert(\"NewAdd2 : ".$NewAdd2." \")</script>";
	echo "<script>alert(\"NewAdd3 : ".$NewAdd3." \")</script>";
	echo "<script>alert(\"DelOld : ".$DelOld."\")</script>";
	echo "<script>alert(\"DelOld1 : ".$DelOld1."\")</script>";
	echo "<script>alert(\"DelOld2 : ".$DelOld2."\")</script>";
	echo "<script>alert(\"DelOld3 : ".$DelOld3."\")</script>";*/
	
	/*Add users to group*/
	if($NewAddTotalNum!="" && $NewAddTotalNum>0)
	{
		/* search correct member index to be placed in group node */
		$member_index = 1;
		for("/nas/group:".$group_index."/member")
		{
			$member_index++;
		}
		
		/* for all new members */
		$index = 1;
		while($index <= $NewAddTotalNum)
		{
			$member = "NewAdd".$index;
			if($$member != "")
			{
				/*set the group member*/
				/*echo "<script>alert(\"exist\")</script>";*/
				set("/nas/group:".$group_index."/member:".$member_index,$$member);
				$member_index++;
				
				//+++ sonnia 2009/2/23 10:20am
				//get the ftp info.
				$group_ftp_path=query("/nas/group:".$group_index."/ftp/path");
				$group_ftp_permission=query("/nas/group:".$group_index."/ftp/permission");
				//--- sonnia
				
				/*update the user db*/
				$i = 1;
				$tmp_user_names = query("/nas/user:".$i."/name");
				while($tmp_user_names != "")
				{
					if($$member == $tmp_user_names)
					{
						$old_group = query("/nas/user:".$i."/group");
						set("/nas/user:".$i."/group", $f_groupname);
						
						//+++ sonnia 2009/2/23 10:20am
						//add the ftp info.						
						set("/nas/user:".$i."/ftp/path", $group_ftp_path);
						set("/nas/user:".$i."/ftp/permission", $group_ftp_permission);
						//--- sonnia
											
						//+++jana
						/* update old group that have member "NewAdd"*/
						if($old_group != "")
						{	
							// find the group 
							for("/nas/group")
							{
								$tmp_group_name = query("name");
								if($old_group == $tmp_group_name)
								{
									// find the member 
									$j = 1;
									$tmp_member = query("member:".$j);
									while($tmp_member!="")
									{
										if($tmp_member == $$member)
										{
											del("member:".$j);	
										}
										$j++;
										$tmp_member = query("member:".$j);	
									}
								}	
							}
						}
						//---jana
						
					}
					$i++;
					$tmp_user_names = query("/nas/user:".$i."/name");
				}
			}
			$index++;
		}
		
		/* update old group that have member "NewAdd"*/
		/*todo */
		/* jana removed
		if($old_group != "")
		{	
			// find the group 
			for("/nas/group")
			{
				$tmp_group_name = query("name");
				if($old_group == $tmp_group_name)
				{
					// find the member 
					$i = 1;
					$tmp_member = query("member:".$i);
					while($tmp_member!="")
					{
						if($tmp_member == $NewAdd)
						{
							del("member:".$i);	
						}
						$i++;
						$tmp_member = query("member:".$i);	
					}
				}	
			}
		}
		*/
	}
	
	
	/*Remove users from group*/
	if($DelOldTotalNum!="" && $DelOldTotalNum>0)
	{
		/* DELETE certain member from a group*/
		/* search correct member to be deleted  */
		$index = 1;
		while($index <= $DelOldTotalNum)
		{	
			$member = "DelOld".$index;
			for("/nas/group:".$group_index."/member")
			{
				$temp_member = query("/nas/group:".$group_index."/member:".$@);
				if($$member == $temp_member)
				{
					/*echo "<script>alert(\"clear group's member\")</script>";*/
					del("/nas/group:".$group_index."/member:".$@);
					//rm the ftp info.					
					for("/nas/user")
					{
						if($temp_member==query("name"))
						{
							del("ftp/path");
							del("ftp/permission");	
						}						
					}
				}
			}
			$index++;	
		}
		
		/*update the user's db*/
		for("/nas/user")
		{
			$tmp_user_name = query("name");
			$index = 1;
			while($index <= $DelOldTotalNum)
			{
				$member = "DelOld".$index;
				if($$member == $tmp_user_name)
				{
					/*echo "<script>alert(\"clear user's group\")</script>";*/
					//set("/nas/group:".$group_index."/member:".$index,$$member);
					set("group","");
				}
				$index++;
			}
		}
	}
	/* hendry add */
	$NEXT_PAGE=$MY_NAME;
	$SUBMIT_STR=";submit USER_ADD;submit GROUP_ADD;submit NET_ACCESS_RELOAD;submit PURE-FTPD";
	if($SUBMIT_STR!="")	{require($G_SAVING_URL);}
	else				{require($G_NO_CHANGED_URL);}		
}

if($total_user == "") {$total_user = 0; /* default value */}


/* --------------------------------------------------------------------------- */
require("/www/model/__html_head.php");
/* --------------------------------------------------------------------------- */
?>

<script>

/* page init functiOn */
function init()
{
	//+++jana
	<?
	echo "group_member_list=[";
	for("/nas/group")
	{
		$member=query("/nas/group:".$@."/member:1");
		if($member != "") 
			{echo "'1',";}
		else
			{echo "'',";}
	}
	echo "];\n";
	?>
	//---jana
	
	setlist();
	showtype();
	SelGroup();
	hiddenitem();
	
	
	/* for modify settings */
	hide("b_modify");
	hide("b_cancel");
}

/* cancel function (accessed in "Don't Save Settings" button */
function do_cancel()
{
	self.location.href="<?=$MY_NAME?>.php?random_str="+generate_random_str();
}

function hide(obj)
{
	get_obj(obj).style.display = "none";
}

function show(obj)
{
	get_obj(obj).style.display = "";		
}

function setlist()
{
	for(j=0;j<=document.form.user_list.length-1;j++)
	{
		document.form.alluser.options[document.form.alluser.length] = new Option(document.form.user_list[j].text, 				document.form.user_list[j].value);
	}
}

function showtype()
{
	if(document.form.addtype[0].checked==true)	//add user
	{	
		document.getElementById("adduser").style.display = "";
		document.getElementById("addgroup").style.display = "none";
	}
	else	//add group
	{
		document.getElementById("adduser").style.display = "none";
		document.getElementById("addgroup").style.display = "";
	}
}

function SelGroup()
{
	var tmp;
	groupname="<?=$f_groupname?>";
	for(i=0;i<=document.form.f_groupname.length-1;i++)
	{
		tmp=0;
		if(document.form.f_groupname[i].text==groupname)
		{
			tmp=1;
			document.form.f_groupname[i].selected=true;
			break;
		}
	}
	if(tmp==1)
		ShowGroupOfUser();
}

function hiddenitem()
{
	document.getElementById("all").style.display = "none";
}

/* check function */
function doCheckALL()
{
	var f=get_obj("form");
	if(document.form.addtype[0].checked==true)
	{
		if(checkAddUser()==false)
			return;
	}
	else
	{
		//checkAddGroup(); //jana removed
		//+++jana
		if(checkAddGroup()==false)
			return;
		//---jana
	}
	f.ACTION_ADD.value = "something";
	f.submit();
}

function checkAddUser()
{
	document.form.f_WEB_NAME.value=document.form.f_WEB_NAME.value.toLowerCase();
	
	//+++jana
	if(document.form.f_WEB_NAME.value.toLowerCase() == "root" || document.form.f_WEB_NAME.value.toLowerCase() == "admin" || document.form.f_WEB_NAME.value.toLowerCase() == "anonymous" || document.form.f_WEB_NAME.value.toLowerCase() == "nobody")
	{
		alert("<?=$a_invalid_username?>");
		//alert("Invalid user name.");
		return false;
	}
	//---jana
	
	if(<?=$total_user?>>=65)	//64'user+1'admin
	{
		alert("<?=$a_max_user_reached?>");
		//alert("The maximum number of users has been reached.");
		return;
	}
	
	if(check_user_password()==false)
	{	
		return false;
	}
}

function checkAddGroup()
{
	document.form.groupname.value=document.form.groupname.value.toLowerCase();
	
	if(document.form.total_group.value>=10)
	{
		alert("<?=$a_max_group_reached?>");
		//alert("The maximum number of groups has been reached.");
		return;
	}
	
	if(document.form.groupname.value=="")
	{
		alert("<?=$a_enter_group_name?>");
 		//alert("Please enter a group name.");
 		document.form.groupname.select();
		document.form.groupname.focus();
 		//return;//jana removed			
 		return false;//jana added
	}
	
	if(document.form.groupname.value.length >16)
	{
 		alert("<?=$a_max_group_length?>");
 		///alert("The group name length cannot exceed 16 characters.");
 		document.form.groupname.select();
		document.form.groupname.focus();
 		return;			
	}
	
	if (document.form.groupname.value.indexOf(" ") != -1) //find the blank space
 	{
 		alert("<?=$a_group_contain_spaces?>");
 		//alert("Group names can not contain spaces.");
 		document.form.groupname.select();
		document.form.groupname.focus();
 		return false;
 	}
 	
	var text=document.form.groupname.value;
    if((text.charAt(0)>'0') && (text.charAt(0)<'9'))
	{
		alert("<?=$a_group_begin_letter?>");
 		//alert("Group names must begin with a letter.");
 		document.form.groupname.select();
		document.form.groupname.focus();
		//return; //jana removed
		return false;//jana added
	}
    
    var re=/^[\w_-]{0,16}$/;	
		if(!re.test(text)){ 
		alert("<?=$a_invalid_group?>"+" \\ /:*?\"< >|.;+=~'[ ]{} @ # ()!'^$% & ,`");
		//alert("The group name can not include the following characters: /:*?\"< >|.;+=~'[ ]{} @ # ()!'^$% & ,`");
 		document.form.groupname.select();
		document.form.groupname.focus();
 		//return; //jana removed
 		return false;//jana added
	}	
    
	re=/^[a-zA-Z][\w_-]{0,16}$/;
	if(!re.test(text)) 
	{
		alert("<?=$a_group_begin_letter?>");
		//alert("Group names must begin with a letter.");
		document.form.groupname.select();
		document.form.groupname.focus();
 		return;
	}
}

function check_user_password()
{
	var name=document.form.f_WEB_NAME.value;

	if( document.form.f_WEB_NAME.value == "" )
	{
		alert("<?=$a_enter_user_name?>");
		//alert("Please enter a user name.");
		document.form.f_WEB_NAME.select();
		document.form.f_WEB_NAME.focus();
		return false;
	}
	
	if (document.form.f_WEB_NAME.value.indexOf(" ") != -1) //find the blank space
 	{
 		alert("<?=$a_user_contain_spaces?>");
 		//alert("User name cannot contain space.");
 		document.form.f_WEB_NAME.select();
		document.form.f_WEB_NAME.focus();
		return false;
 	}
 	
 	if((name.charAt(0)>'0') && (name.charAt(0)<'9'))
	{
		alert("<?=$a_user_begin_letter?>");
 		//alert("User name must begin with a letter.");
 		document.form.f_WEB_NAME.select();
		document.form.f_WEB_NAME.focus();
		return false;

	}

	if (document.form.f_WEB_NAME.value.length >16)
	{
		alert("<?=$a_max_user_length?>");
 		//alert("The user name length cannot exceed 16 characters.");
 		document.form.f_WEB_NAME.select();
		document.form.f_WEB_NAME.focus();
		return false;

	}

	var re=/^[\w_-]{0,16}$/;	
	if(!re.test(name)){
		alert("<?=$a_invalid_user?>"+" \\ /:*?\"< >|.;+=~'[ ]{} @ # ()!'^$% & ,`");
		//alert("The user name can not include the following characters: /:*?\"< >|.;+=~'[ ]{} @ # ()!'^$% & ,`");
 		document.form.f_WEB_NAME.select();
		document.form.f_WEB_NAME.focus();
		return false;

	}	
 	
	re=/^[a-zA-Z][\w_-]{0,16}$/;	
	if(!re.test(name)) {
		alert("<?=$a_user_begin_letter?>");
		//alert("User names must begin with a letter.");
		document.form.f_WEB_NAME.select();
		document.form.f_WEB_NAME.focus();
		return false;

	}

	//set password
	var password =  document.form.f_WEB_PASSWD.value;
	if( document.form.f_WEB_PASSWD.value == "" )
	{
		alert("<?=$a_enter_password?>");
		//alert("Please enter a password.");
		document.form.f_WEB_PASSWD.select();
		document.form.f_WEB_PASSWD.focus();
		return false;
	}

	if (document.form.f_WEB_PASSWD.value.indexOf(" ") != -1) //find the blank space
 	{
 		alert("<?=$a_password_contain_spaces?>");
 		//alert("Password cannot contain space");
 		document.form.f_WEB_PASSWD.select();
		document.form.f_WEB_PASSWD.focus();
		return false;
 	}

	if (document.form.f_WEB_PASSWD.value.length < 5) 
	{
		alert("<?=$a_min_password_length?>");
 		//alert("Password must be at least 5 characters in length. Please try again.");
 		document.form.f_WEB_PASSWD.select();
		document.form.f_WEB_PASSWD.focus();
		return false;
	}
	
	if (document.form.f_WEB_PASSWD.value.length > 16)
	{
		alert("<?=$a_max_password_length?>");
 		//alert("The password length cannot exceed 16 characters.");
 		document.form.f_WEB_PASSWD.select();
		document.form.f_WEB_PASSWD.focus();
		return false;		 			
	}

	var text=document.form.f_WEB_PASSWD.value;	
	re=/^[a-zA-Z0-9]{0,16}$/;	
	if(!re.test(text)) 
	{
		alert("<?=$a_invalid_password?>"+"  \\ / : * ? \" < > | . ; + = ~ \' [ ] { } @ # ( ) ! ^ $ % & , _ -`");
		//alert("The password can not include the following characters:  \\ / : * ? \" < > | . ; + = ~ \' [ ] { } @ # ( ) ! ^ $ % & , _ -");
 		document.form.f_WEB_PASSWD.select();
		document.form.f_WEB_PASSWD.focus();
 		return false;
	}

	if( document.form.f_WEB_PASSWD_2.value == "" )
	{
		alert("<?=$a_enter_confirm_password?>");
		//alert("Please enter a confirm password.");
		document.form.f_WEB_PASSWD_2.select();
		document.form.f_WEB_PASSWD_2.focus();
		return false;		 			
	}	

	if (document.form.f_WEB_PASSWD_2.value.indexOf(" ") != -1) //find the blank space
 	{
 		alert("<?=$a_password_contain_spaces?>");
 		//alert("Password cannot contain space");
 		document.form.f_WEB_PASSWD_2.select();
		document.form.f_WEB_PASSWD_2.focus();
 		return false;
 	}	

	if( document.form.f_WEB_PASSWD.value != document.form.f_WEB_PASSWD_2.value )
	{
		alert("<?=$a_confirm_not_match?>");
		//alert("The new password and confirm password do not match.  Please try again.");
		document.form.f_WEB_PASSWD.value="";
		document.form.f_WEB_PASSWD_2.value="";
		document.form.f_WEB_PASSWD.select();
		document.form.f_WEB_PASSWD.focus();
		return false;
	}
}

function add()
{
	var AddFlag;
	
	if(document.form.f_groupname.selectedIndex!=0)
	{
    	for(i=document.form.user_list.length-1; i>=0; i--)
    	{
			if(document.form.user_list[i].selected)
			{
	    		for(j=0;j<=document.form.user_list2.length-1;j++)
	    		{
	      			if(document.form.user_list2[j].value==document.form.user_list[i].value)
		   				AddFlag=1;
	    		}
	    		if(AddFlag!= "1")
	    			document.form.user_list2.options[document.form.user_list2.length] = new Option(document.form.user_list[i].text, document.form.user_list[i].value);
	    		document.form.user_list.options[i] = null;
			}
		}
	}else
		alert("<?=$a_not_select_group?>");
		//alert("Please select a group.");
		
	//GroupOfUserSetting();
}

function del()
{
	var DelFlag;
    if(document.form.user_list2.selectedIndex!=-1)
	    document.form.all_user.checked=false;
    
    for(i=document.form.user_list2.length-1; i>=0; i--)
    {
		if(document.form.user_list2[i].selected)
		{
			for(j=0;j<=document.form.user_list.length-1;j++)
	    	{
	      		if(document.form.user_list[j].value==document.form.user_list2[i].value)
		   			DelFlag=1;
	    	}
	    	if(DelFlag!= "1")
	    		document.form.user_list.options[document.form.user_list.length] = new Option(document.form.user_list2[i].text, document.form.user_list2[i].value);
			document.form.user_list2.options[i] = null;
   		}
	}
	//GroupOfUserSetting();
}
function set_post_vars_for_form3(name, index, type)
{
	/*
	type == 1 : which names to be added   to   group 
	type == 2 : which names to be deleted from group 
	*/
	var f3 = get_obj("form3");
	
	if(index > 15)
	{
		alert("<?=$a_max_modify_user?>" + name);
		//alert("Only support manipulation of 15 users at a time, cancel modify user: " + name);
		return;
	}
	
	if(type == 1)
	{
		eval("f3.NewAdd"+index+".value = \""+name+"\";");	
	} else
	{
		eval("f3.DelOld"+index+".value = \""+name+"\";");				
	}
}

function GroupOfUserSetting()
{	
	var mynewadd;
	var mydelold;
	var name="";
	var f = get_obj("form");
	var f3 = get_obj("form3");
	var status=document.form.f_groupname.selectedIndex;
	
	if(status!=0)
	{
		for(i=0;i<=document.form.user_list2.length-1;i++)
		{
			name=name+document.form.user_list2[i].value;
		}
		SelUserList=" " + name;
		SelUserList2=" " + name;

	    name_len=name.length //count name_list item
		aa=name.lastIndexOf(" " ,name_len) //search the " "
		name=name.substring(0,aa) //delete " "		
		document.form3.GUserList.value=name;

		document.form3.f_groupname.value=document.form.f_groupname[status].text;
		
		//
		newadd=document.form3.NewAdd.value;
		delold=document.form3.DelOld.value;
		/* hendry modify */
		//newadd=newadd.split("  ");
		newadd=newadd.split(" ");
		
		var userlist="";
		for(i=0;i<=newadd.length-1;i++)
		{
			userlist=userlist+newadd[i] + " ";
			
		}
		document.form3.NewAddTotalNum.value = i - 1;
		//alert("document.form3.NewAddTotalNum " + document.form3.NewAddTotalNum.value);
		
		
		/*hendry modify : fix bug here...
		  length should be -1 not -2  */
		//userlist=userlist.slice(1,userlist.length-2);
		userlist=userlist.slice(1,userlist.length-1);
		
		document.form3.NewAdd.value=userlist;
		
		//delold=delold.split("  ");
		delold=delold.split(" ");
		var userlist2="";
		for(i=0;i<=delold.length-1;i++)
		{
			userlist2=userlist2+delold[i] + " ";
		}
		document.form3.DelOldTotalNum.value = i-1;
		//alert("document.form3.DelOldTotalNum " + document.form3.DelOldTotalNum.value);
		//userlist2=userlist2.slice(1,userlist2.length-2);
		userlist2=userlist2.slice(1,userlist2.length-1);
		document.form3.DelOld.value=userlist2;

		/*hendry modify*/
		/* for NEWADD */
		/* re-parse string, add codes here */
		//alert("document.form3.NewAdd.value : " + document.form3.NewAdd.value);
		mynewadd = document.form3.NewAdd.value.split(" ");
		for(i=0;i<=mynewadd.length-1;i++)
		{
			if(mynewadd[i] != "")
			{
				//alert("mynewadd "+ i +" : " + mynewadd[i]+":");
				set_post_vars_for_form3(mynewadd[i], i+1, 1);
			}
		}
		
		/* for OLDDEL */
		//alert("document.form3.DelOld.value : " + document.form3.DelOld.value);
		//fix bug (remove the whitespace chrcter behind the DelOld.value
		document.form3.DelOld.value = document.form3.DelOld.value.substring(0,document.form3.DelOld.value.length-1);
		mydelold = document.form3.DelOld.value.split("  ");
		for(i=0;i<=mydelold.length-1;i++)
		{
			if(mydelold[i] != "")
			{
				//alert("mydelold "+ i +" : " + mydelold[i]+":");
				set_post_vars_for_form3(mydelold[i], i+1, 2);
			}
		}
		
		/*let ACTION_CHG_GROUP know which group index to change */
		document.form3.group_index.value = document.form.f_groupname.selectedIndex;
		document.form3.submit();
	}
	else
		alert("<?=$a_not_select_group?>");
		//alert("Please select a group.");
}

function Chk_add_del_user(status)
{
	//status:1	add
	//status:2	del
	//status:3	all user
	
	if(status==1)	//add
	{
   		for(i=document.form.user_list.length-1; i>=0; i--)
    	{
			if(document.form.user_list[i].selected)
			{
				seluser= " " +document.form.user_list[i].value;
				olduserlist=" "+document.form.f_groupname.value + " ";
				if(olduserlist.search(seluser)==-1)	//not found--> new add
				{
					if(document.form3.NewAdd.value.search(seluser)==-1)
					{
						document.form3.NewAdd.value=document.form3.NewAdd.value+seluser;
					}
					//alert("newadd=" +document.form3.NewAdd.value)
				}
				else
				{
					deluser=document.form3.DelOld.value;
					document.form3.DelOld.value=deluser.replace(seluser,"");
				}
			}
		}
	}
	else if(status==3)	//all user
	{
   		for(i=document.form.alluser.length-1; i>=0; i--)
    	{
			seluser= " " +document.form.alluser[i].value;
			olduserlist=" "+document.form.f_groupname.value + " ";
			if(olduserlist.search(seluser)==-1)	//not found--> new add
			{
				if(document.form3.NewAdd.value.search(seluser)==-1)
				{
					document.form3.NewAdd.value=document.form3.NewAdd.value+seluser;
				}
				//alert("newadd=" +document.form3.NewAdd.value)
			}
			else
			{
				deluser=document.form3.DelOld.value;
				document.form3.DelOld.value=deluser.replace(seluser,"");
			}
		}
	}
	else			//del
	{
   		for(i=document.form.user_list2.length-1; i>=0; i--)
    	{
			if(document.form.user_list2[i].selected)
			{
				deluser= " " +document.form.user_list2[i].value;
				olduserlist=" "+document.form.f_groupname.value + " ";
				if(olduserlist.search(deluser)!=-1)
				{
					document.form3.DelOld.value=document.form3.DelOld.value+deluser;
				}
				else
				{
					//remove user in form3.NewAdd.value
					newadd=document.form3.NewAdd.value;
					//alert(newadd.search(deluser));
					//alert(newadd.replace(deluser,""));
					document.form3.NewAdd.value=newadd.replace(deluser,"");
				}
			}
		}
	}
}



function ShowGroupOfUser()
{
	document.form3.NewAdd.value="";
	document.form3.DelOld.value="";
	document.form.all_user.checked=false;
	
	CleanUser();
   	var len=document.form.f_groupname.length;
    for(i=0;i<=len-1;i++)
    {
    	if(document.form.f_groupname[i].selected)
    	{
    		var username=document.form.f_groupname[i].value;
    		username=username.split(" ");
    		if(username=="NONE")
    		{
				CleanUser();
				var len=document.form.user_list.length;
				for(i = len-1 ; i>=0; i--)
				{
					document.form.user_list.options[i] = null;
				}
								
				for(i=0;i<=document.form.alluser.length-1;i++)
				{
					document.form.user_list.options[document.form.user_list.length] = new Option(document.form.alluser[i].text, document.form.alluser[i].value);
				}
    		}
    		else
    		{
    			var part_num=0;
				while (part_num < username.length)
				{
					if(username[part_num]!="")
						document.form.user_list2.options[document.form.user_list2.length] = new Option(username[part_num], username[part_num]+ " ");
					part_num+=1;
				}
				part_num=0;
				
				for(i=document.form.user_list.length-1; i>=0; i--)
				{
					document.form.user_list.options[i] = null;
				}
				
	    		for(i=0;i<=document.form.alluser.length-1;i++)
	    		{
	    			part_num=0;
	    			var tmp=0;
	    			while (part_num < username.length)
    				{
    					if(username[part_num]!="")
    					{
							if(document.form.alluser[i].text==username[part_num])
							{
								tmp=1;
							}
    					}
    					part_num+=1;
    				}
    				if(tmp!=1)
    				{
    					document.form.user_list.options[document.form.user_list.length] = new Option(document.form.alluser[i].text, document.form.alluser[i].value);
    				}
    			}
    		}
    		break;
    	}
    	
	}
	
	if(document.form.alluser.length==document.form.user_list2.length)
		document.form.all_user.checked=true;
}

function CleanUser()
{
 	for (k = document.form.user_list2.length-1 ; k>=0; k--) 
	{
		document.form.user_list2.options[k] = null;
	}	
}

function DeleteMember(type,name,flag,index)
{
	var f=get_obj("form");
	//type:1 del user	2:del group
	//name:username
	
	//+++jana	
	//for group, check if there are members in it 
	//+++ hendry
	if(type == 2) 
	{
	if(group_member_list[index-1] != "")//-1: since the index value of array is start from 0
	{
		alert("<?=$a_delete_group_error?>");
		//alert("Can't delete group. The group still have members in it.");
		return;
	}
	}
	//--- hendry
	//---jana
	
	
	if (confirm("You are about to delete this entry."))
	{
		if(type == 1)
		{
			//self.location.href="<?=$MY_NAME?>.php?del_id="+index+"&ACTION_DELETE=user"; 	
			f.ACTION_DELETE.value = "user";
		}
		else if(type == 2)
		{
			//self.location.href="<?=$MY_NAME?>.php?del_id="+index+"&ACTION_DELETE=group"; 	
			f.ACTION_DELETE.value = "group";
		}
		
		f.del_id.value = index;
	}
	f.submit();
}


function ModifyPassword(name, index)
{
	var f=get_obj("form");
		
	f.f_WEB_NAME.disabled = false;
	f.f_WEB_NAME.focus();
	f.f_WEB_PASSWD.focus();
	f.f_WEB_NAME.value = name;
	f.f_WEB_PASSWD.value = "";
	f.f_WEB_PASSWD_2.value = "";
	f.f_WEB_NAME.disabled = true;
	
	//hide "Add" button and change it with "Modify" button and "Cancel" button
	hide("b10");	
	show("b_modify");
	show("b_cancel");
	
	//to prevent confusion, disable the radio button of user and group  
	f.addtype[0].checked = true;
	f.addtype[1].disabled = true;
	showtype();
	
	/* let ACTION_MODIFY know which user id to modify */
	f.modify_id.value = index;
			
}

function doModify()
{
	var f=get_obj("form");
	
	if(check_user_password()==false)
	{
		return;	
	}
	//alert("Do Modify with id : "+ f.modify_id.value);
	f.ACTION_MODIFY.value = "something";
	f.submit();
}

function check()
{
	
}
function doCancelModify()
{
	var f=get_obj("form");
	/* don't do anything, just refresh page */
	f.ACTION_POST.value = "";
	f.ACTION_MODIFY.value = "";
	f.submit();
}

function set_post_vars()
{
	var f=get_obj("form");
	//alert("set post vars");
	
	/* check if add user or add group */
	if(f.addtype[0].checked==true)
	{
		f.add_type.value = "user";	
	} else if(f.addtype[1].checked==true)
	{
		f.add_type.value = "group";	
	}
	//alert("f.add_type.value : " + f.add_type.value);
}

function ba_apply()
{
	GroupOfUserSetting();
}

function allow_all()
{
	document.form3.NewAdd.value="";
	document.form3.DelOld.value="";

	if(!document.form.f_groupname[0].selected)
	{
		if(document.form.all_user.checked)	//all user
		{
			CleanUser();
			for(i=0;i<=document.form.alluser.length-1;i++)
			{
				document.form.alluser[i].selected=true;
				document.form.user_list2.options[document.form.user_list2.length] = new Option(document.form.alluser[i].text, document.form.alluser[i].value);
			}
			Chk_add_del_user(3);
			for(i=0;i<=document.form.alluser.length-1;i++)
			{
				document.form.alluser[i].selected=false;
			}
			for(i=document.form.user_list.length-1; i>=0; i--)
			{
				document.form.user_list.options[i] = null;
			}
		}
		else
		{
			for(i=document.form.user_list.length-1; i>=0; i--)
			{
				document.form.user_list.options[i] = null;
			}		
			for(i=0;i<=document.form.alluser.length-1;i++)
			{
				document.form.alluser[i].selected=true;
				document.form.user_list.options[document.form.user_list.length] = new Option(document.form.alluser[i].text, document.form.alluser[i].value);
			}
			CleanUser();	//del all user
			deluser=document.form.f_groupname.value;
			if(deluser.length>2)
			{
				deluser=deluser.split(" ");
				for(i=0;i<=deluser.length-1;i++)
				{
					document.form3.DelOld.value=document.form3.DelOld.value+ " " + deluser[i] +" ";
				}
			}
		}
	}
	else
	{
		document.form.all_user.checked=false;
	}
	
	//GroupOfUserSetting();
}

</script>
<body onload="init();" <?=$G_BODY_ATTR?>>
<form name="form" id="form" method="post" action="<?=$MY_NAME?>.php" onsubmit="check();set_post_vars()";>

<input type="hidden" name="ACTION_POST"	value="1">
<!-- for modify function -->
<input type="hidden" name="ACTION_MODIFY">
<input type="hidden" name="modify_id">
<!-- for add function -->
<input type="hidden" name="ACTION_ADD">
<input type="hidden" name="add_type" > <!-- value can be "user" or "group" -->
<!-- for delete function -->
<input type="hidden" name="ACTION_DELETE">
<input type="hidden" name="del_id">


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
		<div class="box">
			<h2><?=$m_1st_user_group_title?></h2>
			<table border="0" cellpadding="0" cellspacing="0" bordercolor="#111111" >
        	<tr>
              <td width="500" height="32">
              <table border="0" cellpadding="0" cellspacing="0" style="border-collapse: collapse" bordercolor="#111111" width="90%" id="AutoNumber1">
                <tr>
                  <td width="12%">
                  <input type="radio" name="addtype" id="addtype" value="1" onclick="showtype();" checked><?=$m_user?></td>
                  <td width="47%">
                  <input type="radio" name="addtype" id="addtype" value="2" onclick="showtype();"><?=$m_group?></td>
                  <td width="41%">
                  <!--
                  <input type="hidden" name="total_user" size="20" value="2"></td>-->
                </tr>
               </table>
              </td>
            </tr>
        	
        	<tr>
              <td id="adduser" width="500" height="32">
              <table border="0" cellpadding="0" cellspacing="0" style="border-collapse: collapse" bordercolor="#111111" width="90%" id="AutoNumber2">
              <tr>
              	<td width="22%" height="32">&nbsp; <?=$m_user_name?></td>
              	<td width="70%" height="32"><input type="text" name="f_WEB_NAME" id="f_WEB_NAME" size="17" maxLength=16></td>
              </tr>

              <tr>
              	<td width="22%" height="32">&nbsp; <?=$m_password?></td>
              	<td width="70%" height="32"><input type="password" name="f_WEB_PASSWD" size="17" maxLength=16></td>
              </tr>
              
              <tr>
              	<td width="22%" height="33">&nbsp; <?=$m_confirm_password?></td>
              	<td width="70%" height="33">
	              <input type="password" name="f_WEB_PASSWD_2" size="17" maxLength=16> 
    	  		  <input type="button" value="Add" name="b10" id="b10" onclick="check();set_post_vars();doCheckALL();">
    	  		  <input type="button" value="Modify" name="b_modify" id="b_modify" onclick="doModify();">
    	  		  <input type="button" value="Cancel" name="b_cancel" id="b_cancel" onclick="doCancelModify();">
    	  		</td>
		      </tr>
              </table>
              </td>
            </tr>
        	
        	<tr>
              <td id="addgroup" width="500" height="32">
              <table border="0" cellpadding="0" cellspacing="0" style="border-collapse: collapse" bordercolor="#111111" width="500" id="AutoNumber3">
                <tr>
  				<td width="118" height="1">&nbsp; <?=$m_add_group?></td>
  				<td width="379" height="1">
  				<input type="text" name="groupname" size="17" maxLength=16>
  				<input type="hidden" name="total_group" size="20" value="0"> 
 				<input type="button" value="Add" name="b11" onclick="set_post_vars();doCheckALL();"></td>
                </tr>
              </table>
              </td>
            </tr>	
        	</table>
		</div>
		
		<div class="box">
		<h2><?=$m_2nd_user_group_title?></h2>
		<table border="0" cellpadding="0" cellspacing="0" style="border-collapse: collapse" bordercolor="#111111" width="91%" id="AutoNumber4" height="330">
			<tr>
	      	<td width="40%" height="25" valign="bottom"><?=$m_list_all_user?></td>
	      	<td width="19%" height="25">&nbsp;</td>
	      	<td width="41%" height="25"><?=$m_select_group?>
	      		&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
	      		&nbsp;&nbsp;&nbsp;
	      		<input type="button" value="Apply" name="b_apply" onclick="ba_apply();"> 
	      		<select size="1" name="f_groupname" id="f_groupname" onchange="ShowGroupOfUser();">
	      			<option value="NONE"><?=$a_not_select_group?></option>
<?
					for ("/nas/group")
					{
						$temp_name = get(h,"name");
						$i = 1;
						$temp_member = query("/nas/group:".$@."/member:".$i);
						while($temp_member!="")
						{
							if($i == 1)
							{
								$members = $temp_member;	/*avoid blank space in first element*/
							}else
							{
								$members = $members." ".$temp_member;	
							}
							$i++;
							$temp_member = query("/nas/group:".$@."/member:".$i);
						}
						echo "<option value=\"".$members."\">".$temp_name."</option>";
						$members = "";	/* important : need to clear $members, othrwise next data will also print previous members */
					}
?>	      		
	      		</select><br>
	      		</p>
	      	<br><?=$m_user_in_group?></td>
	    	</tr>
	    	
	    	<tr>
		    <td width="40%" height="243">
		  		<SELECT name=user_list size=10 multiple STYLE="width:200px;height:250px">-->
		  		<!--<SELECT name=user_list size=10 STYLE="width:200px;height:250px">	-->
<?					
					for ("/nas/user")
					{
						echo "<option value=".get(h,"name")." ";
						echo ">".get(h,"name")."</option>\n";
					}
?>
				</SELECT>
			</td>
	      	<td width="19%" height="243">
            <p align="center">
            	<input type="button" value=" Add &gt;&gt;" name="B3" onclick="Chk_add_del_user(1);add();"></p>
            <p align="center">
            	<input type="button" value="&lt;&lt; Remove" name="B4" onclick="Chk_add_del_user(2);del();"></p>
	      	<p align="center">
	 			<input type="checkbox" name="all_user" value="ON" onclick="allow_all();"><?=$m_all_accounts?></td>
	      		
	      	<td width="41%" height="243">
		    	<select size="20" name="user_list2" STYLE="width:200; height:250" multiple>
		    		
		    	</select>
	    	</td>
	    	</tr>
	    	
	    	<tr>
	 		<td width="100%" height="14" colspan="3">
	      	<div id="all" style="display" >
			    <select  name="alluser">
			    </select>
			</div>
			</td>
	    </tr>
		</table>
		</div>
		
		<div class="box">
		<h2><?=$m_3rd_user_group_title?></h2>
		<table cellspacing="0">
        <tr>
    		<td colspan="5" align="right">
			        <img border="0" src="../pic/edit.jpg">: <?=$m_change_password?>
			        <img border="0" src="../pic/release.gif">: <?=$m_delete?>
			</td>
        </tr>
        <tr class="FSCol_Hdr" height="17">
    		<td width="51" align="center"><?=$m_list_number?></td>

    		<td width="174"><?=$m_list_user_name?></td>
    		<td width="279"><?=$m_list_group_name?></td>
    		<td width="12">&nbsp;</td>
   			<td width="12">&nbsp;</td>
        </tr>
<?
			for("/nas/user")
			{	
				$temp_name = get(h,"name");
				$temp_group = get(h,"group");
				
				echo "<TR>";
				echo "<td width=\"43\" height=\"22\" align=\"center\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\">".$@."</td>";
				echo "<td width=\"200\" height=\"22\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\">&nbsp;".$temp_name."</td>";
				echo "<td width=\"395\" height=\"22\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\">&nbsp;".$temp_group."</td>";
				
				echo "<td width=\"15\" height=\"22\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\">";
				/*echo "<a href=\"javascript:ModifyPassword('".$temp_name."','".$@."')\">";*/
				/*hendry modify here, using pop up window for modify */
				echo "<a href=\"javascript:ModifyPassword('".$temp_name."','".$@."')\">";
				echo "<img border=\"0\" src=\"../pic/edit.jpg\" width=\"15\" height=\"17\"></a></td>";
				
				echo "<td width=\"15\" height=\"22\" style=\"border-left-style: none; border-left-width: medium; border-right-style: none; border-right-width: medium; border-top-style: none; border-top-width: medium; border-bottom-style: solid; border-bottom-width: 1\">";
				echo "<a href=\"javascript:DeleteMember('1','".$temp_name."','0','".$@."');\">";
				echo "<img border=\"0\" src=\"../pic/release.gif\" width=\"15\" height=\"18\"></a></td>";
				echo "</TR>";
			}
?>        
		</table>     
		<p></p>     
		</div>
	    
	    <div class="box">
		<h2><?=$m_4th_user_group_title?></h2>
		<table cellspacing="0" >

        <tr class="FSCol_Hdr">
    		<td width="51" height="4" align="center"><?=$m_list_number?></td>
    		<td width="176" height="4"><?=$m_list_user_name?></td>
    		<td width="271" height="4"><?=$m_list_group_name?></td>
    		<td width="32" height="4"></td>
        </tr>
<?
			for("/nas/group")
			{
				$temp_name = get(h,"name");
				
				$i = 1;
				$temp_member = query("/nas/group:".$@."/member:".$i);
				$members = " ";
				
				while($temp_member!="")
				{
					/*echo "<script>alert(\"member exist ".$i." name = ".$temp_member." \")</script>";*/
					$i++;
					$members = $members." ".$temp_member;
					$temp_member = query("/nas/group:".$@."/member:".$i);
				}
				 
				/*echo "<script>alert(\"Members ".$members."\")</script>";*/
				echo "<tr>"; 
				echo "<td align=\"center\" width=\"38\" height=\"22\" style=\"border-bottom-style: solid; border-bottom-width: 1\" >".$@."</td>";
				echo "<td width=\"171\" height=\"22\" style=\"border-bottom-style: solid; border-bottom-width: 1\">".$temp_name."</td>";
				echo "<td width=\"196\" height=\"22\" style=\"word-break: break-all ;border-bottom-style: solid; border-bottom-width: 1\">".$members."&nbsp;</td>";
				echo "<td width=\"87\" height=\"22\" align=\"right\" style=\"word-break: break-all ;border-bottom-style: solid; border-bottom-width: 1\">";
				echo "<a href=\"javascript:DeleteMember('2','".$temp_name."','0','".$@."');\"><img border=\"0\" src=\"../pic/release.gif\"></a></td>";
				echo "</tr>";
			}
?>	
      </table>
		</div>
	    
	      
      
<!-- ________________________________  Main Content End _______________________________ -->
	</td>
	<td <?=$G_HELP_TABLE_ATTR?>><?require($LOCALE_PATH."/help/h_".$MY_NAME.".php");?></td>
</tr>
</table>
<?require("/www/model/__tailer.php");?>
</form>


<!-- do change group here -->
<form name="form3" id="form3" method="POST" action="<?=$MY_NAME?>.php" >
  <p>
  &nbsp;
  <input type="hidden" name="ACTION_CHG_GROUP" value="something" size="20">
  <input type="hidden" name="f_groupname" size="20">
  <input type="hidden" name="GUserList" size="20">
  <input type="hidden" name="NewAdd" size="20">
  <input type="hidden" name="DelOld" size="20">
  
  <input type="hidden" name="DelOldTotalNum" size="20">
  <input type="hidden" name="DelOld1" size="20">
  <input type="hidden" name="DelOld2" size="20">
  <input type="hidden" name="DelOld3" size="20">
  <input type="hidden" name="DelOld4" size="20">
  <input type="hidden" name="DelOld5" size="20">
  <input type="hidden" name="DelOld6" size="20">
  <input type="hidden" name="DelOld7" size="20">
  <input type="hidden" name="DelOld8" size="20">
  <input type="hidden" name="DelOld9" size="20">
  <input type="hidden" name="DelOld10" size="20">
  <input type="hidden" name="DelOld11" size="20">
  <input type="hidden" name="DelOld12" size="20">
  <input type="hidden" name="DelOld13" size="20">
  <input type="hidden" name="DelOld14" size="20">
  <input type="hidden" name="DelOld15" size="20">
  
  <input type="hidden" name="NewAddTotalNum" size="20">
  <input type="hidden" name="NewAdd1" size="20">
  <input type="hidden" name="NewAdd2" size="20">
  <input type="hidden" name="NewAdd3" size="20">
  <input type="hidden" name="NewAdd4" size="20">
  <input type="hidden" name="NewAdd5" size="20">
  <input type="hidden" name="NewAdd6" size="20">
  <input type="hidden" name="NewAdd7" size="20">
  <input type="hidden" name="NewAdd8" size="20">
  <input type="hidden" name="NewAdd9" size="20">
  <input type="hidden" name="NewAdd10" size="20">
  <input type="hidden" name="NewAdd11" size="20">
  <input type="hidden" name="NewAdd12" size="20">
  <input type="hidden" name="NewAdd13" size="20">
  <input type="hidden" name="NewAdd14" size="20">
  <input type="hidden" name="NewAdd15" size="20">
  
  <input type="hidden" name="group_index" size="20">
  <input type="hidden" name="group_name" size="20">
  
  </p>
</form>

</body>
</html>
