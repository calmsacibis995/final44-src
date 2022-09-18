h37658
s 00000/00000/00014
d D 8.1 93/06/01 23:07:34 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00014/00000/00000
d D 5.1 90/06/25 11:36:57 bostic 1 0
c date and time created 90/06/25 11:36:57 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	compile_et
CFLAGS+=-I. -I${.CURDIR}
SRCS=	compile_et.c error_message.c et_name.c init_et.c perror.c
OBJS+=	error_table.o
DPADD=	${LIBL}
LDADD=	-ll
CLEANFILES=et_lex.lex.c y.tab.c y.tab.h error_table.c
NOMAN=	noman

error_table.c: et_lex.lex.c

.include <bsd.prog.mk>
E 1
