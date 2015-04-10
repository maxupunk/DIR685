<p>
공유기의 LAN IP 주소가 변경됩니다. <br><br>
IP 주소가 변경 되는데 수 초가 걸립니다. <br><br>
공유기에 접속하기 위해서 PC의 IP 주소를 변경해야 할 수 도 있습니다. <br><br>
아래 링크로 공유기에 접속할 수 있습니다. 
</p>
<br>
<?
$lan_ip=query("/lan/ethernet/ip");
$lan_url="http:\/\/".$lan_ip;
?>
<a href="<?=$lan_url?>"><?=$lan_url?></a>
<br><br>
