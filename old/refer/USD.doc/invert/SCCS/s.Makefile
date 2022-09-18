h46847
s 00002/00001/00009
d D 8.2 94/05/19 16:30:19 mckusick 4 3
c specify refer database
e
s 00000/00000/00010
d D 8.1 93/06/08 13:23:02 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00008
d D 5.2 93/06/05 17:27:59 bostic 2 1
c new doc.mk; document numbering changes for 4.4BSD
e
s 00010/00000/00000
d D 5.1 90/06/30 15:10:44 bostic 1 0
c new doc makefiles
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 2
DIR=	usd/30.invert
E 2
I 2
DIR=	usd/27.invert
E 2
SRCS=	refer
D 4
MACROS=	-msU
E 4
I 4
MACROS=	-ms
REFER=	refer -e -p /usr/old/dict/papers/Ind
E 4

D 2
paper.${PRINTER}: ${SRCS}
E 2
I 2
paper.ps: ${SRCS}
E 2
	${REFER} ${SRCS} | ${TBL} | ${ROFF} > ${.TARGET}

.include <bsd.doc.mk>
E 1
