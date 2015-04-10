<div class="box">
<a name="port_forwarding"><h2>連接埠轉送</h2></a>
	<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=228>
		<p>
			此進階連接埠轉送選項讓網際網路使用者可以存取您區域網路上的服務。此項功能對提供線上服務（像是 FTP、網頁、或遊戲伺服器）很有用。對於各個項目，您可以在路由器上定義將一個公開的連接埠轉向到內部區域網路上的 IP 網址與區域網路連接埠。
		</p>
		<p>
			進階連接埠轉送參數<br>
			<strong><em>名稱</em></strong> -
			指定一個有意義的名稱給虛擬伺服器，例如網頁伺服器。從「應用程式名稱」下拉式清單裡提供有許多知名類型的虛擬伺服器。選擇這些款目其中之一，然後以此類型伺服器的一般標準值填入一些剩餘的參數。
			<br>
			<strong><em>IP 網址 </em></strong> -
			在您內部網路上將提供虛擬服務系統的 IP 網址，例如 192.168.0.50。您可以從 DHCP 用戶清單裡在「電腦名稱」下拉式選單裡選擇一台電腦，或是您可以手動地輸入該伺服器的 IP 網址。
			<br>
			<strong><em>應用程式名稱 </em></strong> -
			預先定義好常用應用程式的清單可供選擇以便能較快速進行組態設定。<br>
			<strong><em>電腦名稱 </em></strong> - DHCP 用戶清單。<br>
			<strong><em>流量類型</em></strong> -
			選擇服務所使用的通信協定。您可從下拉式選單中選取常用的選擇－UDP、TCP 以及 UDP 和 TCP 兩者。<br>
			<strong><em>私人連接埠</em></strong> -
			將從您內部網路使用的連接埠。<br>
			<strong><em>公共連接埠</em></strong> -
			將從網際網路存取的連接埠。<br>
		</p>
	</td>
</tr>
 </table>
 </div>
 
 
<div class="box">
<a name="application_rules"><h2>應用程式規則</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=64> 
有些應用程式需要多重連線，像是網際網路遊戲、視訊會議、網際網路電話以及其他。這些應用程式很難配合網路地址轉換 (NAT) 作業。如果您需要執行要用到多個連線的應用程式，在「觸發連接埠」欄位指定一個通常會連結到該應用程式的連接埠，選擇通信協定種類為「傳輸控制通信協定 (TCP)」或「使用者資料訊通訊協定 (UDP)」，然後在防火牆連接埠欄位輸入連接到該觸發連接埠的公共連接埠，以開啟它們供流入的資料。在「應用程式名稱」下拉式選單裡已經有定義好的知名應用程式。
<br>

<strong><em>名稱 </em></strong> - 這是調用此應用程式的名稱。 <br>
<strong><em>觸發連接埠 </em></strong>- 這是用以觸發應用程式的連接埠。可以是單一的埠或是一連串埠的範圍。 <br>
<strong><em>流量類型 </em></strong> - 這是用以觸發此應用程式的通信協定。 <br>
<strong><em>防火牆連接埠 </em></strong> - 這是在廣域網路側將用以存取應用程式的連接埠號碼。您可定義一個單一的埠或是一連串埠的範圍。您可以使用逗號以加入多個埠，或埠的範圍。 <br>
<strong><em>流量形式 </em></strong> - 這是該應用程式所用的通信協定。 </td>

 </tr>
 </table>
 </div>
 
 
<div class="box">
<a name="qos_engine"><h2>QoS 引擎</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
<td height=64>
		<p>
			這項智慧型 Smart QoS 藉由確保網路電話 VoIP 或串流的資料流量得到較高的優先順位以改善 VoIP 的聲音品質。為達最佳效能，請勾選「消除遲滯」選項以自動對您的應用程式設定優先順位。
			<br>
		</p>
