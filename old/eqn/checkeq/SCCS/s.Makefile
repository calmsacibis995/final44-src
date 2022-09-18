h62788
s 00001/00000/00006
d D 5.3 90/05/11 15:11:44 bostic 3 2
c add makefile.inc
e
s 00004/00045/00002
d D 5.2 90/05/11 15:10:47 bostic 2 1
c first pass for new make
e
s 00047/00000/00000
d D 5.1 88/10/22 15:57:12 bostic 1 0
c date and time created 88/10/22 15:57:12 by bostic
e
u
U
t
T
I 1
D 2
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
E 2
I 2
#	%W% (Berkeley) %G%
E 2

D 2
CFLAGS=	-O
LIBC=	/lib/libc.a
SRCS=	checkeq.c
OBJS=
MAN=
E 2
I 2
PROG=	checkeq
NOMAN=	noman
E 2

I 3
.include "../../Makefile.inc"
E 3
D 2
all: checkeq

checkeq: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c

clean:
	rm -f ${OBJS} core checkeq

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
	install -s -o bin -g bin -m 755 checkeq ${DESTDIR}/usr/bin

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 2
I 2
.include <bsd.prog.mk>
E 2
E 1
