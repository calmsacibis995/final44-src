h54998
s 00000/00000/00007
d D 8.1 93/06/06 14:41:12 bostic 10 9
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00006
d D 5.8 92/06/29 18:54:32 bostic 9 8
c put keywords back in
e
s 00001/00001/00006
d D 5.7 92/06/29 18:54:17 bostic 8 7
c don't need util.c
e
s 00003/00001/00004
d D 5.6 92/06/19 16:52:00 mccanne 7 6
c port to 4.4
e
s 00000/00001/00005
d D 5.5 91/04/27 16:18:55 bostic 6 5
c doesn't need user.h anymore
e
s 00001/00000/00005
d D 5.4 91/04/27 16:12:37 bostic 5 3
c gcore needs -I/sys 
e
s 00001/00000/00005
d R 5.4 91/01/15 14:04:20 bostic 4 3
c kernel reorg
e
s 00003/00046/00002
d D 5.3 90/05/11 13:50:20 bostic 3 2
c first pass for new make
e
s 00001/00001/00047
d D 5.2 89/05/10 22:26:27 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00048/00000/00000
d D 5.1 88/10/21 13:40:25 bostic 1 0
c date and time created 88/10/21 13:40:25 by bostic
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
D 7
#	%W% (Berkeley) %G%
E 7
I 7
D 9
#	@(#)Makefile	5.5 (Berkeley) 4/27/91
E 9
I 9
#	%W% (Berkeley) %G%
E 9
E 7
E 3

D 3
CFLAGS=	-O
LIBC=	/lib/libc.a
SRCS=	gcore.c
OBJS=
MAN=	gcore.0
E 3
I 3
PROG=	gcore
I 7
D 8
SRCS=	gcore.c md-${MACHINE}.c util.c
E 8
I 8
SRCS=	gcore.c md-${MACHINE}.c
E 8
LDADD=	-lkvm
E 7
I 5
D 6
CFLAGS+=-I/sys
E 6
E 5
E 3

D 3
all: gcore

gcore: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c

clean:
	rm -f ${OBJS} core gcore

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 2
	install -s -o bin -g kmem -m 2755 gcore ${DESTDIR}/usr/ucb
E 2
I 2
	install -s -o bin -g kmem -m 2755 gcore ${DESTDIR}/usr/bin
E 2
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 3
I 3
.include <bsd.prog.mk>
E 3
E 1