</td>
</tr>
</table>
</div>
 
 
<div class="box">
<a name="access_control"><h2>網路過濾器</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=99>
		<p>
			過濾器是用以允許或拒絕區域網路內的電腦以讀取網際網路以及您的網路之用的。在您的網路之內，此裝置可設置成是否要允許或拒絕網際網路以電腦的 MAC 網址對其存取。
		</p>
		<p>
			<strong>MAC 過濾器</strong><br>
			使用 MAC 過濾器以否決區域網路內的電腦使用網際網路。您可以手動加入 MAC 網址或從目前連接到此裝置的用戶清單裡選擇 MAC 網址。
			<br>
			如果您僅想要幾台所選擇電腦擁有網際網路的使用權，而所有其他電腦則沒有網路使用權，選擇「打開 MAC 過濾器並允許 MAC 網址列於下方的電腦存取網路」。
			<br>
			如果您想要所有的電腦都擁有網際網路的使用權，而僅有在清單上的電腦沒有網路使用權，選擇「打開 MAC 過濾器並拒絕 MAC 網址列於下方的電腦存取網路」。
			<br>
			<strong><em>MAC 網址</em></strong> -
			要加到 MAC 過濾清單的網路裝置 MAC 網址。<br>
			<strong><em>DHCP 用戶清單</em></strong> -
			DHCP 用戶端將有其主機名稱列在電腦名稱下拉式選單中。您可以選擇所要加入 MAC 過濾清單的用戶端電腦，然後點擊箭頭按鈕，這將自動地將該電腦的 MAC 網址加入適切的欄位。
		</p>
		<p>
		使用者可以使用<strong>一直</strong>下拉式選單以選擇先前所定義過的排程或點擊<strong>增加新的</strong>按鈕以加入新排程。
		</p>
		<p>
			此核取方塊是用以啟動或取消一特定款目之用。
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="parental_control"><h2>瀏覽器過濾器</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=44>
		<p>
			配合可篩選裝置存取您網路與網際網路的能力，<?query("/sys/modelname");?>  也可運用網域名稱或關鍵字以對您網路上的電腦設定允許或拒絕存取不恰當的網站。
		</p>
		<p>
			<strong>家長監督</strong><br>
			家長監督是運用關鍵字或特定網域名稱以允許或否決您網路上的電腦存取特定網站。選擇「開啟網站過濾器以允許電腦僅使用這些網站」以讓您網路上的電腦僅允許使用特定的 URL 網址與網域名稱。「開啟網站過濾器以否決電腦僅使用這些網站」以不讓您網路上的電腦存取特定的 URL 網址與網域名稱。
		</p>
		<p>
			<span class="style1">範例 1：</span><br>
			如果您希望禁止區域網路的使用者使用任何包含相關於購物的 URL 網址，您需要選擇「開啟網站過濾器以否決電腦僅使用這些網站」然後輸入「購物」到「網站過濾規則」清單。像是以下網站的 URL 網址包含了此關鍵字將會被拒絕存取。
			<br>
			<a href="http://www.yahoo.com/shopping/stores.html">http://www.yahoo.com/shopping/stores.html</a><br>
			<a href="http://www.msn.com/search/shopping-spree.html">http://www.msn.com/search/shopping-spree.html</a>
		</p>
		<p>
			<span class="style1">範例二：</span><br>
			如果您要您的孩子僅使用特定網站，您應該選擇「開啟網站過濾器以允許電腦僅使用這些網站」然後輸入您希望孩子可以使用的這些網域名稱。
		</p>
		<ul>
			<li>Google.com </li>
			<li>Cartoons.com </li>
			<li>Discovery.com </li>
		</ul>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="firewall_dmz"><h2>防火牆設定</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			防火牆設定項目包含有設定一台 DMZ 主機的選項。
		</p>
		<p>
			<strong>啟動 SPI</strong><br>
			狀態性封包檢查 (SPI: Stateful Packet Inspection) 也稱之為動態封包篩選 (Dynamic Packet Filtering) 有助於藉由追蹤每個會談的多個狀態以防止網路攻擊。這種功能驗證會談中所通過的資料流是否符合通信協定。當通信協定為 TCP 時，SPI 檢查封包的序號碼是在會談的有效範圍內，不具有有效序號的封包會被拋棄掉。不論是否啟動 SPI，路由器一定會追溯 TCP 的連線狀態並確保各個 TCP 封包的旗標對目前的狀態是有效的。
		</p>
		<p>
			<strong>非軍事區 (DMZ)</strong><br>
			如果您在 <?query("/sys/modelname");?>  後面有電腦無法順利執行網際網路上的應用程式，那麼您可以開放該電腦使用不受限的網際網路存取。輸入該電腦的 IP 網址成為非軍事區 (DMZ : Demilitarized Zone) 主機以取得不受限的網際網路存取。將一個用戶端加到 DMZ 可能會讓該電腦暴露在各種安全風險之下；所以非萬不得已不要使用此選項（建議僅將採用此做法當成最後手段）。
		</p>
		<p>
			<strong>防火牆規則</strong><br>
			防火牆規則是此路由器根據來源與目的 IP 網址以及流量形式和資料所使用的特定連接埠以允許或否決進入或流出的流量。
			<br>
			<strong><em>名稱</em></strong> - 使用者可為防火牆規則指定一個名稱。<br>
			<strong><em>做法</em></strong> - 使用者可選擇允許或否決流量。<br>
			<strong>介面</strong><br>
			<strong><em>來源</em></strong> -
			使用<strong>來源</strong>下拉式選單以選擇是否流量的起點要從 LAN 或 WAN 介面加以允許或否決。<br>
			<strong><em>目的地</em></strong> -
			使用<strong>目的地</strong>下拉式選單以選擇是否流量的終點要對到達 LAN 或 WAN 介面加以允許或否決。<br>
			<strong><em>IP 網址</em></strong> -
			在此您可藉由輸入 IP 網址在上方欄位以指定單一來源或目的 IP 網址，或可藉由在上方的欄位輸入範圍裡的第一個 IP 網址以及在下方的欄位輸入範圍裡的最後一個 IP 網址以設定一段範圍 IP 網址。
			<br>
			<strong><em>通信協定</em></strong> -
			使用<strong>通信協定</strong>下拉式選單以選擇流量種類。<br>
			<strong><em>連接埠範圍</em></strong> -
			在兩個欄位輸入相同的連接埠號碼以設定單一連接埠或者在上面的欄位輸入範圍裡的第一個連接埠以及在下面的欄位輸入範圍裡的最後一個連接埠以設定一段範圍的連接埠的。<br>
			<strong><em>排程</em></strong> -
			使用<strong>一直</strong>下拉式選單以選擇一個先前所定義好的排程或點擊<strong>增加新的</strong>按鈕以新增一個新排程。
 </p>
