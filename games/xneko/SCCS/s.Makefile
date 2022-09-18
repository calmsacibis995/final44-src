h21918
s 00000/00000/00008
d D 8.1 93/05/31 18:45:54 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00008/00000/00000
d D 5.1 91/05/22 13:03:01 bostic 1 0
c date and time created 91/05/22 13:03:01 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	xneko
MAN6=	xneko.0
DPADD=	${LIBX} ${LIBM}
LDADD=	-lX11/X11 -lm

.include <bsd.prog.mk>
E 1
