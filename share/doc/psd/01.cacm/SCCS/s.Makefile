h42331
s 00000/00000/00011
d D 8.1 93/06/08 18:01:51 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00009
d D 6.4 93/06/05 15:43:54 bostic 4 3
c new doc.mk; document numbering changes for 4.4BSD
e
s 00004/00020/00007
d D 6.3 90/06/30 15:03:45 bostic 3 2
c new doc makefiles
e
s 00003/00002/00024
d D 6.2 86/04/25 01:34:14 cuccia 2 1
c added refer(1) to print references properly. --NHC
e
s 00026/00000/00000
d D 6.1 86/04/24 16:33:21 cuccia 1 0
c date and time created 86/04/24 16:33:21 by cuccia
e
u
U
t
T
I 1
D 3
#
# Copyright (c) 1986 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
E 3
#	%W% (Berkeley) %G%
D 3
#
E 3
I 3

D 4
DIR=	ps2/01.cacm
E 4
I 4
DIR=	psd/01.cacm
E 4
E 3
SRCS=	p.mac p1 p2 p3 p4 p5 p6
MACROS=	-ms
D 3
PRINTER=Pdp
TBL=	dtbl -${PRINTER}
TROFF=	ditroff -${PRINTER}
E 3
I 2
REFER=	refer -p /usr/old/dict/papers/Ind -e
E 2

D 3
paper:	paper.${PRINTER}
	lpr -${PRINTER} -n paper.${PRINTER}

E 3
D 4
paper.${PRINTER}: ${SRCS}
E 4
I 4
paper.ps: ${SRCS}
E 4
D 2
	${TBL} ${SRCS} | ${TROFF} ${MACROS} -t > paper.${PRINTER}
E 2
I 2
D 3
	${REFER} ${SRCS} | ${TBL} | ${TROFF} ${MACROS} -t > paper.${PRINTER}
E 3
I 3
	${REFER} ${SRCS} | ${TBL} | ${ROFF} > ${.TARGET}
E 3
E 2

D 3
clean:
	rm -f paper.[PT]* *.spell errs Errs make.out

spell:	${SRCS}
	@for i in ${SRCS}; do \
		echo $$i; spell $$i | sort | comm -23 - spell.ok > $$i.spell; \
	done
E 3
I 3
.include <bsd.doc.mk>
E 3
E 1
