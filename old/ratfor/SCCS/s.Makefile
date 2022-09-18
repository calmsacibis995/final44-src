h25666
s 00000/00000/00008
d D 8.1 93/06/06 16:08:54 bostic 9 8
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00002/00007
d D 5.8 91/01/19 19:07:28 bostic 8 7
c fix from bsd.prog.mk
e
s 00002/00002/00007
d D 5.7 90/06/26 11:45:43 bostic 7 6
c cleanup
e
s 00006/00045/00003
d D 5.6 90/06/22 19:11:53 bostic 6 5
c pmake makefile
e
s 00001/00001/00047
d D 5.5 89/05/10 22:29:57 bostic 5 4
c file reorg, pathnames.h, paths.h
e
s 00026/00025/00022
d D 5.4 88/10/25 16:14:04 bostic 4 3
c add manual page, cleanup
e
s 00042/00019/00005
d D 5.3 87/06/18 22:46:05 bostic 3 2
c new template
e
s 00001/00000/00023
d D 5.2 87/05/31 21:32:14 bostic 2 1
c added depend label
e
s 00023/00000/00000
d D 5.1 82/12/15 21:49:57 clemc 1 0
c date and time created 82/12/15 21:49:57 by clemc
e
u
U
t
T
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
YFLAGS=	-d
LIBC=	/lib/libc.a
SRCS=	r.c r0.c r1.c r2.c rio.c rlook.c rlex.c
OBJS=	r.o r0.o r1.o r2.o rio.o rlook.o rlex.o
I 4
MAN=	ratfor.0
E 6
E 4
E 3
I 1

D 3
#	%W% (Berkeley) %G%
E 3
I 3
D 6
all: ratfor
E 6
I 6
PROG=	ratfor
D 7
YFLAGS+=-d
E 7
D 8
SRCS=	r0.c r1.c r2.c rio.c rlook.c rlex.c
E 8
I 8
SRCS=	r.c r0.c r1.c r2.c rio.c rlook.c rlex.c
E 8
I 7
CFLAGS+=-I.
E 7
D 8
OBJS+=	r.c
E 8
D 7
CLEANFILES=r.c y.tab.h
E 7
I 7
CLEANFILES=r.c r.o y.tab.h
E 7
E 6
E 3

D 3
CFLAGS = -O
E 3
I 3
D 4
ratfor:	${OBJS} ${LIBC}
E 4
I 4
D 6
ratfor: ${OBJS} ${LIBC}
E 4
	${CC} -o $@ ${CFLAGS} ${OBJS}
E 3

D 3
ratfor:	r0.o r1.o r2.o rio.o rlook.o rlex.o y.tab.o
	cc r*.o y.tab.o -o ratfor
E 3
I 3
D 4
clean: FRC
E 4
I 4
clean:
E 4
	rm -f ${OBJS} core ratfor r.c
E 3

D 3
r0.o:	r.h y.tab.h r0.c
r1.o:	r.h y.tab.h r1.c
r2.o:	r.h y.tab.h r2.c
rio.o:	r.h y.tab.h rio.c
rlook.o:	r.h y.tab.h rlook.c
rlex.o:	r.h y.tab.h rlex.c
y.tab.c:	r.g
	yacc -d r.g
y.tab.h:	r.g
	yacc -d r.g
install: ratfor
	install -s ratfor $(DESTDIR)/usr/bin
clean:
	rm -f y.tab.c *.o ratfor y.tab.h
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
E 3

I 2
D 3
depend:
E 3
I 3
D 4
install: FRC
E 4
I 4
install: ${MAN}
E 4
D 5
	install -s -o bin -g bin -m 755 ratfor ${DESTDIR}/usr/bin/ratfor
E 5
I 5
	install -s -o bin -g bin -m 755 ratfor ${DESTDIR}/usr/bin
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
E 6
I 6
.include <bsd.prog.mk>
E 6
D 4

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

r.o: r.c
r0.o: r0.c r.h /usr/include/stdio.h y.tab.h
r1.o: r1.c r.h /usr/include/stdio.h y.tab.h
r2.o: r2.c r.h /usr/include/stdio.h y.tab.h
rio.o: rio.c r.h /usr/include/stdio.h y.tab.h
rlook.o: rlook.c
rlex.o: rlex.c r.h /usr/include/stdio.h y.tab.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 4
E 3
E 2
E 1
