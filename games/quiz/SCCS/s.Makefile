h29998
s 00000/00000/00016
d D 8.1 93/05/31 17:44:04 bostic 13 12
c 4.4BSD snapshot (revision 8.1)
e
s 00003/00003/00013
d D 5.2 92/08/27 11:42:48 bostic 12 11
c add flowers
e
s 00001/00000/00015
d D 5.1 91/11/10 14:24:24 bostic 11 10
c Jim Oldroyd's version of quiz
e
s 00008/00049/00007
d D 4.8 90/05/11 12:47:34 bostic 10 9
c first pass for new make
e
s 00005/00001/00051
d D 4.7 89/04/11 09:57:27 bostic 9 8
c do quiz categories explicitly
e
s 00026/00020/00026
d D 4.6 88/10/20 11:46:31 bostic 8 7
c add manual page, cleanup
e
s 00001/00001/00045
d D 4.5 87/09/22 10:46:17 bostic 7 6
c fix mkdir
e
s 00012/00007/00034
d D 4.4 87/09/21 11:55:01 bostic 6 3
c integrate with dm
e
s 00014/00007/00034
d R 4.4 87/09/20 10:47:40 bostic 5 3
c integrate with dm
e
s 00031/00031/00010
d D 4.3 87/06/03 16:47:25 bostic 3 2
c new template
e
s 00001/00001/00040
d D 4.2 85/09/07 21:10:40 mckusick 2 1
c strip on install
e
s 00041/00000/00000
d D 4.1 82/11/28 18:24:30 mckusick 1 0
c date and time created 82/11/28 18:24:30 by mckusick
e
u
U
t
T
I 3
D 10
#
D 8
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 8
I 8
# Copyright (c) 1987 The Regents of the University of California.
# All rights reserved.
E 8
#
E 3
I 1
D 8
#	%W%	(Berkeley)	%G%
E 8
I 8
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
E 8
#
E 10
I 8
#	%W% (Berkeley) %G%
D 10
#
E 8
D 3
DESTDIR=
E 3
CFLAGS=	-O
I 3
LIBC=	/lib/libc.a
SRCS=	quiz.c
D 6
OBJS=	quiz.o
E 6
I 6
OBJS=
I 8
MAN=	quiz.0
E 10
I 10

PROG=	quiz
MAN6=	quiz.0
I 11
SRCS=	quiz.c rxp.c
E 11
E 10
I 9
CATS=	africa america areas arith asia babies bard chinese collectives \
D 12
	ed elements europe greek inca index latin locomotive midearth morse \
	murders poetry posneg pres province seq-easy seq-hard sexes sov \
	spell state trek ucc
E 12
I 12
	ed elements europe flowers greek inca index latin locomotive \
	midearth morse murders poetry posneg pres province seq-easy seq-hard \
	sexes sov spell state trek ucc
E 12
I 10
HIDEGAME=hidegame
E 10
E 9
E 8
E 6
E 3

D 3
quiz: quiz.c
	cc ${CFLAGS} -o quiz quiz.c
E 3
I 3
D 10
all: quiz
E 10
I 10
beforeinstall:
	(cd ${.CURDIR}/datfiles; install -c -o ${BINOWN} -g ${BINGRP} -m 444 \
	    ${CATS} ${DESTDIR}/usr/share/games/quiz.db)
E 10
E 3

D 3
install:
D 2
	install quiz ${DESTDIR}/usr/games/quiz
E 2
I 2
	install -s quiz ${DESTDIR}/usr/games/quiz
E 3
I 3
D 6
quiz:	${OBJS} ${LIBC}
	${CC} -o $@ ${CFLAGS} ${OBJS}
E 6
I 6
D 10
quiz: ${LIBC}
D 8
	${CC} -o $@ ${CFLAGS} ${SRCS}
E 8
I 8
	${CC} -o $@ ${CFLAGS} $@.c
E 8
E 6

D 8
clean: FRC
E 8
I 8
clean:
E 8
	rm -f ${OBJS} core quiz

D 8
depend: FRC
E 8
I 8
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 8
D 6
	mkdep ${CFLAGS} ${SRCS}
E 6
I 6
	mkdep -p ${CFLAGS} ${SRCS}
E 6

D 8
install: FRC
E 8
I 8
install: ${MAN}
E 8
D 6
	install -s -o bin -g bin -m 755 quiz ${DESTDIR}/usr/games/quiz
E 3
E 2
	cp -r quiz.k ${DESTDIR}/usr/games/lib
E 6
I 6
D 7
	-mkdir ${DESTDIR}/usr/games/lib/quiz.k > /dev/null 2>&1
E 7
I 7
	-[ -d ${DESTDIR}/usr/games/lib/quiz.k ] || mkdir ${DESTDIR}/usr/games/lib/quiz.k
E 7
	chmod 700 ${DESTDIR}/usr/games/lib/quiz.k
	chown games.bin ${DESTDIR}/usr/games/lib/quiz.k
D 9
	cd quiz.k; install -c -o games -g bin -m 400 * ${DESTDIR}/usr/games/lib/quiz.k
E 9
I 9
	cd quiz.k; install -c -o games -g bin -m 400 ${CATS} ${DESTDIR}/usr/games/lib/quiz.k
E 9
	install -s -o games -g bin -m 700 quiz ${DESTDIR}/usr/games/hide
	(cd ${DESTDIR}/usr/games; rm -f quiz; ln -s dm quiz; chown games.bin quiz)
I 8
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat6
E 8
E 6

D 3
clean:
	rm -f a.out core *.s *.o quiz
E 3
I 3
D 8
lint: FRC
E 8
I 8
lint: ${SRCS}
E 8
	lint ${CFLAGS} ${SRCS}
E 3

D 3
depend:
	cat </dev/null >x.c
	for i in quiz; do \
		(echo $$i: $$i.c >>makedep; \
		/bin/grep '^#[ 	]*include' x.c $$i.c | sed \
			-e 's,<\(.*\)>,"/usr/include/\1",' \
			-e 's/:[^"]*"\([^"]*\)".*/: \1/' \
			-e 's/\.c//' >>makedep); done
	echo '/^# DO NOT DELETE THIS LINE/+2,$$d' >eddep
	echo '$$r makedep' >>eddep
	echo 'w' >>eddep
	cp Makefile Makefile.bak
	ed - Makefile < eddep
	rm eddep makedep x.c
	echo '# DEPENDENCIES MUST END AT END OF FILE' >> Makefile
	echo '# IF YOU PUT STUFF HERE IT WILL GO AWAY' >> Makefile
	echo '# see make depend above' >> Makefile
E 3
I 3
D 8
tags: FRC
E 8
I 8
tags: ${SRCS}
E 8
	ctags ${SRCS}
E 10
I 10
.include <bsd.prog.mk>
E 10
E 3
D 8

D 3
# DO NOT DELETE THIS LINE -- make depend uses it
E 3
I 3
FRC:
E 3

D 3
quiz: quiz.c
quiz: /usr/include/stdio.h
quiz: /usr/include/signal.h
# DEPENDENCIES MUST END AT END OF FILE
# IF YOU PUT STUFF HERE IT WILL GO AWAY
# see make depend above
E 3
I 3
# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

D 6
quiz.o: quiz.c /usr/include/stdio.h /usr/include/signal.h
E 6
I 6
quiz: quiz.c /usr/include/stdio.h /usr/include/signal.h
quiz: /usr/include/machine/trap.h
E 6

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 8
E 3
E 1
