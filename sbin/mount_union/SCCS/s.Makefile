h51001
s 00000/00003/00011
d D 8.4 94/07/13 10:16:47 mckusick 4 3
c no longer needs set-uid root
e
s 00006/00001/00008
d D 8.3 94/03/27 11:57:30 bostic 3 2
c Jan-Simon Pendry's and my new mount code
e
s 00002/00000/00007
d D 8.2 94/02/17 07:37:17 pendry 2 1
c install mount_union setuid root.  permission checks are done in the kernel.
e
s 00007/00000/00000
d D 8.1 94/02/11 19:20:26 pendry 1 0
c date and time created 94/02/11 19:20:26 by pendry
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 3
CFLAGS+=-I/sys
E 3
PROG=	mount_union
I 3
SRCS=	mount_union.c getmntopts.c
E 3
MAN8=	mount_union.0
I 3

MOUNT=	${.CURDIR}/../mount
CFLAGS+= -I/sys -I${MOUNT}
.PATH:	${MOUNT}

E 3
I 2
D 4
BINOWN= root
BINMODE=4555
E 2

E 4
.include <bsd.prog.mk>
E 1
