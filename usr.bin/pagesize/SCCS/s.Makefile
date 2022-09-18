h40029
s 00013/00001/00004
d D 8.2 94/04/03 11:31:10 bostic 5 4
c redo pagesize as a shell script
e
s 00000/00000/00005
d D 8.1 93/06/06 15:49:00 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00003/00046/00002
d D 5.3 90/05/11 14:26:30 bostic 3 2
c first pass for new make
e
s 00001/00001/00047
d D 5.2 89/05/11 10:02:46 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00048/00000/00000
d D 5.1 88/10/18 22:01:52 bostic 1 0
c date and time created 88/10/18 22:01:52 by bostic
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
SRCS=	pagesize.c
OBJS=
MAN=	pagesize.0
E 3
I 3
D 5
PROG=	pagesize
E 5
I 5
MAN1=	pagesize.0
E 5
E 3

I 5
all pagesize: ${MAN1}

clean depend lint tags:

cleandir:
	rm -f ${MAN1}

install: maninstall
	install -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${.CURDIR}/pagesize.sh ${DESTDIR}/${BINDIR}/pagesize

E 5
D 3
all: pagesize

pagesize: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c

clean:
	rm -f ${OBJS} core pagesize

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 2
	install -s -o bin -g bin -m 755 pagesize ${DESTDIR}/bin
E 2
I 2
	install -s -o bin -g bin -m 755 pagesize ${DESTDIR}/usr/bin
E 2
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 3
I 3
.include <bsd.prog.mk>
I 5
.include <bsd.man.mk>
E 5
E 3
E 1
