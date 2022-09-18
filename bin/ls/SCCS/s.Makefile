h65004
s 00000/00000/00006
d D 8.1 93/06/02 18:28:17 mckusick 9 8
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00002/00005
d D 5.7 93/06/02 18:28:07 mckusick 8 6
c getbsize now comes from libc
e
s 00000/00000/00007
d R 8.1 93/05/31 15:03:37 bostic 7 6
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00002/00007
d D 5.6 93/04/27 18:13:13 bostic 6 5
c pwcache(3) now in C library
e
s 00001/00001/00008
d D 5.5 93/03/03 20:35:56 bostic 5 4
c add stat_flags file (used by chflags and install)
e
s 00002/00001/00007
d D 5.4 92/03/01 16:52:44 bostic 4 3
c replace -k with the BLOCKSIZE environmental variable
e
s 00005/00045/00003
d D 5.3 90/05/11 12:40:22 bostic 3 2
c first pass for new make
e
s 00004/00004/00044
d D 5.2 89/06/26 16:38:21 bostic 2 1
c new version
e
s 00048/00000/00000
d D 5.1 88/10/18 21:41:07 bostic 1 0
c date and time created 88/10/18 21:41:07 by bostic
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
E 3
I 3
PROG=	ls
E 3
D 2
SRCS=	ls.c
OBJS=
E 2
I 2
D 4
SRCS=	cmp.c ls.c print.c util.c
E 4
I 4
D 5
SRCS=	cmp.c getbsize.c ls.c print.c util.c
E 5
I 5
D 8
SRCS=	cmp.c getbsize.c stat_flags.c ls.c print.c util.c
E 5
.PATH:	${.CURDIR}/../../bin/df
E 8
I 8
SRCS=	cmp.c stat_flags.c ls.c print.c util.c
E 8
E 4
D 3
OBJS=	cmp.o ls.o print.o util.o
E 2
MAN=	ls.0
E 3
I 3
D 6
DPADD=	${LIBUTIL}
LDADD=	-lutil
E 6
E 3

D 3
all: ls

D 2
ls: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c
E 2
I 2
ls: ${LIBC} ${OBJS}
	${CC} -o $@ ${CFLAGS} ${OBJS}
E 2

clean:
	rm -f ${OBJS} core ls

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
	install -s -o bin -g bin -m 755 ls ${DESTDIR}/bin
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
