h43980
s 00002/00002/00005
d D 8.2 95/04/28 12:47:56 bostic 11 10
c msgs Makefile does not need -lcompat
e
s 00000/00000/00007
d D 8.1 93/06/06 15:39:18 bostic 10 9
c 4.4BSD snapshot (revision 8.1)
e
s 00004/00044/00003
d D 5.8 90/05/11 14:28:18 bostic 9 8
c first pass for new make
e
s 00001/00001/00046
d D 5.7 89/07/30 14:20:45 bostic 8 7
c needs libcompat
e
s 00001/00001/00046
d D 5.6 89/05/11 10:02:16 bostic 7 6
c file reorg, pathnames.h, paths.h
e
s 00003/00003/00044
d D 5.5 89/03/06 12:24:45 bostic 6 5
c typo...
e
s 00027/00027/00020
d D 5.4 88/10/25 16:15:39 bostic 5 4
c add man page, cleanup
e
s 00040/00015/00007
d D 5.3 87/06/16 18:35:23 bostic 4 3
c new template
e
s 00003/00000/00019
d D 5.2 87/05/31 21:12:12 bostic 3 2
c added depend label
e
s 00006/00001/00013
d D 5.1 85/06/04 15:28:16 dist 2 1
c Add copyright
e
s 00014/00000/00000
d D 4.1 82/05/19 10:14:28 rrh 1 0
c date and time created 82/05/19 10:14:28 by rrh
e
u
U
t
T
I 1
D 9
#
D 2
#	%W% %G%
E 2
I 2
D 4
# Copyright (c) 1980 Regents of the University of California.
E 4
I 4
D 5
# Copyright (c) 1987 Regents of the University of California.
E 4
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 5
I 5
# Copyright (c) 1987 The Regents of the University of California.
# All rights reserved.
E 5
#
D 4
#	%W% (Berkeley) %G%
E 4
I 4
D 5
#	%W%	(Berkeley)	%G%
E 5
I 5
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
E 5
E 4
#
E 9
I 5
#	%W% (Berkeley) %G%
D 9
#
E 5
E 2
D 4
#
CFLAGS=-O
SRCS = msgs.c msgs.h Makefile
msgs: msgs.c msgs.h
	cc $(CFLAGS) -o msgs msgs.c -ltermlib
install:
	install -s msgs ${DESTDIR}/usr/ucb
clean:
	-rm -f msgs
E 4
I 4
CFLAGS=	-O
LIBC=	/lib/libc.a
SRCS=	msgs.c
D 5
OBJS=	msgs.o
E 5
I 5
OBJS=
MAN=	msgs.0
E 9
E 5
E 4
I 3

D 4
depend:
E 4
I 4
D 9
all: msgs
E 9
I 9
PROG=	msgs
D 11
DPADD=	${LIBTERM} ${LIBCOMPAT}
LDADD=	-ltermlib -lcompat
E 11
I 11
DPADD=	${LIBTERM}
LDADD=	-ltermlib
E 11
E 9
E 4

E 3
D 4
sources: $(SRCS)
$(SRCS):
	sccs get $@
E 4
I 4
D 5
msgs:	${OBJS} ${LIBC}
E 5
I 5
D 6
msgs: ${OBJS} ${LIBC}
E 5
	${CC} -o $@ ${CFLAGS} ${OBJS} -ltermlib
E 6
I 6
D 9
msgs: ${LIBC}
D 8
	${CC} -o $@ ${CFLAGS} msgs.c -ltermlib
E 8
I 8
	${CC} -o $@ ${CFLAGS} msgs.c -ltermlib -lcompat
E 8
E 6

D 5
clean: FRC
E 5
I 5
clean:
E 5
	rm -f ${OBJS} core msgs

D 5
depend: FRC
E 5
I 5
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 5
D 6
	mkdep ${CFLAGS} ${SRCS}
E 6
I 6
	mkdep -p ${CFLAGS} ${SRCS}
E 6

D 5
install: FRC
E 5
I 5
install: ${MAN}
E 5
D 7
	install -s -o bin -g bin -m 755 msgs ${DESTDIR}/usr/ucb/msgs
E 7
I 7
	install -s -o bin -g bin -m 755 msgs ${DESTDIR}/usr/bin
E 7
I 5
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
E 5

D 5
lint: FRC
E 5
I 5
lint: ${SRCS}
E 5
	lint ${CFLAGS} ${SRCS}

D 5
tags: FRC
E 5
I 5
tags: ${SRCS}
E 5
	ctags ${SRCS}
E 9
I 9
.include <bsd.prog.mk>
E 9
D 5

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

msgs.o: msgs.c /usr/include/stdio.h /usr/include/sys/param.h
msgs.o: /usr/include/sys/types.h /usr/include/signal.h
msgs.o: /usr/include/machine/machparam.h /usr/include/signal.h
msgs.o: /usr/include/sys/dir.h /usr/include/sys/stat.h /usr/include/ctype.h
msgs.o: /usr/include/pwd.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
msgs.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
msgs.o: /usr/include/setjmp.h
msgs.o:msgs.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 5
E 4
E 1
