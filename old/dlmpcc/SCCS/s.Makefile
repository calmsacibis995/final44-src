h04777
s 00001/00000/00013
d D 5.7 91/01/17 14:46:05 bostic 7 6
c kernel reorg
e
s 00009/00046/00004
d D 5.6 90/05/11 16:06:23 bostic 6 5
c first pass for new make
e
s 00003/00002/00047
d D 5.5 89/05/11 14:14:51 bostic 5 4
c file reorg, pathnames.h, paths.h
e
s 00007/00003/00042
d D 5.4 88/10/19 09:56:05 bostic 4 3
c cleanups, add manual pages
e
s 00024/00013/00021
d D 5.3 88/09/18 12:22:02 bostic 3 2
c appropriate copyrights
e
s 00002/00001/00032
d D 5.2 87/11/23 18:31:43 bostic 2 1
c add firmware
e
s 00033/00000/00000
d D 5.1 87/11/15 14:33:53 sam 1 0
c date and time created 87/11/15 14:33:53 by sam
e
u
U
t
T
I 1
D 6
#
D 3
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 3
I 3
# Copyright (c) 1987 The Regents of the University of California.
# All rights reserved.
E 3
#
D 3
#	%W%	(Berkeley)	%G%
E 3
I 3
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
E 3
#
E 6
I 3
#	%W% (Berkeley) %G%
D 6
#
E 3
CFLAGS=	-O
LIBC=	/lib/libc.a
I 3
SRCS=	dlmpcc.c
I 4
MAN=	dlmpcc.0 mpcc.0 mpcctab.0
E 6
I 6

PROG=	dlmpcc
I 7
CFLAGS+=-I/sys
E 7
MAN8=	dlmpcc.0
MAN4=	mpcc.0 mpcctab.0
MANSUBDIR=/tahoe
E 6
I 5
FILES=	mpcc32 mpccdl mpcctab
E 5
E 4
E 3

D 3
all:	dlmpcc
E 3
I 3
D 6
all: dlmpcc
E 6
I 6
beforeinstall:
	(cd ${.CURDIR}/firmware; install -c -o ${BINOWN} -g ${BINGRP} -m 444 \
	     ${FILES} ${DESTDIR}/usr/libdata)
E 6
E 3

D 4
dlmpcc: dlmpcc.c ${LIBC}
E 4
I 4
D 6
dlmpcc: ${LIBC}
E 4
	${CC} ${CFLAGS} -o $@ $@.c

clean:
	rm -f dlmpcc core a.out errs

I 3
cleandir: clean
	rm -f ${MAN} tags .depend

E 3
D 4
depend:
E 4
I 4
depend: ${SRCS}
E 4
	mkdep -p ${CFLAGS} dlmpcc.c

D 2
install: dlmpcc
E 2
I 2
D 4
install:
E 4
I 4
install: ${MAN}
E 4
E 2
D 5
	install -s -o bin -g bin -m 755 dlmpcc ${DESTDIR}/etc/dlmpcc
I 2
	install -c -o bin -g bin -m 444 firmware/* ${DESTDIR}/etc
E 5
I 5
	install -s -o bin -g bin -m 755 dlmpcc ${DESTDIR}/usr/sbin
	(cd firmware; install -c -o bin -g bin -m 444 ${FILES} ${DESTDIR}/usr/libdata)
E 5
I 4
	install -c -o bin -g bin -m 444 dlmpcc.0 ${DESTDIR}/usr/man/cat8/tahoe
	install -c -o bin -g bin -m 444 mpcc.0 ${DESTDIR}/usr/man/cat4/tahoe
	install -c -o bin -g bin -m 444 mpcctab.0 ${DESTDIR}/usr/man/cat4/tahoe
E 4
E 2

D 3
# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.
E 3
I 3
lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}
E 3

D 3
dlmpcc: dlmpcc.c /usr/include/stdio.h /usr/include/ctype.h /usr/include/fcntl.h
dlmpcc: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
dlmpcc: /usr/include/sys/ttydev.h /usr/include/errno.h /usr/include/sys/types.h
dlmpcc: /usr/include/tahoevba/mpreg.h /usr/include/stdio.h scnhdr.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 3
I 3
tags: ${SRCS}
	ctags ${SRCS}
E 6
I 6
.include <bsd.prog.mk>
E 6
E 3
E 1
