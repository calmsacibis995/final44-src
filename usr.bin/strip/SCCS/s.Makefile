h36695
s 00000/00000/00011
d D 8.1 93/06/06 16:25:57 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00007/00046/00004
d D 5.4 90/05/11 13:49:24 bostic 4 3
c first pass for new make
e
s 00003/00001/00047
d D 5.3 90/03/23 10:52:57 bostic 3 2
c check in for pmake
e
s 00001/00001/00047
d D 5.2 89/05/10 22:30:26 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00048/00000/00000
d D 5.1 88/10/18 22:15:53 bostic 1 0
c date and time created 88/10/18 22:15:53 by bostic
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
SRCS=	strip.c
OBJS=
MAN=	strip.0
E 4
I 4
PROG=	strip
E 4

D 4
all: strip

strip: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c

clean:
	rm -f ${OBJS} core strip

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 2
	install -s -o bin -g bin -m 755 strip ${DESTDIR}/bin
E 2
I 2
D 3
	install -s -o bin -g bin -m 755 strip ${DESTDIR}/usr/bin
E 3
I 3
	install -c -o bin -g bin -m 755 strip ${DESTDIR}/usr/bin
	./strip ${DESTDIR}/usr/bin/strip
E 4
I 4
install: maninstall
	install -c -o ${BINOWN} -g ${BINOWN} -m ${BINMODE} strip \
	    ${DESTDIR}${BINDIR}
	./strip ${DESTDIR}${BINDIR}/strip
E 4
	rm -f ./strip
E 3
E 2
D 4
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
E 4

D 4
lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 4
I 4
.include <bsd.prog.mk>
E 4
E 1
