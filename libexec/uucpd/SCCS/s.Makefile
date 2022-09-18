h12669
s 00000/00000/00006
d D 8.1 93/06/04 19:08:05 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00002/00006
d D 5.3 90/06/25 00:13:40 bostic 3 2
c no need to be owned by uucp, just gets run by inetd
e
s 00006/00047/00002
d D 5.2 90/05/11 12:55:12 bostic 2 1
c first pass for new make
e
s 00049/00000/00000
d D 5.1 90/03/22 21:50:02 bostic 1 0
c date and time created 90/03/22 21:50:02 by bostic
e
u
U
t
T
I 1
D 2
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
E 2
I 2
#	%W% (Berkeley) %G%
E 2

D 2
CFLAGS=	-O
LIBC=	/lib/libc.a
SRCS=	uucpd.c
OBJS=
MAN=
E 2
I 2
PROG=	uucpd
D 3
BINOWN=	uucp
BINMODE=500
E 3
NOMAN=	noman
E 2

D 2
all: uucpd

uucpd: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c

clean:
	rm -f ${OBJS} core uucpd

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
	install -s -o uucp -g bin -m 700 uucpd ${DESTDIR}/usr/libexec
	@echo "Don't forget to fork off uucpd in rc.local"
	@echo "	if you're not running inetd."

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 2
I 2
.include <bsd.prog.mk>
E 2
E 1
