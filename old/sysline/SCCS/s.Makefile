h33492
s 00006/00044/00003
d D 5.8 90/05/11 14:23:01 bostic 8 7
c first pass for new make
e
s 00001/00001/00046
d D 5.7 89/05/11 10:55:46 bostic 7 6
c file reorg, pathnames.h, paths.h
e
s 00011/00025/00036
d D 5.6 88/09/26 21:37:59 bostic 6 5
c update!
e
s 00010/00005/00051
d D 5.5 88/06/29 18:48:30 bostic 5 4
c install approved copyright notice
e
s 00025/00017/00031
d D 5.4 88/06/01 16:35:18 bostic 4 3
c add Berkeley specific header
e
s 00036/00016/00012
d D 5.3 87/06/16 19:10:15 bostic 3 2
c new template
e
s 00002/00000/00026
d D 5.2 87/05/31 21:18:29 bostic 2 1
c added depend label
e
s 00026/00000/00000
d D 5.1 85/06/06 12:39:48 mckusick 1 0
c date and time created 85/06/06 12:39:48 by mckusick
e
u
U
t
T
I 1
D 8
#
D 3
# Copyright (c) 1980 Regents of the University of California.
E 3
I 3
# Copyright (c) 1987 Regents of the University of California.
E 3
D 4
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 4
I 4
# All rights reserved.
E 4
#
D 3
#	%W% (Berkeley) %G%
E 3
I 3
D 4
#	%W%	(Berkeley)	%G%
E 4
I 4
# Redistribution and use in source and binary forms are permitted
D 5
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
# is provided ``as is'' without express or implied warranty.
E 5
I 5
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
E 5
E 4
E 3
#
E 8
I 4
#	%W% (Berkeley) %G%
D 8
#
E 4
D 3
#  See the sysline program source for options you may want to modify
#
DESTDIR =
E 3
I 3
CFLAGS=	-O
LIBC=	/lib/libc.a
SRCS=	sysline.c
D 4
OBJS=	sysline.o
E 4
I 4
OBJS=
I 6
MAN=	sysline.0
E 8
E 6
E 4
E 3

D 3
CFLAGS = -O
E 3
I 3
D 8
all: sysline
E 8
I 8
PROG=	sysline
DPADD=	${LIBTERMCAP} ${LIBCURSES} ${LIBUTIL}
LDADD=	-ltermcap -lcurses -lutil
BINGRP=	kmem
BINMODE=2555
E 8
E 3

D 3
.DEFAULT:sysline
E 3
I 3
D 4
sysline: ${OBJS} ${LIBC}
	${CC} ${CFLAGS} -o $@ ${OBJS} -ltermlib -lcurses
E 4
I 4
D 8
sysline: ${LIBC}
D 6
	${CC} ${CFLAGS} -o $@ sysline.c -ltermlib -lcurses
E 6
I 6
	${CC} ${CFLAGS} -o $@ $@.c -ltermlib -lcurses
E 6
E 4
E 3

D 3
sysline: sysline.c
	${CC} ${CFLAGS} -o sysline sysline.c -ltermlib -lcurses
E 3
I 3
D 6
clean: FRC
E 6
I 6
clean:
E 6
D 4
	rm -f ${OBJS} core sysline
E 4
I 4
	rm -f core sysline
E 4
E 3

D 3
nsysline: sysline.c
	${CC} ${CFLAGS} -DTERMINFO -o nsysline sysline.c -lncurses
E 3
I 3
D 6
depend: FRC
E 6
I 6
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 6
D 4
	mkdep ${CFLAGS} ${SRCS}
E 4
I 4
	mkdep -p ${CFLAGS} ${SRCS}
E 4
E 3

D 3
install: sysline
	install -s -g kmem -m 2755 sysline $(DESTDIR)/usr/ucb
E 3
I 3
D 6
install: FRC
E 6
I 6
install: ${MAN}
E 6
D 7
	install -s -o bin -g kmem -m 2755 sysline ${DESTDIR}/usr/ucb/sysline
E 7
I 7
	install -s -o bin -g kmem -m 2755 sysline ${DESTDIR}/usr/bin
E 7
I 6
	install -c -o bin -g bin -m 444 sysline.0 ${DESTDIR}/usr/man/cat1
E 6
E 3

D 3
clean:
	rm -f sysline
E 3
I 3
D 6
lint: FRC
E 6
I 6
lint: ${SRCS}
E 6
	lint ${CFLAGS} ${SRCS}
E 3
I 2

D 3
depend:
E 3
I 3
D 6
tags: FRC
E 6
I 6
tags: ${SRCS}
E 6
	ctags ${SRCS}
E 8
I 8
.include <bsd.prog.mk>
E 8
D 6

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

D 4
sysline.o: sysline.c /usr/include/stdio.h /usr/include/sys/param.h
sysline.o: /usr/include/sys/types.h /usr/include/signal.h
sysline.o: /usr/include/machine/machparam.h /usr/include/sys/signal.h
sysline.o: /usr/include/utmp.h /usr/include/ctype.h /usr/include/sys/time.h
sysline.o: /usr/include/time.h /usr/include/sys/stat.h /usr/include/nlist.h
sysline.o: /usr/include/sys/vtimes.h /usr/include/sys/proc.h
sysline.o: /usr/include/curses.h /usr/include/stdio.h /usr/include/sgtty.h
sysline.o: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
sysline.o: /usr/include/sys/ttydev.h /usr/include/protocols/rwhod.h
E 4
I 4
sysline: sysline.c /usr/include/stdio.h /usr/include/sys/param.h
sysline: /usr/include/sys/types.h /usr/include/signal.h
sysline: /usr/include/machine/trap.h /usr/include/machine/machparam.h
sysline: /usr/include/machine/endian.h /usr/include/sys/signal.h
sysline: /usr/include/utmp.h /usr/include/ctype.h /usr/include/sys/time.h
sysline: /usr/include/time.h /usr/include/sys/stat.h /usr/include/nlist.h
sysline: /usr/include/sys/vtimes.h /usr/include/sys/proc.h
sysline: /usr/include/curses.h /usr/include/stdio.h /usr/include/sgtty.h
sysline: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
sysline: /usr/include/sys/ttydefaults.h /usr/include/sys/ttydev.h
sysline: /usr/include/protocols/rwhod.h
E 4

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 6
E 3
E 2
E 1
