h31684
s 00000/00000/00007
d D 8.1 93/06/08 11:52:50 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00003/00007
d D 5.2 93/06/05 17:14:04 bostic 2 1
c new doc.mk; document numbering changes for 4.4BSD
e
s 00010/00000/00000
d D 5.1 90/06/30 15:06:54 bostic 1 0
c new doc makefiles
e
u
U
t
T
I 1
#       %W% (Berkeley) %G%

DIR=	usd/01.begin
SRCS=	u.mac u0 u1 u2 u3 u4 u5
MACROS= -msU

D 2
paper.${PRINTER}: ${SRCS}
	${ROFF} ${SRCS} > ${.TARGET}

E 2
.include <bsd.doc.mk>
E 1
