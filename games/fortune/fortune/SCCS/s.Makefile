h37462
s 00000/00000/00010
d D 8.1 93/05/31 17:01:34 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00009
d D 5.2 92/06/20 15:48:49 bostic 2 1
c don't compile with DEBUG by default
e
s 00010/00000/00000
d D 5.1 92/02/19 08:30:22 bostic 1 0
c date and time created 92/02/19 08:30:22 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	fortune
MAN6=	fortune.0
D 2
CFLAGS+=-DDEBUG -I${.CURDIR}/../strfile
E 2
I 2
CFLAGS+=-I${.CURDIR}/../strfile
E 2
DPADD=	${COMPAT}
LDADD=	-lcompat

.include "${.CURDIR}/../../Makefile.inc"
.include <bsd.prog.mk>
E 1
