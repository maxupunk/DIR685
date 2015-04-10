<?
$ccode		=query("/runtime/nvram/countrycode");
if($ccode=="392" || $ccode=="JP" && query("/wlan/inf:3/outdoor")!=1 )
{ 
	$ch_low_start=36; 
	$ch_low_end=64;
	$ch_high_start=100;
	$ch_high_end=140;
}
else if($ccode=="826" || $ccode=="GB")	/*FCC*/
{
	$ch_low_start=36; 
	$ch_low_end=64;
	$ch_high_start=100;
	$ch_high_end=140;
}
else if($ccode=="840"|| $ccode=="US")	/*MKK*/
{
	$ch_low_start=36; 
	/* now not support dfs
	$ch_low_end=64;
	*/
	$ch_low_end=48;
	$ch_high_start=149;
	$ch_high_end=165;
}
else
{
	$ch_low_start=36; 
	$ch_low_end=64;
	$ch_high_start=149;
	$ch_high_end=165;
}

$INDEX=$ch_low_start;
while($INDEX<=$ch_low_end)
{
	echo "<option value='".$INDEX."'>".$INDEX."</option>\n";
	$INDEX=$INDEX+4;
}
$INDEX=$ch_high_start;
while($INDEX<=$ch_high_end)
{
	echo "<option value='".$INDEX."'>".$INDEX."</option>\n";
	$INDEX=$INDEX+4;
}

?>
