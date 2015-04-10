<h1>지원 매뉴</h1>
<table border=0 cellspacing=0 cellpadding=0 width=750>
<tr>
<td height=2><b><font size=4>관리</font></b></td>
</tr>
<tr>
<td height=16><p><br>
</td>
</tr>
<tr>
	<td height=20>
		<strong>장치 관리</strong><a name=12></a><br>
		<p>
			<strong><em>관리자 로그인 이름</em></strong> -
			라우터에 관라지로 접속할때 사용할 이름을 입력하세요.
		</p>
		<p>
			<strong><em>관리자 패스워드</em></strong> -
			패스워드를 입력 확인하세요 <strong>관리자 </strong> 계정은 라우터의 관리 인터페이스를 접근하는데 사용합니다.
		</p>
		<p>
			<strong>원격관리</strong><br>
			원격 관리는 인터넷에 사용하는 WAN(Wide Area Network) 포트를 통해서 웹 브라우즈를 사용하여 장비에 설정을 허용합니다. 사용자 이름과 패스워드는 라우터의 관리 인터페이스 접근을 하기 위해 필요합니다.<br>
			<strong><em>IP 접근 허용</em></strong> -
			이 옵션은 사용자가 원격에서 특정 IP를 갖고 인터넷에서 라우터를 접근을 허용합니다. 이 필드를 디폴트인 공백으로 두면 원격 관리가 사용으로 설정된 상태라면 모든 IP 주소가 접근 할수 있다는 의미이기도 합니다.<br>
			<strong><em>포트</em></strong> - 접근에 사용할 포트를 선택하세요 <?query("/sys/modelname");?>.
		</p>
		<p>
			<strong><em>예제: </em></strong><br>
			http://x.x.x.x:8080 에서 x.x.x.x 는 <?query("/sys/modelname");?> WAN IP 주소이고, 8080 포트는 웹-관리 인터페이스에 사용됩니다.
		</p>
	</td>
</tr>
<tr><td height=10>&nbsp;</td></tr>
<tr><td height=10>&nbsp;</td></tr>
<tr>
	<td height=40>
		<a name=14><strong>저장과 리스토어</strong></a><br>
		현재 시스템 설정은 로컬 하드 드라이브에 파일 형태로 저장 할 수 있습니다. 저장된 파일 또는 다른곳에서 만들어진 설정파일은 유닛에 업로드 할 수 있습니다. 시스템 파일을 업로드를 하려면, <strong>브라우즈</strong>클릭하여 사용할 파일을 검색합니다. 디바이스는 팩토리 디폴트 설정으로 리셋 시킬수 있습니다 클릭<strong>리스토어 디바이스</strong>. 리스토어 기능을 필요할때만 사용합니다. 이 기능은 이전에 저장된 설정을 지웁니다. 팩토리 리스토어를 하기전에 시스템 설정을 반드시 저장하시길 바랍니다.<br>
		<strong><em>저장</em></strong> - 이 버튼을 클릭하여 라우터로부터 설정을 저장합니다.<br>
		<strong><em>브라우즈</em></strong> -
		브라우즈를 클릭하여 저장된 설정파일을 위치를 찾고. 로드를 클릭하여 이 저장된 설정을 라우터로 적용합니다.<br>
		<strong><em>리스토어 디바이스</em></strong> -
		이 버튼을 클릭하여 팩토리 디폴트 설정으로 라우터를 리스토어 합니다.
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=51>
		<b>펌웨어 업데이트</b><a name=15></a><br> 
		이 툴을 이용하여 디바이스 펌웨어를 업그레이드 할 수 있습니다. 사용할 펌웨어는 로컬 하드 드라이브에 저장되어 있어야 합니다.클릭 <strong>브라우즈 </strong>하여 업데이트에 사용할 펌웨어를 로컬 하드 드라이브에 검색합니다. 펌웨어를 업그레이드 해도 시스템 설정을 바뀌지 않으나 업그레이드 하기전에 시스템 설정을 저장하기를 권장합니다. D-Link를 체크하시고<a href=<?query("/sys/supporturl");?>>지원 사이트</a>
