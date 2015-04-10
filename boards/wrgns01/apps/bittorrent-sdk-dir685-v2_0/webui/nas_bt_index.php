<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<?
require("/www/model/__admin_check.php");
?>
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
	<title>BitTorrent Download Manager</title>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<script src="./bt_ui/btsdk.js"></script>
	<script src="./bt_ui/btuicommon.js"></script>

	<script>
	//+++ Teresa, for first time to reload
	var onload_time=new Number;
	onload_time=0;
	function myInit() { showUploadFormUrl(); torrentsGet(); initFileUpload(); }
	window.onload = myInit;
	</script>

	<link rel="stylesheet" type="text/css" href="./bt_ui/btbase.css" />
	<!--[if lte IE 6]>
	<link rel="stylesheet" type="text/css" href="./bt_ui/btlteIE6.css" />
	<![endif]-->
</head>
<body>

<script type="text/javascript">

var sdkCtl = new SdkCtl();

/*<div class="tProgress"><div class="progressBar" style="width:100%;"></div><em>100%</em></div> */
function htmlForProgress(ti) {
	var donePercent = torrentDonePercent(ti);
	var t = "<div" + attcls("tProgress") + ">";
	t += "<div" + attcls("progressBar");
	t += attr("style", "width:" + donePercent + ";");
	t += "></div><em>" + donePercent + "</em></div>";
	return t;
}

/*<ul class="tActions">
	<li class="start"><a href="#">Start</a></li>
	<li class="stop" style="display:none;"><a href="#">Stop</a></li>
	<li class="remove"><a href="#">Remove</a></li>
</ul>*/
function htmlForActions(ti) {
	var jsUrl = ajs("torrentStop(" + qs(ti.hash) + ")", "Stop");
	var cls = "stop";
	if (ti.stopped) {
		jsUrl = ajs("torrentStart(" + qs(ti.hash) + ")", "Start");
		cls = "start";
	}
	var t = li(jsUrl, cls);
	jsUrl = ajs("torrentRemoveAsk(" + qs(ti.hash) + ")", "Remove");
	t += li(jsUrl, "remove");
	return ul(t, "tActions");
}

var detailsShown = {};

function detailsForTorrentVisible(hash) { return detailsShown[hash]; }

function htmlForMoreLess(hash) {
	if (detailsForTorrentVisible(hash))
		return ajs("hideDetailsForTorrent(" + qs(hash) + ")", "Less Details");
	else
		return ajs("showDetailsForTorrent(" + qs(hash) + ")", "More Details");
}

function showDetailsForTorrent(hash) { 
	detailsShown[hash] = 1;
	$("moreDetails" + hash).innerHTML = htmlForMoreLess(hash);
	$("moreDetails" + hash).className = "lessDetails";
	showEl("tDetailsCont" + hash);
}

function hideDetailsForTorrent(hash) { 
	delete detailsShown[hash]; 
	$("moreDetails" + hash).innerHTML = htmlForMoreLess(hash);
	$("moreDetails" + hash).className = "moreDetails";
	hideEl("tDetailsCont" + hash);
}

/*<ul class="tBigDetails">
	<li class="size">569 MB</li>
	<li class="remaining">2h 45m</li>
	<li class="moreDetails" id="moreDetails$hash"><a href="toggleDetails('$hash')">More Details</a></li>
</ul>*/
function htmlForBigDetails(ti) {
	var t = li(ppSize(ti.size), "size");
	t += li(torrentEta(ti), "remaining");
	var cls = "moreDetails";
	if (detailsForTorrentVisible(ti.hash))
		cls = "lessDetails";
	t += "<li" + attcls(cls) + attr("id", "moreDetails" + ti.hash) + ">";
	t += htmlForMoreLess(ti.hash) + "</li>";
	return ul(t, "tBigDetails");
}

/*<ul class="tdBytes">
	<li><h3>Remaining:</h3><span class="tDetailsRemaining">56</span></li>
	<li><h3>Downloaded:</h3><span class="tDetailsDownloaded">56</span></li>
	<li><h3>Uploaded:</h3><span class="tDetailsUploaded">23</span></li>
</ul>*/
function htmlForDetailBytes(ti) {
	var t = li(h3("Remaining:") + 
				span(torrentRemaining(ti), "tDetailsRemaining"));
	t += li(h3("Downloaded:") + 
			 span(torrentDownloaded(ti), "tDetailsDownloaded"));
	t += li(h3("Uploaded:") + 
			 span(torrentUploaded(ti), "tDetailsUploaded"));
	return ul(t, "tdBytes");
}

