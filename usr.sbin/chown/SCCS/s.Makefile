h55953
s 00000/00000/00009
d D 8.1 93/06/06 13:51:53 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00000/00008
d D 5.4 90/10/26 14:52:04 bostic 4 3
c change group character, dot, to colon (dot still permitted)
c change the -f flag to ONLY mask errors in changing owner/group
c new manual page, started from the POSIX.2 manual page
c use FTS to walk the tree
e
s 00006/00048/00002
d D 5.3 90/05/11 16:05:32 bostic 3 2
c first pass for new make
e
s 00002/00003/00048
d D 5.2 89/05/11 13:51:17 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00051/00000/00000
d D 5.1 88/10/18 22:44:27 bostic 1 0
c date and time created 88/10/18 22:44:27 by bostic
e
u
U
t
T
I 1
D 3
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
E 3
I 3
#	%W% (Berkeley) %G%
E 3

D 3
CFLAGS=	-O
LIBC=	/lib/libc.a
SRCS=	chown.c
OBJS=
MAN=	chown.0 chgrp.0
E 3
I 3
PROG=	chown
I 4
CFLAGS+=-DSUPPORT_DOT
E 4
MAN1=	chgrp.0
MAN8=	chown.0
LINKS=	${BINDIR}/chown /usr/bin/chgrp
E 3

D 3
all: chown

chown: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c

clean:
	rm -f ${OBJS} core chown

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 2
	install -s -o bin -g bin -m 755 chown ${DESTDIR}/etc
	rm -f ${DESTDIR}/bin/chgrp
	ln ${DESTDIR}/etc/chown ${DESTDIR}/bin/chgrp
E 2
I 2
	install -c -s -o bin -g bin -m 755 chown ${DESTDIR}/sbin
	install -s -o bin -g bin -m 755 chown ${DESTDIR}/usr/bin/chgrp
E 2
	install -c -o bin -g bin -m 444 chown.0 ${DESTDIR}/usr/man/cat8
	install -c -o bin -g bin -m 444 chgrp.0 ${DESTDIR}/usr/man/cat1

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 3
I 3
.include <bsd.prog.mk>
E 3
E 1
