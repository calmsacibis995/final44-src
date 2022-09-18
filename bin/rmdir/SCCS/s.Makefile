h04437
s 00000/00000/00005
d R 8.2 93/05/31 15:11:07 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00000/00005
d D 8.1 93/05/31 15:11:00 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00003/00046/00002
d D 5.2 90/05/11 12:40:28 bostic 2 1
c first pass for new make
e
s 00048/00000/00000
d D 5.1 88/10/18 22:13:07 bostic 1 0
c date and time created 88/10/18 22:13:07 by bostic
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
SRCS=	rmdir.c
OBJS=
MAN=	rmdir.0
E 2
I 2
PROG=	rmdir
E 2

D 2
all: rmdir

rmdir: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c

clean:
	rm -f ${OBJS} core rmdir

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
	install -s -o bin -g bin -m 755 rmdir ${DESTDIR}/bin
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 2
I 2
.include <bsd.prog.mk>
E 2
E 1
