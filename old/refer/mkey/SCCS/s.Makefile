h36496
s 00001/00001/00009
d D 5.3 91/11/14 10:15:35 bostic 3 2
c move to /usr/old
e
s 00001/00001/00009
d D 5.2 90/06/19 16:30:11 bostic 2 1
c install in /usr/libexec
e
s 00010/00000/00000
d D 5.1 90/05/11 14:25:48 bostic 1 0
c first pass for new make
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	mkey
SRCS=	deliv2.c mkey1.c mkey2.c mkey3.c
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
