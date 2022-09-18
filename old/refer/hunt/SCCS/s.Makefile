h48002
s 00001/00001/00013
d D 5.3 91/11/14 10:15:05 bostic 3 2
c move to /usr/old
e
s 00001/00000/00013
d D 5.2 90/06/19 17:13:35 bostic 2 1
c install in libexec, not /usr/bin
e
s 00013/00000/00000
d D 5.1 90/05/11 14:25:38 bostic 1 0
c first pass for new make
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	hunt
SRCS=	deliv2.c glue4.c glue5.c hunt1.c hunt2.c hunt3.c hunt5.c hunt6.c \
	hunt7.c hunt8.c hunt9.c refer3.c shell.c tick.c
CFLAGS+=-I${.CURDIR}/../refer
DPADD=	${LIBCOMPAT}
LDADD=	-lcompat
I 2
D 3
BINDIR=	/usr/libexec
E 3
I 3
BINDIR=	/usr/old/libexec
E 3
E 2
NOMAN=	noman
.PATH:	${.CURDIR}/../deliv ${.CURDIR}/../refer

.include "../../Makefile.inc"
.include <bsd.prog.mk>
E 1
