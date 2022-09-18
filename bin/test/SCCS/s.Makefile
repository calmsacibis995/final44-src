h21049
s 00000/00000/00008
d D 8.1 93/05/31 15:49:41 bostic 8 7
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00006/00008
d D 5.2 93/04/30 11:37:47 bostic 7 6
c quite building operators dynamically (from NetBSD, Adam Glass)
e
s 00004/00012/00010
d D 5.1 92/06/08 17:16:59 bostic 6 5
c Makefile for Almquist's version of test
e
s 00006/00003/00016
d D 1.5 92/06/05 12:40:08 elan 5 4
c Added dependency of operators.o.
e
s 00010/00015/00009
d D 1.4 92/06/04 17:23:04 elan 4 3
c Revised to work with bsd.prog.mk.
e
s 00001/00000/00023
d D 1.3 92/06/03 16:40:16 elan 3 2
c Added chmod to ./mkops.
e
s 00001/00003/00022
d D 1.2 92/06/03 16:34:10 elan 2 1
c Added BSD Copyright
e
s 00025/00000/00000
d D 1.1 92/06/03 13:16:28 elan 1 0
c date and time created 92/06/03 13:16:28 by elan
e
u
U
t
T
I 1
D 2
# Copyright (C) 1989 by Kenneth Almquist.  All rights reserved.
# This file is part of ash, which is distributed under the terms specified
# by the Ash General Public License.  See the file named LICENSE.
E 2
I 2
#        %W% (Berkeley) %G%
E 2

D 6

E 6
D 4
PROG= test
CFLAGS = -O
CC= cc
OBJS= error.o stalloc.o operators.o 
E 4
I 4
PROG=	test
D 5
SRCS=	test.c error.c stalloc.c operators.c
E 5
I 5
D 6
PROG2=  '['
SRCS=   test.c error.c stalloc.c operators.c
E 5
CFLAGS += -I{.CURDIR} -I.
E 6
I 6
SRCS=   test.c operators.c
D 7
CFLAGS+=-I.
E 7
LINKS=	${BINDIR}/test ${BINDIR}/[
MLINKS=	test.1 '[.1'
E 6
D 7
CLEANFILES+= operators.c operators.h unary_op binary_op
E 4

D 4
$(PROG): test.c operators.h extern.h $(OBJS)
	$(CC) $(CFLAGS) -o $@ test.c operators.o error.o stalloc.o
E 4
I 4
D 6
.PATH: /usr/src/bin/test/obj

afterinstall:
E 4
D 5
	-rm -f '['
	ln test '['
E 5
I 5
	ln ${DESTDIR}${BINDIR}/${PROG} ${DESTDIR}${BINDIR}/${PROG2}
E 5

E 6
operators.c operators.h: unary_op binary_op mkops
I 3
D 4
	chmod 555 ./mkops
E 3
	./mkops
E 4
I 4
	cp ${.CURDIR}/unary_op ${.CURDIR}/binary_op .
	sh ${.CURDIR}/mkops
E 7
I 5
D 6


operators.o: operators.c operators.h
E 6
E 5
E 4

D 4
operators.o: operators.h

clean:
	rm -f core.* *.o $(PROG) operators.h operators.c

tags:
	ctags -t -d *.[ch]
E 4
I 4
.include <bsd.prog.mk>
E 4
E 1
