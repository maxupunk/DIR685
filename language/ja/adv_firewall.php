﻿<?
$m_title_firewall ="ファイアウォール設定";
$m_enable_spi="SPIを有効化する";
$m_title_rtsp="アプリケーションレベルゲートウェイ（ALG)設定";
$m_enable_rtsp="RTSPを有効化する";
$m_enable_dos="DoS攻撃からの保護を有効化する";
$m_title_attack_prevention="内部攻撃からの保護を有効化する";
$m_desc_attack_prevention="防御対象の攻撃タイプ";
$m_enable_arp_attack="ARP攻撃";
$m_enable_fake_dhcp="偽DHCPサーバ";
$m_title_firewall_rules ="ファイアウォールルール";
$m_action ="アクション";
$m_allow ="許可";
$m_deny ="禁止";
$m_inf ="インタフェース";
$m_start_ip ="最小のIPアドレス";
$m_end_ip	="最大のIPアドレス";
$m_protocol	="プロトコル";
$m_port_range ="ポート範囲";
$m_src	="送信元";
$m_dst ="宛先";
$m_schedule ="スケジュール";
$m_always_on ="常にオン";
$m_add_new_sch ="スケジュールの新規追加";
$m_title_fw_list="ファイアウォールルールリスト";
$m_allow_ping ="WAN側からのPing";
$m_remote_management="リモート管理";

$m_title_dmz_rule ="DMZホスト";
$m_desc_dmz ="DMZ（Demilitarized Zone：非武装地帯）機能を使用すると、お客様のネットワーク上の任意のコンピュータをルータの外側に配置することができます。ルータの背後に配置されたコンピュータがWebアプリケーションを正常に利用できない場合は、そのコンピュータをDMZ内に配置すると、インターネットアクセスの制限を解くことができます。";

$m_note_dmz ="<strong>注意：</strong>DMZ内に配置されたコンピュータは、さまざまなセキュリティリスクにさらされることになります。この機能は、最後の手段としてご利用ください。";

$m_enable_dmz_host ="DMZホストを有効化する";
$m_ip_addr_dmz ="DMZ IPアドレス";
$m_computer_name ="コンピュータ名";

$a_no_ip_selected	="先にデバイスを選択してください。";
$a_invalid_ip		="不正なIPアドレスが指定されました。";
$a_confirm_to_del_fw="本当にこのルールを削除しますか？";
$a_invalid_port="不正なポートが指定されました。";
$a_invalid_port_range="不正なポート範囲が指定されました。";

$a_invalid_src_startip="不正な送信元最小アドレスが指定されました。";
$a_src_startip_in_different_subnet   ="不正な送信元最小アドレスが指定されました。送信元最小アドレスおよびルータアドレスは、同じサブネット内から指定してください。";

$a_invalid_src_endip="不正な送信元最大アドレスが指定されました。";
$a_src_endip_in_different_subnet   ="不正な送信元最大アドレスが指定されました。送信元最大アドレスおよびルータアドレスは、同じサブネット内から指定してください。";

$a_invalid_dst_startip="不正な宛先最小アドレスが指定されました。";
$a_dst_startip_in_different_subnet   ="不正な宛先最小アドレスが指定されました。宛先最小アドレスおよびルータアドレスは、同じサブネット内から指定してください。";

$a_invalid_dst_endip="不正な宛先最大アドレスが指定されました。";
$a_dst_endip_in_different_subnet   ="不正な宛先最大アドレスが指定されました。宛先最大アドレスおよびルータアドレスは、同じサブネット内から指定してください。";

$a_fw_name_cant_be_empty="ファイアウォール名は省略できません。";
$a_not_support_same_direction="送信元インタフェースと宛先インタフェースに同一の値は指定できません。";
$a_invalid_src_ip_range="不正な送信元IPアドレス範囲が指定されました。";
$a_invalid_dst_ip_range="不正な宛先IPアドレス範囲が指定されました。";
$a_confirm_swap_fw="本当に優先度を変更しますか？";
$a_dmzip_in_different_subnet ="不正なDMZ IPアドレスが指定されました。DMZ IPアドレスおよびルータアドレスは、同じサブネット内から指定してください。";
$a_same_rule_exist ="この名前は既に使用されています。";
$a_not_select_inf ="インタフェースを選択してください。";
?>
