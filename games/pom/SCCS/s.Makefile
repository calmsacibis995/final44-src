h18669
s 00000/00000/00008
d D 8.1 93/05/31 17:42:24 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00008/00000/00000
d D 5.1 90/05/11 12:45:22 bostic 1 0
c first pass for new make
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	pom
MAN6=	pom.0
DPADD=	${LIBM}
LDADD=	-lm

.include <bsd.prog.mk>
E 1
