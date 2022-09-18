h42177
s 00005/00003/00004
d D 5.6 93/03/05 10:24:54 bostic 6 5
c replace machine.c with a shell script that calls uname
e
s 00001/00000/00006
d D 5.5 91/11/26 10:36:50 bostic 5 4
c link in arch man page
e
s 00001/00000/00005
d D 5.4 91/11/25 15:23:24 bostic 4 3
c link arch to machine
e
s 00003/00046/00002
d D 5.3 90/05/11 14:32:25 bostic 3 2
c first pass for new make
e
s 00001/00001/00047
d D 5.2 89/05/11 09:58:22 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00048/00000/00000
d D 5.1 88/10/18 21:46:12 bostic 1 0
c date and time created 88/10/18 21:46:12 by bostic
e
u
U
t
T
I 1
D 3
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
E 3
I 3
#	%W% (Berkeley) %G%
E 3

D 3
CFLAGS=	-O
LIBC=	/lib/libc.a
SRCS=	machine.c
OBJS=
MAN=	machine.0
E 3
I 3
D 6
PROG=	machine
I 4
LINKS=	${BINDIR}/machine ${BINDIR}/arch
I 5
MLINKS=	machine.1 arch.1
E 6
I 6
MAN1=	machine.0

beforeinstall:
	install -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${.CURDIR}/machine.sh ${DESTDIR}${BINDIR}/machine
E 6
E 5
E 4
E 3

D 3
all: machine

machine: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c

clean:
	rm -f ${OBJS} core machine

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 2
	install -s -o bin -g bin -m 755 machine ${DESTDIR}/bin
E 2
I 2
	install -s -o bin -g bin -m 755 machine ${DESTDIR}/usr/bin
E 2
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 3
I 3
.include <bsd.prog.mk>
E 3
E 1
