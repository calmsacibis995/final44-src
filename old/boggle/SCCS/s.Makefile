h41126
s 00000/00000/00023
d D 8.1 93/05/31 16:20:17 bostic 21 20
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00022
d D 5.16 92/03/16 14:19:22 bostic 20 19
c make man page, too
e
s 00003/00001/00020
d D 5.15 91/11/15 12:32:51 bostic 19 18
c add target for program
e
s 00001/00000/00020
d D 5.14 90/07/01 10:50:16 bostic 18 17
c clean comp, bogdict
e
s 00014/00046/00006
d D 5.13 90/05/11 12:47:17 bostic 17 16
c first pass for new make
e
s 00001/00001/00051
d D 5.12 89/07/30 12:26:48 bostic 16 15
c needs libcompat
e
s 00001/00001/00051
d D 5.11 89/05/11 13:48:46 bostic 15 14
c file reorg, pathnames.h, paths.h
e
s 00011/00022/00041
d D 5.10 88/10/19 16:42:26 bostic 14 13
c add manual page, cleanup
e
s 00015/00007/00048
d D 5.9 88/08/12 15:39:51 bostic 13 12
c don't use local libraries
e
s 00012/00016/00043
d D 5.8 87/12/01 17:57:54 bostic 12 11
c cleanup; make clean lable work
e
s 00003/00002/00056
d D 5.7 87/09/21 11:28:44 bostic 11 9
c integrate with dm
e
s 00005/00002/00056
d R 5.7 87/09/19 14:19:12 bostic 10 9
c integrate with dm
e
s 00041/00016/00017
d D 5.6 87/06/05 16:15:13 bostic 9 7
c new template
e
s 00042/00016/00017
d R 5.6 87/06/03 12:15:29 bostic 8 7
c new template
e
s 00002/00000/00031
d D 5.5 87/05/31 20:58:27 bostic 7 6
c added depend label
e
s 00001/00001/00030
d D 5.4 87/04/03 11:15:18 karels 6 5
c use *this* comp
e
s 00001/00001/00030
d D 5.3 85/09/07 21:03:32 mckusick 5 4
c strip on install
e
s 00001/00001/00030
d D 5.2 85/06/23 15:24:49 mckusick 4 3
c missing conditional
e
s 00006/00001/00025
d D 5.1 85/05/30 19:41:57 mckusick 3 2
c Add copyright
e
s 00004/00001/00022
d D 4.2 85/05/27 19:16:23 mckusick 2 1
c do not depend on having /usr/local/lib/w2a
e
s 00023/00000/00000
d D 4.1 82/12/24 13:07:54 sam 1 0
c date and time created 82/12/24 13:07:54 by sam
e
u
U
t
T
I 1
D 3
#	%W%	%G%
E 3
I 3
D 17
#
D 9
# Copyright (c) 1980 Regents of the University of California.
E 9
I 9
# Copyright (c) 1987 Regents of the University of California.
E 9
D 13
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 13
I 13
# All rights reserved.
E 13
#
D 9
#	%W% (Berkeley) %G%
E 9
I 9
D 13
#	%W%	(Berkeley)	%G%
E 13
I 13
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
E 13
E 9
E 3
#
E 17
I 13
#	%W% (Berkeley) %G%
D 17
#
E 13
D 9
DESTDIR=
CC = /bin/cc
CFLAGS = -O
E 9
I 9
CFLAGS=	-O
LIBC=	/lib/libc.a
SRCS=	comp.c boggle.c
I 14
MAN=	boggle.0
E 17
E 14
D 12
CSRCS=	comp.c
COBJS=	comp.o
BSRCS=	boggle.c
BOBJS=	boggle.o
E 12
E 9

D 9
all:	boggle bogdict
E 9
I 9
D 17
all: boggle bogdict
E 17
I 17
PROG=	boggle
MAN6=	boggle.0
DPADD=	${LIBCOMPAT}
LDADD=	-lcompat
HIDEGAME=hidegame
I 18
CLEANFILES=comp bogdict
E 18
E 17
E 9

D 17
bogdict: comp sfile
D 2
	sed -f sfile /usr/local/lib/w2a | uniq | comp >bogdict
E 2
I 2
D 4
	if [ -f /usr/local/lib/w2a ]; \
E 4
I 4
D 13
	-if [ -f /usr/local/lib/w2a ]; \
E 4
		then dict=/usr/local/lib/w2a; \
		else dict=/usr/dict/words; fi; \
