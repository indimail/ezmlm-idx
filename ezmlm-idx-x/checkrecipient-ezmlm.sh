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
	user=$(echo $addr | cut -d@ -f1)
	# get the domain directory
	dir=$(grep "+""$domain""-" SYSCONFDIR/users/assign | awk -F: '{print $5}' 2>/dev/null)
fi

# check if ezmlm list exists
[ -n "$dir" -a -d "$dir/$user" ] && exit 0 || exit 1
