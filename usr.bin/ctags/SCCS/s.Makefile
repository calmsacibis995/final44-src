h38531
s 00000/00000/00007
d D 8.1 93/06/06 14:30:05 bostic 7 6
c 4.4BSD snapshot (revision 8.1)
e
s 00004/00045/00003
d D 5.6 90/05/11 13:50:48 bostic 6 5
c first pass for new make
e
s 00001/00001/00047
d D 5.5 89/05/10 22:19:16 bostic 5 4
c file reorg, pathnames.h, paths.h
e
s 00026/00039/00022
d D 5.4 88/10/22 16:45:51 bostic 4 3
c cleanup, add man page
e
s 00042/00011/00019
d D 5.3 87/06/16 19:28:33 bostic 3 2
c new template
e
s 00002/00000/00028
d D 5.2 87/05/31 21:07:45 bostic 2 1
c added depend label
e
s 00028/00000/00000
d D 5.1 87/03/16 18:00:32 bostic 1 0
c date and time created 87/03/16 18:00:32 by bostic
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
# Copyright (c) 1988 The Regents of the University of California.
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
DESTDIR=
CFLAGS=-O -I.
I 3
LIBC=	/lib/libc.a
E 6
I 6

PROG=	ctags
CFLAGS+=-I${.CURDIR}
E 6
E 3
SRCS=	C.c ctags.c fortran.c lisp.c print.c tree.c yacc.c
D 6
OBJS=	C.o ctags.o fortran.o lisp.o print.o tree.o yacc.o
I 4
MAN=	ctags.0
E 6
E 4

D 3
ctags: ${OBJS}
E 3
I 3
D 6
all: ctags

ctags: ${OBJS} ${LIBC}
E 3
	${CC} ${CFLAGS} -o $@ ${OBJS}

D 3
install: ctags
	install -o root -g staff -m 755 -s ctags ${DESTDIR}/usr/ucb
E 3
I 3
D 4
install: FRC
	install -s -o bin -g bin -m 755 ctags ${DESTDIR}/usr/ucb/ctags
E 3

D 3
clean:
	rm -f ctags *.o core
E 3
I 3
clean: FRC
E 4
I 4
clean:
E 4
	rm -f ${OBJS} core ctags
E 3

D 3
lint:
	lint -I. -chapbx ${SRCS}
E 3
I 3
D 4
lint: FRC
	lint ${CFLAGS} ${SRCS}
E 4
I 4
cleandir: clean
	rm -f ${MAN} tags .depend
E 4
E 3

D 3
tags:
	ctags -dt ${SRCS}
E 3
I 3
D 4
tags: FRC
	ctags ${SRCS}
E 3

I 2
D 3
depend:
E 3
I 3
depend: FRC
E 4
I 4
depend: ${SRCS}
E 4
	mkdep ${CFLAGS} ${SRCS}
E 3

E 2
D 3
${OBJS}: ctags.h
E 3
I 3
D 4
FRC:
E 4
I 4
install: ${MAN}
D 5
	install -s -o bin -g bin -m 755 ctags ${DESTDIR}/usr/ucb
E 5
I 5
	install -s -o bin -g bin -m 755 ctags ${DESTDIR}/usr/bin
E 5
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
E 4

D 4
# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.
E 4
I 4
lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}
E 4

D 4
C.o: C.c /usr/include/stdio.h
C.o:ctags.h
C.o: /usr/include/stdio.h /usr/include/ctype.h
ctags.o: ctags.c
ctags.o:ctags.h
ctags.o: /usr/include/stdio.h /usr/include/ctype.h /usr/include/strings.h
fortran.o: fortran.c
fortran.o:ctags.h
fortran.o: /usr/include/stdio.h /usr/include/ctype.h /usr/include/strings.h
lisp.o: lisp.c
lisp.o:ctags.h
lisp.o: /usr/include/stdio.h /usr/include/ctype.h /usr/include/strings.h
print.o: print.c /usr/include/sys/types.h /usr/include/sys/file.h
print.o:ctags.h
print.o: /usr/include/stdio.h /usr/include/ctype.h
tree.o: tree.c
tree.o:ctags.h
tree.o: /usr/include/stdio.h /usr/include/ctype.h /usr/include/strings.h
yacc.o: yacc.c
yacc.o:ctags.h
yacc.o: /usr/include/stdio.h /usr/include/ctype.h /usr/include/strings.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 4
I 4
tags: ${SRCS}
	ctags ${SRCS}
E 6
I 6
.include <bsd.prog.mk>
E 6
E 4
E 3
E 1
