h58821
s 00000/00000/00012
d D 8.1 93/06/06 14:53:12 bostic 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00001/00012
d D 5.4 93/06/02 17:18:44 bostic 5 4
c move up a level
e
s 00001/00001/00012
d D 5.3 93/02/15 10:05:10 ralph 4 3
c don't need to include /sys
e
s 00001/00001/00012
d D 5.2 91/04/27 16:16:35 bostic 3 1
c needs -I/sys for pcb.h
e
s 00001/00001/00012
d R 5.2 91/01/15 14:14:17 bostic 2 1
c kernel reorg
e
s 00013/00000/00000
d D 5.1 90/05/11 14:58:42 bostic 1 0
c first pass for new make
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	kdump
D 3
CFLAGS+=-I${.CURDIR}/../ktrace
E 3
I 3
D 4
CFLAGS+=-I/sys -I${.CURDIR}/../ktrace
E 4
I 4
CFLAGS+=-I${.CURDIR}/../ktrace
E 4
E 3
SRCS=	kdump.c ioctl.c subr.c
.PATH:	${.CURDIR}/../ktrace
CLEANFILES+=ioctl.c

ioctl.c: mkioctls
	/bin/sh ${.CURDIR}/mkioctls > ioctl.c

D 5
.include "../../Makefile.inc"
E 5
.include <bsd.prog.mk>
E 1
