﻿<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
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
	function myInit() {
		$("btPortDefaultTxt").innerHTML = "Default " + "&nbsp;" + "(" + defaultBtPort + ")";
		loadSettings(); 
	}
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

/* Note: if changed in settings file, must be equal to what is in settings file */
var defaultBtPort = 6881;

/* result of the last /api/settings-get request */
var settings = null;

/* Values set  by the user */
var enteredBtPort = null;
var enteredSeedRatio = null;
var enteredSeedTime = null;
var enteredMaxDlRate = null;
var enteredMaxUlRate = null;
var enteredMaxUlSeedRate = null;

/* assumes rate is integer, returns a rate scaled from the value stored on 
   the server to value shown in UI */
function rateToUI(rate) {
	if (-1 == rate) return rate;
	return rate / 1024;
}

/* assumes rate is txt, returns a rate scaled from the value given by the user
   in the ui to value stored on the server */
function rateFromUI(rate) {
	if ("-1" == rate) return -1;
	return parseFloat(rate) * 1024;
}

/* seed time is in seconds on the server by in UI it's entered in minutes */
/* convert server view of seed time to UI view */
function seedTimeToUI(timeInSecs) {
	return timeInSecs / 60;
}

/* convert UI view of seed time to server view */
function seedTimeFromUI(timeInMins) {
	return timeInMins * 60;
}

function rateFromField(fieldName) { 
	return rateFromUI(parseRateTxt($(fieldName).value)); 
}

function boolStrVal(val) {
	if (1 == val) return true;
	if (0 == val) return false;
	val = val.stripSpaces();
	val = val.toLowerCase();
	if (val == "true") return true;
	if (val == "1") return true;
	return false;
}

function updateErrorClassField(valid, prefix) {
	var fieldId = prefix + "Field";
	var errorElId = prefix + "Error";
	if (valid) {
		$(fieldId).className = "";
		hideEl(errorElId);
	} else {
		$(fieldId).className = "error";
		showEl(errorElId);
	}
}

function parseRateTxt(txt) {
	txt = txt.stripSpaces();
	txt = txt.toLowerCase();
	if ("unlimited" == txt) return "-1";
	return txt;
}

function isZero(txt){
	var i = parseInt(txt, 10);
	if (i==0) return true;
}

function isValidPositiveInt(txt) {
	if (true==isZero(txt)) return false;
	if (0 == txt.length) return false;
	for (var i = 0; i < txt.length; i++) {
		var c = txt.charAt(i)
		if (c < '0' || c > '9') return false;
	}
	return true;
}

function isRateValid(txt) {
	if ("unlimited" == txt) return true;
	if ("-1" == txt) return true;
	return isValidPositiveInt(txt);
}

function isBtPortValid(txt) {
	var BIND_PORT_MIN = 1025;
	var BIND_PORT_MAX = 65000;
	
	if (!isValidPositiveInt(txt)) return false;
	var port = parseFloat(txt);
	if (port <= BIND_PORT_MIN) return false;
	if (port >= BIND_PORT_MAX) return false;
	return true;
}

function isSeedRatioValid(txt) 
{
	var i = parseInt(txt, 10);
	if (i > 100) 
		return false;	 
	return isValidPositiveInt(txt); 
}
function isSeedTimeValid(txt) { return isValidPositiveInt(txt); }

function btPortValidate() {
	var txt = $("btPortField").value.stripSpaces();
	var valid = isBtPortValid(txt);
	updateErrorClassField(valid, "btPort");
	enteredBtPort = txt;
	return valid;
}

function maxDlRateValidate() {
	var txt = $("maxDlRateField").value.stripSpaces();
	var valid = isRateValid(txt);
	updateErrorClassField(valid, "maxDlRate");
	enteredMaxDlRate = txt;
	return valid;
}

function maxUlRateValidate() {
	var txt = $("maxUlRateField").value.stripSpaces();
	var valid = isRateValid(txt);
	updateErrorClassField(valid, "maxUlRate");
	enteredMaxUlRate = txt;
	return valid;
}

