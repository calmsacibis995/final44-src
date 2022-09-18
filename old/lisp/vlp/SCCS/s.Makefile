h63363
s 00001/00017/00015
d D 5.4 91/07/01 14:40:01 bostic 4 3
c makefile's don't need copyrights
e
s 00001/00001/00031
d D 5.3 89/05/10 22:32:49 bostic 3 2
c minor cleanup
e
s 00005/00001/00027
d D 5.2 88/10/25 16:12:51 bostic 2 1
c add cleandir
e
s 00028/00000/00000
d D 5.1 88/10/25 16:07:19 bostic 1 0
c date and time created 88/10/25 16:07:19 by bostic
e
u
U
t
T
I 1
D 4
#
# Copyright (c) 1987 The Regents of the University of California.
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
# WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
#
E 4
#	%W% (Berkeley) %G%
D 4
#
E 4
I 4

E 4
MAN=	vlp.0

D 2
all vlp clean cleandir lint tags: FRC
E 2
I 2
D 3
all vlp clean lint tags: FRC
E 3
I 3
all clean depend lint tags: FRC
E 3
E 2
	cd vlp.${MACHINE}; make ${MFLAGS} DESTDIR=${DESTDIR} $@
I 2

cleandir: clean
	cd vlp.${MACHINE}; make ${MFLAGS} DESTDIR=${DESTDIR} $@
	rm -f ${MAN} tags .depend
E 2

install: ${MAN}
	cd vlp.${MACHINE}; make ${MFLAGS} DESTDIR=${DESTDIR} $@
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat1

FRC:
E 1
