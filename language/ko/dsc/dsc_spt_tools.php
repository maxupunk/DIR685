<div class="box">
<a name="admin"><h2>관리자</h2></a>
<table border=0 cellspacing=0 cellpadding=0>

<tr>
	<td height=20>
		
		<p>
			<strong><em>관리자 로그인 이름</em></strong> -
			공유기에  관리자로 접속할 이름을 입력합니다.
		</p>
		<p>
			<strong><em>관리자 패스워드</em></strong> -
			공유기 관리 인터페이스에 접속을 위해 관리자 패스워드를 입력 입력합니다.
		</p>
		<p>
			<strong>원격 관리</strong><br>
			WAN(Wide Area Network) 포트를 통해 웹 브라이저로 접속, 장치를 원격 관리 할수 있습니다. 공유기 관리 인터페이스를 접속하기 위해 사용자 이름과 패스워드가 필요합니다. 
			<br>
			<strong><em>접속허용 IP</em></strong> -
			이 옵션은 인터넷을 통해 원격으로 특정 IP만 공유기를 접속허용하게 합니다. 원격관리가 동작을 하고 이 필드를 디폴트인 빈칸으로 두면 어떤 IP도 원격으로 공유기 접속을 허용합니다. <br>
			<strong><em>포트</em></strong> - <?query("/sys/modelname");?> 접속에 사용할 포트를 선택하세요
		</p>
		<p>
			<strong><em>예제: </em></strong><br>
			<a href="http://192.168.0.1/help_tools.html">http://x.x.x.x:8080 </a> 는 x.x.x.x는 <?query("/sys/modelname");?>의 WAN IP 어드레스이고, 8080은 웹 관리 인터페이스 접속에 사용되는 포트 입니다.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="time"><h2>시간</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=33>
		<p>
			시간 설정은 공유기의 동기화 스케쥴 서비스와 시스템 로깅 액티비트에 사용하기 위해 설정됩니다.  해당 위치에 맞는 타임 존을 설정 해야 합니다. 시간은 수동으로 설정하거나 NTP(Network Time Protocol) 접속해서 시간을 받아 올수 있습니다. 특정날짜의 시스템 시간을 조정하여 Daylight Saving 시간 날짜를 정할 수 있습니다 
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
</table>
</div>


