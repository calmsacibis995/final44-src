h28232
s 00000/00000/00013
d D 8.1 93/05/31 16:21:41 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00004/00000/00009
d D 5.3 92/05/14 13:26:25 bostic 3 2
c add rot13 shell script
e
s 00007/00049/00002
d D 5.2 90/05/11 12:44:46 bostic 2 1
c first pass for new make
e
s 00051/00000/00000
d D 5.1 89/09/05 15:46:39 bostic 1 0
c date and time created 89/09/05 15:46:39 by bostic
e
u
U
t
T
I 1
D 2
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
E 2
I 2
#	%W% (Berkeley) %G%
E 2

D 2
CFLAGS=	-O
LIBC=	/lib/libc.a
SRCS=	caesar.c
OBJS=
MAN=	caesar.0
E 2
I 2
PROG=	caesar
MAN6=	caesar.0
DPADD=	${LIBM}
LDADD=	-lm
MLINKS=	caesar.6 rot13.6
E 2

I 3
beforeinstall:
	install -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${.CURDIR}/rot13.sh ${DESTDIR}/usr/games/rot13

E 3
D 2
all: caesar

caesar: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c -lm

clean:
	rm -f ${OBJS} core caesar

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
	install -s -o bin -g bin -m 755 caesar ${DESTDIR}/usr/games
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat6
	rm -f ${DESTDIR}/usr/man/cat6/rot13
	ln ${DESTDIR}/usr/man/cat6/${MAN} ${DESTDIR}/usr/man/cat6/rot13.0

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}

E 2
I 2
.include <bsd.prog.mk>
E 2
E 1
