﻿<?
/* ---------------------------------- */
//$TITLE=$m_pre_title."設定";
/* ---------------------------------- */
$a_empty_ssid		="SSIDフィールドは省略できません。";
$a_invalid_ssid		="SSIDフィールドに不正な値が入力されました。確認してください。";
$a_invalid_wlan_band ="802.11規格の周波数帯を選択してください。";

$a_invalid_wep_128_wep_key	="無効なキーが指定されました。キーは13文字の文字列、または26文字の16進数で指定してください。";
$a_invalid_wep_64_wep_key	="無効なキーが指定されました。キーは5文字の文字列、または10文字の16進数で指定してください。";
$a_invalid_wep_128_ascii_wep_key="無効なキーが指定されました。キーは13文字の文字列で指定してください。";
$a_invalid_wep_128_hex_wep_key	="無効なキーが指定されました。キーは26文字の16進数で指定してください。";
$a_invalid_wep_64_ascii_wep_key	="無効なキーが指定されました。キーは5文字の文字列で指定してください。";
$a_invalid_wep_64_hex_wep_key	="無効なキーが指定されました。キーは10文字の16進数で指定してください。";

$a_empty_defkey			="デフォルトWEPキーは省略できません。";
$a_valid_hex_char		="使用できる文字は0～9、A～F、a～fです。";
$a_valid_asc_char		="使用できる文字はASCII文字です。";

$a_invalid_radius_ip1		="不正なRADIUSサーバアドレスが指定されました。";
$a_invalid_radius_port1		="RADIUSサーバポートに不正な値が指定されました。";
$a_empty_radius_sec1		="RADIUSサーバの共有秘密キーは省略できません。";
$a_invalid_radius_sec1		="RADIUSサーバの共有秘密キーはASCII文字で指定してください。";
$a_invalid_passphrase_len	="パスフレーズの長さは8～63です。";
$a_invalid_psk_len		="PSKの長さは64です。";
$a_psk_not_match		="確認用パスフレーズとパスフレーズが一致しません。";
$a_invalid_passphrase	="パスフレーズはASCII文字で指定してください。";
$a_invalid_psk			="PSKは16進数で指定してください。";
$a_unknown_auth="不正な認証タイプが指定されました。";

$a_reset_wps_pin		="PINを工場出荷時のデフォルト状態にリセットしますか？";
$a_gen_new_wps_pin		="本当に新しいPINを生成しますか？";
$a_reset_wps_unconfig	="本当にデバイスを設定前の状態にリセットしますか？";
$a_enable_wps_first		="WPSはまだ有効化されていません。「設定を保存する」ボタンをクリックすると、WPSが有効になります。";

$m_title_wireless_setting	="無線ネットワーク設定";

$m_enable_wireless	="無線機能を有効化する";
$m_wlan_name		="無線ネットワーク名";
$m_wlan_name_comment	="（SSIDとも呼ばれます）";

$m_wlan_band 	="802.11無線周波数帯";
$m_wlan_band_2g ="2.4GHz";
$m_wlan_band_5g ="5GHz";
$m_11g_only		="802.11g単独モード";
$m_11a_only		="802.11a単独モード";
//for support 11n
$m_wlan_mode_set        ="802.11モード";
$m_wlan_mode_11b        ="802.11ｂのみ";
$m_wlan_mode_11g        ="802.11gのみ";
$m_wlan_mode_11n        ="802.11nのみ";
$m_wlan_mode_mix        ="802.11b/g混合";
$m_wlan_mode_mixn       ="802.11b/g/n混合";
//for support 11a
$m_wlan_mode_11a		="802.11aのみ";
$m_wlan_mode_11an 		="802.11a/n混合";

$m_wlan_band_width      ="チャネル幅";
$m_wlan_short_guard     ="ショートガード間隔";
$m_mhz                  ="MHz";

$m_enable_wireless	="無線機能を有効化する";
$m_wlan_name		="無線ネットワーク名";
$m_wlan_name_comment	="（SSIDとも呼ばれます）";
$m_wlan_channel		="無線チャネル";
$m_enable_auto_channel	="自動チャネル選択機能を有効化する";
$m_super_g		="Super Gモード";
$m_super_g_without_turbo="Super GモードTurboなし";
$m_super_g_with_d_turbo ="Super G Dynamic Turboモード";
$m_xr			="通信範囲拡大モード";
$m_11g_only		="802.11g単独モード";
$m_txrate		="通信速度";
$m_mcrate		="マルチキャストレート";
$m_best_auto	="最適（自動）";
$m_mbps			="Mビット/秒";
$m_wmm_enable	="WMMを有効化する";
$m_wlan_qos		="（ワイヤレスQoS）";
$m_enable_ap_hidden	="SSID隠蔽";
$m_ap_hidden_comment	="（SSIDブロードキャストの無効化）";

$m_title_wireless_security	="無線セキュリティモード";

$m_security_mode	="セキュリティモード";
$m_disable_security	="無線セキュリティを無効化する（お勧めしません）";
$m_enable_wep		="WEPによる暗号化を有効にする（基本設定）";
$m_wpa_security		="WPAのみによる暗号化を有効にする（拡張設定）";
$m_wpa2_security	="WPA2のみによる暗号化を有効にする（拡張設定）";
$m_wpa2_auto_security	="WPA/WPA2による暗号化を有効にする（拡張設定）";

$m_title_wep		="WEP";
$m_auth_type		="認証";
$m_open			="オープン";
$m_shared_key		="共有キー";
$m_wep_key_len		="WEP暗号化方式";
$m_64bit_wep		="64ビット";
$m_128bit_wep		="128ビット";
$m_hex			="16進数";
$m_ascii		="ASCII";
$m_key_type		="キータイプ";
$m_default_wep_key	="デフォルトWEPキー";
$m_wep_key		="WEP暗号化キー";
$m_wep64_hint_wording	="（5文字のASCII文字または10桁の16進数）";
$m_wep128_hint_wording	="（13文字のASCII文字または26桁の16進数）";

$m_title_wpa		="WPAのみ";
$m_dsc_wpa		="クライアントに高度な暗号化や認証を使わせるために「WPAのみ」を使います。";
$m_title_wpa2		="WPA2のみ";
$m_dsc_wpa2		="クライアントに高度な暗号化や認証を使わせるために「WPA2のみ」を使います。";
$m_title_wpa2_auto	="WPA/WPA2";
$m_dsc_wpa2_auto	="クライアントに高度な暗号化や認証を使わせるために「WPA/WPA2のみ」を使います。";

$m_cipher_type		="暗号化タイプ";
$m_tkip			="TKIP";
$m_aes			="AES";
$m_psk_eap		="PSK/EAP";
$m_psk			="PSK";
$m_eap			="EAP";
$m_passphrase		="ネットワークキー";
$m_confirm_passphrase	="確認用ネットワークキー";
$m_psk_hint_wording		="8～63文字のASCII文字または64桁の16進数";

$m_8021x		="802.1X";
$m_radius1		="RADIUSサーバ";
$m_shared_sec		="共有秘密キー";
?>
