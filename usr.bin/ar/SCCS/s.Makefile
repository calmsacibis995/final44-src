h22781
s 00000/00000/00016
d D 8.1 93/06/06 14:19:50 bostic 9 8
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00014
d D 5.8 91/03/10 15:38:43 bostic 8 7
c fold header.c into archive.c
e
s 00010/00003/00005
d D 5.7 91/01/17 18:24:37 bostic 7 6
c new version
e
s 00002/00001/00006
d D 5.6 90/06/19 18:23:56 bostic 6 5
c install in section 5 as "ar", too
e
s 00001/00000/00006
d D 5.5 90/06/19 17:59:47 bostic 5 4
c forgot ar.0
e
s 00004/00047/00002
d D 5.4 90/05/11 13:50:53 bostic 4 3
c first pass for new make
e
s 00001/00001/00048
d D 5.3 89/05/10 22:16:57 bostic 3 2
c file reorg, pathnames.h, paths.h
e
s 00004/00003/00045
d D 5.2 89/05/08 13:00:21 bostic 2 1
c file system reorg and pathnames.h
e
s 00048/00000/00000
d D 5.1 88/10/18 20:14:26 bostic 1 0
c date and time created 88/10/18 20:14:26 by bostic
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
SRCS=	ar.c
OBJS=
D 2
MAN=	ar.0
E 2
I 2
MAN=	ar.0 ar5.0
E 4
I 4
PROG=	ar
I 7
CFLAGS+=-I${.CURDIR}
D 8
SRCS=	append.c ar.c archive.c contents.c delete.c extract.c header.c \
	misc.c move.c print.c replace.c 
E 8
I 8
SRCS=	append.c ar.c archive.c contents.c delete.c extract.c misc.c \
	move.c print.c replace.c 
E 8
E 7
I 5
MAN1=	ar.0
E 5
D 6
MAN5=	ar.format.0
E 6
I 6
D 7
MAN5=	arformat.0
MLINKS=	arformat.5 ar.5
E 7
I 7
CLEANFILES=ar.5.0

ar.0: ar.5.0

afterinstall:
	install -c -o ${MANOWN} -g ${MANGRP} -m ${MANMODE} ar.5.0 \
	    ${DESTDIR}${MANDIR}5/ar.0
E 7
E 6
E 4
E 2

D 4
all: ar

ar: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c

clean:
	rm -f ${OBJS} core ar

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 2
	install -s -o bin -g bin -m 755 ar ${DESTDIR}/bin
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
E 2
I 2
D 3
	install -s -o bin -g bin -m 755 ar ${DESTDIR}/usr/pgrm
E 3
I 3
	install -s -o bin -g bin -m 755 ar ${DESTDIR}/usr/bin
E 3
	install -c -o bin -g bin -m 444 ar.0 ${DESTDIR}/usr/man/cat1
	install -c -o bin -g bin -m 444 ar5.0 ${DESTDIR}/usr/man/cat5/ar.0
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
