h17735
s 00010/00000/00000
d D 8.1 94/04/20 00:23:16 mckusick 1 0
c from Rick Macklem
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

DIR=	papers/nqnfs
SRCS=	nqnfs.me
MACROS=	-me

paper.ps: ${SRCS}
	${PIC} ${SRCS} | ${TBL} | ${ROFF} > ${.TARGET}

.include <bsd.doc.mk>
E 1
