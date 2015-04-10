<h1>지원매뉴</h1>
<table border=0 cellspacing=0 cellpadding=0 width=750>
<tr>
	<td height=40>
		<p><font size=4><strong>설정</strong></font></p>
		<p>
			<a name=01><strong>인터넷 설정</strong></a><br>
			웹기반 인터넷 연결 설정 마법사를 사용하시거나 직접 연결을 설정할 수 있습니다.
		</p>
	</td>
</tr>
<tr>
	<td height=59>
		<p>
			<strong>인터넷 연결 설정 마법사 </strong><br>
			이 버튼을 클릭하면 몇가지 간단한 단계를 거쳐 인터넷에 연결 됩니다.<br>
			<strong>무선 보안 설정 마법사 </strong><br>
			이 버튼을 클릭하면 무선 네트워크 설정 및 보안 설정하는 방법을 안내할 것입니다. 
		</p>
	</td>
</tr>
<tr><td height=32>&nbsp;</td></tr>
<tr>
	<td height=46>
		<p>
			<strong>수동 인터넷 연결 설정</strong><br>
			직접 인터넷 연결 설정을 하시려면 이 옵션을 선택하세요.<br>
			<strong>엑세스 포인트 모드</strong><br>
			엑세스 포인트 모드를 선택하면 이 장비는 무선 AP 처럼 동작합니다.  무선 연결을 제외한 모든 NAT 기능은 동작하지 않습니다. <br>
			<strong>인터넷 연결 타입 </strong><br>
			<?query("/sys/modelname");?>를 이용하여 인터넷에 연결하려면 인터넷 연결 설정을 합니다. ISP에서 제공한 정보가 필요하고&quot;일반 설정&quot; 을 사용하여 인터넷 연결 을 설정해야 합니다. 어떤 옵션을 설정해야 할지 확실하지 않을 경우에는 인터넷 서비스 업체(ISP) 에 문의하시기 바랍니다.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=61>
		<p>
			<strong>정적 IP 어드레스</strong><br>
			이 옵션을 선택하면 ISP(Internet Service Provider)업체에서 제공한 IP 어드레스, 서브넷 마스크, 디폴트 게이트웨이 그리고 DNS 서버 어드레스 정보를 입력해야 하고,이런 정보가  확실하지 않을 경우에는 인터넷 서비스 업체(ISP) 에 문의하시기 바랍니다.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=142>
		<p>
			<strong>동적 IP 어드레스</strong><br>
			이 옵션을 선택하면 ISP(Internet Service Provider)업체에서 자동으로 IP 어드레스가 부여 됩니다. 케이블 모뎀 공급사에서도 동적 IP 어드레스가 할당됩니다.
		</p>
		<p>
			<strong><em>호스트 네임 </em></strong>(옵션) -
			호스트 네임은 옵션이고 ISP 업체에 의해 필요하기도 합니다. 
			디폴트 호스트 네임은 장비의 모델 넘버입니다.<br>
			<strong><em>MAC 어드레스 </em></strong> (optional) -
			맥(미디어 액세스 컨트럴) 어드레스 필드는 ISP 업체에서 필요로 합니다. 디폴트 맥 어드레스는 <?query("/sys/modelname");?> WAN 인터페이스 맥어드레스로 설정됩니다.
			&quot;PC MAC 주소 복사&quot;버튼을  사용하면 컴퓨터의 이더넷 카드 맥 어드레스가 자동으로 복사가 됩니다. ISP 업체에서 요구 할때만 필드에 주소를 복사합니다 .<br>
			<strong><em>프라이머리 DNS 어드레스 </em></strong> -
			프라이머리 DNS(도메인 네임 서비스)서버 IP 어드레스를 입력합니다.<br>
			<strong><em>세컨더리  DNS 어드레스</em></strong>(옵션) -
			세컨더리 DNS 서버 IP가 있다면 입력하세요.<br>
			<strong><em>MTU </em></strong> -
			 MTU(최대 전송/전달 단위)는 네트워크를 통해 보낼수 있는 최대 크기의 패킷 사이즈입니다. MTU 보다 큰 메시지는 작은 패킷으로 나누어 집니다. 1500 이 디폴트 값입니다. 이 값을 변경하면 라우터의 성능에 영향을 미칠수 있습니다. 기술지원부서나 ISP 업체에 요구에 의해서만 변경할수 있습니다.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=47>
		<p>
			<strong>PPPoE</strong><br>
			이 옵션은 ISP 업체에서 PPPoE(포인트 투 포인트 오버 이더넷) 연결을 요구할때 사용할 수 있습니다. DSL업체에서는 이 옵션을 사용합니다. 다이나믹 PPPoE는 PPPoE 연결을 위한 IP 어드레스를 자동으로 받아옵니다( 다수의 PPPoE 연결 사용). 스태틱 PPPoE는 PPPoE 연결을 위해 정적 IP를 사용합니다.
		</p>
		<p>
			<strong><em>사용자 이름</em></strong> - PPPoE  사용자 이름을 입력하세요.<br>
			<strong><em>패스워드</em></strong> - PPPoE 패스워드를 입력하세요.<br>
			<strong><em>서비스 이름</em></strong>(옵션) - 
			 ISP업체에서 PPPoE 연결을 위해 서비스 이름을 사용하면, 서비스 이름을 여기에 입력하세요.<br>
			<strong><em>IP 어드레스 </em></strong> -
			맥(미디어 액세스 컨트럴) 어드레스 필드는 ISP 업체에서 필요로 합니다. 디폴트 맥 어드레스는  <?query("/sys/modelname");?> WAN 인터페이스 맥어드레스로 설정됩니다.  &quot;PC MAC 주소 복사&quot;버튼을  사용하면 컴퓨터의 이더넷 카드 맥 어드레스가 자동으로 복사가 됩니다. ISP 업체에서 요구 할때만 필드에 주소를 복사합니.<br>
			<strong><em>프라이머리 DNS 어드레스 </em></strong> -
			ISP에서 제공한 프라이머리 DNS(도메인 네임 서비스)서버 IP 어드레스. 스태틱 PPPoE를 선택할때 이 정보가 필요합니다. 만일 다이나믹 PPPoE를 사용한다면 자동으로 ISP 업체에서 이 정보를 제공합니다.<br>
			<strong><em>세컨더리  DNS 어드레스</em></strong> (옵션) -
			세컨더리 DNS 서버 IP가 있다면 입력하세요.<br>
			<strong><em>최대 유휴시간 </em></strong> -
			디바이스가 PPPoE  세션이 끊기기 전에 비활동 시간. 최대 유휴시간을 정의하면 비활동중에서도 인터넷 연결이 유지된다. 비활동시간이 최대유휴시간을 초과하면 연결이 끊김니다. 이 옵션은 연결 요구 모드에서만 적용됩니다.<br>
			<strong><em>MTU </em></strong> -
			MTU(최대 전송/전달 단위)는 네트워크를 통해 보낼수 있는 최대 크기의 패킷 사이즈입니다. MTU 보다 큰 메시지는 작은 패킷으로 나누어 집니다. 1492 이 디폴트 값입니다. 이 값을 변경하면 라우터의 성능에 영향을 미칠수 있습니다. 기술지원부서나 ISP 업체에 요구에 의해서만 변경할수 있습니다.<br>
			<strong><em>연결 모드 선택</em></strong> -
			항상 on을 선택하면 PPPoE 세션이 끊기지 않습니다. 라우터의 인터넷 연결 또는 해제를 원하는 대로 컨트럴을 할려면 수동을 선택합니다. 연결요구 on 옵션은 디바이스가 인터넷 리소스에 접근을 하려 할때 인터넷 연결을 성립시켜 줍니다.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>PPTP</strong><br>
			이 옵션은 ISP 업체에서 PPTP(포인트 투 포인트 터널링 프로토콜) 연결에 사용하고, 인터넷 연결에는 사용자 이름과 패스워드가 필요합니다. 다이나믹 PPTP는 인터넷 연결을 위하여 자동으로 IP 어드레스를 받습니다. 스태틱 PPTP는 PPTP 연결을 위해 정적 IP를 사용합니다.
		</p>
		<p>
			<strong><em>IP 어드레스</em></strong> - ISP에서 할당한 IP 어드레스 입력.<br>
			<strong><em>서브넷 마스크</em></strong> - ISP에서 할당한 서브넷 마스크 입력.<br>
			<strong><em>게이트웨이</em></strong> - ISP에서 할당한 게이트웨이 IP 어드레스 입력.<br>
			<strong><em>DNS</em></strong> - ISP에서 할당한 DNS 어드레스 입력.<br>
			<strong><em>서버 IP </em></strong> -
			연결하려고 하는 ISP에서 제공한 서버 IP를 입력하세요.<br>
			<strong><em>계정</em></strong> - PPTP 사용자 이름 입력.<br>
			<strong><em>패스워드</em></strong> - PPTP 패스워드 입력.<br>
			<strong><em>최대 유휴시간 </em></strong> -
			디바이스가 PPTP  세션이 끊기기 전에 비활동 시간. 최대 유휴시간을 정의하면 비활동중에서도 인터넷 연결이 유지된다. 비활동시간이 최대유휴시간을 초과하면 연결이 끊김니다. 이 옵션은 연결 요구 모드에서만 적용됩니다.<br>
			<strong><em>MTU </em></strong> -
			MTU(최대 전송/전달 단위)는 네트워크를 통해 보낼수 있는 최대 크기의 패킷 사이즈입니다. MTU 보다 큰 메시지는 작은 패킷으로 나누어 집니다. 1400 이 디폴트 값입니다. 이 값을 변경하면 라우터의 성능에 영향을 미칠수 있습니다. 기술지원부서나 ISP 업체에 요구에 의해서만 변경할수 있습니다.<br>
			<strong><em>연결 모드 선택</em></strong> -
			항상 on을 선택하면 PPTP 세션이 끊기지 않습니다. 라우터의 인터넷 연결 또는 해제를 원하는 대로 컨트럴을 할려면 수동을 선택합니다. 연결요구 on 옵션은 디바이스가 인터넷 리소스에 접근을 하려 할때 인터넷 연결을 성립시켜 줍니다.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>L2TP </strong><br>
			이 옵션은 ISP 업체에서 L2TP(Layer 2 터널링 프로토콜) 연결에 사용하고, 인터넷 연결에는 사용자 이름과 패스워드가 필요합니다. 다이나믹 L2TP는 인터넷 연결을 위하여 자동으로 IP 어드레스를 받습니다. 스태틱 L2TP는 L2TP 연결을 위해 정적 IP를 사용합니다.
		</p>
		<p>
			<strong><em>IP 어드레스</em></strong> - ISP에서 할당한 IP 어드레스 입력.<br>
			<strong><em>서브넷 마스크/em></strong> - ISP에서 할당한 서브넷 마스크 입력.<br>
			<strong><em>게이트웨이</em></strong> - ISP에서 할당한 게이트웨이 IP 어드레스 입력.<br>
			<strong><em>DNS</em></strong> - ISP에서 할당한 DNS 어드레스 입력.<br>
			<strong><em>서버 IP </em></strong> -
			 ISP에서 제공하고, 접속하려는 서버 IP 어드레스 입력.<br>
			<strong><em>L2TP계정</em></strong> - L2TP 사용자 이름 입력.<br>
			<strong><em>L2TP패스워드</em></strong> - L2TP 패스워드 입력하세요.<br>
			<strong><em>최대 유휴시간 </em></strong> -
			디바이스가 L2TP  세션이 끊기기 전에 비활동 시간. 최대 유휴시간을 정의하면 비활동중에서도 인터넷 연결이 유지된다. 비활동시간이 최대유휴시간을 초과하면 연결이 끊김니다. 이 옵션은 연결 요구 모드에서만 적용됩니다.<br>
			<strong><em>MTU</em></strong> -
			MTU(최대 전송/전달 단위)는 네트워크를 통해 보낼수 있는 최대 크기의 패킷 사이즈입니다. MTU 보다 큰 메시지는 작은 패킷으로 나누어 집니다. 1400 이 디폴트 값입니다. 이 값을 변경하면 라우터의 성능에 영향을 미칠수 있습니다. 기술지원부서나 ISP 업체에 요구에 의해서만 변경할수 있습니다.
			<strong><em>연결 모드 선택 </em></strong> -
			항상 on을 선택하면 L2TP 세션이 끊기지 않습니다. 라우터의 인터넷 연결 또는 해제를 원하는 대로 컨트럴을 할려면 수동을 선택합니다. 연결요구 on 옵션은 디바이스가 인터넷 리소스에 접근을 하려 할때 인터넷 연결을 성립시켜 줍니다.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>러시안 PPTP(듀얼 엑세스)</strong><br>
			러시안 PPTP 인터넷 연결을 설정하려면, 이전에 했던 PPTP 연결을 설정해야 합니다. 만일 스태틱 루트가 필요하다면 "고급"메뉴에 있는 "라우팅" 기능을 참고하세요
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>러시안 PPPoE(듀얼 엑세스)</strong><br>
PPPoE 연결은 ISP를 향하는 정적 IP 루트를 사용하고, 연결을 위해 추가로 글로벌 IP 설정을 합니다. 물리적인 WAN 포트에 IP 설정을 정의합니다. 러시안 PPPoE 인터넷 연결을 설정하려면, 이전에 했던 PPPoE 연결을 설정해야 하고, 추가로 ISP에서 제공한 물리적인 WAN IP 설정을 해야 합니다. 만일 스태틱 루트가 필요하다면 "고급"메뉴에 있는 "라우팅" 기능을 참고하세요.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<a name=02><strong>무선 설정</strong></a><br>
			무선 설정 페이지는<?query("/sys/modelname");?> 엑세스 포인스 설정을 포함합니다. 이 페이지는 기존에 사용하거나 현재 있는 무선네트워크에 맞게 <?query("/sys/modelname");?> 설정 바꿀수 있다. 
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>Wi-Fi 프로텍트 설정(  윈도우 비스타에서는 WCN 2.0 로 불리기도 함) </strong><br>
			이 기능은 사용자가 직관적으로 무선 보안 설정을 하도록 해 줍니다. PIN 넘버와 버튼입력이라는 두가지 포맷이 있습니다. PIN 넘버 입력은 무선카드 유틸리트와 윈도우 비스타 무선 클라이언트 유틸리티에 해당되고, 무선카드가 윈도우 비스타 드라이에 검증을 받았다면 라우터와 클라이언트간에 자동으로 무선보안이 설정이 됩니다. 무선카드는 이 기능을 지원하기위해 Wi-Fi 프로텍트 설정이 지원해야 합니다.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>무선 네트워크 이름</strong><br>
			SSID(서비스 설정 인식자)로 알려지고, 무선 로컬 에어리어 네트워크(WLAN)의 이름 입니다. <?query("/sys/modelname");?> 디폴트 SSID는 &quot;dlink&quot; 입니다. 쉽게 바꿀수도 있고, 기존 무선 네트워크에 <?query("/sys/modelname");?>를 추가하기도 합니다.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>무선 채널</strong><br>
			<?query("/sys/modelname");?>의 사용채널을 가리킴. 디폴트 채널은 6 입니다. 커스터 마이징하거나 채널설정을 변경할 수도 있습니다. <?query("/sys/modelname");?>의 자동 스캔 체크박스에서 자동으로 선택할수 있습니다.이 옵션은 라우터가 채널을 선택할 수 있고 적어도 최소한의 간섭만 있을때 사용 권장합니다.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>WMM</strong><br>
			<?query("/sys/modelname");?> 무선 인터페이스의 QoS를 동작하도록 선택하세요.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>무선 숨김 동작 </strong><br>
			  <?query("/sys/modelname");?>의 SSID가 브로드캐스트 하고 싶지 않으면 선택하세요. &nbsp;이 옵션을 동작시키면, <?query("/sys/modelname");?>의 SSID는 Site Survey 유틸리티에 보이지 않습니다. 무선 클라이언트가 접속을 할려면 <?query("/sys/modelname");?>의 SSID를 알아야 하고, 수동으로 입력을 해야 합니다. 디폴트로는 동작상태입니다.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>무선 보안 모드</strong><br>
			무선 네트워크에 전송되는 정보의 무결성을 위해 무선보안은중요합니다. <?query("/sys/modelname");?>는 WEP, WPA only, WPA2 only, WPA/WPA2 (auto-detect)의 4가지 형태의 보안이 가능합니다.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>WEP </strong><br>
			Wired Equivalent Protocol (WEP) 는 무선 로컬 에어리어 네트워크(WLAN)에 사용되는 보안 프로토콜 입니다. WEP는 정보를 WLAN을 통해 인크립션을 해서 보냅니다. 64-bit, 128-bit 두 가지 종류의 WEP 인크립션을 지원합니다.  디폴트는 비동작입니다. WEP는 무선 네트워크 커스터 마이징 하기 위해 변경 할수 있습니다.
		</p>
		<p>
			<strong><em>인증</em></strong> -
			<?query("/sys/modelname");?>가 무선 네트워크 접속하려는 장비를 식별하는 과정입니다. WEP를 사용할때 두가지 타입이 인증이 있습니다.<br> 
			<strong><em>오픈 시스템</em></strong> -
			이 옵션을 선택하면 접속을 하기위해 필요한 인크립션 키를 제공하기 전에 <?query("/sys/modelname");?>와 통신하려는 모든 장치를 허용합니다.<br>
			<strong><em>공유키</em></strong> -
			이 옵션을 선택하면 <?query("/sys/modelname");?>과의 통신을 허용하기 전에, <?query("/sys/modelname");?>과의 통신을 하려면 무선장치에 인크립션 키를 제공, 필요로 합니다.<br>
			<strong><em>WEP 인크립션</em></strong> -
			WEP 인크립션 레벨은 선택합니다. 64-bit, 128-bit WEP 인크립션 레벨을 지원합니다.<br>
			<strong><em>키 타입</em></strong> -
			<?query("/sys/modelname");?>는 HEX (Hexadecimal)와  ASCII (American Standard Code for Information Interchange)를 지원합니다. 키 타입은 무선네트워크에 적절하게 변경 할 수 있습니다.<br>
			<strong><em>키값</em></strong> -
			 키값 1-4는 안전한 네트워크를 관리하기 위해 무선 인크립션 설정을 쉽게 변경 가능하게 합니다. 인크립션 무선 데이터를 위해 특정한 키값을 선택할 수 있습니다.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>WPA/WAP2</strong><br>
			WPA/WAP2는 무선 네트워크 사용자에게 인증과 권한을 부여합니다. WPA는 WEP 보다 더 강한 보안을 지원하고, 키 값을 기반으로 하며 일정한 간격을 두고 자동으로 변경됩니다.
		</p>
		<p>
			<strong><em>암호화 타입</em></strong> -
			WPA를 사용할때 <?query("/sys/modelname");?> 은 두가지 암호화 타입이 지원됩니다.  두가지 옵셥은 TKIP (Temporal Key Integrity Protocol) 과 AES (Advanced Encryption Standard) 입니다.<br>
			<strong><em>PSK/EAP</em></strong> -
			PSK를 선택하면 인증을 위해서 무선 클라이언트에 Pass phrase가 제공되어야 합이다. EAP를 선택하면, 인증을 위한 모든 무선 클라이언트를 위해서 RADIUS 서버가 필요합니다.<br>
			<strong><em>Passphrase</em></strong> -
			PSK가 선택되고 8-63 alphanumeric characters가 입력했을때 무선 클라이언트가 <?query("/sys/modelname");?>와 통신하기위한 것입니다. 다른 무선 장치를 네트워크에 추가 시키려면 Passphrase를 반드시 입력을 해야 합니다. <br>
			<strong><em>802.1X</em></strong> -
			RADIUS 서버를 사용할때 WPA/WPA2 인증이 결합해서 사용됩니다. RADIUS에는 IP 어드레스, 포트, 공유보안이 입력됩니다. 세컨더리 RADIUS 서버도 사용할 수 있습니다.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<a name=03><strong>LAN 설정</strong></a><br>
			LAN (Local Area Network) 인터페이스를 설정을 합니다. &quot;프라이비트 설정&quot;이라고도 합니다. 필요하다면 LAN IP 어드레스를 바꿀수 있습니다. 사설 IP는 인터넷에서 볼수는 없습니다.디폴트 IP 어드레스는 192.168.0.1이고 서브넷 마스크는 255.255.255.0 입니다.<br><br>
			<strong><em>IP 어드레스</em></strong> -
			<?query("/sys/modelname");?>의 디폴트 IP 어드레스는 192.168.0.1 입니다.<br>
			<strong><em>서브넷 마스크</em></strong> -
			?query("/sys/modelname");?>의 서브넷 마스크는 255.255.255.0 입니다.<br>
			<strong><em>로컬 도메인 네임</em></strong> (옵션) - 로컬 도메인 네임을 입력하세요.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong><em>DNS Relay</em></strong> -
			DNS Relay가 동작하면, DHCP 클라이언트 공유기는 DNS 서버 처럼  공유기의 LAN IP 어드레스가 할당됩니다. 공유기가 받은 모든 DNS 요청은 ISP의 DNS 서버로 포워딩 됩니다. DNS Relay가 동작하지 않으면 , 모든 DHCP 클라이언트 공유기는  ISP DNS 서버에게 할당됩니다.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=20>
		<p>
			<strong>DHCP Server</strong><br>
			DHCP 는 Dynamic Host Control Protocol 입니다. DHCP 서버는 요청에 의해 IP 어드레스를 할당합니다.  장치들은 &quot;자동으로 IP주소를&quot;설정합니다. <?query("/sys/modelname");?> 디폴트로 DHCP 서버는 동작입니다. DHCP 어드레스 풀은 자동으로 클라이언트에게 IP 어드레스를 할당 합니다.
		</p>
		<p>
			<strong>DHCP Reservation</strong><br>
			수동으로 &quot;컴퓨터 이름&quot;, &quot;&quot; IP 어드레스&quot;, &quot;맥 어드레스&quot;를 입력할 수 있고, 메뉴에서 현재 DHCP 클라이언트를 볼수 있습니다. 
		</p>
		<p>
			<strong><em>시작 IP 어드레스 </em></strong> DHCP 서버에 할당된 시작하는IP 어드레스.<br>
			<strong><em>끝 IP 어드레스</em></strong>  DHCP 서버에 할당된 마지막 IP 어드레스.<br>
			<strong><em>리즈 시간</em></strong> IP 리즈가 되는 시간.
		</p>
		<p>
			다이나믹 DHCP 클라이언트 테이블에 다이나믹 DHCP 클라이언트 컴퓨터 정보가 표시 됩니다. 테이블에는 호스트 네임, IP 어드레스, 맥 어드레스, DHCP 리즈 타임을 보여 줍니다.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=33>
		<p>
			<strong><a name=04>시간과 일자</a></strong>
		</p>
		<p>
			시간 설정은 공유기의 동기화 스케쥴 서비스와 시스템 로깅 액티비트에 사용하기 위해 설정됩니다.  해당 위치에 맞는 타임 존을 설정 해야 합니다. 시간은 수동으로 설정하거나 NTP(Network Time Protocol) 접속해서 시간을 받아 올수 있습니다. 특정날짜의 시스템 시간을 조정하여 Daylight Saving 시간 날짜를 정할 수 있습니다 .
		</p>
		<p>
			<strong><em>시간 존</em></strong> - 해당 지역에 맞게 시간 존을 설정합니다.<br>
			<strong><em>Daylight Saving</em></strong> -
			해당지역에 Daylight Saving 시간을 시행한다면, 이 설정을 동작시키고, 특정 시작월과  마지막 월, 주. 일,시간을 지정합니다.<br>
			<strong><em>자동 시간 설정</em></strong> -
			<?query("/sys/modelname");?>와 시간동기화 할 수 있는 디링크 시간 서버를 선택하세요. <?query("/sys/modelname");?>와 디링크 NTP 서버가 통신하는 간격은 7일로 선택합니다.<br>
			<strong><em>날짜와 시간 수동설정</em></strong> -
			수동으로 설정할 경우 선택하세요.  특정한 년,월,일,시간,분.초 설정하거나 또는  컴퓨터 시간 설정을 복사하여 관리 인터페이스에 접속에 사용하기 위한  컴퓨터의 시스템 시간에 입력합니다.
		</p>
	</td>
