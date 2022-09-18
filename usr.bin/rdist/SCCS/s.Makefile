h21762
s 00000/00000/00014
d D 8.3 93/07/19 09:51:02 bostic 23 22
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00000/00013
d D 8.2 93/07/19 09:51:00 bostic 22 21
c set the immutable bit on installation
e
s 00000/00000/00013
d D 8.1 93/06/09 22:49:34 bostic 21 20
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00000/00011
d D 5.11 91/03/12 08:53:45 bostic 20 19
c re_exec, re_comp moved to -lcompat
e
s 00001/00000/00010
d D 5.10 90/06/24 11:17:49 bostic 19 18
c clean y.tab.h
e
s 00007/00045/00003
d D 5.9 90/05/11 15:21:37 bostic 18 17
c first pass for new make
e
s 00001/00001/00047
d D 5.8 89/05/11 09:37:50 bostic 17 16
c file reorg, pathnames.h, paths.h
e
s 00001/00001/00047
d D 5.7 89/03/14 12:00:16 bostic 16 15
c create pathnames.h
e
s 00010/00061/00038
d D 5.6 88/09/20 17:18:10 bostic 15 14
c add cleandir, man pages, cleanup
e
s 00010/00005/00089
d D 5.5 88/06/29 20:19:23 bostic 14 13
c install approved copyright notice
e
s 00014/00008/00080
d D 5.4 88/02/01 11:34:35 bostic 13 12
c add new Berkeley headers
e
s 00073/00017/00015
d D 5.3 87/06/16 18:39:42 bostic 12 11
c new template
e
s 00002/00000/00030
d D 5.2 87/05/31 21:13:15 bostic 11 10
c added depend label
e
s 00007/00002/00023
d D 5.1 85/06/06 08:55:19 dist 10 9
c Add copyright
e
s 00001/00001/00024
d D 4.9 85/06/01 13:30:12 edward 9 8
c install with -s
e
s 00001/00001/00024
d D 4.8 85/02/28 14:40:48 ralph 8 7
c moved rdist to /usr/ucb
e
s 00003/00002/00022
d D 4.7 84/12/06 14:55:27 ralph 7 6
c make location of rdist definable (for testing).
e
s 00001/00001/00023
d D 4.6 83/11/30 15:20:48 ralph 6 5
c fix install dependency
e
s 00001/00001/00023
d D 4.5 83/10/28 13:19:17 ralph 5 4
c fixed install line
e
s 00001/00001/00023
d D 4.4 83/10/26 14:23:23 ralph 4 3
c changed to cc -O files
e
s 00001/00001/00023
d D 4.3 83/10/10 16:15:02 ralph 3 2
c stable version that works.
e
s 00005/00005/00019
d D 4.2 83/09/27 14:38:16 ralph 2 1
c First stable version.
e
s 00024/00000/00000
d D 4.1 83/09/07 13:19:10 ralph 1 0
c date and time created 83/09/07 13:19:10 by ralph
e
u
U
t
T
I 1
D 2
#	%M%	%I%	%E%
E 2
I 2
D 3
#	Makefile	4.1	83/09/07
E 3
I 3
D 10
#	%M%	%I%	%E%
E 3
E 2

E 10
I 10
D 18
#
D 12
# Copyright (c) 1983 Regents of the University of California.
E 12
I 12
# Copyright (c) 1987 Regents of the University of California.
E 12
D 13
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 13
I 13
# All rights reserved.
E 13
#
D 12
#	%W% (Berkeley) %G%
E 12
I 12
D 13
#	%W%	(Berkeley)	%G%
E 13
I 13
# Redistribution and use in source and binary forms are permitted
D 14
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
# is provided ``as is'' without express or implied warranty.
E 14
I 14
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
E 14
E 13
E 12
#
E 18
I 13
#	%W% (Berkeley) %G%
D 18
#
E 13
I 12
LIBC=	/lib/libc.a
E 12
E 10
I 7
D 8
RDIST = /usr/local/rdist
E 8
I 8
D 13
RDIST = /usr/ucb/rdist
E 8
E 7
D 12
DESTDIR=
E 12
I 12
CFLAGS= -O -DRDIST=\"${RDIST}\"
E 12
D 2
SRCS =	main.c gram.y docmd.c expand.c server.c
OBJS =	main.o gram.o docmd.o expand.o server.o
E 2
I 2
SRCS =	docmd.c expand.c gram.y lookup.c main.c server.c
OBJS =	docmd.o expand.o gram.o lookup.o main.o server.o
E 13
I 13
D 17
RDIST=	/usr/ucb/rdist
E 17
I 17
RDIST=	/usr/bin/rdist
E 17
D 16
CFLAGS=	-O -DRDIST=\"${RDIST}\"
E 16
I 16
CFLAGS=	-g
E 16
SRCS=	docmd.c expand.c gram.y lookup.c main.c server.c
OBJS=	docmd.o expand.o gram.o lookup.o main.o server.o
I 15
MAN=	rdist.0
E 18
E 15
E 13
E 2
D 12
LINT =	lint -ps
D 4
CFLAGS=
E 4
I 4
D 7
CFLAGS= -O
E 7
I 7
CFLAGS= -O -DRDIST=\"${RDIST}\"
E 12
E 7
E 4

D 12
rdist:	${OBJS}
	${CC} -o rdist ${OBJS}
E 12
I 12
D 18
all: rdist
E 18
I 18
PROG=	rdist
CFLAGS+=-I${.CURDIR}
SRCS=	docmd.c expand.c lookup.c main.c server.c
OBJS+=	gram.o
BINOWN=	root
BINMODE=4555
I 22
INSTALLFLAGS=-fschg
E 22
I 20
DPADD=	${LIBCOMPAT}
LDADD=	-lcompat
E 20
I 19
CLEANFILES=y.tab.h
E 19
E 18
E 12

