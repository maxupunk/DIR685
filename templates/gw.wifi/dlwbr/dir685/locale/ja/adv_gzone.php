﻿<?
$m_gz_title_select			="ゲストゾーンの選択";
$m_gz_title_router			="ゲストゾーン用ルータ設定";
$m_gz_title_isolate			="ゲストゾーン内クライアントの隔離";
$m_gz_title_to_host_routing	="ホストゾーンとゲストゾーン間のルーティング";
$m_gz_title_dhcp_server		="ゲストゾーン用DHCPサーバ設定";
$m_gz_title_dhcp_client		="ゲストゾーン用DHCPクライアントリスト";
$m_gz_title_lock_client		="ゲストゾーン用ロックされたクライアントリスト";

$m_gz_desc_router	="このセクションでは、ルータ上のゲストゾーンの設定を行います。".
									"ゲストゾーンとは、ゲストがインターネットにアクセスするための専用のネットワークです。";

$m_gz_desc_isolate	="この機能を有効化すると、ゲストゾーン内のゲストクライアント同士の通信を禁じます。".
										"ゲストクライアントはインターネットへのアクセスのみを許可されます。";

$m_gz_desc_to_host_routing	="このセクションでは、ホストゾーンとゲストゾーン間のルーティングを可能にする設定を行います。".
													"この機能を有効化していない場合は、ゲストクライアントはホストクライアントのデータにアクセスできません。";

$m_gz_desc_dhcp_server	="このセクションでは、内蔵のDHCPサーバがお客様のネットワーク上のコンピュータにIPアドレスの割り当てを行うように設定を行います。";

$m_gz_desc_lock_client	="Guest Zoneに存在するすべてのPCクライアントをロックするために使われる機能です。".
											"IP/MACアドレスリスト：このリストにあるPCだけがネットワークにアクセスできます。".
											"この機能を有効後、追加のクライアントはアクセスできなくなります。".
											"Guest Zoneは、有線もしくは無線接続を使っているかどうかに依存しません。";

$m_enable_gzone			="ゲストゾーンを有効にする";
$m_include_lan_port		="LANポートを含む";
$m_include_wireless		="無線を含む";
$m_wireless_name		="無線ネットワーク名";
$m_ssid_comment			="（SSIDとも呼ばれます）";
$m_security_mode		="セキュリティモード";
$m_router_ip			="ルータIPアドレス";
$m_router_netmask		="デフォルトサブネットマスク";
$m_enable_gzone_iso		="ゲストゾーンクライアントの隔離を有効にする";
$m_enable_gzone_route	="ゾーン間のルーティングを有効にする";
$m_enable_dhcp_server	="DHCPサーバ機能を有効にする";
$m_dhcp_ip_range		="DHCP IPアドレス範囲";
$m_to					="～";
$m_dhcp_ip_range_comment	="（LANサブネット内のアドレス）";
$m_dhcp_lease_time		="DHCPリース時間";
$m_dhcp_lease_time_comment	="（分）";
$m_lock_client			="ロッククライアントリストを有効にする";

$m_host_name		="ホスト名";
$m_expired_time		="有効期限";

$m_encr_none	="無線セキュリティを無効化する（お勧めしません）";
$m_encr_wep		="WEPによる暗号化を有効にする（基本設定）";
$m_encr_wpa		="WPAのみによる暗号化を有効にする（拡張設定）";
$m_encr_wpa2	="WPA2のみによる暗号化を有効にする（拡張設定）";
$m_encr_wpaauto	="WPA/WPA2による暗号化を有効にする（拡張設定）";

$m_title_wep	="WEP";
$m_auth_type	="認証";
$m_open			="オープン";
$m_shared_key	="共有キー";
$m_wep_key_len	="WEP暗号化方式";
$m_64bit_wep	="64ビット";
$m_128bit_wep	="128ビット";
$m_hex			="16進数";
$m_ascii		="ASCII";
$m_key_type		="キータイプ";
$m_def_wep_key	="デフォルトWEPキー";
$m_wep_key		="WEP暗号化キー";
$m_hint_wep64	="（5文字のASCII文字または10桁の16進数）";
$m_hint_wep128	="（13文字のASCII文字または26桁の16進数）";

$m_title_wpa	="WPAのみ";
$m_dsc_wpa		="WPAのみを指定した場合、ステーション側で高度の暗号化方式および認証の設定が必要となります。";
$m_title_wpa2	="WPA2のみ";
$m_dsc_wpa2		="WPA2のみを指定した場合、ステーション側で高度の暗号化方式および認証の設定が必要となります。";
$m_title_wpa_2	="WPA/WPA2";
$m_dsc_wpa_2	="WPA/WPA2を指定した場合、ステーション側で高度の暗号化方式および認証の設定が必要となります。";

$m_cipher_type	="暗号化タイプ";
$m_tkip			="TKIP";
$m_aes			="AES";
$m_psk			="PSK";
$m_eap			="EAP";
$m_passphrase	="ネットワークキー";
$m_confirm_passphrase   ="確認用ネットワークキー";
$m_psk_hint		="（8～63文字のASCII文字または64桁の16進数）";

$m_8021x		="802.1X";
$m_radius_srvr	="RADIUSサーバ";
$m_shared_sec	="共有秘密キー";

$m_days	="日";
$m_hrs	="時間";
$m_mins	="分";
$m_secs	="秒";

$a_invalid_ip			="不正なIPアドレスが指定されました。";
$a_invalid_netmask		="不正なサブネットマスクが指定されました。";
$a_network_conflict		="ゲストゾーンとホストゾーンには異なるネットワークを指定してください。";
$a_invalid_ip_range		="DHCPサーバに不正なIPアドレス範囲が指定されました。";
$a_invalid_lease_time	="不正なDHCPリース時間が指定されました。";

$a_empty_ssid	="SSIDフィールドは省略できません。";
$a_invalid_ssid	="SSIDフィールドに不正な値が入力されました。確認してください。";
$a_invalid_wep_128_wep_key		="無効なキーが指定されました。キーは13文字の文字列、または26文字の16進数で指定してください。";
$a_invalid_wep_64_wep_key		="無効なキーが指定されました。キーは5文字の文字列、または10文字の16進数で指定してください。";
$a_invalid_wep_128_ascii_wep_key="無効なキーが指定されました。キーは13文字の文字列で指定してください。";
$a_invalid_wep_128_hex_wep_key	="無効なキーが指定されました。キーは26文字の16進数で指定してください。";
$a_invalid_wep_64_ascii_wep_key	="無効なキーが指定されました。キーは5文字の文字列で指定してください。";
$a_invalid_wep_64_hex_wep_key	="無効なキーが指定されました。キーは10文字の16進数で指定してください。";
$a_invalid_passphrase_len		="パスフレーズの長さは8～63です。";
$a_invalid_passphrase			="パスフレーズはASCII文字で指定してください。";
$a_invalid_psk					="PSKは16進数で指定してください。";
$a_invalid_radius_ip			="不正なRADIUSサーバが指定されました。";
$a_invalid_radius_port			="不正なポート番号が指定されました。";
$a_invalid_radius_sec			="不正な秘密鍵が指定されました。";


?>
