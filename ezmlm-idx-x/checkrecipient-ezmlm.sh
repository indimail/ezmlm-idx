#
# This is a Pluggable Address Verification Module for qmail-smtpd
# recipients extension
# This module reads an address from descriptor 3
# if addr is an address configured in ezmlm/ezmlm-idx
# It needs to be called using the qmail-smtpd recipient
# extension in SYSCONFDIR/control/recipients
# like this
#
# @domain|LIBEXEC/ezmlm/checkrecipient-ezmlm
# or
# user|LIBEXEC/ezmlm/checkrecipient-ezmlm
#

check_addr()
{
	# user=$1
	# dir=$2

	# check if ezmlm list exists
	[ -n "$2" -a -d "$2/$1" ] && return 0
	i=1
	found=0
	cut_str=$i
	while true
	do
		str=$(echo $1 | cut -d- -f"$cut_str")
		[ "$str" = "$1" ] && break
		# check if ezmlm list exists
		[ -d $2/$str ] && return 0
		i=$(expr $i + 1)
		cut_str=$cut_str",$i"
	done
	return 1
}

exec 0<&3
read addr

domain=$(echo $addr|cut -d@ -f2)
if [ -z "$domain" ] ; then # mail to local user
	user=$addr
	# get the user's home directory
	dir=$(getent passwd $user | awk -F: '{print $6}')
else
	# check if this is one of our domains
	grep $domain SYSCONFDIR/control/rcpthosts >/dev/null 2>&1
	[ $? -ne 0 ] && exit 1
	user=$(echo $addr | cut -d@ -f1 | sed -e 's{-accept-.*{{' -e 's{-reject-.*{{')
	# get the domain directory
	dir=$(grep "+""$domain""-" SYSCONFDIR/users/assign | awk -F: '{print $5}' 2>/dev/null)
fi

# check if ezmlm list exists
check_addr $user $dir
exit $?