function maxUlSeedRateValidate() {
	var txt = $("maxUlSeedRateField").value.stripSpaces();
	var valid = isRateValid(txt);
	updateErrorClassField(valid, "maxUlSeedRate");
	enteredMaxUlSeedRate = txt;
	return valid;
}

function seedRatioValidate() {
	var txt = $("seedRatioField").value.stripSpaces();
	var valid = isSeedRatioValid(txt);
	updateErrorClassField(valid, "seedRatio");
	enteredSeedRatio = txt;
	return valid;
}

function seedTimeValidate() {
	var txt = $("seedTimeField").value.stripSpaces();
	var valid = isSeedTimeValid(txt);
	updateErrorClassField(valid, "seedTime");
	enteredSeedTime = txt;
	return valid;
}

/* Returns an array of (setting_name, setting_value) tuples for settings whose value
   have changed compared to settings returned by the server */
function getChangedSettings() {
	var changed = [];
	var el = null;
	var currentPort = parseFloat(settings.bind_port);
	var enteredPort = parseFloat($("btPortField").value);
	if ($("btPortCustom").checked) {
		if (enteredPort != currentPort) {
			el = ["bind_port", enteredPort.toString()];
			changed.push(el);
		}
	} else {
		if (currentPort != defaultBtPort) {
			el = ["bind_port", defaultBtPort.toString()];
			changed.push(el);
		}
	}

	var currentAutoBandMan = boolStrVal(settings.auto_bandwidth_management);

	var currentMaxDlRate = settings.max_dl_rate;
	var newMaxDlRate = rateFromField("maxDlRateField");

	var currentMaxUlRate = settings.max_ul_rate;
	var newMaxUlRate = rateFromField("maxUlRateField");

	var currentMaxUlSeedRate = settings.max_ul_rate_seed;
	var newMaxUlSeedRate = rateFromField("maxUlSeedRateField");

	if ($("autoBandMan").checked) {
		if (!currentAutoBandMan) {
			/* Set default values */
			el = ["auto_bandwidth_management", "1"]; changed.push(el);
			el = ["max_dl_rate", "-1"]; changed.push(el);
			el = ["max_ul_rate", "-1"]; changed.push(el);
			el = ["max_ul_rate_seed", "-1"]; changed.push(el);
		}
	} else {
		/* 'manual bandwidth management' radio button selected */
		if (currentAutoBandMan) {
			changed.push(["auto_bandwidth_management", "0"]);
		}

		if (currentMaxDlRate != newMaxDlRate) {
			changed.push(["max_dl_rate", newMaxDlRate.toString()]);
		}

		if (currentMaxUlRate != newMaxUlRate) {
			changed.push(["max_ul_rate", newMaxUlRate.toString()]);
		}

		if (currentMaxUlSeedRate != newMaxUlSeedRate) {
			changed.push(["max_ul_rate_seed", newMaxUlSeedRate.toString()]);
		}
	}

	var currentSeedRatio = settings.seed_ratio;
	var newSeedRatio = $("seedRatioField").value;

	var currentSeedTime = settings.seed_time;
	var newSeedTime = seedTimeFromUI($("seedTimeField").value);

	if ($("seedForever").checked) {
		if ("0" != currentSeedTime) {
			changed.push(["seed_time", 0]);
		}

		if ("0" != currentSeedRatio) {
			changed.push(["seed_ratio", 0]);
		}
	}
	
	if ($("seedRatio").checked) {
		if ("0" != currentSeedTime) {
			changed.push["seed_time", 0];
		}
		if (newSeedRatio != currentSeedRatio) {
			changed.push(["seed_ratio", newSeedRatio]);
		}
	}

	if ($("seedTime").checked) {
		if (newSeedTime != currentSeedTime) {
			changed.push(["seed_time", newSeedTime.toString()]);
		}
		if ("0" != currentSeedRatio) {
			changed.push(["seed_ratio", 0]);
		}
	}

	return changed;
}

