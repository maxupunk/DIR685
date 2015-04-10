<div class="box">
<a name="disk_management"><h2>Disk Management</h2></a>
	<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			The Disk Management page contains information and settings for the local hard drive that is currently installed in the device.<br>
			<br>
			<strong><em>Hard Disk Information</em></strong> -
			This contains details about the hard drive installed in the device.<br>
			<strong><em>Format Setting</em></strong> -
			This button allows you to format the hard drive that is currently installed in the device.<br>
			WARNING: This action will wipe the hard drive clean. All data on the hard drive will be lost!<br>
			<strong><em>Hard Drive Setting</em></strong> -
			Once this setting is enabled the hard drive will go into standby mode after the amount of minutes specified, if no data has been written to or read from the hard drive, to reduce power consumption.<br>
		</p>
	</td>
</tr>
 </table>
</div>

<div class="box">
<a name="users_groups"><h2>Users/Groups</h2></a>
	<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=228>
		<p>
			<strong>Users</strong><br>
			Users can be created here. These accounts can be added to rules in the Network Access and FTP Server sections. Each user created will also have access to the Scheduled Download section.
		</p>
		<p>
			<strong><em>User name</em></strong> -
			Enter user name.<br>
			<strong><em>Password</em></strong> -
			Enter password.<br>
			<strong><em>Confirm Password</em></strong> -
			Enter password again. Click 'Save Settings' to add the user.<br>
			<br>
			The created users will appear in a list near the bottom of this page along with their assigned group (if any). User's passwords can be edited by clicking on the 'notepad with pencil' icon or users can be deleted by clicking on the 'trashcan' icon to the right of the rule.			
		</p>
		<p>
			<strong>Groups</strong><br>
			Groups can be created here. Once a group has been created, it will be available in the Group selection on the Users page.<br>
			<br>
			The created groups will appear in a list near the bottom of this page. Users within these groups will also be displayed.<br>
		</p>
	</td>
</tr>
 </table>
</div>
 
 
<div class="box">
<a name="storage_access"><h2>Storage Access</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=64> 
		<p>
			<strong><em>Category</em></strong> -
			Select either User or Group.<br>
			<strong><em>User or Group</em></strong> -
			Select a user or group from the pull down list. Select 'All Accounts' if you wish to create a rule that applies to all users.<br>
			<strong><em>Folder</em></strong> -
			Click "Browse" to select a folder. This folder must be located on the internal drives.<br>
			<strong><em>Permission</em></strong> -
			Assign "Read Only" or "Read / Write" permissions to the selected folder for the selected user or group.<br>
			<strong><em>Oplocks</em></strong> -
			Opportunistic locks (oplocks) are a characteristic of the LAN Manager networking protocol implemented in the 32-Bit 
			Windows family of operating system environments. Oplocks are guarantees made by a server for a shared logical volume 
			to its clients. These guarantees inform the Client that a file's content will not be allowed to be changed by the 
			server, or if some change is imminent, the client will be notified before the change is allowed to proceed.
			Oplocks are designed to increase network performance when it comes to network file sharing however when using 
			file-based database applications it is recommended to set the share oplocks to <strong>No(off)</strong>. <br>
			<br>
			What operating systems are affected by Oplocks?<br>
			<br>
			By default Vista has Oplocks enabled and can not be disabled. If you are having network performance issues with applications sharing files from the DIR-685 you may try to improve performance by setting Oplocks to <strong>No(off)</strong>.<br>
			<strong><em>Map Archive</em></strong> -
			When enabled, the file attribute--"Archive" will be copied as the file is being stored on the DIR-685. Certain backup softwares attach this attribute to files that are being stored as backups.<br>
			<strong><em>Comment</em></strong> -
			Additional comments about this rule. This is optional and has no functional effect.<br>
			<br>
			Click 'Save Settings' to save the rule. All saved rules will appear in the list near the bottom of this page. Rules can be edited or deleted by clicking on the 'notepad with pencil' or 'trashcan' icon to the right of the rule.<br>
		</p>
 </tr>
