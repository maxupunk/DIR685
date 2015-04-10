<div class="box">
<a name="port_forwarding"><h2>포트 포워딩</h2></a>
	<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=228>
		<p>
			고급 포트 포워딩 옵션은 인터넷을 통해서 유저가 LAN에 접근 가능합니다. FTP, Web 또는 게임 서버 등 온라인 서비스에 유용합니다. 내부 LAN IP 어드레스와 LAN포트를 public 포트로 리다이렉션 해 줍니다.
		</p>
		<p>
			고급 포트 포워딩 변수<br>
			<strong><em>이름</em></strong> -
			웹서버,  사용 가능한 가상서버의 어플리케이션 네임 리스트에 에 사용되는 이름을 의미합니다.  엔트리중 하나를 선택하시고 스탠다드 밸류에 맞춰서 입력하세요.
			<br>
			<strong><em>IP 어드레스 </em></strong> -
			시스템의 IP 어드레스는 가상서비스를 제공합니다 예를들면192.168.0.50. 드롭다운 메뉴에서 DHCP 클라이언트를 선택하시고 또는 수동으로 IP 어드레스를 입력하세요.
			<br>
			<strong><em>어플리케이션 이름 </em></strong> -
			빠른 설정을 위해 사용자가 선택할수 있게 미리 정의된 어플리케이션 리스트 입니다.<br>
			<strong><em>컴퓨터 이름 </em></strong> - DHCP 클라이언트 리스트 입니다.<br>
			<strong><em>트래픽 타입</em></strong> -
			사용하는 서비스 프로토콜을 선택하세요. 보통 UDP, TCP 또는 UDP와 TCP를 드롭다운 메뉴에서 선택하세요<br>
			<strong><em>프라이비트 포트</em></strong> -
			내부 네트워크에서 사용하는 포트 입니다.<br>
			<strong><em>퍼블릭 포트</em></strong> -
			인터넷에 접속, 사용하는 포트 입니다.<br>
		</p>
	</td>
</tr>
 </table>
 </div>
 
 
<div class="box">
<a name="application_rules"><h2>어플리케이션 규칙</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=64> 
일부 어플리케이션은 여러 개의 연결 예를 들면 인터넷 게임, 비디오 컨퍼런스, 인터넷 텔레포니 등을 필요로 합니다. 이러한 어플리케이션은 NAT (Network Address Translation) 통해 동작합니다. 여러 개의 연결을 위해 어플리케이션을 동작시킬때 특히 "Trigger 포트"필드와  TCP (Transmission Control Protocol) 또는  UDP (User Datagram Protocol)와 연관이 있으며, 인바운드 트래픽을 위해 퍼블릭 포트와 방화벽의 포트의 trigger 포트를 할당 오픈을 합니다. 드롭메뉴에서 well-known 어플리케이션으로 미리 정의를 합니다.
<br>

<strong><em>이름 </em></strong> - 어플리케이션 이름 입니다. <br>
<strong><em>Trigger 포트 </em></strong>- 어플리케이션을 trigger 하는 포트입니다. 한 개의 포트 일수도 여러 개 일수도 있습니다.<br>
<strong><em>트래픽 타입 </em></strong> - 어플리케이션을 trigger 하는 프로토콜입니다.<br>
<strong><em>방화벽 포트 </em></strong> - WAN 사이드 포트 넘버 이며, 어플리케이션에 접근에 사용됩니다. 싱글 포트나 여러 개의 포트로 정의 합니다. 콤마를 사용하여 여러 개의 포트나 포트 범위를 추가합니다.<br>
<strong><em>트래픽 타입 </em></strong> - 어플리케이션을 사용하는 프로토콜입니다. </td>

 </tr>
 </table>
 </div>
 
 
<div class="box">
<a name="qos_engine"><h2>Qos엔진</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
<td height=64>
		<p>
			스마트 Qos는 VoIP 보이스 또는 스트리밍 트래픽을 FTP나 Web 트래픽보다 우선으로 처리합니다. 최고 성능을 위해 "lag eliminated" 옵션을 체크하고 자동으로 우선순위에 적용됩니다.
			<br>
		</p>