</td>
</tr>
</table>
</div>


<div class="box">
<a name="routing"><h2>WAN路由設定</h2></a>
<table>
<?if(query("/runtime/func/dis_routing")!="1"){
echo "<tr>\n";
echo "	<td height=99>\n";
echo "		此「路由設定」選項讓您可定義靜態的路徑到特定WAN端目的地。<br>\n";
echo "		<strong><em>啟動 </em></strong> - 設定是否此款目要啟動或關閉。<br>\n";
echo "		<strong><em>介面 </em></strong> - 設定廣域網路或廣域網路實體介面－\n";
echo "		當使用此路線時，IP 封包必須使用此介面以離開此路由器。<br>\n";
echo "		<strong><em>介面（廣域網路）</em></strong> - 這是用以接收來自網路服務供應商(ISP)\n";
echo "		以使用網際網路 IP 網址的介面。<br>\n";
echo "		<strong><em>介面（廣域網路實體）</em></strong> - 這是用以接收來自網路服務供應商(ISP)\n";
echo "		以使用網際網路 IP 網址的介面。<br>\n";
echo "		<strong><em>目的地 </em></strong> - 將會採用此路線的封包 IP 網址。<br>\n";
echo "		<strong><em>子網域遮罩 </em></strong> - 設定在 IP 網址上的哪些位元必須符合\n";
echo "		在此遮罩上的一個位元。 <br>\n";
echo "		<strong><em>閘道 </em></strong> - 設定如果使用這條路線，\n";
echo "		下一個站要採用哪個點。0.0.0.0 的閘道代表沒有下一站，\n";
echo "		而所符合的 IP 網址直接連接到路由器上所指定的介面：WAN 或實體 WAN。 \n";
echo " </td>\n";
echo " </tr>\n";
}
?>
</table>
</div>


