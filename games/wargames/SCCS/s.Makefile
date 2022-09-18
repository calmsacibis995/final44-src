h57888
s 00000/00000/00010
d D 8.1 93/05/31 18:02:20 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00001/00008
d D 5.3 90/06/08 14:00:19 bostic 3 2
c use prog, don't need obj
e
s 00005/00020/00004
d D 5.2 90/05/11 12:45:41 bostic 2 1
c first pass for new make
e
s 00024/00000/00000
d D 5.1 88/10/19 15:51:23 bostic 1 0
c date and time created 88/10/19 15:51:23 by bostic
e
u
U
t
T
I 1
D 2
#
# Copyright (c) 1988 The Regents of the University of California.
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
E 2
#	%W% (Berkeley) %G%
D 2
#
MAN=
E 2

I 3
NOOBJ=	noobj
E 3
all wargames clean cleandir depend lint tags:

D 2
install: ${MAN}
	install -c -o bin -g bin -m 755 wargames.sh ${DESTDIR}/usr/games/wargames
E 2
I 2
install:
	install -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} wargames.sh \
	    ${DESTDIR}/usr/games/wargames

D 3
.include <bsd.own.mk>
E 3
I 3
.include <bsd.prog.mk>
E 3
E 2
E 1
