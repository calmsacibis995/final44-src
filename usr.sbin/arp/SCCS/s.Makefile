h39318
s 00007/00000/00006
d D 8.2 94/04/18 16:41:06 bostic 6 5
c use mandoc macros for arp.4, update the Makefil to install it
e
s 00000/00000/00006
d D 8.1 93/06/06 13:50:33 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00002/00006
d D 5.4 92/01/28 14:24:15 bostic 4 3
c doesn't need setgid kmem anymore
e
s 00006/00046/00002
d D 5.3 90/05/11 16:41:07 bostic 3 2
c first pass for new make
e
s 00001/00001/00047
d D 5.2 89/05/11 14:05:38 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00048/00000/00000
d D 5.1 88/09/19 21:19:44 bostic 1 0
c date and time created 88/09/19 21:19:44 by bostic
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
SRCS=	arp.c
OBJS=
MAN=	arp.0
E 3
I 3
PROG=	arp
D 4
BINGRP=	kmem
BINMODE=2555
E 4
MAN8=	arp.0
I 6
CLEANFILES=arp4.0

all: ${PROG} arp4.0 ${MAN8}

beforeinstall:
	install -c -o ${MANOWN} -g ${MANGRP} -m ${MANMODE} arp4.0 \
	    ${DESTDIR}${MANDIR}4/arp.0
E 6
E 3

D 3
all: arp

arp: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c

clean:
	rm -f ${OBJS} core arp

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 2
	install -s -o bin -g kmem -m 2755 arp ${DESTDIR}/etc/arp
E 2
I 2
	install -s -o bin -g kmem -m 2755 arp ${DESTDIR}/usr/sbin
E 2
	install -c -o bin -g bin -m 444 arp.0 ${DESTDIR}/usr/man/cat8

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 3
I 3
.include <bsd.prog.mk>
E 3
E 1
