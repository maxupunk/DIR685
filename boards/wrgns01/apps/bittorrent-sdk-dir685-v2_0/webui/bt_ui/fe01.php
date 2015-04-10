<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<?
require("/www/model/__admin_check.php");
?>
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
	<title>BitTorrent Download Manager</title>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<script src="./btsdk.js"></script>
	<script src="./btuicommon.js"></script>

	<script>
	function myInit() {  showUploadFormUrl(); torrentsGet(); initFileUpload(); }
	window.onload = myInit;
	</script>

	<link rel="stylesheet" type="text/css" href="./btbase.css" />
	<!--[if lte IE 6]>
	<link rel="stylesheet" type="text/css" href="./btlteIE6.css" />
	<![endif]-->
</head>
<body>

<script type="text/javascript">

var sdkCtl = new SdkCtl();

var SORT_ASC = 1;
var SORT_DSC = 2;

/* Soring function and sorting order for list of torrents */
var torrentListSortFunc = cmpName;
var torrentListSortOrder = SORT_ASC;

/* convert a torrent state to one of the 4 classes: 
    stopped, downloading, finished, seeding */
function trClassFromTorrent(torrent) {
	if (torrent.stopped) return "stopped";
	var state = torrent.state;
	var state_to_class_map = ["queued_for_checking", "downloading", 
		"checking_files", "downloading", 
		"connecting_to_tracker", "downloading", 
		"downloading", "downloading",
		"finished", "finished", 
		"seeding", "seeding", 
		"allocating", "downloading"];
	for (var i = 0; i < state_to_class_map.length / 2; i++) {
		if (state == state_to_class_map[i*2])
			return state_to_class_map[i*2+1];
	}
	return "unknown";
}

function cmpName(t1, t2) {
	var t1cap = t1.caption.toLowerCase();
	var t2cap = t2.caption.toLowerCase();
	if (t1cap < t2cap) { return -1; }
	if (t1cap > t2cap) { return 1; }
	return 0;
}

function cmpSize(t1, t2) { return t1.size - t2.size; }
function cmpPercentDone(t1, t2) { return torrentDonePercentF(t1) - torrentDonePercentF(t2); }
function cmpDownSpeed(t1, t2) { return t1.dl_rate - t2.dl_rate; }
function cmpUpSpeed(t1, t2) { return t1.ul_rate - t2.ul_rate; }
function cmpEta(t1, t2) { return torrentEtaSecs(t1) - torrentEtaSecs(t2); }

var idNames = ["sortName", "sortSize", "sortPercenDone", "sortDownSpeed", "sortUpSpeed", "sortETA"];
var sortFuncs = [cmpName,  cmpSize,    cmpPercentDone,     cmpDownSpeed,    cmpUpSpeed, cmpEta];

function findSortFunc(sortParam) {
	for (var i=0; i < idNames.length; i++) {
		if (sortParam == idNames[i])
			return sortFuncs[i];
	}
	return null;
}

function sortTorrents() {
	if (!torrentListSortFunc) return;
	lastTorrents.sort(torrentListSortFunc);
	if (SORT_DSC == torrentListSortOrder)
		lastTorrents.reverse();
}

function changeTorrentListSortOrder(sortParam) {
	var newSortFunc = findSortFunc(sortParam);
	if (newSortFunc == torrentListSortFunc) {
		torrentListSortOrder = (torrentListSortOrder == SORT_ASC) ? SORT_DSC : SORT_ASC;
	} else {
		torrentListSortOrder = SORT_ASC;
		torrentListSortFunc = findSortFunc(sortParam);
	}
	sortTorrents();
	$("torrentList").innerHTML = htmlForTorrentList(lastTorrents);
}

