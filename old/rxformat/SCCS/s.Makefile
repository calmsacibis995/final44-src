h21991
s 00001/00000/00007
d D 5.4 91/04/11 11:21:16 sklower 4 3
c no links in /usr/include to vax specific stuff; so CFLAGS+=/sys
e
s 00005/00046/00002
d D 5.3 90/05/11 16:05:36 bostic 3 2
c first pass for new make
e
s 00001/00001/00047
d D 5.2 89/05/11 14:15:47 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00048/00000/00000
d D 5.1 88/09/19 15:01:17 bostic 1 0
c date and time created 88/09/19 15:01:17 by bostic
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
SRCS=	rxformat.c
OBJS=
MAN=	rxformat.0
E 3
I 3
PROG=	rxformat
MAN8=	rxformat.0
I 4
CFLAGS+=-I/sys
E 4
MANSUBDIR=/vax
E 3

D 3
all: rxformat

rxformat: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c

clean:
	rm -f ${OBJS} core rxformat

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 2
	install -s -o bin -g bin -m 755 rxformat ${DESTDIR}/etc/rxformat
E 2
I 2
	install -s -o bin -g bin -m 755 rxformat ${DESTDIR}/usr/sbin
E 2
	install -c -o bin -g bin -m 444 rxformat.0 ${DESTDIR}/usr/man/cat8/vax

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 3
I 3
.include <bsd.prog.mk>
E 3
E 1
