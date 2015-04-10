<div class="box">
<a name="port_forwarding"><h2>Port Forwarding</h2></a>
	<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=228>
		<p>
			The Advanced Port Forwarding option gives Internet users access to services on your LAN. This
 feature is useful for hosting online services such as FTP, Web or game servers. For each entry,
 you define a public port on your router for redirection to an internal LAN IP Address and LAN port.
		</p>
		<p>
			Advanced Port Forwarding Parameters<br>
			<strong><em>Name</em></strong> -
			Assign a meaningful name to the virtual server, for example Web Server. Several well-known types of virtual
			server are available from the &quot;Application Name&quot; drop-down list. Selecting one of these entries
			fills some of the remaining parameters with standard values for that type of server.<br>
			<strong><em>IP Address </em></strong> -
			The IP address of the system on your internal network that will provide the virtual service, for example
 192.168.0.50. You can select a computer from the list of DHCP clients in the &quot;Computer Name&quot;
			drop-down menu, or you can manually enter the IP address of the server computer.<br>
			<strong><em>Application Name </em></strong> -
			A list of pre-defined popular applications that users can choose from for faster configuration.<br>
			<strong><em>Computer Name </em></strong> - A list of DHCP clients.<br>
			<strong><em>Traffic Type</em></strong> -
			Select the protocol used by the service. The common choices -- UDP, TCP and both UDP and TCP -- can
			be selected from the drop-down menu.<br>
			<strong><em>Private Port</em></strong> -
			The port that will be used on your internal network.<br>
			<strong><em>Public Port</em></strong> -
			The port that will be accessed from the Internet.<br>
		</p>
	</td>
</tr>
 </table>
 </div>
 
 
<div class="box">
<a name="application_rules"><h2>Application Rules</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=64> 
Some applications require multiple connections, such as Internet gaming, video conferencing, Internet telephony and others. These applications have difficulties working through NAT (Network Address Translation). If you need to run applications that require multiple connections, specify the port normally associated with an application in the &quot;Trigger Port&quot; field, select the protocol type as TCP (Transmission Control Protocol) or UDP (User Datagram Protocol), then enter the public ports associated with the trigger port in the Firewall Port field to open them for inbound traffic. There are already defined well-known applications in the Application Name drop-down menu. <br>

<strong><em>Name </em></strong> - This is the name referencing the application. <br>
<strong><em>Trigger Port </em></strong>- This is the port used to trigger the application. It can be either a single port or a range of ports. <br>
<strong><em>Traffic Type </em></strong> - This is the protocol used to trigger the application. <br>
<strong><em>Firewall Port </em></strong> - This is the port number on the WAN side that will be used to access the application. You may define a single port or a range of ports. You can use a comma to add multiple ports or port ranges. <br>
<strong><em>Traffic Type </em></strong> - This is the protocol used for the application. </td>

 </tr>
 </table>
 </div>
 
 
<div class="box">
<a name="qos_engine"><h2>QoS Engine</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
<td height=64>
		<p>
			This Smart QoS improves your VoIP voice quality or streaming by ensuring that your VoIP or streaming traffic 
			is prioritized over other network traffic, such as FTP or Web. For best performance, please tick the &quot;lag 
			eliminated&quot;	option to automatically set the priority for your applications.<br>
		</p>
