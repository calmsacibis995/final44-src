h12822
s 00000/00000/00005
d D 8.1 93/06/06 14:30:30 bostic 13 12
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00044/00003
d D 5.8 90/05/11 15:16:48 bostic 12 11
c first pass for new make
e
s 00001/00001/00046
d D 5.7 89/05/11 09:42:49 bostic 11 10
c file reorg, pathnames.h, paths.h
e
s 00027/00021/00020
d D 5.6 88/10/22 16:46:29 bostic 10 9
c cleanup, add man page
e
s 00004/00003/00037
d D 5.5 87/07/14 11:57:59 bostic 9 8
c dc.h isn't an OBJECT
e
s 00032/00011/00008
d D 5.4 87/06/18 15:01:02 bostic 8 5
c new template
e
s 00032/00011/00008
d R 5.3 87/06/18 14:59:39 bostic 7 5
c new template
e
s 00031/00010/00009
d R 5.2 87/06/18 14:58:44 bostic 6 5
c new template
e
s 00002/00000/00017
d D 5.1 87/05/31 21:27:36 bostic 5 4
c added depend label
e
s 00002/00002/00015
d D 1.4 83/06/30 14:06:26 sam 4 3
c from sun
e
s 00007/00008/00010
d D 1.3 83/03/30 11:49:38 sam 3 2
c close to what sun sent up
e
s 00001/00000/00017
d D 1.2 83/02/11 16:08:48 rrh 2 1
c Define DESTDIR
e
s 00017/00000/00000
d D 1.1 83/02/11 15:02:06 rrh 1 0
c date and time created 83/02/11 15:02:06 by rrh
e
u
U
t
T
I 1
D 12
#
D 8
#	%W%	(Berkeley)	%E%
E 8
I 8
D 10
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 10
I 10
# Copyright (c) 1988 The Regents of the University of California.
# All rights reserved.
E 10
E 8
#
I 2
D 8
DESTDIR=
E 2
D 3
SRCS = dc.c dc.h
E 3
I 3
SRCS=	dc.c dc.h
CFLAGS=	-O
E 8
I 8
D 10
#	%W%	(Berkeley)	%G%
E 10
I 10
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
E 10
#
E 12
I 10
#	%W% (Berkeley) %G%
D 12
#
E 10
CFLAGS=	-O -I.
LIBC=	/lib/libc.a
SRCS=	dc.c
D 9
OBJS=	dc.h
E 9
I 9
OBJS=
I 10
MAN=	dc.0
E 12
E 10
E 9
E 8

E 3
D 12
all: dc
E 12
I 12
PROG=	dc
E 12

D 8
dc:	dc.c dc.h
D 3
	cc -O dc.c -o dc
E 3
I 3
	${CC} ${CFLAGS} dc.c -o dc
E 8
I 8
D 9
dc:	dc.c ${LIBC}
E 9
I 9
D 10
dc: dc.c ${LIBC}
E 9
	${CC} ${CFLAGS} dc.c -o $@
E 10
I 10
D 12
dc: ${LIBC}
	${CC} ${CFLAGS} -o $@ $@.c
E 10
E 8
E 3

D 3
install: dc
	install -s dc $(DESTDIR)/usr/bin
E 3
I 3
D 4
install:
E 4
I 4
D 8
install: dc
E 4
	install -s dc ${DESTDIR}/usr/bin/dc
E 8
I 8
D 10
clean: FRC
E 10
I 10
clean:
E 10
	rm -f ${OBJS} core dc
E 8

E 3
D 8
clean:
D 4
	rm -f *.o
E 4
I 4
	rm -f *.o dc a.out errs core
E 8
I 8
D 10
depend: FRC
E 10
I 10
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 10
	mkdep -p ${CFLAGS} ${SRCS}
E 8
I 5

D 8
depend:
E 8
I 8
D 10
install: FRC
E 10
I 10
install: ${MAN}
E 10
D 11
	install -s -o bin -g bin -m 755 dc ${DESTDIR}/usr/bin/dc
E 11
I 11
	install -s -o bin -g bin -m 755 dc ${DESTDIR}/usr/bin
E 11
I 10
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
E 10

D 10
lint: FRC
E 10
I 10
lint: ${SRCS}
E 10
	lint ${CFLAGS} ${SRCS}

D 10
tags: FRC
E 10
I 10
tags: ${SRCS}
E 10
	ctags ${SRCS}
E 12
I 12
.include <bsd.prog.mk>
E 12
D 10

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

D 9
dc: dc.c /usr/include/stdio.h /usr/include/signal.h dc.h
E 9
I 9
dc: dc.c /usr/include/stdio.h /usr/include/signal.h /usr/include/machine/trap.h
dc: dc.h
E 9

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 10
E 8
E 5
E 4
D 3

sources: srcs
srcs: $(SRCS)
	sccs get $@
E 3
E 1
