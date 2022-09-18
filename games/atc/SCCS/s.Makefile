h21726
s 00000/00000/00018
d D 8.1 93/05/31 16:04:25 bostic 8 7
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00017
d D 5.7 90/06/27 10:21:48 bostic 7 6
c fix for gcc; # line directives change its notion of the current directory
e
s 00006/00004/00012
d D 5.6 90/05/11 12:48:17 bostic 6 5
c first pass for new make
e
s 00012/00052/00004
d D 5.5 90/04/30 21:09:40 bostic 5 4
c move score to /var/games, games to /usr/share/games
e
s 00001/00001/00055
d D 5.4 89/07/30 12:23:52 bostic 4 3
c need libcompat
e
s 00001/00001/00055
d D 5.3 89/05/11 13:48:15 bostic 3 2
c file reorg, pathnames.h, paths.h
e
s 00025/00076/00031
d D 5.2 88/10/19 16:23:31 bostic 2 1
c add manual page, cleanup
e
s 00107/00000/00000
d D 5.1 87/12/12 17:20:38 bostic 1 0
c date and time created 87/12/12 17:20:38 by bostic
e
u
U
t
T
I 6
#	%W% (Berkeley) %G%

E 6
I 1
D 5
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
D 2

E 2
I 2
#	%W% (Berkeley) %G%
#
E 2
D 3
CFLAGS=	-O -DBSD -DDEST=\"${DESTDIR}/usr/games/lib/atc/\"
E 3
I 3
CFLAGS=	-O -DBSD
E 3
YFLAGS=	-d
LIBC=	/lib/libc.a
LIBS=	-ll -lm -lcurses -ltermcap
E 5
I 5
PROG=	atc
D 7
CFLAGS+=-DBSD -I${.CURDIR}
E 7
I 7
CFLAGS+=-DBSD -I${.CURDIR} -I.
E 7
D 6
SRCLIBS=/usr/lib/libl.a ${LIBM} ${LIBTERM} ${LIBCURSES} ${LIBCOMPAT}
LDFILES=-ll -lm -lcurses -ltermcap -lcompat
E 6
E 5
SRCS=	extern.c grammar.c graphics.c input.c lex.c list.c log.c \
	main.c tunable.c update.c
D 5
OBJS=	extern.o grammar.o input.o lex.o list.o log.o main.o tunable.o \
	graphics.o update.o
