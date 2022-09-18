h32142
s 00000/00000/00012
d D 8.1 93/06/11 15:26:46 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00000/00011
d D 5.2 91/05/03 18:18:44 bostic 2 1
c forgot the -D flag
e
s 00011/00000/00000
d D 5.1 91/05/03 18:17:31 bostic 1 0
c date and time created 91/05/03 18:17:31 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	arp
SRCS=	arp.c
I 2
CFLAGS+=-DLETS_GET_SMALL
E 2
BINGRP=	kmem
BINMODE=2555
NOMAN=	noman
LDFLAGS=-N
.PATH:	${.CURDIR}/../../../../usr.sbin/arp

.include <bsd.prog.mk>
E 1
