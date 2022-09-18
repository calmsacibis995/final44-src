h28953
s 00000/00000/00007
d D 8.1 93/06/08 12:41:26 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00003/00007
d D 5.2 93/06/05 17:16:41 bostic 2 1
c new doc.mk; document numbering changes for 4.4BSD
e
s 00010/00000/00000
d D 5.1 90/06/30 15:07:54 bostic 1 0
c new doc makefiles
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

DIR=	usd/06.bc
SRCS=	bc
MACROS=	-ms

D 2
paper.${PRINTER}: ${SRCS}
	${ROFF} > ${.TARGET}

E 2
.include <bsd.doc.mk>
E 1
