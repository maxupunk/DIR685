<div class="box">
<a name="disk_management"><h2>硬碟管理</h2></a>
	<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			硬碟管理頁面包含了對目前安裝於裝置內本機硬碟的資訊與設定。<br>
			<br>
			<strong><em>硬碟資訊</em></strong> -
			此項目包含了安裝於此裝置內硬碟的詳細資訊。<br>
			<strong><em>格式化設定</em></strong> -
			此按鈕可讓您格式化目前安裝於裝置內的硬碟。<br>
			警告：此項動作將會清掉硬碟。硬碟上的所有資料都將消失！<br>
			<strong><em>硬碟設定</em></strong> -
			一旦啟動此項設定，在過了特定分鐘後如果沒有對硬碟的資料讀寫動作，硬碟將進入待機模式，以降低耗電。<br>
		</p>
	</td>
</tr>
 </table>
</div>

<div class="box">
<a name="users_groups"><h2>使用者/群組</h2></a>
	<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=228>
		<p>
			<strong>使用者</strong><br>
			可在此建立使用者。這些帳號可以加到網路存取與 FTP 伺服器段落的角色了。各個所建立的使用者也將有權使用排程下載段落。
		</p>
		<p>
			<strong><em>使用者名稱</em></strong> -
			輸入使用者名稱。<br>
			<strong><em>密碼</em></strong> -
			輸入密碼。<br>
			<strong><em>確認密碼</em></strong> -
			再次輸入密碼。點擊「儲存設定」以新增此使用者。<br>
			<br>
			所建立的使用者將配合其所指定的群組（如果設定有群組）顯示於此頁面底部的清單。使用者的密碼可藉由點擊「附有鉛筆的記事本」圖示以進行編輯或點擊在角色右方的「垃圾桶」圖示以加以刪除。		
		</p>
		<p>
			<strong>群組</strong><br>
			可在此建立群組。一旦建立了群組，此群組即可在使用者頁面的群組選項裡提供以供選擇。<br>
			<br>
			所建立的群組將會顯示在此頁面底部下方的清單裡。同時在此群組內的使用者也將會顯示。<br>
		</p>
	</td>
</tr>
 </table>
</div>
 
 
<div class="box">
<a name="storage_access"><h2>儲存伺服器存取</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=64> 
		<p>
			<strong><em>類別</em></strong> -
			選擇使用者或群組之一。<br>
			<strong><em>使用者或群組</em></strong> -
			由下拉式清單裡選擇一個使用者或群組。如果您打算建立一個可套用於所有使用者的角色，請選擇「所有帳號」。<br>
			<strong><em>資料夾</em></strong> -
			點擊「瀏覽」以選擇一個資料夾。此資料夾必須是位於內部的硬碟。<br>
			<strong><em>權限</em></strong> -
			就所選擇的資料夾設定「唯讀」或「讀 / 寫」權限給所選擇的使用者或群組。<br>
			<strong><em>Oplocks</em></strong> -
			Oplocks 是 LAN Manager 網路通信協定安裝於 32-位元作業系統環境的一項特性。伺服器保證會為其用戶端對一個共用的邏輯 volume 進行 Oplocks。這些保證通知用戶端一個檔案的內容將不允許由伺服器變更，或是否某些變更即將發生，將會在此變更允許進行前先通知用戶端 。Oplocks 是為了在網路檔案共用的狀況下而設計以增加網路效能；但是當運用以檔案為主的資料庫應用程式時，建議將此共用 oplocks 設定為<strong>無（關閉）</strong>。
			<br>
			<br>
			哪些作業系統會受到 Oplocks 的影響？<br>
			<br>
			依照預設值，Vista 具有 Oplocks 啟動且無法加以關閉。如果您在 DIR -685 因應用程式共用檔案上發生有網路效能問題，您可嘗試藉由將 Oplocks 設定為<strong>無（關閉）</strong>以改善效能。<br>
			<strong><em>對應</em></strong> -
			當啟動時，檔案的屬性－「Archive」將會在當檔案儲存在 DIR-685 上時複製。某些備份軟體會將此屬性加到儲存為備份的檔案上。<br>
			<strong><em>說明</em></strong> -
			關於此角色的額外說明。這是選項的，並且不具有功能性效果。<br>
			<br>
			點擊「儲存設定」以儲存此角色。所有所儲存的角色將會顯示在靠近此頁面下方的清單裡。可藉由點擊在角色右方的「附有鉛筆的記事本」或「垃圾桶」以編輯或刪除此角色。<br>
		</p>
 </tr>
