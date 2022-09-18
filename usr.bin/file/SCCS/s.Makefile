h40331
s 00000/00000/00006
d D 8.1 93/06/06 14:38:35 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00000/00005
d D 5.4 93/03/22 06:21:48 bostic 4 3
c hpux_exec.h is referenced from /sys
e
s 00000/00001/00005
d D 5.3 93/03/08 19:12:49 ralph 3 2
c don't need to include /sys
e
s 00001/00000/00005
d D 5.2 91/11/11 11:40:06 bostic 2 1
c use /sys to get to kernel include files
e
s 00005/00000/00000
d D 5.1 90/06/25 16:53:13 bostic 1 0
c date and time created 90/06/25 16:53:13 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	file
I 4
CFLAGS+=-I/sys
E 4
I 2
D 3
CFLAGS+=-I/sys
E 3
E 2

.include <bsd.prog.mk>
E 1
