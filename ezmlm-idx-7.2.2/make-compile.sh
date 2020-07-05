echo 'source=$1; shift'
echo 'base=`echo "$source" | sed -e s:\\\\.c$::`'
set $CC
cc_arg=$1
shift
echo "if [ -n \"\$CC\" ] ; then"
echo "  " echo \""\$CC" \$CFLAGS $* '-I. -o "$base".o -c "$source" ${1+"$@"}'\"
echo "  " exec   "\$CC" \$CFLAGS $* '-I. -o "$base".o -c "$source" ${1+"$@"}'
echo "else"
echo "  " echo \""$cc_arg" \$CFLAGS $* '-I. -o "$base".o -c "$source" ${1+"$@"}'\"
echo "  " exec   "$cc_arg" \$CFLAGS $* '-I. -o "$base".o -c "$source" ${1+"$@"}'
echo "fi"
