h24397
s 00001/00001/00010
d D 6.3 93/06/08 17:46:06 bostic 4 3
c new doc.mk; document numbering changes for 4.4BSD
e
s 00006/00013/00005
d D 6.2 90/06/30 15:00:19 bostic 3 2
c new doc makefiles
e
s 00004/00002/00014
d D 6.1 86/04/20 15:50:17 mckusick 2 1
c 4.3BSD release document
e
s 00016/00000/00000
d D 5.1 86/04/20 15:28:31 mckusick 1 0
c document distributed with 4.2BSD
e
u
U
t
T
I 1
D 3
#
# Copyright (c) 1983 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
E 3
#	%W% (Berkeley) %G%
D 3
#
D 2
TROFF=	itroff
E 2
I 2
TROFF=	ditroff -Pdp
TBL=	dtbl -Pdp
E 3

E 2
D 3
FILES=	abs.ms motivation.ms equip.ms methodology.ms tests.ms results.ms \
E 3
I 3
DIR=	papers/diskperf
SRCS=	abs.ms motivation.ms equip.ms methodology.ms tests.ms results.ms \
E 3
	conclusions.ms appendix.ms
I 3
MACROS=	-ms
E 3

D 3
paper:	${FILES}
D 2
	@tbl ${FILES} | ${TROFF} -ms
E 2
I 2
	${TBL} ${FILES} | ${TROFF} -ms
E 3
I 3
D 4
paper.${PRINTER}: ${SRCS}
E 4
I 4
paper.ps: ${SRCS}
E 4
	${TBL} ${SRCS} | ${ROFF} > ${.TARGET}
E 3
E 2

D 3
preview:${FILES}
	tbl ${FILES} | nroff -ms | colcrt
E 3
I 3
.include <bsd.doc.mk>
E 3
E 1
