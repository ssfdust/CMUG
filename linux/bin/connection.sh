#!/bin/bash
if [ -f "./user.dat" ]; then
	username=$(./gen | awk '{print $1}')
	passwd=$(./gen | awk '{print $2}')
else
	./gen
	username=$(./gen | awk '{print $1}')
	passwd=$(./gen | awk '{print $2}')
fi

connect()
{
	echo "aaaa"
	file_write
	netctl start CMCC
}


help_menu()
{
	echo "Usage ${0} [options]"
	echo 
	echo "-c   connect to internet"
	echo "-d   disconnect to internet"
	echo "-h   Show this help"
	echo "-r   Delete username and passwd"
	echo "default: -c"
	exit ${1}
}

disconnect()
{
	netctl stop CMCC
}

file_write()
{
	echo "
	Description='Example PPPoE connection'
	Interface=eth0
	Connection=pppoe
	User='$username'
	Password='$passwd'
	" > /etc/netctl/CMCC
}

delete()
{
	rm ./user.dat
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
	  r) delete;;
	  *) connect;;
	esac
done
