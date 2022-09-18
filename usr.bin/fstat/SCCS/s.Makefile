h21689
s 00000/00000/00010
d D 8.1 93/06/06 14:40:38 bostic 12 11
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00002/00010
d D 5.10 93/06/02 19:06:33 mckusick 11 10
c devname moves to libc
e
s 00002/00002/00010
d D 5.9 93/04/27 18:17:31 bostic 10 9
c pwcache(3) now in the C library
e
s 00002/00002/00010
d D 5.8 92/06/08 13:26:35 bostic 9 8
c add kvm library
e
s 00001/00000/00011
d D 5.7 92/01/09 16:32:32 marc 8 7
c -I/sys
e
s 00000/00001/00011
d D 5.6 91/11/04 22:33:12 bostic 7 6
c break FFS into UFS/FFS/LFS; doesn't need -I/sys any more
e
s 00001/00000/00011
d D 5.5 91/04/23 16:16:09 bostic 6 4
c needs -I/sys for machine depend includes
e
s 00001/00000/00011
d R 5.5 91/01/15 14:12:48 bostic 5 4
c kernel reorg
e
s 00008/00046/00003
d D 5.4 90/05/11 15:18:21 bostic 4 3
c first pass for new make
e
s 00005/00004/00044
d D 5.3 90/04/02 21:52:18 bostic 3 2
c checked in for Marc, checkpoint for pmake
e
s 00001/00001/00047
d D 5.2 89/05/11 09:41:29 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00048/00000/00000
d D 5.1 88/10/19 11:18:23 bostic 1 0
c date and time created 88/10/19 11:18:23 by bostic
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
VPATH= ../../bin/ps
E 3
LIBC=	/lib/libc.a
E 4
I 4
PROG=	fstat
E 4
D 3
SRCS=	fstat.c
OBJS=
E 3
I 3
D 11
SRCS=	fstat.c devname.c
I 6
D 7
CFLAGS+=-I/sys
E 7
E 6
D 4
OBJS=	fstat.o devname.o
E 3
MAN=	fstat.0
E 4
I 4
.PATH:	${.CURDIR}/../../bin/ps
E 11
I 8
CFLAGS+=-I/sys
E 8
D 9
DPADD=	${LIBUTIL}
LDADD=	-lutil
E 9
I 9
D 10
DPADD=	${LIBKVM} ${LIBUTIL}
LDADD=	-lkvm -lutil
E 10
I 10
DPADD=	${LIBKVM}
LDADD=	-lkvm
E 10
E 9
BINGRP=	kmem
BINMODE=2555
E 4

D 4
all: fstat

D 3
fstat: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c
E 3
I 3
fstat: ${LIBC} ${OBJS}
	${CC} -o $@ ${CFLAGS} $@.c -lutil
E 3

clean:
	rm -f ${OBJS} core fstat

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 2
	install -s -o bin -g kmem -m 2755 fstat ${DESTDIR}/etc/fstat
E 2
I 2
	install -s -o bin -g kmem -m 2755 fstat ${DESTDIR}/usr/bin
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
