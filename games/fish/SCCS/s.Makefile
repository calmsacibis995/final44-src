h56358
s 00000/00000/00011
d D 8.1 93/05/31 16:53:34 bostic 8 7
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00001/00009
d D 5.7 92/09/02 11:50:04 bostic 7 6
c do it right
e
s 00001/00001/00009
d D 5.6 92/09/02 11:46:46 bostic 6 5
c missing ${DESTDIR}
e
s 00003/00002/00007
d D 5.5 91/01/18 23:17:47 bostic 5 4
c new version
e
s 00001/00000/00008
d D 5.4 90/07/25 22:15:39 bostic 4 3
c move man page to section 6
e
s 00006/00046/00002
d D 5.3 90/05/11 12:45:10 bostic 3 2
c first pass for new make
e
s 00001/00001/00047
d D 5.2 89/07/30 12:26:44 bostic 2 1
c needs libcompat
e
s 00048/00000/00000
d D 5.1 88/10/19 15:34:26 bostic 1 0
c date and time created 88/10/19 15:34:26 by bostic
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
SRCS=	fish.c
OBJS=
MAN=	fish.0
E 3
I 3
PROG=	fish
I 4
MAN6=	fish.0
E 4
D 5
DPADD=	${LIBCOMPAT}
LDADD=	-lcompat
E 5
HIDEGAME=hidegame
I 5

beforeinstall: 
D 6
	install -c -o bin -g bin -m 444 ${.CURDIR}/fish.instr /usr/share/games
E 6
I 6
D 7
	install -c -o bin -g bin -m 444 ${.CURDIR}/fish.instr ${DESTDIR}/usr/share/games
E 7
I 7
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${.CURDIR}/fish.instr \
	    ${DESTDIR}/usr/share/games/fish.instr
E 7
E 6
E 5
E 3

D 3
all: fish

fish: ${LIBC}
D 2
	${CC} -o $@ ${CFLAGS} $@.c
E 2
I 2
	${CC} -o $@ ${CFLAGS} $@.c -lcompat
E 2

clean:
	rm -f ${OBJS} core fish

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
	install -s -o bin -g bin -m 755 fish ${DESTDIR}/usr/games
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat6

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 3
I 3
.include <bsd.prog.mk>
E 3
E 1
