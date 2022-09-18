h12360
s 00002/00002/00006
d D 4.6 90/06/01 15:37:29 bostic 6 5
c do links right
e
s 00005/00047/00003
d D 4.5 90/05/11 12:50:11 bostic 5 4
c first pass for new make
e
s 00027/00024/00023
d D 4.4 89/05/10 22:40:40 bostic 4 3
c new template
e
s 00034/00013/00013
d D 4.3 87/06/19 11:22:22 bostic 3 2
c new template
e
s 00012/00007/00014
d D 4.2 85/05/30 22:53:28 sam 2 1
c add tags; a bit of cleanup
e
s 00021/00000/00000
d D 4.1 82/12/25 10:41:44 sam 1 0
c date and time created 82/12/25 10:41:44 by sam
e
u
U
t
T
I 1
D 3
#	%W%	%G%
E 3
D 5
#
D 3
CFLAGS = -O
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
E 5
I 4
#	%W% (Berkeley) %G%
D 5
#
E 4
CFLAGS=	-O
LIBC=	/lib/libc.a
E 5
I 5

LIB=	ln
E 5
E 3
I 2
SRCS=	allprint.c main.c reject.c yyless.c yywrap.c
D 5
OBJS=	allprint.o main.o reject.o yyless.o yywrap.o
E 5
I 5
D 6
LINKS=	${DESTDIR}/usr/lib/libln.a ${DESTDIR}/usr/lib/libl.a \
	${DESTDIR}/usr/lib/libln_p.a ${DESTDIR}/usr/lib/libl_p.a
E 6
I 6
LINKS=	${LIBDIR}/libln.a ${LIBDIR}/libl.a \
	${LIBDIR}/libln_p.a ${LIBDIR}/libl_p.a
E 6
E 5
D 3
TAGSFILE=tags
E 3
E 2

D 5
all: libln.a

D 2
libln.a:
	cc -c -O allprint.c main.c reject.c yyless.c
	cc -c -O yywrap.c
	rm -f libln.a
	ar rvc libln.a allprint.o main.o reject.o yyless.o yywrap.o
	rm allprint.o main.o reject.o yyless.o yywrap.o
E 2
I 2
libln.a: ${OBJS}
D 3
	ar rc libln.a ${OBJS}
E 3
I 3
D 4
	ar rc $@ ${OBJS}
E 4
I 4
	@echo building normal libln
	@ar rc $@ ${OBJS}
	ranlib libln.a
E 4
E 3
E 2

D 3
install: all
	install libln.a ${DESTDIR}/usr/lib
E 3
I 3
D 4
clean: FRC
E 4
I 4
clean:
E 4
	rm -f ${OBJS} core libln.a

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
	install -o bin -g bin -m 644 libln.a ${DESTDIR}/usr/lib/libln.a
I 4
	ranlib -t ${DESTDIR}/usr/lib/libln.a
E 4
E 3
	rm -f ${DESTDIR}/usr/lib/libl.a
	ln ${DESTDIR}/usr/lib/libln.a ${DESTDIR}/usr/lib/libl.a
D 4
	ranlib ${DESTDIR}/usr/lib/libln.a
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
	rm -f *.o libln.a
E 2
I 2
	rm -f ${OBJS} libln.a tags
E 3
I 3
D 4
tags: FRC
E 4
I 4
tags: ${SRCS}
E 4
	ctags ${SRCS}
E 5
I 5
.include <bsd.lib.mk>
E 5
D 4

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

allprint.o: allprint.c /usr/include/stdio.h
main.o: main.c /usr/include/stdio.h
reject.o: reject.c /usr/include/stdio.h
yyless.o: yyless.c
yywrap.o: yywrap.c

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 4
E 3
E 2
E 1
