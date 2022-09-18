h53788
s 00000/00000/00013
d D 8.1 93/06/12 17:05:14 bostic 27 26
c add 1993 to the copyright notice, yank to 8.1 for 4.4BSD snapshot
e
s 00001/00001/00012
d D 5.19 93/06/12 16:45:22 mckusick 26 24
c delete -h option for printing out IMP host table
e
s 00000/00000/00013
d R 8.1 93/06/06 15:44:27 bostic 25 24
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00000/00012
d D 5.18 93/06/03 16:09:49 bostic 24 23
c look for netimp in /sys
e
s 00003/00001/00009
d D 5.17 92/07/14 09:51:27 bostic 23 22
c don't include .c files, this breaks if /usr/include is a copy!
e
s 00001/00001/00009
d D 5.16 92/07/06 15:36:20 sklower 22 21
c Multicast changes from lbl
e
s 00002/00002/00008
d D 5.15 92/05/27 18:11:57 sklower 21 20
c incorporate changes for new kvm interfaces from lbl
e
s 00002/00000/00008
d D 5.14 90/06/18 17:20:18 sklower 20 19
c use kvm_nlist to avoid numerous lseeks of nlist; use kvm_read to avoid duplication.
e
s 00005/00044/00003
d D 5.13 90/05/11 15:22:08 bostic 19 18
c first pass for new make
e
s 00002/00002/00045
d D 5.12 89/09/25 15:38:43 sklower 18 17
c add support for ISO
e
s 00001/00001/00046
d D 5.11 89/05/11 09:37:13 bostic 17 16
c file reorg, pathnames.h, paths.h
e
s 00010/00064/00037
d D 5.10 88/09/20 18:31:41 bostic 16 15
c update
e
s 00011/00006/00090
d D 5.9 88/06/29 20:41:58 bostic 15 14
c install approved copyright notice
e
s 00010/00004/00086
d D 5.8 88/02/07 20:38:11 karels 14 13
c new copyrights
e
s 00080/00011/00010
d D 5.7 87/06/16 18:37:26 bostic 13 12
c new template
e
s 00002/00000/00019
d D 5.6 87/05/31 21:12:31 bostic 12 11
c added depend label
e
s 00000/00000/00019
d D 5.5 86/01/18 12:48:51 karels 11 10
x 9
c rm bbnnet
e
s 00001/00001/00018
d D 5.4 86/01/11 20:47:38 lepreau 10 9
c clean better
e
s 00001/00001/00018
d D 5.3 85/09/18 16:57:36 karels 9 8
c for walsh
e
s 00001/00001/00018
d D 5.2 85/08/16 19:40:14 sklower 8 7
c Add XNS statistics and control blocks; fix bug printing port numbers
e
s 00007/00001/00012
d D 5.1 85/06/04 15:34:41 dist 7 6
c Add copyright
e
s 00001/00001/00012
d D 4.6 84/10/05 15:22:01 sam 6 5
c fix install (requires setgid kmem)
e
s 00002/00002/00011
d D 4.5 84/06/03 11:13:48 sam 5 4
c addr unix domain sockets with -u flag
e
s 00000/00005/00013
d D 4.4 82/12/18 19:09:23 sam 4 3
c no more asm.sed
e
s 00002/00002/00016
d D 4.3 82/10/21 14:36:50 sam 3 2
c DESTDIR
e
s 00002/00001/00016
d D 4.2 82/10/06 10:32:42 sam 2 1
c sundries
e
s 00017/00000/00000
d D 4.1 82/08/25 22:21:49 sam 1 0
c date and time created 82/08/25 22:21:49 by sam
e
u
U
t
T
I 15
D 19
#
E 15
I 2
D 5
# %W% %G%
E 2
I 1
OBJS=	host.o inet.o if.o main.o mbuf.o route.o
E 5
I 5
D 7
#	%M% (Berkeley) %G%
E 7
I 7
D 14
#
E 14
D 13
# Copyright (c) 1983 Regents of the University of California.
E 13
I 13
# Copyright (c) 1987 Regents of the University of California.
E 13
D 14
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
E 14
I 14
# All rights reserved.
E 14
#
D 13
#	%W% (Berkeley) %G%
E 13
I 13
D 14
#	%W%	(Berkeley)	%G%
E 14
I 14
# Redistribution and use in source and binary forms are permitted
D 15
# provided that this notice is preserved and that due credit is given
# to the University of California at Berkeley. The name of the University
# may not be used to endorse or promote products derived from this
# software without specific prior written permission. This software
# is provided ``as is'' without express or implied warranty.
E 15
I 15
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
E 15
#
E 19
#	%W% (Berkeley) %G%
D 15
#
E 15
E 14
E 13
D 19
#
I 13
CFLAGS=	-O
LIBC=	/lib/libc.a
E 19
I 19

