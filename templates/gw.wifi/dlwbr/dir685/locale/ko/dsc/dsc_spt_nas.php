<div class="box">
<a name="disk_management"><h2>디스크 관리</h2></a>
	<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			디스크 관리 페이지는 현재 장치에 설정과 정보를 포함하고 있습니다.<br>
			<br>
			<strong><em>하드 디스크 정보</em></strong> -
			하드드라이브 상세한 정보를 포함하고 있습니다.<br>
			<strong><em>포맷 설정</em></strong> -
			이 버튼은 하드드라이브를 포맷 할 수 있습니다.<br>
			경고: 이 동작은 하드드라이브 청소합니다. 모든 데이터가 삭제 됩니다.<br>
			<strong><em>하드 드라이브 설정 </em></strong> -
			이 설정이 동작해서 일정시간이 지나면 스탠바이 모들로 바뀌고, 하드드라이브에 쓰여진 데이터가 없다면, 파워 소비가 줄어들겁니다.<br>
		</p>
	</td>
</tr>
 </table>
</div>

<div class="box">
<a name="users_groups"><h2>사용자/그룹</h2></a>
	<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=228>
		<p>
			<strong>유저</strong><br>
			사용자 등록을 합니다. 사용자를 추가하고 네트워크 접근과 FTP 서버 영역에 룰을 정합니다. 추가된 각 유저는 스케쥴 다운로드 영역을 접근 할수 있습니다.
		</p>
		<p>
			<strong><em>사용자 이름</em></strong> -
			이름을 등록하세요<br>
			<strong><em>패스워드</em></strong> -
			패스워드를 입력하세요<br>
			<strong><em>패스워드 확인</em></strong> -
			패스우드를 재 입력하고, '설정저장'버튼을 누르면 사용자가 추가 됩니다.<br>
			<br>
			등록된 사용자는 리스트에 보이고, 그룹에도 등록됩니다(만일 등록했다면).사용자의 패스워드는 '노트패드와 연필' 버튼을 클릭해서 수정가능하고 또는 사용자는 '휴지통'버튼을 눌러 삭제할수도 있습니다. 		
		</p>
		<p>
			<strong>그룹</strong><br>
			그룹등록을 합니다. 그룹이 등록되면 사용자 페이지에서 그룹영역을 사용할 수 있습니다.<br>
			<br>
			등록된 그룹은 이 페이지에 리스트에 보입니다. 이 그룹에 속한 사용자도 같이 보입니다.<br>
		</p>
	</td>
</tr>
 </table>
</div>
 
 
<div class="box">
<a name="storage_access"><h2>저장장치 접근</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=64> 
		<p>
			<strong><em>목록</em></strong> -
			사용자나 그룹을 선택하세요<br>
			<strong><em>사용자 또는 그룹</em></strong> -
			리스트에서 사용자나 그룹을 선택하세요.  모든 사용자에게 룰을 적용하려면 '모든 사용자' 를 선택하세요<br>
			<strong><em>폴더</em></strong> -
			폴더를 선택하려면 "브라우즈"를 클릭하세요.  폴더는 내부 드라이브에 위치해야 합니다.<br>
			<strong><em>허용</em></strong> -
			선택된 사용자나 그룹에 "읽기 전용", "읽기/쓰기" 허용등을 선택할 수 있습니다.<br>
			<strong><em>Oplocks</em></strong> -
			선택 잠금(oplocks) 특성은 32bit 윈도우 패밀리 운영체제에서 동작하는 랜 관리 네트워크 프로토콜 입니다. Oplocks은 클라이언트에게 논리적인 영역을 보장합니다. 이러한 보장은 파일 내용은 변경할수 없다고 클라이언트에게 알리고 또는 만일 변경사항이 발생하기전에 클라이언트에게 변경해도 되는지를 알립니다. Oplocks은 네트워크 성능을 높이기 위해 디자인 되었으며,  네트워크 파일을 공유하기 위해 파일 기반의 데이터베이스 어플리케이션을 사용할때는 Oplocks을 <strong>No(off) </strong>하는 것을 권장합니다.
			<br>
			<br>
			어떤 운영시스템이 Oplocks에 영향을 받을까요?<br>
			<br>
			비스타는 디폴트로 Oplocks가 동작이고, 파일공유 어플리케이션으로 성능 이슈가 생긴다면, DIR-685의 성능을 높이기 위해 Oplocks을 <strong>No(off)</strong>로 설정해야 합니다.
			<br>
			<strong><em>Map Archive</em></strong> -
			이 기능이 동작하면 파일 속성에 "Archive"는 DIR-685에 저장되어 있는 파일을 복사를 합니다.  어떤 백업 소프트웨어는 이런 속성을 갖고 있어서 백업처럼 저장을 합니다.<br>
			<strong><em>코멘트</em></strong> -
			룰에 대한 추가 코멘트를 합니다. 옵션이면 다른 기능에 영향은 없습니다.<br>
			<br>
			설정 저장'을 클릭하면 룰이 저장됩니다.  모든 저장된 룰은 리스트에 보입니다. 룰을 수정하거나 삭제를 하려면 '메모장과 연필' 또는 '휴지통'을 클릭하세요.
			<br>
		</p>
 </tr>
