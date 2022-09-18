# start up .login
set noglob
tset -k -e -Q -s -p\?adm3a \?h19 > /tmp/tset$$
source /tmp/tset$$
rm -f /tmp/tset$$
unset noglob
stty newcrt
set path=(/usr/local /usr/ucb /usr/bin /bin /usr/hosts /usr/new .)
biff y
setenv EXINIT	"set beautify"
umask 22
msgs -q
