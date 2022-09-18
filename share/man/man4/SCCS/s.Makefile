h19901
s 00001/00001/00009
d D 8.2 94/05/19 16:50:08 mckusick 23 22
c add bpf.4
e
s 00000/00000/00010
d D 8.1 93/06/18 00:02:57 mckusick 22 21
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00009
d D 5.18 93/06/18 00:02:49 mckusick 21 19
c delete imp.4
e
s 00000/00000/00010
d R 8.1 93/06/17 23:21:43 mckusick 20 19
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00009
d D 5.17 93/06/17 23:21:17 mckusick 19 17
c kadb.4 is deprecated
e
s 00000/00000/00010
d R 8.1 93/06/05 13:48:14 bostic 18 17
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00009
d D 5.16 93/02/25 17:29:15 torek 17 16
c SUBDIR+=man4.sparc
e
s 00001/00001/00009
d D 5.15 92/07/20 14:35:27 marc 16 15
c add termios.0
e
s 00002/00001/00008
d D 5.14 91/06/17 12:37:33 bostic 15 13
c make stdin, stdout, stderr link to fd
e
s 00001/00001/00008
d D 5.13.1.1 91/05/07 21:50:36 bostic 14 13
c branch for the 2nd network distribution
e
s 00001/00001/00008
d D 5.13 91/03/12 15:35:37 mckusick 13 12
c add unix.4 man page
e
s 00001/00001/00008
d D 5.12 91/02/09 21:07:16 william 12 11
c i386 entry
e
s 00001/00001/00008
d D 5.11 91/02/04 15:38:02 bostic 11 10
c bk.4 -> old/berknet
e
s 00001/00001/00008
d D 5.10 90/07/25 22:36:41 sklower 10 9
c add manual page for esis
e
s 00000/00007/00009
d D 5.9 90/07/01 10:35:13 bostic 9 8
c don't need extra labels
e
s 00001/00001/00015
d D 5.8 90/06/29 18:41:38 bostic 8 7
c %s
e
s 00000/00002/00016
d D 5.7 90/06/22 19:06:09 bostic 7 6
c don't need install/maninstall
e
s 00003/00002/00015
d D 5.6 90/06/07 16:21:59 sklower 6 5
c add man pages for clnp, cltp, route, iso, tp
e
s 00012/00026/00005
d D 5.5 90/05/11 13:56:24 bostic 5 4
c first pass for new make
e
s 00001/00001/00030
d D 5.4 90/05/10 15:02:59 bostic 4 3
c checkpoint for pmake
e
s 00009/00019/00022
d D 5.3 89/03/06 11:02:18 bostic 3 2
c move man pages into source tree
e
s 00010/00005/00031
d D 5.2 88/07/09 11:38:34 bostic 2 1
c install approved copyright notice
e
s 00036/00000/00000
d D 5.1 87/12/12 18:19:18 bostic 1 0
c date and time created 87/12/12 18:19:18 by bostic
e
u
U
f b 
t
T
I 1
D 5
#
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
D 2
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
# is provided ``as is'' without express or implied warranty.
E 2
I 2
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
E 2
#
E 5
#	%W% (Berkeley) %G%
D 5
#
D 3
MDIR=	/usr/man/cat4
SRCS=	arp.4 bk.4 drum.4 icmp.4 idp.4 imp.4 inet.4 ip.4 kdb.4 \
	lo.4 netintro.4 ns.4 nsip.4 null.4 pty.4 spp.4 tcp.4 tty.4 udp.4
OBJS=	arp.0 bk.0 drum.0 icmp.0 idp.0 imp.0 inet.0 ip.0 kdb.0 \
	lo.0 netintro.0 ns.0 nsip.0 null.0 pty.0 spp.0 tcp.0 tty.0 udp.0
LINKS=	networking.0
E 3
I 3
#
D 4
MDIR=	${DESTDIR}/usr/man/cat4
E 4
I 4
MDIR=	${DESTDIR}/usr/share/man/cat4
E 4
OBJS=	bk.0 drum.0 icmp.0 idp.0 imp.0 inet.0 ip.0 kadb.0 lo.0 netintro.0 \
	ns.0 nsip.0 null.0 pty.0 spp.0 tcp.0 tty.0 udp.0
