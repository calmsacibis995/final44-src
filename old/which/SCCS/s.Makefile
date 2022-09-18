h20951
s 00000/00004/00009
d D 5.5 90/07/01 10:27:34 bostic 5 4
c don't need to specify these targets
e
s 00003/00003/00010
d D 5.4 90/05/24 15:30:45 bostic 4 3
c fix install
e
s 00011/00022/00003
d D 5.3 90/05/11 15:19:07 bostic 3 2
c first pass for new make
e
s 00001/00001/00024
d D 5.2 89/05/11 09:39:51 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00025/00000/00000
d D 5.1 88/10/21 15:25:10 bostic 1 0
c date and time created 88/10/21 15:25:10 by bostic
e
u
U
t
T
I 1
D 3
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
E 3
#	%W% (Berkeley) %G%
D 3
#
MAN=	which.0
E 3

D 3
all which clean cleandir depend lint tags:
E 3
I 3
MAN1=	which.0
E 3

D 3
install: ${MAN}
D 2
	install -c -o bin -g bin -m 755 which.csh ${DESTDIR}/usr/ucb/which
E 2
I 2
	install -c -o bin -g bin -m 755 which.csh ${DESTDIR}/usr/bin/which
E 2
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
E 3
I 3
D 4
all: ${MAN1}
E 4
I 4
D 5
all which: ${MAN1}
E 4

D 4
which clean cleandir depend lint tags:
E 4
I 4
clean cleandir depend lint tags:
E 4

E 5
D 4
install: maninstall
E 4
I 4
beforeinstall:
E 4
	install -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${.CURDIR}/which.csh ${DESTDIR}${BINDIR}/which

.include <bsd.prog.mk>
E 3
E 1
