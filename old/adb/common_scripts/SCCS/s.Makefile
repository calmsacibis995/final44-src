h56156
s 00001/00000/00020
d D 5.9 93/05/28 14:10:10 bostic 9 8
c clean the directory out before installing
e
s 00001/00001/00019
d D 5.8 93/04/26 19:09:57 bostic 8 7
c move scripts from /usr/libdata to /usr/old/libdata
e
s 00002/00001/00018
d D 5.7 90/06/08 13:57:59 bostic 7 6
c add obj, use prog not own
e
s 00014/00028/00005
d D 5.6 90/05/11 12:42:39 bostic 6 5
c first pass for new make
e
s 00001/00001/00032
d D 5.5 89/06/10 08:47:46 mckusick 5 4
c add why
e
s 00002/00009/00031
d D 5.4 89/05/08 12:52:39 bostic 4 3
c file system reorg
e
s 00010/00005/00030
d D 5.3 88/07/09 11:23:18 bostic 3 2
c install approved copyright notice
e
s 00001/00001/00034
d D 5.2 88/05/09 14:41:57 bostic 2 1
c remove dirblk, it's machine specific
e
s 00035/00000/00000
d D 5.1 88/03/30 16:04:09 bostic 1 0
c date and time created 88/03/30 16:04:09 by bostic
e
u
U
t
T
I 1
D 6
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
E 6
#	%W% (Berkeley) %G%
D 6
#
E 6
I 6

E 6
D 2
LIST=	buf callout callout.next clist clist.nxt dino dir dir.nxt dirblk \
E 2
I 2
LIST=	buf callout callout.next clist clist.nxt dino dir dir.nxt \
E 2
D 6
	dmap file filsys findinode findinode.nxt findproc host.nxt hosts \
	hosts.nxt hosttable idp ifaddr ifnet ifrw imp in_ifaddr inode inpcb \
	iovec ipreass ipreass.nxt mact mact.nxt mbstat mbuf mbuf.nxt \
	mbufchain mbufs mbufs.nxt mount nameidata nspcb nsrtentry packetchain \
	protosw quota rawcb route rtentry rusage setproc setproc.done socket \
	spp sppcb stat tcpcb tcpip tcpreass tcpreass.nxt text traceall \
D 5
	traceall.nxt u u.all ubadev uio un unpcb urppcb vtimes
E 5
I 5
	traceall.nxt u u.all ubadev uio un unpcb urppcb vtimes why
E 6
I 6
	dmap file filsys findinode findinode.nxt findproc host.nxt \
	hosts hosts.nxt hosttable idp ifaddr ifnet ifrw imp in_ifaddr \
	inode inpcb iovec ipreass ipreass.nxt mact mact.nxt mbstat \
	mbuf mbuf.nxt mbufchain mbufs mbufs.nxt mount nameidata \
	nspcb nsrtentry packetchain protosw quota rawcb route rtentry \
	rusage setproc setproc.done socket spp sppcb stat tcpcb tcpip \
	tcpreass tcpreass.nxt text traceall traceall.nxt tty termios \
	u u.all ubadev uio un unpcb urppcb vtimes why
I 7
NOOBJ=	noobj
E 7
E 6
E 5

D 6
all:
E 6
I 6
all clean cleandir depend lint tags:
E 6

D 6
install: FRC
D 4
	install -c -o bin -g bin -m 444 ${LIST} ${DESTDIR}/usr/lib/adb
E 4
I 4
	install -c -o bin -g bin -m 444 ${LIST} ${DESTDIR}/usr/libdata/adb
E 6
I 6
install:
I 9
	rm -f ${DESTDIR}/usr/old/libdata/adb/*
E 9
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${LIST} \
D 8
	    ${DESTDIR}/usr/libdata/adb
E 8
I 8
	    ${DESTDIR}/usr/old/libdata/adb
E 8
E 6
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
D 6
clean depend lint tags FRC:
E 6
I 6
D 7
.include <bsd.own.mk>
E 7
I 7
.include <bsd.prog.mk>
E 7
E 6
E 4
E 1
