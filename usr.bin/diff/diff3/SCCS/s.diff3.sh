h09112
s 00002/00002/00025
d D 8.1 93/06/06 14:37:36 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00002/00019
d D 4.3 91/04/17 17:20:21 bostic 3 2
c new copyright; att/bsd/shared
e
s 00001/00001/00020
d D 4.2 89/05/11 09:47:25 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00021/00000/00000
d D 4.1 83/02/10 21:00:50 shannon 1 0
c date and time created 83/02/10 21:00:50 by shannon
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
#	%M%	%I%	%E%
E 3
I 3
D 4
# Copyright (c) 1991 The Regents of the University of California.
# All rights reserved.
E 4
I 4
# Copyright (c) 1991, 1993
#	The Regents of the University of California.  All rights reserved.
E 4
E 3
#
I 3
# %sccs.include.proprietary.sh%
#
#	%W% (Berkeley) %G%
#

E 3
e=
case $1 in
-*)
	e=$1
	shift;;
esac
if test $# = 3 -a -f $1 -a -f $2 -a -f $3
then
	:
else
	echo usage: diff3 file1 file2 file3 1>&2
	exit
fi
trap "rm -f /tmp/d3[ab]$$" 0 1 2 13 15
diff $1 $3 >/tmp/d3a$$
diff $2 $3 >/tmp/d3b$$
D 2
/usr/lib/diff3 $e /tmp/d3[ab]$$ $1 $2 $3
E 2
I 2
/usr/libexec/diff3 $e /tmp/d3[ab]$$ $1 $2 $3
E 2
E 1
