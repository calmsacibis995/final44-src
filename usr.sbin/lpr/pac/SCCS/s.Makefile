h34427
s 00000/00000/00010
d D 8.1 93/06/06 14:02:09 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00009
d D 5.2 92/09/01 11:11:58 elan 2 1
c printcap.c goes away.
e
s 00010/00000/00000
d D 5.1 90/05/11 17:09:49 bostic 1 0
c first pass for new make
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	pac
CFLAGS+=-I${.CURDIR}/../common_source
MAN8=	pac.0
D 2
SRCS=	pac.c printcap.c
E 2
I 2
SRCS=	pac.c common.c
E 2
.PATH:	${.CURDIR}/../common_source

.include "../../Makefile.inc"
.include <bsd.prog.mk>
E 1
