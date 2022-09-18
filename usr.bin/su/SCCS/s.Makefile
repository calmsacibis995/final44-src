h02158
s 00000/00000/00011
d D 8.1 93/07/19 09:45:37 bostic 9 8
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00000/00010
d D 5.6 93/07/19 09:45:36 bostic 8 5
c set the immutable bit on installation
e
s 00000/00000/00010
d R 8.1 93/06/06 16:27:37 bostic 7 5
c 4.4BSD snapshot (revision 8.1)
e
s 00003/00003/00007
d D 5.5.1.1 90/10/21 23:04:49 mckusick 6 5
c delete Kerberos compilation for the foreign sites (4.3-Reno)
e
s 00008/00046/00002
d D 5.5 90/05/11 14:13:20 bostic 5 4
c first pass for new make
e
s 00002/00002/00046
d D 5.4 89/10/12 18:14:12 kfall 4 3
c add Kerberos define
e
s 00001/00001/00047
d D 5.3 89/05/11 13:42:24 bostic 3 2
c file reorg, pathnames.h, paths.h
e
s 00004/00004/00044
d D 5.2 88/09/25 22:23:31 bostic 2 1
c do mkdep -p
e
s 00048/00000/00000
d D 5.1 88/09/13 11:06:01 bostic 1 0
c date and time created 88/09/13 11:06:01 by bostic
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
# %W% (Berkeley) %G%
#
E 5
I 5
#	%W% (Berkeley) %G%
E 5

D 4
CFLAGS=	-O
E 4
I 4
D 5
CFLAGS=	-O -DKERBEROS
E 4
LIBC=	/lib/libc.a
SRCS=	su.c
D 2
OBJS=	su.o
E 2
I 2
OBJS=
E 2
MAN=	su.0
E 5
I 5
PROG=	su
D 6
CFLAGS+=-DKERBEROS
DPADD=	${LIBKRB} ${LIBDES}
LDADD=	-lkrb -ldes
E 6
I 6
#CFLAGS+=-DKERBEROS
#DPADD=	${LIBKRB} ${LIBDES}
#LDADD=	-lkrb -ldes
E 6
BINOWN=	root
BINMODE=4555
I 8
INSTALLFLAGS=-fschg
E 8
E 5

D 5
all: su

D 2
su: ${OBJS} ${LIBC}
	${CC} -o $@ ${CFLAGS} ${OBJS}
E 2
I 2
su: ${LIBC}
D 4
	${CC} -o $@ ${CFLAGS} $@.c
E 4
I 4
	${CC} -o $@ ${CFLAGS} $@.c -lkrb -ldes
E 4
E 2

clean:
	rm -f ${OBJS} core su

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
D 2
	mkdep ${CFLAGS} ${SRCS}
E 2
I 2
	mkdep -p ${CFLAGS} ${SRCS}
E 2

install: ${MAN}
D 3
	install -s -o root -g bin -m 4755 su ${DESTDIR}/bin/su
E 3
I 3
	install -s -o root -g bin -m 4755 su ${DESTDIR}/usr/bin
E 3
	install -c -o bin -g bin -m 444 su.0 ${DESTDIR}/usr/man/cat1/su.0

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 5
I 5
.include <bsd.prog.mk>
E 5
E 1
