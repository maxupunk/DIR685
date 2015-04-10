<h1>지원매뉴</h1>
	<table border=0 cellspacing=0 cellpadding=0 width=750 height=1103>
 <tr>
 <td width="750" height=40><font size=4><b>고급</b></font></td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>

 </tr>
<tr>
	<td height=228>
		<p>
			<a name=05><strong>포트 포워딩 </strong></a><br>
			포트 포워딩 옵션은 인터넷을 통해서 유저가 LAN에 접근 가능합니다. FTP,
			Web 또는 게임 서버 등 온라인 서비스에 유용합니다. 
			내부 LAN IP 어드레스와 LAN포트를 public 포트로 리다이렉션 해 줍니다.
		</p>
		<p>
			포트 포워딩 변수<br>
			<strong><em>이름</em></strong> -
			웹서버 처럼 가상서버에 의미있는 이름을 부여 합니다. 여러 개의 잘 알려진 타입의 가상 서버는 사용가능 한 &quot;어플리케이션 이름&quot; 이 드롭다운 메뉴 리스트 있습니다. 이런 리스트 중에 일부 변수에 표준 값으로 채우시고 하나를 선택하세요.<br>
			<strong><em>IP 주소 </em></strong> -
			내부 네트워크의 시스템 IP 주소는 가상 서비스를 제공합니다. 예를 들어, 192.168.0.50 입니다. 
			DHCP 클라이언트 리스트에서 컴퓨터를 선택하고&quot;컴퓨터 이름&quot; 
			드롭다운 매뉴에서 또는 수동으로 서버 컴퓨터 IP 주소를 입력할 수 있습니다.<br>
			<strong><em>어플케이션 이름 </em></strong> -
			사용자가 빠른 설정을 위해 많이 사용하는 어플리케이션을 미리 정의 한 리스트입니다.<br>
			<strong><em>컴퓨터 이름 </em></strong> - DHCP 클라이언트 리스트.<br>
			<strong><em>트래픽 타입</em></strong> -
			서비스에 사용하는 프로토콜을 선택하세요. 드롭다운 매뉴에서 많이 사용하는 UDP, TCP, 
			둘다 UDP와 TCP를 선택할수 있습니다. 특정한 다른 프로토콜은 리스트에서 &quot;Other&quot;
			선택합니다. 그리고 나서 프로토콜 박스에서 상응하는 프로토콜 넘버(IANA에서 지정한)를 입력합니다..<br>
			<strong><em>프라이비트 포트</em></strong> -
			내부 네트워크에서 사용될 포트 입니다.<br>
			<strong><em>공인 포트</em></strong> -
			인터넷에서 사용될 포트 입니다.<br>
		</p>
	</td>
</tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>

 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=64> <strong>어플리케이션 규칙<font size=4><b><a name=06></a></b></font> </strong><br>
일부 어플리케이션  인터넷 게임, 비디오 컨퍼런스, 인터넷 텔레포니, 기타는여러 개의 커넥션을 필요로 합니다. 이런 어플리케이션은 NAT(네트워크 주소 전환)을 통해서 동작하는데 문제가 생깁니다. 사용하는 어플리케이션이 여러 개의 커넥션을 필요로 할때 어플리케이션이 사용하는 일반적인 포트를 &quot;Trigger Port&quot; 필드에서 지정합니다. TCP(전송 컨트롤 프로토콜) 또는 UDP(유저 데이터그램 프로토콜)을 선택하면, 인바운드 트래픽을 위해서 방화벽의 트리거 포트와 연관된 공인 포트를 입력을 합니다. 어플리케이션 이름 드롭 다운 매뉴에서 미리 정의된 많이 사용하는 어프리케이션 이름이 있습니다. <br>

