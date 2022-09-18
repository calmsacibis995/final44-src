h00427
s 00000/00000/00012
d D 8.1 93/06/06 16:37:24 bostic 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00009/00048/00003
d D 5.5 90/05/11 14:15:04 bostic 5 4
c first pass for new make
e
s 00002/00000/00049
d D 5.4 89/10/30 17:14:43 bostic 4 3
c link man page tput to clear
e
s 00007/00006/00042
d D 5.3 89/10/30 17:10:24 bostic 3 2
c replace clear with tput
e
s 00001/00001/00047
d D 5.2 89/05/11 09:42:19 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00048/00000/00000
d D 5.1 88/10/21 13:44:14 bostic 1 0
c date and time created 88/10/21 13:44:14 by bostic
e
u
U
t
T
I 1
D 5
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
E 5
I 5
#	%W% (Berkeley) %G%
E 5

D 5
CFLAGS=	-O
LIBC=	/lib/libc.a
D 3
SRCS=	clear.c
E 3
I 3
SRCS=	tput.c
E 3
OBJS=
D 3
MAN=	clear.0
E 3
I 3
MAN=	tput.0
E 5
I 5
PROG=	tput
DPADD=	${LIBTERMCAP}
LDADD=	-ltermcap
MLINKS=	tput.1 clear.1
E 5
E 3

D 3
all: clear
E 3
I 3
D 5
all: tput
E 5
I 5
beforeinstall:
	install -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${.CURDIR}/clear.sh ${DESTDIR}/usr/bin/clear
E 5
E 3

D 3
clear: ${LIBC}
E 3
I 3
D 5
tput: ${LIBC}
E 3
	${CC} -o $@ ${CFLAGS} $@.c -ltermcap

clean:
D 3
	rm -f ${OBJS} core clear
E 3
I 3
	rm -f ${OBJS} core tput
E 3

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 2
	install -s -o bin -g bin -m 755 clear ${DESTDIR}/usr/ucb
E 2
I 2
D 3
	install -s -o bin -g bin -m 755 clear ${DESTDIR}/usr/bin
E 3
I 3
	install -s -o bin -g bin -m 755 tput ${DESTDIR}/usr/bin
	install -c -o bin -g bin -m 755 clear.sh ${DESTDIR}/usr/bin/clear
E 3
E 2
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
I 4
	rm -f ${DESTDIR}/usr/man/cat1/clear.0
	ln ${DESTDIR}/usr/man/cat1/tput.0 ${DESTDIR}/usr/man/cat1/clear.0
E 4

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 5
I 5
.include <bsd.prog.mk>
E 5
E 1
