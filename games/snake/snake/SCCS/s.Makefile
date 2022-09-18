h23788
s 00000/00000/00011
d D 8.1 93/05/31 17:52:41 bostic 16 15
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00010
d D 5.11 91/02/28 15:06:50 bostic 15 14
c fix up directory structure
e
s 00008/00054/00003
d D 5.10 90/05/11 12:47:58 bostic 14 13
c first pass for new make
e
s 00001/00002/00056
d D 5.9 89/07/30 13:06:35 bostic 13 12
c needs libcompat
e
s 00013/00026/00045
d D 5.8 88/10/20 11:20:52 bostic 12 11
c add manual page, cleanup
e
s 00010/00005/00061
d D 5.7 88/06/18 19:30:45 bostic 11 10
c install approved copyright notice
e
s 00001/00001/00065
d D 5.6 88/04/20 12:29:56 bostic 10 9
c don't overwrite scoreboard if it exists
e
s 00012/00007/00054
d D 5.5 88/03/09 11:29:47 bostic 9 8
c add Berkeley specific header
e
s 00008/00013/00053
d D 5.4 87/09/21 11:58:31 bostic 8 5
c integrate with dm
e
s 00012/00013/00053
d R 5.4 87/09/20 12:01:22 bostic 7 5
c integrate with dm
e
s 00009/00004/00062
d R 5.4 87/09/20 10:59:36 bostic 6 5
c integrate new dm
e
s 00051/00027/00015
d D 5.3 87/06/05 16:17:13 bostic 5 3
c new template
e
s 00052/00027/00015
d R 5.3 87/06/03 17:16:44 bostic 4 3
c new template
e
s 00002/00000/00040
d D 5.2 87/05/31 21:02:06 bostic 3 2
c added depend label
e
s 00006/00001/00034
d D 5.1 85/05/30 08:46:36 dist 2 1
c Add copyright
e
s 00035/00000/00000
d D 4.1 83/07/04 12:48:22 sam 1 0
c date and time created 83/07/04 12:48:22 by sam
e
u
U
t
T
I 1
D 2
#	%M%	%I%	%E%
E 2
I 2
D 14
#
D 5
# Copyright (c) 1980 Regents of the University of California.
E 5
I 5
# Copyright (c) 1987 Regents of the University of California.
E 5
D 9
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 9
I 9
# All rights reserved.
E 9
#
D 5
#	%W% (Berkeley) %G%
E 5
I 5
D 9
#	%W%	(Berkeley)	%G%
E 9
I 9
# Redistribution and use in source and binary forms are permitted
D 11
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
# is provided ``as is'' without express or implied warranty.
E 11
I 11
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
E 11
E 9
E 5
E 2
#
E 14
I 9
#	%W% (Berkeley) %G%
D 14
#
E 9
D 5
DESTDIR=
E 5
CFLAGS=	-O
I 5
LIBC=	/lib/libc.a
E 5
D 13
LIBS=	-lm -ltermcap
E 13
D 5
BIN=	$(DESTDIR)/usr/games
LIB=	$(DESTDIR)/usr/games/lib
USER=	daemon
UTILS=	snscore
OBJS=	snake.o move.o
ALL=	snake ${UTILS}
E 5
I 5
SRCS1=	snake.c move.c
OBJS1=	snake.o move.o
SRCS2=	snscore.c
OBJS2=	snscore.o
I 12
MAN=	snake.0
E 14
E 12
D 8
SRCS3=	busy.c
OBJS3=	busy.o
E 8
E 5

D 5
all:	${ALL}
E 5
I 5
D 12
all:	snake snscore
E 12
I 12
D 14
all: snake snscore
E 14
I 14
PROG=	snake
SRCS=	snake.c move.c
MAN6=	snake.0
DPADD=	${LIBM} ${LIBTERM} ${LIBCOMPAT}
LDADD=	-lm -ltermcap -lcompat
D 15
SUBDIR=	snscore
E 15
HIDEGAME=hidegame
E 14
E 12
E 5

I 15
.include "../../Makefile.inc"
E 15
D 5
snake:	$(OBJS)
	cc $(OBJS) -o snake $(LIBS)
E 5
I 5
D 12
snake:	${OBJS1} ${LIBC}
E 12
I 12
D 14
snake: ${OBJS1} ${LIBC}
E 12
D 13
	${CC} -o $@ ${CFLAGS} ${OBJS1} ${LIBS}
E 13
I 13
	${CC} -o $@ ${CFLAGS} ${OBJS1} -lm -ltermcap -lcompat
E 13
E 5

D 5
snake.o move.o:snake.h
E 5
I 5
snscore: ${OBJS2} ${LIBC}
	${CC} -o $@ ${CFLAGS} ${OBJS2}
