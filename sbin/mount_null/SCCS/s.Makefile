h43427
s 00005/00001/00006
d D 8.3 94/03/27 09:13:05 bostic 4 3
c Jan-Simon Pendry's and my new mount code
e
s 00001/00001/00006
d D 8.2 94/01/12 13:55:01 pendry 3 2
c fix CFLAGS
e
s 00000/00000/00007
d D 8.1 93/06/05 11:03:15 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00007/00000/00000
d D 5.1 92/07/09 13:56:28 heideman 1 0
c date and time created 92/07/09 13:56:28 by heideman
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 3
CFLAGS=	-I/sys
E 3
I 3
D 4
CFLAGS+=-I/sys
E 4
E 3
PROG=	mount_null
I 4
SRCS=	mount_null.c getmntopts.c
E 4
MAN8=	mount_null.0
I 4

MOUNT=	${.CURDIR}/../mount
CFLAGS+= -I/sys -I${MOUNT}
.PATH:	${MOUNT}
E 4

.include <bsd.prog.mk>
E 1