</td>
</tr>
</table>
</div>
 
 
<div class="box">
<a name="access_control"><h2>네트워크 필터</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=99>
		<p>
			필터는 LAN 컴퓨터를 불가 또는 허용합니다. 맥 어드레스를 이용해서 장비를 허용 또는 불가 합니다.
		</p>
		<p>
			<strong>맥 필터</strong><br>
			맥필터를 이용해서 컴퓨터가 인터넷에 접속하는 것을 막을수 있습니다. 현재 접속되어 있는 장치의 맥어드레스 수동으로 선택하거나,  클라이언트 리스트에 있는 맥어드레스를 지정할 수도 있습니다.
			<br>
			컴퓨터를 선택하거나 모든 다른 컴퓨터를 지정할때 "맥 필터링을 On 하고 리스트에 있는 맥어드레스를 인터넷 접근 허용"을 선택하세요. 
			<br>
			리스트에 있는 컴퓨터를 제외한 모든 컴퓨터를 지정할때 "맥 필터링을 On 하고 리스트에 있는 맥어드레스를 인터넷 접근 불가"를 선택하세요. 
			<br>
			<strong><em>맥 어드레스</em></strong> -
			맥 필터 리스트에 맥 어드레스 추가합니다.<br>
			<strong><em>DHCP 클라이언트 리스트</em></strong> -
			드롭다운 메뉴에서 컴퓨터 이름란에 DHCP 클라이언트 호스트 이름이 나열됩니다. 클라이언트 컴퓨터를 선택하고 맥 필터 리스트에 화살표 버튼을 눌러 추가합니다. 자동으로 알맞은 필드에 맥 어드레스가 추가됩니다.
		</p>
		<p>
		사용자는 미리 정의된 스케쥴을 선택하기 위해 <strong>항상</strong> 드롭다운 메뉴를 이용하거나 새로운 스케쥴을 추가하기위해 <strong>뉴</strong> 버튼을 클릭합니다. 
		</p>
		<p>
			체크박스는 특정 엔트리를 동작 또는 비동작하는데 사용합니다.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="parental_control"><h2>웹사이트 필터</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=44>
		<p>
			<?query("/sys/modelname");?>는 컴퓨터나 네트워크 또는 적당하지 않은 웹사이트등을 필터기능을 이용하여 액세스 허용 도는 액세스 불가를 설정합니다.
		</p>
		<p>
			<strong>Parental control</strong><br>
			Parental control은 특정한 웹사이트나 키워드 도메인 네임을 접근하려는 컴퓨터를 허용 또는 불가 할 수 있습니다. 특정 URLs과 도메인 네임을 접근 할수 있도록 "웹사이트 필터링을 On 하고 단지 이 사이트만  접근허용 "을 선택하세요. 특정 URLs과 도메인 네임을 접근 하지 못하도록 "웹사이트 필터링을 On 하고 단지 이 사이트만 접근불가 "을 선택하세요. 
		</p>
		<p>
			<span class="style1">예제 1:</span><br>
			만일 쇼핑과 관련된 URL 웹사이트를 막고 싶다면  "웹사이트 필터링을 On 하고 단지 이 사이트만 접근불가 "을 선택하시고, "쇼핑"을 웹사이트 필터링 규칙 리스트에 입력하세요. URL 키워드를 포함하게 되어서 사용자들이 이런 웹사이트는 접근을 못 합니다.
			<br>
			<a href="http://www.yahoo.com/shopping/stores.html">http://www.yahoo.com/shopping/stores.html</a><br>
			<a href="http://www.msn.com/search/shopping-spree.html">http://www.msn.com/search/shopping-spree.html</a>
		</p>
		<p>
			<span class="style1">예제 2:</span><br>
			만일 애들이 특정 사이트에만 접속하도록 하려면 "웹사이트 필터링을 On 하고 단지 이 사이트만  접근허용 "을 선택하시고 도메인을 입력하세요.
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
<a name="firewall_dmz"><h2>방화벽 설정</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			방화벽 설정에는 DMZ 호스트 설정 부분도 옵션으로 포함되어 있습니다.
		</p>
		<p>
			<strong>SPI 동작</strong><br>
			SPI ("stateful packet inspection" also known as "dynamic packet filtering") 는 사이버 해커를 막는데 도움을 줍니다.  흐르는 트래픽을 프로토콜에 맞는 세션인지를 확인합니다.  프로토콜이 TCP 이고, SPI가 패킷의 세션정보안에 시퀀스 넘버를 체크하고, 불적절한 시퀀스 넘버일 경우 패킷을 버립니다.  SPI가 동작 또는 동작하지 않더라도, 공유기는 TCP 연결상태를 체크하고, TCP 패킷의 flags가 적합한지를 확인합니다.
		</p>
		<p>
			<strong>DMZ </strong><br>
			<?query("/sys/modelname");?> 내부에서 컴퓨터가 인터넷 어플리케이션이 제대로 동작하지 않는다면 컴퓨터에 제한없는 인터넷 엑세스를 허용할 수 있습니다. 인터넷 엑세스가 제한없는 DMZ (Demilitarized Zone) 호스트처럼 컴퓨터에 IP를 입력합니다. 보안위험 노출되어 있는 DMZ에 클라이언트를 추가합니다.  마지막 해결책으로 이 옵션을 사용합니다.
		</p>
		<p>
			<strong>방화벽 규칙</strong><br>
			방화벽 규칙은 출발지와 목적지 IP 어드레스는 물론 이고, 트래픽 타입, 특정 포트를 기준으로 안으로 들어오거나 밖으로 나가는 트래픽을 허용 또는 막을수 있습니다.
			<br>
			<strong><em>이름</em></strong> - 방화벽 규칙의 특정한 이름<br>
			<strong><em>액션</em></strong> - 트래픽을 허용 또는 막음<br>
			<strong>인터페이스</strong><br>
			<strong><em>출발지</em></strong> -
			출발지 드롭메뉴를 선택하여 LAN 또는 WAN 인터페이스에 있는 트래픽을 지정하여 허용하거나 막을수 있습니다.<br>
			<strong><em>목적지</em></strong> -
			목적지 드롭메뉴를 선택하여 LAN 또는 WAN 인터페이스에 있는 트래픽을 지정하여 허용하거나 막을수 있습니다.<br>
			<strong><em>IP 어드레스</em></strong> -
			특정한 출발지 또는 목적지 IP 어드레스를 입력하거나,  IP 어드레스 범위를 처음 시작하는 IP 어드레스와 마지막 IP 어드레스를 입력 하세요.
			<br>
			<strong><em>프로토콜</em></strong> -
			프로토콜 드롭 다운 메뉴에서 트래픽 타입을 선택하세요<br>
			<strong><em>포트 범위</em></strong> -
			특정한 단일 포트를 입력하거나,  포트 범위를 처음 시작하는 포트번호와 마지막 포트 번호를 입력 하세요.<br>
			<strong><em>스케쥴</em></strong> -
			사용자는 미리 정의된 스케쥴을 선택하기 위해 항상 드롭다운 메뉴를 이용하거나 새로운 스케쥴을 추가하기위해 뉴 버튼을 클릭합니다. 
 </p>
