h51551
s 00005/00001/00006
d D 8.3 94/03/27 09:08:35 bostic 5 4
c Jan-Simon Pendry's and my new mount code
e
s 00001/00001/00006
d D 8.2 94/01/12 13:54:33 pendry 4 3
c fix CFLAGS
e
s 00000/00000/00007
d D 8.1 93/06/05 11:02:45 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00006
d D 5.2 92/07/05 15:46:45 bostic 2 1
c use /sys, not /usr/src/sys
e
s 00007/00000/00000
d D 5.1 92/07/05 15:36:09 bostic 1 0
c date and time created 92/07/05 15:36:09 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 2
CFLAGS=	-I/usr/src/sys	# XXX
E 2
I 2
D 4
CFLAGS=	-I/sys
E 4
I 4
D 5
CFLAGS+=-I/sys
E 5
E 4
E 2
PROG=	mount_lofs
I 5
SRCS=	mount_lofs.c getmntopts.c
E 5
MAN8=	mount_lofs.0
I 5

MOUNT=	${.CURDIR}/../mount
CFLAGS+=-I/sys -I${MOUNT}
.PATH:	${MOUNT}
E 5

.include <bsd.prog.mk>
E 1
