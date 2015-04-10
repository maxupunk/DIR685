﻿<?
/* --------------------------------------------------------- */
//$TITLE=$m_pre_title."設定";
/* --------------------------------------------------------- */
$m_title_router_setting	="ルータ設定";
$m_desc_router_setting	="このセクションでは、お客様のルータの内部ネットワーク設定を行います。".
											"ここでは、Webベースの管理インタフェースにアクセスするためのIPアドレスを設定します。このIPアドレスを変更すると、次回のアクセスの際に、PC側のネットワーク設定の変更が必要となる場合があります。";

$m_router_ipaddr	="ルータIPアドレス";
$m_subnet_mask		="デフォルトサブネットマスク";
$m_domain_name		="ローカルドメイン名";
$m_enable_dnsr		="DNSリレーの有効化";

$m_title_dhcp_svr	="DHCPサーバ設定";
$m_desc_dhcp_svr	="このセクションでは、内蔵のDHCPサーバの設定を行い、お客様のネットワーク上のコンピュータにIPアドレスの割り当てを行えるようにします。";

$m_enable_dhcp		="DHCPサーバの有効化";
$m_dhcp_range		="DHCP IPアドレス範囲";
$m_to			="～";
$m_range_comment	="（LANサブネット内のアドレス）";
$m_lease_time		="DHCPリース時間";
$m_netbios	="NetBIOSアナウンスメント";
$m_netbios_learn	="WANからNetBIOS名を学習";
$m_netbios_scope	="NetBIOSスコープ";
$m_optional	="（任意）";
$m_netbios_type	="NetBIOSノードタイプ";
$m_broadcast	="ブロードキャストのみ（WINSサーバが設定されていない場合に使用します）";
$m_ptop	="ポイント・ツー・ポイント（ブロードキャストを行いません）";
$m_mix_mode	="混合モード（ブロードキャスト→ポイント・ツー・ポイントの順番で名前解決を試みます）";
$m_hybrid	="ハイブリッド（ポイント・ツー・ポイント→ブロードキャストの順番で名前解決を試みます）";
$m_primary_wins	="プライマリWINSサーバIPアドレス";
$m_secondary_wins	="セカンダリWINSサーバIPアドレス";

$m_minutes		="（分）";

$m_title_add_client	="DHCPアドレス予約";
$m_computer_name	="コンピュータ名";
$m_clone_mac		="PCのMACアドレスをコピーする";

$m_title_static_client_list ="DHCPアドレス予約リスト";
$remaining_wording	="登録可能なクライアントの残数";

$m_title_client_list	="DHCPクライアントリスト";
$m_host_name		="ホスト名";
$m_ipaddr		="IPアドレス";
$m_macaddr		="MACアドレス";
$m_expired_time		="期限";

$m_days	="日";
$m_hrs	="時間";
$m_mins	="分";
$m_secs	="秒";

$a_invalid_ip		="不正なIPアドレスが指定されました。";
$a_invalid_netmask	="不正なサブネットマスクが指定されました。";
$a_network_conflict	="ゲストゾーンとホストゾーンには異なるネットワークを指定してください。";
$a_lan_wan_conflict ="WANネットワークとLANネットワークには異なる値を指定してください。";
$a_invalid_domain_name	="不正なドメイン名が指定されました。";
$a_invalid_ip_range	="DHCPサーバに不正なIPアドレス範囲が指定されました。";
$a_invalid_lease_time	="不正なDHCPリース時間が指定されました。";
$a_del_confirm		="本当にこのエントリを削除しますか？";
$a_same_static_mac	="このMACアドレスは既に登録されています。他のMACアドレスを指定してください。";
$a_same_static_ip	="このIPアドレスは既に登録されています。他のIPアドレスを指定してください。";
$a_same_static_hostname ="このコンピュータ名は既に登録されています。他のコンピュータ名を指定してください。";
$a_same_with_lan_ip	="LAN IPアドレスと異なる値を指定してください。";
$a_invalid_computer_name="不正なコンピュータ名が指定されました。";
$a_invalid_mac		="不正なMACアドレスが指定されました。";

$a_invalid_form         ="NetBIOSスコープが不正な形式で指定されました。";
$a_invalid_primaywins	="NetBIOSプライマリWINSサーバに不正な値が指定されました。";
$a_invalid_secondaywins	="NetBIOSセカンダリWINSサーバに不正な値が指定されました。";
$a_primary_null		="セカンダリWINSサーバのIPアドレスを指定するには、プライマリWINSサーバも指定する必要があります。";
?>
