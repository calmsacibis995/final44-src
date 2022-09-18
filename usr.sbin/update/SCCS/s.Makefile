h35658
s 00000/00000/00006
d D 8.1 93/06/06 14:12:04 bostic 7 6
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00001/00006
d D 5.6 93/04/27 18:11:12 bostic 6 5
c daemon(3) now in the C library
e
s 00001/00000/00006
d D 5.5 90/06/29 19:09:31 karels 5 4
c use daemon() call
e
s 00004/00046/00002
d D 5.4 90/05/11 16:40:30 bostic 4 3
c first pass for new make
e
s 00001/00001/00047
d D 5.3 89/08/29 18:05:37 sklower 3 2
c move to /usr/sbin
e
s 00001/00001/00047
d D 5.2 89/05/11 14:34:20 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00048/00000/00000
d D 5.1 88/10/19 13:06:38 bostic 1 0
c date and time created 88/10/19 13:06:38 by bostic
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
SRCS=	update.c
OBJS=
MAN=	update.0
E 4
I 4
PROG=	update
MAN8=	update.0
I 5
D 6
LDADD=	-lutil
E 6
E 5
E 4

D 4
all: update

update: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c

clean:
	rm -f ${OBJS} core update

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 2
	install -s -o bin -g bin -m 755 update ${DESTDIR}/etc
E 2
I 2
D 3
	install -s -o bin -g bin -m 755 update ${DESTDIR}/usr/libexec
E 3
I 3
	install -s -o bin -g bin -m 755 update ${DESTDIR}/usr/sbin
E 3
E 2
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat8

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 4
I 4
.include <bsd.prog.mk>
E 4
E 1
