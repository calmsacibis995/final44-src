h37074
s 00000/00000/00011
d D 8.1 93/06/04 19:06:11 bostic 9 8
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00009
d D 5.7 93/04/27 10:23:12 bostic 8 6
c doesn't need libutil
e
s 00007/00004/00007
d D 5.6.1.1 90/10/21 20:27:22 mckusick 7 6
c delete data-stream encryption for the foreign sites (4.3-Reno)
e
s 00001/00001/00010
d D 5.6 90/09/27 22:14:20 mckusick 6 5
c break out -x (encrypted sessions) with #ifdef CRYPT
e
s 00009/00047/00002
d D 5.5 90/05/11 12:55:35 bostic 5 4
c first pass for new make
e
s 00007/00006/00042
d D 5.4 90/03/22 21:40:58 bostic 4 3
c checked in for kfall, before pmake
e
s 00002/00002/00046
d D 5.3 89/05/18 15:42:42 kfall 3 2
c Kerberos-ify
e
s 00001/00001/00047
d D 5.2 89/05/09 13:41:06 bostic 2 1
c file reorg
e
s 00048/00000/00000
d D 5.1 88/09/19 21:59:23 bostic 1 0
c date and time created 88/09/19 21:59:23 by bostic
e
u
U
f b 
t
T
I 1
D 5
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
D 4
# %W% (Berkeley) %G%
E 4
I 4
# @(#)Makefile	5.3 (Berkeley) 5/9/89
E 4
#
E 5
I 5
#	%W% (Berkeley) %G%
E 5

D 3
CFLAGS=	-O
E 3
I 3
D 5
CFLAGS=	-O -DKERBEROS
E 3
LIBC=	/lib/libc.a
SRCS=	rshd.c
D 4
OBJS=
E 4
I 4
OBJS=	rshd.o des_rw.o
E 4
MAN=	rshd.0
I 4
VPATH=	../../usr.bin/rlogin/des
E 5
I 5
PROG=	rshd
D 6
CFLAGS+=-DKERBEROS
E 6
I 6
D 7
CFLAGS+=-DKERBEROS -DCRYPT
E 6
SRCS=	rshd.c des_rw.c
E 7
I 7
SRCS=	rshd.c
#SRCS=	rshd.c des_rw.c
#CFLAGS+=-DKERBEROS -DCRYPT
E 7
MAN8=	rshd.0
D 7
D 8
DPADD=	${LIBUTIL} ${LIBKRB} ${LIBDES}
LDADD=	-lutil -lkrb -ldes
E 8
I 8
DPADD=	${LIBKRB} ${LIBDES}
LDADD=	-lkrb -ldes
E 8
E 7
I 7
#DPADD=	${LIBUTIL} ${LIBKRB} ${LIBDES}
#LDADD=	-lutil -lkrb -ldes
DPADD=	${LIBUTIL}
LDADD=	-lutil
E 7
.PATH: ${.CURDIR}/../../usr.bin/rlogin
E 5
E 4

D 5
all: rshd

D 4
rshd: ${LIBC}
D 3
	${CC} -o $@ ${CFLAGS} $@.c
E 3
I 3
	${CC} -o $@ ${CFLAGS} $@.c -lkrb -ldes
E 4
I 4
rshd: ${LIBC} ${OBJS}
	${CC} -o $@ ${OBJS} ${CFLAGS} -lutil -lkrb -ldes
E 4
E 3

clean:
D 4
	rm -f ${OBJS} core rshd
E 4
I 4
	rm -f core rshd ${OBJS}
E 4

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 2
	install -s -o bin -g bin -m 755 rshd ${DESTDIR}/etc/rshd
E 2
I 2
D 4
	install -s -o bin -g bin -m 755 rshd ${DESTDIR}/usr/libexec
E 4
I 4
	install -s -o root -g bin -m 755 rshd ${DESTDIR}/usr/libexec/rshd
E 4
E 2
	install -c -o bin -g bin -m 444 rshd.0 ${DESTDIR}/usr/man/cat8

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 5
I 5
.include <bsd.prog.mk>
E 5
E 1
