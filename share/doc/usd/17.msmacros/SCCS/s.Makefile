h50301
s 00000/00000/00010
d D 8.1 93/08/14 10:59:20 mckusick 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00003/00000/00007
d D 5.3 93/08/03 13:38:40 elan 4 2
c Need to use tbl and pic.
e
s 00000/00000/00007
d R 8.1 93/06/08 12:55:44 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00004/00006
d D 5.2 93/06/05 17:23:04 bostic 2 1
c new doc.mk; document numbering changes for 4.4BSD
e
s 00010/00000/00000
d D 5.1 90/06/30 15:09:53 bostic 1 0
c new doc makefiles
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 2
DIR=	usd/20.msmacros
E 2
I 2
DIR=	usd/17.msmacros
E 2
SRCS=	ms
MACROS=	-msU
D 2

paper.${PRINTER}: ${SRCS}
	${ROFF} ${SRCS} > ${.TARGET}
E 2

I 4
paper.ps: ${SRCS}
	${SOELIM} ${SRCS} | ${PIC} | ${TBL} | ${ROFF} > ${.TARGET}

E 4
.include <bsd.doc.mk>
E 1