</table>
</div>
 
 
<div class="box">
<a name="ftp_server"><h2>FTP 서버</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=99>
		<p>
			<strong><em>목록</em></strong> -
			사용자나 그룹을 선택하세요.<br>
			<strong><em>사용자</em></strong> -
			리스트에서 사용자나 그룹을 선택하세요.  모든 사용자에게 룰을 적용하려면 '모든 사용자' 를 선택하세요. 익명도 사용자처럼 리스트에 있습니다.<br>
			<strong><em>폴더</em></strong> -
			폴더를 선택하려면 "브라우즈"를 클릭하세요.  폴더는 내부 드라이브에 위치해야 합니다. 루트의 모든 폴더를 접근 하려면 'root' 상자를 클릭하세요.<br>
			<strong><em>허용</em></strong> -
			선택된 사용자나 그룹에 "읽기 전용", "읽기/쓰기" 허용등을 선택할 수 있습니다. 룰을 추가하려면 '추가'를 클릭하세요. 모든 룰이 리스트에 보여집니다. . 룰을 수정하거나 삭제를 하려면 '메모장과 연필' 또는 '휴지통'을 클릭하세요.<br>
			<strong><em>최대 사용자 </em></strong> -
			동시에 FTP 서버에 접속 허용 가능한 사용자 수 입니다. 디폴트는 10입니다.<br>
			<strong><em>유휴시간</em></strong> -
			일정 유휴시간이 지나면  FTP 서버는 로그를 남깁니다.<br>
			<strong><em>포트</em></strong> -
			FTP 서버 포트를 바꾸고 싶으면, 새로운 포트넘버를 여기에 입력하세요.  이것은 고급 설정이며,  복잡해 질수도 있습니다. FTP 포트를 바꾸지 않아도 된다면, 디폴트 값인 21을 그래도 사용하는게 권장사항입니다.<br>
			<strong><em>Flow Control</em></strong> -
			이 기능은 FTP 서버를 통하는 데이터 플로우를 조정합니다. 만일 제한을 한다면, 사용자는 느린 속도로 다운로드를 받을 수 있습니다. 로컬 대역폭을 보장 합니다.<br>
			<strong><em>클라이언트 언어</em></strong> -
			윈도우 FTP 같은 대부분 표준 FTP 클라이언트는 파일을 전송할때 웨스턴 유럽피안 코드페이지를 지원합니다. 노던 유럽피안, 센트럴 유럽피안,  전통과 단순화한 중국 코드페이지도 비표준 FTP 클라이언트를 위해 추가되었고, 지원됩니다.<br>
			<br>
			끝낼때는 '설정저장'  버튼을 클립합니다.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="upnp_av_server"><h2>UPnP AV 서버</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=44>
		<p>
			DIR-685는 UPnpAV 미디어 서버가 빌트인 되어 있고, UPnP AV 미디어 플레이어와 호환 됩니다.<br>
			<br>
			<strong><em>UPnP AV 서버</em></strong> -
			UPnP AV 서버를 동작 또는 동작시키지 않습니다.<br>
			<strong><em>폴더</em></strong> -
			루트 폴더에 있는 미디어 파일(뮤직, 사진, 비디오)을 로케이트 하기 위해 '브라우즈'를 클릭하세요. DIR-685의 모든 파일을 접근할수 있는 루트를 지정할수 있습니다. <br>
			<strong><em>Auto Refresh</em></strong> -
			공유된 UPNP AV 데이터를 5, 15, 30분 또는 1,2,6,12,24 시간 간격으로 자동으로 업데이트 하도록 설정하세요.<br>
			<br>
			끝낼때는 '설정저장'  버튼을 클립합니다.<br>
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="itunes_server"><h2>iTunes 서버</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			The iTunes server will allow iTunes software to automatically detect and play music from the DIR-685.<br>
			<br>
			<strong><em>iTunes 서버</em></strong> -
			iTunes 서버를 동작 또는 동작시키지 않습니다.<br>
			<strong><em>폴더 </em></strong> -
			루트 폴더에 있는 미디어 파일(뮤직, 사진, 비디오)을 로케이트 하기 위해 '브라우즈'를 클릭하세요. DIR-685의 모든 파일을 접근할수 있는 루트를 지정할수 있습니다. <br>
			<strong><em>Auto Refresh</em></strong> -
			공유된 UPNP AV 데이터를 5, 15, 30분 또는 1,2,6,12,24 시간 간격으로 자동으로 업데이트 하도록 설정하세요.<br>
			<br>
			끝낼때는 '설정저장'  버튼을 클립합니다.<br>
		</p>
