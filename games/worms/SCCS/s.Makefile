h18402
s 00000/00000/00008
d D 8.1 93/05/31 18:42:25 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00006/00046/00002
d D 5.3 90/05/11 12:45:31 bostic 3 2
c first pass for new make
e
s 00001/00001/00047
d D 5.2 89/07/30 13:11:38 bostic 2 1
c needs libcompat
e
s 00048/00000/00000
d D 5.1 88/10/19 15:54:46 bostic 1 0
c date and time created 88/10/19 15:54:46 by bostic
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
SRCS=	worms.c
OBJS=
MAN=	worms.0
E 3
I 3
PROG=	worms
MAN6=	worms.0
DPADD=	${LIBCURSES} ${LIBTERM} ${LIBCOMPAT}
LDADD=	-lcurses -ltermcap -lcompat
E 3

D 3
all: worms

worms: ${LIBC}
D 2
	${CC} -o $@ ${CFLAGS} $@.c -lcurses -ltermcap
E 2
I 2
	${CC} -o $@ ${CFLAGS} $@.c -lcurses -ltermcap -lcompat
E 2

clean:
	rm -f ${OBJS} core worms

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
	install -s -o bin -g bin -m 755 worms ${DESTDIR}/usr/games
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