<strong><em>이름 </em></strong> - 어플리케이션을 의미하는 이름입니다. <br>
<strong><em>트리거 포트 </em></strong>- 어플리케이션을 트리거하는데 사용하는 포트입니다. 싱글포트 또는 여러 개의 포트 범위 일 수도 있습니다. <br>
<strong><em>트래픽 타입 </em></strong> - 어플리케이션을 트리거 하는 프로토콜입니다. <br>
<strong><em>방화벽 포트 </em></strong> - 어플리케이션 접근에 사용하는 WAN 사이드 포트 넘버입니다. 싱글 포트 또는 포트 범위를 정의 합니다. 여려개의 포트나 포트 범위를 추가할때 콤마를 사용할 수 있습니다. <br>
<strong><em>트래픽 타입 </em></strong> - 어플리케이션에 사용하는 프로토콜입니다. </td>

 </tr>
 <?if(query("/runtime/func/qos_engine")!="1"){echo "<!--\n";}?>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=64> <strong>Qos 엔진<font size=4><b><a name=01></a></b></font> </strong><br>
 Qos 엔진 기능은 어플리케이션에 우선순위를 두어 네트워크 성능을 향상시키는데 도움을 줍니다.<br>

<strong>Qos 엔진 설정</strong><br>
<strong><em>Qos 엔진 사용</em></strong> - 이 옵션을 사용하면 온라인 게임이나 VoIP 같은 상호교환적인 어플리케이션의 성능을 향상시킵니다. <br>
<strong><em>트래픽 세이핑 사용</em></strong> - 이 옵션을 사용하면, 라우터는 아웃바운드 트래픽 플로우를 제한하고, WAN 업링크 대역폭을 초과하지 않게 합니다.<br>
<strong><em>자동 업링크 속도</em></strong> - 이 옵션이 사용되면, 리부팅 후에 매번 자동으로 업링크 대역폭을 측정하여, WAN 인터페이스를 재 연결합니다. <br>
<strong><em>업링크 속도 측정</em></strong> - 이 측정된 업링크 속도는 지난번에 WAN 인터페이스가 연결될때 값입니다. 이 값은 ISP에서 제시한 값보다 낮을 수 있고, ISP에서 제시한 값은  네트워크 프로토콜의 오버헤드를 포함하지 않습니다. 일반적으로 이 수치는 xDSL의 업링크 속도의 87%에서 91% 사이이고, 케이블 네트워크 연결보다 5kbps 낮습니다. <br>
<strong><em>수동 업링트 속도 </em></strong> - 만일 자동 업링크 속도를 사용하지 않으면, 이 옵션은 수동으로 업링크 속도를 설정하게 합니다. 업링크 속도는 라우터에서 ISP로 데이터가 전송되는 속도입니다. 이 속도은 ISP에서 결정합니다. ISP에서는 1.5Mbps/284kbps 처럼 다운링크/업링크 속도를 지정합니다. 예를 들어 "284"라고 입력합니다. www.dslreports.com 에서 업링크 속도를 측정할수 있는 서비스를 사용할 수 있습니다. DSL 리포트 같은 사이트에서언급하지만, 네트워크 프로토콜 오버헤드를 고려하지 않기 때문에, 일반적으로 ISP에서 제시한 또는 측정된 업링크 속도보다 낮게 언급합니다.<br> 
<strong><em>연결 타입</em></strong> - 디폴트로 라우터는 xDSL/Frame-relay 네트워크 또는 일부 연결 타입(케이블 모뎀 또는 이더넷)을 자동으로 결정하고, 검색된 xDSL 또는 Frame Relay 네트워크 결과를 보여 줍니다. WAN 설정이 "Static" 또는 "DHCP" 으로 되고, 실제로 xDSL을 통해 연결되어 있는 일반적이지 않은 네트워크 연결이면, 이 옵션을 xDSL 또는 다른 Frame Relay 네트워크를 설정하여 라우터가 인지하게끔 하고,최고의 성능을 주기 위해 약간 다른 쉐이프 트래픽을 필요로 합니다. xDSL 또는 다른 Frame Realy 네트워크는 연결전에 측정된 업링크 속도보다는 조금 낮지만, 좀더 낮은 결과를 제공해 줍니다.<br>
<strong><em>검색된 xDSL 또는 Frame Relay 네트워크</em></strong> - 커넥션타입이 자동감지로 설정되면, 자동으로 검색된 커넥션 타입을 여기에 보여 줍니다.<br>
 </td>
 </tr>
 <?if(query("/runtime/func/qos_engine")!="1"){echo "-->\n";}?>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
