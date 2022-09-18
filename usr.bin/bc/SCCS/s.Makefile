h51579
s 00000/00000/00012
d D 8.1 93/06/06 14:24:33 bostic 7 6
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00011
d D 5.6 91/03/01 13:45:48 bostic 6 5
c not worth fixing, but don't want to see the errors either
e
s 00002/00002/00010
d D 5.5 90/06/23 14:53:55 bostic 5 4
c move lib.b to bc.library
e
s 00008/00045/00004
d D 5.4 90/05/11 15:57:38 bostic 4 3
c first pass for new make
e
s 00000/00000/00049
d D 5.3 90/03/24 10:43:21 bostic 3 2
c checkpoint for pmake
e
s 00001/00000/00048
d D 5.2 89/05/10 22:45:52 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00048/00000/00000
d D 5.1 88/10/22 15:50:18 bostic 1 0
c date and time created 88/10/22 15:50:18 by bostic
e
u
U
t
T
I 1
D 4
#
# Copyright (c) 1988 Regents of the University of California.
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
# provided that the above copyright notice and this paragraph are
# duplicated in all such forms and that any documentation, advertising
# materials, and other materials related to such redistribution and
# use acknowledge that the software was developed by the University
# of California, Berkeley.  The name of the University may not be
# used to endorse or promote products derived from this software
# without specific prior written permission.  THIS SOFTWARE IS PROVIDED
# ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
# WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND
# FITNESS FOR A PARTICULAR PURPOSE.
#
# %W% (Berkeley) %G%
#
E 4
I 4
#	%W% (Berkeley) %G%
E 4

D 4
CFLAGS=	-O
LIBC=	/lib/libc.a
E 4
I 4
PROG=	bc
E 4
SRCS=	bc.c
D 4
OBJS=
MAN=	bc.0
E 4
I 4
D 6
CFLAGS+=-I${.CURDIR}
E 6
I 6
CFLAGS+=-w -I${.CURDIR}
E 6
D 5
CLEANFILES=	bc.c
E 5
I 5
CLEANFILES=	bc.c y.tab.h
E 5
E 4

D 4
all: bc
E 4
I 4
beforeinstall:
D 5
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${.CURDIR}/lib.b \
E 5
I 5
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${.CURDIR}/bc.library \
E 5
	    ${DESTDIR}/usr/share/misc
E 4

D 4
bc: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c

clean:
	rm -f ${OBJS} core bc bc.c

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
	install -s -o bin -g bin -m 755 bc ${DESTDIR}/usr/bin
I 2
	install -c -o bin -g bin -m 444 lib.b ${DESTDIR}/usr/share/misc
E 2
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 4
I 4
.include <bsd.prog.mk>
E 4
E 1
