h49919
s 00000/00000/00007
d D 8.1 93/06/06 13:57:29 bostic 7 6
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00001/00007
d D 5.6 93/04/27 18:08:29 bostic 6 5
c daemon(3) now in the C library
e
s 00001/00000/00007
d D 5.5 90/06/29 21:01:30 karels 5 4
c use daemon() call
e
s 00005/00048/00002
d D 5.4 90/05/11 16:39:56 bostic 4 3
c first pass for new make
e
s 00001/00001/00049
d D 5.3 89/05/11 14:08:00 bostic 3 2
c file reorg, pathnames.h, paths.h
e
s 00003/00001/00047
d D 5.2 89/01/28 10:37:32 bostic 2 1
c install in section 8; link to inetd.conf in section 5
e
s 00048/00000/00000
d D 5.1 88/09/19 21:36:23 bostic 1 0
c date and time created 88/09/19 21:36:23 by bostic
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
SRCS=	inetd.c
OBJS=
MAN=	inetd.0
E 4
I 4
PROG=	inetd
I 5
D 6
LDADD=	-lutil
E 6
E 5
MAN8=	inetd.0
MLINKS=	inetd.8 inetd.5
E 4

D 4
all: inetd

inetd: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c

clean:
	rm -f ${OBJS} core inetd

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 3
	install -s -o bin -g bin -m 755 inetd ${DESTDIR}/etc/inetd
E 3
I 3
	install -s -o bin -g bin -m 755 inetd ${DESTDIR}/usr/sbin
E 3
D 2
	install -c -o bin -g bin -m 444 inetd.0 ${DESTDIR}/usr/man/cat1
E 2
I 2
	install -c -o bin -g bin -m 444 inetd.0 ${DESTDIR}/usr/man/cat8
	rm -f ${DESTDIR}/usr/man/cat5/inetd.conf.0
	ln ${DESTDIR}/usr/man/cat8/inetd.0 ${DESTDIR}/usr/man/cat5/inetd.conf.0
E 2

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 4
I 4
.include <bsd.prog.mk>
E 4
E 1