function settingsChanged() {
	var changed = getChangedSettings();
	if (changed.length == 0) return false;
	return true;
}

function enteredSettingsValid() {
	if ($("btPortCustom").checked) {
		var txt = $("btPortField").value.stripSpaces();
		if (!isBtPortValid(txt)) { return false; }
	}
	if ($("manualBandMan").checked) {
		if (!isRateValid($("maxDlRateField").value)) { return false; }
		if (!isRateValid($("maxUlRateField").value)) { return false; }
		if (!isRateValid($("maxUlSeedRateField").value)) { return false; }
	}
	if ($("seedTime").checked) {
		if (!isSeedTimeValid($("seedTimeField").value)) { return false; }
	}
	if ($("seedRatio").checked) {
		if (!isSeedRatioValid($("seedRatioField").value)) { return false; }
	}
	return true;
}

function disableApplyButton() {
    $("apply").disabled = true;
    $("apply").className = "disabled";
}

function enableApplyButton() {
    $("apply").disabled = false;
    $("apply").className = "";
}

function setApplyButtonState() {
	if (!enteredSettingsValid() || !settingsChanged()) {
		disableApplyButton();
		return;
	}
	enableApplyButton();
}

function btPortDefaultSelected() {
	$("btPortDefault").checked = true;
	$("btPortField").value = "";
	updateErrorClassField(true, "btPort");
	setApplyButtonState();
}

function btPortCustomSelected() {
	$("btPortCustom").checked = true;
	var val = enteredBtPort;
	if (null == enteredBtPort)
		val = settings.bind_port;
	$("btPortField").value = val;
	btPortValidate();
	setApplyButtonState();
}

function autoBandManSelected() {
	$("autoBandMan").checked = true;
	$("maxDlRateField").value = "";
	$("maxUlRateField").value = "";
	$("maxUlSeedRateField").value = "";
	updateErrorClassField(true, "maxDlRate");
	updateErrorClassField(true, "maxUlRate");
	updateErrorClassField(true, "maxUlSeedRate");
	setApplyButtonState();
}

function manualBandManSelected() {
	$("manualBandMan").checked = true;
	var val = enteredMaxDlRate;
	if (null == val)
		val = rateToUI(settings.max_dl_rate);
	$("maxDlRateField").value = val;
	val = enteredMaxUlRate;
	if (null == val)
		val = rateToUI(settings.max_ul_rate);
	$("maxUlRateField").value = val;
	val = enteredMaxUlSeedRate;
	if (null == val)
		val = rateToUI(settings.max_ul_rate_seed);
	$("maxUlSeedRateField").value = val;
	maxDlRateValidate();
	maxUlRateValidate();
	maxUlSeedRateValidate();
	setApplyButtonState();
}

function seedForeverSelected() {
	$("seedForever").checked = true;
	$("seedRatioField").value = "";
	$("seedTimeField").value = "";
	updateErrorClassField(true, "seedRatio");
	updateErrorClassField(true, "seedTime");
	setApplyButtonState();
}

function seedRatioSelected() {
	$("seedRatio").checked = true;
	$("seedTimeField").value = "";
	var val = enteredSeedRatio;
	if (null == val) {
		val = settings.seed_ratio;
		if ("0" == val)
			val = "100"; // 100%
	}
	$("seedRatioField").value = val;
	updateErrorClassField(true, "seedTime");
	seedRatioValidate();
	setApplyButtonState();
}

function seedTimeSelected() {
	$("seedTime").checked = true;
	$("seedRatioField").value = "";
	var val = enteredSeedTime;
	if (null == val) {
		val = seedTimeToUI(settings.seed_time);
		if ("0" == val)
			val = "60"; // 60 minutes
	}
	$("seedTimeField").value = val;
	updateErrorClassField(true, "seedRatio");
	seedTimeValidate();
	setApplyButtonState();
}