펌웨어 업데이트 또는 클릭 <strong>지금 체크</strong> 버튼으로 자동으로 새로운 펌웨어를 체크 합니다.
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height=2>
		<p>
			<strong>DDNS 설정 </strong><a name=16></a><br>
			동적 DNS(도메인 네임 서비스)는 변하는(동적) IP 주소를 지속적으로 도메인 네임과 링크해 주는 방법입니다. 대부분 케이블과 DSL 연결은 동적으로 할당된 IP 주소와 일정시간동안 연결이 됩니다. <?query("/sys/modelname");?>과 함께, DDNS 서비스 설정을 할 수 있고 <?query("/sys/modelname");?>는 자동으로 DDNS 서버를 실시간으로 업데이트 하고 새로운 WAN IP 주소를 받습니다.<br>
			<strong><em>서버 주소</em></strong> - 드롭다운 메뉴에서 DDNS 프로바이더를 선택하세요.<br>
			호스트 이름</em></strong> - DDNS 서비스 프로바이더에 등록된 호스트 이름을 입력하세요.<br>
			<strong><em>사용자이름</em></strong> - DDNS 계정을 위한 사용자 이름 입력하세요.<br>
			<strong><em>패스워드</em></strong> - DDNS 계정을 위한 패스워드를 입력하세요. 
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td height="197">
		<p>
			<strong>시스템 체크</strong><a name=17></a><br>
			이 툴은 LAN과 인터넷(WAN)인터페이스의 물리적인 연결을 검증하는데 사용합니다.고급기능으로 LAN 케이블 테스터를 의해 라우터의 모든 이더넷 포트를 나타냅니다. 그래피컬 사용자 인터페이스(GUI)를 통해, 케이블 테스트는 원격진단 및 케이블 오픈,쇼트, 스왑, 미스매치등과 같은 결합을 리포트 하는데 사용됩니다. 이 기능은 서비스콜을 감소시키고, 케이블 연결에 대한 트러블슈팅을 쉽게 할 수 있게 해 줍니다. 
		</p>
		<p>
			<strong>핑 테스트</strong><br>
			이 유용한 진단 유틸리티는 인터넷에 있는 컴퓨터를 체크하는데 사용됩니다. 핑 패킷을 보내고 특정 호스트가 보내는 응답을 듣습니다. 핑(패킷 인터넷 그롭퍼)을 원하는 호스트 이름이나 IP 주소를 입력하고 클릭<strong>핑</strong>합니다. 핑 시도에 대한 상태는 핑 결과 박스에 보여 줍니다.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td>
		<p>
			<strong>스케쥴<a name=18></a></strong></p>
			이 페이지는 라우터의 글로벌 스케쥴 설정에 사용됩니다. 일단 정의되면, 이런 스케쥴은 나중에 라우터의 기능으로 적용될 수 있습니다. <br>
			<strong><em>이름</em></strong> - 정의된 스케쥴 이름 입니다.<br>
			<strong><em>일(날짜)</em></strong> -
			매일 적용되는 이 스케쥴을 날짜, 날짜 범위, 또는 모든 주간 체크박스를 선택하세요.<br>
			<strong><em>매일 - 24 시간</em></strong> -
			특정일 24시간 동안 스케쥴을 적용할려면 이 박스를 체크 하세요.<br>
			<strong><em>시작 시간</em></strong> -
			정의한 스케쥴을 적용할 시간을 선택하세요.<br>
			<strong><em>끝나는 시간</em></strong> -
			정의한 스케쥴을 끝낼 시간을 선택하세요.<br>
			<strong><em스케쥴 규칙 리스트</em></strong> -
			정의한 모든 스케쥴을 보여 줍니다.
		</p>
	</td>
</tr>
<tr><td height=20>&nbsp;</td></tr>
<tr><td height=20>&nbsp;</td></tr>
<tr>
	<td>
		<p>
			<strong>로그 설정</strong><strong><a name=19></a></strong><br>
			로그 파일을 로컬 드라이브에 저장할 수 있고, 나중에 네트워크 트러블슈팅에 사용할 수 있습니다.<br>
			<strong><em>저장</em></strong> - 이 버튼을 클릭하여 로그 전체를 텍스트 파일로 저장합니다.<br>
			<strong><em>로그 타입</em></strong> - 원하는 정보의 타입을 <?query("/sys/modelname");?> 로그로 보냅니다.<br>
			<strong><em>로그 레벨</em></strong> - 원하는 정보의 레벨를  <?query("/sys/modelname");?>로그로 보냅니다.
		</p>
	</td>
</tr>

</table>
						   
