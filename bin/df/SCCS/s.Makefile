h54817
s 00005/00000/00007
d D 8.3 95/05/08 16:16:22 mckusick 11 10
c now need vfslist.c from mount
e
s 00000/00001/00007
d D 8.2 94/04/01 02:06:26 pendry 10 9
c removed COMPAT_43 flag.  the code was removed in df.c version 5.21.
e
s 00000/00000/00008
d D 8.1 93/06/02 18:07:40 mckusick 9 8
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00001/00008
d D 5.5 93/06/02 18:01:29 mckusick 8 5
c getbsize moves to libc
e
s 00002/00001/00007
d D 5.4 92/03/01 16:58:24 bostic 5 3
c replace -k with the BLOCKSIZE environmental variable
e
s 00001/00001/00007
d R 5.4 91/01/15 13:55:00 bostic 4 3
c kernel reorg
e
s 00006/00046/00002
d D 5.3 90/05/11 12:40:33 bostic 3 2
c first pass for new make
e
s 00001/00001/00047
d D 5.2 89/06/08 16:27:44 mckusick 2 1
c add COMPAT_43 flag for now
e
s 00048/00000/00000
d D 5.1 88/10/18 21:20:25 bostic 1 0
c date and time created 88/10/18 21:20:25 by bostic
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

D 2
CFLAGS=	-O
E 2
I 2
D 3
CFLAGS=	-O -DCOMPAT_43
E 2
LIBC=	/lib/libc.a
SRCS=	df.c
OBJS=
MAN=	df.0
E 3
I 3
PROG=	df
I 11
SRCS=	df.c vfslist.c
E 11
D 5
CFLAGS+=-DCOMPAT_43
E 5
I 5
D 8
SRCS=	df.c getbsize.c
E 8
D 10
CFLAGS+=-DCOMPAT_43
E 10
E 5
BINGRP=	operator
BINMODE=2555
I 11

MOUNT=	${.CURDIR}/../../sbin/mount
CFLAGS+= -I${MOUNT}
.PATH:	${MOUNT}
E 11
E 3

D 3
all: df

df: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c

clean:
	rm -f ${OBJS} core df

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
	install -s -o bin -g operator -m 2755 df ${DESTDIR}/bin/df
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
