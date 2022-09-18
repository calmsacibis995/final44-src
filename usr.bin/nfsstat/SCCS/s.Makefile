h23788
s 00000/00000/00010
d D 8.1 93/06/06 15:45:38 bostic 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00008
d D 5.4 92/06/18 12:12:48 bostic 5 4
c kvm has its own library now
e
s 00002/00000/00008
d D 5.3 91/07/01 18:59:41 marc 4 2
c kvm
e
s 00001/00001/00007
d R 5.3 91/01/15 14:14:25 bostic 3 2
c kernel reorg
e
s 00006/00046/00002
d D 5.2 90/05/11 15:18:49 bostic 2 1
c first pass for new make
e
s 00048/00000/00000
d D 5.1 89/07/16 15:54:08 mckusick 1 0
c date and time created 89/07/16 15:54:08 by mckusick
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
CFLAGS=	-O -DNFS
LIBC=	/lib/libc.a
SRCS=	nfsstat.c
OBJS=
MAN=	nfsstat.0
E 2
I 2
PROG=	nfsstat
CFLAGS+=-DNFS
I 4
D 5
DPADD=  ${LIBUTIL}
LDADD= -lutil
E 5
I 5
DPADD=  ${LIBKVM}
LDADD= -lkvm
E 5
E 4
BINGRP=	kmem
BINMODE=2555
E 2

D 2
all: nfsstat

nfsstat: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c

clean:
	rm -f ${OBJS} core nfsstat

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
	install -s -o bin -g kmem -m 2755 nfsstat ${DESTDIR}/usr/bin
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 2
I 2
.include <bsd.prog.mk>
E 2
E 1
