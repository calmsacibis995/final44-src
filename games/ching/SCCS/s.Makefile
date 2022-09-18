h41136
s 00000/00000/00012
d D 8.1 93/05/31 16:46:47 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00002/00011
d D 5.3 90/07/01 10:52:02 bostic 3 2
c do it right.
e
s 00008/00045/00005
d D 5.2 90/05/11 12:45:01 bostic 2 1
c first pass for new make
e
s 00050/00000/00000
d D 5.1 88/10/19 20:06:20 bostic 1 0
c date and time created 88/10/19 20:06:20 by bostic
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
E 2

D 2
CFLAGS=	-O
LIBC=	/lib/libc.a
SRCS=	cno.c phx.c
OBJS=
MAN=	ching.0
E 2
I 2
SUBDIR=	cno phx
E 2
D 3

D 2
all: cno phx
E 2
I 2
all: ching.0
E 3
I 3
MAN6=	ching.0
E 3
E 2

D 2
cno phx: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c
E 2
I 2
beforeinstall:
	install -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${.CURDIR}/ching.sh ${DESTDIR}/usr/games/ching
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${.CURDIR}/hexagrams \
	    ${.CURDIR}/macros ${DESTDIR}/usr/share/games/ching
E 2

D 2
clean:
	rm -f ${OBJS} core cno phx

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
	install -c -o bin -g bin -m 755 ching.sh ${DESTDIR}/usr/games/ching
	-[ -d ${DESTDIR}/usr/games/ching.d ] || mkdir ${DESTDIR}/usr/games/ching.d
	install -s -o bin -g bin -m 755 cno phx ${DESTDIR}/usr/games/ching.d
	install -c -o bin -g bin -m 444 hexagrams macros ${DESTDIR}/usr/games/ching.d

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 2
I 2
.include <bsd.prog.mk>
E 2
E 1
