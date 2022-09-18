h44062
s 00000/00000/00008
d D 8.1 93/06/06 15:23:39 bostic 16 15
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00001/00008
d D 5.13 93/06/06 15:23:06 bostic 15 14
c move man/{apropos,whatis,man} up a level
e
s 00001/00001/00008
d D 5.12 90/09/30 17:57:51 bostic 14 12
c man_conf -> man.conf
e
s 00001/00001/00008
d R 5.12 90/09/30 17:50:44 bostic 13 12
c man_conf.5 -> manconf.5
e
s 00001/00001/00008
d D 5.11 90/06/28 20:34:14 bostic 12 11
c man.conf -> man_conf
e
s 00001/00000/00008
d D 5.10 90/05/27 15:20:29 bostic 11 10
c move to subdirectory of usr.bin/man
e
s 00005/00045/00003
d D 5.9 90/05/11 14:28:32 bostic 10 9
c first pass for new make
e
s 00013/00022/00035
d D 5.8 90/03/11 15:11:06 bostic 9 8
c add -m flag, configurable directory search path (/etc/man.config)
c add man.config man page, redo man(1) man page, now AT&T free.  Change '-'
c option to -c, other minor whacks
e
s 00001/00003/00056
d D 5.7 89/05/11 10:00:39 bostic 8 7
c file reorg, pathnames.h, paths.h
e
s 00027/00035/00032
d D 5.6 88/09/18 18:15:18 bostic 7 6
c move man pages here, split whatis and apropos
e
s 00010/00005/00057
d D 5.5 88/06/29 19:42:44 bostic 6 5
c install approved copyright notice
e
s 00014/00014/00048
d D 5.4 88/01/15 16:43:33 bostic 5 4
c don't make .o's first
e
s 00009/00003/00053
d D 5.3 87/12/16 15:41:36 bostic 4 3
c add Berkeley headers
e
s 00002/00000/00054
d D 5.2 87/06/30 21:06:36 bostic 3 1
c general cleanup
e
s 00002/00000/00054
d R 5.2 87/06/30 19:15:22 bostic 2 1
c it really works now
e
s 00054/00000/00000
d D 5.1 87/06/29 20:55:49 bostic 1 0
c date and time created 87/06/29 20:55:49 by bostic
e
u
U
t
T
I 1
D 10
#
# Copyright (c) 1987 Regents of the University of California.
D 4
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 4
I 4
# All rights reserved.
E 4
#
D 4
#	%W%	(Berkeley)	%G%
E 4
I 4
# Redistribution and use in source and binary forms are permitted
D 6
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
# is provided ``as is'' without express or implied warranty.
E 6
I 6
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
E 6
#
E 10
#	%W% (Berkeley) %G%
E 4
D 10
#
CFLAGS=	-O
LIBC=	/lib/libc.a
E 10
I 10

PROG=	man
E 10
D 7
ASRCS=	apropos.c
D 5
AOBJS=	apropos.o
E 5
MSRCS=	man.c
E 7
I 7
D 9
SRCS=	apropos.c whatis.c man.c
MAN=	man.0 apropos.0 whatis.0
E 9
I 9
SRCS=	config.c man.c
D 10
OBJS=	config.o man.o
MAN=	man.0 man.config.0
E 10
I 10
MAN1=	man.0
D 12
MAN5=	man.conf.0
E 12
I 12
D 14
MAN5=	man_conf.0
E 14
I 14
MAN5=	man.conf.0
E 14
E 12
E 10
E 9
E 7
D 5
MOBJS=	man.o
E 5

I 11
D 15
.include "../../Makefile.inc"
E 15
E 11
D 7
all: man apropos
E 7
I 7
D 9
all: man apropos whatis
E 9
I 9
D 10
all: man
E 9
E 7

I 7
D 9
man: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c
E 9
I 9
man: ${LIBC} ${OBJS}
	${CC} -o $@ ${OBJS}
E 9

E 7
D 5
apropos: ${AOBJS} ${LIBC}
	${CC} -o $@ ${CFLAGS} ${AOBJS}
E 5
I 5
D 9
apropos: ${LIBC}
D 7
	${CC} -o $@ ${CFLAGS} ${ASRCS}
E 7
I 7
	${CC} -o $@ ${CFLAGS} $@.c