/*<ul class="tSeedsAndPeers">
	<li><h3>Seeds:</h3><span class="tDetailsSeeds">11</span></li>
	<li><h3>Peers:</h3><span class="tDetailsPeers">12</span></li>
	<li><h3>Ratio:</h3><span class="tDetailsRatio">143</span></li>
</ul>*/
function htmlForDetailPeers(ti) {
	var seedsTxt = ti.seeds_connected + " (" + ti.seeds_total + ")";
	var t = li(h3("Seeds:") + span(seedsTxt, "tDetailsSeeds"));
	var peersTxt = ti.peers_connected + " (" + ti.peers_total + ")";
	t += li(h3("Peers:") + span(peersTxt, "tDetailsPeers"));
	t += li(h3("Ratio:") + span(torrentRatio(ti), "tDetailsRatio"));
	return ul(t, "tSeedsAndPeers");
}

/*<ul class="tSpeeds">
	<li><h3>Download Speed:</h3><span class="tDetailsDlSpeed">15</span></li>
	<li><h3>Upload Speed:</h3><span class="tDetailsUlSpeed">16</span></li>
	<li><h3>Availability:</h3><span class="tDetailsAvail">18</span></li>
</ul>*/
function htmlForDetailSpeeds(ti) {
	var t = li(h3("Download Speed:") + 
				span(ppRate(ti.dl_rate), "tDetailsDlSpeed"));
	t += li(h3("Upload Speed:") + 
			 span(ppRate(ti.ul_rate), "tDetailsUlSpeed"));
	t += li(h3("Availability:") + 
			 span(torrentAvail(ti), "tDetailsAvail"));
	return ul(t, "tSpeeds");
}

/*<div class="tFiles">
	<h3>Files:</h3>
	<ul class="tFileList">
		<li>name</li>
	</ul>
</div>*/
function htmlForDetailFiles(ti) {
	var files = filesForTorrent[ti.hash];
	if (!files) {
		torrentGetFiles(ti.hash);
		return "";
	}
	var t = "";
	for (var i=0; i < files.length; i++) {
		var file = files[i];
		t += li(file.name.escapeHTML());
	}
	t = h3("Files:") + ul(t, "tFileList");
	return inTag("div", t, "tFiles");
}

/*<div class="tDetailsCont" id="tDetailsCont$Hash">
	and parts for details
</div>*/
function htmlForDetails(ti) {
	var style = "display:none;";
	if (detailsForTorrentVisible(ti.hash))
		style = "display:block;";
	var t = '<div' + attcls("tDetailsCont") + attr("id", "tDetailsCont" + ti.hash)  + attr("style", style) + ">";
	t += htmlForDetailBytes(ti);
	t += htmlForDetailPeers(ti);
	t += htmlForDetailSpeeds(ti);
	t += htmlForDetailFiles(ti);
	return t + "</div>";
}

function htmlForTorrent(ti) {
	var name = ti.caption.escapeHTML();
	var img = statusImageForTorrent(ti);
	var alt = statusTextForTorrent(ti);
	var t = name + "<img" + attr("src", img) + attr("alt", alt) + attr("title", alt) + "/>";
	t = inTag("h2", t);
	t += htmlForProgress(ti);
	t += htmlForActions(ti);
	t += htmlForBigDetails(ti);
	t += htmlForDetails(ti);
	return li(t, "tInfo");
}

function htmlForTorrentList(torrents) {
	var t = "";
	//+++sonnia for record how many seeds still downloading.
	remain_download_seed=0;
	for (var i = 0; i < torrents.length; i++) {
		t += htmlForTorrent(torrents[i]);
	//	if(torrentRemaining(torrents[i])!="0 bytes")
	//	if(torrentStatus(torrents[i])!="finished"||torrentStatus(torrents[i])!="Finished")
		if(!torrentCompleted(torrents[i]))
		{
			remain_download_seed++;
		}	
	}
	return t;
}

