h31968
s 00000/00000/00011
d D 8.1 93/05/31 18:42:53 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00008/00046/00003
d D 5.4 90/05/11 12:45:06 bostic 4 3
c first pass for new make
e
s 00002/00001/00047
d D 5.3 90/02/13 16:18:48 bostic 3 2
c new version
e
s 00001/00001/00047
d D 5.2 89/07/30 13:12:14 bostic 2 1
c needs libcompat
e
s 00048/00000/00000
d D 5.1 88/10/19 15:55:40 bostic 1 0
c date and time created 88/10/19 15:55:40 by bostic
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
SRCS=	wump.c
OBJS=
MAN=	wump.0
E 4
I 4
PROG=	wump
MAN6=	wump.0
HIDEGAME=hidegame
E 4

D 4
all: wump
E 4
I 4
beforeinstall:
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${.CURDIR}/wump.info \
	    ${DESTDIR}/usr/share/games
E 4

D 4
wump: ${LIBC}
D 2
	${CC} -o $@ ${CFLAGS} $@.c
E 2
I 2
D 3
	${CC} -o $@ ${CFLAGS} $@.c -lcompat
E 3
I 3
	${CC} -o $@ ${CFLAGS} $@.c
E 3
E 2

clean:
	rm -f ${OBJS} core wump

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
	install -s -o bin -g bin -m 755 wump ${DESTDIR}/usr/games
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat6
I 3
	install -c -o bin -g bin -m 444 wump.info ${DESTDIR}/usr/share/games
E 3

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 4
I 4
.include <bsd.prog.mk>
E 4
E 1
