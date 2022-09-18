h46457
s 00000/00000/00011
d D 8.1 93/06/02 18:19:42 mckusick 14 13
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00010
d D 5.11 93/06/02 18:19:30 mckusick 13 11
c devname moves to libc
e
s 00000/00000/00011
d R 8.1 93/05/31 15:07:08 bostic 12 11
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00009
d D 5.10 93/04/27 18:15:26 bostic 11 10
c pwcache(3) now in the C library
e
s 00002/00002/00009
d D 5.9 92/04/08 08:26:12 bostic 10 9
c use -lkvm, now
e
s 00001/00001/00010
d D 5.8 92/04/03 14:55:46 mckusick 9 8
c update from Steve McCanne for Sun compatible kvm
e
s 00001/00000/00010
d D 5.7 91/11/12 12:46:52 bostic 8 7
c get vm include files from /sys
e
s 00000/00001/00010
d D 5.6 91/11/04 22:26:47 bostic 7 6
c ps doesn't need -I/sys
e
s 00001/00000/00010
d D 5.5 91/04/23 19:07:25 bostic 6 5
c needs machine dependent includes
e
s 00001/00001/00009
d D 5.4 91/02/08 13:21:08 bostic 5 3
c new list of files
e
s 00001/00000/00010
d R 5.4 91/01/15 13:55:35 bostic 4 3
c kernel reorg
e
s 00008/00046/00002
d D 5.3 90/05/11 12:39:50 bostic 3 2
c first pass for new make
e
s 00005/00005/00043
d D 5.2 90/03/12 16:35:51 mckusick 2 1
c update for new ps structure
e
s 00048/00000/00000
d D 5.1 88/10/18 22:07:11 bostic 1 0
c date and time created 88/10/18 22:07:11 by bostic
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
D 2
SRCS=	ps.c
OBJS=
E 2
I 2
SRCS= ps.c devname.c attime.c
OBJS= ps.o devname.o attime.o
E 2
MAN=	ps.0
E 3
I 3
PROG=	ps
D 5
SRCS=	ps.c devname.c attime.c proc_compare.c
E 5
I 5
D 9
SRCS=	devname.c keyword.c nlist.c print.c ps.c
E 9
I 9
D 13
SRCS=	devname.c fmt.c keyword.c nlist.c print.c ps.c
E 13
I 13
SRCS=	fmt.c keyword.c nlist.c print.c ps.c
E 13
E 9
I 8
CFLAGS+=-I/sys
E 8
I 6
D 7
CFLAGS+=-I/sys
E 7
E 6
E 5
D 10
DPADD=	${LIBMATH} ${LIBUTIL}
LDADD=	-lm -lutil
E 10
I 10
D 11
DPADD=	${LIBMATH} ${LIBKVM} ${LIBUTIL}
LDADD=	-lm -lkvm -lutil
E 11
I 11
DPADD=	${LIBMATH} ${LIBKVM}
LDADD=	-lm -lkvm
E 11
E 10
BINGRP=	kmem
BINMODE=2555
E 3

D 3
all: ps

D 2
ps: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c -lm
E 2
I 2
ps: ${OBJS} ${LIBC}
	${CC} -o $@ ${CFLAGS} ${OBJS} -lm -lutil
E 2

clean:
D 2
	rm -f ${OBJS} core ps
E 2
I 2
	rm -f ${OBJDIR}*.o core ps
E 2

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
	install -s -o bin -g kmem -m 2755 ps ${DESTDIR}/bin/ps
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
