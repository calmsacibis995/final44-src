h42164
s 00000/00000/00008
d D 8.1 93/06/06 14:37:05 bostic 8 7
c 4.4BSD snapshot (revision 8.1)
e
s 00005/00055/00003
d D 4.6 90/05/11 14:30:47 bostic 7 6
c first pass for new make
e
s 00003/00006/00055
d D 4.5 89/05/11 09:59:06 bostic 6 5
c file reorg, pathnames.h, paths.h
e
s 00025/00033/00034
d D 4.4 88/10/25 16:25:33 bostic 5 4
c add man page, cleanup
e
s 00053/00014/00014
d D 4.3 87/06/29 11:52:55 bostic 4 2
c new template
e
s 00053/00014/00014
d R 4.3 87/06/03 00:07:09 bostic 3 2
c new template
e
s 00002/00000/00026
d D 4.2 87/05/31 20:33:01 bostic 2 1
c added depend label
e
s 00026/00000/00000
d D 4.1 83/02/09 14:25:06 sam 1 0
c date and time created 83/02/09 14:25:06 by sam
e
u
U
t
T
I 1
D 4
#	%W%	%G%
E 4
D 7
#
I 4
D 5
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 5
I 5
# Copyright (c) 1987 The Regents of the University of California.
# All rights reserved.
E 5
#
D 5
#	%W%	(Berkeley)	%G%
E 5
I 5
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
E 5
#
E 7
I 5
#	%W% (Berkeley) %G%
D 7
#
E 5
E 4
D 6
DIFF=	/bin/diff
DIFFH=	/usr/lib/diffh
PR=	/bin/pr
CFLAGS=	-O -DDIFF='"${DIFF}"' -DDIFFH='"${DIFFH}"' -DPR='"${PR}"'
E 6
I 6
CFLAGS=	-O
E 6
D 4
DESTDIR=

E 4
I 4
LIBC=	/lib/libc.a
E 7
I 7

PROG=	diff
E 7
E 4
SRCS=	diff.c diffdir.c diffreg.c
D 4
HDRS=	diff.h
E 4
D 7
OBJS=	diff.o diffdir.o diffreg.o
I 4
HSRCS=	diffh.c
HOBJS=	diffh.o
I 5
MAN=	diff.0
E 7
I 7
MLINKS=	diff.1 diffh.1
E 7
E 5
E 4

D 7
all: diff diffh

D 4
diff: ${OBJS}
	cc ${CFLAGS} -o diff ${OBJS} ${LDFLAGS}
E 4
I 4
diff: ${OBJS} ${LIBC}
	${CC} ${CFLAGS} -o $@ ${OBJS}
E 4

D 4
diffh: diffh.o
	cc -o diffh diffh.o ${LDFLAGS}
E 4
I 4
diffh: ${HOBJS} ${LIBC}
	${CC} ${CFLAGS} -o $@ ${HOBJS}
E 4

I 2
D 4
depend:
E 4
I 4
D 5
clean: FRC
E 5
I 5
clean:
E 5
	rm -f ${HOBJS} ${OBJS} core diff diffh
E 4

E 2
D 4
clean:
	rm -f diff diffh ${OBJS} diffh.o
E 4
I 4
D 5
depend: FRC
E 5
I 5
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 5
	mkdep ${CFLAGS} ${HSRCS} ${SRCS}
E 4

D 4
install:
	install -s diff ${DESTDIR}/bin/diff
	install -s diffh ${DESTDIR}/usr/lib/diffh
E 4
I 4
D 5
install: FRC
E 5
I 5
install: ${MAN}
E 5
D 6
	install -s -o bin -g bin -m 755 diff ${DESTDIR}/bin/diff
	install -s -o bin -g bin -m 755 diffh ${DESTDIR}/usr/lib/diffh
E 6
I 6
	install -s -o bin -g bin -m 755 diff ${DESTDIR}/usr/bin/diff
	install -s -o bin -g bin -m 755 diffh ${DESTDIR}/usr/bin/diffh
E 6
I 5
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1
	rm -f ${DESTDIR}/usr/man/cat1/diffh.0
	ln ${DESTDIR}/usr/man/cat1/diff.0 ${DESTDIR}/usr/man/cat1/diffh.0
E 5

D 5
lint: FRC
E 5
I 5
lint: ${SRCS}
E 5
	lint ${CFLAGS} ${SRCS}
	lint ${CFLAGS} ${HSRCS}

D 5
tags: FRC
E 5
I 5
tags: ${SRCS}
E 5
	ctags ${SRCS}
	ctags ${HSRCS}
	sort -o tags tags
E 7
I 7
.include "../../Makefile.inc"
.include <bsd.prog.mk>
E 7
D 5

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

diffh.o: diffh.c /usr/include/stdio.h /usr/include/ctype.h
diffh.o: /usr/include/sys/types.h /usr/include/sys/stat.h
diff.o: diff.c diff.h /usr/include/stdio.h /usr/include/ctype.h
diff.o: /usr/include/sys/param.h /usr/include/sys/types.h /usr/include/signal.h
diff.o: /usr/include/machine/machparam.h /usr/include/sys/stat.h
diff.o: /usr/include/sys/dir.h /usr/include/signal.h
diffdir.o: diffdir.c diff.h /usr/include/stdio.h /usr/include/ctype.h
diffdir.o: /usr/include/sys/param.h /usr/include/sys/types.h
diffdir.o: /usr/include/signal.h /usr/include/machine/machparam.h
diffdir.o: /usr/include/sys/stat.h /usr/include/sys/dir.h /usr/include/signal.h
diffdir.o: /usr/include/a.out.h /usr/include/sys/exec.h
diffreg.o: diffreg.c diff.h /usr/include/stdio.h /usr/include/ctype.h
diffreg.o: /usr/include/sys/param.h /usr/include/sys/types.h
diffreg.o: /usr/include/signal.h /usr/include/machine/machparam.h
diffreg.o: /usr/include/sys/stat.h /usr/include/sys/dir.h /usr/include/signal.h
diffreg.o: /usr/include/a.out.h /usr/include/sys/exec.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 5
E 4
E 1
