h14184
s 00000/00000/00006
d D 8.1 93/05/31 15:02:22 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00001/00006
d D 5.4 91/11/23 10:25:33 bostic 4 3
c do includes right
e
s 00002/00000/00005
d D 5.3 91/07/26 16:19:59 bostic 3 2
c new version from Keith Muller
e
s 00003/00046/00002
d D 5.2 90/05/11 12:39:07 bostic 2 1
c first pass for new make
e
s 00048/00000/00000
d D 5.1 88/10/18 20:25:12 bostic 1 0
c date and time created 88/10/18 20:25:12 by bostic
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
SRCS=	dd.c
OBJS=
MAN=	dd.0
E 2
I 2
PROG=	dd
I 3
D 4
CFLAGS+=	-I${.CURDIR}
E 4
SRCS=	args.c conv.c conv_tab.c dd.c misc.c position.c
E 3
E 2

D 2
all: dd

dd: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c

clean:
	rm -f ${OBJS} core dd

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
	install -s -o bin -g bin -m 755 dd ${DESTDIR}/bin
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
