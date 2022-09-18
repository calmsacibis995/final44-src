h60672
s 00001/00001/00009
d D 8.3 94/01/25 15:02:29 hibler 11 10
c CD9660 is now defined in Makefile (ala NFS and MFS)
e
s 00001/00001/00009
d D 8.2 94/01/12 22:02:33 hibler 10 9
c add -DMFS -DISOFS
e
s 00000/00000/00010
d D 8.1 93/06/05 11:05:33 bostic 9 8
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00009
d D 5.6 93/04/27 18:02:57 bostic 8 7
c daemon(3) now in the C library
e
s 00001/00001/00009
d D 5.5 92/04/15 16:42:01 mckusick 7 4
c add netgroup.5
e
s 00001/00001/00009
d R 5.5 92/04/15 16:21:33 mckusick 6 4
c add netgroup.5
e
s 00001/00001/00009
d R 5.5 91/01/15 14:09:35 bostic 5 4
c kernel reorg
e
s 00001/00001/00009
d D 5.4 90/06/29 20:00:11 karels 4 3
c use daemon() call
e
s 00001/00000/00009
d D 5.3 90/06/25 14:18:13 mckusick 3 2
c add exports.5
e
s 00007/00046/00002
d D 5.2 90/05/11 13:00:26 bostic 2 1
c first pass for new make
e
s 00048/00000/00000
d D 5.1 89/07/16 17:41:49 mckusick 1 0
c date and time created 89/07/16 17:41:49 by mckusick
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
SRCS=	mountd.c
OBJS=
MAN=	mountd.0
E 2
I 2
PROG=	mountd
D 10
CFLAGS+=-DNFS
E 10
I 10
D 11
CFLAGS+=-DNFS -DMFS -DISOFS
E 11
I 11
CFLAGS+=-DNFS -DMFS -DCD9660
E 11
E 10
I 3
D 7
MAN5=	exports.0
E 7
I 7
MAN5=	exports.0 netgroup.0
E 7
E 3
MAN8=	mountd.0
DPADD=	${LIBRPC}
D 4
LDADD=	-lrpc
E 4
I 4
D 8
LDADD=	-lrpc -lutil
E 8
I 8
LDADD=	-lrpc
E 8
E 4
E 2

D 2
all: mountd

mountd: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c -lrpc

clean:
	rm -f ${OBJS} core mountd

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
	install -s -o bin -g bin -m 755 mountd ${DESTDIR}/sbin
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