</td>
</tr>
</table>
</div>
 
 
<div class="box">
<a name="access_control"><h2>Network Filter</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=99>
		<p>
			Filters are used to deny or allow LAN computers from accessing the Internet and also your network.
			Within your network, the unit can be setup to allow or deny Internet access to computers using their MAC addresses.
		</p>
		<p>
			<strong>MAC Filters</strong><br>
			Use MAC Filters to deny computers within the local area network from accessing the Internet.
			You can either manually add a MAC address or select the MAC address from the list of clients
			that are currently connected to the unit.<br>
			Select &quot;Turn MAC Filtering ON and ALLOW computers with MAC address listed below to access
			the network&quot; if you only want selected computers to have network access and all other computers
	not to have network access.<br>
			Select &quot;Turn MAC Filtering ON and DENY computers with MAC addresses listed below to access the
			network&quot; if you want all computers to have network access except those computers in the list.<br>
			<strong><em>MAC Address</em></strong> -
			The MAC address of the network device to be added to the MAC Filter List.<br>
			<strong><em>DHCP Client List</em></strong> -
			DHCP clients will have their hostname listed in the Computer Name drop-down menu. You can select
			the client computer you want to add to the MAC Filter List and click the arrow button. This will
			automatically add that computer's MAC address to the appropriate field.
		</p>
		<p>
			Users can use the <strong>Always</strong> drop-down menu to select a previously defined schedule
			or click the <strong>Add New</strong> button to add a new schedule.
		</p>
		<p>
			The check box is used to enable or disable a particular entry.
		</p>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="parental_control"><h2>Website Filter</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=44>
		<p>
			Along with the ability to filter devices from accessing your network and the Internet,
			the <?query("/sys/modelname");?> can also be configured to allow or deny access, for the computers
			on your network, to inappropriate websites by using a domain name or keywords.
		</p>
		<p>
			<strong>Parental control</strong><br>
			Parental control is used to allow or deny computers on your network from accessing specific web
			sites by using keywords or specific Domain Names. Select &quot;Turn Website Filtering ON and ALLOW computers
			access to ONLY these sites&quot; to only allow computers on your network to access the specified
 URLs and Domain Names. &quot;Turn Website Filtering ON and DENY computers access to ONLY these sites&quot;
			in order to deny computers on your network to access the specified URLs and Domain Names.
		</p>
		<p>
			<span class="style1">Example 1:</span><br>
			If you wanted to block LAN users from any website containing a URL relating to shopping,
			you would need to select &quot;Turn Website Filtering ON and DENY computers access to ONLY
			these sites&quot; and then enter &quot;shopping&quot; into the Website Filtering Rules list.
			Sites like these will be denied access to LAN users because they contain the keyword in the URL.<br>
			<a href="http://www.yahoo.com/shopping/stores.html">http://www.yahoo.com/shopping/stores.html</a><br>
			<a href="http://www.msn.com/search/shopping-spree.html">http://www.msn.com/search/shopping-spree.html</a>
		</p>
		<p>
			<span class="style1">Example 2:</span><br>
			If you want your children to only access particular sites, you would then choose &quot;
			Turn Website Filtering ON and ALLOW computers access to ONLY these sites&quot; and then enter the
			domains you want your children to have access to.
		</p>
		<ul>
			<li>Google.com </li>
			<li>Cartoons.com </li>
			<li>Discovery.com </li>
		</ul>
	</td>
</tr>
</table>
</div>


<div class="box">
<a name="firewall_dmz"><h2>Firewall Settings</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			The Firewall Settings section contains an option to configure a DMZ Host.
		</p>
		<p>
			<strong>Enable SPI</strong><br>
			SPI (&quot;stateful packet inspection&quot; also known as &quot;dynamic packet filtering&quot;) helps
			to prevent cyber attacks by tracking more states per session. It validates that the traffic passing through
			that session conforms to the protocol. When the protocol is TCP, SPI checks that the packet sequence numbers
			are within the valid range for the session, discarding those packets that do not have valid sequence numbers.
			Whether SPI is enabled or not, the router always tracks TCP connection states and ensures that each
			TCP packet's flags are valid for the current state.
		</p>
		<p>
			<strong>DMZ </strong><br>
			If you have a computer that cannot run Internet applications properly from behind the
			<?query("/sys/modelname");?>, then you can allow the computer to have unrestricted Internet access.
			Enter the IP address of that computer as a DMZ (Demilitarized Zone) host with unrestricted Internet access.
			Adding a client to the DMZ may expose that computer to a variety of security risks; so only use this
			option as a last resort.
		</p>
		<p>
			<strong>Firewall Rules</strong><br>
			Firewall Rules are used to allow or deny traffic coming in to or going out of the router based
			on the source and destination IP addresses as well as the traffic type and the specific port
			the data runs on.<br>
			<strong><em>Name</em></strong> - Users can specify a name for a Firewall Rule.<br>
			<strong><em>Action</em></strong> - Users can choose to allow or deny traffic.<br>
			<strong>Interface</strong><br>
			<strong><em>Source</em></strong> -
			Use the <strong>Source</strong> drop-down menu to select if the starting point of the traffic that's
			to be allowed or denied is from the LAN or WAN interface.<br>
			<strong><em>Dest</em></strong> -
			Use the <strong>Dest</strong> drop-down menu to select if the ending point of the traffic
			that's to be allowed or denied is arriving on the LAN or WAN interface.<br>
			<strong><em>IP Address</em></strong> -
			Here you can specify a single source or dest IP address by entering the IP address in the top box
			or enter a range of IP addresses by entering the first IP address of the range in the top box and the
			last IP address of the range in the bottom one.<br>
			<strong><em>Protocol</em></strong> -
			Use the <strong>Protocol</strong> drop-down menu to select the traffic type.<br>
			<strong><em>Port Range</em></strong> -
			Enter the same port number in both boxes to specify a single port or enter the first port of
			the range in the top box and last port of the range in the bottom one to specify a range of ports.<br>
			<strong><em>Schedule</em></strong> -
			Use the <strong>Always</strong> drop-down menu to select a previously defined schedule or click on
			<strong>Add New</strong> button to add a new schedule.
 </p>
