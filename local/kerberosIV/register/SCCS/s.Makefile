h18743
s 00000/00000/00013
d D 8.1 93/06/01 23:15:18 bostic 10 9
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00012
d D 5.3 91/02/25 15:46:07 bostic 9 8
c Needs -DCRYPT
e
s 00001/00000/00012
d D 5.2 90/06/26 09:37:37 bostic 8 7
c needs rlogin for des_rw.c
e
s 00001/00002/00011
d D 5.1 90/06/25 18:26:03 bostic 7 6
c don't need source from rlogin
e
s 00004/00002/00009
d D 1.6 90/06/22 18:53:58 kfall 6 5
c filesystem reorg
e
s 00010/00066/00001
d D 1.5 90/05/11 23:26:20 kfall 5 4
c new Makefile (for new make)
e
s 00018/00014/00049
d D 1.4 89/08/21 18:14:09 kfall 4 3
c filesystem reorg, deal with des_rw correctly
e
s 00014/00015/00049
d D 1.3 89/05/17 22:25:56 kfall 3 2
c cleanup
e
s 00002/00002/00062
d D 1.2 88/12/12 21:00:49 kfall 2 1
c add .o's to OBJS list
e
s 00064/00000/00000
d D 1.1 88/12/12 20:54:43 kfall 1 0
c date and time created 88/12/12 20:54:43 by kfall
e
u
U
t
T
I 1
D 5
#
# Copyright (c) 1988 Regents of the University of California.
D 4
# All rights reregisterded.
E 4
I 4
# All rights reserved.
E 4
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
# @(#)Makefile	5.3 (Berkeley) 9/20/88
#
E 5
I 5
D 6
BINDIR=	/usr/local
E 6
I 6
#	%W% (Berkeley) %G%

E 6
PROG=	register
SRCS=	register.c des_rw.c
I 6
D 9
CFLAGS+=-DKERBEROS -DDEBUG -I${.CURDIR}/../include
E 9
I 9
CFLAGS+=-DCRYPT -DDEBUG -DKERBEROS -I${.CURDIR}/../include
E 9
I 8
.PATH:	${.CURDIR}/../../usr.bin/rlogin
E 8
E 6
DPADD=	${LIBKRB} ${LIBDES}
D 6
CFLAGS+=-DKERBEROS
E 6
LDADD=	-lkrb -ldes
I 7
BINDIR=	/usr/bin
E 7
BINOWN=	root
BINMODE=4555
D 7
.PATH:  ${.CURDIR}/../../usr.bin/rlogin
I 6
BINDIR=	/usr/bin
E 7
E 6
E 5

D 3
CDEFS=	-DKERBEROS
CFLAGS=	-O
E 3
I 3
D 4
CFLAGS=	-O -DKERBEROS
E 4
I 4
D 5
INCDIR=	/usr/src/devel/kerberos/src/include
CFLAGS=	-O -DKERBEROS -I${INCDIR}
E 4
E 3
LIBC=	/lib/libc.a
D 3
KLIB=	/usr/local/lib/libkrb.a
DESLIB=	/usr/local/lib/libdes.a
KDBLIB=	/usr/local/lib/libkrb_dbm.a
INCDIR=	/usr/include/kerberos
E 3
SRC1=	registerd.c
I 3
OBJ1=	registerd.o
E 3
SRC2=	register.c
I 3
OBJ2=	register.o
E 3
SRC3=	make_keypair.c
I 3
OBJ3=	make_keypair.o
E 3
D 2
OBJS=
E 2
I 2
D 4
OBJS=	register.o registerd.o make_keypair.o
E 4
I 4
EXTSRC=	des_rw.c
EXTOBJ=	des_rw.o
OBJS=	register.o registerd.o make_keypair.o ${EXTOBJ}
E 4
E 2
MAN=	register.0 registerd.0 make_keypair.0
I 4
VPATH=	../../usr.bin/rlogin/des
E 4

all: registerd register make_keypair

D 3
registerd: ${SRC1} ${LIBC} ${KLIB} ${DESLIB} registerd.c
	${CC} -o $@ -I${INCDIR} ${CFLAGS} ${CDEFS} ${SRC1} ../lib/des_rw.o -lutil -lkrb -lkrb_dbm -ldes
