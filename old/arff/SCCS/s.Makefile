h38851
s 00000/00001/00007
d D 5.4 91/01/20 16:23:03 bostic 4 3
c give flcopy its own manual page
e
s 00006/00052/00002
d D 5.3 90/05/11 16:05:45 bostic 3 2
c first pass for new make
e
s 00002/00002/00052
d D 5.2 89/05/11 14:15:14 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00054/00000/00000
d D 5.1 88/09/19 15:01:04 bostic 1 0
c date and time created 88/09/19 15:01:04 by bostic
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
SRCS=	arff.c
OBJS=
MAN=	arff.0
E 3
I 3
PROG=	arff
MAN8=	arff.0
MANSUBDIR=/vax
D 4
MLINKS=	arff.8 flcopy.8
E 4
E 3

D 3
all: arff flcopy

arff: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c

flcopy: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c

clean:
	rm -f ${OBJS} core arff flcopy

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 2
	install -s -o bin -g bin -m 755 arff ${DESTDIR}/etc/arff
	install -s -o bin -g bin -m 755 arff ${DESTDIR}/etc/flcopy
E 2
I 2
	install -s -o bin -g bin -m 755 arff ${DESTDIR}/usr/sbin
	install -s -o bin -g bin -m 755 flcopy ${DESTDIR}/usr/sbin
E 2
	install -c -o bin -g bin -m 444 arff.0 ${DESTDIR}/usr/man/cat8/vax
	rm -f ${DESTDIR}/usr/man/cat8/vax/flcopy.0
	ln ${DESTDIR}/usr/man/cat8/vax/arff.0 ${DESTDIR}/usr/man/cat8/vax/flcopy.0

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 3
I 3
.include <bsd.prog.mk>
E 3
E 1