</td>
</tr>
</table>
</div>


<div class="box">
<a name="routing"><h2>Routing</h2></a>
<table>
<?if(query("/runtime/func/dis_routing")!="1"){
echo "<tr>\n";
echo "	<td height=99>\n";
echo "		The Routing option allows you to define static routes to specific destinations.<br>\n";
echo "		<strong><em>Enable </em></strong> - Specifies whether the entry will be enabled or disabled.<br>\n";
echo "		<strong><em>Interface </em></strong> - Specifies the interface -- WAN or WAN Physical -- that\n";
echo "		that the IP packet must use to transit out of the router, when this route is used.<br>\n";
echo "		<strong><em>Interface (WAN)</em></strong> - This is the interface used to receive the IP Address\n";
echo "		from the ISP to access the Internet.<br>\n";
echo "		<strong><em>Interface (WAN Physical)</em></strong> - This is the interface used to receive the IP Address\n";
echo "		from the ISP to access the Internet.<br>\n";
echo "		<strong><em>Destination </em></strong> - The IP address of packets that will take this route.<br>\n";
echo "		<strong><em>Subnet Mask </em></strong> - One bit in the mask that specifies which bits\n";
echo "		of the IP address must match. <br>\n";
echo "		<strong><em>Gateway </em></strong> - Specifies the next hop to be taken if this route is used.\n";
echo "		A gateway of 0.0.0.0 implies there is no next hop, and the IP address matched is directly\n";
echo "		connected to the router on the interface specified: WAN or WAN Physical. \n";
echo " </td>\n";
echo " </tr>\n";
}
?>
</table>
</div>


<div class="box">
<a name="advanced_wireless"><h2>Advanced Wireless</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=20>

 <p>The options on this page should be changed by advanced users or if you are instructed to by one of our support personnel, as this can negatively affect the performance of your router if configured incorrectly. </p>
 <p><strong><em>Transmit Power - </em></strong>You can lower the output power of the <?query("/sys/modelname");?> by selecting a lower percentage of Transmit Power values from the drop-down menu. Your choices are: 100%, 50%, 25%, and 12.5%. </p>
 <p><strong><em>Beacon Interval - </em></strong> Beacons are packets sent by an Access Point to synchronize with the wireless network. Specify a Beacon interval value between 20 and 1000. The default value is set to 100 milliseconds. </p>

 <p><strong><em>RTS Threshold - </em></strong> This value should remain at its default setting of 2346. If you encounter inconsistent data flow, only minor modifications to the value range between 256 and 2346 are recommended. The default value for RTS Threshold is set to 2346. </p>
 <p><strong><em>Fragmentation - </em></strong> This value should remain at its default setting of 2346. If you experience a high packet error rate, you may slightly increase your &quot;Fragmentation&quot; value within the value range of between 1500 and 2346. Setting the Fragmentation value too low may result in poor performance. </p>
 <p><strong><em>DTIM Interval - </em></strong> Enter a value between 1 and 255 for the Delivery Traffic Indication Message (DTIM). A DTIM is a countdown informing clients of the next window for listening to broadcast and multicast messages. When the Access Point has buffered broadcast or multicast messages for associated clients, it sends the next DTIM with a DTIM Interval value. AP clients hear the beacons and awaken to receive the broadcast and multicast messages. The default value for DTIM interval is set to 1. </p>

 <p><strong><em>Preamble Type - </em></strong> The Preamble Type defines the length of the CRC (Cyclic Redundancy Check) block for communication between the Access Point and roaming wireless adapters. Make sure you select the appropriate preamble type and click the Apply button. </p>
 <p><span class="style2">Note: </span>High network traffic areas should use the shorter preamble type. CRC is a common technique for detecting data transmission errors. </p>
 <p><strong><em>CTS Mode - </em></strong>Select None to disable this feature. Select Always to force the router to require each wireless device on the network to perform an RTS/CTS handshake before they are allowed to transmit data. Select Auto to allow the router to decide when RTS/CTS handshakes are necessary. </p>
