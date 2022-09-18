h51426
s 00001/00001/00011
d D 8.2 94/04/22 06:46:27 bostic 4 3
c libln is gone, only libl remains
e
s 00000/00000/00012
d D 8.1 93/06/06 16:27:20 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00011
d D 5.2 91/02/28 17:37:07 bostic 2 1
c Not worth getting right, don't want to see the errors either
e
s 00012/00000/00000
d D 5.1 90/06/05 10:38:42 bostic 1 0
c date and time created 90/06/05 10:38:42 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	beautify
SRCS=	beauty.c tree.c lextab.c bdef.c
D 2
CFLAGS+=-I. -I${.CURDIR}
E 2
I 2
CFLAGS+=-w -I. -I${.CURDIR}
E 2
BINDIR=	/usr/libexec
DPADD=	${LIBLN}
D 4
LDADD=	-lln
E 4
I 4
LDADD=	-ll
E 4
NOMAN=	noman
CLEANFILES=beauty.c lextab.c y.tab.h lex.yy.c y.tab.c

.include <bsd.prog.mk>
E 1
