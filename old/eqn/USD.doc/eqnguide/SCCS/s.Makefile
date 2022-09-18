h36544
s 00000/00000/00010
d D 8.1 93/06/08 13:20:16 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00008
d D 5.2 93/06/05 17:27:02 bostic 2 1
c new doc.mk; document numbering changes for 4.4BSD
e
s 00010/00000/00000
d D 5.1 90/06/30 15:10:32 bostic 1 0
c new doc makefiles
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 2
DIR=	usd/27.eqnguide
E 2
I 2
DIR=	usd/24.eqnguide
E 2
SRCS=	g.mac g0 g1 g2 g3 g4 g5
MACROS=	-msU

D 2
paper.${PRINTER}: ${SRCS}
E 2
I 2
paper.ps: ${SRCS}
E 2
	${EQN} ${SRCS} | ${ROFF} > ${.TARGET}

.include <bsd.doc.mk>
E 1
