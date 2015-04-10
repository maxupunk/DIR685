<?


anchor("/tmp/dr");
set("domain:0/name","DEBUG");
set("domain:8/name","WORLD");
set("domain:12/name","WORLD");
set("domain:32/name","APL3_WORLD");
set("domain:51/name","ETSI4_WORLD");
set("domain:36/name","FCC2_WORLD");
set("domain:40/name","ETSI5_WORLD");
set("domain:31/name","ETSI4_WORLD");
set("domain:48/name","WORLD");
set("domain:112/name","WORLD");
set("domain:56/name","ETSI4_WORLD");
set("domain:84/name","NULL1_ETSIC");
set("domain:68/name","APL1_ETSIC");
set("domain:76/name","NULL1_ETSIC");
set("domain:96/name","APL1_WORLD");
set("domain:100/name","ETSI6_WORLD");
set("domain:124/name","FCC2_FCCA");
set("domain:152/name","APL5_WORLD");
set("domain:156/name","APL1_WORLD");
set("domain:170/name","FCC1_FCCA");
set("domain:188/name","WORLD");
set("domain:191/name","ETSI3_WORLD");
set("domain:196/name","ETSI1_WORLD");
set("domain:203/name","ETSI3_WORLD");
set("domain:208/name","ETSI1_WORLD");
set("domain:214/name","FCC1_FCCA");
set("domain:218/name","WORLD");
set("domain:818/name","WORLD");
set("domain:222/name","WORLD");
set("domain:233/name","ETSI1_WORLD");
set("domain:234/name","WORLD");
set("domain:246/name","ETSI1_WORLD");
set("domain:250/name","ETSI3_WORLD");
set("domain:255/name","ETSI3_WORLD");
set("domain:268/name","ETSI4_WORLD");
set("domain:276/name","ETSI1_WORLD");
set("domain:300/name","WORLD");
set("domain:320/name","FCC1_FCCA");
set("domain:340/name","WORLD");
set("domain:344/name","FCC2_WORLD");
set("domain:348/name","ETSI2_WORLD");
set("domain:352/name","ETSI1_WORLD");
set("domain:356/name","WORLD");
set("domain:360/name","WORLD");
set("domain:364/name","APL1_WORLD");
set("domain:368/name","WORLD");
set("domain:372/name","ETSI1_WORLD");
set("domain:376/name","WORLD");
set("domain:380/name","ETSI1_WORLD");
set("domain:388/name","WORLD");
set("domain:392/name","MKK1_MKKB");
set("domain:393/name","MKK1_FCCA");
set("domain:394/name","MKK2_MKKA");
set("domain:395/name","MKK1_MKKA1");
set("domain:396/name","MKK1_MKKA2");
set("domain:397/name","MKK1_MKKA");
set("domain:400/name","WORLD");
set("domain:398/name","WORLD");
set("domain:404/name","WORLD");
set("domain:408/name","APL2_WORLD");
set("domain:410/name","APL2_APLD");
set("domain:411/name","APL2_WORLD");
set("domain:414/name","WORLD");
set("domain:428/name","WORLD");
set("domain:422/name","WORLD");
set("domain:434/name","WORLD");
set("domain:438/name","ETSI2_WORLD");
set("domain:440/name","ETSI1_WORLD");
set("domain:442/name","ETSI1_WORLD");
set("domain:446/name","FCC2_WORLD");
set("domain:807/name","WORLD");
set("domain:458/name","WORLD");
set("domain:484/name","FCC1_FCCA");
set("domain:492/name","ETSI4_WORLD");
set("domain:504/name","WORLD");
set("domain:528/name","ETSI1_WORLD");
set("domain:554/name","FCC2_ETSIC");
set("domain:558/name","WORLD");
set("domain:578/name","ETSI1_WORLD");
set("domain:512/name","WORLD");
set("domain:586/name","WORLD");
set("domain:591/name","FCC1_FCCA");
set("domain:600/name","WORLD");
set("domain:604/name","WORLD");
set("domain:608/name","FCC1_WORLD");
set("domain:616/name","ETSI1_WORLD");
set("domain:620/name","ETSI1_WORLD");
set("domain:630/name","FCC1_FCCA");
set("domain:634/name","WORLD");
set("domain:642/name","WORLD");
set("domain:643/name","WORLD");
set("domain:682/name","WORLD");
set("domain:702/name","APL4_WORLD");
set("domain:703/name","ETSI3_WORLD");
set("domain:705/name","ETSI1_WORLD");
set("domain:710/name","ETSI1_WORLD");
set("domain:724/name","ETSI1_WORLD");
set("domain:728/name","WORLD");
set("domain:752/name","ETSI1_WORLD");
set("domain:756/name","ETSI2_WORLD");
set("domain:760/name","WORLD");
set("domain:158/name","APL3_WORLD");
set("domain:764/name","APL2_WORLD");
set("domain:780/name","ETSI4_WORLD");
set("domain:788/name","ETSI3_WORLD");
set("domain:792/name","ETSI3_WORLD");
set("domain:784/name","WORLD");
set("domain:804/name","WORLD");
set("domain:826/name","ETSI1_WORLD");
set("domain:840/name","FCC1_FCCA");
set("domain:858/name","APL2_WORLD");
set("domain:860/name","FCC3_FCCA");
set("domain:862/name","APL2_ETSIC");
set("domain:704/name","WORLD");
set("domain:887/name","WORLD");
set("domain:716/name","WORLD");

