h59752
s 00000/00017/00030
d D 5.4 91/05/13 18:05:14 bostic 4 3
c new copyright; att/bsd/shared
e
s 00001/00001/00046
d D 5.3 89/05/10 22:25:31 bostic 3 2
c file reorg, pathnames.h, paths.h
e
s 00039/00012/00008
d D 5.2 88/10/25 16:10:29 bostic 2 1
c it's a program now
e
s 00020/00000/00000
d D 5.1 88/10/21 15:45:51 bostic 1 0
c date and time created 88/10/21 15:45:51 by bostic
e
u
U
t
T
I 1
D 4
#
D 2
# Copyright (c) 1988 Regents of the University of California.
E 2
I 2
# Copyright (c) 1988 The Regents of the University of California.
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
# WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
#
E 4
D 2
# %W% (Berkeley) %G%
E 2
I 2
#	%W% (Berkeley) %G%
E 2
D 4
#
E 4

D 2
all fp clean cleandir depend install lint tags:
E 2
I 2
CFLAGS=	-O
LIBC=	/lib/libc.a
SRCS=	fp.c
OBJS=
MAN=

all: fp

fp: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c

clean:
	rm -f ${OBJS} core fp

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install:
D 3
	install -s -o bin -g bin -m 755 fp ${DESTDIR}/usr/ucb
E 3
I 3
	install -s -o bin -g bin -m 755 fp ${DESTDIR}/usr/bin
E 3

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 2
E 1
