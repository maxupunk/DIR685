<p>
La dirección IP de LAN de este dispositivo está cambiando.<br><br>
Necesita varios segundos para que surta efecto.<br><br>
Puede que necesite cambiar la dirección IP de su ordenador para acceder al dispositivo.<br><br>
Puede acceder al dispositivo mediante el enlace siguiente.
</p>
<br>
<?
$lan_ip=query("/lan/ethernet/ip");
$lan_url="http:\/\/".$lan_ip;
?>
<a href="<?=$lan_url?>"><?=$lan_url?></a>
<br><br>
