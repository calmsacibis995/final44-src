h51130
s 00000/00000/00008
d D 8.1 93/06/06 15:11:41 bostic 7 6
c 4.4BSD snapshot (revision 8.1)
e
s 00005/00042/00003
d D 5.5 90/06/29 11:38:01 bostic 6 5
c redo pascal makefiles
e
s 00002/00002/00043
d D 5.4 90/06/22 19:18:52 kfall 5 4
c libc.a now in /usr/lib
e
s 00022/00022/00023
d D 5.3 89/03/06 11:48:06 bostic 4 3
c cleanup, add cleadir, copyright
e
s 00032/00017/00013
d D 5.2 87/10/26 09:03:07 bostic 3 1
c new template
e
s 00032/00017/00013
d R 5.2 87/10/16 16:05:15 bostic 2 1
c new template
e
s 00030/00000/00000
d D 5.1 86/06/05 14:09:35 mckusick 1 0
c date and time created 86/06/05 14:09:35 by mckusick
e
u
U
t
T
I 1
D 6
#
D 4
# Copyright (c) 1980 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 4
I 4
# Copyright (c) 1989 The Regents of the University of California.
# All rights reserved.
E 4
#
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
#
E 6
E 4
#	%W% (Berkeley) %G%
D 6
#
D 3
INSTALLDIR = ${DESTDIR}/usr/ucb
E 3
I 3
CFLAGS=	-O
D 5
LIBC=	/lib/libc.a
E 5
I 5
LIBC=	/usr/lib/libc.a
E 6
I 6

PROG=	eyacc
E 6
E 5
SRCS=	ey0.c ey1.c ey2.c ey3.c ey4.c ey5.c
D 6
OBJS=	ey0.o ey1.o ey2.o ey3.o ey4.o ey5.o
E 6
I 6
MAN1=	eyacc.0
BINDIR=	/usr/libexec/pascal
E 6
E 3

D 3
eyacc: ey0.o ey1.o ey2.o ey3.o ey4.o ey5.o
	cc -o eyacc -z ey0.o ey1.o ey2.o ey3.o ey4.o ey5.o
E 3
I 3
D 6
all: eyacc
E 3

D 3
.c.o:
	cc -O -c $*.c
E 3
I 3
eyacc: ${LIBC} ${OBJS}
	${CC} ${CFLAGS} -o $@ -z ${OBJS}
E 3

D 3
clean:
	-rm -f *.o eyacc
E 3
I 3
D 4
clean: FRC
E 4
I 4
clean:
E 4
	rm -f ${OBJS} core eyacc
E 3

D 3
install: eyacc
#	cp eyacc ${INSTALLDIR}/eyacc
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
E 3

D 3
print:
	@ls -l | pr
	@pr READ_ME makefile
	@pr ey.h ey0.c ey1.c ey2.c ey3.c ey4.c ey5.c
E 3
I 3
D 4
install: FRC
E 4
I 4
install: ${MAN}
E 4
D 5
#	install -s -o bin -g bin -m 755 eyacc ${DESTDIR}/usr/ucb/eyacc
E 5
I 5
#	install -s -o bin -g bin -m 755 eyacc ${DESTDIR}/usr/bin/eyacc
E 5
E 3

D 3
ey1.o:	ey.h
ey2.o:	ey.h
ey3.o:	ey.h
ey4.o:	ey.h
E 3
I 3
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

ey0.o: ey0.c /usr/include/stdio.h
ey1.o: ey1.c ey.h /usr/include/stdio.h
ey2.o: ey2.c ey.h /usr/include/stdio.h
ey3.o: ey3.c ey.h /usr/include/stdio.h
ey4.o: ey4.c ey.h /usr/include/stdio.h
ey5.o: ey5.c /usr/include/stdio.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 4
E 3
E 1
