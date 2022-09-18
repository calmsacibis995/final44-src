h44360
s 00000/00000/00007
d D 8.1 93/08/14 10:53:13 mckusick 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00000/00006
d D 5.3 93/08/10 11:31:16 elan 4 2
c Need -ms
e
s 00000/00000/00006
d R 8.1 93/06/08 12:47:20 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00004/00005
d D 5.2 93/06/05 17:19:10 bostic 2 1
c new doc.mk; document numbering changes for 4.4BSD
e
s 00009/00000/00000
d D 5.1 90/06/30 15:09:15 bostic 1 0
c new doc makefiles
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 2
DIR=	usd/13.edadv
E 2
I 2
DIR=	usd/10.edadv
E 2
SRCS=	ae.mac ae0 ae1 ae2 ae3 ae4 ae5 ae6 ae7 ae9
I 4
MACROS= -ms
E 4
D 2

paper.${PRINTER}: ${SRCS}
	${ROFF} > ${.TARGET}
E 2

.include <bsd.doc.mk>
E 1
