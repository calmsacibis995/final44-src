h50336
s 00000/00000/00011
d D 8.1 93/08/14 10:45:42 mckusick 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00005/00000/00006
d D 5.3 93/08/09 15:21:37 elan 4 2
c need refer and ms macros
e
s 00000/00000/00006
d R 8.1 93/06/08 12:01:39 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00003/00006
d D 5.2 93/06/05 17:16:11 bostic 2 1
c new doc.mk; document numbering changes for 4.4BSD
e
s 00009/00000/00000
d D 5.1 90/06/30 15:07:31 bostic 1 0
c new doc makefiles
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

DIR=	usd/03.shell
SRCS=	t.mac t1 t2 t3 t4
I 4
MACROS= -ms
REFER=  refer -e -p /usr/old/dict/papers/Ind

paper.ps: ${SRCS}
	${REFER} ${SRCS} | ${ROFF} > ${.TARGET}
E 4

D 2
paper.${PRINTER}: ${SRCS}
	${ROFF} > ${.TARGET}

E 2
.include <bsd.doc.mk>
E 1
