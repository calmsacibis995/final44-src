h07815
s 00002/00002/00050
d D 8.1 93/06/06 16:24:29 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00050
d D 1.7 91/04/25 20:17:58 donn 8 7
c Don't pass a null string to deroff -- it will try to find troff directives
c in the current directory (and dump core).
e
s 00008/00002/00044
d D 1.6 91/04/18 18:07:55 bostic 7 6
c new copyright; att/bsd/shared
e
s 00008/00003/00038
d D 1.5 89/08/21 17:16:05 karels 6 4
c add -t, -l for tex
e
s 00008/00003/00038
d R 1.5 89/08/21 09:24:45 karels 5 4
c add -t, -l for tex, latex
e
s 00008/00008/00033
d D 1.4 89/05/11 13:39:12 bostic 4 3
c file reorg, pathnames.h, paths.h
e
s 00004/00003/00037
d D 1.3 83/09/10 14:35:24 jak 3 2
c fixed -v and -x options
e
s 00026/00018/00014
d D 1.2 83/04/20 21:52:04 mckusick 2 1
c auxilliary files now as options, usage message added, et al --jak
e
s 00032/00000/00000
d D 1.1 83/04/20 15:52:19 mckusick 1 0
c date and time created 83/04/20 15:52:19 by mckusick
e
u
U
t
T
I 1
D 7
#! /bin/sh
E 7
I 7
#!/bin/sh -
E 7
#
D 7
#	%W%	(Berkeley)	%E%
E 7
I 7
D 9
# Copyright (c) 1983 The Regents of the University of California.
# All rights reserved.
E 9
I 9
# Copyright (c) 1983, 1993
#	The Regents of the University of California.  All rights reserved.
E 9
E 7
#
I 7
# %sccs.include.proprietary.sh%
#
#	%W% (Berkeley) %G%
#

E 7
D 2
: B flags, D dictionary, F files, H history, S stop, V data for -v
H=${H-/usr/dict/spellhist}
T=/tmp/spell.$$
V=/dev/null
F= B=
trap "rm -f $T*; exit" 0 1 2 13 15
E 2
I 2
: V data for -v, B flags, D dictionary, S stop, H history, F files, T temp
I 6
: R for deroff program
E 6
V=/dev/null		B=			F= 
D 4
S=/usr/dict/hstop	H=/dev/null		T=/tmp/spell.$$
E 4
I 4
S=/usr/share/dict/hstop	H=/dev/null		T=/tmp/spell.$$
I 6
R="deroff@-w"

E 6
E 4
next="F=$F@"
trap "rm -f $T ${T}a ; exit" 0
E 2
for A in $*
do
	case $A in
D 3
	-v)	B="$B -v"
E 3
I 3
	-v)	B="$B@-v"
E 3
		V=${T}a ;;
I 3
	-x)	B="$B@-x" ;;
E 3
D 2
	-a)	;;
E 2
D 4
	-b) 	D=${D-/usr/dict/hlistb}
E 4
I 4
	-b) 	D=${D-/usr/share/dict/hlistb}
E 4
D 3
		B="$B -b" ;;
E 3
I 3
		B="$B@-b" ;;
E 3
D 2
	*)	F="$F $A"
E 2
I 2
	-d)	next="D=" ;;
	-s)	next="S=" ;;
	-h)	next="H=" ;;
I 6
	-t)	R=detex ;;
	-l)	R=delatex ;;
E 6
D 4
	-*)	echo "Bad flag for spell: $A"
		echo "Usage:  spell [ -v ] [ -b ] [ -d hlist ] [ -s hstop ] [ -h spellhist ]"
E 4
I 4
	-*)	echo "spell: illegal option -- $A"
D 6
		echo "usage: spell [-bv] [-d hlist] [-s hstop] [-h spellhist]"
E 6
I 6
		echo "usage: spell [-bvtl] [-d hlist] [-s hstop] [-h spellhist]"
E 6
E 4
		exit ;;
	*)	eval $next"$A"
		next="F=$F@" ;;
E 2
	esac
D 2
	done
deroff -w $F |\
  sort -u |\
  /usr/lib/spell ${S-/usr/dict/hstop} $T |\
  /usr/lib/spell ${D-/usr/dict/hlista} $V $B |\
  sort -u +0f +0 - $T |\
  tee -a $H
who am i >>$H 2>/dev/null
E 2
I 2
done
IFS=@
case $H in
D 4
/dev/null)	deroff -w $F | sort -u | /usr/lib/spell $S $T |
		/usr/lib/spell ${D-/usr/dict/hlista} $V $B |
E 4
I 4
D 6
/dev/null)	deroff -w $F | sort -u | /usr/libexec/spell $S $T |
E 6
I 6
D 8
/dev/null)	$R $F | sort -u | /usr/libexec/spell $S $T |
E 8
I 8
/dev/null)	eval $R $F | sort -u | /usr/libexec/spell $S $T |
E 8
E 6
		/usr/libexec/spell ${D-/usr/share/dict/hlista} $V $B |
E 4
		sort -u +0f +0 - $T ;;
D 4
*)		deroff -w $F | sort -u | /usr/lib/spell $S $T |
		/usr/lib/spell ${D-/usr/dict/hlista} $V $B |
E 4
I 4
D 6
*)		deroff -w $F | sort -u | /usr/libexec/spell $S $T |
E 6
I 6
D 8
*)		$R $F | sort -u | /usr/libexec/spell $S $T |
E 8
I 8
*)		eval $R $F | sort -u | /usr/libexec/spell $S $T |
E 8
E 6
		/usr/libexec/spell ${D-/usr/share/dict/hlista} $V $B |
E 4
		sort -u +0f +0 - $T | tee -a $H
		who am i >> $H 2> /dev/null ;;
esac
E 2
case $V in
D 2
/dev/null)	exit
E 2
I 2
/dev/null)	exit ;;
E 2
esac
D 2
sed '/^\./d' $V | sort -u +1f +0
E 2
I 2
D 3
sed '/^\./d' $V | sort -u +1f +0 ;;
E 3
I 3
sed '/^\./d' $V | sort -u +1f +0
E 3
E 2
E 1
