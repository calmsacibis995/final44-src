h33860
s 00000/00000/00012
d D 8.1 93/06/06 14:34:44 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00000/00011
d D 5.2 90/06/26 11:46:21 bostic 2 1
c undef yywrap for flex, clean style2.c
e
s 00011/00000/00000
d D 5.1 90/05/11 15:14:53 bostic 1 0
c first pass for new make
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	style2
CFLAGS+=-I${.CURDIR} -I${.CURDIR}/../style1
SRCS=	style2.c
I 2
CLEANFILES=style2.c
E 2
DPADD=	${LIBL}
LDADD=	-ll
NOMAN=	noman
BINDIR=	/usr/libexec

.include <bsd.prog.mk>
E 1
