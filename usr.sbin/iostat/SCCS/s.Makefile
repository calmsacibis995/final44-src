h56160
s 00000/00000/00011
d D 8.1 93/06/06 13:57:37 bostic 9 8
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00009
d D 5.7 92/06/23 10:57:12 mccanne 8 7
c use libkvm instead of libutil to get kvm
e
s 00003/00001/00008
d D 5.6 91/04/23 16:39:47 marc 7 6
c add libutil and -I vmstat for names.c module
e
s 00001/00000/00008
d D 5.5 91/01/17 14:49:45 bostic 6 4
c kernel reorg
e
s 00001/00000/00008
d R 5.5 91/01/14 18:02:54 bostic 5 4
c kernel reorg
e
s 00001/00000/00007
d D 5.4 90/06/25 17:56:29 bostic 4 3
c iostat man page is in section 8
e
s 00005/00046/00002
d D 5.3 90/05/11 16:39:51 bostic 3 2
c first pass for new make
e
s 00001/00001/00047
d D 5.2 89/05/11 14:08:17 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00048/00000/00000
d D 5.1 88/10/22 15:40:51 bostic 1 0
c date and time created 88/10/22 15:40:51 by bostic
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
SRCS=	iostat.c
OBJS=
MAN=	iostat.0
E 3
I 3
PROG=	iostat
I 6
D 7
CFLAGS+=-I/sys
E 7
I 7
CFLAGS+=-I/sys -I${.CURDIR}/../../usr.bin/vmstat
E 7
E 6
I 4
MAN8=	iostat.0
I 7
D 8
DPADD=	${LIBUTIL}
LDADD=	-lutil
E 8
I 8
DPADD=	${LIBKVM}
LDADD=	-lkvm
E 8
E 7
E 4
BINGRP=	kmem
BINMODE=2555
E 3

D 3
all: iostat

iostat: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c

clean:
	rm -f ${OBJS} core iostat

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 2
	install -s -o bin -g kmem -m 2755 iostat ${DESTDIR}/usr/bin
E 2
I 2
	install -s -o bin -g kmem -m 2755 iostat ${DESTDIR}/usr/sbin
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
