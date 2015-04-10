<div class="box">
<a name="port_forwarding"><h2>ポートフォワーディング</h2></a>
	<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=228>
		<p>
			拡張ポートフォワーディング機能を使用すると、インターネットユーザはお客様のLAN上のサービスにアクセスできるようになります。本機能はFTP/Web/ゲームサーバなどのオンラインサービスをホストする場合に便利です。このセクションではルータ上のパブリックポートと、そのポートに送られてきたデータの転送先となる内部LAN IPアドレスおよびLANポートを登録します。
		</p>
		<p>
			拡張ポートフォワーディングパラメータ<br>
			<strong><em>名前</em></strong> -
			仮想サーバの識別しやすい名前（例：Webサーバ）を登録します。「アプリケーション名」ドロップダウンリストから、一般的な仮想サーバ名（タイプ）を選択できます。このリストから仮想サーバ名を選択すると、その後の関連パラメータに、選択したサーバタイプに適した値が自動入力されます。<br>
			<strong><em>IPアドレス </em></strong> -
			仮想サービスの提供に使用するお客様の内部ネットワーク上のシステムのIPアドレス（例：192.168.0.50）。「コンピュータ名」ドロップダウンリストに表示されるDHCPクライアントのリストから、コンピュータを選択するか、あるいはサーバのIPアドレスを手動で入力することもできます。<br>
			<strong><em>アプリケーション名 </em></strong> -
			既に定義されている一般的なアプリケーションのリストです。ここから必要なアプリーケーションを選択することで設定が簡単に行えます。<br>
			<strong><em>コンピュータ名 </em></strong> - DHCPクライアントのリストです。<br>
			<strong><em>トラフィックタイプ</em></strong> -
			サービスで使用するプロトコルを選択します。一般的なプロトコルタイプ（UDP、TCP、UDPおよびTCP）は、ドロップダウンリストから選択できます。<br>
			<strong><em>プライベートポート</em></strong> -
			内部ネットワーク上のポートを指定します。<br>
			<strong><em>パブリックポート</em></strong> -
			インターネット側からのアクセスに使用するポートです。<br>
		</p>
	</td>
</tr>
 </table>
 </div>
 
 
<div class="box">
<a name="application_rules"><h2>アプリケーションルール</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=64> 
インターネットゲームやビデオ会議、インターネット電話などのアプリケーションは、複数のコネクションを必要とします。このようなアプリケーションがNAT（Network Address Transation）を越えて通信するのは困難です。複数のコネクションが必要なアプリケーションを利用するには、「トリガポート」フィールドにアプリケーションに対応するポート番号を入力し、「プロトコルタイプ」（TCP/UDP）を選択します。その際、インバウンドトラフィックを通すために、「ファイアウォールポート」フィールドでトリガーポートと関連するパブリックポートを入力してください。「アプリケーション名」のドロップダウンメニューの中にwell-knownポートは既に定義されています。
<br>

<strong><em>名前 </em></strong> - アプリケーションを識別する名前です。 <br>
<strong><em>トリガポート</em></strong>- アプリケーションを起動するために使われるポートです。1つのポートもしくはポートレンジの両方を指定することができます。 <br>
<strong><em>トラフィックタイプ </em></strong> - アプリケーションを起動するために使われるプロトコルです。<br>
<strong><em>ファイアウォールポート </em></strong> - アプリケーションへのアクセスに使用するWAN側のポート番号です。1つのポートまたは複数のポートを指定できます。複数のポートまたはポート範囲を指定するには、カンマ（,）を使用します。 <br>
<strong><em>トラフィックタイプ </em></strong> - アプリケーションで使用されるプロトコルです。</td>

 </tr>
 </table>
 </div>
 
 
<div class="box">
<a name="qos_engine"><h2>QoSエンジン</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
<td height=64>
		<p>
			Smart QoS機能は、FTPやWeb用のネットワークトラフィックよりも、VoIPやストリーミングトラフィックを優先的に扱うことで、VoIPの音質やストリーミングの質を向上させます。「遅延除去」を選択すると、アプリケーションに対して優先度が自動的に設定され、パフォーマンスを最適化します。
			<br>
		</p>
