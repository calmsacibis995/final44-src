h24497
s 00001/00001/00084
d D 1.2 93/06/08 14:43:53 elan 2 1
c 4.4BSD support.
e
s 00085/00000/00000
d D 1.1 93/05/18 16:58:54 elan 1 0
c date and time created 93/05/18 16:58:54 by elan
e
u
U
t
T
I 1
case $CONFIG in
'')
    if test ! -f config.sh; then
	ln ../config.sh . || \
	ln ../../config.sh . || \
	ln ../../../config.sh . || \
	(echo "Can't find config.sh."; exit 1)
    fi
    . config.sh
    ;;
esac
: This forces SH files to create target in same directory as SH file.
: This is so that make depend always knows where to find SH derivatives.
case "$0" in
*/*) cd `expr X$0 : 'X\(.*\)/'` ;;
esac
echo "Extracting cflags (with variable substitutions)"
: This section of the file will have variable substitutions done on it.
: Move anything that needs config subs from !NO!SUBS! section to !GROK!THIS!.
: Protect any dollar signs and backticks that you do not want interpreted
: by putting a backslash in front.  You may delete these comments.
rm -f cflags
$spitshell >cflags <<!GROK!THIS!
!GROK!THIS!

: In the following dollars and backticks do not need the extra backslash.
$spitshell >>cflags <<'!NO!SUBS!'
case "$0" in
*/*) cd `expr X$0 : 'X\(.*\)/'` ;;
esac
case $CONFIG in
'')
    if test ! -f config.sh; then
	ln ../config.sh . || \
	ln ../../config.sh . || \
	ln ../../../config.sh . || \
	(echo "Can't find config.sh."; exit 1)
    fi 2>/dev/null
    . ./config.sh
    ;;
esac

also=': '
case $# in
1) also='echo 1>&2 "	  CCCMD = "'
esac

case $# in
0) set *.c; echo "The current C flags are:" ;;
esac

set `echo "$* " | sed 's/\.[oc] / /g'`

D 2
for file do
E 2
I 2
for file; do
E 2

    case "$#" in
    1) ;;
    *) echo $n "    $file.c	$c" ;;
    esac

    : allow variables like str_cflags to be evaluated

    eval 'eval ${'"${file}_cflags"'-""}'

    : or customize here

    case "$file" in
    a2p) ;;
    a2py) ;;
    hash) ;;
    str) ;;
    util) ;;
    walk) ;;
    *) ;;
    esac

    echo "$cc -c $ccflags $optimize $large $split"
    eval "$also "'"$cc -c $ccflags $optimize $large $split"'

    . ./config.sh

done
!NO!SUBS!
chmod +x cflags
$eunicefix cflags
E 1
