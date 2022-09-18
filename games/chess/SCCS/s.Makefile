h20757
s 00000/00000/00015
d D 8.1 93/05/31 16:40:01 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00012/00067/00003
d D 5.4 90/05/11 12:46:49 bostic 4 3
c first pass for new make
e
s 00001/00001/00069
d D 5.3 89/10/17 11:22:46 bostic 3 2
c only make chess, not chessr
e
s 00013/00007/00057
d D 5.2 89/10/17 11:01:33 bostic 2 1
c change to BSD
e
s 00064/00000/00000
d D 5.1 89/10/17 10:52:55 bostic 1 0
c date and time created 89/10/17 10:52:55 by bostic
e
u
U
t
T
I 1
D 4
#
# Makefile for CHESS
#
# Copyright (C) 1986, 1987, 1988 Free Software Foundation, Inc.
#
# This file is part of CHESS.
#
# CHESS is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY.  No author or distributor
# accepts responsibility to anyone for the consequences of using it
# or for whether it serves any particular purpose or works at all,
# unless he says so in writing.  Refer to the CHESS General Public
# License for full details.
#
# Everyone is granted permission to copy, modify and redistribute
# CHESS, but only under the conditions described in the
# CHESS General Public License.   A copy of this license is
# supposed to have been given to you along with CHESS so you
# can know your rights and responsibilities.  It should be in a
# file named COPYING.  Among other things, the copyright notice
# and this notice must be preserved on all copies.
#
#
# gnuchess will be the alpha-display version (with curses/termcap)
# gnuchessr will be the non-display version (for dumb terminals and
#    for use with SUN's chesstool and X-window's xchess.
#    To use with latter, add -DCHESSTOOL to the gnuchess.o/nondsp.o
#    compilation lines (e.g. cc -O -DCHESSTOOL ...)
#
D 2
CC= cc
E 2
NEW=move.o
CFLAGS= -O -DNEWMOVE=12
D 3
all : gnuchess gnuchessr
E 3
I 3
all : gnuchess #gnuchessr
E 3
I 2
MAN=	chess.0
E 4
I 4
#	%W% (Berkeley) %G%
E 4
E 2

D 4
gnuchess: gnuchess.o uxdsp.o $(NEW)
D 2
	$(CC) $(CFLAGS) -o gnuchess gnuchess.o uxdsp.o $(NEW) -lcurses -ltermlib
E 2
I 2
	$(CC) $(CFLAGS) -o gnuchess gnuchess.o uxdsp.o $(NEW) \
		-lcurses -ltermlib -lcompat
E 4
I 4
PROG=	chess
SRCS=	gnuchess.c uxdsp.c move.c
CFLAGS+=-DNEWMOVE=12
MAN6=	chess.0
DPADD=	${LIBCURSES} ${LIBTERM} ${LIBCOMPAT}
LDADD=	-lcurses -ltermlib -lcompat
HIDEGAME=hidegame
E 4
E 2

D 4
gnuchessr: gnuchess.o nondsp.o $(NEW)
D 2
	$(CC) $(CFLAGS) -o gnuchessr gnuchess.o nondsp.o $(NEW)
E 2
I 2
	$(CC) $(CFLAGS) -o gnuchessr gnuchess.o nondsp.o $(NEW) -lcompat
E 4
I 4
beforeinstall: 
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${.CURDIR}/gnuchess.book \
	    ${DESTDIR}/usr/share/games
E 4
E 2

D 4
gnuchess.o: gnuchess.c
	$(CC) $(CFLAGS) -c gnuchess.c

move.o: move.c
	$(CC) $(CFLAGS) -c move.c

uxdsp.o: uxdsp.c
	$(CC) $(CFLAGS) -c uxdsp.c

nondsp.o: nondsp.c
	$(CC) $(CFLAGS) -c nondsp.c

distribution:
	tar cf - gnuchess.h gnuchess.c move.h move.c uxdsp.c nondsp.c Xchess gnuchess.book DOCUMENTATION Makefile > gnuchess.tar
	compress gnuchess.tar

D 2
install:
	cp gnuchessr /usr/games/gnuchess.chesstool
	cp gnuchess /usr/games/gnuchess
	cp gnuchess.book /usr/games/lib/gnuchess.book
E 2
I 2
install: ${MAN}
	install -s -o games -g bin -m 4700 gnuchess ${DESTDIR}/usr/games/hide/chess
	(cd ${DESTDIR}/usr/games; rm -f chess; ln -s dm chess; chown games.bin chess)
	install -c -o bin -g bin -m 444 gnuchess.book /usr/games/lib
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat6

#	cp gnuchessr /usr/games/gnuchess.chesstool
#	cp gnuchess /usr/games/gnuchess
#	cp gnuchess.book /usr/games/lib/gnuchess.book
E 2

clean:
	-rm gnuchess gnuchessr *.o

E 4
I 4
.include <bsd.prog.mk>
E 4
E 1
