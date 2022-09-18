h34720
s 00000/00000/00006
d D 8.1 93/06/04 17:19:47 bostic 7 6
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00005
d D 5.5 90/05/15 13:08:16 bostic 6 5
c change the names to something reasonable
e
s 00003/00045/00003
d D 5.4 90/05/11 12:49:15 bostic 5 4
c first pass for new make
e
s 00027/00021/00021
d D 5.3 90/03/22 18:16:41 bostic 4 3
c checkpoint for pmake
e
s 00033/00013/00009
d D 5.2 87/06/30 21:25:32 bostic 3 1
c new template
e
s 00033/00013/00009
d R 5.2 87/06/19 16:30:39 bostic 2 1
c new template
e
s 00022/00000/00000
d D 5.1 85/08/09 21:45:42 mckusick 1 0
c date and time created 85/08/09 21:45:42 by mckusick
e
u
U
t
T
I 1
D 5
#
D 3
# Copyright (c) 1985 Regents of the University of California.
E 3
I 3
D 4
# Copyright (c) 1987 Regents of the University of California.
E 3
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 4
I 4
# Copyright (c) 1989 The Regents of the University of California.
# All rights reserved.
E 4
#
D 3
#	%W% (Berkeley) %G%
E 3
I 3
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
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
E 3
#
E 5
I 4
#	%W% (Berkeley) %G%
D 5
#
E 4
D 3
# Make a Yacc library
#
DESTDIR=
CFLAGS=-O 
E 3
I 3
CFLAGS=	-O
LIBC=	/lib/libc.a
E 5
I 5

LIB=	y
E 5
D 6
SRCS=	libmai.c libzer.c
E 6
I 6
SRCS=	main.c yyerror.c
E 6
D 5
OBJS=	libmai.o libzer.o
E 5
E 3

D 3
liby.a:	libmai.o libzer.o
	ar rv liby.a libmai.o libzer.o
	ranlib liby.a
E 3
I 3
D 5
all: liby.a
E 3

D 3
install: liby.a
	install liby.a ${DESTDIR}/usr/lib/liby.a
E 3
I 3
liby.a: ${OBJS}
D 4
	ar cr $@ ${OBJS}
E 4
I 4
	@echo building normal liby
	@ar cr $@ ${OBJS}
	ranlib liby.a
E 4

D 4
clean: FRC
E 4
I 4
clean:
E 4
	rm -f ${OBJS} core liby.a

D 4
depend: FRC
E 4
I 4
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 4
	mkdep ${CFLAGS} ${SRCS}

D 4
install: FRC
E 4
I 4
install: ${MAN}
E 4
	install -o bin -g bin -m 644 liby.a ${DESTDIR}/usr/lib/liby.a
E 3
D 4
	ranlib ${DESTDIR}/usr/lib/liby.a
E 4
I 4
	ranlib -t ${DESTDIR}/usr/lib/liby.a
E 4

D 3
clean:
	rm -f *.o *.a errs
E 3
I 3
D 4
lint: FRC
E 4
I 4
lint: ${SRCS}
E 4
	lint ${CFLAGS} ${SRCS}

D 4
tags: FRC
E 4
I 4
tags: ${SRCS}
E 4
	ctags ${SRCS}
E 5
I 5
.include <bsd.lib.mk>
E 5
D 4

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

libmai.o: libmai.c
libzer.o: libzer.c /usr/include/stdio.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 4
E 3
E 1
