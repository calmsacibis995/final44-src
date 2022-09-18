h36578
s 00006/00001/00008
d D 8.2 94/03/27 13:05:57 bostic 3 2
c Jan-Simon Pendry's and my new mount code
e
s 00000/00000/00009
d D 8.1 93/06/05 11:03:00 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00009/00000/00000
d D 5.1 92/01/06 16:31:43 mckusick 1 0
c from Rick Macklem
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	mount_nfs
D 3
CFLAGS+=-DNFS
E 3
I 3
SRCS=	mount_nfs.c getmntopts.c
E 3
MAN8=	mount_nfs.0
I 3

MOUNT=	${.CURDIR}/../mount
CFLAGS+= -DNFS -I${MOUNT}
.PATH:	${MOUNT}

E 3
DPADD=	${LIBRPC}
LDADD=	-lrpc

.include <bsd.prog.mk>
E 1
