h32687
s 00001/00017/00010
d D 5.2 91/07/01 14:42:22 bostic 2 1
c makefiles don't get copyrights
e
s 00027/00000/00000
d D 5.1 89/03/29 12:25:39 bostic 1 0
c date and time created 89/03/29 12:25:39 by bostic
e
u
U
t
T
I 1
D 2
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
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
#
E 2
#	%W% (Berkeley) %G%
D 2
#
E 2
I 2

E 2
MAN=	lisp.0 liszt.0 lxref.0

all clean depend lint tags:

cleandir:
	rm -f ${MAN}

install: ${MAN}
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
E 1
