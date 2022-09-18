h26983
s 00000/00000/00009
d D 8.1 93/06/06 16:42:11 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00006/00046/00003
d D 5.3 90/05/11 14:22:14 bostic 3 2
c first pass for new make
e
s 00001/00001/00048
d D 5.2 89/05/11 13:33:23 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00049/00000/00000
d D 5.1 88/10/22 16:20:45 bostic 1 0
c date and time created 88/10/22 16:20:45 by bostic
e
u
U
t
T
I 1
D 3
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
E 3
I 3
#	%W% (Berkeley) %G%
E 3

D 3
CFLAGS=	-O
LIBC=	/lib/libc.a
SRCS=	units.c
OBJS=
MAN=	units.0
E 3
I 3
PROG=	units
E 3

D 3
all: units
E 3
I 3
beforeinstall:
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${.CURDIR}/units.lib \
	    ${DESTDIR}/usr/share/misc
E 3

D 3
units: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c

clean:
	rm -f ${OBJS} core units

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
	install -s -o bin -g bin -m 755 units ${DESTDIR}/usr/bin
D 2
	install -c -o bin -g bin -m 755 units.lib ${DESTDIR}/usr/lib/units
E 2
I 2
	install -c -o bin -g bin -m 755 units.lib ${DESTDIR}/usr/share/misc
E 2
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 3
I 3
.include <bsd.prog.mk>
E 3
E 1
