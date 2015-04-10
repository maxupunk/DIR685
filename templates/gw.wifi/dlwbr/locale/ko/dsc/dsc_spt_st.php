<h1>지원 매뉴</h1>

	<table border=0 cellspacing=0 cellpadding=0 width=750 height=478>
 <tr>
 <td height=2><font size=4><b>상태</b></font></td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>

 </tr>
 <tr>
 <td height=39> <a name=20><strong>장치 정보 </strong><br>
이 페이지는 <?query("/sys/modelname");?>위하여 현재의 정보를 보여줍니다. 이 페이지는 장치의 현재 사용하는 펌웨어의 정보를 보여 줍니다. <br>

&nbsp;<br>
<strong><em>LAN (로컬 에어리어 네트워크) - </em></strong> 이더넷 LAN 인터페이스의 MAN 주소를 보여주고, LAN 인터페이스의 IP 주소와 서브넷 마스크, 라우터의 빌트인 DHCP 서버가 사용 또는 사용안함을 보여 줍니다. <br>
<strong><em>인터넷 - </em></strong> WAN 인터페이스의 MAC 주소, IP 주소, 서브넷 마스크, 디폴트게이트 웨이, DNS 서버 정보를 보여 줍니다<?query("/sys/modelname");?> ISP에서 제공한. ISP 접속에 사용한 연결타입(동적,정적,또는 PPPoE)을 보여 줍니다. 라우터에서 동적을 설정하려면 WAN 인터페이스에 새로운 IP 주소를 할당받기 위한 버튼이 있습니다. 라우터에서 PPPoE를 설정하려면 PPPoE 세션을 연결과 연결안함 버튼이 있습니다.<br> 
<strong><em>
무선 802.11g
<? if(query("/runtime/func/ieee80211n") != "1") { echo "g"; } else { echo "n"; }?>
 - 
</em></strong>무선 인터페이스에 SSID, 채널, 인크립션 사용 인지를 보여 줍니다. </td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>

 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=26><a name=21><b>로그</b></a><br>
 <?query("/sys/modelname");?> 모든 시간에 생기는 활동과 이벤트 로그를 관리합니다. 로그는 400까지 보여줍니다.  새로운 로그는 기존 로그를 덮어씁니다. <br>

 <strong><em>첫 페이지 - </em></strong> 첫페이지 로그를 가려면 이 버튼을 누르세요. <br>
 <strong><em>마지막 페이지 - </em></strong> 마지막 페이지 로그를 가려면 이 버튼을 누르세요. <br>
 <strong><em>이전 - </em></strong>이전 로그페이지로 이동. <br>
 <strong><em>다음 - </em></strong> 다음 로그 페이지로 이동. <br>

 <strong><em>지움 - </em></strong> 전체 로그를 지웁니다. </td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>

 </tr>
 <tr>
 <td height=2><a name=22><strong>통계</strong></a><br>
 <?query("/sys/modelname");?> 처리하는 데이터 트래픽을 관리합니다. 라우터의 인터넷(WAN), LAN, 무선 인터페이스를 통해 전송, 전달되는 패킷량을 볼수 있습니다.
<br>
<strong><em>갱신 - </em></strong>이 버튼은 클릭하면 카운트가 업데이트 됩니다. <br>
<strong><em>리셋 - </em></strong>이 버튼을 클릭하면 카운트를 지웁니다. 장치가 리부트하면 트래픽 카운트가 리셋됩니다. </td>

 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=2><a name=23><b>액티브 세션</b></a><br>
 액티브 세션은 <?query("/sys/modelname");?>을 통하는 출발지와 목적지 패킷을 보여줍니다. <br>
 <strong><em>IP 주소 - </em></strong> 출발지 IP 주소는 패킷이 어디서 출발했는지를 보여줍니다. <br>
 <strong><em>TCP 세션 - </em></strong> 출발지 IP 주소로 부터 보내진 TCP 패킷의 수를 보여줍니다. <br>
 <strong><em>UDP 세션 - </em></strong>  출발지 IP 주소로 부터 보내진 UDP 패킷의 수를 보여줍니다. <br>
</td>

 </tr>
 </tr>
 <tr>
 <td height=20>&nbsp;</td>
 </tr>
 <tr>
 <td height=2><a name=24><b>무선</b></a><br>
 이 페이지는 <?query("/sys/modelname");?>에 몇 명의 클라이언트가 접속해 있는지 보여 줍니다. 이 페이지는 클라이언트가 접속한 모드(802.11b or 802.11g or 802.11n), 얼마동안 접속되어 있는지, 접속한 클라이언트이 각각의 MAC 어드레스를 보여줍니다.
</td>

 </tr>
 </table>
