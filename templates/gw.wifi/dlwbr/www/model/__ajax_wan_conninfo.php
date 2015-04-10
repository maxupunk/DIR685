var __result=<?
if(query("/runtime/wan/inf:1/connectstatus")=="connected" && query("/runtime/switch/wan_port/linktype")!="0")
{
	$conn_status="connected";
}
else
{
	$conn_status="disconnected";
}
?>new Array("OK", "<?=$conn_status?>");
