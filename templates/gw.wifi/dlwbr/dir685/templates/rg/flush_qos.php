# flush_qos.php >>>
iptables -t mangle -F POST_L7
<?
/* vi: set sw=4 ts=4:
 * generating rules for QOS Layer7.
 */
$layer7_mark_chain="POST_L7";
$qos_enable	= query("/qos/mode");
$IPTABLE_LAYER7="iptables -t mangle -A ".$layer7_mark_chain." -m layer7 --l7proto";
$IPTABLE_SET_MARK="-j MARK --set-mark";
if ($qos_enable=="1")
{
	echo "iptables -t mangle -A POSTROUTING -j ".$layer7_mark_chain." \n";

	echo $IPTABLE_LAYER7." sip ".$IPTABLE_SET_MARK." 0xb\n";
	echo $IPTABLE_LAYER7." skypetoskype ".$IPTABLE_SET_MARK." 0xb\n";
	echo $IPTABLE_LAYER7." httpvideo ".$IPTABLE_SET_MARK." 0xc\n";
	echo $IPTABLE_LAYER7." quicktime ".$IPTABLE_SET_MARK." 0xc\n";
	echo $IPTABLE_LAYER7." ftp ".$IPTABLE_SET_MARK." 0xe\n";
	echo $IPTABLE_LAYER7." msn-filetransfer ".$IPTABLE_SET_MARK." 0xe\n";
	echo $IPTABLE_LAYER7." http-dap ".$IPTABLE_SET_MARK." 0xe\n";
	echo $IPTABLE_LAYER7." http-freshdownload ".$IPTABLE_SET_MARK." 0xe\n";
	echo $IPTABLE_LAYER7." bittorrent ".$IPTABLE_SET_MARK." 0xf\n";
	echo $IPTABLE_LAYER7." edonkey ".$IPTABLE_SET_MARK." 0xf\n";
	echo $IPTABLE_LAYER7." fasttrack ".$IPTABLE_SET_MARK." 0xf\n";
	echo $IPTABLE_LAYER7." directconnect ".$IPTABLE_SET_MARK." 0xf\n";
	echo $IPTABLE_LAYER7." gnutella ".$IPTABLE_SET_MARK." 0xf\n";
	echo $IPTABLE_LAYER7." soulseek ".$IPTABLE_SET_MARK." 0xf\n";
	echo $IPTABLE_LAYER7." applejuice ".$IPTABLE_SET_MARK." 0xf\n";
}
?># flush_qos.php <<<
