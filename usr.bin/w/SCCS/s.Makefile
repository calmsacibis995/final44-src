h54610
s 00000/00000/00014
d D 8.1 93/06/06 22:22:54 bostic 11 10
c 4.4BSD snapshot (revision 8.1)
e
s 00003/00003/00011
d D 5.9 93/04/27 15:22:13 bostic 10 9
c getloadavg(3) is in libc, no longer need libutil
c rename attime.c to be pr_time.c, and put both "print time" routines there
e
s 00001/00001/00013
d D 5.8 92/04/13 20:12:33 mckusick 9 8
c add -lkvm
e
s 00003/00002/00011
d D 5.7 92/04/03 16:24:03 mckusick 8 7
c update from Steve McCanne for Sun compatible kvm
e
s 00001/00000/00012
d D 5.6 91/04/23 19:49:40 bostic 7 6
c needs include files from /sys
e
s 00001/00002/00011
d D 5.5 91/04/01 08:54:07 bostic 6 4
c ps no longer uses attime.c, put it in place here
e
s 00001/00000/00013
d R 5.5 91/01/14 17:56:54 bostic 5 4
c kernel reorg
e
s 00011/00049/00002
d D 5.4 90/05/11 14:18:07 bostic 4 3
c first pass for new make
e
s 00005/00004/00046
d D 5.3 90/04/03 20:04:02 bostic 3 2
c checked in for Marc; checkpoint for pmake
e
s 00003/00003/00047
d D 5.2 89/05/11 13:34:36 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00050/00000/00000
d D 5.1 88/10/21 15:17:39 bostic 1 0
c date and time created 88/10/21 15:17:39 by bostic
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
I 3
VPATH=	../../bin/ps
E 3
LIBC=	/lib/libc.a
D 3
SRCS=	w.c
OBJS=
E 3
I 3
SRCS=	w.c attime.c
OBJS=	w.o attime.o
E 3
MAN=	w.0 uptime.0
E 4
I 4
PROG=	w
D 6
SRCS=	w.c attime.c proc_compare.c
E 6
I 6
D 8
SRCS=	attime.c w.c proc_compare.c
I 7
CFLAGS+=-I/sys
E 8
I 8
D 10
SRCS=	attime.c fmt.c w.c proc_compare.c
E 10
I 10
SRCS=	fmt.c pr_time.c proc_compare.c w.c
E 10
E 8
E 7
E 6
MAN1=	w.0 uptime.0
D 10
DPADD=	${LIBUTIL}
D 9
LDADD=	-lutil
E 9
I 9
LDADD=	-lkvm -lutil
E 10
I 10
DPADD=	${LIBKVM}
LDADD=	-lkvm
E 10
E 9
BINGRP=	kmem
BINMODE=2555
LINKS=	${BINDIR}/w ${BINDIR}/uptime
I 8

.PATH: ${.CURDIR}/../../bin/ps
E 8
D 6
.PATH:	${.CURDIR}/../../bin/ps
E 6
E 4

D 4
all: w

D 3
w: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c
E 3
I 3
w: ${LIBC} ${OBJS}
	${CC} -o $@ ${CFLAGS} ${OBJS} -lutil
E 3

clean:
	rm -f ${OBJS} core w

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 2
	install -s -o bin -g kmem -m 2755 w ${DESTDIR}/usr/ucb/w
	rm -f ${DESTDIR}/usr/ucb/uptime
	ln ${DESTDIR}/usr/ucb/w ${DESTDIR}/usr/ucb/uptime
E 2
I 2
	install -s -o bin -g kmem -m 2755 w ${DESTDIR}/usr/bin
	rm -f ${DESTDIR}/usr/bin/uptime
	ln ${DESTDIR}/usr/bin/w ${DESTDIR}/usr/bin/uptime
E 2
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 4
I 4
.include <bsd.prog.mk>
E 4
E 1
