h14126
s 00000/00000/00026
d D 8.1 93/05/31 17:27:24 bostic 9 8
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00025
d D 5.8 92/09/02 11:50:58 bostic 8 7
c just copy the cards
e
s 00001/00001/00025
d D 5.7 92/03/16 14:18:58 bostic 7 6
c make man page, too
e
s 00003/00001/00023
d D 5.6 91/11/15 12:33:18 bostic 6 5
c add target for monop
e
s 00017/00057/00007
d D 5.5 90/05/11 12:48:06 bostic 5 4
c first pass for new make
e
s 00001/00001/00063
d D 5.4 89/07/30 12:59:19 bostic 4 3
c needs libcompat
e
s 00012/00035/00052
d D 5.3 88/10/19 21:53:31 bostic 3 2
c cleanup, add manual page
e
s 00014/00003/00073
d D 5.2 88/06/18 14:54:20 bostic 2 1
c install approved copyright notice
e
s 00076/00000/00000
d D 5.1 87/12/12 17:18:36 bostic 1 0
c date and time created 87/12/12 17:18:36 by bostic
e
u
U
t
T
I 1
D 5
#
# Copyright (c) 1987 Regents of the University of California.
D 2
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 2
I 2
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
#
E 5
#	%W% (Berkeley) %G%
E 2
D 5
#
# Nifty foo monopoly maker
#	Program:  Ken Arnold
#	Makefile:  K.S.
#
CFLAGS=	-O
LIBC=	/lib/libc.a
MSRCS=	monop.c cards.c execute.c getinp.c houses.c jail.c misc.c morg.c \
E 5
I 5

PROG=	monop
SRCS=	monop.c cards.c execute.c getinp.c houses.c jail.c misc.c morg.c \
E 5
	print.c prop.c rent.c roll.c spec.c trade.c
D 5
MOBJS=	monop.o cards.o execute.o getinp.o houses.o jail.o misc.o morg.o \
	print.o prop.o rent.o roll.o spec.o trade.o
ISRCS=	initdeck.c
IOBJS=	initdeck.o
I 3
MAN=	monop.0
E 5
I 5
MAN6=	monop.0
DPADD=	${LIBCOMPAT}
LDADD=	-lcompat
HIDEGAME=hidegame
CLEANFILES+=initdeck cards.pck
E 5
E 3

D 5
all: monop initdeck cards.pck
E 5
I 5
D 6
all: cards.pck
E 6
I 6
D 7
all: monop
E 7
I 7
all: ${PROG} ${MAN6}
E 7

monop: cards.pck
E 6
E 5

D 3
monop:	${MOBJS} ${LIBC}
E 3
I 3
D 5
monop: ${MOBJS} ${LIBC}
E 3
D 4
	${CC} -o $@ ${CFLAGS} ${MOBJS}
E 4
I 4
	${CC} -o $@ ${CFLAGS} ${MOBJS} -lcompat
E 5
I 5
cards.pck: initdeck
	./initdeck ${.CURDIR}/cards.inp
E 5
E 4

D 5
initdeck: ${IOBJS}
	${CC} ${CFLAGS} -o $@ ${IOBJS}
E 5
I 5
initdeck: initdeck.c
	${CC} ${CFLAGS} -o ${.TARGET} ${.CURDIR}/initdeck.c
E 5

D 3
cards.pck: FRC
E 3
I 3
D 5
cards.pck:
E 3
	./initdeck
E 5
I 5
beforeinstall:
D 8
	install -o ${BINOWN} -g ${BINGRP} -m 444 cards.pck \
E 8
I 8
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 cards.pck \
E 8
	    ${DESTDIR}/usr/share/games
E 5

D 3
clean: FRC
E 3
I 3
D 5
clean:
E 3
	rm -f ${IOBJS} ${MOBJS} core monop initdeck cards.pck

D 3
depend: FRC
E 3
I 3
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 3
	mkdep ${CFLAGS} ${MSRCS} ${ISRCS}

D 3
install: FRC
E 3
I 3
install: ${MAN}
E 3
	install -o games -g bin -m 400 cards.pck ${DESTDIR}/usr/games/lib
	install -s -o games -g bin -m 700 monop ${DESTDIR}/usr/games/hide
	(cd ${DESTDIR}/usr/games; rm -f monop; ln -s dm monop; chown games.bin monop)
I 3
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat6
E 3

D 3
lint: FRC
E 3
I 3
lint: ${SRCS}
E 3
	lint ${CFLAGS} ${MSRCS}
	lint ${CFLAGS} ${ISRCS}

D 3
tags: FRC
E 3
I 3
tags: ${SRCS}
E 3
	ctags ${MSRCS} ${ISRCS}
E 5
I 5
.include <bsd.prog.mk>
E 5
D 3

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

monop.o: monop.c monop.def monop.h /usr/include/stdio.h deck.h mon.dat prop.dat
monop.o: brd.dat
cards.o: cards.c monop.ext monop.h /usr/include/stdio.h deck.h
execute.o: execute.c monop.ext monop.h /usr/include/stdio.h deck.h
execute.o: /usr/include/sys/types.h /usr/include/sys/stat.h
execute.o: /usr/include/sys/time.h /usr/include/time.h
getinp.o: getinp.c /usr/include/stdio.h /usr/include/ctype.h
houses.o: houses.c monop.ext monop.h /usr/include/stdio.h deck.h
jail.o: jail.c monop.ext monop.h /usr/include/stdio.h deck.h
misc.o: misc.c monop.ext monop.h /usr/include/stdio.h deck.h
misc.o: /usr/include/ctype.h /usr/include/signal.h /usr/include/machine/trap.h
misc.o: /usr/include/pwd.h
morg.o: morg.c monop.ext monop.h /usr/include/stdio.h deck.h
print.o: print.c monop.ext monop.h /usr/include/stdio.h deck.h
prop.o: prop.c monop.ext monop.h /usr/include/stdio.h deck.h
rent.o: rent.c monop.ext monop.h /usr/include/stdio.h deck.h
roll.o: roll.c
spec.o: spec.c monop.ext monop.h /usr/include/stdio.h deck.h
trade.o: trade.c monop.ext monop.h /usr/include/stdio.h deck.h
initdeck.o: initdeck.c /usr/include/stdio.h deck.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 3
E 1
