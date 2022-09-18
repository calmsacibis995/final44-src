h41505
s 00018/00011/00021
d D 1.5 92/11/05 14:37:31 karels 5 4
c checkpoint for Mike, who is in Minnesota
e
s 00001/00001/00031
d D 1.4 89/02/24 14:50:16 karels 4 3
c add cover.t
e
s 00002/00001/00030
d D 1.3 89/02/23 22:09:29 mckusick 3 2
c need tbl to run the budget
e
s 00014/00008/00017
d D 1.2 89/02/23 21:58:59 mckusick 2 1
c add provision for volume 2
e
s 00025/00000/00000
d D 1.1 89/02/23 18:46:54 mckusick 1 0
c date and time created 89/02/23 18:46:54 by mckusick
e
u
U
t
T
I 1
#
# Copyright (c) 1989 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
#	%W% (Berkeley) %G%
#
D 2
SRCS=	A.t B.t C.t D.t E.t F.t G.t H.t I.t J.t
E 2
I 2
D 4
V1SRCS=	A.t B.t C.t D.t E.t F.t G.t H.t I.t J.t
E 4
I 4
V1SRCS=	cover.t A.t B.t C.t D.t E.t F.t G.t H.t I.t J.t
E 4
V2SRCS=	V2A.t V2B.t
E 2
MACROS=	-ms
D 5
PRINTER=Plz
I 3
TBL=	dtbl -${PRINTER}
E 3
TROFF=	ditroff -${PRINTER}
E 5
I 5
TYPE=psc
PS=ps
PRINTER=lz
TBL=	dtbl -P${TYPE}
TROFF=	ditroff -T${TYPE}
NROFF=	nroff
NTBL=	tbl
E 5

D 2
paper.${PRINTER}: ${SRCS}
	${TROFF} ${MACROS} -t ${SRCS} | psdit >paper.${PRINTER}
E 2
I 2
D 5
all: V1.${PRINTER} V2.${PRINTER}
E 5
I 5
all: V1.${PS} V2.${PS}
E 5
E 2

D 2
print: paper.${PRINTER}
	lpr -${PRINTER} paper.${PRINTER}
E 2
I 2
D 5
V1.${PRINTER}: ${V1SRCS}
	${TROFF} ${MACROS} -t ${V1SRCS} | psdit >V1.${PRINTER}
E 5
I 5
V1.${PS}: ${V1SRCS}
	${TROFF} ${PAGES} ${MACROS} -t ${V1SRCS} | psdit >$@
E 5
E 2

I 2
D 5
V2.${PRINTER}: ${V2SRCS}
D 3
	${TROFF} ${MACROS} -t ${V2SRCS} | psdit >V2.${PRINTER}
E 3
I 3
	${TBL} ${V2SRCS} | ${TROFF} ${MACROS} -t | psdit >V2.${PRINTER}
E 5
I 5
V2.${PS}: ${V2SRCS}
	${TBL} ${V2SRCS} | ${TROFF} ${PAGES} ${MACROS} -t | psdit >$@
E 5
E 3

D 5
print: V1.${PRINTER} V2.${PRINTER}
	lpr -${PRINTER} V1.${PRINTER} V2.${PRINTER}
E 5
I 5
print: V1.${PS} V2.${PS}
	lpr -P${PRINTER} V1.ps V2.ps
E 5

I 5
nroff.out: ${V1SRCS} ${V2SRCS}
	${NTBL} ${V1SRCS} ${V2SRCS} | ${NROFF} ${PAGES} ${MACROS} >$@

E 5
E 2
clean:
D 2
	rm -f *.spell errs Errs make.out paper.${PRINTER}
E 2
I 2
D 5
	rm -f *.spell errs Errs make.out V1.${PRINTER} V2.${PRINTER}
E 5
I 5
	rm -f *.spell errs Errs make.out V1.${PS} V2.${PS}
E 5
E 2

D 2
spell:	${SRCS}
	@for i in ${SRCS}; do \
E 2
I 2
spell:	${V1SRCS} ${V2SRCS}
	@for i in ${V1SRCS} ${V2SRCS}; do \
E 2
		echo $$i; spell $$i | sort | comm -23 - spell.ok > $$i.spell; \
	done
E 1