</table>
</div>
 
 
<div class="box">
<a name="ftp_server"><h2>FTP 伺服器</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=99>
		<p>
			<strong><em>類別</em></strong> -
			選擇使用者或群組之一。<br>
			<strong><em>使用者或群組</em></strong> -
			由下拉式清單裡選擇一個使用者或群組。如果您打算建立一個可套用於所有使用者的角色，請選擇「所有帳號」。<br>
			<strong><em>資料夾</em></strong> -
			點擊「瀏覽」以選擇一個資料夾。此資料夾必須是位於內部的硬碟。如果您想要同時設定對所有硬碟根目錄的存取，勾選「根目錄」核取方塊。<br>
			<strong><em>權限</em></strong> -
			就所選擇的資料夾設定「唯讀」或「讀 / 寫」權限給所選擇的使用者或群組。點擊「新增」以將此角色加入清單。所有所儲存的角色將顯示在此頁面底部的清單。可藉由點擊在角色右方的「附有鉛筆的記事本」或「垃圾桶」圖示以編輯或刪除角色。<br>
			<strong><em>使用者上限</em></strong> -
			輸入此 FTP 伺服器在同一時間所可允許存取的最多使用者數目。<br>
			<strong><em>閒置時間</em></strong> -
			如果使用者閒置超過所指定的時間，FTP 伺服器會將其登出。<br>
			<strong><em>連接埠</em></strong> -
			如果您打算要變更此 FTP 伺服器所使用的連接埠，在此輸入新連接埠號碼。這是一項進階設定，當設置於路由器後方時，可能造成錯亂。除非您具有變更 FTP 連接埠的經驗，建議將此選項設定為預設值 21。<br>
			<strong><em>流量控制</em></strong> -
			此功能將調整通過此 FTP 伺服器的資料流量。如果您在此設定一個限額，使用者可以較慢的速度自此 FTP 處下載。您將可保留一些頻寬。<br>
			<strong><em>用戶端語言</em></strong> -
			大多數標準的 FTP 用戶端（像是 Windows FTP）在傳輸檔案時，僅支援西歐字碼頁面。北歐、中歐、繁體中文與簡體中文以及對西里爾字碼頁面的支援已為非標準 FTP 用戶端加入，以支援這些字元集。<br>
			<br>
			在完成後，點擊「儲存設定」。
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="upnp_av_server"><h2>UPnP AV 伺服器</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=44>
		<p>
			此 DIR-685 具有一內建的 UPnPAV 媒體伺服器，此媒體伺服器可支援與 UPnP AV 相容的媒體播放器。<br>
			<br>
			<strong><em>UPnP AV 伺服器</em></strong> -
			可供開啟或關閉 UPnP AV 伺服器。<br>
			<strong><em>資料夾</em></strong> -
			點擊「瀏覽」以選擇您的媒體檔案（音樂、相片、與視訊）的根資料夾。如果您想要存取在 DIR-685 上所有的內容，您可以選取根目錄。<br>
			<strong><em>自動重新顯示</em></strong> -
			設定自動重新顯示以每隔 5、15、或三十分鐘的間隔自動地更新您所共用的 UPnP AV 資料（也可以設為 1、2、6、12、或 24 小時）。<br>
			<br>
			在完成後，點擊「儲存設定」。<br>
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="itunes_server"><h2>iTunes 伺服器</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			iTune 伺服器將可讓 iTune 軟體自動地偵測並播放來自 DIR-685 的音樂。<br>
			<br>
			<strong><em>iTunes 伺服器</em></strong> -
			啟動或關閉 iTune 伺服器。<br>
			<strong><em>資料夾</em></strong> -
			點擊「瀏覽」以找到您音樂檔案所在的資料夾。如果您想要存取在 DIR-685 上所有的資料夾，您可以選取根目錄。<br>
			<strong><em>自動重新顯示</em></strong> -
			設定自動重新顯示以每隔 5、15、或三十分鐘的間隔自動更新您所分享的 iTune 資源庫資料（也可以設為 1、2、6、12、或 24 小時）。<br>
			<br>
			在完成後，點擊「儲存設定」。<br>
		</p>
</td>
</tr>
</table>
</div>

<div class="box">
<a name="bt_download_manager"><h2>BT 下載管理員</h2></a>
	<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			「BT 下載管理員」頁面包含了用以設定您裝置的參數以讓您不用打開個人電腦就可以自網際網路上下載 Bit Torrent 檔案。<br>
			<br>
			<strong><em>BT 設定</em></strong> -
			這可讓您打開 / 關閉 BT 下載管理員服務。目錄路徑可讓您設定哪個子目錄 / 資料夾您希望用以儲存所下載的檔案。所有的下載將會儲存在此所設定的子目錄下，所有完成的項目儲存在「已完成」的目錄之下而所有進行中的項目會儲存在「未完成」的目錄之下。對各個下載的檔案組織將會保持和原來所下載的檔案完全一致。<br>
			<strong><em>時種下載</em></strong> -
			在 BT 下載管理員畫面，您可以選擇是否要透過 URL 網址或從一個個別的 BT 時種檔案加入新的下載項目。<br>
			所有正下載中的項目將會列在視窗底部，每個下載顯示為一行，以讓您可明確地檢視並控制各個正在下載中的項目。<br>
			<strong><em>下載中項目表</em></strong> -
			對正在下載中的各個項目，點擊「詳細資料」連結以檢視關於目前下載更進一步的資訊。<br>
			<strong><em>停止</em></strong> -
			使用者可以使用此按鈕以停止 / 暫停下載程序，以讓其他正在下載中的項目可以得到較多頻寬。<br>
			<strong><em>移除</em></strong> -
			如果有錯誤發生，使用者可以運用這個位於各個正在下載中項目右手邊的按鈕以取消 / 刪除這個下載。<br>
			<br>
			如果所刪除的項目已經完成下載，僅僅會刪除掉款目，但是已完成下載的檔案會保留在「已完成」目錄。<br>
			<strong><em>移除已完成</em></strong> -
			這個位於正下載中項目表右上角的按鈕可讓使用者移除所有已完成下載的項目，而不會刪除掉所下載的檔案。<br>			
		</p>
	</td>
</tr>
 </table>
</div>