<tr>
	<td height=99>
		<p>
			<a name=07><strong>MAC 필터</strong></a><br>
			필터는 인터넷 또는 네트워크에 접근하는 LAN 컴퓨터를 허용 또는 막는데 사용됩니다. 
			유닛은 MAC 어드레스를 이용하여 인터넷 접근을 허용 또는 막는데 사용됩니다.
		</p>
		<p>
			<strong>MAC 필터</strong><br>
			MAC 필터는 로컬 에어리어 네트워크 컴퓨터가 인터넷 접근을 막는데 사용합니다. 수동으로 MAC 주소를 추가하거나, 유닛에 현재 접속해 있는 클라이언트 리스트에서 MAC 주소를 선택할 수 있습니다.<br>
   Select &quot; MAC 필터링을 On 하고 리스트에 있는 MAC 주소 컴퓨터는 허용합니다&quot; 만일 선택한 컴퓨터만 네트워크 액세스를 허용하고, 나머지 모든 컴퓨터는 네트워크 액세스를 허용하지 않습니다.<br>
   Select &quot; MAC 필터링은 On 하고 리스트에 보이는 MAC 주소를 네트워크 접근을 막습니다&quot;만일 리스트에 있는 컴퓨터를 제외하고 모든 컴퓨터가 네트워크 접근을 원합니다.<br>
			<strong><em>MAC 주소</em></strong> -
			네트워크 디바이스 MAC 주소가 MAC 필터 리스트에 추가 됩니다.<br>
			<strong><em>DHCP 클라이언트 리스트</em></strong> -
			DHCP 클라이언트는 드롭다운 컴퓨터 이름 매뉴에서 각자의 호스트이름을 갖습니다. 
			MAC 필터 리스트에 추가를 원하는 클라이언트 컴퓨터를 선택하시고 화살표 버튼을 누르세요. 
			버튼을 누르면 자동으로 컴퓨터의 MAC 주소가 추가 됩니다.
		</p>
		<p>
			사용자는 <strong>항상</strong>을 사용하여 드롭다운 메뉴에서 이전에 정의했던 스케쥴을 선택하거나 
			또는 클릭<strong>새로운 스케쥴</strong>버튼하여 새로운 스케쥴을 추가합니다.
		</p>
		<p>
			체크 박스는 특정 엔트리를 사용 또는 사용안함에 사용됩니다.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<a name=08><strong>방화벽 & DMZ</strong></a><br>
			방화벽 설정 영역은 DMZ 호스트를 설정하는 옵션을 포함하고 있습니다.
		</p>
		<p>
			<strong>SPI 사용</strong><br>
			SPI(&quot;스테이트풀 패킷 인스펙션&quot;알려진&quot;다이나믹 패킷 필터링&quot;)는 세센상태를 추적하는 사이버공격을 방지하는데 도움을 줍니다.
			프로토콜 규정에 일치하는 세션을 통해 흐르는 트래픽을 검증합니다. 프로토콜이 TCP이고, 
			SPI는 세션정보를 체크하고 부적절한 시퀀스 넘버를 가진 패킷은 폐기합니다. 
			SPI가 사용 또는 사용하지 않거나, 라우터는 항상 TCP 연결상태를 추적하고, 각각의 TCP 패킷을 플레그가 유효한지를 확인합니다.
		</p>
		<p>	
			<strong>DMZ </strong><br>
			만일 컴퓨터가 인터넷 어플리케이션이 <?query("/sys/modelname");?> 
			뒤에서원활하게 동작하지 않는다면, 모든 컴퓨터의 인터넷 접속을 허용합니다.인터넷 접속을 허용하는 DMZ(비무장지대) 
			호스트의 IP 주소를 입력하세요. DMZ에 클라이언트를 추가하는 것은 보안적 
			취약점에 많이 노출이 됩니다. 이 옵션을 마마지막 수단으로 사용합니다.
		</p>
		<p>
			<strong>방화벽 규칙</strong><br>
			방화벽 규칙은 라우터로 들어오고 나가는 트래픽이 허용 또는 막는데 사용하고, 출발지와 목적지 IP, 트래픽 타입, 특정포트를 체크합니다.<br>
			<strong><em>이름</em></strong> - 사용자는 방화벽 규칙에 이름을 지정할수 있다.<br>
			<strong><em>액션</em></strong> - 사용자는 트래픽을 허용 또는 막음을 선택할수 있다.<br>
			<strong>인터페이스</strong><br>
			<strong><em>출발지</em></strong> -
			<strong>출발지</strong>를 드롭다운 메뉴을 사용해서 LAN 또는 WAN 인터페이스에 트래픽이 출발하는 포인트를 선택합니다.<br>
			<strong><em>목적지</em></strong> -
			<strong>목적지</strong>를 드롭다운 메뉴을 사용해서 LAN 또는 WAN 인터페이스에 트래픽이 끝나는 포인트를 선택합니다.<br>
			<strong><em>IP 주소</em></strong> -
			톱 박스에서 입력되는 IP주소의 하나의 출발지 또는 목적지 IP를 지정하거나 또는 톱박스에서 입력되는 첫번째 IP 와 마지막 IP의 범위를 입력합니다. <br>
			<strong><em>프로토콜</em></strong> -
			<strong>프로토콜</strong>을 드롭다운 메뉴를 사용하여 트래픽 타입을 선택합니다.<br>
			<strong><em>포트 범위</em></strong> -
			싱글포트를 지정하여 두개의 박스에 같은 포트 넘버를 입력하거나 또는 포트범위를 지정하여 톱 박스에 시작 포트번호릉 입력하고, 밑에는 마지막 포트번호를 입력하세요. <br>
			<strong><em>스케쥴</em></strong> -
			사용자는 <strong>항상</strong>을 사용하여 드롭다운 메뉴에서 이전에 정의했던 스케쥴을 선택하거나 또는 클릭<strong>새로운 스케쥴</strong>버튼하여 새로운 스케쥴을 추가합니다.
 </p>
	</div></td>