</td>
</tr>
</table>
</div>
 
 
<div class="box">
<a name="access_control"><h2>ネットワークフィルタ</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=99>
		<p>
			フィルタを使用すると、LAN内のコンピュータにインターネットへのアクセスおよびネットワークへのアクセスを許可/禁止できるようになります。ネットワーク内のコンピュータのMACアドレスを指定して、インターネットへのアクセスを許可/禁止するように設定できます。
		</p>
		<p>
			<strong>MACフィルタ</strong><br>
			MACフィルタを使用すると、LAN内のコンピュータからのインターネットアクセスを禁止できます。対象のデバイスのMACアドレスを手動で登録する方法と、現在<?query("/sys/modelname");?>に接続中のクライアントのリストからMACアドレスを選択する方法が用意されています。
			<br>
			指定したコンピュータに対してのみネットワークヘのアクセスを許可したい場合は、「MACフィルタをオンにして以下のMACアドレスのコンピュータにネットワークへのアクセスを許可する」を選択します。
			<br>
			リストに登録したコンピュータ以外のすべてのコンピュータにネットワークへのアクセスを許可したい場合は、「MACフィルタをオンにして以下のMACアドレスのコンピュータにネットワークへのアクセスを禁止する」を選択します。
			<br>
			<strong><em>MACアドレス</em></strong> -
			MACフィルタリストに登録するネットワークデバイスのMACアドレス<br>
			<strong><em>DHCPクライアントリスト</em></strong> -
			DHCPクライアントのホスト名は「コンピュータ名」ドロップダウンリストに表示されます。MACフィルタリストに追加するクライアントコンピュータを選択して、矢印ボタン「<<」をクリックします。するとそのコンピュータのMACアドレスが「MACアドレス」フィールドに自動的に入力されます。
		</p>
		<p>
		<strong>常時</strong>ドロップダウンメニューから、定義済みのスケジュールを選択できます。また<strong>新規登録</strong>ボタンをクリックすると新しいスケジュールを追加できます。
		</p>
		<p>
			チェックボックスを選択/非選択すると、対象のエントリを有効/無効にできます。
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="parental_control"><h2>Webサイトフィルタ</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=44>
		<p>
			<?query("/sys/modelname");?>では、お客様のネットワークやインターネットにアクセスするデバイスをフィルタする機能に加え、ドメイン名やキーワードを指定して、お客さまのネットワーク上のコンピュータから不適切なWebサイトへのアクセスを許可/禁止する機能も提供しています。
		</p>
		<p>
			<strong>ペアレンタルコントロール</strong><br>
			ペアレンタルコントロールは、キーワードやドメイン名を指定して、お客様のネットワーク上のコンピュータから特定のWebサイトへのアクセスを許可/禁止する機能です。「Webサイトフィルタリングをオンにして、これらのサイトへのアクセスのみを許可する」を選択すると、ネットワーク上のコンピュータは指定したURLやドメインへのアクセスしかできなくなります。「Webサイトフィルタリングをオンにして、これらのサイトへのアクセスのみを禁止する」を選択すると、ネットワーク上のコンピュータから指定したURLやドメインへのアクセスが禁止されます。
		</p>
		<p>
			<span class="style1">例1：</span><br>
			LAN内のユーザにショッピング関連サイトへのアクセスを禁止したい場合は、「Webサイトフィルタリングをオンにして、これらのサイトへのアクセスのみを禁止する」を選択し、Webサイトフィルタリングルールリストに「shopping」と入力します。すると、URLに指定したキーワードが含まれるため、以下のようなサイトへのアクセスが拒否されます。
			<br>
			<a href="http://www.yahoo.com/shopping/stores.html">http://www.yahoo.com/shopping/stores.html</a><br>
			<a href="http://www.msn.com/search/shopping-spree.html">http://www.msn.com/search/shopping-spree.html</a>
		</p>
		<p>
			<span class="style1">例2：</span><br>
			子供が特定のサイトにのみアクセスできるようにしたい場合は、「Webサイトフィルタリングをオンにして、これらのサイトへのアクセスのみを許可する」を選択して、アクセスさせたいドメインを入力します。
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
<a name="firewall_dmz"><h2>ファイアウォール設定</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			ファイアウォール設定のセクションでは、DMZホストの設定も行えます。
		</p>
		<p>
			<strong>SPIの有効化</strong><br>
			SPI（"ステートフルパケットインスペクション"別名"ダイナミックパケットフィルタリング"）機能は、通信セッションごとにパケットの整合性を追跡して、サイバー攻撃を防御します。SPIはセッション中のトラフィックがプロトコルに矛盾していないかをチェックします。プロトコルがTCPの場合、SPIはセッション内のパケットのシーケンス番号の整合性を確認し、無効なシーケンス番号を持つパケットを廃棄します。SPIが無効になっている場合でも、ルータは常にTCPコネクションの状態を追跡し、各TCPパケットフラグが現在の状態に対して整合性を保っていることを確認します。
		</p>
		<p>
			<strong>DMZ </strong><br>
			ルータの背後に配置されたコンピュータがWebアプリケーションを正常に利用できない場合、そのようなコンピュータのIPアドレスをDMZ（非武装地帯）ホストとして登録することでインターネットアクセスの制限を解くことができます。DMZに登録されたコンピュータは、さまざまなリスクにさらされる場合があるため、本機能は最後の手段としてご利用ください。
		</p>
		<p>
			<strong>ファイアウォールルール</strong><br>
			ファイアウォールルールを使用すると、ルータに入出力するトラフィックを、送信元/宛先アドレスやトラフィックタイプ、またはデータが通過するポートに基づいて許可/禁止することができます。
			<br>
			<strong><em>名前</em></strong> - ファイアウォールルールの名前を登録します。<br>
			<strong><em>アクション</em></strong> - トラフィックを許可するか禁止するかを選択します。<br>
			<strong>インタフェース</strong><br>
			<strong><em>送信元</em></strong> -
			許可/禁止の対象となるトラフィックのスタートポイントとして、<strong>送信元</strong>ドロップダウンメニューから、LANまたはWANインタフェースのいずれかを選択します。
			<br>
			<strong><em>宛先</em></strong> -
			許可/禁止の対象となるトラフィックのエンドポイントとして、<strong>宛先</strong>ドロップダウンメニューからLANまたはWANインタフェースを選択します。
			<br>
			<strong><em>IPアドレス</em></strong> -
			送信元/宛先IPアドレスを指定します。1件のアドレスを指定する場合には、上のボックスのみに入力します。アドレス範囲を指定する場合は、最初のアドレスを上のボックスに、最後のアドレスをしたのボックスに入力します。
			<br>
			<strong><em>プロトコル</em></strong> -
			<strong>プロトコル</strong>ドロップダウンメニューからトラフィックタイプを選択します。<br>
			<strong><em>ポート範囲</em></strong> -
			1つのポートを指定する場合は、上下のボックスに同じポート番号を入力します。ポート範囲を指定する場合は、上/下それぞれのボックスに、範囲の最初/最後のポートを入力します。<br>
			<strong><em>スケジュール</em></strong> -
			<strong>常時</strong>ドロップダウンメニューをクリックして以前に定義したスケジュールを選択するか、あるいは<strong>新規作成</strong>ボタンをクリックして新しいスケジュールを追加します。
 </p>
