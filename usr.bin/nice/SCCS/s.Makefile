h33112
s 00000/00000/00005
d D 8.1 93/06/06 15:46:13 bostic 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00003/00046/00002
d D 5.5 90/05/11 14:28:10 bostic 5 4
c first pass for new make
e
s 00000/00003/00048
d D 5.4 89/05/20 12:58:00 bostic 4 3
c move nohup
e
s 00001/00001/00050
d D 5.3 89/05/11 10:02:35 bostic 3 2
c file reorg, pathnames.h, paths.h
e
s 00001/00000/00050
d D 5.2 88/10/22 16:13:05 bostic 2 1
c add nohup
e
s 00050/00000/00000
d D 5.1 88/10/18 21:55:03 bostic 1 0
c date and time created 88/10/18 21:55:03 by bostic
e
u
U
t
T
I 1
D 5
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
E 5
I 5
#	%W% (Berkeley) %G%
E 5

D 5
CFLAGS=	-O
LIBC=	/lib/libc.a
SRCS=	nice.c
OBJS=
MAN=	nice.0
E 5
I 5
PROG=	nice
E 5

D 5
all: nice

nice: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c

clean:
	rm -f ${OBJS} core nice

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 3
	install -s -o bin -g bin -m 755 nice ${DESTDIR}/bin
E 3
I 3
	install -s -o bin -g bin -m 755 nice ${DESTDIR}/usr/bin
E 3
I 2
D 4
	install -c -o bin -g bin -m 755 nohup.sh ${DESTDIR}/usr/bin/nohup
E 4
E 2
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
D 4
	rm -f ln ${DESTDIR}/usr/man/cat1/nohup.0
	ln ${DESTDIR}/usr/man/cat1/nice.0 ${DESTDIR}/usr/man/cat1/nohup.0
E 4

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 5
I 5
.include <bsd.prog.mk>
E 5
E 1
