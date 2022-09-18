h32319
s 00000/00000/00012
d D 8.1 93/06/06 14:33:51 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00001/00010
d D 5.2 90/07/01 10:29:21 bostic 2 1
c clean style1.c
e
s 00011/00000/00000
d D 5.1 90/05/11 15:14:49 bostic 1 0
c first pass for new make
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	style1
CFLAGS+=-I${.CURDIR}
SRCS=	style1.c
I 2
BINDIR=	/usr/libexec
E 2
DPADD=	${LIBL}
LDADD=	-ll
NOMAN=	noman
D 2
BINDIR=	/usr/libexec
E 2
I 2
CLEANFILES=style1.c
E 2

.include <bsd.prog.mk>
E 1