</td>
</tr>
</table>
</div>


<div class="box">
<a name="routing"><h2>라우팅</h2></a>
<table>
<?if(query("/runtime/func/dis_routing")!="1"){
echo "<tr>\n";
echo "	<td height=99>\n";
echo "		라우팅 옵션은 특정한 목적지 주소를 정의합니다.<br>\n";
echo "		<strong><em>동작 </em></strong> - 엔트리를 동작 또는 비동작<br>\n";
echo "		<strong><em>인터페이스 </em></strong> - 특정 인터페이스 -- WAN 또는 WAN Physical -- \n";
echo "		이 경로를 사용할때 IP 패킷은 라우터 밖으로 전송된다.<br>\n";
echo "		<strong><em>인터페이스(WAN)</em></strong> - 인터넷 접속을 위해 ISP에서 IP 어드레스를 받는 \n";
echo "		인터페이스<br>\n";
echo "		<strong><em>인터페이스(WAN Physical) </em></strong> - 인터넷 접속을 위해 ISP에서 IP 어드레스를 받는 \n";
echo "		인터페이스<br>\n";
echo "		<strong><em>목적지 </em></strong> - 패킷은 이 경로를 이용합니다.<br>\n";
echo "		<strong><em>서브넷 마스크 </em></strong> - 마스크 안에 하나의 비트는 지정된 IP 어드레스의 비트와 반드시 \n";
echo "		매치가 됩니다.<br>\n";
echo "		<strong><em>게이트웨이 </em></strong> - 이 경로 사용시 다음 홉을 지정합니다. \n";
echo "		게이트 웨이가 0.0.0.0 이면 다음 홉이 없다는 의미이고, 공유기의 인터페이스 \n";
echo "		WAN 또는 WAN Physicl 에 바로 연결 되었고, IP 어드레스가 매치가 됩니다. \n";
echo " </td>\n";
echo " </tr>\n";
}
?>
</table>
</div>


