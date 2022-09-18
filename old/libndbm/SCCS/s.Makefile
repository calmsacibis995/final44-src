h20369
s 00006/00002/00011
d D 5.10 91/02/21 16:41:52 bostic 10 9
c move from libc into libdbm
e
s 00000/00001/00013
d D 5.9 90/06/08 14:05:40 bostic 9 8
c don't need bsd.own.mk
e
s 00001/00000/00013
d D 5.8 90/05/13 14:42:44 bostic 8 7
c needs BINOWN etc.
e
s 00009/00059/00004
d D 5.7 90/05/11 12:50:39 bostic 7 6
c first pass for new make
e
s 00008/00001/00055
d D 5.6 89/04/10 12:01:27 bostic 6 5
c add man page links
e
s 00025/00018/00031
d D 5.5 89/04/03 22:18:50 bostic 5 4
c add man page
e
s 00029/00013/00020
d D 5.4 87/06/19 11:15:06 bostic 4 3
c new template
e
s 00001/00001/00032
d D 5.3 86/04/30 07:51:56 lepreau 3 2
c make dbm.h mode 444
e
s 00006/00001/00027
d D 5.2 85/06/26 14:36:55 bloom 2 1
c Add copyright
e
s 00028/00000/00000
d D 5.1 85/06/25 18:56:40 kre 1 0
c date and time created 85/06/25 18:56:40 by kre
e
u
U
t
T
I 1
D 2
#	%M%	%I%	%E%
E 2
I 2
D 7
#
D 4
# Copyright (c) 1980 Regents of the University of California.
E 4
I 4
D 5
# Copyright (c) 1987 Regents of the University of California.
E 4
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 5
I 5
# Copyright (c) 1989 The Regents of the University of California.
# All rights reserved.
E 5
#
D 4
#	%W% (Berkeley) %G%
E 4
I 4
D 5
#	%W%	(Berkeley)	%G%
E 5
I 5
# Redistribution and use in source and binary forms are permitted
# provided that the above copyright notice and this paragraph are
# duplicated in all such forms and that any documentation,
# advertising materials, and other materials related to such
# distribution and use acknowledge that the software was developed
# by the University of California, Berkeley.  The name of the
# University may not be used to endorse or promote products derived
# from this software without specific prior written permission.
# THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 5
E 4
E 2
#
E 7
I 5
#	%W% (Berkeley) %G%
D 7
#
E 5
D 4
CFLAGS=-O
TAGSFILE=tags
E 4
I 4
CFLAGS=	-O
LIBC=	/lib/libc.a
E 7
I 7

LIB=	dbm
E 7
D 10
SRCS=	dbm.c
D 7
OBJS=	dbm.o
I 5
MAN=	dbm.0
I 6
MDIR=	${DESTDIR}/usr/man/cat3
E 7
I 7
MAN3=	dbm.0
E 10
I 10
CFLAGS+=-I${.CURDIR}
SRCS=	dbm.c ndbm.c
MAN3=	dbm.0 ndbm.0
E 10
MLINKS+=dbm.3 dbminit.3 dbm.3 delete.3 dbm.3 fetch.3 dbm.3 firstkey.3 \
	dbm.3 nextkey.3 dbm.3 store.3
I 10
MLINKS+=ndbm.3 dbm_clearerr.3 ndbm.3 dbm_close.3 ndbm.3 dbm_delete.3 \
	ndbm.3 dbm_error.3 ndbm.3 dbm_fetch.3 ndbm.3 dbm_firstkey.3 \
	ndbm.3 dbm_nextkey.3 ndbm.3 dbm_open.3 ndbm.3 dbm_store.3
E 10
E 7
E 6
E 5
E 4

D 7
all: libdbm.a libdbm_p.a
E 7
I 7
beforeinstall:
	install -c -o ${BINOWN} -g ${BINGRP} -m ${MANMODE} ${.CURDIR}/dbm.h \
	    ${DESTDIR}/usr/include/dbm.h
E 7

I 8
D 9
.include <bsd.own.mk>
E 9
E 8
D 7
libdbm.a: dbm.c
	${CC} -c ${CFLAGS} dbm.c
	ld -r -o libdbm.a -x dbm.o
	rm -f dbm.o

libdbm_p.a: dbm.c
	${CC} -p -c ${CFLAGS} dbm.c
	ld -r -o libdbm_p.a -X dbm.o
	rm -f dbm.o

D 4
install: all
	install -m 644 libdbm.a $(DESTDIR)/usr/lib
	install -m 644 libdbm_p.a $(DESTDIR)/usr/lib
	-cmp -s dbm.h $(DESTDIR)/usr/include/dbm.h || \
D 3
		install -c -m 644 dbm.h $(DESTDIR)/usr/include
E 3
I 3
		install -c -m 444 dbm.h $(DESTDIR)/usr/include
E 4
I 4
D 5
clean: FRC
E 5
I 5
clean:
E 5
	rm -f ${OBJS} core libdbm.a libdbm_p.a
E 4
E 3

D 4
tags:
	ctags -a -f ${TAGSFILE} `pwd`/dbm.c
E 4
I 4
D 5
depend: FRC
E 5
I 5
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 5
	mkdep ${CFLAGS} ${SRCS}
E 4

D 4
clean:
	rm -f *.o libdbm.a libdbm_p.a errs a.out core
E 4
I 4
D 5
install: FRC
E 5
I 5
install: ${MAN}
D 6
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat3
E 6
E 5
	install -o bin -g bin -m 644 libdbm.a ${DESTDIR}/usr/lib/libdbm.a
	install -o bin -g bin -m 644 libdbm_p.a ${DESTDIR}/usr/lib/libdbm_p.a
	install -c -o bin -g bin -m 444 dbm.h ${DESTDIR}/usr/include/dbm.h
I 6
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat3
	rm -f ${MDIR}/dbminit.0; ln ${MDIR}/dbm.0 ${MDIR}/dbminit.0
	rm -f ${MDIR}/delete.0; ln ${MDIR}/dbm.0 ${MDIR}/delete.0
	rm -f ${MDIR}/fetch.0; ln ${MDIR}/dbm.0 ${MDIR}/fetch.0
	rm -f ${MDIR}/firstkey.0; ln ${MDIR}/dbm.0 ${MDIR}/firstkey.0
	rm -f ${MDIR}/nextkey.0; ln ${MDIR}/dbm.0 ${MDIR}/nextkey.0
	rm -f ${MDIR}/store.0; ln ${MDIR}/dbm.0 ${MDIR}/store.0
E 6

D 5
lint: FRC
E 5
I 5
lint: ${SRCS}
E 5
	lint ${CFLAGS} ${SRCS}

D 5
tags: FRC
E 5
I 5
tags: ${SRCS}
E 5
	ctags ${SRCS}
E 7
I 7
.include <bsd.lib.mk>
E 7
D 5

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

dbm.o: dbm.c dbm.h /usr/include/ndbm.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 5
E 4
E 1
