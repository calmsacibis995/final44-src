h17941
s 00003/00044/00003
d D 4.6 90/05/11 14:14:04 bostic 6 5
c first pass for new make
e
s 00001/00001/00046
d D 4.5 89/05/11 13:38:15 bostic 5 4
c file reorg, pathnames.h, paths.h
e
s 00026/00020/00021
d D 4.4 88/10/25 15:12:49 bostic 4 3
c add manual page, cleanup
e
s 00036/00011/00005
d D 4.3 87/06/03 00:05:16 bostic 3 2
c new template
e
s 00002/00000/00014
d D 4.2 87/05/31 20:33:24 bostic 2 1
c added depend label
e
s 00014/00000/00000
d D 4.1 85/04/05 09:29:10 ralph 1 0
c date and time created 85/04/05 09:29:10 by ralph
e
u
U
t
T
I 1
D 3
#	%M%	%I%	%E%
E 3
D 6
#
D 3
CFLAGS=-O -w
E 3
I 3
D 4
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 4
I 4
# Copyright (c) 1987 The Regents of the University of California.
# All rights reserved.
E 4
#
D 4
#	%W%	(Berkeley)	%G%
E 4
I 4
# Redistribution and use in source and binary forms are permitted
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
E 4
#
E 6
I 4
#	%W% (Berkeley) %G%
D 6
#
E 4
CFLAGS=	-O -w
LIBC=	/lib/libc.a
E 6
I 6

PROG=	sed
E 6
SRCS=	sed0.c sed1.c
D 6
OBJS=	sed0.o sed1.o
I 4
MAN=	sed.0
E 6
E 4
E 3

D 3
sed:	sed0.o sed1.o
	cc -o sed *.o
E 3
I 3
D 6
all: sed
E 3

D 3
sed0.o: sed0.c sed.h
sed1.o: sed1.c sed.h
E 3
I 3
D 4
sed:	${OBJS} ${LIBC}
E 4
I 4
sed: ${OBJS} ${LIBC}
E 4
	${CC} -o $@ ${CFLAGS} ${OBJS}
E 3

D 3
install: sed
	install -s sed $(DESTDIR)/bin
clean:
	rm -f *.o sed
E 3
I 3
D 4
clean: FRC
E 4
I 4
clean:
E 4
	rm -f ${OBJS} core sed
E 3
I 2

D 3
depend:
E 3
I 3
D 4
depend: FRC
E 4
I 4
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 4
	mkdep ${CFLAGS} ${SRCS}

D 4
install: FRC
E 4
I 4
install: ${MAN}
E 4
D 5
	install -s -o bin -g bin -m 755 sed ${DESTDIR}/bin/sed
E 5
I 5
	install -s -o bin -g bin -m 755 sed ${DESTDIR}/usr/bin
E 5
I 4
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
E 4

D 4
lint: FRC
E 4
I 4
lint: ${SRCS}
E 4
	lint ${CFLAGS} ${SRCS}

D 4
tags: FRC
E 4
I 4
tags: ${SRCS}
E 4
	ctags ${SRCS}
E 6
I 6
.include <bsd.prog.mk>
E 6
D 4

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

sed0.o: sed0.c /usr/include/stdio.h sed.h
sed1.o: sed1.c /usr/include/stdio.h sed.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 4
E 3
E 2
E 1
