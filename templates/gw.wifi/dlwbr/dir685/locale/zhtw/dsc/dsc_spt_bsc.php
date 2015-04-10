<div class="box">
<a name="internet_setup"><h2>網際網路設定</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=40>
		<p>
			如果您第一次設定此裝置，我們建議您點擊「網際網路連線設定精靈」，並遵循畫面上的說明。如果您想要手動修改或調整裝置設定，點擊「手動網際網路連線設定」。
		</p>
	</td>
</tr>
<tr>
	<td height=59>
		<p>
			<strong>啟動網際網路連線設定精靈</strong><br>
			點擊此按鈕以讓路由器帶您進行幾個簡單的步驟以協助您連接此路由器到網際網路上。
			<br>
			<strong>啟動無線網路安全設定精靈</strong><br>
			點擊此按鈕以讓路由器帶您進行無線網路的設定，包括安全性。
		</p>
	</td>
</tr>
<tr><td height=32>&nbsp;</td></tr>
<tr>
	<td height=46>
		<p>
			<strong>手動網際網路連線設定</strong><br>
			選擇此選項，如果您想要手動輸入用以將此路由器連線到網際網路的設定。
			<br>
			<strong>基地台模式</strong><br>
			啟動「基地台」模式將使此裝置像個無線網路基地台般運作。除了相關於無線網路連線的設定以外，所有與IP分享(NAT)相關功能將取消。
			<br>
			<strong>網際網路連線方式</strong><br>
			「網際網路連線設定」是用於連接 <?query("/sys/modelname");?>  到網際網路。任何在此頁面所需輸入的資訊將由您的網路服務供應商(ISP)提供給您。請就您所申請的特定網路服務供應商(ISP)選擇適切的選項。如果您不確定該選用哪個選項，請洽您的網路服務供應商(ISP)。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=61>
		<p>
			<strong>靜態 IP 網址</strong><br>
			選擇此選項如果您的網路服務供應商(ISP)已提供您一組 IP 網址、子網域遮罩、預設閘道、以及一組網域名稱服務 (DNS) 伺服器網址。輸入此資訊在適切的欄位。如果您不確定該在這些欄位填入哪些資料，請洽您的網路服務供應商(ISP)(ISP)。  
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=142>
		<p>
			<strong>動態 IP 網址</strong><br>
			如果您的網路服務供應商(ISP)每次連線時自動提供您一組變動的 IP 網址，請選擇此選項。有線電視網路供應商通常採用這類動態指派 IP 網址的方式。
		</p>
		<p>
			<strong><em>主機名稱 </em></strong> (選用) -
			主機名稱欄位是選用的，但對某些網路服務供應商(ISP)可能會要求。預設的主機名稱是路由器的機型。<br>
			<strong><em>MAC 網址 </em></strong> (選用) -
			某些網路服務供應商(ISP)會要求要填入媒體存取控制 (MAC : Media Access Control) 欄位。預設的 MAC 網址是設定到 <?query("/sys/modelname");?>  的廣域網路 (WAN) 介面。您可運用「複製 MAC 網址」按鈕以自動複製安裝於用來設定此裝置之電腦乙太網路卡的 MAC 網址。僅在您的 ISP 要求狀況下才填入此欄位。
			<br>
			<strong><em>主要 DNS 網址 </em></strong> -
			輸入由網路服務供應商(ISP) 所提供的主要網域名稱服務伺服器的 IP 網址。<br>
			<strong><em>次要 DNS 網址 </em></strong> (選用) -
			如果網路服務供應商(ISP) 有提供此次要網域名稱服務伺服器的 IP 網址，輸入於此欄位。<br>
			<strong><em>MTU </em></strong> -
			最大傳送/傳輸單位 (Maximum Transmission / Transfer Unit) 是可在網路上傳送的最大封包大小。超過 MTU 的訊息都會被分解成較小的封包。1500 是此選項的預設值。變更此號碼可能會對路由器的效能造成不好的影響。僅在我們的技術服務人員要求下或是您的 ISP 要求下才變更此數字。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=47>
		<p>
			<strong>PPPoE</strong><br>
			如果您的網路服務供應商(ISP) 要求您使用乙太網路上的點對點通信協定 ( PPPoE : Point to Point Protocol over Ethernet ) 連線方式，請選擇此選項。DSL 供應商通常會使用此選項。選擇動態的 PPPoE 以從 PPPoE 連線自動取得 IP 網址（大多數 PPPoE 連線是採用這種方式）。選擇靜態的 PPPoE 以對 PPPoE 連線使用固定的 IP 網址。
		</p>
		<p>
			<strong><em>使用者名稱 </em></strong> - 輸入您的 PPPoE 使用者名稱。<br>
			<strong><em>密碼 </em></strong> - 輸入您的 PPPoE 密碼。<br>
			<strong><em>服務名稱 </em></strong> (選用) -
			如果您的網路服務供應商(ISP) 對此 PPPoE 連線有使用服務名稱，輸入該服務名稱於此。(若沒有請務必不要任意輸入)<br>
			<strong><em>IP 網址 </em></strong> -
			此選項僅適用於靜態 PPPoE。為此 PPPoE 連線輸入固定的 IP 位址於此。<br>
			<strong><em>MAC 網址 </em></strong> (選用) -
			某些網路服務供應商(ISP) 會要求要填入媒體存取控制 (MAC : Media Access Control) 欄位。預設的 MAC 網址是設定到 <?query("/sys/modelname");?>  的廣域網路 (WAN) 介面。您可運用「複製 MAC 網址」按鈕以自動複製安裝於用來設定此裝置之電腦乙太網路卡的 MAC 網址。僅在您的 ISP 要求狀況下才填入此欄位。
			<br>
			<strong><em>主要 DNS 網址 </em></strong> -
			輸入由網路服務供應商(ISP) 所提供的主要網域名稱服務伺服器的 IP 網址。如果您選用的是靜態的 PPPoE，您才需要輸入此項資訊。如果選用的是動態 PPPoE，讓此欄位保留其原有的預設值，因為您的網路服務供應商(ISP) 會自動提供此項資訊。
			<br>
			<strong><em>次要 DNS 網址 </em></strong> (選用) -
			如果網路服務供應商(ISP) 有提供此次要網域名稱服務伺服器的 IP 網址，輸入於此欄位。<br>
			<strong><em>最大閒置時間 </em></strong> -
			在此裝置中斷 PPPoE 連線會談之前的沒有動作的時間（以分鐘計算）。輸入最大閒置時間（以分鐘計算）以定義在這段沒有動作期間所會保持網際網路連線的最長期間。如果沒有動作超過在此所定義的最大閒置時間，將會斷線。這個選項僅適用於「依需要連線 (Connet-on-demand)」連線模式。
			<br>
			<strong><em>MTU </em></strong> -
			最大傳送/傳輸單位 (Maximum Transmission / Transfer Unit) 是可在網路上傳送的最大封包大小。超過 MTU 的訊息都會被分解成較小的封包。1492 是此選項的預設值。變更此號碼可能會對路由器的效能造成不好的影響。僅在我們的技術服務人員要求下或是您的 ISP 要求下才變更此數字。<br>
			<strong><em>連線模式選擇</em></strong> -
			如果您想要路由器永遠不要中斷對 PPPoE 會談的連線，請選擇「一直開啟」。如果您想要控制什麼時候和網際網路連線與斷線，請選擇「手動」。如果由路由器僅在您的網路上有裝置要使用網際網路上的資源時才建立對網際網路的連線時，請選擇「依需要連線」。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>PPTP</strong><br>
			如果您的 ISP 使用「點對點隧道通信協定 (PPTP)」連線方式並已設定給您一組帳號密碼以讓您連上網際網路，請選擇此選項。選擇動態的 PPTP 以為您的 PPTP 連線自動地取得 IP 網址。選擇靜態的 PPTP 以使用固定的 IP 網址進行 PPTP 連線。
		</p>
		<p>
			<strong><em>IP 網址 </em></strong> - 輸入您的網路服務供應商(ISP)提供給您的 IP 網址。<br>
			<strong><em>子網域遮罩 </em></strong> - 輸入您的網路服務供應商(ISP)提供給您的子網域遮罩。<br>
			<strong><em>閘道</em></strong> - 輸入您的網路服務供應商(ISP)提供給您的閘道 IP 網址。<br>
			<strong><em>網域名稱伺服器 (DNS) - </em></strong>輸入您的網路服務供應商(ISP)提供給您的 DNS 網址。<br>
			<strong><em>伺服器 IP </em></strong> -
			輸入伺服器的 IP 網址，您將連線到的這個 IP 網址將由您的 ISP 提供。<br>
			<strong><em>帳號 </em></strong> - 輸入 PPTP 的使用者名稱。<br>
			<strong><em>密碼 </em></strong> - 輸入 PPTP 的密碼。<br>
			<strong><em>最大閒置時間 </em></strong> -
			在此裝置中斷 PPTP 連線會談之前的沒有動作的時間（以分鐘計算）。輸入最大閒置時間（以分鐘計算）以定義在這段沒有動作期間所會保持網際網路連線的最長期間。如果沒有動作超過在此所定義的最大閒置時間，將會斷線。這個選項僅適用於「依需要連線 (Connet-on-demand)」連線模式。
			<br>
			<strong><em>MTU </em></strong> -
			最大傳送/傳輸單位 (Maximum Transmission / Transfer Unit) 是可在網路上傳送的最大封包大小。超過 MTU 的訊息都會被分解成較小的封包。1400 是此選項的預設值。變更此號碼可能會對路由器的效能造成不好的影響。僅在我們的技術服務人員要求下或是您的 ISP 要求下才變更此數字。
			<br>
			<strong><em>連線模式選擇</em></strong> -
			如果您想要路由器永遠不要中斷對 PPTP 會談的連線，請選擇「一直開啟」。如果您想要控制什麼時候和網際網路連線與斷線，請選擇「手動」。如果由路由器僅在您的網路上有裝置要使用網際網路上的資源時才建立對網際網路的連線時，請選擇「依需要連線」。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>L2TP </strong><br>
			如果您的 ISP 使用「第二層隧道通信協定 (L2TP)」連線方式並已設定給您一組帳號密碼以讓您連上網際網路，請選擇此選項。選擇動態的 L2TP 以為您的 L2TP 連線自動地取得 IP 網址。選擇靜態的 L2TP 以使用固定的 IP 網址進行 L2TP 連線。
		</p>
		<p>
			<strong><em>IP 網址 </em></strong> - 輸入您的網路服務供應商(ISP)提供給您的 IP 網址。<br>
			<strong><em>子網域遮罩 </em></strong> - 輸入您的網路服務供應商(ISP)提供給您的子網域遮罩。<br>
			<strong><em>閘道</em></strong> - 輸入您的網路服務供應商(ISP)提供給您的閘道 IP 網址。<br>
			<strong><em>網域名稱伺服器 (DNS)</em></strong> - 輸入您的網路服務供應商(ISP)提供給您的 DNS 網址。<br>
			<strong><em>伺服器 IP </em></strong> -
			輸入伺服器的 IP 網址，您將連線到的這個 IP 網址將由您的 ISP 提供。<br>
			<strong><em>L2TP 帳號 </em></strong> - 輸入 L2TP 的使用者名稱。<br>
			<strong><em>L2TP 密碼 </em></strong> - 輸入 L2TP 的密碼。<br>
			<strong><em>最大閒置時間 </em></strong> -
			在此裝置中斷 L2TP 連線會談之前的沒有動作的時間（以分鐘計算）。輸入最大閒置時間（以分鐘計算）以定義在這段沒有動作期間所會保持網際網路連線的最長期間。如果沒有動作超過在此所定義的最大閒置時間，將會斷線。這個選項僅適用於「依需要連線」 (Connet-on-demand) 連線模式。
			<br>
			<strong><em>MTU</em></strong> -
			最大傳送/傳輸單位 (Maximum Transmission / Transfer Unit) 是可在網路上傳送的最大封包大小。超過 MTU 的訊息都會被分解成較小的封包。1400 是此選項的預設值。變更此號碼可能會對路由器的效能造成不好的影響。僅在我們的技術服務人員要求下或是您的 ISP 要求下才變更此數字。
			<strong><em>連線模式選擇</em></strong> -
			如果您想要路由器永遠不要中斷對 L2TP 會談的連線，請選擇「一直開啟」。如果您想要控制什麼時候和網際網路連線與斷線，請選擇「手動」。如果由路由器僅在您的網路上有裝置要使用網際網路上的資源時才建立對網際網路的連線時，請選擇「依需要連線」。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>PPTP 雙重存取(僅俄羅斯地區)</strong><br>
			要設定俄羅斯 PPTP 網際網路連線方式，依照前述 PPTP 的連線方式進行設定。如果您的 ISP 需要設定任何靜態路線，請參照「進階」選單功能表裡的「路線」功能以進行進一步設定。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>PPPoE 雙重存取(僅俄羅斯地區)</strong><br>
			有些 PPPoE 連線除了整體的 IP 連線以外，使用一條靜態 IP 路線以連到 ISP。這需要為實體 WAN 連接埠增加定義 IP 設定的步驟。要設定俄羅斯 PPPoE 網際網路連線方式，依照前述 PPPoE 的連線方式進行設定。如果您的 ISP 需要設定任何靜態路線，請參照「進階」選單功能表裡的「路線」功能以進行進一步設定。
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="wireless_setup"><h2>無線網路設定</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			「無線網路設定」頁面包含了對 <?query("/sys/modelname");?>  無線基地台部份的設定。這個頁面可讓您客製化自訂您的無線網路或設定 <?query("/sys/modelname");?>  以配合您已建立好既有的無線網路。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Wi-Fi 無線網路保護設定（在 Windows Vista 也稱之為 WCN 2.0）</strong><br>
			此功能提供使用者較為直觀的方式以設定無線網路的安全機制。此機制以兩種格式提供：PIN 號碼與 Push 按鈕。輸入無線網卡功用程式隨附的 PIN 號碼，或 Windows Vista 無線用戶端功用程式，如果該無線網卡具有經驗證的 Windows Vista 驅動程式以自動設定在路由器與用戶端之間的無線網路安全機制。此無線網卡將必須支援 Wi-Fi 無線網路保護設定兩種格式之一，以運用此項功能。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>無線網路名稱</strong><br>
			也稱之為 SSID （服務集識別碼），這是您的無線區域網路 ( WLAN: Wireless Local Area Network ) 的名稱。依照預設值，<?query("/sys/modelname");?>  的 SSID 為「dlink」。這個可以輕易地加以變更以建立一個新的無線網路或將 <?query("/sys/modelname");?>  加入到既有的無線網路。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>無線網路頻道</strong><br>
			顯示 <?query("/sys/modelname");?>  是在哪個頻道上運作。依照預設值，此頻道設為 6。這個值可變更以符合既有無線網路的頻道設定或用以客製化您新的無線網路。點集「啟動自動掃描」核取方塊以讓 <?query("/sys/modelname");?>  自動選擇其所會運作的頻道。建議採用此選項因為路由器會選擇最少干擾的頻道。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>	
 		<p>
 			<strong>傳輸 (TX) 速率</strong><br>
 			根據無線區域網路 (WLAN: Wireless Local Area Network) 上無線網路配接卡的速度選擇基本傳輸速率。
 		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>WMM</strong><br>
			選擇「開啟」以為 <?query("/sys/modelname");?>  的無線網路介面打開 QoS。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>啟動隱藏無線網路</strong><br>
			如果您不希望 <?query("/sys/modelname");?>  廣播無線網路的 SSID，請選擇「啟動」。如果啟動了此選項，<?query("/sys/modelname");?>  的 SSID 將不會被基地台熱點搜尋程式找到，所以在設定您的無線網路用戶端時，您將必須要知道此 <?query("/sys/modelname");?>  的 SSID，並手動地將其輸入，以連線到路由器。此選項的預設值是啟動的。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>無線網路安全模式</strong><br>
			保護您的無線網路很重要因為這些安全機制適用來保障在您無線網路上所傳輸資訊的正確性。<?query("/sys/modelname");?>  能夠處理四種無線安全機制：WEP、單獨 WPA、單獨 WPA2、以及 WPA/WPA2（自動偵測）。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>有線對等通信協定 (WEP) </strong><br>
			有線對等通信協定 (WEP : Wired Equivalent Protocol) 是無線區域網路 (WLAN) 的安全通信協定。WEP 藉由對在 WLAN 上的資料加密以提供安全機制。<?query("/sys/modelname");?>  支援兩個等級的 WEP 加密：64 位元以及 128 位元。預設值是關掉 WEP。可變更 WEP 設定以符合既有的無線網路或客製話您的無線網路。
		</p>
		<p>
			<strong><em>認證</em></strong> -
			認證是 <?query("/sys/modelname");?>  檢驗試圖要加入無線網路之網路裝置的身份。當使用 WEP 時，有兩種認證方式。<br> 
			<strong><em>開放系統</em></strong> -
			選擇此選項以讓所有無線裝置在其被要求要提供需要以取得網路使用權的加密金鑰前和 <?query("/sys/modelname");?>  聯繫。<br>
			<strong><em>分享金鑰</em></strong> -
			選擇此選項以要求所有試圖要和 <?query("/sys/modelname");?>  聯繫的無線裝置提供需要以取得網路使用權的加密金鑰，才讓其和 <?query("/sys/modelname");?>  聯繫。<br>
			<strong><em>WEP 加密</em></strong> -
			選擇您想要在您網路上使用的 WEP 加密層級。所支援的兩個 WEP 加密層級為 64 位元和 128 位元。<br>
			<strong><em>金鑰形式</em></strong> -
			<?query("/sys/modelname");?>  所支援的兩種金鑰形式為 HEX（十六進位）與美國標準資訊交換碼 (ASCII)。可變更金鑰形式以配合既有的無線網路或客製化您的無線網路。<br>
			<strong><em>金鑰</em></strong> -
			1-4 金鑰讓您可輕易地變更無線網路加密設定以保持一個安全的網路。僅需選擇所要用特定的金鑰以對無線網路上的資料進行加密。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>WPA/WPA2</strong><br>
			Wi-Fi 無線網路保護存取 2 (WPA2) 授權與認證在無線區域網上的使用者。WPA2 使用比 WEP 較強的安全機制，且是基於一個會在頻繁間距自動變更的金鑰。
		</p>
		<p>
			<strong><em>加密形式</em></strong> -
			當使用 WPA 做為安全形式時，<?query("/sys/modelname");?>  支援兩種不同的加密形式。這兩種選項為 TKIP（短期金鑰完整協定）與AES（進階加密標準）。<br>
			<strong><em>PSK/EAP</em></strong> -
			當選擇了 PSK，您的無線網路用戶端將需要提供通行碼以公認正。而當選擇了 EAP 時，您將需要在網路上由一台 RADIUS 伺服器以處理所有無線網路用戶端的認證。<br>
			<strong><em>通行碼</em></strong> -
			當選擇了 PSK 時，這是您無線網路用戶端將需要用以和 <?query("/sys/modelname");?>  溝通的憑據。輸入 8-63 個文數字元。請確定將此通行碼寫下，因為在任何其他的無線網路裝置要加到此網路，您將需要輸入此通行碼。<br>
			<strong><em>802.1X</em></strong> -
			這個 WPA2 的認證方式是搭配必須存在於您網路上 RADIUS 伺服器使用的。輸入 RADIUS 所設定的 IP 網址、連接埠、以及共用密碼。如果您的網路上有兩台用以認證的無線網路裝置的 RADIUS 伺服器，您也可以輸入第二台 RADIUS 伺服器的資訊。
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="lan_setup"><h2>網路設定</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			就此裝置有些是區域網路 ( LAN: Local Area Network ) 介面上的設定。這些設定可稱之為「私人設定」。若有需要，您可以變更 LAN 的 IP 位址。LAN 的 IP 位址是在您內部網路上為私人的，因此並不會讓網際網路上看到。預設的 IP 網址是 192.168.0.1 28 搭配子網域遮罩為 255.255.255.0。
			<br><br>
			<strong><em>IP 網址</em></strong> -
			<?query("/sys/modelname");?>  的 IP 網址，預設值為192.168.0.1。<br>
			<strong><em>子網域遮罩</em></strong> -
			<?query("/sys/modelname");?>  子網域遮罩的 IP 網址，預設值為255.255.255.0。<br>
			<strong><em>本機網域名稱</em></strong> (選項的) - 為您的網路輸入本機的網域名稱。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong><em>DNS 中繼</em></strong> -
			當啟動 DNS 中繼，此路由器的 DHCP 用戶端將會設定此路由器的區域網路 IP 網址當成其 DNS 伺服器。路由器所收到的所有 DNS 需求將會轉送給您的 ISP 的 DNS 伺服器。當關掉 DNS 中繼，此路由器的所有 DHCP 用戶端將會設定成 ISP 的 DNS 伺服器。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>DHCP 伺服器</strong><br>
			DHCP 是動態主機控制通信協定 ( DHCP : Dynamic Host Control Protocol ) 的縮寫。DHCP 伺服器賦予在網路上索取 IP 網址的裝置 IP 網址。這些裝置必須設定成「自動取得 IP 網址」。依照預設值，<?query("/sys/modelname");?>  上的 DHCP 伺服器是打開的。DHCP 位址集中區包含了一段範圍的 IP 網址，將會自動配發給此網路上的用戶端。
		</p>
		<p>
			<strong>DHCP 保留</strong><br>
			對您希望此路由器靜態地設定一些 IP 給特定個人電腦，請手動輸入「電腦名稱」、「IP 網址」、以及「MAC 網址」，或是從顯示目前 DHCP 用戶端的下拉式選單裡直接選擇個人電腦。
		</p>
		<p>
			<strong><em>起始 IP 網址</em></strong> DHCP 伺服器指派 IP 的起始 IP 網址。<br>
			<strong><em>結束 IP 網址</em></strong> DHCP 伺服器指派 IP 的結束 IP 網址。<br>
			<strong><em>租用時間</em></strong> 以分鐘計算的IP 租用時間。
		</p>
		<p>
			動態 DHCP 用戶端電腦連接到此裝置將會讓其資訊顯示於動態 DHCP 用戶端表上。此表將顯示主機名稱、IP 網址、MAC 網址、以及各台用戶端電腦的 DHCP 租用逾期時間。
		</p>
	</td>
</tr>
</table>
</div>

<div class="box">
<a name="lcd_setup"><h2>液晶顯示器設定</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			此液晶顯示器設定頁面控制了 <?query("/sys/modelname");?>  上顯示器面板的設定。此頁面可讓您控制螢幕保護程式以及設定此裝置需要閒置多久後，才會讓此液晶顯示器螢幕關掉。
			<br><br>
			<strong><em>螢幕保護器設定</em></strong> -
			螢幕保護器將會顯示儲存在內部硬碟根目錄的「screen_bg.jpg」圖片做為背景，搭配目前的日期與時間隨機在畫面上移動。如果找不到此圖片檔案，將保持黑色做為背景。「時間到」欄位設定表示，如果當此裝置被放著閒置不用，到達該欄位所設定的分鐘數時，將會進入螢幕保護模式。如果按了任何觸控按鈕，此裝置將會離開螢幕保護模式。<br>
			<strong><em>顯示設定</em></strong> -
			此設定在當此裝置閒置到達所設定的「時間到」欄位分鐘數，將關掉液晶顯示器螢幕以節省電源。如果按了任何觸控按鈕，液晶顯示器螢幕將會再打開。<br>
		</p>
	</td>
</tr>
</table>
</div>
