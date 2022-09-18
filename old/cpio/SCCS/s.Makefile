h61998
s 00002/00001/00008
d D 5.8 90/06/19 18:24:38 bostic 9 8
c install in section 5 as "cpio", too
e
s 00006/00045/00003
d D 5.7 90/05/11 15:15:18 bostic 8 7
c first pass for new make
e
s 00001/00001/00047
d D 5.6 89/07/30 14:15:16 bostic 7 6
c needs libcompat
e
s 00003/00003/00045
d D 5.5 89/05/11 09:45:02 bostic 6 5
c file reorg, pathnames.h, paths.h
e
s 00009/00027/00039
d D 5.4 89/03/06 08:13:29 bostic 5 4
c add cleandir, cleanup
e
s 00010/00005/00056
d D 5.3 88/07/09 11:22:06 bostic 4 3
c install approved copyright notice
e
s 00015/00005/00046
d D 5.2 88/03/29 15:19:16 bostic 3 1
c add manual pages
e
s 00014/00004/00047
d R 5.2 88/03/29 15:18:39 bostic 2 1
c add manual pages
e
s 00051/00000/00000
d D 5.1 88/03/29 13:49:01 bostic 1 0
c date and time created 88/03/29 13:49:01 by bostic
e
u
U
t
T
I 1
D 8
#
D 3
# Copyright (c) 1987 Regents of the University of California.
E 3
I 3
# Copyright (c) 1988 Regents of the University of California.
E 3
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
D 4
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
D 3
# software without specific written prior permission. This software
E 3
I 3
# software without specific prior written permission. This software
E 3
# is provided ``as is'' without express or implied warranty.
E 4
I 4
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
E 4
#
E 8
#	%W% (Berkeley) %G%
D 8
#
CFLAGS=	-O
LIBC=	/lib/libc.a
SRCS=	cpio.c
OBJS=
I 3
MAN=	cpio.0 cpio_format.0
E 8
E 3

I 3
D 5
.SUFFIXES: .5 .1 .0

.1.0:
	${DESTDIR}/usr/man/manroff $*.1 > $*.0
.5.0:
	${DESTDIR}/usr/man/manroff $*.5 > $*.0

E 5
E 3
D 8
all: cpio
E 8
I 8
PROG=	cpio
MAN1=	cpio.0
D 9
MAN5=	cpio_format.0
E 9
I 9
MAN5=	cpioformat.0
MLINKS=	cpioformat.5 cpio.5
E 9
DPADD=	${LIBCOMPAT}
LDADD=	-lcompat
E 8

D 8
cpio: ${LIBC}
D 7
	${CC} -o $@ ${CFLAGS} cpio.c
E 7
I 7
	${CC} -o $@ ${CFLAGS} cpio.c -lcompat
E 7

D 5
clean: FRC
D 3
	rm -f ${OBJS} core cpio
E 3
I 3
	rm -f ${OBJS} ${MAN} core cpio
E 5
I 5
clean:
	rm -f ${OBJS} core cpio
E 5
E 3

D 5
depend: FRC
E 5
I 5
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 5
	mkdep -p ${CFLAGS} ${SRCS}

D 3
install: FRC
	install -s -o bin -g bin -m 755 PROG ${DESTDIR}/bin/cpio
E 3
I 3
D 5
install: ${MAN} FRC
E 5
I 5
install: ${MAN}
E 5
D 6
	install -s -o bin -g bin -m 755 cpio ${DESTDIR}/bin/cpio
	install -c -o bin -g bin -m 444 cpio.0 ${DESTDIR}/usr/man/cat1/cpio.0
	install -c -o bin -g bin -m 444 cpio_format.0 ${DESTDIR}/usr/man/cat5/cpio.0
E 6
I 6
	install -s -o bin -g bin -m 755 cpio ${DESTDIR}/usr/bin
	install -c -o bin -g bin -m 444 cpio.0 ${DESTDIR}/usr/man/cat1
	install -c -o bin -g bin -m 444 cpio_format.0 ${DESTDIR}/usr/man/cat5
E 6
E 3

D 5
lint: FRC
E 5
I 5
lint: ${SRCS}
E 5
	lint ${CFLAGS} ${SRCS}

D 5
tags: FRC
E 5
I 5
tags: ${SRCS}
E 5
	ctags ${SRCS}
E 8
I 8
.include <bsd.prog.mk>
E 8
D 5

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

cpio: cpio.c /usr/include/errno.h /usr/include/fcntl.h /usr/include/memory.h
cpio: /usr/include/stdio.h /usr/include/string.h /usr/include/strings.h
cpio: /usr/include/signal.h /usr/include/machine/trap.h /usr/include/varargs.h
cpio: /usr/include/sys/param.h /usr/include/sys/types.h /usr/include/signal.h
cpio: /usr/include/machine/machparam.h /usr/include/machine/endian.h
cpio: /usr/include/sys/types.h /usr/include/sys/stat.h /usr/include/pwd.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 5
E 1
