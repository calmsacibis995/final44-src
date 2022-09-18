h60162
s 00000/00000/00012
d D 8.1 93/06/08 11:35:05 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00001/00010
d D 5.3 90/06/08 14:35:05 bostic 3 2
c don't need obj, use bsd.prog.mk
e
s 00005/00019/00006
d D 5.2 90/05/11 13:54:51 bostic 2 1
c first pass for new make
e
s 00025/00000/00000
d D 5.1 90/03/24 10:15:23 bostic 1 0
c date and time created 90/03/24 10:15:23 by bostic
e
u
U
t
T
I 1
D 2
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
E 2
I 2
#	%W% (Berkeley) %G%
E 2

FILES=	dot.cshrc dot.login dot.mailrc dot.profile dot.rhosts
I 3
NOOBJ=	noobj
E 3

all clean cleandir depend lint tags:

install:
D 2
	install -c -o bin -g bin -m 444 ${FILES} ${DESTDIR}/usr/share/skel
E 2
I 2
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${FILES} \
	    ${DESTDIR}${BINDIR}/skel

D 3
.include <bsd.own.mk>
E 3
I 3
.include <bsd.prog.mk>
E 3
E 2
E 1
