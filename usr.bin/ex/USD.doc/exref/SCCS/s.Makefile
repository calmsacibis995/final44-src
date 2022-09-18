h30250
s 00001/00001/00013
d D 8.4 94/05/23 14:19:13 mckusick 9 8
c bug fix
e
s 00002/00002/00012
d D 8.3 94/05/17 16:30:46 mckusick 8 7
c update for 4.4BSD manuals
e
s 00002/00002/00012
d D 8.2 94/04/22 08:55:08 bostic 7 6
c mv 13.ex to 12.exref; install all the sources
e
s 00000/00000/00014
d D 8.1 93/06/08 12:51:59 bostic 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00013
d D 6.5 93/06/07 20:30:15 bostic 5 4
c typo
e
s 00001/00001/00013
d D 6.4 93/06/05 17:25:31 bostic 4 3
c new doc.mk; document numbering changes for 4.4BSD
e
s 00003/00003/00011
d D 6.3 93/06/05 17:21:41 bostic 3 2
c new doc.mk; document numbering changes for 4.4BSD
e
s 00007/00023/00007
d D 6.2 90/06/30 15:09:32 bostic 2 1
c new doc makefiles
e
s 00030/00000/00000
d D 6.1 86/05/30 18:44:56 mckusick 1 0
c date and time created 86/05/30 18:44:56 by mckusick
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
E 2
I 2

D 3
DIR=	usd/16.ex
E 3
I 3
D 7
DIR=	usd/13.ex
E 3
E 2
SRCS=	ex.rm
E 7
I 7
DIR=	usd/12.exref
D 9
SRCS=	ex.rm ex.summary
E 9
I 9
SRCS=	ex.rm
E 9
E 7
D 8
MACROS=	-msU
E 8
I 8
MACROS=	-ms
E 8
D 2
PRINTER=Pdp
TBL=	dtbl -${PRINTER}
TROFF=	ditroff -${PRINTER}
E 2
I 2
CLEANFILES=summary.*
E 2

D 2
paper:	paper.${PRINTER} summary.${PRINTER}
	lpr -${PRINTER} -n paper.${PRINTER}
	lpr -${PRINTER} -n summary.${PRINTER}
E 2
I 2
D 3
paper.${PRINTER}: ${SRCS} summary.${PRINTER}
E 3
I 3
D 4
paper.ps ${SRCS} summary.${PRINTER}
E 4
I 4
D 5
paper.ps ${SRCS} summary.ps
E 5
I 5
paper.ps: ${SRCS} summary.ps
E 5
E 4
E 3
D 8
	${ROFF} ${SRCS} > ${.TARGET}
E 8
I 8
	${TBL} ${SRCS} | ${ROFF} > ${.TARGET}
E 8
E 2

D 2
paper.${PRINTER}: ${SRCS}
	${TROFF} ${MACROS} -t ${SRCS} > paper.${PRINTER}

E 2
D 3
summary.${PRINTER}: ex.summary
E 3
I 3
summary.ps: ex.summary
E 3
D 2
	${TBL} ex.summary | ${TROFF} ${MACROS} -t > summary.${PRINTER}
E 2
I 2
	${TBL} ex.summary | ${ROFF} > ${.TARGET}
E 2

D 2
clean:
	rm -f paper.[PT]* summary.[PT]* *.spell errs Errs make.out

spell:	${SRCS}
	@for i in ${SRCS}; do \
		echo $$i; spell $$i | sort | comm -23 - spell.ok > $$i.spell; \
	done
E 2
I 2
.include <bsd.doc.mk>
E 2
E 1
