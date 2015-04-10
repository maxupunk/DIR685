#!/bin/sh
echo [$0] ... > /dev/console
<?
/* vi: set sw=4 ts=4: */
require("/etc/templates/troot.php");
$mode=query("/nas/network_access/mode");//jana added
/*1234*/
if ($generate_start==1 && $mode !=0)//jana modified
{
		$network_access_config = "/var/smb.conf";    
		$network_access_open_mode = "/var/open_mode";    
		fwrite($network_access_config, "[global]\n");
		fwrite2($network_access_config, "\tunix charset = UTF8\n");
		fwrite2($network_access_config, "\tkernel change notify = yes\n");  
		fwrite2($network_access_config, "\tdead time = 1\n");
		fwrite2($network_access_config, "\tmax smbd processes = 9\n");
		fwrite2($network_access_config, "\tsecurity = user \n");
		fwrite2($network_access_config, "\tencrypt passwords = yes \n");
		fwrite2($network_access_config, "\tnull passwords = yes \n");
		fwrite2($network_access_config, "\tpid directory = /var/run \n");
		fwrite2($network_access_config, "\tload printers = no \n");
		fwrite2($network_access_config, "\tguest account = nobody \n");
		fwrite2($network_access_config, "\tlog file = /var/log/log.%m \n");
		fwrite2($network_access_config, "\tmax log size = 1 \n");
		fwrite2($network_access_config, "\tsocket options = IPTOS_LOWDELAY TCP_NODELAY SO_SNDBUF=65536 SO_RCVBUF=65536 \n");
		fwrite2($network_access_config, "\tmax xmit = 65536 \n");
		fwrite2($network_access_config, "\tread size = 65536 \n");
		fwrite2($network_access_config, "\tread prediction = true\n");
		fwrite2($network_access_config, "\tdns proxy = no \n");
		fwrite2($network_access_config, "\tmap to guest=bad user \n");
		fwrite2($network_access_config, "\tworkgroup = workgroup \n");
		fwrite2($network_access_config, "\tnetbios name = DIR-685\n");
		fwrite2($network_access_config, "\tserver string = DIR-685\n");
//		$permission=query("/nas/network_access_open_mode/share_path:1/permission");
//		$device_name=query("/nas/network_access_open_mode/share_path:1/path");
		if($mode == 1 )//open mode
		{
			fwrite($network_access_open_mode, "1\n");
			for("/nas/network_access_open_mode/share_path")
			{
				$device_name=query(path);
				if($device_name!="/" && $device_name!="")
				{
				$folder="/tmp/storage_dev/".$device_name;			
				$comment=query("/nas/network_access_open_mode/share_path:1/comment");
	    		    		
				fwrite2($network_access_config, "[ ".$device_name." ]\n");
				fwrite2($network_access_config, "\tcomment = ".$comment." \n");
				fwrite2($network_access_config, "\tpath = ".$folder." \n");
				fwrite2($network_access_config, "\tuse sendfile = yes \n");
				fwrite2($network_access_config, "\tuse receivefile = yes \n");
				if($permission=="0")
				{fwrite2($network_access_config, "\tread only = yes \n");}
				else
				{fwrite2($network_access_config, "\tread only = no \n");}
				fwrite2($network_access_config, "\tpublic    = yes \n");
				}
				fwrite2($network_access_config,"\tcreate mode = 0777 \n");
                fwrite2($network_access_config,"\tdirectory mode = 0777 \n");
			}

		}
		else //security mode
		{
			
			unlink("/var/open_mode");
			$index=1;
			 for ("/nas/user")
			 {
			 	for("network_access/share_path")
			 	{
			 		$permission=query("permission");
			 		if($permission!="")
					{
						$user=query("/nas/user:".$index."/name");
						
						$oplocks=query("oplocks");
						$map=query("map_archive");
						$comment=query("comment");
						$share=query("share");
						/*hendry : let web know the unique share name*/
						set("share_web",$share);
						
						$root_folder=query("device_name");		
						$sub_folder=query("folder");
						for("/nas/network_access_open_mode/share_path")
						{
							$device_name=query("path");
							if($root_folder==$device_name)
							{
								$folder="/tmp/storage_dev/".$device_name."/".$sub_folder."";		
							}
						}
						if($folder!="")
						{
						fwrite2($network_access_config, "[ ".$share." ]\n");
						fwrite2($network_access_config, "\tcomment = ".$comment." \n");
						fwrite2($network_access_config, "\tpath = ".$folder." \n");
						fwrite2($network_access_config, "\tdns proxy = no \n");
						fwrite2($network_access_config, "\tvalid users = ".$user."\n");
						fwrite2($network_access_config, "\tguest ok = no\n");
						fwrite2($network_access_config, "\tuse sendfile = yes \n");
						fwrite2($network_access_config, "\tuse receivefile = yes \n");
						if($permission=="0")
						{fwrite2($network_access_config, "\tread only = yes \n");}
						else
						{fwrite2($network_access_config, "\tread only = no \n");}	
						fwrite2($network_access_config, "\toplocks = ".$oplocks." \n");
						fwrite2($network_access_config, "\tmap archive = ".$map." \n");	
						fwrite2($network_access_config,"\tcreate mode = 0777 \n");
                        fwrite2($network_access_config,"\tdirectory mode = 0777 \n");				
					}			
			 	}		 	
			 	}		 	
				$index++;
			}
			for("/nas/network_access_all_user/share_path")
			{
				$index=1;
				$permission=query("permission");
				if($permission!="")
				{					
					$user="";
					for ("/nas/user")
					{
						$user=$user." ".query("/nas/user:".$index."/name");
						$index++;
					}
					
					$oplocks=query("oplocks");
					$map=query("map_archive");
					$comment=query("comment");
					$share=query("share");
					/*hendry : let web know the unique share name*/
					set("share_web",$share);
					
					$root_folder=query("device_name");		
					$sub_folder=query("folder");
					for("/nas/network_access_open_mode/share_path")
					{
						$device_name=query("path");
						if($root_folder==$device_name)
						{
							$folder="/tmp/storage_dev/".$device_name."/".$sub_folder."";		
						}
					}
					if($folder!="")
					{
					fwrite2($network_access_config, "[ ".$share." ]\n");
					fwrite2($network_access_config, "\tcomment = ".$comment." \n");
					fwrite2($network_access_config, "\tpath = ".$folder." \n");
					fwrite2($network_access_config, "\tdns proxy = no \n");
					fwrite2($network_access_config, "\tvalid users = ".$user."\n");
					fwrite2($network_access_config, "\tguest ok = no\n");
					fwrite2($network_access_config, "\tuse sendfile = yes \n");
					fwrite2($network_access_config, "\tuse receivefile = yes \n");
					if($permission=="0")
					{fwrite2($network_access_config, "\tread only = yes \n");}
					else
					{fwrite2($network_access_config, "\tread only = no \n");}
					fwrite2($network_access_config, "\toplocks = ".$oplocks." \n");
					fwrite2($network_access_config, "\tmap archive = ".$map." \n");
					fwrite2($network_access_config,"\tcreate mode = 0777 \n");
                    fwrite2($network_access_config,"\tdirectory mode = 0777 \n");
				}
			}
			}
			
			
			for("/nas/network_access_allow_guest/share_path")
			{
				$permission=query("permission");
				if($permission!="")
				{
					
					$oplocks=query("oplocks");
					$map=query("map_archive");
					$comment=query("comment");
					$share=query("share");
					/*hendry : let web know the unique share name*/
					set("share_web",$share);
					$root_folder=query("device_name");		
					$sub_folder=query("folder");
					for("/nas/network_access_open_mode/share_path")
					{
						$device_name=query("path");
						if($root_folder==$device_name)
						{
							$folder="/tmp/storage_dev/".$device_name."/".$sub_folder."";		
						}
					}
					if($folder!="")
					{
				
					fwrite2($network_access_config, "[ ".$share." ]\n");
					fwrite2($network_access_config, "\tcomment = ".$comment." \n");
					fwrite2($network_access_config, "\tpath = ".$folder." \n");
					fwrite2($network_access_config, "\tdns proxy = no \n");
					fwrite2($network_access_config, "\tpublic    = yes \n");
					fwrite2($network_access_config, "\tguest ok = yes\n");
					fwrite2($network_access_config, "\tuse sendfile = yes \n");
					fwrite2($network_access_config, "\tuse receivefile = yes \n");
					if($permission=="0")
					{fwrite2($network_access_config, "\tread only = yes \n");}
					else
					{fwrite2($network_access_config, "\tread only = no \n");}
					fwrite2($network_access_config, "\toplocks = ".$oplocks." \n");
					fwrite2($network_access_config, "\tmap archive = ".$map." \n");
					fwrite2($network_access_config,"\tcreate mode = 0777 \n");
                    fwrite2($network_access_config,"\tdirectory mode = 0777 \n");
				}
			}
			}
			
			
			
			$index=1;
			 for ("/nas/group")
			 {
			 	for("network_access/share_path")
			 	{
				 	$permission=query("permission");
				 	$temp_member="";//jana added
				 	$member="";//jana added
					if($permission!="")
					{
						$group=query("/nas/group:".$index."/name");
						//loop to get users in this gp
						$i = 1;
						$temp_member = query("/nas/group:".$index."/member:".$i);
						while($temp_member!="")
						{
							$member = $member." ".$temp_member;	
							$i++;
							$temp_member = query("/nas/group:".$index."/member:".$i);
						}
						
						
						$oplocks=query("oplocks");
						$map=query("map_archive");
						$comment=query("comment");
						$share=query("share");
						/*hendry : let web know the unique share name*/
						set("share_web",$share);
				
						$root_folder=query("device_name");		
						$sub_folder=query("folder");
						for("/nas/network_access_open_mode/share_path")
						{
							$device_name=query("path");
							if($root_folder==$device_name)
							{
								$folder="/tmp/storage_dev/".$device_name."/".$sub_folder."";		
							}
						}
						if($folder!="")
						{
						fwrite2($network_access_config, "[ ".$share." ]\n");
						fwrite2($network_access_config, "\tcomment = ".$comment." \n");
						fwrite2($network_access_config, "\tpath = ".$folder." \n");
						fwrite2($network_access_config, "\tdns proxy = no \n");
						
						fwrite2($network_access_config, "\tvalid users = ".$member."\n");
						fwrite2($network_access_config, "\tguest ok = no \n");
						fwrite2($network_access_config, "\tuse sendfile = yes \n");
						fwrite2($network_access_config, "\tuse receivefile = yes \n");
						if($permission=="0")
						{fwrite2($network_access_config, "\tread only = yes \n");}
						else
						{fwrite2($network_access_config, "\tread only = no \n");}	
						
						fwrite2($network_access_config, "\toplocks = ".$oplocks." \n");
						fwrite2($network_access_config, "\tmap archive = ".$map." \n");
						fwrite2($network_access_config,"\tcreate mode = 0777 \n");
                        fwrite2($network_access_config,"\tdirectory mode = 0777 \n");
					}
				}
				}
				$index++;			
			}
		}
		echo "echo \"Start smbd...\" > /dev/console\n";
		echo "smbd -s ".$network_access_config." -D \n";
		echo "nmbd -D\n";
}
else if ($generate_start==2 && $mode !=0)	//for reload config file only
{
	echo "echo \"Reload config file for smbd ...\" > /dev/console\n";
	echo "killall -SIGHUP smbd \n";
}
else
{
	echo "echo \"Stop smbd ...\" > /dev/console\n";
	echo "killall -w smbd \n"; 
	echo "killall -w nmbd \n";
}
?>
