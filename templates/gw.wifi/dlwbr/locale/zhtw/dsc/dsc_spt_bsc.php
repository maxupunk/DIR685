<h1>支援功能表</h1>
<table border=0 cellspacing=0 cellpadding=0 width=750>
<tr>
	<td height=40>
		<p><font size=4><strong>設定</strong></font></p>
		<p>
			<a name=01><strong>Internet 設定</strong></a><br>
			如果您是首次組態本裝置，我們建議您按一下<strong>Internet 連線設定精靈</strong>，
			並遵循螢幕上的指示進行。 如果您希望手動修改或組態裝置設定，
			按一下<strong>手動 Internet 連線設定</strong>。
		</p>
	</td>
</tr>
<tr>
	<td height=59>
		<p>
			<strong>啟動 Internet 連線設定精靈</strong><br>
			按一下此按鈕，讓路由器指引您幾個簡單步驟，協助您連線路由器到 Internet 上。<br>
			<strong>啟動無線安全性設定精靈</strong><br>
			按一下此按鈕，讓路由器指引您組態包含安全性在內的無線網路設定。
		</p>
	</td>
</tr>
<tr><td height=32>&nbsp;</td></tr>
<tr>
	<td height=46>
		<p>
			<strong>手動 Internet 連線設定</strong><br>
			如果想要手動輸入連線路由器到 Internet 所必要的設定，請選取此選項。<br>

			<strong>無線存取點模式</strong><br>
			啟用&quot;無線存取點模式&quot;可使裝置扮演無線 AP 的功能。
			除了與無線相關的設定之外，所有 NAT 功能都會關閉。<br>

			<strong>Internet 連線類型</strong><br>
			關於Internet連線設定主要為協助<?query("/sys/modelname");?>連線至網際網路。
			相關需要輸入至此網頁設定訊息請參考您ISP寬頻業者所提供給您的設定資料通常顯示為&quot;廣域網路設定&quot;.
			請依照您ISP提供的資料選擇設定適當的網際網路連線設定項目。假如您不確定該設定哪些項目，
			敬請聯繫您的ISP寬頻服務業者。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=61>
		<p>
			<strong>靜態 IP 位址</strong><br>
			當您的ISP業者提供給您的設定資料為IP位址,子網域遮罩,預設閘道器位址與DNS伺服器位址時，
			請選擇此項目進行對外連線的設定。請在設定頁面中輸入設當的資料。假如您不確定該輸入哪些資料，
			敬請聯繫您的ISP寬頻服務業者。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=142>
		<p>
			<strong>動態 IP 位址</strong><br>
			當您的ISP業者提供給您的寬頻服務為自動取的IP位址，請您選擇此項目進行對外連線設定。
			多數 Cable 寬頻數據服務是使用動態方式取得對外連線的IP位址。
		</p>
		<p>
			<strong><em>主機名稱 </em></strong> (optional) -
			部分ISP服務業者會要求您設定主機名稱，此為選項設定項目。預設的主機名稱為寬頻路由器的產品型號。.<br>
			<strong><em>MAC 位址 </em></strong> (optional) -
			部分ISP服務業者會要求您設定 MAC (Media Access Control)位址。
			預設的MAC位址為WAN介面的MAC位址<?query("/sys/modelname");?>。
			您可以使用 &quot;複製MAC位址&quot; 按鍵自動複製您電腦乙太網路卡的MAC位址。
			此欄為並非必要填寫的設定除非ISP服務業者要求。<br>
			<strong><em>主要 DNS 位址 </em></strong> -
			請輸入您IPS服務業者提供給您的主要DNS位址。<br>
			<strong><em>次要DNS 位址 </em></strong> (optional) -
			當ISP服務業者有提供給您次要的DNS位址，請將是要DSN位址填入此欄位。<br>
			<strong><em>MTU </em></strong> -
			MTU (Maximum Transmission/Transfer Unit) 為設定可傳送至網際網路的最大封包大小。
			當資料封包大於MTU的數值時將會被切割成較小的封包進行傳送。MTU預設值為 1500。
			改變此數值可能造成寬頻路由器的效能降低。
			當您要改變此設定，請確認您對MTU有相當了解或是經由ISP服務業者技術人員協助再進行修正。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=47>
		<p>
			<strong>PPPoE</strong><br>
			當您的ISP業者提供給您的上網方式為PPPoE (Point to Point Protocol over Ethernet)撥接上網連線，
			請您選擇此項目進行對外連線設定。
			多數DSL寬頻服務是採用PPPoE的方式提供使用者上網的服務。選擇動態PPPoE以透過PPPoE連線自動取得 IP位址。
			選擇靜態PPPoE以透過PPPoE 連線取得固定的IP位址。
		</p>
		<p>
			<strong><em>使用者名稱 </em></strong> - 輸入您PPPoE 的使用者名稱。<br>
			<strong><em>密碼 </em></strong> - 輸入您PPPoE的撥接密碼。<br>
			<strong><em>服務名稱 </em></strong> (optional) -
			當您的ISP服務業者有提供給您PPPoE連線的服務名稱，請在此欄位輸入服務名稱。<br>
			<strong><em>IP 位址 </em></strong> -
			此項目僅提供給予靜態PPPoE使用.請輸入PPPoE 連線的靜態IP位址。<br>
			<strong><em>MAC 位址 </em></strong> (optional) -
			部分ISP服務業者會要求您設定 MAC (Media Access Control)位址。
			預設的MAC位址為WAN介面的MAC位址<?query("/sys/modelname");?>。
			您可以使用 &quot;複製MAC位址&quot; 按鍵自動複製您電腦乙太網路卡的MAC位址。
			此欄為並非必要填寫的設定除非ISP服務業者要求。<br>
			<strong><em>主要 DNS 位址 </em></strong> -
			主要DNS (Domain Name System) 伺服器IP 位址,是由您的ISP服務業者所提供。
			當您選擇使用靜態PPPoE撥接連線時，您必須輸入此欄位。假如您使用的是動態PPPoE撥接您就不需要額外設定，
			相關設定會經由ISP服務業者自動提供。<br>
			<strong><em>次要DNS位址 </em></strong> (optional) -
			當ISP服務業者有提供給您次要的DNS位址，請將是要DSN位址填入此欄位。<br>
			<strong><em>最大閒置時間 </em></strong> -
			此設定會統計設備閒置的時間已停止PPPoE的連線Session。
			敬請輸入最大閒置時間以定義網路連線閒置的時間並在不進行連線時維護網路。
			當閒置的時間超過最大閒置時間,則連線將會被結束。此設定主要為提供給非月租或臨時連線所需要的設定選項。<br>
			<strong><em>MTU </em></strong> -
			MTU (Maximum Transmission/Transfer Unit) 為設定可傳送至網際網路的最大封包大小。
			當資料封包大於MTU的數值時將會被切割成較小的封包進行傳送。MTU預設值為 1492。
			改變此數值可能造成寬頻路由器的效能降低。當您要改變此設定，
			請確認您對MTU有相當了解或是經由ISP服務業者技術人員協助再進行修正。<br>
			<strong><em>連線模式選取</em></strong> -
            當您希望PPPoE連線的Session永遠不要離線時，請選擇&quot;永遠開啟&quot;。
            若您希望自行控制寬頻路由器的連線與離線請選擇&quot;手動&quot;。&quot;視需求連線&quot;的項目可讓您依照需求時
            再行建立寬頻路由器的網路連線。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>PPTP</strong><br>
			當您的ISP使用PPTP(Point to Point Tunneling Protocol)進行連線並提供給您使用者名稱與密碼來存取網際網路時，
			請選擇此項目。選擇動態PPTP以從PPTP的連線自動取得IP位址。選擇靜態PPTP以使用靜態IP位址進行PPTP連線。
		</p>
		<p>
			<strong><em>IP 位址 </em></strong> - 輸入ISP業者提供給您的IP位址。<br>
			<strong><em>子網路遮罩 </em></strong> - 輸入ISP業者提供給您的子網路遮罩。<br>
			<strong><em>閘道器</em></strong> -  輸入ISP業者提供給您的閘道器IP位址。<br>
			<strong><em>DNS - </em></strong> 輸入ISP業者提供給您的DSN IP位址。<br>
			<strong><em>Server IP </em></strong> - 輸入ISP業者提供給您的伺服器IP位址。<br>
			<strong><em>帳號 </em></strong> - 輸入您 PPTP 使用者名稱。<br>
			<strong><em>密碼 </em></strong> - 輸入您PPTP 密碼。<br>
			<strong><em>閒置時間 </em></strong> -
			此設定會統計設備閒置的時間已停止PPPoE的連線Session。敬請輸入最大閒置時間以定義網路連線閒置的時間
			並在不進行連線時維護網路。當閒置的時間超過最大閒置時間,則連線將會被結束。
			此設定主要為提供給非月租或臨時連線所需要的設定選項。<br>
			<strong><em>MTU </em></strong> -
			MTU (Maximum Transmission/Transfer Unit) 為設定可傳送至網際網路的最大封包大小。
			當資料封包大於MTU的數值時將會被切割成較小的封包進行傳送。MTU預設值為 1400。
			改變此數值可能造成寬頻路由器的效能降低。當您要改變此設定，請確認您對MTU有相當了解
			或是經由ISP服務業者技術人員協助再進行修正。<br>
			<strong><em>連線模式選取</em></strong> -
			當您希望PPPoE連線的Session永遠不要離線時，請選擇&quot;永遠開啟&quot;。
			若您希望自行控制寬頻路由器的連線與離線請選擇&quot;手動&quot;。&quot;視需求連線&quot;的項目可讓您依照需求時
			再行建立寬頻路由器的網路連線。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>L2TP </strong><br>
			當您的ISP使用L2TP(Layer 2 Tunneling Protocol)進行連線並提供給您使用者名稱與密碼來存取網際網路時，
			請選擇此項目。選擇動態L2TP以從L2TP的連線自動取得IP位址。選擇靜態L2TP以使用靜態IP位址進行L2TP連線。
		</p>
		<p>
			<strong><em>IP 位址 </em></strong> - 輸入ISP業者提供給您的IP位址。<br>
			<strong><em>子網路遮罩 </em></strong> - 輸入ISP業者提供給您的子網路遮罩。<br>
			<strong><em>閘道器</em></strong> -  輸入ISP業者提供給您的閘道器IP位址。<br>
			<strong><em>DNS - </em></strong> 輸入ISP業者提供給您的DSN IP位址。<br>
			<strong><em>Server IP </em></strong> - 輸入ISP業者提供給您的伺服器IP位址。<br>
			<strong><em>帳號 </em></strong> - 輸入您 L2TP 使用者名稱。<br>
			<strong><em>密碼 </em></strong> - 輸入您L2TP 密碼。<br>
			<strong><em>閒置時間 </em></strong> -
			此設定會統計設備閒置的時間已停止PPPoE的連線Session。敬請輸入最大閒置時間以定義網路連線閒置的時間
			並在不進行連線時維護網路。當閒置的時間超過最大閒置時間,則連線將會被結束。此設定主要為提供給非月租
			或臨時連線所需要的設定選項。<br>
			<strong><em>MTU </em></strong> -
			MTU (Maximum Transmission/Transfer Unit) 為設定可傳送至網際網路的最大封包大小。
			當資料封包大於MTU的數值時將會被切割成較小的封包進行傳送。MTU預設值為 1400。
			改變此數值可能造成寬頻路由器的效能降低。當您要改變此設定，
			請確認您對MTU有相當了解或是經由ISP服務業者技術人員協助再進行修正。<br>
			<strong><em>連線模式選取</em></strong> -
			當您希望PPPoE連線的Session永遠不要離線時，請選擇&quot;永遠開啟&quot;。若您希望自行控制寬頻路由器的連線
			與離線請選擇&quot;手動&quot;。&quot;視需求連線&quot;的項目可讓您依照需求時再行建立寬頻路由器的網路連線。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<a name=02><strong>無線網路設定</strong></a><br>
			此無線網路設定頁面包含 <?query("/sys/modelname");?>無線基地台部分的設定。
			此頁面可讓您客製化設定無線網路或針對<?query("/sys/modelname");?>已設定過的無線網路組態進行修正。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Wi-Fi 保護的設定(WPS) (Windows Vista 中也稱 WCN 2.0)</strong><br>
			此功能提供使用者透過更直覺的方式設定無線網路安全。共有兩中方式可以進行設定: PIN 識別碼與push按鈕。
			當無線網路卡與設備都有支援WPS安全設定時，請將無線網路設備上的PIN識別碼輸入至無線網路可的設定工具或
			Windows Vista作業系統內建的無線設定工具中的PIN識別碼欄位。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>無線網路名稱</strong><br>
			一般稱為SSID (Service Set Identifier),此名稱為您無線區域網路的名稱(WLAN)。
			<?query("/sys/modelname");?>預設的SSID名稱為 &quot;dlink&quot;。
			您可以簡單的改變<?query("/sys/modelname");?>無線網路的名稱，方便您辨識個人無線網路。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>無線頻道</strong><br>
			設定<?query("/sys/modelname");?>所要運作的無線頻道。預設的無線頻道為6。
			您可以針對既有的無線網路或即將新增的無線網路改變無線網路所使用的無線頻道。
			點選&quot;自動掃描&quot;可讓<?query("/sys/modelname");?>自動選擇頻道。
			建議您選用此項目讓寬頻路由器自行判斷採用的無線網路頻道，以減少無線頻道干擾或重疊。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>WMM</strong><br>
			選擇此項目可開啟<?query("/sys/modelname");?>無線網路QoS功能。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>啟用隱藏無線網路 </strong><br>
			當您不希望<?query("/sys/modelname");?>無線網路的SSID被廣播時請啟用此功能。
			&nbsp;當您啟用此功能<?query("/sys/modelname");?>的無線網路名稱將會被隱藏並無法顯示於無線網路搜尋軟體上。
			故當您在設定無線網路卡時，您必須記得您<?query("/sys/modelname");?>的SSID名稱並且手動的建立與
			無線寬頻路由器的無線連線。此功能預設為停用。
	</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>無線安全模式</strong><br>
			為了保障無線網路資料傳輸的安全，啟用無線安全模式是非常重要的。
			<?query("/sys/modelname");?>提供了四種無線安全模式;
			WEP, WPA only, WPA2 only, and WPA/WPA2 (自動偵測)
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>WEP </strong><br>
			Wired Equivalent Protocol (WEP) 為無線區域網路無線安全協定。
			WEP 提供資料在無線網路傳輸時的資料加密功能。 <?query("/sys/modelname");?>支援兩種等級的WEP加密:
			64-bit 與128-bit. WEP 預設為停用。 您可以針對既有的無線網路或即將新增的無線網路設定WEP無線網路安全加密。
		</p>
		<p>
			<strong><em>認證</em></strong> -
			認證功能主要針對網路設備希望加入<?query("/sys/modelname");?>的無線網路時進行身分的辨識。
			當您使用WEP時共有兩種認證方式。<br>
			<strong><em>Open System</em></strong> -
			當他們必須提供加密金鑰來獲得存取網路時，選擇此項目以允許無線網路設備連線至<?query("/sys/modelname");?>。<br>
			<strong><em>Shared Key</em></strong> -
			當任何無線設備需要連線至<?query("/sys/modelname");?>時選擇此項目,以在允許它們連線至<?query("/sys/modelname");?>
			前提供所需要的加密金鑰。<br>
			<strong><em>WEP 加密</em></strong> -
			選擇您無線網路所要使用的WEP無線加密等級。WEP 無線加密提供了64-bit 與128-bit兩種加密等級。<br>
			<strong><em>鑰匙類型</em></strong> -
			<?query("/sys/modelname");?>提供的鑰匙共有HEX (Hexadecimal) 與ASCII (American Standard
			Code for Information Interchange)兩種。您可以針對既有的無線網路或即將新增的無線網路選擇WEP無線網路安全加密
			使用鑰匙的類型。<br>
			<strong><em>鑰匙</em></strong> -
			為了方便維護無線網路安全加密設定提供了最多可設定1-4組的鑰匙。讓使用者可以簡單的選擇所要使用的無線安全加密鑰匙。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>WPA-Personal</strong><br>
			Wi-Fi Protected Access (WPA)提供無線網路使用者存取之授權予認證。WPA提供使用者比WEP更加安全的無線加密，
			主要透過定時的自動改變鑰匙提高安全性。
		</p>
		<p>
			<strong><em>密碼類型</em></strong> -
			<?query("/sys/modelname");?>的WPA安全加密共支援兩種不同的密碼類型。<br>
			<strong><em>PSK/EAP</em></strong> -
			當選擇 PSK方式時,您的無線用戶端將必須提供通行碼進行認證。當選擇 EAP方式時,您的網路必須具備Radius 認證伺服器
			且所有的無線用戶端的無線存取認證皆需透過此伺服器。<br>
			<strong><em>通行碼</em></strong> -
			當選擇PSK加密方式時，通行碼為無線用戶端要與<?query("/sys/modelname");?>連線時所需要的認證密碼。
			請輸入8-63 字母或數字所組成的字元。建議您將此通行碼用筆記下來，當任何無線用戶端需要存取無線網路時
			必須知道此通行碼才可存取您的網路。<br>
			<strong><em>802.1X</em></strong> -
			802.1x的意思為在您的網路環境中若是用WPA認證必須結合RADIUS 伺服器。輸入IP位址,服務埠,與您Radius組態
			所需要的Shared Secret。當您的網路環境中存在另一個Radius伺服器時，您也可以選擇設定第二組Radius Server。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>WPA2</strong><br>
			Wi-Fi Protected Access 2(WPA2) 提供無線網路使用者存取之授權予認證。WPA2提供使用者比WEP更加安全的無線加密，
			主要透過定時的自動改變鑰匙提高安全性。
		</p>
		<p>
			<strong><em>密碼類型</em></strong> -
			<?query("/sys/modelname");?>的WPA2安全加密共支援兩種不同的密碼類型。<br>
			<strong><em>PSK/EAP</em></strong> -
			當選擇 PSK方式時,您的無線用戶端將必須提供通行碼進行認證。當選擇 EAP方式時,您的網路必須具備Radius 認證伺服器
			且所有的無線用戶端的無線存取認證皆需透過此伺服器。<br>
			<strong><em>通行碼</em></strong> -
			當選擇PSK加密方式時，通行碼為無線用戶端要與<?query("/sys/modelname");?>連線時所需要的認證密碼。
			請輸入8-63 字母或數字所組成的字元。建議您將此通行碼用筆記下來，當任何無線用戶端需要存取無線網路時
			必須知道此通行碼才可存取您的網路。<br>
			<strong><em>802.1X</em></strong> -
			802.1x的意思為在您的網路環境中若是用WPA認證必須結合RADIUS 伺服器。輸入IP位址,服務埠,與您Radius組態
			所需要的Shared Secret。當您的網路環境中存在另一個Radius伺服器時，您也可以選擇設定第二組Radius Server。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>WPA2-Auto</strong><br>
			此選項允許<?query("/sys/modelname");?>同時提供WPA2 and WPA 用戶端同時無線連線。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<a name=03><strong>區域網路設定</strong></a><br>
			這裡為設備區域網路(Local Area Network)介面的設定頁面。此設定關於 &quot;私人網路設定&quot;。
			在必要的狀況下您可以改變IP位址。此私人的區域網路 IP位址為您內部網路的位址無法從網際網路進入連線此位址。
			預設的IP位址為192.168.0.1 ,子網路遮罩為255.255.255.0.<br><br>
			<strong><em>IP 位址</em></strong> -
			<?query("/sys/modelname");?>的IP位址,預設為192.168.0.1.<br>
			<strong><em>子網路遮罩</em></strong> -
			<?query("/sys/modelname");?>的子網路遮罩,預設為255.255.255.0<br>
			<strong><em>區域領域名稱</em></strong> (optional) - 輸入您區域網路的網路名稱。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong><em>DNS 轉發</em></strong> -
			當啟用DNS轉發功能, 寬頻路由器下的DHCP用戶端將透過DNS 伺服器取得IP 位址。所有寬頻路由器接收到的DNS服務需求
			將會傳送給ISP業者的DNS伺服器。
			當關閉DNS轉發功能，所有寬頻路由器的DHCP用戶端將會指派ISP DNS伺服器。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>DHCP 伺服器</strong><br>
			DHCP 全名為 Dynamic Host Control Protocol. DHCP伺服器自動分派網路使用者所需要的IP位址。
			這些設備必須設定&quot;自動取得IP位址&quot;。
			<?query("/sys/modelname");?>預設是啟用DHCP伺服器的功能。在DHCP伺服器中提供了一個指定範圍的IP 位址，
			並指派IP位址給需要的網路用戶端 。
		</p>
		<p>
			<strong>DHCP 保留</strong><br>
			輸入 &quot;電腦名稱&quot;, &quot;IP 位址&quot; 與 &quot;MAC 位址&quot; 手動提供特定的網路設備或電腦
			在每次存取寬頻路由器時,都可以取得相同的IP 位址您也可以透過下拉式選單選擇DHCP 用戶端。
		</p>
		<p>
			<strong><em>開始 IP 位址</em></strong> DHCP 伺服器分派IP的IP起始位址。<br>
			<strong><em>結束 IP 位址</em></strong> DHCP 伺服器分派IP的IP結束位址。<br>
			<strong><em>租用時間</em></strong> IP位址釋放時間長度設定。
		</p>
		<p>
			透過DHCP方式取的IP位置的電腦，在DHCP用戶端清單中將會顯示相關的訊息。表格中會顯示 主機名稱, IP位址,
			MAC 位址, 與DHCP租用IP位址給予用戶端電腦的時間。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=33>
		<p>
			<strong><a name=04>時間與日期</a></strong>
		</p>
		<p>
			時間的設定主要為提供寬頻路由器排程服務與系統事件記錄的時間對應。您必須設定您所在位置的時區。
			時間的設定可以透過手動方式或是連線至NTP伺服器以取得時間。你也可以設定日光時間系統將會自動校準時間。
		</p>
		<p>
			<strong><em>時區</em></strong> - 選擇您所在位置的時區。<br>
			<strong><em>日光時間</em></strong> -
			假如您的所在位置位於日光保存時間時,請啟用此項目並在發生的年份與時間輸入開始與結束月，星期，日期，與時間。<br>
			<strong><em>自動時間組態</em></strong> -
			選擇<?query("/sys/modelname");?>所想要同步的時間伺服器。<?query("/sys/modelname");?>將會定期同步時間伺服器
			的時間。<br>
			<strong><em>手動設定日期與時間</em></strong> -
			當您想要手動設定時間時請選擇此項目。您必須輸入年份，月份，日期，時，分，與秒。
			或是直接點選複製您電腦系統的時間按鍵複製時間至寬頻路由器。
		</p>
	</td>