D 6
	sed -f sfile $$dict | uniq | comp >bogdict
E 6
I 6
	sed -f sfile $$dict | uniq | ./comp >bogdict
E 13
I 13
D 15
	sed -f sfile /usr/dict/words | uniq | ./comp >bogdict
E 15
I 15
	sed -f sfile /usr/share/dict/words | uniq | ./comp >bogdict
E 17
I 17
D 19
all: bogdict
E 19
I 19
D 20
all: boggle
E 20
I 20
all: ${PROG} ${MAN6}
E 20

boggle: bogdict
E 19
E 17
E 15
E 13
E 6
E 2

D 9
install:
D 5
	install boggle ${DESTDIR}/usr/games/boggle
E 5
I 5
	install -s boggle ${DESTDIR}/usr/games/boggle
E 5
	install bogdict ${DESTDIR}/usr/games/bogdict
E 9
I 9
D 12
boggle:	${BOBJS} ${LIBC}
	${CC} -o $@ ${CFLAGS} ${BOBJS}
E 12
I 12
D 14
boggle: ${LIBC}
E 14
I 14
D 17
boggle comp: ${LIBC}
E 14
D 16
	${CC} -o $@ ${CFLAGS} $@.c
E 16
I 16
	${CC} -o $@ ${CFLAGS} $@.c -lcompat
E 17
I 17
bogdict: /usr/share/dict/words comp sfile
	sed -f ${.CURDIR}/sfile /usr/share/dict/words | uniq | ./comp >bogdict
E 17
E 16
E 12
E 9

D 9
boggle: boggle.c
	cc -o boggle ${CFLAGS} boggle.c
E 9
I 9
D 12
comp:	${COBJS} ${LIBC}
	${CC} -o $@ ${CFLAGS} ${COBJS}
E 12
I 12
D 14
comp: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c
E 12
E 9

D 9
comp: comp.c
	cc -o comp ${CFLAGS} comp.c
E 9
I 9
clean: FRC
E 14
I 14
D 17
clean:
E 14
	rm -f ${OBJS} core comp boggle bogdict
E 17
I 17
beforeinstall:
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 bogdict \
	    ${DESTDIR}/usr/share/games
comp:
	${CC} -O ${.CURDIR}/comp.c -o ${.TARGET}
E 17
E 9

D 9
clean:
	rm -f bogdict boggle comp
E 9
I 9
D 14
depend: FRC
E 14
I 14
D 17
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 14
D 12
	mkdep ${CFLAGS} ${SRCS}
E 12
I 12
	mkdep -p ${CFLAGS} ${SRCS}
E 12
E 9
I 7

D 9
depend:
E 9
I 9
D 14
install: FRC
E 14
I 14
install: ${MAN}
E 14
D 11
	install -s -o bin -g bin -m 755 boggle ${DESTDIR}/usr/games/boggle
	install -o bin -g bin -m 444 bogdict ${DESTDIR}/usr/games/bogdict
E 11
I 11
	install -s -o games -g bin -m 4700 boggle ${DESTDIR}/usr/games/hide/boggle
	install -o games -g bin -m 400 bogdict ${DESTDIR}/usr/games/lib/bogdict
	(cd ${DESTDIR}/usr/games; rm -f boggle; ln -s dm boggle; chown games.bin boggle)
I 14
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat6
E 14
E 11

D 14
lint: FRC
E 14
I 14
lint: ${SRCS}
E 14
D 12
	lint ${CFLAGS} ${CSRCS}
	lint ${CFLAGS} ${BSRCS}
E 12
I 12
	lint ${CFLAGS} comp.c
	lint ${CFLAGS} boggle.c
E 12

D 14
tags: FRC
E 14
I 14
tags: ${SRCS}
E 14
	ctags ${SRCS}
E 17
I 17
.include <bsd.prog.mk>
E 17
D 14

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

D 12
comp.o: comp.c /usr/include/stdio.h
boggle.o: boggle.c /usr/include/ctype.h /usr/include/errno.h
boggle.o: /usr/include/setjmp.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
boggle.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
boggle.o: /usr/include/signal.h /usr/include/stdio.h
E 12
I 12
comp: comp.c /usr/include/stdio.h
boggle: boggle.c /usr/include/ctype.h /usr/include/errno.h
boggle: /usr/include/setjmp.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
boggle: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
boggle: /usr/include/signal.h /usr/include/machine/trap.h /usr/include/stdio.h
E 12

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 14
E 9
E 7
E 1
