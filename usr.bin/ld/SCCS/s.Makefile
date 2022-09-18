h32684
s 00000/00000/00007
d D 8.1 93/06/06 14:54:13 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00003/00004/00004
d D 6.2 91/04/30 12:42:35 bostic 2 1
c rename ld++ as the default loader, ld
e
s 00008/00000/00000
d D 6.1 91/02/07 23:33:43 donn 1 0
c date and time created 91/02/07 23:33:43 by donn
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 2
PROG=		ld++
BINDIR=		/usr/libexec
SRCS=		ld++.c cplus-dem.c
NOMAN=		noman
E 2
I 2
PROG=	ld
SRCS=	ld.c cplus-dem.c
NOMAN=	noman
E 2

.include <bsd.prog.mk>
E 1