E 3
I 3
D 4
registerd: ${OBJ1} ${LIBC}
	${CC} -o $@ ${CFLAGS} ${SRC1} -lutil -lkdb -lkrb -ldes -lkrb
E 4
I 4
registerd: ${OBJ1} ${LIBC} ${EXTOBJ}
	${CC} -o $@ ${CFLAGS} ${OBJ1} ${EXTOBJ} -lutil -lkdb -lkrb -ldes
E 4
E 3

D 3
register: ${SRC2} ${LIBC} ${KLIB} ${DESLIB} register.c
	${CC} -o $@ -I${INCDIR} ${CFLAGS} ${CDEFS} ${SRC2} ../lib/des_rw.o -lutil -lkrb -ldes
E 3
I 3
D 4
register: ${OBJ2} ${LIBC}
	${CC} -o $@ ${CFLAGS} ${SRC2} -lutil -lkrb -ldes -lkrb
E 4
I 4
register: ${OBJ2} ${LIBC} ${EXTOBJ}
	${CC} -o $@ ${CFLAGS} ${OBJ2} ${EXTOBJ} -lutil -lkrb -ldes -lkrb
E 4
E 3

D 3
make_keypair: ${SRC3} ${LIBC} ${KLIB} ${DESLIB} make_keypair.c
	${CC} -o $@ -I${INCDIR} ${CFLAGS} ${CDEFS} ${SRC3} ../lib/des_rw.o -lutil -lkrb -lkrb_dbm -ldes
E 3
I 3
make_keypair: ${OBJ3} ${LIBC}
D 4
	${CC} -o $@ ${CFLAGS} ${SRC3} -lutil -lkdb -lkrb -ldes
E 4
I 4
	${CC} -o $@ ${CFLAGS} ${OBJ3} -lutil -lkdb -lkrb -ldes
E 4
E 3

clean:
	rm -f ${OBJS} core registerd register make_keypair

cleandir: clean
	rm -f ${MAN} tags .depend

D 4
depend: ${SRC1} ${SRC2} ${SRC3}
	mkdep -p ${CFLAGS} ${SRC1} ${SRC2} ${SRC3}
E 4
I 4
depend: ${SRC1} ${SRC2} ${SRC3} ${EXTSRC}
	mkdep -p ${CFLAGS} ${SRC1} ${SRC2} ${SRC3} ${EXTSRC}
E 4

D 3
install: ${MAN}
	install -s -o bin -g bin -m 755 registerd ${DESTDIR}/etc/registerd
D 2
	install -s -o bin -g bin -m 755 register ${DESTDIR}/usr/local/register
E 2
I 2
	install -s -o root -g bin -m 4755 register ${DESTDIR}/usr/local/register
E 3
I 3
#install: ${MAN}
install:
	install -s -o bin -g bin -m 755 registerd ${DESTDIR}/usr/libexec
D 4
	install -s -o root -g bin -m 4755 register ${DESTDIR}/usr/athena/register
E 3
E 2
	install -c -o bin -g bin -m 444 registerd.0 ${DESTDIR}/usr/man/cat8
	install -c -o bin -g bin -m 444 register.0 ${DESTDIR}/usr/man/cat1
	install -c -o bin -g bin -m 444 make_keypair.0 ${DESTDIR}/usr/man/cat8
E 4
I 4
	install -s -o root -g bin -m 4755 register ${DESTDIR}/usr/local/register
#	install -c -o bin -g bin -m 444 registerd.0 ${DESTDIR}/usr/man/cat8
#	install -c -o bin -g bin -m 444 register.0 ${DESTDIR}/usr/man/cat1
#	install -c -o bin -g bin -m 444 make_keypair.0 ${DESTDIR}/usr/man/cat8
E 4

lint: ${SRC1} ${SRC2} ${SRC3}
	lint ${CFLAGS} ${SRC1} ${SRC2} ${SRC3}

tags: ${SRC1} ${SRC2} ${SRC3}
	ctags ${SRC1} ${SRC2} ${SRC3}
E 5
I 5
.include <bsd.prog.mk>
E 5
E 1
