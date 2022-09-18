h59258
s 00000/00000/00010
d D 8.1 93/06/05 10:51:32 bostic 8 7
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00008
d D 5.7 92/05/26 15:14:18 bostic 7 6
c kvm is in its own library now
e
s 00002/00000/00008
d D 5.6 91/05/02 19:29:30 bostic 6 5
c Rewrite from scratch, add Berkeley specific copyright.
c Delete the "-" option, don't display a timestamp.  Do avoid nonprintable
c characters, work on dead kernels
c 
e
s 00001/00000/00007
d D 5.5 90/07/25 22:14:53 bostic 5 4
c mv man page to section 8
e
s 00005/00046/00002
d D 5.4 90/05/11 13:04:01 bostic 4 3
c first pass for new make
e
s 00001/00001/00047
d D 5.3 89/05/15 08:30:39 bostic 3 2
c move dmesg to /sbin
e
s 00001/00001/00047
d D 5.2 89/05/11 14:07:22 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00048/00000/00000
d D 5.1 88/10/19 11:04:48 bostic 1 0
c date and time created 88/10/19 11:04:48 by bostic
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
LIBC=	/lib/libc.a
SRCS=	dmesg.c
OBJS=
MAN=	dmesg.0
E 4
I 4
PROG=	dmesg
I 5
MAN8=	dmesg.0
E 5
BINGRP=	kmem
BINMODE=2555
I 6
D 7
LDADD=	-lutil
DPADD=	${LIBUTIL}
E 7
I 7
LDADD=	-lkvm
DPADD=	${LIBKVM}
E 7
E 6
E 4

D 4
all: dmesg

dmesg: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c

clean:
	rm -f ${OBJS} core dmesg

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 2
	install -s -o bin -g kmem -m 2755 dmesg ${DESTDIR}/etc
E 2
I 2
D 3
	install -s -o bin -g kmem -m 2755 dmesg ${DESTDIR}/usr/sbin
E 3
I 3
	install -s -o bin -g kmem -m 2755 dmesg ${DESTDIR}/sbin
E 3
E 2
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat8

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 4
I 4
.include <bsd.prog.mk>
E 4
E 1
