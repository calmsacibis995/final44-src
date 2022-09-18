h48772
s 00000/00000/00010
d D 8.1 93/06/06 14:59:47 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00006/00054/00004
d D 5.2 90/05/11 15:13:15 bostic 2 1
c first pass for new make
e
s 00056/00000/00000
d D 5.1 90/03/06 11:23:44 bostic 1 0
c date and time created 90/03/06 11:23:44 by bostic
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
CFLAGS=	-O
LIBC=	/usr/lib/libc.a
SRCS=	locate.c bigram.c code.c
OBJS=	locate.o bigram.o code.o
MAN=	locate.0
E 2

D 2
all: locate bigram code
E 2
I 2
PROG=	locate
E 2

D 2
bigram code locate:${LIBC}
	${CC} ${CFLAGS} -o $@ $@.c
E 2
I 2
beforeinstall:
	install -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${.CURDIR}/updatedb.csh ${DESTDIR}/usr/libexec/locate.updatedb
E 2

D 2
clean:
	rm -f ${OBJS} core locate bigram code

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
	install -s -o bin -g bin -m 755 locate ${DESTDIR}/usr/bin
	install -s -o bin -g bin -m 755 code \
	    ${DESTDIR}/usr/libexec/locate.code
	install -s -o bin -g bin -m 755 bigram \
	    ${DESTDIR}/usr/libexec/locate.bigram
	install -c -o bin -g bin -m 755 updatedb.csh \
	    ${DESTDIR}/usr/libexec/locate.updatedb
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1

lint: ${SRCS}
	lint ${CFLAGS} locate.c
	lint ${CFLAGS} bigram.c
	lint ${CFLAGS} code.c

tags: ${SRCS}
	ctags locate.c
	ctags -a bigram.c
	ctags -a code.c
	sort -o tags tags
E 2
I 2
.include "../../Makefile.inc"
.include <bsd.prog.mk>
E 2
E 1
