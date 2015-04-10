<p>
正在更改该设备的LAN IP地址。<br><br>
需要几秒钟生效。<br><br>
您需要更改您的计算机的IP地址来访问设备。<br><br>
您可以通过下面的链接来访问该设备。
</p>
<br>
<?
$lan_ip=query("/lan/ethernet/ip");
$lan_url="http:\/\/".$lan_ip;
?>
<a href="<?=$lan_url?>"><?=$lan_url?></a>
<br><br>
