h12750
s 00000/00000/00005
d D 8.1 93/06/06 14:40:22 bostic 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00044/00003
d D 5.5 90/05/11 13:50:25 bostic 5 4
c first pass for new make
e
s 00001/00001/00046
d D 5.4 90/03/23 10:32:30 bostic 4 3
c checkpoint before pmake
e
s 00001/00001/00046
d D 5.3 89/05/10 22:25:41 bostic 3 2
c file reorg, pathnames.h, paths.h
e
s 00027/00021/00020
d D 5.2 88/10/25 18:20:51 bostic 2 1
c add man page, cleanup
e
s 00041/00000/00000
d D 5.1 87/12/12 17:41:32 bostic 1 0
c date and time created 87/12/12 17:41:32 by bostic
e
u
U
t
T
I 1
D 5
#
D 2
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 2
I 2
# Copyright (c) 1987 The Regents of the University of California.
# All rights reserved.
E 2
#
D 2
#	%W%	(Berkeley)	%G%
E 2
I 2
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
E 2
#
E 5
I 2
#	%W% (Berkeley) %G%
D 5
#
E 2
CFLAGS=	-O
LIBC=	/lib/libc.a
SRCS=	fsplit.c
D 2
OBJS=	fsplit.o
E 2
I 2
OBJS=
MAN=	fsplit.0
E 5
E 2

D 5
all: fsplit
E 5
I 5
PROG=	fsplit
E 5

D 2
fsplit:	${SRCS} ${LIBC}
E 2
I 2
D 5
fsplit: ${SRCS} ${LIBC}
E 2
D 4
	${CC} -o $@ ${CFLAGS} ${SRCS
E 4
I 4
	${CC} -o $@ ${CFLAGS} ${SRCS}
E 4

D 2
clean: FRC
E 2
I 2
clean:
E 2
	rm -f ${OBJS} core fsplit

D 2
depend: FRC
E 2
I 2
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 2
	mkdep -p ${CFLAGS} ${SRCS}

D 2
install: FRC
E 2
I 2
install: ${MAN}
E 2
D 3
	install -s -o bin -g bin -m 755 fsplit ${DESTDIR}/usr/ucb/fsplit
E 3
I 3
	install -s -o bin -g bin -m 755 fsplit ${DESTDIR}/usr/bin
E 3
I 2
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
E 2

D 2
lint: FRC
E 2
I 2
lint: ${SRCS}
E 2
	lint ${CFLAGS} ${SRCS}

D 2
tags: FRC
E 2
I 2
tags: ${SRCS}
E 2
	ctags ${SRCS}
E 5
I 5
.include <bsd.prog.mk>
E 5
D 2

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

fsplit: fsplit.c /usr/include/ctype.h /usr/include/stdio.h
fsplit: /usr/include/sys/types.h /usr/include/sys/stat.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 2
E 1
