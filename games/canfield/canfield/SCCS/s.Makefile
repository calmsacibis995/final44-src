h14240
s 00000/00000/00011
d D 8.1 93/05/31 16:22:30 bostic 8 7
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00001/00009
d D 5.7 91/04/08 08:35:39 bostic 7 6
c use subdirectories
e
s 00007/00054/00003
d D 5.6 90/05/11 12:46:41 bostic 6 5
c first pass for new make
e
s 00001/00001/00056
d D 5.5 89/07/30 12:28:45 bostic 5 4
c needs libcompat
e
s 00012/00019/00045
d D 5.4 88/10/19 16:47:30 bostic 4 3
c add manual pages, cleanup
e
s 00010/00005/00054
d D 5.3 88/06/18 19:49:11 bostic 3 2
c install approved copyright notice
e
s 00011/00005/00048
d D 5.2 88/05/06 10:36:34 bostic 2 1
c add Berkeley header
e
s 00053/00000/00000
d D 5.1 87/12/12 17:21:52 bostic 1 0
c date and time created 87/12/12 17:21:52 by bostic
e
u
U
t
T
I 1
D 6
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
D 3
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
# is provided ``as is'' without express or implied warranty.
E 3
I 3
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
E 3
E 2
#
E 6
I 2
#	%W% (Berkeley) %G%
D 6
#
E 2
CFLAGS=	-O
LIBC=	/lib/libc.a
CSRCS=	canfield.c
CFSRCS=	cfscores.c
I 4
MAN=	canfield.0
E 6
E 4

D 6
all: canfield cfscores
E 6
I 6
PROG=	canfield
MAN6=	canfield.0
DPADD=	${LIBCURSES} ${LIBTERM} ${LIBCOMPAT}
LDADD=	-lcurses -ltermcap -lcompat
D 7
SUBDIR=	cfscores
E 7
HIDEGAME=hidegame
E 6

I 7

.include "../../Makefile.inc"
E 7
D 6
canfield: ${LIBC}
D 5
	${CC} -o $@ ${CFLAGS} ${CSRCS} -lcurses -ltermcap
E 5
I 5
	${CC} -o $@ ${CFLAGS} ${CSRCS} -lcurses -ltermcap -lcompat
E 5

cfscores: ${LIBC}
	${CC} -o $@ ${CFLAGS} ${CFSRCS}

D 4
clean: FRC
E 4
I 4
clean:
E 4
	rm -f core canfield cfscores

D 4
depend: FRC
E 4
I 4
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 4
	mkdep -p ${CFLAGS} ${CSRCS} ${CFSRCS}

D 4
install: FRC
E 4
I 4
install: ${MAN}
E 4
	install -s -o games -g bin -m 700 canfield ${DESTDIR}/usr/games/hide
	install -s -o games -g bin -m 700 cfscores ${DESTDIR}/usr/games/hide
	(cd ${DESTDIR}/usr/games; rm -f canfield; ln -s dm canfield; chown games.bin canfield)
	(cd ${DESTDIR}/usr/games; rm -f cfscores; ln -s dm cfscores; chown games.bin cfscores)
	-[ -f ${DESTDIR}/usr/games/lib/cfscores ] || install -c -o games -g bin -m 600 /dev/null ${DESTDIR}/usr/games/lib/cfscores
I 4
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat6
	rm -f ${DESTDIR}/usr/man/cat6/cfscores.0
	ln ${DESTDIR}/usr/man/cat6/canfield.0 ${DESTDIR}/usr/man/cat6/cfscores.0
E 4

D 4
lint: FRC
E 4
I 4
lint: ${SRCS}
E 4
	lint ${CFLAGS} ${CSRCS}
	lint ${CFLAGS} ${CFSRCS}

D 4
tags: FRC
E 4
I 4
tags: ${SRCS}
E 4
	ctags ${CSRCS} ${CFSRCS}
E 6
I 6
.include <bsd.prog.mk>
E 6
D 4

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

canfield: canfield.c /usr/include/curses.h /usr/include/stdio.h
canfield: /usr/include/sgtty.h /usr/include/sys/ioctl.h
D 2
canfield: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
canfield: /usr/include/ctype.h /usr/include/signal.h
E 2
I 2
canfield: /usr/include/sys/ttychars.h /usr/include/sys/ttydefaults.h
canfield: /usr/include/sys/ttydev.h /usr/include/ctype.h /usr/include/signal.h
E 2
canfield: /usr/include/machine/trap.h /usr/include/sys/types.h
cfscores: cfscores.c /usr/include/pwd.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 4
E 1
