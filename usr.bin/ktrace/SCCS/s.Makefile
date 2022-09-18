h62961
s 00000/00000/00006
d D 8.1 93/06/06 14:53:33 bostic 13 12
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00001/00006
d D 5.6 93/06/02 17:19:37 bostic 12 11
c move up a level
e
s 00000/00001/00007
d D 5.5 93/02/15 10:06:28 ralph 11 10
c don't need to include /sys
e
s 00001/00000/00007
d D 5.4 91/11/11 11:47:00 bostic 10 9
c -I/sys for now, user.h has <vm/*> includes
e
s 00000/00001/00007
d D 5.3 91/04/27 16:22:18 bostic 9 8
c don't need user.h anymore
e
s 00001/00000/00007
d D 5.2 91/04/27 16:16:09 bostic 8 7
c needs -I/sys for pcb.h
e
s 00000/00000/00007
d D 5.1 91/01/17 17:30:52 bostic 7 5
c yank to 5.1
e
s 00001/00000/00007
d R 5.1 91/01/15 14:13:37 bostic 6 5
c kernel reorg
e
s 00005/00052/00002
d D 1.5 90/05/11 14:58:40 bostic 5 4
c first pass for new make
e
s 00002/00002/00052
d D 1.4 90/05/11 14:51:29 marc 4 3
c checkpoint for pmake
e
s 00004/00005/00050
d D 1.3 90/03/23 10:41:11 bostic 3 2
c check in for Marc, so can modify for pmake
e
s 00011/00008/00044
d D 1.2 88/12/21 19:04:27 marc 2 1
c changed interface, first "official" version
e
s 00052/00000/00000
d D 1.1 88/12/14 16:21:45 marc 1 0
c date and time created 88/12/14 16:21:45 by marc
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
# @(#)Makefile	5.1 (Berkeley) 10/22/88
#
E 5
I 5
#	%W% (Berkeley) %G%
E 5

D 5
CFLAGS=	-O
D 4
LIBC=	/lib/libc.a
E 4
I 4
LIBC=	/usr/lib/libc.a
E 4
D 2
SRCS=	ktrace.c kdump.c
OBJS=
MAN=
E 2
I 2
SRCS=	ktrace.c kdump.c subr.c ioctl.c
D 3
OBJS=	ktrace.o kdump.o subr.o	ioctl.o
E 3
I 3
OBJS=	ktrace.o kdump.o subr.o ioctl.o
E 3
MAN=	ktrace.0 kdump.0
E 5
I 5
PROG=	ktrace
SRCS=	ktrace.c subr.c
I 10
D 11
CFLAGS+=-I/sys				# XXX
E 11
E 10
I 8
D 9
CFLAGS+=-I/sys
E 9
E 8
E 5
E 2

D 5
all: ktrace kdump

D 2
ktrace: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c
E 2
I 2
ktrace: ${LIBC} subr.o
	${CC} -o $@ ${CFLAGS} $@.c subr.o
E 2

D 2
kdump: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c
E 2
I 2
kdump: ${LIBC} ioctl.o subr.o
	${CC} -o $@ ${CFLAGS} $@.c ioctl.o subr.o
E 2

I 2
ioctl.c: mkioctls
D 3
	./mkioctls > ioctl.c
E 3
I 3
D 4
	/bin/sh ./mkioctls > ioctl.c
E 4
I 4
	/bin/sh ${.CURDIR}/mkioctls > ioctl.c
E 4
E 3

E 2
clean:
	rm -f ${OBJS} core ktrace kdump

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 3
	install -s -o bin -g bin -m 755 ktrace ${DESTDIR}/usr/bin
	install -s -o bin -g bin -m 755 kdump ${DESTDIR}/usr/bin
D 2
	#install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
E 2
I 2
	: install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
E 3
I 3
	install -s -o bin -g bin -m 755 ktrace kdump ${DESTDIR}/usr/bin
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
E 3
E 2

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 5
I 5
D 12
.include "../../Makefile.inc"
E 12
.include <bsd.prog.mk>
E 5
E 1
