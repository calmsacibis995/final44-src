h64932
s 00001/00001/00009
d D 8.3 94/05/19 16:32:38 mckusick 7 6
c needs to use eqn
e
s 00001/00001/00009
d D 8.2 94/05/16 22:42:10 mckusick 6 5
c update for 4.4BSD manuals
e
s 00000/00000/00010
d D 8.1 93/08/14 11:09:36 mckusick 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00003/00000/00007
d D 5.3 93/08/04 14:02:39 elan 4 2
c Need tbl.
e
s 00000/00000/00007
d R 8.1 93/06/08 13:24:48 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00004/00006
d D 5.2 93/06/05 17:29:35 bostic 2 1
c new doc.mk; document numbering changes for 4.4BSD
e
s 00010/00000/00000
d D 5.1 90/06/30 15:10:59 bostic 1 0
c new doc makefiles
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 2
DIR=	usd/32.diction
E 2
I 2
DIR=	usd/29.diction
E 2
SRCS=	rm0 rm1 rm2 ap1 ap2
D 6
MACROS=	-msU
E 6
I 6
MACROS=	-ms
E 6
D 2

paper.${PRINTER}: ${SRCS}
	${ROFF} ${SRCS} > ${.TARGET}
E 2

I 4
paper.ps: ${SRCS}
D 7
	${TBL} ${SRCS} | ${ROFF} > ${.TARGET}
E 7
I 7
	${TBL} ${SRCS} | ${EQN} | ${ROFF} > ${.TARGET}
E 7

E 4
.include <bsd.doc.mk>
E 1
