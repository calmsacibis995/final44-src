h02924
s 00000/00000/00006
d D 8.1 93/06/06 15:50:48 bostic 9 8
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00074/00004
d D 5.8 90/06/30 22:56:26 bostic 8 7
c new makefiles
e
s 00011/00005/00067
d D 5.7 88/07/09 11:05:42 bostic 7 6
c install approved copyright notice
e
s 00062/00017/00010
d D 5.6 88/02/18 10:09:57 bostic 6 5
c new template
e
s 00009/00004/00018
d D 5.5 87/07/25 16:16:30 bostic 5 4
c make/install the man page
e
s 00002/00001/00020
d D 5.4 86/05/31 17:20:24 van 4 3
c added CFLAGS
e
s 00001/00001/00020
d D 5.3 86/03/29 13:44:15 bloom 3 2
c make install depend on binary
e
s 00002/00002/00019
d D 5.2 85/11/15 09:43:03 lepreau 2 1
c install -s, not -c
e
s 00021/00000/00000
d D 5.1 85/09/10 11:51:49 mckusick 1 0
c date and time created 85/09/10 11:51:49 by mckusick
e
u
U
t
T
I 6
D 8
#
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
D 7
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific written prior permission. This software
# is provided ``as is'' without express or implied warranty.
E 7
I 7
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
E 7
#
E 8
E 6
I 1
#	%W% (Berkeley) %G%
D 8
#
E 8
I 7

E 7
D 6
# $Header: Makefile,v 1.3 85/03/26 15:03:26 lwall Exp $
E 6
I 6
D 8
CFLAGS=	-O
LIBC=	/lib/libc.a
E 8
I 8
PROG=	patch
E 8
SRCS=	patch.c pch.c inp.c version.c util.c
D 8
OBJS=	patch.o pch.o inp.o util.o version.o
E 8
E 6

D 6
BINDIR = $(DESTDIR)/usr/new
I 4
CFLAGS = -O
E 6
I 6
D 8
.SUFFIXES: .man .0
E 6
E 4

I 5
D 6
all: patch patch.0
E 6
I 6
.man.0:
	${DESTDIR}/usr/man/manroff $*.man > $*.0
E 6

E 5
D 6
patch: patch.c
D 4
	cc patch.c -O -o patch
E 4
I 4
D 5
	cc patch.c $(CFLAGS) -o patch
E 5
I 5
	${CC} patch.c $(CFLAGS) -o patch
E 6
I 6
all: patch
E 6
E 5
E 4

D 3
install:
E 3
I 3
D 5
install: patch
E 3
D 2
	install -c patch $(BINDIR)
E 2
I 2
	install -s patch $(BINDIR)
E 2
	install -c -m 444 patch.n ${DESTDIR}/usr/man/mann/patch.n
E 5
I 5
D 6
patch.0: patch.n
	../../man/manroff patch.n > patch.0
E 6
I 6
patch: ${OBJS} ${LIBC}
	${CC} -o $@ ${CFLAGS} ${OBJS}
E 6

D 6
install:
	install -s -o bin -g src -m 755 patch $(BINDIR)
	install -c -o bin -g src -m 444 patch.0 ${DESTDIR}/usr/new/man/cat1/patch.0
E 6
I 6
clean: FRC
	rm -f ${OBJS} core patch Makefile.old bsd config.sh \
	eunice loc pdp11 usg v7
E 6
E 5

D 6
clean:
D 2
	rm patch
E 2
I 2
	rm -f patch patch.kit a.out core errs
E 6
I 6
depend: FRC
	mkdep ${CFLAGS} ${SRCS}
E 6
E 2

D 6
shar:
	shar patch.man patch.c Makefile >patch.kit
E 6
I 6
install: patch.0
	install -c -o bin -g bin -m 444 patch.0 ${DESTDIR}/usr/new/man/cat1
	install -s -o bin -g bin -m 755 patch ${DESTDIR}/usr/new
E 6

D 6
lint:
	lint -phbvxac patch.c
E 6
I 6
lint: FRC
	lint ${CFLAGS} ${SRCS}

tags: FRC
	ctags ${SRCS}

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

patch.o: patch.c INTERN.h common.h config.h /usr/include/stdio.h
patch.o: /usr/include/assert.h /usr/include/sys/types.h /usr/include/sys/stat.h
patch.o: /usr/include/ctype.h /usr/include/signal.h /usr/include/machine/trap.h
patch.o: EXTERN.h version.h util.h pch.h inp.h
pch.o: pch.c EXTERN.h common.h config.h /usr/include/stdio.h
pch.o: /usr/include/assert.h /usr/include/sys/types.h /usr/include/sys/stat.h
pch.o: /usr/include/ctype.h /usr/include/signal.h /usr/include/machine/trap.h
pch.o: util.h INTERN.h pch.h
inp.o: inp.c EXTERN.h common.h config.h /usr/include/stdio.h
inp.o: /usr/include/assert.h /usr/include/sys/types.h /usr/include/sys/stat.h
inp.o: /usr/include/ctype.h /usr/include/signal.h /usr/include/machine/trap.h
inp.o: util.h pch.h INTERN.h inp.h
version.o: version.c EXTERN.h common.h config.h /usr/include/stdio.h
version.o: /usr/include/assert.h /usr/include/sys/types.h
version.o: /usr/include/sys/stat.h /usr/include/ctype.h /usr/include/signal.h
version.o: /usr/include/machine/trap.h util.h INTERN.h patchlevel.h version.h
util.o: util.c EXTERN.h common.h config.h /usr/include/stdio.h
util.o: /usr/include/assert.h /usr/include/sys/types.h /usr/include/sys/stat.h
util.o: /usr/include/ctype.h /usr/include/signal.h /usr/include/machine/trap.h
util.o: INTERN.h util.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 8
I 8
.include <bsd.prog.mk>
E 8
E 6
E 1
