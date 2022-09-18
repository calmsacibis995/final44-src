h20359
s 00008/00019/00029
d D 5.3 90/05/24 21:05:00 bostic 3 2
c new copyright notice
e
s 00001/00001/00047
d D 5.2 89/09/05 20:59:41 bostic 2 1
c reorg
e
s 00048/00000/00000
d D 5.1 89/03/13 21:20:05 bostic 1 0
c date and time created 89/03/13 21:20:05 by bostic
e
u
U
t
T
I 1
D 3
#!/bin/sh -
#
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.
#
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
#
#	%W% (Berkeley) %G%
#
E 3
I 3
/*-
 * Copyright (c) 1987 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */
E 3

# program to link to
D 2
RSH=/usr/ucb/rsh
E 2
I 2
RSH=/usr/bin/rsh
E 2

# address search pattern to recognize local hosts
LOCALADDR='^128\.32'

# awk pattern for uninteresting (eg, long form) alias
SKIP='/^ucb|\.berkeley\.edu$|^$/'

# Special entries that don't get generated normally
SPECIAL='ucbvax ucbarpa'

rm -rf TMP_HOSTS hosts.bak
mkdir TMP_HOSTS
cd TMP_HOSTS

for i in `egrep "$LOCALADDR" ${DESTDIR}/etc/hosts | awk "\\$2 !~ $SKIP {print \\$2} \\$3 !~ $SKIP {print \\$3} \\$4 !~ $SKIP {print \\$4}"`; do
	ln -s $RSH $i
done

for i in $SPECIAL; do
	ln -s $RSH $i
done

cd ..
mv hosts hosts.bak
mv TMP_HOSTS hosts
rm -rf hosts.bak
E 1