<div class="box">
<a name="advanced_wireless"><h2>進階無線網路設定</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=20>

 <p>在此頁面的選項應由進階的使用者來變更或是當您受到我們的支援人員指示時來進行變更，因為如果設定不當，可能對您路由器的效能造成負面影響。
 </p>
 <p><strong><em>發射功率 - </em></strong>您可藉由從下拉式選單選擇較低的發射功率值以降低 <?query("/sys/modelname");?>  的輸出功率。您可用的選項有：100%、50%、25%、與 12.5%。 </p>
 <p><strong><em>信標間隔 - </em></strong> 信標是基地台所發送的封包以和無線網路同步。指定一個介於 20 到 1000 之間的信標間隔值。預設值是設為 100 毫秒。 </p>

 <p><strong><em>RTS 臨界值 - </em></strong> 此值應保持其預設值 2346。如果您發生不一致的資料流，只建議您小幅度地對此值的範圍進行修改（在介於 256 與 2346 之間）。RTS 臨界值的預設值是 2346。 </p>
 <p><strong><em>片段 - </em></strong> 此值應保持其預設值 2346。如果您發生高封包錯誤綠，您可以在介於 1500 與 2346 的範圍之間稍微增加您的「片段」值。將片段值設得太低可能導致效能變差。 </p>
 <p><strong><em>遞交流量顯示訊息 (DTIM) 間隔 - </em></strong> 對遞交流量顯示訊息 (DTIM) 輸入一個介於 1 與 255 之間的值。DTIM 是一項對監聽廣播與多播訊息下一窗口的倒數告知用戶端。當基地台對相關的用戶端有緩衝的廣播或多播訊息，它會以 DTIM 間隔值發送 DTIM。應用程式用戶端監聽到此信標並醒來以接收廣播或多播訊息。DTIM 的預設值是設定為 1。 </p>

 <p><strong><em>前頭訊號類型形式 - </em></strong> 此前頭訊號類型形式定義了在基地台與漫遊的無線介面間循環重複檢查 (CRC) 區塊的長度。請確定您選擇了適切的前頭訊號類型形式並點擊了「套用」按鈕。 </p>
 <p><span class="style2">注意： </span>高網路流量區域應使用較短的前頭訊號類型形式。CRC 是一種用以偵測資料傳輸錯誤的常用技術。 </p>
 <p><strong><em>CTS 模式 - </em></strong>選擇「無」以取消此項功能。選擇「必要」以強制此路由器取得網路上的各個無線網路裝置以在允許它們傳遞資料前進行 RTS/CTS 信號交換。選擇「自動」以讓路由器決定何時需要進行 RTS/CTS 信號交換。 </p>
<?if(query("/runtime/func/ieee80211n")!="1"){
 echo "<p><strong><em>802.11g Only Mode - </em></strong>Enable this mode if your network is made up of purely 802.11g devices. If you have both 802.11b and 802.11g wireless clients, disable this mode. </p> </td>";
}?>
 </tr>
 </tr>
 </table>
 </div>
 
 
<div class="box">
<a name="advanced_network"><h2>進階網路設定</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=20>

 <p>此項目包含可變更路由器處理某些種類資料流量方式的設定。我們建議除非您已熟悉這些設定或是已得到我們的支援人員之一給您指示，否則不要變更任何這些設定。
 </p>

<!--
 <p><strong>VPN Passthrough </strong><br>The device supports VPN (Virtual Private Network) passthrough for PPTP (Point-to-Point Tunneling Protocol) and IPSec (IP Security). Once VPN passthrough is enabled, there is no need to create any Virtual Server or Port Forwarding entries in order for outbound VPN sessions to be established properly. Multiple VPN connections can be made through the device. This is useful when you have many VPN clients on the Local Area Network. </p>
