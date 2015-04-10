<div class="box">
<a name="device_info"><h2>Device Info</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=39> 
This page displays current information for the <?query("/sys/modelname");?>. The page will show the version of firmware currently loaded on the device. <br>

&nbsp;<br>
<strong><em>LAN (Local Area Network) - </em></strong>This displays the MAC Address of the Ethernet LAN interface, the IP Address and Subnet Mask of the LAN interface, and whether or not the router's built-in DHCP server is Enabled or Disabled. <br>
<strong><em>WAN (Wide Area Network) - </em></strong>This displays the MAC Address of the WAN interface, as well as the IP Address, Subnet Mask, Default Gateway, and DNS server information that the <?query("/sys/modelname");?> has obtained from your ISP. It will also display the connection type (Dynamic, Static, or PPPoE) that is used to establish a connection with your ISP. If the router is configured for Dynamic, then there will be buttons for releasing and renewing the IP Address assigned to the WAN interface. If the router is configured for PPPoE, there will be buttons for connecting and disconnecting the PPPoE session.<br> 
<strong><em>
Wireless 802.11
<? if(query("/runtime/func/ieee80211n") != "1") { echo "g"; } else { echo "n"; }?>
 - 
</em></strong>This displays the SSID, Channel, and whether or not Encryption is enabled on the Wireless interface. </td>
</tr>
</table>
</div>


<div class="box">
<a name="log"><h2>Log</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=26>
 The <?query("/sys/modelname");?> keeps a running log of events and activities occurring on it at all times. The log will display up to 400 recent logs. Newer log activities will overwrite the older logs. <br>

 <strong><em>First Page - </em></strong> Click this button to go to the first page of the log. <br>
 <strong><em>Last Page - </em></strong> Click this button to go to the last page of the log. <br>
 <strong><em>Previous - </em></strong> Moves back one log page. <br>
 <strong><em>Next - </em></strong> Moves forward one log page. <br>

 <strong><em>Clear - </em></strong> Clears the logs completely. </td>
 </tr>
 </table>
 </div>
 
 
<div class="box">
<a name="statistics"><h2>Statistics</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=2>
 The <?query("/sys/modelname");?> keeps statistic of the data traffic that it handles. You are able to view the amount of packets that the router has Received and Transmitted on the Internet (WAN), LAN, and Wireless interfaces.
<br>
<strong><em>Refresh - </em></strong>Click this button to update the counters. <br>
<strong><em>Reset - </em></strong>Click this button to clear the counters. The traffic counter will reset when the device is rebooted. </td>
</tr>
</table>
</div>


<div class="box">
<a name="internet_session"><h2>Internet session</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=2>
 Internet Session display Source and Destination packets passing through the <?query("/sys/modelname");?>. <br>
 <strong><em>IP Address - </em></strong> The source IP address of where the packets are originated from. <br>
 <strong><em>TCP Session - </em></strong> This shows the number of TCP packets are being sent from the source IP address. <br>
 <strong><em>UDP Session - </em></strong> This shows the number of UDP packets are being sent from the source IP address. <br>
 <strong><em>Protocol - </em></strong> This is the type of packets transmitted between the source and destination IP. <br>
 Source IP - This shows the IP address of where the packets are originated from. <br>
 Source Port - This shows the port being used to transmit packets to the Dest IP. <br>
 Dest IP - This shows the IP address of where the packets are destined to. <br>
 Dest Port - This shows the port being used to receive packets from the source IP. 
</td>
 </tr>
 </tr>
</table>
</div>
 
 
<div class="box">
<a name="wireless"><h2>Wireless</h2></a>
<table border=0 cellspacing=0 cellpadding=0>
 <tr>
 <td height=2>
 Use this page in order to view how many wireless clients have associated with the <?query("/sys/modelname");?>. This page shows the MAC address of each associated client, how long they have been associated, and the mode they are connecting in (802.11b, 802.11g or 802.11n).
</td>
 </tr>
</table>
</div> 
