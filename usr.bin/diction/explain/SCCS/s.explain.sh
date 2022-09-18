h50382
s 00000/00000/00015
d D 8.1 93/06/06 14:33:00 bostic 8 7
c 4.4BSD snapshot (revision 8.1)
e
s 00005/00002/00010
d D 4.7 91/04/17 17:13:16 bostic 7 6
c new copyright; att/bsd/shared
e
s 00001/00001/00011
d D 4.6 89/05/11 09:46:38 bostic 6 5
c file reorg, pathnames.h, paths.h
e
s 00005/00010/00007
d D 4.5 83/05/27 17:05:29 ralph 5 4
c simpified version which doesn't use temporary files.
e
s 00000/00000/00017
d D 4.4 82/11/06 17:13:35 rrh 4 3
c Change so default macro package is -me; added -me, -ma and -k flags
c for deroff
e
s 00000/00000/00017
d D 4.3 82/11/06 17:08:12 rrh 3 2
c Change path to deroff so deroff is taken from /usr/bin
e
s 00000/00000/00017
d D 4.2 82/11/06 14:35:13 rrh 2 1
c Bill Jolitz @ Berkeley received this version from Lorindia Cherry
c around September 1981, as the ``most recent version''.  Deltas 
c seem to be progressive, rather than regressive, although the BTL sid for
c deroff.c is retrograde; this is probably a case of parallel development
e
s 00017/00000/00000
d D 4.1 82/11/06 13:48:41 rrh 1 0
c Oldest available version at Berkeley
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
# %sccs.include.proprietary.sh%
E 7
#
I 7
#	%W% (Berkeley) %G%
#

E 7
D 5
trap 'rm $$; exit' 1 2 3 15
E 5
D 6
D=/usr/lib/explain.d
E 6
I 6
D=/usr/share/dict/explain.d
E 6
D 5
while echo "phrase?";read x
E 5
I 5
while	echo 'phrase?'
	read x
E 5
do
D 5
cat >$$ <<dn
/$x.*	/s/\(.*\)	\(.*\)/use "\2" for "\1"/p
dn
case $x in
[a-z]*)
sed -n -f $$ $D; rm $$;;
*) rm $$;;
esac
E 5
I 5
	case $x in
	[a-z]*)	sed -n /"$x"'.*	/s/\(.*\)	\(.*\)/use "\2" for "\1"/p' $D
	esac
E 5
done
E 1