E 5
E 3

D 3
.SUFFIXES: .4 .0
E 3
I 3
D 5
all clean depend lint tags:
E 5
I 5
D 6
MAN4=	bk.0 drum.0 fd.0 icmp.0 idp.0 imp.0 inet.0 ip.0 kadb.0 lo.0 \
	netintro.0 ns.0 nsip.0 null.0 pty.0 spp.0 tcp.0 tty.0 udp.0
E 6
I 6
D 10
MAN4=	bk.0 clnp.0 cltp.0 drum.0 fd.0 icmp.0 idp.0 imp.0 inet.0 ip.0 \
E 10
I 10
D 11
MAN4=	bk.0 clnp.0 cltp.0 drum.0 esis.0 fd.0 icmp.0 idp.0 imp.0 inet.0 ip.0 \
E 11
I 11
D 21
MAN4=	clnp.0 cltp.0 drum.0 esis.0 fd.0 icmp.0 idp.0 imp.0 inet.0 ip.0 \
E 21
I 21
D 23
MAN4=	clnp.0 cltp.0 drum.0 esis.0 fd.0 icmp.0 idp.0 inet.0 ip.0 \
E 23
I 23
MAN4=	bpf.0 clnp.0 cltp.0 drum.0 esis.0 fd.0 icmp.0 idp.0 inet.0 ip.0 \
E 23
E 21
E 11
E 10
D 19
	iso.0 kadb.0 lo.0 netintro.0 ns.0 nsip.0 null.0 pty.0 route.0 \
E 19
I 19
	iso.0 lo.0 netintro.0 ns.0 nsip.0 null.0 pty.0 route.0 \
E 19
D 13
	spp.0 tcp.0 tp.0 tty.0 udp.0
E 13
I 13
D 14
D 16
	spp.0 tcp.0 tp.0 tty.0 udp.0 unix.0
E 16
I 16
	spp.0 tcp.0 termios.0 tp.0 tty.0 udp.0 unix.0
E 16
E 14
I 14
	spp.0 tcp.0 tp.0 udp.0 unix.0
E 14
E 13
E 6
D 15
MLINKS=	netintro.4 networking.4
E 15
I 15
MLINKS+=fd.4 stderr.4 fd.4 stdin.4 fd.4 stdout.4
MLINKS+=netintro.4 networking.4
E 15
D 8
SUBDIR=	man4.tahoe man4.vax
E 8
I 8
D 12
SUBDIR=	man4.hp300 man4.tahoe man4.vax
E 12
I 12
D 17
SUBDIR=	man4.hp300 man4.tahoe man4.vax man4.i386
E 17
I 17
SUBDIR=	man4.hp300 man4.i386 man4.sparc man4.tahoe man4.vax
E 17
E 12
E 8
E 5
E 3

I 5
D 9
all: ${MAN4}

clean depend lint tags:

E 5
D 3
.4.0:
	${DESTDIR}/usr/man/manroff $*.4 > $*.0

all: ${OBJS}

clean: FRC
E 3
I 3
cleandir:
E 3
D 5
	rm -f ${OBJS}
E 5
I 5
	rm -f ${MAN4}
E 5

E 9
D 3
install: FRC
	cd ${DESTDIR}${MDIR}; rm -f *.0
	install -c -o bin -g bin -m 444 ${OBJS} ${DESTDIR}${MDIR}
	ln ${DESTDIR}${MDIR}/netintro.0 ${DESTDIR}${MDIR}/networking.0

FRC:
E 3
I 3
D 5
install: ${OBJS}
	install -c -o bin -g bin -m 444 ${OBJS} ${MDIR}
	rm -f ${MDIR}/networking.0; ln ${MDIR}/netintro.0 ${MDIR}/networking.0
E 5
I 5
D 7
install: maninstall

E 7
.include <bsd.prog.mk>
E 5
E 3
E 1
