h37329
s 00000/00000/00007
d D 8.1 93/06/08 14:06:48 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00004/00005
d D 5.2 93/06/05 16:44:50 mckusick 2 1
c new doc.mk; document numbering changes for 4.4BSD
e
s 00009/00000/00000
d D 5.1 93/05/20 16:19:31 bostic 1 0
c date and time created 93/05/20 16:19:31 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 2
DIR=	papers/nfs
SRCS=	nfs-notes.me
E 2
I 2
DIR=	smm/06.nfs
SRCS=	0.t 1.t 2.t ref.t
E 2
MACROS=	-me

D 2
paper.${PRINTER}: ${SRCS}
	${TBL} ${SRCS} | ${ROFF} > ${.TARGET}
E 2
.include <bsd.doc.mk>
E 1
