h14735
s 00002/00001/00006
d D 5.4 90/06/19 18:23:33 bostic 4 3
c install in section 5 as "tar", too
e
s 00004/00045/00003
d D 5.3 90/05/11 12:40:07 bostic 3 2
c first pass for new make
e
s 00014/00014/00034
d D 5.2 89/05/08 12:59:19 bostic 2 1
c file system reorg and pathnames.h
e
s 00048/00000/00000
d D 5.1 88/10/18 22:21:08 bostic 1 0
c date and time created 88/10/18 22:21:08 by bostic
e
u
U
t
T
I 1
D 3
#
D 2
# Copyright (c) 1988 Regents of the University of California.
E 2
I 2
# Copyright (c) 1989 The Regents of the University of California.
E 2
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
# provided that the above copyright notice and this paragraph are
D 2
# duplicated in all such forms and that any documentation, advertising
# materials, and other materials related to such redistribution and
# use acknowledge that the software was developed by the University
# of California, Berkeley.  The name of the University may not be
# used to endorse or promote products derived from this software
# without specific prior written permission.  THIS SOFTWARE IS PROVIDED
# ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
# WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND
# FITNESS FOR A PARTICULAR PURPOSE.
E 2
I 2
# duplicated in all such forms and that any documentation,
# advertising materials, and other materials related to such
# distribution and use acknowledge that the software was developed
# by the University of California, Berkeley.  The name of the
# University may not be used to endorse or promote products derived
# from this software without specific prior written permission.
# THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
#
E 3
D 2
# %W% (Berkeley) %G%
E 2
I 2
#	%W% (Berkeley) %G%
E 2
D 3
#
D 2

E 2
CFLAGS=	-O
LIBC=	/lib/libc.a
SRCS=	tar.c
OBJS=
D 2
MAN=	tar.0
E 2
I 2
MAN=	tar.0 tar5.0
E 3
E 2

D 3
all: tar
E 3
I 3
PROG=	tar
MAN1=	tar.0
D 4
MAN5=	tar.format.0
E 4
I 4
MAN5=	tarformat.0
MLINKS=	tarformat.5 tar.5
E 4
E 3

D 3
tar: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c

clean:
	rm -f ${OBJS} core tar

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
	install -s -o bin -g bin -m 755 tar ${DESTDIR}/bin
D 2
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
E 2
I 2
	install -c -o bin -g bin -m 444 tar.0 ${DESTDIR}/usr/man/cat1
	install -c -o bin -g bin -m 444 tar5.0 ${DESTDIR}/usr/man/cat5/tar.0
E 2

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 3
I 3
.include <bsd.prog.mk>
E 3
E 1
