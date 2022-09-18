h41111
s 00000/00000/00014
d D 8.1 93/06/06 13:57:47 bostic 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00006/00000/00008
d D 5.5 93/05/02 15:47:51 mckusick 5 4
c note taht the program may be safely run setuid to root
e
s 00002/00000/00006
d D 5.4 92/05/19 01:08:53 torek 4 3
c rewrite to use kvm library
e
s 00004/00046/00002
d D 5.3 90/05/11 16:39:44 bostic 3 2
c first pass for new make
e
s 00001/00001/00047
d D 5.2 89/05/11 14:08:34 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00048/00000/00000
d D 5.1 88/10/19 11:22:54 bostic 1 0
c date and time created 88/10/19 11:22:54 by bostic
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
# WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND
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
SRCS=	kgmon.c
OBJS=
MAN=	kgmon.0
E 3
I 3
PROG=	kgmon
MAN8=	kgmon.0
I 4
DPADD=	${LIBKVM}
LDADD=	-lkvm
I 5
#
# This program may safely be run setuid-root to allow non-root
# users to start, stop, and reset profiling buffers.
#
#BINOWN=root
#BINMODE=4555
E 5
E 4
E 3

D 3
all: kgmon

kgmon: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c

clean:
	rm -f ${OBJS} core kgmon

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 2
	install -s -o bin -g bin -m 755 kgmon ${DESTDIR}/etc
E 2
I 2
	install -s -o bin -g bin -m 755 kgmon ${DESTDIR}/usr/sbin
E 2
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat8

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 3
I 3
.include <bsd.prog.mk>
E 3
E 1
