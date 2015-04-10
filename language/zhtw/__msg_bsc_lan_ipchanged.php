<p>
此裝置的 LAN IP 位址正在變更。<br><br>
需要數秒鐘生效。<br><br>
您可能必須變更電腦的 IP 位址，才能存取裝置。<br><br>
您可以透過下列鏈結來存取裝置。
</p>
<br>
<?
$lan_ip=query("/lan/ethernet/ip");
$lan_url="http:\/\/".$lan_ip;
?>
<a href="<?=$lan_url?>"><?=$lan_url?></a>
<br><br>
