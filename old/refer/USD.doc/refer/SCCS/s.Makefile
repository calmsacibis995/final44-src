h52571
s 00003/00003/00010
d D 8.2 94/05/20 15:41:50 mckusick 6 5
c add refer.mac; start using tbl
e
s 00000/00000/00013
d D 8.1 93/06/08 13:21:34 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00011
d D 6.4 93/06/05 17:27:46 bostic 4 3
c new doc.mk; document numbering changes for 4.4BSD
e
s 00001/00000/00012
d D 6.3 91/04/17 13:13:15 bostic 3 2
c remove biblio.ig on clean
e
s 00004/00019/00008
d D 6.2 90/06/30 15:10:40 bostic 2 1
c new doc makefiles
e
s 00027/00000/00000
d D 6.1 86/06/02 16:34:39 mckusick 1 0
c date and time created 86/06/02 16:34:39 by mckusick
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

E 2
# refer.mac should be typed on a 12 pitch Daisy wheel printer
I 2
D 4
DIR=	usd/29.refer
E 4
I 4
DIR=	usd/26.refer
E 4
E 2
D 6
SRCS=	refer.bib
MACROS=	-msU
E 6
I 6
SRCS=	refer.bib refer.mac
MACROS=	-ms
E 6
D 2
PRINTER=Pdp
E 2
REFER=	refer -p biblio
I 3
CLEANFILES=biblio.ig
E 3
D 2
TROFF=	ditroff -${PRINTER}
E 2

D 2
paper:	paper.${PRINTER}
	lpr -${PRINTER} -n paper.${PRINTER}

E 2
D 4
paper.${PRINTER}: ${SRCS}
E 4
I 4
paper.ps: ${SRCS}
E 4
D 2
	${REFER} ${SRCS} | ${TROFF} ${MACROS} -t > paper.${PRINTER}
E 2
I 2
D 6
	${REFER} ${SRCS} | ${ROFF} > ${.TARGET}
E 6
I 6
	${REFER} ${SRCS} | ${TBL} | ${ROFF} > ${.TARGET}
E 6
E 2

D 2
clean:
	rm -f paper.[PT]* *.spell errs Errs make.out

spell:	${SRCS}
	@for i in ${SRCS}; do \
		echo $$i; spell $$i | sort | comm -23 - spell.ok > $$i.spell; \
	done
E 2
I 2
.include <bsd.doc.mk>
E 2
E 1