</tr>
<tr><td height=2>&nbsp;</td></tr>
<tr><td height=2>&nbsp;</td></tr>
<tr>
	<td height=44>
		<p>
			<strong><a name="05">Parental control</a></strong><br>
			Parental control은 특정한 웹사이트나 키워드 도메인 네임을 접근하려는 컴퓨터를 허용 또는 불가 할 수 있습니다. 특정 URLs과 도메인 네임을 접근 할수 있도록 "웹사이트 필터링을 On 하고 단지 이 사이트만  접근허용 "을 선택하세요. 특정 URLs과 도메인 네임을 접근 하지 못하도록 "웹사이트 필터링을 On 하고 단지 이 사이트만 접근불가 "을 선택하세요. 
		</p>
		<p>
			<span class="style1">예제 1:</span><br>
			만일 쇼핑과 관련된 URL 웹사이트를 막고 싶다면  &quot;웹사이트 필터링을 On 하고 단지 이 사이트만 접근불가 &quot;을 선택하시고, &quot;쇼핑&quot;을 웹사이트 필터링 규칙 리스트에 입력하세요. URL 키워드를 포함하게 되어서 사용자들이 이런 웹사이트는 접근을 못 합니다.<br>
			http://shopping.yahoo.com/<br>
			http://shopping.msn.com/

		</p>
		<p>
			<span class="style1">예제 2:</span><br>
			만일 애들이 특정 사이트에만 접속하도록 하려면 &quot;웹사이트 필터링을 On 하고 단지 이 사이트만  접근허용 &quot;을 선택하시고 도메인을 입력하세요.
		</p>
		<ul>
			<li>Google.com </li>
			<li>Cartoons.com </li>
			<li>Discovery.com </li>
		</ul>
	</td>
</tr>
</table>
