h47047
s 00005/00000/00006
d D 8.4 94/03/27 11:47:35 bostic 4 3
c Jan-Simon Pendry's and my new mount code
e
s 00001/00002/00005
d D 8.3 94/02/17 10:17:03 pendry 3 2
c added procfs man page
e
s 00002/00001/00005
d D 8.2 94/01/27 08:34:02 bostic 2 1
c no man page at the moeemnt
e
s 00006/00000/00000
d D 8.1 94/01/25 14:08:21 bostic 1 0
c date and time created 94/01/25 14:08:21 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	mount_procfs
I 4
SRCS=	mount_procfs.c getmntopts.c
E 4
D 2
MAN8=	mount_procfs.0
E 2
I 2
D 3
#MAN8=	mount_procfs.0
NOMAN=	noman
E 3
I 3
MAN8=	mount_procfs.0
I 4

MOUNT=	${.CURDIR}/../mount
CFLAGS+= -I${MOUNT}
.PATH:	${MOUNT}
E 4
E 3
E 2

.include <bsd.prog.mk>
E 1
