h60401
s 00000/00000/00017
d D 8.1 93/05/31 17:58:25 bostic 15 14
c 4.4BSD snapshot (revision 8.1)
e
s 00008/00053/00009
d D 5.8 90/05/11 12:48:03 bostic 14 13
c first pass for new make
e
s 00001/00002/00061
d D 5.7 89/07/30 13:13:54 bostic 13 12
c needs libcompat
e
s 00010/00066/00053
d D 5.6 88/10/20 11:26:54 bostic 12 11
c add manual page, cleanup
e
s 00010/00005/00109
d D 5.5 88/06/18 15:06:58 bostic 11 10
c install approved copyright notice
e
s 00010/00004/00104
d D 5.4 88/05/05 18:33:01 bostic 10 9
c written by Eric Allman; add Berkeley header
e
s 00002/00001/00106
d D 5.3 87/09/21 12:00:06 bostic 9 7
c integrate with dm
e
s 00004/00001/00106
d R 5.3 87/09/20 11:08:03 bostic 8 7
c integrate with dm
e
s 00075/00149/00032
d D 5.2 87/06/03 17:22:32 bostic 7 6
c new template
e
s 00006/00001/00175
d D 5.1 85/05/30 08:47:13 dist 6 5
c Add copyright
e
s 00008/00021/00168
d D 4.5 83/07/04 12:38:37 sam 5 4
c cleanup and make sure it goes in /usr/games
e
s 00001/00001/00188
d D 4.4 83/05/27 15:06:40 layer 4 3
c typo
e
s 00011/00000/00178
d D 4.3 83/05/27 15:04:49 layer 3 2
c make depend for new files
e
s 00004/00004/00174
d D 4.2 83/05/27 00:35:21 layer 2 1
c finished conversion to 4.1c
e
s 00178/00000/00000
d D 4.1 83/03/25 10:41:00 mckusick 1 0
c date and time created 83/03/25 10:41:00 by mckusick
e
u
U
t
T
I 1
D 5
#	%W%	(Berkeley)	%E%
E 5
I 5
D 6
#	%M%	%I%	%E%
E 6
I 6
D 14
#
D 7
# Copyright (c) 1980 Regents of the University of California.
E 7
I 7
# Copyright (c) 1987 Regents of the University of California.
E 7
D 10
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 10
I 10
# All rights reserved.
E 10
#
D 7
#	%W% (Berkeley) %G%
E 7
I 7
D 10
#	%W%	(Berkeley)	%G%
E 10
I 10
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
E 10
E 7
E 6
E 5
#
E 14
I 10
#	%W% (Berkeley) %G%
D 14
#
E 10
D 7
DESTDIR=
E 7
D 2
CFLAGS=	-O
E 2
I 2
D 5
CFLAGS=	# -O
E 5
I 5
CFLAGS=	-O
E 5
E 2
D 7
LFLAGS=	
E 7
I 7
LIBC=	/lib/libc.a
E 14
I 14

PROG=	trek
E 14
D 13
LIBS=	-lm
E 13
E 7
D 5

# The program itself
#
PROG=	trek

# Sources
#
E 5
SRCS=	abandon.c attack.c autover.c capture.c check_out.c checkcond.c \
	compkl.c computer.c damage.c damaged.c dcrept.c destruct.c \
	dock.c dumpgame.c dumpme.c dumpssradio.c events.c externs.c \
	getcodi.c getpar.c help.c impulse.c initquad.c kill.c klmove.c \
	lose.c lrscan.c main.c move.c nova.c out.c phaser.c play.c ram.c \
D 14
	ranf.c rest.c schedule.c score.c setup.c setwarp.c shell.c \
E 14
I 14
	ranf.c rest.c schedule.c score.c setup.c setwarp.c \
E 14
	shield.c snova.c srscan.c systemname.c torped.c utility.c \
D 2
	visual.c warp.c win.c
E 2
I 2
	visual.c warp.c win.c cgetc.c
E 2
D 5

# Objects
#
E 5
D 14
OBJS=	abandon.o attack.o autover.o capture.o check_out.o checkcond.o \
	compkl.o computer.o damage.o damaged.o dcrept.o destruct.o \
	dock.o dumpgame.o dumpme.o dumpssradio.o events.o externs.o \
	getcodi.o getpar.o help.o impulse.o initquad.o kill.o klmove.o \
	lose.o lrscan.o main.o move.o nova.o out.o phaser.o play.o ram.o \
	ranf.o rest.o schedule.o score.o setup.o setwarp.o shell.o \
	shield.o snova.o srscan.o systemname.o torped.o utility.o \
D 2
	visual.o warp.o win.o
E 2
I 2
	visual.o warp.o win.o cgetc.o
I 12
MAN=	trek.0
E 14
I 14
MAN6=	trek.0
DPADD=	${LIBM} ${LIBCOMPAT}
LDADD=	-lm -lcompat
HIDEGAME=hidegame
E 14
E 12
E 2
D 5

