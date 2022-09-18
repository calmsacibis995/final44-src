h40644
s 00000/00000/00009
d D 8.1 93/05/31 16:14:10 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00005/00048/00003
d D 5.3 90/05/11 12:45:13 bostic 3 2
c first pass for new make
e
s 00005/00005/00046
d D 5.2 88/10/19 15:40:24 bostic 2 1
c add morse, ppt
e
s 00048/00000/00000
d D 5.1 88/10/19 15:27:18 bostic 1 0
c date and time created 88/10/19 15:27:18 by bostic
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
# WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
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
D 2
SRCS=	bcd.c
E 2
I 2
SRCS=	bcd.c morse.c ppt.c
E 2
OBJS=
MAN=	bcd.0
E 3
I 3
PROG=	bcd
MAN6=	bcd.0
MLINKS=	bcd.6 morse.6 bcd.6 ppt.6
HIDEGAME=hidegame
E 3

D 2
all: bcd
E 2
I 2
D 3
all: bcd morse ppt
E 3
I 3
.include <bsd.prog.mk>
E 3
E 2

D 2
bcd: ${LIBC}
E 2
I 2
D 3
bcd morse ppt: ${LIBC}
E 2
	${CC} -o $@ ${CFLAGS} $@.c

clean:
D 2
	rm -f ${OBJS} core bcd
E 2
I 2
	rm -f ${OBJS} core bcd morse ppt
E 2

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 2
	install -s -o bin -g bin -m 755 bcd ${DESTDIR}/usr/games
E 2
I 2
	install -s -o bin -g bin -m 755 bcd morse ppt ${DESTDIR}/usr/games
E 2
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat6
	rm -f ${DESTDIR}/usr/man/cat6/morse.0 ${DESTDIR}/usr/man/cat6/ppt.0
	ln ${DESTDIR}/usr/man/cat6/bcd.0 ${DESTDIR}/usr/man/cat6/morse.0
	ln ${DESTDIR}/usr/man/cat6/bcd.0 ${DESTDIR}/usr/man/cat6/ppt.0

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 3
E 1
