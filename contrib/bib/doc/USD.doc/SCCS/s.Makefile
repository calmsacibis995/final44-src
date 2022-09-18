h11060
s 00000/00000/00015
d D 8.1 93/06/08 13:24:04 bostic 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00010/00022/00005
d D 6.5 93/06/07 23:49:47 bostic 5 4
c make the paper build for 4.4BSD (albeith with *lots* of errors)
e
s 00001/00001/00026
d D 6.4 90/05/28 19:54:05 samples 4 3
c Should be ready for VAXEN or SUNEN
e
s 00001/00001/00026
d D 6.3 90/05/28 19:52:17 samples 3 2
c 
e
s 00010/00009/00017
d D 6.2 90/05/28 16:55:52 samples 2 1
c added lots of notes on new tib compatibility features
e
s 00026/00000/00000
d D 6.1 86/06/02 17:06:24 mckusick 1 0
c date and time created 86/06/02 17:06:24 by mckusick
e
u
U
t
T
I 1
D 5
#
# Copyright (c) 1986 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
D 4
#	%W% (Berkeley) %G%
E 4
I 4
#	@(#)Makefile	6.3 (Berkeley) 5/28/90
E 4
#
SRCS=	bibdoc.ms
D 2
MACROS=	-msU
PRINTER=Pdp
E 2
I 2
MACROS=	-i char.macros -ms
D 3
PRINTER=Plp
E 3
I 3
PRINTER=Pps
E 3
E 2
BIB=	bib
TROFF=	ditroff -${PRINTER}
E 5
I 5
#	%W% (Berkeley) %G%
E 5

D 2
paper:	paper.${PRINTER}
E 2
I 2
D 5
paper:	paper.${PRINTER} INDEX
E 2
	lpr -${PRINTER} -n paper.${PRINTER}
E 5

D 2
paper.${PRINTER}: ${SRCS}
	${BIB} ${SRCS} | ${TROFF} ${MACROS} -t > paper.${PRINTER}
E 2
I 2
D 5
paper.${PRINTER}: ${SRCS} INDEX
	${BIB} ${SRCS} | tbl | ${TROFF} ${MACROS} -t > paper.${PRINTER}
E 5
I 5
DIR=	usd/28.bib
SRCS=	char.macros bibdoc.ms
MACROS=	-ms
CLEANFILES+=INDEX
E 5
E 2

D 5
clean:
	rm -f paper.[PT]* *.spell errs Errs make.out
E 5
I 5
paper.ps: ${SRCS} INDEX
	/usr/contrib/bin/bib -Tib ${SRCS} | ${TBL} | ${ROFF} > ${.TARGET}
E 5

D 2
spell:	${SRCS}
	@for i in ${SRCS}; do \
		echo $$i; spell $$i | sort | comm -23 - spell.ok > $$i.spell; \
	done
E 2
I 2
D 5
spell:	bibdoc.ms
	spell bibdoc.ms | sort | comm -23 - spell.ok > bibdoc.spell 

E 5
INDEX:	testrefs
D 5
	invert testrefs
E 5
I 5
	/usr/contrib/bin/invert testrefs

.include <bsd.doc.mk>
E 5
E 2
E 1
