h33465
s 00000/00000/00007
d D 8.1 93/06/06 14:47:33 bostic 7 6
c 4.4BSD snapshot (revision 8.1)
e
s 00004/00044/00003
d D 4.6 90/05/11 15:09:38 bostic 6 5
c first pass for new make
e
s 00001/00001/00046
d D 4.5 89/05/11 09:56:58 bostic 5 4
c file reorg, pathnames.h, paths.h
e
s 00028/00021/00019
d D 4.4 88/10/25 15:45:23 bostic 4 3
c add man page, cleanup
e
s 00035/00010/00005
d D 4.3 87/06/18 17:51:34 bostic 3 2
c new template
e
s 00002/00000/00013
d D 4.2 87/05/31 21:29:37 bostic 2 1
c added depend label
e
s 00013/00000/00000
d D 4.1 83/03/30 12:03:04 sam 1 0
c date and time created 83/03/30 12:03:04 by sam
e
u
U
t
T
I 1
D 3
#	%M%	%I%	%E%
E 3
D 6
#
D 3
CFLAGS=-O
DESTDIR=
E 3
I 3
D 4
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 4
I 4
# Copyright (c) 1987 The Regents of the University of California.
# All rights reserved.
E 4
#
D 4
#	%W%	(Berkeley)	%G%
E 4
I 4
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
# WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
#
E 6
I 4
#	%W% (Berkeley) %G%
D 6
#
E 4
CFLAGS=	-O
LIBC=	/lib/libc.a
SRCS=	graph.c
D 4
OBJS=	graph.o
E 4
I 4
OBJS=
MAN=	graph.0
E 6
E 4
E 3

D 3
graph: graph.c
	${CC} $(CFLAGS) -o graph graph.c -lplot -lm
E 3
I 3
D 6
all: graph
E 6
I 6
PROG=	graph
DPADD=	${LIBM} ${LIBPLOT}
LDADD=	-lplot -lm
E 6
E 3

D 3
install: graph
	install -s graph ${DESTDIR}/usr/bin/graph
E 3
I 3
D 6
graph: ${SRCS} ${LIBC}
D 4
	${CC} -o $@ ${CFLAGS} ${SRCS} -lplot -lm
E 4
I 4
	${CC} -o $@ ${CFLAGS} $@.c -lplot -lm
E 4
E 3

D 3
clean:
	rm -f *.o graph
E 3
I 3
D 4
clean: FRC
E 4
I 4
clean:
E 4
	rm -f ${OBJS} core graph
E 3
I 2

D 3
depend:
E 3
I 3
D 4
depend: FRC
	mkdep ${CFLAGS} ${SRCS}
E 4
I 4
cleandir: clean
	rm -f ${MAN} tags .depend
E 4

D 4
install: FRC
E 4
I 4
depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
E 4
D 5
	install -s -o bin -g bin -m 755 graph ${DESTDIR}/usr/bin/graph
E 5
I 5
	install -s -o bin -g bin -m 755 graph ${DESTDIR}/usr/bin
E 5
I 4
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
E 4

D 4
lint: FRC
E 4
I 4
lint: ${SRCS}
E 4
	lint ${CFLAGS} ${SRCS}

D 4
tags: FRC
E 4
I 4
tags: ${SRCS}
E 4
	ctags ${SRCS}
E 6
I 6
.include <bsd.prog.mk>
E 6
D 4

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

graph.o: graph.c /usr/include/stdio.h /usr/include/ctype.h /usr/include/math.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 4
E 3
E 2
E 1