<div class="box">
<a name="log_settings"><h2>로그 설정</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			로컬 드라이브에 로그 파일을 저장할수 있고, 나중에 네트워크 트러블슈팅에 사용합니다.
			<br>
			<strong><em>저장</em></strong> - 저장버튼을 클릭하여 로그 엔트리를 텍스트 파일로 저장합니다.<br>
			<strong><em>로그 타입</em></strong> - <?query("/sys/modelname");?> 로그의 인포메이션 타입을 선택합니다.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="email_settings"><h2>이메일 설정</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			디바이스의 로그 파일을 특정한 이메일 주소로 보내는 설정입니다.<br>
			<br>
			<strong><em>보내는 이메일 주소</em></strong> - 
			보내는 이메일을 주소입니다.  요즘 SMTP 서비스는 유효한 이메일 어드레스 주소를 요구합니다. 그리고 정상적인 주소인지 테스트 합니다.<br>
			<strong><em>받는 이메일 주소</em></strong> - 
			디바이스 로그 파일을 받는 주소입니다. 이메일 계정 사용자는 로그 파일을 볼수 있습니다.<br>
			<strong><em>이메일 제목</em></strong> - 
			이메일 타이틀 입니다.<br>
			<strong><em>SMTP 서버 어드레스</em></strong> - 
			메일서버의 도메인 네임 어드레스이고, 요청된 이메일 계정에 디바이스 로그파일을 전달합니다.<br>
			<strong><em>SMTP 서버 포트</em></strong> - 
			메일서버가 사용하는 포트입니다.<br>
			<strong><em>인증 설정</em></strong> - 
			SMTP 서버는 보안적인 이유로 이메일을 보내기 전에 계정 이름과 패스워드를 체크 확인합니다.<br>
			<strong><em>계정 이름</em></strong> - 
			SMTP 서버 인증에 사용되는 사용자 이름입니다.<br>
			<strong><em>패스워드</em></strong> - 
			 SMTP 서버 인증에 사용되는 사용자 패스워드 입니다.<br>
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="system"><h2>시스템</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=40>
	로컬 하드 드라이브에 현재 시스템 설정이 파일형태로 저장 할 수 있습니다. 저장파일 또는 저장된 설정은 디바이스에 의해 유닛으로 업로드 가능 합니다. 시스템 파일을 리로드 하려면, <strong>Browse</strong>를 클릭하여 로컬 하드 드라이브에 원하는 파일을 검색합니다. 디비이스에 <strong>Restore Device</strong>를 클릭하면 공장에서 출하된 상태인 디폴트 설정으로 복귀합니다.  Restore 기능은 필요할때만 사용합니다. 이 기능은 기존 설정을 삭제 합니다.  팩토리 restore 하기전에 시스템 설정을 저장해야 합니다.
	<br>
		<strong><em>저장</em></strong> - 저장버튼을 클릭하면 공유기의 설정파일이 저장됩니다.<br>
		<strong><em>브라우즈</em></strong> -
		브라우즈를 클릭하여 저장된 설정파일을 위치를 지정하고,  로드 및 적용을 하여 공유기의 설정을 저장합니다.<br>
		<strong><em>Restore 디바이스 </em></strong> -
		공장에서 출하된 상태인 디폴트 설정으로 복귀합니다.
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="firmware"><h2>펌웨어</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=51>
		이 도구를 이용하여 디바이스 펌웨어를 업그레이드 합니다. 컴퓨터의 로컬 하드 드라이브에 사용을 원하는 펌웨어가 저장되어 있어야 합니다. 브라우즈를 클릭하여 로컬 하드드라이브에 업그레이드에 사용할 펌웨어를 검색합니다. 펌웨어를 업그레이드 하는 것은 시스템 설정에 영향이 없지만, 펌웨어를 업그레이드 하기전에 시스템 설정을 저장하는 것을 권장합니다. 펌웨어 업데이트를 위해  D-Link <a href=<?query("/sys/supporturl");?>>지원 사</a>이트를 체크하시거나 또는 지금 체크 버튼을 클릭하여 자동으로 공유기에 새로운 펌웨어를 체크 합니다.
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="dynamic_dns"><h2>동적 DNS</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=2>
		<p>
			동적 DNS(도메인 네임 서비스)은 지속적으로 도메인 네임과 동적으로 변하는 IP 어드레스를 연결해 줍니다. 케이블과 DSL 연결에서는 , 동적 IP를 할당 받고. 이 IP로 연결을 하고 일정 시간동안 사용됩니다. <?query("/sys/modelname");?>와 함께  DDNS 서비스를 설정하고, <?query("/sys/modelname");?>는 자동으로 DDNS 서버를 업데이트 하고, 매번 새로운 WAN IP 어드레스를 받습니다.
			<br>
			<strong><em>서버 어드레스</em></strong> - 드롭다운 메뉴에서 DDNS 프로바이더를 지정합니다.<br>
			<strong><em>호스트 이름</em></strong> - DDNS 서비스 프로바이더에 등록된 이름을 등록합니다.<br>
			<strong><em>사용자이름</em></strong> - DDNS 계정에 사용할 사용자 이름을 입력합니다.<br>
			<strong><em>패스워드</em></strong> - DDNS 계정에 사용하는 패스워드를 입력합니다.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="system_check"><h2>시스템 체크</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			이 도구는 인터넷(WAN)인터이스와 LAN 간에 물리적인 연결을 검사합니다. 고급기능이며, 공유기의 모든 이더넷 포트를 LAN 케이블 테스터로 기록합니다.  GUI를 통해서 케이블 테스트를 원격에서 진단하고, 오픈 서킷, 숏 서킷, 스왑페어, 임피던드 불일치 같은 케이블 문제를 리포트 합니다. 이 기능은 서비스 콜을 줄이고, 사용자에게 케이블 연결 트러블슈팅을 쉽게 해 줍니다.
		</p>
		<p>
			<strong>핑 테스트</strong><br>
			이 유용한 진단 유틸리티는 인터넷에 있는 컴퓨터를 체크 하는데 사용합니다. 특정 호스트에 핑 패킷을 보내서 응답을 받습니다. 핑을 사용하려는 호스트 이름 또는 IP 어드레스를 입력하고 <strong>Ping</strong>을 클릭합니다. 핑 시도 상태는 핑 결과 박스에 보여 집니다.		
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="schedules"><h2>스케쥴</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>	
			이 페이지는 공유기의 글로벌 스케쥴을 설정하는데 사용합니다.  설정을 하면 공유기에 스케쥴링 기능이 지원이 되고 그후에 적용이 됩니다.
			<br>
			<strong><em>이름</em></strong> - 스케쥴에 정의된 이름 입니다.<br>
			<strong><em>일자</em></strong> -
			이 정의된 스케쥴을 원하는 일자, 일정기간, 주, 매일에 선택합니다.<br>
			<strong><em>매일 - 24시간</em></strong> -
			특정일 전체 24시간동안 스케쥴을 액티브 할려면 이 박스를 체크합니다.<br>
			<strong><em>시작시간</em></strong> -
			정의된 스케쥴을 액티브 할 시간을 선택합니다.<br>
			<strong><em>끝나는 시간</em></strong> -
			정의된 시스쥴을 끝내는 시간을 선택합니다.<br>
			<strong><em>스케쥴 룰 리스트</em></strong> -
			정의된 모든 스케쥴을 보여 줍니다.
		</p>
	</td>
</tr>
</table>
</div>

						   