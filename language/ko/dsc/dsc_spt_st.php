<div class="box">
<a name="device_info"><h2>디바이스 정보</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=39> 
이 페이지는 <?query("/sys/modelname");?>의 현재 정보를 보여 줍니다. 현재 디바이스에 펌웨어 버전을 보여 줍니다.
<br>

&nbsp;<br>
<strong><em>LAN (Local Area Network) - </em></strong>이더넷 인터페이스의 맥 어드레스와 IP 어드레스, 랜 인터페이스의 서브넷 마스크를 보여 주고, 공유기에 빌트인 되어 있는 DHCP 서버가 동작하는지 동작하지 않는지도 보여 줍니다.<br>
<strong><em>WAN (Wide Area Network) - </em></strong><?query("/sys/modelname");?>의 WAN 인터페이스의 맥어드레스, IP 어드레스, 서브넷 마스크, 디폴트 게이트웨이, DNS 서버 정보를 보여 줍니다. 그리고 연결성립에 사용된 연결타입(동적, 정적, 또는 PPPoE)도 보여 줍니다. 만일 공유기가 동적IP로 설정되었다면, WAN 인터페이스에 할당될 IP 어드레스를 위해 해제 및 갱신 버튼이 있을 것 입니다. 만일 공유기가 PPPoE로 설정되었으면, PPPoE 세션을 위한 연결 및 비연결 버튼이 있을 것 입니다.<br> 
<strong><em>
무선 802.11
<? if(query("/runtime/func/ieee80211n") != "1") { echo "g"; } else { echo "n"; }?>
 - 
</em></strong>무선 인터페이스에 동작하는 SSID, 채널 그리고 인크립션이 동작하는 지를 보여 줍니다. </td>
</tr>
</table>
</div>


<div class="box">
<a name="log"><h2>로그</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=26>
 <?query("/sys/modelname");?>은 매시간 액티비트와 이벤트 발생할때 마다 로그를 만듭니다. 최근 400개까지의 로그를 보여 줍니다. 새로운 로그는 기존 로그를 덮어습니다.
<br>

 <strong><em>첫 페이지 - </em></strong> 이 버튼을 클릭하면 로그의 첫페이지로 이동합니다. <br>
 <strong><em>마지막 페이지 - </em></strong> 이 버튼을 클릭하면 로그의 마지막 페이지로 이동합니다. <br>
 <strong><em>이전 - </em></strong> 전페이지로 이동 합니다. <br>
 <strong><em>다음 - </em></strong> 다음페이지로 이동합니다. <br>

 <strong><em>삭제 - </em></strong> 로그를 삭제합니다. </td>
 </tr>
 </table>
 </div>
 
 
<div class="box">
<a name="statistics"><h2>상태</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=2>
 <?query("/sys/modelname");?>은 처리하는 데이터 트래픽을 통계합니다. 공유기의 인터넷(WAN), LAN, 무선으로 보내거나 받은 일정양의 패킷을 볼 수도 있습니다.
<br>
<strong><em>갱신 - </em></strong>이 버튼을 클릭하면 카운터를 업데이트 합니다.<br>
<strong><em>리셋 - </em></strong>이 버튼을 클릭하면 카운터를 삭제 합니다. 디바이스가 리부팅을 하면 트래픽 카운터는 리셋됩니다. </td>
</tr>
</table>
</div>


<div class="box">
<a name="internet_session"><h2>인터넷 세션</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=2>
 <?query("/sys/modelname");?>를 통과하는 패킷의 출발지와 목적지 인터넷 세션을 보여줍니다.  <br>
 <strong><em>IP 어드레스 - </em></strong> 패킷이 시작한 출발지 IP 어드레스 입니다. <br>
 <strong><em>TCP 세션 - </em></strong> 출발지 IP에서 보내진 TCP 패킷의 수를 보여 줍니다. <br>
 <strong><em>UDP 세션 - </em></strong> 출발지 IP에서 보내진 UDP 패킷의 수를 보여 줍니다.<br>
 <strong><em>프로토콜 - </em></strong> 출발지와 목적지 IP 사이에 전송된 패킷의 타입을 의미합니다. <br>
 출발지 IP - 패킷이 출발한 IP 어드레스를 보여줍니다.<br>
 출발지 포트 - 목적지 IP로 패킷이 전송되는데 사용한 포트를 보여줍니다. <br>
 목적지 IP - 패킷이 전달된 목적지 IP 어드레스를 보여 줍니다. <br>
 목적지 포트 - 출발지 IP에서 패킷을 받는데 사용한 포트를 보여 줍니다.
</td>
 </tr>
 </tr>
</table>
</div>
 
 
<div class="box">
<a name="wireless"><h2>무선</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=2>
 얼마나 많은 클라이언트가 <?query("/sys/modelname");?>와 연결이 되었는지를 보여 줍니다. 각 연결된 클라이언트의 맥 어드레스를 보여주고, 얼마동안 연결되었는지, 어떤 모드로 연결되었는지(802.11b, 802.11g, 또는 802.11n) 보여 줍니다.
</td>
 </tr>
</table>
</div> 
