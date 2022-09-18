h04791
s 00000/00000/00012
d D 8.1 93/06/06 22:28:37 bostic 7 6
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00003/00010
d D 5.6 93/03/03 20:34:23 bostic 6 5
c add uappend, uchange, sappend, schange flags as -f option to install
e
s 00001/00000/00012
d D 5.5 90/06/24 11:16:22 bostic 5 4
c clean xinstall
e
s 00007/00043/00005
d D 5.4 90/05/11 13:49:10 bostic 4 3
c first pass for new make
e
s 00001/00001/00047
d D 5.3 90/03/11 10:18:25 mckusick 3 2
c have to add explicit dependency on install.c as mkdep does not find it
e
s 00003/00003/00045
d D 5.2 88/11/21 10:31:19 bostic 2 1
c make dependencies work right
e
s 00048/00000/00000
d D 5.1 88/09/22 16:47:00 bostic 1 0
c date and time created 88/09/22 16:47:00 by bostic
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
SRCS=	install.c
OBJS=
MAN=	install.0
E 4
I 4
PROG=	xinstall
I 6
SRCS=	stat_flags.c xinstall.c
E 6
MAN1=	install.0
I 5
D 6
CLEANFILES=xinstall
E 6
I 6
.PATH:	${.CURDIR}/../../bin/ls
E 6
E 5
E 4

D 4
all: xinstall
E 4
I 4
install: maninstall
	install ${STRIP} -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${PROG} ${DESTDIR}${BINDIR}/install
E 4

D 3
xinstall: ${LIBC}
E 3
I 3
D 4
xinstall: install.c ${LIBC}
E 3
D 2
	${CC} -o install ${CFLAGS} install.c
E 2
I 2
	${CC} -o xinstall ${CFLAGS} install.c
E 4
I 4
.include <bsd.prog.mk>
E 4
E 2
D 6

D 4
clean:
D 2
	rm -f ${OBJS} core install
E 2
I 2
	rm -f ${OBJS} core xinstall
E 4
E 2

E 6
D 4
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 2
	install -s -o bin -g bin -m 755 install ${DESTDIR}/usr/bin/install
E 2
I 2
	install -s -o bin -g bin -m 755 xinstall ${DESTDIR}/usr/bin/install
E 2
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 4
E 1
