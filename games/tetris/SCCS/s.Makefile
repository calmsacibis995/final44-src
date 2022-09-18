h33529
s 00000/00000/00010
d D 8.1 93/05/31 17:54:22 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00002/00010
d D 5.2 93/05/29 10:31:33 bostic 2 1
c make it work
e
s 00012/00000/00000
d D 5.1 93/05/17 09:13:04 bostic 1 0
c date and time created 93/05/17 09:13:04 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	tetris
SRCS=	input.c screen.c shapes.c scores.c tetris.c
MAN6=	tetris.0
DPADD=	${LIBTERM}
LDADD=	-ltermcap
HIDEGAME=hidegame

D 2
all: ${PROG}

E 2
.include <bsd.prog.mk>
E 1
