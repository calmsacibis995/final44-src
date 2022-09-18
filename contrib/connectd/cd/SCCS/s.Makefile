h03860
s 00004/00047/00004
d D 5.2 93/05/29 11:17:13 bostic 2 1
c new copyright notices
e
s 00048/00000/00000
d D 5.1 89/05/16 08:51:15 bostic 1 0
c date and time created 89/05/16 08:51:15 by bostic
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
# This code is derived from software contributed to Berkeley by
# Bill Jolitz.
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
CFLAGS=	-O -I../include
LIBC=	/lib/libc.a
E 2
SRCS=	main.c rcv.c snd.c
D 2
OBJS=	main.o rcv.o snd.o
MAN=
E 2
I 2
CFLAGS+=-I../include
NOMAN=
E 2

D 2
all: cd
E 2
I 2
.include <bsd.prog.mk>
E 2

D 2
cd: ${LIBC} ${OBJS}
	${CC} -o $@ ${CFLAGS} ${OBJS}

clean:
	rm -f ${OBJS} core cd

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
#	install -s -o bin -g bin -m 755 cd ${DESTDIR}/
#	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 2
E 1
