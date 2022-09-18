h22102
s 00000/00000/00017
d D 8.1 93/06/05 13:43:27 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00011/00024/00006
d D 5.4 90/05/11 13:56:31 bostic 4 3
c first pass for new make
e
s 00008/00019/00022
d D 5.3 89/03/06 10:58:02 bostic 3 2
c move man pages into source tree
e
s 00010/00005/00031
d D 5.2 88/07/09 11:39:11 bostic 2 1
c install approved copyright notice
e
s 00036/00000/00000
d D 5.1 87/12/12 18:20:11 bostic 1 0
c date and time created 87/12/12 18:20:11 by bostic
e
u
U
t
T
I 1
D 4
#
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
D 2
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
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
D 3
# WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 3
I 3
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 3
E 2
#
E 4
#	%W% (Berkeley) %G%
D 4
#
D 3
MDIR=	/usr/man/cat4/tahoe
SRCS=	ace.4 autoconf.4 cons.4 cy.4 dr.4 enp.4 ik.4 intro.4 lp.4 mem.4 \
	mpcc.4 mpcctab.4 mtio.4 vd.4 vx.4
E 3
I 3
MDIR=	${DESTDIR}/usr/man/cat4/tahoe
E 3
OBJS=	ace.0 autoconf.0 cons.0 cy.0 dr.0 enp.0 ik.0 intro.0 lp.0 mem.0 \
E 4
I 4

MAN4=	ace.0 autoconf.0 cons.0 cy.0 dr.0 enp.0 ik.0 intro.0 lp.0 mem.0 \
E 4
D 3
	mpcc.0 mpcctab.0 mtio.0 vd.0 vx.0
LINKS=	kmem.0
E 3
I 3
	mtio.0 vd.0 vx.0
I 4
MLINKS=	mem.4 kmem.4
MANSUBDIR=/tahoe
E 4
E 3

D 3
.SUFFIXES: .4 .0
E 3
I 3
D 4
all clean depend lint tags:
E 4
I 4
all: ${MAN4}
E 4
E 3

I 4
clean depend lint tags:

E 4
D 3
.4.0:
	${DESTDIR}/usr/man/manroff $*.4 > $*.0

all: ${OBJS}

clean: FRC
E 3
I 3
cleandir:
E 3
D 4
	rm -f ${OBJS}
E 4
I 4
	rm -f ${MAN4}
E 4

D 3
install: FRC
	cd ${DESTDIR}${MDIR}; rm -f *.0
	install -c -o bin -g bin -m 444 ${OBJS} ${DESTDIR}${MDIR}
	ln ${DESTDIR}${MDIR}/mem.0 ${DESTDIR}${MDIR}/kmem.0

FRC:
E 3
I 3
D 4
install: ${OBJS}
	install -c -o bin -g bin -m 444 ${OBJS} ${MDIR}
	rm -f ${MDIR}/kmem.0; ln ${MDIR}/mem.0 ${MDIR}/kmem.0
E 4
I 4
install: maninstall

.include <bsd.prog.mk>
E 4
E 3
E 1
