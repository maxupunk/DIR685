/* result of the last /api/get-torrents request */
var lastTorrents = null;

var torrentsRefreshTimeout = null;

/* Infohash of currently selected torrent */
var selectedTorrentHash = null;

/* Infohash of the torrent to select after removal. Only needed
   by fe01.html */
var torrentToSelectAfterRemovalHash = null;

/* dict mapping infohash of a torrent with dict describing files in that torrent */
var filesForTorrent = {};

var REMOVE_DONT_ASK = 1;
var REMOVE_ASK_IF_INCOMPLETE = 2;
var REMOVE_ASK_ALWAYS = 3;

/* CUSTOMIZATION: you can change the policy used when user clicks "remove torrent" link */
var removeMode = REMOVE_ASK_ALWAYS;

/* Communicates torrent to remove between torrentRemoveAsk() and torrentRemoveYes().
   TODO: it's a bit lame to use a global but the alternative (rewriting links)
   is more work */
var torrentHashToRemove = null;

var remain_download_seed=0;

function getUploadFile() { return $("uploadFile").fileEl.value; }
function clearUploadFile() {
	$("uploadFile").fileEl.value = "";
	var el = $("uploadFileName");
	if (el) el.innerHTML = "No File Selected";
}

function showUploadFormFile() {
	clearUploadFile();
	hideEl("divUploadUrl");
	showEl("divUploadFile");
	var el = $("tAddUrl");
	if (el) {
		el.className = "";
		$("tAddFile").className = "on";
	}
}

var ADD_URL_TXT = "Add Torrent From URL";

function getUploadUrl() { return $("uploadUrl").elements[0].value; }
function clearUploadUrl() {
	var el = $("uploadUrl");
	el.elements[0].value = ADD_URL_TXT;
	el.elements[0].className = "notentered";
}

function showUploadFormUrl() {
	clearUploadUrl();
	hideEl("divUploadFile");
	showEl("divUploadUrl");
	var el = $("tAddUrl");
	if (el) {
		el.className = "on";
		$("tAddFile").className = "";
	}
}

function uploadUrlFocus() {
	var el = $("uploadUrl").elements[0];
	if (ADD_URL_TXT == el.value)
		el.value = "";
	el.className = "";
}

function uploadUrlBlur() {
	var url = getUploadUrl();
	if ("" == url)
		clearUploadUrl();
}

var SEARCH_TXT = "Search BitTorrent.com";

function clearSearch() {
	var el = $("btSearch").elements[0];
	el.value = SEARCH_TXT;
	el.className = "notentered";
}

function searchFocus() {
	var el = $("btSearch");
	if (SEARCH_TXT == el.elements[0].value)
		el.elements[0].value = "";
	el.elements[0].className = "";
}

function searchBlur() {
	var el = $("btSearch");
	if ("" == el.elements[0].value)
		clearSearch();
}

function stopRefresh() { 
	clearTimeout(torrentsRefreshTimeout); 
	torrentsRefreshTimeout = null;
}

function showAlert(msgTxt, buttonTxt, cls) {
	stopRefresh();
	$("msgAlert").className = cls;
	$("msgAlertId").innerHTML = msgTxt;
	$("msgAlertBtnId").innerHTML = buttonTxt;
	showEl("msgAlert");
}

function hideAlert() { hideEl("msgAlert"); }
function hideRemoveTorrentAlert() { hideEl("removeTorrentAlert"); }

function hideAlerts() {
	hideAlert();
	hideRemoveTorrentAlert();
}

/* Very crude detection of valid URLs */
function isValidUrl(txt) {
	if (txt.length < 8) return false;
	if (-1 == txt.indexOf("://")) return false;
	return true;
}

function initFileUpload() {
	var domCompliant = (document.createElement && document.getElementsByTagName);
	if (!domCompliant) return;
	var pseudoFileUpload = document.createElement('div');
	var x = document.getElementsByTagName('input');
	for (var i=0;i<x.length;i++) {
		if (x[i].type != 'file') continue;
		if (x[i].parentNode.className != 'holder') continue;
		x[i].className = 'hideFileInput';
		holder = x[i].parentNode;
		holder.parentNode.getElementsByTagName('p')[0].className = 'on';
		x[i].asscParagraph = holder.parentNode.getElementsByTagName('p')[0];
		x[i].onchange = x[i].onmouseout = function () {
		    if (this.value != '') {
			    this.asscParagraph.innerHTML = this.value;
			    this.asscParagraph.className = 'on picked';
			}    
			else {
			    this.asscParagraph.innerHTML = 'No File Selected';
			    this.asscParagraph.className = 'on';
			}
		};
		holder.file = x[i];
		holder.onmousemove = function(e)
		{
			if (typeof e == 'undefined') e = window.event;
			if (typeof e.pageY == 'undefined' &&  typeof e.clientX == 'number' && document.documentElement)
			{
				e.pageX = e.clientX + document.documentElement.scrollLeft;
				e.pageY = e.clientY + document.documentElement.scrollTop;
			};

			var ox = oy = 0;
			var elem = this;
			if (elem.offsetParent)
			{
				ox = elem.offsetLeft;
				oy = elem.offsetTop;
				while (elem = elem.offsetParent)
				{
					ox += elem.offsetLeft;
					oy += elem.offsetTop;
				};
			};

			var x = e.pageX - ox;
			var y = e.pageY - oy;
			var w = this.file.offsetWidth;
			var h = this.file.offsetHeight;

			this.file.style.top		= y - (h / 2)  + 'px';
			this.file.style.left	= x - (w - 30) + 'px';
		};
	}
}

