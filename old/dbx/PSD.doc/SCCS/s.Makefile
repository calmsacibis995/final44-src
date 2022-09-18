h00863
s 00005/00022/00005
d D 6.2 90/06/30 15:03:00 bostic 2 1
c new doc makefiles
e
s 00027/00000/00000
d D 6.1 86/05/05 16:25:27 mckusick 1 0
c date and time created 86/05/05 16:25:27 by mckusick
e
u
U
t
T
I 1
D 2
#
# Copyright (c) 1986 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
E 2
#	%W% (Berkeley) %G%
D 2
#
PRINTER=-Pdp
TROFF=	ditroff ${PRINTER}
TBL=	dtbl ${PRINTER}
LPR=	lpr -n ${PRINTER}
E 2

I 2
DIR=	ps1/11.dbx
E 2
SRCS=	dbx.ms
I 2
MACROS=	-ms
E 2

D 2
paper:	dbx.n
	${LPR} dbx.n
E 2
I 2
paper.${PRINTER}: ${SRCS}
	${TBL} ${SRCS} | ${ROFF} > ${.TARGET}
E 2

D 2
dbx.n:	${SRCS}
	${TBL} ${SRCS} | ${TROFF} -t -msU >dbx.n

clean:
	rm -f dbx.n

spell:	${SRCS}
	@for i in ${SRCS}; do \
		echo $$i; spell $$i | sort | comm -23 - spell.ok > $$i.spell; \
	done
E 2
I 2
.include <bsd.doc.mk>
E 2
E 1
