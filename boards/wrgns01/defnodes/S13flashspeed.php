<?
/* flash programming speed */
$flashspeed = query("/runtime/nvram/flashspeed");
if ($flashspeed == "")	{ $flashspeed=2900; }
if ($flashspeed < 1000)	{ $flashspeed=1000; }
$flashspeed = $flashspeed * 10 / 10;
set("/runtime/sys/info/fptime", $flashspeed);
set("/runtime/sys/info/bootuptime", 50);
?>