</tr>

<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
 <tr>
 <td height=20><p><strong>무선 고급 <a name=10></a></strong></p>

 <p>이 페이지의 옵션은 고급사용자에 의해 변경되거나 또는 지원인력으로 부터 지시를 받는게 나으며, 만일 설정이 부정절하다면 성능에 떨어질수 있습니다. </p>
 <p><strong><em>전송 파워 - </em></strong>드롭다운 메뉴에서 낮은 퍼센트의 전송파워 값은 선택하여<?query("/sys/modelname");?> 출력파워를 낮출수 있습니다. 선택은 : 100%, 50%, 25%, and 12.5% 입니다. </p>
 <p><strong><em>비콘 간격 - </em></strong> 비콘은 무선 네트워크와 액세스포인트간에 동기화를 위해 보내지는 패킷입니다. 비콘 간격을 20 ~ 1000 사이에서 지정합니다. 디폴트 값은 100 milliseconds 입니다. </p>

 <p><strong><em>RTS 쓰래드홀드 - </em></strong> 이 값은 디폴트 설정인 2346으로 두어야 합니다. 만일 데이터 플로우가 일관성이 없다면 값을 256 ~ 2346 범위안에서 수정하기를 권장합니다. 디폴트 값으로 RTS Threshold은 2346 입니다. </p>
 <p><strong><em>프레그멘테이션 - </em></strong> 이 값은 디폴트 설정인 2346으로 두어야 합니다. 만일 높은 패킷 에러률이 생긴다면 &quot;프레그멘테이션&quot;값을 1500 ~ 2346 사이에서 약간 높일수 잇습니다. 프레그멘테이션은 너무 낮게 설정하면 낮은 성능이 나올수도 있습니다. </p>
 <p><strong><em>DTIM 간격 - </em></strong>  Delivery Traffic Indication Message (DTIM)값을 1 - 255 사이에서 입력하세요. DTIM은 브로드캐스트와 멀티캐스트 메시지를 듣기위해 다음 윈도우 클라이언트에 카운트다운을 알립니다.  AP가 연관된 클라이언트를 위하여 브로트캐스트 또는 멀티캐스트 메시지를 처리할때, DTIM 간격 값 만큼 다음 DTIM에 보냅니다. AP 클라이언트는 beacons을 듣고, 브로드캐스트와 멀티캐스트를 받습니다. 디폴트로 DITM 간격은 1 입니다. </p>

 <p><strong><em>프리엠블 타입 - </em></strong> Preamble 타입은 CRC (Cyclic Redundancy Check) 길이를 정의하고, AP와 로밍 무선 어댑터간의 통신을 막습니다. 적절한 preamble 타입을 신중히 선택하시고, 적용 버튼을 누르세요. </p>
 <p><span class="style2">Note: </span>높은 네트워크 트래픽 지역은 짧은 preamble 타입을 사용해야 합니다. CRC는 전송에러를 찾아내는데 유용한 기술입니다. </p>
 <p><strong><em>CTS 모드 - </em></strong>아무것도 선택하지 않으면 이 기능을 동작하지 않습니다. 항상을 선택하면 전송데이터가 허용되기 전에 무선 디바이스에 RTS/CTS 핸드세이크을 수행하도록 요구합니다. 자동을 선택하면 RTS/CTS 핸드세이크가 필요한지 결정합니다. </p>
