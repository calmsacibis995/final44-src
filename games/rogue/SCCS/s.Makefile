h01713
s 00000/00000/00013
d D 8.1 93/05/31 17:46:37 bostic 10 9
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00012
d D 5.9 92/08/27 13:41:52 elan 9 8
c got rid of 4.2 flag
e
s 00001/00001/00012
d D 5.8 92/07/29 12:22:20 bostic 8 7
c needs -fwritable-strings
e
s 00008/00047/00005
d D 5.7 90/05/11 12:46:23 bostic 7 6
c first pass for new make
e
s 00001/00001/00051
d D 5.6 89/07/30 13:05:22 bostic 6 5
c needs libcompat
e
s 00010/00082/00042
d D 5.5 88/10/19 21:58:54 bostic 5 4
c cleanup, add manual page
e
s 00010/00005/00114
d D 5.4 88/07/09 11:16:30 bostic 4 3
c install approved copyright notice
e
s 00005/00005/00114
d D 5.3 88/01/13 16:26:18 bostic 3 2
c it's rogue now, not pdrogue
e
s 00005/00005/00114
d D 5.2 87/12/01 18:02:48 bostic 2 1
c rename so won't conflict with KA's rogue
e
s 00119/00000/00000
d D 5.1 87/11/25 15:30:53 bostic 1 0
c from Tim Stoehr
e
u
U
t
T
I 1
D 7
#
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
D 4
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific written prior permission. This software
# is provided ``as is'' without express or implied warranty.
E 4
I 4
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
E 7
#	%W% (Berkeley) %G%
D 7
#
CFLAGS=	-O -DUNIX -DUNIX_BSD4_2
LIBC=	/lib/libc.a
E 7
I 7

PROG=	rogue
D 8
CFLAGS+=-DUNIX -DUNIX_BSD4_2
E 8
I 8
D 9
CFLAGS+=-DUNIX -DUNIX_BSD4_2 -fwritable-strings
E 9
I 9
CFLAGS+=-DUNIX -fwritable-strings
E 9
E 8
E 7
SRCS=	curses.c hit.c init.c inventory.c level.c machdep.c main.c \
	message.c monster.c move.c object.c pack.c play.c random.c ring.c \
	room.c save.c score.c spec_hit.c throw.c trap.c use.c zap.c
D 7
OBJS=	curses.o hit.o init.o inventory.o level.o machdep.o main.o \
	message.o monster.o move.o object.o pack.o play.o random.o ring.o \
	room.o save.o score.o spec_hit.o throw.o trap.o use.o zap.o
I 5
MAN=	rogue.0
E 7
I 7
DPADD=	${LIBCURSES} ${LIBTERM} ${LIBCOMPAT}
LDADD=	-lcurses -ltermlib -lcompat
HIDEGAME=hidegame
MAN6=	rogue.0
E 7
E 5

D 2
all: rogue
E 2
I 2
D 3
all: pdrogue
E 3
I 3
D 7
all: rogue
E 3
E 2

D 2
rogue: ${OBJS} ${LIBC}
E 2
I 2
D 3
pdrogue: ${OBJS} ${LIBC}
E 3
I 3
rogue: ${OBJS} ${LIBC}
E 3
E 2
D 6
	${CC} ${OBJS} -o $@ -lcurses -ltermlib
E 6
I 6
	${CC} ${OBJS} -o $@ -lcurses -ltermlib -lcompat
E 6

D 5
clean: FRC
E 5
I 5
clean:
E 5
D 2
	rm -f ${OBJS} core rogue
E 2
I 2
D 3
	rm -f ${OBJS} core pdrogue
E 3
I 3
	rm -f ${OBJS} core rogue
E 3
E 2

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
D 2
	install -s -o games -g bin -m 4700 rogue ${DESTDIR}/usr/games/hide
	(cd ${DESTDIR}/usr/games; rm -f rogue; ln -s dm rogue; chown games.bin rogue)
E 2
I 2
D 3
	install -s -o games -g bin -m 4700 pdrogue ${DESTDIR}/usr/games/hide
	(cd ${DESTDIR}/usr/games; rm -f pdrogue; ln -s dm pdrogue; chown games.bin pdrogue)
E 3
I 3
	install -s -o games -g bin -m 4700 rogue ${DESTDIR}/usr/games/hide
	(cd ${DESTDIR}/usr/games; rm -f rogue; ln -s dm rogue; chown games.bin rogue)
I 5
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat6
E 5
E 3
E 2

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

curses.o: curses.c
hit.o: hit.c rogue.h /usr/include/curses.h /usr/include/stdio.h
hit.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
hit.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
init.o: init.c /usr/include/stdio.h rogue.h /usr/include/curses.h
init.o: /usr/include/stdio.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
init.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
inventory.o: inventory.c rogue.h /usr/include/curses.h /usr/include/stdio.h
inventory.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
inventory.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
level.o: level.c rogue.h /usr/include/curses.h /usr/include/stdio.h
level.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
level.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
machdep.o: machdep.c /usr/include/stdio.h /usr/include/sys/types.h
machdep.o: /usr/include/sys/file.h /usr/include/sys/stat.h
machdep.o: /usr/include/sys/time.h /usr/include/time.h /usr/include/sgtty.h
machdep.o: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
machdep.o: /usr/include/sys/ttydev.h /usr/include/signal.h
machdep.o: /usr/include/machine/trap.h rogue.h /usr/include/curses.h
machdep.o: /usr/include/stdio.h /usr/include/sgtty.h
main.o: main.c rogue.h /usr/include/curses.h /usr/include/stdio.h
main.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
main.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
message.o: message.c /usr/include/stdio.h rogue.h /usr/include/curses.h
message.o: /usr/include/stdio.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
message.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
monster.o: monster.c rogue.h /usr/include/curses.h /usr/include/stdio.h
monster.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
monster.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
move.o: move.c rogue.h /usr/include/curses.h /usr/include/stdio.h
move.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
move.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
object.o: object.c rogue.h /usr/include/curses.h /usr/include/stdio.h
object.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
object.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
pack.o: pack.c rogue.h /usr/include/curses.h /usr/include/stdio.h
pack.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
pack.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
play.o: play.c rogue.h /usr/include/curses.h /usr/include/stdio.h
play.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
play.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
random.o: random.c
ring.o: ring.c rogue.h /usr/include/curses.h /usr/include/stdio.h
ring.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
ring.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
room.o: room.c rogue.h /usr/include/curses.h /usr/include/stdio.h
room.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
room.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
save.o: save.c /usr/include/stdio.h rogue.h /usr/include/curses.h
save.o: /usr/include/stdio.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
save.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
score.o: score.c /usr/include/stdio.h rogue.h /usr/include/curses.h
score.o: /usr/include/stdio.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
score.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
spec_hit.o: spec_hit.c rogue.h /usr/include/curses.h /usr/include/stdio.h
spec_hit.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
spec_hit.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
throw.o: throw.c rogue.h /usr/include/curses.h /usr/include/stdio.h
throw.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
throw.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
trap.o: trap.c rogue.h /usr/include/curses.h /usr/include/stdio.h
trap.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
trap.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
use.o: use.c rogue.h /usr/include/curses.h /usr/include/stdio.h
use.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
use.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
zap.o: zap.c rogue.h /usr/include/curses.h /usr/include/stdio.h
zap.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
zap.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 5
E 1
