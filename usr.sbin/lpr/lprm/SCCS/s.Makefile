h60154
s 00000/00000/00012
d D 8.1 93/06/06 14:01:40 bostic 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00011
d D 5.5 92/09/01 11:11:18 elan 5 4
c printcap.c goes away.
e
s 00000/00001/00012
d D 5.4 90/06/19 18:33:14 bostic 4 3
c don't need Makefile.inc
e
s 00001/00000/00012
d D 5.3 90/06/19 18:32:39 bostic 3 2
c install in /usr/bin
e
s 00003/00000/00009
d D 5.2 90/05/13 17:43:42 bostic 2 1
c forgot permissions
e
s 00009/00000/00000
d D 5.1 90/05/11 17:11:44 bostic 1 0
c first pass for new make
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	lprm
CFLAGS+=-I${.CURDIR}/../common_source
D 5
SRCS=	lprm.c rmjob.c startdaemon.c common.c printcap.c
E 5
I 5
SRCS=	lprm.c rmjob.c startdaemon.c common.c
E 5
I 2
BINOWN=	root
BINGRP=	daemon
BINMODE=6555
I 3
BINDIR=	/usr/bin
E 3
E 2
.PATH:	${.CURDIR}/../common_source

D 4
.include "../../Makefile.inc"
E 4
.include <bsd.prog.mk>
E 1
