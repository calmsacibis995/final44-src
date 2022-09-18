h21751
s 00000/00000/00012
d D 8.1 93/07/19 09:42:58 bostic 10 9
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00000/00011
d D 5.7 93/07/19 09:42:53 bostic 9 6
c set the immutable bit on installation
e
s 00000/00000/00011
d R 8.1 93/06/09 22:43:38 bostic 8 6
c 4.4BSD snapshot (revision 8.1)
e
s 00006/00003/00008
d D 5.6.1.1 90/10/21 22:40:06 mckusick 7 6
c delete Kerberos compilation for the foreign sites (4.3-Reno)
e
s 00001/00000/00010
d D 5.6 90/06/24 16:52:40 bostic 6 5
c add klogin.c
e
s 00008/00046/00002
d D 5.5 90/05/11 15:57:07 bostic 5 4
c first pass for new make
e
s 00001/00001/00047
d D 5.4 90/03/29 17:00:41 kfall 4 3
c include files for kerberos have moved into /usr/include/kerberosIV
e
s 00001/00001/00047
d D 5.3 89/05/09 13:37:52 bostic 3 2
c file reorg
e
s 00002/00002/00046
d D 5.2 89/02/07 21:59:45 kfall 2 1
c define Kerberos flag (uses Kerberos now)
e
s 00048/00000/00000
d D 5.1 88/10/18 22:32:06 bostic 1 0
c date and time created 88/10/18 22:32:06 by bostic
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

D 2
CFLAGS=	-O
E 2
I 2
D 4
CFLAGS=	-O -DKERBEROS
E 4
I 4
D 5
CFLAGS=	-O -DKERBEROS -I/usr/include/kerberosIV
E 4
E 2
LIBC=	/lib/libc.a
SRCS=	login.c
OBJS=
MAN=	login.0
E 5
I 5
CFLAGS+=-DKERBEROS
PROG=	login
I 6
D 7
SRCS=	klogin.c login.c
E 6
DPADD=	${LIBUTIL} ${LIBKRB} ${LIBDES}
LDADD=	-lutil -lkrb -ldes
E 7
I 7
SRCS=	login.c
#SRCS=	klogin.c login.c
#DPADD=	${LIBUTIL} ${LIBKRB} ${LIBDES}
#LDADD=	-lutil -lkrb -ldes
DPADD=	${LIBUTIL}
LDADD=	-lutil
E 7
BINOWN=	root
BINMODE=4555
I 9
INSTALLFLAGS=-fschg
E 9
E 5

D 5
all: login

login: ${LIBC}
D 2
	${CC} -o $@ ${CFLAGS} $@.c -lutil
E 2
I 2
	${CC} -o $@ ${CFLAGS} $@.c -lutil -lkrb -ldes
E 2

clean:
	rm -f ${OBJS} core login

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 3
	install -s -o root -g bin -m 4755 login ${DESTDIR}/bin/login
E 3
I 3
	install -s -o root -g bin -m 4755 login ${DESTDIR}/usr/bin/login
E 3
	install -c -o bin -g bin -m 444 login.0 ${DESTDIR}/usr/man/cat1

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 5
I 5
.include <bsd.prog.mk>
E 5
E 1
