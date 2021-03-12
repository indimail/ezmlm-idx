echo 'main="$1"; shift'
set $LD
shift
ld_args=$1
if [ -d /usr/lib64/mysql ] ; then
	mysql_libdir=-L/usr/lib64/mysql
elif [ -d /usr/local/mysql ] ; then
	mysql_libdir=-L/usr/local/lib/mysql
elif [ -d /opt/local/mysql ] ; then
	mysql_libdir=-L/opt/local/lib/mysql
else
	mysql_libdir=""
fi
echo "if [ -n \"\$CC\" ] ; then"
echo "  " echo \""\$CC" \$LDFLAGS $* $mysql_libdir '-o "$main" "$main".o ${1+"$@"}'\"
echo "  " exec   "\$CC" \$LDFLAGS $* $mysql_libdir '-o "$main" "$main".o ${1+"$@"}'
echo "else"
echo "  " echo \""$ld_args" \$LDFLAGS $* $mysql_libdir '-o "$main" "$main".o -L. ${1+"$@"}'\"
echo "  " exec   "$ld_args" \$LDFLAGS $* $mysql_libdir '-o "$main" "$main".o -L. ${1+"$@"}'
echo "fi"
