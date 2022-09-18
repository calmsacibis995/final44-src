h65399
s 00000/00000/00011
d D 8.1 93/06/04 18:59:13 bostic 11 9
c 4.4BSD snapshot (revision 8.1)
e
s 00007/00004/00007
d D 5.9.1.1 90/10/21 20:18:25 mckusick 10 9
c delete data-stream encryption for the foreign sites (4.3-Reno)
e
s 00001/00001/00010
d D 5.9 90/09/27 21:55:49 mckusick 9 8
c break out -x (encrypted sessions) with #ifdef CRYPT
e
s 00008/00046/00003
d D 5.8 90/05/11 12:55:38 bostic 8 7
c first pass for new make
e
s 00005/00004/00044
d D 5.7 90/03/22 21:38:04 bostic 7 6
c check in for kfall, before pmake
e
s 00002/00002/00046
d D 5.6 89/05/17 19:05:33 kfall 6 5
c turn on Kerberos flag (see also /etc/inetd.conf)
e
s 00001/00001/00047
d D 5.5 89/05/09 13:39:04 bostic 5 4
c file reorg
e
s 00001/00001/00047
d D 5.4 89/01/06 19:54:52 karels 4 3
c binary moved to /usr/libexec
e
s 00000/00003/00048
d D 5.3 88/09/20 16:06:13 bostic 3 2
c typo...
e
s 00005/00003/00046
d D 5.2 88/09/19 21:44:20 bostic 2 1
c minor cleanups for networking release
e
s 00049/00000/00000
d D 5.1 88/08/31 11:58:12 bostic 1 0
c date and time created 88/08/31 11:58:12 by bostic
e
u
U
f b 
t
T
I 1
D 8
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
E 8
I 8
#	%W% (Berkeley) %G%
E 8

D 6
CFLAGS=	-O
E 6
I 6
D 8
CFLAGS=	-O -DKERBEROS
E 6
LIBC=	/lib/libc.a
E 8
I 8
PROG=	rlogind
D 9
CFLAGS+=-DKERBEROS
E 9
I 9
D 10
CFLAGS+=-DKERBEROS -DCRYPT
E 9
E 8
D 7
SRCS=	rlogind.c
OBJS=
E 7
I 7
SRCS=	rlogind.c des_rw.c
E 10
I 10
SRCS=	rlogind.c
#SRCS=	rlogind.c des_rw.c
#CFLAGS+=-DKERBEROS -DCRYPT
E 10
D 8
OBJS=	des_rw.o
E 7
MAN=	rlogind.0
I 7
VPATH=	../../usr.bin/rlogin/des
E 8
I 8
MAN8=	rlogind.0
D 10
DPADD=	${LIBUTIL} ${LIBKRB} ${LIBDES}
LDADD=	-lutil -lkrb -ldes
E 10
I 10
#DPADD=	${LIBUTIL} ${LIBKRB} ${LIBDES}
#LDADD=	-lutil -lkrb -ldes
DPADD=	${LIBUTIL}
LDADD=	-lutil
E 10
.PATH: ${.CURDIR}/../../usr.bin/rlogin
E 8
E 7
D 2
MAN8=	/usr/man/cat8/
E 2

D 8
all: rlogind

D 7
rlogind: ${SRCS} ${LIBC}
D 6
	${CC} -o $@ ${CFLAGS} ${SRCS} -lutil
E 6
I 6
	${CC} -o $@ ${CFLAGS} ${SRCS} -lutil -lkrb -ldes
E 7
I 7
rlogind: ${LIBC} ${OBJS}
	${CC} -o $@ ${CFLAGS} $@.c ${OBJS} -lutil -lkrb -ldes
E 7
E 6

D 3
cleandir: clean
	rm -f tags .depend

E 3
clean:
D 2
	rm -f ${OBJS} core rlogind ${MAN}
E 2
I 2
	rm -f ${OBJS} core rlogind
E 2

I 2
cleandir: clean
	rm -f ${MAN} tags .depend

E 2
depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 4
	install -s -o bin -g bin -m 755 rlogind ${DESTDIR}/etc/rlogind
E 4
I 4
D 5
	install -s -o bin -g bin -m 755 rlogind ${DESTDIR}/usr/libexec/rlogind
E 5
I 5
	install -s -o bin -g bin -m 755 rlogind ${DESTDIR}/usr/libexec
E 5
E 4
D 2
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}${MAN8}${MAN}
E 2
I 2
	install -c -o bin -g bin -m 444 rlogind.0 ${DESTDIR}/usr/man/cat8
E 2

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 8
I 8
.include <bsd.prog.mk>
E 8
E 1
