<h1>支援功能表</h1>
<table border=0 cellspacing=0 cellpadding=0 width=750>
<tr>
<td height=2><b><font size=4>維護</font></b></td>
</tr>
<tr>
<td height=16><p><br>
</td>
</tr>
<tr>
	<td height=20>
		<strong>裝置管理</strong><a name=12></a><br>
		<p>
			<strong><em>管理者登入名稱</em></strong> -
			輸入可以 Admin (管理者) 存取權限登入路由器的名稱。
		</p>
		<p>
			<strong><em>管理者密碼</em></strong> -
			輸入及確認<strong>admin</strong>帳號用來存取路由器管理介面的密碼。
		</p>
		<p>
			<strong>遠端管理</strong><br>
			遠端管理功能可讓裝置利用 Web 瀏覽程式從 Internet，透過 WAN 服務埠組態。
			並且需要使用使用者名稱與密碼來存取路由器的管理介面。<br>
			<strong><em>允許存取的 IP</em></strong> -
			這個選項可讓使用者指定特定 IP 位址，以從 Internet 遠端存取路由器。
			 此欄位預設為空白，也就是說在啟用遠端管理功能後，
			 預設為Internet 上的任何 IP 位址都可以遠端存取該路由器。<br>
			<strong><em>服務埠</em></strong> -選取用來存取<?query("/sys/modelname");?>的服務埠。.
		</p>
		<p>
			<strong><em>範例: </em></strong><br>
			<a href="http://192.168.0.1/help_tools.html">http://x.x.x.x:8080 </a>
			其中 x.x.x.x 為 <?query("/sys/modelname");?> 的 WAN IP 位址，
			而 8080 為 Web 管理介面使用的服務埠。
		</p>
	</td>
</tr>
<tr><td height=10>&nbsp;</td></tr>
<tr><td height=10>&nbsp;</td></tr>
<tr>
	<td height=40>
		<a name=14><strong>儲存與還原</strong></a><br>
		目前的系統設定可以儲存為本地硬碟機中的一個檔案。
		儲存的檔案或裝置建立的任何其他儲存設定檔都可以上載到裝置中。
		要重新載入系統設定檔案，按一下<strong>瀏覽</strong>以在硬碟機中搜尋要使用的檔案。
		也可以按一下<strong>還原裝置</strong>，以將裝置重設回工廠預設值。
		只在必要時使用還原功能。 這個動作將抹除裝置中先前儲存的設定。
		確定在進行出廠還原之前，先儲存系統設定。<br>
		
		<strong><em>儲存</em></strong> - 按一下此按鈕以儲存路由器的組態檔案。<br>
		<strong><em>瀏覽</em></strong> - 按一下<strong>瀏覽</strong>以找到儲存的組態檔案，
		並按<strong>載入</strong>以套用儲存的設定到路由器。<br>
		<strong><em>還原裝置</em></strong> - 按一下此按鈕以還原路由器到出廠預設設定。
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=51>
		<b>韌體更新</b><a name=15></a><br>
		您可以使用此工具更新裝置的韌體。 
		確定您要使用的韌體儲存在電腦的本地硬碟機上。 
		按一下<strong>瀏覽</strong>以搜尋本地硬碟機上將用來更新的韌體。
		更新韌體不會變更任何系統設定，但建議在進行韌體更新之前先儲存系統設定。
		請參閱 D-Link <a href=<?query("/sys/supporturl");?>>支援網站</a>尋找韌體更新，或者您也可按一下<strong>現在檢查</strong>按鈕，
		讓路由器自動檢查新韌體。
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=2>
		<p>
			<strong>DDNS 設定</strong><a name=16></a><br>
			動態 DNS (網域名稱服務) 是連結網域名稱與變動 (動態) IP 位址的一種方法。
			使用纜線數據機或 DSL 連線時，會指定一個動態 IP 位址給您，該位址只在該次連線的持續期內使用。
			使用 <?query("/sys/modelname");?>，您可以設定 DDNS 服務，
			在 DDNS 伺服器接收新的 WAN IP 位址時，自動更新您的伺服器。<br>
			<strong><em>伺服器位址</em></strong> - 從下拉式功能表選取您的 DDNS 提供者。<br>
			<strong><em>主機名稱</em></strong> - 輸入您在 DDNS 服務提供者註冊的主機名稱。<br>
			<strong><em>使用者名稱</em></strong> - 輸入您 DDNS 帳號的使用者名稱。<br>
			<strong><em>密碼</em></strong> - 輸入您 DDNS 帳號的密碼。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height="197">
		<p>
			<strong>系統檢查</strong><a name=17></a><br>
			這套工具可用來驗證 LAN 與 WAN 介面的實體連線。
			這是個在路由器上每一 Ethernet 接埠上均整合 LAN 線纜測試器的先進功能。
			透過圖形使用者介面 (GUI)，<strong>線纜測試</strong>可用來遠端診斷與報告線纜錯誤，
			例如開路、短路、插拔與阻抗不匹配等。 由於使用者可輕易疑難排解線纜連線問題，
			因此可大幅降低服務請求電話與人員往返。
		</p>
		<p>
			<strong>脈測測試</strong><br>
			這項實用的診斷公用程式可用來檢查電腦是否在 Internet 上。
			它會傳送 ping 封包，並傾聽來自原定主機的回應。
			輸入您想要脈測 (ping; Packet Internet Groper) 的 IP 位址並按下<strong>脈測</strong>。
			您的脈測嘗試的狀態會顯示在<strong>脈測結果</strong>方塊中。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td>
		<p>
			<strong>排程<a name=18></a></strong></p>
			本頁用來組態路由器的全域排程。 在定義之後，這些排程稍後可套用到支援排程的路由器功能上。<br>
			<strong><em>名稱</em></strong> - 這是指定義中的排程名稱。<br>
			<strong><em>日</em></strong> -
			選取一星期中的日、數日，或整個星期核取方塊以每天套用此排程。<br>
			<strong><em>全天 - 24小時</em></strong> -
			核取此方塊讓排程在指定日的 24 小時內作用。<br>
			<strong><em>開始時間</em></strong> -
			選取希望定義中排程開始作用的時間。<br>
			<strong><em>結束時間</em></strong> -
			選取希望定義中排程停止作用的時間。<br>
			<strong><em>排程規則清單</em></strong> -
			顯示已定義的所有排程。
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td>
		<p>
			<strong>記錄設定</strong><strong><a name=19></a></strong><br>
			您可以儲存記錄檔案到本地硬碟機中，稍後可傳送給網路管理者以進行疑難排解。<br>
			<strong><em>儲存Save</em></strong> - 按一下此按鈕以儲存記錄項目到文字檔案中。<br>
			<strong><em>記錄類型</em></strong> - 選取您想要的資訊類型。
		</p>
	</td>
</tr>
</table>
