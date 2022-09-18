h48334
s 00000/00000/00012
d D 8.1 93/06/06 14:00:14 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00011
d D 5.3 92/09/01 11:09:19 elan 3 2
c printcap.c goes away.
e
s 00002/00000/00010
d D 5.2 90/05/13 17:42:39 bostic 2 1
c forgot permissions
e
s 00010/00000/00000
d D 5.1 90/05/11 17:11:42 bostic 1 0
c first pass for new make
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	lpc
CFLAGS+=-I${.CURDIR}/../common_source
MAN8=	lpc.0
D 3
SRCS=	lpc.c cmds.c cmdtab.c startdaemon.c common.c printcap.c
E 3
I 3
SRCS=	lpc.c cmds.c cmdtab.c startdaemon.c common.c
E 3
I 2
BINGRP=	daemon
BINMODE=2555
E 2
.PATH:	${.CURDIR}/../common_source

.include "../../Makefile.inc"
.include <bsd.prog.mk>
E 1