<?if(query("/runtime/func/ieee80211n")!="1"){
 echo "<p><strong><em>802.11g Only Mode - </em></strong>802.11g 디바이스로 네트워크를 구성한다면 이 모드를 사용하세요. 만일 802.11b 또는 802.11g 무선 클라이언트가 있다면 이 모드를 사용하지 않습니다. </p> </td>";
}?>

 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=20><p><strong>고급 네트워크 <a name=11></a></strong></p>

 <p>이 영역은 공유기가 일정한 타입의 트래픽을 관리하는 방법을 바꾸는 설정을 할 수 있습니다.  설정을 바꾸거나 내용에 익숙하지 않다면 설정을 바꾸지 않은것을 권장합니다. </p>

<!--
 <p><strong>VPN Passthrough </strong><br>The device supports VPN (Virtual Private Network) passthrough for PPTP (Point-to-Point Tunneling Protocol) and IPSec (IP Security). Once VPN passthrough is enabled, there is no need to create any Virtual Server or Port Forwarding entries in order for outbound VPN sessions to establish properly. Multiple VPN connections can be made through the device. This is useful when you have many VPN clients on the Local Area Network. </p>
-->

 <p><strong>UPnP </strong><br>UPnP 는 Universal Plug and Play 이며 네트워크장비, 소프트웨어,주변기기간 상호호환성을 제공합니다.  <?query("/sys/modelname");?>는 UPnP 동작가능한 공유기이며, 다른 UPnP 장치/소프트웨어와도 동작합니다. UPnP 기능을 원하지 않는다면 "동작안함"을 선택하면 됩니다. </p>
 <p><strong>WAN 핑 </strong><br>WAN Ping 응답이 가능하면, 장비의  퍼블릭 WAN (Wide Area Network) IP 어드레스를 ping 명령어를 이용하여 인터넷 사용자에게 응답을 하도록 합니다. 퍼블릭 WAN IP로 핑을치는 것은 WAN IP 어드레스가 유효한지 테스트를 하고, 이 방법은 해커에게는 통상적인 방법입니다. </p>
 <p><strong>WAN 포트 속도 </strong><br><?query("/sys/modelname");?>: WAN 인터페이스의 속도를 선택할수 있습니다. 100Mbps, 10Mbps, 또는 10/100Mbps 자동을 선택할 수 있습니다. </p>