E 7
E 5

D 5
man:	${MOBJS} ${LIBC}
	${CC} -o $@ ${CFLAGS} ${MOBJS}
E 5
I 5
D 7
man: ${LIBC}
	${CC} -o $@ ${CFLAGS} ${MSRCS}
E 7
I 7
whatis: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c
E 7
E 5

E 9
D 7
clean: FRC
D 5
	rm -f ${AOBJS} ${MOBJS} core apropos man
E 5
I 5
	rm -f core apropos man
E 7
I 7
clean:
D 9
	rm -f core apropos whatis man
E 9
I 9
	rm -f core man ${OBJS}
E 9
E 7
E 5

D 7
depend: FRC
D 5
	mkdep ${CFLAGS} ${ASRCS} ${MSRCS}
E 5
I 5
	mkdep -p ${CFLAGS} ${ASRCS} ${MSRCS}
E 7
I 7
cleandir: clean
	rm -f ${MAN} tags .depend
E 7
E 5

D 7
install: FRC
I 3
	rm -f ${DESTDIR}/usr/ucb/whatis ${DESTDIR}/usr/ucb/apropos
E 7
I 7
depend:
D 9
	mkdep -p ${CFLAGS} ${SRCS}
E 9
I 9
	mkdep ${CFLAGS} ${SRCS}
E 9

install: ${MAN}
E 7
E 3
D 8
	install -s -o bin -g bin -m 755 apropos ${DESTDIR}/usr/ucb/apropos
I 7
	install -s -o bin -g bin -m 755 whatis ${DESTDIR}/usr/ucb/whatis
E 7
	install -s -o bin -g bin -m 755 man ${DESTDIR}/usr/ucb/man
E 8
I 8
D 9
	install -s -o bin -g bin -m 755 apropos whatis man ${DESTDIR}/usr/bin
E 8
I 3
D 7
	ln ${DESTDIR}/usr/ucb/apropos ${DESTDIR}/usr/ucb/whatis
E 7
I 7
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
E 9
I 9
	install -s -o bin -g bin -m 755 man ${DESTDIR}/usr/bin
	install -c -o bin -g bin -m 444 man.0 ${DESTDIR}/usr/man/cat1
	install -c -o bin -g bin -m 444 man.config.0 ${DESTDIR}/usr/man/cat5
E 9
E 7
E 3

D 7
lint: FRC
	lint ${CFLAGS} ${ASRCS}
	lint ${CFLAGS} ${MSRCS}
E 7
I 7
lint:
D 9
	lint ${CFLAGS} apropos.c
	lint ${CFLAGS} whatis.c
	lint ${CFLAGS} man.c
E 9
I 9
	lint ${CFLAGS} ${SRCS}
E 9
E 7

D 7
tags: FRC
	ctags ${ASRCS}
	ctags ${MSRCS}
E 7
I 7
tags:
D 9
	ctags apropos.c
	ctags -a whatis.c
	ctags -a man.c
E 7
	sort -o tags tags
E 9
I 9
	ctags ${SRCS}
E 10
I 10
.include <bsd.prog.mk>
E 10
E 9
D 7

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

D 5
apropos.o: apropos.c /usr/include/sys/param.h /usr/include/sys/types.h
apropos.o: /usr/include/signal.h /usr/include/machine/machparam.h
apropos.o: /usr/include/stdio.h /usr/include/ctype.h
man.o: man.c /usr/include/sys/param.h /usr/include/sys/types.h
man.o: /usr/include/signal.h /usr/include/machine/machparam.h
man.o: /usr/include/sys/file.h /usr/include/stdio.h /usr/include/ctype.h
E 5
I 5
apropos: apropos.c /usr/include/sys/param.h /usr/include/sys/types.h
apropos: /usr/include/signal.h /usr/include/machine/trap.h
apropos: /usr/include/machine/machparam.h /usr/include/machine/endian.h
apropos: /usr/include/stdio.h /usr/include/ctype.h
man: man.c /usr/include/sys/param.h /usr/include/sys/types.h
man: /usr/include/signal.h /usr/include/machine/trap.h
man: /usr/include/machine/machparam.h /usr/include/machine/endian.h
man: /usr/include/sys/file.h /usr/include/stdio.h /usr/include/ctype.h
E 5

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 7
E 1
