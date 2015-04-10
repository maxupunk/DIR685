<?
set("/sys/modelname",	"DIR-685");
anchor("/sys");
set("devicename",		"D-Link Wireless Router");
set("modeldescription",	"Wireless G Router");
set("vendor",			"D-Link");
set("hwversion",		"A1");
set("url",				"http:\/\/www.dlink.com.tw");
set("supporturl",		"http:\/\/support.dlink.com.tw");
set("ipaddr",			"192.168.0.1");
set("netmask",			"255.255.255.0");
set("startip",			"192.168.0.100");
set("endip",			"192.168.0.199");
set("ssid",				"dlink");
set("authtype",			"s");
set("fwinfosrv",		"wrpd.dlink.com.tw");
set("fwinfopath",		"/router/firmware/query.asp");
set("wlandriverver",    "Ralink RT2880 iNIC v1.1.8.3");
set("kernel_version",		"Linux version 2.6.15");//jana added
set("/widget/version","v2");//jana added

set("/lan/dhcp/server/pool:1/staticdhcp/max_client", "25");
set("/routing/route/max_rules",	"20");

set("/nat/vrtsrv/max_rules",			25);
set("/nat/porttrigger/max_rules",		25);
set("/security/macfilter/max_rules",	25);
set("/security/urlblocking/max_rules",	25);
set("/security/firewall/max_rules",		50);
set("/routing/route/max_rules",			32);

/* function availability */
set("/runtime/func/superg",				"0");
set("/runtime/func/wps",				"1");
set("/runtime/func/static_dhcp",		"1");
set("/runtime/func/firewall",			"1");
set("/runtime/func/log_setting",		"1");
set("/runtime/func/schedule",			"1");
set("/runtime/func/schedule/vrtsrv",	"0");
set("/runtime/func/schedule/portt", 	"0");
set("/runtime/func/schedule/macfilter", "1");
set("/runtime/func/schedule/firewall",	"1");
set("/runtime/func/neaps",				"1");
set("/runtime/func/wfadev",				"1");
/*set("/runtime/func/lpd",				"1");*/
set("/runtime/func/widget/yahoo",		"1");
set("/runtime/func/ieee80211n", 		"1");
set("/runtime/func/wwan_3g", 			"1");

/*Hendry add*/
set("/runtime/httpd/maxuploadsize",		"16384000");
?>