</td>
</tr>
</table>
</div>


<div class="box">
<a name="routing"><h2>ルーティング</h2></a>
<table>
<?if(query("/runtime/func/dis_routing")!="1"){
echo "<tr>\n";
echo "	<td height=99>\n";
echo "		ルーティングオプションでは、特定の宛先へのスタティックルートを定義します。<br>\n";
echo "		<strong><em>有効化 </em></strong> - 選択/非選択して、エントリを有効化/無効化します。<br>\n";
echo "		<strong><em>インタフェース </em></strong> - このルートが使用されるとき、IPパケットをルータ上で転送するために使用するインタフェース\n";
echo "		（WANまたは物理WAN)を指定します。<br>\n";
echo "		<strong><em>インタフェース（WAN）</em></strong> -インターネットアクセス用にISPが提供するIPアドレスを\n";
echo "		受信するためのインタフェース<br>\n";
echo "		<strong><em>インタフェース（物理WAN）</em></strong> - インターネットアクセス用にISPが提供するIPアドレスを\n";
echo "		受信するためのインタフェース<br>\n";
echo "		<strong><em>宛先 </em></strong> - このルートを使用するパケットの宛先IPアドレス<br>\n";
echo "		<strong><em>サブネットマスク </em></strong> - IPアドレスのどのビットがマッチすべきかを\n";
echo "		指定するマスク<br>\n";
echo "		<strong><em>ゲートウェイ </em></strong> - このルートのネクストホップを指定します。0.0.0.0と指定すると、ネクストホップが存在しない設定となり、\n";
echo "		上記の宛先IPアドレスにマッチしたパケットは直接ルータの指定インタフェース（\n";
echo "		WANまたは物理WAN)に送信されます。 \n";
echo " </td>\n";
echo " </tr>\n";
}
?>
</table>
</div>


