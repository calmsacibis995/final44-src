h45192
s 00000/00000/00021
d D 8.1 93/06/09 22:57:25 bostic 16 15
c 4.4BSD snapshot (revision 8.1)
e
s 00003/00003/00018
d D 5.12 93/06/09 22:57:21 bostic 15 13
c install from the obj directory, not from (read-only) /usr/src
e
s 00000/00000/00021
d R 8.1 93/06/06 22:20:18 bostic 14 13
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00002/00021
d D 5.11 92/09/09 13:50:03 elan 13 12
c deleted unecessary line.
e
s 00006/00000/00017
d D 5.10 92/09/09 13:49:18 elan 12 11
c Added cap_mkdb.
e
s 00001/00001/00016
d D 5.9 92/09/01 12:11:32 elan 11 10
c vgrindefs.c is gone.
e
s 00012/00058/00005
d D 5.8 90/06/05 11:03:23 bostic 10 9
c pmake style makefile
e
s 00001/00001/00062
d D 5.7 90/05/11 13:49:04 bostic 9 8
c first pass for new make
e
s 00001/00001/00062
d D 5.6 89/05/10 22:33:05 bostic 8 7
c file reorg, pathnames.h, paths.h
e
s 00009/00006/00054
d D 5.5 89/05/01 08:39:31 bostic 7 6
c file system reorganization; pathnames.h
e
s 00025/00020/00035
d D 5.4 88/10/25 18:29:59 bostic 6 5
c add man page, cleanup
e
s 00044/00022/00011
d D 5.3 87/12/01 20:35:16 bostic 5 3
c new template
e
s 00044/00022/00011
d R 5.3 87/06/16 19:08:14 bostic 4 3
c new template
e
s 00002/00000/00031
d D 5.2 87/05/31 21:15:38 bostic 3 2
c added depend label
e
s 00006/00001/00025
d D 5.1 85/06/06 09:27:48 dist 2 1
c Add copyright
e
s 00026/00000/00000
d D 4.1 82/10/19 00:52:09 mckusick 1 0
c date and time created 82/10/19 00:52:09 by mckusick
e
u
U
t
T
I 1
D 2
#	%W%	(Berkeley)	%G%
E 2
I 2
D 10
#
D 5
# Copyright (c) 1980 Regents of the University of California.
E 5
I 5
D 6
# Copyright (c) 1987 Regents of the University of California.
E 5
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 6
I 6
# Copyright (c) 1987 The Regents of the University of California.
# All rights reserved.
E 6
#
D 5
#	%W% (Berkeley) %G%
E 5
I 5
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
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 6
E 5
E 2
#
E 10
I 6
#	%W% (Berkeley) %G%
D 10
#
E 6
D 5
DESTDIR=
CFLAGS=-O 
SOURCES=vfontedpr.c vgrindefs.c regexp.c retest.c
CMDS=vfontedpr retest
OBJS=retest.o regexp.o vfontedpr.o vgrindefs.o
E 5
I 5
CFLAGS=	-O
D 9
LIBC=	/lib/libc.a
E 9
I 9
LIBC=	/usr/lib/libc.a
E 9
RSRCS=	retest.c regexp.c
ROBJS=	retest.o regexp.o
VSRCS=	regexp.c vfontedpr.c vgrindefs.c
VOBJS=	regexp.o vfontedpr.o vgrindefs.o
I 6
D 7
MAN=	vgrind.0
E 7
I 7
MAN=	vgrind.0 vgrindefs.0
E 10
E 7
E 6
E 5

D 5
all:	$(CMDS) ${OBJS}
E 5
I 5
D 10
all: retest vfontedpr
E 10
I 10
PROG=	vfontedpr
D 11
SRCS=	regexp.c vfontedpr.c vgrindefs.c
E 11
I 11
SRCS=	regexp.c vfontedpr.c
E 11
MAN1=	vgrind.0
MAN5=	vgrindefs.0
BINDIR=	/usr/libexec
I 12
D 15
CLEANFILES+= vgrindefs.src.db
E 15
I 15
CLEANFILES+=vgrindefs.src.db
E 15
E 12
E 10
E 5

I 12
D 13
vgrindefs.src.db: vgrindefs.src

E 13
E 12
D 5
vfontedpr: vfontedpr.o vgrindefs.o regexp.o
	cc ${CFLAGS} -o vfontedpr vfontedpr.o vgrindefs.o regexp.o
retest: retest.o regexp.o
	cc ${CFLAGS} -o retest retest.c regexp.o