-->

 <p><strong>UPnP </strong><br>UPnP 是泛用插入即可用 (Universal Plug and Play) 的縮寫，是指一種可提供在網路設備、軟體、與週邊設備間相容性的網路架構。<?query("/sys/modelname");?>  是一台具備 UPnP 功能的路由器，代表它可和其他 UPnP 裝置 / 軟體搭配使用。如果您不打算使用此 UPnP 功能可藉由選擇「取消」以取消此功能。
 </p>
 <p><strong>廣域網路 Ping </strong><br>當啟動廣域網路 WAN Ping，您會使在裝置上的公眾廣域網路 WAN IP 網址回應由網際網路使用者所發出的 Ping 指令。使用 ping 指令來測試公眾廣域網路上的 IP 網址是駭客常用的手法以測試您的 WAN IP 網址是否有效。
 </p>
 <p><strong>廣域網路連接埠速度 </strong><br>此選項讓您選擇 <?query("/sys/modelname");?>  廣域網路 WAN 界面的速度：選擇 100Mbps、10Mbps、或 10/100/1000Mbps Auto。
 </p>

<!--
 <p><strong>Gaming Mode </strong><br>If you are experiencing difficulties when playing online games or even certain applications that use voice data, you may need to enable Gaming Mode in order for these applications to work correctly. When not playing games or using these voice applications, it is recommended that Gaming Mode is disabled. </p>
--> 

<?if(query("/runtime/func/dis_multicast_stream")!="1"){
echo " <p><strong>廣播串流</strong><br>啟動此選項以讓廣播的資料流量從網際網路更有效率地進入您的網路。 </p> </td>\n";
}
?>

 </tr>
<!--
<?if(query("/runtime/func/dis_multicast_stream")!="1"){
echo "<tr><td height=20>&nbsp;</td></tr>\n";
echo "<tr>\n";
echo "	<td height=20>\n";
echo "		<p>\n";
echo "			<strong>Multicast Streams</strong><br>\n";
echo "			Enable this option if you are receiving a Video On Demand type service from the Internet.\n";
echo "			The router uses the IGMP protocol to support efficient multicasting -- transmission of identical content,\n";
echo "			such as multimedia, from a source to a number of recipients.\n"; 
echo "			This option must be enabled if any applications on the LAN participate in a multicast group.\n"; 
echo "			If you have a multimedia LAN application that is not receiving content as expected, try enabling this option.\n";
echo "		</p>\n";
echo "	</td>\n";
echo "</tr>\n";
}
?>
--> 
</table>
</div>
 

