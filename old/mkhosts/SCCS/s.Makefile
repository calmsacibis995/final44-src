h38141
s 00001/00002/00037
d D 5.5 90/05/24 17:35:16 bostic 5 4
c needs to know how to make man pges
e
s 00023/00035/00016
d D 5.4 90/05/11 16:04:54 bostic 4 3
c first pass for new make
e
s 00001/00001/00050
d D 5.3 89/05/11 14:21:27 bostic 3 2
c file reorg, pathnames.h, paths.h
e
s 00003/00002/00048
d D 5.2 89/03/05 15:44:47 bostic 2 1
c conditional install
e
s 00050/00000/00000
d D 5.1 88/10/19 11:45:49 bostic 1 0
c date and time created 88/10/19 11:45:49 by bostic
e
u
U
t
T
I 1
D 4
#
# Copyright (c) 1988 Regents of the University of California.
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
# provided that the above copyright notice and this paragraph are
# duplicated in all such forms and that any documentation, advertising
# materials, and other materials related to such redistribution and
# use acknowledge that the software was developed by the University
# of California, Berkeley.  The name of the University may not be
# used to endorse or promote products derived from this software
# without specific prior written permission.  THIS SOFTWARE IS PROVIDED
# ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
# WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND
# FITNESS FOR A PARTICULAR PURPOSE.
#
# %W% (Berkeley) %G%
#
E 4
I 4
#	%W% (Berkeley) %G%
E 4

D 4
CFLAGS=	-O
LIBC=	/lib/libc.a
E 4
SRCS=	mkhosts.c
D 4
OBJS=
MAN=	mkhosts.0
E 4
I 4
MAN8=	mkhosts.0
.PATH:	${.CURDIR}
E 4

D 4
all: mkhosts
E 4
I 4
all: mkhosts ${MAN8}
E 4

D 4
mkhosts: ${LIBC}
	@echo "Mkhosts only works with the dbm version of the hostent routines."
	@echo "If gethosts() is not in libc, mkhosts isn't installed."
	-${CC} -o $@ ${CFLAGS} $@.c || make clean
E 4
I 4
mkhosts: ${LIBC} mkhosts.c
	@echo "Mkhosts requires the dbm version of the hostent(3) routines."
	@echo "If gethosts(3) is not in libc, mkhosts will not be installed."
	-${CC} -o ${.TARGET} ${CFLAGS} ${.CURDIR}/${.PREFIX}.c || \
	    cd ${.CURDIR} && ${MAKE} clean
E 4

clean:
D 4
	rm -f ${OBJS} core mkhosts
E 4
I 4
	rm -f core mkhosts mkhosts.o
E 4

cleandir: clean
D 4
	rm -f ${MAN} tags .depend
E 4
I 4
	rm -f ${MAN8} tags .depend
E 4

depend: ${SRCS}
D 4
	mkdep -p ${CFLAGS} ${SRCS}
E 4
I 4
	mkdep -p ${CFLAGS} ${.ALLSRC}
E 4

D 4
install: ${MAN}
D 2
	install -s -o bin -g bin -m 755 mkhosts ${DESTDIR}/etc
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat8
E 2
I 2
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat8;
E 4
I 4
install: maninstall
E 4
	-if [ -f mkhosts ]; then \
D 3
	    install -s -o bin -g bin -m 755 mkhosts ${DESTDIR}/etc; fi
E 3
I 3
D 4
	    install -s -o bin -g bin -m 755 mkhosts ${DESTDIR}/usr/sbin; fi
E 4
I 4
	    install ${STRIP} -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
		mkhosts ${DESTDIR}${BINDIR}; \
	else \
		exit 0; \
	fi
E 4
E 3
E 2

lint: ${SRCS}
D 4
	lint ${CFLAGS} ${SRCS}
E 4
I 4
	cd ${.CURDIR}; lint ${CFLAGS} ${LINTFLAGS} ${SRCS}
E 4

tags: ${SRCS}
D 4
	ctags ${SRCS}
E 4
I 4
	cd ${.CURDIR}; ctags ${SRCS}

D 5
.include <bsd.own.mk>
.include <bsd.man.mk>
E 5
I 5
.include <bsd.prog.mk>
E 5
E 4
E 1
