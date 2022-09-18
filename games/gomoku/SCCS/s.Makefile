h22696
s 00010/00000/00000
d D 8.1 94/07/24 22:58:09 mckusick 1 0
c from Ralph Campbell
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	gomoku
SRCS=	bdinit.c bdisp.c main.c makemove.c pickmove.c stoc.c
MAN6=	gomoku.0
DPADD=	${LIBCURSES} ${LIBTERM}
LDADD=	-lcurses -ltermlib
HIDEGAME=hidegame

.include <bsd.prog.mk>
E 1
