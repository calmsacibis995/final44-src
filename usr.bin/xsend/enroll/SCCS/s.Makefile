h30827
s 00000/00000/00012
d D 8.1 93/06/06 22:30:17 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00012/00000/00000
d D 5.1 90/05/11 14:17:44 bostic 1 0
c first pass for new make
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	enroll
CFLAGS+=-I${.CURDIR}/../common_source
SRCS=	enroll.c lib.c
NOMAN=	man
DPADD=	${LIBMP} ${LIBCOMPAT}
LDADD=	-lmp -lcompat
.PATH:	${.CURDIR}/../common_source

.include "../../Makefile.inc"
.include <bsd.prog.mk>
E 1
