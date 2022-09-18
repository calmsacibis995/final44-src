h31838
s 00000/00000/00009
d D 8.1 93/05/31 17:53:07 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00008
d D 5.2 91/02/28 15:07:27 bostic 2 1
c fix up directory structure
e
s 00009/00000/00000
d D 5.1 90/05/11 12:47:56 bostic 1 0
c first pass for new make
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	snscore
D 2
CFLAGS+=-I${.CURDIR}/..
E 2
I 2
CFLAGS+=-I${.CURDIR}/../snake
E 2
NOMAN=	noman
HIDEGAME=hidegame

.include "../../Makefile.inc"
.include <bsd.prog.mk>
E 1
