h39477
s 00000/00000/00008
d D 8.1 93/06/06 14:05:07 bostic 5 3
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00000/00008
d R 5.4 91/01/14 18:01:13 bostic 4 3
c kernel reorg
e
s 00006/00048/00002
d D 5.3 90/05/11 16:04:43 bostic 3 2
c first pass for new make
e
s 00003/00003/00047
d D 5.2 89/05/11 14:31:30 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00048/00000/00000
d D 5.1 88/10/19 12:09:08 bostic 1 0
c date and time created 88/10/19 12:09:08 by bostic
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
SRCS=	quotaon.c
OBJS=
MAN=	quotaon.0
E 3
I 3
PROG=	quotaon
MAN8=	quotaon.0
MLINKS=	quotaon.8 quotaoff.8
LINKS=	${BINDIR}/quotaon ${BINDIR}/quotaoff
E 3

D 3
all: quotaon

quotaon: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c

clean:
	rm -f ${OBJS} core quotaon

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 2
	install -s -o bin -g bin -m 755 quotaon ${DESTDIR}/etc
	rm -f ${DESTDIR}/etc/quotaoff
	ln ${DESTDIR}/etc/quotaon ${DESTDIR}/etc/quotaoff
E 2
I 2
	install -s -o bin -g bin -m 755 quotaon ${DESTDIR}/usr/sbin
	rm -f ${DESTDIR}/usr/sbin/quotaoff
	ln ${DESTDIR}/usr/sbin/quotaon ${DESTDIR}/usr/sbin/quotaoff
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