function settingsToForm() {
	enteredBtPort = null;
	enteredSeedRatio = null;
	enteredSeedTime = null;
	enteredMaxDlRate = null;
	enteredMaxUlRate = null;
	enteredMaxUlSeedRate = null;

	var auto_bw = false;
	var btPort = parseFloat(settings.bind_port);
	if (btPort == defaultBtPort)
		btPortDefaultSelected();
	else
		btPortCustomSelected();

	if (boolStrVal(settings.auto_bandwidth_management)) {
		autoBandManSelected();
	} else {
		manualBandManSelected();
	}

	var seedRatio = parseFloat(settings.seed_ratio);
	var seedTime = parseFloat(settings.seed_time);
	if (0 == seedRatio && 0 == seedTime) {
		seedForeverSelected();
	} else if (0 != seedRatio) {
		seedRatioSelected();
	} else {
		seedTimeSelected();
	}
}

function onLoadSettingsFinished(request) {
	if (failedRequest(request)) {
		showConnectionError();
		return;
	}
	hideEl("msgAlert");
	var rsp = request.responseText;
	var json = evalJson(rsp);
	settings = json.settings;
	settingsToForm();
	hideEl("inProgress");
	showEl("container");
	setApplyButtonState();
}

function btPortDefaultClick() { btPortDefaultSelected();}
function btPortCustomClick() { btPortCustomSelected(); }
function autoBandManClick() { autoBandManSelected(); }
function manualBandManClick() { manualBandManSelected(); }
function seedForeverClick() { seedForeverSelected(); }
function seedRatioClick() { seedRatioSelected(); }
function seedTimeClick() { seedTimeSelected(); }

function btPortFieldFocus() { btPortCustomSelected(); }
function maxDlRateFieldFocus() { manualBandManSelected(); }
function maxUlRateFieldFocus() { manualBandManSelected(); }
function maxUlSeedRateFieldFocus() { manualBandManSelected(); }
function seedRatioFieldFocus() { seedRatioSelected(); }
function seedTimeFieldFocus() { seedTimeSelected(); }

function btPortFieldChange() { btPortValidate(); setApplyButtonState(); }
function btPortFieldKeyPress() { setTimeout(btPortFieldChange, 0); return true; }

function maxDlRateFieldChange() { maxDlRateValidate(); setApplyButtonState(); }
function maxDlRateFieldKeyPress() { setTimeout(maxDlRateFieldChange, 0); return true; }

function maxUlRateFieldChange() { maxUlRateValidate(); setApplyButtonState(); }
function maxUlRateFieldKeyPress() { setTimeout(maxUlRateFieldChange, 0); return true; }

function maxUlSeedRateFieldChange() { maxUlSeedRateValidate(); setApplyButtonState(); }
function maxUlSeedRateFieldKeyPress() { setTimeout(maxUlSeedRateFieldChange, 0); return true; }

function seedRatioFieldChange() { seedRatioValidate(); setApplyButtonState(); }
function seedRatioFieldKeyPress() { setTimeout(seedRatioFieldChange, 0); return true; }

function seedTimeFieldChange() { seedTimeValidate(); setApplyButtonState(); }
function seedTimeFieldKeyPress() { setTimeout(seedTimeFieldChange, 0); return true; }

function allSettingsValid() {
	var valid = true;
	if ($("btPortCustom").checked) {
		valid = btPortValidate();
		if (!valid) return false;
	}
	if ($("manualBandMan").checked) {
		valid = maxDlRateValidate();
		if (!valid) return false;
		valid = maxUlRateValidate();
		if (!valid) return false;
		valid = maxUlSeedRateValidate();
		if (!valid) return false;
	}

	if ($("seedRatio").checked) {
		valid = seedRatioValidate();
		if (!valid) return false;
	}

	if ($("seedTime").checked) {
		valid = seedTimeValidate();
		if (!valid) return false;
	}
	return true;
}

function settingsSubmit() {
	var valid = allSettingsValid();
	if (!valid) {
		showMsgAlert("Some settings are not valid.", "Okay");
		disableApplyButton();
		return false;
	}
	var changed_settings = getChangedSettings();
	if (0 == changed_settings.length) {
		showMsgAlert("No settings have changed.", "Okay");
		return false;
	}
	/* for debugging: */
	/* alert(sdkCtl.appSettingsSetUrl(changed_settings)); */
	sdkCtl.appSettingsSet(changed_settings, onSettingsSetFinished);
	return false;
}

