h30706
s 00003/00003/00021
d D 8.2 94/05/16 17:55:10 mckusick 9 8
c update to work with ditroff
e
s 00000/00000/00024
d D 8.1 93/08/14 11:05:08 mckusick 8 7
c 4.4BSD snapshot (revision 8.1)
e
s 00011/00026/00013
d D 6.6 93/08/14 09:19:06 elan 7 5
c update to reduce number of documents produced
e
s 00000/00000/00039
d R 8.1 93/06/08 13:07:51 bostic 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00008/00010/00031
d D 6.5 93/06/05 17:24:44 bostic 5 4
c new doc.mk; document numbering changes for 4.4BSD
e
s 00015/00029/00026
d D 6.4 90/06/30 15:10:17 bostic 4 3
c new doc makefiles
e
s 00037/00014/00018
d D 6.3 86/04/21 14:32:30 mckusick 3 2
c aps-5 typesetting fixes
e
s 00010/00006/00022
d D 6.2 86/04/17 14:21:18 mckusick 2 1
c cannot do whole paper at once, it makes troff loop?!?
e
s 00028/00000/00000
d D 6.1 86/04/17 12:56:49 mckusick 1 0
c date and time created 86/04/17 12:56:49 by mckusick
e
u
U
t
T
I 1
D 4
#
# Copyright (c) 1986 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
E 4
#	%W% (Berkeley) %G%
D 4
#
E 4
I 4

D 5
DIR=	usd/24.troff
E 5
I 5
DIR=	usd/21.troff
E 5
E 4
D 2
#SRCS=	m.mac m0 m0a m1 m2 m3 m4 m5 table1 table2 add obsolete
SRCS=	m.mac m0 m0a m1 m2 m3 m4 m5 table1 table2
E 2
I 2
D 3
SRCS=	m.mac m0 m0a m1 m2 m3 m4 m5
APNDX=	table1 table2
E 2
MARCOS=	-msU
E 3
I 3
D 7
INTRO=	m0
TUTOR=	m0a
PAPER=	m1 m2 m3 m4
APNDX1=	m5
APNDX2=	table1
APNDX3=	table2
MACROS=	m.mac
E 7
I 7
SRCS=	m0 m0a m1 m2 m3 m4 m5
APNDX=	table1 table2
D 9
MACROS= m.mac
E 9
I 9
MACROS= m.mac -
E 9
E 7
E 3
D 4
PRINTER=Pdp
D 3
EQN=	deqn -${PRINTER}
E 3
TBL=	dtbl -${PRINTER}
TROFF=	ditroff -${PRINTER}
I 3
LPR=	lpr -n -${PRINTER}
E 4
E 3

D 2
paper:	paper.${PRINTER}
E 2
I 2
D 3
paper:	paper.${PRINTER} apndx.${PRINTER}
E 2
	lpr -${PRINTER} -n paper.${PRINTER}
I 2
	lpr -${PRINTER} -n apndx.${PRINTER}
E 3
I 3
D 4
paper:	intro.${PRINTER} tutor.${PRINTER} paper.${PRINTER}
paper:	apndx1.${PRINTER} apndx2.${PRINTER} apndx3.${PRINTER} 
	${LPR} intro.${PRINTER}
	${LPR} tutor.${PRINTER}
	${LPR} paper.${PRINTER}
	${LPR} apndx1.${PRINTER}
	${LPR} apndx2.${PRINTER}
	${LPR} apndx3.${PRINTER}
E 4
I 4
D 5
paper.${PRINTER}: intro.${PRINTER} tutor.${PRINTER} apndx1.${PRINTER} \
	apndx2.${PRINTER} apndx3.${PRINTER}
E 5
I 5
D 7
paper.ps: intro.ps tutor.ps apndx1.ps apndx2.ps apndx3.ps
E 5
	${TBL} ${PAPER} | ${ROFF} > ${.TARGET}
E 7
I 7
all: paper.ps apndx.ps
E 7
E 4
E 3
E 2

D 3
paper.${PRINTER}: ${SRCS}
	${EQN} ${SRCS} | ${TBL} | ${TROFF} ${MACROS} -t > paper.${PRINTER}
E 3
I 3
D 5
intro.${PRINTER}: ${INTRO}
E 5
I 5
D 7
intro.ps: ${INTRO}
E 5
D 4
	${TROFF} -t ${MACROS} ${INTRO} > intro.${PRINTER}
