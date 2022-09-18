h26739
s 00000/00000/00007
d R 8.2 93/05/31 15:02:48 bostic 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00000/00007
d D 8.1 93/05/31 15:02:44 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00006
d D 5.4 90/06/24 17:05:08 bostic 4 3
c clean y.tab.h
e
s 00004/00045/00003
d D 5.3 90/05/11 12:42:01 bostic 3 2
c first pass for new make
e
s 00001/00001/00047
d D 5.2 89/05/11 10:42:01 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00048/00000/00000
d D 5.1 88/10/18 21:33:40 bostic 1 0
c date and time created 88/10/18 21:33:40 by bostic
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
E 3
I 3
PROG=	expr
E 3
SRCS=	expr.c
D 3
OBJS=	expr.o
MAN=	expr.0
E 3
I 3
D 4
CLEANFILES=	expr.c
E 4
I 4
CLEANFILES=	expr.c y.tab.h
E 4
E 3

D 3
all: expr

expr: ${OBJS} ${LIBC}
	${CC} -o $@ ${CFLAGS} ${OBJS}

clean:
	rm -f ${OBJS} expr.c core expr

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 2
	install -s -o bin -g bin -m 755 expr ${DESTDIR}/bin
E 2
I 2
	install -s -o bin -g bin -m 755 expr ${DESTDIR}/usr/bin
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
