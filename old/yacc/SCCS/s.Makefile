h10137
s 00007/00045/00003
d D 4.7 90/05/31 16:46:25 bostic 7 6
c pmake
e
s 00002/00002/00046
d D 4.6 89/05/10 22:31:16 bostic 6 5
c file reorg, pathnames.h, paths.h
e
s 00025/00021/00023
d D 4.5 88/10/25 15:57:48 bostic 5 4
c add man page, cleanup
e
s 00037/00018/00007
d D 4.4 87/06/19 00:03:20 bostic 4 3
c new template
e
s 00002/00000/00023
d D 4.3 87/05/31 21:34:21 bostic 3 2
c added depend label
e
s 00001/00000/00022
d D 4.2 83/02/11 16:09:42 rrh 2 1
c define DESTDIR
e
s 00022/00000/00000
d D 4.1 83/02/11 15:24:51 rrh 1 0
c date and time created 83/02/11 15:24:51 by rrh
e
u
U
t
T
I 1
D 7
#
D 4
#	%W%	(Berkeley)	%E%
E 4
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
E 4
#
I 2
D 4
DESTDIR=
E 2
CFLAGS=-O -DWORD32
SRCS = Makefile dextern files yaccpar \
	y1.c y2.c y3.c y4.c \
	yaccdiffs yaccnews
E 4
I 4
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
I 5
#	%W% (Berkeley) %G%
#
E 5
CFLAGS=	-O -DWORD32
LIBC=	/lib/libc.a
E 7
I 7
#	%W% (Berkeley) %G%

PROG=	yacc
CFLAGS+=-DWORD32
E 7
SRCS=	y1.c y2.c y3.c y4.c
D 7
OBJS=	y1.o y2.o y3.o y4.o
I 5
MAN=	yacc.0
E 7
I 7
MAN1=	yacc.0
E 7
E 5
E 4

D 7
all: yacc
E 7
I 7
beforeinstall:
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${.CURDIR}/old.yaccpar \
	    ${DESTDIR}/usr/share/misc
E 7

D 4
yacc: y1.o y2.o y3.o y4.o
	$(CC) -o yacc y?.o 
y1.o y2.o y3.o y4.o: dextern files
install:
	install -s yacc $(DESTDIR)/usr/bin
	install -c yaccpar $(DESTDIR)/usr/lib
clean :
	-rm -f *.o yacc
E 4
I 4
D 7
yacc: ${OBJS} ${LIBC}
	${CC} -o $@ ${CFLAGS} ${OBJS}
E 4

D 4
srcs: $(SRCS)
$(SRCS):
	sccs get $@
E 4
I 4
D 5
clean: FRC
E 5
I 5
clean:
E 5
	rm -f ${OBJS} core yacc
E 4
I 3

D 4
depend:
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

D 5
install: FRC
E 5
I 5
install: ${MAN}
E 5
D 6
	install -s -o bin -g bin -m 755 yacc ${DESTDIR}/usr/bin/yacc
	install -c -o bin -g bin -m 755 yaccpar ${DESTDIR}/usr/lib/yaccpar
E 6
I 6
	install -s -o bin -g bin -m 755 yacc ${DESTDIR}/usr/bin
	install -c -o bin -g bin -m 755 yaccpar ${DESTDIR}/usr/share/misc
E 6
I 5
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
E 5

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
E 7
I 7
.include <bsd.prog.mk>
E 7
D 5

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

y1.o: y1.c dextern /usr/include/stdio.h /usr/include/ctype.h files
y2.o: y2.c dextern /usr/include/stdio.h /usr/include/ctype.h files
y3.o: y3.c dextern /usr/include/stdio.h /usr/include/ctype.h files
y4.o: y4.c dextern /usr/include/stdio.h /usr/include/ctype.h files

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 5
E 4
E 3
E 1
