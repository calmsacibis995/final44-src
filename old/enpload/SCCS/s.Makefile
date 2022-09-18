h37112
s 00001/00000/00014
d D 5.9 91/11/14 11:44:00 bostic 10 9
c use -I/sys for kernel includes
e
s 00000/00001/00014
d D 5.8 91/11/04 22:27:09 bostic 9 8
c enpload doesn't need -I/sys
e
s 00001/00000/00014
d D 5.7 91/01/17 14:51:52 bostic 8 6
c kernel reorg
e
s 00001/00000/00014
d R 5.7 91/01/14 17:20:07 bostic 7 6
c kernel reorg
e
s 00011/00045/00003
d D 5.6 90/05/11 13:00:28 bostic 6 5
c first pass for new make
e
s 00001/00001/00047
d D 5.5 90/02/24 22:07:56 bostic 5 4
c move enpcode to /etc; it's the only thing using /libdata
e
s 00002/00002/00046
d D 5.4 89/06/26 16:21:02 bostic 4 3
c enpload -> /sbin; enpcode -> /libdata
e
s 00002/00002/00046
d D 5.3 89/05/11 14:14:38 bostic 3 2
c file reorg, pathnames.h, paths.h
e
s 00002/00001/00046
d D 5.2 88/10/19 13:58:42 bostic 2 1
c add manual page
e
s 00047/00000/00000
d D 5.1 88/09/18 12:30:54 bostic 1 0
c date and time created 88/09/18 12:30:54 by bostic
e
u
U
t
T
I 1
D 6
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
E 6
I 6
#	%W% (Berkeley) %G%
E 6

D 6
CFLAGS=	-O
LIBC=	/lib/libc.a
SRCS=	enpload.c
D 2
MAN=
E 2
I 2
MAN=	enpload.0
E 6
I 6
PROG=	enpload
I 10
CFLAGS+=-I/sys
E 10
I 8
D 9
CFLAGS+=-I/sys
E 9
E 8
MAN8=	enpload.0
E 6
E 2

D 6
all: enpload
E 6
I 6
install:
	install ${STRIP} -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} enpload \
	    ${DESTDIR}${BINDIR}
	install -c -o ${MANOWN} -g ${MANGRP} -m ${MANMODE} ${MAN8} \
	    ${DESTDIR}${MANDIR}8/tahoe
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${.CURDIR}/enpcode \
	    ${DESTDIR}/etc
E 6

D 6
enpload: ${OBJS} ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c

clean:
	rm -f ${OBJS} core enpload

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 3
	install -s -o bin -g bin -m 755 enpload ${DESTDIR}/etc/enpload
E 3
I 3
D 4
	install -s -o bin -g bin -m 755 enpload ${DESTDIR}/usr/sbin
E 4
I 4
	install -s -o bin -g bin -m 755 enpload ${DESTDIR}/sbin
E 4
E 3
I 2
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat8/tahoe
E 2
D 3
	install -c -o bin -g bin -m 444 enpcode ${DESTDIR}/etc/enpcode
E 3
I 3
D 4
	install -c -o bin -g bin -m 444 enpcode ${DESTDIR}/usr/libdata
E 4
I 4
D 5
	install -c -o bin -g bin -m 444 enpcode ${DESTDIR}/libdata
E 5
I 5
	install -c -o bin -g bin -m 444 enpcode ${DESTDIR}/etc
E 5
E 4
E 3

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 6
I 6
.include <bsd.prog.mk>
E 6
E 1
