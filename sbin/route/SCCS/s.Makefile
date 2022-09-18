h44322
s 00000/00000/00025
d D 8.1 93/06/05 11:12:57 bostic 11 10
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00001/00023
d D 5.10 93/05/19 17:31:41 bostic 10 9
c build tags
e
s 00001/00001/00023
d D 5.9 92/03/19 20:13:47 bostic 9 8
c mkdep needs keywords.h
e
s 00001/00001/00023
d D 5.8 92/03/16 14:26:11 bostic 8 7
c build the man page, too
e
s 00002/00001/00022
d D 5.7 91/11/15 17:31:26 bostic 7 6
c add route label
e
s 00001/00000/00022
d D 5.6 91/06/27 15:02:32 sklower 6 5
c add x25 addressing, ability to spell arbitrary sockaddrs.
e
s 00002/00000/00020
d D 5.5 90/11/29 17:04:11 sklower 5 4
c standard install should be suid root
e
s 00001/00001/00019
d D 5.4 90/06/07 13:47:54 sklower 4 3
c remove reference to /dev/stdin
e
s 00016/00044/00004
d D 5.3 90/05/11 13:04:37 bostic 3 2
c first pass for new make
e
s 00001/00001/00047
d D 5.2 89/05/11 13:56:01 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00048/00000/00000
d D 5.1 88/09/27 22:25:22 bostic 1 0
c date and time created 88/09/27 22:25:22 by bostic
e
u
U
t
T
I 1
D 3
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
E 3
I 3
#	%W% (Berkeley) %G%
E 3

D 3
CFLAGS=	-O
LIBC=	/lib/libc.a
SRCS=	route.c
OBJS=
MAN=	route.0
E 3
I 3
PROG=	route
MAN8=	route.0
I 6
SRCS=	route.c ccitt_addr.c
E 6
CFLAGS+=-I.
CLEANFILES+=keywords.h
I 5
BINOWN=	root
BINMODE=4555
E 5
E 3

D 3
all: route
E 3
I 3
D 7
all route depend lint tags: keywords.h
E 7
I 7
D 8
all: route
E 8
I 8
all: route ${MAN8}
E 8
D 9
route depend lint tags: keywords.h
E 9
I 9
D 10
route .depend lint tags: keywords.h
E 10
E 9
E 7
E 3

D 3
route: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c
E 3
I 3
keywords.h: keywords
	sed -e '/^#/d' -e '/^$$/d' ${.CURDIR}/keywords > _keywords.tmp
D 4
	tr a-z A-Z < _keywords.tmp | paste _keywords.tmp /dev/stdin | \
E 4
I 4
	tr a-z A-Z < _keywords.tmp | paste _keywords.tmp - | \
E 4
	    awk '{ \
		if (NF > 1) \
			printf "#define\tK_%s\t%d\n\t{\"%s\", K_%s},\n", \
			    $$2, NR, $$1, $$2 }' \
	    > ${.TARGET}
	rm -f _keywords.tmp
E 3

D 3
clean:
	rm -f ${OBJS} core route

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
D 2
	install -s -o bin -g bin -m 755 route ${DESTDIR}/etc/route
E 2
I 2
	install -s -o bin -g bin -m 755 route ${DESTDIR}/sbin
E 2
	install -c -o bin -g bin -m 444 route.0 ${DESTDIR}/usr/man/cat8

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 3
I 3
.include <bsd.prog.mk>
I 10

route .depend lint tags: keywords.h
E 10
E 3
E 1
