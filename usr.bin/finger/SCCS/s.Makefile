h40722
s 00000/00000/00006
d D 8.1 93/06/06 14:39:34 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00003/00045/00003
d D 5.3 90/05/11 15:14:19 bostic 3 2
c first pass for new make
e
s 00005/00009/00043
d D 5.2 89/05/10 15:37:15 bostic 2 1
c cleanup, don't install link to "f"
e
s 00048/00000/00000
d D 5.1 88/09/20 16:58:20 bostic 1 0
c date and time created 88/09/20 16:58:20 by bostic
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
E 3
I 3
PROG=	finger
E 3
D 2
SRCS=	finger.c
OBJS=
E 2
I 2
SRCS=	finger.c lprint.c net.c sprint.c util.c
D 3
OBJS=	finger.o lprint.o net.o sprint.o util.o
E 2
MAN=	finger.0
E 3

D 3
all: finger

D 2
finger: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c
E 2
I 2
finger: ${LIBC} ${OBJS}
	${CC} -o $@ ${CFLAGS} ${OBJS}
E 2

clean:
	rm -f ${OBJS} core finger

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 2
	install -s -o bin -g bin -m 755 finger ${DESTDIR}/usr/ucb/finger
E 2
I 2
	install -s -o bin -g bin -m 755 finger ${DESTDIR}/usr/bin
E 2
	install -c -o bin -g bin -m 444 finger.0 ${DESTDIR}/usr/man/cat1
D 2
	rm -f ${DESTDIR}/usr/ucb/f
	ln ${DESTDIR}/usr/ucb/finger ${DESTDIR}/usr/ucb/f
	rm -f ${DESTDIR}/usr/man/cat1/f.0
	ln ${DESTDIR}/usr/man/cat1/finger.0 ${DESTDIR}/usr/man/cat1/f.0
E 2

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 3
I 3
.include <bsd.prog.mk>
E 3
E 1
