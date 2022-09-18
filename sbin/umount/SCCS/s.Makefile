h58134
s 00001/00000/00012
d D 8.4 95/06/22 18:41:42 mckusick 9 8
c add umount.8 manual page
e
s 00005/00000/00007
d D 8.3 95/05/08 17:21:20 mckusick 8 7
c list processing now done in vfslist from mount
e
s 00000/00002/00007
d D 8.2 94/02/20 16:21:53 bostic 7 6
c NFS is always on, break mount.8 up into mount.8 and umount.8
e
s 00000/00000/00009
d D 8.1 93/06/05 11:26:36 bostic 6 4
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00008
d R 5.5 91/01/15 14:12:04 bostic 5 4
c kernel reorg
e
s 00007/00045/00002
d D 5.4 90/05/11 13:04:15 bostic 4 3
c first pass for new make
e
s 00002/00002/00045
d D 5.3 89/07/11 19:14:15 mckusick 3 2
c update to support NFS (from Rick Macklem)
e
s 00001/00001/00046
d D 5.2 89/05/11 13:56:48 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00047/00000/00000
d D 5.1 88/10/19 13:05:54 bostic 1 0
c date and time created 88/10/19 13:05:54 by bostic
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

D 3
CFLAGS=	-O
E 3
I 3
D 4
CFLAGS=	-O -DNFS
E 3
LIBC=	/lib/libc.a
SRCS=	umount.c
OBJS=
MAN=
E 4
I 4
PROG=	umount
I 8
SRCS=	umount.c vfslist.c
I 9
MAN8=	umount.0
E 9
E 8
D 7
CFLAGS+=-DNFS
NOMAN=	noman
E 7
DPADD=	${LIBRPC}
LDADD=	-lrpc
I 8

MOUNT=	${.CURDIR}/../../sbin/mount
CFLAGS+= -I${MOUNT}
.PATH:	${MOUNT}
E 8
E 4

D 4
all: umount

umount: ${LIBC}
D 3
	${CC} -o $@ ${CFLAGS} $@.c
E 3
I 3
	${CC} -o $@ ${CFLAGS} $@.c -lrpc
E 3

clean:
	rm -f ${OBJS} core umount

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 2
	install -s -o bin -g bin -m 755 umount ${DESTDIR}/etc
E 2
I 2
	install -s -o bin -g bin -m 755 umount ${DESTDIR}/sbin
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
