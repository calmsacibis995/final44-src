h17165
s 00000/00000/00006
d D 8.1 93/06/06 14:23:02 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00004/00048/00002
d D 5.2 90/05/11 14:32:37 bostic 2 1
c first pass for new make
e
s 00050/00000/00000
d D 5.1 88/09/26 15:06:04 bostic 1 0
c date and time created 88/09/26 15:06:04 by bostic
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
SRCS=	basename.c dirname.c
OBJS=
MAN=	basename.0
E 2
I 2
PROG=	basename
MLINKS=	basename.1 dirname.1
E 2

D 2
all: basename dirname

basename dirname: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c

clean:
	rm -f ${OBJS} core basename dirname

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
	install -s -o bin -g bin -m 755 basename dirname ${DESTDIR}/usr/bin
	install -c -o bin -g bin -m 444 basename.0 ${DESTDIR}/usr/man/cat1
	rm -f ${DESTDIR}/usr/man/cat1/dirname.0
	ln ${DESTDIR}/usr/man/cat1/basename.0 ${DESTDIR}/usr/man/cat1/dirname.0

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 2
I 2
.include <bsd.prog.mk>
E 2
E 1
