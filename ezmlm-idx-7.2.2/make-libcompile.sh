echo 'source=$1; shift'
echo 'base=`echo "$source" | sed -e s:\\\\.c$::`'
set $CC
cc_args=$1
shift
echo "if [ -n \"\$CC\" ] ; then"
echo "  " echo \""\$CC" \$CFLAGS "$CCLO" $* '-I. -o "$base".lo -c "$source" ${1+"$@"}'\"
echo "  " exec   "\$CC" \$CFLAGS "$CCLO" $* '-I. -o "$base".lo -c "$source" ${1+"$@"}'
echo "else"
echo "  " echo \""$cc_args" \$CFLAGS "$CCLO" $* '-I. -o "$base".lo -c "$source" ${1+"$@"}'\"
echo "  " exec   "$cc_args" \$CFLAGS "$CCLO" $* '-I. -o "$base".lo -c "$source" ${1+"$@"}'
echo "fi"
