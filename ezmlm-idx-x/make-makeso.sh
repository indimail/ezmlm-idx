ldargs=$LDSO
set $ldargs
LD=$1
shift
echo echo exec "$LD $*" -L. -o '${1+"$@"}'
echo exec "$LD $*" -L. -o '${1+"$@"}'
