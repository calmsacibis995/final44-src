h45232
s 00004/00001/00024
d D 5.2 88/10/31 22:50:13 bostic 2 1
c cleandir should actually do something
e
s 00025/00000/00000
d D 5.1 88/10/19 13:14:08 bostic 1 0
c date and time created 88/10/19 13:14:08 by bostic
e
u
U
t
T
I 1
#
# Copyright (c) 1988 The Regents of the University of California.
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
MAN=	mklost+found.0

D 2
all mklost+found clean cleandir depend lint tags:
E 2
I 2
all mklost+found clean depend lint tags:

cleandir:
	rm -f ${MAN}
E 2

install: ${MAN}
	install -c -o bin -g bin -m 755 mklost+found.sh ${DESTDIR}/etc/mklost+found
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat8
E 1
