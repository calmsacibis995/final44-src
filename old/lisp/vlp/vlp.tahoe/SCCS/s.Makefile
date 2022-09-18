h59556
s 00001/00018/00029
d D 5.3 91/07/01 14:41:06 bostic 3 2
c makefiles don't need copyrights
e
s 00001/00001/00046
d D 5.2 89/05/10 22:32:21 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00047/00000/00000
d D 5.1 88/10/25 16:04:38 bostic 1 0
c date and time created 88/10/25 16:04:38 by bostic
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

CFLAGS=	-O
LIBC=	/lib/libc.a
SRCS=	vlp.c
OBJS=
MAN=

all: vlp

vlp: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c

clean:
	rm -f ${OBJS} core vlp

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install:
D 2
	install -s -o bin -g bin -m 755 vlp ${DESTDIR}/usr/ucb
E 2
I 2
	install -s -o bin -g bin -m 755 vlp ${DESTDIR}/usr/bin
E 2

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 1
