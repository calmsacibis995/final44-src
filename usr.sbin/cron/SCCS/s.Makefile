h49267
s 00000/00000/00007
d D 8.1 93/06/06 13:55:48 bostic 9 8
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00001/00007
d D 5.8 93/04/27 18:07:59 bostic 8 7
c daemon(3) now in the C library
e
s 00002/00001/00006
d D 5.7 92/07/25 10:55:04 bostic 7 6
c crontab goes in section 5
e
s 00001/00002/00006
d D 5.6 91/05/10 13:26:58 cael 6 5
c add crontab.5/delete link
e
s 00001/00000/00007
d D 5.5 90/06/29 21:05:01 karels 5 4
c use daemon() call
e
s 00004/00047/00003
d D 5.4 90/05/11 16:40:49 bostic 4 3
c first pass for new make
e
s 00001/00001/00049
d D 5.3 89/05/11 14:06:54 bostic 3 2
c file reorg, pathnames.h, paths.h
e
s 00013/00011/00037
d D 5.2 89/03/26 21:18:30 bostic 2 1
c clean up copyright, link man page to crontab(5)
e
s 00048/00000/00000
d D 5.1 88/10/19 10:40:17 bostic 1 0
c date and time created 88/10/19 10:40:17 by bostic
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
# Copyright (c) 1989 The Regents of the University of California.
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
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
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

D 4
CFLAGS=	-O
LIBC=	/lib/libc.a
SRCS=	cron.c
OBJS=
MAN=	cron.0
E 4
I 4
PROG=	cron
I 5
D 8
LDADD=	-lutil
E 8
E 5
D 6
MAN8=	cron.0
MLINKS=	cron.8 crontab.5
E 6
I 6
D 7
MAN8=	cron.0 crontab.0
E 7
I 7
MAN8=	cron.0
MAN5=	crontab.0
E 7
E 6
E 4

D 4
all: cron

cron: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c

clean:
	rm -f ${OBJS} core cron

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 3
	install -s -o bin -g bin -m 755 cron ${DESTDIR}/etc
E 3
I 3
	install -s -o bin -g bin -m 755 cron ${DESTDIR}/usr/sbin
E 3
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat8
I 2
	rm -f ${DESTDIR}/usr/man/cat5/crontab.0
	ln ${DESTDIR}/usr/man/cat8/cron.0 ${DESTDIR}/usr/man/cat5/crontab.0
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