<div class="box">
<a name="guest_zone"><h2>無線訪客區</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			無線訪客區選擇<br>
			此選擇協助您定義無線訪客區的規模。<br>
			<strong><em>啟動無線訪客區域</em></strong>  - 設定是否此無線訪客區將啟動或取消。<br>
			<strong><em>納入區域網路連接埠</em></strong>  - 設定哪個區域網路連接埠將會被納入在無線訪客區。<br>
			<strong><em>納入無線網路</em></strong>  - 設定是否要對無線訪客區加入額外無線網路區域以供其使用。<br>
			<strong><em>無線網路名稱</em></strong> -  提供無線訪客區無線網路名稱。 <br>
		</p>
		<p>
			<strong><em>無線網路安全模式</em></strong><br>
			保護您的無線網路很重要因為這些安全機制適用來保障在您無線網路上所傳輸資訊的正確性。<?query("/sys/modelname");?>  能夠處理四種無線安全機制：WEP、單獨 WPA、單獨 WPA2、以及 WPA/WPA2（自動偵測）。
			<br>
		</p>
		<p>
			<strong><em>有線對等通信協定 (WEP)</em></strong><br>
			有線對等通信協定 (WEP : Wired Equivalent Protocol) 是無線區域網路 (WLAN) 的安全通信協定。WEP 藉由對在 WLAN 上的資料加密以提供安全機制。<?query("/sys/modelname");?>  支援兩個等級的 WEP 加密：64 位元以及 128 位元。預設值是關掉 WEP。可變更 WEP 設定以符合既有的無線網路或客製話您的無線網路。
			<br>
		</p>
		<p>
			<strong><em>認證</em></strong> - 認證是 <?query("/sys/modelname");?>  檢驗試圖要加入無線網路之網路裝置的身份。當使用 WEP 時，有兩種認證方式。 <br>
			<strong><em>開放系統</em></strong> -選擇此選項以讓所有無線裝置在其被要求要提供需要以取得網路使用權的加密金鑰前和 <?query("/sys/modelname");?>  聯繫。 <br>
			<strong><em>分享金鑰 </em></strong> - 選擇此選項以要求所有試圖要和 <?query("/sys/modelname");?>  聯繫的無線裝置提供需要以取得網路使用權的加密金鑰，才讓其和 <?query("/sys/modelname");?>  聯繫。 <br>
			<strong><em>WEP 加密</em></strong> - 選擇您想要在您網路上使用的 WEP 加密層級。所支援的兩個 WEP 加密層級為 64 位元和 128 位元。<br>
			<strong><em>金鑰形式 </em></strong> - <?query("/sys/modelname");?>  所支援的兩種金鑰形式為 HEX（十六進位）與美國標準資訊交換碼 (ASCII)。可變更金鑰形式以配合既有的無線網路或客製化您的無線網路。 <br>
			<strong><em>金鑰</em></strong> - 1-4 金鑰讓您可輕易地變更無線網路加密設定以保持一個安全的網路。僅需選擇所要用特定的金鑰以對無線網路上的資料進行加密。 <br>
		</p>
		<p>
			<strong><em>WPA 個人</em></strong><br>
			Wi-Fi 無線網路保護存取 (WPA) 授權與認證在無線區域網上的使用者。WPA 使用比 WEP 較強的安全機制，且是基於一個會在頻繁間距自動變更的金鑰。
			 <br>
		</p>
		<p>
			<strong><em>加密形式</em></strong> - 當使用 WPA 做為安全形式時，<?query("/sys/modelname");?>  支援兩種不同的加密形式。這兩種選項為 TKIP（短期金鑰完整協定）與AES（進階加密標準）。 <br>
			<strong><em>PSK/EAP</em></strong> -當選擇了 PSK，您的無線網路用戶端將需要提供通行碼以公認正。而當選擇了 EAP 時，您將需要在網路上由一台 RADIUS 伺服器以處理所有無線網路用戶端的認證。 <br>
			<strong><em>通行碼 </em></strong> - 當選擇了 PSK 時，這是您無線網路用戶端將需要用以和 <?query("/sys/modelname");?>  溝通的憑據。輸入 8-63 個文數字元。請確定將此通行碼寫下，因為在任何其他的無線網路裝置要加到此網路，您將需要輸入此通行碼。 <br>
			<strong><em>802.1X </em></strong> - 這個 WPA2 的認證方式是搭配必須存在於您網路上 RADIUS 伺服器使用的。輸入 RADIUS 所設定的 IP 網址、連接埠、以及共用密碼。如果您的網路上有兩台用以認證的無線網路裝置的 RADIUS 伺服器，您也可以輸入第二台 RADIUS 伺服器的資訊。 <br>
		</p>
		<p>
			<strong><em>WPA2</em></strong><br>
			Wi-Fi 無線網路保護存取 2 (WPA2) 授權與認證在無線區域網上的使用者。WPA2 使用比 WEP 較強的安全機制，且是基於一個會在頻繁間距自動變更的金鑰。
		 <br>
		</p>
		<p>
			<strong><em>加密形式</em></strong> - 當使用 WPA 做為安全形式時，<?query("/sys/modelname");?>  支援兩種不同的加密形式。這兩種選項為 TKIP（短期金鑰完整協定）與AES（進階加密標準）。 <br>
			<strong><em>PSK/EAP</em></strong> - 當選擇了 PSK，您的無線網路用戶端將需要提供通行碼以公認正。而當選擇了 EAP 時，您將需要在網路上由一台 RADIUS 伺服器以處理所有無線網路用戶端的認證。 <br>
			<strong><em>通行碼</em></strong> - 當選擇了 PSK 時，這是您無線網路用戶端將需要用以和 <?query("/sys/modelname");?>  溝通的憑據。輸入 8-63 個文數字元。請確定將此通行碼寫下，因為在任何其他的無線網路裝置要加到此網路，您將需要輸入此通行碼。 <br>
			<strong><em>802.1X </em></strong> - 這個 WPA2 的認證方式是搭配必須存在於您網路上 RADIUS 伺服器使用的。輸入 RADIUS 所設定的 IP 網址、連接埠、以及共用密碼。如果您的網路上有兩台用以認證的無線網路裝置的 RADIUS 伺服器，您也可以輸入第二台 RADIUS 伺服器的資訊。 <br>
		</p>
		<p>
			<strong><em>WPA2-Auto</em></strong> <br>
			此選項可讓 <?query("/sys/modelname");?>  同時擁有 WPA2 與 WPA 2 兩種用戶端。<br>
		</p>
		<p>
			<strong><em>對無線訪客區的區域網路設定</em></strong><br> 
			這些是此裝置用於無線訪客區區域網路介面的設定。這些設定可以稱之為「私人設定」。如果需要，您可以變更 IP 網址。此 IP 網址對您內部網路是私下的，而且無法從網際網路上看到。預設的 IP 網址是 192.168.1.1，子網域遮罩是 255.255.255.0。
			<br>
		</p>
		<p>
			<strong><em>IP 網址</em></strong> - <?query("/sys/modelname");?>  的 IP 網址，預設值是 192.168.1.1。 <br>
			<strong><em>子網域遮罩</em></strong> - <?query("/sys/modelname");?>  的子網域遮罩網址，預設值是 255.255.255.0。 <br>
		</p>
		<p>
			<strong><em>啟動無線訪客區域用戶端隔離</em></strong> ： <br>
			啟動此功能以免訪客用戶端存取到其他用戶端的資料。訪客用戶端僅能存取網際網路。
		 <br>
		</p>
		<p>
			<strong><em>啟動在區域間的傳送</em></strong> ： <br>
			使用此段落以啟動在主機區域與無線訪客區域間的傳送，不啟動此功能，無線訪客區域的用戶無法存取在主機區域端的資料。
		 <br>
		</p>
		<p>
			<strong><em>對無線訪客區的 DHCP 伺服器</em></strong> <br>
			DHCP 代表動態主機控制通信協定。DHCP 伺服器指派 IP 網址給在網路上索取 IP 的裝置。這些裝置必須設在「自動取得 IP 網址」。依照預設值，在 <?query("/sys/modelname");?>  上的 DHCP 伺服器是開啟的。DHCP 網址集中區包含了一段將用以自動地設定網路上用戶的 IP 網址範圍。 
		 <br>
		</p>
		<p>
			<strong><em>起始 IP 網址</em></strong> - DHCP 伺服器指派 IP 的起始 IP 網址。 <br>
			<strong><em>結束 IP 網址</em></strong> -DHCP 伺服器指派 IP 的結束 IP 網址。 <br>
			<strong><em>租用時間</em></strong> -以分鐘計算的IP 租用時間。動態 DHCP 用戶端電腦連接到此裝置將會讓其資訊顯示在動態 DHCP 用戶端表上。此表將顯示主機名稱、IP 網址、MAC 網址、以及每台用戶端電腦 DHCP 租期的逾期時間。 <br>
		</p>
</td>
</tr>
</table>
</div>
 
<div class="box">
<a name="wake_on_lan"><h2>區域網路喚醒</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			區域網路喚醒功能可用以從遠端經由此路由器打開區域網路上的個人電腦。指定可由區域網路喚醒神奇封包將使用的 UDP 連接埠以免路由器認為區域網路喚醒要求是懷有敵意的攻擊而加以攔阻。
			<br>
			<br>
			<strong><em>UDP 連接埠</em></strong> - 
			這是 <?query("/sys/modelname");?>  將用以監聽會開啟個人電腦神奇封包的唯一連接埠。<br>
			<strong><em>介面</em></strong> - 
			（此設定目前無法加以改變，在之後的韌體版本也許有可能變更此項設定）。<br>		
		</p>
	</td>
</tr>
</table>
</div>
