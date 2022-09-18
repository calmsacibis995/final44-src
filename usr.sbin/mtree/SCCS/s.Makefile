h05693
s 00001/00000/00008
d D 8.2 95/04/27 15:37:18 bostic 8 7
c mtree man page installs in wrong cat directory
c From: Chris Torek <torek@BSDI.COM>
e
s 00000/00000/00008
d D 8.1 93/06/06 14:03:29 bostic 7 6
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00007
d D 5.6 92/02/19 12:19:40 bostic 6 5
c change CFLAGS
e
s 00003/00002/00005
d D 5.5 91/12/11 17:56:10 bostic 5 4
c version 2; add cksum, make keywords flexible, new output format
e
s 00001/00004/00006
d D 5.4 90/05/25 13:53:39 bostic 4 3
c rename some files, don't need tbl anymore
e
s 00006/00046/00004
d D 5.3 90/05/11 16:40:23 bostic 3 2
c first pass for new make
e
s 00003/00000/00047
d D 5.2 90/04/28 15:08:45 bostic 2 1
c add tbl for man page
e
s 00047/00000/00000
d D 5.1 89/09/04 16:24:58 bostic 1 0
c date and time created 89/09/04 16:24:58 by bostic
e
u
U
t
T
I 1
D 3
#
# Copyright (c) 1989 The Regents of the University of California.
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
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
#
E 3
#	%W% (Berkeley) %G%
D 3
#
CFLAGS=	-O
LIBC=	/lib/libc.a
E 3
I 3

PROG=	mtree
I 8
MAN8=	mtree.0
E 8
E 3
D 4
SRCS=	compare.c cwalk.c mtree.c spec.c util.c
E 4
I 4
D 5
SRCS=	compare.c create.c mtree.c spec.c verify.c
E 4
D 3
OBJS=	compare.o cwalk.o mtree.o spec.o util.o
MAN=	mtree.0
E 3
I 3
.PATH:	${.CURDIR}
E 5
I 5
D 6
CFLAGS=-O
E 6
I 6
#CFLAGS+=-DDEBUG
E 6
SRCS=	compare.c crc.c create.c misc.c mtree.c spec.c verify.c
.PATH:	${.CURDIR}/../../usr.bin/cksum
E 5
E 3
D 4

D 3
all: mtree
E 3
I 3
mtree.0: mtree.1
	tbl ${.CURDIR}/mtree.1 | nroff -h -man > $@
E 4
E 3

D 3
mtree: ${OBJS} ${LIBC}
	${CC} -o $@ ${CFLAGS} ${OBJS}

clean:
	rm -f ${MAN} ${OBJS} core mtree

cleandir:
	rm -f ${OBJS} core mtree tags .depend

depend: ${SRCS}
	mkdep ${CFLAGS} ${SRCS}

install: ${MAN}
	install -s -o bin -g bin -m 755 mtree ${DESTDIR}/usr/sbin
	install -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1

I 2
mtree.0:
	tbl mtree.1 | nroff -h -man > $@

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
