<div class="box">
<a name="admin"><h2>Admin</h2></a>
<table border=0 cellspacing=0 cellpadding=0>

<tr>
	<td height=20>
		
		<p>
			<strong><em>Administrator Login Name</em></strong> -
			Enter the name that will be used to login to the router with Admin access.
		</p>
		<p>
			<strong><em>Administrator password</em></strong> -
			Enter and confirm the password that the <strong>admin </strong> account will use to access the router's management interface.
		</p>
		<p>
			<strong>Remote Management</strong><br>
			Remote Management allows the device to be configured through the WAN (Wide Area Network) port
			from the Internet using a web browser. A username and password is still required to access the
			router's management interface.<br>
			<strong><em>IP Allowed to Access</em></strong> -
			This option allows users to specify a particular IP address from the Internet to be allowed to access the router
			remotely. This field is 0.0.0.0 by default which means any IP address from the Internet can access the router
			remotely once remote management is enabled.<br>
			<strong><em>Port</em></strong> - Select the port which will be used to access the <?query("/sys/modelname");?>.
		</p>
		<p>
			<strong><em>Example: </em></strong><br>
			<a href="http://192.168.0.1/help_tools.html">http://x.x.x.x:8080 </a> whereas x.x.x.x is the
			WAN IP address of the <?query("/sys/modelname");?> and 8080 is the port used for the Web-Management interface.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="time"><h2>Time</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=33>
		<p>
			The Time Configuration settings are used by the router for synchronizing scheduled services and
			system logging activities. You will need to set the time zone corresponding to your location.
			The time can be set manually or the device can connect to a NTP (Network Time Protocol) server to
			retrieve the time. You may also set Daylight Saving Time dates, which will automatically adjust the system time on the specified dates.
		</p>
		<p>
			<strong><em>Time Zone</em></strong> - Select the Time Zone for the region you are in.<br>
			<strong><em>Daylight Saving</em></strong> -
			If the region you are in observes Daylight Savings Time, enable this option.<br>
			<strong><em>Automatic Time Configuration</em></strong> -
			Select a D-Link time server which you would like the <?query("/sys/modelname");?> to synchronize
			its time with. The interval at which the <?query("/sys/modelname");?> will
			communicate with the D-Link NTP server is set to 7 days.<br>
			<strong><em>Set the Date and Time Manually</em></strong> -
			Select this option if you would like to specify the time manually. You must specify the Year,
			Month, Day, Hour, Minute, and Second, or you can click the Copy Your Computer's Time Settings
			button to copy the system time from the computer being used to access the management interface.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="log_settings"><h2>Log Settings</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			You can save the log file to a local drive which can later be used to send to a network
			administrator for troubleshooting.<br>
			<strong><em>Save</em></strong> - Click this button to save the log entries to a text file.<br>
			<strong><em>Log Type</em></strong> - Select the type of information you would like the <?query("/sys/modelname");?> to log.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="email_settings"><h2>Email Settings</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			The Email Settings allows you to send the Device Log file to a specified email address.<br>
			<br>
			<strong><em>From Email Address</em></strong> - 
			The email address which the email will be sent from.  Most modern SMTP services require this to be a valid email address and will carry out tests to see if it is genuine.<br>
			<strong><em>To Email Address</em></strong> - 
			The email address that the Device Log file will be sent to.  The log file will be seen by the person accessing this email account.<br>
			<strong><em>Email Subject</em></strong> - 
			The title of the email.<br>
			<strong><em>SMTP Server Address</em></strong> - 
			The IP address or Domain Name of the mail server that will forward the device log file to the required email account.<br>
			<strong><em>SMTP Server Port</em></strong> - 
			The port that the mail server will use.<br>
			<strong><em>Enable Authentication</em></strong> - 
			For security reasons some SMTP servers check the account name and password to confirm that the email it is processing is from one of its clients.<br>
			<strong><em>Account Name</em></strong> - 
			The account name used for authentication with the SMTP Server.<br>
			<strong><em>Password</em></strong> - 
			The password of the account used for authentication with the SMTP Server.<br>
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="system"><h2>System</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=40>
		The current system settings can be saved as a file onto the local hard drive.
		The saved file or any other saved setting file created by device can be uploaded into the unit.
		To reload a system settings file, click on <strong>Browse</strong> to search the local hard drive
		for the file to be used. The device can also be reset back to factory default settings by clicking
		on <strong>Restore Device</strong>. Use the restore feature only if necessary. This will erase previously
		save settings for the unit. Make sure to save your system settings before carrying out a factory restore.<br>
		<strong><em>Save</em></strong> - Click this button to save the configuration file from the router.<br>
		<strong><em>Browse</em></strong> -
		Click Browse to locate a saved configuration file and then click to Load and apply the
		saved settings to the router.<br>
		<strong><em>Restore Device</em></strong> -
		Click this button to restore the router to its factory default settings.
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="firmware"><h2>Firmware</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=51>
		You can upgrade the firmware of the device using this tool. Make sure that the firmware
		you want to use is saved on the local hard drive of the computer. Click on <strong>Browse </strong>
		to search the local hard drive for the firmware to be used for the update. Upgrading the firmware
		will not change any of your system settings but it is recommended that you save your system settings
		before carrying out a firmware upgrade. Please check the D-Link <a href=<?query("/sys/supporturl");?>>support site</a>
		for firmware updates or you can click on the <strong>Check Now</strong> button to have the router check the
		new firmware automatically.
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="dynamic_dns"><h2>Dynamic DNS</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=2>
		<p>
			Dynamic DNS (Domain Name Service) is a method of keeping a domain name linked to a
			changing (dynamic) IP address. With most Cable and DSL connections, you are assigned
			a dynamic IP address and that address is used only for the duration of that specific
			connection. With the <?query("/sys/modelname");?>, you can setup your DDNS service and
			the <?query("/sys/modelname");?> will automatically update your DDNS server every time
			it receives a new WAN IP address.<br>
			<strong><em>Server Address</em></strong> - Choose your DDNS provider from the drop down menu.<br>
			<strong><em>Host Name</em></strong> - Enter the Host Name that you registered with your DDNS service provider.<br>
			<strong><em>Username</em></strong> - Enter the username for your DDNS account.<br>
			<strong><em>Password</em></strong> - Enter the password for your DDNS account.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="system_check"><h2>System Check</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>
			This tool can be used to verify physical connectivity on both the LAN and Internet (WAN) interfaces.
			This is an advanced feature that integrates a LAN cable tester on every Ethernet port on the router.
			Through the graphical user interface (GUI), a Cable Test can be carried out to remotely diagnose and report
			cable faults such as open circuits, short circuits, swapped pairs, and impedance mismatch. This feature significantly reduces
			service calls and returns by allowing users to easily troubleshoot their cable connections.
		</p>
		<p>
			<strong>Ping Test</strong><br>
			This useful diagnostic utility can be used to check if a computer is on the Internet.
			It sends ping packets and listens for replies from the specific host. Enter in a host name or the IP
			address that you want to ping (Packet Internet Groper) and click <strong>Ping </strong>. The status of
			your Ping attempt will be displayed in the Ping Result box.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="schedules"><h2>Schedules</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td>
		<p>	
			This page is used to configure global schedules for the router. Once defined,
			these schedules can later be applied to the features of the router that support scheduling.<br>
			<strong><em>Name</em></strong> - The name of the schedule being defined.<br>
			<strong><em>Day(s)</em></strong> -
			Select a day, range of days, or select the All Week checkbox to have this schedule .apply every day.<br>
			<strong><em>All Day - 24 hrs</em></strong> -
			Check this box to have the schedule active the entire 24 hours on the days specified.<br>
			<strong><em>Start Time</em></strong> -
			Select the time at which you would like the schedule being defined to become active.<br>
			<strong><em>End Time</em></strong> -
			Select the time at which you would like the schedule being defined to become inactive.<br>
			<strong><em>Schedule Rules List</em></strong> -
			This displays all the schedules that have been defined.
		</p>
	</td>
</tr>
</table>
</div>

						   