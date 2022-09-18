h27498
s 00000/00000/00009
d D 8.1 93/06/01 23:13:23 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00009/00000/00000
d D 5.1 90/06/25 18:22:50 bostic 1 0
c date and time created 90/06/25 18:22:50 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	make_keypair
MAN8=	make_keypair.0
CFLAGS+=-DKERBEROS -I${.CURDIR}/../register
DPADD=	${LIBKRB} ${LIBDES}
LDADD=	-lkdb -lkrb -ldes

.include <bsd.prog.mk>
E 1
