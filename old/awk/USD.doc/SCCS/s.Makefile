h59487
s 00000/00000/00011
d D 8.1 93/08/14 10:57:33 mckusick 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00001/00009
d D 5.4 93/08/10 11:50:32 elan 5 4
c Need refer.
e
s 00003/00000/00007
d D 5.3 93/08/03 13:37:52 elan 4 2
c Need to use tbl.
e
s 00000/00000/00007
d R 8.1 93/06/08 12:54:54 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00004/00006
d D 5.2 93/06/05 17:22:54 bostic 2 1
c new doc.mk; document numbering changes for 4.4BSD
e
s 00010/00000/00000
d D 5.1 90/06/30 15:09:46 bostic 1 0
c new doc makefiles
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 2
DIR=	usd/19.awk
E 2
I 2
DIR=	usd/16.awk
E 2
SRCS=	awk
MACROS=	-msU
I 5
REFER= refer -e -p /usr/old/dict/papers/Ind
E 5
D 2

paper.${PRINTER}: ${SRCS}
	${ROFF} ${SRCS} > ${.TARGET}
E 2

I 4
paper.ps: ${SRCS}
D 5
	${TBL} ${SRCS} | ${ROFF} > ${.TARGET}
E 5
I 5
	${REFER} ${SRCS} | ${TBL} | ${ROFF} > ${.TARGET}
E 5

E 4
.include <bsd.doc.mk>
E 1
