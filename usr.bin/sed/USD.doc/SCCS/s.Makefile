h31701
s 00000/00000/00007
d D 8.1 93/06/08 12:54:13 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00004/00006
d D 5.2 93/06/05 17:22:21 bostic 2 1
c new doc.mk; document numbering changes for 4.4BSD
e
s 00010/00000/00000
d D 5.1 90/06/30 15:09:41 bostic 1 0
c new doc makefiles
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 2
DIR=	usd/18.sed
E 2
I 2
DIR=	usd/15.sed
E 2
SRCS=	sed
MACROS=	-msU
D 2

paper.${PRINTER}: ${SRCS}
	${ROFF} ${SRCS} > ${.TARGET}
E 2

.include <bsd.doc.mk>
E 1