D 12
${OBJS}:  defs.h
E 12
I 12
D 13
rdist:	${OBJS} ${LIBC}
E 13
I 13
D 18
rdist: ${OBJS} ${LIBC}
E 13
	${CC} -o $@ ${CFLAGS} ${OBJS}
E 12

D 12
clean:
	rm -f *.o gram.c errs
E 12
I 12
D 15
clean: FRC
E 15
I 15
clean:
E 15
	rm -f ${OBJS} core rdist
E 12

I 11
D 12
depend:
E 12
I 12
D 15
depend: FRC
E 15
I 15
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 15
	mkdep ${CFLAGS} ${SRCS}
E 12

E 11
D 6
install:
E 6
I 6
D 12
install: rdist
E 6
D 5
	install -s rdist ${DESTDIR}/usr/ucb/rdist
E 5
I 5
D 7
	install -s -m 4751 rdist ${DESTDIR}/usr/local/rdist
E 7
I 7
D 9
	install -m 4751 rdist ${DESTDIR}${RDIST}
E 9
I 9
	install -s -m 4751 rdist ${DESTDIR}${RDIST}
E 12
I 12
D 15
install: FRC
E 15
I 15
install: ${MAN}
E 15
	install -s -o root -g bin -m 4751 rdist ${DESTDIR}${RDIST}
I 15
	install -c -o bin -g bin -m 444 rdist.0 ${DESTDIR}/usr/man/cat1
E 15
E 12
E 9
E 7
E 5

D 2
lint:	main.c gram.c docmd.c expand.c server.c
	${LINT} main.c gram.c docmd.c expand.c server.c
E 2
I 2
D 12
lint:	docmd.c expand.c gram.c lookup.c main.c server.c
	${LINT} docmd.c expand.c gram.c lookup.c main.c server.c
E 12
I 12
D 15
lint: FRC
E 15
I 15
lint: ${SRCS}
E 15
	lint ${CFLAGS} ${SRCS}
E 12
E 2

D 12
print:	${SRCS}
	lpr -p ${SRCS} defs.h
E 12
I 12
D 15
tags: FRC
E 15
I 15
tags: ${SRCS}
E 15
	ctags ${SRCS}
E 18
I 18
.include <bsd.prog.mk>
E 18
D 15

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

docmd.o: docmd.c
docmd.o:defs.h
docmd.o: /usr/include/stdio.h /usr/include/ctype.h /usr/include/errno.h
docmd.o: /usr/include/pwd.h /usr/include/grp.h /usr/include/sys/param.h
docmd.o: /usr/include/sys/types.h /usr/include/signal.h
docmd.o: /usr/include/machine/machparam.h /usr/include/sys/dir.h
docmd.o: /usr/include/sys/stat.h /usr/include/sys/time.h /usr/include/time.h
docmd.o: /usr/include/netinet/in.h /usr/include/setjmp.h /usr/include/netdb.h
expand.o: expand.c
expand.o:defs.h
expand.o: /usr/include/stdio.h /usr/include/ctype.h /usr/include/errno.h
expand.o: /usr/include/pwd.h /usr/include/grp.h /usr/include/sys/param.h
expand.o: /usr/include/sys/types.h /usr/include/signal.h
expand.o: /usr/include/machine/machparam.h /usr/include/sys/dir.h
expand.o: /usr/include/sys/stat.h /usr/include/sys/time.h /usr/include/time.h
expand.o: /usr/include/netinet/in.h
gram.o: gram.y
gram.o:defs.h
gram.o: /usr/include/stdio.h /usr/include/ctype.h /usr/include/errno.h
gram.o: /usr/include/pwd.h /usr/include/grp.h /usr/include/sys/param.h
gram.o: /usr/include/sys/types.h /usr/include/signal.h
gram.o: /usr/include/machine/machparam.h /usr/include/sys/dir.h
gram.o: /usr/include/sys/stat.h /usr/include/sys/time.h /usr/include/time.h
gram.o: /usr/include/netinet/in.h
lookup.o: lookup.c
lookup.o:defs.h
lookup.o: /usr/include/stdio.h /usr/include/ctype.h /usr/include/errno.h
lookup.o: /usr/include/pwd.h /usr/include/grp.h /usr/include/sys/param.h
lookup.o: /usr/include/sys/types.h /usr/include/signal.h
lookup.o: /usr/include/machine/machparam.h /usr/include/sys/dir.h
lookup.o: /usr/include/sys/stat.h /usr/include/sys/time.h /usr/include/time.h
lookup.o: /usr/include/netinet/in.h
main.o: main.c
main.o:defs.h
main.o: /usr/include/stdio.h /usr/include/ctype.h /usr/include/errno.h
main.o: /usr/include/pwd.h /usr/include/grp.h /usr/include/sys/param.h
main.o: /usr/include/sys/types.h /usr/include/signal.h
main.o: /usr/include/machine/machparam.h /usr/include/sys/dir.h
main.o: /usr/include/sys/stat.h /usr/include/sys/time.h /usr/include/time.h
main.o: /usr/include/netinet/in.h
server.o: server.c
server.o:defs.h
server.o: /usr/include/stdio.h /usr/include/ctype.h /usr/include/errno.h
server.o: /usr/include/pwd.h /usr/include/grp.h /usr/include/sys/param.h
server.o: /usr/include/sys/types.h /usr/include/signal.h
server.o: /usr/include/machine/machparam.h /usr/include/sys/dir.h
server.o: /usr/include/sys/stat.h /usr/include/sys/time.h /usr/include/time.h
server.o: /usr/include/netinet/in.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 15
E 12
E 1
