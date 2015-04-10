<div class="box">
<a name="admin"><h2>管理者</h2></a>
<table border=0 cellspacing=0 cellpadding=0>

<tr>
	<td height=20>
		
		<p>
			<strong><em>管理者ログイン名</em></strong> -
			ルータにAdmin権限でアクセスするための名前を入力します。
		</p>
		<p>
			<strong><em>管理者パスワード</em></strong> -
			ルータの管理インタフェースにアクセスするための<strong>Admin</strong>アカウント用パスワードを入力します。
		</p>
		<p>
			<strong>リモート管理</strong><br>
			リモート管理機能を使用すると、インターネット側からWebブラウザを使用したデバイス設定がWANポート経由で行えます。ルータの管理インタフェースにアクセスするには、ユーザ名とパスワードの入力が必要です。
			<br>
			<strong><em>アクセスを許可するIPアドレス</em></strong> -
			インターネット側からルータにリモートアクセス可能な特定のIPアドレスを指定できます。デフォルトではこのフィールドは空白となっていて、リモート管理が有効化されると、どのIPアドレスからでもインターネット経由でルータにリモートアクセスが可能な状態になります。<br>
			<strong><em>ポート</em></strong> - <?query("/sys/modelname");?>へのアクセスに使用するポートを指定します。
		</p>
		<p>
			<strong><em>例：</em></strong><br>
			<a href="http://192.168.0.1/help_tools.html">http://x.x.x.x:8080 </a> （x.x.x.xは<?query("/sys/modelname");?>のWAN IPアドレス。8080はWeb形式の管理インタフェースに使用するポートです。）
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="time"><h2>時刻</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=33>
		<p>
			時刻設定はルータが時間指定で実行するサービスやシステムロギングのための時刻同期に使用します。お客様の地域に合わせたタイムゾーンの設定を行ってください。時刻設定は手動で、あるいはデバイスをNTP（Network Time Protocol）サーバに接続して取得できます。またサマータイムの設定を行えば、指定日に自動的にシステムの時刻調整が行われます。
		</p>
		<p>
			<strong><em>タイムゾーン</em></strong> - お客様の地域を選択します。<br>
			<strong><em>サマータイム</em></strong> -
			お客様の地域がサマータイムを採用している場合は、このオプションを選択し、サマータイム開始日および終了日の月、週、日、時間を入力します。<br>
			<strong><em>自動時刻設定</em></strong> -
			<?query("/sys/modelname");?>の時刻同期に使用するD-Link NTPサーバを選択します。<?query("/sys/modelname");?>がD-Link NTPサーバと通信して同期を行う間隔は7日間に設定されています。<br>
			<strong><em>手動で時刻を設定する</em></strong> -
			手動で時刻設定を行う場合にはこのオプションを選択します。年、月、日、時間、分、秒を入力する方法と、「コピー」ボタンをクリックして管理インタフェースへのアクセスに使用しているコンピュータのシステム時間をコピーする方法が用意されています。
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="log_settings"><h2>ログ設定</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			ログファイルをローカルディスクに保存し、後でネットワーク管理者に送信してトラブルシューティングに役立てることができます。
			<br>
			<strong><em>保存</em></strong> - ログエントリをテキストファイルに保存します。<br>
			<strong><em>ログタイプ</em></strong> - 取得するログの種類を選択します。
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="email_settings"><h2>メール設定</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			メール設定を行うと、指定したメールアドレスにログファイルを送信できます。
			<br>
			<br>
			<strong><em>送信者メールアドレス</em></strong> - 
			メールの送信者のメールアドレス。最新式のSMTPサーバでは、このアドレスが有効なものであるかテストを行います。<br>
			<strong><em>宛先メールアドレス</em></strong> - 
			デバイスのログファイルの送信先のメールアドレス。このメールアカウントにアクセスするとログファイルが確認できます。<br>
			<strong><em>件名</em></strong> - 
			メールのタイトル<br>
			<strong><em>SMTPサーバアドレス</em></strong> - 
			宛先のメールアカウントへデバイスのログファイルを転送するメールサーバのIPアドレスまたはドメイン名。<br>
			<strong><em>SMTPサーバポート</em></strong> - 
			メールサーバが使用するポート<br>
			<strong><em>認証を有効にする</em></strong> - 
			SMTPサーバの仕様によっては、セキュリティの目的でアカウント名とパスワードをチェックして、メールが自身のクライアントからのものであるかを確認する場合があります。<br>
			<strong><em>アカウント名</em></strong> - 
			SMTPサーバが認証に使用するアカウント名<br>
			<strong><em>パスワード</em></strong> - 
			SMTPサーバが認証に使用するアカウントのパスワード<br>
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="system"><h2>システム</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=40>
	現在のシステム設定はローカルのハードディスク上にファイルとして保存できます。保存されている現在のシステム設定や、デバイスが作成し保存したすべての設定ファイルはユニットにアップロードできます。システム設定ファイルを再ロードするには、<strong>参照</strong>ボタンをクリックしてローカルハードディスクから対象のファイルを指定します。<strong>デバイスの復旧</strong>ボタンをクリックすると、デバイスを工場出荷時の状態にリセットできます。ただしこの操作は必要時のみに行ってください。この操作を行うと、ユニットに前回保存された設定が失われます。工場出荷時の状態に戻す前には必ずシステム設定を保存するようにしてください。
	<br>
		<strong><em>保存</em></strong> - このボタンをクリックするとルータの設定ファイルを保存します。<br>
		<strong><em>参照</em></strong> -
		「参照」ボタンをクリックして、保存されている設定ファイルを選択したら、「ロード」ボタンをクリックしてルータに適用します。<br>
		<strong><em>デバイスの復旧</em></strong> -
		このボタンをクリックすると、ルータを工場出荷時の状態に復旧させます。
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="firmware"><h2>ファームウェア</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=51>
	このツールを使用してデバイスのファームウェアアップグレードを行います。使用したいファームウェアは、必ずコンピュータのローカルハードディスク上に保存してください。「参照」ボタンをクリックして、ローカルハードディスク内のアップデートに使用するファームウェアを選択します。ファームウェアのアップグレードによりシステム設定が変更されることはありません。しかし、ファームウェアアップグレードを実行する前には、念のためシステム設定を保存しておくことをお勧めします。ファームウェア更新情報については、D-Linkの<a href=<?query("/sys/supporturl");?>>サポー</a>トサイトを確認するか、あるいは「すぐ確認する」ボタンをクリックするとルータが自動的に新しいファームウェアの情報を取得します。
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="dynamic_dns"><h2>ダイナミックDNS</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=2>
		<p>
			ダイナミックDNS（Domain Name Service）は動的（ダイナミック）に変化するIPアドレスとドメイン名との関連付けを保つためのメソッドです。通常、ケーブルやDSL接続の場合は、ダイナミックIPアドレスを割り当てられ、そのアドレスはその接続の間だけ使用されます。<?query("/sys/modelname");?>では、DDNSサービスの設定を行うと、新しいWAN IPアドレスが割り当てられるたび、<?query("/sys/modelname");?>が自動的にDDNSサーバを更新します。
			<br>
			<strong><em>サーバアドレス</em></strong> - ドロップダウンメニューから契約するDDNSプロバイダを選択します。<br>
			<strong><em>ホスト名</em></strong> - DDNSサービスプロバイダに登録したホスト名を入力します。<br>
			<strong><em>ユーザ名</em></strong> - お客様のDDNSアカウントのユーザ名を入力します。<br>
			<strong><em>パスワード</em></strong> - お客様のDDNSアカウントのパスワードを入力します。
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="system_check"><h2>システムチェック</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			このツールを使用して、LANおよびインターネット（WAN）インタフェースの物理的な接続性をチェックできます。これはルータのすべてのイーサネットポート上にLANケーブルテスタを組み込んで実現する拡張機能です。GUIを経由したケーブルテストが可能であり、開回路や短絡、誤配線、インピーダンス不整合などのケーブルの不具合を診断・報告します。この機能により、ケーブル接続のトラブルシューティングをユーザ自身が簡単に行えるようになり、お問い合わせの手間を省くことができます。
		</p>
		<p>
			<strong>Pingテスト</strong><br>
			この便利な診断ユーティリティを使用すると、インターネット上でコンピュータの導通確認ができます。Pingパケットを送信して、特定のホストからの応答をリッスンします。Ping送信を行う相手のホスト名またはIPアドレスを入力し、<strong>Ping</strong>ボタンをクリックします。「Ping結果」ボックスに、診断結果が表示されます。
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="schedules"><h2>スケジュール</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>	
			このページではルータのグローバルスケジュールを設定します。ここで定義したスケジュールは、スケジュールをサポートするルータの各機能に適用できます。
			<br>
			<strong><em>名前</em></strong> - スケジュールに定義する名前<br>
			<strong><em>曜日</em></strong> -
			曜日、曜日の範囲を指定します。「毎日」を選択すると、本スケジュールを適用した機能は毎日アクティブ化されます。<br>
			<strong><em>終日 - 24時間</em></strong> -
			このボックスを選択すると、本スケジュールを適用した機能は指定した曜日に終日アクティブ化されます。<br>
			<strong><em>開始時刻</em></strong> -
			本スケジュールを適用した機能がアクティブになる時間を指定します。<br>
			<strong><em>終了時刻</em></strong> -
			本スケジュールを適用した機能が非アクティブになる時間を指定します。<br>
			<strong><em>スケジュールルールリスト</em></strong> -
			定義済みのすべてのスケジュールが表示されます。
		</p>
	</td>
</tr>
</table>
</div>

						   