h24367
s 00002/00002/00021
d D 8.1 93/06/06 14:31:24 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00003/00018
d D 5.3 91/04/17 17:10:44 bostic 3 2
c new copyright; att/bsd/shared
e
s 00007/00003/00014
d D 5.2 89/05/11 09:46:43 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00017/00000/00000
d D 5.1 89/04/18 15:49:46 bostic 1 0
c date and time created 89/04/18 15:49:46 by bostic
e
u
U
t
T
I 1
D 2
#! /bin/sh
E 2
I 2
#!/bin/sh -
E 2
#
D 2
#	@(#)suggest.sh	4.4	(Berkeley)	82/11/06
E 2
I 2
D 3
# Copyright (c) 1988 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 3
I 3
D 4
# Copyright (c) 1988 The Regents of the University of California.
# All rights reserved.
E 4
I 4
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
E 4
E 3
E 2
#
I 3
# %sccs.include.proprietary.sh%
#
E 3
I 2
#	%W% (Berkeley) %G%
#
I 3

E 3
E 2
trap 'rm $$; exit' 1 2 3 15
D 2
D=/usr/lib/explain.d
E 2
I 2
D=/usr/share/dict/explain.d
E 2
while echo "phrase?";read x
do
cat >$$ <<dn
/$x.*	/s/\(.*\)	\(.*\)/use "\2" for "\1"/p
dn
case $x in
[a-z]*)
sed -n -f $$ $D; rm $$;;
*) rm $$;;
esac
done
E 1
