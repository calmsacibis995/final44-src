h45062
s 00000/00000/00012
d D 8.1 93/07/19 09:44:36 bostic 10 9
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00000/00011
d D 5.7 93/07/19 09:44:35 bostic 9 6
c set the immutable bit on installation
e
s 00000/00000/00011
d R 8.1 93/06/06 16:10:04 bostic 8 6
c 4.4BSD snapshot (revision 8.1)
e
s 00005/00004/00007
d D 5.6.1.1 90/10/21 18:27:19 mckusick 7 6
c delete data-stream encryption for the foreign sites (4.3-Reno)
e
s 00001/00001/00010
d D 5.6 90/09/27 21:46:16 mckusick 6 5
c break out -x functionality into #ifdef CRYPT
e
s 00009/00047/00002
d D 5.5 90/05/11 15:21:26 bostic 5 4
c first pass for new make
e
s 00001/00001/00048
d D 5.4 90/03/29 17:11:01 kfall 4 3
c kerberos include files moved to /usr/include/kerberosIV
e
s 00008/00007/00041
d D 5.3 89/08/22 17:35:18 kfall 3 2
c deal with kcmd and krcmd.c correctly
e
s 00001/00001/00047
d D 5.2 89/05/11 09:38:11 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00048/00000/00000
d D 5.1 88/09/19 13:02:41 bostic 1 0
c date and time created 88/09/19 13:02:41 by bostic
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
D 4
CFLAGS=	-O -DKERBEROS
E 4
I 4
D 5
CFLAGS=	-O -DKERBEROS -I/usr/include/kerberosIV
E 4
E 3
LIBC=	/lib/libc.a
D 3
SRCS=	rlogin.c
OBJS=
E 3
I 3
SRCS=	rlogin.c kcmd/krcmd.c kcmd/kcmd.c des/des_rw.c
OBJS=	krcmd.o kcmd.o des_rw.o
E 3
MAN=	rlogin.0
I 3
VPATH=	des:kcmd
E 5
I 5
PROG=	rlogin
D 7
SRCS=	rlogin.c krcmd.c kcmd.c des_rw.c
DPADD=	${LIBKRB} ${LIBDES}
D 6
CFLAGS+=-DKERBEROS
E 6
I 6
CFLAGS+=-DKERBEROS -DCRYPT
E 6
LDADD=	-lkrb -ldes
E 7
I 7
SRCS=	rlogin.c
#SRCS=	rlogin.c krcmd.c kcmd.c des_rw.c
#DPADD=	${LIBKRB} ${LIBDES}
#CFLAGS+=-DKERBEROS
#LDADD=	-lkrb -ldes
E 7
BINOWN=	root
BINMODE=4555
I 9
INSTALLFLAGS=-fschg
E 9
E 5
E 3

D 5
all: rlogin

D 3
rlogin: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c
E 3
I 3
rlogin: ${LIBC} ${OBJS}
	${CC} -o $@ ${CFLAGS} $@.c ${OBJS} -lkrb -ldes
E 3

clean:
D 3
	rm -f ${OBJS} core rlogin
E 3
I 3
	rm -f ${OBJS} core rlogin ${OBJS}
E 3

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 2
	install -s -o root -g bin -m 4755 rlogin ${DESTDIR}/usr/ucb/rlogin
E 2
I 2
	install -s -o root -g bin -m 4755 rlogin ${DESTDIR}/usr/bin
E 2
	install -c -o bin -g bin -m 444 rlogin.0 ${DESTDIR}/usr/man/cat1

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 5
I 5
.include <bsd.prog.mk>
E 5
E 1
