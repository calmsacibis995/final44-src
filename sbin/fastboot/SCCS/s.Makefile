h53052
s 00000/00000/00012
d D 8.1 93/06/05 10:55:31 bostic 7 6
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00004/00012
d D 5.6 90/06/23 14:18:45 bostic 6 5
c don't need special targets now
e
s 00002/00001/00014
d D 5.5 90/05/24 16:55:01 bostic 5 4
c add man links
e
s 00013/00026/00003
d D 5.4 90/05/11 13:05:36 bostic 4 3
c first pass for new make
e
s 00004/00002/00025
d D 5.3 89/05/11 13:52:53 bostic 3 2
c file reorg, pathnames.h, paths.h
e
s 00001/00000/00026
d D 5.2 88/10/19 13:12:11 bostic 2 1
c add fasthalt
e
s 00026/00000/00000
d D 5.1 88/10/19 13:10:40 bostic 1 0
c date and time created 88/10/19 13:10:40 by bostic
e
u
U
t
T
I 1
D 4
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
E 4
I 4
#	%W% (Berkeley) %G%
E 4

D 4
MAN=	fastboot.0
E 4
I 4
MAN8=	fastboot.0
I 5
MLINKS=	fastboot.8 fasthalt.8
E 5
E 4

D 4
all fastboot clean cleandir depend lint tags:
E 4
I 4
D 6
all fastboot: ${MAN8}
E 4

D 4
install: ${MAN}
D 3
	install -c -o bin -g bin -m 755 fastboot.sh ${DESTDIR}/etc/fastboot
I 2
	install -c -o bin -g bin -m 755 fasthalt.sh ${DESTDIR}/etc/fasthalt
E 3
I 3
	install -c -o bin -g bin -m 755 fastboot.sh \
	    ${DESTDIR}/sbin/fastboot
	install -c -o bin -g bin -m 755 fasthalt.sh \
	    ${DESTDIR}/sbin/fasthalt
E 3
E 2
	install -c -o bin -g bin -m 444 ${MAN} ${DESTDIR}/usr/man/cat8
E 4
I 4
clean cleandir depend lint tags:

E 6
D 5
install: maninstall
E 5
I 5
beforeinstall:
E 5
	install -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${.CURDIR}/fastboot.sh ${DESTDIR}${BINDIR}/fastboot
	install -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${.CURDIR}/fasthalt.sh ${DESTDIR}${BINDIR}/fasthalt

.include <bsd.prog.mk>
E 4
E 1
