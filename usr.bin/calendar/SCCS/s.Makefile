h38223
s 00000/00000/00009
d D 8.1 93/06/06 14:26:22 bostic 11 10
c 4.4BSD snapshot (revision 8.1)
e
s 00005/00045/00004
d D 4.8 90/05/11 15:21:55 bostic 10 9
c first pass for new make
e
s 00002/00002/00047
d D 4.7 89/11/27 14:59:36 bostic 9 8
c install everything in calendars
e
s 00003/00002/00046
d D 4.6 89/10/13 14:23:13 bostic 8 7
c only one calendar program now, add new include files
e
s 00001/00001/00047
d D 4.5 89/05/11 09:58:13 bostic 7 6
c file reorg, pathnames.h, paths.h
e
s 00028/00021/00020
d D 4.4 88/10/22 16:41:20 bostic 6 5
c cleanup, add manual page
e
s 00035/00010/00006
d D 4.3 87/06/19 06:11:08 bostic 5 2
c new template
e
s 00035/00010/00006
d R 4.3 87/06/18 15:01:40 bostic 4 2
c new template
e
s 00035/00010/00006
d R 4.3 87/06/18 14:57:25 bostic 3 2
c new template
e
s 00002/00000/00014
d D 4.2 87/05/31 21:27:23 bostic 2 1
c added depend label
e
s 00014/00000/00000
d D 4.1 83/08/13 16:10:00 sam 1 0
c date and time created 83/08/13 16:10:00 by sam
e
u
U
t
T
I 1
D 5
#	%M%	%I%	%E%
E 5
D 10
#
D 5
DESTDIR=
E 5
I 5
D 6
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 6
I 6
# Copyright (c) 1988 The Regents of the University of California.
# All rights reserved.
E 6
#
D 6
#	%W%	(Berkeley)	%G%
E 6
I 6
# Redistribution and use in source and binary forms are permitted
# provided that the above copyright notice and this paragraph are
# duplicated in all such forms and that any documentation,
# advertising materials, and other materials related to such
# distribution and use acknowledge that the software was developed
# by the University of California, Berkeley.  The name of the
# University may not be used to endorse or promote products derived
# from this software without specific prior written permission.
# THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
# WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 6
#
E 10
I 6
#	%W% (Berkeley) %G%
D 10
#
E 6
E 5
CFLAGS=	-O
I 5
LIBC=	/lib/libc.a
SRCS=	calendar.c
D 6
OBJS=	calendar.o
E 6
I 6
OBJS=
MAN=	calendar.0
E 10
I 8
D 9
CALS=	calendar.history calendar.holiday calendar.birthday calendar.usholiday
E 9
E 8
E 6
E 5

D 5
calendar: calendar.c
	${CC} ${CFLAGS} -o calendar calendar.c
E 5
I 5
D 10
all: calendar
E 10
I 10
PROG=	calendar
E 10
E 5

D 5
install:
	install -s calendar $(DESTDIR)/usr/lib
	install -c -m 755 calendar.sh $(DESTDIR)/usr/bin/calendar
E 5
I 5
D 6
calendar: calendar.c ${LIBC}
	${CC} ${CFLAGS} -o $@ calendar.c
E 6
I 6
D 10
calendar: ${LIBC}
	${CC} ${CFLAGS} -o $@ $@.c
E 10
I 10
beforeinstall:
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 \
	    ${.CURDIR}/calendars/calendar.* ${DESTDIR}/usr/share/calendar
E 10
E 6
E 5

D 5
clean:
	rm -f calendar
E 5
I 5
D 6
clean: FRC
E 6
I 6
D 10
clean:
E 6
	rm -f ${OBJS} core calendar
E 5
I 2

D 5
depend:
E 5
I 5
D 6
depend: FRC
E 6
I 6
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 6
	mkdep -p ${CFLAGS} ${SRCS}

D 6
install: FRC
E 6
I 6
install: ${MAN}
E 6
D 7
	install -s -o bin -g bin -m 755 calendar ${DESTDIR}/usr/lib
E 7
I 7
D 8
	install -s -o bin -g bin -m 755 calendar ${DESTDIR}/usr/libexec
E 7
	install -c -o bin -g bin -m 755 calendar.sh ${DESTDIR}/usr/bin/calendar
E 8
I 8
	install -s -o bin -g bin -m 755 calendar ${DESTDIR}/usr/bin
E 8
I 6
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
I 8
D 9
	install -c -o bin -g bin -m 444 ${CALS} ${DESTDIR}/usr/share/calendar
E 9
I 9
	install -c -o bin -g bin -m 444 calendars/calendar.* \
		${DESTDIR}/usr/share/calendar
E 9
E 8
E 6

D 6
lint: FRC
E 6
I 6
lint: ${SRCS}
E 6
	lint ${CFLAGS} ${SRCS}

D 6
tags: FRC
E 6
I 6
tags: ${SRCS}
E 6
	ctags ${SRCS}
E 10
I 10
.include <bsd.prog.mk>
E 10
D 6

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

calendar.o: calendar.c /usr/include/sys/time.h /usr/include/time.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 6
E 5
E 2
E 1
