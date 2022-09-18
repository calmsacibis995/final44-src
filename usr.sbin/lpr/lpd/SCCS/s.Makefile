h07392
s 00000/00000/00011
d D 8.1 93/06/06 14:00:35 bostic 7 6
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00001/00011
d D 5.6 93/04/27 18:10:33 bostic 6 5
c daemon(3) now in the C library
e
s 00001/00001/00011
d D 5.5 92/09/01 11:10:00 elan 5 4
c printcap.c goes away.
e
s 00001/00003/00012
d D 5.4 90/10/26 11:10:37 bostic 4 3
c only root should execute this, no need for setuid or special ownership
e
s 00001/00000/00014
d D 5.3 90/06/29 20:55:55 karels 3 2
c use daemon() call
e
s 00003/00000/00011
d D 5.2 90/05/13 17:43:18 bostic 2 1
c forgot permissions
e
s 00011/00000/00000
d D 5.1 90/05/11 17:11:57 bostic 1 0
c first pass for new make
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	lpd
CFLAGS+=-I${.CURDIR}/../common_source
I 3
D 6
LDADD=	-lutil
E 6
E 3
MAN8=	lpd.0
SRCS=	lpd.c printjob.c recvjob.c displayq.c rmjob.c startdaemon.c \
D 5
	lpdchar.c common.c printcap.c
E 5
I 5
	lpdchar.c common.c
E 5
I 2
D 4
BINOWN=	root
BINGRP=	daemon
BINMODE=6555
E 4
E 2
.PATH:	${.CURDIR}/../common_source

.include "../../Makefile.inc"
.include <bsd.prog.mk>
E 1
