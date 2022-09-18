h52090
s 00000/00000/00012
d D 8.1 93/06/06 14:01:38 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00011
d D 5.4 92/09/01 11:10:55 elan 4 3
c printcap.c goes away.
e
s 00001/00001/00011
d D 5.3 90/06/19 18:33:44 bostic 3 2
c install in /usr/bin
e
s 00003/00000/00009
d D 5.2 90/05/13 17:43:30 bostic 2 1
c forgot permissions
e
s 00009/00000/00000
d D 5.1 90/05/11 17:11:54 bostic 1 0
c first pass for new make
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	lpr
CFLAGS+=-I${.CURDIR}/../common_source
D 4
SRCS=	lpr.c startdaemon.c printcap.c
E 4
I 4
SRCS=	lpr.c startdaemon.c common.c
E 4
I 2
BINOWN=	root
BINGRP=	daemon
BINMODE=6555
I 3
BINDIR=	/usr/bin
E 3
E 2
.PATH:	${.CURDIR}/../common_source

D 3
.include "../../Makefile.inc"
E 3
.include <bsd.prog.mk>
E 1
