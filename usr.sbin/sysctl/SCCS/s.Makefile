h48435
s 00000/00000/00006
d D 8.1 93/06/06 14:07:27 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00002/00006
d D 5.4 93/06/02 19:10:33 mckusick 4 3
c devname moves to libc
e
s 00002/00000/00006
d D 5.3 93/05/26 00:10:30 mckusick 3 2
c add code for console device (if present)
e
s 00000/00001/00006
d D 5.2 93/04/27 16:15:12 bostic 2 1
c getloadavg(3) -> libc; sysctl no longer needs libutil or libkvm
e
s 00007/00000/00000
d D 5.1 93/03/31 14:39:09 mckusick 1 0
c date and time created 93/03/31 14:39:09 by mckusick
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	sysctl
MAN8=	sysctl.0
I 3
D 4
SRCS=	sysctl.c devname.c
.PATH: ${.CURDIR}/../../bin/ps
E 4
E 3
D 2
LDADD=	-lutil -lkvm
E 2

.include <bsd.prog.mk>
E 1
