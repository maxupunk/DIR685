#!/bin/sh
echo [$0] ... > /dev/console
LANMAC=`xmldbc -i -g /runtime/layout/lanmac`
UPNP_XML="/var/wsc_upnp_xml"
xmldbc -i -s /runtime/wps_upnp/uuid `genuuid -s InternetGatewayDevice -m $LANMAC`
cp -r /etc/templates/wsc_upnp_xml /var/.
chmod -R +x $UPNP_XML
xmldbc -A $UPNP_XML/WFADeviceDesc.php > $UPNP_XML/WFADeviceDesc.xml
chmod -R +x $UPNP_XML
