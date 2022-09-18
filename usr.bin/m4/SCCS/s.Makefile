h44342
s 00000/00000/00010
d D 8.1 93/06/06 15:04:44 bostic 11 10
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00000/00008
d D 5.9 91/09/03 11:45:04 bostic 10 9
c add SCCS header
e
s 00003/00005/00005
d D 5.8 91/09/03 11:37:52 bostic 9 7
c New version from Oz Yigit; BSD-ized
e
s 00001/00000/00010
d D 5.7.1.1 91/05/08 13:12:24 bostic 8 7
c branch for the 2nd network distribution
e
s 00006/00051/00004
d D 5.7 90/05/11 13:49:56 bostic 7 6
c first pass for new make
e
s 00016/00008/00039
d D 5.6 89/08/28 15:51:05 bostic 6 5
c Makefile for new version from Ozan Yigit
e
s 00001/00001/00046
d D 5.5 89/05/10 22:28:31 bostic 5 4
c file reorg, pathnames.h, paths.h
e
s 00025/00019/00022
d D 5.4 88/10/25 15:46:25 bostic 4 3
c add man page, cleanup
e
s 00037/00009/00004
d D 5.3 87/06/18 19:37:07 bostic 3 2
c new template
e
s 00002/00000/00011
d D 5.2 87/05/31 21:30:40 bostic 2 1
c added depend label
e
s 00011/00000/00000
d D 5.1 82/12/15 23:19:37 clemc 1 0
c date and time created 82/12/15 23:19:37 by clemc
e
u
U
f b 
t
Virgin BTL M4 as sent out in 4.1
T
I 10
#	%W% (Berkeley) %G%

E 10
I 7
D 9
#	%W% (Berkeley) %G%
E 7
I 1
D 3
# %W% (Berkeley) %G%
E 3
I 3
#
D 4
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 4
I 4
D 6
# Copyright (c) 1987 The Regents of the University of California.
E 6
I 6
D 7
# Copyright (c) 1989 The Regents of the University of California.
E 6
# All rights reserved.
E 4
#
I 6
# This code is derived from software contributed to Berkeley by
# Ozan Yigit.
#
E 6
D 4
#	%W%	(Berkeley)	%G%
E 4
I 4
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
D 6
# WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 6
I 6
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 6
E 4
#
I 4
D 6
#	%W% (Berkeley) %G%
E 6
I 6
#	@(#)Makefile	5.2 (Berkeley) 8/28/89
E 6
#
E 4
D 6
CFLAGS=	-O
E 6
I 6

#
E 7
#	-DEXTENDED 
D 7
#		if you like to get paste & spaste macros.
#
CFLAGS=	-O -DEXTENDED
E 6
LIBC=	/lib/libc.a
E 7
I 7
#		if you want the paste & spaste macros.
E 9
I 9
# -DEXTENDED 
# 	if you want the paste & spaste macros.
E 9

PROG=	m4
CFLAGS+=-DEXTENDED
E 7
D 6
SRCS=	m4.c m4y.c
OBJS=	m4.o m4y.o
E 6
I 6
D 9
SRCS =  main.c eval.c serv.c look.c misc.c expr.c
E 9
I 9
SRCS=	eval.c expr.c look.c main.c misc.c
E 9
I 8
NOMAN=	noman
E 8
D 7
OBJS =  main.o eval.o serv.o look.o misc.o expr.o
E 6
I 4
MAN=	m4.0
E 7
E 4
E 3

D 3
CFLAGS=-O
m4:	m4.o m4y.o
	$(CC) -o m4 m4.o m4y.o 
E 3
I 3
D 7
all: m4
E 3

D 3
install:
	install -s m4 $(DESTDIR)/usr/bin
E 3
I 3
m4: ${OBJS} ${LIBC}
	${CC} -o $@ ${CFLAGS} ${OBJS}
E 3

D 3
clean:
	rm -f *.o
E 3
I 3
D 4
clean: FRC
E 4
I 4
clean:
E 4
D 6
	rm -f ${OBJS} core m4 m4y.c
E 6
I 6
	rm -f ${OBJS} core m4
E 6
E 3
I 2

D 3
depend:
E 3
I 3
D 4
depend: ${SRCS} FRC
E 4
I 4
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 4
	mkdep ${CFLAGS} ${SRCS}

D 4
install: FRC
E 4
I 4
install: ${MAN}
E 4
D 5
	install -s -o bin -g bin -m 755 m4 ${DESTDIR}/usr/bin/m4
E 5
I 5
D 6
	install -s -o bin -g bin -m 755 m4 ${DESTDIR}/usr/bin
E 6
I 6
	install -s -o bin -g bin -m 755 m4 ${DESTDIR}/usr/bin/m4
E 6
E 5
I 4
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
E 4

D 4
lint: ${SRCS} FRC
E 4
I 4
lint: ${SRCS}
E 4
	lint ${CFLAGS} ${SRCS}

D 4
tags: ${SRCS} FRC
E 4
I 4
tags: ${SRCS}
E 4
	ctags ${SRCS}
E 7
I 7
.include <bsd.prog.mk>
E 7
D 4

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

m4.o: m4.c /usr/include/stdio.h /usr/include/signal.h
m4y.o: m4y.c

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 4
E 3
E 2
E 1
