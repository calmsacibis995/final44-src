h30952
s 00000/00000/00008
d D 8.1 93/06/07 20:37:33 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00001/00006
d D 5.2 93/06/07 20:36:37 bostic 2 1
c make depend, tags work
e
s 00007/00000/00000
d D 5.1 93/06/06 15:34:21 bostic 1 0
c date and time created 93/06/06 15:34:21 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	mklocale
D 2
SRCS=	yacc.y lex.l
E 2
I 2
SRCS=	yacc.c lex.c
E 2
CFLAGS+=-I.
I 2
CLEANFILES+=y.tab.h yacc.c lex.c
E 2

.include <bsd.prog.mk>
E 1