<div class="box">
<a name="advanced_wireless"><h2>고급 무선</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=20>

 <p>이 옵션은 고급 사용자를 위한 페이지 이며, 적절하게 설정하지 못할 경우에는 공유기 성능에 부정적인 영향이 나타납니다.
</p>
 <p><strong><em>전송파워 - </em></strong>드롭다운 메뉴에서 전송파워 값을 선택 할 수 있으며,  <?query("/sys/modelname");?> 외부파워 출력을 줄일수 있습니다. 100%, 50%, 25%, 12.5%를 선택할수 있습니다.</p>
 <p><strong><em>Beacon 간격- </em></strong> Beacon은 AP에 의해 보내지는 패킷이고, AP는 무선네트워크와 동기화를 합니다. 특정 Beacon 간격은 20 ~1000 입니다. 디폴트는 100 milliseconds 입니다. </p>

 <p><strong><em>RTS Threshold - </em></strong> 이 값은 디폴트 2346으로 그대도 둬야 합니다. 만일 데이터 플로우가 일치하지 않는 다면,  256 -2346 범위안에서 수정하는것을 권장합니다. RTS Threshold의 디폴트 값은 2346 입니다. </p>
 <p><strong><em>Fragmentation - </em></strong> 이 값은 디폴트 2346으로 그대도 둬야 합니다. 패킷 에러률이 높다면 1500 - 2346 범위안에서 "Fragmentation" 값을 올려서 수정할수 있습니다. Fragmentation 값이 너무 낮을경우 성능이 나빠질수도 있습니다.</p>
 <p><strong><em>DTIM 간격 - </em></strong> Delivery Traffic Indication Message (DTIM)값을 1 - 255 사이에서 입력하세요. DTIM은 브로드캐스트와 멀티캐스트 메시지를 듣기위해 다음 윈도우 클라이언트에 카운트다운을 알립니다.  AP가 연관된 클라이언트를 위하여 브로트캐스트 또는 멀티캐스트 메시지를 처리할때, DTIM 간격 값 만큼 다음 DTIM에 보냅니다. AP 클라이언트는 beacons을 듣고, 브로드캐스트와 멀티캐스트를 받습니다. 디폴트로 DITM 간격은 1 입니다.
 </p>

 <p><strong><em>Preamble 타입 - </em></strong> Preamble 타입은 CRC (Cyclic Redundancy Check) 길이를 정의하고, AP와 로밍 무선 어댑터간의 통신을 막습니다. 적절한 preamble 타입을 신중히 선택하시고, 적용 버튼을 누르세요 </p>
 <p><span class="style2">노트: </span>높은 네트워크 트래픽 지역은 짧은 preamble 타입을 사용해야 합니다. CRC는 전송에러를 찾아내는데 유용한 기술입니다.</p>
 <p><strong><em>CTS 모드 - </em></strong>아무것도 선택하지 않으면 이 기능을 동작하지 않습니다. 항상을 선택하면 전송데이터가 허용되기 전에 무선 디바이스에 RTS/CTS 핸드세이크을 수행하도록 요구합니다. 자동을 선택하면 RTS/CTS 핸드세이크가 필요한지 결정합니다. </p>
<?if(query("/runtime/func/ieee80211n")!="1"){
 echo "<p><strong><em>802.11g Only Mode - </em></strong>Enable this mode if your network is made up of purely 802.11g devices. If you have both 802.11b and 802.11g wireless clients, disable this mode. </p> </td>";
}?>
 </tr>
 </tr>
 </table>
 </div>
 
 
