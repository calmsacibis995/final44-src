h22833
s 00003/00003/00060
d D 1.4 90/06/29 17:12:56 kfall 4 3
c check in for Kevin Fall -- no idea what the changes are
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
#
# Copyright (c) 1988 Regents of the University of California.
# All rights reregisterded.
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

D 3
CDEFS=	-DKERBEROS
CFLAGS=	-O
E 3
I 3
CFLAGS=	-O -DKERBEROS
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
OBJS=	register.o registerd.o make_keypair.o
E 2
MAN=	register.0 registerd.0 make_keypair.0

all: registerd register make_keypair

D 3
registerd: ${SRC1} ${LIBC} ${KLIB} ${DESLIB} registerd.c
	${CC} -o $@ -I${INCDIR} ${CFLAGS} ${CDEFS} ${SRC1} ../lib/des_rw.o -lutil -lkrb -lkrb_dbm -ldes
E 3
I 3
registerd: ${OBJ1} ${LIBC}
D 4
	${CC} -o $@ ${CFLAGS} ${SRC1} -lutil -lkdb -lkrb -ldes -lkrb
E 4
I 4
	${CC} -o $@ ${CFLAGS} ${OBJ1} -lutil -lkdb -lkrb -ldes -lkrb
E 4
E 3

D 3
register: ${SRC2} ${LIBC} ${KLIB} ${DESLIB} register.c
	${CC} -o $@ -I${INCDIR} ${CFLAGS} ${CDEFS} ${SRC2} ../lib/des_rw.o -lutil -lkrb -ldes
E 3
I 3
register: ${OBJ2} ${LIBC}
D 4
	${CC} -o $@ ${CFLAGS} ${SRC2} -lutil -lkrb -ldes -lkrb
E 4
I 4
	${CC} -o $@ ${CFLAGS} ${OBJ2} -lutil -lkrb -ldes -lkrb
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

depend: ${SRC1} ${SRC2} ${SRC3}
	mkdep -p ${CFLAGS} ${SRC1} ${SRC2} ${SRC3}

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
	install -s -o root -g bin -m 4755 register ${DESTDIR}/usr/athena/register
E 3
E 2
	install -c -o bin -g bin -m 444 registerd.0 ${DESTDIR}/usr/man/cat8
	install -c -o bin -g bin -m 444 register.0 ${DESTDIR}/usr/man/cat1
	install -c -o bin -g bin -m 444 make_keypair.0 ${DESTDIR}/usr/man/cat8

lint: ${SRC1} ${SRC2} ${SRC3}
	lint ${CFLAGS} ${SRC1} ${SRC2} ${SRC3}

tags: ${SRC1} ${SRC2} ${SRC3}
	ctags ${SRC1} ${SRC2} ${SRC3}
E 1