$country_code=query("/runtime/nvram/countrycode");
$domain_region=query("/tmp/dr/domain:".$country_code."/name");

$version_no=query("/runtime/sys/info/firmwareversion");
$build_no=query("/runtime/sys/info/firmwarebuildno");

$wan_mac=query("/runtime/layout/wanmac");
$lan_mac=query("/runtime/layout/lanmac");
$wlan_mac=query("/runtime/layout/wlanmac");

$fwinfo_srv=query("/sys/fwinfosrv");
$fwinfo_path=query("/sys/fwinfopath");
$model_name=query("/sys/modelname");
$ssid=get(h,"/wireless/ssid");
$build_date=query("/runtime/sys/info/firmwarebuildate");
$build_datedd      = query("/runtime/time/dateddyymm");
$build_datetime      = fread("/etc/config/builddaytime");
$build_digest      = fread("/etc/config/digest");
$wlan_driver	= query("/sys/wlandriverver");

$m_context_title	="Versione";

$m_context_title_mandatory="Obbligatorio";
$m_context_title_optional="Facoltativo";
$m_firmware_external_version = "Versione esterna firmware: ";
$m_firmware_internal_version = "Versione interna firmware: ";
$m_date = "Data:";
$m_checksum = "Checksum:";
$m_wlan_domain = "Dominio WLAN:";
$m_firmare_query = "Query firmware:";
$m_system_uptime = "Tempo di attività sistema:";
$m_wan_mac = "MAC WAN: ";
$m_lan_mac = "MAC LAN: ";
$m_wlan_mac = "MAC WLAN: ";

$m_kernel = "Kernel: ";
$m_ssid = "SSID: ";
$m_default_setting = "Impostazione di default: ";
$m_ssid = "SSID: ";
$m_svn = "SVN: ";
$m_debug_mode = "Modalità di debug: ";
$m_apps = "Applicazioni: ";
$m_wlan_driver = "Unità WLAN: ";

$m_c_mandatory = "<table>";
$m_c_mandatory = $m_c_mandatory."<tr><td class=l_tb width=200>".$m_firmware_external_version."</td><td>".$version_no."</td></tr>";
$m_c_mandatory = $m_c_mandatory."<tr><td class=l_tb>".$m_firmware_internal_version."</td><td>".$build_no."</td></tr>";
$m_c_mandatory = $m_c_mandatory."<tr><td class=l_tb>".$m_date."</td><td>".$build_datedd."</td></tr>";
//$m_c_mandatory = $m_c_mandatory."<tr><td>".$m_system_uptime."</td><td><script>document.write(shortTime());</script></td></tr>";
$m_c_mandatory = $m_c_mandatory."<tr><td>".$m_checksum."</td><td>"."<script>document.write(EncodeHex());</script></td></tr>";
$m_c_mandatory = $m_c_mandatory."<tr><td class=l_tb>".$m_wlan_domain."</td><td>".$domain_region."</td></tr>";
//$m_c_mandatory = $m_c_mandatory."<tr><td>".$m_firmare_query."</td><td>http:\/\/".$fwinfo_srv.$fwinfo_path."?model=".$model_name."</td></tr>";
$m_c_mandatory = $m_c_mandatory."<tr><td class=l_tb>".$m_firmare_query."</td><td><script>document.write(getQueryUrl());</script></td></tr>";


$m_c_optional = "<tr><td class=l_tb>".$m_wan_mac."</td><td>".$wan_mac."</td></tr>";
$m_c_optional = $m_c_optional."<tr><td class=l_tb>".$m_lan_mac."</td><td>".$lan_mac."</td></tr>";
$m_c_optional = $m_c_optional."<tr><td class=l_tb>".$m_wlan_mac."</td><td>".$wlan_mac."</td></tr>";

//$m_c_optional = $m_c_optional."<tr><td >".$m_kernel."</td><td>".$."</td></tr>";
$m_c_optional = $m_c_optional."<tr><td class=l_tb>".$m_apps."</td><td>".$build_date."</td></tr>";
$m_c_optional = $m_c_optional."<tr><td class=l_tb>".$m_wlan_driver."</td><td>".$wlan_driver."</td></tr>";
$m_c_optional = $m_c_optional."<tr><td class=l_tb>".$m_ssid."</td><td>".$ssid."</td></tr>";



$m_c_optional = $m_c_optional."</table>";

$m_context = $m_c_mandatory;
//length limit of $m_context, so add $m_context_next.
$m_context_next = $m_c_optional;

//$m_context = "版本 : ".$version_no."<br><br>Build Number : ".$build_no."<br><br>";
//$m_context = $m_context."System Uptime : <script>document.write(shortTime());</script>";

$m_days		= "giorni";
$m_button_dsc	=$m_continue;
?>
