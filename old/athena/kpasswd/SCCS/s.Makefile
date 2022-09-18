h24029
s 00003/00002/00054
d D 1.3 90/06/29 17:12:39 kfall 3 2
c check in for Kevin Fall -- no idea what the changes are
e
s 00009/00012/00047
d D 1.2 89/05/17 22:49:59 kfall 2 1
c add Berkeley headers
e
s 00059/00000/00000
d D 1.1 88/12/12 20:32:14 kfall 1 0
c date and time created 88/12/12 20:32:14 by kfall
e
u
U
t
T
I 1
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
# @(#)Makefile	5.3 (Berkeley) 9/20/88
#

D 2
CDEFS=	-DKERBEROS
CFLAGS=	-O
E 2
I 2
CFLAGS=	-O -DKERBEROS
E 2
LIBC=	/lib/libc.a
D 2
KLIB=	/usr/local/lib/libkrb.a
DESLIB=	/usr/local/lib/libdes.a
KDBLIB=	/usr/local/lib/libkrb_dbm.a
INCDIR=	/usr/include/kerberos
E 2
SRC1=	kpasswd.c
I 2
OBJ1=	kpasswd.o
E 2
SRC2=	kpasswdd.c
I 2
OBJ2=	kpasswdd.o
E 2
OBJS=	kpasswd.o kpasswdd.o
MAN=	kpasswd.0 kpasswdd.0

all: kpasswd kpasswdd

D 2
kpasswd: ${SRC1} ${LIBC} ${KLIB} ${DESLIB} kpasswd.c
	${CC} -o $@ -I${INCDIR} ${CFLAGS} ${CDEFS} ${SRC1} ../lib/des_rw.o -lutil -lkrb -ldes
E 2
I 2
kpasswd: ${OBJ1} ${LIBC}
	${CC} -o $@ ${CFLAGS} ${OBJ1} -lutil -lkrb -ldes
E 2

D 2
kpasswdd: ${SRC2} ${LIBC} ${KLIB} ${DESLIB} kpasswdd.c
	${CC} -o $@ -I${INCDIR} ${CFLAGS} ${CDEFS} ${SRC2} ../lib/des_rw.o -lutil -lkrb -lkrb_dbm -ldes
E 2
I 2
kpasswdd: ${OBJ2} ${LIBC}
	${CC} -o $@ ${CFLAGS} ${OBJ2} -lutil -lkrb -lkdb -ldes
E 2

clean:
	rm -f ${OBJS} core kpasswd kpasswdd

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRC1} ${SRC2}
	mkdep -p ${CFLAGS} ${SRC1} ${SRC2}

D 3
install: ${MAN}
E 3
I 3
#install: ${MAN}
install:
E 3
D 2
	install -s -o bin -g bin -m 755 kpasswdd ${DESTDIR}/etc/kpasswdd
	install -s -o bin -g bin -m 755 kpasswd ${DESTDIR}/usr/local
E 2
I 2
	install -s -o bin -g bin -m 755 kpasswdd ${DESTDIR}/usr/libexec/kpasswdd
	install -s -o bin -g bin -m 755 kpasswd ${DESTDIR}/usr/athena
E 2
	install -c -o bin -g bin -m 444 kpasswd.0 ${DESTDIR}/usr/man/cat1
D 3
	install -c -o bin -g bin -m 444 kpasswdd.0 ${DESTDIR}/usr/man/cat8
E 3
I 3
#	install -c -o bin -g bin -m 444 kpasswdd.0 ${DESTDIR}/usr/man/cat8
E 3

lint: ${SRC1} ${SRC2}
	lint ${CFLAGS} ${SRC1} ${SRC2}

tags: ${SRC1} ${SRC2}
	ctags ${SRC1} ${SRC2}
E 1
