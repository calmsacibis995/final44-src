h14622
s 00000/00000/00013
d D 8.1 93/06/06 22:31:07 bostic 9 8
c 4.4BSD snapshot (revision 8.1)
e
s 00010/00060/00003
d D 4.8 90/05/11 14:17:51 bostic 8 7
c first pass for new make
e
s 00003/00003/00060
d D 4.7 89/07/30 15:02:33 bostic 7 6
c needs libcompat
e
s 00002/00003/00061
d D 4.6 89/05/11 13:35:27 bostic 6 5
c file reorg, pathnames.h, paths.h
e
s 00025/00026/00035
d D 4.5 88/10/25 15:58:49 bostic 5 4
c add man page, cleanup
e
s 00050/00018/00011
d D 4.4 87/06/19 00:00:43 bostic 4 3
c new template
e
s 00002/00000/00027
d D 4.3 87/05/31 21:34:06 bostic 3 2
c added depend label
e
s 00006/00007/00021
d D 4.2 83/06/30 14:26:47 sam 2 1
c from sun
e
s 00028/00000/00000
d D 4.1 83/03/30 12:08:40 sam 1 0
c date and time created 83/03/30 12:08:40 by sam
e
u
U
t
T
I 1
D 4
#	%M%	%I%	%E%
E 4
D 8
#
I 4
D 5
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 5
I 5
# Copyright (c) 1987 The Regents of the University of California.
# All rights reserved.
E 5
#
D 5
#	%W%	(Berkeley)	%G%
E 5
I 5
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
E 5
#
E 8
I 5
#	%W% (Berkeley) %G%
D 8
#
E 5
E 4
D 2
CFLAGS=	-O -d2
E 2
I 2
CFLAGS=	-O
E 2
D 4
DESTDIR=
I 2
ALL=	enroll xsend xget
E 4
I 4
LIBC=	/lib/libc.a
SRCS=	enroll.c lib.c xget.c xsend.c
OBJS=	enroll.o lib.o xget.o xsend.o
I 5
MAN=	xsend.0
E 8
E 5
E 4
E 2

D 2
all:	enroll xsend xget
E 2
I 2
D 4
all:	${ALL}
E 4
I 4
D 8
all: enroll xsend xget
E 8
I 8
PROG=	xsend
CFLAGS+=-I${.CURDIR}/../common_source
SRCS=	xsend.c lib.c
DPADD=	${LIBMP} ${LIBCOMPAT}
LDADD=	-lmp -lcompat
MAN1=	xsend.0
MLINKS=	xsend.1 enroll.1 xsend.1 xget.1
.PATH:	${.CURDIR}/../common_source
E 8
E 4
E 2

D 4
enroll:	enroll.o lib.o
	${CC} enroll.o lib.o -lmp -o enroll
E 4
I 4
D 8
enroll: enroll.o lib.o ${LIBC}
D 7
	${CC} enroll.o lib.o -lmp -o $@
E 7
I 7
	${CC} enroll.o lib.o -o $@ -lmp -lcompat
E 7
E 4

D 4
xget:	xget.o lib.o
	${CC} xget.o lib.o -lmp -o xget
E 4
I 4
xget: xget.o lib.o ${LIBC}
D 7
	${CC} xget.o lib.o -lmp -o $@
E 7
I 7
	${CC} xget.o lib.o -o $@ -lmp -lcompat
E 7
E 4

D 4
xsend:	xsend.o lib.o
	${CC} xsend.o lib.o -lmp -o xsend
E 4
I 4
xsend: xsend.o lib.o ${LIBC}
D 7
	${CC} xsend.o lib.o -lmp -o $@
E 7
I 7
	${CC} xsend.o lib.o -o $@ -lmp -lcompat
E 7
E 4

D 4
enroll.o xget.o xsend.o lib.o:	xmail.h
E 4
I 4
D 5
clean: FRC
E 5
I 5
clean:
E 5
	rm -f ${OBJS} core enroll xsend xget
E 4

D 4
list:
D 2
	@pr -2 -w124 m.h xmail.h enroll.c xsend.c xget.c lib.c makefile
E 2
I 2
	@pr -2 -w124 m.h xmail.h enroll.c xsend.c xget.c lib.c Makefile
E 4
I 4
D 5
depend: FRC
E 5
I 5
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 5
	mkdep ${CFLAGS} ${SRCS}
E 4
E 2

D 4
install: enroll xsend xget
D 2
	install -s enroll ${DESTDIR}/usr/bin
	install -s xsend ${DESTDIR}/usr/bin
	install -s xget ${DESTDIR}/usr/bin
E 2
I 2
	for i in ${ALL}; do install -s $$i ${DESTDIR}/usr/bin; done
E 4
I 4
D 5
install: FRC
E 5
I 5
install: ${MAN}
E 5
D 6
	install -s -o bin -g bin -m 755 enroll ${DESTDIR}/usr/bin/enroll
	install -s -o bin -g bin -m 755 xget ${DESTDIR}/usr/bin/xget
	install -s -o bin -g bin -m 755 xsend ${DESTDIR}/usr/bin/xsend
E 6
I 6
	install -s -o bin -g bin -m 755 enroll xget xsend \
	    ${DESTDIR}/usr/bin
E 6
I 5
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
	rm -f ${DESTDIR}/usr/man/cat1/enroll.0
	rm -f ${DESTDIR}/usr/man/cat1/xget.0
	ln ${DESTDIR}/usr/man/cat1/xsend.0 ${DESTDIR}/usr/man/cat1/enroll.0
	ln ${DESTDIR}/usr/man/cat1/xsend.0 ${DESTDIR}/usr/man/cat1/xget.0
E 5
E 4
E 2

D 4
clean:
D 2
	rm -f *.o yacc.* y.tab.c
E 2
I 2
	rm -f *.o yacc.* y.tab.c ${ALL}
E 4
I 4
D 5
lint: FRC
E 5
I 5
lint: ${SRCS}
E 5
	lint ${CFLAGS} enroll.c lib.c
	lint ${CFLAGS} xget.c lib.c
	lint ${CFLAGS} xsend.c lib.c
E 4
I 3

D 4
depend:
E 4
I 4
D 5
tags: FRC
E 5
I 5
tags: ${SRCS
E 5
	ctags enroll.c lib.c
	ctags -a xget.c
	ctags -a xsend.c
	sort -o tags tags
E 8
I 8
.include "../../Makefile.inc"
.include <bsd.prog.mk>
E 8
D 5

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

enroll.o: enroll.c xmail.h /usr/include/stdio.h /usr/include/mp.h
enroll.o: /usr/include/pwd.h /usr/include/sys/types.h
lib.o: lib.c xmail.h /usr/include/stdio.h /usr/include/mp.h
xget.o: xget.c xmail.h /usr/include/stdio.h /usr/include/mp.h
xget.o: /usr/include/sys/types.h /usr/include/sys/dir.h /usr/include/ctype.h
xget.o: /usr/include/pwd.h /usr/include/sys/stat.h
xsend.o: xsend.c xmail.h /usr/include/stdio.h /usr/include/mp.h
xsend.o: /usr/include/sys/types.h /usr/include/pwd.h /usr/include/sys/stat.h
xsend.o: /usr/include/sys/dir.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 5
E 4
E 3
E 2
E 1
