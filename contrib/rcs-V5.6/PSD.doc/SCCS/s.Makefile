h44374
s 00001/00001/00009
d D 8.2 94/05/24 11:26:30 mckusick 4 3
c use the correct macro package
e
s 00001/00001/00009
d D 8.1 93/08/14 10:13:56 mckusick 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00003/00000/00007
d D 1.2 93/08/02 12:23:09 elan 2 1
c Needed soelim, pic and tbl for paper.ps.
e
s 00007/00000/00000
d D 1.1 93/07/30 14:04:16 elan 1 0
c date and time created 93/07/30 14:04:16 by elan
e
u
U
t
T
I 1
D 3
#	@(#)Makefile	8.1 (Berkeley) 6/8/93
E 3
I 3
#	%W% (Berkeley) %G%
E 3

DIR=	psd/13.rcs
SRCS=	rcs.ms
D 4
MACROS=	-msU
E 4
I 4
MACROS=	-ms
E 4

I 2
paper.ps: ${SRCS} ${DPADD}
	${SOELIM} ${SRCS} | ${PIC} | ${TBL} | ${ROFF} > ${.TARGET}

E 2
.include <bsd.doc.mk>
E 1