# Header files
#
E 5
D 7
HDRS=	getpar.h trek.h
E 7

D 5
${PROG}: ${OBJS} ${HDRS}
D 2
	cc ${LFLAGS} -o ${PROG} ${OBJS}
E 2
I 2
	cc ${LFLAGS} -o ${PROG} ${OBJS} -lm
E 5
I 5
D 7
trek: 	${OBJS} ${HDRS}
	cc ${LFLAGS} -o trek ${OBJS} -lm
E 7
I 7
D 14
all: trek
E 7
E 5
E 2

D 7
${OBJS}:
D 5
	cc ${CFLAGS} -c $*.c
E 5
I 5
	${CC} ${CFLAGS} -c $*.c
E 7
I 7
D 10
trek: 	${OBJS} ${LIBC}
E 10
I 10
trek: ${OBJS} ${LIBC}
E 10
D 13
	${CC} ${CFLAGS} -o $@ ${OBJS} ${LIBS}
E 13
I 13
	${CC} ${CFLAGS} -o $@ ${OBJS} -lm -lcompat
E 13
E 7
E 5

I 3
D 4
tags:	./tags $(SRCS)
E 4
I 4
D 7
tags:	tags $(SRCS)
E 4
	ctags $(SRCS)
E 7
I 7
D 12
clean: FRC
E 12
I 12
clean:
E 12
	rm -f ${OBJS} core trek
E 7

E 3
D 5
install: ${PROG}
	install ${PROG} ${DESTDIR}/usr/local/${PROG}
E 5
I 5
D 7
install: trek
	install -s trek ${DESTDIR}/usr/games/trek
E 7
I 7
D 12
depend: FRC
E 12
I 12
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 12
	mkdep ${CFLAGS} ${SRCS}
E 7
E 5

D 7
clean:
D 5
	rm -f a.out core ${OBJS} ${PROG}
E 5
I 5
	rm -f a.out core ${OBJS} trek
E 7
I 7
D 12
install: FRC
E 12
I 12
install: ${MAN}
E 12
D 9
	install -s -o bin -g bin -m 755 trek ${DESTDIR}/usr/games/trek
E 9
I 9
	install -s -o games -g bin -m 700 trek ${DESTDIR}/usr/games/hide
	(cd ${DESTDIR}/usr/games; rm -f trek; ln -s dm trek; chown games.bin trek)
I 12
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat6
E 12
E 9
E 7
E 5

D 7
depend:
	cat </dev/null >x.c
	for i in ${SRCS}; do \
		(echo `basename $$i .c`.o: $$i >>makedep; \
		/bin/grep '^#[ 	]*include' x.c $$i | sed \
			-e 's,<\(.*\)>,"/usr/include/\1",' \
			-e 's/:[^"]*"\([^"]*\)".*/: \1/' \
			-e 's/\.c/.o/' >>makedep); done
	echo '/^# DO NOT DELETE THIS LINE/+2,$$d' >eddep
	echo '$$r makedep' >>eddep
	echo 'w' >>eddep
	cp Makefile Makefile.bak
	ed - Makefile < eddep
	rm eddep makedep x.c
	echo '# DEPENDENCIES MUST END AT END OF FILE' >> Makefile
	echo '# IF YOU PUT STUFF HERE IT WILL GO AWAY' >> Makefile
	echo '# see make depend above' >> Makefile
E 7
I 7
D 12
lint: FRC
E 12
I 12
lint: ${SRCS}
E 12
	lint ${CFLAGS} ${SRCS}
E 7

D 7
# DO NOT DELETE THIS LINE -- make depend uses it
E 7
I 7
D 12
tags: FRC
E 12
I 12
tags: ${SRCS}
E 12
	ctags ${SRCS}
E 14
I 14
.include <bsd.prog.mk>
E 14
E 7
D 12