E 5

D 5
snscore: snscore.c
	cc $(CFLAGS) snscore.c -o snscore
E 5
I 5
D 8
busy:	${OBJS3} ${LIBC}
	${CC} -o $@ ${CFLAGS} ${OBJS3}
E 5

E 8
D 5
busy:	busy.c
	cc $(CFLAGS) busy.c -o busy
E 5
I 5
D 12
clean: FRC
D 8
	rm -f ${OBJS1} ${OBJS2} ${OBJS3} core snake snscore busy
E 8
I 8
	rm -f ${OBJS1} ${OBJS2} core snake snscore busy
E 12
I 12
clean:
	rm -f ${OBJS1} ${OBJS2} core snake snscore
E 12
E 8
E 5

D 5
install: all
	install -s -m 4755 -o ${USER} snake ${BIN}/snake
	install -s -m 755 -o ${USER} snscore ${BIN}/snscore
#	install -s -m 755 -o ${USER} busy ${BIN}/busy
	cat /dev/null >> $(LIB)/snakerawscores
	chmod 644 $(LIB)/snakerawscores
	chown $(USER) $(LIB)/snakerawscores
E 5
I 5
D 12
depend: FRC
E 12
I 12
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 12
D 8
	mkdep ${CFLAGS} ${SRCS1} ${SRCS2} ${SRCS3}
E 8
I 8
	mkdep ${CFLAGS} ${SRCS1} ${SRCS2}
E 8
E 5

D 5
clean:
	rm -f *.o ${ALL}
E 5
I 5
D 12
install: FRC
E 12
I 12
install: ${MAN}
E 12
D 8
	install -s -o daemon -g bin -m 4755 snake ${DESTDIR}/usr/games/snake
	install -s -o daemon -g bin -m 755 snscore ${DESTDIR}/usr/games/snscore
	install -c -o daemon -g bin -m 644 /dev/null ${DESTDIR}/usr/games/lib/snakerawscores
#	install -s -o daemon -g bin -m 755 busy ${DESTDIR}/usr/games/busy
E 8
I 8
	install -s -o games -g bin -m 4700 snake ${DESTDIR}/usr/games/hide
	(cd ${DESTDIR}/usr/games; rm -f snake; ln -s dm snake; chown games.bin snake)
	install -s -o games -g bin -m 700 snscore ${DESTDIR}/usr/games/hide
	(cd ${DESTDIR}/usr/games; rm -f snscore; ln -s dm snscore; chown games.bin snscore)
D 10
	install -c -o games -g bin -m 600 /dev/null ${DESTDIR}/usr/games/lib/snakerawscores
E 10
I 10
	-[ -s ${DESTDIR}/usr/games/lib/snakerawscores ] || install -c -o games -g bin -m 600 /dev/null ${DESTDIR}/usr/games/lib/snakerawscores
I 12
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat6
E 12
E 10
E 8
E 5
I 3

D 5
depend:
E 5
I 5
D 12
lint: FRC
E 12
I 12
lint: ${SRCS}
E 12
	lint ${CFLAGS} ${SRCS1}
	lint ${CFLAGS} ${SRCS2}
D 8
	lint ${CFLAGS} ${SRCS3}
E 8

D 12
tags: FRC
E 12
I 12
tags: ${SRCS}
E 12
D 8
	ctags ${SRCS1} ${SRCS2} ${SRCS3}
E 8
I 8
	ctags ${SRCS1} ${SRCS2}
E 14
I 14
.include <bsd.prog.mk>
E 14
E 8
D 12

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

snake.o: snake.c snake.h /usr/include/stdio.h /usr/include/assert.h
snake.o: /usr/include/sys/types.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
snake.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
D 9
snake.o: /usr/include/signal.h /usr/include/math.h /usr/include/pwd.h
E 9
I 9
snake.o: /usr/include/signal.h /usr/include/machine/trap.h /usr/include/math.h
snake.o: /usr/include/pwd.h
E 9
move.o: move.c snake.h /usr/include/stdio.h /usr/include/assert.h
move.o: /usr/include/sys/types.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
move.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
D 9
move.o: /usr/include/signal.h /usr/include/math.h
E 9
I 9
move.o: /usr/include/signal.h /usr/include/machine/trap.h /usr/include/math.h
E 9
snscore.o: snscore.c /usr/include/stdio.h /usr/include/pwd.h
D 9
busy.o: busy.c /usr/include/stdio.h /usr/include/sys/types.h
busy.o: /usr/include/a.out.h /usr/include/sys/exec.h
E 9

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 12
E 5
E 3
E 1
