h14809
s 00000/00000/00007
d D 8.1 93/06/05 11:08:18 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00001/00007
d D 5.4 93/04/27 18:05:18 bostic 4 3
c daemon(3) now in the C library
e
s 00001/00000/00007
d D 5.3 90/06/29 20:10:20 karels 3 2
c use daemon() call
e
s 00005/00046/00002
d D 5.2 90/05/11 13:04:09 bostic 2 1
c first pass for new make
e
s 00048/00000/00000
d D 5.1 89/08/30 15:46:08 mckusick 1 0
c date and time created 89/08/30 15:46:08 by mckusick
e
u
U
t
T
I 1
D 2
#
# Copyright (c) 1989 Regents of the University of California.
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
E 2
I 2
#	%W% (Berkeley) %G%
E 2

D 2
CFLAGS=	-O -DNFS
LIBC=	/lib/libc.a
SRCS=	nfsiod.c
OBJS=
MAN=	nfsiod.0
E 2
I 2
PROG=	nfsiod
CFLAGS+=-DNFS
MAN8=	nfsiod.0
I 3
D 4
LDADD=	-lutil
E 4
E 3
E 2

D 2
all: nfsiod

nfsiod: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c

clean:
	rm -f ${OBJS} core nfsiod

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
	install -s -o bin -g bin -m 755 nfsiod ${DESTDIR}/sbin
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat8

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 2
I 2
.include <bsd.prog.mk>
E 2
E 1