/*<table summary="Statistics of all torrent activity">
	<thead>
		<tr>
			<th scope="col"><a href="#" id="sortName">Name</a></th>
			<th scope="col"><a href="#" id="sortSize">Size</a></th>
			<th scope="col"><a href="#" id="sortPercentDone">PercentDone</a></th>
			<th scope="col"><a href="#" id="sortDownSpeed">Down Speed</a></th>
			<th scope="col"><a href="#" id="sortUpSpeed">Up Speed</a></th>
			<th scope="col"><a href="#" id="sortETA">ETA</a></th>
		</tr>
	</thead>
	<tbody>
		<tr class="on [stopped | downloading | finished | seeding]" onClick="selectTorrent($hash)">
		<th scope="row">caption</th>
		<td>size</td>
		<td>progress</td>
		<td>dl speed</td>
		<td>ul speed</td>
		<td>eta</td>
		</tr>
	</tbody>
</table>*/
function htmlForTorrentList(torrents) {
	var t = "";
	var colNames = ["Name", "Size", "Progress", "Download", "Upload", "ETA"];
	for (var i = 0; i < idNames.length; i++) {
		var id = idNames[i];
		var name = colNames[i];
		var cls = name;
		if (torrentListSortFunc == sortFuncs[i]) {
			cls = (torrentListSortOrder == SORT_ASC) ? cls + " sortasc" : cls + " sortdsc";
		}
		var url = 'javascript:changeTorrentListSortOrder(' + qs(id) + ')';
		var link = "<a href='" + url + "' id=" + qs(id) + ">" + name + "</a>";
		var txTxt = th(link, "col", cls);
		t += th(link, "col", cls);
	}

	t = thead(tr(t));
	for (var i = 0; i < torrents.length; i++) {
		var ti = torrents[i];
		var name = ti.caption.escapeHTML();
		var trClass = "on ";
		var selectTorrentJs = null;
		if (selectedTorrentHash != ti.hash) {
			selectTorrentJs = "selectTorrent(" + qs(ti.hash) + ");";
			name = ajs(selectTorrentJs, ti.caption);
			trClass = "";
		}
		trClass += trClassFromTorrent(ti);
		var onClickTxt = "";
		if (selectTorrentJs) onClickTxt = " onClick=" + qs2(selectTorrentJs);
		trTxt = "<tr" + attcls(trClass) + onClickTxt + ">";
		var img = statusImageForTorrent(ti);
		var alt = statusTextForTorrent(ti);
		trTxt += '<th scope="row" class="tname">';
		trTxt += "<img" + attr("src", img) + attr("alt", alt) + attr("title", alt) + "/>";
		trTxt += name + '</th>';
		trTxt += td(ppSize(parseFloat(ti.size)));
		trTxt += "<td class=\"tprogress\"><div id=\"progressContainer\"><div id=\"progressBar\" style=\"width:" + torrentDonePercent(ti) + ";\"></div><em>" + torrentDonePercent(ti) + "</em></div></td>";
		trTxt += td(ppRate(ti.dl_rate));
		trTxt += td(ppRate(ti.ul_rate));
		trTxt += td(torrentEta(ti));
		trTxt += "</tr>";
		t += trTxt;
	}
	return startTag("table cellspacing=9") + tbody(t) + endTag("table");
}

function torrentFileCompleted(file) { return file.done == file.size; }

/*	<li>fielname one</li>
	<li>filename two</li> */
function htmlForFiles(hash, files) {
	var t = "";
	for (var i = 0; i < files.length; i++) {
		var file = files[i];
		var url = file.name.escapeHTML();
		if (torrentFileCompleted(file))
			url = "<a href=" + qs2("/api/torrent-file-get?hash=" + hash + "&id=" + file.id) + ">" + file.name.escapeHTML() + "</a>";
		t += li(url);
	}
	return t;
}

function showFiles(hash, files) {
	var html = htmlForFiles(hash, files);
	$("tFileList").innerHTML = html;
	showEl("tFiles");
}

function showFilesForTorrent(hash) {
	var files = filesForTorrent[hash];
	if (files) 
		showFiles(hash, files);
}

function htmlForTorrentActions(torrent) {
	var t = ""; 
	var liTxt = "";
	var liCls = "";
	var hash = "";
	if (torrent) 
		hash = qs2(torrent.hash);
	liTxt = "Start";
	if (torrent && torrent.stopped)
		liTxt = ajs("torrentStart(" + hash+ ");", liTxt);
	t += li(liTxt);
	liTxt = "Stop";
	if (torrent && !torrent.stopped)
		liTxt = ajs("torrentStop(" + hash + ");", liTxt);
	t += li(liTxt);

	liTxt = "Remove";
	liCls = "aRemove";
	if (torrent) 
		liTxt = ajs("torrentRemoveAsk(" + hash + ");", liTxt);
	t += li(liTxt, liCls);

	return t;
}

function showTorrentActions(torrent) {
	$("tActions").innerHTML = htmlForTorrentActions(torrent);
}

