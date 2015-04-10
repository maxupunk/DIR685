<?
/* AP */
echo "APAifsn=3;7;1;1"		."\n";
echo "APCwmin=4;4;3;2"		."\n";
echo "APCwmax=6;10;4;3"		."\n";
if($WMM_PAR=="11b")	{	echo "APTxop=0;0;188;102"	."\n";}
else				{	echo "APTxop=0;0;94;47"		."\n";}
echo "APACM=0;0;0;0"		."\n";
/* STA */
echo "BSSAifsn=3;7;2;2"		."\n";
echo "BSSCwmin=4;4;3;2"		."\n";
echo "BSSCwmax=10;10;4;3"	."\n";
if($WMM_PAR=="11b")	{	echo "BSSTxop=0;0;188;102"	."\n";}
else				{	echo "BSSTxop=0;0;94;47"	."\n";}
echo "BSSACM=0;0;0;0"		."\n";

echo "AckPolicy=0;0;0;0"	."\n";
?>
