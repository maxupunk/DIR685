<?
$lc_dbg_msg="0";

if ($LOCK_CLIENT_TYPE=="gzone")
{
	$path_dhcp_lease	= "/runtime/dhcpserver:2/lease";
	$path_static_dhcp	= "/gzone/dhcp/server/pool:1/staticdhcp";
	$path_mac_filter	= "/gzone/macfilter";
	$max_static_dhcp	= query("/gzone/dhcp/server/pool:1/staticdhcp/max_client")
	$max_mac_filter		= query("/gzone/macfilter/max_rules");
	if ($max_static_dhcp	==""){$max_static_dhcp	=25;}
	if ($max_mac_filter		==""){$max_mac_filter	=25;}
}
else
{
	$path_dhcp_lease	= "/runtime/dhcpserver/lease";
	$path_static_dhcp	= "/lan/dhcp/server/pool:1/staticdhcp";
	$path_mac_filter	= "/security/macfilter";
	$max_static_dhcp	= query("/lan/dhcp/server/pool:1/staticdhcp/max_client")
	$max_mac_filter		= query("/security/macfilter/max_rules");
	if ($max_static_dhcp	==""){$max_static_dhcp	=25;}
	if ($max_mac_filter		==""){$max_mac_filter	=25;}
}
if ($max_static_dhcp > $max_mac_filter)	{$max_rules=$max_static_dhcp;	$min_rules=$max_mac_filter;}
else									{$max_rules=$max_mac_filter;	$min_rules=$max_static_dhcp;}

if ($lc_dbg_msg=="1")	{echo "<!--\n";}

if ($ENABLE_LOCK_CLIENT=="1")
{
	/* enable the MAC filter */
	set($path_mac_filter."/enable", "1");
	set($path_mac_filter."/action", "1");

	set($path_static_dhcp."/enable", "1");
	$lc_index=0;
	$dhcp_index=0;
	for($path_dhcp_lease)
	{
		$dhcp_index++;
		$dhcp_entry = $path_dhcp_lease.":".$dhcp_index;

		if ($lc_dbg_msg=="1")
		{
			echo "-----------------------------------\n";
			echo "lc_index="	.$lc_index		."\t";
			echo "min_rules="	.$min_rules		."\n";
			echo "dhcp_index="	.$dhcp_index	."\n";
			echo "expire="	.query($dhcp_entry."/expire")."\n";
		}
		if (query($dhcp_entry."/expire")>0 && $lc_index <= $min_rules)
		{
			$lc_index++;
			/* static dhcp client list */
			$path_entry=$path_static_dhcp."/entry:".$lc_index;
			set($path_entry."/enable",		"1");
			set($path_entry."/mac",			query($dhcp_entry."/mac"));
			set($path_entry."/ip",			query($dhcp_entry."/ip"));
			set($path_entry."/hostname",	query($dhcp_entry."/hostname"));

			if ($lc_dbg_msg=="1")
			{
				echo "path_entry="	.$path_entry	."\n";
				echo "set enable="	.query($path_entry."/enable")	.";";
				echo "\t mac="		.query($path_entry."/mac")		.";";
				echo "\t ip="		.query($path_entry."/ip")		.";";
				echo "\t hostname="	.query($path_entry."/hostname")	."\n\n";
			}
			
			/* mac filter rules */
			$path_entry=$path_mac_filter."/entry:".$lc_index;
			set($path_entry."/enable",		"1");
			set($path_entry."/mac",			query($dhcp_entry."/mac"));
			set($path_entry."/schedule/id",	"");

			if ($lc_dbg_msg=="1")
			{
				echo "path_entry="	.$path_entry	."\n";
				echo "set mac="			.query($path_entry."/mac")	.";";
				echo "\t schedule="		.query($path_entry."/schedule/id")	."\n";
			}
		}
	}
	$clear_index=$max_rules;
	while($clear_index > $lc_index)
	{
		$path_entry=$path_static_dhcp."/entry:".$clear_index;	del($path_entry);
		if ($lc_dbg_msg=="1")	{echo "del [".$path_entry."]\n";}
		
		$path_entry=$path_mac_filter."/entry:".$clear_index;	del($path_entry);
		if ($lc_dbg_msg=="1")	{echo "del [".$path_entry."]\n";}
		
		$clear_index--;
	}
}
else
{
	/* enable the MAC filter */
	set($path_mac_filter."/enable", "0");
	set($path_mac_filter."/action", "0");

	$lc_index=$max_rules;
	while($lc_index > 0)
	{
		$path_entry=$path_static_dhcp."/entry:".$lc_index;
		del($path_entry);
		if ($lc_dbg_msg=="1")	{echo "del [".$path_entry."]\n";}
		
		$path_entry=$path_mac_filter."/entry:".$lc_index;
		del($path_entry);
		if ($lc_dbg_msg=="1")	{echo "del [".$path_entry."]\n";}

		$lc_index--;
	}
}

if ($lc_dbg_msg=="1")	{echo "-->\n";}

?>