<div class="box">
<a name="advanced_wireless"><h2>無線詳細設定</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=20>

 <p>このページにおいて誤った設定を行うとパフォーマンスに悪影響を与える場合があります。ここでの設定変更はお客様が上級ユーザである場合、あるいは弊社のサポートスタッフによる指示があった場合にのみ行ってください。
</p>
 <p><strong><em>送信電力 - </em></strong><?query("/sys/modelname");?>の送信電力（100%, 50%, 25%, 12.5%）をドロップダウンメニューから選択できます。 </p>
 <p><strong><em>ビーコン間隔 - </em></strong> ビーコンは無線ネットワークとの同期を計る目的でアクセスポイントから送出するパケットです。20～1000（ミリ秒）の範囲から指定してください。デフォルト値は100（ミリ秒）です。 </p>

 <p><strong><em>RTS閾値 - </em></strong> なるべくデフォルトの設定（2346）のまま使用してください。データフローに不整合が発生している場合は、256～2346の範囲内で微調整することをお勧めします。デフォルト値は2346です。</p>
 <p><strong><em>フラグメント閾値 - </em></strong> なるべくデフォルトの設定（2346）のまま使用してください。パケットエラー率が高い場合、1500～2346の範囲内で大きめの値を指定して問題を回避できる場合があります。値が小さすぎると、パフォーマンスに悪影響を与える場合があります。</p>
 <p><strong><em>DTIM間隔 - </em></strong> DTIM（Delivery Traffic Indication Message）間隔を1～255の範囲で値を入力してください。DTIMは、、ブロードバンドおよびマルチキャスト メッセージをリッスンする次のウィンドウをクライアントに知らせるカウントダウン項目です。アクセスポイントは、アソシエートしたクライアント向けのブロードキャストやマルチキャストメッセージをバッファすると、DTIM間隔値で設定した次のDTIMを送信します。クライアントは、ビーコンをを検知し、ブロードキャストやマルチキャストメッセージを受信するためにアウェイク状態となります。DTIM間隔のデフォルト値は1です。</p>

 <p><strong><em>プリアンブルタイプ - </em></strong> プリアンブルタイプでは、アクセスポイントとローミング中の無線アダプタ間の通信で使用するCRCブロックの長さを定義します。適切なタイプを選択したら「適用」ボタンをクリックしてください。 </p>
 <p><span class="style2">注意： </span>高負荷なネットワークにはショートプリアンブルを使用します。CRCはデータ転送エラーの検知を行う一般的な技術です。</p>
 <p><strong><em>CTSモード - </em></strong>本機能を無効にするには「なし」を選択します。「常時」を選択すると、ルータはネットワーク上の無線デバイスからのデータ送信を許可するまえに、RTS/CTSハンドシェークを行うよう要求します。「自動」を選択すると、ルータがRTS/CTSハンドシェークが必要かどうかを判断します。 </p>
<?if(query("/runtime/func/ieee80211n")!="1"){
 echo "<p><strong><em>802.11g Only Mode - </em></strong>Enable this mode if your network is made up of purely 802.11g devices. If you have both 802.11b and 802.11g wireless clients, disable this mode. </p> </td>";
}?>
 </tr>
 </tr>
 </table>
 </div>
 
 
