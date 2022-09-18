h37312
s 00000/00000/00010
d D 8.1 93/05/31 16:52:53 bostic 8 7
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00000/00009
d D 5.7 91/04/08 17:50:52 bostic 7 6
c link factor.6 and primes.6
e
s 00006/00051/00003
d D 5.6 90/05/11 12:45:27 bostic 6 5
c first pass for new make
e
s 00003/00001/00051
d D 5.5 90/02/01 10:26:44 bostic 5 4
c forgot primes manual page
e
s 00021/00022/00031
d D 5.4 90/02/01 10:22:52 bostic 4 3
c new version from Landon Curt Noll
e
s 00002/00000/00051
d D 5.3 89/05/11 13:49:04 bostic 3 2
c file reorg, pathnames.h, paths.h
e
s 00007/00004/00044
d D 5.2 88/10/19 15:48:06 bostic 2 1
c add primes
e
s 00048/00000/00000
d D 5.1 88/10/19 15:33:10 bostic 1 0
c date and time created 88/10/19 15:33:10 by bostic
e
u
U
t
T
I 1
D 6
#
D 4
# Copyright (c) 1988 Regents of the University of California.
E 4
I 4
# Copyright (c) 1989 The Regents of the University of California.
E 4
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
# provided that the above copyright notice and this paragraph are
D 4
# duplicated in all such forms and that any documentation, advertising
# materials, and other materials related to such redistribution and
# use acknowledge that the software was developed by the University
# of California, Berkeley.  The name of the University may not be
# used to endorse or promote products derived from this software
# without specific prior written permission.  THIS SOFTWARE IS PROVIDED
# ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
# WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND
# FITNESS FOR A PARTICULAR PURPOSE.
E 4
I 4
# duplicated in all such forms and that any documentation,
# advertising materials, and other materials related to such
# distribution and use acknowledge that the software was developed
# by the University of California, Berkeley.  The name of the
# University may not be used to endorse or promote products derived
# from this software without specific prior written permission.
# THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
#
E 6
D 4
# %W% (Berkeley) %G%
E 4
I 4
#	%W% (Berkeley) %G%
E 4
D 6
#
D 4

E 4
CFLAGS=	-O
LIBC=	/lib/libc.a
D 2
SRCS=	factor.c
E 2
I 2
D 4
SRCS=	factor.c primes.c
E 2
OBJS=
E 4
I 4
FSRCS=	factor.c pr_tbl.c
FOBJS=	factor.o pr_tbl.o
PSRCS=	primes.c pr_tbl.c pattern.c
POBJS=	primes.o pr_tbl.o pattern.o
E 4
MAN=	factor.0
E 6

D 2
all: factor
E 2
I 2
D 6
all: factor primes
E 6
I 6
PROG=	factor
SRCS=	factor.c pr_tbl.c
CFLAGS+=-I${.CURDIR}/../primes
MAN6=	factor.0
I 7
MLINKS+=factor.6 primes.6
E 7
.PATH:	${.CURDIR}/../primes
E 6
E 2

D 4
factor: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c
E 4
I 4
D 6
factor: ${LIBC} ${FOBJS}
	${CC} -o $@ ${CFLAGS} ${FOBJS}
E 4

I 2
D 4
primes: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c -lm
E 4
I 4
primes: ${LIBC} ${POBJS}
	${CC} -o $@ ${CFLAGS} ${POBJS} -lm
E 4

E 2
clean:
D 2
	rm -f ${OBJS} core factor
E 2
I 2
D 4
	rm -f ${OBJS} core factor primes
E 4
I 4
	rm -f ${FOBJS} ${POBJS} core factor primes
E 4
E 2

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 2
	install -s -o bin -g bin -m 755 factor ${DESTDIR}/usr/games
E 2
I 2
	install -s -o bin -g bin -m 755 factor primes ${DESTDIR}/usr/games
E 2
D 4
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat6
I 3
	rm -f ${DESTDIR}/usr/man/cat6/primes.0
	ln ${DESTDIR}/usr/man/cat6/${MAN} ${DESTDIR}/usr/man/cat6/primes.0
E 4
I 4
D 5
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
E 5
I 5
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat6
	rm -f ${DESTDIR}/usr/man/cat6/primes.0
	ln ${DESTDIR}/usr/man/cat6/${MAN} ${DESTDIR}/usr/man/cat6/primes.0
E 5
E 4
E 3

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 6
I 6
.include <bsd.prog.mk>
E 6
E 1
