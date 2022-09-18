h20358
s 00001/00001/00013
d D 5.7 93/04/26 19:09:38 bostic 7 6
c move scripts from /usr/libdata to /usr/old/libdata
e
s 00002/00001/00012
d D 5.6 90/06/08 13:57:49 bostic 6 5
c add obj, use prog not own
e
s 00007/00023/00006
d D 5.5 90/05/11 12:42:55 bostic 5 4
c first pass for new make
e
s 00002/00008/00027
d D 5.4 89/05/08 12:51:08 bostic 4 3
c file system reorg
e
s 00010/00005/00025
d D 5.3 88/07/09 11:23:59 bostic 3 2
c install approved copyright notice
e
s 00003/00002/00027
d D 5.2 88/05/09 14:43:33 bostic 2 1
c add dirblk 
e
s 00029/00000/00000
d D 5.1 88/03/30 16:01:18 bostic 1 0
c date and time created 88/03/30 16:01:18 by bostic
e
u
U
t
T
I 1
D 5
#
# Copyright (c) 1988 Regents of the University of California.
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
D 3
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific written prior permission. This software
# is provided ``as is'' without express or implied warranty.
E 3
I 3
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
E 3
#
E 5
#	%W% (Berkeley) %G%
D 5
#
E 5
I 5

E 5
D 2
LIST=	dmcstats findproc.nxt frame ifuba ifubinfo ifxmt mba_device mba_hd \
	pcb proc setproc.nxt stacktrace trapframe tty ubahd
E 2
I 2
LIST=	dirblk dmcstats findproc.nxt frame ifuba ifubinfo ifxmt \
	mba_device mba_hd pcb proc setproc.nxt stacktrace trapframe \
D 5
	tty ubahd
E 5
I 5
	ubahd
I 6
NOOBJ=	noobj
E 6
E 5
E 2

D 5
all:
E 5
I 5
all clean cleandir depend lint tags:
E 5

D 5
install: FRC
D 4
	install -c -o bin -g bin -m 444 ${LIST} ${DESTDIR}/usr/lib/adb
E 4
I 4
	install -c -o bin -g bin -m 444 ${LIST} ${DESTDIR}/usr/libdata/adb
E 5
I 5
install:
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${LIST} \
D 7
	    ${DESTDIR}/usr/libdata/adb
E 7
I 7
	    ${DESTDIR}/usr/old/libdata/adb
E 7
E 5
E 4

D 4
clean:
depend:
lint:
tags:
FRC:

# DO NOT DELETE THIS LINE -- make depend uses it
E 4
I 4
D 5
clean depend lint tags FRC:
E 4

E 5
I 5
D 6
.include <bsd.own.mk>
E 6
I 6
.include <bsd.prog.mk>
E 6
E 5
E 1
