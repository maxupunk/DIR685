<?
/* vi: set sw=4 ts=4: */
require("/etc/templates/troot.php");

$klog_pid="/var/run/klogd.pid";
$lanif=query("/runtime/layout/lanif");
$wanif=query("/runtime/wan/inf:1/interface");
if ($wanif=="") { $wanif=query("/runtime/layout/wanif"); }

if ($klogd_only != 1)
{
	$syslog_pid="/var/run/syslogd.pid";

	echo "if [ -f ".$syslog_pid." ]; then\n";
	echo "	PID=`cat ".$syslog_pid."`\n";
	echo "	if [ $PID != 0 ]; then\n";
	echo "		kill $PID > /dev/console 2>&1\n";
	echo "	fi\n";
	echo "	rm -f ".$syslog_pid."\n";
	echo "fi\n";

	$email_enable=query("/sys/log/emailenable");
	$email=query("/sys/log/email");
	$mail_auth_enable=query("/sys/log/emailauthenable");
	$opts="";
	anchor("/security/log");
	if (query("systeminfo")==1)		{ $opts=$opts." -F sysact"; }
	if (query("debuginfo")==1)		{ $opts=$opts." -F debug"; }
	if (query("attackinfo")==1)		{ $opts=$opts." -F attack"; }
	if (query("droppacketinfo")==1)	{ $opts=$opts." -F drop"; }
	if (query("noticeinfo")==1)		{ $opts=$opts." -F notice"; }
	if (email_enable == "1")
	{
		if ($mail_auth_enable == "0")	{$opts=$opts." -t /var/log/messages -m -a ".$email;}
		else							{$opts=$opts." -t /var/log/messages -m -A -a ".$email;}
	}
	$logenbale=query("/sys/log/logserverenable");
	$logsrv=query("/sys/log/logserver");
	if ($logenbale == "1" && $logsrv != "")
	{ $opts=$opts." -R \"".$logsrv.":514\""; }
	if ($opts != "")
	{
		echo "syslogd ".$opts." &\n";
		echo "echo $! > ".$syslog_pid."\n";
	}
}

echo "if [ -f ".$klog_pid." ]; then\n";
echo "	PID=`cat ".$klog_pid."`\n";
echo "	if [ $PID != 0 ]; then\n";
echo "		kill $PID > /dev/console 2>&1\n";
echo "	fi\n";
echo "	rm -f ".$klog_pid."\n";
echo "fi\n";
echo "klogd -l ".$lanif." -w ".$wanif." &\n";
echo "echo $! > ".$klog_pid."\n";

?>