<div class="box">
<a name="advanced_network"><h2>고급 네트워크 </h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=20>

 <p>이 영역은 공유기가 일정한 타입의 트래픽을 관리하는 방법을 바꾸는 설정을 할 수 있습니다.  설정을 바꾸거나 내용에 익숙하지 않다면 설정을 바꾸지 않은것을 권장합니다.
 </p>

<!--
 <p><strong>VPN Passthrough </strong><br>The device supports VPN (Virtual Private Network) passthrough for PPTP (Point-to-Point Tunneling Protocol) and IPSec (IP Security). Once VPN passthrough is enabled, there is no need to create any Virtual Server or Port Forwarding entries in order for outbound VPN sessions to be established properly. Multiple VPN connections can be made through the device. This is useful when you have many VPN clients on the Local Area Network. </p>
-->

 <p><strong>UPnP </strong><br>UPnP 는 Universal Plug and Play 이며 네트워크장비, 소프트웨어,주변기기간 상호호환성을 제공합니다. <?query("/sys/modelname");?>는 UPnP 동작가능한 공유기이며, 다른 UPnP 장치/소프트웨어와도 동작합니다. UPnP 기능을 원하지 않는다면 "동작안함"을 선택하면 됩니다.
</p>
 <p><strong>WAN Ping </strong><br>WAN Ping 응답이 가능하면, 장비의  퍼블릭 WAN (Wide Area Network) IP 어드레스를 ping 명령어를 이용하여 인터넷 사용자에게 응답을 하도록 합니다. 퍼블릭 WAN IP로 핑을치는 것은 WAN IP 어드레스가 유효한지 테스트를 하고, 이 방법은 해커에게는 통상적인 방법입니다.
</p>
 <p><strong>WAN Port Speed </strong><br><?query("/sys/modelname");?>의 WAN 인터페이스의 속도를 선택할수 있습니다. 100Mbps, 10Mbps, 또는 10/100/1000Mbps 자동을 선택할 수 있습니다.
</p>

<!--
 <p><strong>Gaming Mode </strong><br>If you are experiencing difficulties when playing online games or even certain applications that use voice data, you may need to enable Gaming Mode in order for these applications to work correctly. When not playing games or using these voice applications, it is recommended that Gaming Mode is disabled. </p>
--> 

