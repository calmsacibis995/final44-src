h51106
s 00000/00000/00044
d D 8.1 93/06/06 14:33:32 bostic 10 9
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00043
d D 4.9 91/07/31 16:43:56 bostic 9 8
c deroff is in /usr/bin, not /usr/ucb
e
s 00005/00002/00039
d D 4.8 91/04/17 17:13:50 bostic 8 7
c new copyright; att/bsd/shared
e
s 00001/00001/00040
d D 4.7 89/08/31 08:28:39 bostic 7 6
c ^ hasn't been the pipe character in a long while
e
s 00002/00002/00039
d D 4.6 89/05/11 09:46:41 bostic 6 5
c file reorg, pathnames.h, paths.h
e
s 00001/00001/00040
d D 4.5 82/11/06 17:55:16 rrh 5 4
c Change location of style1, style2, and style3 to be in /usr/lib
e
s 00006/00002/00035
d D 4.4 82/11/06 17:13:32 rrh 4 3
c Change so default macro package is -me; added -me, -ma and -k flags
c for deroff
e
s 00002/00006/00035
d D 4.3 82/11/06 17:08:09 rrh 3 2
c Change path to deroff so deroff is taken from /usr/bin
e
s 00019/00007/00022
d D 4.2 82/11/06 14:35:19 rrh 2 1
c Bill Jolitz @ Berkeley received this version from Lorindia Cherry
c around September 1981, as the ``most recent version''.  Deltas 
c seem to be progressive, rather than regressive, although the BTL sid for
c deroff.c is retrograde; this is probably a case of parallel development
e
s 00029/00000/00000
d D 4.1 82/11/06 13:48:42 rrh 1 0
c Oldest available version at Berkeley
e
u
U
t
T
I 1
D 8
#! /bin/sh
E 8
I 8
#!/bin/sh -
E 8
#
D 8
#	%W%	(Berkeley)	%E%
E 8
I 8
# %sccs.include.proprietary.sh%
E 8
#
I 8
#	%W% (Berkeley) %G%
#

E 8
D 2
B=/usr/lib
echo $*
E 2
I 2
D 5
L=/usr/lib/style
E 5
I 5
D 6
L=/usr/lib
E 5
D 3
C=/usr/llc/collect/scatch
if test -w $C
then
echo $HOME $* `date` >>$C 2>/dev/null
fi
E 3
I 3
B=/usr/bin
E 6
I 6
L=/usr/libexec
D 9
B=/usr/ucb
E 9
I 9
B=/usr/bin
E 9
E 6
E 3
echo " " $*
E 2
sflag=-s
I 2
eflag=
Pflag=
nflag=
E 2
lflag=
lcon=
rflag=
rcon=
D 4
mflag=-ms
E 4
I 4
mflag=-me
E 4
D 2
mlflag=
eflag=
Pflag=
E 2
I 2
mlflag=-ml
I 4
kflag=
E 4
E 2
for i in $*
do case $i in
-r) rflag=-r; shift; rcon=$1;shift;continue;;
-l)lflag=-l; shift; lcon=$1;shift;continue;;
-mm) mflag=-mm;shift;continue;;
-ms) mflag=-ms;shift;continue;;
I 4
-me) mflag=-me;shift;continue;;
-ma) mflag=-ma;shift;continue;;
E 4
D 2
-ml) mlflag=-ml;shift;continue;;
E 2
I 2
-li|-ml) mlflag=-ml;shift;continue;;
+li|-tt)mlflag=;shift;continue;;
E 2
-p) sflag=-p;shift;continue;;
-a) sflag=-a;shift;continue;;
-e) eflag=-e;shift;continue;;
-P) Pflag=-P;shift;continue;;
I 2
-n) nflag=-n;shift;continue;;
-N) nflag=-N;shift;continue;;
I 4
-k) kflag=-k;shift;continue;;
E 4
-flags) echo $0 "[-flags] [-r num] [-l num] [-e] [-p] [-n] [-N] [-a] [-P] [-mm|-ms] [-li|+li] [file ...]";exit;;
-*) echo unknown style flag $i; exit;;
*) break;;
E 2
esac
done
D 2
$B/deroff $mflag $mlflag $*^$B/style1^$B/style2^$B/style3 $rflag $rcon $lflag $lcon $sflag $eflag $Pflag
E 2
I 2
D 3
deroff $mflag $mlflag $*^$L/style1^$L/style2^$L/style3 $rflag $rcon $lflag $lcon $sflag $nflag $eflag $Pflag
E 3
I 3
D 4
$B/deroff $mflag $mlflag $*^$L/style1^$L/style2^$L/style3 $rflag $rcon $lflag $lcon $sflag $nflag $eflag $Pflag
E 4
I 4
D 7
$B/deroff $kflag $mflag $mlflag $*^$L/style1^$L/style2^$L/style3 $rflag $rcon $lflag $lcon $sflag $nflag $eflag $Pflag
E 7
I 7
$B/deroff $kflag $mflag $mlflag $* | $L/style1 | $L/style2 | $L/style3 $rflag $rcon $lflag $lcon $sflag $nflag $eflag $Pflag
E 7
E 4
E 3
E 2
E 1
