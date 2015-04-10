<div class="box">
<a name="admin"><h2>管理者設定</h2></a>
<table border=0 cellspacing=0 cellpadding=0>

<tr>
	<td height=20>
		
		<p>
			<strong><em>管理員登入名稱</em></strong> -
			輸入將用以具有 Admin 管理權限登入到此路由器的名稱。
		</p>
		<p>
			<strong><em>管理員密碼</em></strong> -
			輸入並確認<strong>admin</strong>帳號將使用的密碼，以使用此路由器的管理介面。
		</p>
		<p>
			<strong>遠端管理</strong><br>
			遠端管理可讓運用網頁瀏覽器自網際網路透過廣域網路 (WAN) 對此裝置進行設定。仍然需要使用者名稱與密碼以存取此路由器的管理介面。
			<br>
			<strong><em>所允許存取的 IP</em></strong> -
			此選項可讓使用者指定一來自網際網路上特定的 IP 網址以允許自遠端存取此路由器。此欄位依照預設值保留為空白，其用意為一旦遠距管理啟動，來自網際網路的任何IP 都可以遠距地存取此路由器。
			<br>
			<strong><em>連接埠</em></strong> - 選擇將用以存取此 <?query("/sys/modelname");?>  的連接埠。
		</p>
		<p>
			<strong><em>範例: </em></strong><br>
			<a href="http://192.168.0.1/help_tools.html">http://x.x.x.x:8080 </a> 其中 x.x.x.x 是 <?query("/sys/modelname");?>  廣域網路 (WAN) 的 IP 網址，而 8080 是網路管理介面所使用的連接埠。
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="time"><h2>設備時間/日期</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=33>
		<p>
			此路由器會運用時間組態設定以同步所排程的服務及系統日誌記錄活動。您將需要依照您所在的區域設定時區。此時間可以手動設定或可以連線到一台網路時間通信協定 (NTP) 伺服器以取得時間。您也可以設定日光節約時間日期，這將會根據所指定的日期自動地調整系統時間。
		</p>
		<p>
			<strong><em>時區</em></strong> - 選擇您所位於的時區。<br>
			<strong><em>日光節約時間</em></strong> -
			如果您所在的時區會採用「日光節約時間」，啟動此選項並指定當年度起訖月、週、日以及時間。<br>
			<strong><em>自動時間設定</em></strong> -
			選擇一台您想要 <?query("/sys/modelname");?>  與其同步的 D-Link 時間伺服器。<?query("/sys/modelname");?>  將與此 D-Link NTP 伺服器同步的間隔設為七天。<br>
			<strong><em>手動設定日期與時間</em></strong> -
			如果您想要手動設定時間，選擇此選項。您必須指定年、月、日、時、分、秒，或是您可以點擊「複製您電腦的時間設定」按鈕以複製正在使用以存取管理介面電腦的系統時間。
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="log_settings"><h2>日誌記錄設定</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			您可以儲存日誌記錄檔到本機硬碟，以供之後使用或寄給網路管理員以進行故障排除。
			<br>
			<strong><em>儲存</em></strong> - 點擊此按鈕以儲存日誌記錄到一個文字檔。<br>
			<strong><em>日誌記錄類型</em></strong> - 選擇您所要 <?query("/sys/modelname");?>  加以記錄的資訊種類。
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="email_settings"><h2>Email 通知設定</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			Email 通知設定可讓您發送此裝置的日誌記錄檔到所指定的 email 電子郵件信箱網址。<br>
			<br>
			<strong><em>來自電子郵件信箱網址</em></strong> - 
			此電子郵件的發送源頭電子郵件信箱網址。大多數現在的 SMTP 裝置都需要一個有效的電子郵件信箱網址做為發送源頭，並會對其進行檢查。<br>
			<strong><em>送往電子郵件信箱網址</em></strong> - 
			此裝置的日誌記錄檔將寄送去的電子郵件信箱網址。有權存取此電子郵件信箱網址的人將可看到此裝置的日誌記錄檔。<br>
			<strong><em>電子郵件標題</em></strong> - 
			電子郵件的標題內容。<br>
			<strong><em>SMTP 伺服器網址</em></strong> - 
			將會寄發日誌記錄檔到所指定電子郵件信箱的電子郵件伺服器的 IP 網址或網域名稱。<br>
			<strong><em>SMTP 伺服器連接埠</em></strong> - 
			此電子郵件伺服器所會使用的連接埠。<br>
			<strong><em>啟動驗證</em></strong> - 
			為了安全理由，有些 SMTP 伺服器會檢查帳號名稱與密碼以確認其所處理的郵件是來自其用戶。<br>
			<strong><em>帳號名稱</em></strong> - 
			SMTP 伺服器用以驗證的帳號名稱。<br>
			<strong><em>密碼</em></strong> - 
			SMTP 伺服器用以驗證的密碼。<br>
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="system"><h2>系統工具</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=40>
		目前的系統設定可儲存成一個檔案以存到本機硬碟。所儲存的檔案或任何其他由此裝置所儲存的檔案可以被上載到此裝置。要重新載入系統設定檔案，點擊<strong>瀏覽</strong>以在本機硬碟上搜尋所要使用的檔案。也可點擊<strong>復原裝置</strong>以將此裝置重置回到其出廠預設值。請僅在必要時才使用此復原功能。這項操作將會清除先前對此裝置所儲存的設定。請確定在執行出廠預設值前先儲存您的系統設定。
		<br>
		<strong><em>儲存</em></strong> - 點擊此按鈕以自路由器儲存組態設定檔。<br>
		<strong><em>瀏覽</em></strong> -
		點擊「瀏覽」以找到一個所儲存的組態設定檔，然後點擊以套用此所儲存的設定到路由器。<br>
		<strong><em>復原裝置</em></strong> -
		點擊此按鈕以將此路由器恢復到其出廠預設值。
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="firmware"><h2>韌體更新</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=51>
	您可使用此工具以更新此裝置的韌體。請確定您想要使用的韌體是儲存在電腦的本機硬碟上。
	點擊<strong>瀏覽</strong>以搜尋本機硬碟上所要用以更新的韌體。更新韌體將不會變更任何您的系統設定，
	但仍建議您在執行韌體更新前先儲存您的系統設定。
	請查看 D-Link <a href=<?query("/sys/supporturl");?>>支援網站<a>以瞭解韌體更新的最新狀況或您可點擊<strong>現在查看</strong>按鈕以讓此路由器自動地檢查新的韌體。
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="dynamic_dns"><h2>動態DNS設定 (DDNS)</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=2>
		<p>
			動態網域名稱服務 (DNS) 是用以保持一個網域名稱連結到變動的（動態的）IP 網址。大多數的有線電視與 DSL 連線，都會指派一個動態的 IP 網址給您，而此網址僅在這次特定的連線過程中使用。透過 <?query("/sys/modelname");?> ，您可以設定 DDNS ，然後 <?query("/sys/modelname");?>  會在每次收到一個新的廣域網路 (WAN) IP 網址時，自動地更新您的 DDNS 伺服器。
			<br>
			<strong><em>伺服器位址</em></strong> - 從下拉式選單中選擇您的 DDNS 服務供應商。<br>
			<strong><em>主機名稱</em></strong> - 輸入向您的 DDNS 服務供應商所註冊的主機名稱。<br>
			<strong><em>使用者名稱</em></strong> - 輸入您 DDNS 帳號的使用者名稱。<br>
			<strong><em>密碼</em></strong> - 輸入您 DDNS 帳號的密碼。
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="system_check"><h2>系統檢查</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			此工具可用以驗證區域網路 (LAN) 與網際網路 (WAN) 介面兩方面的實體連線。這是一項對此路由器的每一個連接埠加上網路線路測試器的先進功能。透過圖形化使用者介面 (GUI)，可在遠端進行診斷並通報線路的故障（像是斷路、短路、對偶線交錯、以及阻抗不符）。這項功能可顯著地降低維修的需求並藉由讓使用者可輕鬆地排除其網路連線上的障礙以帶來回報。
		</p>
		<p>
			<strong>Ping 測試</strong><br>
			這個有用的偵錯工具可用於檢測是否一台電腦是在網際網路上。此偵錯工具傳送一個 ping 封包給特定主機然後聆聽其回覆。輸入一個您所想要 ping ( Packet Internet Grouper )主機名稱或 IP 位址，然後點擊<strong>Ping</strong>。您的 Ping 嘗試的結果將會顯示在 Ping 結果方塊內。
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="schedules"><h2>時間排程</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>	
			此頁面是用以對此路由器設定整體的排程。一旦定義完成，這些排程在之後可套用到此路由器支援排程的功能。
			<br>
			<strong><em>名稱</em></strong> - 所定義排程的名稱。<br>
			<strong><em>日期</em></strong> -
			選擇一個日子、一段期間、或勾選整週核取方塊以讓此排程套用到每一天。<br>
			<strong><em>整天 - 24 小時</em></strong> -
			勾選此核取方塊以讓排程在所指定的日子全天 24 小時作用。<br>
			<strong><em>開始時間</em></strong> -
			選擇您想要所定義的排程啟動的時間。<br>
			<strong><em>結束時間</em></strong> -
			選擇您想要所定義的排程停止的時間。<br>
			<strong><em>排程規則清單</em></strong> -
			這個項目顯示所有曾定義的排程。
		</p>
	</td>
</tr>
</table>
</div>

						   