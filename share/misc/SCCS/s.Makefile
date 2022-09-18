h56620
s 00000/00000/00013
d D 8.1 93/06/08 11:37:01 bostic 15 14
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00012
d D 5.14 92/08/27 11:28:25 bostic 14 13
c add flowers
e
s 00001/00001/00012
d D 5.13 91/05/07 17:42:46 bostic 13 12
c delete greek from the distribution
e
s 00001/00001/00012
d D 5.12 91/02/08 13:39:18 bostic 12 11
c add zipcodes
e
s 00001/00001/00012
d D 5.11 91/01/21 20:15:25 cael 11 10
c .
e
s 00001/00001/00012
d D 5.10 90/06/24 17:40:39 bostic 10 9
c birthday -> birthtoken
e
s 00003/00004/00010
d D 5.9 90/06/08 14:35:54 bostic 9 8
c don't need obj, use bsd.prog.mk
e
s 00001/00024/00013
d D 5.8 90/06/01 17:59:25 bostic 8 7
c missed some redist stuff
e
s 00001/00001/00036
d D 5.7 90/06/01 17:55:51 bostic 7 6
c move redist stuff to share/copyr directory
e
s 00007/00002/00030
d D 5.6 90/05/15 22:48:13 mckusick 6 5
c add redist.gas
e
s 00002/00001/00030
d D 5.5 90/05/10 11:18:24 bostic 5 4
c put .include last
e
s 00005/00005/00026
d D 5.4 90/05/10 10:55:48 bostic 4 3
c add airport
e
s 00021/00002/00010
d D 5.3 90/05/09 10:09:12 mckusick 3 2
c add rules for generating redist files
e
s 00006/00019/00006
d D 5.2 90/05/09 10:01:27 bostic 2 1
c new makefile format
e
s 00025/00000/00000
d D 5.1 90/03/24 10:12:36 bostic 1 0
c date and time created 90/03/24 10:12:36 by bostic
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
FILES=	ascii eqnchar greek inter.phone man.template na.phone operator
E 2
I 2
D 4
FILES=	ascii birthday eqnchar greek inter.phone man.template na.phone \
	noredist.c operator redist.c redist.man redist.sh
E 4
I 4
D 10
FILES=	airport ascii birthday eqnchar greek inter.phone man.template \
E 10
I 10
D 13
FILES=	airport ascii birthtoken eqnchar greek inter.phone man.template \
E 13
I 13
D 14
FILES=	airport ascii birthtoken eqnchar inter.phone man.template \
E 14
I 14
FILES=	airport ascii birthtoken eqnchar flowers inter.phone man.template \
E 14
E 13
E 10
D 6
	na.phone noredist.c operator redist.c redist.man redist.sh
E 6
I 6
D 7
	na.phone noredist.c operator redist.c redist.man redist.sh redist.gas
E 7
I 7
D 11
	na.phone operator
E 11
I 11
D 12
	mdoc.template na.phone operator
E 12
I 12
	mdoc.template na.phone operator zipcodes
E 12
E 11
I 9
NOOBJ=	noobj
E 9
E 7
E 6
E 4
E 2

D 3
all clean cleandir depend lint tags:
E 3
I 3
D 9
all: ${FILES}
E 9
I 9
all clean cleandir depend lint tags:
E 9
D 5
.include <bsd.own.mk>
E 5
E 3

I 3
D 8
clean cleandir:
D 6
	rm -f redist.c redist.sh redist.man
E 6
I 6
	rm -f redist.c redist.sh redist.man redist.gas
E 6

E 8
E 3
install:
D 2
	install -c -o bin -g bin -m 444 ${FILES} ${DESTDIR}/usr/share/misc
E 2
I 2
	cd ${.CURDIR}; install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${FILES} \
	    ${DESTDIR}${BINDIR}/misc

D 3
.include <bsd.own.mk>
E 3
I 3
D 8
depend lint tags:

redist.c: redist
	rm -f redist.c
D 4
	sed 's/^/ */' <redist >redist.c
E 4
I 4
	sed 's/^/ */' < redist > redist.c
E 4
	chmod 444 redist.c

redist.sh: redist
	rm -f redist.sh
D 4
	sed 's/^/#/' <redist >redist.sh
E 4
I 4
	sed 's/^/#/' < redist > redist.sh
E 4
	chmod 444 redist.sh

redist.man: redist
	rm -f redist.man
D 4
	sed 's/^/.\\"/' <redist >redist.man
E 4
I 4
	sed 's/^/.\\"/' < redist > redist.man
E 4
	chmod 444 redist.man
I 6

redist.gas: redist
	rm -f redist.gas
	sed 's/^/|/' < redist > redist.gas
	chmod 444 redist.gas
E 8
I 8
D 9
clean cleandir depend lint tags:
E 8
E 6
I 5

.include <bsd.own.mk>
E 9
I 9
.include <bsd.prog.mk>
E 9
E 5
E 3
E 2
E 1
