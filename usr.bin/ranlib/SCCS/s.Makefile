h39136
s 00000/00000/00016
d D 8.1 93/06/06 16:04:03 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00015
d D 5.4 91/03/12 09:20:01 bostic 4 3
c comply with ar source changes nothing else
e
s 00011/00000/00005
d D 5.3 91/01/18 18:45:04 bostic 3 2
c new version
e
s 00003/00046/00002
d D 5.2 90/05/11 13:49:34 bostic 2 1
c first pass for new make
e
s 00048/00000/00000
d D 5.1 88/10/22 16:14:22 bostic 1 0
c date and time created 88/10/22 16:14:22 by bostic
e
u
U
t
T
I 1
D 2
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
E 2
I 2
#	%W% (Berkeley) %G%
E 2

D 2
CFLAGS=	-O
LIBC=	/lib/libc.a
SRCS=	ranlib.c
OBJS=
MAN=	ranlib.0
E 2
I 2
PROG=	ranlib
I 3
D 4
SRCS=	archive.c build.c header.c misc.c ranlib.c touch.c
E 4
I 4
SRCS=	archive.c build.c misc.c ranlib.c touch.c
E 4
CFLAGS+=-I${.CURDIR} -I${.CURDIR}/../ar
MAN1=	ranlib.0
VPATH=	${.CURDIR}/../ar
CLEANFILES=ranlib.5.0

ranlib.0: ranlib.5.0

afterinstall:
	install -c -o ${MANOWN} -g ${MANGRP} -m ${MANMODE} ranlib.5.0 \
	    ${DESTDIR}${MANDIR}5/ranlib.0
E 3
E 2

D 2
all: ranlib

ranlib: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c

clean:
	rm -f ${OBJS} core ranlib

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
	install -s -o bin -g bin -m 755 ranlib ${DESTDIR}/usr/bin
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 2
I 2
.include <bsd.prog.mk>
E 2
E 1