function showTorrentDetails(ti) {
	if (!ti) {
		hideEl("tDetails");
		hideEl("vDivider");
		return;
	}
	$("tDetailsName").innerHTML = ti.caption;
	$("tDetailsProgress").innerHTML = "<div id=\"progressContainer\"><div id=\"progressBar\" style=\"width:" + torrentDonePercent(ti) + ";\"></div><em>" + torrentDonePercent(ti) + "</em></div>";
	$("tDetailsSize").innerHTML = ppSize(parseFloat(ti.size));
	$("tDetailsRemaining").innerHTML = torrentRemaining(ti);
	$("tDetailsDownloaded").innerHTML = torrentDownloaded(ti);
	$("tDetailsUploaded").innerHTML = torrentUploaded(ti);
	$("tDetailsSeeds").innerHTML = ti.seeds_connected + " (" + ti.seeds_total + ")";;
	$("tDetailsPeers").innerHTML = ti.peers_connected + " (" + ti.peers_total + ")";
	$("tDetailsRatio").innerHTML = torrentRatio(ti);
	$("tDetailsAvail").innerHTML = torrentAvail(ti);
	$("tDetailsDlSpeed").innerHTML = ppRate(ti.dl_rate);
	$("tDetailsUlSpeed").innerHTML = ppRate(ti.ul_rate);
	showEl("tDetails");
	showEl("vDivider");
}

function onTorrentsRefreshFinished(request) {
	if (failedRequest(request)) {
		showConnectionError();
		return;
	}
	lastTorrents = torrentsFromRequest(request);
	sortTorrents();
	$("torrentList").innerHTML = htmlForTorrentList(lastTorrents);
	var total_dl_ul = calcTotalDlUlRate(lastTorrents);
	var total_dl = ppRate(total_dl_ul[0]);
	var total_ul = ppRate(total_dl_ul[1]);
	$("tdlspeed").innerHTML = total_dl;
	$("tulspeed").innerHTML = total_ul;

	hideAlerts();
	showEl("tActions");
	showEl("torrentList");

	if (0 == lastTorrents.length) {
		showEl("noTorrents");
	} else {
		hideEl("noTorrents");
	}
	stopRefresh(); /* just in case cancel previous timeout */
	torrentsRefreshTimeout = setTimeout("torrentsRefresh()", sdkCtl.refreshFreq);
	showTorrentDetails(torrentFromHash(selectedTorrentHash));
	showTorrentActions(torrentFromHash(selectedTorrentHash));
	if (null == selectedTorrentHash) {
		if (lastTorrents.length > 0) {
			selectTorrent(lastTorrents[0].hash);
		}
	}
}

function onTorrentGetFilesFinished(request) {
	if (failedRequest(request)) {
		showConnectionError();
		return;
	}
	var rsp = request.responseText;
	var json = evalJson(rsp);
	for (var hash in json.torrents) {
		filesForTorrent[hash] = json.torrents[hash];
	}
	showFilesForTorrent(selectedTorrentHash);
}

function selectTorrent(hash) {
	if (null == hash) return;
	selectedTorrentHash = hash;
	showTorrentDetails(torrentFromHash(selectedTorrentHash));
	showTorrentActions(torrentFromHash(selectedTorrentHash));
	$("torrentList").innerHTML = htmlForTorrentList(lastTorrents);
	torrentGetFiles(hash);
	torrentsRefresh();
}

function chooseTorrentToSelectAfterRemoval() {
	for (var i=0; i < lastTorrents.length; i++) {
		var t = lastTorrents[i];
		if (t.hash != selectedTorrentHash)
			continue;

		if (i == lastTorrents.length - 1) {
			/* if last one in the list, select the one before */
			if (i > 0)
				return lastTorrents[i-1].hash;
			return null;
		} else {
			/* if not last, select one after */
			return lastTorrents[i+1].hash;
		}
	}
	return null;
}

function showConnectionError() {  showAlert("Connection to server failed.", "Retry", "error"); }

</script>
<!--
<div id="banner" class="cl">
	<div id="bt-branding">
		<h1><a href="./fe01.html"><strong>BitTorrent<span></span></strong> Download Manager</a></h1>
		<form action="http://www.bittorrent.com/search" method="post" id="btSearch">
			<input type="text" name="q" title="Search BitTorrent.com" onfocus="searchFocus();" onblur="searchBlur();" class="notentered" value="Search BitTorrent.com" />
			<button type="submit">Search</button>
		</form>
	</div>
