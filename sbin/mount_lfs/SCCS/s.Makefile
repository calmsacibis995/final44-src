h34935
s 00005/00000/00006
d D 8.2 94/03/27 09:06:31 bostic 3 2
c Jan-Simon Pendry's and my new mount code
e
s 00000/00000/00006
d D 8.1 93/06/08 19:13:57 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00006/00000/00000
d D 5.1 93/06/08 18:48:12 bostic 1 0
c date and time created 93/06/08 18:48:12 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	mount_lfs
I 3
SRCS=	mount_lfs.c getmntopts.c
E 3
MAN8=	mount_lfs.0
I 3

MOUNT=	${.CURDIR}/../mount
CFLAGS+= -I${MOUNT}
.PATH:	${MOUNT}
E 3

.include <bsd.prog.mk>
E 1
