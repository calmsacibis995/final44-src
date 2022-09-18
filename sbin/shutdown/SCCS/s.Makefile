h21457
s 00000/00000/00009
d D 8.1 93/06/05 11:21:11 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00007/00045/00002
d D 5.3 90/05/11 13:04:30 bostic 3 2
c first pass for new make
e
s 00001/00001/00046
d D 5.2 89/05/11 13:56:23 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00047/00000/00000
d D 5.1 88/09/18 16:51:20 bostic 1 0
c date and time created 88/09/18 16:51:20 by bostic
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
SRCS=	shutdown.c
MAN=	shutdown.0
E 3
I 3
PROG=	shutdown
MAN8=	shutdown.0
BINOWN=	root
BINGRP=	operator
BINMODE=4550
E 3

D 3
all: shutdown

shutdown: ${SRCS} ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c

clean:
	rm -f ${OBJS} core shutdown

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 2
	install -s -o root -g operator -m 4750 shutdown ${DESTDIR}/etc/shutdown
E 2
I 2
	install -s -o root -g operator -m 4750 shutdown ${DESTDIR}/sbin
E 2
	install -c -o bin -g bin -m 444 shutdown.0 ${DESTDIR}/usr/man/cat8/shutdown.0

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 3
I 3
.include <bsd.prog.mk>
E 3
E 1
