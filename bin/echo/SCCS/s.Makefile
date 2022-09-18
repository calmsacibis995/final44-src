h18540
s 00000/00000/00005
d D 8.1 93/05/31 15:02:30 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00003/00046/00002
d D 5.4 90/05/11 12:42:04 bostic 4 3
c first pass for new make
e
s 00001/00001/00047
d D 5.3 89/06/22 10:18:47 bostic 3 2
c /usr/bin -> /bin
e
s 00001/00001/00047
d D 5.2 89/05/11 10:03:00 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00048/00000/00000
d D 5.1 88/10/18 21:26:49 bostic 1 0
c date and time created 88/10/18 21:26:49 by bostic
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
SRCS=	echo.c
OBJS=
MAN=	echo.0
E 4
I 4
PROG=	echo
E 4

D 4
all: echo

echo: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c

clean:
	rm -f ${OBJS} core echo

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 2
	install -s -o bin -g bin -m 755 echo ${DESTDIR}/bin
E 2
I 2
D 3
	install -s -o bin -g bin -m 755 echo ${DESTDIR}/usr/bin
E 3
I 3
	install -s -o bin -g bin -m 755 echo ${DESTDIR}/bin
E 3
E 2
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 4
I 4
.include <bsd.prog.mk>
E 4
E 1