<?if(query("/runtime/func/ieee80211n")!="1"){
 echo "<p><strong><em>802.11g Only Mode - </em></strong>Enable this mode if your network is made up of purely 802.11g devices. If you have both 802.11b and 802.11g wireless clients, disable this mode. </p> </td>";
}?>
 </tr>
 </tr>
 </table>
 </div>
 
 
<div class="box">
<a name="advanced_network"><h2>Advanced Network</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=20>

 <p>This section contains settings which can change the way the router handles certain types of traffic. We recommend that you don't change any of these settings unless you are already familiar with them or have been instructed to change them by one of our support personnel. </p>

<!--
 <p><strong>VPN Passthrough </strong><br>The device supports VPN (Virtual Private Network) passthrough for PPTP (Point-to-Point Tunneling Protocol) and IPSec (IP Security). Once VPN passthrough is enabled, there is no need to create any Virtual Server or Port Forwarding entries in order for outbound VPN sessions to be established properly. Multiple VPN connections can be made through the device. This is useful when you have many VPN clients on the Local Area Network. </p>
-->

 <p><strong>UPnP </strong><br>UPnP is short for Universal Plug and Play which is a networking architecture that provides compatibility between networking equipment, software, and peripherals. The <?query("/sys/modelname");?> is a UPnP enabled router, meaning that it will work with other UPnP devices/software. If you do not want to use the UPnP function, it can be disabled by selecting &quot;Disabled&quot;. </p>
 <p><strong>WAN Ping </strong><br>When you Enable WAN Ping respond, you are causing the public WAN (Wide Area Network) IP address on the device to respond to ping commands sent by Internet users. Pinging public WAN IP addresses is a common method used by hackers to test whether your WAN IP address is valid. </p>
 <p><strong>WAN Port Speed </strong><br>This allows you to select the speed of the WAN interface of the <?query("/sys/modelname");?>: Choose 100Mbps, 10Mbps, or 10/100/1000Mbps Auto. </p>

<!--
 <p><strong>Gaming Mode </strong><br>If you are experiencing difficulties when playing online games or even certain applications that use voice data, you may need to enable Gaming Mode in order for these applications to work correctly. When not playing games or using these voice applications, it is recommended that Gaming Mode is disabled. </p>
--> 

<?if(query("/runtime/func/dis_multicast_stream")!="1"){
echo " <p><strong>Multicast Streams</strong><br>Enable this option to allow Multicast traffic to pass from the Internet to your network more efficiently. </p> </td>\n";
}
?>

 </tr>
<!--
<?if(query("/runtime/func/dis_multicast_stream")!="1"){
echo "<tr><td height=20>&nbsp;</td></tr>\n";
echo "<tr>\n";
echo "	<td height=20>\n";
echo "		<p>\n";
echo "			<strong>Multicast Streams</strong><br>\n";
echo "			Enable this option if you are receiving a Video On Demand type service from the Internet.\n";
echo "			The router uses the IGMP protocol to support efficient multicasting -- transmission of identical content,\n";
echo "			such as multimedia, from a source to a number of recipients.\n"; 
echo "			This option must be enabled if any applications on the LAN participate in a multicast group.\n"; 
echo "			If you have a multimedia LAN application that is not receiving content as expected, try enabling this option.\n";
echo "		</p>\n";
echo "	</td>\n";
echo "</tr>\n";
}
?>
--> 
</table>
</div>
 

