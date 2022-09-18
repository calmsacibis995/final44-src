h34471
s 00001/00001/00012
d D 5.2 90/06/24 16:07:36 bostic 2 1
c it was really named whatabout
e
s 00013/00000/00000
d D 5.1 90/05/11 14:25:32 bostic 1 0
c first pass for new make
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 2
PROG=	what
E 2
I 2
PROG=	whatabout
E 2
CFLAGS+=-I${.CURDIR}/../refer
SRCS=	what1.c what2.c what3.c what4.c mkey3.c shell.c
DPADD=	${LIBCOMPAT}
LDADD=	-lcompat
NOMAN=	noman

.PATH:	${.CURDIR}/../hunt ${.CURDIR}/../mkey

.include "../../Makefile.inc"
.include <bsd.prog.mk>
E 1
