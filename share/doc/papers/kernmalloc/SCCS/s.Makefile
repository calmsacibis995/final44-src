h44487
s 00001/00001/00010
d D 1.8 93/06/08 17:48:17 bostic 8 7
c new doc.mk; document numbering changes for 4.4BSD
e
s 00002/00003/00009
d D 1.7 93/06/08 17:47:36 bostic 7 6
c new doc.mk; document numbering changes for 4.4BSD
e
s 00001/00000/00011
d D 1.6 91/12/10 16:42:13 mckusick 6 5
c specify printer
e
s 00002/00001/00009
d D 1.5 90/07/06 01:37:59 bostic 5 4
c typo
e
s 00005/00027/00005
d D 1.4 90/06/30 15:00:49 bostic 4 3
c new doc makefiles
e
s 00002/00002/00030
d D 1.3 88/07/27 12:22:39 karels 3 2
c change to Usenix reprint format
e
s 00016/00007/00016
d D 1.2 88/04/22 17:38:26 mckusick 2 1
c lots of new preprocessors
e
s 00023/00000/00000
d D 1.1 88/02/20 16:46:14 mckusick 1 0
c date and time created 88/02/20 16:46:14 by mckusick
e
u
U
t
T
I 1
D 4
#
# Copyright (c) 1988 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
E 4
#	%W% (Berkeley) %G%
D 4
#
E 4
I 4

DIR=	papers/kernmalloc
E 4
D 2
SRCS=	kernmalloc.ms
E 2
I 2
SRCS=	kernmalloc.t appendix.t
D 4
FIGS=	alloc.fig usage.tbl
E 4
E 2
MACROS=	-ms
I 6
D 7
PRINTER=lz
E 7
E 6
D 2
PRINTER=Plz
EQN=	deqn -${PRINTER}
TROFF=	ditroff -${PRINTER}
E 2
I 2
D 4
PRINTER=lz
SOELIM=	soelim
TBL=	dtbl -P${PRINTER}
EQN=	deqn -P${PRINTER}
PIC=	pic -P${PRINTER}
GRIND=	vgrind -f
D 3
TROFF=	rsh vangogh ditroff -P${PRINTER} ${MACROS}
E 3
I 3
TROFF=	ditroff -P${PRINTER} ${MACROS}
E 4
E 3
E 2

D 2
paper: ${SRCS}
	${EQN} ${SRCS} | ${TROFF} ${MACROS}
E 2
I 2
D 4
print: paper.${PRINTER}
	lpr -P${PRINTER} -n paper.${PRINTER}
E 4
I 4
D 8
paper.${PRINTER}: ${SRCS} alloc.fig usage.tbl
E 8
I 8
paper.ps: ${SRCS} alloc.fig usage.tbl
E 8
D 5
	${SOELIM} ${SRCS} | ${TBL} | ${PIC} | ${EQN} | ${GRIND} | ${ROFF}
E 5
I 5
D 7
	${SOELIM} ${SRCS} | ${TBL} | ${PIC} | ${EQN} | ${GRIND} | ${ROFF} \
	> ${.TARGET}
E 7
I 7
	${SOELIM} ${SRCS} | ${TBL} | ${PIC} | ${EQN} | ${GRIND} | \
	    ${ROFF} > ${.TARGET}
E 7
E 5
E 4
E 2

I 2
D 4
paper.${PRINTER}: ${SRCS} ${FIGS}
	${SOELIM} ${SRCS} | ${TBL} | ${PIC} | ${EQN} | ${GRIND} | \
D 3
		${TROFF} -t - >paper.${PRINTER}
E 3
I 3
		${TROFF} -t ${PAGES} - >paper.${PRINTER}
E 3

E 2
clean:
D 2
	rm -f paper.[PT]* *.spell errs Errs make.out
E 2
I 2
	rm -f paper.${PRINTER} paper.[PT]* *.spell errs Errs make.out
E 2

spell:	${SRCS}
	@for i in ${SRCS}; do \
		echo $$i; spell $$i | sort | comm -23 - spell.ok > $$i.spell; \
	done
E 4
I 4
.include <bsd.doc.mk>
E 4
E 1
