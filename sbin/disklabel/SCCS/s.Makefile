h46245
s 00000/00002/00014
d D 8.2 94/03/17 07:18:03 bostic 11 10
c Don't install disklabel setgid; it doesn't need to be setgid if it
c isn't world executable; if it isn't setgid, it can be world executable.
c From: Craig Leres <leres@ee.lbl.gov>
e
s 00000/00000/00016
d D 8.1 93/06/05 10:50:58 bostic 10 9
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00002/00015
d D 5.8 92/03/16 14:25:41 bostic 9 8
c build the man page, too
e
s 00002/00001/00015
d D 5.7 91/11/15 17:19:03 bostic 8 7
c add program target
e
s 00001/00000/00015
d D 5.6 91/04/01 08:51:57 bostic 7 5
c add dkcksum.c (taken from C library)
e
s 00001/00000/00015
d R 5.6 91/01/15 14:06:23 bostic 6 5
c kernel reorg
e
s 00001/00000/00014
d D 5.5 90/07/01 10:45:44 bostic 5 4
c quick, wrong, fix for the June tape
e
s 00010/00045/00004
d D 5.4 90/05/11 13:05:48 bostic 4 3
c first pass for new make
e
s 00001/00001/00048
d D 5.3 89/05/11 13:51:46 bostic 3 2
c file reorg, pathnames.h, paths.h
e
s 00003/00002/00046
d D 5.2 88/10/31 21:28:39 bostic 2 1
c add disklabel.5 
e
s 00048/00000/00000
d D 5.1 88/10/19 11:01:43 bostic 1 0
c date and time created 88/10/19 11:01:43 by bostic
e
u
U
t
T
I 1
D 4
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
E 4
I 4
#	%W% (Berkeley) %G%
E 4

D 4
CFLAGS=	-O
LIBC=	/lib/libc.a
SRCS=	disklabel.c
OBJS=
D 2
MAN=	disklabel.0
E 2
I 2
MAN=	disklabel.0 disklabel.5.0
E 4
I 4
PROG=	disklabel
I 7
SRCS=	disklabel.c dkcksum.c
E 7
MAN8=	disklabel.0
D 11
BINGRP=operator
BINMODE=2550
E 11
I 5
CLEANFILES=disklabel.5.0
E 5
E 4
E 2

D 4
all: disklabel
E 4
I 4
D 8
all: disklabel.5.0
E 8
I 8
D 9
all: disklabel
disklabel: disklabel.5.0
E 9
I 9
all: ${PROG} disklabel.5.0 ${MAN8}
E 9
E 8
E 4

D 4
disklabel: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c
E 4
I 4
beforeinstall:
	install -c -o ${MANOWN} -g ${MANGRP} -m ${MANMODE} disklabel.5.0 \
	    ${DESTDIR}${MANDIR}5/disklabel.0
E 4

D 4
clean:
	rm -f ${OBJS} core disklabel

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 3
	install -s -o bin -g operator -m 2750 disklabel ${DESTDIR}/etc
E 3
I 3
	install -s -o bin -g operator -m 2750 disklabel ${DESTDIR}/sbin
E 3
D 2
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat8
E 2
I 2
	install -c -o bin -g bin -m 444 disklabel.0 ${DESTDIR}/usr/man/cat8
	install -c -o bin -g bin -m 444 disklabel.5.0 ${DESTDIR}/usr/man/cat5/disklabel.0
E 2

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 4
I 4
.include <bsd.prog.mk>
E 4
E 1
