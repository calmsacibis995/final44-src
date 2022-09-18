h37206
s 00001/00001/00009
d D 5.3 91/11/14 10:15:17 bostic 3 2
c move to /usr/old
e
s 00001/00001/00009
d D 5.2 90/06/19 16:29:53 bostic 2 1
c install in /usr/libexec
e
s 00010/00000/00000
d D 5.1 90/05/11 14:26:00 bostic 1 0
c first pass for new make
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	inv
SRCS=	deliv2.c inv1.c inv2.c inv3.c inv5.c inv6.c
CFLAGS+=-I${.CURDIR}/../refer
I 2
D 3
BINDIR=	/usr/libexec
E 3
I 3
BINDIR=	/usr/old/libexec
E 3
E 2
NOMAN=	noman
.PATH:	${.CURDIR}/../deliv

D 2
.include "../../Makefile.inc"
E 2
.include <bsd.prog.mk>
E 1