<?if(query("/runtime/func/dis_multicast_stream")!="1"){
echo " <p><strong>Multicast Streams</strong><br>이 옵션은 네트워크의 효율을 위해 멀티캐스트 트래픽을 허용하도록 합니다.
</p> </td>\n";
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
<a name="guest_zone"><h2>게스트 존</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			게스트 존 선택<br>
			이 영역은 게스트존 영역을 정의 합니다.<br>
			<strong><em>게스트 존 동작</em></strong>  - 게스트존을 동작시키거나 동작시키지 않도록 지정<br>
			<strong><em>LAN 포트 포함</em></strong>  - 게스트존을 포함할 LAN 포트 지정<br>
			<strong><em>무선 포함</em></strong>  - 게스트존으로 사용하기 위한 무선 존 추가  지정<br>
			<strong><em>무선 네트워크 이름</em></strong> -  게스트존 무선 네트워크 이름 제공<br>
		</p>
		<p>
			<strong><em>무선 보안 모드</em></strong><br>
			무선 네트워크에 전송되는 정보의 무결성을 위해 무선보안은중요합니다. <?query("/sys/modelname");?>는 WEP, WPA only, WPA2 only, WPA/WPA2 (auto-detect)의 4가지 형태의 보안이 가능합니다.
			<br>
		</p>
		<p>
			<strong><em>WEP</em></strong><br>
			Wired Equivalent Protocol (WEP) 는 무선 로컬 에어리´ 네트워크(WLAN)에 사용되는 보안 프로토콜 입니다. WEP는 정보를 WLAN을 통해 인크립션을 해서 보냅니다. <?query("/sys/modelname");?>는 64-bit, 128-bit 두 가지 종류의 WEP 인크립션을 지원합니다.  디폴트는 비동작입니다. WEP는 무선 네트워크 커스터 마이징 하기 위해 변경 할수 있습니다.
			<br>
		</p>
		<p>
			<strong><em>인증</em></strong> - <?query("/sys/modelname");?>가 무선 네트워크 접속하려는 장비를 식별하는 과정입니다. WEP를 사용할때 두가지 타입이 인증이 있습니다.
			<br>
			<strong><em>오픈 시스템</em></strong> -이 옵션을 선택하면 접속을 하기위해 필요한 인크립션 키를 제공하기 전에 <?query("/sys/modelname");?>와 통신하려는 모든 장치를 허용합니다.<br>
			<strong><em>공유키 </em></strong> - 이 옵션을 선택하면 <?query("/sys/modelname");?>과의 통신을 허용하기 전에, <?query("/sys/modelname");?>과의 통신을 하려면 무선장치에 인크립션 키를 제공, 필요로 합니다. <br>
			<strong><em>WEP 인크립션</em></strong> - WEP 인크립션 레벨은 선택합니다. 64-bit, 128-bit WEP 인크립션 레벨을 지원합니다.<br>
			<strong><em>키 타입 </em></strong> - <?query("/sys/modelname");?>는 HEX (Hexadecimal)와  ASCII (American Standard Code for Information Interchange)를 지원합니다. 키 타입은 무선네트워크에 적절하게 변경 할 수 있습니다.
			<br>
			<strong><em>키값</em></strong> - 키값 1-4는 안전한 네트워크를 관리하기 위해 무선 인크립션 설정을 쉽게 변경 가능하게 합니다. 인크립션 무선 데이터를 위해 특정한 키값을 선택할 수 있습니다.<br>
		</p>
		<p>
			<strong><em>WPA-Personal</em></strong><br>
			Wi-Fi 프로텍트 엑세스는 무선 네트워크 사용자에게 인증과 권한을 부여합니다. WPA는 WEP 보다 더 강한 보안을 지원하고, 키 값을 기반으로 하며 일정한 간격을 두고 자동으로 변경됩니다.
			<br>
		</p>
		<p>
			<strong><em>암호화 타입</em></strong> - WPA를 사용할때 <?query("/sys/modelname");?>은 두가지 암호화 타입이 지원됩니다.  두가지 옵셥은 TKIP (Temporal Key Integrity Protocol) 과 AES (Advanced Encryption Standard) 입니다.<br>
			<strong><em>PSK/EAP</em></strong> -PSK를 선택하면 인증을 위해서 무선 클라이언트에 Pass phrase가 제공되어야 합이다. EAP를 선택하면, 인증을 위한 모든 무선 클라이언트를 위해서 RADIUS 서버가 필요합니다.<br>
			<strong><em>Passphrase </em></strong> - PSK가 선택되고 8-63 alphanumeric characters가 입력했을때 무선 클라이언트가 <?query("/sys/modelname");?>와 통신하기위한 것입니다. 다른 무선 장치를 네트워크에 추가 시키려면 Passphrase를 반드시 입력을 해야 합니다. <br>
			<strong><em>802.1X </em></strong> - RADIUS 서버를 사용할때 WPA 인증이 결합해서 사용됩니다. RADIUS에는 IP 어드레스, 포트, 공유보안이 입력됩니다. 세컨더리 RADIUS 서버도 사용할 수 있습니다. <br>
		</p>
		<p>
			<strong><em>WPA2</em></strong><br>
			Wi-Fi 프로텍트 엑세스2는 무선 네트워크 사용자에게 인증과 권한을 부여합니다. WPA2는 WEP 보다 더 강한 보안을 지원하고, 키 값을 기반으로 하며 일정한 간격을 두고 자동으로 변경됩니다.
			<br>
		</p>
		<p>
			<strong><em>암호화 타입</em></strong> - WPA를 사용할때 <?query("/sys/modelname");?>은 두가지 암호화 타입이 지원됩니다.  두가지 옵셥은 TKIP (Temporal Key Integrity Protocol) 과 AES (Advanced Encryption Standard) 입니다.<br>
			<strong><em>PSK/EAP</em></strong> - PSK를 선택하면 인증을 위해서 무선 클라이언트에 Pass phrase가 제공되어야 합이다. EAP를 선택하면, 인증을 위한 모든 무선 클라이언트를 위해서 RADIUS 서버가 필요합니다.<br>
			<strong><em>Passphrase</em></strong> - PSK가 선택되고 8-63 alphanumeric characters가 입력했을때 무선 클라이언트가 <?query("/sys/modelname");?>와 통신하기위한 것입니다. 다른 무선 장치를 네트워크에 추가 시키려면 Passphrase를 반드시 입력을 해야 합니다. <br>
			<strong><em>802.1X </em></strong> - RADIUS 서버를 사용할때 WPA 인증이 결합해서 사용됩니다. RADIUS에는 IP 어드레스, 포트, 공유보안이 입력됩니다. 세컨더리 RADIUS 서버도 사용할 수 있습니다.<br>
		</p>
		<p>
			<strong><em>WPA2-Auto</em></strong> <br>
			이 옵션은 <?query("/sys/modelname");?>가 두개의 WPA2와 WPA 클라이언트가 동시에 연결을 허용합니다.
			<br>
		</p>
		<p>
			<strong><em>게스트 존을 위한 LAN 설정</em></strong><br> 
			게스트 존 LAN (Local Area Network) 인터페이스를 설정을 합니다. 프라이비트 설정이라고도 합니다. 필요하다면 LAN IP 어드레스를 바꿀수 있습니다. 사설 IP는 인터넷에서 볼수는 없습니다.디폴트 IP 어드레스는 192.168.1.1이고 서브넷 마스크는 255.255.255.0 입니다.
			<br>
		</p>
		<p>
			<strong><em>IP 어드레스</em></strong> - <?query("/sys/modelname");?>의 디폴트 IP 어드레스느 192.168.1.1 이다 <br>
			<strong><em>서브넷 마스크</em></strong> - <?query("/sys/modelname");?>의 디폴트 서브넷 마스크는 255.255.255.0 이다 <br>
		</p>
		<p>
			<strong><em>게스트 존 클라이언트 Isolation 동작</em></strong> : <br>
			게스트 클라이언트가 게스트 존에 있는 다른 클라이언트에 접속을 막는 기능을 동작시킵니다. 게스트 클라이언트는 인터넷만 접속 가능합니다.
			<br>
		</p>
		<p>
			<strong><em>존에 라우팅 동작</em></strong> : <br>
			호스트 존과 게스트 존에 라우팅을 동작 시킵니다. 게스트 클라이언트는 이 기능없이는 호스트 클라이언트 데이터에 접근할 수 없습니다.
			<br>
		</p>
		<p>
			<strong><em>게스트 존을 위한 DHCP 서버</em></strong> <br>
			DHCP 는 Dynamic Host Control Protocol 입니다. DHCP 서버는 요청에 의해 IP 어드레스를 할당합니다.  장치들은 자동으로 설정합니다. <?query("/sys/modelname");?> 디폴트로 DHCP 서버는 동작입니다. DHCP 어드레스 풀은 자동으로 클라이언트에게 IP 어드레스를 할당 합니다.
			<br>
		</p>
		<p>
			<strong><em>시작 IP 어드레스</em></strong> - DHCP 서버에 할당된 시작하는IP 어드레스 <br>
			<strong><em>끝 IP 어드레스</em></strong> -DHCP 서버에 할당된 마지막 IP 어드레스 <br>
			<strong><em>리즈 시간</em></strong> -IP 리즈가 되는 시간. 다이나믹 DHCP 클라이언트 테이블에 다이나믹 DHCP 클라이언트 컴퓨터 정보가 표시 됩니다. 테이블에는 호스트 네임, IP 어드레스, 맥 어드레스, DHCP 리즈 타임을 보여 줍니다.<br>
		</p>
</td>
</tr>
</table>
</div>
 
<div class="box">
<a name="wake_on_lan"><h2>원격부팅</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			원격부팅 기능은 원격에서 라우터 내부에 연결되어 있는 PC를 부팅시킬때 사용합니다.  UDP 포트를 사용하고,  원격부팅 매직 패킷은 침입자 시도를 블러킹합니다.
			<br>
			<br>
			<strong><em>UDP 포트</em></strong> - 
			<?query("/sys/modelname");?>의 매직패킷을 사용하고, PC를 부팅시킵니다.<br>
			<strong><em>인터페이스</em></strong> - 
			( 이 설정은 현재 변경할 수 없습니다. 나중에 릴리이스되는 펌웨어에 의해 변경할수 있습니다.)<br>		
		</p>
	</td>
</tr>
</table>
</div>
