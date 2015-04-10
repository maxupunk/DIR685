<?
/* -------------------------------------------- get config ----------------------------------------*/
/* Count the BSSID number */
$bssid_num = 1;
$mbssid_en=query("/gzone/members/wlan:2/enable");
if ($mbssid_en=="1" && query("/runtime/router/enable")==1) {$bssid_num=2;}
/* -------- RT2860AP.dat -------*/
echo "BssidNum="	.$bssid_num ."\n";
/* -------------------------------------------- get config ----------------------------------------*/
$STR_H_SSID			="";
$STR_WMM			="";
$STR_MCS			="";
$STR_AUTH			="";
$STR_ENCRYPT		="";
$STR_AUTH			="";
$STR_ENCRYPT		="";
$STR_PSK			="";
$STR_WEP_DEF_INDEX	="";
$STR_WEP_TYPE		="";
$STR_WEP			="";
$STR_1X				="";
$STR_NO_FORWARDING 	="";

$div				="";

$inf=0;
//+++ Teresa, avoid while loop reset value
$need_wep_count=0;
$need_psk_count=0;
//--- Teresa, avoid while loop reset value
while($inf < $bssid_num)
{
	$inf++;
	if ($inf=="1")	{anchor("/wireless");}
	else			{anchor("/wlan/inf:".$inf);}

	/* hidden ssid */
	$tmp_h_ssid		=query("ssidhidden");		if ($tmp_h_ssid=="")	{$tmp_h_ssid="0";}
	$STR_H_SSID		=$STR_H_SSID.$div.$tmp_h_ssid;
	/* wmm , make the wmm value of all bssids following the main bssid's. */
	$tmp_wmm		=query("/wireless/wmm");				if ($tmp_wmm=="")		{$tmp_wmm="0";}
	$STR_WMM		=$STR_WMM.$div.$tmp_wmm;
	/* mcs (txrate) */
	$tmp_wlanmode	=query("wlanmode");			if ($tmp_wlanmode=="")	{$tmp_wlanmode	="7";}
	$tmp_txrate		=query("txrate");			if ($tmp_txrate=="")	{$tmp_txrate	="0";}
	$tmp_mcs_en		=query("mcs/enable");		if ($tmp_mcs_en=="")	{$tmp_mcs_en	="0";}
	if ($tmp_wlanmode =="4") /* 11n only */
	{
		if (query("mcs/auto")=="1")	{$tmp_mcs_index="33";}
		else
		{
			$mcs_index = query("mcs/index");
			if ($mcs_index=="") {$mcs_index=33;}
			$tmp_mcs_index  =$mcs_index;
		}
	}
	else if ($tmp_wlanmode=="1" || $tmp_wlanmode=="2") /* 11g only, or 11b only */
	{
		/* Ralink is no more support txtrae parameter, 
		 * instead, tx rate is set by  "WirelessMode" and "HT_MCS" combination.		*/
		/*          11B                     11G                               		*/
		/*--------------------------------------------------------------------------*/
		if		($tmp_txrate == "1"		||	$tmp_txrate == "6")	{$tmp_mcs_index = 0; }
		else if ($tmp_txrate == "2"		||	$tmp_txrate == "9")	{$tmp_mcs_index = 1; }
		else if ($tmp_txrate == "5.5"	||	$tmp_txrate == "12"){$tmp_mcs_index = 2; }
		else if ($tmp_txrate == "11"	||	$tmp_txrate == "18"){$tmp_mcs_index = 3; }
		else if (							$tmp_txrate == "24"){$tmp_mcs_index = 4; }
		else if (							$tmp_txrate == "36"){$tmp_mcs_index = 5; }
		else if (							$tmp_txrate == "48"){$tmp_mcs_index = 6; }
		else if (							$tmp_txrate == "54"){$tmp_mcs_index = 7; }
		else													{$tmp_mcs_index = 33;}/* set default as "auto" */
	}
	else	/* other mixed mode, so set the mcs as "auto". */
	{
		$tmp_mcs_index="33";
	}
	$STR_MCS	=$STR_MCS.$div.$tmp_mcs_index;

	/* auth and encrytption */
	/* auth_type:
		 0:open system, 1:share key,
		 2: WPA, 3: WPA-PSK, 
		 4: WPA2, 5: WPA2-PSK, 
		 6: WPA + WPA2, 7: WPA-PSK + WPA2-PSK,
		 8:802.1X 
	*/
	$tmp_authtype		=query("authtype");
	$tmp_encrypttype	=query("encrypttype");
	
	//all wpa related packets will be handled by hostapd
	if($tmp_authtype != "0" && $tmp_authtype != "1" ) 
	{
		$tmp_authtype		="0";
		$tmp_encrypttype	="0";
	}
	$need_wep			="0";
	$need_psk			="0";
	if ($tmp_authtype=="0")
	{
		$STR_AUTH	=$STR_AUTH.$div."OPEN";
		if ($tmp_encrypttype=="1")	{$STR_ENCRYPT=$STR_ENCRYPT.$div."WEP";		$need_wep="1";	$need_wep_count++;}
		else						{$STR_ENCRYPT=$STR_ENCRYPT.$div."NONE";	}
	}
	else if ($tmp_authtype=="1")
	{
		$STR_AUTH	=$STR_AUTH.$div."SHARED";
		$STR_ENCRYPT=$STR_ENCRYPT.$div."WEP";
		$need_wep	="1";
		$need_wep_count++;
	}
	else if ($tmp_authtype=="2")
	{
		$STR_AUTH	=$STR_AUTH.$div."WPA";
		$need_radius="1";
	}
	else if ($tmp_authtype=="3")
	{
		$STR_AUTH	=$STR_AUTH.$div."WPAPSK";
		$need_psk	="1";
		$need_psk_count++;
	}
	else if ($tmp_authtype=="4")
	{
		$STR_AUTH	=$STR_AUTH.$div."WPA2";
		$need_radius="1";
	}
	else if ($tmp_authtype=="5")
	{
		$STR_AUTH	=$STR_AUTH.$div."WPA2PSK";
		$need_psk	="1";
		$need_psk_count++;
	}
	else if ($tmp_authtype=="6")
	{
		$STR_AUTH	=$STR_AUTH.$div."WPA1WPA2";
		$need_radius="1";
	}
	else if ($tmp_authtype=="7")
	{
		$STR_AUTH	=$STR_AUTH.$div."WPAPSKWPA2PSK";
		$need_psk	="1";
		$need_psk_count++;
	}
	if ($tmp_authtype>=2)
	{
		$STR_1X		=$STR_1X.$div."0";
		if 		($tmp_encrypttype=="2")	{$STR_ENCRYPT=$STR_ENCRYPT.$div."TKIP";}
		else if ($tmp_encrypttype=="3")	{$STR_ENCRYPT=$STR_ENCRYPT.$div."AES";}
		else 							{$STR_ENCRYPT=$STR_ENCRYPT.$div."TKIPAES";}
	}
	
	/* -------- RT2860AP.dat -------*/
	/* ssid */
	echo "SSID".$inf."=".query("ssid")."\n";
	/*------------------------------*/
	if ($need_wep=="1")
	{
		$tmp_defkey_index	=query("wep/defkey");
		$tmp_keytype		=query("wep/format");
		if ($tmp_keytype=="1")	{$tmp_keytype="1";}	/* ASCII */
		else 					{$tmp_keytype="0";} /* Hex */
		if ($div!="")
		{
			/* give the dummy info for primary bssid.*/
			if ($STR_WEP_DEF_INDEX=="")	{$STR_WEP_DEF_INDEX="1";}
			if ($STR_WEP_TYPE=="")		{$STR_WEP_TYPE="0";}
		}
		$STR_WEP_DEF_INDEX	=$STR_WEP_DEF_INDEX.$div.$tmp_defkey_index;
		$STR_WEP_TYPE		=$STR_WEP_TYPE.$div.$tmp_keytype;
		
		/* -------- RT2860AP.dat -------*/
		echo "Key".$tmp_defkey_index."Str".$inf."=".query("wep/key:".$tmp_defkey_index)."\n";
		/*------------------------------*/
	}
	if ($need_psk=="1")
	{
		$tmp_psk = query("wpa/key");
		/* -------- RT2860AP.dat -------*/
		if ($tmp_psk!=""){echo "WPAPSK".$inf."=".query("wpa/key")."\n";}
		/*------------------------------*/
	}

	if( query("bridge/wlan2wlan") == "0")
	{
		$STR_NO_FORWARDING = $STR_NO_FORWARDING.$div."1";
	}
	else
	{
		$STR_NO_FORWARDING = $STR_NO_FORWARDING.$div."0";
	}
	
	$div=";";
}

