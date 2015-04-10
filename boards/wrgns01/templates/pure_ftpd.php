#!/bin/sh
echo [$0] ... > /dev/console
<?
/* vi: set sw=4 ts=4: */
require("/etc/templates/troot.php");
$ftp_tbl="/etc/ftp_tbl";
$ftpgroup="/etc/ftpgroup";
$shadow_file="/etc/shadow";
$passwd_file="/etc/passwd";
if ($generate_start==1)
{
	if (query("/nas/ftp/enable")!="1")
	{
		echo "echo pure_ftpd is disabled ! > /dev/console\n";
	}
	else
	{
		anchor("/nas/ftp");
		$max_user=query("max_user");
		$idle_time=query("idle_time");
		$port=query("port");
		$language=query("language");		
		$flow_control = query("flow_control")*10;	
		if ($flow_control=="")	{$flow_control="0";} 
		$mode=query(mode);
		if($mode=="1")
		{
			$ip_address=query("/lan/ethernet/ip");
			$ip_address=$ip_address.",";
			$tmp_iptables_command=query("/runtime/ftp/iptables_rules");
			if($tmp_iptables_command!="")
			{	echo "".$tmp_iptables_command."";}
		}
		else if($mode=="2")
		{	
			$tmp_iptables_command=query("/runtime/ftp/iptables_rules");
			$interface=query("/runtime/wan/inf:1/interface");
			if($interface=="")
			{
				$wan_ip=query("/runtime/wan/inf:1/ip");
			}
			if($tmp_iptables_command!="")
			{	echo "".$tmp_iptables_command."";}
			if($interface=="")
			{
				if($wan_ip!="")
				{
					echo "iptables -t nat -A PRE_MISC -d ".$wan_ip." -p tcp --dport ".$port." -j ACCEPT > /dev/console\n";//jana added
					$tmp_iptables_command="iptables -t nat -D PRE_MISC -d ".$wan_ip." -p tcp --dport ".$port." -j ACCEPT > /dev/console\n";
				}
			}			
			else
			{
				echo "iptables -t nat -A PRE_MISC -i ".$interface." -p tcp --dport ".$port." -j ACCEPT > /dev/console\n";//jana added
				$tmp_iptables_command="iptables -t nat -D PRE_MISC -i ".$interface." -p tcp --dport ".$port." -j ACCEPT > /dev/console\n";
			}			
			$ip_address=query("/runtime/wan/inf:1/ip");
			$ip_address=$ip_address.",";
			
			set("/runtime/ftp/iptables_rules",$tmp_iptables_command);
		}
		else
		{	
			$tmp_iptables_command=query("/runtime/ftp/iptables_rules");
			if($tmp_iptables_command!="")
			{	echo "".$tmp_iptables_command."";}
			$interface=query("/runtime/wan/inf:1/interface");
			if($interface=="")
			{
				$wan_ip=query("/runtime/wan/inf:1/ip");
			}
			if($interface=="")
			{
				if($wan_ip!="")
				{
					echo "iptables -t nat -A PRE_MISC -d ".$wan_ip." -p tcp --dport ".$port." -j ACCEPT > /dev/console\n";//jana added
					$tmp_iptables_command="iptables -t nat -D PRE_MISC -d ".$wan_ip." -p tcp --dport ".$port." -j ACCEPT > /dev/console\n";
				}
			}			
			else
			{
				echo "iptables -t nat -A PRE_MISC -i ".$interface." -p tcp --dport ".$port." -j ACCEPT > /dev/console\n";//jana added
				$tmp_iptables_command="iptables -t nat -D PRE_MISC -i ".$interface." -p tcp --dport ".$port." -j ACCEPT > /dev/console\n";
			}	
			 set("/runtime/ftp/iptables_rules",$tmp_iptables_command);
			$ip_address="";}
		fwrite($ftp_tbl,"");
		fwrite($ftpgroup,"");
		fwrite($shadow_file,"");
		fwrite($passwd_file,"root:x:0:0:Linux User,,,:/:/bin/sh\n");
		fwrite2($passwd_file,"nobody:x:500:500:Linux User,,,:/:/bin/sh\n");//for smb guest account
		for ("/nas/user")
		{
			$permission=query("ftp/permission");
			$user=query("name");
			$password=query("password");
			$path=query("ftp/path");
				
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
				//echo "adduser ".$user." -p ".$password." -h ".$root_path."\n";//jana removed		
				echo "adduser ".$user." -p ".$password." -h "."\"".$root_path."\""."\n";//jana added
			}
			else
			{
				//echo "adduser ".$user." -g ".$group." -p ".$password." -h ".$root_path."\n";//jana removed	
				echo "adduser ".$user." -g ".$group." -p ".$password." -h "."\"".$root_path."\""."\n";//jana added
			}
			
		}
		for ("/nas/group")
		{
		
			$permission=query("ftp/permission");
			if($permission!="")
			{
				$group=query("name");
				fwrite2($ftpgroup,"".$group.",".$permission."\n");
			}
		}
		//check annoy account enable or not
		$permission=query("/nas/ftp/permission");
		if($permission!="")
		{
			fwrite2($ftp_tbl,"anonymous,".$permission."\n");
			$path="/tmp/storage_dev/";
			$path=$path.query("/nas/ftp/path");
			fwrite2("/var/passwd","ftp:*:95:95::".$path.":/bin/sh\n");
		}
		echo "echo \"Start pure_ftpd...\" > /dev/console\n";
		
		if($flow_control=="0")
		{
			echo "pure-ftpd -c ".$max_user." -I ".$idle_time." -S ".$ip_address."".$port." -8 UTF-8 -9 ".$language." -A -H -U 0:0 & \n";		
		}
		else
		{
			echo "pure-ftpd -c ".$max_user." -I ".$idle_time." -S ".$ip_address."".$port." -8 UTF-8 -9 ".$language." -t ".$flow_control." -T ".$flow_control." -A -H -U 0:0 & \n";		
		}
		
	}
}
else
{
	if (query("/nas/ftp/enable")!="1")
	{
		echo "echo pure_ftpd is disabled ! > /dev/console\n";
	}
	else
	{	
		echo "echo \"Stop pure_ftpd ...\" > /dev/console\n";
		echo "killall -w pure-ftpd\n"; 
		$tmp_iptables_command=query("/runtime/ftp/iptables_rules");
		if($tmp_iptables_command!="")
		{	echo "".$tmp_iptables_command."";}
	}
}
?>
