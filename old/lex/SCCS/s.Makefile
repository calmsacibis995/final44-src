h48831
s 00001/00000/00011
d D 4.7 90/06/17 21:01:49 bostic 7 6
c get extra files
e
s 00007/00047/00004
d D 4.6 90/05/11 13:50:05 bostic 6 5
c first pass for new make
e
s 00002/00003/00049
d D 4.5 89/05/10 22:27:49 bostic 5 4
c file reorg, pathnames.h, paths.h
e
s 00025/00022/00027
d D 4.4 88/10/25 15:43:33 bostic 4 3
c add man page, cleanup
e
s 00040/00023/00009
d D 4.3 87/06/18 18:06:36 bostic 3 2
c new template
e
s 00002/00000/00030
d D 4.2 87/05/31 21:30:10 bostic 2 1
c added depend label
e
s 00030/00000/00000
d D 4.1 83/08/11 20:50:28 sam 1 0
c date and time created 83/08/11 20:50:28 by sam
e
u
U
t
T
I 1
D 3
#	%M%	%I%	%E%
E 3
D 6
#
D 3
CFLAGS = -O
E 3
I 3
D 4
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 4
I 4
# Copyright (c) 1987 The Regents of the University of California.
# All rights reserved.
E 4
#
D 4
#	%W%	(Berkeley)	%G%
E 4
I 4
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
E 4
#
E 6
I 4
#	%W% (Berkeley) %G%
D 6
#
E 4
CFLAGS=	-O
LIBC=	/lib/libc.a
E 6
I 6

PROG=	lex
E 6
SRCS=	lmain.c parser.c sub1.c sub2.c header.c
D 6
OBJS=	lmain.o parser.o sub1.o sub2.o header.o
I 4
MAN=	lex.0
E 6
I 6
CFLAGS+=-I${.CURDIR}
I 7
CLEANFILES+=parser.c y.tab.h
E 7
E 6
E 4
E 3

D 6
all: lex
E 6
I 6
beforeinstall:
	install -c -o ${BINOWN} -g ${BINGRP} -m ${MANMODE} ${.CURDIR}/nrform \
	    ${.CURDIR}/ncform ${DESTDIR}/usr/share/misc
E 6

D 3
lex: lmain.o y.tab.o sub1.o sub2.o header.o
	cc lmain.o y.tab.o sub1.o sub2.o header.o -o lex
E 3
I 3
D 6
lex: ${OBJS} ${LIBC}
	${CC} ${CFLAGS} ${OBJS} -o $@
E 3

D 3
smallex:
	cc -DSMALL -O lmain.c y.tab.c sub1.c sub2.c header.c -o smallex
E 3
I 3
smallex: ${SRCS} ${LIBC} FRC
	${CC} -DSMALL ${CFLAGS} ${SRCS} -o $@
E 3

D 3
y.tab.c: parser.y
	yacc parser.y
lmain.o:lmain.c ldefs.c once.c
	cc -c -O lmain.c
sub1.o: sub1.c ldefs.c
	cc -c -O sub1.c
sub2.o: sub2.c ldefs.c
	cc -c -O sub2.c
header.o: header.c ldefs.c
	cc -c -O header.c
E 3
I 3
D 4
clean: FRC
E 4
I 4
clean:
E 4
	rm -f ${OBJS} core lex smallex parser.c
E 3

D 3
install: all
	install -s lex $(DESTDIR)/usr/bin
	install -c ncform $(DESTDIR)/usr/lib/lex
	install -c nrform $(DESTDIR)/usr/lib/lex
E 3
I 3
D 4
depend: ${SRCS} FRC
E 4
I 4
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 4
	mkdep ${CFLAGS} ${SRCS}
E 3

D 3
clean:
	rm -f *.o lex y.tab.c
E 3
I 3
D 4
install: FRC
E 4
I 4
install: ${MAN}
E 4
D 5
	install -s -o bin -g bin -m 755 lex ${DESTDIR}/usr/bin/lex
	install -c -o bin -g bin -m 755 ncform ${DESTDIR}/usr/lib/lex/ncform
	install -c -o bin -g bin -m 755 nrform ${DESTDIR}/usr/lib/lex/nrform
E 5
I 5
	install -s -o bin -g bin -m 755 lex ${DESTDIR}/usr/bin
	install -c -o bin -g bin -m 444 nrform ncform ${DESTDIR}/usr/share/misc
E 5
I 4
	install -c -o bin -g bin -m 755 ${MAN} ${DESTDIR}/usr/man/cat1
E 4
E 3
I 2

D 3
depend:
E 3
I 3
D 4
lint: ${SRCS} FRC
E 4
I 4
lint: ${SRCS}
E 4
	lint ${CFLAGS} ${SRCS}

D 4
tags: ${SRCS} FRC
E 4
I 4
tags: ${SRCS}
E 4
	ctags ${SRCS}
E 6
I 6
.include <bsd.prog.mk>
E 6
D 4

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

lmain.o: lmain.c ldefs.c /usr/include/stdio.h once.c
parser.o: parser.c ldefs.c /usr/include/stdio.h
sub1.o: sub1.c ldefs.c /usr/include/stdio.h
sub2.o: sub2.c ldefs.c /usr/include/stdio.h
header.o: header.c ldefs.c /usr/include/stdio.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 4
E 3
E 2
E 1
