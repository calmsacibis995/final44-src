h36030
s 00011/00000/00000
d D 5.1 90/05/11 14:25:43 bostic 1 0
c first pass for new make
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	refer
SRCS=	deliv2.c glue1.c glue2.c glue3.c glue4.c glue5.c hunt2.c hunt3.c \
	hunt5.c hunt6.c hunt7.c hunt8.c hunt9.c mkey3.c refer0.c refer1.c \
	refer2.c refer4.c refer5.c refer6.c refer7.c refer8.c shell.c
CFLAGS+=-I${.CURDIR}
.PATH:	${.CURDIR}/../deliv ${.CURDIR}/../hunt ${.CURDIR}/../mkey

.include "../../Makefile.inc"
.include <bsd.prog.mk>
E 1
