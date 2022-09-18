h39167
s 00001/00001/00007
d D 8.6 95/05/08 13:02:38 mckusick 13 12
c break out vfslist.c for df
e
s 00001/00000/00007
d D 8.5 94/03/27 08:20:41 bostic 12 11
c document that getmntopts.3 doesn't get installed
e
s 00001/00000/00006
d D 8.4 94/03/27 07:42:52 bostic 11 10
c add mount_ufs.c getmntopts.c
e
s 00000/00001/00006
d D 8.3 94/02/20 16:22:09 bostic 10 9
c break mount.8 up into mount.8 and umount.8
e
s 00000/00003/00007
d D 8.2 94/02/16 23:49:26 pendry 9 8
c no longer needs support for nfs and other "external" filesystems.
e
s 00000/00000/00010
d D 8.1 93/06/05 11:01:30 bostic 8 6
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00009
d R 5.6 91/01/15 14:09:07 bostic 7 6
c kernel reorg
e
s 00008/00049/00002
d D 5.5 90/05/11 13:05:13 bostic 6 4
c first pass for new make
e
s 00001/00001/00050
d R 5.5 89/09/12 18:36:35 mckusick 5 4
c add memory filesystem
e
s 00003/00000/00048
d D 5.4 89/08/16 09:41:57 bostic 4 3
c link to unmount
e
s 00002/00002/00046
d D 5.3 89/07/11 19:04:17 mckusick 3 2
c update to support NFS (from Rick Macklem)
e
s 00001/00001/00047
d D 5.2 89/05/11 13:54:28 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00048/00000/00000
d D 5.1 88/10/19 12:03:59 bostic 1 0
c date and time created 88/10/19 12:03:59 by bostic
e
u
U
t
T
I 1
D 6
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
E 6
I 6
#	%W% (Berkeley) %G%
E 6

D 3
CFLAGS=	-O
E 3
I 3
D 6
CFLAGS=	-O -DNFS
E 3
LIBC=	/lib/libc.a
SRCS=	mount.c
OBJS=
MAN=	mount.0
E 6
I 6
PROG=	mount
I 11
D 13
SRCS=	mount.c mount_ufs.c getmntopts.c
E 13
I 13
SRCS=	mount.c mount_ufs.c getmntopts.c vfslist.c
E 13
E 11
D 9
CFLAGS+=-DNFS
E 9
MAN8=	mount.0
I 12
# We do NOT install the getmntopts.3 man page.
E 12
D 9
DPADD=	${LIBRPC}
LDADD=	-lrpc
E 9
D 10
MLINKS=	mount.8 umount.8
E 10
E 6

D 6
all: mount

mount: ${LIBC}
D 3
	${CC} -o $@ ${CFLAGS} $@.c
E 3
I 3
	${CC} -o $@ ${CFLAGS} $@.c -lrpc
E 3

clean:
	rm -f ${OBJS} core mount

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 2
	install -s -o bin -g bin -m 755 mount ${DESTDIR}/etc
E 2
I 2
	install -s -o bin -g bin -m 755 mount ${DESTDIR}/sbin
E 2
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat8
I 4
	rm -f ${DESTDIR}/usr/man/cat8/umount.0
	ln ${DESTDIR}/usr/man/cat8/mount.0 ${DESTDIR}/usr/man/cat8/umount.0

E 4

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 6
I 6
.include <bsd.prog.mk>
E 6
E 1
