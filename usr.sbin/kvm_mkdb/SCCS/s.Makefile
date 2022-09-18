h18622
s 00000/00000/00007
d D 8.1 93/06/06 13:58:38 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00006
d D 5.2 92/05/04 17:18:15 bostic 4 3
c add testdb.c
e
s 00001/00000/00006
d D 5.1 91/02/12 22:58:46 bostic 3 2
c break kernel nlist stuff into a separate file
e
s 00003/00045/00003
d D 1.2 90/05/11 16:03:59 bostic 2 1
c first pass for new make
e
s 00048/00000/00000
d D 1.1 90/03/07 14:45:46 marc 1 0
c date and time created 90/03/07 14:45:46 by marc
e
u
U
t
T
I 1
D 2
#
# Copyright (c) 1989 The Regents of the University of California.
# All rights reserved.
#
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
#
E 2
#	%W% (Berkeley) %G%
D 2
#
E 2

D 2
CFLAGS=	-O
LIBC=	/lib/libc.a
SRCS=	kvm_mkdb.c
OBJS=
MAN=	kvm_mkdb.0
E 2
I 2
PROG=	kvm_mkdb
I 3
D 4
SRCS=	kvm_mkdb.c nlist.c
E 4
I 4
SRCS=	kvm_mkdb.c nlist.c testdb.c
E 4
E 3
MAN8=	kvm_mkdb.0
E 2

D 2
all: kvm_mkdb

kvm_mkdb: ${LIBC}
	${CC} -o $@ ${CFLAGS} $@.c

clean:
	rm -f ${OBJS} core kvm_mkdb

cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
	mkdep -p ${CFLAGS} ${SRCS}

install: ${MAN}
	install -s -o bin -g bin kvm_mkdb ${DESTDIR}/usr/sbin
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat8

lint: ${SRCS}
	lint ${CFLAGS} ${SRCS}

tags: ${SRCS}
	ctags ${SRCS}
E 2
I 2
.include <bsd.prog.mk>
E 2
E 1
