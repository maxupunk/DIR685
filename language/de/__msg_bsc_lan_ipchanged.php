<p>
Die LAN-IP-Adresse des Geräts wird geändert.<br><br>
Es dauert einige Sekunden, bis die Einstellungen wirksam werden.<br><br>
Unter Umständen muss für den Zugriff auf das Gerät die IP-Adresse des Computers geändert werden.<br><br>
Über die nachfolgende Verknüpfung können Sie auf das Gerät zugreifen.
</p>
<br>
<?
$lan_ip=query("/lan/ethernet/ip");
$lan_url="http:\/\/".$lan_ip;
?>
<a href="<?=$lan_url?>"><?=$lan_url?></a>
<br><br>
