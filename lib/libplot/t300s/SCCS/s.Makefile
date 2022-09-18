h24842
s 00000/00000/00007
d D 8.1 93/06/04 17:51:18 bostic 7 6
c 4.4BSD snapshot (revision 8.1)
e
s 00004/00058/00003
d D 4.5 90/05/11 12:52:48 bostic 6 5
c first pass for new make
e
s 00055/00005/00006
d D 4.4 87/06/19 16:40:42 bostic 5 4
c new tempalte
e
s 00002/00002/00009
d D 4.3 83/09/21 18:55:14 sam 4 2
c wrong library name
e
s 00001/00001/00010
d R 4.3 83/09/21 18:52:23 sam 3 2
c wrong library name
e
s 00002/00002/00009
d D 4.2 83/07/09 23:44:23 sam 2 1
c name change
e
s 00011/00000/00000
d D 4.1 83/06/27 14:16:37 sam 1 0
c date and time created 83/06/27 14:16:37 by sam
e
u
U
t
T
I 1
D 5
#	%M%	%I%	%E%
E 5
D 6
#
I 5
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
#	%W%	(Berkeley)	%G%
#
E 5
CFLAGS=	-O
I 5
LIBC=	/lib/libc.a
E 6
I 6
#	%W% (Berkeley) %G%

LIB=	300s
E 6
SRCS=	arc.c box.c circle.c close.c dot.c erase.c label.c \
	line.c linmod.c move.c open.c point.c space.c subr.c
E 5
D 6
OBJS=	arc.o box.o circle.o close.o dot.o erase.o label.o \
	line.o linmod.o move.o open.o point.o space.o subr.o
E 6

D 2
../libt300s.a:	${OBJS}
	ar cu ../libt300s.a ${OBJS}
E 2
I 2
D 4
../libt300s:	${OBJS}
	ar cu ../libt300s ${OBJS}
E 4
I 4
D 5
../lib300s:	${OBJS}
	ar cu ../lib300s ${OBJS}
E 5
I 5
D 6
all: ../lib300s
E 5
E 4
E 2

D 5
clean:
	rm -f ${OBJS} errs a.out core
E 5
I 5
../lib300s: ${OBJS}
	ar cu $@ ${OBJS}

clean: FRC
	rm -f ${OBJS} core

depend: FRC
	mkdep ${CFLAGS} ${SRCS}

lint: FRC
	lint ${CFLAGS} ${SRCS}

tags: FRC
	ctags ${SRCS}

install:
FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

arc.o: arc.c
box.o: box.c
circle.o: circle.c
close.o: close.c /usr/include/stdio.h
dot.o: dot.c
erase.o: erase.c con.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
erase.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
label.o: label.c con.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
label.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
line.o: line.c con.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
line.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
linmod.o: linmod.c
move.o: move.c
open.o: open.c /usr/include/sgtty.h /usr/include/sys/ioctl.h
open.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
point.o: point.c con.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
point.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
space.o: space.c con.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
space.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
subr.o: subr.c /usr/include/stdio.h con.h /usr/include/sgtty.h
subr.o: /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
subr.o: /usr/include/sys/ttydev.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 6
I 6
.include <bsd.lib.mk>
E 6
E 5
E 1