<!--
 <p><strong>Gaming Mode </strong><br>If you are experiencing difficulties when playing online games or even certain applications that use voice data, you may need to enable Gaming Mode for these applications to work correctly. When not playing games or using these voice applications, it is recommended that Gaming Mode is disabled. </p>
--> 
<?if(query("/runtime/func/dis_multicast_stream")!="1"){
echo " <p><strong>멀티캐스트 스트림</strong><br>이 옵션은 네트워크의 효율을 위해 멀티캐스트 트래픽을 허용하도록 합니다. </p> </td>\n";
}
?>
 </tr>

<?if(query("/runtime/func/dis_multicast_stream")!="1"){
echo "<tr><td height=20>&nbsp;</td></tr>\n";
echo "<tr>\n";
echo "	<td height=20>\n";
echo "		<p>\n";
echo "			<strong>멀티캐스트 스트림 사용</strong><br>\n";
echo "			인터넷에서 서비스 요구 타입의 비디오를 받을때 이 옵션을 사용합니다.\n";
echo "			라우터는 IGMP 프로토콜을 사용하여 소스로부터 많은수가 받아들이는 멀티캐스트 같은,\n";
echo "			특정 컨텐츠에 대한 멀티캐스트 전송에 효과적입니다.\n"; 
echo "			어떤 어플리케이션이 멀티캐스트 그룹에 참여하려면 이 옵션을 사용해야 합니다.\n"; 
echo "			멀티미디어 LAN 어플리케이션에서 특정 컨텐츠를 받지 못한다면 이 옵션을 사용하세요.\n";
echo "		</p>\n";
echo "	</td>\n";
echo "</tr>\n";
}
?>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
<?if(query("/runtime/func/dis_routing")!="1"){
echo "<tr>\n";
echo "	<td height=99><strong>라우팅 </strong><a name=12></a><br>\n";
echo "		라우팅 옵션은 특정한 목적지 주소를 정의합니다.<br>\n";
echo "		<strong><em>동작 </em></strong> - 엔트리를 동작 또는 동작하지 않도록 지정.<br>\n";
echo "		<strong><em>인터페이스 </em></strong> - 인터페이스를 지정 -- WAN 또는 WAN Physical -- \n";
echo "		이 경로를 사용할때 IP 패킷은 라우터 밖으로 전송된다.<br>\n";
echo "		<strong><em>인터페이스(WAN)</em></strong> - - 인터넷 접속을 위해 ISP에서\n";
echo "		 IP 어드레스를 받는 인터페이스.<br>\n";
echo "		<strong><em>인터페이스(WAN Physical)</em></strong> -  인터넷 접속을 위해 ISP에서\n";
echo "		IP 어드레스를 받는 인터페이스.<br>\n";
echo "		<strong><em>목적지 </em></strong> - 패킷은 이 경로를 이용합니다.<br>\n";
echo "		<strong><em>서브넷 마스크 </em></strong> - 마스크 안에 하나의 비트는 지정된\n";
echo "		 IP 어드레스의 비트와 반드시 매치가 됩니다. <br>\n";
echo "		<strong><em>게이트웨이</em></strong> - 이 경로 사용시 다음 홉을 지정합니다.\n";
echo "		게이트 웨이가 0.0.0.0 이면 다음 홉이 없다는 의미이고, 공유기의 인터페이스 WAN 또는 WAN Physicl 에 바로 연결 되었고,\n";
echo "		 IP 어드레스가 매치가 됩니다. \n";
echo " </td>\n";
echo " </tr>\n";
}
?>

 <tr>
 <td height=20>&nbsp;</td>
 </tr>

 </table>
