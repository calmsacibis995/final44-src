h18961
s 00000/00000/00008
d D 8.1 93/06/06 11:36:33 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00006/00046/00002
d D 5.4 90/05/11 16:41:20 bostic 4 3
c first pass for new make
e
s 00001/00001/00047
d D 5.3 89/07/30 14:55:39 bostic 3 2
c needs libcompat
e
s 00001/00001/00047
d D 5.2 89/05/11 14:03:51 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00048/00000/00000
d D 5.1 88/10/19 10:31:19 bostic 1 0
c date and time created 88/10/19 10:31:19 by bostic
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
SRCS=	ac.c
OBJS=
MAN=	ac.0
E 4
I 4
PROG=	ac
MAN8=	ac.0
DPADD=	${LIBCOMPAT}
LDADD=	-lcompat
E 4

D 4
all: ac

ac: ${LIBC}
D 3
	${CC} -o $@ ${CFLAGS} $@.c
E 3
I 3
	${CC} -o $@ ${CFLAGS} $@.c -lcompat
E 3

clean:
	rm -f ${OBJS} core ac

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 2
	install -s -o bin -g bin -m 755 ac ${DESTDIR}/etc
E 2
I 2
	install -s -o bin -g bin -m 755 ac ${DESTDIR}/usr/sbin
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