</tr>
<tr><td height=2>&nbsp;</td></tr>
<tr><td height=2>&nbsp;</td></tr>
<tr>
	<td height=44>
		<p>
			<strong><a name=05>家長控制</a></strong>
		</p>
		<p>
		<?query("/sys/modelname");?>具備網頁存取過濾的功能，您可設定電腦允許或拒絕存取網頁，
		以阻擋不當的網頁瀏覽，您可透過輸入網域名稱或是關鍵字的方式。
	</p>
		<p>
			<strong>家長控制</strong><br>
			家長控制功能可讓您依照關鍵字或是特殊網域名稱允許或拒絕您區域網路中的電腦無法存取不當網站。
			&quot;啟用網頁過濾功能與允許電腦只能存取特定網頁&quot; 讓您網路中的電腦僅可從取限定的網頁或是網域。
			&quot;啟用網頁過濾功能與拒絕電腦存取限定的網頁&quot;讓您的區域網路中的電腦無法存取特定的網頁或網域。
		</p>
		<p>
			<span class="style1">範例 1:</span><br>
			假如您想要阻擋區域網路的使用者存取任何有關購物(shopping)的網頁內容或網址。
			您可以選擇&quot;啟用網頁過濾功能與拒絕電腦存取限定的網頁&quot; 再來輸入&quot;shopping&quot;
			至網頁過濾規則清單。
			區域網路內的使用者將無法進入下列網址的網站因為網址內包含被限制的關鍵字。<br>
			<a href="http://shopping.yahoo.com/">http://shopping.yahoo.com/</a><br>
			<a href="http://shopping.msn.com/">http://shopping.msn.com/</a>
		</p>
		<p>
			<span class="style1">範例 2:</span><br>
			假如您希望您的孩子僅可以存取特定的網站,您可以選擇 &quot;啟用網頁過濾功能與允許電腦只能存取特定網頁&quot;
			然後輸入您想要讓您小孩存取的網域。
		</p>
		<ul>
			<li>Google.com</li>
			<li>Cartoons.com</li>
			<li>Discovery.com</li>
		</ul>
	</td>
</tr>
</table>
