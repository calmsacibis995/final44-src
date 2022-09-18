h64752
s 00000/00000/00005
d D 8.1 93/06/06 14:53:57 bostic 8 7
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00003/00005
d D 5.7 93/06/02 19:08:25 mckusick 7 6
c devname moves to libc
e
s 00000/00002/00008
d D 5.6 93/04/27 18:17:42 bostic 6 5
c pwcache(3) now in the C library
e
s 00003/00000/00007
d D 5.5 92/07/12 23:17:12 bostic 5 4
c assumed that sizeof(struct acct) was a power of 2; also misused off_t
c rewrite to use stdio instead of read/write, fseek is pretty efficient
c use the dev_mkdb database, prototype functions, random assorted cleanups
e
s 00005/00046/00002
d D 5.4 90/05/11 15:56:49 bostic 4 3
c first pass for new make
e
s 00001/00001/00047
d D 5.3 90/03/05 10:39:56 bostic 3 2
c needs libutil now
e
s 00001/00001/00047
d D 5.2 89/05/10 22:46:39 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00048/00000/00000
d D 5.1 88/10/21 13:49:09 bostic 1 0
c date and time created 88/10/21 13:49:09 by bostic
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
SRCS=	lastcomm.c
OBJS=
MAN=	lastcomm.0
E 4
I 4
PROG=	lastcomm
I 5
D 7
SRCS=	devname.c lastcomm.c
E 5
D 6
DPADD=	${LIBUTIL}
LDADD=	-lutil
E 6
I 5

.PATH: ${.CURDIR}/../../bin/ps
E 7
E 5
E 4

D 4
all: lastcomm

lastcomm: ${LIBC}
D 3
	${CC} -o $@ ${CFLAGS} $@.c
E 3
I 3
	${CC} -o $@ ${CFLAGS} $@.c -lutil
E 3

clean:
	rm -f ${OBJS} core lastcomm

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 2
	install -s -o bin -g bin -m 755 lastcomm ${DESTDIR}/usr/ucb
E 2
I 2
	install -s -o bin -g bin -m 755 lastcomm ${DESTDIR}/usr/bin
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
