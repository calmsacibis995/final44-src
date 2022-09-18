h65425
s 00000/00000/00008
d D 8.1 93/06/06 14:50:15 bostic 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00001/00008
d D 5.5 91/03/07 22:14:41 donn 5 4
c ... or maybe it doesn't after all
e
s 00001/00000/00008
d D 5.4 91/03/07 21:15:20 bostic 4 3
c hexdump *needs* writable strings...
e
s 00005/00051/00003
d D 5.3 90/05/11 15:18:43 bostic 3 2
c first pass for new make
e
s 00002/00002/00052
d D 5.2 89/08/29 23:01:47 bostic 2 1
c remove bpad.c
e
s 00054/00000/00000
d D 5.1 89/08/29 18:36:09 bostic 1 0
c date and time created 89/08/29 18:36:09 by bostic
e
u
U
t
T
I 1
D 3
#
# Copyright (c) 1989 The Regents of the University of California.
# All rights reserved.
#
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
#
E 3
#	%W% (Berkeley) %G%
D 3
#
CFLAGS=	-O
LIBC=	/lib/libc.a
D 2
SRCS=	bpad.c conv.c display.c hexdump.c parse.c
OBJS=	bpad.o conv.o display.o hexdump.o parse.o
E 2
I 2
SRCS=	conv.c display.c hexdump.c parse.c
OBJS=	conv.o display.o hexdump.o parse.o
E 2
MAN=	hexdump.0
E 3

D 3
all: hexdump
E 3
I 3
PROG=	hexdump
I 4
D 5
CFLAGS+=-fwritable-strings
E 5
E 4
SRCS=	conv.c display.c hexdump.c hexsyntax.c odsyntax.c parse.c
MAN1=	hexdump.0 od.0
LINKS=	${BINDIR}/hexdump ${BINDIR}/od
E 3

D 3
hexdump: ${LIBC} ${OBJS}
	${CC} -o $@ ${CFLAGS} ${OBJS}

hexdump.0: hexdump.1
	tbl hexdump.1 | nroff -man > hexdump.0

clean:
	rm -f ${OBJS} core hexdump

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep ${CFLAGS} ${SRCS}

install: ${MAN}
	install -s -o bin -g bin -m 755 hexdump ${DESTDIR}/usr/bin
	rm -f ${DESTDIR}/usr/bin/od
	ln ${DESTDIR}/usr/bin/hexdump ${DESTDIR}/usr/bin/od
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
	rm -f ${DESTDIR}/usr/man/cat1/od.0
	ln ${DESTDIR}/usr/man/cat1/hexdump.0 ${DESTDIR}/usr/man/cat1/od.0

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 3
I 3
.include <bsd.prog.mk>
E 3
E 1
