h32384
s 00000/00000/00007
d D 8.1 93/06/05 11:21:49 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00005/00048/00002
d D 5.4 90/05/11 13:04:26 bostic 4 3
c first pass for new make
e
s 00001/00001/00049
d D 5.3 89/04/21 10:07:00 bostic 3 2
c file system reorganization, pathnames.h
e
s 00002/00000/00048
d D 5.2 88/11/23 11:50:13 bostic 2 1
c make "man slip" work
e
s 00048/00000/00000
d D 5.1 88/09/27 22:26:33 bostic 1 0
c date and time created 88/09/27 22:26:33 by bostic
e
u
U
t
T
I 1
D 4
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
E 4
I 4
#	%W% (Berkeley) %G%
E 4

D 4
CFLAGS=	-O
LIBC=	/lib/libc.a
SRCS=	slattach.c
OBJS=
MAN=	slattach.0
E 4
I 4
PROG=	slattach
MAN8=	slattach.0
MLINKS=	slattach.8 slip.8
E 4

D 4
all: slattach

slattach: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c

clean:
	rm -f ${OBJS} core slattach

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 3
	install -s -o bin -g bin -m 755 slattach ${DESTDIR}/etc/slattach
E 3
I 3
	install -s -o bin -g bin -m 755 slattach ${DESTDIR}/sbin
E 3
	install -c -o bin -g bin -m 444 slattach.0 ${DESTDIR}/usr/man/cat8
I 2
	rm -f ${DESTDIR}/usr/man/cat8/slip.0
	ln ${DESTDIR}/usr/man/cat8/slattach.0 ${DESTDIR}/usr/man/cat8/slip.0
E 2

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 4
I 4
.include <bsd.prog.mk>
E 4
E 1
