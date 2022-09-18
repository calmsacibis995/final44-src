h41262
s 00000/00000/00010
d D 8.1 93/06/04 18:50:46 bostic 17 16
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00009
d D 5.13 93/05/27 16:08:06 elan 16 15
c deleted getttytab.c; turn off debugging
e
s 00001/00001/00009
d D 5.12 91/01/21 09:44:31 bostic 15 14
c delete get_date, just use strftime
e
s 00000/00004/00010
d D 5.11 90/07/02 16:26:13 bostic 14 13
c don't install gettytab from here
e
s 00001/00000/00013
d D 5.10 90/06/30 11:07:30 bostic 13 12
c needs dependency for libutil
e
s 00001/00001/00012
d D 5.9 90/06/29 16:03:01 marc 12 11
c sett system defaults
e
s 00001/00000/00012
d D 5.8 90/06/28 23:28:05 marc 11 10
c needs libutil
e
s 00008/00046/00004
d D 5.7 90/05/11 12:55:44 bostic 10 9
c first pass for new make
e
s 00003/00002/00047
d D 5.6 90/03/22 21:25:38 bostic 9 8
c checkpoint before pmake
e
s 00004/00003/00045
d D 5.5 89/05/11 14:32:59 bostic 8 7
c file reorg, pathnames.h, paths.h
e
s 00026/00030/00022
d D 5.4 88/10/25 19:01:01 bostic 7 6
c add man page, cleanup
e
s 00039/00015/00013
d D 5.3 87/06/02 21:49:26 bostic 6 4
c new template
e
s 00039/00015/00013
d R 5.3 87/06/02 20:23:04 bostic 5 4
c new template
e
s 00002/00000/00026
d D 5.2 87/05/31 20:39:21 bostic 4 3
c added depend label
e
s 00006/00001/00020
d D 5.1 85/04/29 12:04:52 dist 3 2
c Add copyright
e
s 00002/00001/00019
d D 4.2 85/02/05 08:45:48 ralph 2 1
c added get_date() for putting date in login banner (%d).
e
s 00020/00000/00000
d D 4.1 83/07/06 00:11:14 sam 1 0
c date and time created 83/07/06 00:11:14 by sam
e
u
U
t
T
I 1
D 3
#	%M%	%I%	%E%
E 3
I 3
D 10
#
D 6
# Copyright (c) 1980 Regents of the University of California.
E 6
I 6
D 7
# Copyright (c) 1987 Regents of the University of California.
E 6
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 7
I 7
# Copyright (c) 1987 The Regents of the University of California.
# All rights reserved.
E 7
#
D 6
#	%W% (Berkeley) %G%
E 6
I 6
D 7
#	%W%	(Berkeley)	%G%
E 7
I 7
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
E 7
E 6
E 3
#
E 10
I 7
#	%W% (Berkeley) %G%
D 10
#
E 7
D 6
DESTDIR=
E 6
CFLAGS=	-O
I 6
LIBC=	/lib/libc.a
E 10
I 10

PROG=	getty
E 10
D 12
SRCS=	main.c init.c subr.c gettytab.c get_date.c
E 12
I 12
D 15
SRCS=	main.c init.c subr.c gettytab.c get_date.c ttydefaults.c
E 15
I 15
D 16
SRCS=	main.c init.c subr.c gettytab.c ttydefaults.c
E 16
I 16
SRCS=	main.c init.c subr.c ttydefaults.c
E 16
E 15
I 13
DPADD=	${LIBUTIL}
E 13
E 12
I 11
LDADD=	-lutil
E 11
E 6
D 2
OBJS=	main.o init.o subr.o gettytab.o
E 2
I 2
D 10
OBJS=	main.o init.o subr.o gettytab.o get_date.o
I 7
D 8
MAN=	getty.0
E 8
I 8
D 9
MAN=	getty.0 gettytab.0
E 9
I 9
MAN=	getty.0 gettytab.0 ttys.0
E 10
I 10
MAN5=	gettytab.0 ttys.0
MAN8=	getty.0
E 10
E 9
E 8
E 7
E 2

D 6
all:	getty
E 6
I 6
D 10
all: getty
E 10
I 10
D 14
beforeinstall:
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${.CURDIR}/gettytab \
	    ${DESTDIR}/etc/gettytab
E 10
E 6

E 14
D 6
getty:	${OBJS}
	${CC} -o getty ${OBJS}
E 6
I 6
D 7
getty:	${OBJS} ${LIBC}
E 7
I 7
D 10
getty: ${OBJS} ${LIBC}
E 7
	${CC} -o $@ ${CFLAGS} ${OBJS}
E 6

D 6
install: all
	install -s getty ${DESTDIR}/etc/getty
I 2
	install -c -m 444 gettytab ${DESTDIR}/etc/gettytab
E 6
I 6
D 7
clean: FRC
E 7
I 7
clean:
E 7
	rm -f ${OBJS} core getty
E 6
E 2

D 6
clean:
	rm -f getty ${OBJS} a.out core errs
E 6
I 6
D 7
depend: FRC
E 7
I 7
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 7
	mkdep ${CFLAGS} ${SRCS}
E 6

I 4
D 6
depend:
E 6
I 6
D 7
install: FRC
E 7
I 7
install: ${MAN}
E 7
D 8
	install -s -o bin -g bin -m 755 getty ${DESTDIR}/etc/getty
E 8
I 8
	install -s -o bin -g bin -m 755 getty ${DESTDIR}/usr/libexec
E 8
	install -c -o bin -g bin -m 444 gettytab ${DESTDIR}/etc/gettytab
I 7
D 8
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat8
E 8
I 8
D 9
	install -c -o bin -g bin -m 444 gettytab.0 ${DESTDIR}/usr/man/cat5
E 9
I 9
	install -c -o bin -g bin -m 444 gettytab.0 ttys.0 \
	    ${DESTDIR}/usr/man/cat5
E 9
	install -c -o bin -g bin -m 444 getty.0 ${DESTDIR}/usr/man/cat8
E 8
E 7
E 6

E 4
D 6
main.o: gettytab.h
init.o: gettytab.h
subr.o: gettytab.h
E 6
I 6
D 7
lint: FRC
E 7
I 7
lint: ${SRCS}
E 7
	lint ${CFLAGS} ${SRCS}

D 7
tags: FRC
E 7
I 7
tags: ${SRCS}
E 7
	ctags ${SRCS}
E 10
I 10
.include <bsd.prog.mk>
E 10
D 7

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

main.o: main.c /usr/include/sgtty.h /usr/include/sys/ioctl.h
main.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
main.o: /usr/include/signal.h /usr/include/ctype.h /usr/include/setjmp.h
main.o: /usr/include/syslog.h /usr/include/sys/file.h gettytab.h
init.o: init.c /usr/include/sgtty.h /usr/include/sys/ioctl.h
init.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h gettytab.h
subr.o: subr.c /usr/include/sgtty.h /usr/include/sys/ioctl.h
subr.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h gettytab.h
subr.o: /usr/include/sys/time.h /usr/include/time.h
gettytab.o: gettytab.c /usr/include/ctype.h
get_date.o: get_date.c /usr/include/stdio.h /usr/include/sys/time.h
get_date.o: /usr/include/time.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 7
E 6
E 1
