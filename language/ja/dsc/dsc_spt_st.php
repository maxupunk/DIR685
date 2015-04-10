<div class="box">
<a name="device_info"><h2>デバイス情報</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=39> 
このページでは、<?query("/sys/modelname");?>の現在の情報が表示されます。また現在デバイスで使用しているファームウェアバージョンも表示されます。
<br>

&nbsp;<br>
<strong><em>LAN (Local Area Network) - </em></strong>LANインタフェースのMACアドレス、IPアドレスおよびサブネットマスクが表示されます。またルータの内蔵DHCPサーバの状態（有効/無効）も表示されます。<br>
<strong><em>WAN (Wide Area Network) - </em></strong>WANインタフェースのMACアドレス、IPアドレスおよびサブネットマスク、デフォルトゲートウェイ、およびISPから取得したDNSサーバの情報が表示されます。また、ISPとの接続タイプ（ダイナミック、スタティック、またはPPPoE）も表示されます。ルータの設定が動的に行われている場合は、WANインタフェースに割り当てるIPアドレスのリリースおよび更新を行うボタンも表示されます。ルータにPPPoEの設定が行われている場合は、PPPoEセッションの接続/切断を行うボタンが表示されます。<br> 
<strong><em>
無線802.11
<? if(query("/runtime/func/ieee80211n") != "1") { echo "g"; } else { echo "n"; }?>
 - 
</em></strong>SSID、チャネル、および無線インタフェースにおいて暗号化が有効化されているかが表示されます。</td>
</tr>
</table>
</div>


<div class="box">
<a name="log"><h2>ログ</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=26>
 <?query("/sys/modelname");?>で発生するイベントやアクティビティはログとして保存されます。このページには最新の400件のログが表示されます。新しいログは古いログを上書きするかたちで表示されます。
<br>

 <strong><em>最初のページ - </em></strong> クリックするとログの最初のページが表示されます。<br>
 <strong><em>最後のページ - </em></strong> クリックするとログの最後のページが表示されます。<br>
 <strong><em>前 - </em></strong> 1ページ前のログが表示されます。 <br>
 <strong><em>次 - </em></strong> 1ページ後のログが表示されます。 <br>

 <strong><em>クリア - </em></strong> ログを完全にクリアします。 </td>
 </tr>
 </table>
 </div>
 
 
<div class="box">
<a name="statistics"><h2>統計情報</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=2>
 <?query("/sys/modelname");?>は処理するデータトラフィックの統計情報を保存しています。ルータのWAN、LAN、および無線インタフェース上で受信/送信したパケット数を確認できます。

<br>
<strong><em>更新 - </em></strong>このボタンをクリックするとカウンタが更新されます。 <br>
<strong><em>リセット - </em></strong>このボタンをクリックするとカウンタがリセットされます。トラフィックカウンタはデバイスが再起動されるとリセットされます。</td>
</tr>
</table>
</div>


<div class="box">
<a name="internet_session"><h2>インターネットセッション</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=2>
 このページでは<?query("/sys/modelname");?>で送受信中のパケットの情報を表示します。<br>
 <strong><em>IPアドレス - </em></strong> パケットの送信元のIPアドレス<br>
 <strong><em>TCPセッション - </em></strong> 送信元IPアドレスから送信されるTCPパケットの数<br>
 <strong><em>UDPセッション - </em></strong> 送信元IPアドレスから送信されるUDPパケットの数 <br>
 <strong><em>プロトコル - </em></strong> 送信元IPアドレスと宛先IPアドレス間で送受信されるパケットのタイプ <br>
 送信元IPアドレス - パケットの送信元のIPアドレス <br>
 送信元ポート - 宛先IPアドレスへのパケット送信に使用しているポート<br>
 宛先IPアドレス - パケットの宛先のIPアドレス <br>
 宛先ポート - 送信元IPからのパケット受信に使用しているポート 
</td>
 </tr>
 </tr>
</table>
</div>
 
 
<div class="box">
<a name="wireless"><h2>無線</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=2>
 このページでは、<?query("/sys/modelname");?>に接続する無線クライアントの数を確認できます。また、接続する各クライアントのMACアドレス、接続時間、接続モード（802.11b、802.11g、802.11a、または802.11n）が表示されます。
</td>
 </tr>
</table>
</div> 