function uploadFormUrlOnSubmit() {
	if(remain_download_seed >=10 )
	{
		showAlert("BT already have 10 seeds downloading, please add seed after download finished. (Max. downloading seeds: 10)", "Okay","error");
		return false;
	}
	var url = getUploadUrl();
	if (isValidUrl(url)) {
		showAlert("Torrent URL has been sent.", "Okay");
		torrentAddUrl(url);
	}
	else {
		showAlert(qs2(url) + " doesn't look like a valid url.", "Okay", "error");
		return false;
	}
	return false;
}

/* "dl" is for torrent beeing downloaded
   "ul" is for seed
   "inactive" is for stopped */
function statusImageForTorrent(torrent) {
	if (torrent.stopped)
		return "./bt_ui/img/inactive.png";
	if (torrentIsSeed(torrent))
		return "./bt_ui/img/up.png";
	return "./bt_ui/img/dl.png";
}

function statusTextForTorrent(torrent) {
	if (torrent.stopped)
		return "Stopped";
	if (torrentIsSeed(torrent))
		return "Seeding";
	return "Downloading";
}

function torrentFromHash(hash) {
	for (var i=0; i < lastTorrents.length; i++) {
		var ti = lastTorrents[i];
		if (hash == ti.hash)
			return ti;
	}
	return null;
}

function apiTorrentAddFinishedOk() {
	clearUploadFile();
	torrentsRefresh();
}

function apiTorrentAddFailed() {
	clearUploadFile();
	showAlert("Failed to add this torrent file (invalid torrent?).", "Okay", "error");
}

function removeCompletedTorrents() { 
	for (var i=0; i < lastTorrents.length; i++) {
		var torrent = lastTorrents[i];
		if (torrentCompleted(torrent))
			torrentRemove(torrent.hash); 
	}
}

function onTorrentsGetFinished(request) {
	if (failedRequest(request)) {
		if(onload_time < 5/* 5 times * 2 sec */)
		{
			stopRefresh();
			setTimeout("torrentsRefresh()", sdkCtl.refreshFreq);
			onload_time++;
			return;
		}
		showConnectionError();
		return;
	}
	onTorrentsRefreshFinished(request);
}

function onTorrentStopFinished(request) { torrentsRefresh(); }
function onTorrentStartFinished(request) { torrentsRefresh(); }
function onTorrentRemoveFinished() { 
	if (null == torrentToSelectAfterRemovalHash)
	{
		selectedTorrentHash = null;
		torrentsRefresh(); 
	}
	else
	{
		selectTorrent(torrentToSelectAfterRemovalHash);
	}
}
function onTorrentFileGetFinished(request) { torrentsRefresh(); }

function torrentFileGet(hash, file_id) {
	sdkCtl.torrentFileGet(hash, file_id, onTorrentFileGetFinished);
}
function torrentStop(hash) { sdkCtl.torrentStop(hash, onTorrentStopFinished); }
function torrentStart(hash) { sdkCtl.torrentStart(hash, onTorrentStartFinished); }
function torrentGetFiles(hash) { sdkCtl.torrentGetFiles(hash, onTorrentGetFilesFinished); }
function torrentsGet() { sdkCtl.torrentsGet(onTorrentsGetFinished); }
function torrentRemoveAsk(hash) {
	var ask = false;
	if (REMOVE_ASK_ALWAYS == removeMode) {
		ask = true;
	}
	else if (REMOVE_ASK_IF_INCOMPLETE == removeMode) {
		if (!torrentCompleted(torrentFromHash(hash)))
			ask = true;
	}
	if (ask) {
		torrentHashToRemove = hash;
		if (!torrentCompleted(torrentFromHash(hash))) {
			$("removeTorrentTxt").innerHTML = "Removing this torrent will delete the unfinished download.";
		} else {
			$("removeTorrentTxt").innerHTML = "Remove the torrent?";
		}
		showEl("removeTorrentAlert");
		stopRefresh();
	} else {
		torrentToSelectAfterRemovalHash = chooseTorrentToSelectAfterRemoval();
		torrentRemove(hash);
	}
}

function torrentRemoveYes() { 
	torrentToSelectAfterRemovalHash = chooseTorrentToSelectAfterRemoval();
	hideRemoveTorrentAlert(); 
	torrentRemove(torrentHashToRemove); 
}

function torrentRemove(hash) {
	var deleteData = false;
	var torrent = torrentFromHash(hash);
	if (torrent && !torrentCompleted(torrent))
		deleteData = true;
	sdkCtl.torrentRemove(hash, deleteData, onTorrentRemoveFinished); 
}
function torrentsRefresh() { torrentsGet(); }
function onTorrentAddUrlFinished() { /* do nothing */ }

function torrentAddUrl(url) { 
	sdkCtl.torrentAddUrl(url, true, onTorrentAddUrlFinished); 
	clearUploadUrl();
}