<div class="box">
<a name="guest_zone"><h2>Guest Zone</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			Guest Zone Selection<br>
			The selection helps you to define the Guest Zone scale.<br>
			<strong><em>Enable Guest Zone</em></strong>  - Specifies whether the Guest Zone will be enabled or disabled.<br>
			<strong><em>Wireless Network Name</em></strong> -  Provide a name for Guest Zone wireless network. <br>
		</p>
		<p>
			<strong><em>Wireless Security Mode</em></strong><br>
			Securing your wireless network is important as it is used to protect the integrity of the information being 
			transmitted over your wireless network. The <?query("/sys/modelname");?> is capable of 4 types of wireless security; 
			WEP, WPA only, WPA2 only, and WPA/WPA2 (auto-detect) <br>
		</p>
		<p>
			<strong><em>WEP</em></strong><br>
			Wired Equivalent Protocol (WEP) is a wireless security protocol for Wireless Local Area Networks (WLAN). 
			WEP provides security by encrypting the data that is sent over the WLAN. The <?query("/sys/modelname");?> supports 
			2 levels of WEP Encryption: 64-bit and 128-bit. WEP is disabled by default. The WEP setting can be changed to fit 
			an existing wireless network or to customize your wireless network. <br>
		</p>
		<p>
			<strong><em>Authentication</em></strong> - Authentication is a process by which the <?query("/sys/modelname");?> 
			verifies the identity of a network device that is attempting to join the wireless network. There are two types 
			authentication for this device when using WEP. <br>
			<strong><em>Open System</em></strong> -Select this option to allow all wireless devices to communicate with the 
			<?query("/sys/modelname");?> before they are required to provide the encryption key needed to gain access to the 
			network. <br>
			<strong><em>Shared Key </em></strong> - Select this option to require any wireless device attempting to communicate 
			with the <?query("/sys/modelname");?> to provide the encryption key needed to access the network before they are 
			allowed to communicate with the <?query("/sys/modelname");?>. <br>
			<strong><em>WEP Encryption</em></strong> - Select the level of WEP Encryption that you would like to use on your 
			network. The two supported levels of WEP encryption are 64-bit and 128-bit.<br>
			<strong><em>Key Type </em></strong> - The Key Types that are supported by the <?query("/sys/modelname");?> are HEX 
			(Hexadecimal) and ASCII (American Standard Code for Information Interchange.) The Key Type can be changed to fit an 
			existing wireless network or to customize your wireless network. <br>
			<strong><em>Keys</em></strong> - Keys 1-4 allow you to easily change wireless encryption settings to maintain a 
			secure network. Simply select the specific key to be used for encrypting wireless data on the network. <br>
		</p>
		<p>
			<strong><em>WPA-Personal</em></strong><br>
			Wi-Fi Protected Access authorizes and authenticates users onto the wireless network. WPA uses stronger security than 
			WEP and is based on a key that changes automatically at a regular interval. <br>
		</p>
		<p>
			<strong><em>Cipher Type</em></strong> - The <?query("/sys/modelname");?> support two different cipher types when WPA 
			is used as the Security Type. These two options are TKIP (Temporal Key Integrity Protocol) and AES (Advanced Encryption 
			Standard). <br>
			<strong><em>PSK/EAP</em></strong> -When PSK is selected, your wireless clients will need to provide a Passphrase for 
			authentication. When EAP is selected, you will need to have a RADIUS server on your network which will handle the 
			authentication of all your wireless clients. <br>
			<strong><em>Passphrase </em></strong> - This is what your wireless clients will need in order to communicate with your 
			<?query("/sys/modelname");?>, when PSK is selected. Enter 8-63 alphanumeric characters. Be sure to write this Passphrase 
			down as you will need to enter it on any other wireless devices you are trying to add to your network. <br>
			<strong><em>802.1X </em></strong> - This means of WPA authentication is used in conjunction with a RADIUS server that 
			must be present on your network. Enter the IP address, port, and Shared Secret that you RADIUS is configured for. 
			You also have the option to enter information for a second RADIUS server in the even that there are two on your network 
			which you are using to authenticate wireless clients. <br>
		</p>
		<p>
			<strong><em>WPA2</em></strong><br>
			Wi-Fi Protected Access 2 authorizes and authenticates users onto the wireless network. WPA2 uses stronger security 
			than WEP and is based on a key that changes automatically at a regular interval. <br>
		</p>
		<p>
			<strong><em>Cipher Type</em></strong> - The <?query("/sys/modelname");?> support two different cipher types when WPA 
			is used as the Security Type. These two options are TKIP (Temporal Key Integrity Protocol) and AES (Advanced Encryption 
			Standard). <br>
			<strong><em>PSK/EAP</em></strong> - When PSK is selected, your wireless clients will need to provide a Passphrase for
			authentication. When EAP is selected, you will need to have a RADIUS server on your network which will handle the 
			authentication of all your wireless clients. <br>
			<strong><em>Passphrase</em></strong> - This is what your wireless clients will need in order to communicate with your 
			<?query("/sys/modelname");?>, when PSK is selected. Enter 8-63 alphanumeric characters. Be sure to write this Passphrase 
			down as you will need to enter it on any other wireless devices you are trying to add to your network. <br>
			<strong><em>802.1X </em></strong> - This means of WPA2 authentication is used in conjunction with a RADIUS server that 
			must be present on your network. Enter the IP address, port, and Shared Secret that you RADIUS is configured for. 
			You also have the option to enter information for a second RADIUS server in the even that there are two on your network 
			which you are using to authenticate wireless clients. <br>
		</p>
		<p>
			<strong><em>WPA2-Auto</em></strong> <br>
			This option allows the <?query("/sys/modelname");?> to have both WPA2 and WPA clients connected to it simultaneously.<br>
		</p>
		<p>
			<strong><em>LAN Setup for Guest Zone</em></strong><br> 
			These are the settings of the Guest Zone LAN (Local Area Network) interface for the device. These settings may be 
			referred to as "private settings". You may change the IP address if needed. The IP address is private to your internal 
			network and cannot be seen on the Internet. The default IP address is 192.168.1.1 with a subnet mask of 255.255.255.0.<br>
		</p>
		<p>
			<strong><em>IP Address</em></strong> - IP address of the <?query("/sys/modelname");?>, default is 192.168.1.1. <br>
			<strong><em>Subnet Mask</em></strong> - Subnet Mask of <?query("/sys/modelname");?>, default is 255.255.255.0. <br>
		</p>
		<p>
			<strong><em>Enable Guest Zone Client Isolation</em></strong> : <br>
			Enable the function to prevent one guest client to access other clients in the Guest Zone. The guest client can access 
			to the Internet only. <br>
		</p>
		<p>
			<strong><em>Enable Routing Between Zones</em></strong> : <br>
			Use this section to enable routing between Host Zone and Guest Zone, Guest clients can not access Host clients' data 
			without enable the function. <br>
		</p>
		<p>
			<strong><em>DHCP Server for Guest Zone</em></strong> <br>
			DHCP stands for Dynamic Host Control Protocol. The DHCP server assigns IP addresses to devices on the network that 
			request them. These devices must be set to &quot;Obtain the IP address automatically&quot;. By default, the DHCP 
			Server is enabled on the <?query("/sys/modelname");?>. The DHCP address pool contains the range of the IP address 
			that will automatically be assigned to the clients on the network. <br>
		</p>
		<p>
			<strong><em>Starting IP address</em></strong> - The starting IP address for the DHCP server's IP assignment. <br>
			<strong><em>Ending IP address</em></strong> -The ending IP address for the DHCP server's IP assignment. <br>
			<strong><em>Lease Time</em></strong> -The length of time in minutes for the IP lease. 
			Dynamic DHCP client computers connected to the unit will have their information displayed in the Dynamic DHCP Client 
			Table. The table will show the Host Name, IP Address, MAC Address, and Expired Time of the DHCP lease for each client 
			computer. <br>
		</p>
</td>
</tr>
</table>
</div>
 
<div class="box">
<a name="wake_on_lan"><h2>Wake on LAN</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
<tr>
	<td height=20>
		<p>
			The Wake on LAN function can be used to remotely turn on a PC connected to the LAN side of the router. Specify the UDP port that will be used by the Wake on LAN magic packet to prevent the router from thinking the Wake on LAN request is a hostile attack and blocking it.<br>
			<br>
			<strong><em>UDP Port</em></strong> - 
			This is the unique port that the DIR-685 will use to listen for the magic packets that will turn on the PC.<br>
			<strong><em>Interface</em></strong> - 
			(This setting can't currently be changed. It may be possible to change this setting in later firmware releases).<br>		
		</p>
	</td>
</tr>
</table>
</div>
