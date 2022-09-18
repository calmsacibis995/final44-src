h35498
s 00005/00000/00006
d D 8.2 94/03/27 08:59:37 bostic 3 2
c Jan-Simon Pendry's and my new mount code
e
s 00000/00000/00006
d D 8.1 93/06/05 11:02:09 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00006/00000/00000
d D 5.1 92/07/05 14:15:29 bostic 1 0
c date and time created 92/07/05 14:15:29 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	mount_fdesc
I 3
SRCS=	mount_fdesc.c getmntopts.c
E 3
MAN8=	mount_fdesc.0
I 3

MOUNT=	${.CURDIR}/../mount
CFLAGS+= -I${MOUNT}
.PATH:	${MOUNT}
E 3

.include <bsd.prog.mk>
E 1
