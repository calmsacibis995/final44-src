h33874
s 00002/00002/00065
d D 8.1 93/06/06 15:31:09 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00003/00060
d D 5.6 93/01/23 12:56:01 bostic 6 5
c fix from Chris for expansion problem in previous version
e
s 00003/00007/00060
d D 5.5 92/12/01 20:16:15 bostic 5 4
c from Chris, handle gcc's that emit ./foo.h instead of just foo.h
e
s 00007/00002/00060
d D 5.4 91/09/23 14:53:57 bostic 4 3
c fix -p and include SED in compile statement so user can set SED
e
s 00000/00002/00062
d D 5.3 91/05/06 18:24:03 bostic 3 2
c don't toss arguments
e
s 00004/00013/00060
d D 5.2 91/04/12 16:43:20 bostic 2 1
c give all the versions their on SCCS id's
e
s 00073/00000/00000
d D 5.1 91/04/12 16:41:48 bostic 1 0
c date and time created 91/04/12 16:41:48 by bostic
e
u
U
t
T
I 1
#!/bin/sh -
#
D 2
# Copyright (c) 1987 Regents of the University of California.
E 2
I 2
D 7
# Copyright (c) 1991 The Regents of the University of California.
E 2
# All rights reserved.
E 7
I 7
# Copyright (c) 1991, 1993
#	The Regents of the University of California.  All rights reserved.
E 7
#
D 2
# Redistribution and use in source and binary forms are permitted
# provided that the above copyright notice and this paragraph are
# duplicated in all such forms and that any documentation,
# advertising materials, and other materials related to such
# distribution and use acknowledge that the software was developed
# by the University of California, Berkeley.  The name of the
# University may not be used to endorse or promote products derived
# from this software without specific prior written permission.
# THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
# WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
I 2
# %sccs.include.redist.sh%
E 2
#
D 2
#	@(#)mkdep.sh	5.18 (Berkeley) 3/5/89
E 2
I 2
#	%W% (Berkeley) %G%
E 2
#
I 2

E 2
PATH=/bin:/usr/bin:/usr/ucb
export PATH

D=.depend			# default dependency file is .depend
append=0
I 4
D 5
SED=
E 5
I 5
D 6
RM_DOT_O=
E 6
I 6
pflag=
E 6
E 5
E 4

while :
	do case "$1" in
		# -a appends to the depend file
		-a)
			append=1
			shift ;;

		# -f allows you to select a makefile name
		-f)
			D=$2
			shift; shift ;;

		# the -p flag produces "program: program.c" style dependencies
		# so .o's don't get produced
		-p)
D 4
			SED='s;\.o;;'
E 4
I 4
D 5
			SED=p
E 5
I 5
D 6
			RM_DOT_O="-e 's;\.o :; :;'"
E 6
I 6
			pflag=p
E 6
E 5
E 4
			shift ;;
D 3
		-*)
			shift ;;
E 3
		*)
			break ;;
	esac
done

if [ $# = 0 ] ; then
	echo 'usage: mkdep [-p] [-f depend_file] [cc_flags] file ...'
	exit 1
fi

TMP=/tmp/mkdep$$

trap 'rm -f $TMP ; exit 1' 1 2 3 13 15

D 4
cpp -M $* > $TMP
E 4
I 4
D 5
if [ "$SED"x = x ]; then
	cpp -M $* > $TMP
else
	cpp -M $* | sed 's;\.o :; :;' > $TMP
fi
E 5
I 5
D 6
cpp -M $* | sed $RM_DOT_O -e 's; \./; ;g' > $TMP
E 6
I 6
if [ x$pflag = x ]; then
	cpp -M $* | sed -e 's; \./; ;g' > $TMP
else
	cpp -M $* | sed -e 's;\.o :; :;' -e 's; \./; ;g' > $TMP
fi
E 6
E 5
E 4

if [ $? != 0 ]; then
	echo 'mkdep: compile failed.'
	rm -f $TMP
	exit 1
fi

if [ $append = 1 ]; then
	cat $TMP >> $D
	rm -f $TMP
else
	mv $TMP $D
fi
exit 0
E 1
