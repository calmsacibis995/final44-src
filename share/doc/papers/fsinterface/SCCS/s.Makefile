h36282
s 00000/00004/00007
d D 5.3 93/06/08 17:46:23 bostic 3 2
c new doc.mk; document numbering changes for 4.4BSD
e
s 00002/00001/00009
d D 5.2 90/12/16 17:05:04 mckusick 2 1
c print it out right
e
s 00010/00000/00000
d D 5.1 90/06/30 15:00:25 bostic 1 0
c new doc makefiles
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

DIR=	papers/fsinterface
D 2
SRCS=	abstract.ms fsinterface.ms
E 2
I 2
SRCS=	fsinterface.ms
E 2
MACROS=	-ms
I 2
D 3
PRINTER=lz
E 2

paper.${PRINTER}: ${SRCS}
	${ROFF} ${SRCS} > ${.TARGET}
E 3

.include <bsd.doc.mk>
E 1