</td>
</tr>
</table>
</div>

<div class="box">
<a name="bt_download_manager"><h2>BT 다운로드 매니저</h2></a>
	<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			BT 다운로드 매니저 페이지는 PC의 부팅 없이 인터넷에서 bit torrent 파일을 다운받을수 있게 설정하는 부분이 포함되어 있다<br>
			<br>
			<strong><em>BT 설정</em></strong> -
			BT 다운로드 매니져 서비스를 동작 또는 동작하지 않도록 할수 있다. 다운로드 파일을 저장할수 있게 디렉토리 패스를 지정할수 있다.  모든 다운로드 파일은 지정된 디렉토리에 저장할수 있고, 완료된 파일은 "완료" 폴더에 저장되고,  완료되지 않은 파일은 "비완료"라는 폴더에 저장된다. 파일 관리자에 의해 원래 다운로드 파일을 남긴다. <br>
			<strong><em>Torrent 다운로드</em></strong> -
			BT 다운로드 매니져 화면에는 URL 또는 개인적인 BT 파일이든지 아이템을 추가 다운로드를 허용합니다.<br>
			모든 아이템은 리스트에서 볼수 있으며, 각 행 별로 다운로드 중인 각 파일을 컨트롤 하거나 뷰 할수 있습니다.<br>
			<strong><em>다운로드 아이템 테이블</em></strong> -
			다운로드 중인 아이템에 대해  "더 자세히"를 클릭하면 좀 더 자세한 정보를 볼 수 있습니다.<br>
			<strong><em>정지</em></strong> -
			다운로드 정지/일시멈춤을 클릭하면, 다른 다운로드 아이템은 대역폭을 더 확보할수 있습니다.<br>
			<strong><em>제거</em></strong> -
			실수로 다운로드을 하고 있을때, 취소/삭제 버튼을 클릭하면 다운로드를 제거할수 있습니다.<br>
			<br>
			삭제된 아이템이 이미 완료가 되면, 항목만 삭제가 되었고, 파일은  "완료" 디렉토리에 보관이 되어 있습니다.
			<br>
			<strong><em>제거 완료</em></strong> -
			이 버튼은 다운로드 된 파일을 삭제하지 않고,  테이블에 있는 모든 다운로드가 완료된 파일을 제거 할수 있습니다.<br>			
		</p>
	</td>
</tr>
 </table>
</div>
