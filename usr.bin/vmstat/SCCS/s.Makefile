h13680
s 00000/00000/00011
d D 8.1 93/06/06 22:22:15 bostic 11 10
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00010
d D 5.9 92/06/23 10:51:40 mccanne 10 9
c oops, also need to change LIBUTIL to LIBKVM.
e
s 00001/00001/00010
d D 5.8 92/06/23 10:46:03 mccanne 9 8
c use libkvm instead of libutil to get kvm
e
s 00001/00000/00010
d D 5.7 91/04/24 12:30:57 bostic 8 7
c mv man page to section 8
e
s 00001/00001/00009
d D 5.6 91/04/23 17:15:59 bostic 7 6
c add names.c to dependency list
e
s 00001/00000/00009
d D 5.5 91/01/17 15:00:56 bostic 6 4
c kernel reorg
e
s 00001/00000/00009
d R 5.5 91/01/14 17:56:06 bostic 5 4
c kernel reorg
e
s 00002/00000/00007
d D 5.4 90/12/18 11:06:54 bostic 4 3
c make vmstat work on crash dumps (use kvm lib); vmstat -t doesn't work
c any more; make multiple options work; an incredible amount of lint.
c From Chris Torek
e
s 00005/00046/00002
d D 5.3 90/05/11 14:18:13 bostic 3 2
c first pass for new make
e
s 00001/00001/00047
d D 5.2 89/05/11 13:33:54 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00048/00000/00000
d D 5.1 88/10/21 13:42:03 bostic 1 0
c date and time created 88/10/21 13:42:03 by bostic
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
SRCS=	vmstat.c
OBJS=
MAN=	vmstat.0
E 3
I 3
PROG=	vmstat
I 6
CFLAGS+=-I/sys
I 8
MAN8=	vmstat.0
E 8
E 6
BINGRP=	kmem
BINMODE=2555
I 4
D 7
DPADD=	${LIBUTIL}
E 7
I 7
D 10
DPADD=	names.c ${LIBUTIL}
E 10
I 10
DPADD=	names.c ${LIBKVM}
E 10
E 7
D 9
LDADD=	-lutil
E 9
I 9
LDADD=	-lkvm
E 9
E 4
E 3

D 3
all: vmstat

vmstat: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c

clean:
	rm -f ${OBJS} core vmstat

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 2
	install -s -o bin -g kmem -m 2755 vmstat ${DESTDIR}/usr/ucb
E 2
I 2
	install -s -o bin -g kmem -m 2755 vmstat ${DESTDIR}/usr/bin
E 2
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 3
I 3
.include <bsd.prog.mk>
E 3
E 1