/* bridge */
echo "NoForwarding="	.$STR_NO_FORWARDING."\n";
echo "NoForwardingBTNBSSID=1;1\n";
//if( query(/wlan/inf:2/bridge/wlan2wlan)=="0" )
//{
//	echo "NoForwardingBTNBSSID=1\n";
//}
//else
//{
//	echo "NoForwardingBTNBSSID=0\n";
//}
////remove the internal bridge in wireless card if we need multiple ssid
//if ($mbssid_en=="1")
//{
//	echo "BUILT_IN_BRIDGE=0\n";
//}

/* -------- RT2860AP.dat -------*/
echo "HT_MCS="			.$STR_MCS			."\n";
echo "HideSSID="		.$STR_H_SSID		."\n";
/* Authentication */
echo "AuthMode="		.$STR_AUTH			."\n";
echo "EncrypType="		.$STR_ENCRYPT		."\n";

//if ($need_wep=="1")	//+++ Teresa, avoid while loop reset value
if ($need_wep_count > 0)
{
	echo "DefaultKeyID="	.$STR_WEP_DEF_INDEX	."\n";
	echo "Key1Type="		.$STR_WEP_TYPE		."\n";
	echo "Key2Type="		.$STR_WEP_TYPE		."\n";
	echo "Key3Type="		.$STR_WEP_TYPE		."\n";
	echo "Key4Type="		.$STR_WEP_TYPE		."\n";
}
if ($STR_1X!="")
{
	echo "IEEE8021X="		.$STR_1X			."\n";
}
if ($need_radius=="1")	/* WPA, WPA2, WPA/WPA2 */
{
	anchor("/wireless/wpa/radius:1");
	$STR_RADIUS_SRV	=query("host");
	$STR_RADIUS_PORT=query("port");
	$STR_KEY		=query("secret");
	echo "RADIUS_Server="	.$STR_RADIUS_SRV	."\n";
	echo "RADIUS_Port="		.$STR_RADIUS_PORT	."\n";
	echo "RADIUS_Key=".		.$STR_KEY			."\n";
}
//if ($need_radius=="1" || $need_psk=="1")	//+++ Teresa, avoid while loop reset value
if ($need_radius=="1" || $need_psk_count > 0)
{
	anchor("/wireless");
	$rekey_interval =query("wpa/grp_rekey_interval");
	$pmk_period     =query("wpa/pmkperiod");    if ($pmk_period=="")    {$pmk_period="10";}
	$rekey_method   =query("wpa/rekeymethod");  if ($rekey_method=="")  {$rekey_method="DISABLE";}
	echo "RekeyInterval="	.$rekey_interval	."\n";
	echo "RekeyMethod="		.$rekey_method		."\n";
	echo "PMKCachePeriod="	.$pmk_period		."\n";
	echo "own_ip_addr="		.$wlan_ip			."\n";
}


