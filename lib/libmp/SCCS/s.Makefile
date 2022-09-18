h07710
s 00000/00000/00007
d D 8.1 93/06/04 17:17:06 bostic 7 6
c 4.4BSD snapshot (revision 8.1)
e
s 00004/00049/00003
d D 5.1 90/05/11 12:50:44 bostic 6 5
c first pass for new make
e
s 00004/00002/00048
d D 4.5 89/05/10 22:38:52 bostic 5 4
c minor cleanup
e
s 00025/00023/00025
d D 4.4 89/04/10 11:02:00 bostic 4 3
c add man page
e
s 00042/00017/00006
d D 4.3 87/06/19 14:55:29 bostic 3 2
c new template
e
s 00009/00001/00014
d D 4.2 85/05/30 22:59:56 sam 2 1
c add tags
e
s 00015/00000/00000
d D 4.1 82/12/25 10:50:36 sam 1 0
c date and time created 82/12/25 10:50:36 by sam
e
u
U
t
T
I 1
D 3
#	%W%	%G%
E 3
D 6
#
D 3
DESTDIR=
CFLAGS=-O
I 2
SRCS= pow.c gcd.c msqrt.c mdiv.c mout.c mult.c madd.c util.c
E 2
OBJS= pow.o gcd.o msqrt.o mdiv.o mout.o mult.o madd.o util.o
I 2
TAGSFILE=tags
E 3
I 3
D 4
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 4
I 4
# Copyright (c) 1989 The Regents of the University of California.
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
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
#
E 6
I 4
#	%W% (Berkeley) %G%
D 6
#
E 4
CFLAGS=	-O
LIBC=	/lib/libc.a
E 6
I 6

LIB=	mp
E 6
SRCS=	pow.c gcd.c msqrt.c mdiv.c mout.c mult.c madd.c util.c
D 6
OBJS=	pow.o gcd.o msqrt.o mdiv.o mout.o mult.o madd.o util.o
I 4
MAN=	mp.0
E 6
I 6
MAN3=	mp.0
E 6
E 4
E 3
E 2

D 3
libmp.a: $(OBJS)
	ar cr libmp.a $(OBJS)
E 3
I 3
D 6
all: libmp.a
E 3

D 3
install: libmp.a
	install libmp.a ${DESTDIR}/usr/lib/libmp.a
E 3
I 3
libmp.a: ${OBJS}
D 5
	ar cr $@ ${OBJS}
E 5
I 5
	@echo building normal libmp
	@ar cr $@ ${OBJS}
	ranlib libmp.a
E 5

D 4
clean: FRC
E 4
I 4
clean:
E 4
	rm -f ${OBJS} core libmp.a

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
	install -o bin -g bin -m 644 libmp.a ${DESTDIR}/usr/lib/libmp.a
E 3
D 5
	ranlib ${DESTDIR}/usr/lib/libmp.a
E 5
I 5
	ranlib -t ${DESTDIR}/usr/lib/libmp.a
E 5
I 4
	install -c -o bin -g bin -m 444 mp.0 ${DESTDIR}/usr/man/cat3
E 4

I 2
D 3
tags:
	cwd=`pwd`; \
	for i in ${SRCS}; do \
		ctags -a -f ${TAGSFILE} $$cwd/$$i; \
	done
E 3
I 3
D 4
lint: FRC
E 4
I 4
lint: ${SRCS}
E 4
	lint ${CFLAGS} ${SRCS}
E 3

E 2
D 3
clean:
D 2
	rm -f *.o libmp.a
E 2
I 2
	rm -f ${OBJS} libmp.a tags
E 3
I 3
D 4
tags: FRC
E 4
I 4
tags: ${SRCS}
E 4
	ctags ${SRCS}

FRC:
E 6
I 6
.include <bsd.lib.mk>
E 6
D 4

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

pow.o: pow.c /usr/include/mp.h
gcd.o: gcd.c /usr/include/mp.h
msqrt.o: msqrt.c /usr/include/mp.h
mdiv.o: mdiv.c /usr/include/mp.h
mout.o: mout.c /usr/include/stdio.h /usr/include/mp.h
mult.o: mult.c /usr/include/mp.h
madd.o: madd.c /usr/include/mp.h
util.o: util.c /usr/include/stdio.h /usr/include/mp.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 4
E 3
E 2
E 1