D 7
abandon.o: abandon.c
abandon.o: trek.h
attack.o: attack.c
attack.o: trek.h
autover.o: autover.c
autover.o: trek.h
capture.o: capture.c
capture.o: trek.h
check_out.o: check_out.c
check_out.o: trek.h
checkcond.o: checkcond.c
checkcond.o: trek.h
compkl.o: compkl.c
compkl.o: trek.h
computer.o: computer.c
computer.o: trek.h
computer.o: getpar.h
I 3
computer.o: /usr/include/stdio.h
E 3
damage.o: damage.c
damage.o: trek.h
damaged.o: damaged.c
damaged.o: trek.h
dcrept.o: dcrept.c
dcrept.o: trek.h
destruct.o: destruct.c
destruct.o: trek.h
dock.o: dock.c
dock.o: trek.h
dumpgame.o: dumpgame.c
dumpgame.o: trek.h
dumpme.o: dumpme.c
dumpme.o: trek.h
dumpssradio.o: dumpssradio.c
dumpssradio.o: trek.h
events.o: events.c
events.o: trek.h
externs.o: externs.c
externs.o: trek.h
getcodi.o: getcodi.c
getcodi.o: getpar.h
getpar.o: getpar.c
I 3
getpar.o: /usr/include/stdio.h
E 3
getpar.o: getpar.h
help.o: help.c
help.o: trek.h
impulse.o: impulse.c
impulse.o: trek.h
initquad.o: initquad.c
initquad.o: trek.h
kill.o: kill.c
kill.o: trek.h
klmove.o: klmove.c
klmove.o: trek.h
lose.o: lose.c
lose.o: trek.h
lrscan.o: lrscan.c
lrscan.o: trek.h
main.o: main.c
main.o: trek.h
I 3
main.o: /usr/include/stdio.h
main.o: /usr/include/sgtty.h
E 3
move.o: move.c
move.o: trek.h
nova.o: nova.c
nova.o: trek.h
out.o: out.c
out.o: trek.h
phaser.o: phaser.c
phaser.o: trek.h
phaser.o: getpar.h
play.o: play.c
play.o: trek.h
play.o: getpar.h
ram.o: ram.c
ram.o: trek.h
ranf.o: ranf.c
I 3
ranf.o: /usr/include/stdio.h
E 3
rest.o: rest.c
rest.o: trek.h
rest.o: getpar.h
schedule.o: schedule.c
schedule.o: trek.h
score.o: score.c
score.o: trek.h
score.o: getpar.h
setup.o: setup.c
setup.o: trek.h
setup.o: getpar.h
setwarp.o: setwarp.c
setwarp.o: trek.h
setwarp.o: getpar.h
E 7
I 7
FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

abandon.o: abandon.c trek.h
attack.o: attack.c trek.h
autover.o: autover.c trek.h
capture.o: capture.c trek.h
check_out.o: check_out.c trek.h
checkcond.o: checkcond.c trek.h
compkl.o: compkl.c trek.h
computer.o: computer.c trek.h getpar.h /usr/include/stdio.h
damage.o: damage.c trek.h
damaged.o: damaged.c trek.h
dcrept.o: dcrept.c trek.h
destruct.o: destruct.c trek.h
dock.o: dock.c trek.h
dumpgame.o: dumpgame.c trek.h
dumpme.o: dumpme.c trek.h
dumpssradio.o: dumpssradio.c trek.h
events.o: events.c trek.h
externs.o: externs.c trek.h
getcodi.o: getcodi.c getpar.h
getpar.o: getpar.c /usr/include/stdio.h getpar.h
help.o: help.c trek.h
impulse.o: impulse.c trek.h
initquad.o: initquad.c trek.h
kill.o: kill.c trek.h
klmove.o: klmove.c trek.h
lose.o: lose.c trek.h
lrscan.o: lrscan.c trek.h
main.o: main.c trek.h /usr/include/stdio.h /usr/include/sgtty.h
main.o: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
main.o: /usr/include/sys/ttydev.h
move.o: move.c trek.h
nova.o: nova.c trek.h
out.o: out.c trek.h
phaser.o: phaser.c trek.h getpar.h
play.o: play.c trek.h getpar.h
ram.o: ram.c trek.h
ranf.o: ranf.c /usr/include/stdio.h
rest.o: rest.c trek.h getpar.h
schedule.o: schedule.c trek.h
score.o: score.c trek.h getpar.h
setup.o: setup.c trek.h getpar.h
setwarp.o: setwarp.c trek.h getpar.h
E 7
shell.o: shell.c
D 7
shield.o: shield.c
shield.o: trek.h
shield.o: getpar.h
snova.o: snova.c
snova.o: trek.h
srscan.o: srscan.c
srscan.o: trek.h
srscan.o: getpar.h
systemname.o: systemname.c
systemname.o: trek.h
torped.o: torped.c
I 3
torped.o: /usr/include/stdio.h
E 3
torped.o: trek.h
E 7
I 7
shield.o: shield.c trek.h getpar.h
snova.o: snova.c trek.h
srscan.o: srscan.c trek.h getpar.h
systemname.o: systemname.c trek.h
torped.o: torped.c /usr/include/stdio.h trek.h
E 7
utility.o: utility.c
D 7
visual.o: visual.c
visual.o: trek.h
warp.o: warp.c
warp.o: trek.h
win.o: win.c
win.o: trek.h
win.o: getpar.h
I 3
cgetc.o: cgetc.c
cgetc.o: /usr/include/stdio.h
E 3
# DEPENDENCIES MUST END AT END OF FILE
# IF YOU PUT STUFF HERE IT WILL GO AWAY
# see make depend above
E 7
I 7
visual.o: visual.c trek.h
warp.o: warp.c trek.h
win.o: win.c trek.h getpar.h
cgetc.o: cgetc.c /usr/include/stdio.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 12
E 7
E 1
