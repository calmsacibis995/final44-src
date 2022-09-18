h35862
s 00000/00000/00010
d D 8.1 93/06/08 13:19:01 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00008
d D 5.2 93/06/05 17:26:25 bostic 2 1
c new doc.mk; document numbering changes for 4.4BSD
e
s 00010/00000/00000
d D 5.1 90/06/30 15:10:28 bostic 1 0
c new doc makefiles
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 2
DIR=	usd/26.eqn
E 2
I 2
DIR=	usd/23.eqn
E 2
SRCS=	e.mac e0 e1 e2 e3 e4 e5 e6 e7
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
