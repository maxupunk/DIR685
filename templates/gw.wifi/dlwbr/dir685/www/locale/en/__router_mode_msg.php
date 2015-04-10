<div id="show_wait_msg" >
<p>The device is changing to router mode...</p>
Please <font color=red><b>DO NOT POWER OFF</b></font> the device.<br><br>
Please wait for
<input type='Text' readonly name='WaitInfo' value='150' size='2'
style='border-width:0; background-color:#DFDFDF; color:#FF3030; text-align:center'>
seconds...
<br><br>
</div>

<div id="show_msg" style="display:none">
<p>You may need to change the IP address of your computer to access the device.</p>
<p>You can access the device by clicking the link below.</p>
<?
	$ipaddr = query("/lan/ethernet/ip");
	echo "<p><a href=http:\/\/".$ipaddr.">http:\/\/".$ipaddr."</a></p>\n"; 
?>
<br>
</div>
