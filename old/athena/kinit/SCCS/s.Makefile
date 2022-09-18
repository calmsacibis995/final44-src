h14239
s 00001/00001/00048
d D 1.4 89/02/05 16:03:30 kfall 4 3
c install depends on kinit
e
s 00001/00001/00048
d D 1.3 89/02/04 14:18:05 kfall 3 2
c change install destination
e
s 00001/00001/00048
d D 1.2 89/02/03 23:19:09 kfall 2 1
c -g flag is now -O
e
s 00049/00000/00000
d D 1.1 89/02/03 23:18:43 kfall 1 0
c date and time created 89/02/03 23:18:43 by kfall
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
# @(#)Makefile	5.1 (Berkeley) 10/18/88
#

D 2
CFLAGS=	-g -DKERBEROS
E 2
I 2
CFLAGS=	-O -DKERBEROS
E 2
LIBC=	/lib/libc.a
LIBS=	/usr/lib/libkrb.a /usr/lib/libdes.a
SRCS=	kinit.c
OBJS=
MAN=	kinit.0

all: kinit

kinit: ${LIBS} ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c -lkrb -ldes

clean:
	rm -f ${OBJS} core kinit

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

D 4
install: ${MAN}
E 4
I 4
install: ${MAN} kinit
E 4
D 3
	install -s -o bin -g bin -m 755 kinit ${DESTDIR}/bin
E 3
I 3
	install -s -o bin -g bin -m 755 kinit ${DESTDIR}/usr/athena
E 3
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 1