<div class="box">
<a name="advanced_network"><h2>ネットワーク詳細設定</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=20>

 <p>このセクションでは、ルータが特定のタイプのトラフィックに対して行う処理方法を変更できます。ここでの変更は、これらの設定内容について熟知されている方、あるいは弊社のサポートスタッフによる指示があった場合のみ行ってください。
</p>

<!--
 <p><strong>VPN Passthrough </strong><br>The device supports VPN (Virtual Private Network) passthrough for PPTP (Point-to-Point Tunneling Protocol) and IPSec (IP Security). Once VPN passthrough is enabled, there is no need to create any Virtual Server or Port Forwarding entries in order for outbound VPN sessions to be established properly. Multiple VPN connections can be made through the device. This is useful when you have many VPN clients on the Local Area Network. </p>
-->

 <p><strong>UPnP </strong><br>UPnPとはユニバーサルプラグアンドプレイの略で、ネットワーク機器、ソフトウェアおよび周辺機器間の互換性を提供するネットワーキングアーキテクチャです。<?query("/sys/modelname");?>はUPｎPをサポートしており、他のUPｎP対応デバイスやソフトウェアと互換性を持ちます。UPｎP機能を使用したくない場合は、「無効にする」を選択してください。
</p>
 <p><strong>WAN Ping </strong><br>WAN側からのPingへの応答を有効にすると、インターネット側のユーザからパブリックWAN（Wide Area Network）IPアドレス宛に送信されたPingコマンドに応答を返すようになります。ハッカーがパブリックWAN IPアドレスにPing送信を行い、そのアドレスの有効性をテストするケースがよくあります。
</p>
 <p><strong>WANポート速度 </strong><br><?query("/sys/modelname");?>のWANインタフェースの通信速度を指定できます。100Mbps, 10Mbps, 10/100/1000Mbps自動検知から選択可能です。 
</p>

<!--
 <p><strong>Gaming Mode </strong><br>If you are experiencing difficulties when playing online games or even certain applications that use voice data, you may need to enable Gaming Mode in order for these applications to work correctly. When not playing games or using these voice applications, it is recommended that Gaming Mode is disabled. </p>
--> 

