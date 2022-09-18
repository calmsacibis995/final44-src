h53910
s 00000/00000/00011
d D 8.1 93/06/08 18:02:53 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00009
d D 6.4 93/06/05 15:46:24 bostic 4 3
c new doc.mk; document numbering changes for 4.4BSD
e
s 00005/00023/00006
d D 6.3 90/06/30 15:04:01 bostic 3 2
c new doc makefiles
e
s 00005/00002/00024
d D 6.2 86/06/17 20:02:56 mckusick 2 1
c add pic
e
s 00026/00000/00000
d D 6.1 86/04/29 11:47:55 cuccia 1 0
c date and time created 86/04/29 11:47:55 by cuccia
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
DIR=	ps2/04.implement
E 4
I 4
DIR=	psd/02.implement
E 4
E 3
SRCS=	implement
I 2
D 3
PICFILES= fig1.pic fig2.pic
E 3
E 2
MACROS=	-ms
D 3
PRINTER=Pdp
TROFF=	ditroff -${PRINTER}
E 3
REFER=	refer -p /usr/old/dict/papers/Ind -e
I 2
D 3
PIC= pic -${PRINTER}
E 3
E 2

D 3
paper:	paper.${PRINTER}
	lpr -${PRINTER} -n paper.${PRINTER}
E 3
I 3
D 4
paper.${PRINTER}: ${SRCS} fig1.pic fig2.pic
E 4
I 4
paper.ps: ${SRCS} fig1.pic fig2.pic
E 4
	${SOELIM} ${SRCS} | ${REFER} | ${PIC} | ${ROFF} > ${.TARGET}
E 3

D 2
paper.${PRINTER}: ${SRCS}
	${REFER} ${SRCS} | ${TROFF} ${MACROS} -t > paper.${PRINTER}
E 2
I 2
D 3
paper.${PRINTER}: ${SRCS} ${PICFILES}
	soelim   ${SRCS} > paper.pic
	${REFER} paper.pic | ${PIC} | ${TROFF} ${MACROS} -t > paper.${PRINTER}
E 2

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
