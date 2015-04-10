<div class="box">
<a name="device_info"><h2>裝置資訊</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=39> 
此頁面顯示了 <?query("/sys/modelname");?>  目前的資訊。此頁面將顯示目前載入於此裝置上的韌體版本。
<br>

&nbsp;<br>
<strong><em>LAN (區域網路) - </em></strong>這顯示了乙太網路區域網路介面的 MAC 位址、IP 位址以及區域網路介面的子網域遮罩、和此路由器所內建的 DHCP 伺服器是開啟或關閉的狀態。 <br>
<strong><em>WAN (廣域網路) - </em></strong>這顯示了 WAN 網路介面的 MAC 位址、以及 IP 位址、以及子網域遮罩、預設閘道器、和 <?query("/sys/modelname");?>  自您的 ISP 所取得的 DNS 伺服器資訊。也會顯示用於和您的 ISP 建立連線的連線方式（動態、靜態、或 PPPoE）。如果此路由器設定為動態，將會有按鈕以供釋出與更新設定給此 WAN 介面的 IP。如果此路由器是設定為 PPPoE 將會有按鈕以連接及關閉 PPPoE 會談。<br> 
<strong><em>
無線網路 802.11
<? if(query("/runtime/func/ieee80211n") != "1") { echo "g"; } else { echo "n"; }?>
 - 
</em></strong>這顯示了 SSID、頻道、以及是否會對無線介面啟動加密。 </td>
</tr>
</table>
</div>


<div class="box">
<a name="log"><h2>裝置記錄</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=26>
 <?query("/sys/modelname");?>  隨時保留在其上所發生的運轉事件與活動日誌記錄。此日誌記錄會顯示多達 400 項最近的日誌記錄。較新的日誌記錄活動會覆蓋掉較舊的日誌記錄。
<br>

 <strong><em>第一頁 - </em></strong> 點擊此按鈕以前往日誌記錄的第一頁。 <br>
 <strong><em>最終頁 - </em></strong> 點擊此按鈕以前往日誌記錄的最終頁。 <br>
 <strong><em>前一頁 - </em></strong> 在日誌記錄裡往後移動一頁面。 <br>
 <strong><em>下一頁 - </em></strong> 在日誌記錄裡往前移動一頁面。 <br>

 <strong><em>清除 - </em></strong> 完全清除日誌作業記錄 </td>
 </tr>
 </table>
 </div>
 
 
<div class="box">
<a name="statistics"><h2>流量狀態</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=2>
 <?query("/sys/modelname");?>  保持其所處理的資料流量統計資料。您可以檢視此路由器所在網際網路（廣域網路）、區域網路、以及無線網路上所接收與傳送的封包量。
<br>
<strong><em>重新顯示 - </em></strong>點擊此按鈕以更新各計數器。 <br>
<strong><em>重置 - </em></strong>點擊此按鈕以清除各計數器。當此裝置重新開機時，流量計數器將會重置。 </td>
</tr>
</table>
</div>


<div class="box">
<a name="internet_session"><h2>網際網路會談(NAT session)</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=2>
 網際網路會談顯示通過 <?query("/sys/modelname");?>  的來源與目的封包。 <br>
 <strong><em>IP 位址 - </em></strong> 封包所來自發送源的 IP 位址。 <br>
 <strong><em>TCP 會談 - </em></strong> 此項目顯示從來源 IP 位址發送的 TCP 封包數目。 <br>
 <strong><em>UDP 會談 - </em></strong> 此項目顯示從來源 IP 位址發送的 UDP 封包數目。 <br>
 <strong><em>通信協定 - </em></strong> 在來源與目的地 IP 間傳遞的封包種類。 <br>
 來源 IP - 此項目顯示封包所來自發送源的 IP 位址。 <br>
 來源連接埠  - 這顯示用於傳遞封包到目的地 IP 的連接埠。 <br>
 目的地 IP - 此項目顯示封包所發送前往的 IP 位址。 <br>
 目的地連接埠 - 這顯示在目的地用於接收封包的連接埠。 
</td>
 </tr>
 </tr>
</table>
</div>
 
 
<div class="box">
<a name="wireless"><h2>無線網路狀態</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=2>
 使用此頁面以檢視有多少無線裝置用戶端已連線到 <?query("/sys/modelname");?> 。此頁面顯示各個所連線用戶端的 MAC 位址、它們已連線的時間、以及其連線的模式（802.11b、802.11g、802.11a 或 802.11n）。
</td>
 </tr>
</table>
</div> 
