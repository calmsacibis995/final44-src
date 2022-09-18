h37838
s 00003/00003/00054
d D 1.4 87/04/01 15:49:53 jaap 4 3
c Just checking in
e
s 00001/00001/00056
d D 1.3 85/05/02 17:58:23 jaap 3 2
c Added -Tver option...
e
s 00012/00009/00045
d D 1.2 85/03/03 22:39:10 jaap 2 1
c Removed errors, added Versatec support (jaap).
e
s 00054/00000/00000
d D 1.1 85/03/01 17:20:28 jaap 1 0
c date and time created 85/03/01 17:20:28 by jaap
e
u
U
t
T
I 1
#!/bin/sh
#
#	%M%	(CWI)	%I%	%E%
#
IDDIR=/usr/lib/ditroff/ideal
filter=t
iflags=
for i
do
	case $i in
	-p*)	filter=p
		shift ;;
	-4*)	filter=4
		shift ;;
	-n*)	filter=n
		shift ;;
	-a*)	filter=a
		shift ;;
	-t*)	filter=t
		shift ;;
D 3
	-v*)	filter=v
E 3
I 3
	-Tver*)	filter=v
E 3
		shift ;;
	-T202*)	filter=2
		shift ;;
	-Taps*)	filter=a
		shift ;;
	-s*)	sflags=s
		shift ;;
	-q*)	fflags=-q
		shift ;;
	*)	iflags="$iflags $i"
		shift ;;
	esac
done
case $filter in
D 2
	p)	$IDDIR/ideal $iflags | $IDDIR/idfilt/pfilt ;;
	v)	$IDDIR/ideal $iflags | $IDDIR/idfilt/vfilt ;;
E 2
I 2
	p)	$IDDIR/ideal $iflags | $IDDIR/pfilt ;;
E 2
D 4
	4)	$IDDIR/ideal $iflags >/tmp/id`getuid`
D 2
		$IDDIR/idfilt/4filt /tmp/id`getuid`
E 2
I 2
		$IDDIR/4filt /tmp/id`getuid`
E 2
		rm /tmp/id`getuid` ;;
E 4
I 4
	4)	$IDDIR/ideal $iflags >/tmp/id$$
		$IDDIR/4filt /tmp/id$$
		rm /tmp/id$$ ;;
E 4
	n)	$IDDIR/ideal $iflags ;;
	t)	case $sflags in
D 2
		s)	$IDDIR/ideal $iflags | $IDDIR/idfilt/idsort | $IDDIR/idfilt/tfilt $fflags ;;
		*)	$IDDIR/ideal $iflags | $IDDIR/idfilt/tfilt $fflags ;;
E 2
I 2
		s)	$IDDIR/ideal $iflags | $IDDIR/idsort | $IDDIR/tfilt $fflags ;;
		*)	$IDDIR/ideal $iflags | $IDDIR/tfilt $fflags ;;
E 2
		esac ;;
I 2
	v)	case $sflags in
		s)	$IDDIR/ideal $iflags | $IDDIR/idsort | $IDDIR/vfilt $fflags ;;
		*)	$IDDIR/ideal $iflags | $IDDIR/vfilt $fflags ;;
		esac ;;
E 2
	a)	case $sflags in
D 2
		s)	$IDDIR/ideal $iflags | $IDDIR/idfilt/idsort | $IDDIR/idfilt/apsfilt $fflags ;;
		*)	$IDDIR/ideal $iflags | $IDDIR/idfilt/apsfilt $fflags ;;
E 2
I 2
		s)	$IDDIR/ideal $iflags | $IDDIR/idsort | $IDDIR/apsfilt $fflags ;;
		*)	$IDDIR/ideal $iflags | $IDDIR/apsfilt $fflags ;;
E 2
		esac ;;
	2)	case $sflags in
D 2
		s)	$IDDIR/ideal $iflags | $IDDIR/idfilt/idsort | $IDDIR/idfilt/202filt $fflags ;;
		*)	$IDDIR/ideal $iflags | $IDDIR/idfilt/202filt $fflags ;;
E 2
I 2
		s)	$IDDIR/ideal $iflags | $IDDIR/idsort | $IDDIR/202filt $fflags ;;
		*)	$IDDIR/ideal $iflags | $IDDIR/202filt $fflags ;;
E 2
		esac ;;
esac
E 1
