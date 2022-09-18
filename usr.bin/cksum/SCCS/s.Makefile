h51837
s 00002/00000/00006
d D 8.2 95/04/28 16:38:58 bostic 5 4
c create an alias for cksum named sum
e
s 00000/00000/00006
d D 8.1 93/06/06 14:27:38 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00005
d D 5.3 91/04/04 12:25:18 bostic 3 2
c add System V and BSD historic algorithms
e
s 00001/00000/00005
d D 5.2 91/04/01 15:11:25 bostic 2 1
c break crc routine out into separate module; for use by mtree(8)
e
s 00005/00000/00000
d D 5.1 91/03/08 17:58:12 bostic 1 0
c date and time created 91/03/08 17:58:12 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	cksum
I 2
D 3
SRCS=	cksum.c crc.c
E 3
I 3
SRCS=	cksum.c crc.c print.c sum1.c sum2.c
I 5
LINKS=	${BINDIR}/cksum ${BINDIR}/sum
MLINKS=	cksum.1 sum.1
E 5
E 3
E 2

.include <bsd.prog.mk>
E 1
