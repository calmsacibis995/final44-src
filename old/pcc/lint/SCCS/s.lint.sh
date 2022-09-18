h64548
s 00001/00001/00039
d D 1.10 89/08/24 19:23:48 bostic 10 9
c rename to something obvious
e
s 00005/00005/00035
d D 1.9 89/05/10 22:28:12 bostic 9 8
c file reorg, pathnames.h, paths.h
e
s 00002/00001/00038
d D 1.8 88/07/07 04:58:27 edward 8 7
c ignore flags -R, -p*, -g*
e
s 00016/00011/00023
d D 1.7 85/03/11 13:10:10 edward 7 6
c check -*n* and -*p* only in lint flags (e.g., not in -I*n*)
e
s 00002/00002/00032
d D 1.6 84/12/11 12:45:57 edward 6 5
c don't pass -O to cpp, throw it away
e
s 00002/00001/00032
d D 1.5 83/04/09 15:07:47 edward 5 4
c Changed -X to use /usr/src/usr.bin/lint (instead of /usr/scj/lint)
e
s 00008/00003/00025
d D 1.4 83/03/05 17:37:37 nicklin 4 3
c implemented lint library construction - problems to Edward Wang
e
s 00001/00001/00027
d D 1.3 82/11/16 13:39:29 rrh 3 2
c echo the name of each C file lint processes before processing begins
c this mostly emulates what cc does when it compiles multiple files
e
s 00001/00000/00027
d D 1.2 82/09/21 11:43:29 rrh 2 1
c Tell csh that this script is really a sh script
e
s 00027/00000/00000
d D 1.1 82/08/30 13:16:14 rrh 1 0
c date and time created 82/08/30 13:16:14 by rrh
e
u
U
t
T
I 2
#! /bin/sh
E 2
I 1
#
#	%W%	(Berkeley)	%G%
#
D 7
L=/usr/lib/lint/lint T=/usr/tmp/lint.$$ PATH=/bin:/usr/bin O="-C -Dlint"
D 4
X= P=unix LL=/usr/lib/lint
E 4
I 4
X= P=unix LL=/usr/lib/lint C=
E 7
I 7
D 9
L=/usr/lib/lint/lint T=/tmp/lint.$$ PATH=/bin:/usr/bin O="-C -Dlint"
X= P=unix LL=/usr/lib/lint
E 9
I 9
D 10
L=/usr/libexec/lint T=/tmp/lint.$$
E 10
I 10
L=/usr/libexec/lintpass T=/tmp/lint.$$
E 10
PATH=/bin:/usr/bin:/usr/pgrm
O="-C -Dlint"
X= P=unix LL=/usr/libdata/lint
E 9
C=
E 7
E 4
trap "rm -f $T; exit" 1 2 15
for A in $*
do
	case $A in
D 7
	-*n*)	P= ;;
	-*p*)	P=port ;;
	esac
	case $A in
E 7
	*.ln)	cat $A >>$T ;;
	-l*)	cat $LL/llib$A.ln >>$T ;;
I 4
D 7
	-C?*)	P= C=`echo $A | sed -e s/-C/llib-l/` ; X="$X -L -C$C" ;;
E 4
D 6
	-[IDOU]*)	O="$O $A" ;;
D 5
	-X)	LL=/usr/scj/lint L=/usr/scj/lint/lpass ;;
E 5
I 5
#	-X)	LL=/usr/scj/lint L=/usr/scj/lint/lpass ;;
E 6
I 6
	-[IDU]*)	O="$O $A" ;;
E 7
I 7
	-C?*)	P=
		C=`echo $A | sed -e s/-C/llib-l/`
		X="$X -L -C$C" ;;
	-[IDU]*)O="$O $A" ;;
E 7
D 8
	-O)	;;
E 8
I 8
	-[ORpg]*)
		;;
E 8
E 6
D 7
	-X)	LL=/usr/src/usr.bin/lint L=/usr/src/usr.bin/lint/lpass ;;
E 5
D 4
	-*)	X="$X$A" ;;
E 4
I 4
	-*)	X="$X $A" ;;
E 4
D 3
	*)	(/lib/cpp $O $A | ${L}1 $X >>$T)2>&1
E 3
I 3
	*)	echo "$A:" ; (/lib/cpp $O $A | ${L}1 $X >>$T)2>&1
E 7
I 7
D 9
	-X)	LL=/usr/src/usr.bin/lint
		L=/usr/src/usr.bin/lint/lpass ;;
E 9
	-*)	X="$X $A"
		case $A in
		-*n*)	P= ;;
		-*p*)	P=port ;;
		esac ;;
	*)	echo "$A:"
D 9
		(/lib/cpp $O $A | ${L}1 $X >>$T)2>&1
E 9
I 9
		(cpp $O $A | ${L}1 $X >>$T)2>&1
E 9
E 7
E 3
	esac
	done
case $P in
	unix)	cat $LL/llib-lc.ln >>$T ;;
	port)	cat $LL/llib-port.ln >>$T ;;
I 4
	"")	cat /dev/null >>$T ;;
E 4
	esac
D 4
${L}2 $T $X
E 4
I 4
case $C in
	"")	${L}2 $T $X ;;
	*)	cp $T $C.ln ;;
	esac
E 4
rm -f $T
E 1
