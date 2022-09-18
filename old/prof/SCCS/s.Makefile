h39311
s 00001/00001/00048
d D 4.5 89/05/10 22:29:04 bostic 5 4
c file reorg, pathnames.h, paths.h
e
s 00028/00023/00021
d D 4.4 88/10/25 16:20:52 bostic 4 3
c add man page, cleanup
e
s 00039/00013/00005
d D 4.3 87/06/18 22:39:52 bostic 3 2
c new template
e
s 00003/00001/00015
d D 4.2 87/05/31 21:32:00 bostic 2 1
c added depend label
e
s 00016/00000/00000
d D 4.1 83/06/02 16:53:27 sam 1 0
c date and time created 83/06/02 16:53:27 by sam
e
u
U
t
T
I 1
D 3
#	%W% (Berkeley) %G%
E 3
#
D 3
# If you don't want to plot, take out the -Dplot and the ref. to plot.a
PLOT = -lplot -Dplot
CFLAGS=-O 
prof:	prof.o
	$(CC) -o prof prof.o $(PLOT)
E 3
I 3
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
I 4
#	%W% (Berkeley) %G%
#
E 4
# If you don't want to plot, take out the -Dplot and the loader
# reference to plot.a
CFLAGS=	-O -Dplot
LIBC=	/lib/libc.a
SRCS=	prof.c
D 4
OBJS=	prof.o
E 4
I 4
OBJS=
MAN=	prof.0
E 4
E 3

D 3
prof.o: prof.c
	cc -c $(CFLAGS) $(PLOT) prof.c
E 3
I 3
all: prof
E 3

D 3
install:
	install -s prof $(DESTDIR)/usr/bin
E 3
I 3
D 4
prof: ${OBJS} ${LIBC}
	${CC} -o $@ ${CFLAGS} ${OBJS} -lplot
E 4
I 4
prof: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c -lplot
E 4
E 3

D 2
clean :
E 2
I 2
D 3
clean:
E 2
	rm -f *.o prof
E 3
I 3
D 4
clean: FRC
E 4
I 4
clean:
E 4
	rm -f ${OBJS} core prof
E 3
I 2

D 3
depend:
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

D 4
install: FRC
E 4
I 4
install: ${MAN}
E 4
D 5
	install -s -o bin -g bin -m 755 prof ${DESTDIR}/usr/bin/prof
E 5
I 5
	install -s -o bin -g bin -m 755 prof ${DESTDIR}/usr/bin
E 5
I 4
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
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
D 4

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

prof.o: prof.c /usr/include/stdio.h /usr/include/sys/types.h
prof.o: /usr/include/sys/stat.h /usr/include/a.out.h /usr/include/sys/exec.h
prof.o: /usr/include/sys/time.h /usr/include/time.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 4
E 3
E 2
E 1
