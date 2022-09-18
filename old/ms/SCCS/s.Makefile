h38215
s 00002/00000/00018
d D 5.7 91/10/07 21:06:09 cael 7 6
c merged into /usr/old/lib tree
e
s 00001/00001/00017
d D 5.6 91/01/02 12:37:47 karels 6 5
c add tmac.sU
e
s 00002/00001/00016
d D 5.5 90/06/08 14:37:08 bostic 5 4
c don't need obj, use bsd.prog.mk
e
s 00004/00001/00013
d D 5.4 90/06/02 17:47:33 karels 4 3
c reorg; insert keyworks
e
s 00007/00024/00007
d D 5.3 90/05/11 13:57:01 bostic 3 2
c first pass for new make
e
s 00016/00015/00015
d D 5.2 89/05/10 22:43:48 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00030/00000/00000
d D 5.1 89/04/13 10:02:06 bostic 1 0
c date and time created 89/04/13 10:02:06 by bostic
e
u
U
t
T
I 1
D 3
#
D 2
# Copyright (c) 1988 Regents of the University of California.
E 2
I 2
# Copyright (c) 1989 The Regents of the University of California.
E 2
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
D 2
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific written prior permission. This software
# is provided ``as is'' without express or implied warranty.
E 2
I 2
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
E 2
#
E 3
D 2
#	@(#)Makefile	5.1 (Berkeley) 5/21/88
E 2
I 2
#	%W% (Berkeley) %G%
E 2
D 3
#
D 2
MSLIB=	/usr/lib/ms
TMLIB=	/usr/lib/tmac
E 2
I 2
MSLIB=	/usr/share/ms
TMLIB=	/usr/share/tmac
E 3
I 3

E 3
E 2
MSSRCS=	acc.ms cov.ms eqn.ms ref.ms tbl.ms ths.ms toc.ms
D 4
TMSRCS=	tmac.os tmac.s
E 4
I 4
D 6
TMSRCS=	tmac.s tmac.os tmac.scover
E 6
I 6
TMSRCS=	tmac.s tmac.os tmac.scover tmac.sU
E 6
I 5
NOOBJ=	noobj
E 5

# sources for old tmac.*, previously installed in /usr/lib/tmac
OSRCS=	tmac.sdisp tmac.skeep tmac.srefs
E 4

D 2
all:
E 2
I 2
all clean cleandir depend lint tags:
E 2

D 2
install: FRC
E 2
I 2
install:
E 2
D 3
	-[ -d ${DESTDIR}${MSLIB} ] || mkdir ${DESTDIR}${MSLIB}
	chown bin.bin ${DESTDIR}${MSLIB}
	chmod 755 ${DESTDIR}${MSLIB}
	install -c -o bin -g bin -m 444 ${MSSRCS} ${DESTDIR}${MSLIB}
	install -c -o bin -g bin -m 444 ${TMSRCS} ${DESTDIR}${TMLIB}
E 3
I 3
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${MSSRCS} \
	    ${DESTDIR}${BINDIR}/ms
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${TMSRCS} \
	    ${DESTDIR}${BINDIR}/tmac

I 7
BINDIR?=        /usr/old/lib

E 7
D 5
.include <bsd.own.mk>
E 5
I 5
.include <bsd.prog.mk>
E 5
E 3
D 2

clean:
depend:
FRC:
E 2
E 1
