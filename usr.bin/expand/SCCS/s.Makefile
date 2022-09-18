h46897
s 00000/00000/00006
d D 8.1 93/06/09 22:38:04 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00004/00048/00002
d D 5.4 90/05/11 15:10:38 bostic 4 3
c first pass for new make
e
s 00001/00001/00049
d D 5.3 89/05/11 09:49:47 bostic 3 2
c file reorg, pathnames.h, paths.h
e
s 00005/00005/00043
d D 5.2 88/10/21 15:08:47 bostic 2 1
c add unexpand
e
s 00048/00000/00000
d D 5.1 88/10/21 13:46:24 bostic 1 0
c date and time created 88/10/21 13:46:24 by bostic
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
D 2
SRCS=	expand.c
E 2
I 2
SRCS=	expand.c unexpand.c
E 2
OBJS=
MAN=	expand.0
E 4
I 4
PROG=	expand
MLINKS=	expand.1 unexpand.1
E 4

D 2
all: expand
E 2
I 2
D 4
all: expand unexpand
E 2

D 2
expand: ${LIBC}
E 2
I 2
expand unexpand: ${LIBC}
E 2
	${CC} -o $@ ${CFLAGS} $@.c

clean:
D 2
	rm -f ${OBJS} core expand
E 2
I 2
	rm -f ${OBJS} core expand unexpand
E 2

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 2
	install -s -o bin -g bin -m 755 expand ${DESTDIR}/usr/ucb
E 2
I 2
D 3
	install -s -o bin -g bin -m 755 expand unexpand ${DESTDIR}/usr/ucb
E 3
I 3
	install -s -o bin -g bin -m 755 expand unexpand ${DESTDIR}/usr/bin
E 3
E 2
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
	rm -f ${DESTDIR}/usr/man/cat1/unexpand.0
	ln ${DESTDIR}/usr/man/cat1/expand.0 ${DESTDIR}/usr/man/cat1/unexpand.0

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 4
I 4
.include <bsd.prog.mk>
E 4
E 1