/* -------------------------------------------- get config ----------------------------------------*/
$txburst	="1";
$wmm		=query("/wireless/wmm");	if ($wmm=="1"){$txburst="0";}
/* -------- RT2860AP.dat -------*/
/* WMM */
$vista_logo = query("/wireless/auth_logo");

echo "WmmCapable="		.$STR_WMM	."\n";
echo "APSDCapable="		.$STR_WMM	."\n";
echo "TxBurst="			.$txburst	."\n";
/***********************************************************************************
 * Ralink:
 *	1. no matter wmm is diabled or enabled, the WMM parameters should be set.
 *	2. Both of parameter for STA and AP have to be set. (from Ralink)
 ***********************************************************************************/
echo "APAifsn=3;7;1;1"		."\n";
if ($vista_logo=="1")
{ echo "APCwmin=3;3;3;2"	."\n"; }
else
{ echo "APCwmin=4;4;3;2" 	."\n"; }
echo "APCwmax=6;10;4;3"		."\n";
echo "APTxop=0;0;94;47"		."\n";	//for 11a/g
//echo "APTxop=0;0;188;102"	."\n";	//for 11b
echo "APACM=0;0;0;0"		."\n";

echo "BSSAifsn=3;7;2;2"		."\n";
echo "BSSCwmin=4;4;3;2"		."\n";
echo "BSSCwmax=10;10;4;3"	."\n";
echo "BSSTxop=0;0;94;47"	."\n";
echo "BSSACM=0;0;0;0"		."\n";

echo "AckPolicy=0;0;0;0"	."\n";
?>
