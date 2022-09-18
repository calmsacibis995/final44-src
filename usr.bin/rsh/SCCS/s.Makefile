h37548
s 00000/00000/00013
d D 8.1 93/07/19 09:49:35 bostic 10 9
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00000/00012
d D 5.7 93/07/19 09:49:33 bostic 9 6
c set the immutable bit on installation
e
s 00000/00000/00012
d R 8.1 93/06/06 16:11:19 bostic 8 6
c 4.4BSD snapshot (revision 8.1)
e
s 00005/00004/00008
d D 5.6.1.1 90/10/21 20:07:56 mckusick 7 6
c delete data-stream encryption for the foreign sites (4.3-Reno)
e
s 00001/00001/00011
d D 5.6 90/09/27 22:07:06 mckusick 6 5
c break out -x (encrypted sessions) with #ifdef CRYPT
e
s 00009/00047/00003
d D 5.5 90/05/11 14:23:30 bostic 5 4
c first pass for new make
e
s 00001/00001/00049
d D 5.4 89/08/30 19:45:19 kfall 4 3
c remove some redundancy
e
s 00009/00007/00041
d D 5.3 89/08/22 17:36:19 kfall 3 2
c deal with krcmd.c and kcmd.c correctly
e
s 00001/00001/00047
d D 5.2 89/05/11 10:06:38 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00048/00000/00000
d D 5.1 88/09/20 17:26:27 bostic 1 0
c date and time created 88/09/20 17:26:27 by bostic
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
D 3
# %W% (Berkeley) %G%
E 3
I 3
# @(#)Makefile	5.2 (Berkeley) 5/11/89
E 3
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
E 5
I 5
PROG=	rsh
D 6
CFLAGS+=-DKERBEROS
E 6
I 6
D 7
CFLAGS+=-DKERBEROS -DCRYPT
E 6
E 5
D 3
SRCS=	rsh.c
OBJS=
E 3
I 3
SRCS=	rsh.c krcmd.c kcmd.c des_rw.c
D 5
OBJS=	rsh.o krcmd.o kcmd.o des_rw.o
E 3
MAN=	rsh.0
I 3
VPATH=	../rlogin/kcmd:../rlogin/des
E 5
I 5
DPADD=	${LIBKRB} ${LIBDES}
LDADD=	-lkrb -ldes
E 7
I 7
SRCS=	rsh.c
#CFLAGS+=-DKERBEROS -DCRYPT
#SRCS=	rsh.c krcmd.c kcmd.c des_rw.c
#DPADD=	${LIBKRB} ${LIBDES}
#LDADD=	-lkrb -ldes
E 7
BINOWN=	root
BINMODE=4555
I 9
INSTALLFLAGS=-fschg
E 9
.PATH:	${.CURDIR}/../rlogin
E 5
E 3

D 5
all: rsh

D 3
rsh: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c
E 3
I 3
rsh: ${LIBC} ${OBJS}
D 4
	${CC} -o $@ ${CFLAGS} $@.c ${OBJS} -lkrb -ldes
E 4
I 4
	${CC} -o $@ ${CFLAGS} ${OBJS} -lkrb -ldes
E 4
E 3

clean:
D 3
	rm -f ${OBJS} core rsh
E 3
I 3
	rm -f core rsh ${OBJS}
E 3

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 2
	install -s -o root -g bin -m 4755 rsh ${DESTDIR}/usr/ucb/rsh
E 2
I 2
	install -s -o root -g bin -m 4755 rsh ${DESTDIR}/usr/bin
E 2
	install -c -o bin -g bin -m 444 rsh.0 ${DESTDIR}/usr/man/cat1

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 5
I 5
.include <bsd.prog.mk>
E 5
E 1