E 5
I 5
D 10
vfontedpr: ${VOBJS} ${LIBC}
	${CC} ${CFLAGS} -o $@ ${VOBJS}
E 5

D 5
install: all
	install -s vfontedpr ${DESTDIR}/usr/lib/vfontedpr
	install -c vgrind.sh ${DESTDIR}/usr/ucb/vgrind
	install -c vgrindefs.src ${DESTDIR}/usr/lib/vgrindefs
	install -c tmac.vgrind ${DESTDIR}/usr/lib/tmac/tmac.vgrind
E 5
I 5
retest: ${ROBJS} ${LIBC}
	${CC} ${CFLAGS} -o $@ ${ROBJS}
E 5

D 5
clean:
	rm -f ${CMDS} ${OBJS}
E 5
I 5
D 6
clean: FRC
E 6
I 6
clean:
E 6
	rm -f ${OBJS} ${ROBJS} ${VOBJS} core retest vfontedpr
E 5

I 3
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
	mkdep ${CFLAGS} ${RSRCS} ${VSRCS}
E 5

E 3
D 5
vprintall:
	csh /usr/ucb/vprint ${SOURCES}
E 5
I 5
D 6
install: FRC
E 6
I 6
install: ${MAN}
E 6
D 7
	install -s -o bin -g bin -m 755 vfontedpr ${DESTDIR}/usr/lib/vfontedpr
	install -c -o bin -g bin -m 755 vgrind.sh ${DESTDIR}/usr/ucb/vgrind
	install -c -o bin -g bin -m 755 vgrindefs.src ${DESTDIR}/usr/lib/vgrindefs
	install -c -o bin -g bin -m 755 tmac.vgrind ${DESTDIR}/usr/lib/tmac/tmac.vgrind
I 6
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
E 7
I 7
	install -s -o bin -g bin -m 755 vfontedpr ${DESTDIR}/usr/libexec
D 8
	install -c -o bin -g bin -m 755 vgrind.sh ${DESTDIR}/usr/pgrm/vgrind
E 8
I 8
	install -c -o bin -g bin -m 755 vgrind.sh ${DESTDIR}/usr/bin/vgrind
E 8
	install -c -o bin -g bin -m 755 vgrindefs.src \
E 10
I 10
beforeinstall:
I 12
D 15
	cap_mkdb ${.CURDIR}/vgrindefs.src
E 15
I 15
	cap_mkdb -f vgrindefs.src ${.CURDIR}/vgrindefs.src
E 15
E 12
	install -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${.CURDIR}/vgrind.sh ${DESTDIR}/usr/bin/vgrind
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${.CURDIR}/vgrindefs.src \
E 10
	    ${DESTDIR}/usr/share/misc/vgrindefs
I 12
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 \
D 15
	    ${.CURDIR}/vgrindefs.src.db ${DESTDIR}/usr/share/misc/vgrindefs.db
E 15
I 15
	    vgrindefs.src.db ${DESTDIR}/usr/share/misc/vgrindefs.db
E 15
E 12
D 10
	install -c -o bin -g bin -m 755 tmac.vgrind \
	    ${DESTDIR}/usr/share/tmac/tmac.vgrind
	install -c -o bin -g bin -m 444 vgrind.0 ${DESTDIR}/usr/man/cat1
	install -c -o bin -g bin -m 444 vgrindefs.0 ${DESTDIR}/usr/man/cat5
E 10
I 10
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${.CURDIR}/tmac.vgrind \
	    ${DESTDIR}/usr/share/tmac
E 10
E 7
E 6

D 6
lint: FRC
E 6
I 6
D 10
lint: ${SRCS}
E 6
	lint ${CFLAGS} ${RSRCS}
	lint ${CFLAGS} ${VSRCS}

D 6
tags: FRC
E 6
I 6
tags: ${SRCS}
E 6
	ctags ${RSRCS}
	ctags -a ${VSRCS}
	sort -o tags tags

FRC:
E 10
I 10
.include <bsd.prog.mk>
E 10
D 6

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

retest.o: retest.c /usr/include/ctype.h
regexp.o: regexp.c /usr/include/ctype.h regexp.c /usr/include/ctype.h
vfontedpr.o: vfontedpr.c /usr/include/ctype.h /usr/include/stdio.h
vfontedpr.o: /usr/include/sys/types.h /usr/include/sys/stat.h
vgrindefs.o: vgrindefs.c /usr/include/ctype.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 6
E 5
E 1
