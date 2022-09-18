h16018
s 00002/00000/00006
d D 5.4 91/03/08 14:38:32 bostic 4 3
c use the dbm library
e
s 00004/00046/00002
d D 5.3 90/05/11 16:04:28 bostic 3 2
c first pass for new make
e
s 00001/00001/00047
d D 5.2 89/05/11 13:57:09 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00048/00000/00000
d D 5.1 88/10/19 11:50:43 bostic 1 0
c date and time created 88/10/19 11:50:43 by bostic
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
SRCS=	mkpasswd.c
OBJS=
MAN=	mkpasswd.0
E 3
I 3
PROG=	mkpasswd
MAN8=	mkpasswd.0
I 4
DPADD=	${LIBDBM}
LDADD=	-ldbm
E 4
E 3

D 3
all: mkpasswd

mkpasswd: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c

clean:
	rm -f ${OBJS} core mkpasswd

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 2
	install -s -o bin -g bin -m 755 mkpasswd ${DESTDIR}/etc
E 2
I 2
	install -s -o bin -g bin -m 755 mkpasswd ${DESTDIR}/usr/sbin
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
