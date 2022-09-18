h18629
s 00000/00000/00013
d D 8.1 93/07/19 09:50:14 bostic 9 8
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00000/00012
d D 5.6 93/07/19 09:50:13 bostic 8 6
c set the immutable bit on installation
e
s 00000/00000/00012
d R 8.1 93/05/31 15:08:23 bostic 7 6
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00011
d D 5.5 92/06/20 12:30:02 bostic 6 4
c break some functions out into util.c
e
s 00005/00004/00008
d D 5.4.1.1 90/10/21 21:18:45 mckusick 5 4
c delete data-stream encryption for the foreign sites (4.3-Reno)
e
s 00001/00001/00011
d D 5.4 90/10/21 21:14:21 mckusick 4 3
c add -DCRYPT to get -x processing
e
s 00009/00046/00003
d D 5.3 90/05/11 12:38:59 bostic 3 2
c first pass for new make
e
s 00007/00006/00042
d D 5.2 89/08/30 20:03:39 kfall 2 1
c remove redundancy
e
s 00048/00000/00000
d D 5.1 88/09/20 16:32:31 bostic 1 0
c date and time created 88/09/20 16:32:31 by bostic
e
u
U
f b 
t
T
I 1
D 3
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
D 2
# %W% (Berkeley) %G%
E 2
I 2
# @(#)Makefile	5.1 (Berkeley) 9/20/88
E 2
#
E 3
I 3
#	%W% (Berkeley) %G%
E 3

D 2
CFLAGS=	-O
E 2
I 2
D 3
CFLAGS=	-O -DKERBEROS
E 2
LIBC=	/lib/libc.a
E 3
I 3
PROG=	rcp
E 3
D 2
SRCS=	rcp.c
OBJS=
E 2
I 2
D 5
D 6
SRCS=	rcp.c krcmd.c kcmd.c
E 6
I 6
SRCS=	rcp.c krcmd.c kcmd.c util.c
E 6
D 3
OBJS=	rcp.o krcmd.o kcmd.o
E 2
MAN=	rcp.0
I 2
VPATH=	/usr/src/usr.bin/rlogin/kcmd:
E 3
I 3
D 4
CFLAGS+=-DKERBEROS
E 4
I 4
CFLAGS+=-DKERBEROS -DCRYPT
E 4
DPADD=	${LIBKRB} ${LIBDES}
LDADD=	-lkrb -ldes
E 5
I 5
SRCS=	rcp.c
#SRCS=	rcp.c krcmd.c kcmd.c
#CFLAGS+=-DKERBEROS -DCRYPT
#DPADD=	${LIBKRB} ${LIBDES}
#LDADD=	-lkrb -ldes
E 5
BINOWN=	root
BINMODE=4555
I 8
INSTALLFLAGS=-fschg
E 8
.PATH:	${.CURDIR}/../../usr.bin/rlogin
E 3
E 2

D 3
all: rcp

D 2
rcp: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c
E 2
I 2
rcp: ${LIBC} ${OBJS}
	${CC} -o $@ ${CFLAGS} ${OBJS} -lkrb -ldes
E 2

clean:
	rm -f ${OBJS} core rcp

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
	install -s -o root -g bin -m 4755 rcp ${DESTDIR}/bin/rcp
	install -c -o bin -g bin -m 444 rcp.0 ${DESTDIR}/usr/man/cat1

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 3
I 3
.include <bsd.prog.mk>
E 3
E 1
