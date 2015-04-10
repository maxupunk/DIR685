<h1>支援功能表</h1>
<table border=0 cellspacing=0 cellpadding=0 width=750 height=1103>
<tr><td width="750" height=40><font size=4><b>進階</b></font></td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=228>
	<p>
		<a name=05><strong>進階服務埠轉傳</strong></a><br>
		<strong>進階服務埠轉傳</strong>選項可讓 Internet 使用者存取您內部網路的服務應用。
		此功能主要應用於內部網路架設如 FTP、Web 或遊戲伺服器等網路線上服務。
		針對每個項目，您可定義路由器上的一個公用服務埠，以重導到一內部區域網路 IP 位址兼 LAN 服務埠。
	</p>
	<p>
		進階服務埠轉傳參數<br>
		<strong><em>名稱</em></strong> -
		指定有意義的名稱給虛擬伺服器，例如 Web Server。
		&quot;應用程式名稱&quot;下拉式清單提供數個為人熟知的虛擬伺服器類型。
		選取其中一個項目會以該類型伺服器的標準值填入其餘的參數。<br>
		<strong><em>IP 位址</em></strong> -
		提供虛擬服務的內部網路上系統的 IP 位址，例如 192.168.0.50。
		您可從&quot;電腦名稱&quot;下拉式功能表的 DHCP 用戶端清單中選取一部電腦，
		或是手動輸入該伺服器電腦的 IP 位址。<br>
		<strong><em>應用程式名稱</em></strong> -
		預先定義的常見應用程式清單，讓使用者可從中選擇進行更快速的組態。<br>
		<strong><em>電腦名稱</em></strong> - DHCP 用戶端的清單。<br>
		<strong><em>交通類型</em></strong> -
		選取服務使用的協定。 常見的選擇－UDP、TCP及 UDP 與 TCP－可從下拉式功能表選取。
		若要指定任何其他協定，從清單上選取&quot;其他&quot;，
		然後在<strong>協定</strong>方塊輸入對應的協定編號 (如 IANA 所指定)。<br>
		<strong><em>私人服務埠</em></strong> -
		用有您內部網路的接埠。<br>
		<strong><em>公用服務埠</em></strong> -
		可從 Internet 存取的接埠。<br>
	</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=64>
	<strong>應用程式規則<font size=4><b><a name=06></a></b></font></strong><br>
	某些應用程式需要多個連線，例如 Internet 遊戲、視訊會議、Internet 電話與其他應用。
	這些應用程式網路穿透 NAT (Network Address Translation) 有困難。
	如果您必須執行需要數個連線的應用程式，請在&quot;觸發器服務埠&quot;欄位，
	指定應用程式常用的服務埠，選取協定類型為 TCP (Transmission Control Protocol)
	或 UDP (User Datagram Protocol)，然後在<strong>防火牆服務埠</strong>欄位輸入與觸發器服務埠相關的公用服務埠，
	以針對傳入的網路流量開啟服務埠。<strong>應用程式名稱</strong>下拉式功能表中已定義了為人熟知的應用程式。<br>
	<strong><em>名稱</em></strong> -  這是指應用程式的名稱。<br>
	<strong><em>觸發器服務埠</em></strong> - 這是用來觸發應用程式的服務埠。
	這可能是單一服務埠或連續範圍內的服務埠。<br>
	<strong><em>觸發類型</em></strong> - 這是用來觸發應用程式的協定。<br>
	<strong><em>防火牆接埠</em></strong> - 這是用來存取應用程式的 WAN 端之埠服務編號。
	您可定義單一服務埠或連續範圍內的服務埠。 您可使用逗號，以新增多服務埠或服務埠範圍。<br>
	<strong><em>網路流量類型</em></strong> - 這是針對應用程式使用的協定。
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=99>
	<p>
		<a name=07><strong>存取控制</strong></a><br>
		過濾器用來拒絕或允許 LAN 電腦是否可存取 Internet 與您的網路。
		在您的網路內，裝置可以設定以電腦的 MAC 位址，允許或拒絕 Internet 存取電腦。
	</p>
	<p>
		<strong>MAC 過濾器</strong><br>
		使用 MAC 過濾器以拒絕區域網路內的電腦存取 Internet。
		您可以手動新增 MAC 位址，或從目前連線本裝置的用戶端清單選取 MAC 位址。<br>
		如果您只想要選取的電腦擁有網路存取權限，而其他電腦無存取權限，
		選取<strong>開啟 MAC 過濾器並允許下列 MAC 位址的電腦存取網路</strong>。<br>
		如果您只想要除了清單上的電腦之外所有電腦擁有網路存取權限，
		選取<strong>開啟 MAC 過濾器並拒絕下列 MAC 位址的電腦存取網路</strong>。<br>
		<strong><em>MAC 位址</em></strong> -
		將新增到 MAC 過濾清單的網路裝置之 MAC 位址。<br>
		<strong><em>DHCP 用戶端清單</em></strong> -
		DHCP 用戶端將在<strong>電腦名稱</strong>下拉式功能表中出現其主機名稱。
		您也可選取想要新增到<strong>MAC 過濾器清單</strong>中的用戶端電腦，
		並按一下箭頭按鈕。 這將自動新增該電腦的 MAC 位址到適當的欄位中。
	</p>
	<p>
		使用者可使用<strong>永遠</strong>下拉式功能表，以選取先前定義的排程，
		或是按一下<strong>新增</strong>按鈕以新增新排程。
	</p>
	<p>
		核取方塊用來啟用或關閉特定項目。
	</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
	<p>
		<a name=08><strong>防火牆與 DMZ</strong></a><br>
		防火牆設定一節內含組態 DMS 主機的選項。
	</p>
	<p>
		<strong>啟用 SPI</strong><br>
		SPI (&quot;狀態封包檢查&quot;，亦稱為&quot;動態封包過濾&quot;)
		可在每個工作階段 (session) 追蹤更多狀態，以避免網路攻擊。
		這可驗證該工作階段通過的網路流量遵循協定規範。
		當使用 TCP 協定時，SPI 會檢查封包序號在該工作階段的有效範圍內，
		並丟棄沒有有效序號的封包。 無論是否啟用 SPI，
		路由器會一直追蹤 TCP 連線狀態並確保 TCP 封包的旗標對目前狀態有效。
	</p>
	<p>
		<strong>DMZ </strong><br>
		如果您有一台電腦，其無法從裝置後端正常地執行 Internet 應用程式，
		那麼您可以允許該電腦可以無限制地存取 Internet。
		請輸入沒有限制存取 Internet 的 DMZ (非戰區，Demilitarized Zone)
		主機 IP 位址。新增一個用戶端至 DMZ 可能會將該電腦暴露在許多的安全性風險中，
		因此非必要時請勿使用本選項。
	</p>
	<p>
		<strong>防火牆規則Firewall Rules</strong><br>
		防火牆規則主要用為依照目的與來源IP位址,或是網路流量類型,與特殊應用服務埠之設定允許
		或拒絕網路流量進出寬頻路由器。<br>
		<strong><em>名稱</em></strong> - 使用者可針對防火強的規則給予特定的名稱。<br>
		<strong><em>動作</em></strong> - 使用者可選擇規則為允許拒絕網路流量通過。<br>
		<strong>介面</strong><br>
		<strong><em>來源</em></strong> -
		使用<strong>來源</strong> 經由下拉式選單選擇要開始設定允許或拒絕網路流量通過的介面為區域網路或廣域網路。<br>
		<strong><em>目的</em></strong> -
		使用<strong>目的</strong> 經由下拉式選單選擇要結束設定允許或拒絕網路流量要到達的介面為區域網路或廣域網路。<br>
		<strong><em>IP 位址</em></strong> -您可以在上方欄位輸入單一個來源或目的IP位址或是以IP位址範圍的方式輸入
		一段位址區間,請在上方欄位輸入開始的IP位址並在下方欄位輸入結束的IP位址。<br>
		<strong><em>協定</em></strong> -
		使用<strong>協定</strong>經由下拉式選單選擇流量類型。<br>
		<strong><em>服務埠範圍</em></strong> -
		在兩個欄位中輸入相同的特定服務埠或是以範圍的方式在上方欄位輸入範圍開始的服務埠並在下方欄位輸入結束的　　　　　　　　　　　　服務埠。<br>
		<strong><em>排程</em></strong> -
		使用<strong>永遠</strong> 經由下拉式選單選擇以設定的排程或單擊
		<strong>新增</strong> 按鍵新增排程。
	</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
	<p><strong>進階無線網路 <a name=09></a></strong></p>
	<p>
		當您要設定此網頁使請先確認您對於無線網路之細部設定是否了解,建議您要更動此網頁的設定值前請先請教相關技術人員
		或是D-Link客服人員以免造成無線網路效能降低。
	</p>
	<p>
		<strong><em>傳輸 (TX)速率 - </em></strong> 根據您無線網路的無線網路卡速度，選取基本傳輸率。
		強烈建議保持此設定為自動。
	</p>
	<p>
		<strong><em>發射功率 - </em></strong>您可以將低無線傳輸的輸出功率 <?query("/sys/modelname");?>
		經由下拉式選單選擇降低傳輸功率的百分比。您選擇的可以是: 100%, 50%, 25%, 12.5%。
	</p>
	<p>
		<strong><em>Beacon 間隔 - </em></strong> 信標 (beacon) 是存取點傳出的封包，用來同步化無線網路。
		指定一個值。是預設設定，也是建議值。建議Beacon 間隔間隔數值為20至1000。預設的數值為 100 毫秒。
	</p>
	<p>
		<strong><em>RTS 臨界值 - </em></strong> 這個值應保持其 2346的預設設定。只有當不一致的資料流
		出現問題時，才應該進行小幅修改。建議修改的數值介於256至2346之間。預先設定值為 2346。
	</p>
	<p>
		<strong><em>分割- </em></strong> 這個值應保持其 2346的預設設定。當您發覺封包傳輸錯誤率過高時，您可以稍微修正
		您的&quot;分割&quot; 數值必須介於 1500 to 2346。當設定分隔Fragmentation）數值過低可能造成傳輸效能降低。
	</p>
	<p>
		<strong><em>DTIM 間隔 - </em></strong> 傳遞網路流量指示訊息(DTIM)數值必需介1至255之間。
		DTIM 是倒數動作，它會告知下一視窗的用戶端傾聽廣播與多點傳播訊息。
		當無線基地台有緩衝的廣播與多點傳播訊息給關聯的用戶端時，它將會傳送下一個DTIM並帶有DTIM的間隔數值。
		無線用戶端會聽到Beacons封包並意識到要傳送廣播與多點傳播訊息。預設的DTIM間隔數值為1。
	</p>
	<p>
		<strong><em>前序編編碼類型 - </em></strong> 。[前序編碼] 針對無線路由器與漫遊無線網路卡之間的通訊，
		定義 CRC 區塊 (CRC 檢查是偵測資料傳輸錯誤的常見技巧) 的長度。敬請選擇適當的前序編碼類型並點選Apply 按鍵。
	</p>
	<p>
		<span class="style2">備註: </span>高網路流量地區必須使用短前序編碼類型。 CRC 是偵測資料傳輸錯誤的常見技巧。
	</p>
	<p>
		<strong><em>CTS 模式 - </em></strong>選擇None 將停用此功能。
		選擇自動將會在網路上的寬頻路由器與每一個無線網路設備在允許傳送資料前執行RTS/CTS的信號交換。
		選擇自動以允許寬頻路由器決定當RTS/CTS的信號交換是否必要。
	</p>
	<p>
		<strong><em>802.11g 單獨模式 - </em></strong>當您的想要建立一個單存的802.11g無線網路時您必須啟用此功能。
		若是您同時有802.11b與802.11g的設備需同時共用無線網則您必須停用此模式。
	</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
	<p><strong>進階網路 <a name=10></a></strong></p>
	<p>在此設定頁面中您可以改變寬頻路由器某些特定應用的網路傳輸類型。我們強烈您在不熟悉或沒有必要的狀況下，
	建議您不要任意修正這些設定。若要進行修改請經由技術人員協助指導。</p>
	<!--
	<p>
		<strong>VPN 穿透 </strong><br>本設備支援VPN (虛擬私人網路) 穿透的功能支援方式為
		PPTP (Point-to-Point Tunneling Protocol) 與 IPSec (IP Security). 當VPN穿透功能為啟用時,
		您可以不需要針對VPN的Session建立或開啟任何虛擬伺服器或是服務埠轉發的指令。
		經由此設備可讓多重的VPN連線通過。這對當您有許多的VPN用戶端在區域網路時很有用。
	</p>
	-->
	<p>
		<strong>UPnP </strong><br>UPnP為Universal Plug and Play 的縮寫且為網路設備與軟體或其他週邊之間的一個溝通協定。
		這<?query("/sys/modelname");?> 是啟用UPnP 寬頻路由器, 表示將會與其他啟用UPnP的設備或軟體一起運作。
		若是您不想要使用此功能，您可以選擇將它停用。
	</p>
	<p>
		<strong>WAN Ping </strong><br>如果您啟用此功能，路由器的 WAN 埠將會回應來自廣域網路針對WAN埠IP位址
		所傳送的Ping 請求。
		透過Ping的方式來確認網路連線是否正常為駭客常使用的方式。
	</p>
	<p>
		<strong>WAN Port　速度 </strong><br>此選項可讓您選擇WAN介面的網路傳輸速率 <?query("/sys/modelname");?>:
		請選擇 100Mbps, 10Mbps, 或 10/100Mbps 自動。
	</p>
	<p>
		<strong>遊戲模式 </strong><br>當您的網路應用包含線上遊戲的對戰，或是其它網路語音服務時，
		建立您啟用此遊戲模式並能夠讓您的網路應用更加穩定。若是您沒有使用這些網路應用時則建議您將遊戲模式關閉。
	</p>
	<!--
	<p><strong>多點傳播串流</strong><br>啟用此功能可讓多點傳播的網路流量更佳的順暢。</p>
	-->
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
	<p>
		<strong>啟用多點傳播串流</strong><br>
		當您有透過網際網路觀看線上影音電視等服務時必須將此功能啟用。
		寬頻路由器為使用IGMP的協定來提升多點傳播的效能--傳送同一個內容,
		例如多媒體影音,經由相同的來源提供給多人觀看。當區域網路中的任何應用參與了
		multicast group就必須將此功能啟用。若是您發現區域網路多媒體的應用傳輸效能不佳時,
		試看看將此功能啟用。
	</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=99>
		<strong>路由 </strong><a name=11></a><br>
		透過路由設定的項目您可以定義到達目的位址的路徑。<br>
		<strong><em>啟用 </em></strong> - 決定是否啟用或停用。<br>
		<strong><em>介面 </em></strong> - 決定設定的介面 -- WAN 或 實體WAN -- 當此路由使用時,
		表示IP 封包必須傳送出寬頻路由器。<br>
		<strong><em>介面(WAN)</em></strong> - 此為接收從ISP業者提供存取網際網路IP位址的介面。<br>
		<strong><em>介面 (實體WAN)</em></strong> - 此為接收從ISP業者到其他ISP業者提供存取網際網路IP位址的介面。<br>
		<strong><em>目的 </em></strong> - 封包內的IP位址將會選用此路徑。<br>
		<strong><em>子網路遮罩 </em></strong> - 每一個位元的遮罩必須與IP位址的位元相符合。<br>
		<strong><em>閘道 </em></strong> - 此定義網路路由的下一個位置。
		閘道器定器為 0.0.0.0 表示沒有下一個位置,且IP位址為直截連線至路由器所指定的介面：WAN 或實體WAN。
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
</table>
