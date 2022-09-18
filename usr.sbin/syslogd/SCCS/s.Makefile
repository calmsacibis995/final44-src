h61122
s 00000/00000/00009
d D 8.1 93/06/06 14:08:38 bostic 9 8
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00001/00009
d D 5.8 93/04/27 18:11:35 bostic 8 7
c daemon(3) now in the C library
e
s 00001/00000/00009
d D 5.7 90/09/30 20:41:25 bostic 7 6
c add syslog.conf.5
e
s 00001/00000/00008
d D 5.6 90/06/29 20:14:32 karels 6 5
c use daemon() call
e
s 00001/00000/00007
d D 5.5 90/06/25 18:11:02 bostic 5 4
c don't use a symlink, just set .PATH
e
s 00004/00045/00003
d D 5.4 90/05/11 16:08:07 bostic 4 3
c first pass for new make
e
s 00005/00005/00043
d D 5.3 89/11/13 18:40:21 bostic 3 2
c add ttymsg.c
e
s 00001/00001/00047
d D 5.2 89/05/11 14:13:35 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00048/00000/00000
d D 5.1 88/09/27 22:27:03 bostic 1 0
c date and time created 88/09/27 22:27:03 by bostic
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
E 4
I 4
PROG=	syslogd
E 4
D 3
SRCS=	syslogd.c
OBJS=
E 3
I 3
SRCS=	syslogd.c ttymsg.c
I 5
.PATH:	${.CURDIR}/../../usr.bin/wall
I 7
MAN5=	syslog.conf.0
E 7
E 5
D 4
OBJS=	syslogd.o ttymsg.o
E 3
MAN=	syslogd.0
E 4
I 4
MAN8=	syslogd.0
I 6
D 8
LDADD=	-lutil
E 8
E 6
E 4

D 4
all: syslogd

D 3
syslogd: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c
E 3
I 3
syslogd: ${LIBC} ${OBJS}
	${CC} -o $@ ${CFLAGS} ${OBJS}
E 3

clean:
	rm -f ${OBJS} core syslogd

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
D 3
	mkdep -p ${CFLAGS} ${SRCS}
E 3
I 3
	mkdep ${CFLAGS} ${SRCS}
E 3

install: ${MAN}
D 2
	install -s -o bin -g bin -m 755 syslogd ${DESTDIR}/etc/syslogd
E 2
I 2
	install -s -o bin -g bin -m 755 syslogd ${DESTDIR}/usr/sbin
E 2
	install -c -o bin -g bin -m 444 syslogd.0 ${DESTDIR}/usr/man/cat8

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 4
I 4
.include <bsd.prog.mk>
E 4
E 1
