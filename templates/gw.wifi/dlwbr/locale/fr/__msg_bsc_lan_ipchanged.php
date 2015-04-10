<p>
L'adresse IP du LAN de l'appareil est en cours de modification.<br><br>
Le changement prendra effet dans quelques secondes.<br><br>
Vous devrez peut-être changer l'adresse IP de votre ordinateur pour accéder à l'appareil.<br><br>
Pour accéder à l'appareil, cliquez sur le lien ci-dessous.
</p>
<br>
<?
$lan_ip=query("/lan/ethernet/ip");
$lan_url="http:\/\/".$lan_ip;
?>
<a href="<?=$lan_url?>"><?=$lan_url?></a>
<br><br>
