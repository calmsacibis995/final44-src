h21921
s 00000/00000/00008
d D 8.1 93/06/06 14:59:17 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00008/00000/00000
d D 5.1 90/05/11 15:13:08 bostic 1 0
c first pass for new make
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	locate.code
CFLAGS+=-I${.CURDIR}/../locate
NOMAN=	noman
BINDIR=	/usr/libexec

.include <bsd.prog.mk>
E 1
