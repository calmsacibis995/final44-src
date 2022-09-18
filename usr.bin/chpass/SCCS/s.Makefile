h25508
s 00001/00000/00014
d D 8.2 94/04/02 07:56:56 pendry 12 11
c prettyness police
e
s 00000/00000/00014
d D 8.1 93/07/22 09:24:52 bostic 11 10
c 4.4BSD snapshot (revision 8.1)
e
s 00003/00001/00011
d D 5.7 93/07/22 09:24:46 bostic 10 7
c schg flag prevents links, so have to do the links first,
c and then set the flag
e
s 00000/00000/00012
d R 8.1 93/07/20 06:22:58 bostic 9 7
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00000/00012
d R 8.1 93/07/19 09:47:14 bostic 8 7
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00000/00011
d D 5.6 93/07/19 09:47:13 bostic 7 5
c set the immutable bit on installation
e
s 00000/00000/00011
d R 8.1 93/06/06 14:27:36 bostic 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00010
d D 5.5 91/02/19 14:28:31 bostic 5 4
c vipw moved to usr.sbin
e
s 00002/00001/00009
d D 5.4 91/02/12 22:37:47 bostic 4 3
c rework the password subsystem
e
s 00007/00052/00003
d D 5.3 90/05/11 15:18:04 bostic 3 2
c first pass for new make
e
s 00006/00004/00049
d D 5.2 89/05/11 09:42:04 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00053/00000/00000
d D 5.1 89/02/22 17:24:01 bostic 1 0
c date and time created 89/02/22 17:24:01 by bostic
e
u
U
t
T
I 1
D 3
#
# Copyright (c) 1988 The Regents of the University of California.
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
# provided that the above copyright notice and this paragraph are
# duplicated in all such forms and that any documentation,
# advertising materials, and other materials related to such
# distribution and use acknowledge that the software was developed
# by the University of California, Berkeley.  The name of the
# University may not be used to endorse or promote products derived
# from this software without specific prior written permission.
# THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
# WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
#
E 3
#	%W% (Berkeley) %G%
D 3
#
D 2
CFLAGS=	-I. -O
E 2
I 2
CFLAGS=	-O
E 2
LIBC=	/lib/libc.a
E 3
I 3

PROG=	chpass
E 3
D 4
SRCS=	chpass.c field.c util.c
E 4
I 4
SRCS=	chpass.c edit.c field.c pw_copy.c pw_scan.c pw_util.c table.c util.c
E 4
D 3
OBJS=	chpass.o field.o util.o
MAN=	chpass.0
E 3
I 3
BINOWN=	root
BINMODE=4555
I 7
D 10
INSTALLFLAGS=-fschg
E 10
E 7
I 4
D 5
.PATH:	${.CURDIR}/../../usr.sbin/pwd_mkdb ${.CURDIR}/../../sbin/vipw
E 5
I 5
.PATH:	${.CURDIR}/../../usr.sbin/pwd_mkdb ${.CURDIR}/../../usr.sbin/vipw
I 12
CFLAGS+=-I${.CURDIR}/../../usr.sbin/pwd_mkdb -I${.CURDIR}/../../usr.sbin/vipw
E 12
E 5
E 4
LINKS=	${BINDIR}/chpass ${BINDIR}/chfn ${BINDIR}/chpass ${BINDIR}/chsh
MLINKS=	chpass.1 chfn.1 chpass.1 chsh.1
I 10

afterinstall:
	chflags schg /usr/bin/chpass
E 10
E 3

D 3
all: chpass

chpass: ${LIBC} ${OBJS}
	${CC} ${CFLAGS} -o $@ ${OBJS}

clean:
	rm -f ${OBJS} core chpass

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep ${CFLAGS} ${SRCS}

install: ${MAN}
I 2
	install -s -o root -g bin -m 4755 chpass ${DESTDIR}/usr/bin
E 2
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
D 2
	install -s -o root -g bin -m 4755 chpass ${DESTDIR}/bin/chpass
	rm -f ${DESTDIR}/bin/chfn; ln ${DESTDIR}/bin/chpass ${DESTDIR}/bin/chfn
	rm -f ${DESTDIR}/bin/chsh; ln ${DESTDIR}/bin/chpass ${DESTDIR}/bin/chsh
E 2
I 2
	rm -f ${DESTDIR}/usr/bin/chfn; ln ${DESTDIR}/usr/bin/chpass \
	    ${DESTDIR}/usr/bin/chfn
	rm -f ${DESTDIR}/usr/bin/chsh; ln ${DESTDIR}/usr/bin/chpass \
	    ${DESTDIR}/usr/bin/chsh
E 2
	rm -f ${DESTDIR}/usr/man/cat1/chfn.0
	rm -f ${DESTDIR}/usr/man/cat1/chsh.0
	ln ${DESTDIR}/usr/man/cat1/chpass.0 ${DESTDIR}/usr/man/cat1/chfn.0
	ln ${DESTDIR}/usr/man/cat1/chpass.0 ${DESTDIR}/usr/man/cat1/chsh.0

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 3
I 3
.include <bsd.prog.mk>
E 3
E 1