E 4
I 4
	${ROFF} ${INTRO} > ${.TARGET}
E 7
I 7
paper.ps: ${SRCS}
D 9
	${TBL} ${SRCS} | ${ROFF} - > ${.TARGET}
E 9
I 9
	${TBL} ${SRCS} | ${ROFF} > ${.TARGET}
E 9
E 7
E 4
E 3

I 2
D 3
apndx.${PRINTER}: ${APNDX}
	${EQN} ${APNDX} | ${TBL} | ${TROFF} ${MACROS} -t > apndx.${PRINTER}
E 3
I 3
D 5
tutor.${PRINTER}: ${TUTOR}
E 5
I 5
D 7
tutor.ps: ${TUTOR}
E 5
D 4
	${TBL} ${TUTOR} | ${TROFF} -t ${MACROS} - > tutor.${PRINTER}
E 4
I 4
	${TBL} ${TUTOR} | ${ROFF} > ${.TARGET}
E 7
I 7
apndx.ps: ${APNDX}
D 9
	${TBL} ${APNDX} | ${ROFF} - > ${.TARGET}
E 9
I 9
	${TBL} ${APNDX} | ${ROFF} > ${.TARGET}
E 9
E 7
E 4
E 3

I 3
D 4
paper.${PRINTER}: ${PAPER}
	${TBL} ${PAPER} | ${TROFF} -t ${MACROS} - > paper.${PRINTER}

E 4
D 5
apndx1.${PRINTER}: ${APNDX1}
E 5
I 5
D 7
apndx1.ps: ${APNDX1}
E 5
D 4
	${TROFF} -t ${MACROS} ${APNDX1} > apndx1.${PRINTER}
E 4
I 4
	${ROFF} ${APNDX1} > ${.TARGET}
E 4

D 5
apndx2.${PRINTER}: ${APNDX2}
E 5
I 5
apndx2.ps: ${APNDX2}
E 5
D 4
	${TROFF} -t ${MACROS} ${APNDX2} > apndx2.${PRINTER}
E 4
I 4
	${ROFF} ${APNDX2} > ${.TARGET}
E 4

D 5
apndx3.${PRINTER}: ${APNDX3}
E 5
I 5
apndx3.ps: ${APNDX3}
E 5
D 4
	${TROFF} -t ${MACROS} ${APNDX3} > apndx3.${PRINTER}
E 4
I 4
	${ROFF} ${APNDX3} > ${.TARGET}
E 4

E 7
E 3
E 2
clean:
D 2
	rm -f paper.${PRINTER} *.spell errs Errs make.out
E 2
I 2
D 3
	rm -f paper.${PRINTER} apndx.${PRINTER} *.spell errs Errs make.out
E 3
I 3
D 5
	rm -f intro.${PRINTER} tutor.${PRINTER} paper.${PRINTER} \
D 4
		apndx1.${PRINTER} apndx2.${PRINTER} apndx3.${PRINTER} \
		*.spell errs Errs make.out
E 4
I 4
	    apndx1.${PRINTER} apndx2.${PRINTER} apndx3.${PRINTER} \
E 5
I 5
D 7
	rm -f intro.ps tutor.ps paper.ps apndx1.ps apndx2.ps apndx3.ps \
E 5
	    *.spell errs Errs make.out
E 7
I 7
	rm -f paper.ps apndx.ps *.spell errs Errs make.out
E 7
E 4
E 3
E 2

D 2
spell:	${SRCS}
	@for i in ${SRCS}; do \
E 2
I 2
D 3
spell:	${SRCS} ${APNDX}
	@for i in ${SRCS} ${APNDX}; do \
E 3
I 3
D 4
spell:	${INTRO} ${TUTOR} ${PAPER} ${APNDX1} ${APNDX2} ${APNDX3}
E 4
I 4
D 7
spell: ${INTRO} ${TUTOR} ${PAPER} ${APNDX1} ${APNDX2} ${APNDX3}
E 4
	@for i in ${INTRO} ${TUTOR} ${PAPER} ${APNDX1} ${APNDX2} ${APNDX3}; do \
E 7
I 7
spell: ${SRCS} ${APNDX}
	@for i in ${PAPER} ${APNDX}; do \
E 7
E 3
E 2
		echo $$i; spell $$i | sort | comm -23 - spell.ok > $$i.spell; \
	done
I 4

.include <bsd.doc.mk>
E 4
E 1
