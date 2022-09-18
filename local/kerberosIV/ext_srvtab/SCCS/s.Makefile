h27218
s 00000/00000/00009
d D 8.1 93/06/01 23:08:53 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00009/00000/00000
d D 5.1 90/06/25 11:37:06 bostic 1 0
c date and time created 90/06/25 11:37:06 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	ext_srvtab
CFLAGS+=-DKERBEROS -I${.CURDIR}/../include
DPADD=	${LIBKDB} ${LIBKRB} ${LIBDES}
LDADD=	-lkdb -lkrb -ldes
NOMAN=	noman

.include <bsd.prog.mk>
E 1
