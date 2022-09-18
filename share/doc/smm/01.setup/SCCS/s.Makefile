h53322
s 00000/00000/00015
d D 8.1 93/07/27 18:58:57 mckusick 8 7
c 4.4BSD snapshot (revision 8.1)
e
s 00012/00002/00003
d D 5.5 93/07/09 21:13:56 mckusick 7 5
c first pass at getting updated for 4.4BSD
e
s 00000/00000/00005
d R 8.1 93/06/08 17:21:16 bostic 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00010/00003
d D 5.4 93/06/08 17:21:11 bostic 5 3
c make it (mostly) work
e
s 00000/00000/00013
d R 8.1 93/06/08 13:56:25 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00012
d D 5.3 93/06/05 16:40:06 bostic 3 2
c new doc.mk; document numbering changes for 4.4BSD
e
s 00009/00023/00004
d D 5.2 90/06/30 15:04:42 bostic 2 1
c this isn't right, but checkpoint for June tape
e
s 00027/00000/00000
d D 5.1 88/07/17 09:37:22 karels 1 0
c date and time created 88/07/17 09:37:22 by karels
e
u
U
t
T
I 1
D 2
#
# Copyright (c) 1988 Regents of the University of California.
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
E 2

D 2
all:
	cd ${MACHINE}; make ${MFLAGS}
E 2
I 2
D 5
DIR=	smm/01.setup
SRCS=	0.t 1.t 2.t 3.t 4.t 5.t 6.t a.t b.t
.if ${MACHINE} == "vax"
SRCS+=	c.t
.endif
.PATH:	${.CURDIR}/${MACHINE} ${.CURDIR}/common
E 5
I 5
D 7
SUBDIR=	tahoe vax
E 7
I 7
DIR=	smm/01.setup
SRCS=	0.t 1.t 2.t 3.t 4.t 5.t 6.t
FILES=	${SRCS}
MACROS=	-ms
E 7
E 5
E 2

D 2
setup:
	cd ${MACHINE}; make ${MFLAGS} setup
E 2
I 2
D 3
paper.${PRINTER}: ${SRCS}
E 3
I 3
D 5
paper.ps: ${SRCS}
E 3
	${EQN} ${.ALLSRC} | ${TBL} | ${ROFF} > ${.TARGET}
E 2

D 2
setup.out:
	cd ${MACHINE}; make ${MFLAGS} setup.out
E 2
I 2
.include <bsd.doc.mk>
E 5
I 5
D 7
.include <bsd.subdir.mk>
E 7
I 7
paper.ps: ${SRCS}
	${TBL} ${SRCS} | ${ROFF} > ${.TARGET}

install: ${SRCS}
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 \
	    Makefile ${FILES} ${EXTRA} ${DESTDIR}${BINDIR}/${DIR}

.include <bsd.doc.mk>
E 7
E 5
E 2
E 1
