#!/bin/bash
username=$(./gen | awk '{print $1}')
passwd=$(./gen | awk '{print $2}')

connect()
{
	file_write
	echo "$username * $passwd" > /etc/ppp/pap-secrets
	pppd call CMCC
}


help_menu()
{
	echo "Usage ${0} [options]"
	echo 
	echo "-c   connect to internet"
	echo "-d   disconnect to internet"
	echo "-h   Show this help"
	echo "default: -c"
	exit ${1}
}

disconnect()
{
	poff CMCC
}

file_write()
{
	echo "
	plugin rp-pppoe.so
	# rp_pppoe_ac 'your ac name'
	# rp_pppoe_service 'your service name'
	  
	# network interface
	eth0
	# login name
	name \"$username\"
	usepeerdns
	persist
	# Uncomment this if you want to enable dial on demand
	#demand
	#idle 180
	defaultroute
	hide-password
	noauth
	" > /etc/ppp/peers/CMCC
}
if [[ ${EUID} -ne 0 ]]; then
    echo "This script must be run as root."
    _usage 1
fi

while getopts 'c:d:h' arg; do
	case "${arg}" in
		c) connect;;
	  d) disconnect;;
	  h) help_menu;;
	  *) connect;;
	esac
done
