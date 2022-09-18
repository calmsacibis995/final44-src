h49757
s 00000/00000/00011
d D 8.1 93/07/19 09:41:01 bostic 8 7
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00001/00009
d D 5.6 93/07/19 09:40:56 bostic 7 5
c set the immutable bit on installation
e
s 00000/00000/00010
d R 8.1 93/06/05 11:00:35 bostic 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00009
d D 5.5 93/03/03 15:22:48 mckusick 5 4
c make -DSECURE on by default
e
s 00001/00000/00009
d D 5.4 92/07/19 17:00:13 marc 4 3
c make prompting for shell the default
e
s 00006/00045/00003
d D 5.3 90/05/11 13:05:20 bostic 3 2
c first pass for new make
e
s 00001/00001/00047
d D 5.2 89/05/11 13:53:58 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00048/00000/00000
d D 5.1 88/08/31 12:18:57 bostic 1 0
c date and time created 88/08/31 12:18:57 by bostic
e
u
U
t
T
I 1
D 3
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
E 3
#	%W% (Berkeley) %G%
D 3
#
CFLAGS=	-O
LIBC=	/lib/libc.a
SRCS=	init.c
OBJS=
MAN=	init.0
MAN8=	/usr/man/cat8/
E 3

D 3
all: init
E 3
I 3
PROG=	init
MAN8=	init.0
DPADD=	${LIBUTIL}
LDADD=	-lutil
BINMODE=500
I 4
D 5
CFLAGS += -DDEBUGSHELL
E 5
I 5
D 7
CFLAGS += -DDEBUGSHELL -DSECURE
E 7
I 7
INSTALLFLAGS=-fschg
CFLAGS+=-DDEBUGSHELL -DSECURE
E 7
E 5
E 4
E 3

D 3
init: ${SRCS} ${LIBC}
	${CC} -o $@ ${CFLAGS} ${SRCS} -lutil

cleandir: clean
	rm -f tags .depend

clean:
	rm -f ${OBJS} core init ${MAN}

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 2
	install -s -o bin -g bin -m 700 init ${DESTDIR}/etc/init
E 2
I 2
	install -s -o bin -g bin -m 700 init ${DESTDIR}/sbin/init
E 2
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}${MAN8}${MAN}

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 3
I 3
.include <bsd.prog.mk>
E 3
E 1
