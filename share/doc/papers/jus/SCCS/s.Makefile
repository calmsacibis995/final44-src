h28090
s 00000/00004/00007
d D 5.2 93/06/08 17:47:02 bostic 2 1
c new doc.mk; document numbering changes for 4.4BSD
e
s 00011/00000/00000
d D 5.1 92/11/12 15:30:10 mckusick 1 0
c date and time created 92/11/12 15:30:10 by mckusick
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

DIR=	papers/jus
SRCS=	paper.ms
MACROS=	-ms
D 2
PRINTER=lz

paper.${PRINTER}: ${SRCS}
	${ROFF} ${SRCS} > ${.TARGET}
E 2

.include <bsd.doc.mk>
E 1
