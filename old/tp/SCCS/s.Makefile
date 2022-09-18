h47270
s 00005/00045/00003
d D 4.6 90/07/04 20:12:10 bostic 6 5
c pmake makefile
e
s 00004/00003/00044
d D 4.5 89/05/11 13:50:55 bostic 5 4
c file reorg, pathnames.h, paths.h
e
s 00026/00025/00021
d D 4.4 88/10/25 15:28:32 bostic 4 3
c add man page, cleanup
e
s 00040/00012/00006
d D 4.3 87/06/02 23:41:34 bostic 3 2
c new template
e
s 00002/00000/00016
d D 4.2 87/05/31 20:34:10 bostic 2 1
c added depend label
e
s 00016/00000/00000
d D 4.1 82/12/18 15:14:10 sam 1 0
c date and time created 82/12/18 15:14:10 by sam
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
D 6
#
D 4
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 4
I 4
# Copyright (c) 1987 The Regents of the University of California.
# All rights reserved.
E 4
#
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
# WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
#
E 6
I 4
#	%W% (Berkeley) %G%
D 6
#
E 4
CFLAGS=	-O
LIBC=	/lib/libc.a
E 6
I 6

PROG=	tp
E 6
SRCS=	tp0.c tp1.c tp2.c tp3.c
D 6
OBJS=	tp0.o tp1.o tp2.o tp3.o
I 4
D 5
MAN=	tp.0
E 5
I 5
MAN=	tp.0 tp5.0
E 6
I 6
MAN1=	tp.0
MAN5=	tp5.0
E 6
E 5
E 4
E 3

D 3
CFLAGS=-O
h = tp.h tp_defs.h
o  = tp0.o tp1.o tp2.o tp3.o
E 3
I 3
D 6
all: tp
E 3

D 3
tp :	$o
	$(CC) -o tp $o
E 3
I 3
D 4
tp:	${OBJS} ${LIBC}
E 4
I 4
tp: ${OBJS} ${LIBC}
E 4
	${CC} -o $@ ${CFLAGS} ${OBJS}
E 3

D 3
$o :	$h
E 3
I 3
D 4
clean: FRC
E 4
I 4
clean:
E 4
	rm -f ${OBJS} core tp
E 3

D 3
install : tp
	install -s tp ${DESTDIR}/bin
E 3
I 3
D 4
depend: FRC
E 4
I 4
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 4
	mkdep ${CFLAGS} ${SRCS}
E 3

D 3
clean : 
	rm -f *.o
E 3
I 3
D 4
install: FRC
E 4
I 4
install: ${MAN}
E 4
D 5
	install -s -o bin -g bin -m 755 tp ${DESTDIR}/bin/tp
I 4
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
E 5
I 5
	install -s -o bin -g bin -m 755 tp ${DESTDIR}/usr/ucb
	install -c -o bin -g bin -m 444 tp.0 ${DESTDIR}/usr/man/cat1
	install -c -o bin -g bin -m 444 tp5.0 ${DESTDIR}/usr/man/cat5/tp.0
E 5
E 4
E 3
I 2

D 3
depend:
E 3
I 3
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
E 6
I 6
.include <bsd.prog.mk>
E 6
D 4

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

tp0.o: tp0.c tp.h tp_defs.h
tp1.o: tp1.c tp.h
tp2.o: tp2.c tp.h /usr/include/stdio.h /usr/include/sys/param.h
tp2.o: /usr/include/sys/types.h /usr/include/signal.h
tp2.o: /usr/include/machine/machparam.h /usr/include/sys/stat.h
tp2.o: /usr/include/sys/dir.h
tp3.o: tp3.c tp.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 4
E 3
E 2
E 1