function onTorrentsRefreshFinished(request) {
	if (failedRequest(request)) {
		showConnectionError();
		return;
	}
	lastTorrents = torrentsFromRequest(request);
	$("torrentList").innerHTML = htmlForTorrentList(lastTorrents);
	var total_dl_ul = calcTotalDlUlRate(lastTorrents);
	var total_dl = ppRate(total_dl_ul[0]);
	var total_ul = ppRate(total_dl_ul[1]);
	$("tdlspeed").innerHTML = total_dl;
	$("tulspeed").innerHTML = total_ul;

	hideAlerts();
	if (0 == lastTorrents.length) {
		showEl("noTorrents");
	} else {
		hideEl("noTorrents");
		showEl("torrentList");
	}
	stopRefresh(); /* just in case cancel previous timeout */
	torrentsRefreshTimeout = setTimeout("torrentsRefresh()", sdkCtl.refreshFreq);
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
	$("torrentList").innerHTML = htmlForTorrentList(lastTorrents);
}

function showConnectionError() { 
	showAlert("Connection to server failed, you can press \"Retry\" or wait to automating connection.", "Retry", "error"); 
	setTimeout("torrentsRefresh()", sdkCtl.refreshFreq);
}

function check_max_download_seeds()
{
	if(remain_download_seed >=10 )
	{
		showAlert("BT already have 10 seeds downloading, please add seed after download finished. (Max. downloading seeds: 10)", "Okay","error");
		clearUploadFile();
		return false;
	}	
	return true;
}

/* not needed for nas_bt_index.php */
function chooseTorrentToSelectAfterRemoval() { return null; }
</script>
<!--
<div id="banner" class="cl">
	<div id="bt-branding">
		<h1><a href="./bt_ui/fe01.html"><strong>BitTorrent<span></span></strong> Download Manager</a></h1>
		<form action="http://www.bittorrent.com/search" method="post" id="btSearch">
			<input type="text" name="q" title="Search BitTorrent.com" onfocus="searchFocus();" onblur="searchBlur();" class="notentered" value="Search BitTorrent.com" />
			<button type="submit">Search</button>
		</form>
	</div>
</div>
-->
<div id="container">
	<div id="appB">
		<div id="nav-stats">
			<ul id="nav">
			    <li>Downloads</li>
				<li class="last"><a href="./nas_bt_settings.php">Settings</a></li>
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
    			<form id="uploadUrl" onsubmit="return uploadFormUrlOnSubmit();">
    				<input name="q" maxlength="2048" onfocus="uploadUrlFocus();" onblur="uploadUrlBlur();" title="Add Torrent From URL" />
    				<button type="submit">Add</button>
    			</form>
    		</div>

    		<div id="divUploadFile" style="display:none;">
    			<form id="uploadFile" onsubmit="return check_max_download_seeds();" method="POST" action="/api/torrent-add?start=yes" target="uploadFrame" enctype="multipart/form-data">
    			<div class="holder">
    				<input type="file" name="fileEl" title="Add Torrent From File" />
    			</div>
    			<p id="uploadFileName">No File Selected</p>
    			<button type="submit">Add</button>
    			</form>
    			<iframe id="uploadFrame" name="uploadFrame" style="width:0px;height:0px;border:0px"></iframe>
    		</div>

    		<ul id="add-options">
    			<li id="tAddUrl" class="on"><a href="javascript:showUploadFormUrl()">Add Torrent From URL</a></li>
    			<li id="tAddFile" class=""><a href="javascript:showUploadFormFile()">Add Torrent From File</a></li>
    		</ul>
		
		</div>

		<div id="removeCompleted"><a href="javascript:removeCompletedTorrents();">Remove Completed</a></div>

		<ul id="torrentList"> </ul>

		<div id="noTorrents" style="display:none;">There are currently no torrents. Add a torrent above.</div>
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
<hr>
<center>
	<a href="javascript:stopRefresh()">stopRefresh</a>&nbsp;&nbsp;
	<a href="javascript:showConnectionError();stopRefresh()">showConnectionError</a>
</center>
-->

</body>
</html>
