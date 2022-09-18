h06818
s 00001/00001/00025
d D 5.8 92/07/18 03:47:22 cael 8 7
c remove old nroff -h flag as groff does not use it
e
s 00003/00000/00023
d D 5.7 91/01/14 17:24:49 bostic 7 6
c create e.def for "make depend"
e
s 00001/00001/00022
d D 5.6 90/06/24 11:15:26 bostic 6 5
c clean e.def
e
s 00001/00000/00022
d D 5.5 90/05/11 15:12:08 bostic 5 4
c add Makefile.inc
e
s 00016/00060/00006
d D 5.4 90/05/11 15:10:58 bostic 4 3
c first pass for new make
e
s 00003/00000/00059
d D 5.3 88/10/25 18:34:20 bostic 3 2
c need to run eqn on eqn's man page... poetic justice, that...
e
s 00026/00044/00033
d D 5.2 88/10/22 15:58:48 bostic 2 1
c cleanup, add labels, man page
e
s 00077/00000/00000
d D 5.1 87/12/12 17:34:57 bostic 1 0
c date and time created 87/12/12 17:34:57 by bostic
e
u
U
t
T
I 1
D 4
#
D 2
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 2
I 2
# Copyright (c) 1987 The Regents of the University of California.
# All rights reserved.
E 2
#
D 2
#	%W%	(Berkeley)	%G%
E 2
I 2
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
E 2
#
E 4
I 2
#	%W% (Berkeley) %G%
D 4
#
E 2
COMMON=	../common_source
CFLAGS=	-O -I. -I${COMMON}
YFLAGS=	-d
VPATH=	${COMMON}
LIBC=	/lib/libc.a
SRCS=	e.c diacrit.c eqnbox.c font.c fromto.c funny.c glob.c integral.c \
	io.c lex.c lookup.c mark.c matrix.c move.c over.c paren.c pile.c \
	shift.c size.c sqrt.c text.c
OBJS=	e.o diacrit.o eqnbox.o font.o fromto.o funny.o glob.o integral.o \
	io.o lex.o lookup.o mark.o matrix.o move.o over.o paren.o pile.o \
	shift.o size.o sqrt.o text.o
I 2
MAN=	eqn.0
E 4
E 2

D 4
all: eqn
E 4
I 4
PROG=	eqn
CFLAGS+=-I. -I${.CURDIR}/../common_source
SRCS=	diacrit.c eqnbox.c font.c fromto.c funny.c glob.c integral.c io.c \
	lex.c lookup.c mark.c matrix.c move.c over.c paren.c pile.c shift.c \
	size.c sqrt.c text.c
OBJS+=	e.o
.PATH:	${.CURDIR}/../common_source
YFLAGS+=-d
MLINKS=	eqn.1 checkeq.1 eqn.1 neqn.1
D 6
CLEANFILES+=e.c y.tab.h
E 6
I 6
CLEANFILES+=e.c e.def y.tab.h
E 6
E 4

D 4
eqn: ${OBJS} ${LIBC}
	${CC} -o $@ ${CFLAGS} ${OBJS}
E 4
I 4
e.c:
	${YACC} ${YFLAGS} ${.CURDIR}/../common_source/e.y
	mv y.tab.c e.c
	mv y.tab.h e.def
E 4

I 7
e.def: e.c
.depend: e.def

E 7
I 3
eqn.0:
D 4
	eqn eqn.1 | nroff -h -man > $@
E 4
I 4
D 8
	eqn ${.CURDIR}/eqn.1 | nroff -h -man > ${.TARGET}
E 8
I 8
	eqn ${.CURDIR}/eqn.1 | nroff -man > ${.TARGET}
E 8
E 4

I 5
.include "../../Makefile.inc"
E 5
E 3
D 4
e.c: ${COMMON}/e.y
	${YACC} ${YFLAGS} ${COMMON}/e.y
	mv y.tab.h e.def
	mv y.tab.c e.c

D 2
clean: FRC
E 2
I 2
clean:
E 2
	rm -f ${OBJS} core e.def e.c eqn

D 2
depend: ${SRCS} FRC
E 2
I 2
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 2
	mkdep ${CFLAGS} ${SRCS}

D 2
install: FRC
	install -s -o bin -g bin -m 755 eqn ${DESTDIR}/usr/bin/eqn
E 2
I 2
install: ${MAN}
	install -s -o bin -g bin -m 755 eqn ${DESTDIR}/usr/bin
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
	rm -f ${DESTDIR}/usr/man/cat1/checkeq.0
	rm -f ${DESTDIR}/usr/man/cat1/neqn.0
	ln ${DESTDIR}/usr/man/cat1/eqn.0 ${DESTDIR}/usr/man/cat1/checkeq.0
	ln ${DESTDIR}/usr/man/cat1/eqn.0 ${DESTDIR}/usr/man/cat1/neqn.0
E 2

D 2
lint: ${SRCS} FRC
E 2
I 2
lint: ${SRCS}
E 2
	lint ${CFLAGS} ${SRCS}

D 2
tags: ${SRCS} FRC
E 2
I 2
tags: ${SRCS}
E 2
	ctags ${SRCS}
E 4
I 4
.include <bsd.prog.mk>
E 4
D 2

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

e.o: e.c ../common_source/e.h /usr/include/stdio.h
diacrit.o: ../common_source/diacrit.c ../common_source/e.h /usr/include/stdio.h
diacrit.o: e.def
eqnbox.o: ../common_source/eqnbox.c ../common_source/e.h /usr/include/stdio.h
font.o: ../common_source/font.c ../common_source/e.h /usr/include/stdio.h
fromto.o: ../common_source/fromto.c ../common_source/e.h /usr/include/stdio.h
funny.o: ../common_source/funny.c ../common_source/e.h /usr/include/stdio.h
funny.o: e.def
glob.o: ../common_source/glob.c ../common_source/e.h /usr/include/stdio.h
integral.o: ../common_source/integral.c ../common_source/e.h
integral.o: /usr/include/stdio.h e.def
io.o: ../common_source/io.c ../common_source/e.h /usr/include/stdio.h
lex.o: ../common_source/lex.c ../common_source/e.h /usr/include/stdio.h e.def
lookup.o: ../common_source/lookup.c ../common_source/e.h /usr/include/stdio.h
lookup.o: e.def
mark.o: ../common_source/mark.c ../common_source/e.h /usr/include/stdio.h
matrix.o: ../common_source/matrix.c ../common_source/e.h /usr/include/stdio.h
move.o: ../common_source/move.c ../common_source/e.h /usr/include/stdio.h e.def
over.o: ../common_source/over.c ../common_source/e.h /usr/include/stdio.h
paren.o: ../common_source/paren.c ../common_source/e.h /usr/include/stdio.h
pile.o: ../common_source/pile.c ../common_source/e.h /usr/include/stdio.h
shift.o: ../common_source/shift.c ../common_source/e.h /usr/include/stdio.h
shift.o: e.def
size.o: ../common_source/size.c ../common_source/e.h /usr/include/stdio.h
sqrt.o: ../common_source/sqrt.c ../common_source/e.h /usr/include/stdio.h
text.o: ../common_source/text.c ../common_source/e.h /usr/include/stdio.h e.def

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 2
E 1