I 2
MAN=	atc.0
E 5
I 5
D 6
HIDEGAME=hidegame
E 6
MAN6=	atc.0
D 6
CLEANFILES=grammar.c y.tab.h lex.c
E 6
I 6
DPADD=	${usr/lib/libl.a ${LIBM} ${LIBTERM} ${LIBCURSES} ${LIBCOMPAT}
LDADD=	-ll -lm -lcurses -ltermcap -lcompat
E 6
GAMES=	ATC_scores Game_List Killer crossover default easy game_2
I 6
CLEANFILES=grammar.c y.tab.h lex.c
HIDEGAME=hidegame
E 6
E 5
E 2

D 5
all: atc
E 5
I 5
beforeinstall: 
	(cd ${.CURDIR}/games; install -c -o ${BINOWN} -g ${BINGRP} -m 400 \
	    ${GAMES} ${DESTDIR}/usr/share/games/atc)
E 5

D 5
atc: ${OBJS} ${LIBC}
D 4
	${CC} ${CFLAGS} ${OBJS} ${LIBS} -o $@
E 4
I 4
	${CC} ${CFLAGS} ${OBJS} ${LIBS} -o $@ -lcompat
E 4

D 2
clean: FRC
E 2
I 2
clean:
E 2
	rm -f ${OBJS} core atc grammar.c y.tab.h y.tab.c lex.yy.c lex.c

D 2
depend: lex.c grammar.c FRC
E 2
I 2
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 2
	mkdep ${CFLAGS} ${SRCS}

D 2
install: FRC
E 2
I 2
install: ${MAN}
E 2
	-[ -d ${DESTDIR}/usr/games/lib/atc ] || mkdir ${DESTDIR}/usr/games/lib/atc
	chmod 700 ${DESTDIR}/usr/games/lib/atc
	chown games.bin ${DESTDIR}/usr/games/lib/atc
	(cd games; install -c -o games -g bin -m 600 * ${DESTDIR}/usr/games/lib/atc)
	install -s -o games -g bin -m 4700 atc ${DESTDIR}/usr/games/hide/atc
	(cd ${DESTDIR}/usr/games; rm -f atc; ln -s dm atc; chown games.bin atc)
I 2
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/games/cat6
E 2

D 2
lint: lex.c grammar.c FRC
E 2
I 2
lint: ${SRCS}
E 2
	lint ${CFLAGS} ${SRCS}

D 2
tags: lex.c grammar.c FRC
E 2
I 2
tags: ${SRCS}
E 2
	ctags ${SRCS}
E 5
I 5
.include <bsd.prog.mk>
E 5
D 2

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

extern.o: extern.c include.h /usr/include/stdio.h /usr/include/ctype.h
extern.o: /usr/include/pwd.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
extern.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
extern.o: /usr/include/sys/time.h /usr/include/time.h /usr/include/sys/file.h
extern.o: /usr/include/signal.h /usr/include/machine/trap.h /usr/include/math.h
extern.o: /usr/include/curses.h /usr/include/stdio.h /usr/include/sgtty.h def.h
extern.o: struct.h extern.h tunable.h
grammar.o: grammar.c include.h /usr/include/stdio.h /usr/include/ctype.h
grammar.o: /usr/include/pwd.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
grammar.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
grammar.o: /usr/include/sys/time.h /usr/include/time.h /usr/include/sys/file.h
grammar.o: /usr/include/signal.h /usr/include/machine/trap.h
grammar.o: /usr/include/math.h /usr/include/curses.h /usr/include/stdio.h
grammar.o: /usr/include/sgtty.h def.h struct.h extern.h tunable.h
graphics.o: graphics.c include.h /usr/include/stdio.h /usr/include/ctype.h
graphics.o: /usr/include/pwd.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
graphics.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
graphics.o: /usr/include/sys/time.h /usr/include/time.h /usr/include/sys/file.h
graphics.o: /usr/include/signal.h /usr/include/machine/trap.h
graphics.o: /usr/include/math.h /usr/include/curses.h /usr/include/stdio.h
graphics.o: /usr/include/sgtty.h def.h struct.h extern.h tunable.h
input.o: input.c include.h /usr/include/stdio.h /usr/include/ctype.h
input.o: /usr/include/pwd.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
input.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
input.o: /usr/include/sys/time.h /usr/include/time.h /usr/include/sys/file.h
input.o: /usr/include/signal.h /usr/include/machine/trap.h /usr/include/math.h
input.o: /usr/include/curses.h /usr/include/stdio.h /usr/include/sgtty.h def.h
input.o: struct.h extern.h tunable.h
lex.o: lex.c /usr/include/stdio.h y.tab.h
list.o: list.c include.h /usr/include/stdio.h /usr/include/ctype.h
list.o: /usr/include/pwd.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
list.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
list.o: /usr/include/sys/time.h /usr/include/time.h /usr/include/sys/file.h
list.o: /usr/include/signal.h /usr/include/machine/trap.h /usr/include/math.h
list.o: /usr/include/curses.h /usr/include/stdio.h /usr/include/sgtty.h def.h
list.o: struct.h extern.h tunable.h
log.o: log.c include.h /usr/include/stdio.h /usr/include/ctype.h
log.o: /usr/include/pwd.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
log.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
log.o: /usr/include/sys/time.h /usr/include/time.h /usr/include/sys/file.h
log.o: /usr/include/signal.h /usr/include/machine/trap.h /usr/include/math.h
log.o: /usr/include/curses.h /usr/include/stdio.h /usr/include/sgtty.h def.h
log.o: struct.h extern.h tunable.h
main.o: main.c include.h /usr/include/stdio.h /usr/include/ctype.h
main.o: /usr/include/pwd.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
main.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
main.o: /usr/include/sys/time.h /usr/include/time.h /usr/include/sys/file.h
main.o: /usr/include/signal.h /usr/include/machine/trap.h /usr/include/math.h
main.o: /usr/include/curses.h /usr/include/stdio.h /usr/include/sgtty.h def.h
main.o: struct.h extern.h tunable.h
tunable.o: tunable.c
update.o: update.c include.h /usr/include/stdio.h /usr/include/ctype.h
update.o: /usr/include/pwd.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
update.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
update.o: /usr/include/sys/time.h /usr/include/time.h /usr/include/sys/file.h
update.o: /usr/include/signal.h /usr/include/machine/trap.h /usr/include/math.h
update.o: /usr/include/curses.h /usr/include/stdio.h /usr/include/sgtty.h def.h
update.o: struct.h extern.h tunable.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 2
E 1
