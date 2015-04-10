<? /* vi: set sw=4 ts=4: */
/* Get values */
$imgsig	= fread("/etc/config/image_sign");
$bver	= fread("/etc/config/buildver");
$bnum	= fread("/etc/config/buildno");
$bdate	= fread("/etc/config/builddate");
$lanmac	= query("/runtime/nvram/lanmac");
$lan2mac= query("/runtime/nvram/lan2mac");
$wanmac	= query("/runtime/nvram/wanmac");
$hwrev	= query("/runtime/nvram/hwrev");
$pin	= query("/runtime/nvram/pin");
$ccode	= query("/runtime/nvram/countrycode");
/* sanity check */
if ($lanmac == "")	{ $lanmac="00:de:fa:15:00:01"; }
if ($lan2mac == "")	{ $lan2mac="00:de:fa:15:a1:02"; }
if ($wanmac == "")	{ $wanmac="00:de:fa:15:00:02"; }
if ($hwrev  == "")	{ $hwrev="N/A"; }
if ($ccode	== "")	{ $ccode = "840";}
/* SET nodes */
/* -- layout */
set("/runtime/layout/image_sign", "");
anchor("/runtime/layout");
	set("image_sign",	$imgsig);
	set("wanmac",		$wanmac);
	set("lanmac",		$lanmac);
	set("lanmac2",		$lan2mac);
	set("wlanmac",		$lanmac);
	set("wlanmac2",		$lan2mac);
	set("wanif",		"eth1");
	set("lanif",		"br0");
	set("wlanif",		"ra0");
	set("lanif2",		"br1");
	set("wlanif2",		"ra1");
	set("countrycode",	$ccode);
/* -- sys info*/
set("/runtime/sys/info/dummy", "");
anchor("/runtime/sys/info");
	set("hardwareversion",	$hwrev);
	set("firmwareversion",	$bver);
	set("firmwarebuildno",	$bnum);
	set("firmwarebuildate",	$bdate);
/* -- WPS pin */
set("/runtime/wps/pin",		$pin);
/* -- others */
set("/sys/telnetd",			"true");
set("/sys/sessiontimeout",	"600");
set("/proc/web/sessionum",	"8");
set("/proc/web/authnum",	"6");
?>
