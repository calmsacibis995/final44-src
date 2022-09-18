h02392
s 00000/00000/00006
d D 8.1 93/06/06 13:52:06 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00003/00045/00003
d D 5.3 90/05/11 16:41:01 bostic 3 2
c first pass for new make
e
s 00012/00012/00036
d D 5.2 89/04/18 12:09:53 bostic 2 1
c reorg, fix copyright
e
s 00048/00000/00000
d D 5.1 88/12/05 15:43:16 bostic 1 0
c date and time created 88/12/05 15:43:16 by bostic
e
u
U
t
T
I 1
D 3
#
D 2
# Copyright (c) 1988 Regents of the University of California.
E 2
I 2
# Copyright (c) 1989 The Regents of the University of California.
E 2
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
# provided that the above copyright notice and this paragraph are
D 2
# duplicated in all such forms and that any documentation, advertising
# materials, and other materials related to such redistribution and
# use acknowledge that the software was developed by the University
# of California, Berkeley.  The name of the University may not be
# used to endorse or promote products derived from this software
# without specific prior written permission.  THIS SOFTWARE IS PROVIDED
# ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
# WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND
# FITNESS FOR A PARTICULAR PURPOSE.
E 2
I 2
# duplicated in all such forms and that any documentation,
# advertising materials, and other materials related to such
# distribution and use acknowledge that the software was developed
# by the University of California, Berkeley.  The name of the
# University may not be used to endorse or promote products derived
# from this software without specific prior written permission.
# THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
#
E 3
D 2
# %W% (Berkeley) %G%
E 2
I 2
#	%W% (Berkeley) %G%
E 2
D 3
#
E 3

D 3
CFLAGS=	-O
LIBC=	/lib/libc.a
SRCS=	chroot.c
OBJS=
MAN=	chroot.0
E 3
I 3
PROG=	chroot
MAN8=	chroot.0
E 3

D 3
all: chroot

chroot: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c

clean:
	rm -f ${OBJS} core chroot

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 2
	install -s -o bin -g bin -m 755 chroot ${DESTDIR}/bin
E 2
I 2
	install -s -o bin -g bin -m 755 chroot ${DESTDIR}/usr/sbin
E 2
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat8

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 3
I 3
.include <bsd.prog.mk>
E 3
E 1
