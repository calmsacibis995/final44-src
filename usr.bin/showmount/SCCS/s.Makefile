h08213
s 00000/00000/00007
d D 8.1 93/06/06 16:19:43 bostic 4 2
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00000/00007
d R 6.3 91/01/14 17:42:30 bostic 3 2
c kernel reorg
e
s 00005/00046/00002
d D 6.2 90/05/11 15:16:01 bostic 2 1
c first pass for new make
e
s 00048/00000/00000
d D 6.1 89/11/30 23:57:10 mckusick 1 0
c contributed by Rick Macklem
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
SRCS=	showmount.c
OBJS=
MAN=	showmount.0
E 2
I 2
PROG=	showmount
DPADD=	${LIBRPC}
LDADD=	-lrpc
E 2

D 2
all: showmount

showmount: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c -lrpc

clean:
	rm -f ${OBJS} core showmount

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
	install -s -o bin -g bin -m 755 showmount ${DESTDIR}/sbin
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat8

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 2
I 2
.include <bsd.prog.mk>
E 2
E 1
