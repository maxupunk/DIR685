<h1>支援功能表</h1>

	<table border=0 cellspacing=0 cellpadding=0 width=750 height=478>
 <tr>
 <td height=2><font size=4><b>狀態</b></font></td>
 </tr>
 <tr>
 <td height=39> <a name=20><strong>裝置資訊</strong><br>
此頁顯示<?query("/sys/modelname");?>的目前資訊。此頁將顯示該裝置目前載入的韌體版本。<br>

&nbsp;<br>
<strong><em>LAN (區域網路) - </em></strong>顯示 Ethernet LAN 介面的 MAC 位址、LAN 介面的 IP 位址與子網路遮罩，
以及路由器的內建 DHCP 伺服器啟用或關閉。<br>

<strong><em>WAN (廣域網路) - </em></strong>顯示 WAN 介面的 MAC 位址，
以及 <?query("/sys/modelname");?> 從您 ISP 取得的 IP 位址、子網路遮罩、
預設閘道與 DNS 伺服器資訊。 本頁也顯示用來與您 ISP 建立連線所使用的連線類型 
(動態、靜態或 PPPoE)。 如果路由器組態為 [動態]，將會出現按鈕以釋放與更新指定給 WAN 介面的 IP 位址。 
如果路由器針對 PPPoE 組態，就會出現連線與中斷 PPPoE 工作階段的按鈕。<br> 

<strong><em>
Wireless 802.11
<? if(query("/runtime/func/ieee80211n") != "1") { echo "g"; } else { echo "n"; }?>
 - </em></strong>會顯示 SSID、頻道，以及無線介面的加密是否啟用。</td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>

 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=26><a name=21><b>記錄</b></a><br>
 <?query("/sys/modelname");?> 會隨時針對本身發生的事件與活動，維護一份即時記錄 (log)。 記錄會顯示最多 400 個最近的記錄。 較新的記錄活動會覆寫較舊的記錄。<br>

 <strong><em>第一頁 - </em></strong>按一下此鈕以前往記錄的第一頁。<br>
 <strong><em>最後一頁 - </em></strong>按一下此鈕以前往記錄的最後一頁。<br>
 <strong><em>前一頁 - </em></strong>往前移動一個記錄頁。<br>
 <strong><em>下一頁 - </em></strong>往後移動一個記錄頁。<br>

 <strong><em>清除 - </em></strong>完全清除記錄。</td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>

 </tr>
 <tr>
 <td height=2><a name=22><strong>狀態</strong></a><br>
<?query("/sys/modelname");?> 會維護其所處理的資料流量的統計數據。 
您可以檢視路由器在 WAN、LAN 與無線介面上接收與傳送的封包量。
<br>
<strong><em>重新整理 - </em></strong>按一下此鈕以更新計數器。<br>
<strong><em>重設 - </em></strong>按一下此鈕以清除計數器。 網路流量計數器會在裝置重新開機時重設。</td>

 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=2><a name=23><b>運作中Session</b></a><br>
 &quot;運作中Session&quot;用來顯示通過<?query("/sys/modelname");?>的來源與目的封包。<br>
 <strong><em>IP 位址 - </em></strong> 封包源始的來源 IP 位址。<br>
 <strong><em>TCP 工作階段 - </em></strong>顯示從來源 IP 位址傳送的 TCP 封包數。<br>
 <strong><em>UDP 工作階段 - </em></strong>顯示從來源 IP 位址傳送的 UDP 封包數。<br>
 <strong><em>協定 - </em></strong>這是來源與目的 IP 之間傳送的封包類型。<br>
 來源IP - 顯示封包源始的 IP 位址。<br>
 來源服務埠 - 顯示正用來傳送封包到目的 IP 的服務埠。<br>
 目的 IP - 顯示封包目的地的 IP 位址。<br>
 目的服務埠 - 顯示正用來從來源 IP 接收封包的服務埠。 


</td>

 </tr>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=2><a name=24><b>無線網路</b></a><br>
 利用此頁以檢視有多少無線用戶端已與 <?query("/sys/modelname");?> 連線。
 本頁顯示每個無線連線用戶端的 MAC 位址、與其已連線的歷時，以及其所連線的模式 (802.11b 或 802.11g)。
</td>

 </tr>
 </table>
