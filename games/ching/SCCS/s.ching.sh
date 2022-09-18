h20506
s 00002/00002/00021
d D 8.1 93/05/31 16:46:52 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00003/00019
d D 4.5 91/04/08 17:28:53 bostic 5 4
c new copyright; att/bsd/shared
e
s 00005/00004/00017
d D 4.4 90/04/30 22:06:02 bostic 4 3
c move data files to /usr/share/games/ching
e
s 00013/00008/00008
d D 4.3 88/10/19 20:03:54 bostic 3 2
c copyright notice, handle PAGER correctly, minor cleanups
e
s 00005/00002/00011
d D 4.2 83/05/19 12:03:39 peter 2 1
c pipe reading through more.
c confusion since cno and more can't both be reading from stdin
c in the same pipeline.
c thus the hacker placates the seekers.
e
s 00013/00000/00000
d D 4.1 82/10/27 17:43:20 peter 1 0
c date and time created 82/10/27 17:43:20 by peter
e
u
U
t
T
I 1
D 3
#! /bin/sh
E 3
I 3
#!/bin/sh -
E 3
#
D 3
#	%W%	(Berkeley)	%E%
E 3
I 3
D 5
# Copyright (c) 1988 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 5
I 5
D 6
# Copyright (c) 1983, 1988 The Regents of the University of California.
# All rights reserved.
E 6
I 6
# Copyright (c) 1983, 1988, 1993
#	The Regents of the University of California.  All rights reserved.
E 6
#
# %sccs.include.proprietary.sh%
E 5
E 3
#
D 3
cd /usr/games/lib/ching.d
PATH=:$PATH
E 3
I 3
#	%W% (Berkeley) %G%
#

D 4
cd /usr/games/ching.d
E 4
I 4
cd /usr/games
DIR=/usr/share/games/ching
E 4
E 3
case $1 in
	[6-9]*)	H=$1;shift;;
esac
D 3
if	test $H
D 2
then	phx $H | nroff $* macros -
else	cno | phx | nroff $* macros -
E 2
I 2
then	phx $H | nroff $* macros - | more -s
else	cno > "/tmp/#$$" 
E 3
I 3
if test $H; then
D 4
	./phx $H | nroff $* macros - | ${PAGER-more}
E 4
I 4
	./ching.phx $H | nroff $* $DIR/macros - | ${PAGER-more}
E 4
else
D 4
	./cno > "/tmp/#$$"
E 4
I 4
	./ching.cno > "/tmp/#$$"
E 4
E 3
	echo "  "
D 3
	phx < "/tmp/#$$" | nroff $* macros - | more -s
E 3
I 3
D 4
	./phx < "/tmp/#$$" | nroff $* macros - | ${PAGER-more}
E 4
I 4
	./ching.phx < "/tmp/#$$" | nroff $* $DIR/macros - | ${PAGER-more}
E 4
E 3
	rm "/tmp/#$$"
E 2
fi
E 1