<?if(query("/runtime/func/dis_multicast_stream")!="1"){
echo " <p><strong>マルチキャストストリーム</strong><br>このオプションを有効化すると、インターネット側からお客様のネットワークへのマルチキャストトラフィックの転送効率を向上します。</p> </td>\n";
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
<a name="guest_zone"><h2>ゲストゾーン</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			ゲストゾーンの選択<br>
			ゲストゾーンの規模を定義できます。<br>
			<strong><em>ゲストゾーンを有効にする</em></strong>  - 指定したゲストゾーンを有効/無効にします。<br>
			<strong><em>LANポートを含む</em></strong>  - ゲストゾーンに含めるLANポートを指定します。<br>
			<strong><em>無線を含む</em></strong>  - ゲストゾーンに別の無線ゾーンを使用するかどうかを指定します。<br>
			<strong><em>無線ネットワーク名</em></strong> -  ゲストゾーンに名前を登録します。<br>
		</p>
		<p>
			<strong><em>無線セキュリティモード</em></strong><br>
			無線ネットワーク上で送受信される情報の整合性を保つために無線ネットワークのセキュリティは重要です。<?query("/sys/modelname");?>はWEP、WPAのみ、WPA2のみ、WPA/WPA2（自動検出）の4種類の無線セキュリティを提供します。
			<br>
		</p>
		<p>
			<strong><em>WEP</em></strong><br>
			WEP（Wired Equivalent Protocol）は、無線LAN用のセキュリティプロトコルです。WEPではWLAN上で送受信されるデータを暗号化することで安全性を提供します。<?query("/sys/modelname");?>は、64ビットと128ビットの2つのレベルのWEP暗号方式をサポートします。WEPはデフォルトでは無効化されています。WEP設定を変更して、既存の無線ネットワークに適合させたり、無線ネットワークをカスタマイズできます。
			<br>
		</p>
		<p>
			<strong><em>認証</em></strong> - 認証とは、<?query("/sys/modelname");?>が無線ネットワークへのアクセスを試みるネットワークデバイスの身元を確認するプロセスを意味します。本デバイスでWEPを使用する場合、2種類の認証方法が提供されます。<br>
			<strong><em>オープンシステム</em></strong> -このオプションを選択すると、ネットワークへのアクセスに必要な暗号化キーの提示を求めれる前に、すべての無線デバイスと<?query("/sys/modelname");?>の接続が可能になります。<br>
			<strong><em>共有キー </em></strong> - このオプションを選択すると、<?query("/sys/modelname");?>との通信を試みる無線デバイスは、<?query("/sys/modelname");?>との接続を許可される前にネットワークアクセス用の暗号化キーの提示を求められます。<br>
			<strong><em>WEP暗号</em></strong> - ネットワークで使用するWEP暗号化方式のレベルを選択します。64ビットと128ビットの2つのレベルがサポートされています。<br>
			<strong><em>キータイプ </em></strong> - <?query("/sys/modelname");?>がサポートするキータイプはHEX（16進数）およびASCIIです。キータイプを変更して、既存の無線ネットワークに適合させたり、無線ネットワークをカスタマイズできます。<br>
			<strong><em>キー</em></strong> - キー1からキー4を指定して、ネットワーク保護に使用する無線暗号キーを簡単に変更できます。ネットワーク上の無線データの暗号化に使用するキーを、1～4から選択します。 <br>
		</p>
		<p>
			<strong><em>WPAパーソナル</em></strong><br>
			WPA（Wi-Fi Protected Access）は、無線ネットワーク上でのユーザの認証を行います。WPAでは、キーが一定の間隔で定期的に変更されるため、WEPより高い安全性を提供します。
		<br>
		</p>
		<p>
			<strong><em>暗号化タイプ</em></strong> -<?query("/sys/modelname");?>では、セキュリティタイプにWPAが指定される場合、TKIP（Temporal Key Integrity Protocol）とAES（Advanced Encryption Standard）の2種類の暗号タイプを提供します。<br>
			<strong><em>PSK/EAP</em></strong> -PSKを選択すると、認証を行うために無線クライアントからのパスフレーズの提示が必要となります。EAPを選択する場合は、すべての無線クライアントの認証を行うRADIUSサーバをネットワーク上に設置する必要があります。<br>
			<strong><em>パスフレーズ </em></strong> -PSKを使用する場合、無線クライアントが<?query("/sys/modelname");?>と通信する際に必要となります。8～63文字の英数字を入力してください。このパスフレーズは、ネットワークに無線デバイスを追加する際に必要となるため、書き留めるなどして保管してください。 <br>
			<strong><em>802.1X </em></strong> - WPA認証が、ネットワーク上に設置したRADIUSサーバを使用して行われることを意味します。RADIUSサーバに設定したIPアドレス、ポート、共有秘密キーを入力してください。無線クライアントの認証に使用するRADIUSサーバがネットワーク上に2台ある場合は、2台目のRADIUSサーバの情報も入力してください。<br>
		</p>
		<p>
			<strong><em>WPA2</em></strong><br>
			WPA2（Wi-Fi Protected Access 2）は、無線ネットワーク上でのユーザの認証を行います。WPAでは、キーが一定の間隔で定期的に変更されるため、WEPより高い安全性を提供します。
			<br>
		</p>
		<p>
			<strong><em>暗号化タイプ</em></strong> - <?query("/sys/modelname");?>では、セキュリティタイプにWPAが指定される場合、TKIP（Temporal Key Integrity Protocol）とAES（Advanced Encryption Standard）の2種類の暗号タイプを提供します。<br>
			<strong><em>PSK/EAP</em></strong> - PSKを選択すると、認証を行うために無線クライアントからのパスフレーズの提示が必要となります。EAPを選択する場合は、すべての無線クライアントの認証を行うRADIUSサーバをネットワーク上に設置する必要があります。<br>
			<strong><em>パスフレーズ</em></strong> - PSKを使用する場合、無線クライアントが<?query("/sys/modelname");?>と通信する際に必要となります。8～63文字の英数字を入力してください。このパスフレーズは、ネットワークに無線デバイスを追加する際に必要となるため、書き留めるなどして保管してください。<br>
			<strong><em>802.1X </em></strong> - WPA2認証が、ネットワーク上に設置したRADIUSサーバを使用して行われることを意味します。RADIUSサーバに設定したIPアドレス、ポート、共有秘密キーを入力してください。無線クライアントの認証に使用するRADIUSサーバがネットワーク上に2台ある場合は、2台目のRADIUSサーバの情報も入力してください。<br>
		</p>
		<p>
			<strong><em>WPA2自動検知</em></strong> <br>
			このオプションを選択すると、WPA2とWPAの両方のクライアントの同時接続が可能になります。
			<br>
		</p>
		<p>
			<strong><em>ゲストゾーン用LAN設定</em></strong><br> 
			デバイスのゲストゾーンLANインタフェースの設定を行います。これらの設定は、"プライベート設定"とも呼ばれます。必要であればIPアドレスを変更できます。このIPアドレスは内部ネットワーク専用のアドレスで、インターネット側からは見ることが出来ません。デフォルトのIPアドレスは192.168.1.1で、サブネットマスクは255.255.255.0です。
			<br>
		</p>
		<p>
			<strong><em>IPアドレス</em></strong> - <?query("/sys/modelname");?>のIPアドレス。デフォルト値は192.168.1.1。<br>
			<strong><em>サブネットマスク</em></strong> - <?query("/sys/modelname");?>のサブネットマスク。デフォルト値は255.255.255.0。<br>
		</p>
		<p>
			<strong><em>ゲストゾーンクライアントの隔離を有効にする：</em></strong> : <br>
			ゲストゾーン内のゲストクライアント同士のアクセスを禁じます。ゲストクライアントはインターネットへのみアクセス可能です。
		 <br>
		</p>
		<p>
			<strong><em>ゾーン間のルーティングを有効にする：</em></strong> : <br>
			このセクションではホストゾーンとゲストゾーン間のルーティングを有効にします。この機能が無効化されていると、ゲストクライアントはホストクライアントのデータにアクセスできません。
			<br>
		</p>
		<p>
			<strong><em>ゲストゾーン用DHCPサーバ</em></strong> <br>
			DHCPはDynamic Host Control Protocolの略です。DHCPサーバはネットワーク上のデバイスからの要求に基づき、IPアドレスを割り当てます。これらのデバイスには「自動的にIPアドレスを取得する」設定をしておく必要があります。<?query("/sys/modelname");?>では、このDHCPサーバ機能はデフォルトで有効化されています。DHCPアドレスプールには、ネットワーク上のクライアントに自動的に割り当てるIPアドレス範囲が登録されています。
			<br>
		</p>
		<p>
			<strong><em>最小IPアドレス</em></strong> - DHCPサーバが割り当てるIPアドレス範囲の最小のアドレス。<br>
			<strong><em>最大IPアドレス</em></strong> -DHCPサーバが割り当てるIPアドレス範囲の最大のアドレス。<br>
			<strong><em>リース時間</em></strong> -IPアドレスをリースする時間（分）。<?query("/sys/modelname");?>に接続するダイナミックDHCPクライアントの情報は、ダイナミックDHCPクライアントテーブルに表示されます。テーブルでは、各クライアントコンピュータのホスト名、IPアドレス、MACアドレスおよびリースの有効期限が確認できます。<br>
		</p>
</td>
</tr>
</table>
</div>
 
<div class="box">
<a name="wake_on_lan"><h2>Wake on LAN</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			Wake on LAN機能を使用すると、ルータのLAN側に接続するPCの電源をリモートから投入できるようになります。ルータがWake on LANリクエストを有害な攻撃であるとみなして、ブロックしてしまわないように、Wake on LANマジックパケットを送信するUDPポートを指定します。
			<br>
			<br>
			<strong><em>UDPポート</em></strong> - 
			<?query("/sys/modelname");?>がPCの電源投入を行うために使用するマジックパケットをリッスンする特定のポート。<br>
			<strong><em>インタフェース</em></strong> - 
			（この設定は現在変更できません。将来のファームウェアリリースにおいて変更可能とする予定です。）<br>		
		</p>
	</td>
</tr>
</table>
</div>
