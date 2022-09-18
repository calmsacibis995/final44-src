h21340
s 00005/00002/00026
d D 4.8 91/04/17 17:12:32 bostic 8 7
c new copyright; att/bsd/shared
e
s 00001/00001/00027
d D 4.7 89/08/31 08:29:33 bostic 7 6
c ^ hasn't been the pipe character in a long while
e
s 00001/00001/00027
d D 4.6 89/05/11 09:46:36 bostic 6 5
c file reorg, pathnames.h, paths.h
e
s 00001/00001/00027
d D 4.5 82/11/06 17:54:54 rrh 5 4
c fix minor formatting botch
e
s 00006/00002/00022
d D 4.4 82/11/06 17:13:29 rrh 4 3
c Change so default macro package is -me; added -me, -ma and -k flags
c for deroff
e
s 00002/00001/00022
d D 4.3 82/11/06 17:08:06 rrh 3 2
c Change path to deroff so deroff is taken from /usr/bin
e
s 00001/00001/00022
d D 4.2 82/11/06 14:35:35 rrh 2 1
c Bill Jolitz @ Berkeley received this version from Lorindia Cherry
c around September 1981, as the ``most recent version''.  Deltas 
c seem to be progressive, rather than regressive, although the BTL sid for
c deroff.c is retrograde; this is probably a case of parallel development
e
s 00023/00000/00000
d D 4.1 82/11/06 13:48:39 rrh 1 0
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
I 3
D=/usr/bin
E 3
D 6
B=/usr/lib
E 6
I 6
B=/usr/libexec
E 6
echo $*
rest=
flag=
nflag=
D 4
mflag=-mm
E 4
I 4
mflag=-me
E 4
D 2
lflag=
E 2
I 2
D 5
lflag= -ml
E 5
I 5
lflag=-ml
E 5
I 4
kflag=
E 4
E 2
file=
for i
do case $i in
 -f) flag=-f;shift; file=$1; shift; continue;;
-n) nflag=-n;shift; continue;;
I 4
-k) kflag=-k;shift; continue;;
E 4
 -mm) mflag=$1; shift; continue;;
-ms) mflag=$1;shift;continue;;
I 4
-me) mflag=$1;shift;continue;;
-ma) mflag=$1;shift;continue;;
E 4
-ml) lflag=$1;shift;continue;;
*) rest=$*; break;;
esac
done
D 3
 $B/deroff $mflag $lflag $rest^$B/dprog -d $nflag $flag $file
E 3
I 3
D 4
 $D/deroff $mflag $lflag $rest^$B/dprog -d $nflag $flag $file
E 4
I 4
D 7
 $D/deroff $kflag $lflag $mflag $rest^$B/dprog -d $nflag $flag $file
E 7
I 7
 $D/deroff $kflag $lflag $mflag $rest | $B/dprog -d $nflag $flag $file
E 7
E 4
E 3
E 1