PROG=	netstat
E 19
D 18
SRCS=	host.c inet.c if.c main.c mbuf.c route.c unix.c ns.c
E 13
E 7
D 8
OBJS=	host.o inet.o if.o main.o mbuf.o route.o unix.o
E 8
I 8
D 9
OBJS=	host.o inet.o if.o main.o mbuf.o route.o unix.o ns.o
E 18
I 18
D 22
SRCS=	host.c inet.c if.c main.c mbuf.c route.c unix.c ns.c iso.c
E 22
I 22
D 23
SRCS=	host.c inet.c if.c main.c mbuf.c route.c unix.c ns.c iso.c mroute.c
E 23
I 23
D 26
SRCS=	host.c if.c inet.c iso.c main.c mbuf.c mroute.c ns.c route.c \
E 26
I 26
SRCS=	if.c inet.c iso.c main.c mbuf.c mroute.c ns.c route.c \
E 26
	tp_astring.c unix.c
I 24
CFLAGS+=-I/sys
E 24
.PATH:	${.CURDIR}/../../sys/netiso
E 23
E 22
D 19
OBJS=	host.o inet.o if.o main.o mbuf.o route.o unix.o ns.o iso.o
E 18
I 16
MAN=	netstat.0
E 19
I 19
BINGRP=	kmem
BINMODE=2555
I 20
D 21
LDADD=	-lutil
DPADD=	${LIBUTIL}
E 21
I 21
LDADD=	-lkvm
DPADD=	${LIBKVM}
E 21
E 20
E 19
E 16
E 9
I 9
OBJS=	host.o inet.o if.o main.o mbuf.o route.o unix.o ns.o bbnnet.o
E 9
E 8
E 5
D 13
CFLAGS=-O
D 3
DESTDIR=/usr/ucb
E 3
I 3
DESTDIR=
E 13
E 3

D 4
.c.o:
	${CC} -S ${CFLAGS} $*.c
	sed -f ../asm.sed $*.s | ${AS} -o $*.o
	rm -f $*.s

E 4
D 13
netstat: ${OBJS}
	${CC} ${OBJS} -o netstat
E 13
I 13
D 19
all: netstat
E 13

D 13
install: netstat
D 3
	install -s netstat ${DESTDIR}
E 3
I 3
D 6
	install -s netstat ${DESTDIR}/usr/ucb
E 6
I 6
	install -s -m 2755 -g kmem netstat ${DESTDIR}/usr/ucb/netstat
E 13
I 13
netstat: ${OBJS} ${LIBC}
	${CC} -o $@ ${CFLAGS} ${OBJS}
E 13
E 6
E 3

D 13
clean:
D 2
	rm -f *.o core a.out
E 2
I 2
D 10
	rm -f *.o core a.out errs
E 10
I 10
	rm -f *.o core a.out errs netstat
E 13
I 13
D 16
clean: FRC
E 16
I 16
clean:
E 16
	rm -f ${OBJS} core netstat
E 13
I 12

D 13
depend:
E 13
I 13
D 16
depend: FRC
E 16
I 16
cleandir: clean
	rm -f ${MAN} tags .depend

depend: ${SRCS}
E 16
	mkdep ${CFLAGS} ${SRCS}

D 16
install: FRC
E 16
I 16
install: ${MAN}
E 16
D 17
	install -s -o bin -g kmem -m 2755 netstat ${DESTDIR}/usr/ucb/netstat
E 17
I 17
	install -s -o bin -g kmem -m 2755 netstat ${DESTDIR}/usr/bin
E 17
I 16
	install -c -o bin -g bin -m 444 netstat.0 ${DESTDIR}/usr/man/cat1
E 16

D 16
lint: FRC
E 16
I 16
lint: ${SRCS}
E 16
	lint ${CFLAGS} ${SRCS}

D 16
tags: FRC
E 16
I 16
tags: ${SRCS}
E 16
	ctags ${SRCS}
E 19
I 19
.include <bsd.prog.mk>
E 19
D 16

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