</div>
-->
<div id="container">
	<div id="application">
		<div id="nav-stats">
			<ul id="nav">
			    <li>Downloads</li>
				<li class="last"><a href="./btsettings.html">Settings</a></li>
				<!--<li class="last"><a href="http://SDK_LICENCEE_SUPPORT_PAGE">Support</a></li>-->
			</ul>
			<div id="totalStats">
				<h2>Total Speeds</h2>
				<ul class="cl">
					<li><h3>Downloads:</h3> <span id="tdlspeed"></span></li>
					<li><h3>Uploads:</h3> <span id="tulspeed"></span></li>
				</ul>
			</div>
		</div>
		<h1>Torrent Downloads</h1>
		
		<div id="uploadOptions">

			<div id="divUploadUrl">
				<form id="uploadUrl" onsubmit="return uploadFormUrlOnSubmit();" >
					<input name="q" maxlength="2048" onfocus="uploadUrlFocus();" onblur="uploadUrlBlur();" class="notentered" title="Add Torrent From URL" />
					<button type="submit">Add</button>
				</form>
			</div>

			<div id="divUploadFile" style="display:none;">
				<form id="uploadFile" method="POST" action="/api/torrent-add?start=yes" target="uploadFrame" enctype="multipart/form-data">
					<div class="holder">
						<input type="file" name="fileEl" title="Add Torrent From File" />
					</div>
					<p id="uploadFileName">No File Selected</p>
					<button type="submit">Add</button>
				</form>
				<iframe id="uploadFrame" name="uploadFrame" style="width:0px;height:0px;border:0px;"></iframe>
			</div>

			<ul id="add-options">
				<li id="tAddUrl" class="on"><a href="javascript:showUploadFormUrl()">Add Torrent From URL</a></li>
				<li id="tAddFile" class=""><a href="javascript:showUploadFormFile()">Add Torrent From File</a></li>
			</ul>
		
		</div>

		<ul id="tActions" class="cl"></ul>
		
		<div id="torrentList"></div>

		<div id="noTorrents" style="display:none;">There are currently no torrents. Add a torrent above.</div>

		<div id="vDivider" style="display:none"></div>

		<div id="tDetails" class="cl" style="display:none">
			<h2><em>Torrent Details:</em> <span id="tDetailsName"></span></h2>
			<div id="tDetailsProgress"></div>
			<ul id="tdBytes">
				<li><h3>Size:</h3><span id="tDetailsSize"></span></li>
				<li><h3>Remaining:</h3><span id="tDetailsRemaining"></span></li>
				<li><h3>Downloaded:</h3><span id="tDetailsDownloaded"></span></li>
				<li><h3>Uploaded:</h3><span id="tDetailsUploaded"></span></li>
			</ul>
			<ul id="tSeedsAndPeers">
				<li><h3>Seeds:</h3><span id="tDetailsSeeds"></span></li>
				<li><h3>Peers:</h3><span id="tDetailsPeers"></span></li>
				<li><h3>Ratio:</h3><span id="tDetailsRatio"></span></li>
				<li><h3>Availability:</h3><span id="tDetailsAvail"></span></li>
			</ul>
			<ul id="tSpeeds">
				<li><h3>Download Speed:</h3><span id="tDetailsDlSpeed"></span></li>
				<li><h3>Upload Speed:</h3><span id="tDetailsUlSpeed"></span></li>
			</ul>
			<div id="tFiles">
				<h3>Files:</h3>
				<ul id="tFileList">
				</ul>
			</div>
		</div>
	</div>
</div>

<div id="msgAlert" style="display:none;">
	<div class="bg"></div>
	<div class="message">
	    <p id="msgAlertId"></p>
	    <a id="msgAlertBtnId" class="oButton" href="javascript:torrentsRefresh();">Retry</a>
	</div>
</div>

<div id="removeTorrentAlert" style="display:none;">
	<div class="bg"></div>
	<div class="message">
		<p id="removeTorrentTxt">your message</p>
		<div class="cl">
			<a class="oButton first" href="javascript:torrentRemoveYes();">Remove</a>
			<a class="oButton" href="javascript:torrentsRefresh();">Cancel</a>
		</div>
	</div>
</div>

<!--
<hr><center>
<a href="javascript:stopRefresh()">stopRefresh</a>&nbsp;&nbsp;
<a href="javascript:showConnectionError();stopRefresh()">showConnectionError</a>
</center>
-->

</body>
</html>
