#!/bin/sh
echo [$0] ... > /dev/console
<?
/* vi: set sw=4 ts=4: */
require("/etc/templates/troot.php");
$shadow_file="/etc/shadow";
$passwd_file="/etc/passwd";
$ftp_tbl="/etc/ftp_tbl";
$smb_tmp="/var/smbpasswd.tmp";
if ($generate_start==1)//add
{
	fwrite($shadow_file,"");
	fwrite($passwd_file,"root:x:0:0:Linux User,,,:/:/bin/sh\n");
	fwrite2($passwd_file,"nobody:x:500:500:Linux User,,,:/:/bin/sh\n");//for smb guest account
	fwrite($smb_tmp,"");
	fwrite($ftp_tbl,"");
	echo "rm /var/smbpasswd \n";
	/* jana removed
	echo "killall smbd \n";//kill smbd first to update smb.conf
	$network_access_config = "/var/smb.conf";  //update smb conf
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
	*/
	for ("/nas/user")//discard old file and create new one
	{
		$name=query("name");
		$password=query("password");
		$path=query("ftp/path");
		$permission=query("ftp/permission");
		if($permission!="")
		{
			fwrite2($ftp_tbl,"".$user.",".$permission."\n");
			$root_path="/tmp/storage_dev/";
			$root_path=$root_path.$path;
		}
		else
		{
			$root_path="/home/ftp";
		}
		$group=query("group");
		if($group=="")//the user is not in group
		{
			echo "adduser ".$name." -p ".$password." -h ".$root_path."\n";		
		}
		else
		{
			echo "adduser ".$name." -g ".$group." -p ".$password." -h ".$root_path."\n";		
		}
		fwrite2($smb_tmp,"".$name." ".$password."\n");			
		
		/*jana removed
		for("/nas/user:".$@."/network_access/share_path")
		{
			$permission=query("permission");
			if($permission!="")
			{
				$user=query("/nas/user:".$@."/name");
				$folder="/tmp/storage_dev/";
				$folder=$folder.query("path");
				$oplocks=query("oplocks");
				$map=query("map_archive");
				$comment=query("comment");
				$share=query("share");
			
				fwrite2($network_access_config, "[ ".$share." ]\n");
				fwrite2($network_access_config, "\tcomment = ".$comment." \n");
				fwrite2($network_access_config, "\tpath = ".$folder." \n");
				fwrite2($network_access_config, "\tdns proxy = no \n");
					
				fwrite2($network_access_config, "\tvalid us0131ers = ".$user."\n");
				fwrite2($network_access_config, "\tguest ok = no \n");
					
				if($permission=="0")
				{fwrite2($network_access_config, "\tread only = no \n");}
				else
				{fwrite2($network_access_config, "\tread only = yes \n");}	
				
				fwrite2($network_access_config, "\toplocks = ".$oplocks." \n");
				fwrite2($network_access_config, "\tmap archive = ".$map." \n");
			}	
		}
		*/
				
	}
	
	/*jana removed
	 for ("/nas/group")
		 {
		 	for("/nas/group:".$@."/network_access/share_path")
		 	{
			 	$permission=query("permission");
				if($permission!="")
				{
					$group=query("/nas/group:".$@."/name");
					//loop to get users in this gp
					$i = 1;
					$temp_member = query("/nas/group:".$@."/member:".$i);
					while($temp_member!="")
					{
						$member = $member." ".$temp_member;	
						echo "marco ".$member."".$i."\n";
						$i++;
						$temp_member = query("/nas/group:".$@."/member:".$i);
					}
					
					$folder="/tmp/storage_dev/";
					$folder=$folder.query("path");
					
					$oplocks=query("oplocks");
					$map=query("map_archive");
					$comment=query("comment");
					$share=query("share");
			
					fwrite2($network_access_config, "[ ".$share." ]\n");
					fwrite2($network_access_config, "\tcomment = ".$comment." \n");
					fwrite2($network_access_config, "\tpath = ".$folder." \n");
					fwrite2($network_access_config, "\tdns proxy = no \n");
					
					fwrite2($network_access_config, "\tvalid users = ".$member."\n");
					fwrite2($network_access_config, "\tguest ok = no \n");
					
					if($permission=="0")
					{fwrite2($network_access_config, "\tread only = no \n");}
					else
					{fwrite2($network_access_config, "\tread only = yes \n");}	
					
					fwrite2($network_access_config, "\toplocks = ".$oplocks." \n");
					fwrite2($network_access_config, "\tmap archive = ".$map." \n");
				}
			}			
		}
		*/
	echo "echo \"Start smbd...\" > /dev/console\n";
	//echo "smbd -s ".$network_access_config." -D \n"; //jana removed
	echo "smbpasswd -f ".$smb_tmp." \n";						
	echo "smbpasswd -a nobody -n \n";
}
else//del
{
	echo "echo \"Deluser ...\" > /dev/console\n";
	echo "deluser ".$name." \n"; 
	echo "smbpasswd -x ".$name." \n";
	fwrite($ftp_tbl,"");
	for ("/nas/user")//update ftp acc.
	{
		$permission=query("ftp/permission");
		if($permission!="")//for ftp acc.
		{
			$user=query("/nas/user:".$@."/name");
			fwrite2($ftp_tbl,"".$user.",".$permission."\n");
		}	
	}
	echo "killall smbd \n";//kill smbd first to update smb.conf
	/*jana removed
	$network_access_config = "/var/smb.conf";  //update smb conf
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
	for ("/nas/user")
	{
	 	$permission=query("network_access/permission");
		if($permission!="")
		{
			$user=query("/nas/user:".$@."/name");
			$folder="/tmp/";
			$folder=$folder.query("network_access/path");
			
			$oplocks=query("network_access/oplocks");
			$map=query("network_access/map_archive");
			$comment=query("network_access/comment");
			$share=query("network_access/share");
		
			fwrite2($network_access_config, "[ ".$share." ]\n");
			fwrite2($network_access_config, "\tcomment = ".$comment." \n");
			fwrite2($network_access_config, "\tpath = ".$folder." \n");
			fwrite2($network_access_config, "\tdns proxy = no \n");
				
			fwrite2($network_access_config, "\tvalid us0131ers = ".$user."\n");
			fwrite2($network_access_config, "\tguest ok = no \n");
				
			if($permission=="0")
			{fwrite2($network_access_config, "\tread only = no \n");}
			else
			{fwrite2($network_access_config, "\tread only = yes \n");}	
			
			fwrite2($network_access_config, "\toplocks = ".$oplocks." \n");
			fwrite2($network_access_config, "\tmap archive = ".$map." \n");
		}			
	}	
	for ("/nas/group")
	{
		$permission=query("network_access/permission");
		if($permission!="")
		{
			$group=query("/nas/group:".$@."/name");
			//loop to get users in this gp
			for(/nas/group/member)
			{
				$user=$user.query("/member")." ";					
			}
			$folder="/tmp/";
			$folder=$folder.query("network_access/path");
				
			$oplocks=query("network_access/oplocks");
			$map=query("network_access/map_archive");
			$comment=query("network_access/comment");
			$share=query("network_access/share");
		
			fwrite2($network_access_config, "[ ".$share." ]\n");
			fwrite2($network_access_config, "\tcomment = ".$comment." \n");
			fwrite2($network_access_config, "\tpath = ".$folder." \n");
			fwrite2($network_access_config, "\tdns proxy = no \n");
				
			fwrite2($network_access_config, "\tvalid users = ".$user."\n");
			fwrite2($network_access_config, "\tguest ok = no \n");
				
			if($permission=="0")
			{fwrite2($network_access_config, "\tread only = no \n");}
			else
			{fwrite2($network_access_config, "\tread only = yes \n");}	
				
			fwrite2($network_access_config, "\toplocks = ".$oplocks." \n");
			fwrite2($network_access_config, "\tmap archive = ".$map." \n");
		}			
	}
	echo "echo \"Start smbd...\" > /dev/console\n";
	echo "smbd -s ".$network_access_config." -D \n";
	*/
}
?>
