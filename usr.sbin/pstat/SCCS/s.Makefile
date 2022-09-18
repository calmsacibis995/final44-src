h52450
s 00000/00000/00010
d D 8.1 93/06/06 14:04:05 bostic 9 8
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00003/00010
d D 5.7 93/06/04 17:34:35 mckusick 8 7
c devname moves to libc
e
s 00003/00003/00010
d D 5.6 93/04/27 10:18:58 bostic 7 6
c doesn't need libutil
e
s 00001/00001/00012
d D 5.5 93/04/03 12:12:07 mckusick 6 5
c add kvm library
e
s 00001/00000/00012
d D 5.4 91/06/26 14:01:23 marc 5 3
c -I/sys
e
s 00001/00000/00012
d R 5.4 91/01/14 17:54:07 bostic 4 3
c kernel reorg
e
s 00010/00046/00002
d D 5.3 90/05/11 15:58:15 bostic 3 2
c first pass for new make
e
s 00001/00001/00047
d D 5.2 89/05/10 22:45:03 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00048/00000/00000
d D 5.1 88/10/19 11:49:36 bostic 1 0
c date and time created 88/10/19 11:49:36 by bostic
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
SRCS=	pstat.c
OBJS=
MAN=	pstat.0
E 3
I 3
PROG=	pstat
I 5
D 7
CFLAGS+= -I/sys
E 7
I 7
CFLAGS+=-I/sys
E 7
E 5
D 8
SRCS=	pstat.c devname.c
.PATH:	${.CURDIR}/../../bin/ps
MAN8=	pstat.0
E 8
D 7
DPADD= ${LIBUTIL}
D 6
LDADD=	-lutil
E 6
I 6
LDADD=	-lutil -lkvm
E 7
E 6
BINGRP=	kmem
BINMODE=2555
I 7
DPADD=	${LIBKVM}
LDADD=	-lkvm
E 7
E 3

D 3
all: pstat

pstat: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c

clean:
	rm -f ${OBJS} core pstat

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 2
	install -s -o bin -g kmem -m 2755 pstat ${DESTDIR}/etc
E 2
I 2
	install -s -o bin -g kmem -m 2755 pstat ${DESTDIR}/usr/bin
E 2
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat8

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 3
I 3
.include <bsd.prog.mk>
E 3
E 1