host.o: host.c /usr/include/sys/types.h /usr/include/sys/mbuf.h
host.o: /usr/include/netinet/in.h /usr/include/netimp/if_imp.h
host.o: /usr/include/netimp/if_imphost.h
inet.o: inet.c /usr/include/strings.h /usr/include/stdio.h
inet.o: /usr/include/sys/param.h /usr/include/sys/types.h /usr/include/signal.h
inet.o: /usr/include/machine/machparam.h /usr/include/sys/socket.h
inet.o: /usr/include/sys/socketvar.h /usr/include/sys/mbuf.h
inet.o: /usr/include/sys/protosw.h /usr/include/net/route.h
inet.o: /usr/include/netinet/in.h /usr/include/netinet/in_systm.h
inet.o: /usr/include/netinet/in_pcb.h /usr/include/netinet/ip.h
inet.o: /usr/include/netinet/ip_icmp.h /usr/include/netinet/icmp_var.h
inet.o: /usr/include/netinet/ip_var.h /usr/include/netinet/tcp.h
inet.o: /usr/include/netinet/tcpip.h /usr/include/netinet/tcp_seq.h
inet.o: /usr/include/netinet/tcp_fsm.h /usr/include/netinet/tcp_timer.h
inet.o: /usr/include/netinet/tcp_var.h /usr/include/netinet/tcp_debug.h
inet.o: /usr/include/netinet/udp.h /usr/include/netinet/udp_var.h
inet.o: /usr/include/netdb.h
if.o: if.c /usr/include/sys/types.h /usr/include/sys/socket.h
if.o: /usr/include/net/if.h /usr/include/net/if_arp.h /usr/include/netinet/in.h
if.o: /usr/include/netinet/in_var.h /usr/include/netns/ns.h
if.o: /usr/include/stdio.h /usr/include/signal.h
main.o: main.c /usr/include/sys/param.h /usr/include/sys/types.h
main.o: /usr/include/signal.h /usr/include/machine/machparam.h
main.o: /usr/include/sys/vmmac.h /usr/include/sys/socket.h
main.o: /usr/include/machine/pte.h /usr/include/ctype.h /usr/include/errno.h
main.o: /usr/include/netdb.h /usr/include/nlist.h /usr/include/stdio.h
mbuf.o: mbuf.c /usr/include/stdio.h /usr/include/sys/param.h
mbuf.o: /usr/include/sys/types.h /usr/include/signal.h
mbuf.o: /usr/include/machine/machparam.h /usr/include/sys/mbuf.h
route.o: route.c /usr/include/stdio.h /usr/include/strings.h
route.o: /usr/include/sys/param.h /usr/include/sys/types.h
route.o: /usr/include/signal.h /usr/include/machine/machparam.h
route.o: /usr/include/sys/socket.h /usr/include/sys/mbuf.h
route.o: /usr/include/net/if.h /usr/include/net/if_arp.h
route.o: /usr/include/net/route.h /usr/include/netinet/in.h
route.o: /usr/include/netns/ns.h /usr/include/netdb.h
unix.o: unix.c /usr/include/sys/param.h /usr/include/sys/types.h
unix.o: /usr/include/signal.h /usr/include/machine/machparam.h
unix.o: /usr/include/sys/protosw.h /usr/include/sys/socket.h
unix.o: /usr/include/sys/socketvar.h /usr/include/sys/mbuf.h
unix.o: /usr/include/sys/un.h /usr/include/sys/unpcb.h /usr/include/sys/file.h
ns.o: ns.c /usr/include/stdio.h /usr/include/errno.h /usr/include/nlist.h
ns.o: /usr/include/sys/types.h /usr/include/sys/socket.h
ns.o: /usr/include/sys/socketvar.h /usr/include/sys/mbuf.h
ns.o: /usr/include/sys/protosw.h /usr/include/net/route.h /usr/include/net/if.h
ns.o: /usr/include/net/if_arp.h /usr/include/netinet/tcp_fsm.h
ns.o: /usr/include/netinet/tcp_timer.h /usr/include/netns/ns.h
ns.o: /usr/include/netns/ns_pcb.h /usr/include/netns/idp.h
ns.o: /usr/include/netns/idp_var.h /usr/include/netns/ns_error.h
ns.o: /usr/include/netns/sp.h /usr/include/netns/spidp.h
ns.o: /usr/include/netns/spp_var.h /usr/include/netns/spp_debug.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
E 16
E 13
E 12
E 10
E 2
E 1
