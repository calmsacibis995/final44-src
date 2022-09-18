h09803
s 00000/00000/00009
d D 8.1 93/05/31 16:52:14 bostic 10 9
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00004/00008
d D 5.9 93/04/27 16:05:02 bostic 9 8
c getloadavg(3) is no longer privileged, dm no longer needs libutil
e
s 00002/00002/00010
d D 5.8 92/06/16 20:30:07 bostic 8 7
c kvm is a separate library now
e
s 00001/00002/00011
d D 5.7 90/09/30 17:59:54 bostic 7 6
c no need for links anymore
e
s 00002/00002/00011
d D 5.6 90/06/26 10:32:55 bostic 6 5
c cleanup, make documentation match program, move config files into /etc
e
s 00009/00046/00004
d D 5.5 90/05/11 12:48:09 bostic 5 4
c first pass for new make
e
s 00011/00019/00039
d D 5.4 88/09/29 14:34:11 bostic 4 3
c cleanup, add manual pages
e
s 00010/00005/00048
d D 5.3 88/06/18 14:47:02 bostic 3 2
c install approved copyright notice
e
s 00011/00011/00042
d D 5.2 87/12/29 17:29:47 bostic 2 1
c don't use intermediate .o
e
s 00053/00000/00000
d D 5.1 87/11/30 16:17:23 bostic 1 0
c date and time created 87/11/30 16:17:23 by bostic
e
u
U
t
T
I 1
D 5
#
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
D 3
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific written prior permission. This software
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
#
E 5
#	%W% (Berkeley) %G%
D 5
#
# -DLOG		log games in /usr/adm
CFLAGS=	-O
LIBC=	/lib/libc.a
SRCS=	dm.c
D 2
OBJS=	dm.o
E 2
I 2
OBJS=
I 4
MAN=	dm.0 dm.config.0
E 5
E 4
E 2

D 5
all: dm
E 5
I 5
# -DLOG		log games
PROG=	dm
MAN8=	dm.0
D 6
MAN5=	dm.config.0
E 6
I 6
D 7
MAN5=	dmconf.0
MLINKS=	dmconf.5 dm.5
E 7
I 7
MAN5=	dm.conf.0
E 7
E 6
D 9
BINGRP=	kmem
BINMODE=6555
D 8
DPADD=	${LIBUTIL}
LDADD=	-lutil
E 8
I 8
DPADD=	${LIBUTIL} ${LIBKVM}
LDADD=	-lutil -lkvm
E 9
I 9
BINMODE=4555
E 9
E 8
E 5

D 2
dm: ${OBJS} ${LIBC}
	${CC} -o $@ ${CFLAGS} ${OBJS}
E 2
I 2
D 5
dm: ${LIBC}
	${CC} -o $@ ${CFLAGS} dm.c
E 5
I 5
.include <bsd.prog.mk>
E 5
E 2
D 6

E 6
D 4
clean: FRC
E 4
I 4
D 5
clean:
E 4
D 2
	rm -f ${OBJS} core dm
E 2
I 2
	rm -f core dm
E 2

D 4
depend: FRC
E 4
I 4
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 4
D 2
	mkdep ${CFLAGS} ${SRCS}
E 2
I 2
	mkdep -p ${CFLAGS} ${SRCS}
E 2

D 4
install: FRC
E 4
I 4
install: ${MAN}
E 4
	install -s -o games -g kmem -m 6755 dm ${DESTDIR}/usr/games
#	install -c -o games -g bin -m 444 dm.config ${DESTDIR}/usr/games
I 4
	install -c -o bin -g bin -m 444 dm.0 ${DESTDIR}/usr/man/cat8
	install -c -o bin -g bin -m 444 dm.config.0 ${DESTDIR}/usr/man/cat5
E 4

D 4
lint: FRC
E 4
I 4
lint: ${SRCS}
E 4
	lint ${CFLAGS} ${SRCS}

D 4
tags: FRC
E 4
I 4
tags: ${SRCS}
E 4
	ctags ${SRCS}
E 5
D 4

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

D 2
dm.o: dm.c /usr/include/sys/param.h /usr/include/sys/types.h
dm.o: /usr/include/signal.h /usr/include/machine/trap.h
dm.o: /usr/include/machine/machparam.h /usr/include/sys/file.h
dm.o: /usr/include/sys/time.h /usr/include/time.h /usr/include/sys/resource.h
dm.o: /usr/include/pwd.h /usr/include/utmp.h /usr/include/nlist.h
dm.o: /usr/include/stdio.h /usr/include/ctype.h
E 2
I 2
dm: dm.c /usr/include/sys/param.h /usr/include/sys/types.h
dm: /usr/include/signal.h /usr/include/machine/trap.h
dm: /usr/include/machine/machparam.h /usr/include/sys/file.h
dm: /usr/include/sys/time.h /usr/include/time.h /usr/include/sys/resource.h
dm: /usr/include/pwd.h /usr/include/utmp.h /usr/include/nlist.h
dm: /usr/include/stdio.h /usr/include/ctype.h
E 2

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 4
E 1
