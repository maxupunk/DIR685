#!/bin/sh
echo [$0] $1 ... > /dev/console
usockc /var/run/fresetd_unixsock $1
