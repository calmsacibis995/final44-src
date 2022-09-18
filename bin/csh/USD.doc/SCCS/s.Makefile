h42372
s 00000/00000/00007
d D 8.1 93/08/14 10:46:53 mckusick 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00000/00006
d D 5.3 93/08/10 11:29:50 elan 4 2
c need -ms.
e
s 00000/00000/00006
d R 8.1 93/06/08 12:03:28 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00003/00006
d D 5.2 93/06/05 17:16:20 bostic 2 1
c new doc.mk; document numbering changes for 4.4BSD
e
s 00009/00000/00000
d D 5.1 90/06/30 15:07:44 bostic 1 0
c new doc makefiles
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

DIR=	usd/04.csh
SRCS=	tabs csh.1 csh.2 csh.3 csh.4 csh.a csh.g
I 4
MACROS= -ms
E 4

D 2
paper.${PRINTER}: ${SRCS}
	${ROFF} > ${.TARGET}

E 2
.include <bsd.doc.mk>
E 1
