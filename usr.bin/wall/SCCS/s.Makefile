h34801
s 00000/00000/00008
d D 8.1 93/06/06 22:23:17 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00005/00045/00003
d D 5.4 90/05/11 14:11:42 bostic 4 3
c first pass for new make
e
s 00005/00004/00043
d D 5.3 90/04/03 20:06:18 bostic 3 2
c add ttymsg, minor cleanups
e
s 00002/00002/00045
d D 5.2 89/05/11 13:45:56 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00047/00000/00000
d D 5.1 88/09/18 17:00:37 bostic 1 0
c date and time created 88/09/18 17:00:37 by bostic
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
PROG=	wall
E 4
D 3
SRCS=	wall.c
E 3
I 3
SRCS=	ttymsg.c wall.c
D 4
OBJS=	ttymsg.o wall.o
E 3
MAN=	wall.0
E 4
I 4
BINGRP=	tty
BINMODE=2555
E 4

D 4
all: wall

D 3
wall: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c
E 3
I 3
wall: ${LIBC} ${OBJS}
	${CC} -o $@ ${CFLAGS} ${OBJS}
E 3

clean:
	rm -f ${OBJS} core wall

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
D 3
	mkdep -p ${CFLAGS} ${SRCS}
E 3
I 3
	mkdep ${CFLAGS} ${SRCS}
E 3

install: ${MAN}
D 2
	install -s -o bin -g tty -m 2755 wall ${DESTDIR}/bin/wall
	install -c -o bin -g bin -m 444 wall.0 ${DESTDIR}/usr/man/cat8/wall.0
E 2
I 2
	install -s -o bin -g tty -m 2755 wall ${DESTDIR}/usr/bin
	install -c -o bin -g bin -m 444 wall.0 ${DESTDIR}/usr/man/cat1
E 2

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 4
I 4
.include <bsd.prog.mk>
E 4
E 1
