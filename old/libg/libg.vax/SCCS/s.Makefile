h16423
s 00021/00010/00017
d D 5.3 89/05/10 22:39:41 bostic 3 2
c new template
e
s 00023/00007/00004
d D 5.2 87/06/19 11:20:28 bostic 2 1
c new template
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
D 2
#	%W%	(Berkeley)	%E%
E 2
I 2
D 3
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 3
I 3
# Copyright (c) 1989 The Regents of the University of California.
# All rights reserved.
E 3
E 2
#
D 2
libg.a:	dbxxx.s
	as dbxxx.s -o libg.a
E 2
I 2
D 3
#	%W%	(Berkeley)	%G%
E 3
I 3
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
E 3
#
I 3
#	%W% (Berkeley) %G%
#
E 3
CFLAGS=	-O
LIBC=	/lib/libc.a
SRCS=
OBJS=
E 2

D 2
install: libg.a
	install -c libg.a ${DESTDIR}/usr/lib
E 2
I 2
all: libg.a
E 2

D 2
clean:
	rm -f libg.a
E 2
I 2
libg.a: dbxxx.s
	${AS} dbxxx.s -o $@

D 3
clean: FRC
E 3
I 3
clean:
E 3
	rm -f ${OBJS} core libg.a

D 3
install: FRC
E 3
I 3
cleandir: clean
	rm -f ${MAN} tags .depend

install: ${MAN}
E 3
	install -o bin -g bin -m 644 libg.a ${DESTDIR}/usr/lib/libg.a

D 3
depend:
lint:
tags:
FRC:
E 3
I 3
depend lint tags FRC:
E 3
E 2
E 1