function onSettingsSetFinished(request) {
	/* showMsgAlert("Your settings changes have been applied.", "Okay", "nas_bt_index.php"); */
	showMsgAlert("Your settings changes have been applied.", "Okay", "nas_bt_settings.php");
}

function loadSettings() { 
	sdkCtl.appSettingsGet(onLoadSettingsFinished); 
}

function showMsgAlert(txt, btnText, url) {
	$("msgAlertTxt").innerHTML = txt;
	$("msgAlertBtnTxt").innerHTML = btnText;
	if (null != url)
		$("msgAlertBtnTxt").href = url;
	showEl("msgAlert");
}

function showConnectionError() {
	showMsgAlert("Connection to server failed.", "Retry");
}

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
<div id="inProgress">
	<center>Please wait... Downloading settings.</center>
</div>

<div id="container" style="display:none;">
    <div id="settings">
        <div id="nav-stats">
            <ul id="nav">
                <li><a href="./nas_bt_index.php">Downloads</a></li>
                <li class="last">Settings</li>
                <!--<li class="last"><a href="http://SDK_LICENCEE_SUPPORT_PAGE">Support</a></li>-->
            </ul>
        </div>
        <h1>Settings</h1>
        <div id="edit-settings" class="cl">
            <form onsubmit="return settingsSubmit();">
                <p id="help-link"><a href="#settings-help">Settings Help</a></p>
                
                <fieldset id="port">
                    <legend>Port Settings:</legend>
                    <h2>Port Settings:</h2>
                    <ol class="set">
                        <li>
                            <input type="radio" name="ports" id="btPortDefault" onclick="btPortDefaultClick();"/>
                            <label for="btPortDefault" id="btPortDefaultTxt">Default &nbsp;(6881)</label>
                        </li>
                        <li>
                            <input type="radio" name="ports" id="btPortCustom" onclick="btPortCustomClick();"/>
                            <label for="btPortCustom">Custom</label>
                            <ol>
                                <li>
                                    <label for="btPortField">Incoming connections port:</label>
                                    <input type="text" id="btPortField" onkeypress="return btPortFieldKeyPress();" onfocus="btPortFieldFocus();"/>
                                    <p id="btPortError" style="display:none;">Value must be a number between 1025 and 65000.</p>
                                </li>
                            </ol>
                        </li>
                    </ol>
                </fieldset>

                <fieldset id="bandwidth">
                    <legend>Bandwidth Management:</legend>
                    <h2>Bandwidth Management:</h2>
                    <ol class="set">
                        <li>
                            <input type="radio" name="bandMan" id="autoBandMan" onclick="autoBandManClick();"/>
                            <label for="autoBandMan">Automatic</label>
                        </li>
                        <li>
                            <input type="radio" name="bandMan" id="manualBandMan"  onclick="manualBandManClick();"/>
                            <label for="manualBandMan">Manual</label>
                            <ol>
                                <li>
                                    <label for="maxDlRateField">Maximum download rate (kB/s):</label>
                                    <input type="text" id="maxDlRateField"  onfocus="maxDlRateFieldFocus();" onkeypress="return maxDlRateFieldKeyPress();" />
                                    <span class="dflt">default: -1 (unlimited)</span>
                                    <p id="maxDlRateError" style="display:none;">Value must be a positive integer or -1 for unlimited</p>
                                </li>
                                <li>
                                    <label for="maxUpRateField">Maximum upload rate (kB/s):</label>
                                    <input type="text" id="maxUlRateField"  onfocus="maxUlRateFieldFocus();" onkeypress="return maxUlRateFieldKeyPress();" />
                                    <span class="dflt">default: -1 (unlimited)</span>
                                    <p id="maxUlRateError" style="display:none;">Value must be a positive integer or -1 for unlimited</p>
                                </li>
                                <li>
                                    <label for="maxUlSeedRateField">Max. upload rate when seeding (kB/s)</label>
                                    <input type="text" id="maxUlSeedRateField" onfocus="maxUlSeedRateFieldFocus();" onkeypress="return maxUlSeedRateFieldKeyPress();"/>
                                    <p id="maxUlSeedRateError" style="display:none;">Value must be a positive integer or -1 for unlimited</p>
                                    <span class="dflt">default: -1 (unlimited)</span>
                                </li>
                            </ol>
                        </li>
                    </ol>
                </fieldset>
                <fieldset id="seeding">
                    <legend>Seeding:</legend>
                    <h2>Seeding:</h2>
                    <ol class="set">
                        <li>
                            <input type="radio" name="seedOption" id="seedForever" onclick="seedForeverClick();"/>
                            <label for="seedForever">Seed until removed</label>
                        </li>
                        <li>
                            <input type="radio" name="seedOption" id="seedRatio" onclick="seedRatioClick();"/>
                            <label for="seedRatio">Stop seeding when ratio reaches</label>
                            <input type="text" name="ratio" id="seedRatioField" onfocus="seedRatioFieldFocus();" onkeypress="return seedRatioFieldKeyPress();" title="Ratio limit for seeding" />
                            <span>%</span>
                            <p id="seedRatioError" style="display:none;">Value must be a number between 1 and 100</p>
                        </li>
                        <li>
                            <input type="radio" name="seedOption" id="seedTime" onclick="seedTimeClick();"/>
                            <label for="seedTime">Stop seeding after</label>
                            <input type="text" name="seedTimeField" id="seedTimeField" onfocus="seedTimeFieldFocus();" onkeypress="return seedTimeFieldKeyPress();" title="Minutes to seed for" />
                            <span>minutes</span>
                            <p id="seedTimeError" style="display:none;">Value must be a positive integer</p>
                        </li>
                    </ol>
                </fieldset>
                <button type="submit" id="apply">Apply</button>
                <button type="reset" id="cancel" onClick="document.location.href='nas_bt_index.php'">Cancel</button>
            </form>
        </div>
        <div id="settings-help">
            <h2>Settings Help</h2>
            <div id="psHelp">
                <h3>Help with Port Settings</h3>
                <p>This setting is used to change the port where BitTorrent listens for incoming connections.  If you are behind a router with network address translation (NAT), BitTorrent will attempt to configure your router's port mappings via UPnP or NAT-PMP.  If your router is not capable of mapping ports automatically, you may need to configure port forwarding manually on your router.  If your device has a public IP address (i.e. is not subject to NAT), you may need to change this setting if the default port is blocked by a firewall.</p>
                <p class="linkBack"><a href="#port">Back to Port Settings</a></p>
            </div>
            <div id="bmHelp">
                <h3>Help with Bandwidth Management</h3>
                <p>When set to "Automatic", BitTorrent automatically moderates its use of your Internet connection to avoid disrupting other applications and users.  To impose a strict cap on BitTorrent's use of your connection, you may manually set the maximum rates at which BitTorrent will download, upload, and seed.</p>
                <p class="linkBack"><a href="#bandwidth">Back to Bandwidth Management</a></p>
            </div>
            <div id="sHelp">
                <h3>Help with Seeding</h3>
                <p>By default BitTorrent will seed a fully-downloaded torrent until you remove it.  There are two alternative seeding policies that you may set.  Seeding can be stopped automatically when the ratio of uploaded
to download bytes reaches a threshold that you set.  Or, seeding can be stopped automatically after a set number of minutes.</p>
                <p class="linkBack"><a href="#seeding">Back to Seeding</a></p>
            </div>
        </div>
    </div>
</div>

<div id="msgAlert" style="display:none;">
	<div class="bg"></div>
	<div class="message">
	    <p id="msgAlertTxt"></p>
	    <a id="msgAlertBtnTxt" class="oButton" href="javascript:loadSettings();">Retry</a>
	</div>
</div>

</body>
</html>
