h46082
s 00023/00018/00022
d D 5.4 89/05/10 22:40:16 bostic 4 3
c new template
e
s 00034/00007/00006
d D 5.3 87/06/19 11:18:35 bostic 3 2
c new template
e
s 00004/00002/00009
d D 5.2 86/07/26 13:19:16 sam 2 1
c tahoe
e
s 00011/00000/00000
d D 5.1 85/07/12 19:31:28 mckusick 1 0
c date and time created 85/07/12 19:31:28 by mckusick
e
u
U
t
T
I 1
#
D 3
#	%W%	(Berkeley)	%E%
E 3
I 3
D 4
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 4
I 4
# Copyright (c) 1989 The Regents of the University of California.
# All rights reserved.
E 4
E 3
#
D 2
libg.a:	dbxxx.s
	as dbxxx.s -o libg.a
E 2
I 2
D 3
DESTDIR=
E 3
I 3
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
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
#
I 4
#	%W% (Berkeley) %G%
#
E 4
CFLAGS=	-O
LIBC=	/lib/libc.a
SRCS=	dbxxx.c
OBJS=	dbxxx.o
E 3

D 3
libg.a:	dbxxx.c
E 3
I 3
all: libg.a

libg.a: dbxxx.c
E 3
	${CC} -E dbxxx.c | ${AS} -o libg.a
E 2

D 3
install: libg.a
	install -c libg.a ${DESTDIR}/usr/lib
E 3
I 3
D 4
clean: FRC
E 4
I 4
clean:
E 4
	rm -f ${OBJS} core libg.a
E 3

D 3
clean:
	rm -f libg.a
E 3
I 3
D 4
depend: FRC
E 4
I 4
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 4
	mkdep ${CFLAGS} ${SRCS}

D 4
install: FRC
E 4
I 4
install: ${MAN}
E 4
	install -o bin -g bin -m 644 libg.a ${DESTDIR}/usr/lib/libg.a

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
D 4

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

dbxxx.o: dbxxx.c

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 4
E 3
E 1
