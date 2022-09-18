h25301
s 00000/00003/00007
d D 5.2 93/06/08 17:45:36 bostic 2 1
c new doc.mk; document numbering changes for 4.4BSD
e
s 00010/00000/00000
d D 5.1 90/06/30 15:00:12 bostic 1 0
c new doc makefiles
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

DIR=	papers/beyond43
SRCS=	beyond43.ms
MACROS=	-ms

D 2
paper.${PRINTER}: ${SRCS}
	${ROFF} ${SRCS} > ${.TARGET}

E 2
.include <bsd.doc.mk>
E 1