</table>
</div>
 
 
<div class="box">
<a name="ftp_server"><h2>Ftp Server</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=99>
		<p>
			<strong><em>Category</em></strong> -
			Select either user or group.<br>
			<strong><em>User</em></strong> -
			Select a user or group from the pull down list. Select 'All Accounts' if you wish to create a rule that applies to everyone. Anonymous will always be listed as a user.<br>
			<strong><em>Folder</em></strong> -
			Click "Browse" to select a folder and assign this folder to the selected user. This folder must be located on the internal drives. If you wish to assign access to the root of all drives simultaneously, put a check in the 'root' box.<br>
			<strong><em>Permission</em></strong> -
			Assign "Read Only" or "Read / Write" permissions to the selected folder for the selected user or group.
			Click 'Add' to add the rule to the list. All saved rules will appear in the list near the bottom of this page. Rules can be edited or deleted by clicking on the 'notepad with pencil' or 'trashcan' icons to the right of the rule.<br>
			<strong><em>Max User</em></strong> -
			Enter the maximum number of users that will be allowed to access the FTP server at one time. The default value is 10.<br>
			<strong><em>Idle Time</em></strong> -
			The FTP server will log a user out if he exceeds the specified idle time.<br>
			<strong><em>Port</em></strong> -
			If you wish to change the port that the FTP server uses, enter in the new number here. This is an advanced setting and a change can cause complications when behind a router. It is recommended to leave this at the default of 21 unless you have experience with changing the FTP port.<br>
			<strong><em>Flow Control</em></strong> -
			This function will adjust the data flow through the FTP server. If you set a limit here, users may download from the FTP server at a slower speed, however, you will conserve local bandwidth.<br>
			<strong><em>Client Language</em></strong> -
			Most standard FTP clients like Windows FTP, only support Western European codepage when transferring files. Northern European, Central European, Traditional and Simplified Chinese as well as Cyrillic codepage support has been added for non standard FTP clients that are capable of supporting these character sets.<br>
			<br>
			Click 'Save Settings' when finished.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="upnp_av_server"><h2>UPnP AV Server</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=44>
		<p>
			The DIR-685 has a built-in UPnPAV media server that can be used with UPnP AV compatible media players.<br>
			<br>
			<strong><em>UPnP AV Server</em></strong> -
			Enable or Disable the UPnP AV Server.<br>
			<strong><em>Folder</em></strong> -
			Click 'Browse' to locate the root folder of your media files (music, photos, and video). Root can be chosen if you want to have access to all content on the DIR-685.<br>
			<strong><em>Auto Refresh</em></strong> -
			Configure auto refresh to automatically update your shared UPNP AV data every 5, 15 or 30 minutes or from 1,2,6,12 or 24hour intervals.<br>
			<br>
			Click 'Save Settings' when finished.<br>
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="itunes_server"><h2>iTunes Server</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			The iTunes server will allow iTunes software to automatically detect and play music from the DIR-685.<br>
			<br>
			<strong><em>iTunes Server</em></strong> -
			Enable or Disable the iTunes Server.<br>
			<strong><em>Folder</em></strong> -
			Uncheck root, then click 'Browse' to locate the folder which contains your music files. Root can be chosen if you want to have access to all folders of the DIR-685.<br>
			<strong><em>Auto Refresh</em></strong> -
			Configure auto refresh to automatically update your shared iTunes Library data every 5, 15 or 30 minutes or from 1,2,6,12 or 24hour intervals.<br>
			<br>
			Click 'Save Settings' when finished.<br>
		</p>
</td>
</tr>
</table>
</div>

<div class="box">
<a name="bt_download_manager"><h2>BT Download Manager</h2></a>
	<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			The BT Download Manager page contains settings to set up your device so that Bit Torrent files can be downloaded from the Internet, without having to turn on your PC.<br>
			<br>
			<strong><em>BT Setting</em></strong> -
			This allows you to turn on/off the BT Download Manager service. The directory path allows you to indicate which directory/folder you would like to save your downloaded files to.  All downloads will be stored in the indicated directory, with all completed items stored in a directory named "completed" and all on-going items stored in a directory named "incomplete". File organization for each download will remain exactly the same as the original downloaded files.<br>
			<strong><em>Torrent Downloads</em></strong> -
			In the BT Download Manager screen you are allowed to choose whether to add new download items through a URL or from an individual BT seed file.<br>
			All items that are downloading will be listed at the bottom of the window, showing one download per row, so you can clearly view and control each item that is downloading.<br>
			<strong><em>Table of downloading items</em></strong> -
			For each item that is downloading, click the "more details" link to view further information about the current downloads.<br>
			<strong><em>Stop</em></strong> -
			Users can use this button to stop/halt the download process, allowing other items that are downloading to have more bandwidth.<br>
			<strong><em>Remove</em></strong> -
			Users can use the button on the right-hand side of each item that is downloading to cancel/delete the item being downloaded, if a mistake has been made.<br>
			<br>
			If the deleted item has already completed, only the entry will be deleted, but the files that have already been downloaded will be kept under the "completed" directory.<br>
			<strong><em>Remove Completed</em></strong> -
			This button at the top right corner of the downloading item table allows users to remove all the finished download items from the table, without deleting the downloaded files.<br>			
		</p>
	</td>
</tr>
 </table>
</div>
