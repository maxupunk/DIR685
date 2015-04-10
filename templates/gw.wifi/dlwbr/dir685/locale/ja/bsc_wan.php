﻿<?
$m_title_ap_mode	="アクセスポイントモード";
$m_desc_ap_mode		="ルータ上のNAT機能を無効にして、アクセスポイントとして機能させます。";
$m_enable_ap_mode	="アクセスポイントモードを有効にする";

$m_title_wan_type	="インターネット接続タイプ";
$m_desc_wan_type	="ルータがインターネットに接続する際に使用するモードを選択します。";

$m_wan_type	="インターネット接続タイプは";
$m_static_ip	="スタティックIP";
$m_dhcp		="ダイナミックIP（DHCP)";
$m_pppoe	="PPPoE（ユーザ名/パスワード）";
$m_pptp		="PPTP（ユーザ名/パスワード）";
$m_l2tp		="L2TP（ユーザ名/パスワード）";
$m_russia_pptp		="ロシアPPTP（デュアルアクセス）";
$m_russia_pppoe		="ロシアPPPoE（デュアルアクセス）";
$m_mppe		="MPPE";
$m_wwan 	="３G USBアダプタ";

$m_title_static	="インターネット接続タイプ－スタティックIPアドレス";
$m_desc_static	="お客様が契約するISP（インターネットサービスプロバイダ）によって提供される、スタティックIPアドレス情報を入力します。";

$m_comment_isp	="（ISPによって割り振られた）";
$m_subnet	="サブネットマスク";
$m_isp_gateway	="ISPゲートウェイアドレス";
$m_macaddr	="MACアドレス";
$m_optional	="（任意）";
$m_clone_mac	="MACアドレスをコピー";
$m_primary_dns	="プライマリDNSアドレス";
$m_secondary_dns="セカンダリDNSアドレス";
$m_mtu		="MTU";

$m_title_dhcp	="インターネット接続タイプ－ダイナミックIP（DHCP)";
$m_desc_dhcp	="IPアドレスやユーザ名、パスワードなどの情報が、お客様が契約するISP（インターネットサービスプロバイダ）によって提供されない場合は、こちらのタイプを選択します。";

$m_host_name		="ホスト名";
$m_ppp_idle_time	="最大アイドル時間";
$m_ppp_connect_mode	="接続モードの選択";
$m_always_on		="常にオン";
$m_manual		="マニュアル";
$m_on_demand		="オンデマンド接続";

$__info_from_isp	="ISPにより提供された情報を入力してください。";

$m_title_pppoe	="PPPoE";
$m_title_russia_pppoe	="ロシアPPPoE（デュアルアクセス）";
$m_desc_pppoe	= $__info_from_isp;
$m_title_physical	="物理WAN設定";

$m_dynamic_pppoe	="ダイナミックPPPoE";
$m_static_pppoe		="スタティックPPPoE";
$m_retype_pwd		="確認用パスワード";
$m_pppoe_svc_name	="サービス名";
$m_minutes		="分";
$m_auto_dns		="ISPからDNSを取得する";
$m_manual_dns	="DNSを手動で設定する";

$m_title_pptp	="PPTP";
$m_title_russia_pptp	="ロシアPPTP（デュアルアクセス）";
$m_desc_pptp	= $__info_from_isp;

$m_title_l2tp	="L2TP";
$m_desc_l2tp	= $__info_from_isp;

$m_dynamic_ip		="ダイナミックIPアドレス";
$m_static_ip		="スタティックIPアドレス";
$m_gateway		="ゲートウェイIPアドレス";
$m_dns			="DNSサーバIPアドレス";
$m_server_ip		="サーバIPアドレス/サーバ名";
$m_pptp_account		="PPTPアカウント";
$m_pptp_password	="PPTPパスワード";
$m_pptp_retype_pwd	="確認用PPTPパスワード";
$m_l2tp_account		="L2TPアカウント";
$m_l2tp_password	="L2TPパスワード";
$m_l2tp_retype_pwd	="確認用L２TPパスワード";

