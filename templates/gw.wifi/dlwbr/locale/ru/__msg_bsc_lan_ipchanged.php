﻿<p>
Изменение IP-адреса LAN для этого устройства.<br><br>
Подождите несколько секунд.<br><br>
Для получения доступа к устройству, возможно, следует изменить IP-адрес компьютера.<br><br>
Кликните по ссылке ниже, чтобы получить доступ к устройству.
</p>
<br>
<?
$lan_ip=query("/lan/ethernet/ip");
$lan_url="http:\/\/".$lan_ip;
?>
<a href="<?=$lan_url?>"><?=$lan_url?></a>
<br><br>
