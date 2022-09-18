h42351
s 00023/00018/00024
d D 5.2 89/03/05 17:19:05 bostic 2 1
c add cleandir label, Berkeley copyright, cleanup
e
s 00042/00000/00000
d D 5.1 87/12/12 17:22:15 bostic 1 0
c date and time created 87/12/12 17:22:15 by bostic
e
u
U
t
T
I 1
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
I 2
#	%W% (Berkeley) %G%
#
E 2
CFLAGS=	-O
LIBC=	/lib/libc.a
SRCS=	btlgammon.c
OBJS=

all: btlgammon

btlgammon: ${OBJS} ${LIBC}
	${CC} -o $@ ${CFLAGS} ${SRCS}

D 2
clean: FRC
E 2
I 2
clean:
E 2
	rm -f ${OBJS} core btlgammon

D 2
depend: FRC
E 2
I 2
cleandir: ${MAN}
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 2
	mkdep -p ${CFLAGS} ${SRCS}

D 2
install: FRC
E 2
I 2
install: ${MAN}
E 2
	install -s -o games -g bin -m 4700 btlgammon ${DESTDIR}/usr/games/hide
	install -c -o games -g bin -m 444 backrules ${DESTDIR}/usr/games/lib
	(cd ${DESTDIR}/usr/games; rm -f btlgammon; ln -s dm btlgammon; chown games.bin btlgammon)

D 2
lint: FRC
E 2
I 2
lint: ${SRCS}
E 2
	lint ${CFLAGS} ${SRCS}

D 2
tags: FRC
E 2
I 2
tags: ${SRCS}
E 2
	ctags ${SRCS}
D 2

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

btlgammon: btlgammon.c /usr/include/stdio.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 2
E 1