$m_title_wwan			="インターネット接続タイプ－ワイヤレスWAN";
$m_desc_wwan			="ISP（インターネットサービスプロバイダ）により提供された情報を入力してください。";
$m_card_device			="カード";
$m_driver				="ドライバ";
$m_manufacturer			="製造者";
$m_product 				="製品";
$m_pin_code				="PIN";
$m_username				="ユーザ名";
$m_password				="パスワード";
$m_dial_num				="ダイヤル番号";
$m_auth_proto			="認証プロトコル";
$m_wwan_auth_auto 		="自動（PAP＋CHAP）";
$m_wwan_pap				="PAPのみ";
$m_wwan_chap			="CHAPのみ";
$m_auto_reconn 			="自動再接続";
$m_apn					="APN";
$m_enable 				="有効";
$m_disable				="無効";
$m_keep_alive_int 		="キープアライブ間隔";
$m_seconds 				="（秒）";
$m_keep_alive_server1 	="キープアライブサーバ1";
$m_keep_alive_server2 	="キープアライブサーバ2";
$m_wwan_reconn_mode		="再接続モード";
$m_wwan_minutes			="（分、０＝無限）";
$m_wwan_bytes			="（バイト）";
$m_country				="国名";
$m_isp					="ISP";
$m_choice_country		="国名を選択してください。";
$m_choice_isp			="ISP名を選択してください。";

$m_auth_server	="認証サーバ";
$m_login_server ="ログインサーバのIPアドレス/サーバ名";

/*----------802.1x------------*/

$m_8021x_setting	   	="802.1x";
$m_8021x_setting_description ="ISP（インターネットサービスプロバイダ）により提供された情報を入力してください。";

$m_8021x_eap_type		="EAPタイプ";
$m_8021x_md5			="MD5";
$m_8021x_peap			="PEAP";
$m_8021x_ttls			="TTLS";

$m_8021x_authentication	="認証";
$m_8021x_pap			="PAP";
$m_8021x_chap			="CHAP";
$m_8021x_mschap			="MSCHAP";
$m_8021x_mschapv2		="MSCHAPバージョン２";

$m_8021x_identity		="ユーザ名";
$m_8021x_pass		="パスワード";
$m_8021x_pass2		="確認用パスワード";

/*------------------------------*/


$a_invalid_ip		="不正なIPアドレスが指定されました。";
$a_invalid_netmask	="不正なサブネットマスクが指定されました。";
$a_invalid_mac		="不正なMACアドレスが指定されました。";
$a_invalid_mtu		="不正なMTU値が指定されました。";
$a_invalid_hostname	="不正なホスト名が指定されました。";
$a_invalid_username	="不正なユーザ名が指定されました。";
$a_password_mismatch	="確認用のパスワードが新しいパスワードと一致しません。";
$a_invalid_idletime	="不正なアイドル時間が指定されました。";

$a_srv_in_different_subnet	="不正なサーバIPアドレスが指定されました。サーバとルータのアドレスは同じネットワーク内から指定する必要があります。";
$a_gw_in_different_subnet	="不正なゲートウェイIPアドレスが指定されました。ゲートウェイとルータのアドレスは同じネットワーク内から指定する必要があります。";
$a_server_empty		="サーバIPアドレスおよびサーバ名は省略できません。";
$a_account_empty	="アカウントは省略できません。";

$a_card_device_not_selected ="カードが選択されていません。";
$a_dial_num_empty 			="ダイヤル番号は省略できません。";
$a_auth_proto_not_selected 	="認証プロトコルが選択されていません。";
$a_apn_empty 				="APNは省略できません。";
$a_keep_alive_int_empty 	="自動再接続が選択されている場合は、キープアライブ送信間隔は省略できません。";
$a_invalid_keep_alive_int 	="キープアライブ送信間隔の値は、20～3600の範囲から指定してください。";

/*---------------802.1x alert message---------------*/
$a_empty_username		="ユーザ名は省略できません。";
$a_empty_password		="パスワードは省略できません。";
$a_empty_password_v		="確認用パスワードは省略できません。";
$a_diff_password		="パスワードが一致しません。";
$a_empty_field			="このフィールドは省略できません。";
/*--------------------------------------------------*/

?>
