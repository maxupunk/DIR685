<p>
L'indirizzo IP LAN del dispositivo verr¨¤ modificato.<br><br>
La modifica richiede alcuni secondi.<br><br>
Potrebbe essere necessario modificare l'indirizzo IP del computer per poter accedere al dispositivo.<br><br>
Per accedere al dispositivo, fare clic sul collegamento seguente.
</p>
<br>
<?
$lan_ip=query("/lan/ethernet/ip");
$lan_url="http:\/\/".$lan_ip;
?>
<a href="<?=$lan_url?>"><?=$lan_url?></a>
<br><br>
