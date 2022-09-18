h34022
s 00000/00000/00009
d D 8.1 93/06/07 10:23:51 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00001/00009
d D 6.2 93/05/20 16:05:27 bostic 3 2
c convert from dbm to ndbm
e
s 00000/00000/00010
d D 6.1 92/12/21 16:13:41 eric 2 1
c Release 6
e
s 00010/00000/00000
d D 5.1 90/05/11 16:08:18 bostic 1 0
c first pass for new make
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	praliases
CFLAGS+=-I${.CURDIR}/../src
DPADD=	${LIBDBM}
D 3
LDADD=	-ldbm
E 3
NOMAN=	noman

.include "../../Makefile.inc"
.include <bsd.prog.mk>
E 1
