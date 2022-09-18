h45427
s 00002/00001/00009
d D 8.3 94/03/27 08:58:29 bostic 3 2
c prettiness police
e
s 00005/00001/00005
d D 8.2 94/03/27 08:31:46 bostic 2 1
c Jan-Simon Pendry and my new mount code
c mount_cd9660 pretty much completely rewritten for cleanliness, KNF, and ANSI
e
s 00006/00000/00000
d D 8.1 94/01/21 18:27:40 mckusick 1 0
c date and time created 94/01/21 18:27:40 by mckusick
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 2
PROG = mount_cd9660
E 2
I 2
PROG=	mount_cd9660
SRCS=	mount_cd9660.c getmntopts.c
E 2
D 3
MAN8=	${PROG}.0
E 3
I 3
MAN8=	mount_cd9660.0

E 3
I 2
MOUNT=	${.CURDIR}/../mount
CFLAGS+= -I${MOUNT}
.PATH:	${MOUNT}
E 2

.include <bsd.prog.mk>
E 1
