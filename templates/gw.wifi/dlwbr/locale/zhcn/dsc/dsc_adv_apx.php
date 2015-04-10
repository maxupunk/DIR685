<h1>WAN加速<?
$appex_ver=fread("/proc/net/appex/version");
if($appex_ver == "") { $appex_ver=query("/apx/version"); }
if($appex_ver != "") { echo " (ver. ".$appex_ver.")"; }
?></h1>
<p>
用户通过这些选项对AppEx WAN加速设置进行配置。
</p>
