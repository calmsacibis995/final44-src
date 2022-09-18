h54341
s 00000/00000/00008
d D 8.1 93/06/07 10:22:18 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00004/00006
d D 6.2 93/05/28 14:27:38 eric 4 3
c adjust compile flags & library includes
e
s 00000/00000/00010
d D 6.1 92/12/21 16:10:00 eric 3 2
c Release 6
e
s 00001/00001/00009
d D 5.2 92/12/19 14:31:01 eric 2 1
c compile in everything possible.... by default
e
s 00010/00000/00000
d D 5.1 92/11/15 14:57:52 eric 1 0
c date and time created 92/11/15 14:57:52 by eric
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	makemap
D 2
CFLAGS+=-I${.CURDIR}/../src -DBTREE_MAP -DDBM_MAP
E 2
I 2
D 4
CFLAGS+=-I${.CURDIR}/../src -DDBM_MAP -DBTREE_MAP -DHASH_MAP
E 2
DPADD=	${LIBDBM}
LDADD=	-ldbm
NOMAN=	noman
E 4
I 4
MAN8=	makemap.0
CFLAGS+=-I${.CURDIR}/../src -DNDBM -DNEWDB
E 4

.include "../../Makefile.inc"
.include <bsd.prog.mk>
E 1
