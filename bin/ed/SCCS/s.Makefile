h55962
s 00003/00046/00002
d D 5.2 90/05/11 12:41:56 bostic 2 1
c first pass for new make
e
s 00048/00000/00000
d D 5.1 88/10/18 22:31:41 bostic 1 0
c date and time created 88/10/18 22:31:41 by bostic
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
SRCS=	ed.c
OBJS=
MAN=	ed.0
E 2
I 2
PROG=	ed
E 2

D 2
all: ed

ed: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c

clean:
	rm -f ${OBJS} core ed

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
	install -s -o bin -g bin -m 755 ed ${DESTDIR}/bin
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 2
I 2
.include <bsd.prog.mk>
E 2
E 1
