h37704
s 00000/00000/00009
d D 8.1 93/06/08 19:11:47 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00008
d D 1.3 93/06/08 19:11:43 bostic 3 2
c fix man page install
e
s 00001/00001/00008
d D 1.2 93/05/19 16:29:35 elan 2 1
c CFLAGS= -> += 
e
s 00009/00000/00000
d D 1.1 93/05/19 16:16:30 elan 1 0
c date and time created 93/05/19 16:16:30 by elan
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	xroach
D 3
MAN6=	xroach
E 3
I 3
MAN6=	xroach.0
E 3
D 2
CFLAGS=	-I${.CURDIR}/bitmaps
E 2
I 2
CFLAGS+= -I${.CURDIR}/bitmaps
E 2
DPADD=	${LIBX} ${LIBM}
LDADD=	-lX11/X11 -lm

.include <bsd.prog.mk>
E 1
