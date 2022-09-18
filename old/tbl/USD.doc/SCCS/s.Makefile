h46468
s 00002/00002/00008
d D 8.2 94/05/16 22:03:50 mckusick 4 3
c update for 4.4BSD manual printing
e
s 00000/00000/00010
d D 8.1 93/06/08 13:21:01 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00008
d D 5.2 93/06/05 17:27:27 bostic 2 1
c new doc.mk; document numbering changes for 4.4BSD
e
s 00010/00000/00000
d D 5.1 90/06/30 15:10:36 bostic 1 0
c new doc makefiles
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 2
DIR=	usd/28.tbl
E 2
I 2
DIR=	usd/25.tbl
E 2
SRCS=	tbl
D 4
MACROS=	-msU
E 4
I 4
MACROS=	-ms
E 4

D 2
paper.${PRINTER}: ${SRCS}
E 2
I 2
paper.ps: ${SRCS}
E 2
D 4
	${TBL} ${SRCS} | ${ROFF} > ${.TARGET}
E 4
I 4
	${TBL} ${SRCS} | ${EQN} | ${ROFF} > ${.TARGET}
E 4

.include <bsd.doc.mk>
E 1
