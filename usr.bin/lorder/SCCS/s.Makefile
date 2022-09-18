h06500
s 00000/00000/00017
d D 8.1 93/06/06 15:01:42 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00016
d D 5.3 90/05/18 10:25:03 bostic 3 2
c need man suffix rules
e
s 00014/00022/00003
d D 5.2 90/05/11 13:49:59 bostic 2 1
c first pass for new make
e
s 00025/00000/00000
d D 5.1 88/10/22 16:09:30 bostic 1 0
c date and time created 88/10/22 16:09:30 by bostic
e
u
U
t
T
I 1
D 2
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
E 2
#	%W% (Berkeley) %G%
D 2
#
MAN=	lorder.0
E 2

D 2
all lorder clean cleandir depend lint tags:
E 2
I 2
MAN1=	lorder.0
E 2

D 2
install: ${MAN}
	install -c -o bin -g bin -m 755 lorder.sh ${DESTDIR}/usr/bin/lorder
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
E 2
I 2
all lorder: ${MAN1}

clean depend lint tags:

cleandir:
	rm -f ${MAN1}

install: maninstall
	install -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${.CURDIR}/lorder.sh ${DESTDIR}/${BINDIR}/lorder

D 3
.include <bsd.own.mk>
E 3
I 3
.include <bsd.prog.mk>
E 3
.include <bsd.man.mk>
E 2
E 1
